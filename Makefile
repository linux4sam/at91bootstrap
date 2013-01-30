#
# Default config file is in $(TOPDIR)/board/$(BOARD_NAME)/*_defconfig
# First, run xxx_defconfig
# Then, `make menuconfig' if needed
#

TOPDIR=$(shell pwd)

CONFIG_CONFIG_IN=Config.in
CONFIG_DEFCONFIG=.defconfig
CONFIG=config

CONFIG_SHELL=$(shell which bash)
ifeq ($(CONFIG_SHELL),)
$(error GNU Bash is needed to build Bootstrap!)
endif

BINDIR:=$(TOPDIR)/binaries

DATE := $(shell date)
VERSION := 3.5.1
REVISION :=

noconfig_targets:= menuconfig defconfig $(CONFIG) oldconfig

# Check first if we want to configure at91bootstrap
#
ifeq ($(filter $(noconfig_targets),$(MAKECMDGOALS)),)
-include .config
endif

include	host-utilities/host.mk

ifeq ($(HAVE_DOT_CONFIG),)

all: menuconfig

# configuration
# ---------------------------------------------------------------------------

HOSTCFLAGS=$(CFLAGS_FOR_BUILD)
export HOSTCFLAGS

$(CONFIG)/conf:
	@mkdir -p $(CONFIG)/at91bootstrap-config
	$(MAKE) CC="$(HOSTCC)" -C $(CONFIG) conf
	-@if [ ! -f .config ]; then \
		cp $(CONFIG_DEFCONFIG) .config; \
	fi

$(CONFIG)/mconf:
	@mkdir -p $(CONFIG)/at91bootstrap-config
	$(MAKE) CC="$(HOSTCC)" -C $(CONFIG) conf mconf
	-@if [ ! -f .config ]; then \
		cp $(CONFIG_DEFCONFIG) .config; \
	fi

menuconfig: $(CONFIG)/mconf
	@mkdir -p $(CONFIG)/at91bootstrap-config
	@if ! KCONFIG_AUTOCONFIG=$(CONFIG)/at91bootstrap-config/auto.conf \
		KCONFIG_AUTOHEADER=$(CONFIG)/at91bootstrap-config/autoconf.h \
		$(CONFIG)/mconf $(CONFIG_CONFIG_IN); then \
		test -f .config.cmd || rm -f .config; \
	fi

$(CONFIG): $(CONFIG)/conf
	@mkdir -p $(CONFIG)/at91bootstrap-config
	@KCONFIG_AUTOCONFIG=$(CONFIG)/at91bootstrap-config/auto.conf \
		KCONFIG_AUTOHEADER=$(CONFIG)/at91bootstrap-config/autoconf.h \
		$(CONFIG)/conf $(CONFIG_CONFIG_IN)

oldconfig: $(CONFIG)/conf
	@mkdir -p $(CONFIG)/at91bootstrap-config
	@KCONFIG_AUTOCONFIG=$(CONFIG)/at91bootstrap-config/auto.conf \
		KCONFIG_AUTOHEADER=$(CONFIG)/at91bootstrap-config/autoconf.h \
		$(CONFIG)/conf -o $(CONFIG_CONFIG_IN)

defconfig: $(CONFIG)/conf
	@mkdir -p $(CONFIG)/at91bootstrap-config
	@KCONFIG_AUTOCONFIG=$(CONFIG)/at91bootstrap-config/auto.conf \
		KCONFIG_AUTOHEADER=$(CONFIG)/at91bootstrap-config/autoconf.h \
		$(CONFIG)/conf -d $(CONFIG_CONFIG_IN)


else #  Have DOT Config

ifeq ($(CROSS_COMPILE),)
$(error Environment variable "CROSS_COMPILE" must be defined!)
endif

AS=$(CROSS_COMPILE)gcc
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
NM= $(CROSS_COMPILE)nm
SIZE=$(CROSS_COMPILE)size
OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump

PROJECT := $(strip $(subst ",,$(CONFIG_PROJECT)))
IMG_ADDRESS := $(strip $(subst ",,$(CONFIG_IMG_ADDRESS)))
IMG_SIZE := $(strip $(subst ",,$(CONFIG_IMG_SIZE)))
JUMP_ADDR := $(strip $(subst ",,$(CONFIG_JUMP_ADDR)))
OF_OFFSET := $(strip $(subst ",,$(CONFIG_OF_OFFSET)))
OF_LENGTH := $(strip $(subst ",,$(CONFIG_OF_LENGTH)))
OF_FILENAME := $(strip $(subst ",,$(CONFIG_OF_FILENAME)))
OF_ADDRESS := $(strip $(subst ",,$(CONFIG_OF_ADDRESS)))
BOOTSTRAP_MAXSIZE := $(strip $(subst ",,$(CONFIG_BOOTSTRAP_MAXSIZE)))
MEMORY := $(strip $(subst ",,$(CONFIG_MEMORY)))
IMAGE_NAME:= $(strip $(subst ",,$(CONFIG_IMAGE_NAME)))
CARD_SUFFIX := $(strip $(subst ",,$(CONFIG_CARD_SUFFIX)))
OS_MEM_BANK := $(strip $(subst ",,$(CONFIG_OS_MEM_BANK)))
OS_MEM_SIZE := $(strip $(subst ",,$(CONFIG_OS_MEM_SIZE)))
OS_IMAGE_NAME := $(strip $(subst ",,$(CONFIG_OS_IMAGE_NAME)))
LINUX_KERNEL_ARG_STRING := $(strip $(subst ",,$(CONFIG_LINUX_KERNEL_ARG_STRING)))

# Board definitions
BOARDNAME=$(strip $(subst ",,$(CONFIG_BOARDNAME)))

# CHIP is UNUSED
CHIP:=$(strip $(subst ",,$(CONFIG_CHIP)))
BOARD:=$(strip $(subst ",,$(CONFIG_BOARD)))
MACH_TYPE:=$(strip $(subst ",,$(CONFIG_MACH_TYPE)))
LINK_ADDR:=$(strip $(subst ",,$(CONFIG_LINK_ADDR)))
DATA_SECTION_ADDR:=$(strip $(subst ",,$(CONFIG_DATA_SECTION_ADDR)))
TOP_OF_MEMORY:=$(strip $(subst ",,$(CONFIG_TOP_OF_MEMORY)))

# CRYSTAL is UNUSED
CRYSTAL:=$(strip $(subst ",,$(CONFIG_CRYSTAL)))

# driver definitions
SPI_CLK:=$(strip $(subst ",,$(CONFIG_SPI_CLK)))
SPI_BOOT:=$(strip $(subst ",,$(CONFIG_SPI_BOOT)))

ifeq ($(REVISION),)
REV:=
else
REV:=-$(strip $(subst ",,$(REVISION)))
endif

ifeq ($(CONFIG_OF_LIBFDT), y)
BLOB:=-dt
else
BLOB:=
endif

obj=build/$(BOARDNAME)/

BOOT_NAME=$(BOARDNAME)-$(PROJECT)$(CARD_SUFFIX)boot-$(IMAGE_NAME)$(BLOB)-$(VERSION)$(REV)
AT91BOOTSTRAP:=$(BINDIR)/$(BOOT_NAME).bin

ifeq ($(IMAGE),)
IMAGE=$(BOOT_NAME).bin
endif

ifeq ($(SYMLINK),)
SYMLINK=at91bootstrap.bin
endif

COBJS-y:= $(TOPDIR)/main.o $(TOPDIR)/board/$(BOARDNAME)/$(BOARD).o
SOBJS-y:= $(TOPDIR)/crt0_gnu.o
DIRS:=$(TOPDIR) $(TOPDIR)/board/$(BOARDNAME) $(TOPDIR)/lib $(TOPDIR)/driver

include	lib/libc.mk
include	driver/driver.mk
include	fs/src/fat.mk

#$(SOBJS-y:.o=.S)

SRCS:= $(COBJS-y:.o=.c)
OBJS:= $(SOBJS-y) $(COBJS-y)
INCL=board/$(BOARD)
GC_SECTIONS=--gc-sections

CPPFLAGS=-ffunction-sections -g -Os -Wall \
	-fno-stack-protector \
	-I$(INCL) -Iinclude -Ifs/include \
	-DAT91BOOTSTRAP_VERSION=\"$(VERSION)$(REV)\" -DCOMPILE_TIME="\"$(DATE)\""

ASFLAGS=-g -Os -Wall -I$(INCL) -Iinclude

include	toplevel_cpp.mk
include	board/board_cpp.mk
include	driver/driver_cpp.mk

# Linker flags.
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to map file
#  -lc 	   : 	tells the linker to tie in newlib
#  -lgcc   : 	tells the linker to tie in newlib
LDFLAGS+=-nostartfiles -Map=$(BINDIR)/$(BOOT_NAME).map --cref -static
LDFLAGS+=-T elf32-littlearm.lds $(GC_SECTIONS) -Ttext $(LINK_ADDR)

ifneq ($(DATA_SECTION_ADDR),)
LDFLAGS+=-Tdata $(DATA_SECTION_ADDR)
endif

gccversion := $(shell expr `$(CC) -dumpversion`)

gcclibdir := $(shell dirname `$(CC) -print-libgcc-file-name`)
LIBPATH := -lgcc -L$(gcclibdir)

ifdef YYY   # For other utils
ifeq ($(CC),gcc) 
TARGETS=no-cross-compiler
else
TARGETS=$(obj) $(AT91BOOTSTRAP) host-utilities .config filesize
endif
endif

TARGETS=$(obj) $(AT91BOOTSTRAP)

PHONY:=all

all: PrintFlags $(AT91BOOTSTRAP) ChkFileSize

PrintFlags:
	@echo CC
	@echo ========
	@echo $(CC) $(gccversion)&& echo
	@echo as FLAGS
	@echo ========
	@echo $(ASFLAGS) && echo
	@echo gcc FLAGS
	@echo =========
	@echo $(CPPFLAGS) && echo
	@echo lib Path
	@echo ========
	@echo $(LIBPATH) && echo
	@echo ld FLAGS
	@echo ========
	@echo $(LDFLAGS) && echo

$(AT91BOOTSTRAP): $(OBJS)
	$(if $(wildcard $(BINDIR)),,mkdir -p $(BINDIR))
	@echo "  LD        "$(BOOT_NAME).elf
	@$(LD) $(LDFLAGS) -n -o $(BINDIR)/$(BOOT_NAME).elf $(OBJS) ${LIBPATH}
#	@$(OBJCOPY) --strip-debug --strip-unneeded $(BINDIR)/$(BOOT_NAME).elf -O binary $(BINDIR)/$(BOOT_NAME).bin
	@$(OBJCOPY) --strip-all $(BINDIR)/$(BOOT_NAME).elf -O binary $@

%.o : %.c .config
	@echo "  CC        "$<
	@$(CC) $(CPPFLAGS) -c -o $@ $<

%.o : %.S .config
	@echo "  AS        "$<
	@$(AS) $(ASFLAGS)  -c -o $@  $<


PHONY+= boot bootstrap

rebuild: clean all

ChkFileSize: $(AT91BOOTSTRAP)
	@( fsize=`stat -c%s $(BINDIR)/$(BOOT_NAME).bin`; \
	  echo "Size of $(BOOT_NAME).bin is $$fsize bytes"; \
	  if [ "$$fsize" -gt "$(BOOTSTRAP_MAXSIZE)" ] ; then \
		echo "[Failed***] It's too big to fit into SRAM area. the support maxium size is $(BOOTSTRAP_MAXSIZE)"; \
		rm -rf $(BINDIR); \
		exit 2;\
	  else \
	  	echo "[Succeeded] It's OK to fit into SRAM area"; \
	  fi )
endif  # HAVE_DOT_CONFIG

PHONY+= rebuild

%_defconfig:
	echo $(shell find ./board/ -name $@)
	cp $(shell find ./board/ -name $@) .config
	@$(MAKE) oldconfig

update:
	cp .config board/$(BOARD)/$(BOARDNAME)_defconfig

no-cross-compiler:
	@echo
	@echo
	@echo
	@echo "	You should consider using a cross compiler for ARM !"
	@echo "	I.E: CROSS_COMPILE should contains something useful."
	@echo

debug:
	@echo CONFIG=$(CONFIG)
	@echo AS=$(AS)
	@echo CROSS_COMPILE=$(CROSS_COMPILE)

PHONY+=update no-cross-compiler debug

distrib: config-clean
	find . -type f \( -name .depend \
		-o -name '*.srec' \
		-o -name '*.elf' \
		-o -name '*.map' \
		-o -name '*.o' \
		-o -name '*~' \) \
		-print0 \
		| xargs -0 rm -f
	rm -fr result
	rm -fr build
	rm -fr log
	rm -fr .auto.deps
	rm -fr ..make.deps.tmp
	rm -fr .config.cmd .config.old
	make -C config clean
	rm -fr config/at91bootstrap-config
	rm -fr config/conf
	rm -f  config/.depend
	rm -fr $(BINDIR)
	rm -f .installed
	rm -f .configured

config-clean:
	make -C config distclean
	rm -fr config/at91bootstrap-config
	rm -f  config/.depend

clean:
	find . -type f \( -name .depend \
		-o -name '*.srec' \
		-o -name '*.o' \
		-o -name '*~' \) \
		-print0 \
		| xargs -0 rm -f
	rm -fr $(obj)

distclean: clean config-clean
#	rm -fr $(BINDIR)
	rm -fr .config .config.cmd .config.old
	rm -fr .auto.deps
	rm -f .installed
	rm -f ..*.tmp
	rm -f .configured

mrproper: distclean
	rm -fr $(BINDIR)
	rm -fr log

PHONY+=distrib config-clean clean distclean mrproper

tarball: distrib
	rm -fr ../source/at91bootstrap-$(VERSION)
	rm -fr ../source/at91bootstrap-$(VERSION).tar*
	mkdir -p ../source
	find . -depth -print0 | cpio --null -pvd ../source/at91bootstrap-$(VERSION)
	rm -fr ../source/at91bootstrap-$(VERSION)/.git
	tar -C ../source -cvf ../source/at91bootstrap-$(VERSION).tar at91bootstrap-$(VERSION)
	bzip2  ../source/at91bootstrap-$(VERSION).tar
	cp ../source/at91bootstrap-$(VERSION).tar.bz2 /usr/local/install/downloads

tarballx: clean
	F=`basename $(CURDIR)` ; cd .. ; \
	T=`basename $(CURDIR)`-$(VERSION).tar ;  \
	tar --force-local -cvf $$T $$F; \
	rm -f $$T.bz2 ; \
	bzip2 $$T ; \
	cp -f $$T.bz2 /usr/local/install/downloads

PHONY+=tarball tarballx

.PHONY: $(PHONY)
