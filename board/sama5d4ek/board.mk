gcc_cortexa5=$(shell $(CC) --target-help | grep cortex-a5)

ifeq (, $(findstring cortex-a5,$(gcc_cortexa5)))
CPPFLAGS += -DCONFIG_SAMA5D4EK

ASFLAGS += \
	-DCONFIG_SAMA5D4EK
else
CPPFLAGS += \
	-DCONFIG_SAMA5D4EK \
	-mcpu=cortex-a5

ASFLAGS += \
	-DCONFIG_SAMA5D4EK \
	-mcpu=cortex-a5
endif
