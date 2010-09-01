1 Compiling an at91bootstrap project

1.1 GNU ARM Toolchain
===========================================================================================
1.1.1 Linux

AT91Bootstrap has been compiled and tested under Linux using the following GNU ARM
binary distribution which can be downloaded from the following URL: http://www.gnuarm.org
GCC-3.4 toolchain: binutils-2.15, gcc-3.4.3-c-c++-java, newlib-1.12.0, insight-6.1, tar.bz2
(or newer)
Once your toolchain is installed, install at91bootstrap in a directory and cd into it.

1.1.2 Windows

AT91Bootstrap has been compiled and tested under Cygwin using the following GNU ARM
binary distribution which can be downloaded from the following URL: http://www.gnuarm.org
GCC-4.1 toolchain: binutils-2.16.1, gcc-4.1.0-c-c++, newlib-1.14.0, insight-6.4, setup.exe
(or newer)
Note: Cygwin can be downloaded from the following URL:http://www.cygwin.com/


1.2 Compiling DataFlashBoot
===========================================================================================

1.2.1 AT91SAM9261-EK
---------------------
Go into the project directory
>  cd board/at91sam9261ek/dataflash
>  make

Configurations are in Makefile and at91sam9261ek.h files and can be modified according your needs.

1.2.2 AT91SAM9260-EK
---------------------
Go into the project directory
>  cd board/at91sam9260ek/dataflash
>  make

Configurations are in Makefile and at91sam9260ek.h files and can be modified according your needs.

===================================================================================================
===  WARNING for AT91SAM9260 DataFlashBoot							===
===================================================================================================
DataFlashBoot binary image size must be less than 4kBytes as it is the AT91SAM9260 internal available SRAM size.

According the GCC toolchain which is used (GCC-3.4 Toolchain or less), resulting code size
may be higher than the allowed 4kBytes. In such a case, either update your GCC toolchain to
a more recent one (GCC-4.0 Toolchain or higher) or do not use the provided gpio driver to
configure SDRAM PIOs for example. Indeed, replace sdramc_hw_init() function in
board/at91sam9260ek.c source file by:

#ifdef CFG_SDRAM
void sdramc_hw_init(void)
{
/* Configure the PIO controller to enable 32-bits SDRAM */
writel(0xFFFF0000, AT91C_BASE_PIOC + PIO_ASR(0));
writel(0xFFFF0000, AT91C_BASE_PIOC + PIO_PDR(0));
}
#endif

Note: Code is less readable but it should be sufficient enough to have less than 4kBytes code size
without having to re-compile a complete GCC toolchain.

