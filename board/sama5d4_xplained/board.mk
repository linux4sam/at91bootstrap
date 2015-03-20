gcc_cortexa5=$(shell $(CC) --target-help | grep cortex-a5)

ifeq (, $(findstring cortex-a5,$(gcc_cortexa5)))
CPPFLAGS += -DCONFIG_SAMA5D4_XPLAINED

ASFLAGS += \
	-DCONFIG_SAMA5D4_XPLAINED
else
CPPFLAGS += \
	-DCONFIG_SAMA5D4_XPLAINED \
	-mcpu=cortex-a5

ASFLAGS += \
	-DCONFIG_SAMA5D4_XPLAINED \
	-mcpu=cortex-a5
endif
