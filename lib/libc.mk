# Makefile for AT91-Bootstrap libc directory
# DIRS				+= libc

LIBC:=$(TOPDIR)/lib/

COBJS-y				+=	$(LIBC)string.o
COBJS-y				+=	$(LIBC)div0.o
COBJS-y				+=	$(LIBC)udiv.o
COBJS-y				+=	$(LIBC)eabi_utils.o

SOBJS-y				+=	$(LIBC)_udivsi3.o
SOBJS-y				+=	$(LIBC)_umodsi3.o

