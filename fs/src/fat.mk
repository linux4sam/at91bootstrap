# Makefile for AT91Bootstrap ./fs/src directory
# DIRS				+= ./fs/src

FS_FAT:=$(TOPDIR)/fs/src

COBJS-$(CONFIG_SDCARD)	+=  $(FS_FAT)/ff.o
COBJS-$(CONFIG_SDCARD)	+=  $(FS_FAT)/diskio.o


