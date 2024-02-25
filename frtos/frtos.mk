FRTOS_MK_FILE	:= $(realpath $(lastword $(MAKEFILE_LIST)))
FRTOS_PATH	:= $(shell dirname $(FRTOS_MK_FILE))

CHIP		:= at91sam7s256
BOARD		:= ok-7s256
REF_BOARD	:= at91sam7s-ek

FRTOSLIB	:= $(FRTOS_PATH)/libs
INCLUDES	+= -I$(FRTOSLIB)
VPATH		+= $(FRTOSLIB)
CFLAGS		+= -D__AT91LIB_FREERTOS__
ASFLAGS		+= -D__AT91LIB_FREERTOS__
C_OBJECTS	+= aic.o pit.o

FREERTOS_PATH		:= $(HOME)/iHDD00/07.WORKSPACE/FreeRTOS-LTS/FreeRTOS
FREERTOS_KERNEL_PATH	:= $(FREERTOS_PATH)/FreeRTOS-Kernel
INCLUDES		+= -I$(FREERTOS_KERNEL_PATH)/include
VPATH			+= $(FREERTOS_KERNEL_PATH)
VPATH			+= $(FREERTOS_KERNEL_PATH)/portable/MemMang
C_OBJECTS		+= croutine.o event_groups.o list.o queue.o stream_buffer.o tasks.o timers.o
C_OBJECTS		+= heap_1.o

FREERTOS_PORT_PATH	:= $(FRTOS_PATH)/portable/GCC/ARM7_AT91SAM7S
INCLUDES		+= -I$(FREERTOS_PORT_PATH)
VPATH			+= $(FREERTOS_PORT_PATH)
C_OBJECTS		+= port.o portISR.o

include $(FRTOS_PATH)/../at91.mk
include $(FRTOS_PATH)/../jlink.mk
