# Makefile for AT91Bootstrap libc directory
# DIRS				+= libc

LIBC:=$(TOPDIR)/lib

COBJS-y		+= $(LIBC)/string.o
COBJS-y		+= $(LIBC)/eabi_utils.o
COBJS-y		+= $(LIBC)/div.o

COBJS-$(CONFIG_CRC32)	+= $(LIBC)/crc32.o
COBJS-$(CONFIG_OF_LIBFDT) += $(LIBC)/fdt.o
