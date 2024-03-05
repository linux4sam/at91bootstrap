# Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
#
# SPDX-License-Identifier: MIT

ifeq ($(CONFIG_CORE_ARM926EJS), y)
ifeq ($(CROSS_COMPILE),xc32-)
ifeq ($(CONFIG_SAM9X60),y)
CPPFLAGS += -mprocessor=ATSAM9X60 -mfloat-abi=soft
ASFLAGS += -mprocessor=ATSAM9X60 -mfloat-abi=soft
endif
else
CPPFLAGS += -mcpu=arm926ej-s -mtune=arm926ej-s -mfloat-abi=soft
ASFLAGS += -mcpu=arm926ej-s -mtune=arm926ej-s -mfloat-abi=soft
endif
endif

ifeq ($(CONFIG_CORE_CORTEX_A5), y)
ifeq ($(CROSS_COMPILE),xc32-)
ifeq ($(CONFIG_SAMA5D2),y)
CPPFLAGS += -mprocessor=ATSAMA5D27
ASFLAGS += -mprocessor=ATSAMA5D27
endif
else
CPPFLAGS += -mcpu=cortex-a5 -mtune=cortex-a5 -mfpu=vfpv4-d16
ASFLAGS += -mcpu=cortex-a5 -mtune=cortex-a5 -mfpu=vfpv4-d16
endif
endif

ifeq ($(CONFIG_CORE_CORTEX_A7), y)
ifeq ($(CROSS_COMPILE),xc32-)
ifeq ($(CONFIG_SAMA7G5),y)
CPPFLAGS += -mprocessor=SAMA7G54
ASFLAGS += -mprocessor=SAMA7G54
else ifeq ($(CONFIG_SAMA7D65),y)
CPPFLAGS += -mprocessor=SAMA7D65
ASFLAGS += -mprocessor=SAMA7D65
endif
else
CPPFLAGS += -mcpu=cortex-a7 -mtune=cortex-a7 -mfpu=vfpv4-d16
ASFLAGS += -mcpu=cortex-a7 -mtune=cortex-a7 -mfpu=vfpv4-d16
endif
endif
