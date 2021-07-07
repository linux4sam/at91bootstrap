# AT91Bootstrap Project

AT91Bootstrap is the 2nd level bootloader for Microchip microprocessors (aka AT91).
It providing a set of algorithms to manage the hardware initialization such as
clock speed configuration, PIO settings, DRAM initialization, to download your
main application from specified boot media: NAND FLASH, serial FLASH (both
AT25-compatible of DataFlash), serial EEPROM, SD Card, etc. to main memory and
to start it.

AT91Bootstrap 4 is the next milestone for AT91Bootstrap, which adds the support
for devices instead of boards, and full implementation for each device's
external memory support and serial connection.

Supported AT91 Devices:
- SAM9X60
- SAMA5D2
- SAMA5D3
- SAMA5D4
- SAMA7G5

1 Host Setup
================================================================================

## 1.1 Generic Requirements

Python3
 - needed by the scripts that prepend the PMECC header for the NAND flash boot

## 1.2 Linux Host Requirements

Refer to the GNU ARM Toolchain section below for toolchain recommendations.

We recommend using a GNU Make with a version of 4.2 or newer.

## 1.3 Windows Host Setup

### 1.3.1 Install required tools

A toolchain such as GNU Tools for Arm Embedded Processors shall be provided.
Get one from e.g. <https://developer.arm.com/open-source/gnu-toolchain/gnu-rm>.
Further instructions below are written as if the toolchain had been installed
to C:\opt\gnu_tools_arm\7-2018-q2.

Building AT91Bootstrap requires a POSIX environment. Several tools are available
on the market to provide such an environment. In these instructions we rely on
Minimal SYStem 2 (MSYS2).
Get MSYS2 from <http://www.msys2.org>.
Install it. The installation wizard ask for the installation folder, and
suggests to keep its full path short.
Further instructions below are written as if MSYS2 had been installed to
C:\opt\msys.

MSYS2 notably provides a minimal Bourne Shell, named mintty.
Launch mintty in the "MSYS2 MSYS" configuration: either search for the
"MSYS2 MSYS" shortcut in the Program menu, or invoke the Run dialog
('Windows' and 'R' key combination) and enter the following command at the Open
prompt:

    C:\opt\msys\msys2_shell.cmd -msys

In this terminal, whose prompt is suffixed with "MSYS", request the package
manager to update both its database and the packages already installed:

    $ pacman -Syuu

Still at the "MSYS" prompt, install additional packages that we will need later
on when building AT91Bootstrap:

    $ pacman -S bc gawk gcc git make python tar

Finally, close the "MSYS2 MSYS" terminal window.

### 1.3.2 Open a shell suitable for building AT91Bootstrap

Launch mintty in the "MSYS2 MinGW 64-bit" configuration: either search for the
"MSYS2 MinGW 64-bit" shortcut in the Program menu, or invoke the Run dialog
('Windows' and 'R' key combination) and enter the following command at the Open
prompt:

    C:\opt\msys\msys2_shell.cmd -mingw64

In this terminal, whose prompt is suffixed with "MINGW64", configure environment
variables:

    $ export CROSS_COMPILE=/c/opt/gnu_tools_arm/7-2018-q2/bin/arm-none-eabi-

Still at the "MINGW64" prompt, proceed with instructions given in the Compile
AT91Bootstrap section below.

2 GNU ARM Toolchain
================================================================================

AT91Bootstrap has been compiled and tested under Linux using the following GNU
ARM Toolchain:
- gcc version 7.2.1 (Linaro GCC 7.2-2017.11)
- gcc version 7.3.1 (Linaro GCC 7.2-2018.05)
- gcc version 7.5.0 (Linaro GCC 7.5-2019.12)
- gcc version 8.2.0 (Ubuntu 8.2.0-7ubuntu1)
- gcc version 10.2.1 20201103 (GNU Toolchain for the A-profile Architecture 10.2-2020.11 (arm-10.16))
We recommend using a toolchain newer than 6.0

3 Compile AT91Bootstrap
================================================================================

Bootstrap configuration files are placed in the configs directory.

Each configuration is named in the following format:

<i>\<board name>\[-bsr\]\<boot media>_\<image to boot>_defconfig</i>

Example: <i>sam9x60ekdf_qspi_linux_image_dt_defconfig</i> has

\<board name> = **sam9x60ek** : The SAM9X60 EK board

\[-bsr\] = optional , the fact that it's missing, means that CONFIG_BACKUP is not selected for this defconfig

\<boot media> = **df_qspi** : \<df> stands for DataFlash, this means that DataFlash QSPI is used as boot media for next stage

\<image to boot> = **linux_image_dt** : Linux image and device tree blob will be copied from boot media to external RAM

## 3.1 Compile DataFlash Boot (dataflash is QSPI in this example)

Let's use sam9x60ek as an example.

### 3.1.1 Compile booting kernel & dt image from dataflash (QSPI)

    $ cd <project directory>
    $ make mrproper
    $ make sam9x60ekdf_qspi_linux_image_dt_defconfig
    $ make

If the building process is successful, the final .bin image can be found under
build/binaries/

### 3.1.2 Compile booting u-boot image from dataflash (QSPI)

    $ cd <project directory>
    $ make mrproper
    $ make sam9x60ekdf_qspi_uboot_defconfig
    $ make

If the building process is successful, the final .bin image can be found under
build/binaries/

## 3.2 Compile NandFlash Boot

Let's use sam9x60ek as an example.

### 3.2.1 Compile booting kernel & dt image from NAND flash

    $ cd <project directory>
    $ make mrproper
    $ make sam9x60eknf_linux_image_dt_defconfig
    $ make

If the building process is successful, the final .bin image can be found under
build/binaries/

### 3.2.2 Compile booting u-boot image from NAND flash

    $ cd <project directory>
    $ make mrproper
    $ make sam9x60eknf_uboot_defconfig
    $ make

If the building process is successful, the final .bin image can be found under
build/binaries/

## 3.3 Compile SDCardBoot

Let's use sam9x60ek as an example,

### 3.3.1 Compile booting kernel & dt image from SDCard

    $ cd <project directory>
    $ make mrproper
    $ make sam9x60eksd_linux_image_dt_defconfig
    $ make

If the building process is successful, the final .bin image can be found under
build/binaries/

### 3.3.2 Compile booting u-boot image from SDCard

    $ cd <project directory>
    $ make mrproper
    $ make sam9x60eksd_uboot_dt_defconfig
    $ make

If the building process is successful, the final .bin image can be found under
build/binaries/

4 Release
================================================================================
If you plan to release the project, you can use the command as below

    $ cd <project directory>
    $ make tarball

If the command is successful, the .tar.gz tar package can be found under
the project top directory.

5 Customizing your bootstrap
================================================================================

## 5.1 Support for Device

### 5.1.1 Selecting your device

With AT91Bootstrap you can select your MPU device from the menuconfig.

### 5.1.2 Selecting your device features

You can select your device features, for example which of the USART to be used
as default output for the bootloader. All serial consoles and IOSETs are
already implemented. You have to pick the one your board uses from menuconfig.

You can also select your external memory device according to your board, and
your external memory timings to match supported memory module, or the
standard JEDEC timings.

6 Contributing your own board
================================================================================

If the system board that you have is not listed, then you will need
to port AT91Bootstrap to your hardware platform. To do this, you need to
customize your bootstrap as in chapter 5 of this documentation.

Once you are done customizing, you can do

    $ make savedefconfig

Then you will have a saved 'defconfig' file that can be placed into
configs/ directory, after you rename it according to the rule described
in chapter 3.

The configuration file can be send as a patch as described in chapter 7.

You should be able to do the above steps without requiring to write any actual C code.
However your board may require specific 'board quirks', as some boards do. In this case you will have to implement your quirk into AT91Bootstrap and send this board quirk as a separate patch. Board quirks include for example: resetting of certain devices on the board, reconfiguring specific I/O pins, or blocking the TWI access on some busses.

7 Contributing
================================================================================

To contribute to AT91Bootstrap you should submit the patches for review to
the github pull-request facility directly or the forum. And don't forget to
Cc the maintainers.

Linux4SAM Website:

https://www.linux4sam.org

Linux4SAM Github repository, with interface for opening issues and pull requests:

https://github.com/linux4sam

Microchip Linux for MPUs Forum:

https://www.microchip.com/forums/f542.aspx

Maintainers:

Eugen Hristev <eugen.hristev@microchip.com>

Nicolas Ferre <nicolas.ferre@microchip.com>

When creating patches insert the [at91bootstrap] tag in the subject, for example
use something like:

    git format-patch -s --subject-prefix='at91bootstrap][PATCH' <origin>

8 License
================================================================================

AT91Bootstrap is licensed under the MIT license.

License text file is available under LICENSES directory in the source code tree.

-End-
