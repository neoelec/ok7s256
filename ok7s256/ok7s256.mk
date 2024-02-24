OK7S256_MK_FILE	:= $(realpath $(lastword $(MAKEFILE_LIST)))
OK7S256_PATH	:= $(shell dirname $(OK7S256_MK_FILE))

CHIP		:= at91sam7s256
BOARD		:= ok-7s256
REF_BOARD	:= at91sam7s-ek

OK7S256LIB	:= $(OK7S256_PATH)/libs
INCLUDES	+= -I$(OK7S256LIB)
VPATH		+= $(OK7S256LIB)

LIBRARIES	:= -lm

include $(OK7S256_PATH)/../at91.mk
include $(OK7S256_PATH)/../jlink.mk
