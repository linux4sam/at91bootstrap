/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (C) 2012 Atmel Corporation*
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaiimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "common.h"
#include "hardware.h"
#include "arch/at91sama5_mpddrc.h"

static inline unsigned int mpddrc_readl(unsigned int reg)
{
	return readl((void *)AT91C_BASE_MPDDRC + reg);
}

static inline void mpddrc_writel(unsigned int reg, unsigned int value)
{
	writel((value), ((void *)AT91C_BASE_MPDDRC + reg));
}

void init_mpddr_sdramc(void)
{
	unsigned int i;

	mpddrc_writel(MPDDRC_DLL_SOR, (0x01 | (0x01 << 16) | (0x01 << 24)));	/* MPDDRC DLL Slave Offset Register */
	
	mpddrc_writel(MPDDRC_DLL_MOR, 0xC5011f07);	/* MPDDRC DLL Master Offset Register */
	
	mpddrc_writel(MPDDRC_IO_CALIBR, 0x00850404);	/* MPDDRC I/O Calibration Register */

	/* 
	 * Step1#: Program the memory device type into the Memory Device Register 
	 */
	mpddrc_writel(MPDDRC_MD, AT91C_MPDDRC_MD_DDR2_SDRAM | AT91C_MPDDRC_DBW_32BITS);  /* Memory Device Register */

	/* 
	 * Step2#: Program the features of DDR2-SDRAM device into the Timing Register, 
	 * and into the Configuration Register
	 */
	mpddrc_writel(MPDDRC_TPR0, (AT91C_MPDDRC_TRAS_6		/* Timing 0 Register */
				| AT91C_MPDDRC_TRCD_2
				| AT91C_MPDDRC_TWR_2
				| AT91C_MPDDRC_TRC_8
				| AT91C_MPDDRC_TRP_2
				| AT91C_MPDDRC_TRRD_2
				| AT91C_MPDDRC_TWTR_2
				| AT91C_MPDDRC_TMRD_2));

	mpddrc_writel(MPDDRC_TPR1, 0x02C81311);	/* Timing 1 Register */

	mpddrc_writel(MPDDRC_TPR2, (AT91C_MPDDRC_TXARD_2	/* Timing 2 Register */
    				| AT91C_MPDDRC_TXARDS_7
				| AT91C_MPDDRC_TRPA_3
				| AT91C_MPDDRC_TRTP_2
				| AT91C_MPDDRC_TFAW_7));

	/* 
	 * Configuration Register:
	 * row = 13, column(DDR) = 10, CAS 3, 
	 * DLL reset disable, phase error correction is enabled / normal driver strength 
	 */
	mpddrc_writel(MPDDRC_CR, (AT91C_MPDDRC_NC_DDR10	
    				| AT91C_MPDDRC_NR_13
				| AT91C_MPDDRC_CAS_3_DDR2
				| AT91C_MPDDRC_NB_8
				| AT91C_MPDDRC_NDQS_DISABLED
				| AT91C_MPDDRC_UNAL_SUPPORTED));

	/*
	 * Step3#:An NOP command is issued to the DDR-SDRAM.
	 * Now, clocks which drive the DDR2-SDRAM device are enabled
	 */
	mpddrc_writel(MPDDRC_MR, AT91C_MPDDRC_MODE_NOP);
	writel(0x00000000,0x20000000);
	for (i = 0 ; i < 500000 ; i++);

	/*
	 * Step4#:An NOP command is issued to the DDR2-SDRAM.
	 * Now, CKE is driven high
	 */
	mpddrc_writel(MPDDRC_MR, AT91C_MPDDRC_MODE_NOP);
	writel(0x00000000,0x20000000);
	for (i = 0 ; i < 500000 ; i++);

	/*
	 * Step5#: An all bank precharge command is issued to the DDR2-SDRAM
	 */
	mpddrc_writel(MPDDRC_MR, AT91C_MPDDRC_MODE_PRECHARGE);
	writel(0x00000000,0x20000000);
	for (i = 0 ; i < 500000 ; i++);
 
 	/*
	 * Step6#: An Extended Mode Register set cycle is issued to chose between commercial 
	 * or high temperature operations.
	 * The write address must be chosen so that BA[1] is set to 1 and BA[0] is set to 0
	 */
	/* Step7#: This address is for example purposes only */ 
	mpddrc_writel(MPDDRC_MR, AT91C_MPDDRC_MODE_EXT_LMR);
	writel(0x00000000,0x24000000);
	for (i = 0 ; i < 500000 ; i++);

	/*
	 * Step8#: An Extended Mode Register set (EMRS3) cycle is issued to set the Extended Mode Register to "0"
	 * The write address must be chosen so that BA[1] is set 0 and BA[0] is set to 1
	 */
	mpddrc_writel(MPDDRC_MR, AT91C_MPDDRC_MODE_EXT_LMR);
	writel(0x00000000,0x26000000);
	for (i = 0 ; i < 500000 ; i++);
	
	/*
	 * Step9#: An Extended Mode Register set(EMRS1) cycle is issued to enabled DLL and to program D.I.C
	 * The write address must be chosen so that BA[1] is set to 0 and BA[0] is set to 1
	 */
	 /* Step10#: An additional 200 cycles of clock are required for locking DLL */
	mpddrc_writel(MPDDRC_MR, AT91C_MPDDRC_MODE_EXT_LMR);
	writel(0x00000000,0x22000000);
	for (i = 0 ; i < 500000 ; i++);

	/*
	 * Step11#: Program DLL field into the Configuration Register
	 */
	/* Configuration Register:Enable DLL reset */
	mpddrc_writel(MPDDRC_CR, (AT91C_MPDDRC_NC_DDR10	
    				| AT91C_MPDDRC_NR_13
				| AT91C_MPDDRC_CAS_3_DDR2
				| AT91C_MPDDRC_ENABLE_RST_DLL
				| AT91C_MPDDRC_NB_8
				| AT91C_MPDDRC_NDQS_DISABLED
				| AT91C_MPDDRC_UNAL_SUPPORTED));

	/*
	 * Step12#: A Mode Register set (MRS) cycle is issued to reset DLL.
	 */
	mpddrc_writel(MPDDRC_MR, AT91C_MPDDRC_MODE_LMR);
	writel(0x00000000,0x20000000);
	for (i = 0 ; i < 500000 ; i++);

	/*
	 * Step13#: An all bank precharge command is issued to the DDR2-SDRAM
	 */
	mpddrc_writel(MPDDRC_MR, AT91C_MPDDRC_MODE_PRECHARGE);
	writel(0x00000000,0x20000000);
	for (i = 0 ; i < 500000 ; i++);

	/*
	 * Step14#: Two auto-refresh (CBR) cycles are provided
	 */
	mpddrc_writel(MPDDRC_MR, AT91C_MPDDRC_MODE_REFRESH);
	writel(0x00000000,0x20000000);
	for (i = 0 ; i < 500000 ; i++);

	mpddrc_writel(MPDDRC_MR, AT91C_MPDDRC_MODE_REFRESH);
	writel(0x00000000,0x20000000);
	for (i = 0 ; i < 500000 ; i++);
	
	/*
	 * Step15#: Program DLL field into the Configuration Register to low (Disable DLL reset)
	 */
	/* Configuration Register:Disable DLL reset */
	mpddrc_writel(MPDDRC_CR, (AT91C_MPDDRC_NC_DDR10	
    				| AT91C_MPDDRC_NR_13
				| AT91C_MPDDRC_CAS_3_DDR2
				| AT91C_MPDDRC_DISABLE_RST_DLL
				| AT91C_MPDDRC_NB_8
				| AT91C_MPDDRC_NDQS_DISABLED
				| AT91C_MPDDRC_UNAL_SUPPORTED));

	/*
	 * Step16#: A Mode Register set cycle is issued to program the parameters of the DDR2-SDRAM devices,
	 * in particular CAS latency, burst length and to disable DLL reset.
	 */
	mpddrc_writel(MPDDRC_MR, AT91C_MPDDRC_MODE_LMR);
	writel(0x00000000,0x20000000);
	for (i = 0 ; i < 500000 ; i++);

	/* 
	 * Step17#: Program OCD field into the Configuration Register to high (OCD calibration default) 
	 */
	/* Configuration Register:OCD calibration default */
	mpddrc_writel(MPDDRC_CR, (AT91C_MPDDRC_NC_DDR10	
 			| AT91C_MPDDRC_NR_13
			| AT91C_MPDDRC_CAS_3_DDR2
			| AT91C_MPDDRC_OCD_DEFAULT
			| AT91C_MPDDRC_NB_8
			| AT91C_MPDDRC_NDQS_DISABLED
			| AT91C_MPDDRC_UNAL_SUPPORTED));

	/*
	 * Step18#: An Extended Mode Register (EMRS1) cycle is issued to OCD default value
	 * The write address must be chosen so that BA[1] is set to 0 and BA[0] is set to 1
	 */
	mpddrc_writel(MPDDRC_MR, AT91C_MPDDRC_MODE_EXT_LMR);
	writel(0x00000000,0x22000000);
	for (i = 0 ; i < 500000 ; i++);

	/*
	 * Step19#: Program OCD field in the Configuration Register to low (OCD calibration mode exit)
	 */
	/* Configuration Register:OCD calibration default */
	mpddrc_writel(MPDDRC_CR, (AT91C_MPDDRC_NC_DDR10
    				| AT91C_MPDDRC_NR_13
				| AT91C_MPDDRC_CAS_3_DDR2
				| AT91C_MPDDRC_NB_8
				| AT91C_MPDDRC_NDQS_DISABLED
				| AT91C_MPDDRC_UNAL_SUPPORTED));

	/*
	 * Step20#: An Extended Mode Register set (EMRS1) cycle is issued to enable OCD exit
	 * The write address must be chosen so that BA[1] is set to 0 and BA[0] is set to 1
	 */
	mpddrc_writel(MPDDRC_MR, AT91C_MPDDRC_MODE_EXT_LMR);
	writel(0x00000000,0x22000000);
	for (i = 0 ; i < 500000 ; i++);

	/*
	 * Step21#: A Normal mode command is provided
	 */
	mpddrc_writel(MPDDRC_MR, AT91C_MPDDRC_MODE_NORMAL);
	writel(0x00000000,0x20000000);
	for (i = 0 ; i < 500000 ; i++);

	/*
	 * Step22#: Perform a write access to any DDR2-SDRAM address
	 */
	writel(0x00000000,0x20000000);
	for (i = 0 ; i < 500000 ; i++);

	/*
	 * Step23#: Write the refresh rate into the count field in the Refresh Timer register
	 */
	mpddrc_writel(MPDDRC_RTR, 0x00300208);		/* Refresh Timer register : 520 for 133 MHz */
}
