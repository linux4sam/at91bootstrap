Compiling an at91bootstrap project

1 GNU ARM Toolchain
===========================================================================================
1.1 Linux

AT91Bootstrap has been compiled and tested under Linux using the following GNU ARM Toolchain
- gcc version 4.2.1 (CodeSourcery Sourcery G++ Lite 2007q3-51)
- gcc version 4.2.3 (Sourcery G++ Lite 2008q1-126)
- gcc version 4.4.1 (Sourcery G++ Lite 2009q3-67)
- gcc version 4.4.1 (Sourcery G++ Lite 2010q1-202)
- gcc version 4.5.2 (Sourcery G++ Lite 2011.03-41)
- gcc version 4.7.2 (Sourcery CodeBench Lite 2012.09-64)
- gcc version 4.6.3 (Ubuntu/Linaro 4.6.3-1ubuntu5)
- gcc version 4.5.3 20110223 (prerelease) (GCC) (OE 2011.03)
- gcc version 4.3.5 (Buildroot 2011.05)

1.2 Compile DataFlashBoot
===========================================================================================

Let's use at91sam9x5ek as an example,

1.2.1 Compile booting u-boot image from DataFlash

$ cd <project directory>
$ make mrproper
$ make at91sam9x5ekdf_uboot_defconfig
$ make

If the building process is successful, the final .bin image can be found under binaries/

1.2.2 Compile booting kernel image from DataFlash

$ cd <project directory>
$ make mrproper
$ make at91sam9x5ekdf_linux_defconfig
$ make

If the building process is successful, the final .bin image can be found under binaries/


1.2.3 Compile booting kernel & dt image from DataFlash

$ cd <project directory>
$ make mrproper
$ make at91sam9x5ekdf_linux_dt_defconfig
$ make

If the building process is successful, the final .bin image can be found under binaries/

1.3 Compile NandFlashBoot
===========================================================================================

Let's use at91sam9m10g45ek as an example,

1.3.1 Compile bootiing u-boot image from NandFlash

$ cd <project directory>
$ make mrproper
$ make at91sam9m10g45eknf_uboot_defconfig 
$ make

If the building process is successful, the final .bin image can be found under binaries/

1.3.2 Compile booting kernel image from NandFlash

$ cd <project directory>
$ make mrproper
$ make at91sam9m10g45eknf_linux_defconfig
$ make

If the building process is successful, the final .bin image can be found under binaries/

1.3.3 Compile booting kernel & dt image from NandFlash

$ cd <project directory>
$ make mrproper
$ make at91sam9m10g45eknf_linux_dt_defconfig
$ make

If the building process is successful, the final .bin image can be found under binaries/

1.4 Compile SDCardBoot
===========================================================================================

Let's use at91sam9m10g45ek as an example,

1.4.1 Compile booting u-boot image from SDCard

$ cd <project directory>
$ make mrproper
$ make at91sam9m10g45eksd_uboot_defconfig
$ make

If the building process is successful, the final .bin image can be found under binaries/

1.4.2 Compile booting linux image from SDCard

$ cd <project directory>
$ make mrproper
$ make at91sam9m10g45eksd_linux_defconfig
$ make

If the building process is successful, the final .bin image can be found under binaries/

1.4.2 Compile booting linux & dt image from SDCard

$ cd <project directory>
$ make mrproper
$ make at91sam9m10g45eksd_linux_dt_defconfig
$ make

If the building process is successful, the final .bin image can be found under binaries/

-End-
