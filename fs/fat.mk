# Makefile for AT91Bootstrap ./fs directory
# DIRS				+= ./f

FS_FAT:=$(TOPDIR)/fs

COBJS-$(CONFIG_SDCARD)	+=  $(FS_FAT)/ff.o
COBJS-$(CONFIG_SDCARD)	+=  $(FS_FAT)/diskio.o


