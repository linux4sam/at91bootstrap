# Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
#
# SPDX-License-Identifier: MIT

CPPFLAGS += \
	-DMACH_TYPE=$(MACH_TYPE) 		\
	-DTOP_OF_MEMORY=$(TOP_OF_MEMORY)

ASFLAGS += \
	-DMACH_TYPE=$(MACH_TYPE) 		\
	-DTOP_OF_MEMORY=$(TOP_OF_MEMORY)

include device/chips.mk

ifeq ($(CONFIG_THUMB),y)
CPPFLAGS += -DCONFIG_THUMB -mthumb -mthumb-interwork
ASFLAGS += -DCONFIG_THUMB -mthumb-interwork
endif
