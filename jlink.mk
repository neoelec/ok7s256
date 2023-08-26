JLINK_PATH	:= /opt/SEGGER/JLink

JFLASHEXE	:= $(JLINK_PATH)/JFlashExe
JLINKGDBEXE	:= $(JLINK_PATH)/JLinkGDBServerCLExe

JLINKCHIP	:= $(shell echo $(CHIP) | tr  '[:lower:]' '[:upper:]')
JFLASHFLAGS	:= -openprj $(JLINK_PATH)/Samples/JFlash/ProjectFiles/Atmel/$(JLINKCHIP).jflash
JLINKGDBFLAGS	:= -device $(JLINKCHIP)

define JLINK_RULES
CMM_$(1)	:= $(OUTPUT)-$(1).cmm
$$(CMM_$(1)): $$(ELF_$(1))
	@echo "B::" > $$@
	@echo "PRIVATE &os_ppd" >> $$@
	@echo "&os_ppd=OS.PresentPracticeDirectory()" >> $$@
	@echo "sYmbol.Delete" >> $$@
	@echo "Data.LOAD.Elf &os_ppd/"`basename $$<`" /NoCODE" >> $$@
	@echo "ENDDO" >> $$@

$(1): $$(CMM_$(1))

jflash_$(1): $(1)
	@$(JFLASHEXE) $(JFLASHFLAGS) -open $$(BIN_$(1)),`cat $$(LD_SCRIPT_$(1)) | \
			grep -E '$(1).+ORIGIN' | \
			perl -pe 's/^.+ORIGIN\s*=\s*(\S+)\s*,.+$$$$/$$$$1/'` \
		-auto -startapp -exit

jlinkgdb_$(1): $(1)
	@$(JLINKGDBEXE) -select USB=0  $(JLINKGDBFLAGS) \
		-endian little -if JTAG -speed 4000 -noir -noLocalhostOnly -nologtofile \
		-port 2331 -SWOPort 2332 -TelnetPort 2333

endef

$(foreach MEMORY, $(MEMORIES), $(eval $(call JLINK_RULES,$(MEMORY))))
