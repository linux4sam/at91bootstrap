cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/sama5d27_toolchain.cmake")
set(PROJECT_NAME at91bootstrap)

project(
  ${PROJECT_NAME}
  DESCRIPTION "Build the 2nd stage bootloader for the SAMA5D27"
  LANGUAGES C ASM
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
  ${PROJECT_NAME}_build
  crt0_gnu.S
  main.c
  driver/at91_aicredir.c
  driver/at91_flexcom.c
  driver/at91_pio.c
  driver/at91_pit.c
  driver/at91_rstc.c
  driver/at91_slowclk.c
  driver/at91_usart.c
  driver/at91_wdt.c
  driver/at91_xdmac.c
  driver/board_hw_init.c
  driver/common.c
  driver/ddramc.c
  driver/debug.c
  driver/led.c
  driver/lp310_l2cc.c
  driver/matrix.c
  driver/mci_media.c
  driver/sdcard.c
  driver/sdhc.c
  driver/sfrbu.c
  driver/shdwc.c
  driver/pmc/clk-common.c
  driver/pmc/master-clk.c
  driver/pmc/pll-clk.c
  driver/pmc/utmi-clk.c
  driver/pmc/periph-clk-sam9x5.c
  driver/pmc/generic-clk.c
  lib/consttime_memequal.c
  lib/string.c
  lib/div.c
  lib/eabi_utils.c
  lib/xmodem.c
  lib/crc16.c
  fs/src/ff.c
  fs/src/diskio.c
  fs/src/option/ccsbcs.c
  device/sama5d2/sama5d2.c
  device/sama5d2/flexcomm_usart.c
  device/sama5d2/serial_bootloader.c

)

target_include_directories(
  ${PROJECT_NAME}_build
  PRIVATE
  device/sama5d2
  include
  fs/include
  config/at91bootstrap-config
  lib
)

execute_process(
  COMMAND git describe --tags --always --dirty
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  OUTPUT_VARIABLE VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

set(OUTPUT_BINARY_NAME "BOOT.bin")
set(AT91BOOTSTRAP_VERSION "${VERSION}")
set(COMPILE_TIME "${current_time}")
set(LINK_ADDR 0x200000)
set(JUMP_ADDR 0x23f00000)
set(TOP_OF_MEMORY 0x210000)
set(IMAGE_NAME "BUILD.bin")
set(BANNER "AT91Bootstrap UART ${VERSION} ${current_time}")
set(BOARD_MAINOSC 24000000)
set(BOOTSTRAP_DEBUG_LEVEL DEBUG_INFO)
set(DDR_RAM_START 0x20ff0000)

string(TIMESTAMP current_time)

target_compile_options(
  ${PROJECT_NAME}_build
  PRIVATE
  -include ${CMAKE_CURRENT_BINARY_DIR}/version.h
  -Wall
  -g
  -Os
  -Wl,--defsym,TOP_OF_MEMORY=${TOP_OF_MEMORY}
  -Wl,--defsym,MACH_TYPE=9999
)

target_compile_definitions(
  ${PROJECT_NAME}_build
  PRIVATE
  IMG_ADDRESS
  IMG_SIZE
  MMU_TABLE_BASE_ADDR
  OF_OFFSET
  OF_ADDRESS
  CMDLINE_FILE
  CMDLINE
  CONFIG_DDR2
  CONFIG_DDR_1_GBIT
  CONFIG_PMC_MCK_CLK
  CONFIG_DEBUG
  USART_BOOT
)


configure_file(
  version.h.in
  version.h
  @ONLY
)


add_custom_command(
  TARGET ${PROJECT_NAME}_build
  POST_BUILD
  COMMAND arm-none-eabi-objcopy -O binary ${PROJECT_NAME}_build ${OUTPUT_BINARY_NAME}
)

add_custom_target(
  flash
  COMMAND zsh ${CMAKE_SOURCE_DIR}/cmake/flash.sh ${OUTPUT_BINARY_NAME}
)
add_dependencies(flash ${PROJECT_NAME}_build)
