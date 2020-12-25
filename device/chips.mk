ifeq ($(CONFIG_CORE_ARM926EJS), y)
CPPFLAGS += -mcpu=arm926ej-s -mtune=arm926ej-s -mfloat-abi=soft
ASFLAGS += -mcpu=arm926ej-s -mtune=arm926ej-s -mfloat-abi=soft
endif

ifeq ($(CONFIG_CORE_CORTEX_A5), y)
CPPFLAGS += -mcpu=cortex-a5 -mtune=cortex-a5
ASFLAGS += -mcpu=cortex-a5 -mtune=cortex-a5
endif

ifeq ($(CONFIG_CORE_CORTEX_A7), y)
CPPFLAGS += -mcpu=cortex-a7 -mtune=cortex-a7
ASFLAGS += -mcpu=cortex-a7 -mtune=cortex-a7
endif
