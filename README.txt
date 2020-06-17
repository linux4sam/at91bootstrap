# AT91Bootstrap Project

AT91Bootstrap is the 2nd level bootloader for Microchip microprocessors (aka AT91).
It providing a set of algorithms to manage the hardware initialization such as
clock speed configuration, PIO settings, DRAM initialization, to download your
main application from specified boot media: NAND FLASH, serial FLASH (both
AT25-compatible of DataFlash), serial EEPROM, SD Card, etc. to main memory and
to start it.

1 Host Setup
================================================================================

## 1.1 Using an Integrated Development Environment

AT91Bootstrap was initially designed to bootstrap Linux-powered targets, and,
being based on Kconfig and Makefiles, is primarily configured and built from a
Bash shell on a Linux build system. Users of U-Boot and of the Linux Kernel are
already familiar with the commands involved in this process.

Now, and this will be detailed in the subsequent sections, other operating
systems may be used to compile AT91Bootstrap, still on the command line, once
the build system has been set up for that purpose.

As an alternative to using the Command-Line Interface, Microchip provides the
MPLAB X IDE, which can be used to build, load and debug AT91Bootstrap. This
environment is offered when targeting recent MPUs such as the SAM9X60 and the
SAMA5D2x series.
Users who favor an IDE over the CLI will find MPLAB X IDE available for Windows,
macOS and Linux platforms, at <https://www.microchip.com/mplab/mplab-x-ide>.

Note: the next sections will notably discuss the supported toolchains, which
shall be installed separately even when AT91Bootstrap is compiled within the
MPLAB X IDE.

## 1.2 Generic Requirements

Python3
 - needed by the scripts that prepend the PMECC header for the NAND flash boot

## 1.3 Linux Host Requirements

Refer to the GNU ARM Toolchain section below for toolchain recommendations.

## 1.4 macOS Host Setup

### 1.4.1 Install required tools

Many Unix-like utilities are installed as standard, as part of macOS - often in
a BSD or macOS variant - and are available at shell prompt.
AT91Bootstrap, to be configured and built, may require the GNU variant of a
given utility, occasionally. It also requires a few additional tools.
Several package managers are available on the market and provide a large choice
of open source tools, already compiled and packaged for macOS systems.
For this purpose and throughout this README we will use MacPorts, from
The MacPorts Project.
Get MacPorts from <https://www.macports.org> and follow the installation
instructions given on their website. As of writing, MacPorts requires Apple's
Xcode, and Xcode Command Line Tools, to be installed on the machine.

Once MacPorts is installed, open the terminal emulator of your choice. Apple's
Terminal for instance, which may be found under the Applications' Utilities
subdirectory. At shell prompt, request the MacPorts package manager to update
both its database and the packages already installed:

    $ sudo port -v selfupdate
    $ sudo port upgrade outdated

Now install the few additional packages needed to configure and build
AT91Bootstrap:

    $ sudo port install arm-none-eabi-binutils arm-none-eabi-gcc gettext ncurses
    $ sudo port install pkgconfig python38
    $ sudo port select --set python3 python38

Here a recent toolchain, notably, is obtained from MacPorts, conveniently.
By default, MacPorts installs executables - including those forming the
toolchain - in the /opt/local/bin directory and prepend the PATH environment
variable with this path.

Alternatively, may a specific toolchain or a specific version be preferred, GNU
Tools for Arm Embedded Processors, for instance, can be downloaded from
<https://developer.arm.com/open-source/gnu-toolchain/gnu-rm> and extracted to
the installation directory of your choice. The bin/ subdirectory there would
contain the compiler and other toolchain binaries used in subsequent steps.

### 1.4.2 Optionally configure MPLAB X IDE

If you use MPLAB X IDE and wish you could add the toolchain to the executable
search path, effective for all projects, you may edit the
mplab_platform/etc/mplab_ide.conf file in MPLAB's installation directory.
Mind that modifying this file will likely require administrator privileges.
Either open the file with a text editor such as MacroMates' TextMate, so that
you can append the below line to it, where /opt/local/bin stands for the path to
the toolchain binaries:

    PATH=$PATH:/opt/local/bin

Or do it on the command line. In a terminal emulator issue the below command,
where /opt/local/bin stands for the path to the toolchain binaries, and
/Applications/Microchip/MPLABX/v5.40 stands for the directory MPLAB has been
installed to:

    $ echo "PATH=\$PATH:/opt/local/bin" | sudo tee -a /Applications/Microchip/MPLABX/v5.40/mplab_platform/etc/mplab_ide.conf

The change will come into effect the next time you launch MPLAB X IDE.

### 1.4.3 Open a shell suitable for building AT91Bootstrap

Open the terminal emulator of your choice and configure environment variables:

    $ export CROSS_COMPILE=/opt/local/bin/arm-none-eabi-

Then, still at this shell prompt, proceed with the instructions given in the
Compile AT91Bootstrap section below.

## 1.5 Windows Host Setup

### 1.5.1 Install required tools

A toolchain such as GNU Tools for Arm Embedded Processors shall be provided.
Get one from e.g. <https://developer.arm.com/open-source/gnu-toolchain/gnu-rm>.
Further instructions below are written as if the toolchain had been installed
to C:\opt\gnu_tools_arm\7-2018-q2.

Building AT91Bootstrap on the command line requires a POSIX environment. Several
tools are available on the market to provide such an environment. In this
section we rely on Minimal SYStem 2 (MSYS2).
Get MSYS2 from <http://www.msys2.org>.
Install it. The installation wizard prompts for the installation directory, and
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

    $ pacman -S bash bc binutils bison coreutils findutils flex gawk gcc gettext
    $ pacman -S git gperf grep gzip make ncurses-devel pkg-config python sed tar
    $ pacman -S which

Finally, close the "MSYS2 MSYS" terminal window.

### 1.5.2 Open a shell suitable for building AT91Bootstrap

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
- gcc version 4.6.3 (Ubuntu/Linaro 4.6.3-1ubuntu5)
- gcc version 4.7.3 (Sourcery CodeBench Lite 2013.05-24)
- gcc version 4.8.2 (Ubuntu 4.8.2-19ubuntu1)
- gcc version 4.8.3 (Sourcery CodeBench Lite 2014.05-29)
- gcc version 4.9.3 (Linaro GCC 2014.11)
- gcc version 5.1.1 (Linaro GCC 5.1-2015.08)
- gcc version 7.2.1 (Linaro GCC 7.2-2017.11)
- gcc version 7.3.1 (Linaro GCC 7.2-2018.05)
- gcc version 8.2.0 (Ubuntu 8.2.0-7ubuntu1)

WARNING: check KNOWN_ISSUES for issues with older gcc versions. We recommend
using a toolchain newer than 6.0.

3 Compile AT91Bootstrap
================================================================================

## 3.1 Compile DataFlashBoot

Let's use at91sam9x5ek as an example.

### 3.1.1 Compile booting u-boot image from DataFlash

    $ cd <project directory>
    $ make mrproper
    $ make at91sam9x5ekdf_uboot_defconfig
    $ make

If the building process is successful, the final .bin image can be found under
binaries/

### 3.1.2 Compile booting kernel image from DataFlash

    $ cd <project directory>
    $ make mrproper
    $ make at91sam9x5ekdf_linux_defconfig
    $ make

If the building process is successful, the final .bin image can be found under
binaries/

### 3.1.3 Compile booting kernel & dt image from DataFlash

    $ cd <project directory>
    $ make mrproper
    $ make at91sam9x5ekdf_linux_dt_defconfig
    $ make

If the building process is successful, the final .bin image can be found under
binaries/

## 3.2 Compile NandFlashBoot

Let's use at91sam9m10g45ek as an example.

### 3.2.1 Compile booting u-boot image from NandFlash

    $ cd <project directory>
    $ make mrproper
    $ make at91sam9m10g45eknf_uboot_defconfig
    $ make

If the building process is successful, the final .bin image can be found under
binaries/

### 3.2.2 Compile booting kernel image from NandFlash

    $ cd <project directory>
    $ make mrproper
    $ make at91sam9m10g45eknf_linux_defconfig
    $ make

If the building process is successful, the final .bin image can be found under
binaries/

### 3.2.3 Compile booting kernel & dt image from NandFlash

    $ cd <project directory>
    $ make mrproper
    $ make at91sam9m10g45eknf_linux_dt_defconfig
    $ make

If the building process is successful, the final .bin image can be found under
binaries/

## 3.3 Compile SDCardBoot

Let's use at91sam9m10g45ek as an example,

### 3.3.1 Compile booting u-boot image from SDCard

    $ cd <project directory>
    $ make mrproper
    $ make at91sam9m10g45eksd_uboot_defconfig
    $ make

If the building process is successful, the final .bin image can be found under
binaries/

### 3.3.2 Compile booting linux image from SDCard

    $ cd <project directory>
    $ make mrproper
    $ make at91sam9m10g45eksd_linux_defconfig
    $ make

If the building process is successful, the final .bin image can be found under
binaries/

### 3.3.3 Compile booting linux & dt image from SDCard

    $ cd <project directory>
    $ make mrproper
    $ make at91sam9m10g45eksd_linux_dt_defconfig
    $ make

If the building process is successful, the final .bin image can be found under
binaries/

4 Release
================================================================================
If you plan to release the project, you can use the command as below

    $ cd <project directory>
    $ make tarball

If the command is successful, the .tar.gz tar package can be found under
the project top directory.

5 Others
================================================================================

## 5.1 About booting from NOR flash.

### 5.1.1 ROM Code version

Booting from the external NOR flash is supported in ROM code v2.1
for SAMA5D3x. Bootstrap relocates the binary to the internal SRAM and run.

### 5.1.2 SAM-BA

Using SAM-BA to program the binary to the NOR flash is a little different
from other booting mode. Namely, there is no 'Send Boot File' command for
NOR flash.

You should use 'Send File' command to send the binary file the same like
for a normal file, with 'Address' selected to 0.

6 Contributing your own board
================================================================================

If the system board that you have is not listed, then you will need
to port AT91Bootstrap to your hardware platform. To do this, follow these
steps:

1\. Create a new directory to hold your board specific code under
  contrib/board/ directory. Add any files you need.  
  In your board directory, you will need at least the "board.mk",
  a "<board>.c", "<board>.h", "Config.in.board", and "Config.in.boardname".  
2\. Create the necessary default configuration files such as
  "<board>df_uboot_defconfig" in your new board directory.  
3\. Add(source) your board's "Config.in.board" in "contrib/board/Config.in.board" file.  
4\. Add(source) your board's "Config.in.boardname" in the "contrib/board/Config.in.boardname" file.  
5\. Add your board's "<board>.h" in the "contrib/include/contrib_board.h" file.  
6\. Run "make <board>df_uboot_defconfig" with your new name.  
7\. Type "make", and you should get the final .bin image can be found under
  the binaries/ directory.  

7 Contributing
================================================================================

To contribute to AT91Bootstrap you should submit the patches for review to
the github pull-request facility directly or the forum. And don't forget to
Cc the maintainers.

AT91 Forum:

http://www.at91.com/discussions/

Maintainers:

Eugen Hristev <eugen.hristev@microchip.com>

Nicolas Ferre <nicolas.ferre@microchip.com>

When creating patches insert the [at91bootstrap] tag in the subject, for example
use something like:

    git format-patch -s --subject-prefix='at91bootstrap][PATCH' <origin>

-End-
