target remote localhost:2331
monitor reset
monitor halt
file binaries/sama5d3xek-dataflash-boot-softapp-3.5.4-HGR_BaV.elf
load
break main
break load_dataflash
break dataflash_read_array_DMA
