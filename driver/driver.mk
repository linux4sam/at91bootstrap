# Makefile for AT91-Bootstrap drivers directory
# DIRS				+= drivers

DRIVERS:=
DRIVERS_SRC:=$(TOPDIR)/driver
ifeq ($(ALLOW_HSMCI),y)
COBJS-$(CONFIG_SDCARD)             +=  $(DRIVERS_SRC)/mci_hs.o
else
COBJS-$(CONFIG_SDCARD)             +=  $(DRIVERS_SRC)/mci.o
endif

COBJS-$(CONFIG_SDCARD)             +=  $(DRIVERS_SRC)/Media.o
COBJS-$(CONFIG_SDCARD)             +=  $(DRIVERS_SRC)/diskio.o


ifeq ($(ALLOW_HSMCI),y)
COBJS-$(CONFIG_SDCARD)             +=  $(DRIVERS_SRC)/dma.o
COBJS-$(CONFIG_SDCARD)             +=  $(DRIVERS_SRC)/dmad.o
endif
COBJS-$(CONFIG_SDCARD)             +=  $(DRIVERS_SRC)/MEDSdcard.o
COBJS-$(CONFIG_SDCARD)             +=  $(DRIVERS_SRC)/pio.o
COBJS-$(CONFIG_SDCARD)             +=  $(DRIVERS_SRC)/sdmmc_mci.o
COBJS-$(CONFIG_SDCARD)             +=  $(DRIVERS_SRC)/ff.o

COBJS-$(CONFIG_DEBUG)	+=	$(DRIVERS_SRC)/dbgu.o
COBJS-$(CONFIG_DEBUG)	+=	$(DRIVERS_SRC)/debug.o
COBJS-y					+=	$(DRIVERS_SRC)/gpio.o
COBJS-y					+=	$(DRIVERS_SRC)/pmc.o

COBJS-$(CONFIG_SDRAM)		+=	$(DRIVERS_SRC)/sdramc.o
COBJS-$(CONFIG_SDDRC)		+=	$(DRIVERS_SRC)/sddrc.o
COBJS-$(CONFIG_DDR2)		+=	$(DRIVERS_SRC)/ddramc.o

COBJS-$(CONFIG_DATAFLASH)	+=	$(DRIVERS_SRC)/dataflash.o
COBJS-$(CONFIG_FLASH)		+=	$(DRIVERS_SRC)/flash.o
COBJS-$(CONFIG_NANDFLASH)	+=	$(DRIVERS_SRC)/nandflash.o
COBJS-$(CONFIG_USER_HW_INIT)	+=	$(DRIVERS_SRC)/user_hw_init.o

COBJS-$(CONFIG_ENABLE_SW_ECC) += $(DRIVERS_SRC)/hamming.o
COBJS-$(CONFIG_NANDFLASH) += $(DRIVERS_SRC)/NandSpareScheme.o

COBJS-$(CONFIG_LOAD_LINUX) += $(DRIVERS_SRC)/linux_loader.o

COBJS-$(CONFIG_LOAD_NK) += $(DRIVERS_SRC)/wince_loader.o
COBJS-$(CONFIG_LOAD_EBOOT) += $(DRIVERS_SRC)/wince_loader.o

