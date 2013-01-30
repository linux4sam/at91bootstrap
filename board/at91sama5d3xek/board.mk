$(shell $(CC) --target-help > tmp.file)
gcc_cortexa5=$(shell grep cortex-a5 tmp.file)

ifeq (, $(findstring cortex-a5,$(gcc_cortexa5)))
CPPFLAGS += -DCONFIG_AT91SAMA5D3XEK

ASFLAGS += \
	-DCONFIG_AT91SAMA5D3XEK
else
CPPFLAGS += \
	-DCONFIG_AT91SAMA5D3XEK \
	-mtune=cortex-a5

ASFLAGS += \
	-DCONFIG_AT91SAMA5D3XEK
	-mcpu=cortex-a5
endif

$(shell rm tmp.file)
