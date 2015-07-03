AT91Bootstrap Project

AT91Bootstrap is the 2nd level bootloader for Atmel SMART microprocessors (aka AT91).
It providing a set of algorithms to manage the hardware initialization such as
clock speed configuration, PIO settings, DRAM initialization, to download your
main application from specified boot media: NAND FLASH, serial FLASH (both
AT25-compatible of DataFlash), serial EEPROM, SD Card, etc. to main memory and
to start it.

1 GNU ARM Toolchain
================================================================================

AT91Bootstrap has been compiled and tested under Linux using the following GNU
ARM Toolchain:
- gcc version 4.2.1 (CodeSourcery Sourcery G++ Lite 2007q3-51)
- gcc version 4.2.3 (Sourcery G++ Lite 2008q1-126)
- gcc version 4.3.5 (Buildroot 2011.05)
- gcc version 4.4.1 (Sourcery G++ Lite 2009q3-67)
- gcc version 4.4.1 (Sourcery G++ Lite 2010q1-202)
- gcc version 4.5.2 (Sourcery G++ Lite 2011.03-41)
- gcc version 4.5.3 20110223 (prerelease) (GCC) (OE 2011.03)
- gcc version 4.6.3 (Ubuntu/Linaro 4.6.3-1ubuntu5)
- gcc version 4.7.2 (Sourcery CodeBench Lite 2012.09-64)
- gcc version 4.7.3 (Sourcery CodeBench Lite 2013.05-24)
- gcc version 4.8.2 (Ubuntu 4.8.2-19ubuntu1)

2 Compile AT91Bootstrap
================================================================================

2.1 Compile DataFlashBoot

Let's use at91sam9x5ek as an example,

2.1.1 Compile booting u-boot image from DataFlash

$ cd <project directory>
$ make mrproper
$ make at91sam9x5ekdf_uboot_defconfig
$ make

If the building process is successful, the final .bin image can be found under
binaries/

2.1.2 Compile booting kernel image from DataFlash

$ cd <project directory>
$ make mrproper
$ make at91sam9x5ekdf_linux_defconfig
$ make

If the building process is successful, the final .bin image can be found under
binaries/

2.1.3 Compile booting kernel & dt image from DataFlash

$ cd <project directory>
$ make mrproper
$ make at91sam9x5ekdf_linux_dt_defconfig
$ make

If the building process is successful, the final .bin image can be found under
binaries/

2.2 Compile NandFlashBoot

Let's use at91sam9m10g45ek as an example,

2.2.1 Compile booting u-boot image from NandFlash

$ cd <project directory>
$ make mrproper
$ make at91sam9m10g45eknf_uboot_defconfig 
$ make

If the building process is successful, the final .bin image can be found under
binaries/

2.2.2 Compile booting kernel image from NandFlash

$ cd <project directory>
$ make mrproper
$ make at91sam9m10g45eknf_linux_defconfig
$ make

If the building process is successful, the final .bin image can be found under
binaries/

2.2.3 Compile booting kernel & dt image from NandFlash

$ cd <project directory>
$ make mrproper
$ make at91sam9m10g45eknf_linux_dt_defconfig
$ make

If the building process is successful, the final .bin image can be found under
binaries/

2.3 Compile SDCardBoot

Let's use at91sam9m10g45ek as an example,

2.3.1 Compile booting u-boot image from SDCard

$ cd <project directory>
$ make mrproper
$ make at91sam9m10g45eksd_uboot_defconfig
$ make

If the building process is successful, the final .bin image can be found under
binaries/

2.3.2 Compile booting linux image from SDCard

$ cd <project directory>
$ make mrproper
$ make at91sam9m10g45eksd_linux_defconfig
$ make

If the building process is successful, the final .bin image can be found under
binaries/

2.3.3 Compile booting linux & dt image from SDCard

$ cd <project directory>
$ make mrproper
$ make at91sam9m10g45eksd_linux_dt_defconfig
$ make

If the building process is successful, the final .bin image can be found under
binaries/

3 Release
================================================================================
If you plan to release the project, you can use the command as below

$ cd <project directory>
$ make tarball

If the command is successful, the .tar.gz tar package can be found under
the project top directory.

4. Others
================================================================================
4.1 About booting from NOR flash.
4.1.1 ROM Code version
    Booting from the external NOR flash is supported in ROM code v2.1
    for SAMA5D3x. Bootstrap relocates the binary to the internal SRAM and run.

4.1.2. SAM-BA
    Using SAM-BA to program the binary to the NOR flash has a little different
    from other booting mode. there is no 'Send Boot File' command for NOR flash.

    You should use 'Send File' command to send the binary file as same as
    the normal file, with 'Address' selected to 0.

5 Contributing
================================================================================

To contribute to AT91Bootstrap you should submit the patches for review to:
the github pull-request facility directly or the forum. And don't forget to
Cc the maintainers.

AT91 Forum:
http://www.at91.com/discussions/

Maintainers:
Wenyou Yang <wenyou.yang@atmel.com>
Nicolas Ferre <nicolas.ferre@atmel.com>

When creating patches insert the [at91bootstrap] tag in the subject, for example
use something like:
git format-patch -s --subject-prefix='at91bootstrap][PATCH' <origin>

-End-
