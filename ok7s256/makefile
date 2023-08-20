#==============================================================================
#  *** WinARM template makefile ***
#
#  by Martin Thomas, Kaiserslautern, Germany 
#  based on the WinAVR makefile written by Eric B. Weddington, Jorg Wunsch, et al.
#------------------------------------------------------------------------------
# Command line: Make All   = Build user program.
#               Make Clean = Clean files in project.
#
# Changelog: - 17. Feb. 2005 - added thumb-interwork support (mth)
#            - 28. Apr. 2005 - added C++ support (mth)
#            - 29. Arp. 2005 - changed handling for lst-Filename (mth)
#            - 01. May. 2007 - modified for OK-7S256 Kit(D.Y. Yoon)
#==============================================================================

#----- MCU name and submodel. -------------------------------------------------
MCU = arm7tdmi
SUBMDL = AT91SAM7S256
#THUMB = -mthumb

#----- Target memory model. (ROM=final, RAM=debugging)
RUN_MODE=ROM_RUN
#RUN_MODE=RAM_RUN

#----- Output file format. (binary or ihex)
FORMAT = binary
#FORMAT = ihex

#----- Current project name.
PROJECT1 = $(PROJ)
PROJECT2 = $(notdir $(PROJECT1))
PROJECT = $(PROJECT2:.pnproj=)

#----- Target file name without extension.
#TARGET = main

#----- List Assembler source files here.(Make them always end in a capital .S.)
ASRC = 

#----- List Assembler source files here which must be assembled in ARM-Mode.
ASRCARM = Cstartup.S 

#----- List C source files here. (C dependencies are automatically generated.)
SRC = 

#----- List C source files here which must be compiled in ARM-Mode.
SRCARM = Cstartup_SAM7.c $(TARGET).c

#----- Optimization level.(0, 1, 2, 3, s)
OPT = s

#----- Debugging file format.
DEBUG = dwarf-2
#DEBUG = stabs

#----- Compiler flag to set the C Standard level.
#      c89   - ANSI C
#      gnu89 - c89 plus GCC extensions
#      c99   - ISO C99 standard (not yet fully implemented)
#      gnu99 - c99 plus GCC extensions
CSTANDARD = -std=gnu99

#----- -D or -U options for ASM.
ADEFS = -D$(RUN_MODE)

#----- -D or -U options for C.
CDEFS = -D$(RUN_MODE)

#----- -I options.
CINCS =

#----- Assembler flags. -------------------------------------------------------
#      -Wa,... : tell GCC to pass this to the assembler.
#      -ahlms  : create listing
#      -gstabs : have the assembler create line number information
ASFLAGS = $(ADEFS) -Wa,-adhlns=$(<:.S=.lst),-g$(DEBUG)

#----- Compiler flags.
#      -g*        : generate debugging information
#      -O*        : optimization level
#      -Wall...   : warning level
#      -Wa,...    : tell GCC to pass this to the assembler.
#      -adhlns... : create assembler listing
CFLAGS = -g$(DEBUG)
CFLAGS += $(CDEFS) $(CINCS)
CFLAGS += -O$(OPT)
CFLAGS += -Wall -Wcast-align -Wimplicit 
CFLAGS += -Wpointer-arith -Wswitch
CFLAGS += -Wredundant-decls -Wreturn-type -Wshadow -Wunused
CFLAGS += -Wa,-adhlns=$(subst $(suffix $<),.lst,$<) 

#----- flags only for C
CONLYFLAGS += -Wnested-externs 
CONLYFLAGS += $(CSTANDARD)

#----- Compiler flags to generate dependency files.
GENDEPFLAGS = -MD -MP -MF .dep/$(@F).d

#----- Combine all necessary flags and optional flags.
ALL_ASFLAGS = -mcpu=$(MCU) $(ASFLAGS)
ALL_CFLAGS = -mcpu=$(MCU) $(CFLAGS) $(GENDEPFLAGS)

#----- Linker flags.
#      -Wl,... : tell GCC to pass this to linker.
#      -Map    : create map file
#      --cref  : add cross reference to map file
LDFLAGS = -nostartfiles -Wl,-Map=$(PROJECT).map,--cref
LDFLAGS += -lc -lgcc -lm

#----- Set linker-script depending on target memory model.
ifeq ($(RUN_MODE),RAM_RUN)
LDFLAGS += -T$(SUBMDL)-RAM.ld
else 
LDFLAGS += -T$(SUBMDL)-ROM.ld
endif

#----- Define Messages in English. --------------------------------------------
MSG_CLEANING = Cleaning files in project:
MSG_ASSEMBLING = Assembling:
MSG_ASSEMBLING_ARM = "Assembling (ARM-only):"
MSG_COMPILING = Compiling C:
MSG_COMPILING_ARM = "Compiling C (ARM-only):"
MSG_LINKING = Linking:
MSG_FLASH = Creating load file for flash:
MSG_SYMBOL_TABLE = Creating symbol table:
MSG_EXTENDED_LISTING = Creating extended listing:
MSG_FILESIZE = ELF file size:
MSG_TARGETSIZE = Target file size:

#----- Define programs and commands. ------------------------------------------
CC = arm-elf-gcc
OBJCOPY = arm-elf-objcopy
OBJDUMP = arm-elf-objdump
NM = arm-elf-nm
SIZE = arm-elf-size
REMOVE = rm -f

#----- Define all object files.
AOBJ = $(ASRC:.S=.o)
COBJ = $(SRC:.c=.o) 
AOBJARM = $(ASRCARM:.S=.o)
COBJARM = $(SRCARM:.c=.o)

#----- Link: create ELF output file from object files.
%.elf:  $(AOBJARM) $(AOBJ) $(COBJARM) $(COBJ)
	@echo
	@echo $(MSG_LINKING) $@
	$(CC) $(ALL_CFLAGS) $(AOBJARM) $(AOBJ) $(COBJARM) $(COBJ) --output $@ $(LDFLAGS)

#----- Create final output file (.bin) from ELF output file.
%.bin: %.elf
	@echo
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O $(FORMAT) $< $@

#----- Create final output files (.hex) from ELF output file.
%.hex: %.elf
	@echo
	@echo $(MSG_FLASH) $@
	$(OBJCOPY) -O $(FORMAT) $< $@

#----- Create extended listing file(.lss) from ELF output file.
%.lss: %.elf
	@echo
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -S -C $< > $@

#----- Create symbol table file(.sym) from ELF output file.
%.sym: %.elf
	@echo
	@echo $(MSG_SYMBOL_TABLE) $@
	$(NM) -n $< > $@

#----- Assemble: create object files from assembler source files.(ARM/Thumb)
$(AOBJ): %.o : %.S
	@echo
	@echo $(MSG_ASSEMBLING) $<
	$(CC) -c $(THUMB) $(ALL_ASFLAGS) $< -o $@

#----- Assemble: create object files from assembler source files.(ARM-only)
$(AOBJARM): %.o : %.S
	@echo
	@echo $(MSG_ASSEMBLING_ARM) $<
	$(CC) -c $(ALL_ASFLAGS) $< -o $@

#----- Compile: create object files from C source files.(ARM/Thumb)
$(COBJ): %.o : %.c
	@echo
	@echo $(MSG_COMPILING) $<
	$(CC) -c $(THUMB) $(ALL_CFLAGS) $(CONLYFLAGS) $< -o $@ 

#----- Compile: create object files from C source files.(ARM-only)
$(COBJARM): %.o : %.c
	@echo
	@echo $(MSG_COMPILING_ARM) $<
	$(CC) -c $(ALL_CFLAGS) $(CONLYFLAGS) $< -o $@ 

#----- Clean files in project. ------------------------------------------------
clean:
	@echo
	@echo $(MSG_CLEANING)
	$(REMOVE) .dep/* | exit 0
	$(REMOVE) *.o   | exit 0
	$(REMOVE) *.bin | exit 0
	$(REMOVE) *.hex | exit 0
	$(REMOVE) *.elf | exit 0
	$(REMOVE) *.lss | exit 0
	$(REMOVE) *.lst | exit 0
	$(REMOVE) *.map | exit 0
	$(REMOVE) *.sym | exit 0
	@echo

#----- Build user program. ----------------------------------------------------
all: gccversion build filesize

#----- Display compiler version information.
gccversion :
	@echo
	@$(CC) --version

#----- Build program.
ifeq ($(FORMAT),binary)
build: elf bin lss sym
else 
build: elf hex lss sym
endif

elf: $(PROJECT).elf
bin: $(PROJECT).bin
hex: $(PROJECT).hex
lss: $(PROJECT).lss
sym: $(PROJECT).sym

#----- Display file size.
ELFSIZE = $(SIZE) -A -x $(PROJECT).elf
BINSIZE = $(SIZE) --target=$(FORMAT) $(PROJECT).bin
HEXSIZE = $(SIZE) --target=$(FORMAT) $(PROJECT).hex

filesize:
	@echo
	@if [ -f $(PROJECT).elf ]; then echo; echo $(MSG_FILESIZE); $(ELFSIZE); fi
        ifeq ($(FORMAT),binary)
	@echo $(MSG_TARGETSIZE); $(BINSIZE); fi
        else 
	@echo $(MSG_TARGETSIZE); $(HEXSIZE); fi
        endif
