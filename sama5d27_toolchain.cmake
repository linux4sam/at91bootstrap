set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_STANDARD 99)

# Find arm-none-eabi-gcc
find_program(ARM_GCC_EXECUTABLE NAMES arm-none-eabi-gcc)
if(NOT ARM_GCC_EXECUTABLE)
  message(FATAL_ERROR "arm-none-eabi-gcc not found")
endif()

find_program(ARM_G++_EXECUTABLE NAMES arm-none-eabi-g++)
if(NOT ARM_G++_EXECUTABLE)
  message(FATAL_ERROR "arm-none-eabi-g++ not found")
endif()

# Specify the cross compiler (adjust the path if needed)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(SAMA5D27_LINK_ADDR 0x200000)

set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)
set(C_FLAGS "-ffunction-sections -mno-unaligned-access -nostdlib -fno-stack-protector -fno-common -fno-builtin -fno-jump-tables -fno-pie -mcpu=cortex-a5 -mtune=cortex-a5 -mfpu=vfpv4-d16")
set(CMAKE_C_FLAGS_INIT ${C_FLAGS})
set(CMAKE_CXX_FLAGS_INIT ${C_FLAGS})
set(CMAKE_ASM_FLAGS_INIT "-mcpu=cortex-a5 -mtune=cortex-a5 -mfpu=vfpv4-d16")

set(CMAKE_EXE_LINKER_FLAGS_INIT "-T ${CMAKE_SOURCE_DIR}/elf32-littlearm.lds -Wl,--gc-sections,-Map=${CMAKE_BINARY_DIR}/${PROJECT_NAME}.map,--cref -static -Ttext=${SAMA5D27_LINK_ADDR} -z noexecstack")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
