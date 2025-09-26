# Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
#
# SPDX-License-Identifier: MIT

#
# Default config file is in configs/$(DEVICE_NAME)*_defconfig
# First, run xxx_defconfig
# Then, `make menuconfig' if needed
#

# Do not:
# o  use make's built-in rules and variables
#    (this increases performance and avoids hard-to-debug behaviour);
# o  print "Entering directory ...";
MAKEFLAGS += -rR --no-print-directory

CONFIG_CONFIG_IN=Kconfig
CONFIG_DEFCONFIG=.defconfig
CONFIG=config

# Detect if the current command interpreter is a Unix-like shell,
# or a non-*nix interpreter such as Command Prompt/PowerShell.
# When given a *nix shell, we'll further assume that all the necessary tools
# are installed, and enable all the rules and features.
# With a non-*nix interpreter we'll trim the recipes, skipping unsupported
# commands and scripts.
ifeq ($(strip $(shell echo $$0)),$$0)
NIX_SHELL=
else
NIX_SHELL=1
CONFIG_SHELL := $(shell which bash)
ifeq ($(CONFIG_SHELL),)
$(error GNU Bash is needed to build Kconfig host tools!)
endif
endif

BUILDDIR ?= ./build
BINDIR:=$(BUILDDIR)/binaries
SYMLINK ?= at91bootstrap.bin
SYMLINK_BOOT ?= boot.bin
SYMLINK_ELF ?= at91bootstrap.elf
SYMLINK_ELF_STRIPPED ?= at91bootstrap-stripped.elf

include	host-utilities/host.mk

ifeq ($(origin BUILD_DATE), undefined)
# Automatically escape '%' symbols when recipes are implemented as batch files
PERCENT := $(if $(findstring %%_dummy_,$(shell echo %%_dummy_)),%,%%)
# see https://reproducible-builds.org/docs/source-date-epoch/#makefile
DATE_FMT = +$(PERCENT)Y-$(PERCENT)m-$(PERCENT)d $(PERCENT)H:$(PERCENT)M:$(PERCENT)S
ifdef SOURCE_DATE_EPOCH
	BUILD_DATE := $(shell $(DATE) -u -d "@$(SOURCE_DATE_EPOCH)" "$(DATE_FMT)" 2>$(DEV_NULL) || $(DATE) -u -r "$(SOURCE_DATE_EPOCH)" "$(DATE_FMT)" 2>$(DEV_NULL) || $(DATE) -u "$(DATE_FMT)")
else
	BUILD_DATE := $(shell $(DATE) "$(DATE_FMT)")
endif
endif
export VERSION := 4.0.12-rc1
REVISION :=
ifdef NIX_SHELL
SCMINFO := $(shell (host-utilities/setlocalversion))
endif

ifeq ($(SCMINFO),)
-include scminfo.mk
SCMINFO=$(RECORD_SCMINFO)
endif

TARBALL_NAME=AT91Bootstrap-$(VERSION)$(REV)$(SCMINFO).tar.gz
TARBALL_DIR=../tarball_dir
TARBALL_PREFIX=at91bootstrap-$(VERSION)$(REV)/

# Use 'make V=1' for the verbose mode
ifneq ("$(origin V)", "command line")
Q=@
export Q
endif

# Function brief: Search for existing files, recursively
# param 1: List of directories to search in
# param 2: List of patterns to match
# return: List of paths to the matching files, relative to and including param 1
rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(strip $(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d)))

# Function brief: Check if one LD option is supported by linker being used
# param 1: LD option to check
# return: LD option being checked if supported
ldckflags=$(shell $(LD) $(1) -v >$(DEV_NULL) 2>$(DEV_NULL) && echo "$(1)")

noconfig_targets:= menuconfig defconfig $(CONFIG) oldconfig savedefconfig

# Check first if we want to configure at91bootstrap
#
ifeq ($(filter $(noconfig_targets),$(MAKECMDGOALS)),)
-include .config
endif

ifeq ($(CONFIG_HAVE_DOT_CONFIG),)

all: menuconfig

# configuration
# ---------------------------------------------------------------------------

HOSTCFLAGS=$(CFLAGS_FOR_BUILD)
export HOSTCFLAGS

$(CONFIG)/conf: | $(CONFIG)/at91bootstrap-config
	@$(MAKE) CC="$(HOSTCC)" -C $(CONFIG) conf
	-@if [ ! -f .config ]; then \
		cp $(CONFIG_DEFCONFIG) .config; \
	fi

$(CONFIG)/mconf: | $(CONFIG)/at91bootstrap-config
	@$(MAKE) CC="$(HOSTCC)" -C $(CONFIG) conf mconf
	-@if [ ! -f .config ]; then \
		cp $(CONFIG_DEFCONFIG) .config; \
	fi

menuconfig: $(CONFIG)/mconf
	@if ! KCONFIG_AUTOCONFIG=$(CONFIG)/at91bootstrap-config/auto.conf \
		KCONFIG_AUTOHEADER=$(CONFIG)/at91bootstrap-config/autoconf.h \
		$(CONFIG)/mconf $(CONFIG_CONFIG_IN); then \
		test -f .config.cmd || rm -f .config; \
	fi

$(CONFIG): $(CONFIG)/conf
	@KCONFIG_AUTOCONFIG=$(CONFIG)/at91bootstrap-config/auto.conf \
		KCONFIG_AUTOHEADER=$(CONFIG)/at91bootstrap-config/autoconf.h \
		$(CONFIG)/conf $(CONFIG_CONFIG_IN)

oldconfig: $(CONFIG)/conf
	@KCONFIG_AUTOCONFIG=$(CONFIG)/at91bootstrap-config/auto.conf \
		KCONFIG_AUTOHEADER=$(CONFIG)/at91bootstrap-config/autoconf.h \
		$(CONFIG)/conf --oldconfig $(CONFIG_CONFIG_IN)

defconfig: $(CONFIG)/conf
	@KCONFIG_AUTOCONFIG=$(CONFIG)/at91bootstrap-config/auto.conf \
		KCONFIG_AUTOHEADER=$(CONFIG)/at91bootstrap-config/autoconf.h \
		$(CONFIG)/conf --defconfig=.config $(CONFIG_CONFIG_IN)

savedefconfig: $(CONFIG)/conf
	@KCONFIG_AUTOCONFIG=$(CONFIG)/at91bootstrap-config/auto.conf \
		KCONFIG_AUTOHEADER=$(CONFIG)/at91bootstrap-config/autoconf.h \
		$(CONFIG)/conf --savedefconfig=defconfig $(CONFIG_CONFIG_IN)

else #  Have DOT Config

HOSTARCH := $(patsubst arm%,arm,$(shell uname -m))

AS=$(CROSS_COMPILE)gcc
CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
NM= $(CROSS_COMPILE)nm
SIZE=$(CROSS_COMPILE)size
OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump

SAM-BA=sam-ba

PROJECT := $(strip $(subst ",,$(CONFIG_PROJECT)))
IMG_ADDRESS := $(strip $(subst ",,$(CONFIG_IMG_ADDRESS)))
IMG_SIZE := $(strip $(subst ",,$(CONFIG_IMG_SIZE)))
JUMP_ADDR := $(strip $(subst ",,$(CONFIG_JUMP_ADDR)))
OF_OFFSET := $(strip $(subst ",,$(CONFIG_OF_OFFSET)))
OF_ADDRESS := $(strip $(subst ",,$(CONFIG_OF_ADDRESS)))
BOOTSTRAP_MAXSIZE := $(strip $(subst ",,$(CONFIG_BOOTSTRAP_MAXSIZE)))
MEMORY := $(strip $(subst ",,$(CONFIG_MEMORY)))
IMAGE_NAME:= $(strip $(subst ",,$(CONFIG_IMAGE_NAME)))
CARD_SUFFIX := $(strip $(subst ",,$(CONFIG_CARD_SUFFIX)))
LINUX_KERNEL_ARG_STRING := $(strip $(subst ",,$(CONFIG_LINUX_KERNEL_ARG_STRING)))
LINUX_KERNEL_ARG_STRING_FILE := $(strip $(subst ",,$(CONFIG_LINUX_KERNEL_ARG_STRING_FILE)))

ifeq ($(CONFIG_FAST_BOOT), y)
LIB_PATH =fast-boot
ifeq ($(CONFIG_SDCARD), y)
LIB_NAME =fastboot_sd
else ifeq ($(CONFIG_QSPI), y)
LIB_NAME =fastboot_qspi
else ifeq ($(CONFIG_NANDFLASH), y)
LIB_NAME =fastboot_nand
endif
endif

# Device definitions
DEVICENAME:=$(strip $(subst ",,$(CONFIG_DEVICENAME)))

ifeq ($(CONFIG_OVERRIDE_MACH_TYPE), y)
MACH_TYPE:=$(strip $(subst ",,$(CONFIG_CUSTOM_MACH_TYPE)))
else
MACH_TYPE:=$(strip $(subst ",,$(CONFIG_MACH_TYPE)))
endif

LINK_ADDR:=$(strip $(subst ",,$(CONFIG_LINK_ADDR)))
TOP_OF_MEMORY:=$(strip $(subst ",,$(CONFIG_TOP_OF_MEMORY)))

# CRYSTAL is UNUSED
CRYSTAL:=$(strip $(subst ",,$(CONFIG_CRYSTAL)))

ifeq ($(CONFIG_MMU), y)
MMU_TABLE_BASE_ADDR := $(strip $(subst ",,$(CONFIG_MMU_TABLE_BASE_ADDR)))
endif

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

ifeq ($(CONFIG_LOAD_LINUX), y)
TARGET_NAME:=linux-$(or $(subst I,i,$(IMAGE_NAME)),image)
else ifeq ($(CONFIG_LOAD_ANDROID), y)
TARGET_NAME:=android-$(or $(subst I,i,$(IMAGE_NAME)),image)
else ifeq ($(CONFIG_LOAD_OPTEE), y)
TARGET_NAME:=$(or $(subst -,,$(basename $(IMAGE_NAME))),uboot)
else ifeq ($(CONFIG_LOAD_UBOOT), y)
TARGET_NAME:=$(or $(subst -,,$(basename $(IMAGE_NAME))),uboot)
else ifeq ($(CONFIG_LOAD_64KB), y)
TARGET_NAME:=$(or $(basename $(IMAGE_NAME)),softpack)
else ifeq ($(CONFIG_LOAD_1MB), y)
TARGET_NAME:=$(or $(basename $(IMAGE_NAME)),softpack)
else ifeq ($(CONFIG_LOAD_4MB), y)
TARGET_NAME:=$(or $(basename $(IMAGE_NAME)),softpack)
else
TARGET_NAME:=$(or $(basename $(IMAGE_NAME)),none)
endif

ifneq ($(TARGET_NAME), none)
BOOT_NAME=$(DEVICENAME)-$(PROJECT)$(CARD_SUFFIX)boot-$(TARGET_NAME)$(BLOB)-$(VERSION)$(REV)
else
BOOT_NAME=$(DEVICENAME)-boot-$(TARGET_NAME)$(BLOB)-$(VERSION)$(REV)
endif
AT91BOOTSTRAP:=$(BINDIR)/$(BOOT_NAME).bin

ifeq ($(IMAGE),)
IMAGE=$(BOOT_NAME).bin
endif

COBJS-y:= main.o
SOBJS-y:= crt0_gnu.o

# Verify that DEVICENAME is the name of a subdirectory of device/
DEVICE_LOCATE=$(if $(wildcard device/$(DEVICENAME)/.),device/$(DEVICENAME))
ifeq ("$(realpath $(DEVICE_LOCATE))", "")
$(error ERROR: *** device not found!)
endif

COBJS-y += $(DEVICE_LOCATE)/$(DEVICENAME).o
INCL = $(DEVICE_LOCATE)

include	lib/lib.mk
include	driver/driver.mk
include	fs/src/fat.mk

GC_SECTIONS=--gc-sections

# $(EXTRA_CC_ARGS) can be used to pass extra CC parameters to toolchain
# For example, Yocto Project can pass the sysroot
NOSTDINC_FLAGS := -nostdinc -isystem "$(shell "$(CC)" $(EXTRA_CC_ARGS) -print-file-name=include)"

CPPFLAGS=$(EXTRA_CC_ARGS) $(NOSTDINC_FLAGS) -ffunction-sections -g -Os -Wall \
	-mno-unaligned-access \
	-fno-stack-protector -fno-common -fno-builtin -fno-jump-tables -fno-pie \
	-I$(INCL) -Iinclude -Ifs/include -Ifast-boot\
	-I$(CONFIG)/at91bootstrap-config \
	-include $(CONFIG)/at91bootstrap-config/autoconf.h \
	-DAT91BOOTSTRAP_VERSION=\"$(VERSION)$(REV)$(SCMINFO)\" -DCOMPILE_TIME="\"$(BUILD_DATE)\""

ASFLAGS=$(EXTRA_CC_ARGS) -g -Os -Wall -I$(INCL) -Iinclude -include $(CONFIG)/at91bootstrap-config/autoconf.h

include	toplevel_cpp.mk
include	device/device_cpp.mk

include	driver/driver_cpp.mk

OBJS := $(addprefix $(BUILDDIR)/,$(SOBJS-y) $(COBJS-y))

ifeq ($(CONFIG_ENTER_NWD), y)
link_script:=elf32-littlearm-tz.lds
else
link_script:=elf32-littlearm.lds
endif

# Linker flags.
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to map file
#  -lc 	   : 	tells the linker to tie in newlib
#  -lgcc   : 	tells the linker to tie in newlib
LDFLAGS=$(EXTRA_CC_ARGS) -Map=$(BINDIR)/$(BOOT_NAME).map --cref -static
LDFLAGS+=-z noexecstack
LDFLAGS+=$(call ldckflags,--no-warn-rwx-segments)
LDFLAGS+=-T $(link_script) $(GC_SECTIONS) -Ttext $(LINK_ADDR)

REMOVE_SECTIONS=-R .note -R .comment -R .note.gnu.build-id

gccversion := $(shell "$(CC)" -dumpversion)

ifdef YYY   # For other utils
ifeq ($(CC),gcc) 
TARGETS=no-cross-compiler
else
TARGETS=$(AT91BOOTSTRAP) host-utilities .config filesize
endif
endif

TARGETS=CheckCrossCompile PrintFlags $(AT91BOOTSTRAP)
ifdef NIX_SHELL
TARGETS+=ChkFileSize
endif

ifeq ($(CONFIG_NANDFLASH)$(CONFIG_USE_PMECC), yy)
TARGETS+=${AT91BOOTSTRAP}.pmecc
endif

ifeq ($(CONFIG_SAMA7D65), y)
ifneq ($(CONFIG_INIT_AND_STOP)$(CONFIG_LOAD_AND_STOP), y)
# PTI stands for Plain Text Image mode. Format used for a chip configured
# in Non-Secure mode. See "Bootstrap Image Format" in product's datasheet.
PTI:=plaintextimg
DUAL_BOOT_VERSION := $(strip $(subst ",,$(CONFIG_DUAL_BOOT_VERSION)))
AT91BOOTSTRAP_PTI:=$(BINDIR)/$(BOOT_NAME)-$(PTI).bin
TARGETS+=${AT91BOOTSTRAP_PTI}
SYMLINK_PTI_BOOT ?= boot-${PTI}.bin
endif
endif

PHONY:=all

all: $(TARGETS)

CheckCrossCompile:
	$(if $(filter-out arm,$(HOSTARCH)),$(if $(CROSS_COMPILE),, \
		$(error Error: the CROSS_COMPILE environment variable must be defined)))

PrintFlags:
	$(info CC)
	$(info ========)
	$(info $(CC) $(gccversion))
	$(info )
	$(info as FLAGS)
	$(info ========)
	$(info $(ASFLAGS))
	$(info )
	$(info gcc FLAGS)
	$(info =========)
	$(info $(CPPFLAGS))
	$(info )
	$(info ld FLAGS)
	$(info ========)
	$(info $(LDFLAGS))
	$(info )

$(AT91BOOTSTRAP): $(OBJS) | $(BINDIR)
	$(Q)$(MKDIR) -p $(dir $@)
	@echo "  LD        "$(BOOT_NAME).elf
ifeq ($(CONFIG_FAST_BOOT), y)
	$(Q)"$(LD)" $(LDFLAGS) -n -o $(BINDIR)/$(BOOT_NAME).elf $(OBJS) -L$(LIB_PATH) -l$(LIB_NAME)
else
	$(Q)"$(LD)" $(LDFLAGS) -n -o $(BINDIR)/$(BOOT_NAME).elf $(OBJS)
endif
	$(Q)"$(OBJCOPY)" --strip-all $(REMOVE_SECTIONS) $(BINDIR)/$(BOOT_NAME).elf -O binary $@
ifdef NIX_SHELL
	@ln -sf $(BOOT_NAME).elf ${BINDIR}/${SYMLINK_ELF}
	@ln -sf $(BOOT_NAME).elf ${BINDIR}/${SYMLINK_ELF_STRIPPED}
	@ln -sf $(BOOT_NAME).bin ${BINDIR}/${SYMLINK}
	@ln -sf $(BOOT_NAME).bin ${BINDIR}/${SYMLINK_BOOT}
else
	@cp -l ${BINDIR}/$(BOOT_NAME).elf ${BINDIR}/${SYMLINK_ELF}
	@cp -l ${BINDIR}/$(BOOT_NAME).elf ${BINDIR}/${SYMLINK_ELF_STRIPPED}
	@cp -l ${BINDIR}/$(BOOT_NAME).bin ${BINDIR}/${SYMLINK}
	@cp -l ${BINDIR}/$(BOOT_NAME).bin ${BINDIR}/${SYMLINK_BOOT}
endif

$(BUILDDIR)/%.o : %.c .config
	$(Q)$(MKDIR) -p $(dir $@)
	@echo "  CC        "$<
	$(Q)"$(CC)" $(CPPFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o : %.S .config
	$(Q)$(MKDIR) -p $(dir $@)
	@echo "  AS        "$<
	$(Q)"$(AS)" $(ASFLAGS) -c -o $@ $<

$(AT91BOOTSTRAP).pmecc: $(BINDIR)/pmecc.tmp $(AT91BOOTSTRAP)
	$(Q)test -f $< && cat $+ > $@ || rm -f $@

$(AT91BOOTSTRAP_PTI): $(AT91BOOTSTRAP) ChkSamBa
	$(Q)"$(SAM-BA)" -u gen_image:$(DEVICENAME):$<:$@:$(DUAL_BOOT_VERSION)
ifdef NIX_SHELL
	@ln -sf $(BOOT_NAME)-$(PTI).bin ${BINDIR}/${SYMLINK_PTI_BOOT}
endif

$(BINDIR)/pmecc.tmp: .config | $(BINDIR)
ifdef NIX_SHELL
	$(Q)./scripts/addpmecchead.py .config $(BINDIR)
endif

PHONY+= bootstrap

rebuild: clean all

ifdef NIX_SHELL
ChkSamBa:
	@( $(SAM-BA) -u:test::: > /dev/null 2>&1 ; \
	  if [ $$? -ne 0 ] ; then \
		$(SAM-BA) -v ; \
		if [ $$? -ne 0 ] ; then \
			echo "[Failed***] SAM-BA tool not installed or not in the \$$PATH"; \
			exit 2; \
		else \
			echo "The '-g' option is deprecated and not supported anymore."; \
			echo "Please upgrade to sam-ba v3.8 for better functionality."; \
			echo "[Failed***] SAM-BA tool version not able to generate bootable binary"; \
			exit 3; \
		fi \
	  else \
		echo "[Succeeded] SAM-BA tool generating bootable binary image available"; \
	  fi )
PHONY+= ChkSamBa
else
ChkSamBa:
	$(SHELL) /C nbproject\get_sam_ba_version.bat
PHONY+= ChkSamBa
endif

ChkFileSize: $(AT91BOOTSTRAP)
	@( fsize=`./scripts/get_sram_size.sh $(BINDIR)/$(BOOT_NAME).map`; \
	  if [ $$? -ne 0 ] ; then \
		rm $(BINDIR)/$(BOOT_NAME).bin ;\
		rm ${BINDIR}/${SYMLINK}; \
		rm ${BINDIR}/${SYMLINK_BOOT}; \
		exit 3; \
	  fi ; \
	  echo "Size of $(BOOT_NAME).bin is $$fsize bytes"; \
	  if [ "$$fsize" -gt "$(BOOTSTRAP_MAXSIZE)" ] ; then \
		echo "[Failed***] It's too big to fit into SRAM area. the supported maximum size is $(BOOTSTRAP_MAXSIZE)"; \
		rm $(BINDIR)/$(BOOT_NAME).bin ;\
		rm ${BINDIR}/${SYMLINK}; \
		rm ${BINDIR}/${SYMLINK_BOOT}; \
		exit 2;\
	  else \
	  	echo "[Succeeded] It's OK to fit into SRAM area"; \
		sram_size=`expr $(BOOTSTRAP_MAXSIZE) \* 2`; \
		stack_space=`expr $$sram_size - $$fsize`; \
		echo "[Attention] The space left for stack is $$stack_space bytes"; \
	  fi )
endif  # CONFIG_HAVE_DOT_CONFIG

PHONY+= rebuild

prepare: .prepared | $(CONFIG)/at91bootstrap-config $(BINDIR)

.prepared: $(wildcard .config)
	@echo AT91BOOTSTRAP_PREP_REV = 1 > $@
	@echo AT91BOOTSTRAP_VERSIONNO = $(VERSION) >> $@
	@echo KBUILD_KCONFIG = $(CONFIG_CONFIG_IN) >> $@
	@echo KCONFIG_DEFCONFIG = $(CONFIG_DEFCONFIG) >> $@
	@echo KCONFIG_CONFIG = .config >> $@
	@echo KCONFIG_AUTOCONFIGOUTPUT = $(CONFIG)/at91bootstrap-config >> $@
	@echo KCONFIG_AUTOCONFIG = $(CONFIG)/at91bootstrap-config/auto.conf >> $@
	@echo KCONFIG_AUTOHEADER = $(CONFIG)/at91bootstrap-config/autoconf.h >> $@
	@echo AT91BOOTSTRAP_SCMREVIN = scminfo.mk >> $@
	@echo AT91BOOTSTRAP_BINOUTPUT = $(BINDIR) >> $@
	@echo AT91BOOTSTRAP_ELF = $(BINDIR)/$(SYMLINK_ELF) >> $@
	@echo AT91BOOTSTRAP_BIN = $(BINDIR)/$(SYMLINK) >> $@
ifneq ($(CONFIG_HAVE_DOT_CONFIG),)
	@echo AT91BOOTSTRAP_MAP = $(BINDIR)/$(BOOT_NAME).map >> $@
	@echo AT91BOOTSTRAP_VERSIONEXTD = $(VERSION)$(REV)$(SCMINFO) >> $@
	@echo AT91BOOTSTRAP_TARBALL = $(TARBALL_NAME) >> $@
	@echo AT91BOOTSTRAP_BOARDDIR = $(BOARD_LOCATE) >> $@
endif

$(CONFIG)/at91bootstrap-config $(BINDIR):
	@$(MKDIR) -p $@

%_defconfig:
	@(conf_file=`find ./ -name $@`; \
	if [ "$$conf_file"x != "x" ]; then \
		cp $$conf_file .config; \
	else \
		echo "Error: *** Cannot find file: $@"; \
		exit 2; \
	fi )
	@$(MAKE) defconfig

update:
	cp .config configs/$(DEVICENAME)_defconfig

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

distrib: mrproper
	$(Q)rm -f  $(call rwildcard,.,*.elf *.map)
	$(Q)rm -fr result
	$(Q)rm -fr build
	$(Q)rm -fr ..make.deps.tmp
	$(Q)rm -fr config/conf

config-clean:
	@echo "  CLEAN        "configuration files!
	$(Q)$(MAKE) -C config distclean
	$(Q)rm -fr config/at91bootstrap-config
	$(Q)rm -f  config/.depend

clean:
	@echo "  CLEAN        "obj and misc files!
	$(Q)rm -f $(CONFIG)/.depend
	$(Q)rm -f $(call rwildcard,$(BUILDDIR),*.o *.srec *~)

distclean: clean config-clean
#	rm -fr $(BINDIR)
	$(Q)rm -fr .config .config.cmd .config.old
	$(Q)rm -fr .auto.deps
	$(Q)rm -f .installed
	$(Q)rm -fr ..make.deps.tmp ..config.tmp
	$(Q)rm -f $(BINDIR)/pmecc.tmp
	$(Q)rm -f .configured
	$(Q)rm -f .prepared
	$(Q)rm -f $(subst $$,\$$,$(call rwildcard,scripts,*$$py.class))
	$(Q)rm -fr debug
	$(Q)rm -f default.config
	$(Q)rm -f default.config.old
	$(Q)rm -f nbproject/Makefile-default.mk
	$(Q)rm -f nbproject/Makefile-genesis.properties
	$(Q)rm -f nbproject/Makefile-impl.mk
	$(Q)rm -f nbproject/Makefile-local-default.mk
	$(Q)rm -f nbproject/Makefile-variables.mk
	$(Q)rm -f nbproject/Package-default.bash
	$(Q)rm -fr nbproject/private

mplabclean: clean
	@echo "  CLEAN        "binary files!
	$(Q)rm -fr $(BUILDDIR)
	$(Q)rm -fr log

mrproper: distclean
	@echo "  CLEAN        "binary files!
	$(Q)rm -fr $(BUILDDIR)
	$(Q)rm -fr log

PHONY+=distrib config-clean clean distclean mrproper

tarball:
	@echo "Tar the source code to ${TARBALL_NAME}"
	$(Q)$(MKDIR) -p ${TARBALL_DIR}
	$(Q)git archive --prefix=${TARBALL_PREFIX} HEAD | gzip > ${TARBALL_DIR}/${TARBALL_NAME}
	$(Q)echo "RECORD_SCMINFO=${SCMINFO}" > ${TARBALL_DIR}/scminfo.mk
	$(Q)cd ${TARBALL_DIR}; tar -xzf ${TARBALL_NAME}
	$(Q)cd ${TARBALL_DIR}; cp scminfo.mk ${TARBALL_PREFIX}
	$(Q)cd ${TARBALL_DIR}; tar czf ${TARBALL_NAME} ${TARBALL_PREFIX}
	$(Q)cp ${TARBALL_DIR}/${TARBALL_NAME} .
	$(Q)rm -rf ${TARBALL_DIR}

PHONY+=tarball

.PHONY: $(PHONY)
