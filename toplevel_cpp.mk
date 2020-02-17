CPPFLAGS += \
	-DIMG_ADDRESS=$(IMG_ADDRESS)	\
	-DIMG_SIZE=$(IMG_SIZE)		\
	-DJUMP_ADDR=$(JUMP_ADDR)	\
	-DOF_OFFSET=$(OF_OFFSET)	\
	-DOF_ADDRESS=$(OF_ADDRESS)	\
	-DMEM_BANK=$(MEM_BANK)	\
	-DIMAGE_NAME="\"$(IMAGE_NAME)\""	\
	-DCMDLINE="\"$(LINUX_KERNEL_ARG_STRING)\""	\
	-DCMDLINE_FILE="\"$(LINUX_KERNEL_ARG_STRING_FILE)\""	\
	-DTOP_OF_MEMORY=$(TOP_OF_MEMORY)	\
	-DMACH_TYPE=$(MACH_TYPE)		\

ASFLAGS += -DJUMP_ADDR=$(JUMP_ADDR)		\
	-DTOP_OF_MEMORY=$(TOP_OF_MEMORY)	\
	-DMACH_TYPE=$(MACH_TYPE)		\

ASFLAGS += -DLINK_ADDR=$(CONFIG_LINK_ADDR)

ifeq ($(CONFIG_RAM_512MB), y)
CPPFLAGS += \
	-DMEM_SIZE=0x20000000
endif

ifeq ($(CONFIG_RAM_256MB), y)
CPPFLAGS += \
	-DMEM_SIZE=0x10000000
endif

ifeq ($(CONFIG_RAM_128MB), y)
CPPFLAGS += \
	-DMEM_SIZE=0x8000000
endif

ifeq ($(CONFIG_RAM_64MB), y)
CPPFLAGS += \
	-DMEM_SIZE=0x4000000
endif

ifeq ($(CONFIG_RAM_32MB), y)
CPPFLAGS += \
	-DMEM_SIZE=0x2000000
endif

ifeq ($(CONFIG_RAM_8MB), y)
CPPFLAGS += \
	-DMEM_SIZE=0x800000
endif

ifeq ($(CONFIG_DEBUG),y)
CPPFLAGS += -DCONFIG_DEBUG
endif

ifeq ($(CONFIG_HW_DISPLAY_BANNER),y)
BANNER:="$(CONFIG_HW_BANNER)"
CPPFLAGS += -DBANNER="$(BANNER)"
CPPFLAGS += -DCONFIG_HW_DISPLAY_BANNER
endif

ifeq ($(CONFIG_HW_INIT),y)
CPPFLAGS += -DCONFIG_HW_INIT
endif

ifeq ($(CONFIG_USER_HW_INIT),y)
CPPFLAGS += -DCONFIG_USER_HW_INIT
endif

ifeq ($(CONFIG_OVERRIDE_CMDLINE),y)
CPPFLAGS += -DCONFIG_OVERRIDE_CMDLINE
endif

ifeq ($(CONFIG_OVERRIDE_CMDLINE_FROM_EXT_FILE),y)
CPPFLAGS += -DCONFIG_OVERRIDE_CMDLINE_FROM_EXT_FILE
endif

ifeq ($(CONFIG_BOARD_HAS_2_BANKS),y)
CPPFLAGS += -DMEM_BANK2=$(MEM_BANK2)
endif

#ifeq ($(CONFIG_LOAD_NONE),y)
#CPPFLAGS += -DCONFIG_LOAD_NONE
#endif

ifeq ($(CONFIG_CRYSTAL_12_000MHZ),y)
CPPFLAGS += -DBOARD_MAINOSC=12000000
endif

ifeq ($(CONFIG_CRYSTAL_16_000MHZ),y)
CPPFLAGS += -DBOARD_MAINOSC=16000000
endif

ifeq ($(CONFIG_CRYSTAL_16_36766MHZ),y)
CPPFLAGS += -DBOARD_MAINOSC=16367660
endif

ifeq ($(CONFIG_CRYSTAL_18_432MHZ),y)
CPPFLAGS += -DBOARD_MAINOSC=18432000
endif

ifeq ($(CONFIG_CRYSTAL_24_000MHZ),y)
CPPFLAGS += -DBOARD_MAINOSC=24000000
endif

ifeq ($(CONFIG_CONSOLE_INDEX_0),y)
CPPFLAGS += -DCONFIG_CONSOLE_INDEX=0
endif

ifeq ($(CONFIG_CONSOLE_INDEX_1),y)
CPPFLAGS += -DCONFIG_CONSOLE_INDEX=1
endif
ifeq ($(CONFIG_CONSOLE_INDEX_2),y)
CPPFLAGS += -DCONFIG_CONSOLE_INDEX=2
endif
ifeq ($(CONFIG_CONSOLE_INDEX_3),y)
CPPFLAGS += -DCONFIG_CONSOLE_INDEX=3
endif
ifeq ($(CONFIG_CONSOLE_INDEX_4),y)
CPPFLAGS += -DCONFIG_CONSOLE_INDEX=4
endif
ifeq ($(CONFIG_CONSOLE_INDEX_5),y)
CPPFLAGS += -DCONFIG_CONSOLE_INDEX=5
endif
ifeq ($(CONFIG_CONSOLE_INDEX_6),y)
CPPFLAGS += -DCONFIG_CONSOLE_INDEX=6
endif
ifeq ($(CONFIG_CONSOLE_INDEX_7),y)
CPPFLAGS += -DCONFIG_CONSOLE_INDEX=7
endif
ifeq ($(CONFIG_CONSOLE_INDEX_8),y)
CPPFLAGS += -DCONFIG_CONSOLE_INDEX=8
endif
ifeq ($(CONFIG_CONSOLE_INDEX_9),y)
CPPFLAGS += -DCONFIG_CONSOLE_INDEX=9
endif
ifeq ($(CONFIG_CONSOLE_INDEX_10),y)
CPPFLAGS += -DCONFIG_CONSOLE_INDEX=10
endif
ifeq ($(CONFIG_CONSOLE_INDEX_11),y)
CPPFLAGS += -DCONFIG_CONSOLE_INDEX=11
endif
ifeq ($(CONFIG_CONSOLE_INDEX_12),y)
CPPFLAGS += -DCONFIG_CONSOLE_INDEX=12
endif
ifeq ($(CONFIG_CONSOLE_INDEX_13),y)
CPPFLAGS += -DCONFIG_CONSOLE_INDEX=13
endif
ifeq ($(CONFIG_CONSOLE_INDEX_14),y)
CPPFLAGS += -DCONFIG_CONSOLE_INDEX=14
endif
ifeq ($(CONFIG_CONSOLE_INDEX_15),y)
CPPFLAGS += -DCONFIG_CONSOLE_INDEX=15
endif

