$(shell $(CC) --target-help > tmp.file)
gcc_cortexa5=$(shell grep cortex-a5 tmp.file)

ifeq (, $(findstring cortex-a5,$(gcc_cortexa5)))
CPPFLAGS += -DCONFIG_SAMA5D3XEK

ASFLAGS += \
	-DCONFIG_SAMA5D3XEK
else
CPPFLAGS += \
	-DCONFIG_SAMA5D3XEK \
	-mtune=cortex-a5

ASFLAGS += \
	-DCONFIG_SAMA5D3XEK
	-mcpu=cortex-a5
endif

$(shell rm tmp.file)

#Add MMU support helpers
COBJS-$(CONFIG_WITH_MMU) += $(TOPDIR)/board/$(BOARDNAME)/CP15.o

#Add Support assembler file
SOBJS-$(CONFIG_WITH_MMU) += $(TOPDIR)/board/$(BOARDNAME)/cp15_asm_gcc.o

#Add DMA support file
COBJS-$(CONFIG_DATAFLASH_LOAD_WITH_DMA) += $(TOPDIR)/board/$(BOARDNAME)/dma_hardware_interface.o
