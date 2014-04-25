# Makefile for AT91-Bootstrap drivers directory
# DIRS				+= drivers

DRIVERS:=
DRIVERS_SRC:=$(TOPDIR)/driver

COBJS-$(CONFIG_DEBUG)		+= $(DRIVERS_SRC)/debug.o

COBJS-$(CONFIG_SCLK)		+= $(DRIVERS_SRC)/at91_slowclk.o

COBJS-y				+= $(DRIVERS_SRC)/at91_pio.o
COBJS-y				+= $(DRIVERS_SRC)/pmc.o
COBJS-y				+= $(DRIVERS_SRC)/at91_pit.o
COBJS-y				+= $(DRIVERS_SRC)/at91_wdt.o
COBJS-y				+= $(DRIVERS_SRC)/at91_usart.o

#Provide a stub implementation. otherwise : done in each board directory.
ifeq ($(CONFIG_USER_HW_INIT),)
COBJS-$(CONFIG_USER_HW_INIT)	+= $(DRIVERS_SRC)/hw_init_hook.o
endif

#Only if external RAM used.
ifeq ($(CONFIG_ONLY_INTERNAL_RAM),)
COBJS-$(CONFIG_SDRAM)		+= $(DRIVERS_SRC)/sdramc.o
COBJS-$(CONFIG_SDDRC)		+= $(DRIVERS_SRC)/sddrc.o
COBJS-$(CONFIG_DDR2)		+= $(DRIVERS_SRC)/ddramc_DDR2.o
COBJS-$(CONFIG_LPDDR1)		+= $(DRIVERS_SRC)/ddramc_LPDDR1.o
COBJS-$(CONFIG_EXTERNAL_RAM_TEST) += $(DRIVERS_SRC)/ddram_utils.o
endif

COBJS-$(CONFIG_SDCARD)		+= $(DRIVERS_SRC)/at91_mci.o

COBJS-$(CONFIG_SDCARD)		+= $(DRIVERS_SRC)/mci_media.o
COBJS-$(CONFIG_SDCARD)		+= $(DRIVERS_SRC)/sdcard.o

COBJS-$(CONFIG_NANDFLASH)	+= $(DRIVERS_SRC)/nandflash.o
COBJS-$(CONFIG_USE_PMECC)	+= $(DRIVERS_SRC)/pmecc.o
COBJS-$(CONFIG_ENABLE_SW_ECC) 	+= $(DRIVERS_SRC)/hamming.o

COBJS-$(CONFIG_DATAFLASH)	+= $(DRIVERS_SRC)/at91_spi.o
COBJS-$(CONFIG_DATAFLASH)	+= $(DRIVERS_SRC)/dataflash.o

COBJS-$(CONFIG_FLASH)		+= $(DRIVERS_SRC)/flash.o

COBJS-$(CONFIG_LOAD_LINUX)	+= $(DRIVERS_SRC)/load_kernel.o
COBJS-$(CONFIG_LOAD_ANDROID)	+= $(DRIVERS_SRC)/load_kernel.o

COBJS-$(CONFIG_LOAD_ONE_WIRE)	+= $(DRIVERS_SRC)/ds24xx.o

COBJS-$(CONFIG_DATAFLASH_LOAD_WITH_DMA) += $(DRIVERS_SRC)/dma_dev.o
COBJS-$(CONFIG_DATAFLASH_LOAD_WITH_DMA) += $(DRIVERS_SRC)/dmad.o
COBJS-$(CONFIG_DATAFLASH_LOAD_WITH_DMA) += $(DRIVERS_SRC)/at91_dma.o
