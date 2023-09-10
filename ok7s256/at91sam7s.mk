# ----------------------------------------------------------------------------
#         ATMEL Microcontroller Software Support
# ----------------------------------------------------------------------------
# Copyright (c) 2008, Atmel Corporation
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# - Redistributions of source code must retain the above copyright notice,
# this list of conditions and the disclaimer below.
#
# Atmel's name may not be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
# DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
# OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# ----------------------------------------------------------------------------

COMMON_MK_FILE	:= $(realpath $(lastword $(MAKEFILE_LIST)))
PROJECT_PATH	:= $(shell dirname $(COMMON_MK_FILE))

# 	Makefile for compiling the Getting Started project

#-------------------------------------------------------------------------------
#		User-modifiable options
#-------------------------------------------------------------------------------

#TARGET		:=

# Chip & board used for compilation
# (can be overriden by adding CHIP=chip and BOARD=board to the command-line)
CHIP		:= at91sam7s256
BOARD		:= ok-7s256
REF_BOARD	:= at91sam7s-ek

# Trace level used for compilation
# (can be overriden by adding TRACE_LEVEL=#number to the command-line)
# TRACE_LEVEL_DEBUG      5
# TRACE_LEVEL_INFO       4
# TRACE_LEVEL_WARNING    3
# TRACE_LEVEL_ERROR      2
# TRACE_LEVEL_FATAL      1
# TRACE_LEVEL_NO_TRACE   0
TRACE_LEVEL	:= 0

# Optimization level, put in comment for debugging
OPTIMIZATION	:= -Os

# AT91 library directory
AT91LIB		:= $(PROJECT_PATH)/../at91lib

# OK-7s256 library directory
OK7S256LIB	:= $(PROJECT_PATH)/ok7s256_lib

# Output file basename
OUTPUT		:= $(TARGET)-$(BOARD)-$(CHIP)

# J-Link
JLINK		:= /opt/SEGGER/JLink

# Compile for all memories available on the board (this sets $(MEMORIES))
include $(AT91LIB)/boards/$(BOARD)/board.mak

# Output directories
BIN		:= bin
OBJ		:= obj

#-------------------------------------------------------------------------------
#		Tools
#-------------------------------------------------------------------------------

# Tool suffix when cross-compiling
CROSS_COMPILE	:= arm-none-eabi-

# Compilation tools
CC		:= $(CROSS_COMPILE)gcc
SIZE		:= $(CROSS_COMPILE)size
STRIP		:= $(CROSS_COMPILE)strip
OBJCOPY		:= $(CROSS_COMPILE)objcopy
JFLASHEXE	:= $(JLINK)/JFlashExe

# Flags
CFLAGS		:= -Wall -mlong-calls -ffunction-sections --param=min-pagesize=0
CFLAGS		+= -D$(CHIP) -DTRACE_LEVEL=$(TRACE_LEVEL)
ASFLAGS		:= -D$(CHIP) -D__ASSEMBLY__
LDFLAGS		:= -nostartfiles -Wl,--gc-sections
JFLASHFLAGS	:= -openprj $(JLINK)/Samples/JFlash/ProjectFiles/Atmel/$(shell echo $(CHIP) | tr  '[:lower:]' '[:upper:]').jflash

#-------------------------------------------------------------------------------
#		Files
#-------------------------------------------------------------------------------

# Directories where source files can be found
BOARDS		:= $(AT91LIB)/boards
DRV		:= $(AT91LIB)/drivers
PERIPH		:= $(AT91LIB)/peripherals
UTILITY		:= $(AT91LIB)/utility

INCLUDES	:= -I$(AT91LIB)
INCLUDES	+= -I$(AT91LIB)/boards/$(BOARD)
INCLUDES	+= -I$(AT91LIB)/peripherals
INCLUDES	+= -I$(OK7S256LIB)

VPATH		+= $(BOARDS)/$(BOARD) $(BOARDS)/$(BOARD)/$(CHIP)
VPATH		+= $(PERIPH)/dbgu
VPATH		+= $(PERIPH)/cp15
VPATH		+= $(PERIPH)/rstc
VPATH		+= $(UTILITY)
VPATH		+= $(OK7S256LIB)

# Objects built from C source files
#C_OBJECTS	:= $(TARGET).o
C_OBJECTS	+= stdio.o dbgu.o cp15.o rstc.o
C_OBJECTS	+= board_memories.o board_lowlevel.o

# Objects built from Assembly source files
ASM_OBJECTS	+= board_cstartup.o
ASM_OBJECTS	+= cp15_asm.o

LIBRARIES	:= -lm

# Append OBJ and BIN directories to output filename
OUTPUT		:= $(BIN)/$(OUTPUT)

#-------------------------------------------------------------------------------
#		Rules
#-------------------------------------------------------------------------------

all: $(MEMORIES)

$(MEMORIES): $(BIN) $(OBJ)

$(BIN) $(OBJ):
	mkdir $@

define RULES
C_OBJECTS_$(1)	:= $(addprefix $(OBJ)/$(1)_, $(C_OBJECTS))
ASM_OBJECTS_$(1):= $(addprefix $(OBJ)/$(1)_, $(ASM_OBJECTS))
LD_SCRIPT_$(1)	:= $(AT91LIB)/boards/$(REF_BOARD)/$(CHIP)/$(1).lds

ELF_$(1)	:= $(OUTPUT)-$(1).elf
$$(ELF_$(1)): $$(ASM_OBJECTS_$(1)) $$(C_OBJECTS_$(1))
	$(CC) -g $(OPTIMIZATION) $(LDFLAGS) -T"$$(LD_SCRIPT_$(1))" \
		-o $$@ $$^ $(LIBRARIES)
	$(SIZE) $$^ $$@

BIN_$(1)	:= $(OUTPUT)-$(1).bin
$$(BIN_$(1)): $$(ELF_$(1))
	$(OBJCOPY) -O binary $$< $$@

$(1): $$(BIN_$(1))

$$(C_OBJECTS_$(1)): $(OBJ)/$(1)_%.o: %.c Makefile $(COMMON_MK_FILE)
	$(CC) -g $(OPTIMIZATION) $(INCLUDES) $(CFLAGS) -D$(1) -c -o $$@ $$<

$$(ASM_OBJECTS_$(1)): $(OBJ)/$(1)_%.o: %.S Makefile $(COMMON_MK_FILE)
	$(CC) -g $(OPTIMIZATION) $(INCLUDES) $(ASFLAGS) -D$(1) -c -o $$@ $$<

program_$(1): $(1)
	$(JFLASHEXE) $(JFLASHFLAGS) -open $$(BIN_$(1)),`cat $$(LD_SCRIPT_$(1)) | \
			grep -E '$(1).+ORIGIN' | \
			perl -pe 's/^.+ORIGIN\s*=\s*(\S+)\s*,.+$$$$/$$$$1/'` \
		-auto -startapp -exit

endef

$(foreach MEMORY, $(MEMORIES), $(eval $(call RULES,$(MEMORY))))

clean:
	@rm -rf $(OBJ)/ $(BIN)/ $(BIN)/
