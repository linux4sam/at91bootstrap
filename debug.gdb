target remote :2331
monitor reset
monitor halt
file binaries/at91bootstrap.elf
load
break main
break load_dataflash
