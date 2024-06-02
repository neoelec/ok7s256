JLINK_PATH	:= /opt/SEGGER/JLink

JFLASHEXE	:= $(JLINK_PATH)/JFlashExe
JLINKGDBEXE	:= $(JLINK_PATH)/JLinkGDBServerCLExe

JLINKCHIP	:= $(shell echo $(CHIP) | tr  '[:lower:]' '[:upper:]')
JFLASHFLAGS	:= -openprj $(JLINK_PATH)/Samples/JFlash/ProjectFiles/Atmel/$(JLINKCHIP).jflash
JLINKGDBFLAGS	:= -device $(JLINKCHIP)

define JLINK_RULES
jflash_$(1): $(1)
	@$(JFLASHEXE) $(JFLASHFLAGS) -open $$(BIN_$(1)),`cat $$(LD_SCRIPT_$(1)) | \
			grep -E '$(1).+ORIGIN' | \
			perl -pe 's/^.+ORIGIN\s*=\s*(\S+)\s*,.+$$$$/$$$$1/'` \
		-auto -startapp -exit

jlinkgdb_$(1): $(1)
	@echo "B::" > target.cmm
	@echo 'PRIVATE &E_Func &E_Args' >> target.cmm
	@echo 'ENTRY &E_Func %LINE &E_Args' >> target.cmm
	@echo 'PRIVATE &ret' >> target.cmm
	@echo '&G_RCN_PWD=OS.PresentPracticeDirectory()' >> target.cmm
	@echo 'ChDir &G_RCN_PWD' >> target.cmm
	@echo '&G_RCN_Baremetal_Elf_File="$(OUTPUT)-$(1).elf"' >> target.cmm
	@echo 'DO $(AT91_PATH)/debug.cmm &E_Func &E_Args' >> target.cmm
	@echo 'ENTRY &ret' >> target.cmm
	@echo 'ENDDO &ret' >> target.cmm
	@$(JLINKGDBEXE) -select USB=0  $(JLINKGDBFLAGS) \
		-endian little -if JTAG -speed 4000 -noir -noLocalhostOnly -nologtofile \
		-port 2331 -SWOPort 2332 -TelnetPort 2333

endef

$(foreach MEMORY, $(MEMORIES), $(eval $(call JLINK_RULES,$(MEMORY))))
