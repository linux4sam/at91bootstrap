$(shell $(CC) --target-help > tmp.file)
gcc_cortexa5=$(shell grep cortex-a5 tmp.file)

ifeq (, $(findstring cortex-a5,$(gcc_cortexa5)))
CPPFLAGS += -DCONFIG_SAMA5D31_BEEAVE

ASFLAGS += \
	-DCONFIG_SAMA5D31_BEEAVE
else
CPPFLAGS += \
	-DCONFIG_SAMA5D31_BEEAVE \
	-mtune=cortex-a5

ASFLAGS += \
	-DCONFIG_SAMA5D31_BEEAVE
	-mcpu=cortex-a5
endif

$(shell rm tmp.file)

#Add MMU support
COBJS-$(CONFIG_WITH_MMU) += $(TOPDIR)/board/$(BOARDNAME)/driver/CP15.o
SOBJS-$(CONFIG_WITH_MMU) += $(TOPDIR)/board/$(BOARDNAME)/driver/cp15_asm_gcc.o
COBJS-$(CONFIG_WITH_MMU) += $(TOPDIR)/board/$(BOARDNAME)/driver/mmu.o

ifeq ($(CONFIG_WITH_MMU),y)
CPPFLAGS += -I$(TOPDIR)/board/$(BOARDNAME)/driver
endif

#Add DMA support file
COBJS-$(CONFIG_DATAFLASH_LOAD_WITH_DMA) += $(TOPDIR)/board/$(BOARDNAME)/dma_hardware_interface.o


#Add the memory lowlevel init code according to the actual type : only LP-DDR1 !
COBJS-$(CONFIG_LPDDR1) += $(TOPDIR)/board/$(BOARDNAME)/lpddr1.o
COBJS-$(CONFIG_RAM_CHIP_IS43LR32800) += $(TOPDIR)/board/$(BOARDNAME)/is43lr32800.o
COBJS-$(CONFIG_RAM_CHIP_W948D2) += $(TOPDIR)/board/$(BOARDNAME)/wd948d2.o
