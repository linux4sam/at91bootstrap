# Makefile for AT91-Bootstrap drivers directory
# DIRS				+= drivers

DRIVERS:=
DRIVERS_SRC:=$(TOPDIR)/driver

COBJS-$(CONFIG_SDCARD)		+= $(DRIVERS_SRC)/at91_mci.o
COBJS-$(CONFIG_SDCARD)		+= $(DRIVERS_SRC)/sdcard.o

COBJS-$(CONFIG_DEBUG)		+= $(DRIVERS_SRC)/dbgu.o
COBJS-$(CONFIG_DEBUG)		+= $(DRIVERS_SRC)/debug.o
COBJS-y				+= $(DRIVERS_SRC)/at91_pio.o
COBJS-y				+= $(DRIVERS_SRC)/pmc.o

COBJS-$(CONFIG_USER_HW_INIT)	+= $(DRIVERS_SRC)/hw_init_hook.o

COBJS-$(CONFIG_SDRAM)		+= $(DRIVERS_SRC)/sdramc.o
COBJS-$(CONFIG_SDDRC)		+= $(DRIVERS_SRC)/sddrc.o

ifeq ($(CONFIG_BOARD), "at91sama5d3xek")
COBJS-$(CONFIG_DDR2)		+= $(DRIVERS_SRC)/mpddrsdramc.o
else
COBJS-$(CONFIG_DDR2)		+= $(DRIVERS_SRC)/ddramc.o
endif

ifeq ($(CONFIG_BOARD), "at91sam9260ek")
COBJS-$(CONFIG_NANDFLASH)	+= $(DRIVERS_SRC)/nandflash_9260.o
else
COBJS-$(CONFIG_NANDFLASH)	+= $(DRIVERS_SRC)/nandflash.o
endif

COBJS-$(CONFIG_ENABLE_SW_ECC) 	+= $(DRIVERS_SRC)/hamming.o

COBJS-$(CONFIG_DATAFLASH)	+= $(DRIVERS_SRC)/at91_spi.o
COBJS-$(CONFIG_DATAFLASH)	+= $(DRIVERS_SRC)/serial_flash.o

COBJS-$(CONFIG_FLASH)		+= $(DRIVERS_SRC)/flash.o

COBJS-$(CONFIG_LOAD_LINUX)	+= $(DRIVERS_SRC)/load_kernel.o

# Currently, 9x5 only
COBJS-$(CONFIG_AT91SAM9X5EK)	+= $(DRIVERS_SRC)/ds24xx.o
