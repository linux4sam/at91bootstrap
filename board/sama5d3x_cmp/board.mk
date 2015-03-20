gcc_cortexa5=$(shell $(CC) --target-help | grep cortex-a5)

ifeq (, $(findstring cortex-a5,$(gcc_cortexa5)))
CPPFLAGS += -DCONFIG_SAMA5D3X_CMP

ASFLAGS += \
	-DCONFIG_SAMA5D3X_CMP
else
CPPFLAGS += \
	-DCONFIG_SAMA5D3X_CMP \
	-mcpu=cortex-a5 \
	-mtune=cortex-a5

ASFLAGS += \
	-DCONFIG_SAMA5D3X_CMP \
	-mcpu=cortex-a5
endif
