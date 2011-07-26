//  ----------------------------------------------------------------------------
//          ATMEL Microcontroller Software Support  -  ROUSSET  -
//  ----------------------------------------------------------------------------
//  DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
//  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
//  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
//  DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
//  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
//  OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
//  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  ----------------------------------------------------------------------------
// File Name           : AT91SAM9GX5.h
// Object              : AT91SAM9GX5 definitions
// Generated           : AT91 SW Application Group  07/28/2010 (14:47:34)
// 
// CVS Reference       : /AT91SAM9GX5.pl/1.34/Fri Jun 18 13:22:20 2010//
// CVS Reference       : /PIO3_SAM9GX5.pl/1.4/Fri Dec  4 13:56:54 2009//
// CVS Reference       : /HDMA_SAM9GX5.pl/1.1/Tue Mar  3 18:01:26 2009//
// CVS Reference       : /HMATRIX2_SAM9GX5.pl/1.3/Wed Jul 29 13:16:15 2009//
// CVS Reference       : /HDDRSDRC2_SAM9GX5.pl/1.1/Mon Jun 15 09:48:16 2009//
// CVS Reference       : /PMC_SAM9GX5.pl/1.3/Fri Dec  4 13:56:55 2009//
// CVS Reference       : /SYS_SAM9GX5.pl/1.3/Fri Dec  4 13:57:00 2009//
// CVS Reference       : /CCR_SAM9GX5.pl/1.7/Fri Jun 18 13:22:26 2010//
// CVS Reference       : /SFR_SAM9GX5.pl/1.3/Mon Apr  6 10:38:50 2009//
// CVS Reference       : /TSC_SAM9GX5.pl/1.3/Fri Dec  4 13:57:01 2009//
// CVS Reference       : /ISI_SAM9264.pl/1.2/Thu Feb  5 07:57:23 2009//
// CVS Reference       : /EMACB_SAM9264.pl/1.1/Tue Sep 25 12:07:23 2007//
// CVS Reference       : /HSMC3_SAM9264.pl/1.1/Wed Oct 10 09:39:31 2007//
// CVS Reference       : /EBI_SAM9260.pl/1.1/Fri Sep 30 12:12:14 2005//
// CVS Reference       : /BCH_SAM9GX5.pl/1.5/Fri Jun 18 13:22:22 2010//
// CVS Reference       : /BCH_EL_SAM9GX5.pl/1.2/Fri Jul 10 11:39:56 2009//
// CVS Reference       : /AIC_6075A.pl/1.1/Mon Jul 12 17:04:01 2004//
// CVS Reference       : /PDC_6074C.pl/1.2/Thu Feb  3 09:02:11 2005//
// CVS Reference       : /DBGU_SAM9GX5.pl/1.2/Fri Dec  4 13:56:49 2009//
// CVS Reference       : /RSTC_6098A.pl/1.4/Mon Sep 15 12:47:42 2008//
// CVS Reference       : /SHDWC_6122A.pl/1.3/Wed Oct  6 14:16:58 2004//
// CVS Reference       : /RTTC_6081A.pl/1.2/Thu Nov  4 13:57:22 2004//
// CVS Reference       : /PITC_6079A.pl/1.2/Thu Nov  4 13:56:22 2004//
// CVS Reference       : /WDTC_6080A.pl/1.3/Thu Nov  4 13:58:52 2004//
// CVS Reference       : /TC_6082A.pl/1.8/Mon Sep 15 12:49:16 2008//
// CVS Reference       : /MCI_SAM9GX5.pl/1.1/Mon Apr  6 10:43:48 2009//
// CVS Reference       : /TWI_SAM9GX5.pl/1.1/Mon Apr  6 10:43:49 2009//
// CVS Reference       : /US_SAM9GX5.pl/1.1/Mon Apr  6 10:38:52 2009//
// CVS Reference       : /SSC_SAM9GX5.pl/1.1/Mon Apr  6 10:38:51 2009//
// CVS Reference       : /SPI2_SAM9GX5.pl/1.1/Mon Apr  6 10:38:50 2009//
// CVS Reference       : /PWM_6044D.pl/1.2/Tue May 10 12:39:09 2005//
// CVS Reference       : /UDPHS_SAM9_7ept6dma4iso.pl/1.4/Wed Jun 11 09:13:52 2008//
// CVS Reference       : /RTC_1245D.pl/1.3/Fri Sep 17 14:01:31 2004//
// CVS Reference       : /uhphs_ohci.pl/1.1/Fri Jun 22 14:20:34 2007//
// CVS Reference       : /uhphs_ehci.pl/1.3/Tue Jul 17 07:50:29 2007//
// CVS Reference       : /CAN_6019B.pl/1.1/Mon Jan 31 13:54:30 2005//
// CVS Reference       : /HSSD_SAM.pl/1.4/Wed Jul 29 13:16:16 2009//
// CVS Reference       : /HLCDC4_prelim.pl/1.5/Fri Jun 18 13:22:25 2010//
//  ----------------------------------------------------------------------------

// Hardware register definition

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR SPECIAL FUNCTION REGISTER
// *****************************************************************************
// *** Register offset in AT91S_SFR structure ***
#define SFR_EMA         ( 0)    // memory Extra Margin Adjustment control
#define SFR_DDRCFG      ( 4)    // DDR2 SSTL18 control
#define SFR_EBIDELAY    (12)    // EBI DDR controller clock delay
#define SFR_UTMICFG     (16)    // UTMI Software Reset, and OHCI suspend interrupt control
#define SFR_INT         (20)    // OHCI suspend Interrupt status
// -------- SFR_EMA : (SFR Offset: 0x0) memory Extra Margin Adjustment control register -------- 
#define AT91C_SFR_RAM_EMA         (0x7UL <<  0) // (SFR) SRAM EMA
#define 	AT91C_SFR_RAM_EMA_0                    (0x0UL)  // (SFR) Normal Mode
#define 	AT91C_SFR_RAM_EMA_1                    (0x1UL)  // (SFR) DEBUG MODE 1
#define 	AT91C_SFR_RAM_EMA_2                    (0x2UL)  // (SFR) DEBUG MODE 2
#define 	AT91C_SFR_RAM_EMA_3                    (0x3UL)  // (SFR) DEBUG MODE 3
#define 	AT91C_SFR_RAM_EMA_4                    (0x4UL)  // (SFR) DEBUG MODE 4
#define 	AT91C_SFR_RAM_EMA_5                    (0x5UL)  // (SFR) DEBUG MODE 5
#define 	AT91C_SFR_RAM_EMA_6                    (0x6UL)  // (SFR) DEBUG MODE 6
#define 	AT91C_SFR_RAM_EMA_7                    (0x7UL)  // (SFR) DEBUG MODE 7
#define AT91C_SFR_DPRAM_EMA       (0x7UL <<  4) // (SFR) SRAM EMA
#define 	AT91C_SFR_DPRAM_EMA_0                    (0x0UL <<  4)  // (SFR) Normal Mode
#define 	AT91C_SFR_DPRAM_EMA_1                    (0x1UL <<  4)  // (SFR) DEBUG MODE 1
#define 	AT91C_SFR_DPRAM_EMA_2                    (0x2UL <<  4)  // (SFR) DEBUG MODE 2
#define 	AT91C_SFR_DPRAM_EMA_3                    (0x3UL <<  4)  // (SFR) DEBUG MODE 3
#define 	AT91C_SFR_DPRAM_EMA_4                    (0x4UL <<  4)  // (SFR) DEBUG MODE 4
#define 	AT91C_SFR_DPRAM_EMA_5                    (0x5UL <<  4)  // (SFR) DEBUG MODE 5
#define 	AT91C_SFR_DPRAM_EMA_6                    (0x6UL <<  4)  // (SFR) DEBUG MODE 6
#define 	AT91C_SFR_DPRAM_EMA_7                    (0x7UL <<  4)  // (SFR) DEBUG MODE 7
#define AT91C_SFR_RF_EMA          (0x7UL <<  8) // (SFR) SRAM EMA
#define 	AT91C_SFR_RF_EMA_0                    (0x0UL <<  8)     // (SFR) Normal Mode
#define 	AT91C_SFR_RF_EMA_1                    (0x1UL <<  8)     // (SFR) DEBUG MODE 1
#define 	AT91C_SFR_RF_EMA_2                    (0x2UL <<  8)     // (SFR) DEBUG MODE 2
#define 	AT91C_SFR_RF_EMA_3                    (0x3UL <<  8)     // (SFR) DEBUG MODE 3
#define 	AT91C_SFR_RF_EMA_4                    (0x4UL <<  8)     // (SFR) DEBUG MODE 4
#define 	AT91C_SFR_RF_EMA_5                    (0x5UL <<  8)     // (SFR) DEBUG MODE 5
#define 	AT91C_SFR_RF_EMA_6                    (0x6UL <<  8)     // (SFR) DEBUG MODE 6
#define 	AT91C_SFR_RF_EMA_7                    (0x7UL <<  8)     // (SFR) DEBUG MODE 7
#define AT91C_SFR_DPRF_EMA        (0x7UL << 12) // (SFR) SRAM EMA
#define 	AT91C_SFR_DPRF_EMA_0                    (0x0UL << 12)   // (SFR) Normal Mode
#define 	AT91C_SFR_DPRF_EMA_1                    (0x1UL << 12)   // (SFR) DEBUG MODE 1
#define 	AT91C_SFR_DPRF_EMA_2                    (0x2UL << 12)   // (SFR) DEBUG MODE 2
#define 	AT91C_SFR_DPRF_EMA_3                    (0x3UL << 12)   // (SFR) DEBUG MODE 3
#define 	AT91C_SFR_DPRF_EMA_4                    (0x4UL << 12)   // (SFR) DEBUG MODE 4
#define 	AT91C_SFR_DPRF_EMA_5                    (0x5UL << 12)   // (SFR) DEBUG MODE 5
#define 	AT91C_SFR_DPRF_EMA_6                    (0x6UL << 12)   // (SFR) DEBUG MODE 6
#define 	AT91C_SFR_DPRF_EMA_7                    (0x7UL << 12)   // (SFR) DEBUG MODE 7
#define AT91C_SFR_ROM_EMA         (0x7UL << 16) // (SFR) SRAM EMA
#define 	AT91C_SFR_ROM_EMA_0                    (0x0UL << 16)    // (SFR) Normal Mode
#define 	AT91C_SFR_ROM_EMA_1                    (0x1UL << 16)    // (SFR) DEBUG MODE 1
#define 	AT91C_SFR_ROM_EMA_2                    (0x2UL << 16)    // (SFR) DEBUG MODE 2
#define 	AT91C_SFR_ROM_EMA_3                    (0x3UL << 16)    // (SFR) DEBUG MODE 3
#define 	AT91C_SFR_ROM_EMA_4                    (0x4UL << 16)    // (SFR) DEBUG MODE 4
#define 	AT91C_SFR_ROM_EMA_5                    (0x5UL << 16)    // (SFR) DEBUG MODE 5
#define 	AT91C_SFR_ROM_EMA_6                    (0x6UL << 16)    // (SFR) DEBUG MODE 6
#define 	AT91C_SFR_ROM_EMA_7                    (0x7UL << 16)    // (SFR) DEBUG MODE 7
// -------- SFR_DDRCFG : (SFR Offset: 0x4) DDR2 SSTL18 control register -------- 
#define AT91C_SFR_DDRCFG_SSTL     (0x1UL <<  0) // (SFR) Control DDR2 pads SSTL mode control
#define 	AT91C_SFR_DDRCFG_SSTL_NORMAL               (0x0UL)      // (SFR) Force pads in SSTL18 mode when DDR2 is connected
#define 	AT91C_SFR_DDRCFG_SSTL_COMPATIBLE           (0x1UL)      // (SFR) LVCMOS level (compatible SSTL18)
#define AT91C_SFR_DDRCFG_CLKDELAY (0x1UL <<  8) // (SFR) Control DDR2 pads clocks delay on clk, dqs0, dqs1
#define 	AT91C_SFR_DDRCFG_CLKDELAY_HARD                 (0x0UL <<  8)    // (SFR) Fixed by hardware
#define 	AT91C_SFR_DDRCFG_CLKDELAY_SOFT                 (0x1UL <<  8)    // (SFR) Software must write correct delay value
// -------- SFR_EBIDELAY : (SFR Offset: 0xc) EBI DDR controller clock delay -------- 
#define AT91C_SFR_EBIDELAY_CLK    (0xFFUL <<  0)        // (SFR) Control CLK clock delay
#define 	AT91C_SFR_EBIDELAY_CLK_0                    (0x0UL)     // (SFR) minimum delay
#define 	AT91C_SFR_EBIDELAY_CLK_1                    (0x1UL)     // (SFR)
#define 	AT91C_SFR_EBIDELAY_CLK_2                    (0x2UL)     // (SFR)
#define 	AT91C_SFR_EBIDELAY_CLK_3                    (0x3UL)     // (SFR)
#define 	AT91C_SFR_EBIDELAY_CLK_4                    (0x4UL)     // (SFR)
#define 	AT91C_SFR_EBIDELAY_CLK_5                    (0x5UL)     // (SFR)
#define 	AT91C_SFR_EBIDELAY_CLK_6                    (0x6UL)     // (SFR)
#define 	AT91C_SFR_EBIDELAY_CLK_7                    (0x7UL)     // (SFR)
#define 	AT91C_SFR_EBIDELAY_CLK_8                    (0x8UL)     // (SFR)
#define 	AT91C_SFR_EBIDELAY_CLK_9                    (0x9UL)     // (SFR)
#define 	AT91C_SFR_EBIDELAY_CLK_10                   (0xAUL)     // (SFR)
#define 	AT91C_SFR_EBIDELAY_CLK_11                   (0xBUL)     // (SFR)
#define 	AT91C_SFR_EBIDELAY_CLK_12                   (0xCUL)     // (SFR)
#define 	AT91C_SFR_EBIDELAY_CLK_13                   (0xDUL)     // (SFR)
#define 	AT91C_SFR_EBIDELAY_CLK_14                   (0xEUL)     // (SFR)
#define 	AT91C_SFR_EBIDELAY_CLK_15                   (0xFUL)     // (SFR)
#define 	AT91C_SFR_EBIDELAY_CLK_16                   (0x10UL)    // (SFR)
#define AT91C_SFR_EBIDELAY_DQS0   (0xFFUL <<  8)        // (SFR) Control DQS0 clock delay
#define 	AT91C_SFR_EBIDELAY_DQS0_0                    (0x0UL <<  8)      // (SFR) minimum delay
#define 	AT91C_SFR_EBIDELAY_DQS0_1                    (0x1UL <<  8)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS0_2                    (0x2UL <<  8)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS0_3                    (0x3UL <<  8)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS0_4                    (0x4UL <<  8)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS0_5                    (0x5UL <<  8)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS0_6                    (0x6UL <<  8)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS0_7                    (0x7UL <<  8)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS0_8                    (0x8UL <<  8)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS0_9                    (0x9UL <<  8)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS0_10                   (0xAUL <<  8)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS0_11                   (0xBUL <<  8)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS0_12                   (0xCUL <<  8)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS0_13                   (0xDUL <<  8)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS0_14                   (0xEUL <<  8)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS0_15                   (0xFUL <<  8)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS0_16                   (0x10UL <<  8)     // (SFR)
#define AT91C_SFR_EBIDELAY_DQS1   (0xFFUL << 16)        // (SFR) Control DQS1 clock delay
#define 	AT91C_SFR_EBIDELAY_DQS1_0                    (0x0UL << 16)      // (SFR) minimum delay
#define 	AT91C_SFR_EBIDELAY_DQS1_1                    (0x1UL << 16)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS1_2                    (0x2UL << 16)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS1_3                    (0x3UL << 16)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS1_4                    (0x4UL << 16)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS1_5                    (0x5UL << 16)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS1_6                    (0x6UL << 16)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS1_7                    (0x7UL << 16)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS1_8                    (0x8UL << 16)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS1_9                    (0x9UL << 16)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS1_10                   (0xAUL << 16)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS1_11                   (0xBUL << 16)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS1_12                   (0xCUL << 16)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS1_13                   (0xDUL << 16)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS1_14                   (0xEUL << 16)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS1_15                   (0xFUL << 16)      // (SFR)
#define 	AT91C_SFR_EBIDELAY_DQS1_16                   (0x10UL << 16)     // (SFR)
// -------- SFR_UTMICFG : (SFR Offset: 0x10) UTMI Software Reset -------- 
#define AT91C_SFR_UTMICFG_PORT0   (0x1UL <<  0) // (SFR) UTMI Software Reset port 0
#define AT91C_SFR_UTMICFG_PORT1   (0x1UL <<  1) // (SFR) UTMI Software Reset port 1
#define AT91C_SFR_UTMICFG_PORT2   (0x1UL <<  2) // (SFR) UTMI Software Reset port 2
#define AT91C_SFR_UTMICFG_OHCI_SUSP_INT_ENABLE (0x1UL <<  4)    // (SFR) OHCI Suspend Interrupt enable
#define AT91C_SFR_UTMICFG_OHCI_APP_START_CLK (0x1UL <<  5)      // (SFR) OHCI App Start Clock
#define AT91C_SFR_UTMICFG_UTMI_FORCE_PULLUP_OFF (0x1UL << 23)   // (SFR) UTMI Force Pullup Off
// -------- SFR_OHCI_SUSP_INT : (SFR Offset: 0x14) OHCI suspend Interrupt status -------- 
#define AT91C_SFR_OHCI_SUSP_INT_STATUS (0x3UL <<  0)    // (SFR) OHCI suspend Interrupt status
#define 	AT91C_SFR_OHCI_SUSP_INT_STATUS_PORT0                (0x1UL)     // (SFR) OHCI suspend Interrupt status for port 0
#define 	AT91C_SFR_OHCI_SUSP_INT_STATUS_PORT1                (0x2UL)     // (SFR) OHCI suspend Interrupt status for port 1

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR System Peripherals
// *****************************************************************************
// -------- SLCKSEL : (SYS Offset: 0x3e50) Slow Clock Selection Register (Osc32k Mode Register) -------- 
#define AT91C_SLCKSEL_RCEN        (0x1UL <<  0) // (SYS) Enable Internal RC Oscillator
#define AT91C_SLCKSEL_OSC32EN     (0x1UL <<  1) // (SYS) Enable External Oscillator
#define AT91C_SLCKSEL_OSC32BYP    (0x1UL <<  2) // (SYS) Bypass External Oscillator
#define AT91C_SLCKSEL_OSCSEL      (0x1UL <<  3) // (SYS) OSC Selection
// -------- BSCR : (SYS Offset: 0x3e54) BSCR Boot Sequence Control Register -------- 
#define AT91C_BSCR_BSCV           (0x7UL <<  0) // (SYS) Boot Sequence Control Value
// -------- GPBR : (SYS Offset: 0x3e60) GPBR General Purpose Register -------- 
#define AT91C_GPBR_GPRV           (0x0UL <<  0) // (SYS) General Purpose Register Value

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR External Bus Interface
// *****************************************************************************
// *** Register offset in AT91S_EBI structure ***
#define EBI_DUMMY       ( 0)    // Dummy register - Do not use

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR DDR2/SDRAM Controller
// *****************************************************************************
// *** Register offset in AT91S_HDDRSDRC2 structure ***
#define HDDRSDRC2_MR    ( 0)    // Mode Register
#define HDDRSDRC2_RTR   ( 4)    // Refresh Timer Register
#define HDDRSDRC2_CR    ( 8)    // Configuration Register
#define HDDRSDRC2_T0PR  (12)    // Timing0 Register
#define HDDRSDRC2_T1PR  (16)    // Timing1 Register
#define HDDRSDRC2_T2PR  (20)    // Timing2 Register
#define HDDRSDRC2_T3PR  (24)    // Timing3 Register
#define HDDRSDRC2_LPR   (28)    // Low-power Register
#define HDDRSDRC2_MDR   (32)    // Memory Device Register
#define HDDRSDRC2_DLL   (36)    // DLL Information Register
#define HDDRSDRC2_VER   (40)    // DLL Version Register
#define HDDRSDRC2_HS    (44)    // High Speed Register
#define HDDRSDRC2_REF   (48)    // Adjust Refresh Register
#define HDDRSDRC2_DELAY1 (52)   // Pad delay1 Register
#define HDDRSDRC2_DELAY2 (56)   // Pad delay2 Register
#define HDDRSDRC2_DELAY3 (60)   // Pad delay3 Register
#define HDDRSDRC2_DELAY4 (64)   // Pad delay4 Register
#define HDDRSDRC2_DELAY5 (68)   // Pad delay5 Register
#define HDDRSDRC2_DELAY6 (72)   // Pad delay6 Register
#define HDDRSDRC2_DELAY7 (76)   // Pad delay7 Register
#define HDDRSDRC2_DELAY8 (80)   // Pad delay8 Register
#define HDDRSDRC2_DRIVESTRENGTH (84)    // Drive Strength I/O Register
#define HDDRSDRC2_WPCR  (228)   // High Speed Register
#define HDDRSDRC2_WPSR  (232)   // High Speed Register
#define HDDRSDRC2_VERSION (252) // Version Register
// -------- HDDRSDRC2_MR : (HDDRSDRC2 Offset: 0x0) Mode Register -------- 
#define AT91C_DDRC2_MODE          (0x7UL <<  0) // (HDDRSDRC2) DDR/SDRAM Command Mode
#define 	AT91C_DDRC2_MODE_NORMAL_CMD           (0x0UL)   // (HDDRSDRC2) Normal Mode
#define 	AT91C_DDRC2_MODE_NOP_CMD              (0x1UL)   // (HDDRSDRC2) Issue a NOP Command at every access
#define 	AT91C_DDRC2_MODE_PRCGALL_CMD          (0x2UL)   // (HDDRSDRC2) Issue a All Banks Precharge Command at every access
#define 	AT91C_DDRC2_MODE_LMR_CMD              (0x3UL)   // (HDDRSDRC2) Issue a Load Mode Register at every access
#define 	AT91C_DDRC2_MODE_RFSH_CMD             (0x4UL)   // (HDDRSDRC2) Issue a Refresh
#define 	AT91C_DDRC2_MODE_EXT_LMR_CMD          (0x5UL)   // (HDDRSDRC2) Issue an Extended Load Mode Register
#define 	AT91C_DDRC2_MODE_DEEP_CMD             (0x6UL)   // (HDDRSDRC2) Enter Deep Power Mode
#define 	AT91C_DDRC2_MODE_Reserved             (0x7UL)   // (HDDRSDRC2) Reserved value
// -------- HDDRSDRC2_RTR : (HDDRSDRC2 Offset: 0x4) Refresh Timer Register -------- 
#define AT91C_DDRC2_COUNT         (0xFFFUL <<  0)       // (HDDRSDRC2) Refresh Timer Count
// -------- HDDRSDRC2_CR : (HDDRSDRC2 Offset: 0x8) Configuration Register -------- 
#define AT91C_DDRC2_NC            (0x3UL <<  0) // (HDDRSDRC2) Number of Column Bits
#define 	AT91C_DDRC2_NC_DDR9_SDR8            (0x0UL)     // (HDDRSDRC2) DDR 9 Bits | SDR 8 Bits
#define 	AT91C_DDRC2_NC_DDR10_SDR9           (0x1UL)     // (HDDRSDRC2) DDR 10 Bits | SDR 9 Bits
#define 	AT91C_DDRC2_NC_DDR11_SDR10          (0x2UL)     // (HDDRSDRC2) DDR 11 Bits | SDR 10 Bits
#define 	AT91C_DDRC2_NC_DDR12_SDR11          (0x3UL)     // (HDDRSDRC2) DDR 12 Bits | SDR 11 Bits
#define AT91C_DDRC2_NR            (0x3UL <<  2) // (HDDRSDRC2) Number of Row Bits
#define 	AT91C_DDRC2_NR_11                   (0x0UL <<  2)       // (HDDRSDRC2) 11 Bits
#define 	AT91C_DDRC2_NR_12                   (0x1UL <<  2)       // (HDDRSDRC2) 12 Bits
#define 	AT91C_DDRC2_NR_13                   (0x2UL <<  2)       // (HDDRSDRC2) 13 Bits
#define 	AT91C_DDRC2_NR_14                   (0x3UL <<  2)       // (HDDRSDRC2) 14 Bits
#define AT91C_DDRC2_CAS           (0x7UL <<  4) // (HDDRSDRC2) CAS Latency
#define 	AT91C_DDRC2_CAS_2                    (0x2UL <<  4)      // (HDDRSDRC2) 2 cycles (DDR1/SDR)
#define 	AT91C_DDRC2_CAS_3                    (0x3UL <<  4)      // (HDDRSDRC2) 3 cycles (DDR2/DDR1/SDR)
#define 	AT91C_DDRC2_CAS_4                    (0x4UL <<  4)      // (HDDRSDRC2) 4 cycles (DDR2)
#define 	AT91C_DDRC2_CAS_2_5                  (0x6UL <<  4)      // (HDDRSDRC2) 2.5 cycles (DDR1)
#define AT91C_DDRC2_DLL           (0x1UL <<  7) // (HDDRSDRC2) DLL Reset
#define 	AT91C_DDRC2_DLL_RESET_DISABLED       (0x0UL <<  7)      // (HDDRSDRC2) DLL normal mode
#define 	AT91C_DDRC2_DLL_RESET_ENABLED        (0x1UL <<  7)      // (HDDRSDRC2) Reset DLL
#define AT91C_DDRC2_DIC_DS        (0x1UL <<  8) // (HDDRSDRC2) Output driver impedance control
#define AT91C_DDRC2_OCD           (0x7UL << 12) // (HDDRSDRC2) Off chip driver
#define 	AT91C_DDRC2_OCD_EXIT                 (0x0UL << 12)      // (HDDRSDRC2) Exit OCD calibration mode.
#define 	AT91C_DDRC2_OCD_DEFAULT              (0x7UL << 12)      // (HDDRSDRC2) Program OCD calibration default value.
#define AT91C_DDRC2_DQMS          (0x1UL << 16) // (HDDRSDRC2) Data Mask share
#define 	AT91C_DDRC2_DQMS_NOT_SHARED           (0x0UL << 16)     // (HDDRSDRC2) Used DQM bits are not shared
#define 	AT91C_DDRC2_DQMS_SHARED               (0x1UL << 16)     // (HDDRSDRC2) Used DQM bits are shared
#define AT91C_DDRC2_ENRDM         (0x1UL << 17) // (HDDRSDRC2) DQS/DATA phase error correction
#define 	AT91C_DDRC2_ENRDM_OFF                  (0x0UL << 17)    // (HDDRSDRC2) phase error correction disabled
#define 	AT91C_DDRC2_ENRDM_ON                   (0x1UL << 17)    // (HDDRSDRC2) phase error correction enabled
#define AT91C_DDRC2_NB_BANKS      (0x1UL << 20) // (HDDRSDRC2) Number of Banks
#define 	AT91C_DDRC2_NB_BANKS_4              (0x0UL << 20)    // (HDDRSDRC2) 4 banks
#define 	AT91C_DDRC2_NB_BANKS_8              (0x1UL << 20)    // (HDDRSDRC2) 8 banks
#define AT91C_DDRC2_DECOD         (0x1UL << 22) // (HDDRSDRC2) Type of Decoding
#define 	AT91C_DDRC2_DECOD_SEQUENTIAL        (0x0UL << 22)
#define 	AT91C_DDRC2_DECOD_INTERLEAVED       (0x1UL << 22)
// -------- HDDRSDRC2_T0PR : (HDDRSDRC2 Offset: 0xc) Timing0 Register -------- 
#define AT91C_DDRC2_TRAS          (0xFUL <<  0) // (HDDRSDRC2) Active to precharge delay
#define 	AT91C_DDRC2_TRAS_0                    (0x0UL)   // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TRAS_1                    (0x1UL)   // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TRAS_2                    (0x2UL)   // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TRAS_3                    (0x3UL)   // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TRAS_4                    (0x4UL)   // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TRAS_5                    (0x5UL)   // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TRAS_6                    (0x6UL)   // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TRAS_7                    (0x7UL)   // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TRAS_8                    (0x8UL)   // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TRAS_9                    (0x9UL)   // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TRAS_10                   (0xAUL)   // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TRAS_11                   (0xBUL)   // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TRAS_12                   (0xCUL)   // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TRAS_13                   (0xDUL)   // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TRAS_14                   (0xEUL)   // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TRAS_15                   (0xFUL)   // (HDDRSDRC2) Value : 15
#define AT91C_DDRC2_TRCD          (0xFUL <<  4) // (HDDRSDRC2) Row to column delay
#define 	AT91C_DDRC2_TRCD_0                    (0x0UL <<  4)     // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TRCD_1                    (0x1UL <<  4)     // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TRCD_2                    (0x2UL <<  4)     // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TRCD_3                    (0x3UL <<  4)     // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TRCD_4                    (0x4UL <<  4)     // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TRCD_5                    (0x5UL <<  4)     // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TRCD_6                    (0x6UL <<  4)     // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TRCD_7                    (0x7UL <<  4)     // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TRCD_8                    (0x8UL <<  4)     // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TRCD_9                    (0x9UL <<  4)     // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TRCD_10                   (0xAUL <<  4)     // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TRCD_11                   (0xBUL <<  4)     // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TRCD_12                   (0xCUL <<  4)     // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TRCD_13                   (0xDUL <<  4)     // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TRCD_14                   (0xEUL <<  4)     // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TRCD_15                   (0xFUL <<  4)     // (HDDRSDRC2) Value : 15
#define AT91C_DDRC2_TWR           (0xFUL <<  8) // (HDDRSDRC2) Write recovery delay
#define 	AT91C_DDRC2_TWR_0                    (0x0UL <<  8)      // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TWR_1                    (0x1UL <<  8)      // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TWR_2                    (0x2UL <<  8)      // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TWR_3                    (0x3UL <<  8)      // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TWR_4                    (0x4UL <<  8)      // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TWR_5                    (0x5UL <<  8)      // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TWR_6                    (0x6UL <<  8)      // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TWR_7                    (0x7UL <<  8)      // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TWR_8                    (0x8UL <<  8)      // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TWR_9                    (0x9UL <<  8)      // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TWR_10                   (0xAUL <<  8)      // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TWR_11                   (0xBUL <<  8)      // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TWR_12                   (0xCUL <<  8)      // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TWR_13                   (0xDUL <<  8)      // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TWR_14                   (0xEUL <<  8)      // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TWR_15                   (0xFUL <<  8)      // (HDDRSDRC2) Value : 15
#define AT91C_DDRC2_TRC           (0xFUL << 12) // (HDDRSDRC2) Row cycle delay
#define 	AT91C_DDRC2_TRC_0                    (0x0UL << 12)      // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TRC_1                    (0x1UL << 12)      // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TRC_2                    (0x2UL << 12)      // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TRC_3                    (0x3UL << 12)      // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TRC_4                    (0x4UL << 12)      // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TRC_5                    (0x5UL << 12)      // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TRC_6                    (0x6UL << 12)      // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TRC_7                    (0x7UL << 12)      // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TRC_8                    (0x8UL << 12)      // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TRC_9                    (0x9UL << 12)      // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TRC_10                   (0xAUL << 12)      // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TRC_11                   (0xBUL << 12)      // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TRC_12                   (0xCUL << 12)      // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TRC_13                   (0xDUL << 12)      // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TRC_14                   (0xEUL << 12)      // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TRC_15                   (0xFUL << 12)      // (HDDRSDRC2) Value : 15
#define AT91C_DDRC2_TRP           (0xFUL << 16) // (HDDRSDRC2) Row precharge delay
#define 	AT91C_DDRC2_TRP_0                    (0x0UL << 16)      // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TRP_1                    (0x1UL << 16)      // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TRP_2                    (0x2UL << 16)      // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TRP_3                    (0x3UL << 16)      // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TRP_4                    (0x4UL << 16)      // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TRP_5                    (0x5UL << 16)      // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TRP_6                    (0x6UL << 16)      // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TRP_7                    (0x7UL << 16)      // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TRP_8                    (0x8UL << 16)      // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TRP_9                    (0x9UL << 16)      // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TRP_10                   (0xAUL << 16)      // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TRP_11                   (0xBUL << 16)      // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TRP_12                   (0xCUL << 16)      // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TRP_13                   (0xDUL << 16)      // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TRP_14                   (0xEUL << 16)      // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TRP_15                   (0xFUL << 16)      // (HDDRSDRC2) Value : 15
#define AT91C_DDRC2_TRRD          (0xFUL << 20) // (HDDRSDRC2) Active bankA to Active bankB
#define 	AT91C_DDRC2_TRRD_0                    (0x0UL << 20)     // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TRRD_1                    (0x1UL << 20)     // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TRRD_2                    (0x2UL << 20)     // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TRRD_3                    (0x3UL << 20)     // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TRRD_4                    (0x4UL << 20)     // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TRRD_5                    (0x5UL << 20)     // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TRRD_6                    (0x6UL << 20)     // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TRRD_7                    (0x7UL << 20)     // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TRRD_8                    (0x8UL << 20)     // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TRRD_9                    (0x9UL << 20)     // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TRRD_10                   (0xAUL << 20)     // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TRRD_11                   (0xBUL << 20)     // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TRRD_12                   (0xCUL << 20)     // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TRRD_13                   (0xDUL << 20)     // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TRRD_14                   (0xEUL << 20)     // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TRRD_15                   (0xFUL << 20)     // (HDDRSDRC2) Value : 15
#define AT91C_DDRC2_TWTR          (0x7UL << 24) // (HDDRSDRC2) Internal write to read delay
#define 	AT91C_DDRC2_TWTR_0                    (0x0UL << 24)
#define 	AT91C_DDRC2_TWTR_1                    (0x1UL << 24)
#define 	AT91C_DDRC2_TWTR_2                    (0x2UL << 24)
#define 	AT91C_DDRC2_TWTR_3                    (0x3UL << 24)
#define 	AT91C_DDRC2_TWTR_4                    (0x4UL << 24)
#define 	AT91C_DDRC2_TWTR_5                    (0x5UL << 24)
#define 	AT91C_DDRC2_TWTR_6                    (0x6UL << 24)
#define 	AT91C_DDRC2_TWTR_7                    (0x7UL << 24)
#define AT91C_DDRC2_TMRD          (0xFUL << 28) // (HDDRSDRC2) Load mode register command to active or refresh command
#define 	AT91C_DDRC2_TMRD_0                    (0x0UL << 28)     // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TMRD_1                    (0x1UL << 28)     // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TMRD_2                    (0x2UL << 28)     // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TMRD_3                    (0x3UL << 28)     // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TMRD_4                    (0x4UL << 28)     // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TMRD_5                    (0x5UL << 28)     // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TMRD_6                    (0x6UL << 28)     // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TMRD_7                    (0x7UL << 28)     // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TMRD_8                    (0x8UL << 28)     // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TMRD_9                    (0x9UL << 28)     // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TMRD_10                   (0xAUL << 28)     // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TMRD_11                   (0xBUL << 28)     // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TMRD_12                   (0xCUL << 28)     // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TMRD_13                   (0xDUL << 28)     // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TMRD_14                   (0xEUL << 28)     // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TMRD_15                   (0xFUL << 28)     // (HDDRSDRC2) Value : 15
// -------- HDDRSDRC2_T1PR : (HDDRSDRC2 Offset: 0x10) Timing1 Register -------- 
#define AT91C_DDRC2_TRFC          (0x1FUL <<  0)        // (HDDRSDRC2) row cycle delay
#define 	AT91C_DDRC2_TRFC_0                    (0x0UL)   // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TRFC_1                    (0x1UL)   // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TRFC_2                    (0x2UL)   // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TRFC_3                    (0x3UL)   // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TRFC_4                    (0x4UL)   // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TRFC_5                    (0x5UL)   // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TRFC_6                    (0x6UL)   // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TRFC_7                    (0x7UL)   // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TRFC_8                    (0x8UL)   // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TRFC_9                    (0x9UL)   // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TRFC_10                   (0xAUL)   // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TRFC_11                   (0xBUL)   // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TRFC_12                   (0xCUL)   // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TRFC_13                   (0xDUL)   // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TRFC_14                   (0xEUL)   // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TRFC_15                   (0xFUL)   // (HDDRSDRC2) Value : 15
#define 	AT91C_DDRC2_TRFC_16                   (0x10UL)  // (HDDRSDRC2) Value : 16
#define 	AT91C_DDRC2_TRFC_17                   (0x11UL)  // (HDDRSDRC2) Value : 17
#define 	AT91C_DDRC2_TRFC_18                   (0x12UL)  // (HDDRSDRC2) Value : 18
#define 	AT91C_DDRC2_TRFC_19                   (0x13UL)  // (HDDRSDRC2) Value : 19
#define 	AT91C_DDRC2_TRFC_20                   (0x14UL)  // (HDDRSDRC2) Value : 20
#define 	AT91C_DDRC2_TRFC_21                   (0x15UL)  // (HDDRSDRC2) Value : 21
#define 	AT91C_DDRC2_TRFC_22                   (0x16UL)  // (HDDRSDRC2) Value : 22
#define 	AT91C_DDRC2_TRFC_23                   (0x17UL)  // (HDDRSDRC2) Value : 23
#define 	AT91C_DDRC2_TRFC_24                   (0x18UL)  // (HDDRSDRC2) Value : 24
#define 	AT91C_DDRC2_TRFC_25                   (0x19UL)  // (HDDRSDRC2) Value : 25
#define 	AT91C_DDRC2_TRFC_26                   (0x1AUL)  // (HDDRSDRC2) Value : 26
#define 	AT91C_DDRC2_TRFC_27                   (0x1BUL)  // (HDDRSDRC2) Value : 27
#define 	AT91C_DDRC2_TRFC_28                   (0x1CUL)  // (HDDRSDRC2) Value : 28
#define 	AT91C_DDRC2_TRFC_29                   (0x1DUL)  // (HDDRSDRC2) Value : 29
#define 	AT91C_DDRC2_TRFC_30                   (0x1EUL)  // (HDDRSDRC2) Value : 30
#define 	AT91C_DDRC2_TRFC_31                   (0x1FUL)  // (HDDRSDRC2) Value : 31
#define AT91C_DDRC2_TXSNR         (0xFFUL <<  8)        // (HDDRSDRC2) Exit self refresh delay to Read command
#define 	AT91C_DDRC2_TXSNR_0                    (0x0UL <<  8)    // (HDDRSDRC2) Value :   0
#define 	AT91C_DDRC2_TXSNR_8                    (0x8UL <<  8)    // (HDDRSDRC2) Value :   8
#define 	AT91C_DDRC2_TXSNR_16                   (0x10UL <<  8)   // (HDDRSDRC2) Value :  16
#define 	AT91C_DDRC2_TXSNR_32                   (0x20UL <<  8)   // (HDDRSDRC2) Value :  32
#define 	AT91C_DDRC2_TXSNR_48                   (0x30UL <<  8)   // (HDDRSDRC2) Value :  48
#define 	AT91C_DDRC2_TXSNR_64                   (0x40UL <<  8)   // (HDDRSDRC2) Value :  64
#define 	AT91C_DDRC2_TXSNR_80                   (0x50UL <<  8)   // (HDDRSDRC2) Value :  80
#define 	AT91C_DDRC2_TXSNR_96                   (0x60UL <<  8)   // (HDDRSDRC2) Value :  96
#define 	AT91C_DDRC2_TXSNR_112                  (0x70UL <<  8)   // (HDDRSDRC2) Value : 112
#define 	AT91C_DDRC2_TXSNR_128                  (0x80UL <<  8)   // (HDDRSDRC2) Value : 128
#define 	AT91C_DDRC2_TXSNR_144                  (0x90UL <<  8)   // (HDDRSDRC2) Value : 144
#define 	AT91C_DDRC2_TXSNR_160                  (0xA0UL <<  8)   // (HDDRSDRC2) Value : 160
#define 	AT91C_DDRC2_TXSNR_176                  (0xB0UL <<  8)   // (HDDRSDRC2) Value : 176
#define 	AT91C_DDRC2_TXSNR_192                  (0xC0UL <<  8)   // (HDDRSDRC2) Value : 192
#define 	AT91C_DDRC2_TXSNR_208                  (0xD0UL <<  8)   // (HDDRSDRC2) Value : 208
#define 	AT91C_DDRC2_TXSNR_224                  (0xE0UL <<  8)   // (HDDRSDRC2) Value : 224
#define 	AT91C_DDRC2_TXSNR_240                  (0xF0UL <<  8)   // (HDDRSDRC2) Value : 240
#define 	AT91C_DDRC2_TXSNR_255                  (0xFFUL <<  8)   // (HDDRSDRC2) Value : 255
#define AT91C_DDRC2_TXSRD         (0xFFUL << 16)        // (HDDRSDRC2) Exit self refresh delay to Read command
#define 	AT91C_DDRC2_TXSRD_0                    (0x0UL << 16)    // (HDDRSDRC2) Value :   0
#define 	AT91C_DDRC2_TXSRD_8                    (0x8UL << 16)    // (HDDRSDRC2) Value :   8
#define 	AT91C_DDRC2_TXSRD_16                   (0x10UL << 16)   // (HDDRSDRC2) Value :  16
#define 	AT91C_DDRC2_TXSRD_32                   (0x20UL << 16)   // (HDDRSDRC2) Value :  32
#define 	AT91C_DDRC2_TXSRD_48                   (0x30UL << 16)   // (HDDRSDRC2) Value :  48
#define 	AT91C_DDRC2_TXSRD_64                   (0x40UL << 16)   // (HDDRSDRC2) Value :  64
#define 	AT91C_DDRC2_TXSRD_80                   (0x50UL << 16)   // (HDDRSDRC2) Value :  80
#define 	AT91C_DDRC2_TXSRD_96                   (0x60UL << 16)   // (HDDRSDRC2) Value :  96
#define 	AT91C_DDRC2_TXSRD_112                  (0x70UL << 16)   // (HDDRSDRC2) Value : 112
#define 	AT91C_DDRC2_TXSRD_128                  (0x80UL << 16)   // (HDDRSDRC2) Value : 128
#define 	AT91C_DDRC2_TXSRD_144                  (0x90UL << 16)   // (HDDRSDRC2) Value : 144
#define 	AT91C_DDRC2_TXSRD_160                  (0xA0UL << 16)   // (HDDRSDRC2) Value : 160
#define 	AT91C_DDRC2_TXSRD_176                  (0xB0UL << 16)   // (HDDRSDRC2) Value : 176
#define 	AT91C_DDRC2_TXSRD_192                  (0xC0UL << 16)   // (HDDRSDRC2) Value : 192
#define 	AT91C_DDRC2_TXSRD_208                  (0xD0UL << 16)   // (HDDRSDRC2) Value : 208
#define 	AT91C_DDRC2_TXSRD_224                  (0xE0UL << 16)   // (HDDRSDRC2) Value : 224
#define 	AT91C_DDRC2_TXSRD_240                  (0xF0UL << 16)   // (HDDRSDRC2) Value : 240
#define 	AT91C_DDRC2_TXSRD_255                  (0xFFUL << 16)   // (HDDRSDRC2) Value : 255
#define AT91C_DDRC2_TXP           (0xFUL << 24) // (HDDRSDRC2) Exit Power-down delay to first command
#define 	AT91C_DDRC2_TXP_0                    (0x0UL << 24)      // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TXP_1                    (0x1UL << 24)      // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TXP_2                    (0x2UL << 24)      // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TXP_3                    (0x3UL << 24)      // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TXP_4                    (0x4UL << 24)      // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TXP_5                    (0x5UL << 24)      // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TXP_6                    (0x6UL << 24)      // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TXP_7                    (0x7UL << 24)      // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TXP_8                    (0x8UL << 24)      // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TXP_9                    (0x9UL << 24)      // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TXP_10                   (0xAUL << 24)      // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TXP_11                   (0xBUL << 24)      // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TXP_12                   (0xCUL << 24)      // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TXP_13                   (0xDUL << 24)      // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TXP_14                   (0xEUL << 24)      // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TXP_15                   (0xFUL << 24)      // (HDDRSDRC2) Value : 15
// -------- HDDRSDRC2_T2PR : (HDDRSDRC2 Offset: 0x14) Timing2 Register -------- 
#define AT91C_DDRC2_TXARD         (0xFUL <<  0) // (HDDRSDRC2) Exit active power down delay to read command in 'Fast Exit' mode.
#define 	AT91C_DDRC2_TXARD_0                    (0x0UL)  // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TXARD_1                    (0x1UL)  // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TXARD_2                    (0x2UL)  // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TXARD_3                    (0x3UL)  // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TXARD_4                    (0x4UL)  // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TXARD_5                    (0x5UL)  // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TXARD_6                    (0x6UL)  // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TXARD_7                    (0x7UL)  // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TXARD_8                    (0x8UL)  // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TXARD_9                    (0x9UL)  // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TXARD_10                   (0xAUL)  // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TXARD_11                   (0xBUL)  // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TXARD_12                   (0xCUL)  // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TXARD_13                   (0xDUL)  // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TXARD_14                   (0xEUL)  // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TXARD_15                   (0xFUL)  // (HDDRSDRC2) Value : 15
#define AT91C_DDRC2_TXARDS        (0xFUL <<  4) // (HDDRSDRC2) Exit active power down delay to read command in 'Slow Exit' mode.
#define 	AT91C_DDRC2_TXARDS_0                    (0x0UL <<  4)   // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TXARDS_1                    (0x1UL <<  4)   // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TXARDS_2                    (0x2UL <<  4)   // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TXARDS_3                    (0x3UL <<  4)   // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TXARDS_4                    (0x4UL <<  4)   // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TXARDS_5                    (0x5UL <<  4)   // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TXARDS_6                    (0x6UL <<  4)   // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TXARDS_7                    (0x7UL <<  4)   // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TXARDS_8                    (0x8UL <<  4)   // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TXARDS_9                    (0x9UL <<  4)   // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TXARDS_10                   (0xAUL <<  4)   // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TXARDS_11                   (0xBUL <<  4)   // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TXARDS_12                   (0xCUL <<  4)   // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TXARDS_13                   (0xDUL <<  4)   // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TXARDS_14                   (0xEUL <<  4)   // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TXARDS_15                   (0xFUL <<  4)   // (HDDRSDRC2) Value : 15
#define AT91C_DDRC2_TRPA          (0xFUL << 8) // (HDDRSDRC2) Row precharge all delay
#define 	AT91C_DDRC2_TRPA_0                    (0x0UL << 8)     // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TRPA_1                    (0x1UL << 8)     // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TRPA_2                    (0x2UL << 8)     // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TRPA_3                    (0x3UL << 8)     // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TRPA_4                    (0x4UL << 8)     // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TRPA_5                    (0x5UL << 8)     // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TRPA_6                    (0x6UL << 8)     // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TRPA_7                    (0x7UL << 8)     // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TRPA_8                    (0x8UL << 8)     // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TRPA_9                    (0x9UL << 8)     // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TRPA_10                   (0xAUL << 8)     // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TRPA_11                   (0xBUL << 8)     // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TRPA_12                   (0xCUL << 8)     // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TRPA_13                   (0xDUL << 8)     // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TRPA_14                   (0xEUL << 8)     // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TRPA_15                   (0xFUL << 8)     // (HDDRSDRC2) Value : 15
#define AT91C_DDRC2_TRTP          (0xFUL << 12) // (HDDRSDRC2) Read to Precharge delay
#define 	AT91C_DDRC2_TRTP_0                    (0x0UL << 12)     // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TRTP_1                    (0x1UL << 12)     // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TRTP_2                    (0x2UL << 12)     // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TRTP_3                    (0x3UL << 12)     // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TRTP_4                    (0x4UL << 12)     // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TRTP_5                    (0x5UL << 12)     // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TRTP_6                    (0x6UL << 12)     // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TRTP_7                    (0x7UL << 12)     // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TRTP_8                    (0x8UL << 12)     // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TRTP_9                    (0x9UL << 12)     // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TRTP_10                   (0xAUL << 12)     // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TRTP_11                   (0xBUL << 12)     // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TRTP_12                   (0xCUL << 12)     // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TRTP_13                   (0xDUL << 12)     // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TRTP_14                   (0xEUL << 12)     // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TRTP_15                   (0xFUL << 12)     // (HDDRSDRC2) Value : 15
#define AT91C_DDRC2_TFAW          (0xFUL << 16) // (HDDRSDRC2) Four Active window
#define 	AT91C_DDRC2_TFAW_0                    (0x0UL << 12)     // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TFAW_1                    (0x1UL << 12)     // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TFAW_2                    (0x2UL << 12)     // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TFAW_3                    (0x3UL << 12)     // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TFAW_4                    (0x4UL << 12)     // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TFAW_5                    (0x5UL << 12)     // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TFAW_6                    (0x6UL << 12)     // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TFAW_7                    (0x7UL << 12)     // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TFAW_8                    (0x8UL << 12)     // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TFAW_9                    (0x9UL << 12)     // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TFAW_10                   (0xAUL << 12)     // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TFAW_11                   (0xBUL << 12)     // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TFAW_12                   (0xCUL << 12)     // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TFAW_13                   (0xDUL << 12)     // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TFAW_14                   (0xEUL << 12)     // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TFAW_15                   (0xFUL << 12)     // (HDDRSDRC2) Value : 15
// -------- HDDRSDRC2_T3PR : (HDDRSDRC2 Offset: 0x18) Timing3 Register -------- 
#define AT91C_DDRC2_TANPD         (0xFUL <<  0) // (HDDRSDRC2) ODT to power down entry
#define 	AT91C_DDRC2_TANPD_0                    (0x0UL)  // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TANPD_1                    (0x1UL)  // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TANPD_2                    (0x2UL)  // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TANPD_3                    (0x3UL)  // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TANPD_4                    (0x4UL)  // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TANPD_5                    (0x5UL)  // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TANPD_6                    (0x6UL)  // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TANPD_7                    (0x7UL)  // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TANPD_8                    (0x8UL)  // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TANPD_9                    (0x9UL)  // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TANPD_10                   (0xAUL)  // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TANPD_11                   (0xBUL)  // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TANPD_12                   (0xCUL)  // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TANPD_13                   (0xDUL)  // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TANPD_14                   (0xEUL)  // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TANPD_15                   (0xFUL)  // (HDDRSDRC2) Value : 15
#define AT91C_DDRC2_TAXPD         (0xFUL <<  4) // (HDDRSDRC2) ODT power down exit
#define 	AT91C_DDRC2_TAXPD_0                    (0x0UL <<  4)    // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TAXPD_1                    (0x1UL <<  4)    // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TAXPD_2                    (0x2UL <<  4)    // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TAXPD_3                    (0x3UL <<  4)    // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TAXPD_4                    (0x4UL <<  4)    // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TAXPD_5                    (0x5UL <<  4)    // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TAXPD_6                    (0x6UL <<  4)    // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TAXPD_7                    (0x7UL <<  4)    // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TAXPD_8                    (0x8UL <<  4)    // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TAXPD_9                    (0x9UL <<  4)    // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TAXPD_10                   (0xAUL <<  4)    // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TAXPD_11                   (0xBUL <<  4)    // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TAXPD_12                   (0xCUL <<  4)    // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TAXPD_13                   (0xDUL <<  4)    // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TAXPD_14                   (0xEUL <<  4)    // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TAXPD_15                   (0xFUL <<  4)    // (HDDRSDRC2) Value : 15
#define AT91C_DDRC2_TAOFPD        (0xFUL <<  8) // (HDDRSDRC2) ODT turn off in power down mode
#define 	AT91C_DDRC2_TAOFPD_0                    (0x0UL <<  8)   // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TAOFPD_1                    (0x1UL <<  8)   // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TAOFPD_2                    (0x2UL <<  8)   // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TAOFPD_3                    (0x3UL <<  8)   // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TAOFPD_4                    (0x4UL <<  8)   // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TAOFPD_5                    (0x5UL <<  8)   // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TAOFPD_6                    (0x6UL <<  8)   // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TAOFPD_7                    (0x7UL <<  8)   // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TAOFPD_8                    (0x8UL <<  8)   // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TAOFPD_9                    (0x9UL <<  8)   // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TAOFPD_10                   (0xAUL <<  8)   // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TAOFPD_11                   (0xBUL <<  8)   // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TAOFPD_12                   (0xCUL <<  8)   // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TAOFPD_13                   (0xDUL <<  8)   // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TAOFPD_14                   (0xEUL <<  8)   // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TAOFPD_15                   (0xFUL <<  8)   // (HDDRSDRC2) Value : 15
#define AT91C_DDRC2_TAOFD         (0xFUL << 12) // (HDDRSDRC2) ODT turn off delay
#define 	AT91C_DDRC2_TAOFD_0                    (0x0UL << 12)    // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TAOFD_1                    (0x1UL << 12)    // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TAOFD_2                    (0x2UL << 12)    // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TAOFD_3                    (0x3UL << 12)    // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TAOFD_4                    (0x4UL << 12)    // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TAOFD_5                    (0x5UL << 12)    // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TAOFD_6                    (0x6UL << 12)    // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TAOFD_7                    (0x7UL << 12)    // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TAOFD_8                    (0x8UL << 12)    // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TAOFD_9                    (0x9UL << 12)    // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TAOFD_10                   (0xAUL << 12)    // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TAOFD_11                   (0xBUL << 12)    // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TAOFD_12                   (0xCUL << 12)    // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TAOFD_13                   (0xDUL << 12)    // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TAOFD_14                   (0xEUL << 12)    // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TAOFD_15                   (0xFUL << 12)    // (HDDRSDRC2) Value : 15
#define AT91C_DDRC2_TAONPD        (0xFUL << 16) // (HDDRSDRC2) ODT turn on in power down mode
#define 	AT91C_DDRC2_TAONPD_0                    (0x0UL << 16)   // (HDDRSDRC2) Value :  0
#define 	AT91C_DDRC2_TAONPD_1                    (0x1UL << 16)   // (HDDRSDRC2) Value :  1
#define 	AT91C_DDRC2_TAONPD_2                    (0x2UL << 16)   // (HDDRSDRC2) Value :  2
#define 	AT91C_DDRC2_TAONPD_3                    (0x3UL << 16)   // (HDDRSDRC2) Value :  3
#define 	AT91C_DDRC2_TAONPD_4                    (0x4UL << 16)   // (HDDRSDRC2) Value :  4
#define 	AT91C_DDRC2_TAONPD_5                    (0x5UL << 16)   // (HDDRSDRC2) Value :  5
#define 	AT91C_DDRC2_TAONPD_6                    (0x6UL << 16)   // (HDDRSDRC2) Value :  6
#define 	AT91C_DDRC2_TAONPD_7                    (0x7UL << 16)   // (HDDRSDRC2) Value :  7
#define 	AT91C_DDRC2_TAONPD_8                    (0x8UL << 16)   // (HDDRSDRC2) Value :  8
#define 	AT91C_DDRC2_TAONPD_9                    (0x9UL << 16)   // (HDDRSDRC2) Value :  9
#define 	AT91C_DDRC2_TAONPD_10                   (0xAUL << 16)   // (HDDRSDRC2) Value : 10
#define 	AT91C_DDRC2_TAONPD_11                   (0xBUL << 16)   // (HDDRSDRC2) Value : 11
#define 	AT91C_DDRC2_TAONPD_12                   (0xCUL << 16)   // (HDDRSDRC2) Value : 12
#define 	AT91C_DDRC2_TAONPD_13                   (0xDUL << 16)   // (HDDRSDRC2) Value : 13
#define 	AT91C_DDRC2_TAONPD_14                   (0xEUL << 16)   // (HDDRSDRC2) Value : 14
#define 	AT91C_DDRC2_TAONPD_15                   (0xFUL << 16)   // (HDDRSDRC2) Value : 15
// -------- HDDRSDRC2_LPR : (HDDRSDRC2 Offset: 0x1c)  -------- 
#define AT91C_DDRC2_LPCB          (0x3UL <<  0) // (HDDRSDRC2) Low-power Command Bit
#define 	AT91C_DDRC2_LPCB_DISABLED             (0x0UL)   // (HDDRSDRC2) Low-power Feature is inhibited: no power-down, self refresh and Deep power mode are issued to the SDRAM device.
#define 	AT91C_DDRC2_LPCB_SELFREFRESH          (0x1UL)   // (HDDRSDRC2) The DDRSDRAMC Controller issues a Self Refresh Command to the SDRAM device, the clock(s) is/are de-activated and the CKE signal is set low. The SDRAM device leaves the self refresh mode when accessed and enters it after the access.
#define 	AT91C_DDRC2_LPCB_POWERDOWN            (0x2UL)   // (HDDRSDRC2) The HDDRSDRC2 Controller issues a Power-down Command to the SDRAM device after each access, the CKE signal is set low. The SDRAM device leaves the power-down mode when accessed and enters it after the access.
#define 	AT91C_DDRC2_LPCB_DEEP_PWD             (0x3UL)   // (HDDRSDRC2) The HDDRSDRC2 Controller issues a Deep Power-down Command to the Mobile SDRAM device. This mode is unique to Mobile SDRAM devices
#define AT91C_DDRC2_CLK_FR        (0x1UL <<  2) // (HDDRSDRC2) Clock frozen Command Bit
#define 	AT91C_DDRC2_CLK_FR_DISABLED             (0x0UL <<  2)   // (HDDRSDRC2) Low-power Feature is inhibited: no power-down, self refresh and Deep power mode are issued to the SDRAM device.
#define 	AT91C_DDRC2_CLK_FR_SELFREFRESH          (0x1UL <<  2)   // (HDDRSDRC2) The DDRSDRAMC Controller issues a Self Refresh Command to the SDRAM device, the clock(s) is/are de-activated and the CKE signal is set low. The SDRAM device leaves the self refresh mode when accessed and enters it after the access.
#define 	AT91C_DDRC2_CLK_FR_POWERDOWN            (0x2UL <<  2)   // (HDDRSDRC2) The HDDRSDRC2 Controller issues a Power-down Command to the SDRAM device after each access, the CKE signal is set low. The SDRAM device leaves the power-down mode when accessed and enters it after the access.
#define 	AT91C_DDRC2_CLK_FR_DEEP_PWD             (0x3UL <<  2)   // (HDDRSDRC2) The HDDRSDRC2 Controller issues a Deep Power-down Command to the Mobile SDRAM device. This mode is unique to Mobile SDRAM devices
#define AT91C_DDRC2_PASR          (0x7UL <<  4) // (HDDRSDRC2) Partial Array Self Refresh
#define AT91C_                    (0x0UL <<  8) // (HDDRSDRC2)
#define AT91C_DDRC2_DS            (0x3UL << 10) // (HDDRSDRC2) Drive strength
#define AT91C_DDRC2_TIMEOUT       (0x3UL << 12) // (HDDRSDRC2) low-power mode delay
#define 	AT91C_DDRC2_TIMEOUT_0                    (0x0UL << 12)  // (HDDRSDRC2) The SDRAM controller activates the SDRAM low-power mode immediately after the end of the last transfer.
#define 	AT91C_DDRC2_TIMEOUT_64                   (0x1UL << 12)  // (HDDRSDRC2) The SDRAM controller activates the SDRAM low-power mode 64 clock cycles after the end of the last transfer.
#define 	AT91C_DDRC2_TIMEOUT_128                  (0x2UL << 12)  // (HDDRSDRC2) The SDRAM controller activates the SDRAM low-power mode 128 clock cycles after the end of the last transfer.
#define 	AT91C_DDRC2_TIMEOUT_Reserved             (0x3UL << 12)  // (HDDRSDRC2) Reserved
#define AT91C_DDRC2_ADPE          (0x1UL << 16) // (HDDRSDRC2) Active Power Down Exit time
#define 	AT91C_DDRC2_ADPE_FAST                 (0x0UL << 16)     // (HDDRSDRC2) Fast Exit
#define 	AT91C_DDRC2_ADPE_SLOW                 (0x1UL << 16)     // (HDDRSDRC2) Slow Exit
// -------- HDDRSDRC2_MDR : (HDDRSDRC2 Offset: 0x20) Memory Device Register -------- 
#define AT91C_DDRC2_MD            (0x7UL <<  0) // (HDDRSDRC2) memory device
#define 	AT91C_DDRC2_MD_SDR_SDRAM            (0x0UL)     // (HDDRSDRC2) SDR SDRAM
#define 	AT91C_DDRC2_MD_LP_SDR_SDRAM         (0x1UL)     // (HDDRSDRC2) Low Power SDR SDRAM
#define 	AT91C_DDRC2_MD_DDR_SDRAM            (0x2UL)     // (HDDRSDRC2) DDR SDRAM
#define 	AT91C_DDRC2_MD_LP_DDR_SDRAM         (0x3UL)     // (HDDRSDRC2) Low Power DDR SDRAM
#define 	AT91C_DDRC2_MD_DDR2_SDRAM           (0x6UL)     // (HDDRSDRC2) DDR2 SDRAM
#define AT91C_DDRC2_DBW           (0x1UL <<  4) // (HDDRSDRC2) Data Bus Width
#define 	AT91C_DDRC2_DBW_32_BITS              (0x0UL <<  4)      // (HDDRSDRC2) 32 Bits datas bus
#define 	AT91C_DDRC2_DBW_16_BITS              (0x1UL <<  4)      // (HDDRSDRC2) 16 Bits datas bus
// -------- HDDRSDRC2_DLL : (HDDRSDRC2 Offset: 0x24) DLL Information Register -------- 
#define AT91C_DDRC2_MDINC         (0x1UL <<  0) // (HDDRSDRC2) DLL Master Delay Increment
#define AT91C_DDRC2_MDDEC         (0x1UL <<  1) // (HDDRSDRC2) DLL Master Delay Decrement
#define AT91C_DDRC2_MDOVF         (0x1UL <<  2) // (HDDRSDRC2) DLL Master Delay Overflow Flag
#define AT91C_DDRC2_SDCOVF        (0x1UL <<  3) // (HDDRSDRC2) DLL Slave Delay Correction Overflow Flag
#define AT91C_DDRC2_SDCUDF        (0x1UL <<  4) // (HDDRSDRC2) DLL Slave Delay Correction Underflow Flag
#define AT91C_DDRC2_SDERF         (0x1UL <<  5) // (HDDRSDRC2) DLL Slave Delay Correction Error Flag
#define AT91C_DDRC2_MDVAL         (0xFFUL <<  8)        // (HDDRSDRC2) DLL Master Delay Value
#define AT91C_DDRC2_SDVAL         (0xFFUL << 16)        // (HDDRSDRC2) DLL Slave Delay Value
#define AT91C_DDRC2_SDCVAL        (0xFFUL << 24)        // (HDDRSDRC2) DLL Slave Delay Correction Value
// -------- HDDRSDRC2_HS : (HDDRSDRC2 Offset: 0x2c) High Speed Register -------- 
#define AT91C_DDRC2_DA            (0x1UL <<  0) // (HDDRSDRC2) Decode cycle
#define AT91C_DDRC2_NO_OPT        (0x1UL <<  1) // (HDDRSDRC2) Disable optimization
#define AT91C_DDRC2_NO_ANT        (0x1UL <<  2) // (HDDRSDRC2) Disable Anticipated read
#define AT91C_DDRC2_RES_DQS       (0x1UL <<  3) // (HDDRSDRC2) Reset DQS Active
// -------- HDDRSDRC2_ADJ_REF : (HDDRSDRC2 Offset: 0x30) Adjust Refresh Register -------- 
#define AT91C_COUNT_ADJ           (0xFFFFUL <<  0)      // (HDDRSDRC2) ADJust REFresh timer counter
#define AT91C_ADJ_REF             (0x1UL << 16) // (HDDRSDRC2) ADJust REFresh
#define AT91C_SRR_VALUE           (0xFUL << 20) // (HDDRSDRC2) Content of Status Read Register
// -------- HDDRSDRC2_DELAY1 : (HDDRSDRC2 Offset: 0x34) Pad delay1 Register -------- 
#define AT91C_DDRC2_DELAY         (0xFUL <<  0) // (HDDRSDRC2) Pad delay value
// -------- HDDRSDRC2_DELAY2 : (HDDRSDRC2 Offset: 0x38) Pad delay2 Register -------- 
// -------- HDDRSDRC2_DELAY3 : (HDDRSDRC2 Offset: 0x3c) Pad delay3 Register -------- 
// -------- HDDRSDRC2_DELAY4 : (HDDRSDRC2 Offset: 0x40) Pad delay4 Register -------- 
// -------- HDDRSDRC2_DELAY5 : (HDDRSDRC2 Offset: 0x44) Pad delay5 Register -------- 
// -------- HDDRSDRC2_DELAY6 : (HDDRSDRC2 Offset: 0x48) Pad delay6 Register -------- 
// -------- HDDRSDRC2_DELAY7 : (HDDRSDRC2 Offset: 0x4c) Pad delay7 Register -------- 
// -------- HDDRSDRC2_DELAY8 : (HDDRSDRC2 Offset: 0x50) Pad delay8 Register -------- 
// -------- HDDRSDRC2_DRIVESTRENGTH : (HDDRSDRC2 Offset: 0x54) Drive Strength I/O Register -------- 
#define AT91C_DDRC2_DSC           (0x1UL <<  0) // (HDDRSDRC2) Drive Strength Configuration
// -------- HDDRSDRC2_WPCR : (HDDRSDRC2 Offset: 0xe4) Write Protect Control Register -------- 
#define AT91C_DDRC2_WPEN          (0x1UL <<  0) // (HDDRSDRC2) write protect enable
#define AT91C_DDRC2_WPKEY         (0xFFFFFFUL <<  8)    // (HDDRSDRC2) write protect key
// -------- HDDRSDRC2_WPSR : (HDDRSDRC2 Offset: 0xe8) Write Protect Status Register -------- 
#define AT91C_DDRC2_WPVS          (0x1UL <<  0) // (HDDRSDRC2) write protect violation status
#define AT91C_DDRC2_WPSRC         (0xFFFFUL <<  8)      // (HDDRSDRC2) write protect source address

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Static Memory Controller Interface
// *****************************************************************************
// *** Register offset in AT91S_SMC structure ***
#define SMC_SETUP0      ( 0)    //  Setup Register for CS 0
#define SMC_PULSE0      ( 4)    //  Pulse Register for CS 0
#define SMC_CYCLE0      ( 8)    //  Cycle Register for CS 0
#define SMC_CTRL0       (12)    //  Control Register for CS 0
#define SMC_SETUP1      (16)    //  Setup Register for CS 1
#define SMC_PULSE1      (20)    //  Pulse Register for CS 1
#define SMC_CYCLE1      (24)    //  Cycle Register for CS 1
#define SMC_CTRL1       (28)    //  Control Register for CS 1
#define SMC_SETUP2      (32)    //  Setup Register for CS 2
#define SMC_PULSE2      (36)    //  Pulse Register for CS 2
#define SMC_CYCLE2      (40)    //  Cycle Register for CS 2
#define SMC_CTRL2       (44)    //  Control Register for CS 2
#define SMC_SETUP3      (48)    //  Setup Register for CS 3
#define SMC_PULSE3      (52)    //  Pulse Register for CS 3
#define SMC_CYCLE3      (56)    //  Cycle Register for CS 3
#define SMC_CTRL3       (60)    //  Control Register for CS 3
#define SMC_SETUP4      (64)    //  Setup Register for CS 4
#define SMC_PULSE4      (68)    //  Pulse Register for CS 4
#define SMC_CYCLE4      (72)    //  Cycle Register for CS 4
#define SMC_CTRL4       (76)    //  Control Register for CS 4
#define SMC_SETUP5      (80)    //  Setup Register for CS 5
#define SMC_PULSE5      (84)    //  Pulse Register for CS 5
#define SMC_CYCLE5      (88)    //  Cycle Register for CS 5
#define SMC_CTRL5       (92)    //  Control Register for CS 5
#define SMC_SETUP6      (96)    //  Setup Register for CS 6
#define SMC_PULSE6      (100)   //  Pulse Register for CS 6
#define SMC_CYCLE6      (104)   //  Cycle Register for CS 6
#define SMC_CTRL6       (108)   //  Control Register for CS 6
#define SMC_SETUP7      (112)   //  Setup Register for CS 7
#define SMC_PULSE7      (116)   //  Pulse Register for CS 7
#define SMC_CYCLE7      (120)   //  Cycle Register for CS 7
#define SMC_CTRL7       (124)   //  Control Register for CS 7
#define SMC_DELAY1      (192)   // SMC Delay Control Register
#define SMC_DELAY2      (196)   // SMC Delay Control Register
#define SMC_DELAY3      (200)   // SMC Delay Control Register
#define SMC_DELAY4      (204)   // SMC Delay Control Register
#define SMC_DELAY5      (208)   // SMC Delay Control Register
#define SMC_DELAY6      (212)   // SMC Delay Control Register
#define SMC_DELAY7      (216)   // SMC Delay Control Register
#define SMC_DELAY8      (220)   // SMC Delay Control Register
// -------- SMC_SETUP : (SMC Offset: 0x0) Setup Register for CS x -------- 
#define AT91C_SMC_NWESETUP        (0x3FUL <<  0)        // (SMC) NWE Setup Length
#define AT91C_SMC_NCSSETUPWR      (0x3FUL <<  8)        // (SMC) NCS Setup Length in WRite Access
#define AT91C_SMC_NRDSETUP        (0x3FUL << 16)        // (SMC) NRD Setup Length
#define AT91C_SMC_NCSSETUPRD      (0x3FUL << 24)        // (SMC) NCS Setup Length in ReaD Access
// -------- SMC_PULSE : (SMC Offset: 0x4) Pulse Register for CS x -------- 
#define AT91C_SMC_NWEPULSE        (0x7FUL <<  0)        // (SMC) NWE Pulse Length
#define AT91C_SMC_NCSPULSEWR      (0x7FUL <<  8)        // (SMC) NCS Pulse Length in WRite Access
#define AT91C_SMC_NRDPULSE        (0x7FUL << 16)        // (SMC) NRD Pulse Length
#define AT91C_SMC_NCSPULSERD      (0x7FUL << 24)        // (SMC) NCS Pulse Length in ReaD Access
// -------- SMC_CYC : (SMC Offset: 0x8) Cycle Register for CS x -------- 
#define AT91C_SMC_NWECYCLE        (0x1FFUL <<  0)       // (SMC) Total Write Cycle Length
#define AT91C_SMC_NRDCYCLE        (0x1FFUL << 16)       // (SMC) Total Read Cycle Length
// -------- SMC_CTRL : (SMC Offset: 0xc) Control Register for CS x -------- 
#define AT91C_SMC_READMODE        (0x1UL <<  0) // (SMC) Read Mode
#define AT91C_SMC_WRITEMODE       (0x1UL <<  1) // (SMC) Write Mode
#define AT91C_SMC_NWAITM          (0x3UL <<  4) // (SMC) NWAIT Mode
#define 	AT91C_SMC_NWAITM_NWAIT_DISABLE        (0x0UL <<  4)     // (SMC) External NWAIT disabled.
#define 	AT91C_SMC_NWAITM_NWAIT_ENABLE_FROZEN  (0x2UL <<  4)     // (SMC) External NWAIT enabled in frozen mode.
#define 	AT91C_SMC_NWAITM_NWAIT_ENABLE_READY   (0x3UL <<  4)     // (SMC) External NWAIT enabled in ready mode.
#define AT91C_SMC_BAT             (0x1UL <<  8) // (SMC) Byte Access Type
#define 	AT91C_SMC_BAT_BYTE_SELECT          (0x0UL <<  8)        // (SMC) Write controled by ncs, nbs0, nbs1, nbs2, nbs3. Read controled by ncs, nrd, nbs0, nbs1, nbs2, nbs3.
#define 	AT91C_SMC_BAT_BYTE_WRITE           (0x1UL <<  8)        // (SMC) Write controled by ncs, nwe0, nwe1, nwe2, nwe3. Read controled by ncs and nrd.
#define AT91C_SMC_DBW             (0x3UL << 12) // (SMC) Data Bus Width
#define 	AT91C_SMC_DBW_WIDTH_EIGTH_BITS     (0x0UL << 12)        // (SMC) 8 bits.
#define 	AT91C_SMC_DBW_WIDTH_SIXTEEN_BITS   (0x1UL << 12)        // (SMC) 16 bits.
#define 	AT91C_SMC_DBW_WIDTH_THIRTY_TWO_BITS (0x2UL << 12)       // (SMC) 32 bits.
#define AT91C_SMC_TDF             (0xFUL << 16) // (SMC) Data Float Time.
#define AT91C_SMC_TDFEN           (0x1UL << 20) // (SMC) TDF Enabled.
#define AT91C_SMC_PMEN            (0x1UL << 24) // (SMC) Page Mode Enabled.
#define AT91C_SMC_PS              (0x3UL << 28) // (SMC) Page Size
#define 	AT91C_SMC_PS_SIZE_FOUR_BYTES      (0x0UL << 28) // (SMC) 4 bytes.
#define 	AT91C_SMC_PS_SIZE_EIGHT_BYTES     (0x1UL << 28) // (SMC) 8 bytes.
#define 	AT91C_SMC_PS_SIZE_SIXTEEN_BYTES   (0x2UL << 28) // (SMC) 16 bytes.
#define 	AT91C_SMC_PS_SIZE_THIRTY_TWO_BYTES (0x3UL << 28)        // (SMC) 32 bytes.
// -------- SMC_SETUP : (SMC Offset: 0x10) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x14) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x18) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x1c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x20) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x24) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x28) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x2c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x30) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x34) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x38) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x3c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x40) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x44) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x48) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x4c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x50) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x54) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x58) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x5c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x60) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x64) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x68) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x6c) Control Register for CS x -------- 
// -------- SMC_SETUP : (SMC Offset: 0x70) Setup Register for CS x -------- 
// -------- SMC_PULSE : (SMC Offset: 0x74) Pulse Register for CS x -------- 
// -------- SMC_CYC : (SMC Offset: 0x78) Cycle Register for CS x -------- 
// -------- SMC_CTRL : (SMC Offset: 0x7c) Control Register for CS x -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR AHB Matrix2 Interface
// *****************************************************************************
// *** Register offset in AT91S_MATRIX structure ***
#define MATRIX_MCFG0    ( 0)    //  Master Configuration Register 0  : ARM-I
#define MATRIX_MCFG1    ( 4)    //  Master Configuration Register 1  ; ARM-D
#define MATRIX_MCFG2    ( 8)    //  Master Configuration Register 2  : DMA0 Master Port 0
#define MATRIX_MCFG3    (12)    //  Master Configuration Register 3  : DMA0 Master Port 1
#define MATRIX_MCFG4    (16)    //  Master Configuration Register 4  : DMA1 Master Port 0
#define MATRIX_MCFG5    (20)    //  Master Configuration Register 5  : DMA1 Master Port 1
#define MATRIX_MCFG6    (24)    //  Master Configuration Register 6  : USB Device
#define MATRIX_MCFG7    (28)    //  Master Configuration Register 7  : USB Host EHCI
#define MATRIX_MCFG8    (32)    //  Master Configuration Register 8  : USB Host OHCI
#define MATRIX_MCFG9    (36)    //  Master Configuration Register 9  : hisi/lcdc
#define MATRIX_MCFG10   (40)    //  Master Configuration Register 10 : eMAC0
#define MATRIX_MCFG11   (44)    //  Master Configuration Register 11 : eMAC1
#define MATRIX_SCFG0    (64)    //  Slave Configuration Register 0  : SRAM
#define MATRIX_SCFG1    (68)    //  Slave Configuration Register 1  : ROM
#define MATRIX_SCFG2    (72)    //  Slave Configuration Register 2  : SMD
#define MATRIX_SCFG3    (76)    //  Slave Configuration Register 3  : USB Slaves
#define MATRIX_SCFG4    (80)    //  Slave Configuration Register 4  ; EBI
#define MATRIX_SCFG5    (84)    //  Slave Configuration Register 5  : DDR2 S1
#define MATRIX_SCFG6    (88)    //  Slave Configuration Register 6  : DDR2 S2
#define MATRIX_SCFG7    (92)    //  Slave Configuration Register 7  : DDR2 S3
#define MATRIX_SCFG8    (96)    //  Slave Configuration Register 8  : Peripheral Bridge 0
#define MATRIX_SCFG9    (100)   //  Slave Configuration Register 9  : Peripheral Bridge 1
#define MATRIX_PRAS0    (128)   //  PRAS0  : SRAM
#define MATRIX_PRBS0    (132)   //  PRBS0  : SRAM
#define MATRIX_PRAS1    (136)   //  PRAS1  : ROM
#define MATRIX_PRBS1    (140)   //  PRBS1  : ROM
#define MATRIX_PRAS2    (144)   //  PRAS2  : SMD
#define MATRIX_PRBS2    (148)   //  PRBS2  : SMD
#define MATRIX_PRAS3    (152)   //  PRAS3  : USB Slaves
#define MATRIX_PRBS3    (156)   //  PRBS3  : USB Slaves
#define MATRIX_PRAS4    (160)   //  PRAS4  : EBI
#define MATRIX_PRBS4    (164)   //  PRBS4  : EBI
#define MATRIX_PRAS5    (168)   //  PRAS5  : DDR2 S1
#define MATRIX_PRBS5    (172)   //  PRBS5  : DDR2 S1
#define MATRIX_PRAS6    (176)   //  PRAS6  : DDR2 S2
#define MATRIX_PRBS6    (180)   //  PRBS6  : DDR2 S2
#define MATRIX_PRAS7    (184)   //  PRAS7  : DDR2 S3
#define MATRIX_PRBS7    (188)   //  PRBS7  : DDR2 S3
#define MATRIX_PRAS8    (192)   //  PRAS8  : Peripheral Bridge 0
#define MATRIX_PRBS8    (196)   //  PRBS8  : Peripheral Bridge 0
#define MATRIX_PRAS9    (200)   //  PRAS9  : Peripheral Bridge 1
#define MATRIX_PRBS9    (204)   //  PRBS9  : Peripheral Bridge 1
#define MATRIX_MRCR     (256)   //  Master Remap Control Register
#define MATRIX_SFR0     (272)   //  Special Function Register 0
#define MATRIX_SFR1     (276)   //  Special Function Register 1
#define MATRIX_SFR2     (280)   //  Special Function Register 2
#define MATRIX_SFR3     (284)   //  Special Function Register 3
#define MATRIX_SFR4     (288)   //  Special Function Register 4
#define MATRIX_SFR5     (292)   //  Special Function Register 5
#define MATRIX_SFR6     (296)   //  Special Function Register 6
#define MATRIX_SFR7     (300)   //  Special Function Register 7
#define MATRIX_SFR8     (304)   //  Special Function Register 8
#define MATRIX_SFR9     (308)   //  Special Function Register 9
#define MATRIX_SFR10    (312)   //  Special Function Register 10
#define MATRIX_SFR11    (316)   //  Special Function Register 11
#define MATRIX_SFR12    (320)   //  Special Function Register 12
#define MATRIX_SFR13    (324)   //  Special Function Register 13
#define MATRIX_SFR14    (328)   //  Special Function Register 14
#define MATRIX_SFR15    (332)   //  Special Function Register 15
#define MATRIX_WRPROTEN (484)   //  Write Protection Control Register
#define MATRIX_WRPROTST (488)   //  Write Protection Status Register
#define MATRIX_ADDRSIZE (492)   // HMATRIX2 ADDRSIZE REGISTER
#define MATRIX_IPNAME1  (496)   // HMATRIX2 IPNAME1 REGISTER
#define MATRIX_IPNAME2  (500)   // HMATRIX2 IPNAME2 REGISTER
#define MATRIX_FEATURES (504)   // HMATRIX2 FEATURES REGISTER
#define MATRIX_VER      (508)   // HMATRIX2 VERSION REGISTER
// -------- MATRIX_MCFG0 : (MATRIX Offset: 0x0) Master Configuration Register ARM-I -------- 
#define AT91C_MATRIX_ULBT         (0x7UL <<  0) // (MATRIX) Undefined Length Burst Type
// -------- MATRIX_MCFG1 : (MATRIX Offset: 0x4) Master Configuration Register ARM-D -------- 
// -------- MATRIX_MCFG2 : (MATRIX Offset: 0x8) Master Configuration Register DMA0 Master Port 0 -------- 
// -------- MATRIX_MCFG3 : (MATRIX Offset: 0xc) Master Configuration Register DMA0 Master Port 1 -------- 
// -------- MATRIX_MCFG4 : (MATRIX Offset: 0x10) Master Configuration Register DMA1 Master Port 0 -------- 
// -------- MATRIX_MCFG5 : (MATRIX Offset: 0x14) Master Configuration Register DMA1 Master Port 1 -------- 
// -------- MATRIX_MCFG6 : (MATRIX Offset: 0x18) Master Configuration Register USB Device -------- 
// -------- MATRIX_MCFG7 : (MATRIX Offset: 0x1c) Master Configuration Register USB Host EHCI -------- 
// -------- MATRIX_MCFG8 : (MATRIX Offset: 0x20) Master Configuration Register USB Host OHCI -------- 
// -------- MATRIX_MCFG9 : (MATRIX Offset: 0x24) Master Configuration Register HISI/LCD -------- 
// -------- MATRIX_MCFG10 : (MATRIX Offset: 0x28) Master Configuration Register EMAC0 -------- 
// -------- MATRIX_MCFG11 : (MATRIX Offset: 0x2c) Master Configuration Register EMAC1 -------- 
// -------- MATRIX_SCFG0 : (MATRIX Offset: 0x40) Slave Configuration Register 0 (Internal SRAM) -------- 
#define AT91C_MATRIX_SLOT_CYCLE   (0xFFUL <<  0)        // (MATRIX) Maximum Number of Allowed Cycles for a Burst
#define AT91C_MATRIX_DEFMSTR_TYPE (0x3UL << 16) // (MATRIX) Default Master Type
#define 	AT91C_MATRIX_DEFMSTR_TYPE_NO_DEFMSTR           (0x0UL << 16)    // (MATRIX) No Default Master. At the end of current slave access, if no other master request is pending, the slave is deconnected from all masters. This results in having a one cycle latency for the first transfer of a burst.
#define 	AT91C_MATRIX_DEFMSTR_TYPE_LAST_DEFMSTR         (0x1UL << 16)    // (MATRIX) Last Default Master. At the end of current slave access, if no other master request is pending, the slave stay connected with the last master having accessed it. This results in not having the one cycle latency when the last master re-trying access on the slave.
#define 	AT91C_MATRIX_DEFMSTR_TYPE_FIXED_DEFMSTR        (0x2UL << 16)    // (MATRIX) Fixed Default Master. At the end of current slave access, if no other master request is pending, the slave connects with fixed which number is in FIXED_DEFMSTR field. This results in not having the one cycle latency when the fixed master re-trying access on the slave.
#define AT91C_MATRIX_FIXED_DEFMSTR0 (0xFUL << 18)       // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_ARM926I              (0x0UL << 18)  // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_ARM926D              (0x1UL << 18)  // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_DMA0_PORT0           (0x2UL << 18)  // (MATRIX) DMA0 Port 0 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_DMA0_PORT1           (0x3UL << 18)  // (MATRIX) DMA0 Port 1 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_DMA1_PORT0           (0x4UL << 18)  // (MATRIX) DMA1 Port 0 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_DMA1_PORT1           (0x5UL << 18)  // (MATRIX) DMA1 Port 1 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_UDPHS                (0x6UL << 18)  // (MATRIX) USB Device Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_UHPHS_EHCI           (0x7UL << 18)  // (MATRIX) USB Host EHCI Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_UHPHS_OHCI           (0x8UL << 18)  // (MATRIX) USB Host OHCI Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_ISI                  (0x9UL << 18)  // (MATRIX) ISI/LCD Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_EMAC0                (0xAUL << 18)  // (MATRIX) EMAC0 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR0_EMAC1                (0xBUL << 18)  // (MATRIX) EMAC1 Master is Default Master
#define AT91C_MATRIX_ARBT         (0x3UL << 24) // (MATRIX) Arbitration Type
// -------- MATRIX_SCFG1 : (MATRIX Offset: 0x44) Slave Configuration Register 1 (ROM) -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR1 (0xFUL << 18)       // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_ARM926I              (0x0UL << 18)  // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_ARM926D              (0x1UL << 18)  // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_DMA0_PORT0           (0x2UL << 18)  // (MATRIX) DMA0 Port 0 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_DMA0_PORT1           (0x3UL << 18)  // (MATRIX) DMA0 Port 1 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_DMA1_PORT0           (0x4UL << 18)  // (MATRIX) DMA1 Port 0 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR1_DMA1_PORT1           (0x5UL << 18)  // (MATRIX) DMA1 Port 1 Master is Default Master
// -------- MATRIX_SCFG2 : (MATRIX Offset: 0x48) Slave Configuration Register 2 (Soft Modem) -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR2 (0xFUL << 18)       // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR2_ARM926I              (0x0UL << 18)  // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR2_ARM926D              (0x1UL << 18)  // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR2_DMA1_PORT0           (0x4UL << 18)  // (MATRIX) DMA1 Port 0 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR2_DMA1_PORT1           (0x5UL << 18)  // (MATRIX) DMA1 Port 1 Master is Default Master
// -------- MATRIX_SCFG3 : (MATRIX Offset: 0x4c) Slave Configuration Register 3 (USB Device) -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR3 (0xFUL << 18)       // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_ARM926I              (0x0UL << 18)  // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR3_ARM926D              (0x1UL << 18)  // (MATRIX) ARM926EJ-S Data Master is Default Master
// -------- MATRIX_SCFG4 : (MATRIX Offset: 0x50) Slave Configuration Register 4 (EBI) -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR4 (0xFUL << 18)       // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_ARM926I              (0x0UL << 18)  // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_ARM926D              (0x1UL << 18)  // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_DMA0_PORT0           (0x2UL << 18)  // (MATRIX) DMA0 Port 0 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_DMA0_PORT1           (0x3UL << 18)  // (MATRIX) DMA0 Port 1 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_DMA1_PORT0           (0x4UL << 18)  // (MATRIX) DMA1 Port 0 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_DMA1_PORT1           (0x5UL << 18)  // (MATRIX) DMA1 Port 1 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_UDPHS                (0x6UL << 18)  // (MATRIX) USB Device Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_UHPHS_EHCI           (0x7UL << 18)  // (MATRIX) USB Host EHCI Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_UHPHS_OHCI           (0x8UL << 18)  // (MATRIX) USB Host OHCI Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_ISI                  (0x9UL << 18)  // (MATRIX) ISI/LCD Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_EMAC0                (0xAUL << 18)  // (MATRIX) EMAC0 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR4_EMAC1                (0xBUL << 18)  // (MATRIX) EMAC1 Master is Default Master
// -------- MATRIX_SCFG5 : (MATRIX Offset: 0x54) Slave Configuration Register 5 (DDR2 Slave Port 1) -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR5 (0xFUL << 18)       // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_ARM926I              (0x0UL << 18)  // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_DMA0_PORT0           (0x2UL << 18)  // (MATRIX) DMA0 Port 0 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR5_DMA0_PORT1           (0x3UL << 18)  // (MATRIX) DMA0 Port 1 Master is Default Master
// -------- MATRIX_SCFG6 : (MATRIX Offset: 0x58) Slave Configuration Register 6 (DDR2 Slave Port 2) -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR6 (0xFUL << 18)       // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_ARM926D              (0x1UL << 18)  // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_DMA1_PORT0           (0x4UL << 18)  // (MATRIX) DMA1 Port 0 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR6_DMA1_PORT1           (0x5UL << 18)  // (MATRIX) DMA1 Port 1 Master is Default Master
// -------- MATRIX_SCFG7 : (MATRIX Offset: 0x5c) Slave Configuration Register 7 (DDR2 Slave Port 3) -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR7 (0xFUL << 18)       // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR7_ISI                  (0x9UL << 18)  // (MATRIX) ISI/LCD Master is Default Master
// -------- MATRIX_SCFG8 : (MATRIX Offset: 0x60) Slave Configuration Register 8 (Peripheral Bridge 0) -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR8 (0xFUL << 18)       // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR8_ARM926I              (0x0UL << 18)  // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR8_ARM926D              (0x1UL << 18)  // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR8_DMA0_PORT0           (0x2UL << 18)  // (MATRIX) DMA0 Port 0 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR8_DMA0_PORT1           (0x3UL << 18)  // (MATRIX) DMA0 Port 1 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR8_DMA1_PORT0           (0x4UL << 18)  // (MATRIX) DMA1 Port 0 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR8_DMA1_PORT1           (0x5UL << 18)  // (MATRIX) DMA1 Port 1 Master is Default Master
// -------- MATRIX_SCFG9 : (MATRIX Offset: 0x64) Slave Configuration Register 9 (Peripheral Bridge 1) -------- 
#define AT91C_MATRIX_FIXED_DEFMSTR9 (0xFUL << 18)       // (MATRIX) Fixed Index of Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR9_ARM926I              (0x0UL << 18)  // (MATRIX) ARM926EJ-S Instruction Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR9_ARM926D              (0x1UL << 18)  // (MATRIX) ARM926EJ-S Data Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR9_DMA0_PORT0           (0x2UL << 18)  // (MATRIX) DMA0 Port 0 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR9_DMA0_PORT1           (0x3UL << 18)  // (MATRIX) DMA0 Port 1 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR9_DMA1_PORT0           (0x4UL << 18)  // (MATRIX) DMA1 Port 0 Master is Default Master
#define 	AT91C_MATRIX_FIXED_DEFMSTR9_DMA1_PORT1           (0x5UL << 18)  // (MATRIX) DMA1 Port 1 EHCI Master is Default Master
// -------- MATRIX_PRAS0 : (MATRIX Offset: 0x80) PRAS0 Register -------- 
#define AT91C_MATRIX_M0PR         (0x3UL <<  0) // (MATRIX) ARM926EJ-S Instruction priority
#define AT91C_MATRIX_M1PR         (0x3UL <<  4) // (MATRIX) ARM926EJ-S Data priority
#define AT91C_MATRIX_M2PR         (0x3UL <<  8) // (MATRIX) DMA0 Master Port 0 priority
#define AT91C_MATRIX_M3PR         (0x3UL << 12) // (MATRIX) DMA0 Master Port 1 priority
#define AT91C_MATRIX_M4PR         (0x3UL << 16) // (MATRIX) DMA1 Master Port 0 priority
#define AT91C_MATRIX_M5PR         (0x3UL << 20) // (MATRIX) DMA1 Master Port 1 priority
#define AT91C_MATRIX_M6PR         (0x3UL << 24) // (MATRIX) USB Device priority
#define AT91C_MATRIX_M7PR         (0x3UL << 28) // (MATRIX) USB Host EHCI priority
// -------- MATRIX_PRBS0 : (MATRIX Offset: 0x84) PRBS0 Register -------- 
#define AT91C_MATRIX_M8PR         (0x3UL <<  0) // (MATRIX) USB Host OHCI priority
#define AT91C_MATRIX_M9PR         (0x3UL <<  4) // (MATRIX) ISI/LCD priority
#define AT91C_MATRIX_M10PR        (0x3UL <<  8) // (MATRIX) EMAC0 priority
#define AT91C_MATRIX_M11PR        (0x3UL << 12) // (MATRIX) EMAC1 priority
// -------- MATRIX_PRAS1 : (MATRIX Offset: 0x88) PRAS1 Register -------- 
// -------- MATRIX_PRBS1 : (MATRIX Offset: 0x8c) PRBS1 Register -------- 
// -------- MATRIX_PRAS2 : (MATRIX Offset: 0x90) PRAS2 Register -------- 
// -------- MATRIX_PRBS2 : (MATRIX Offset: 0x94) PRBS2 Register -------- 
// -------- MATRIX_PRAS3 : (MATRIX Offset: 0x98) PRAS3 Register -------- 
// -------- MATRIX_PRBS3 : (MATRIX Offset: 0x9c) PRBS3 Register -------- 
// -------- MATRIX_PRAS4 : (MATRIX Offset: 0xa0) PRAS4 Register -------- 
// -------- MATRIX_PRBS4 : (MATRIX Offset: 0xa4) PRBS4 Register -------- 
// -------- MATRIX_PRAS5 : (MATRIX Offset: 0xa8) PRAS5 Register -------- 
// -------- MATRIX_PRBS5 : (MATRIX Offset: 0xac) PRBS5 Register -------- 
// -------- MATRIX_PRAS6 : (MATRIX Offset: 0xb0) PRAS6 Register -------- 
// -------- MATRIX_PRBS6 : (MATRIX Offset: 0xb4) PRBS6 Register -------- 
// -------- MATRIX_PRAS7 : (MATRIX Offset: 0xb8) PRAS7 Register -------- 
// -------- MATRIX_PRBS7 : (MATRIX Offset: 0xbc) PRBS7 Register -------- 
// -------- MATRIX_PRAS8 : (MATRIX Offset: 0xc0) PRAS8 Register -------- 
// -------- MATRIX_PRBS8 : (MATRIX Offset: 0xc4) PRBS8 Register -------- 
// -------- MATRIX_PRAS9 : (MATRIX Offset: 0xc8) PRAS9 Register -------- 
// -------- MATRIX_PRBS9 : (MATRIX Offset: 0xcc) PRBS9 Register -------- 
// -------- MATRIX_MRCR : (MATRIX Offset: 0x100) MRCR Register -------- 
#define AT91C_MATRIX_RCA926I      (0x1UL <<  0) // (MATRIX) Remap Command Bit for ARM926EJ-S Instruction
#define AT91C_MATRIX_RCA926D      (0x1UL <<  1) // (MATRIX) Remap Command Bit for ARM926EJ-S Data
#define AT91C_MATRIX_RCB2         (0x1UL <<  2) // (MATRIX) Remap Command Bit for DMA0 Master Port 0
#define AT91C_MATRIX_RCB3         (0x1UL <<  3) // (MATRIX) Remap Command Bit for DMA0 Master Port 1
#define AT91C_MATRIX_RCB4         (0x1UL <<  4) // (MATRIX) Remap Command Bit for DMA1 Master Port 0
#define AT91C_MATRIX_RCB5         (0x1UL <<  5) // (MATRIX) Remap Command Bit for DMA1 Master Port 1
#define AT91C_MATRIX_RCB6         (0x1UL <<  6) // (MATRIX) Remap Command Bit for USB Device
#define AT91C_MATRIX_RCB7         (0x1UL <<  7) // (MATRIX) Remap Command Bit for USB Host EHCI
#define AT91C_MATRIX_RCB8         (0x1UL <<  8) // (MATRIX) Remap Command Bit for USB Host OHCI
#define AT91C_MATRIX_RCB9         (0x1UL <<  9) // (MATRIX) Remap Command Bit for ISI/LCD
#define AT91C_MATRIX_RCB10        (0x1UL << 10) // (MATRIX) Remap Command Bit for EMAC0
#define AT91C_MATRIX_RCB11        (0x1UL << 11) // (MATRIX) Remap Command Bit for EMAC1
// -------- MATRIX_SFR0 : (MATRIX Offset: 0x110) Special Function Register 0 -------- 
// -------- MATRIX_SFR1 : (MATRIX Offset: 0x114) Special Function Register 1 -------- 
// -------- MATRIX_SFR2 : (MATRIX Offset: 0x118) Special Function Register 2 -------- 
// -------- MATRIX_SFR3 : (MATRIX Offset: 0x11c) Special Function Register 3 -------- 
// -------- MATRIX_SFR4 : (MATRIX Offset: 0x120) Special Function Register 4 -------- 
// -------- MATRIX_SFR5 : (MATRIX Offset: 0x124) Special Function Register 5 -------- 
// -------- MATRIX_SFR6 : (MATRIX Offset: 0x128) Special Function Register 6 -------- 
// -------- MATRIX_SFR7 : (MATRIX Offset: 0x12c) Special Function Register 7 -------- 
// -------- MATRIX_SFR8 : (MATRIX Offset: 0x130) Special Function Register 8 -------- 
// -------- MATRIX_SFR9 : (MATRIX Offset: 0x134) Special Function Register 9 -------- 
// -------- MATRIX_SFR10 : (MATRIX Offset: 0x138) Special Function Register 10 -------- 
// -------- MATRIX_SFR11 : (MATRIX Offset: 0x13c) Special Function Register 11 -------- 
// -------- MATRIX_SFR12 : (MATRIX Offset: 0x140) Special Function Register 12 -------- 
// -------- MATRIX_SFR13 : (MATRIX Offset: 0x144) Special Function Register 13 -------- 
// -------- MATRIX_SFR0 : (MATRIX Offset: 0x148) Special Function Register 14 -------- 
// -------- MATRIX_SFR15 : (MATRIX Offset: 0x14c) Special Function Register 15 -------- 
// -------- MATRIX_WRPROTEN : (MATRIX Offset: 0x1e4) Write Protection Control Register -------- 
#define AT91C_MATRIX_WRPROT       (0x1UL <<  0) // (MATRIX) Enable/Disable Write Protection of HMATRIX2 configuration registers (requires key)
#define 	AT91C_MATRIX_WRPROT_DISABLE              (0x0UL)        // (MATRIX) Disable Write Protection of HMATRIX2 configuration registers
#define 	AT91C_MATRIX_WRPROT_ENABLE               (0x1UL)        // (MATRIX) Enable  Write Protection of HMATRIX2 configuration registers
// -------- MATRIX_WRPROTST : (MATRIX Offset: 0x1e8) Write Protection Status Register -------- 
#define AT91C_MATRIX_WRPROT_VIOLATION (0x1UL <<  0)     // (MATRIX) Violation of Write Protection of HMATRIX2 configuration registers
#define 	AT91C_MATRIX_WRPROT_VIOLATION_UNDETECTED           (0x0UL)      // (MATRIX) No violation of Write Protection of HMATRIX2 configuration registers
#define 	AT91C_MATRIX_WRPROT_VIOLATION_DETECTED             (0x1UL)      // (MATRIX) Violation of  Write Protection of HMATRIX2 configuration registers
#define AT91C_MATRIX_WRPROT_VIOLATION_OFFSET (0x1FFUL <<  8)    // (MATRIX) Offset where violation of Write Protection of HMATRIX2 configuration registers is detected
// -------- HMATRIX2_VER : (MATRIX Offset: 0x1fc)  VERSION  Register -------- 
#define AT91C_HMATRIX2_VER        (0xFUL <<  0) // (MATRIX)  VERSION  Register

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR AHB CCFG Interface
// *****************************************************************************
// *** Register offset in AT91S_CCFG structure ***
#define CCFG_ROM        ( 4)    //  Slave 1 (ROM) Wait-State Configuration Register
#define CCFG_UDPHS      (12)    //  USB Device HS configuration Register
#define CCFG_EBICSA     (16)    //  EBI Chip Select Assignement Register
#define CCFG_MATRIXVERSION (236)        //  Version Register
// -------- CCFG_ROM : (CCFG Offset: 0x4) AHB Slave 1 (ROM) Configuration -------- 
#define AT91C_ROM_WS_CFG          (0x1UL <<  0) // (CCFG) Rom Wait State Configuration
#define 	AT91C_ROM_WS_CFG_NO_WAIT              (0x0UL)   // (CCFG) ROM accesses are No Wait-State accesses.
#define 	AT91C_ROM_WS_CFG_SINGLE_WAIT          (0x1UL)   // (CCFG) ROM accesses are all One Wait-State accesses.
// -------- CCFG_UDPHS : (CCFG Offset: 0xc) USB Device HS configuration -------- 
#define AT91C_CCFG_DONT_USE_UTMI_LOCK (0x1UL <<  0)     // (CCFG)
#define 	AT91C_CCFG_DONT_USE_UTMI_LOCK_DONT_USE_LOCK        (0x0UL)      // (CCFG)
// -------- CCFG_EBICSA : (CCFG Offset: 0x10) EBI Chip Select Assignement Register -------- 
#define AT91C_EBI_CS1A            (0x1UL <<  1) // (CCFG) Chip Select 1 Assignment
#define 	AT91C_EBI_CS1A_SMC                  (0x0UL <<  1)       // (CCFG) Chip Select 1 is assigned to the Static Memory Controller.
#define 	AT91C_EBI_CS1A_SDRAMC               (0x1UL <<  1)       // (CCFG) Chip Select 1 is assigned to the SDRAM Controller.
#define AT91C_EBI_CS3A            (0x1UL <<  3) // (CCFG) Chip Select 3 Assignment
#define 	AT91C_EBI_CS3A_SMC                  (0x0UL <<  3)       // (CCFG) Chip Select 3 is only assigned to the Static Memory Controller and NCS3 behaves as defined by the SMC.
#define 	AT91C_EBI_CS3A_SM                   (0x1UL <<  3)       // (CCFG) Chip Select 3 is assigned to the Static Memory Controller and the SmartMedia Logic is activated.
#define AT91C_EBI_DBPUC           (0x1UL <<  8) // (CCFG) Data Bus Pull-up Configuration
#define AT91C_EBI_DBPDC           (0x1UL <<  9) // (CCFG) Data Bus Pull-down Configuration
#define AT91C_EBI_DRV             (0x1UL << 17) // (CCFG) EBI I/O Drive Configuration
#define 	AT91C_EBI_DRV_LD                   (0x0UL << 17)        // (CCFG) optimized for memories with Low  Drive
#define 	AT91C_EBI_DRV_HD                   (0x1UL << 17)        // (CCFG) optimized for memories with High Drive
#define AT91C_EBI_NFD0_ON_D16     (0x1UL << 24) // (CCFG) Nand Flash databus selection
#define AT91C_EBI_DDR_MP_EN       (0x1UL << 25) // (CCFG) DDR Multiport Enable

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Advanced Interrupt Controller
// *****************************************************************************
// *** Register offset in AT91S_AIC structure ***
#define AIC_SMR         ( 0)    // Source Mode Register
#define AIC_SVR         (128)   // Source Vector Register
#define AIC_IVR         (256)   // IRQ Vector Register
#define AIC_FVR         (260)   // FIQ Vector Register
#define AIC_ISR         (264)   // Interrupt Status Register
#define AIC_IPR         (268)   // Interrupt Pending Register
#define AIC_IMR         (272)   // Interrupt Mask Register
#define AIC_CISR        (276)   // Core Interrupt Status Register
#define AIC_IECR        (288)   // Interrupt Enable Command Register
#define AIC_IDCR        (292)   // Interrupt Disable Command Register
#define AIC_ICCR        (296)   // Interrupt Clear Command Register
#define AIC_ISCR        (300)   // Interrupt Set Command Register
#define AIC_EOICR       (304)   // End of Interrupt Command Register
#define AIC_SPU         (308)   // Spurious Vector Register
#define AIC_DCR         (312)   // Debug Control Register (Protect)
#define AIC_FFER        (320)   // Fast Forcing Enable Register
#define AIC_FFDR        (324)   // Fast Forcing Disable Register
#define AIC_FFSR        (328)   // Fast Forcing Status Register
// -------- AIC_SMR : (AIC Offset: 0x0) Control Register -------- 
#define AT91C_AIC_PRIOR           (0x7UL <<  0) // (AIC) Priority Level
#define 	AT91C_AIC_PRIOR_LOWEST               (0x0UL)    // (AIC) Lowest priority level
#define 	AT91C_AIC_PRIOR_HIGHEST              (0x7UL)    // (AIC) Highest priority level
#define AT91C_AIC_SRCTYPE         (0x3UL <<  5) // (AIC) Interrupt Source Type
#define 	AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE  (0x0UL <<  5)    // (AIC) Internal Sources Code Label Level Sensitive
#define 	AT91C_AIC_SRCTYPE_INT_EDGE_TRIGGERED   (0x1UL <<  5)    // (AIC) Internal Sources Code Label Edge triggered
#define 	AT91C_AIC_SRCTYPE_EXT_HIGH_LEVEL       (0x2UL <<  5)    // (AIC) External Sources Code Label High-level Sensitive
#define 	AT91C_AIC_SRCTYPE_EXT_POSITIVE_EDGE    (0x3UL <<  5)    // (AIC) External Sources Code Label Positive Edge triggered
// -------- AIC_CISR : (AIC Offset: 0x114) AIC Core Interrupt Status Register -------- 
#define AT91C_AIC_NFIQ            (0x1UL <<  0) // (AIC) NFIQ Status
#define AT91C_AIC_NIRQ            (0x1UL <<  1) // (AIC) NIRQ Status
// -------- AIC_DCR : (AIC Offset: 0x138) AIC Debug Control Register (Protect) -------- 
#define AT91C_AIC_DCR_PROT        (0x1UL <<  0) // (AIC) Protection Mode
#define AT91C_AIC_DCR_GMSK        (0x1UL <<  1) // (AIC) General Mask

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Debug Unit
// *****************************************************************************
// *** Register offset in AT91S_DBGU structure ***
#define DBGU_CR         ( 0)    // Control Register
#define DBGU_MR         ( 4)    // Mode Register
#define DBGU_IER        ( 8)    // Interrupt Enable Register
#define DBGU_IDR        (12)    // Interrupt Disable Register
#define DBGU_IMR        (16)    // Interrupt Mask Register
#define DBGU_CSR        (20)    // Channel Status Register
#define DBGU_RHR        (24)    // Receiver Holding Register
#define DBGU_THR        (28)    // Transmitter Holding Register
#define DBGU_BRGR       (32)    // Baud Rate Generator Register
#define DBGU_CIDR       (64)    // Chip ID Register
#define DBGU_EXID       (68)    // Chip ID Extension Register
#define DBGU_FNTR       (72)    // Force NTRST Register
#define DBGU_ADDRSIZE   (236)   // DBGU ADDRSIZE REGISTER
#define DBGU_IPNAME1    (240)   // DBGU IPNAME1 REGISTER
#define DBGU_IPNAME2    (244)   // DBGU IPNAME2 REGISTER
#define DBGU_FEATURES   (248)   // DBGU FEATURES REGISTER
#define DBGU_VER        (252)   // DBGU VERSION REGISTER
// -------- DBGU_CR : (DBGU Offset: 0x0) Debug Unit Control Register -------- 
#define AT91C_DBGU_RSTRX          (0x1UL <<  2) // (DBGU) Reset Receiver
#define AT91C_DBGU_RSTTX          (0x1UL <<  3) // (DBGU) Reset Transmitter
#define AT91C_DBGU_RXEN           (0x1UL <<  4) // (DBGU) Receiver Enable
#define AT91C_DBGU_RXDIS          (0x1UL <<  5) // (DBGU) Receiver Disable
#define AT91C_DBGU_TXEN           (0x1UL <<  6) // (DBGU) Transmitter Enable
#define AT91C_DBGU_TXDIS          (0x1UL <<  7) // (DBGU) Transmitter Disable
#define AT91C_DBGU_RSTSTA         (0x1UL <<  8) // (DBGU) Reset Status Bits
// -------- DBGU_MR : (DBGU Offset: 0x4) Debug Unit Mode Register -------- 
#define AT91C_DBGU_PAR            (0x7UL <<  9) // (DBGU) Parity type
#define 	AT91C_DBGU_PAR_EVEN                 (0x0UL <<  9)       // (DBGU) Even Parity
#define 	AT91C_DBGU_PAR_ODD                  (0x1UL <<  9)       // (DBGU) Odd Parity
#define 	AT91C_DBGU_PAR_SPACE                (0x2UL <<  9)       // (DBGU) Parity forced to 0 (Space)
#define 	AT91C_DBGU_PAR_MARK                 (0x3UL <<  9)       // (DBGU) Parity forced to 1 (Mark)
#define 	AT91C_DBGU_PAR_NONE                 (0x4UL <<  9)       // (DBGU) No Parity
#define AT91C_DBGU_CHMODE         (0x3UL << 14) // (DBGU) Channel Mode
#define 	AT91C_DBGU_CHMODE_NORMAL               (0x0UL << 14)    // (DBGU) Normal Mode: The debug unit channel operates as an RX/TX debug unit.
#define 	AT91C_DBGU_CHMODE_AUTO                 (0x1UL << 14)    // (DBGU) Automatic Echo: Receiver Data Input is connected to the TXD pin.
#define 	AT91C_DBGU_CHMODE_LOCAL                (0x2UL << 14)    // (DBGU) Local Loopback: Transmitter Output Signal is connected to Receiver Input Signal.
#define 	AT91C_DBGU_CHMODE_REMOTE               (0x3UL << 14)    // (DBGU) Remote Loopback: RXD pin is internally connected to TXD pin.
// -------- DBGU_IER : (DBGU Offset: 0x8) Debug Unit Interrupt Enable Register -------- 
#define AT91C_DBGU_RXRDY          (0x1UL <<  0) // (DBGU) RXRDY Interrupt
#define AT91C_DBGU_TXRDY          (0x1UL <<  1) // (DBGU) TXRDY Interrupt
#define AT91C_DBGU_ENDRX          (0x1UL <<  3) // (DBGU) End of Receive Transfer Interrupt
#define AT91C_DBGU_ENDTX          (0x1UL <<  4) // (DBGU) End of Transmit Interrupt
#define AT91C_DBGU_OVRE           (0x1UL <<  5) // (DBGU) Overrun Interrupt
#define AT91C_DBGU_FRAME          (0x1UL <<  6) // (DBGU) Framing Error Interrupt
#define AT91C_DBGU_PARE           (0x1UL <<  7) // (DBGU) Parity Error Interrupt
#define AT91C_DBGU_TXEMPTY        (0x1UL <<  9) // (DBGU) TXEMPTY Interrupt
#define AT91C_DBGU_TXBUFE         (0x1UL << 11) // (DBGU) TXBUFE Interrupt
#define AT91C_DBGU_RXBUFF         (0x1UL << 12) // (DBGU) RXBUFF Interrupt
#define AT91C_DBGU_COMM_TX        (0x1UL << 30) // (DBGU) COMM_TX Interrupt
#define AT91C_DBGU_COMM_RX        (0x1UL << 31) // (DBGU) COMM_RX Interrupt
// -------- DBGU_IDR : (DBGU Offset: 0xc) Debug Unit Interrupt Disable Register -------- 
// -------- DBGU_IMR : (DBGU Offset: 0x10) Debug Unit Interrupt Mask Register -------- 
// -------- DBGU_CSR : (DBGU Offset: 0x14) Debug Unit Channel Status Register -------- 
// -------- DBGU_FNTR : (DBGU Offset: 0x48) Debug Unit FORCE_NTRST Register -------- 
#define AT91C_DBGU_FORCE_NTRST    (0x1UL <<  0) // (DBGU) Force NTRST in JTAG

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Parallel Input Output Controler
// *****************************************************************************
// *** Register offset in AT91S_PIO structure ***
#define PIO_PER(p)         ( 0 + (p) * 0x200)   // PIO Enable Register
#define PIO_PDR(p)         ( 4 + (p) * 0x200)   // PIO Disable Register
#define PIO_PSR(p)         ( 8 + (p) * 0x200)   // PIO Status Register
#define PIO_OER(p)         (16 + (p) * 0x200)   // Output Enable Register
#define PIO_ODR(p)         (20 + (p) * 0x200)   // Output Disable Registerr
#define PIO_OSR(p)         (24 + (p) * 0x200)   // Output Status Register
#define PIO_IFER(p)        (32 + (p) * 0x200)   // Input Filter Enable Register
#define PIO_IFDR(p)        (36 + (p) * 0x200)   // Input Filter Disable Register
#define PIO_IFSR(p)        (40 + (p) * 0x200)   // Input Filter Status Register
#define PIO_SODR(p)        (48 + (p) * 0x200)   // Set Output Data Register
#define PIO_CODR(p)        (52 + (p) * 0x200)   // Clear Output Data Register
#define PIO_ODSR(p)        (56 + (p) * 0x200)   // Output Data Status Register
#define PIO_PDSR(p)        (60 + (p) * 0x200)   // Pin Data Status Register
#define PIO_IER(p)         (64 + (p) * 0x200)   // Interrupt Enable Register
#define PIO_IDR(p)         (68 + (p) * 0x200)   // Interrupt Disable Register
#define PIO_IMR(p)         (72 + (p) * 0x200)   // Interrupt Mask Register
#define PIO_ISR(p)         (76 + (p) * 0x200)   // Interrupt Status Register
#define PIO_MDER(p)        (80 + (p) * 0x200)   // Multi-driver Enable Register
#define PIO_MDDR(p)        (84 + (p) * 0x200)   // Multi-driver Disable Register
#define PIO_MDSR(p)        (88 + (p) * 0x200)   // Multi-driver Status Register
#define PIO_PPUDR(p)       (96 + (p) * 0x200)   // Pull-up Disable Register
#define PIO_PPUER(p)       (100 + (p) * 0x200)  // Pull-up Enable Register
#define PIO_PPUSR(p)       (104 + (p) * 0x200)  // Pull-up Status Register
#define PIO_SP1(p)         (112 + (p) * 0x200)  // Select Peripheral 1 Register
#define PIO_SP2(p)         (116 + (p) * 0x200)  // Select Peripheral 2 Register
#define PIO_ABSR(p)        (120 + (p) * 0x200)  // AB Select Status Register
#define PIO_PPDDR(p)       (144 + (p) * 0x200)  // Pull-down Disable Register
#define PIO_PPDER(p)       (148 + (p) * 0x200)  // Pull-down Enable Register
#define PIO_PPDSR(p)       (152 + (p) * 0x200)  // Pull-down Status Register
#define PIO_OWER(p)        (160 + (p) * 0x200)  // Output Write Enable Register
#define PIO_OWDR(p)        (164 + (p) * 0x200)  // Output Write Disable Register
#define PIO_OWSR(p)        (168 + (p) * 0x200)  // Output Write Status Register
#define PIO_ADDRSIZE(p)    (236 + (p) * 0x200)  // PIO ADDRSIZE REGISTER
#define PIO_IPNAME1(p)     (240 + (p) * 0x200)  // PIO IPNAME1  REGISTER
#define PIO_IPNAME2(p)     (244 + (p) * 0x200)  // PIO IPNAME2  REGISTER
#define PIO_FEATURES(p)    (248 + (p) * 0x200)  // PIO FEATURES REGISTER
#define PIO_VER(p)         (252 + (p) * 0x200)  // PIO VERSION  REGISTER
#define PIO_SCHMITT(p)     (256 + (p) * 0x200)  // PIO SCHMITT Register
#define PIO_DELAY1(p)      (272 + (p) * 0x200)  // PIO DELAY1  Register
#define PIO_DRIVE1(p)      (276 + (p) * 0x200)  // PIO DRIVE1  Register
#define PIO_DRIVE2(p)      (280 + (p) * 0x200)  // PIO DRIVE2  Register
#define PIO_SENMR(p)       (336 + (p) * 0x200)  // Sensor Mode Register
#define PIO_SENIER(p)      (340 + (p) * 0x200)  // Sensor Interrupt Enable Register
#define PIO_SENIDR(p)      (344 + (p) * 0x200)  // Sensor Interrupt Disable Register
#define PIO_SENIMR(p)      (348 + (p) * 0x200)  // Sensor Interrupt Mask Register
#define PIO_SENISR(p)      (352 + (p) * 0x200)  // Sensor Interrupt Status Register
#define PIO_SENDATA(p)     (356 + (p) * 0x200)  // Sensor Data Register

#define AT91C_NR_PIO               (32 * 4)

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Power Management Controller 3 V204
// *****************************************************************************
// *** Register offset in AT91S_PMC structure ***
#define PMC_SCER        ( 0)    // System Clock Enable Register
#define PMC_SCDR        ( 4)    // System Clock Disable Register
#define PMC_SCSR        ( 8)    // System Clock Status Register
#define PMC_PCER        (16)    // Peripheral Clock Enable Register  (0:31 PERI_ID)
#define PMC_PCDR        (20)    // Peripheral Clock Disable Register (0:31 PERI_ID)
#define PMC_PCSR        (24)    // Peripheral Clock Status Register  (0:31 PERI_ID)
#define PMC_UCKR        (28)    // UTMI Clock Configuration Register
#define PMC_MOR         (32)    // Main Oscillator Register
#define PMC_MCFR        (36)    // Main Clock  Frequency Register
#define PMC_PLLAR       (40)    // PLL A Register
#define PMC_PLLBR       (44)    // PLL B Register
#define PMC_MCKR        (48)    // Master Clock Register
#define PMC_USB         (56)    // USB clock register
#define PMC_SMD         (60)    // SMD clock register
#define PMC_PCKR        (64)    // Programmable Clock 0 Register
#define PMC_IER         (96)    // Interrupt Enable Register
#define PMC_IDR         (100)   // Interrupt Disable Register
#define PMC_SR          (104)   // Status Register
#define PMC_IMR         (108)   // Interrupt Mask Register
#define PMC_FSMR        (112)   // Fast Startup Mode Register
#define PMC_FSPR        (116)   // Fast Startup Polarity Register
#define PMC_FOCR        (120)   // Fault Output Clear Register
#define PMC_PLLICPR     (128)   // PLL Charge Pump Current Register
#define PMC_ADDRSIZE    (236)   //
#define PMC_NAME1       (240)   //
#define PMC_NAME2       (244)   //
#define PMC_FEATURES    (248)   //
#define PMC_VERSION     (252)   //
#define PMC_PCER1       (256)   // Peripheral Clock Enable Register  32:63 PERI_ID
#define PMC_PCDR1       (260)   // Peripheral Clock Disable Register 32:63 PERI_ID
#define PMC_PCSR1       (264)   // Peripheral Clock Status Register  32:63 PERI_ID
#define PMC_PCR         (268)   // Peripheral Control Register
// -------- PMC_SCER : (PMC Offset: 0x0) System Clock Enable Register -------- 
#define AT91C_PMC_DDR             (0x1UL <<  2) // (PMC) DDR controller Clock2x
#define AT91C_PMC_UHP             (0x1UL <<  6) // (PMC) USB Host Port Clock
#define AT91C_PMC_UDP             (0x1UL <<  7) // (PMC) USB Device Port Clock
#define AT91C_PMC_PCK0            (0x1UL <<  8) // (PMC) Programmable Clock Output
#define AT91C_PMC_PCK1            (0x1UL <<  9) // (PMC) Programmable Clock Output
// -------- PMC_SCDR : (PMC Offset: 0x4) System Clock Disable Register -------- 
// -------- PMC_SCSR : (PMC Offset: 0x8) System Clock Status Register -------- 
#define AT91C_PMC_PCK             (0x1UL <<  0) // (PMC) Processor Clock
// -------- CKGR_UCKR : (PMC Offset: 0x1c) UTMI Clock Configuration Register -------- 
#define AT91C_CKGR_UOSCEN         (0x1UL <<  0) // (PMC) UTMI Oscillator Enable
#define AT91C_CKGR_OSCBYPASS      (0x1UL <<  1) // (PMC) UTMI Oscillator Bypass
#define AT91C_CKGR_OSCOUNT        (0xFFUL <<  8)        // (PMC) UTMI Oscillator Start-up Time
#define AT91C_CKGR_UPLLEN         (0x1UL << 16) // (PMC) UTMI PLL Enable
#define 	AT91C_CKGR_UPLLEN_DISABLED             (0x0UL << 16)    // (PMC) The UTMI PLL is disabled
#define 	AT91C_CKGR_UPLLEN_ENABLED              (0x1UL << 16)    // (PMC) The UTMI PLL is enabled
#define AT91C_CKGR_UPLLCOUNT      (0xFUL << 20) // (PMC) UTMI Oscillator Start-up Time
#define AT91C_CKGR_BIASEN         (0x1UL << 24) // (PMC) UTMI BIAS Enable
#define 	AT91C_CKGR_BIASEN_DISABLED             (0x0UL << 24)    // (PMC) The UTMI BIAS is disabled
#define 	AT91C_CKGR_BIASEN_ENABLED              (0x1UL << 24)    // (PMC) The UTMI BIAS is enabled
#define AT91C_CKGR_BIASCOUNT      (0xFUL << 28) // (PMC) UTMI BIAS Start-up Time
// -------- CKGR_MOR : (PMC Offset: 0x20) Main Oscillator Register -------- 
#define AT91C_CKGR_MOSCXTEN       (0x1UL <<  0) // (PMC) Main Crystal Oscillator Enable
#define AT91C_CKGR_MOSCXTBY       (0x1UL <<  1) // (PMC) Main Crystal Oscillator Bypass
#define AT91C_CKGR_WAITMODE       (0x1UL <<  2) // (PMC) Main Crystal Oscillator Bypass
#define AT91C_CKGR_MOSCRCEN       (0x1UL <<  3) // (PMC) Main On-Chip RC Oscillator Enable
#define AT91C_CKGR_MOSCXTST       (0xFFUL <<  8)        // (PMC) Main Crystal Oscillator Start-up Time
#define AT91C_CKGR_KEY            (0xFFUL << 16)        // (PMC) Clock Generator Controller Writing Protection Key
#define AT91C_CKGR_MOSCSEL        (0x1UL << 24) // (PMC) Main Oscillator Selection
#define AT91C_CKGR_CFDEN          (0x1UL << 25) // (PMC) Clock Failure Detector Enable
// -------- CKGR_MCFR : (PMC Offset: 0x24) Main Clock Frequency Register -------- 
#define AT91C_CKGR_MAINF          (0xFFFFUL <<  0)      // (PMC) Main Clock Frequency
#define AT91C_CKGR_MAINRDY        (0x1UL << 16) // (PMC) Main Clock Ready
// -------- CKGR_PLLAR : (PMC Offset: 0x28) PLL A Register -------- 
#define AT91C_CKGR_DIVA           (0xFFUL <<  0)        // (PMC) Divider A Selected
#define 	AT91C_CKGR_DIVA_0                    (0x0UL)    // (PMC) Divider A output is 0
#define 	AT91C_CKGR_DIVA_BYPASS               (0x1UL)    // (PMC) Divider A is bypassed
#define AT91C_CKGR_PLLACOUNT      (0x3FUL <<  8)        // (PMC) PLL A Counter
#define AT91C_CKGR_OUTA           (0x3UL << 14) // (PMC) PLL A Output Frequency Range
#define 	AT91C_CKGR_OUTA_0                    (0x0UL << 14)      // (PMC) Please refer to the PLLA datasheet
#define 	AT91C_CKGR_OUTA_1                    (0x1UL << 14)      // (PMC) Please refer to the PLLA datasheet
#define 	AT91C_CKGR_OUTA_2                    (0x2UL << 14)      // (PMC) Please refer to the PLLA datasheet
#define 	AT91C_CKGR_OUTA_3                    (0x3UL << 14)      // (PMC) Please refer to the PLLA datasheet
#define AT91C_CKGR_MULA           (0x7FFUL << 16)       // (PMC) PLL A Multiplier
#define AT91C_CKGR_SRCA           (0x1UL << 29) // (PMC)
// -------- CKGR_PLLBR : (PMC Offset: 0x2c) PLL B Register -------- 
#define AT91C_CKGR_DIVB           (0xFFUL <<  0)        // (PMC) Divider B Selected
#define 	AT91C_CKGR_DIVB_0                    (0x0UL)    // (PMC) Divider B output is 0
#define 	AT91C_CKGR_DIVB_BYPASS               (0x1UL)    // (PMC) Divider B is bypassed
#define AT91C_CKGR_PLLBCOUNT      (0x3FUL <<  8)        // (PMC) PLL B Counter
#define AT91C_CKGR_OUTB           (0x3UL << 14) // (PMC) PLL B Output Frequency Range
#define 	AT91C_CKGR_OUTB_0                    (0x0UL << 14)      // (PMC) Please refer to the PLLB datasheet
#define 	AT91C_CKGR_OUTB_1                    (0x1UL << 14)      // (PMC) Please refer to the PLLB datasheet
#define 	AT91C_CKGR_OUTB_2                    (0x2UL << 14)      // (PMC) Please refer to the PLLB datasheet
#define 	AT91C_CKGR_OUTB_3                    (0x3UL << 14)      // (PMC) Please refer to the PLLB datasheet
#define AT91C_CKGR_MULB           (0x7FFUL << 16)       // (PMC) PLL B Multiplier
// -------- PMC_MCKR : (PMC Offset: 0x30) Master Clock Register -------- 
#define AT91C_PMC_CSS             (0x7UL <<  0) // (PMC) Programmable Clock Selection
#define 	AT91C_PMC_CSS_SLOW_CLK             (0x0UL)      // (PMC) Slow Clock is selected
#define 	AT91C_PMC_CSS_MAIN_CLK             (0x1UL)      // (PMC) Main Clock is selected
#define 	AT91C_PMC_CSS_PLLA_CLK             (0x2UL)      // (PMC) Clock from PLL A is selected
#define 	AT91C_PMC_CSS_UPLL_CLK             (0x3UL)      // (PMC) Clock from UTMI PLL is selected
#define 	AT91C_PMC_CSS_SYS_CLK              (0x4UL)      // (PMC) System clock is selected
#define AT91C_PMC_PRES            (0xFUL <<  4) // (PMC) Programmable Clock Prescaler
#define 	AT91C_PMC_PRES_CLK                  (0x0UL <<  4)       // (PMC) Selected clock
#define 	AT91C_PMC_PRES_CLK_2                (0x1UL <<  4)       // (PMC) Selected clock divided by 2
#define 	AT91C_PMC_PRES_CLK_4                (0x2UL <<  4)       // (PMC) Selected clock divided by 4
#define 	AT91C_PMC_PRES_CLK_8                (0x3UL <<  4)       // (PMC) Selected clock divided by 8
#define 	AT91C_PMC_PRES_CLK_16               (0x4UL <<  4)       // (PMC) Selected clock divided by 16
#define 	AT91C_PMC_PRES_CLK_32               (0x5UL <<  4)       // (PMC) Selected clock divided by 32
#define 	AT91C_PMC_PRES_CLK_64               (0x6UL <<  4)       // (PMC) Selected clock divided by 64
#define 	AT91C_PMC_PRES_CLK_3                (0x7UL <<  4)       // (PMC) Selected clock divided by 3
#define 	AT91C_PMC_PRES_CLK_1_5              (0x8UL <<  4)       // (PMC) Selected clock divided by 1.5
#define AT91C_PMC_MDIV            (0x3UL <<  8) // (PMC) Master Clock Division
#define 	AT91C_PMC_MDIV_1                    (0x0UL <<  8)       // (PMC) Processor clock = Master Clock ; DDR Clock = Master Clock
#define 	AT91C_PMC_MDIV_2                    (0x1UL <<  8)       // (PMC) Processor clock = 2 * Master Clock ; DDR Clock = 2 * Master Clock
#define 	AT91C_PMC_MDIV_4                    (0x2UL <<  8)       // (PMC) Processor clock = 4 * Master Clock ; DDR Clock = 2 * Master Clock
#define 	AT91C_PMC_MDIV_3                    (0x3UL <<  8)       // (PMC) Processor clock = 3 * Master Clock ; DDR Clock = 2 * Master Clock
#define AT91C_PMC_PLLADIV2        (0x1UL << 12) // (PMC) PLLA divisor by 2
#define 	AT91C_PMC_PLLADIV2_1                    (0x0UL << 12)   // (PMC) PLLA clock frequency is divided by 1
#define 	AT91C_PMC_PLLADIV2_2                    (0x1UL << 12)   // (PMC) PLLA clock frequency is divided by 2
// -------- PMC_USB : (PMC Offset: 0x38) USB Clock Register -------- 
#define AT91C_PMC_USBS            (0x1UL <<  0) // (PMC) USBS
#define 	AT91C_PMC_USBS_USB_PLLA             (0x0UL)     // (PMC) USB Clock Input is PLLA
#define 	AT91C_PMC_USBS_USB_UPLL             (0x1UL)     // (PMC) USB Clock Input is UPLL
#define AT91C_PMC_USBDIV          (0xFUL <<  8) // (PMC) USBDIV
#define 	AT91C_PMC_USBDIV_1                    (0x0UL <<  8)     // (PMC) USB Clock divided by 1
#define 	AT91C_PMC_USBDIV_2                    (0x1UL <<  8)     // (PMC) USB Clock divided by 2
#define 	AT91C_PMC_USBDIV_3                    (0x2UL <<  8)     // (PMC) USB Clock divided by 3
#define 	AT91C_PMC_USBDIV_4                    (0x3UL <<  8)     // (PMC) USB Clock divided by 4
#define 	AT91C_PMC_USBDIV_5                    (0x4UL <<  8)     // (PMC) USB Clock divided by 5
#define 	AT91C_PMC_USBDIV_6                    (0x5UL <<  8)     // (PMC) USB Clock divided by 6
#define 	AT91C_PMC_USBDIV_7                    (0x6UL <<  8)     // (PMC) USB Clock divided by 7
#define 	AT91C_PMC_USBDIV_8                    (0x7UL <<  8)     // (PMC) USB Clock divided by 8
#define 	AT91C_PMC_USBDIV_9                    (0x8UL <<  8)     // (PMC) USB Clock divided by 9
#define 	AT91C_PMC_USBDIV_10                   (0x9UL <<  8)     // (PMC) USB Clock divided by 10
#define 	AT91C_PMC_USBDIV_11                   (0xAUL <<  8)     // (PMC) USB Clock divided by 11
#define 	AT91C_PMC_USBDIV_12                   (0xBUL <<  8)     // (PMC) USB Clock divided by 12
#define 	AT91C_PMC_USBDIV_13                   (0xCUL <<  8)     // (PMC) USB Clock divided by 13
#define 	AT91C_PMC_USBDIV_14                   (0xDUL <<  8)     // (PMC) USB Clock divided by 14
#define 	AT91C_PMC_USBDIV_15                   (0xEUL <<  8)     // (PMC) USB Clock divided by 15
#define 	AT91C_PMC_USBDIV_16                   (0xFUL <<  8)     // (PMC) USB Clock divided by 16
// -------- PMC_SMD : (PMC Offset: 0x3c) SMD Clock Register -------- 
#define AT91C_PMC_SMDS            (0x1UL <<  0) // (PMC) SMDS
#define 	AT91C_PMC_SMDS_SMD_PLLA             (0x0UL)     // (PMC) SMD Clock Input is PLLA
#define 	AT91C_PMC_SMDS_SMD_PLLB             (0x1UL)     // (PMC) SMD Clock Input is PLLB
#define AT91C_PMC_SMDDIV          (0x1FUL <<  8)        // (PMC) SMDDIV
#define 	AT91C_PMC_SMDDIV_1                    (0x0UL <<  8)     // (PMC) SMD Clock divided by 1
#define 	AT91C_PMC_SMDDIV_2                    (0x1UL <<  8)     // (PMC) SMD Clock divided by 2
#define 	AT91C_PMC_SMDDIV_3                    (0x2UL <<  8)     // (PMC) SMD Clock divided by 3
#define 	AT91C_PMC_SMDDIV_4                    (0x3UL <<  8)     // (PMC) SMD Clock divided by 4
#define 	AT91C_PMC_SMDDIV_5                    (0x4UL <<  8)     // (PMC) SMD Clock divided by 5
#define 	AT91C_PMC_SMDDIV_6                    (0x5UL <<  8)     // (PMC) SMD Clock divided by 6
#define 	AT91C_PMC_SMDDIV_7                    (0x6UL <<  8)     // (PMC) SMD Clock divided by 7
#define 	AT91C_PMC_SMDDIV_8                    (0x7UL <<  8)     // (PMC) SMD Clock divided by 8
#define 	AT91C_PMC_SMDDIV_9                    (0x8UL <<  8)     // (PMC) SMD Clock divided by 9
#define 	AT91C_PMC_SMDDIV_10                   (0x9UL <<  8)     // (PMC) SMD Clock divided by 10
#define 	AT91C_PMC_SMDDIV_11                   (0xAUL <<  8)     // (PMC) SMD Clock divided by 11
#define 	AT91C_PMC_SMDDIV_12                   (0xBUL <<  8)     // (PMC) SMD Clock divided by 12
#define 	AT91C_PMC_SMDDIV_13                   (0xCUL <<  8)     // (PMC) SMD Clock divided by 13
#define 	AT91C_PMC_SMDDIV_14                   (0xDUL <<  8)     // (PMC) SMD Clock divided by 14
#define 	AT91C_PMC_SMDDIV_15                   (0xEUL <<  8)     // (PMC) SMD Clock divided by 15
#define 	AT91C_PMC_SMDDIV_16                   (0xFUL <<  8)     // (PMC) SMD Clock divided by 16
#define 	AT91C_PMC_SMDDIV_17                   (0x10UL <<  8)    // (PMC) SMD Clock divided by 17
#define 	AT91C_PMC_SMDDIV_18                   (0x11UL <<  8)    // (PMC) SMD Clock divided by 18
#define 	AT91C_PMC_SMDDIV_19                   (0x12UL <<  8)    // (PMC) SMD Clock divided by 19
#define 	AT91C_PMC_SMDDIV_20                   (0x13UL <<  8)    // (PMC) SMD Clock divided by 20
#define 	AT91C_PMC_SMDDIV_21                   (0x14UL <<  8)    // (PMC) SMD Clock divided by 21
#define 	AT91C_PMC_SMDDIV_22                   (0x15UL <<  8)    // (PMC) SMD Clock divided by 22
#define 	AT91C_PMC_SMDDIV_23                   (0x16UL <<  8)    // (PMC) SMD Clock divided by 23
#define 	AT91C_PMC_SMDDIV_24                   (0x17UL <<  8)    // (PMC) SMD Clock divided by 24
#define 	AT91C_PMC_SMDDIV_25                   (0x18UL <<  8)    // (PMC) SMD Clock divided by 25
#define 	AT91C_PMC_SMDDIV_26                   (0x19UL <<  8)    // (PMC) SMD Clock divided by 26
#define 	AT91C_PMC_SMDDIV_27                   (0x1AUL <<  8)    // (PMC) SMD Clock divided by 27
#define 	AT91C_PMC_SMDDIV_28                   (0x1BUL <<  8)    // (PMC) SMD Clock divided by 28
#define 	AT91C_PMC_SMDDIV_29                   (0x1CUL <<  8)    // (PMC) SMD Clock divided by 29
#define 	AT91C_PMC_SMDDIV_30                   (0x1DUL <<  8)    // (PMC) SMD Clock divided by 30
#define 	AT91C_PMC_SMDDIV_31                   (0x1EUL <<  8)    // (PMC) SMD Clock divided by 31
#define 	AT91C_PMC_SMDDIV_32                   (0x1FUL <<  8)    // (PMC) SMD Clock divided by 32
// -------- PMC_PCKR : (PMC Offset: 0x40) Programmable Clock Register -------- 
#define AT91C_PMC_SLCKMCK         (0x1UL <<  8) // (PMC) Programmable Clock Prescaler
#define 	AT91C_PMC_SLCKMCK_SLCK                 (0x0UL <<  8)    // (PMC) Slow Clock selected
#define 	AT91C_PMC_SLCKMCK_MCK                  (0x1UL <<  8)    // (PMC) Master Clock selected
// -------- PMC_IER : (PMC Offset: 0x60) PMC Interrupt Enable Register -------- 
#define AT91C_PMC_MOSCXTS         (0x1UL <<  0) // (PMC) Main Crystal Oscillator Status/Enable/Disable/Mask
#define AT91C_PMC_LOCKA           (0x1UL <<  1) // (PMC) PLL A Status/Enable/Disable/Mask
#define AT91C_PMC_MCKRDY          (0x1UL <<  3) // (PMC) Master Clock Status/Enable/Disable/Mask
#define AT91C_PMC_LOCKU           (0x1UL <<  6) // (PMC) PLL UTMI Status/Enable/Disable/Mask
#define AT91C_PMC_PCKRDY0         (0x1UL <<  8) // (PMC) PCK0_RDY Status/Enable/Disable/Mask
#define AT91C_PMC_PCKRDY1         (0x1UL <<  9) // (PMC) PCK1_RDY Status/Enable/Disable/Mask
#define AT91C_PMC_MOSCSELS        (0x1UL << 16) // (PMC) Main Oscillator Selection Status
#define AT91C_PMC_MOSCRCS         (0x1UL << 17) // (PMC) Main On-Chip RC Oscillator Status
#define AT91C_PMC_CFDEV           (0x1UL << 18) // (PMC) Clock Failure Detector Event
// -------- PMC_IDR : (PMC Offset: 0x64) PMC Interrupt Disable Register -------- 
// -------- PMC_SR : (PMC Offset: 0x68) PMC Status Register -------- 
#define AT91C_PMC_CFDS            (0x1UL << 19) // (PMC) Clock Failure Detector Status
#define AT91C_PMC_FOS             (0x1UL << 20) // (PMC) Clock Failure Detector Fault Output Status
// -------- PMC_IMR : (PMC Offset: 0x6c) PMC Interrupt Mask Register -------- 
// -------- PMC_FSMR : (PMC Offset: 0x70) Fast Startup Mode Register -------- 
#define AT91C_PMC_FSTT            (0xFFFFUL <<  0)      // (PMC) Fast Start-up Input Enable 0 to 15
#define AT91C_PMC_RTTAL           (0x1UL << 16) // (PMC) RTT Alarm Enable
#define AT91C_PMC_RTCAL           (0x1UL << 17) // (PMC) RTC Alarm Enable
#define AT91C_PMC_USBAL           (0x1UL << 18) // (PMC) USB Alarm Enable
#define AT91C_PMC_LPM             (0x1UL << 20) // (PMC) Low Power Mode
// -------- PMC_FSPR : (PMC Offset: 0x74) Fast Startup Polarity Register -------- 
#define AT91C_PMC_FSTP            (0xFFFFUL <<  0)      // (PMC) Fast Start-up Input Polarity 0 to 15
// -------- PMC_FOCR : (PMC Offset: 0x78) Fault Output Clear Register -------- 
#define AT91C_PMC_FOCLR           (0x1UL <<  0) // (PMC) Fault Output Clear
// -------- PMC_PLLICPR : (PMC Offset: 0x80) PLL Charge Pump Current Register -------- 
#define AT91C_PMC_ICPPLLA         (0xFUL <<  0) // (PMC) PLLA charge pump current setting
#define 	AT91C_PMC_ICPPLLA_0                    (0x0UL)  // (PMC) 595-800 MHz
#define 	AT91C_PMC_ICPPLLA_1                    (0x1UL)  // (PMC) 395-600 MHz
#define AT91C_PMC_REALLOCK        (0x1UL <<  7) // (PMC) PLLs use real lock signals when 1
#define AT91C_PMC_IPLLA           (0xFUL <<  8) // (PMC) PLLA special setting
#define 	AT91C_PMC_IPLLA_0                    (0x0UL <<  8)      // (PMC) Internal LFT
#define 	AT91C_PMC_IPLLA_1                    (0x1UL <<  8)      // (PMC) External LFT
// -------- PMC_FEATURES : (PMC Offset: 0xf8)   -------- 
#define AT91C_PMC_CFGAHBCLK       (0x1UL <<  0) // (PMC)
#define 	AT91C_PMC_CFGAHBCLK_0                    (0x0UL)        // (PMC)
#define 	AT91C_PMC_CFGAHBCLK_1                    (0x1UL)        // (PMC)
#define AT91C_PMC_HCLKEN          (0x1UL <<  1) // (PMC)
#define 	AT91C_PMC_HCLKEN_0                    (0x0UL <<  1)     // (PMC)
#define 	AT91C_PMC_HCLKEN_1                    (0x1UL <<  1)     // (PMC)
#define AT91C_PMC_PERMCLK         (0x1UL <<  2) // (PMC)
#define 	AT91C_PMC_PERMCLK_0                    (0x0UL <<  2)    // (PMC)
#define 	AT91C_PMC_PERMCLK_1                    (0x1UL <<  2)    // (PMC)
#define AT91C_PMC_CORE2           (0x1UL <<  3) // (PMC)
#define 	AT91C_PMC_CORE2_0                    (0x0UL <<  3)      // (PMC)
#define 	AT91C_PMC_CORE2_1                    (0x1UL <<  3)      // (PMC)
#define AT91C_PMC_USBDEVCK        (0x1UL <<  4) // (PMC)
#define 	AT91C_PMC_USBDEVCK_0                    (0x0UL <<  4)   // (PMC)
#define 	AT91C_PMC_USBDEVCK_1                    (0x1UL <<  4)   // (PMC)
#define AT91C_PMC_USBHOSTCK       (0x1UL <<  5) // (PMC)
#define 	AT91C_PMC_USBHOSTCK_0                    (0x0UL <<  5)  // (PMC)
#define 	AT91C_PMC_USBHOSTCK_1                    (0x1UL <<  5)  // (PMC)
#define AT91C_PMC_USBOTGCK        (0x1UL <<  6) // (PMC)
#define 	AT91C_PMC_USBOTGCK_0                    (0x0UL <<  6)   // (PMC)
#define 	AT91C_PMC_USBOTGCK_1                    (0x1UL <<  6)   // (PMC)
#define AT91C_PMC_UHSYNRST        (0x1UL <<  7) // (PMC)
#define 	AT91C_PMC_UHSYNRST_0                    (0x0UL <<  7)   // (PMC)
#define 	AT91C_PMC_UHSYNRST_1                    (0x1UL <<  7)   // (PMC)
#define AT91C_PMC_UOSYNRST        (0x1UL <<  8) // (PMC)
#define 	AT91C_PMC_UOSYNRST_0                    (0x0UL <<  8)   // (PMC)
#define 	AT91C_PMC_UOSYNRST_1                    (0x1UL <<  8)   // (PMC)
#define AT91C_PMC_PLLENPOL        (0x1UL <<  9) // (PMC)
#define 	AT91C_PMC_PLLENPOL_0                    (0x0UL <<  9)   // (PMC)
#define 	AT91C_PMC_PLLENPOL_1                    (0x1UL <<  9)   // (PMC)
#define AT91C_PMC_BIASREG         (0x1UL << 10) // (PMC)
#define 	AT91C_PMC_BIASREG_0                    (0x0UL << 10)    // (PMC)
#define 	AT91C_PMC_BIASREG_1                    (0x1UL << 10)    // (PMC)
#define AT91C_PMC_OUTPLL          (0x1UL << 11) // (PMC)
#define 	AT91C_PMC_OUTPLL_0                    (0x0UL << 11)     // (PMC)
#define 	AT91C_PMC_OUTPLL_1                    (0x1UL << 11)     // (PMC)
#define AT91C_PMC_OUTCURR         (0x1UL << 12) // (PMC)
#define 	AT91C_PMC_OUTCURR_0                    (0x0UL << 12)    // (PMC)
#define 	AT91C_PMC_OUTCURR_1                    (0x1UL << 12)    // (PMC)
#define AT91C_PMC_FWUP            (0x1UL << 13) // (PMC)
#define 	AT91C_PMC_FWUP_0                    (0x0UL << 13)       // (PMC)
#define 	AT91C_PMC_FWUP_1                    (0x1UL << 13)       // (PMC)
#define AT91C_PMC_SELMAINCLK      (0x1UL << 14) // (PMC)
#define 	AT91C_PMC_SELMAINCLK_0                    (0x0UL << 14) // (PMC)
#define 	AT91C_PMC_SELMAINCLK_1                    (0x1UL << 14) // (PMC)
#define AT91C_PMC_RSTCLKM         (0x1UL << 15) // (PMC)
#define 	AT91C_PMC_RSTCLKM_0                    (0x0UL << 15)    // (PMC)
#define 	AT91C_PMC_RSTCLKM_1                    (0x1UL << 15)    // (PMC)
#define AT91C_PMC_NB_PERIPH_CLOCK (0xFFUL << 16)        // (PMC)
// -------- PMC_VERSION : (PMC Offset: 0xfc)   -------- 
#define AT91C_PMC_Version         (0xFFFFUL <<  0)      // (PMC)
#define 	AT91C_PMC_Version_0                    (0x0UL)  // (PMC)
#define 	AT91C_PMC_Version_1                    (0x1UL)  // (PMC)
#define AT91C_PMC_MFN             (0x7UL << 16) // (PMC)
#define 	AT91C_PMC_MFN_0                    (0x0UL << 16)        // (PMC)
#define 	AT91C_PMC_MFN_1                    (0x1UL << 16)        // (PMC)
// -------- PMC_PCR : (PMC Offset: 0x10c) Peripheral Control Register -------- 
#define AT91C_PMC_PID             (0x3FUL <<  0)        // (PMC) Peripheral Identifier
#define AT91C_PMC_CMD             (0x1UL << 12) // (PMC) Read / Write Command
#define AT91C_PMC_DIV             (0x3UL << 16) // (PMC) Peripheral clock Divider
#define AT91C_PMC_EN              (0x1UL << 28) // (PMC) Peripheral Clock Enable

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Clock Generator Controller
// *****************************************************************************
// *** Register offset in AT91S_CKGR structure ***
#define CKGR_UCKR       ( 0)    // UTMI Clock Configuration Register
#define CKGR_MOR        ( 4)    // Main Oscillator Register
#define CKGR_MCFR       ( 8)    // Main Clock Frequency Register
#define CKGR_PLLAR      (12)    // PLL A Register
#define CKGR_PLLBR      (16)    // PLL B Register
// -------- CKGR_UCKR : (CKGR Offset: 0x0) UTMI Clock Configuration Register -------- 
// -------- CKGR_MOR : (CKGR Offset: 0x4) Main Oscillator Register -------- 
// -------- CKGR_MCFR : (CKGR Offset: 0x8) Main Clock Frequency Register -------- 
// -------- CKGR_PLLAR : (CKGR Offset: 0xc) PLL A Register -------- 
// -------- CKGR_PLLBR : (CKGR Offset: 0x10) PLL B Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Reset Controller Interface
// *****************************************************************************
// *** Register offset in AT91S_RSTC structure ***
#define RSTC_RCR        ( 0)    // Reset Control Register
#define RSTC_RSR        ( 4)    // Reset Status Register
#define RSTC_RMR        ( 8)    // Reset Mode Register
#define RSTC_VER        (252)   // Version Register
// -------- RSTC_RCR : (RSTC Offset: 0x0) Reset Control Register -------- 
#define AT91C_RSTC_PROCRST        (0x1UL <<  0) // (RSTC) Processor Reset
#define AT91C_RSTC_ICERST         (0x1UL <<  1) // (RSTC) ICE Interface Reset
#define AT91C_RSTC_PERRST         (0x1UL <<  2) // (RSTC) Peripheral Reset
#define AT91C_RSTC_EXTRST         (0x1UL <<  3) // (RSTC) External Reset
#define AT91C_RSTC_KEY            (0xFFUL << 24)        // (RSTC) Password
// -------- RSTC_RSR : (RSTC Offset: 0x4) Reset Status Register -------- 
#define AT91C_RSTC_URSTS          (0x1UL <<  0) // (RSTC) User Reset Status
#define AT91C_RSTC_RSTTYP         (0x7UL <<  8) // (RSTC) Reset Type
#define 	AT91C_RSTC_RSTTYP_GENERAL              (0x0UL <<  8)    // (RSTC) General reset. Both VDDCORE and VDDBU rising.
#define 	AT91C_RSTC_RSTTYP_WAKEUP               (0x1UL <<  8)    // (RSTC) WakeUp Reset. VDDCORE rising.
#define 	AT91C_RSTC_RSTTYP_WATCHDOG             (0x2UL <<  8)    // (RSTC) Watchdog Reset. Watchdog overflow occured.
#define 	AT91C_RSTC_RSTTYP_SOFTWARE             (0x3UL <<  8)    // (RSTC) Software Reset. Processor reset required by the software.
#define 	AT91C_RSTC_RSTTYP_USER                 (0x4UL <<  8)    // (RSTC) User Reset. NRST pin detected low.
#define AT91C_RSTC_NRSTL          (0x1UL << 16) // (RSTC) NRST pin level
#define AT91C_RSTC_SRCMP          (0x1UL << 17) // (RSTC) Software Reset Command in Progress.
// -------- RSTC_RMR : (RSTC Offset: 0x8) Reset Mode Register -------- 
#define AT91C_RSTC_URSTEN         (0x1UL <<  0) // (RSTC) User Reset Enable
#define AT91C_RSTC_URSTIEN        (0x1UL <<  4) // (RSTC) User Reset Interrupt Enable
#define AT91C_RSTC_ERSTL          (0xFUL <<  8) // (RSTC) User Reset Enable

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Shut Down Controller Interface
// *****************************************************************************
// *** Register offset in AT91S_SHDWC structure ***
#define SHDWC_SHCR      ( 0)    // Shut Down Control Register
#define SHDWC_SHMR      ( 4)    // Shut Down Mode Register
#define SHDWC_SHSR      ( 8)    // Shut Down Status Register
// -------- SHDWC_SHCR : (SHDWC Offset: 0x0) Shut Down Control Register -------- 
#define AT91C_SHDWC_SHDW          (0x1UL <<  0) // (SHDWC) Processor Reset
#define AT91C_SHDWC_KEY           (0xFFUL << 24)        // (SHDWC) Shut down KEY Password
// -------- SHDWC_SHMR : (SHDWC Offset: 0x4) Shut Down Mode Register -------- 
#define AT91C_SHDWC_WKMODE0       (0x3UL <<  0) // (SHDWC) Wake Up 0 Mode Selection
#define 	AT91C_SHDWC_WKMODE0_NONE                 (0x0UL)        // (SHDWC) None. No detection is performed on the wake up input.
#define 	AT91C_SHDWC_WKMODE0_HIGH                 (0x1UL)        // (SHDWC) High Level.
#define 	AT91C_SHDWC_WKMODE0_LOW                  (0x2UL)        // (SHDWC) Low Level.
#define 	AT91C_SHDWC_WKMODE0_ANYLEVEL             (0x3UL)        // (SHDWC) Any level change.
#define AT91C_SHDWC_CPTWK0        (0xFUL <<  4) // (SHDWC) Counter On Wake Up 0
#define AT91C_SHDWC_WKMODE1       (0x3UL <<  8) // (SHDWC) Wake Up 1 Mode Selection
#define 	AT91C_SHDWC_WKMODE1_NONE                 (0x0UL <<  8)  // (SHDWC) None. No detection is performed on the wake up input.
#define 	AT91C_SHDWC_WKMODE1_HIGH                 (0x1UL <<  8)  // (SHDWC) High Level.
#define 	AT91C_SHDWC_WKMODE1_LOW                  (0x2UL <<  8)  // (SHDWC) Low Level.
#define 	AT91C_SHDWC_WKMODE1_ANYLEVEL             (0x3UL <<  8)  // (SHDWC) Any level change.
#define AT91C_SHDWC_CPTWK1        (0xFUL << 12) // (SHDWC) Counter On Wake Up 1
#define AT91C_SHDWC_RTTWKEN       (0x1UL << 16) // (SHDWC) Real Time Timer Wake Up Enable
#define AT91C_SHDWC_RTCWKEN       (0x1UL << 17) // (SHDWC) Real Time Clock Wake Up Enable
// -------- SHDWC_SHSR : (SHDWC Offset: 0x8) Shut Down Status Register -------- 
#define AT91C_SHDWC_WAKEUP0       (0x1UL <<  0) // (SHDWC) Wake Up 0 Status
#define AT91C_SHDWC_WAKEUP1       (0x1UL <<  1) // (SHDWC) Wake Up 1 Status
#define AT91C_SHDWC_FWKUP         (0x1UL <<  2) // (SHDWC) Force Wake Up Status
#define AT91C_SHDWC_RTTWK         (0x1UL << 16) // (SHDWC) Real Time Timer wake Up
#define AT91C_SHDWC_RTCWK         (0x1UL << 17) // (SHDWC) Real Time Clock wake Up

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Real Time Timer Controller Interface
// *****************************************************************************
// *** Register offset in AT91S_RTTC structure ***
#define RTTC_RTMR       ( 0)    // Real-time Mode Register
#define RTTC_RTAR       ( 4)    // Real-time Alarm Register
#define RTTC_RTVR       ( 8)    // Real-time Value Register
#define RTTC_RTSR       (12)    // Real-time Status Register
// -------- RTTC_RTMR : (RTTC Offset: 0x0) Real-time Mode Register -------- 
#define AT91C_RTTC_RTPRES         (0xFFFFUL <<  0)      // (RTTC) Real-time Timer Prescaler Value
#define AT91C_RTTC_ALMIEN         (0x1UL << 16) // (RTTC) Alarm Interrupt Enable
#define AT91C_RTTC_RTTINCIEN      (0x1UL << 17) // (RTTC) Real Time Timer Increment Interrupt Enable
#define AT91C_RTTC_RTTRST         (0x1UL << 18) // (RTTC) Real Time Timer Restart
// -------- RTTC_RTAR : (RTTC Offset: 0x4) Real-time Alarm Register -------- 
#define AT91C_RTTC_ALMV           (0x0UL <<  0) // (RTTC) Alarm Value
// -------- RTTC_RTVR : (RTTC Offset: 0x8) Current Real-time Value Register -------- 
#define AT91C_RTTC_CRTV           (0x0UL <<  0) // (RTTC) Current Real-time Value
// -------- RTTC_RTSR : (RTTC Offset: 0xc) Real-time Status Register -------- 
#define AT91C_RTTC_ALMS           (0x1UL <<  0) // (RTTC) Real-time Alarm Status
#define AT91C_RTTC_RTTINC         (0x1UL <<  1) // (RTTC) Real-time Timer Increment

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Periodic Interval Timer Controller Interface
// *****************************************************************************
// *** Register offset in AT91S_PITC structure ***
#define PITC_PIMR       ( 0)    // Period Interval Mode Register
#define PITC_PISR       ( 4)    // Period Interval Status Register
#define PITC_PIVR       ( 8)    // Period Interval Value Register
#define PITC_PIIR       (12)    // Period Interval Image Register
// -------- PITC_PIMR : (PITC Offset: 0x0) Periodic Interval Mode Register -------- 
#define AT91C_PITC_PIV            (0xFFFFFUL <<  0)     // (PITC) Periodic Interval Value
#define AT91C_PITC_PITEN          (0x1UL << 24) // (PITC) Periodic Interval Timer Enabled
#define AT91C_PITC_PITIEN         (0x1UL << 25) // (PITC) Periodic Interval Timer Interrupt Enable
// -------- PITC_PISR : (PITC Offset: 0x4) Periodic Interval Status Register -------- 
#define AT91C_PITC_PITS           (0x1UL <<  0) // (PITC) Periodic Interval Timer Status
// -------- PITC_PIVR : (PITC Offset: 0x8) Periodic Interval Value Register -------- 
#define AT91C_PITC_CPIV           (0xFFFFFUL <<  0)     // (PITC) Current Periodic Interval Value
#define AT91C_PITC_PICNT          (0xFFFUL << 20)       // (PITC) Periodic Interval Counter
// -------- PITC_PIIR : (PITC Offset: 0xc) Periodic Interval Image Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Watchdog Timer Controller Interface
// *****************************************************************************
// *** Register offset in AT91S_WDTC structure ***
#define WDTC_WDCR       ( 0)    // Watchdog Control Register
#define WDTC_WDMR       ( 4)    // Watchdog Mode Register
#define WDTC_WDSR       ( 8)    // Watchdog Status Register
// -------- WDTC_WDCR : (WDTC Offset: 0x0) Periodic Interval Image Register -------- 
#define AT91C_WDTC_WDRSTT         (0x1UL <<  0) // (WDTC) Watchdog Restart
#define AT91C_WDTC_KEY            (0xFFUL << 24)        // (WDTC) Watchdog KEY Password
// -------- WDTC_WDMR : (WDTC Offset: 0x4) Watchdog Mode Register -------- 
#define AT91C_WDTC_WDV            (0xFFFUL <<  0)       // (WDTC) Watchdog Timer Restart
#define AT91C_WDTC_WDFIEN         (0x1UL << 12) // (WDTC) Watchdog Fault Interrupt Enable
#define AT91C_WDTC_WDRSTEN        (0x1UL << 13) // (WDTC) Watchdog Reset Enable
#define AT91C_WDTC_WDRPROC        (0x1UL << 14) // (WDTC) Watchdog Timer Restart
#define AT91C_WDTC_WDDIS          (0x1UL << 15) // (WDTC) Watchdog Disable
#define AT91C_WDTC_WDD            (0xFFFUL << 16)       // (WDTC) Watchdog Delta Value
#define AT91C_WDTC_WDDBGHLT       (0x1UL << 28) // (WDTC) Watchdog Debug Halt
#define AT91C_WDTC_WDIDLEHLT      (0x1UL << 29) // (WDTC) Watchdog Idle Halt
// -------- WDTC_WDSR : (WDTC Offset: 0x8) Watchdog Status Register -------- 
#define AT91C_WDTC_WDUNF          (0x1UL <<  0) // (WDTC) Watchdog Underflow
#define AT91C_WDTC_WDERR          (0x1UL <<  1) // (WDTC) Watchdog Error

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Real-time Clock Alarm and Parallel Load Interface
// *****************************************************************************
// *** Register offset in AT91S_RTC structure ***
#define RTC_CR          ( 0)    // Control Register
#define RTC_MR          ( 4)    // Mode Register
#define RTC_TIMR        ( 8)    // Time Register
#define RTC_CALR        (12)    // Calendar Register
#define RTC_TIMALR      (16)    // Time Alarm Register
#define RTC_CALALR      (20)    // Calendar Alarm Register
#define RTC_SR          (24)    // Status Register
#define RTC_SCCR        (28)    // Status Clear Command Register
#define RTC_IER         (32)    // Interrupt Enable Register
#define RTC_IDR         (36)    // Interrupt Disable Register
#define RTC_IMR         (40)    // Interrupt Mask Register
#define RTC_VER         (44)    // Valid Entry Register
// -------- RTC_CR : (RTC Offset: 0x0) RTC Control Register -------- 
#define AT91C_RTC_UPDTIM          (0x1UL <<  0) // (RTC) Update Request Time Register
#define AT91C_RTC_UPDCAL          (0x1UL <<  1) // (RTC) Update Request Calendar Register
#define AT91C_RTC_TIMEVSEL        (0x3UL <<  8) // (RTC) Time Event Selection
#define 	AT91C_RTC_TIMEVSEL_MINUTE               (0x0UL <<  8)   // (RTC) Minute change.
#define 	AT91C_RTC_TIMEVSEL_HOUR                 (0x1UL <<  8)   // (RTC) Hour change.
#define 	AT91C_RTC_TIMEVSEL_DAY24                (0x2UL <<  8)   // (RTC) Every day at midnight.
#define 	AT91C_RTC_TIMEVSEL_DAY12                (0x3UL <<  8)   // (RTC) Every day at noon.
#define AT91C_RTC_CALEVSEL        (0x3UL << 16) // (RTC) Calendar Event Selection
#define 	AT91C_RTC_CALEVSEL_WEEK                 (0x0UL << 16)   // (RTC) Week change (every Monday at time 00:00:00).
#define 	AT91C_RTC_CALEVSEL_MONTH                (0x1UL << 16)   // (RTC) Month change (every 01 of each month at time 00:00:00).
#define 	AT91C_RTC_CALEVSEL_YEAR                 (0x2UL << 16)   // (RTC) Year change (every January 1 at time 00:00:00).
// -------- RTC_MR : (RTC Offset: 0x4) RTC Mode Register -------- 
#define AT91C_RTC_HRMOD           (0x1UL <<  0) // (RTC) 12-24 hour Mode
// -------- RTC_TIMR : (RTC Offset: 0x8) RTC Time Register -------- 
#define AT91C_RTC_SEC             (0x7FUL <<  0)        // (RTC) Current Second
#define AT91C_RTC_MIN             (0x7FUL <<  8)        // (RTC) Current Minute
#define AT91C_RTC_HOUR            (0x3FUL << 16)        // (RTC) Current Hour
#define AT91C_RTC_AMPM            (0x1UL << 22) // (RTC) Ante Meridiem, Post Meridiem Indicator
// -------- RTC_CALR : (RTC Offset: 0xc) RTC Calendar Register -------- 
#define AT91C_RTC_CENT            (0x3FUL <<  0)        // (RTC) Current Century
#define AT91C_RTC_YEAR            (0xFFUL <<  8)        // (RTC) Current Year
#define AT91C_RTC_MONTH           (0x1FUL << 16)        // (RTC) Current Month
#define AT91C_RTC_DAY             (0x7UL << 21) // (RTC) Current Day
#define AT91C_RTC_DATE            (0x3FUL << 24)        // (RTC) Current Date
// -------- RTC_TIMALR : (RTC Offset: 0x10) RTC Time Alarm Register -------- 
#define AT91C_RTC_SECEN           (0x1UL <<  7) // (RTC) Second Alarm Enable
#define AT91C_RTC_MINEN           (0x1UL << 15) // (RTC) Minute Alarm
#define AT91C_RTC_HOUREN          (0x1UL << 23) // (RTC) Current Hour
// -------- RTC_CALALR : (RTC Offset: 0x14) RTC Calendar Alarm Register -------- 
#define AT91C_RTC_MONTHEN         (0x1UL << 23) // (RTC) Month Alarm Enable
#define AT91C_RTC_DATEEN          (0x1UL << 31) // (RTC) Date Alarm Enable
// -------- RTC_SR : (RTC Offset: 0x18) RTC Status Register -------- 
#define AT91C_RTC_ACKUPD          (0x1UL <<  0) // (RTC) Acknowledge for Update
#define AT91C_RTC_ALARM           (0x1UL <<  1) // (RTC) Alarm Flag
#define AT91C_RTC_SECEV           (0x1UL <<  2) // (RTC) Second Event
#define AT91C_RTC_TIMEV           (0x1UL <<  3) // (RTC) Time Event
#define AT91C_RTC_CALEV           (0x1UL <<  4) // (RTC) Calendar event
// -------- RTC_SCCR : (RTC Offset: 0x1c) RTC Status Clear Command Register -------- 
// -------- RTC_IER : (RTC Offset: 0x20) RTC Interrupt Enable Register -------- 
// -------- RTC_IDR : (RTC Offset: 0x24) RTC Interrupt Disable Register -------- 
// -------- RTC_IMR : (RTC Offset: 0x28) RTC Interrupt Mask Register -------- 
// -------- RTC_VER : (RTC Offset: 0x2c) RTC Valid Entry Register -------- 
#define AT91C_RTC_NVTIM           (0x1UL <<  0) // (RTC) Non valid Time
#define AT91C_RTC_NVCAL           (0x1UL <<  1) // (RTC) Non valid Calendar
#define AT91C_RTC_NVTIMALR        (0x1UL <<  2) // (RTC) Non valid time Alarm
#define AT91C_RTC_NVCALALR        (0x1UL <<  3) // (RTC) Nonvalid Calendar Alarm

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Timer Counter Channel Interface
// *****************************************************************************
// *** Register offset in AT91S_TC structure ***
#define TC_CCR          ( 0)    // Channel Control Register
#define TC_CMR          ( 4)    // Channel Mode Register (Capture Mode / Waveform Mode)
#define TC_CV           (16)    // Counter Value
#define TC_RA           (20)    // Register A
#define TC_RB           (24)    // Register B
#define TC_RC           (28)    // Register C
#define TC_SR           (32)    // Status Register
#define TC_IER          (36)    // Interrupt Enable Register
#define TC_IDR          (40)    // Interrupt Disable Register
#define TC_IMR          (44)    // Interrupt Mask Register
// -------- TC_CCR : (TC Offset: 0x0) TC Channel Control Register -------- 
#define AT91C_TC_CLKEN            (0x1UL <<  0) // (TC) Counter Clock Enable Command
#define AT91C_TC_CLKDIS           (0x1UL <<  1) // (TC) Counter Clock Disable Command
#define AT91C_TC_SWTRG            (0x1UL <<  2) // (TC) Software Trigger Command
// -------- TC_CMR : (TC Offset: 0x4) TC Channel Mode Register: Capture Mode / Waveform Mode -------- 
#define AT91C_TC_CLKS             (0x7UL <<  0) // (TC) Clock Selection
#define 	AT91C_TC_CLKS_TIMER_DIV1_CLOCK     (0x0UL)      // (TC) Clock selected: TIMER_DIV1_CLOCK
#define 	AT91C_TC_CLKS_TIMER_DIV2_CLOCK     (0x1UL)      // (TC) Clock selected: TIMER_DIV2_CLOCK
#define 	AT91C_TC_CLKS_TIMER_DIV3_CLOCK     (0x2UL)      // (TC) Clock selected: TIMER_DIV3_CLOCK
#define 	AT91C_TC_CLKS_TIMER_DIV4_CLOCK     (0x3UL)      // (TC) Clock selected: TIMER_DIV4_CLOCK
#define 	AT91C_TC_CLKS_TIMER_DIV5_CLOCK     (0x4UL)      // (TC) Clock selected: TIMER_DIV5_CLOCK
#define 	AT91C_TC_CLKS_XC0                  (0x5UL)      // (TC) Clock selected: XC0
#define 	AT91C_TC_CLKS_XC1                  (0x6UL)      // (TC) Clock selected: XC1
#define 	AT91C_TC_CLKS_XC2                  (0x7UL)      // (TC) Clock selected: XC2
#define AT91C_TC_CLKI             (0x1UL <<  3) // (TC) Clock Invert
#define AT91C_TC_BURST            (0x3UL <<  4) // (TC) Burst Signal Selection
#define 	AT91C_TC_BURST_NONE                 (0x0UL <<  4)       // (TC) The clock is not gated by an external signal
#define 	AT91C_TC_BURST_XC0                  (0x1UL <<  4)       // (TC) XC0 is ANDed with the selected clock
#define 	AT91C_TC_BURST_XC1                  (0x2UL <<  4)       // (TC) XC1 is ANDed with the selected clock
#define 	AT91C_TC_BURST_XC2                  (0x3UL <<  4)       // (TC) XC2 is ANDed with the selected clock
#define AT91C_TC_CPCSTOP          (0x1UL <<  6) // (TC) Counter Clock Stopped with RC Compare
#define AT91C_TC_LDBSTOP          (0x1UL <<  6) // (TC) Counter Clock Stopped with RB Loading
#define AT91C_TC_CPCDIS           (0x1UL <<  7) // (TC) Counter Clock Disable with RC Compare
#define AT91C_TC_LDBDIS           (0x1UL <<  7) // (TC) Counter Clock Disabled with RB Loading
#define AT91C_TC_ETRGEDG          (0x3UL <<  8) // (TC) External Trigger Edge Selection
#define 	AT91C_TC_ETRGEDG_NONE                 (0x0UL <<  8)     // (TC) Edge: None
#define 	AT91C_TC_ETRGEDG_RISING               (0x1UL <<  8)     // (TC) Edge: rising edge
#define 	AT91C_TC_ETRGEDG_FALLING              (0x2UL <<  8)     // (TC) Edge: falling edge
#define 	AT91C_TC_ETRGEDG_BOTH                 (0x3UL <<  8)     // (TC) Edge: each edge
#define AT91C_TC_EEVTEDG          (0x3UL <<  8) // (TC) External Event Edge Selection
#define 	AT91C_TC_EEVTEDG_NONE                 (0x0UL <<  8)     // (TC) Edge: None
#define 	AT91C_TC_EEVTEDG_RISING               (0x1UL <<  8)     // (TC) Edge: rising edge
#define 	AT91C_TC_EEVTEDG_FALLING              (0x2UL <<  8)     // (TC) Edge: falling edge
#define 	AT91C_TC_EEVTEDG_BOTH                 (0x3UL <<  8)     // (TC) Edge: each edge
#define AT91C_TC_EEVT             (0x3UL << 10) // (TC) External Event  Selection
#define 	AT91C_TC_EEVT_TIOB                 (0x0UL << 10)        // (TC) Signal selected as external event: TIOB TIOB direction: input
#define 	AT91C_TC_EEVT_XC0                  (0x1UL << 10)        // (TC) Signal selected as external event: XC0 TIOB direction: output
#define 	AT91C_TC_EEVT_XC1                  (0x2UL << 10)        // (TC) Signal selected as external event: XC1 TIOB direction: output
#define 	AT91C_TC_EEVT_XC2                  (0x3UL << 10)        // (TC) Signal selected as external event: XC2 TIOB direction: output
#define AT91C_TC_ABETRG           (0x1UL << 10) // (TC) TIOA or TIOB External Trigger Selection
#define AT91C_TC_ENETRG           (0x1UL << 12) // (TC) External Event Trigger enable
#define AT91C_TC_WAVESEL          (0x3UL << 13) // (TC) Waveform  Selection
#define 	AT91C_TC_WAVESEL_UP                   (0x0UL << 13)     // (TC) UP mode without atomatic trigger on RC Compare
#define 	AT91C_TC_WAVESEL_UPDOWN               (0x1UL << 13)     // (TC) UPDOWN mode without automatic trigger on RC Compare
#define 	AT91C_TC_WAVESEL_UP_AUTO              (0x2UL << 13)     // (TC) UP mode with automatic trigger on RC Compare
#define 	AT91C_TC_WAVESEL_UPDOWN_AUTO          (0x3UL << 13)     // (TC) UPDOWN mode with automatic trigger on RC Compare
#define AT91C_TC_CPCTRG           (0x1UL << 14) // (TC) RC Compare Trigger Enable
#define AT91C_TC_WAVE             (0x1UL << 15) // (TC)
#define AT91C_TC_ACPA             (0x3UL << 16) // (TC) RA Compare Effect on TIOA
#define 	AT91C_TC_ACPA_NONE                 (0x0UL << 16)        // (TC) Effect: none
#define 	AT91C_TC_ACPA_SET                  (0x1UL << 16)        // (TC) Effect: set
#define 	AT91C_TC_ACPA_CLEAR                (0x2UL << 16)        // (TC) Effect: clear
#define 	AT91C_TC_ACPA_TOGGLE               (0x3UL << 16)        // (TC) Effect: toggle
#define AT91C_TC_LDRA             (0x3UL << 16) // (TC) RA Loading Selection
#define 	AT91C_TC_LDRA_NONE                 (0x0UL << 16)        // (TC) Edge: None
#define 	AT91C_TC_LDRA_RISING               (0x1UL << 16)        // (TC) Edge: rising edge of TIOA
#define 	AT91C_TC_LDRA_FALLING              (0x2UL << 16)        // (TC) Edge: falling edge of TIOA
#define 	AT91C_TC_LDRA_BOTH                 (0x3UL << 16)        // (TC) Edge: each edge of TIOA
#define AT91C_TC_ACPC             (0x3UL << 18) // (TC) RC Compare Effect on TIOA
#define 	AT91C_TC_ACPC_NONE                 (0x0UL << 18)        // (TC) Effect: none
#define 	AT91C_TC_ACPC_SET                  (0x1UL << 18)        // (TC) Effect: set
#define 	AT91C_TC_ACPC_CLEAR                (0x2UL << 18)        // (TC) Effect: clear
#define 	AT91C_TC_ACPC_TOGGLE               (0x3UL << 18)        // (TC) Effect: toggle
#define AT91C_TC_LDRB             (0x3UL << 18) // (TC) RB Loading Selection
#define 	AT91C_TC_LDRB_NONE                 (0x0UL << 18)        // (TC) Edge: None
#define 	AT91C_TC_LDRB_RISING               (0x1UL << 18)        // (TC) Edge: rising edge of TIOA
#define 	AT91C_TC_LDRB_FALLING              (0x2UL << 18)        // (TC) Edge: falling edge of TIOA
#define 	AT91C_TC_LDRB_BOTH                 (0x3UL << 18)        // (TC) Edge: each edge of TIOA
#define AT91C_TC_AEEVT            (0x3UL << 20) // (TC) External Event Effect on TIOA
#define 	AT91C_TC_AEEVT_NONE                 (0x0UL << 20)       // (TC) Effect: none
#define 	AT91C_TC_AEEVT_SET                  (0x1UL << 20)       // (TC) Effect: set
#define 	AT91C_TC_AEEVT_CLEAR                (0x2UL << 20)       // (TC) Effect: clear
#define 	AT91C_TC_AEEVT_TOGGLE               (0x3UL << 20)       // (TC) Effect: toggle
#define AT91C_TC_ASWTRG           (0x3UL << 22) // (TC) Software Trigger Effect on TIOA
#define 	AT91C_TC_ASWTRG_NONE                 (0x0UL << 22)      // (TC) Effect: none
#define 	AT91C_TC_ASWTRG_SET                  (0x1UL << 22)      // (TC) Effect: set
#define 	AT91C_TC_ASWTRG_CLEAR                (0x2UL << 22)      // (TC) Effect: clear
#define 	AT91C_TC_ASWTRG_TOGGLE               (0x3UL << 22)      // (TC) Effect: toggle
#define AT91C_TC_BCPB             (0x3UL << 24) // (TC) RB Compare Effect on TIOB
#define 	AT91C_TC_BCPB_NONE                 (0x0UL << 24)        // (TC) Effect: none
#define 	AT91C_TC_BCPB_SET                  (0x1UL << 24)        // (TC) Effect: set
#define 	AT91C_TC_BCPB_CLEAR                (0x2UL << 24)        // (TC) Effect: clear
#define 	AT91C_TC_BCPB_TOGGLE               (0x3UL << 24)        // (TC) Effect: toggle
#define AT91C_TC_BCPC             (0x3UL << 26) // (TC) RC Compare Effect on TIOB
#define 	AT91C_TC_BCPC_NONE                 (0x0UL << 26)        // (TC) Effect: none
#define 	AT91C_TC_BCPC_SET                  (0x1UL << 26)        // (TC) Effect: set
#define 	AT91C_TC_BCPC_CLEAR                (0x2UL << 26)        // (TC) Effect: clear
#define 	AT91C_TC_BCPC_TOGGLE               (0x3UL << 26)        // (TC) Effect: toggle
#define AT91C_TC_BEEVT            (0x3UL << 28) // (TC) External Event Effect on TIOB
#define 	AT91C_TC_BEEVT_NONE                 (0x0UL << 28)       // (TC) Effect: none
#define 	AT91C_TC_BEEVT_SET                  (0x1UL << 28)       // (TC) Effect: set
#define 	AT91C_TC_BEEVT_CLEAR                (0x2UL << 28)       // (TC) Effect: clear
#define 	AT91C_TC_BEEVT_TOGGLE               (0x3UL << 28)       // (TC) Effect: toggle
#define AT91C_TC_BSWTRG           (0x3UL << 30) // (TC) Software Trigger Effect on TIOB
#define 	AT91C_TC_BSWTRG_NONE                 (0x0UL << 30)      // (TC) Effect: none
#define 	AT91C_TC_BSWTRG_SET                  (0x1UL << 30)      // (TC) Effect: set
#define 	AT91C_TC_BSWTRG_CLEAR                (0x2UL << 30)      // (TC) Effect: clear
#define 	AT91C_TC_BSWTRG_TOGGLE               (0x3UL << 30)      // (TC) Effect: toggle
// -------- TC_SR : (TC Offset: 0x20) TC Channel Status Register -------- 
#define AT91C_TC_COVFS            (0x1UL <<  0) // (TC) Counter Overflow
#define AT91C_TC_LOVRS            (0x1UL <<  1) // (TC) Load Overrun
#define AT91C_TC_CPAS             (0x1UL <<  2) // (TC) RA Compare
#define AT91C_TC_CPBS             (0x1UL <<  3) // (TC) RB Compare
#define AT91C_TC_CPCS             (0x1UL <<  4) // (TC) RC Compare
#define AT91C_TC_LDRAS            (0x1UL <<  5) // (TC) RA Loading
#define AT91C_TC_LDRBS            (0x1UL <<  6) // (TC) RB Loading
#define AT91C_TC_ETRGS            (0x1UL <<  7) // (TC) External Trigger
#define AT91C_TC_CLKSTA           (0x1UL << 16) // (TC) Clock Enabling
#define AT91C_TC_MTIOA            (0x1UL << 17) // (TC) TIOA Mirror
#define AT91C_TC_MTIOB            (0x1UL << 18) // (TC) TIOA Mirror
// -------- TC_IER : (TC Offset: 0x24) TC Channel Interrupt Enable Register -------- 
// -------- TC_IDR : (TC Offset: 0x28) TC Channel Interrupt Disable Register -------- 
// -------- TC_IMR : (TC Offset: 0x2c) TC Channel Interrupt Mask Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Timer Counter Interface
// *****************************************************************************
// *** Register offset in AT91S_TCB structure ***
#define TCB_TC0         ( 0)    // TC Channel 0
#define TCB_TC1         (64)    // TC Channel 1
#define TCB_TC2         (128)   // TC Channel 2
#define TCB_BCR         (192)   // TC Block Control Register
#define TCB_BMR         (196)   // TC Block Mode Register
#define TCB_ADDRSIZE    (236)   // TC ADDRSIZE REGISTER
#define TCB_IPNAME1     (240)   // TC IPNAME1 REGISTER
#define TCB_IPNAME2     (244)   // TC IPNAME2 REGISTER
#define TCB_FEATURES    (248)   // TC FEATURES REGISTER
#define TCB_VER         (252)   //  Version Register
// -------- TCB_BCR : (TCB Offset: 0xc0) TC Block Control Register -------- 
#define AT91C_TCB_SYNC            (0x1UL <<  0) // (TCB) Synchro Command
// -------- TCB_BMR : (TCB Offset: 0xc4) TC Block Mode Register -------- 
#define AT91C_TCB_TC0XC0S         (0x3UL <<  0) // (TCB) External Clock Signal 0 Selection
#define 	AT91C_TCB_TC0XC0S_TCLK0                (0x0UL)  // (TCB) TCLK0 connected to XC0
#define 	AT91C_TCB_TC0XC0S_NONE                 (0x1UL)  // (TCB) None signal connected to XC0
#define 	AT91C_TCB_TC0XC0S_TIOA1                (0x2UL)  // (TCB) TIOA1 connected to XC0
#define 	AT91C_TCB_TC0XC0S_TIOA2                (0x3UL)  // (TCB) TIOA2 connected to XC0
#define AT91C_TCB_TC1XC1S         (0x3UL <<  2) // (TCB) External Clock Signal 1 Selection
#define 	AT91C_TCB_TC1XC1S_TCLK1                (0x0UL <<  2)    // (TCB) TCLK1 connected to XC1
#define 	AT91C_TCB_TC1XC1S_NONE                 (0x1UL <<  2)    // (TCB) None signal connected to XC1
#define 	AT91C_TCB_TC1XC1S_TIOA0                (0x2UL <<  2)    // (TCB) TIOA0 connected to XC1
#define 	AT91C_TCB_TC1XC1S_TIOA2                (0x3UL <<  2)    // (TCB) TIOA2 connected to XC1
#define AT91C_TCB_TC2XC2S         (0x3UL <<  4) // (TCB) External Clock Signal 2 Selection
#define 	AT91C_TCB_TC2XC2S_TCLK2                (0x0UL <<  4)    // (TCB) TCLK2 connected to XC2
#define 	AT91C_TCB_TC2XC2S_NONE                 (0x1UL <<  4)    // (TCB) None signal connected to XC2
#define 	AT91C_TCB_TC2XC2S_TIOA0                (0x2UL <<  4)    // (TCB) TIOA0 connected to XC2
#define 	AT91C_TCB_TC2XC2S_TIOA1                (0x3UL <<  4)    // (TCB) TIOA2 connected to XC2

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Multimedia Card Interface
// *****************************************************************************
// *** Register offset in AT91S_MCI structure ***
#define MCI_CR          ( 0)    // MCI Control Register
#define MCI_MR          ( 4)    // MCI Mode Register
#define MCI_DTOR        ( 8)    // MCI Data Timeout Register
#define MCI_SDCR        (12)    // MCI SD/SDIO Card Register
#define MCI_ARGR        (16)    // MCI Argument Register
#define MCI_CMDR        (20)    // MCI Command Register
#define MCI_BLKR        (24)    // MCI Block Register
#define MCI_CSTOR       (28)    // MCI Completion Signal Timeout Register
#define MCI_RSPR        (32)    // MCI Response Register
#define MCI_RDR         (48)    // MCI Receive Data Register
#define MCI_TDR         (52)    // MCI Transmit Data Register
#define MCI_SR          (64)    // MCI Status Register
#define MCI_IER         (68)    // MCI Interrupt Enable Register
#define MCI_IDR         (72)    // MCI Interrupt Disable Register
#define MCI_IMR         (76)    // MCI Interrupt Mask Register
#define MCI_DMA         (80)    // MCI DMA Configuration Register
#define MCI_CFG         (84)    // MCI Configuration Register
#define MCI_WPCR        (228)   // MCI Write Protection Control Register
#define MCI_WPSR        (232)   // MCI Write Protection Status Register
#define MCI_ADDRSIZE    (236)   // MCI ADDRSIZE REGISTER
#define MCI_IPNAME1     (240)   // MCI IPNAME1 REGISTER
#define MCI_IPNAME2     (244)   // MCI IPNAME2 REGISTER
#define MCI_FEATURES    (248)   // MCI FEATURES REGISTER
#define MCI_VER         (252)   // MCI VERSION REGISTER
#define MCI_FIFO        (512)   // MCI FIFO Aperture Register
// -------- MCI_CR : (MCI Offset: 0x0) MCI Control Register -------- 
#define AT91C_MCI_MCIEN           (0x1UL <<  0) // (MCI) Multimedia Interface Enable
#define 	AT91C_MCI_MCIEN_0                    (0x0UL)    // (MCI) No effect
#define 	AT91C_MCI_MCIEN_1                    (0x1UL)    // (MCI) Enable the MultiMedia Interface if MCIDIS is 0
#define AT91C_MCI_MCIDIS          (0x1UL <<  1) // (MCI) Multimedia Interface Disable
#define 	AT91C_MCI_MCIDIS_0                    (0x0UL <<  1)     // (MCI) No effect
#define 	AT91C_MCI_MCIDIS_1                    (0x1UL <<  1)     // (MCI) Disable the MultiMedia Interface
#define AT91C_MCI_PWSEN           (0x1UL <<  2) // (MCI) Power Save Mode Enable
#define 	AT91C_MCI_PWSEN_0                    (0x0UL <<  2)      // (MCI) No effect
#define 	AT91C_MCI_PWSEN_1                    (0x1UL <<  2)      // (MCI) Enable the Power-saving mode if PWSDIS is 0.
#define AT91C_MCI_PWSDIS          (0x1UL <<  3) // (MCI) Power Save Mode Disable
#define 	AT91C_MCI_PWSDIS_0                    (0x0UL <<  3)     // (MCI) No effect
#define 	AT91C_MCI_PWSDIS_1                    (0x1UL <<  3)     // (MCI) Disable the Power-saving mode.
#define AT91C_MCI_IOWAITEN        (0x1UL <<  4) // (MCI) SDIO Read Wait Enable
#define 	AT91C_MCI_IOWAITEN_0                    (0x0UL <<  4)   // (MCI) No effect
#define 	AT91C_MCI_IOWAITEN_1                    (0x1UL <<  4)   // (MCI) Enables the SDIO Read Wait Operation.
#define AT91C_MCI_IOWAITDIS       (0x1UL <<  5) // (MCI) SDIO Read Wait Disable
#define 	AT91C_MCI_IOWAITDIS_0                    (0x0UL <<  5)  // (MCI) No effect
#define 	AT91C_MCI_IOWAITDIS_1                    (0x1UL <<  5)  // (MCI) Disables the SDIO Read Wait Operation.
#define AT91C_MCI_SWRST           (0x1UL <<  7) // (MCI) MCI Software reset
#define 	AT91C_MCI_SWRST_0                    (0x0UL <<  7)      // (MCI) No effect
#define 	AT91C_MCI_SWRST_1                    (0x1UL <<  7)      // (MCI) Resets the MCI
// -------- MCI_MR : (MCI Offset: 0x4) MCI Mode Register -------- 
#define AT91C_MCI_CLKDIV          (0xFFUL <<  0)        // (MCI) Clock Divider
#define AT91C_MCI_PWSDIV          (0x7UL <<  8) // (MCI) Power Saving Divider
#define AT91C_MCI_RDPROOF         (0x1UL << 11) // (MCI) Read Proof Enable
#define 	AT91C_MCI_RDPROOF_DISABLE              (0x0UL << 11)    // (MCI) Disables Read Proof
#define 	AT91C_MCI_RDPROOF_ENABLE               (0x1UL << 11)    // (MCI) Enables Read Proof
#define AT91C_MCI_WRPROOF         (0x1UL << 12) // (MCI) Write Proof Enable
#define 	AT91C_MCI_WRPROOF_DISABLE              (0x0UL << 12)    // (MCI) Disables Write Proof
#define 	AT91C_MCI_WRPROOF_ENABLE               (0x1UL << 12)    // (MCI) Enables Write Proof
#define AT91C_MCI_PDCFBYTE        (0x1UL << 13) // (MCI) PDC Force Byte Transfer
#define 	AT91C_MCI_PDCFBYTE_DISABLE              (0x0UL << 13)   // (MCI) Disables PDC Force Byte Transfer
#define 	AT91C_MCI_PDCFBYTE_ENABLE               (0x1UL << 13)   // (MCI) Enables PDC Force Byte Transfer
#define AT91C_MCI_PDCPADV         (0x1UL << 14) // (MCI) PDC Padding Value
#define AT91C_MCI_PDCMODE         (0x1UL << 15) // (MCI) PDC Oriented Mode
#define 	AT91C_MCI_PDCMODE_DISABLE              (0x0UL << 15)    // (MCI) Disables PDC Transfer
#define 	AT91C_MCI_PDCMODE_ENABLE               (0x1UL << 15)    // (MCI) Enables PDC Transfer
#define AT91C_MCI_BLKLEN          (0xFFFFUL << 16)      // (MCI) Data Block Length
// -------- MCI_DTOR : (MCI Offset: 0x8) MCI Data Timeout Register -------- 
#define AT91C_MCI_DTOCYC          (0xFUL <<  0) // (MCI) Data Timeout Cycle Number
#define AT91C_MCI_DTOMUL          (0x7UL <<  4) // (MCI) Data Timeout Multiplier
#define 	AT91C_MCI_DTOMUL_1                    (0x0UL <<  4)     // (MCI) DTOCYC x 1
#define 	AT91C_MCI_DTOMUL_16                   (0x1UL <<  4)     // (MCI) DTOCYC x 16
#define 	AT91C_MCI_DTOMUL_128                  (0x2UL <<  4)     // (MCI) DTOCYC x 128
#define 	AT91C_MCI_DTOMUL_256                  (0x3UL <<  4)     // (MCI) DTOCYC x 256
#define 	AT91C_MCI_DTOMUL_1024                 (0x4UL <<  4)     // (MCI) DTOCYC x 1024
#define 	AT91C_MCI_DTOMUL_4096                 (0x5UL <<  4)     // (MCI) DTOCYC x 4096
#define 	AT91C_MCI_DTOMUL_65536                (0x6UL <<  4)     // (MCI) DTOCYC x 65536
#define 	AT91C_MCI_DTOMUL_1048576              (0x7UL <<  4)     // (MCI) DTOCYC x 1048576
// -------- MCI_SDCR : (MCI Offset: 0xc) MCI SD Card Register -------- 
#define AT91C_MCI_SCDSEL          (0x3UL <<  0) // (MCI) SD Card/SDIO Selector
#define 	AT91C_MCI_SCDSEL_SLOTA                (0x0UL)   // (MCI) Slot A selected
#define 	AT91C_MCI_SCDSEL_SLOTB                (0x1UL)   // (MCI) Slot B selected
#define 	AT91C_MCI_SCDSEL_SLOTC                (0x2UL)   // (MCI) Slot C selected
#define 	AT91C_MCI_SCDSEL_SLOTD                (0x3UL)   // (MCI) Slot D selected
#define AT91C_MCI_SCDBUS          (0x3UL <<  6) // (MCI) SDCard/SDIO Bus Width
#define 	AT91C_MCI_SCDBUS_1BIT                 (0x0UL <<  6)     // (MCI) 1-bit data bus
#define 	AT91C_MCI_SCDBUS_4BITS                (0x2UL <<  6)     // (MCI) 4-bits data bus
#define 	AT91C_MCI_SCDBUS_8BITS                (0x3UL <<  6)     // (MCI) 8-bits data bus
// -------- MCI_CMDR : (MCI Offset: 0x14) MCI Command Register -------- 
#define AT91C_MCI_CMDNB           (0x3FUL <<  0)        // (MCI) Command Number
#define AT91C_MCI_RSPTYP          (0x3UL <<  6) // (MCI) Response Type
#define 	AT91C_MCI_RSPTYP_NO                   (0x0UL <<  6)     // (MCI) No response
#define 	AT91C_MCI_RSPTYP_48                   (0x1UL <<  6)     // (MCI) 48-bit response
#define 	AT91C_MCI_RSPTYP_136                  (0x2UL <<  6)     // (MCI) 136-bit response
#define 	AT91C_MCI_RSPTYP_R1B                  (0x3UL <<  6)     // (MCI) R1b response
#define AT91C_MCI_SPCMD           (0x7UL <<  8) // (MCI) Special CMD
#define 	AT91C_MCI_SPCMD_NONE                 (0x0UL <<  8)      // (MCI) Not a special CMD
#define 	AT91C_MCI_SPCMD_INIT                 (0x1UL <<  8)      // (MCI) Initialization CMD
#define 	AT91C_MCI_SPCMD_SYNC                 (0x2UL <<  8)      // (MCI) Synchronized CMD
#define 	AT91C_MCI_SPCMD_CE_ATA               (0x3UL <<  8)      // (MCI) CE-ATA Completion Signal disable CMD
#define 	AT91C_MCI_SPCMD_IT_CMD               (0x4UL <<  8)      // (MCI) Interrupt command
#define 	AT91C_MCI_SPCMD_IT_REP               (0x5UL <<  8)      // (MCI) Interrupt response
#define AT91C_MCI_OPDCMD          (0x1UL << 11) // (MCI) Open Drain Command
#define 	AT91C_MCI_OPDCMD_PUSHPULL             (0x0UL << 11)     // (MCI) Push/pull command
#define 	AT91C_MCI_OPDCMD_OPENDRAIN            (0x1UL << 11)     // (MCI) Open drain command
#define AT91C_MCI_MAXLAT          (0x1UL << 12) // (MCI) Maximum Latency for Command to respond
#define 	AT91C_MCI_MAXLAT_5                    (0x0UL << 12)     // (MCI) 5 cycles maximum latency
#define 	AT91C_MCI_MAXLAT_64                   (0x1UL << 12)     // (MCI) 64 cycles maximum latency
#define AT91C_MCI_TRCMD           (0x3UL << 16) // (MCI) Transfer CMD
#define 	AT91C_MCI_TRCMD_NO                   (0x0UL << 16)      // (MCI) No transfer
#define 	AT91C_MCI_TRCMD_START                (0x1UL << 16)      // (MCI) Start transfer
#define 	AT91C_MCI_TRCMD_STOP                 (0x2UL << 16)      // (MCI) Stop transfer
#define AT91C_MCI_TRDIR           (0x1UL << 18) // (MCI) Transfer Direction
#define 	AT91C_MCI_TRDIR_WRITE                (0x0UL << 18)      // (MCI) Write
#define 	AT91C_MCI_TRDIR_READ                 (0x1UL << 18)      // (MCI) Read
#define AT91C_MCI_TRTYP           (0x7UL << 19) // (MCI) Transfer Type
#define 	AT91C_MCI_TRTYP_BLOCK                (0x0UL << 19)      // (MCI) MMC/SDCard Single Block Transfer type
#define 	AT91C_MCI_TRTYP_MULTIPLE             (0x1UL << 19)      // (MCI) MMC/SDCard Multiple Block transfer type
#define 	AT91C_MCI_TRTYP_STREAM               (0x2UL << 19)      // (MCI) MMC Stream transfer type
#define 	AT91C_MCI_TRTYP_SDIO_BYTE            (0x4UL << 19)      // (MCI) SDIO Byte transfer type
#define 	AT91C_MCI_TRTYP_SDIO_BLOCK           (0x5UL << 19)      // (MCI) SDIO Block transfer type
#define AT91C_MCI_IOSPCMD         (0x3UL << 24) // (MCI) SDIO Special Command
#define 	AT91C_MCI_IOSPCMD_NONE                 (0x0UL << 24)    // (MCI) NOT a special command
#define 	AT91C_MCI_IOSPCMD_SUSPEND              (0x1UL << 24)    // (MCI) SDIO Suspend Command
#define 	AT91C_MCI_IOSPCMD_RESUME               (0x2UL << 24)    // (MCI) SDIO Resume Command
#define AT91C_MCI_ATACS           (0x1UL << 26) // (MCI) ATA with command completion signal
#define 	AT91C_MCI_ATACS_NORMAL               (0x0UL << 26)      // (MCI) normal operation mode
#define 	AT91C_MCI_ATACS_COMPLETION           (0x1UL << 26)      // (MCI) completion signal is expected within MCI_CSTOR
// -------- MCI_BLKR : (MCI Offset: 0x18) MCI Block Register -------- 
#define AT91C_MCI_BCNT            (0xFFFFUL <<  0)      // (MCI) MMC/SDIO Block Count / SDIO Byte Count
// -------- MCI_CSTOR : (MCI Offset: 0x1c) MCI Completion Signal Timeout Register -------- 
#define AT91C_MCI_CSTOCYC         (0xFUL <<  0) // (MCI) Completion Signal Timeout Cycle Number
#define AT91C_MCI_CSTOMUL         (0x7UL <<  4) // (MCI) Completion Signal Timeout Multiplier
#define 	AT91C_MCI_CSTOMUL_1                    (0x0UL <<  4)    // (MCI) CSTOCYC x 1
#define 	AT91C_MCI_CSTOMUL_16                   (0x1UL <<  4)    // (MCI) CSTOCYC x  16
#define 	AT91C_MCI_CSTOMUL_128                  (0x2UL <<  4)    // (MCI) CSTOCYC x  128
#define 	AT91C_MCI_CSTOMUL_256                  (0x3UL <<  4)    // (MCI) CSTOCYC x  256
#define 	AT91C_MCI_CSTOMUL_1024                 (0x4UL <<  4)    // (MCI) CSTOCYC x  1024
#define 	AT91C_MCI_CSTOMUL_4096                 (0x5UL <<  4)    // (MCI) CSTOCYC x  4096
#define 	AT91C_MCI_CSTOMUL_65536                (0x6UL <<  4)    // (MCI) CSTOCYC x  65536
#define 	AT91C_MCI_CSTOMUL_1048576              (0x7UL <<  4)    // (MCI) CSTOCYC x  1048576
// -------- MCI_SR : (MCI Offset: 0x40) MCI Status Register -------- 
#define AT91C_MCI_CMDRDY          (0x1UL <<  0) // (MCI) Command Ready flag
#define AT91C_MCI_RXRDY           (0x1UL <<  1) // (MCI) RX Ready flag
#define AT91C_MCI_TXRDY           (0x1UL <<  2) // (MCI) TX Ready flag
#define AT91C_MCI_BLKE            (0x1UL <<  3) // (MCI) Data Block Transfer Ended flag
#define AT91C_MCI_DTIP            (0x1UL <<  4) // (MCI) Data Transfer in Progress flag
#define AT91C_MCI_NOTBUSY         (0x1UL <<  5) // (MCI) Data Line Not Busy flag
#define AT91C_MCI_ENDRX           (0x1UL <<  6) // (MCI) End of RX Buffer flag
#define AT91C_MCI_ENDTX           (0x1UL <<  7) // (MCI) End of TX Buffer flag
#define AT91C_MCI_SDIOIRQA        (0x1UL <<  8) // (MCI) SDIO Interrupt for Slot A
#define AT91C_MCI_SDIOIRQB        (0x1UL <<  9) // (MCI) SDIO Interrupt for Slot B
#define AT91C_MCI_SDIOIRQC        (0x1UL << 10) // (MCI) SDIO Interrupt for Slot C
#define AT91C_MCI_SDIOIRQD        (0x1UL << 11) // (MCI) SDIO Interrupt for Slot D
#define AT91C_MCI_SDIOWAIT        (0x1UL << 12) // (MCI) SDIO Read Wait operation flag
#define AT91C_MCI_CSRCV           (0x1UL << 13) // (MCI) CE-ATA Completion Signal flag
#define AT91C_MCI_RXBUFF          (0x1UL << 14) // (MCI) RX Buffer Full flag
#define AT91C_MCI_TXBUFE          (0x1UL << 15) // (MCI) TX Buffer Empty flag
#define AT91C_MCI_RINDE           (0x1UL << 16) // (MCI) Response Index Error flag
#define AT91C_MCI_RDIRE           (0x1UL << 17) // (MCI) Response Direction Error flag
#define AT91C_MCI_RCRCE           (0x1UL << 18) // (MCI) Response CRC Error flag
#define AT91C_MCI_RENDE           (0x1UL << 19) // (MCI) Response End Bit Error flag
#define AT91C_MCI_RTOE            (0x1UL << 20) // (MCI) Response Time-out Error flag
#define AT91C_MCI_DCRCE           (0x1UL << 21) // (MCI) data CRC Error flag
#define AT91C_MCI_DTOE            (0x1UL << 22) // (MCI) Data timeout Error flag
#define AT91C_MCI_CSTOE           (0x1UL << 23) // (MCI) Completion Signal timeout Error flag
#define AT91C_MCI_BLKOVRE         (0x1UL << 24) // (MCI) DMA Block Overrun Error flag
#define AT91C_MCI_DMADONE         (0x1UL << 25) // (MCI) DMA Transfer Done flag
#define AT91C_MCI_FIFOEMPTY       (0x1UL << 26) // (MCI) FIFO Empty flag
#define AT91C_MCI_XFRDONE         (0x1UL << 27) // (MCI) Transfer Done flag
#define AT91C_MCI_OVRE            (0x1UL << 30) // (MCI) Overrun flag
#define AT91C_MCI_UNRE            (0x1UL << 31) // (MCI) Underrun flag
// -------- MCI_IER : (MCI Offset: 0x44) MCI Interrupt Enable Register -------- 
// -------- MCI_IDR : (MCI Offset: 0x48) MCI Interrupt Disable Register -------- 
// -------- MCI_IMR : (MCI Offset: 0x4c) MCI Interrupt Mask Register -------- 
// -------- MCI_DMA : (MCI Offset: 0x50) MCI DMA Configuration Register -------- 
#define AT91C_MCI_OFFSET          (0x3UL <<  0) // (MCI) DMA Write Buffer Offset
#define AT91C_MCI_CHKSIZE         (0x7UL <<  4) // (MCI) DMA Channel Read/Write Chunk Size
#define 	AT91C_MCI_CHKSIZE_1                    (0x0UL <<  4)    // (MCI) Number of data transferred is 1
#define 	AT91C_MCI_CHKSIZE_4                    (0x1UL <<  4)    // (MCI) Number of data transferred is 4
#define 	AT91C_MCI_CHKSIZE_8                    (0x2UL <<  4)    // (MCI) Number of data transferred is 8
#define 	AT91C_MCI_CHKSIZE_16                   (0x3UL <<  4)    // (MCI) Number of data transferred is 16
#define 	AT91C_MCI_CHKSIZE_32                   (0x4UL <<  4)    // (MCI) Number of data transferred is 32
#define AT91C_MCI_DMAEN           (0x1UL <<  8) // (MCI) DMA Hardware Handshaking Enable
#define 	AT91C_MCI_DMAEN_DISABLE              (0x0UL <<  8)      // (MCI) DMA interface is disabled
#define 	AT91C_MCI_DMAEN_ENABLE               (0x1UL <<  8)      // (MCI) DMA interface is enabled
// -------- MCI_CFG : (MCI Offset: 0x54) MCI Configuration Register -------- 
#define AT91C_MCI_FIFOMODE        (0x1UL <<  0) // (MCI) MCI Internal FIFO Control Mode
#define 	AT91C_MCI_FIFOMODE_AMOUNTDATA           (0x0UL) // (MCI) A write transfer starts when a sufficient amount of datas is written into the FIFO
#define 	AT91C_MCI_FIFOMODE_ONEDATA              (0x1UL) // (MCI) A write transfer starts as soon as one data is written into the FIFO
#define AT91C_MCI_FERRCTRL        (0x1UL <<  4) // (MCI) Flow Error Flag Reset Control Mode
#define 	AT91C_MCI_FERRCTRL_RWCMD                (0x0UL <<  4)   // (MCI) When an underflow/overflow condition flag is set, a new Write/Read command is needed to reset the flag
#define 	AT91C_MCI_FERRCTRL_READSR               (0x1UL <<  4)   // (MCI) When an underflow/overflow condition flag is set, a read status resets the flag
#define AT91C_MCI_HSMODE          (0x1UL <<  8) // (MCI) High Speed Mode
#define 	AT91C_MCI_HSMODE_DISABLE              (0x0UL <<  8)     // (MCI) Default Bus Timing Mode
#define 	AT91C_MCI_HSMODE_ENABLE               (0x1UL <<  8)     // (MCI) High Speed Mode
#define AT91C_MCI_LSYNC           (0x1UL << 12) // (MCI) Synchronize on last block
#define 	AT91C_MCI_LSYNC_CURRENT              (0x0UL << 12)      // (MCI) Pending command sent at end of current data block
#define 	AT91C_MCI_LSYNC_INFINITE             (0x1UL << 12)      // (MCI) Pending command sent at end of block transfer when transfer length is not infinite
// -------- MCI_WPCR : (MCI Offset: 0xe4) Write Protection Control Register -------- 
#define AT91C_MCI_WP_EN           (0x1UL <<  0) // (MCI) Write Protection Enable
#define 	AT91C_MCI_WP_EN_DISABLE              (0x0UL)    // (MCI) Write Operation is disabled (if WP_KEY corresponds)
#define 	AT91C_MCI_WP_EN_ENABLE               (0x1UL)    // (MCI) Write Operation is enabled (if WP_KEY corresponds)
#define AT91C_MCI_WP_KEY          (0xFFFFFFUL <<  8)    // (MCI) Write Protection Key
// -------- MCI_WPSR : (MCI Offset: 0xe8) Write Protection Status Register -------- 
#define AT91C_MCI_WP_VS           (0xFUL <<  0) // (MCI) Write Protection Violation Status
#define 	AT91C_MCI_WP_VS_NO_VIOLATION         (0x0UL)    // (MCI) No Write Protection Violation detected since last read
#define 	AT91C_MCI_WP_VS_ON_WRITE             (0x1UL)    // (MCI) Write Protection Violation detected since last read
#define 	AT91C_MCI_WP_VS_ON_RESET             (0x2UL)    // (MCI) Software Reset Violation detected since last read
#define 	AT91C_MCI_WP_VS_ON_BOTH              (0x3UL)    // (MCI) Write Protection and Software Reset Violation detected since last read
#define AT91C_MCI_WP_VSRC         (0xFUL <<  8) // (MCI) Write Protection Violation Source
#define 	AT91C_MCI_WP_VSRC_NO_VIOLATION         (0x0UL <<  8)    // (MCI) No Write Protection Violation detected since last read
#define 	AT91C_MCI_WP_VSRC_MCI_MR               (0x1UL <<  8)    // (MCI) Write Protection Violation detected on MCI_MR since last read
#define 	AT91C_MCI_WP_VSRC_MCI_DTOR             (0x2UL <<  8)    // (MCI) Write Protection Violation detected on MCI_DTOR since last read
#define 	AT91C_MCI_WP_VSRC_MCI_SDCR             (0x3UL <<  8)    // (MCI) Write Protection Violation detected on MCI_SDCR since last read
#define 	AT91C_MCI_WP_VSRC_MCI_CSTOR            (0x4UL <<  8)    // (MCI) Write Protection Violation detected on MCI_CSTOR since last read
#define 	AT91C_MCI_WP_VSRC_MCI_DMA              (0x5UL <<  8)    // (MCI) Write Protection Violation detected on MCI_DMA since last read
#define 	AT91C_MCI_WP_VSRC_MCI_CFG              (0x6UL <<  8)    // (MCI) Write Protection Violation detected on MCI_CFG since last read
#define 	AT91C_MCI_WP_VSRC_MCI_DEL              (0x7UL <<  8)    // (MCI) Write Protection Violation detected on MCI_DEL since last read
// -------- MCI_VER : (MCI Offset: 0xfc)  VERSION  Register -------- 
#define AT91C_MCI_VER             (0xFUL <<  0) // (MCI)  VERSION  Register

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Two-wire Interface
// *****************************************************************************
// *** Register offset in AT91S_TWI structure ***
#define TWI_CR          ( 0)    // Control Register
#define TWI_MMR         ( 4)    // Master Mode Register
#define TWI_SMR         ( 8)    // Slave Mode Register
#define TWI_IADR        (12)    // Internal Address Register
#define TWI_CWGR        (16)    // Clock Waveform Generator Register
#define TWI_SR          (32)    // Status Register
#define TWI_IER         (36)    // Interrupt Enable Register
#define TWI_IDR         (40)    // Interrupt Disable Register
#define TWI_IMR         (44)    // Interrupt Mask Register
#define TWI_RHR         (48)    // Receive Holding Register
#define TWI_THR         (52)    // Transmit Holding Register
#define TWI_ADDRSIZE    (236)   // TWI ADDRSIZE REGISTER
#define TWI_IPNAME1     (240)   // TWI IPNAME1 REGISTER
#define TWI_IPNAME2     (244)   // TWI IPNAME2 REGISTER
#define TWI_FEATURES    (248)   // TWI FEATURES REGISTER
#define TWI_VER         (252)   // Version Register
// -------- TWI_CR : (TWI Offset: 0x0) TWI Control Register -------- 
#define AT91C_TWI_START           (0x1UL <<  0) // (TWI) Send a START Condition
#define AT91C_TWI_STOP            (0x1UL <<  1) // (TWI) Send a STOP Condition
#define AT91C_TWI_MSEN            (0x1UL <<  2) // (TWI) TWI Master Transfer Enabled
#define AT91C_TWI_MSDIS           (0x1UL <<  3) // (TWI) TWI Master Transfer Disabled
#define AT91C_TWI_SVEN            (0x1UL <<  4) // (TWI) TWI Slave mode Enabled
#define AT91C_TWI_SVDIS           (0x1UL <<  5) // (TWI) TWI Slave mode Disabled
#define AT91C_TWI_SWRST           (0x1UL <<  7) // (TWI) Software Reset
// -------- TWI_MMR : (TWI Offset: 0x4) TWI Master Mode Register -------- 
#define AT91C_TWI_IADRSZ          (0x3UL <<  8) // (TWI) Internal Device Address Size
#define 	AT91C_TWI_IADRSZ_NO                   (0x0UL <<  8)     // (TWI) No internal device address
#define 	AT91C_TWI_IADRSZ_1_BYTE               (0x1UL <<  8)     // (TWI) One-byte internal device address
#define 	AT91C_TWI_IADRSZ_2_BYTE               (0x2UL <<  8)     // (TWI) Two-byte internal device address
#define 	AT91C_TWI_IADRSZ_3_BYTE               (0x3UL <<  8)     // (TWI) Three-byte internal device address
#define AT91C_TWI_MREAD           (0x1UL << 12) // (TWI) Master Read Direction
#define AT91C_TWI_DADR            (0x7FUL << 16)        // (TWI) Device Address
// -------- TWI_SMR : (TWI Offset: 0x8) TWI Slave Mode Register -------- 
#define AT91C_TWI_SADR            (0x7FUL << 16)        // (TWI) Slave Address
// -------- TWI_CWGR : (TWI Offset: 0x10) TWI Clock Waveform Generator Register -------- 
#define AT91C_TWI_CLDIV           (0xFFUL <<  0)        // (TWI) Clock Low Divider
#define AT91C_TWI_CHDIV           (0xFFUL <<  8)        // (TWI) Clock High Divider
#define AT91C_TWI_CKDIV           (0x7UL << 16) // (TWI) Clock Divider
// -------- TWI_SR : (TWI Offset: 0x20) TWI Status Register -------- 
#define AT91C_TWI_TXCOMP_SLAVE    (0x1UL <<  0) // (TWI) Transmission Completed
#define AT91C_TWI_TXCOMP_MASTER   (0x1UL <<  0) // (TWI) Transmission Completed
#define AT91C_TWI_RXRDY           (0x1UL <<  1) // (TWI) Receive holding register ReaDY
#define AT91C_TWI_TXRDY_MASTER    (0x1UL <<  2) // (TWI) Transmit holding register ReaDY
#define AT91C_TWI_TXRDY_SLAVE     (0x1UL <<  2) // (TWI) Transmit holding register ReaDY
#define AT91C_TWI_SVREAD          (0x1UL <<  3) // (TWI) Slave READ (used only in Slave mode)
#define AT91C_TWI_SVACC           (0x1UL <<  4) // (TWI) Slave ACCess (used only in Slave mode)
#define AT91C_TWI_GACC            (0x1UL <<  5) // (TWI) General Call ACcess (used only in Slave mode)
#define AT91C_TWI_OVRE            (0x1UL <<  6) // (TWI) Overrun Error (used only in Master and Multi-master mode)
#define AT91C_TWI_NACK_SLAVE      (0x1UL <<  8) // (TWI) Not Acknowledged
#define AT91C_TWI_NACK_MASTER     (0x1UL <<  8) // (TWI) Not Acknowledged
#define AT91C_TWI_ARBLST_MULTI_MASTER (0x1UL <<  9)     // (TWI) Arbitration Lost (used only in Multimaster mode)
#define AT91C_TWI_SCLWS           (0x1UL << 10) // (TWI) Clock Wait State (used only in Slave mode)
#define AT91C_TWI_EOSACC          (0x1UL << 11) // (TWI) End Of Slave ACCess (used only in Slave mode)
#define AT91C_TWI_ENDRX           (0x1UL << 12) // (TWI) End of Receiver Transfer
#define AT91C_TWI_ENDTX           (0x1UL << 13) // (TWI) End of Receiver Transfer
#define AT91C_TWI_RXBUFF          (0x1UL << 14) // (TWI) RXBUFF Interrupt
#define AT91C_TWI_TXBUFE          (0x1UL << 15) // (TWI) TXBUFE Interrupt
// -------- TWI_IER : (TWI Offset: 0x24) TWI Interrupt Enable Register -------- 
// -------- TWI_IDR : (TWI Offset: 0x28) TWI Interrupt Disable Register -------- 
// -------- TWI_IMR : (TWI Offset: 0x2c) TWI Interrupt Mask Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Usart
// *****************************************************************************
// *** Register offset in AT91S_USART structure ***
#define US_CR           ( 0)    // Control Register
#define US_MR           ( 4)    // Mode Register
#define US_IER          ( 8)    // Interrupt Enable Register
#define US_IDR          (12)    // Interrupt Disable Register
#define US_IMR          (16)    // Interrupt Mask Register
#define US_CSR          (20)    // Channel Status Register
#define US_RHR          (24)    // Receiver Holding Register
#define US_THR          (28)    // Transmitter Holding Register
#define US_BRGR         (32)    // Baud Rate Generator Register
#define US_RTOR         (36)    // Receiver Time-out Register
#define US_TTGR         (40)    // Transmitter Time-guard Register
#define US_FIDI         (64)    // FI_DI_Ratio Register
#define US_NER          (68)    // Nb Errors Register
#define US_IF           (76)    // IRDA_FILTER Register
#define US_MAN          (80)    // Manchester Encoder Decoder Register
#define US_ADDRSIZE     (236)   // US ADDRSIZE REGISTER
#define US_IPNAME1      (240)   // US IPNAME1 REGISTER
#define US_IPNAME2      (244)   // US IPNAME2 REGISTER
#define US_FEATURES     (248)   // US FEATURES REGISTER
#define US_VER          (252)   // VERSION Register
// -------- US_CR : (USART Offset: 0x0)  Control Register -------- 
#define AT91C_US_RSTRX            (0x1UL <<  2) // (USART) Reset Receiver
#define AT91C_US_RSTTX            (0x1UL <<  3) // (USART) Reset Transmitter
#define AT91C_US_RXEN             (0x1UL <<  4) // (USART) Receiver Enable
#define AT91C_US_RXDIS            (0x1UL <<  5) // (USART) Receiver Disable
#define AT91C_US_TXEN             (0x1UL <<  6) // (USART) Transmitter Enable
#define AT91C_US_TXDIS            (0x1UL <<  7) // (USART) Transmitter Disable
#define AT91C_US_RSTSTA           (0x1UL <<  8) // (USART) Reset Status Bits
#define AT91C_US_STTBRK           (0x1UL <<  9) // (USART) Start Break
#define AT91C_US_STPBRK           (0x1UL << 10) // (USART) Stop Break
#define AT91C_US_STTTO            (0x1UL << 11) // (USART) Start Time-out
#define AT91C_US_SENDA            (0x1UL << 12) // (USART) Send Address
#define AT91C_US_RSTIT            (0x1UL << 13) // (USART) Reset Iterations
#define AT91C_US_RSTNACK          (0x1UL << 14) // (USART) Reset Non Acknowledge
#define AT91C_US_RETTO            (0x1UL << 15) // (USART) Rearm Time-out
#define AT91C_US_DTREN            (0x1UL << 16) // (USART) Data Terminal ready Enable
#define AT91C_US_DTRDIS           (0x1UL << 17) // (USART) Data Terminal ready Disable
#define AT91C_US_RTSEN            (0x1UL << 18) // (USART) Request to Send enable
#define AT91C_US_RTSDIS           (0x1UL << 19) // (USART) Request to Send Disable
// -------- US_MR : (USART Offset: 0x4)  Mode Register -------- 
#define AT91C_US_USMODE           (0xFUL <<  0) // (USART) Usart mode
#define 	AT91C_US_USMODE_NORMAL               (0x0UL)    // (USART) Normal
#define 	AT91C_US_USMODE_RS485                (0x1UL)    // (USART) RS485
#define 	AT91C_US_USMODE_HWHSH                (0x2UL)    // (USART) Hardware Handshaking
#define 	AT91C_US_USMODE_MODEM                (0x3UL)    // (USART) Modem
#define 	AT91C_US_USMODE_ISO7816_0            (0x4UL)    // (USART) ISO7816 protocol: T = 0
#define 	AT91C_US_USMODE_ISO7816_1            (0x6UL)    // (USART) ISO7816 protocol: T = 1
#define 	AT91C_US_USMODE_IRDA                 (0x8UL)    // (USART) IrDA
#define 	AT91C_US_USMODE_SWHSH                (0xCUL)    // (USART) Software Handshaking
#define AT91C_US_CLKS             (0x3UL <<  4) // (USART) Clock Selection (Baud Rate generator Input Clock
#define 	AT91C_US_CLKS_CLOCK                (0x0UL <<  4)        // (USART) Clock
#define 	AT91C_US_CLKS_FDIV1                (0x1UL <<  4)        // (USART) fdiv1
#define 	AT91C_US_CLKS_SLOW                 (0x2UL <<  4)        // (USART) slow_clock (ARM)
#define 	AT91C_US_CLKS_EXT                  (0x3UL <<  4)        // (USART) External (SCK)
#define AT91C_US_CHRL             (0x3UL <<  6) // (USART) Clock Selection (Baud Rate generator Input Clock
#define 	AT91C_US_CHRL_5_BITS               (0x0UL <<  6)        // (USART) Character Length: 5 bits
#define 	AT91C_US_CHRL_6_BITS               (0x1UL <<  6)        // (USART) Character Length: 6 bits
#define 	AT91C_US_CHRL_7_BITS               (0x2UL <<  6)        // (USART) Character Length: 7 bits
#define 	AT91C_US_CHRL_8_BITS               (0x3UL <<  6)        // (USART) Character Length: 8 bits
#define AT91C_US_SYNC             (0x1UL <<  8) // (USART) Synchronous Mode Select
#define AT91C_US_PAR              (0x7UL <<  9) // (USART) Parity type
#define 	AT91C_US_PAR_EVEN                 (0x0UL <<  9) // (USART) Even Parity
#define 	AT91C_US_PAR_ODD                  (0x1UL <<  9) // (USART) Odd Parity
#define 	AT91C_US_PAR_SPACE                (0x2UL <<  9) // (USART) Parity forced to 0 (Space)
#define 	AT91C_US_PAR_MARK                 (0x3UL <<  9) // (USART) Parity forced to 1 (Mark)
#define 	AT91C_US_PAR_NONE                 (0x4UL <<  9) // (USART) No Parity
#define 	AT91C_US_PAR_MULTI_DROP           (0x6UL <<  9) // (USART) Multi-drop mode
#define AT91C_US_NBSTOP           (0x3UL << 12) // (USART) Number of Stop bits
#define 	AT91C_US_NBSTOP_1_BIT                (0x0UL << 12)      // (USART) 1 stop bit
#define 	AT91C_US_NBSTOP_15_BIT               (0x1UL << 12)      // (USART) Asynchronous (SYNC=0) 2 stop bits Synchronous (SYNC=1) 2 stop bits
#define 	AT91C_US_NBSTOP_2_BIT                (0x2UL << 12)      // (USART) 2 stop bits
#define AT91C_US_CHMODE           (0x3UL << 14) // (USART) Channel Mode
#define 	AT91C_US_CHMODE_NORMAL               (0x0UL << 14)      // (USART) Normal Mode: The USART channel operates as an RX/TX USART.
#define 	AT91C_US_CHMODE_AUTO                 (0x1UL << 14)      // (USART) Automatic Echo: Receiver Data Input is connected to the TXD pin.
#define 	AT91C_US_CHMODE_LOCAL                (0x2UL << 14)      // (USART) Local Loopback: Transmitter Output Signal is connected to Receiver Input Signal.
#define 	AT91C_US_CHMODE_REMOTE               (0x3UL << 14)      // (USART) Remote Loopback: RXD pin is internally connected to TXD pin.
#define AT91C_US_MSBF             (0x1UL << 16) // (USART) Bit Order
#define AT91C_US_MODE9            (0x1UL << 17) // (USART) 9-bit Character length
#define AT91C_US_CKLO             (0x1UL << 18) // (USART) Clock Output Select
#define AT91C_US_OVER             (0x1UL << 19) // (USART) Over Sampling Mode
#define AT91C_US_INACK            (0x1UL << 20) // (USART) Inhibit Non Acknowledge
#define AT91C_US_DSNACK           (0x1UL << 21) // (USART) Disable Successive NACK
#define AT91C_US_VAR_SYNC         (0x1UL << 22) // (USART) Variable synchronization of command/data sync Start Frame Delimiter
#define AT91C_US_MAX_ITER         (0x1UL << 24) // (USART) Number of Repetitions
#define AT91C_US_FILTER           (0x1UL << 28) // (USART) Receive Line Filter
#define AT91C_US_MANMODE          (0x1UL << 29) // (USART) Manchester Encoder/Decoder Enable
#define AT91C_US_MODSYNC          (0x1UL << 30) // (USART) Manchester Synchronization mode
#define AT91C_US_ONEBIT           (0x1UL << 31) // (USART) Start Frame Delimiter selector
// -------- US_IER : (USART Offset: 0x8)  Interrupt Enable Register -------- 
#define AT91C_US_RXRDY            (0x1UL <<  0) // (USART) RXRDY Interrupt
#define AT91C_US_TXRDY            (0x1UL <<  1) // (USART) TXRDY Interrupt
#define AT91C_US_RXBRK            (0x1UL <<  2) // (USART) Break Received/End of Break
#define AT91C_US_ENDRX            (0x1UL <<  3) // (USART) End of Receive Transfer Interrupt
#define AT91C_US_ENDTX            (0x1UL <<  4) // (USART) End of Transmit Interrupt
#define AT91C_US_OVRE             (0x1UL <<  5) // (USART) Overrun Interrupt
#define AT91C_US_FRAME            (0x1UL <<  6) // (USART) Framing Error Interrupt
#define AT91C_US_PARE             (0x1UL <<  7) // (USART) Parity Error Interrupt
#define AT91C_US_TIMEOUT          (0x1UL <<  8) // (USART) Receiver Time-out
#define AT91C_US_TXEMPTY          (0x1UL <<  9) // (USART) TXEMPTY Interrupt
#define AT91C_US_ITERATION        (0x1UL << 10) // (USART) Max number of Repetitions Reached
#define AT91C_US_TXBUFE           (0x1UL << 11) // (USART) TXBUFE Interrupt
#define AT91C_US_RXBUFF           (0x1UL << 12) // (USART) RXBUFF Interrupt
#define AT91C_US_NACK             (0x1UL << 13) // (USART) Non Acknowledge
#define AT91C_US_RIIC             (0x1UL << 16) // (USART) Ring INdicator Input Change Flag
#define AT91C_US_DSRIC            (0x1UL << 17) // (USART) Data Set Ready Input Change Flag
#define AT91C_US_DCDIC            (0x1UL << 18) // (USART) Data Carrier Flag
#define AT91C_US_CTSIC            (0x1UL << 19) // (USART) Clear To Send Input Change Flag
#define AT91C_US_MANE             (0x1UL << 20) // (USART) Manchester Error Interrupt
// -------- US_IDR : (USART Offset: 0xc)  Interrupt Disable Register -------- 
// -------- US_IMR : (USART Offset: 0x10)  Interrupt Mask Register -------- 
// -------- US_CSR : (USART Offset: 0x14)  Channel Status Register -------- 
#define AT91C_US_RI               (0x1UL << 20) // (USART) Image of RI Input
#define AT91C_US_DSR              (0x1UL << 21) // (USART) Image of DSR Input
#define AT91C_US_DCD              (0x1UL << 22) // (USART) Image of DCD Input
#define AT91C_US_CTS              (0x1UL << 23) // (USART) Image of CTS Input
#define AT91C_US_MANERR           (0x1UL << 24) // (USART) Manchester Error
// -------- US_MAN : (USART Offset: 0x50) Manchester Encoder Decoder Register -------- 
#define AT91C_US_TX_PL            (0xFUL <<  0) // (USART) Transmitter Preamble Length
#define AT91C_US_TX_PP            (0x3UL <<  8) // (USART) Transmitter Preamble Pattern
#define 	AT91C_US_TX_PP_ALL_ONE              (0x0UL <<  8)       // (USART) ALL_ONE
#define 	AT91C_US_TX_PP_ALL_ZERO             (0x1UL <<  8)       // (USART) ALL_ZERO
#define 	AT91C_US_TX_PP_ZERO_ONE             (0x2UL <<  8)       // (USART) ZERO_ONE
#define 	AT91C_US_TX_PP_ONE_ZERO             (0x3UL <<  8)       // (USART) ONE_ZERO
#define AT91C_US_TX_MPOL          (0x1UL << 12) // (USART) Transmitter Manchester Polarity
#define AT91C_US_RX_PL            (0xFUL << 16) // (USART) Receiver Preamble Length
#define AT91C_US_RX_PP            (0x3UL << 24) // (USART) Receiver Preamble Pattern detected
#define 	AT91C_US_RX_PP_ALL_ONE              (0x0UL << 24)       // (USART) ALL_ONE
#define 	AT91C_US_RX_PP_ALL_ZERO             (0x1UL << 24)       // (USART) ALL_ZERO
#define 	AT91C_US_RX_PP_ZERO_ONE             (0x2UL << 24)       // (USART) ZERO_ONE
#define 	AT91C_US_RX_PP_ONE_ZERO             (0x3UL << 24)       // (USART) ONE_ZERO
#define AT91C_US_RX_MPOL          (0x1UL << 28) // (USART) Receiver Manchester Polarity
#define AT91C_US_DRIFT            (0x1UL << 30) // (USART) Drift compensation

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Synchronous Serial Controller Interface
// *****************************************************************************
// *** Register offset in AT91S_SSC structure ***
#define SSC_CR          ( 0)    // Control Register
#define SSC_CMR         ( 4)    // Clock Mode Register
#define SSC_RCMR        (16)    // Receive Clock ModeRegister
#define SSC_RFMR        (20)    // Receive Frame Mode Register
#define SSC_TCMR        (24)    // Transmit Clock Mode Register
#define SSC_TFMR        (28)    // Transmit Frame Mode Register
#define SSC_RHR         (32)    // Receive Holding Register
#define SSC_THR         (36)    // Transmit Holding Register
#define SSC_RSHR        (48)    // Receive Sync Holding Register
#define SSC_TSHR        (52)    // Transmit Sync Holding Register
#define SSC_SR          (64)    // Status Register
#define SSC_IER         (68)    // Interrupt Enable Register
#define SSC_IDR         (72)    // Interrupt Disable Register
#define SSC_IMR         (76)    // Interrupt Mask Register
#define SSC_ADDRSIZE    (236)   // SSC ADDRSIZE REGISTER
#define SSC_IPNAME1     (240)   // SSC IPNAME1 REGISTER
#define SSC_IPNAME2     (244)   // SSC IPNAME2 REGISTER
#define SSC_FEATURES    (248)   // SSC FEATURES REGISTER
#define SSC_VER         (252)   // Version Register
// -------- SSC_CR : (SSC Offset: 0x0) SSC Control Register -------- 
#define AT91C_SSC_RXEN            (0x1UL <<  0) // (SSC) Receive Enable
#define AT91C_SSC_RXDIS           (0x1UL <<  1) // (SSC) Receive Disable
#define AT91C_SSC_TXEN            (0x1UL <<  8) // (SSC) Transmit Enable
#define AT91C_SSC_TXDIS           (0x1UL <<  9) // (SSC) Transmit Disable
#define AT91C_SSC_SWRST           (0x1UL << 15) // (SSC) Software Reset
// -------- SSC_RCMR : (SSC Offset: 0x10) SSC Receive Clock Mode Register -------- 
#define AT91C_SSC_CKS             (0x3UL <<  0) // (SSC) Receive/Transmit Clock Selection
#define 	AT91C_SSC_CKS_DIV                  (0x0UL)      // (SSC) Divided Clock
#define 	AT91C_SSC_CKS_TK                   (0x1UL)      // (SSC) TK Clock signal
#define 	AT91C_SSC_CKS_RK                   (0x2UL)      // (SSC) RK pin
#define AT91C_SSC_CKO             (0x7UL <<  2) // (SSC) Receive/Transmit Clock Output Mode Selection
#define 	AT91C_SSC_CKO_NONE                 (0x0UL <<  2)        // (SSC) Receive/Transmit Clock Output Mode: None RK pin: Input-only
#define 	AT91C_SSC_CKO_CONTINOUS            (0x1UL <<  2)        // (SSC) Continuous Receive/Transmit Clock RK pin: Output
#define 	AT91C_SSC_CKO_DATA_TX              (0x2UL <<  2)        // (SSC) Receive/Transmit Clock only during data transfers RK pin: Output
#define AT91C_SSC_CKI             (0x1UL <<  5) // (SSC) Receive/Transmit Clock Inversion
#define AT91C_SSC_CKG             (0x3UL <<  6) // (SSC) Receive/Transmit Clock Gating Selection
#define 	AT91C_SSC_CKG_NONE                 (0x0UL <<  6)        // (SSC) Receive/Transmit Clock Gating: None, continuous clock
#define 	AT91C_SSC_CKG_LOW                  (0x1UL <<  6)        // (SSC) Receive/Transmit Clock enabled only if RF Low
#define 	AT91C_SSC_CKG_HIGH                 (0x2UL <<  6)        // (SSC) Receive/Transmit Clock enabled only if RF High
#define AT91C_SSC_START           (0xFUL <<  8) // (SSC) Receive/Transmit Start Selection
#define 	AT91C_SSC_START_CONTINOUS            (0x0UL <<  8)      // (SSC) Continuous, as soon as the receiver is enabled, and immediately after the end of transfer of the previous data.
#define 	AT91C_SSC_START_TX                   (0x1UL <<  8)      // (SSC) Transmit/Receive start
#define 	AT91C_SSC_START_LOW_RF               (0x2UL <<  8)      // (SSC) Detection of a low level on RF input
#define 	AT91C_SSC_START_HIGH_RF              (0x3UL <<  8)      // (SSC) Detection of a high level on RF input
#define 	AT91C_SSC_START_FALL_RF              (0x4UL <<  8)      // (SSC) Detection of a falling edge on RF input
#define 	AT91C_SSC_START_RISE_RF              (0x5UL <<  8)      // (SSC) Detection of a rising edge on RF input
#define 	AT91C_SSC_START_LEVEL_RF             (0x6UL <<  8)      // (SSC) Detection of any level change on RF input
#define 	AT91C_SSC_START_EDGE_RF              (0x7UL <<  8)      // (SSC) Detection of any edge on RF input
#define 	AT91C_SSC_START_0                    (0x8UL <<  8)      // (SSC) Compare 0
#define AT91C_SSC_STOP            (0x1UL << 12) // (SSC) Receive Stop Selection
#define AT91C_SSC_STTDLY          (0xFFUL << 16)        // (SSC) Receive/Transmit Start Delay
#define AT91C_SSC_PERIOD          (0xFFUL << 24)        // (SSC) Receive/Transmit Period Divider Selection
// -------- SSC_RFMR : (SSC Offset: 0x14) SSC Receive Frame Mode Register -------- 
#define AT91C_SSC_DATLEN          (0x1FUL <<  0)        // (SSC) Data Length
#define AT91C_SSC_LOOP            (0x1UL <<  5) // (SSC) Loop Mode
#define AT91C_SSC_MSBF            (0x1UL <<  7) // (SSC) Most Significant Bit First
#define AT91C_SSC_DATNB           (0xFUL <<  8) // (SSC) Data Number per Frame
#define AT91C_SSC_FSLEN           (0xFUL << 16) // (SSC) Receive/Transmit Frame Sync length
#define AT91C_SSC_FSOS            (0x7UL << 20) // (SSC) Receive/Transmit Frame Sync Output Selection
#define 	AT91C_SSC_FSOS_NONE                 (0x0UL << 20)       // (SSC) Selected Receive/Transmit Frame Sync Signal: None RK pin Input-only
#define 	AT91C_SSC_FSOS_NEGATIVE             (0x1UL << 20)       // (SSC) Selected Receive/Transmit Frame Sync Signal: Negative Pulse
#define 	AT91C_SSC_FSOS_POSITIVE             (0x2UL << 20)       // (SSC) Selected Receive/Transmit Frame Sync Signal: Positive Pulse
#define 	AT91C_SSC_FSOS_LOW                  (0x3UL << 20)       // (SSC) Selected Receive/Transmit Frame Sync Signal: Driver Low during data transfer
#define 	AT91C_SSC_FSOS_HIGH                 (0x4UL << 20)       // (SSC) Selected Receive/Transmit Frame Sync Signal: Driver High during data transfer
#define 	AT91C_SSC_FSOS_TOGGLE               (0x5UL << 20)       // (SSC) Selected Receive/Transmit Frame Sync Signal: Toggling at each start of data transfer
#define AT91C_SSC_FSEDGE          (0x1UL << 24) // (SSC) Frame Sync Edge Detection
// -------- SSC_TCMR : (SSC Offset: 0x18) SSC Transmit Clock Mode Register -------- 
// -------- SSC_TFMR : (SSC Offset: 0x1c) SSC Transmit Frame Mode Register -------- 
#define AT91C_SSC_DATDEF          (0x1UL <<  5) // (SSC) Data Default Value
#define AT91C_SSC_FSDEN           (0x1UL << 23) // (SSC) Frame Sync Data Enable
// -------- SSC_SR : (SSC Offset: 0x40) SSC Status Register -------- 
#define AT91C_SSC_TXRDY           (0x1UL <<  0) // (SSC) Transmit Ready
#define AT91C_SSC_TXEMPTY         (0x1UL <<  1) // (SSC) Transmit Empty
#define AT91C_SSC_ENDTX           (0x1UL <<  2) // (SSC) End Of Transmission
#define AT91C_SSC_TXBUFE          (0x1UL <<  3) // (SSC) Transmit Buffer Empty
#define AT91C_SSC_RXRDY           (0x1UL <<  4) // (SSC) Receive Ready
#define AT91C_SSC_OVRUN           (0x1UL <<  5) // (SSC) Receive Overrun
#define AT91C_SSC_ENDRX           (0x1UL <<  6) // (SSC) End of Reception
#define AT91C_SSC_RXBUFF          (0x1UL <<  7) // (SSC) Receive Buffer Full
#define AT91C_SSC_CP0             (0x1UL <<  8) // (SSC) Compare 0
#define AT91C_SSC_CP1             (0x1UL <<  9) // (SSC) Compare 1
#define AT91C_SSC_TXSYN           (0x1UL << 10) // (SSC) Transmit Sync
#define AT91C_SSC_RXSYN           (0x1UL << 11) // (SSC) Receive Sync
#define AT91C_SSC_TXENA           (0x1UL << 16) // (SSC) Transmit Enable
#define AT91C_SSC_RXENA           (0x1UL << 17) // (SSC) Receive Enable
// -------- SSC_IER : (SSC Offset: 0x44) SSC Interrupt Enable Register -------- 
// -------- SSC_IDR : (SSC Offset: 0x48) SSC Interrupt Disable Register -------- 
// -------- SSC_IMR : (SSC Offset: 0x4c) SSC Interrupt Mask Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR PWMC Channel Interface
// *****************************************************************************
// *** Register offset in AT91S_PWMC_CH structure ***
#define PWMC_CMR        ( 0)    // Channel Mode Register
#define PWMC_CDTYR      ( 4)    // Channel Duty Cycle Register
#define PWMC_CPRDR      ( 8)    // Channel Period Register
#define PWMC_CCNTR      (12)    // Channel Counter Register
#define PWMC_CUPDR      (16)    // Channel Update Register
#define PWMC_Reserved   (20)    // Reserved
// -------- PWMC_CMR : (PWMC_CH Offset: 0x0) PWMC Channel Mode Register -------- 
#define AT91C_PWMC_CPRE           (0xFUL <<  0) // (PWMC_CH) Channel Pre-scaler : PWMC_CLKx
#define 	AT91C_PWMC_CPRE_MCK                  (0x0UL)    // (PWMC_CH)
#define 	AT91C_PWMC_CPRE_MCKA                 (0xBUL)    // (PWMC_CH)
#define 	AT91C_PWMC_CPRE_MCKB                 (0xCUL)    // (PWMC_CH)
#define AT91C_PWMC_CALG           (0x1UL <<  8) // (PWMC_CH) Channel Alignment
#define AT91C_PWMC_CPOL           (0x1UL <<  9) // (PWMC_CH) Channel Polarity
#define AT91C_PWMC_CPD            (0x1UL << 10) // (PWMC_CH) Channel Update Period
// -------- PWMC_CDTYR : (PWMC_CH Offset: 0x4) PWMC Channel Duty Cycle Register -------- 
#define AT91C_PWMC_CDTY           (0x0UL <<  0) // (PWMC_CH) Channel Duty Cycle
// -------- PWMC_CPRDR : (PWMC_CH Offset: 0x8) PWMC Channel Period Register -------- 
#define AT91C_PWMC_CPRD           (0x0UL <<  0) // (PWMC_CH) Channel Period
// -------- PWMC_CCNTR : (PWMC_CH Offset: 0xc) PWMC Channel Counter Register -------- 
#define AT91C_PWMC_CCNT           (0x0UL <<  0) // (PWMC_CH) Channel Counter
// -------- PWMC_CUPDR : (PWMC_CH Offset: 0x10) PWMC Channel Update Register -------- 
#define AT91C_PWMC_CUPD           (0x0UL <<  0) // (PWMC_CH) Channel Update

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Pulse Width Modulation Controller Interface
// *****************************************************************************
// *** Register offset in AT91S_PWMC structure ***
#define PWMC_MR         ( 0)    // PWMC Mode Register
#define PWMC_ENA        ( 4)    // PWMC Enable Register
#define PWMC_DIS        ( 8)    // PWMC Disable Register
#define PWMC_SR         (12)    // PWMC Status Register
#define PWMC_IER        (16)    // PWMC Interrupt Enable Register
#define PWMC_IDR        (20)    // PWMC Interrupt Disable Register
#define PWMC_IMR        (24)    // PWMC Interrupt Mask Register
#define PWMC_ISR        (28)    // PWMC Interrupt Status Register
#define PWMC_VR         (252)   // PWMC Version Register
#define PWMC_CH         (512)   // PWMC Channel
// -------- PWMC_MR : (PWMC Offset: 0x0) PWMC Mode Register -------- 
#define AT91C_PWMC_DIVA           (0xFFUL <<  0)        // (PWMC) CLKA divide factor.
#define AT91C_PWMC_PREA           (0xFUL <<  8) // (PWMC) Divider Input Clock Prescaler A
#define 	AT91C_PWMC_PREA_MCK                  (0x0UL <<  8)      // (PWMC)
#define AT91C_PWMC_DIVB           (0xFFUL << 16)        // (PWMC) CLKB divide factor.
#define AT91C_PWMC_PREB           (0xFUL << 24) // (PWMC) Divider Input Clock Prescaler B
#define 	AT91C_PWMC_PREB_MCK                  (0x0UL << 24)      // (PWMC)
// -------- PWMC_ENA : (PWMC Offset: 0x4) PWMC Enable Register -------- 
#define AT91C_PWMC_CHID0          (0x1UL <<  0) // (PWMC) Channel ID 0
#define AT91C_PWMC_CHID1          (0x1UL <<  1) // (PWMC) Channel ID 1
#define AT91C_PWMC_CHID2          (0x1UL <<  2) // (PWMC) Channel ID 2
#define AT91C_PWMC_CHID3          (0x1UL <<  3) // (PWMC) Channel ID 3
#define AT91C_PWMC_CHID4          (0x1UL <<  4) // (PWMC) Channel ID 4
#define AT91C_PWMC_CHID5          (0x1UL <<  5) // (PWMC) Channel ID 5
#define AT91C_PWMC_CHID6          (0x1UL <<  6) // (PWMC) Channel ID 6
#define AT91C_PWMC_CHID7          (0x1UL <<  7) // (PWMC) Channel ID 7
// -------- PWMC_DIS : (PWMC Offset: 0x8) PWMC Disable Register -------- 
// -------- PWMC_SR : (PWMC Offset: 0xc) PWMC Status Register -------- 
// -------- PWMC_IER : (PWMC Offset: 0x10) PWMC Interrupt Enable Register -------- 
// -------- PWMC_IDR : (PWMC Offset: 0x14) PWMC Interrupt Disable Register -------- 
// -------- PWMC_IMR : (PWMC Offset: 0x18) PWMC Interrupt Mask Register -------- 
// -------- PWMC_ISR : (PWMC Offset: 0x1c) PWMC Interrupt Status Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Serial Parallel Interface
// *****************************************************************************
// *** Register offset in AT91S_SPI structure ***
#define SPI_CR          ( 0)    // Control Register
#define SPI_MR          ( 4)    // Mode Register
#define SPI_RDR         ( 8)    // Receive Data Register
#define SPI_TDR         (12)    // Transmit Data Register
#define SPI_SR          (16)    // Status Register
#define SPI_IER         (20)    // Interrupt Enable Register
#define SPI_IDR         (24)    // Interrupt Disable Register
#define SPI_IMR         (28)    // Interrupt Mask Register
#define SPI_CSR         (48)    // Chip Select Register
#define SPI_ADDRSIZE    (236)   // SPI ADDRSIZE REGISTER
#define SPI_IPNAME1     (240)   // SPI IPNAME1 REGISTER
#define SPI_IPNAME2     (244)   // SPI IPNAME2 REGISTER
#define SPI_FEATURES    (248)   // SPI FEATURES REGISTER
#define SPI_VER         (252)   // Version Register
// -------- SPI_CR : (SPI Offset: 0x0) SPI Control Register -------- 
#define AT91C_SPI_SPIEN           (0x1UL <<  0) // (SPI) SPI Enable
#define AT91C_SPI_SPIDIS          (0x1UL <<  1) // (SPI) SPI Disable
#define AT91C_SPI_SWRST           (0x1UL <<  7) // (SPI) SPI Software reset
#define AT91C_SPI_LASTXFER        (0x1UL << 24) // (SPI) SPI Last Transfer
// -------- SPI_MR : (SPI Offset: 0x4) SPI Mode Register -------- 
#define AT91C_SPI_MSTR            (0x1UL <<  0) // (SPI) Master/Slave Mode
#define AT91C_SPI_PS              (0x1UL <<  1) // (SPI) Peripheral Select
#define 	AT91C_SPI_PS_FIXED                (0x0UL <<  1) // (SPI) Fixed Peripheral Select
#define 	AT91C_SPI_PS_VARIABLE             (0x1UL <<  1) // (SPI) Variable Peripheral Select
#define AT91C_SPI_PCSDEC          (0x1UL <<  2) // (SPI) Chip Select Decode
#define AT91C_SPI_FDIV            (0x1UL <<  3) // (SPI) Clock Selection
#define AT91C_SPI_MODFDIS         (0x1UL <<  4) // (SPI) Mode Fault Detection
#define AT91C_SPI_LLB             (0x1UL <<  7) // (SPI) Clock Selection
#define AT91C_SPI_PCS             (0xFUL << 16) // (SPI) Peripheral Chip Select
#define AT91C_SPI_DLYBCS          (0xFFUL << 24)        // (SPI) Delay Between Chip Selects
// -------- SPI_RDR : (SPI Offset: 0x8) Receive Data Register -------- 
#define AT91C_SPI_RD              (0xFFFFUL <<  0)      // (SPI) Receive Data
#define AT91C_SPI_RPCS            (0xFUL << 16) // (SPI) Peripheral Chip Select Status
// -------- SPI_TDR : (SPI Offset: 0xc) Transmit Data Register -------- 
#define AT91C_SPI_TD              (0xFFFFUL <<  0)      // (SPI) Transmit Data
#define AT91C_SPI_TPCS            (0xFUL << 16) // (SPI) Peripheral Chip Select Status
// -------- SPI_SR : (SPI Offset: 0x10) Status Register -------- 
#define AT91C_SPI_RDRF            (0x1UL <<  0) // (SPI) Receive Data Register Full
#define AT91C_SPI_TDRE            (0x1UL <<  1) // (SPI) Transmit Data Register Empty
#define AT91C_SPI_MODF            (0x1UL <<  2) // (SPI) Mode Fault Error
#define AT91C_SPI_OVRES           (0x1UL <<  3) // (SPI) Overrun Error Status
#define AT91C_SPI_ENDRX           (0x1UL <<  4) // (SPI) End of Receiver Transfer
#define AT91C_SPI_ENDTX           (0x1UL <<  5) // (SPI) End of Receiver Transfer
#define AT91C_SPI_RXBUFF          (0x1UL <<  6) // (SPI) RXBUFF Interrupt
#define AT91C_SPI_TXBUFE          (0x1UL <<  7) // (SPI) TXBUFE Interrupt
#define AT91C_SPI_NSSR            (0x1UL <<  8) // (SPI) NSSR Interrupt
#define AT91C_SPI_TXEMPTY         (0x1UL <<  9) // (SPI) TXEMPTY Interrupt
#define AT91C_SPI_SPIENS          (0x1UL << 16) // (SPI) Enable Status
// -------- SPI_IER : (SPI Offset: 0x14) Interrupt Enable Register -------- 
// -------- SPI_IDR : (SPI Offset: 0x18) Interrupt Disable Register -------- 
// -------- SPI_IMR : (SPI Offset: 0x1c) Interrupt Mask Register -------- 
// -------- SPI_CSR : (SPI Offset: 0x30) Chip Select Register -------- 
#define AT91C_SPI_CPOL            (0x1UL <<  0) // (SPI) Clock Polarity
#define AT91C_SPI_NCPHA           (0x1UL <<  1) // (SPI) Clock Phase
#define AT91C_SPI_CSNAAT          (0x1UL <<  2) // (SPI) Chip Select Not Active After Transfer (Ignored if CSAAT = 1)
#define AT91C_SPI_CSAAT           (0x1UL <<  3) // (SPI) Chip Select Active After Transfer
#define AT91C_SPI_BITS            (0xFUL <<  4) // (SPI) Bits Per Transfer
#define 	AT91C_SPI_BITS_8                    (0x0UL <<  4)       // (SPI) 8 Bits Per transfer
#define 	AT91C_SPI_BITS_9                    (0x1UL <<  4)       // (SPI) 9 Bits Per transfer
#define 	AT91C_SPI_BITS_10                   (0x2UL <<  4)       // (SPI) 10 Bits Per transfer
#define 	AT91C_SPI_BITS_11                   (0x3UL <<  4)       // (SPI) 11 Bits Per transfer
#define 	AT91C_SPI_BITS_12                   (0x4UL <<  4)       // (SPI) 12 Bits Per transfer
#define 	AT91C_SPI_BITS_13                   (0x5UL <<  4)       // (SPI) 13 Bits Per transfer
#define 	AT91C_SPI_BITS_14                   (0x6UL <<  4)       // (SPI) 14 Bits Per transfer
#define 	AT91C_SPI_BITS_15                   (0x7UL <<  4)       // (SPI) 15 Bits Per transfer
#define 	AT91C_SPI_BITS_16                   (0x8UL <<  4)       // (SPI) 16 Bits Per transfer
#define AT91C_SPI_SCBR            (0xFFUL <<  8)        // (SPI) Serial Clock Baud Rate
#define AT91C_SPI_DLYBS           (0xFFUL << 16)        // (SPI) Delay Before SPCK
#define AT91C_SPI_DLYBCT          (0xFFUL << 24)        // (SPI) Delay Between Consecutive Transfers

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Analog to Digital Convertor
// *****************************************************************************
// *** Register offset in AT91S_TSC structure ***
#define TSC_CR          ( 0)    // ADC Control Register
#define TSC_MR          ( 4)    // ADC Mode Register
#define TSC_SEQ1R       ( 8)    // Channel Sequence 1 Register
#define TSC_SEQ2R       (12)    // Channel Sequence 2 Register
#define TSC_CHER        (16)    // ADC Channel Enable Register
#define TSC_CHDR        (20)    // ADC Channel Disable Register
#define TSC_CHSR        (24)    // ADC Channel Status Register
#define TSC_LCDR        (32)    // ADC Last Converted Data Register
#define TSC_IER         (36)    // ADC Interrupt Enable Register
#define TSC_IDR         (40)    // ADC Interrupt Disable Register
#define TSC_IMR         (44)    // ADC Interrupt Mask Register
#define TSC_ISR         (48)    // ADC Interrupt Status Register
#define TSC_OVER        (60)    // ADC Overrun Status Register
#define TSC_EMR         (64)    // ADC Extended Mode Register
#define TSC_CWR         (68)    // ADC Compare Window Register
#define TSC_CGR         (72)    // ADC Channel Gain Register
#define TSC_COR         (76)    // ADC Channel Offset Register
#define TSC_CDR0        (80)    // ADC Channel Data Register 0
#define TSC_CDR1        (84)    // ADC Channel Data Register 1
#define TSC_CDR2        (88)    // ADC Channel Data Register 2
#define TSC_CDR3        (92)    // ADC Channel Data Register 3
#define TSC_CDR4        (96)    // ADC Channel Data Register 4
#define TSC_CDR5        (100)   // ADC Channel Data Register 5
#define TSC_CDR6        (104)   // ADC Channel Data Register 6
#define TSC_CDR7        (108)   // ADC Channel Data Register 7
#define TSC_CDR8        (112)   // ADC Channel Data Register 8
#define TSC_CDR9        (116)   // ADC Channel Data Register 9
#define TSC_CDR10       (120)   // ADC Channel Data Register 10
#define TSC_CDR11       (124)   // ADC Channel Data Register 11
#define TSC_TSMR        (176)   // ADC Touch Screen Mode Register
#define TSC_XPOSR       (180)   // ADC Touch Screen X Posistion Register
#define TSC_YPOSR       (184)   // ADC Touch Screen Y Posistion Register
#define TSC_PRESSR      (188)   // ADC Touch Screen Pressure Register
#define TSC_TRGR        (192)   // ADC Trigger Register
#define TSC_VER         (252)   // ADC VERSION REGISTER
// -------- ADC_CR : (TSC Offset: 0x0) ADC Control Register -------- 
#define AT91C_ADC_SWRST           (0x1UL <<  0) // (TSC) Software Reset
#define AT91C_ADC_START           (0x1UL <<  1) // (TSC) Start Conversion
#define AT91C_ADC_CALIB           (0x1UL <<  2) // (TSC) Touch Screen Calibration
// -------- ADC_MR : (TSC Offset: 0x4) ADC Mode Register -------- 
#define AT91C_ADC_TRGEN           (0x1UL <<  0) // (TSC) Trigger Enable
#define 	AT91C_ADC_TRGEN_DIS                  (0x0UL)    // (TSC) Hradware triggers are disabled. Starting a conversion is only possible by software
#define 	AT91C_ADC_TRGEN_EN                   (0x1UL)    // (TSC) Hardware trigger selected by TRGSEL field is enabled.
#define AT91C_ADC_TRGSEL          (0x7UL <<  1) // (TSC) Trigger Selection
#define 	AT91C_ADC_TRGSEL_EXT                  (0x0UL <<  1)     // (TSC) Selected TRGSEL = External Trigger
#define 	AT91C_ADC_TRGSEL_TIOA0                (0x1UL <<  1)     // (TSC) Selected TRGSEL = TIAO0
#define 	AT91C_ADC_TRGSEL_TRIG_SEL2            (0x2UL <<  1)     // (TSC) Selected TRGSEL = Trigger Selection 2
#define 	AT91C_ADC_TRGSEL_TRIG_SEL3            (0x3UL <<  1)     // (TSC) Selected TRGSEL = Trigger Selection 3
#define 	AT91C_ADC_TRGSEL_TRIG_SEL4            (0x4UL <<  1)     // (TSC) Selected TRGSEL = Trigger Selection 4
#define 	AT91C_ADC_TRGSEL_TRIG_SEL5            (0x5UL <<  1)     // (TSC) Selected TRGSEL = Trigger Selection 5
#define 	AT91C_ADC_TRGSEL_TRIG_SEL6            (0x6UL <<  1)     // (TSC) Selected TRGSEL = Trigger Selection 6
#define 	AT91C_ADC_TRGSEL_RESERVED             (0x7UL <<  1)     // (TSC) Selected TRGSEL = Reserved
#define AT91C_ADC_LOWRES          (0x1UL <<  4) // (TSC) Resolution.
#define 	AT91C_ADC_LOWRES_10_BIT               (0x0UL <<  4)     // (TSC) 10-bit resolution
#define 	AT91C_ADC_LOWRES_8_BIT                (0x1UL <<  4)     // (TSC) 8-bit resolution
#define AT91C_ADC_SLEEP           (0x1UL <<  5) // (TSC) Sleep Mode
#define 	AT91C_ADC_SLEEP_NORMAL_MODE          (0x0UL <<  5)      // (TSC) Normal Mode
#define 	AT91C_ADC_SLEEP_SLEEP_MODE           (0x1UL <<  5)      // (TSC) Sleep Mode
#define AT91C_ADC_FWUP            (0x1UL <<  6) // (TSC) Fast Wake Up
#define 	AT91C_ADC_FWUP_NORMAL_MODE          (0x0UL <<  6)       // (TSC) Normal Mode
#define 	AT91C_ADC_FWUP_FAST_MODE            (0x1UL <<  6)       // (TSC) Fast Wake Up Mode
#define AT91C_ADC_FREERUN         (0x1UL <<  7) // (TSC) Free Run Mode
#define 	AT91C_ADC_FREERUN_NORMAL_MODE          (0x0UL <<  7)    // (TSC) Normal Mode
#define 	AT91C_ADC_FREERUN_FREE_MODE            (0x1UL <<  7)    // (TSC) Free Run Mode Mode : Never wait for any trigger
#define AT91C_ADC_PRESCAL         (0xFFUL <<  8)        // (TSC) Prescaler rate selection
#define AT91C_ADC_STARTUP         (0xFUL << 16) // (TSC) Startup Time
#define AT91C_ADC_SETTLING        (0x3UL << 20) // (TSC) Analog Settling Time
#define AT91C_ADC_ANACH           (0x1UL << 23) // (TSC) Analog Change
#define 	AT91C_ADC_ANACH_DIS                  (0x0UL << 23)      // (TSC) No analog change on channel switching: DIFF0, GAIN0 and OFF0are used for all channels.
#define 	AT91C_ADC_ANACH_ENA                  (0x1UL << 23)      // (TSC) Allows different analog setting for each channels.
#define AT91C_ADC_TRACKTIM        (0xFUL << 24) // (TSC) Tracking Time
#define AT91C_ADC_TRANSFER        (0x3UL << 28) // (TSC) Transfer Time
#define AT91C_ADC_USEQ            (0x1UL << 31) // (TSC) User Sequence Enable
#define 	AT91C_ADC_USEQ_NORMAL               (0x0UL << 31)       // (TSC) The controller converts channels in a simple numeric order
#define 	AT91C_ADC_USEQ_USER                 (0x1UL << 31)       // (TSC) The sequence respects that is defined in ADC_SEQ1R and ADC_SEQ2R registers
// --------     ADC_SEQ1R : (TSC Offset: 0x8) ADC Channel Channel Sequence 1 Register -------- 
#define AT91C_ADC_1STCH           (0xFUL <<  0) // (TSC) First Channel of the Sequence
#define 	AT91C_ADC_1STCH_CH0                  (0x0UL)    // (TSC) First channel is CH0
#define 	AT91C_ADC_1STCH_CH1                  (0x1UL)    // (TSC) First channel is CH1
#define 	AT91C_ADC_1STCH_CH2                  (0x2UL)    // (TSC) First channel is CH2
#define 	AT91C_ADC_1STCH_CH3                  (0x3UL)    // (TSC) First channel is CH3
#define 	AT91C_ADC_1STCH_CH4                  (0x4UL)    // (TSC) First channel is CH4
#define 	AT91C_ADC_1STCH_CH5                  (0x5UL)    // (TSC) First channel is CH5
#define 	AT91C_ADC_1STCH_CH6                  (0x6UL)    // (TSC) First channel is CH6
#define 	AT91C_ADC_1STCH_CH7                  (0x7UL)    // (TSC) First channel is CH7
#define 	AT91C_ADC_1STCH_CH8                  (0x8UL)    // (TSC) First channel is CH8
#define 	AT91C_ADC_1STCH_CH9                  (0x9UL)    // (TSC) First channel is CH9
#define 	AT91C_ADC_1STCH_CH10                 (0xAUL)    // (TSC) First channel is CH10
#define 	AT91C_ADC_1STCH_CH11                 (0xBUL)    // (TSC) First channel is CH11
#define AT91C_ADC_2NDCH           (0xFUL <<  4) // (TSC) Second Channel of the Sequence
#define 	AT91C_ADC_2NDCH_CH0                  (0x0UL <<  4)      // (TSC) Second channel is CH0
#define 	AT91C_ADC_2NDCH_CH1                  (0x1UL <<  4)      // (TSC) Second channel is CH1
#define 	AT91C_ADC_2NDCH_CH2                  (0x2UL <<  4)      // (TSC) Second channel is CH2
#define 	AT91C_ADC_2NDCH_CH3                  (0x3UL <<  4)      // (TSC) Second channel is CH3
#define 	AT91C_ADC_2NDCH_CH4                  (0x4UL <<  4)      // (TSC) Second channel is CH4
#define 	AT91C_ADC_2NDCH_CH5                  (0x5UL <<  4)      // (TSC) Second channel is CH5
#define 	AT91C_ADC_2NDCH_CH6                  (0x6UL <<  4)      // (TSC) Second channel is CH6
#define 	AT91C_ADC_2NDCH_CH7                  (0x7UL <<  4)      // (TSC) Second channel is CH7
#define 	AT91C_ADC_2NDCH_CH8                  (0x8UL <<  4)      // (TSC) Second channel is CH8
#define 	AT91C_ADC_2NDCH_CH9                  (0x9UL <<  4)      // (TSC) Second channel is CH9
#define 	AT91C_ADC_2NDCH_CH10                 (0xAUL <<  4)      // (TSC) Second channel is CH10
#define 	AT91C_ADC_2NDCH_CH11                 (0xBUL <<  4)      // (TSC) Second channel is CH11
#define AT91C_ADC_3RDCH           (0xFUL <<  8) // (TSC) Third Channel of the Sequence
#define 	AT91C_ADC_3RDCH_CH0                  (0x0UL <<  8)      // (TSC) Third channel is CH0
#define 	AT91C_ADC_3RDCH_CH1                  (0x1UL <<  8)      // (TSC) Third channel is CH1
#define 	AT91C_ADC_3RDCH_CH2                  (0x2UL <<  8)      // (TSC) Third channel is CH2
#define 	AT91C_ADC_3RDCH_CH3                  (0x3UL <<  8)      // (TSC) Third channel is CH3
#define 	AT91C_ADC_3RDCH_CH4                  (0x4UL <<  8)      // (TSC) Third channel is CH4
#define 	AT91C_ADC_3RDCH_CH5                  (0x5UL <<  8)      // (TSC) Third channel is CH5
#define 	AT91C_ADC_3RDCH_CH6                  (0x6UL <<  8)      // (TSC) Third channel is CH6
#define 	AT91C_ADC_3RDCH_CH7                  (0x7UL <<  8)      // (TSC) Third channel is CH7
#define 	AT91C_ADC_3RDCH_CH8                  (0x8UL <<  8)      // (TSC) Third channel is CH8
#define 	AT91C_ADC_3RDCH_CH9                  (0x9UL <<  8)      // (TSC) Third channel is CH9
#define 	AT91C_ADC_3RDCH_CH10                 (0xAUL <<  8)      // (TSC) Third channel is CH10
#define 	AT91C_ADC_3RDCH_CH11                 (0xBUL <<  8)      // (TSC) Third channel is CH11
#define AT91C_ADC_4THCH           (0xFUL << 12) // (TSC) Fourth Channel of the Sequence
#define 	AT91C_ADC_4THCH_CH0                  (0x0UL << 12)      // (TSC) Fourth channel is CH0
#define 	AT91C_ADC_4THCH_CH1                  (0x1UL << 12)      // (TSC) Fourth channel is CH1
#define 	AT91C_ADC_4THCH_CH2                  (0x2UL << 12)      // (TSC) Fourth channel is CH2
#define 	AT91C_ADC_4THCH_CH3                  (0x3UL << 12)      // (TSC) Fourth channel is CH3
#define 	AT91C_ADC_4THCH_CH4                  (0x4UL << 12)      // (TSC) Fourth channel is CH4
#define 	AT91C_ADC_4THCH_CH5                  (0x5UL << 12)      // (TSC) Fourth channel is CH5
#define 	AT91C_ADC_4THCH_CH6                  (0x6UL << 12)      // (TSC) Fourth channel is CH6
#define 	AT91C_ADC_4THCH_CH7                  (0x7UL << 12)      // (TSC) Fourth channel is CH7
#define 	AT91C_ADC_4THCH_CH8                  (0x8UL << 12)      // (TSC) Fourth channel is CH8
#define 	AT91C_ADC_4THCH_CH9                  (0x9UL << 12)      // (TSC) Fourth channel is CH9
#define 	AT91C_ADC_4THCH_CH10                 (0xAUL << 12)      // (TSC) Fourth channel is CH10
#define 	AT91C_ADC_4THCH_CH11                 (0xBUL << 12)      // (TSC) Fourth channel is CH11
#define AT91C_ADC_5THCH           (0xFUL << 16) // (TSC) Fifth Channel of the Sequence
#define 	AT91C_ADC_5THCH_CH0                  (0x0UL << 16)      // (TSC) Fifth channel is CH0
#define 	AT91C_ADC_5THCH_CH1                  (0x1UL << 16)      // (TSC) Fifth channel is CH1
#define 	AT91C_ADC_5THCH_CH2                  (0x2UL << 16)      // (TSC) Fifth channel is CH2
#define 	AT91C_ADC_5THCH_CH3                  (0x3UL << 16)      // (TSC) Fifth channel is CH3
#define 	AT91C_ADC_5THCH_CH4                  (0x4UL << 16)      // (TSC) Fifth channel is CH4
#define 	AT91C_ADC_5THCH_CH5                  (0x5UL << 16)      // (TSC) Fifth channel is CH5
#define 	AT91C_ADC_5THCH_CH6                  (0x6UL << 16)      // (TSC) Fifth channel is CH6
#define 	AT91C_ADC_5THCH_CH7                  (0x7UL << 16)      // (TSC) Fifth channel is CH7
#define 	AT91C_ADC_5THCH_CH8                  (0x8UL << 16)      // (TSC) Fifth channel is CH8
#define 	AT91C_ADC_5THCH_CH9                  (0x9UL << 16)      // (TSC) Fifth channel is CH9
#define 	AT91C_ADC_5THCH_CH10                 (0xAUL << 16)      // (TSC) Fifth channel is CH10
#define 	AT91C_ADC_5THCH_CH11                 (0xBUL << 16)      // (TSC) Fifth channel is CH11
#define AT91C_ADC_6THCH           (0xFUL << 20) // (TSC) Sixth Channel of the Sequence
#define 	AT91C_ADC_6THCH_CH0                  (0x0UL << 20)      // (TSC) Sixth channel is CH0
#define 	AT91C_ADC_6THCH_CH1                  (0x1UL << 20)      // (TSC) Sixth channel is CH1
#define 	AT91C_ADC_6THCH_CH2                  (0x2UL << 20)      // (TSC) Sixth channel is CH2
#define 	AT91C_ADC_6THCH_CH3                  (0x3UL << 20)      // (TSC) Sixth channel is CH3
#define 	AT91C_ADC_6THCH_CH4                  (0x4UL << 20)      // (TSC) Sixth channel is CH4
#define 	AT91C_ADC_6THCH_CH5                  (0x5UL << 20)      // (TSC) Sixth channel is CH5
#define 	AT91C_ADC_6THCH_CH6                  (0x6UL << 20)      // (TSC) Sixth channel is CH6
#define 	AT91C_ADC_6THCH_CH7                  (0x7UL << 20)      // (TSC) Sixth channel is CH7
#define 	AT91C_ADC_6THCH_CH8                  (0x8UL << 20)      // (TSC) Sixth channel is CH8
#define 	AT91C_ADC_6THCH_CH9                  (0x9UL << 20)      // (TSC) Sixth channel is CH9
#define 	AT91C_ADC_6THCH_CH10                 (0xAUL << 20)      // (TSC) Sixth channel is CH10
#define 	AT91C_ADC_6THCH_CH11                 (0xBUL << 20)      // (TSC) Sixth channel is CH11
#define AT91C_ADC_7THCH           (0xFUL << 24) // (TSC) Seventh Channel of the Sequence
#define 	AT91C_ADC_7THCH_CH0                  (0x0UL << 24)      // (TSC) Seventh channel is CH0
#define 	AT91C_ADC_7THCH_CH1                  (0x1UL << 24)      // (TSC) Seventh channel is CH1
#define 	AT91C_ADC_7THCH_CH2                  (0x2UL << 24)      // (TSC) Seventh channel is CH2
#define 	AT91C_ADC_7THCH_CH3                  (0x3UL << 24)      // (TSC) Seventh channel is CH3
#define 	AT91C_ADC_7THCH_CH4                  (0x4UL << 24)      // (TSC) Seventh channel is CH4
#define 	AT91C_ADC_7THCH_CH5                  (0x5UL << 24)      // (TSC) Seventh channel is CH5
#define 	AT91C_ADC_7THCH_CH6                  (0x6UL << 24)      // (TSC) Seventh channel is CH6
#define 	AT91C_ADC_7THCH_CH7                  (0x7UL << 24)      // (TSC) Seventh channel is CH7
#define 	AT91C_ADC_7THCH_CH8                  (0x8UL << 24)      // (TSC) Seventh channel is CH8
#define 	AT91C_ADC_7THCH_CH9                  (0x9UL << 24)      // (TSC) Seventh channel is CH9
#define 	AT91C_ADC_7THCH_CH10                 (0xAUL << 24)      // (TSC) Seventh channel is CH10
#define 	AT91C_ADC_7THCH_CH11                 (0xBUL << 24)      // (TSC) Seventh channel is CH11
#define AT91C_ADC_8THCH           (0xFUL << 28) // (TSC) Eighth Channel of the Sequence
#define 	AT91C_ADC_8THCH_CH0                  (0x0UL << 28)      // (TSC) Eighth channel is CH0
#define 	AT91C_ADC_8THCH_CH1                  (0x1UL << 28)      // (TSC) Eighth channel is CH1
#define 	AT91C_ADC_8THCH_CH2                  (0x2UL << 28)      // (TSC) Eighth channel is CH2
#define 	AT91C_ADC_8THCH_CH3                  (0x3UL << 28)      // (TSC) Eighth channel is CH3
#define 	AT91C_ADC_8THCH_CH4                  (0x4UL << 28)      // (TSC) Eighth channel is CH4
#define 	AT91C_ADC_8THCH_CH5                  (0x5UL << 28)      // (TSC) Eighth channel is CH5
#define 	AT91C_ADC_8THCH_CH6                  (0x6UL << 28)      // (TSC) Eighth channel is CH6
#define 	AT91C_ADC_8THCH_CH7                  (0x7UL << 28)      // (TSC) Eighth channel is CH7
#define 	AT91C_ADC_8THCH_CH8                  (0x8UL << 28)      // (TSC) Eighth channel is CH8
#define 	AT91C_ADC_8THCH_CH9                  (0x9UL << 28)      // (TSC) Eighth channel is CH9
#define 	AT91C_ADC_8THCH_CH10                 (0xAUL << 28)      // (TSC) Eighth channel is CH10
#define 	AT91C_ADC_8THCH_CH11                 (0xBUL << 28)      // (TSC) Eighth channel is CH11
// --------     ADC_SEQ2R : (TSC Offset: 0xc) ADC Channel Channel Sequence 2 Register -------- 
#define AT91C_ADC_9THCH           (0xFUL <<  0) // (TSC) Ninth Channel of the Sequence
#define 	AT91C_ADC_9THCH_CH0                  (0x0UL)    // (TSC) Ninth channel is CH0
#define 	AT91C_ADC_9THCH_CH1                  (0x1UL)    // (TSC) Ninth channel is CH1
#define 	AT91C_ADC_9THCH_CH2                  (0x2UL)    // (TSC) Ninth channel is CH2
#define 	AT91C_ADC_9THCH_CH3                  (0x3UL)    // (TSC) Ninth channel is CH3
#define 	AT91C_ADC_9THCH_CH4                  (0x4UL)    // (TSC) Ninth channel is CH4
#define 	AT91C_ADC_9THCH_CH5                  (0x5UL)    // (TSC) Ninth channel is CH5
#define 	AT91C_ADC_9THCH_CH6                  (0x6UL)    // (TSC) Ninth channel is CH6
#define 	AT91C_ADC_9THCH_CH7                  (0x7UL)    // (TSC) Ninth channel is CH7
#define 	AT91C_ADC_9THCH_CH8                  (0x8UL)    // (TSC) Ninth channel is CH8
#define 	AT91C_ADC_9THCH_CH9                  (0x9UL)    // (TSC) Ninth channel is CH9
#define 	AT91C_ADC_9THCH_CH10                 (0xAUL)    // (TSC) Ninth channel is CH10
#define 	AT91C_ADC_9THCH_CH11                 (0xBUL)    // (TSC) Ninth channel is CH11
#define AT91C_ADC_10THCH          (0xFUL <<  4) // (TSC) Tenth Channel of the Sequence
#define 	AT91C_ADC_10THCH_CH0                  (0x0UL <<  4)     // (TSC) Tenth channel is CH0
#define 	AT91C_ADC_10THCH_CH1                  (0x1UL <<  4)     // (TSC) Tenth channel is CH1
#define 	AT91C_ADC_10THCH_CH2                  (0x2UL <<  4)     // (TSC) Tenth channel is CH2
#define 	AT91C_ADC_10THCH_CH3                  (0x3UL <<  4)     // (TSC) Tenth channel is CH3
#define 	AT91C_ADC_10THCH_CH4                  (0x4UL <<  4)     // (TSC) Tenth channel is CH4
#define 	AT91C_ADC_10THCH_CH5                  (0x5UL <<  4)     // (TSC) Tenth channel is CH5
#define 	AT91C_ADC_10THCH_CH6                  (0x6UL <<  4)     // (TSC) Tenth channel is CH6
#define 	AT91C_ADC_10THCH_CH7                  (0x7UL <<  4)     // (TSC) Tenth channel is CH7
#define 	AT91C_ADC_10THCH_CH8                  (0x8UL <<  4)     // (TSC) Tenth channel is CH8
#define 	AT91C_ADC_10THCH_CH9                  (0x9UL <<  4)     // (TSC) Tenth channel is CH9
#define 	AT91C_ADC_10THCH_CH10                 (0xAUL <<  4)     // (TSC) Tenth channel is CH10
#define 	AT91C_ADC_10THCH_CH11                 (0xBUL <<  4)     // (TSC) Tenth channel is CH11
#define AT91C_ADC_11THCH          (0xFUL <<  8) // (TSC) Eleventh Channel of the Sequence
#define 	AT91C_ADC_11THCH_CH0                  (0x0UL <<  8)     // (TSC) Eleventh channel is CH0
#define 	AT91C_ADC_11THCH_CH1                  (0x1UL <<  8)     // (TSC) Eleventh channel is CH1
#define 	AT91C_ADC_11THCH_CH2                  (0x2UL <<  8)     // (TSC) Eleventh channel is CH2
#define 	AT91C_ADC_11THCH_CH3                  (0x3UL <<  8)     // (TSC) Eleventh channel is CH3
#define 	AT91C_ADC_11THCH_CH4                  (0x4UL <<  8)     // (TSC) Eleventh channel is CH4
#define 	AT91C_ADC_11THCH_CH5                  (0x5UL <<  8)     // (TSC) Eleventh channel is CH5
#define 	AT91C_ADC_11THCH_CH6                  (0x6UL <<  8)     // (TSC) Eleventh channel is CH6
#define 	AT91C_ADC_11THCH_CH7                  (0x7UL <<  8)     // (TSC) Eleventh channel is CH7
#define 	AT91C_ADC_11THCH_CH8                  (0x8UL <<  8)     // (TSC) Eleventh channel is CH8
#define 	AT91C_ADC_11THCH_CH9                  (0x9UL <<  8)     // (TSC) Eleventh channel is CH9
#define 	AT91C_ADC_11THCH_CH10                 (0xAUL <<  8)     // (TSC) Eleventh channel is CH10
#define 	AT91C_ADC_11THCH_CH11                 (0xBUL <<  8)     // (TSC) Eleventh channel is CH11
#define AT91C_ADC_12THCH          (0xFUL << 12) // (TSC) Twelfth Channel of the Sequence
#define 	AT91C_ADC_12THCH_CH0                  (0x0UL << 12)     // (TSC) Twelfth channel is CH0
#define 	AT91C_ADC_12THCH_CH1                  (0x1UL << 12)     // (TSC) Twelfth channel is CH1
#define 	AT91C_ADC_12THCH_CH2                  (0x2UL << 12)     // (TSC) Twelfth channel is CH2
#define 	AT91C_ADC_12THCH_CH3                  (0x3UL << 12)     // (TSC) Twelfth channel is CH3
#define 	AT91C_ADC_12THCH_CH4                  (0x4UL << 12)     // (TSC) Twelfth channel is CH4
#define 	AT91C_ADC_12THCH_CH5                  (0x5UL << 12)     // (TSC) Twelfth channel is CH5
#define 	AT91C_ADC_12THCH_CH6                  (0x6UL << 12)     // (TSC) Twelfth channel is CH6
#define 	AT91C_ADC_12THCH_CH7                  (0x7UL << 12)     // (TSC) Twelfth channel is CH7
#define 	AT91C_ADC_12THCH_CH8                  (0x8UL << 12)     // (TSC) Twelfth channel is CH8
#define 	AT91C_ADC_12THCH_CH9                  (0x9UL << 12)     // (TSC) Twelfth channel is CH9
#define 	AT91C_ADC_12THCH_CH10                 (0xAUL << 12)     // (TSC) Twelfth channel is CH10
#define 	AT91C_ADC_12THCH_CH11                 (0xBUL << 12)     // (TSC) Twelfth channel is CH11
#define AT91C_ADC_13THCH          (0xFUL << 16) // (TSC) Thirteenth Channel of the Sequence
#define 	AT91C_ADC_13THCH_CH0                  (0x0UL << 16)     // (TSC) Thirteenth channel is CH0
#define 	AT91C_ADC_13THCH_CH1                  (0x1UL << 16)     // (TSC) Thirteenth channel is CH1
#define 	AT91C_ADC_13THCH_CH2                  (0x2UL << 16)     // (TSC) Thirteenth channel is CH2
#define 	AT91C_ADC_13THCH_CH3                  (0x3UL << 16)     // (TSC) Thirteenth channel is CH3
#define 	AT91C_ADC_13THCH_CH4                  (0x4UL << 16)     // (TSC) Thirteenth channel is CH4
#define 	AT91C_ADC_13THCH_CH5                  (0x5UL << 16)     // (TSC) Thirteenth channel is CH5
#define 	AT91C_ADC_13THCH_CH6                  (0x6UL << 16)     // (TSC) Thirteenth channel is CH6
#define 	AT91C_ADC_13THCH_CH7                  (0x7UL << 16)     // (TSC) Thirteenth channel is CH7
#define 	AT91C_ADC_13THCH_CH8                  (0x8UL << 16)     // (TSC) Thirteenth channel is CH8
#define 	AT91C_ADC_13THCH_CH9                  (0x9UL << 16)     // (TSC) Thirteenth channel is CH9
#define 	AT91C_ADC_13THCH_CH10                 (0xAUL << 16)     // (TSC) Thirteenth channel is CH10
#define 	AT91C_ADC_13THCH_CH11                 (0xBUL << 16)     // (TSC) Thirteenth channel is CH11
#define AT91C_ADC_14THCH          (0xFUL << 20) // (TSC) Fourteenth Channel of the Sequence
#define 	AT91C_ADC_14THCH_CH0                  (0x0UL << 20)     // (TSC) Fourteenth channel is CH0
#define 	AT91C_ADC_14THCH_CH1                  (0x1UL << 20)     // (TSC) Fourteenth channel is CH1
#define 	AT91C_ADC_14THCH_CH2                  (0x2UL << 20)     // (TSC) Fourteenth channel is CH2
#define 	AT91C_ADC_14THCH_CH3                  (0x3UL << 20)     // (TSC) Fourteenth channel is CH3
#define 	AT91C_ADC_14THCH_CH4                  (0x4UL << 20)     // (TSC) Fourteenth channel is CH4
#define 	AT91C_ADC_14THCH_CH5                  (0x5UL << 20)     // (TSC) Fourteenth channel is CH5
#define 	AT91C_ADC_14THCH_CH6                  (0x6UL << 20)     // (TSC) Fourteenth channel is CH6
#define 	AT91C_ADC_14THCH_CH7                  (0x7UL << 20)     // (TSC) Fourteenth channel is CH7
#define 	AT91C_ADC_14THCH_CH8                  (0x8UL << 20)     // (TSC) Fourteenth channel is CH8
#define 	AT91C_ADC_14THCH_CH9                  (0x9UL << 20)     // (TSC) Fourteenth channel is CH9
#define 	AT91C_ADC_14THCH_CH10                 (0xAUL << 20)     // (TSC) Fourteenth channel is CH10
#define 	AT91C_ADC_14THCH_CH11                 (0xBUL << 20)     // (TSC) Fourteenth channel is CH11
#define AT91C_ADC_15THCH          (0xFUL << 24) // (TSC) Fifteenth Channel of the Sequence
#define 	AT91C_ADC_15THCH_CH0                  (0x0UL << 24)     // (TSC) Fifteenth channel is CH0
#define 	AT91C_ADC_15THCH_CH1                  (0x1UL << 24)     // (TSC) Fifteenth channel is CH1
#define 	AT91C_ADC_15THCH_CH2                  (0x2UL << 24)     // (TSC) Fifteenth channel is CH2
#define 	AT91C_ADC_15THCH_CH3                  (0x3UL << 24)     // (TSC) Fifteenth channel is CH3
#define 	AT91C_ADC_15THCH_CH4                  (0x4UL << 24)     // (TSC) Fifteenth channel is CH4
#define 	AT91C_ADC_15THCH_CH5                  (0x5UL << 24)     // (TSC) Fifteenth channel is CH5
#define 	AT91C_ADC_15THCH_CH6                  (0x6UL << 24)     // (TSC) Fifteenth channel is CH6
#define 	AT91C_ADC_15THCH_CH7                  (0x7UL << 24)     // (TSC) Fifteenth channel is CH7
#define 	AT91C_ADC_15THCH_CH8                  (0x8UL << 24)     // (TSC) Fifteenth channel is CH8
#define 	AT91C_ADC_15THCH_CH9                  (0x9UL << 24)     // (TSC) Fifteenth channel is CH9
#define 	AT91C_ADC_15THCH_CH10                 (0xAUL << 24)     // (TSC) Fifteenth channel is CH10
#define 	AT91C_ADC_15THCH_CH11                 (0xBUL << 24)     // (TSC) Fifteenth channel is CH11
#define AT91C_ADC_16THCH          (0xFUL << 28) // (TSC) Sixteenth Channel of the Sequence
#define 	AT91C_ADC_16THCH_CH0                  (0x0UL << 28)     // (TSC) Sixteenth channel is CH0
#define 	AT91C_ADC_16THCH_CH1                  (0x1UL << 28)     // (TSC) Sixteenth channel is CH1
#define 	AT91C_ADC_16THCH_CH2                  (0x2UL << 28)     // (TSC) Sixteenth channel is CH2
#define 	AT91C_ADC_16THCH_CH3                  (0x3UL << 28)     // (TSC) Sixteenth channel is CH3
#define 	AT91C_ADC_16THCH_CH4                  (0x4UL << 28)     // (TSC) Sixteenth channel is CH4
#define 	AT91C_ADC_16THCH_CH5                  (0x5UL << 28)     // (TSC) Sixteenth channel is CH5
#define 	AT91C_ADC_16THCH_CH6                  (0x6UL << 28)     // (TSC) Sixteenth channel is CH6
#define 	AT91C_ADC_16THCH_CH7                  (0x7UL << 28)     // (TSC) Sixteenth channel is CH7
#define 	AT91C_ADC_16THCH_CH8                  (0x8UL << 28)     // (TSC) Sixteenth channel is CH8
#define 	AT91C_ADC_16THCH_CH9                  (0x9UL << 28)     // (TSC) Sixteenth channel is CH9
#define 	AT91C_ADC_16THCH_CH10                 (0xAUL << 28)     // (TSC) Sixteenth channel is CH10
#define 	AT91C_ADC_16THCH_CH11                 (0xBUL << 28)     // (TSC) Sixteenth channel is CH11
// --------     ADC_CHER : (TSC Offset: 0x10) ADC Channel Enable Register -------- 
#define AT91C_ADC_CH0             (0x1UL <<  0) // (TSC) Channel 0
#define AT91C_ADC_CH1             (0x1UL <<  1) // (TSC) Channel 1
#define AT91C_ADC_CH2             (0x1UL <<  2) // (TSC) Channel 2
#define AT91C_ADC_CH3             (0x1UL <<  3) // (TSC) Channel 3
#define AT91C_ADC_CH4             (0x1UL <<  4) // (TSC) Channel 4
#define AT91C_ADC_CH5             (0x1UL <<  5) // (TSC) Channel 5
#define AT91C_ADC_CH6             (0x1UL <<  6) // (TSC) Channel 6
#define AT91C_ADC_CH7             (0x1UL <<  7) // (TSC) Channel 7
#define AT91C_ADC_CH8             (0x1UL <<  8) // (TSC) Channel 8
#define AT91C_ADC_CH9             (0x1UL <<  9) // (TSC) Channel 9
#define AT91C_ADC_CH10            (0x1UL << 10) // (TSC) Channel 10
#define AT91C_ADC_CH11            (0x1UL << 11) // (TSC) Channel 11
// --------     ADC_CHDR : (TSC Offset: 0x14) ADC Channel Disable Register -------- 
// --------     ADC_CHSR : (TSC Offset: 0x18) ADC Channel Status Register -------- 
// -------- ADC_LCDR : (TSC Offset: 0x20) ADC Last Converted Data Register -------- 
#define AT91C_ADC_LDATA           (0x3FFUL <<  0)       // (TSC) Last Data Converted
#define AT91C_ADC_CHNB            (0xFUL << 12) // (TSC) Channel Number
// -------- ADC_IER : (TSC Offset: 0x24) ADC Interrupt Enable Register -------- 
#define AT91C_ADC_EOC0            (0x1UL <<  0) // (TSC) End of Conversion
#define AT91C_ADC_EOC1            (0x1UL <<  1) // (TSC) End of Conversion
#define AT91C_ADC_EOC2            (0x1UL <<  2) // (TSC) End of Conversion
#define AT91C_ADC_EOC3            (0x1UL <<  3) // (TSC) End of Conversion
#define AT91C_ADC_EOC4            (0x1UL <<  4) // (TSC) End of Conversion
#define AT91C_ADC_EOC5            (0x1UL <<  5) // (TSC) End of Conversion
#define AT91C_ADC_EOC6            (0x1UL <<  6) // (TSC) End of Conversion
#define AT91C_ADC_EOC7            (0x1UL <<  7) // (TSC) End of Conversion
#define AT91C_ADC_EOC8            (0x1UL <<  8) // (TSC) End of Conversion
#define AT91C_ADC_EOC9            (0x1UL <<  9) // (TSC) End of Conversion
#define AT91C_ADC_EOC10           (0x1UL << 10) // (TSC) End of Conversion
#define AT91C_ADC_EOC11           (0x1UL << 11) // (TSC) End of Conversion
#define AT91C_ADC_EOC12           (0x1UL << 12) // (TSC) End of Conversion
#define AT91C_ADC_EOC13           (0x1UL << 13) // (TSC) End of Conversion
#define AT91C_ADC_EOC14           (0x1UL << 14) // (TSC) End of Conversion
#define AT91C_ADC_EOC15           (0x1UL << 15) // (TSC) End of Conversion
#define AT91C_ADC_DRDY            (0x1UL << 16) // (TSC) Data Ready
#define AT91C_ADC_GOVRE           (0x1UL << 17) // (TSC) General Overrun
#define AT91C_ADC_COMPE           (0x1UL << 18) // (TSC) Comparison Event
#define AT91C_ADC_ENDRX           (0x1UL << 19) // (TSC) End of Receiver Transfer
#define AT91C_ADC_RXBUFF          (0x1UL << 20) // (TSC) RXBUFF Interrupt
#define AT91C_ADC_XRDY            (0x1UL << 24) // (TSC) Measure XPOS Ready
#define AT91C_ADC_YRDY            (0x1UL << 25) // (TSC) Measure YPOS Ready
#define AT91C_ADC_PRDY            (0x1UL << 26) // (TSC) Measure Pressure Ready
#define AT91C_ADC_PEN             (0x1UL << 27) // (TSC) Pen Contact
#define AT91C_ADC_NOPEN           (0x1UL << 28) // (TSC) No Pen Contact
// -------- ADC_IDR : (TSC Offset: 0x28) ADC Interrupt Disable Register -------- 
// -------- ADC_IMR : (TSC Offset: 0x2c) ADC Interrupt Mask Register -------- 
// -------- ADC_ISR : (TSC Offset: 0x30) ADC Interrupt Status Register -------- 
#define AT91C_ADC_PENSTATUS       (0x1UL << 29) // (TSC) Pen detect status
// -------- ADC_OVER : (TSC Offset: 0x3c) ADC Overrun Status Register -------- 
#define AT91C_ADC_OVRE0           (0x1UL <<  0) // (TSC) Overrun Error
#define AT91C_ADC_OVRE1           (0x1UL <<  1) // (TSC) Overrun Error
#define AT91C_ADC_OVRE2           (0x1UL <<  2) // (TSC) Overrun Error
#define AT91C_ADC_OVRE3           (0x1UL <<  3) // (TSC) Overrun Error
#define AT91C_ADC_OVRE4           (0x1UL <<  4) // (TSC) Overrun Error
#define AT91C_ADC_OVRE5           (0x1UL <<  5) // (TSC) Overrun Error
#define AT91C_ADC_OVRE6           (0x1UL <<  6) // (TSC) Overrun Error
#define AT91C_ADC_OVRE7           (0x1UL <<  7) // (TSC) Overrun Error
#define AT91C_ADC_OVRE8           (0x1UL <<  8) // (TSC) Overrun Error
#define AT91C_ADC_OVRE9           (0x1UL <<  9) // (TSC) Overrun Error
#define AT91C_ADC_OVRE10          (0x1UL << 10) // (TSC) Overrun Error
#define AT91C_ADC_OVRE11          (0x1UL << 11) // (TSC) Overrun Error
#define AT91C_ADC_OVRE12          (0x1UL << 12) // (TSC) Overrun Error
#define AT91C_ADC_OVRE13          (0x1UL << 13) // (TSC) Overrun Error
#define AT91C_ADC_OVRE14          (0x1UL << 14) // (TSC) Overrun Error
#define AT91C_ADC_OVRE15          (0x1UL << 15) // (TSC) Overrun Error
// -------- ADC_EMR : (TSC Offset: 0x40) ADC Extended Mode Register -------- 
#define AT91C_ADC_CMPMODE         (0x3UL <<  0) // (TSC) Comparison Mode
#define 	AT91C_ADC_CMPMODE_LOWER                (0x0UL)  // (TSC) Generates an event when the converted data is lower than the low threshold of the window
#define 	AT91C_ADC_CMPMODE_HIGHER               (0x1UL)  // (TSC) Generates an event when the converted data is higher than the low threshold of the window
#define 	AT91C_ADC_CMPMODE_OUT                  (0x2UL)  // (TSC) Generates an event when the converted data is out of the comparison window
#define 	AT91C_ADC_CMPMODE_IN                   (0x3UL)  // (TSC) Generates an event when the converted data is in of the comparison window
#define 	AT91C_ADC_CMPMODE_CH0                  (0x0UL <<  4)    // (TSC) The channel 0 has to be compared
#define 	AT91C_ADC_CMPMODE_CH1                  (0x1UL <<  4)    // (TSC) The channel 1 has to be compared
#define 	AT91C_ADC_CMPMODE_CH2                  (0x2UL <<  4)    // (TSC) The channel 2 has to be compared
#define 	AT91C_ADC_CMPMODE_CH3                  (0x3UL <<  4)    // (TSC) The channel 3 has to be compared
#define 	AT91C_ADC_CMPMODE_CH4                  (0x4UL <<  4)    // (TSC) The channel 4 has to be compared
#define 	AT91C_ADC_CMPMODE_CH5                  (0x5UL <<  4)    // (TSC) The channel 5 has to be compared
#define 	AT91C_ADC_CMPMODE_CH6                  (0x6UL <<  4)    // (TSC) The channel 6 has to be compared
#define 	AT91C_ADC_CMPMODE_CH7                  (0x7UL <<  4)    // (TSC) The channel 7 has to be compared
#define 	AT91C_ADC_CMPMODE_CH8                  (0x8UL <<  4)    // (TSC) The channel 8 has to be compared
#define 	AT91C_ADC_CMPMODE_CH9                  (0x9UL <<  4)    // (TSC) The channel 9 has to be compared
#define 	AT91C_ADC_CMPMODE_CH10                 (0xAUL <<  4)    // (TSC) The channel 10 has to be compared
#define 	AT91C_ADC_CMPMODE_CH11                 (0xBUL <<  4)    // (TSC) The channel 11 has to be compared
#define 	AT91C_ADC_CMPMODE_CH12                 (0xCUL <<  4)    // (TSC) The channel 12 has to be compared
#define 	AT91C_ADC_CMPMODE_CH13                 (0xDUL <<  4)    // (TSC) The channel 13 has to be compared
#define 	AT91C_ADC_CMPMODE_CH14                 (0xEUL <<  4)    // (TSC) The channel 14 has to be compared
#define 	AT91C_ADC_CMPMODE_CH15                 (0xFUL <<  4)    // (TSC) The channel 15 has to be compared
#define AT91C_ADC_CMPALL          (0x1UL <<  9) // (TSC) Compare All Channels
#define 	AT91C_ADC_CMPALL_DIS                  (0x0UL <<  9)     // (TSC) Only the channel indicated in CMPSEL field is compared
#define 	AT91C_ADC_CMPALL_ENA                  (0x1UL <<  9)     // (TSC) All channels are compared
#define AT91C_ADC_CMPFILTER       (0xFUL << 12) // (TSC) Compare Event Filtering
#define 	AT91C_ADC_CMPFILTER_1                    (0x1UL << 12)  // (TSC) The channel 1 has to be compared
#define 	AT91C_ADC_CMPFILTER_2                    (0x2UL << 12)  // (TSC) The channel 2 has to be compared
#define 	AT91C_ADC_CMPFILTER_3                    (0x3UL << 12)  // (TSC) The channel 3 has to be compared
#define 	AT91C_ADC_CMPFILTER_4                    (0x4UL << 12)  // (TSC) The channel 4 has to be compared
#define 	AT91C_ADC_CMPFILTER_5                    (0x5UL << 12)  // (TSC) The channel 5 has to be compared
#define 	AT91C_ADC_CMPFILTER_6                    (0x6UL << 12)  // (TSC) The channel 6 has to be compared
#define 	AT91C_ADC_CMPFILTER_7                    (0x7UL << 12)  // (TSC) The channel 7 has to be compared
#define 	AT91C_ADC_CMPFILTER_8                    (0x8UL << 12)  // (TSC) The channel 8 has to be compared
#define 	AT91C_ADC_CMPFILTER_9                    (0x9UL << 12)  // (TSC) The channel 9 has to be compared
#define 	AT91C_ADC_CMPFILTER_10                   (0xAUL << 12)  // (TSC) The channel 10 has to be compared
#define 	AT91C_ADC_CMPFILTER_11                   (0xBUL << 12)  // (TSC) The channel 11 has to be compared
#define 	AT91C_ADC_CMPFILTER_12                   (0xCUL << 12)  // (TSC) The channel 12 has to be compared
#define 	AT91C_ADC_CMPFILTER_13                   (0xDUL << 12)  // (TSC) The channel 13 has to be compared
#define 	AT91C_ADC_CMPFILTER_14                   (0xEUL << 12)  // (TSC) The channel 14 has to be compared
#define 	AT91C_ADC_CMPFILTER_15                   (0xFUL << 12)  // (TSC) The channel 15 has to be compared
#define AT91C_ADC_TAG             (0x1UL << 24) // (TSC) Tag of ADC_LCDR register
#define 	AT91C_ADC_TAG_DIS                  (0x0UL << 24)        // (TSC) Set CHNB to zero in ADC_LCDR
#define 	AT91C_ADC_TAG_ENA                  (0x1UL << 24)        // (TSC) Append the channel number to the conversion result in ADC_LCDR register
// -------- ADC_CWR : (TSC Offset: 0x44) ADC Comparison Window Register -------- 
#define AT91C_ADC_LOWTHRES        (0xFFFUL <<  0)       // (TSC) Low Threshold
#define AT91C_ADC_HIGHTHRES       (0xFFFUL << 16)       // (TSC) High Threshold
// -------- ADC_CGR : (TSC Offset: 0x48) ADC Channel Gain Register -------- 
#define AT91C_ADC_GAIN0           (0x3UL <<  0) // (TSC) Gain for channel 0
#define 	AT91C_ADC_GAIN0_0                    (0x0UL)    // (TSC) If DIFF0 = 0 : GAIN0 = 1. If DIFF0 = 1 : GAIN0 = 0.5.
#define 	AT91C_ADC_GAIN0_1                    (0x1UL)    // (TSC) GAIN0 = 1.
#define 	AT91C_ADC_GAIN0_2                    (0x2UL)    // (TSC) GAIN0 = 2.
#define 	AT91C_ADC_GAIN0_3                    (0x3UL)    // (TSC) If DIFF0 = 0 : GAIN0 = 4. If DIFF0 = 1 : GAIN0 = 2.
#define AT91C_ADC_GAIN1           (0x3UL <<  2) // (TSC) Gain for channel 1
#define 	AT91C_ADC_GAIN1_0                    (0x0UL <<  2)      // (TSC) If DIFF1 = 0 : GAIN1 = 1. If DIFF1 = 1 : GAIN1 = 0.5.
#define 	AT91C_ADC_GAIN1_1                    (0x1UL <<  2)      // (TSC) GAIN1 = 1.
#define 	AT91C_ADC_GAIN1_2                    (0x2UL <<  2)      // (TSC) GAIN1 = 2.
#define 	AT91C_ADC_GAIN1_3                    (0x3UL <<  2)      // (TSC) If DIFF1 = 0 : GAIN1 = 4. If DIFF1 = 1 : GAIN1 = 2.
#define AT91C_ADC_GAIN2           (0x3UL <<  4) // (TSC) Gain for channel 2
#define 	AT91C_ADC_GAIN2_0                    (0x0UL <<  4)      // (TSC) If DIFF2 = 0 : GAIN2 = 1. If DIFF2 = 1 : GAIN2 = 0.5.
#define 	AT91C_ADC_GAIN2_1                    (0x1UL <<  4)      // (TSC) GAIN2 = 1.
#define 	AT91C_ADC_GAIN2_2                    (0x2UL <<  4)      // (TSC) GAIN2 = 2.
#define 	AT91C_ADC_GAIN2_3                    (0x3UL <<  4)      // (TSC) If DIFF2 = 0 : GAIN2 = 4. If DIFF2 = 1 : GAIN2 = 2.
#define AT91C_ADC_GAIN3           (0x3UL <<  6) // (TSC) Gain for channel 3
#define 	AT91C_ADC_GAIN3_0                    (0x0UL <<  6)      // (TSC) If DIFF3 = 0 : GAIN3 = 1. If DIFF3 = 1 : GAIN3 = 0.5.
#define 	AT91C_ADC_GAIN3_1                    (0x1UL <<  6)      // (TSC) GAIN3 = 1.
#define 	AT91C_ADC_GAIN3_2                    (0x2UL <<  6)      // (TSC) GAIN3 = 2.
#define 	AT91C_ADC_GAIN3_3                    (0x3UL <<  6)      // (TSC) If DIFF3 = 0 : GAIN3 = 4. If DIFF3 = 1 : GAIN3 = 2.
#define AT91C_ADC_GAIN4           (0x3UL <<  8) // (TSC) Gain for channel 4
#define 	AT91C_ADC_GAIN4_0                    (0x0UL <<  8)      // (TSC) If DIFF4 = 0 : GAIN4 = 1. If DIFF4 = 1 : GAIN4 = 0.5.
#define 	AT91C_ADC_GAIN4_1                    (0x1UL <<  8)      // (TSC) GAIN4 = 1.
#define 	AT91C_ADC_GAIN4_2                    (0x2UL <<  8)      // (TSC) GAIN4 = 2.
#define 	AT91C_ADC_GAIN4_3                    (0x3UL <<  8)      // (TSC) If DIFF4 = 0 : GAIN4 = 4. If DIFF4 = 1 : GAIN4 = 2.
#define AT91C_ADC_GAIN5           (0x3UL << 10) // (TSC) Gain for channel 5
#define 	AT91C_ADC_GAIN5_0                    (0x0UL << 10)      // (TSC) If DIFF5 = 0 : GAIN5 = 1. If DIFF5 = 1 : GAIN5 = 0.5.
#define 	AT91C_ADC_GAIN5_1                    (0x1UL << 10)      // (TSC) GAIN5 = 1.
#define 	AT91C_ADC_GAIN5_2                    (0x2UL << 10)      // (TSC) GAIN5 = 2.
#define 	AT91C_ADC_GAIN5_3                    (0x3UL << 10)      // (TSC) If DIFF5 = 0 : GAIN5 = 4. If DIFF5 = 1 : GAIN5 = 2.
#define AT91C_ADC_GAIN6           (0x3UL << 12) // (TSC) Gain for channel 6
#define 	AT91C_ADC_GAIN6_0                    (0x0UL << 12)      // (TSC) If DIFF6 = 0 : GAIN6 = 1. If DIFF6 = 1 : GAIN6 = 0.5.
#define 	AT91C_ADC_GAIN6_1                    (0x1UL << 12)      // (TSC) GAIN6 = 1.
#define 	AT91C_ADC_GAIN6_2                    (0x2UL << 12)      // (TSC) GAIN6 = 2.
#define 	AT91C_ADC_GAIN6_3                    (0x3UL << 12)      // (TSC) If DIFF6 = 0 : GAIN6 = 4. If DIFF6 = 1 : GAIN6 = 2.
#define AT91C_ADC_GAIN7           (0x3UL << 14) // (TSC) Gain for channel 7
#define 	AT91C_ADC_GAIN7_0                    (0x0UL << 14)      // (TSC) If DIFF7 = 0 : GAIN7 = 1. If DIFF7 = 1 : GAIN7 = 0.5.
#define 	AT91C_ADC_GAIN7_1                    (0x1UL << 14)      // (TSC) GAIN7 = 1.
#define 	AT91C_ADC_GAIN7_2                    (0x2UL << 14)      // (TSC) GAIN7 = 2.
#define 	AT91C_ADC_GAIN7_3                    (0x3UL << 14)      // (TSC) If DIFF7 = 0 : GAIN7 = 4. If DIFF7 = 1 : GAIN7 = 2.
#define AT91C_ADC_GAIN8           (0x3UL << 16) // (TSC) Gain for channel 8
#define 	AT91C_ADC_GAIN8_0                    (0x0UL << 16)      // (TSC) If DIFF8 = 0 : GAIN8 = 1. If DIFF8 = 1 : GAIN8 = 0.5.
#define 	AT91C_ADC_GAIN8_1                    (0x1UL << 16)      // (TSC) GAIN8 = 1.
#define 	AT91C_ADC_GAIN8_2                    (0x2UL << 16)      // (TSC) GAIN8 = 2.
#define 	AT91C_ADC_GAIN8_3                    (0x3UL << 16)      // (TSC) If DIFF8 = 0 : GAIN8 = 4. If DIFF8 = 1 : GAIN8 = 2.
#define AT91C_ADC_GAIN9           (0x3UL << 18) // (TSC) Gain for channel 9
#define 	AT91C_ADC_GAIN9_0                    (0x0UL << 18)      // (TSC) If DIFF9 = 0 : GAIN9 = 1. If DIFF9 = 1 : GAIN9 = 0.5.
#define 	AT91C_ADC_GAIN9_1                    (0x1UL << 18)      // (TSC) GAIN9 = 1.
#define 	AT91C_ADC_GAIN9_2                    (0x2UL << 18)      // (TSC) GAIN9 = 2.
#define 	AT91C_ADC_GAIN9_3                    (0x3UL << 18)      // (TSC) If DIFF9 = 0 : GAIN9 = 4. If DIFF9 = 1 : GAIN9 = 2.
// -------- ADC_COR : (TSC Offset: 0x4c) ADC Channel Offset Register -------- 
#define AT91C_ADC_OFF0            (0x1UL <<  0) // (TSC) Offset for channel 0
#define 	AT91C_ADC_OFF0_DIS                  (0x0UL)     // (TSC) No offset
#define 	AT91C_ADC_OFF0_ENA                  (0x1UL)     // (TSC) Center the analog signal on Vrefin/2 before the gain scaling. The offset applied is : (G-1)Vrefin/2
#define AT91C_ADC_OFF1            (0x1UL <<  1) // (TSC) Offset for channel 1
#define 	AT91C_ADC_OFF1_DIS                  (0x0UL <<  1)       // (TSC) No offset
#define 	AT91C_ADC_OFF1_ENA                  (0x1UL <<  1)       // (TSC) Center the analog signal on Vrefin/2 before the gain scaling. The offset applied is : (G-1)Vrefin/2
#define AT91C_ADC_OFF2            (0x1UL <<  2) // (TSC) Offset for channel 2
#define 	AT91C_ADC_OFF2_DIS                  (0x0UL <<  2)       // (TSC) No offset
#define 	AT91C_ADC_OFF2_ENA                  (0x1UL <<  2)       // (TSC) Center the analog signal on Vrefin/2 before the gain scaling. The offset applied is : (G-1)Vrefin/2
#define AT91C_ADC_OFF3            (0x1UL <<  3) // (TSC) Offset for channel 3
#define 	AT91C_ADC_OFF3_DIS                  (0x0UL <<  3)       // (TSC) No offset
#define 	AT91C_ADC_OFF3_ENA                  (0x1UL <<  3)       // (TSC) Center the analog signal on Vrefin/2 before the gain scaling. The offset applied is : (G-1)Vrefin/2
#define AT91C_ADC_OFF4            (0x1UL <<  4) // (TSC) Offset for channel 4
#define 	AT91C_ADC_OFF4_DIS                  (0x0UL <<  4)       // (TSC) No offset
#define 	AT91C_ADC_OFF4_ENA                  (0x1UL <<  4)       // (TSC) Center the analog signal on Vrefin/2 before the gain scaling. The offset applied is : (G-1)Vrefin/2
#define AT91C_ADC_OFF5            (0x1UL <<  5) // (TSC) Offset for channel 5
#define 	AT91C_ADC_OFF5_DIS                  (0x0UL <<  5)       // (TSC) No offset
#define 	AT91C_ADC_OFF5_ENA                  (0x1UL <<  5)       // (TSC) Center the analog signal on Vrefin/2 before the gain scaling. The offset applied is : (G-1)Vrefin/2
#define AT91C_ADC_OFF6            (0x1UL <<  6) // (TSC) Offset for channel 6
#define 	AT91C_ADC_OFF6_DIS                  (0x0UL <<  6)       // (TSC) No offset
#define 	AT91C_ADC_OFF6_ENA                  (0x1UL <<  6)       // (TSC) Center the analog signal on Vrefin/2 before the gain scaling. The offset applied is : (G-1)Vrefin/2
#define AT91C_ADC_OFF7            (0x1UL <<  7) // (TSC) Offset for channel 7
#define 	AT91C_ADC_OFF7_DIS                  (0x0UL <<  7)       // (TSC) No offset
#define 	AT91C_ADC_OFF7_ENA                  (0x1UL <<  7)       // (TSC) Center the analog signal on Vrefin/2 before the gain scaling. The offset applied is : (G-1)Vrefin/2
#define AT91C_ADC_OFF8            (0x1UL <<  8) // (TSC) Offset for channel 8
#define 	AT91C_ADC_OFF8_DIS                  (0x0UL <<  8)       // (TSC) No offset
#define 	AT91C_ADC_OFF8_ENA                  (0x1UL <<  8)       // (TSC) Center the analog signal on Vrefin/2 before the gain scaling. The offset applied is : (G-1)Vrefin/2
#define AT91C_ADC_OFF9            (0x1UL <<  9) // (TSC) Offset for channel 9
#define 	AT91C_ADC_OFF9_DIS                  (0x0UL <<  9)       // (TSC) No offset
#define 	AT91C_ADC_OFF9_ENA                  (0x1UL <<  9)       // (TSC) Center the analog signal on Vrefin/2 before the gain scaling. The offset applied is : (G-1)Vrefin/2
#define AT91C_ADC_OFF10           (0x1UL << 10) // (TSC) Offset for channel 10
#define 	AT91C_ADC_OFF10_DIS                  (0x0UL << 10)      // (TSC) No offset
#define 	AT91C_ADC_OFF10_ENA                  (0x1UL << 10)      // (TSC) Center the analog signal on Vrefin/2 before the gain scaling. The offset applied is : (G-1)Vrefin/2
#define AT91C_ADC_OFF11           (0x1UL << 11) // (TSC) Offset for channel 11
#define 	AT91C_ADC_OFF11_DIS                  (0x0UL << 11)      // (TSC) No offset
#define 	AT91C_ADC_OFF11_ENA                  (0x1UL << 11)      // (TSC) Center the analog signal on Vrefin/2 before the gain scaling. The offset applied is : (G-1)Vrefin/2
#define AT91C_ADC_OFF12           (0x1UL << 12) // (TSC) Offset for channel 12
#define 	AT91C_ADC_OFF12_DIS                  (0x0UL << 12)      // (TSC) No offset
#define 	AT91C_ADC_OFF12_ENA                  (0x1UL << 12)      // (TSC) Center the analog signal on Vrefin/2 before the gain scaling. The offset applied is : (G-1)Vrefin/2
#define AT91C_ADC_OFF13           (0x1UL << 13) // (TSC) Offset for channel 13
#define 	AT91C_ADC_OFF13_DIS                  (0x0UL << 13)      // (TSC) No offset
#define 	AT91C_ADC_OFF13_ENA                  (0x1UL << 13)      // (TSC) Center the analog signal on Vrefin/2 before the gain scaling. The offset applied is : (G-1)Vrefin/2
#define AT91C_ADC_OFF14           (0x1UL << 14) // (TSC) Offset for channel 14
#define 	AT91C_ADC_OFF14_DIS                  (0x0UL << 14)      // (TSC) No offset
#define 	AT91C_ADC_OFF14_ENA                  (0x1UL << 14)      // (TSC) Center the analog signal on Vrefin/2 before the gain scaling. The offset applied is : (G-1)Vrefin/2
#define AT91C_ADC_OFF15           (0x1UL << 15) // (TSC) Offset for channel 15
#define 	AT91C_ADC_OFF15_DIS                  (0x0UL << 15)      // (TSC) No offset
#define 	AT91C_ADC_OFF15_ENA                  (0x1UL << 15)      // (TSC) Center the analog signal on Vrefin/2 before the gain scaling. The offset applied is : (G-1)Vrefin/2
#define AT91C_ADC_DIFF0           (0x1UL << 16) // (TSC) Differential inputs for channel 0
#define 	AT91C_ADC_DIFF0_SINGLE               (0x0UL << 16)      // (TSC) Single ended mode
#define 	AT91C_ADC_DIFF0_DIFFERENTIAL         (0x1UL << 16)      // (TSC) Fully differential mode
#define AT91C_ADC_DIFF1           (0x1UL << 17) // (TSC) Differential inputs for channel 1
#define 	AT91C_ADC_DIFF1_SINGLE               (0x0UL << 17)      // (TSC) Single ended mode
#define 	AT91C_ADC_DIFF1_DIFFERENTIAL         (0x1UL << 17)      // (TSC) Fully differential mode
#define AT91C_ADC_DIFF2           (0x1UL << 18) // (TSC) Differential inputs for channel 2
#define 	AT91C_ADC_DIFF2_SINGLE               (0x0UL << 18)      // (TSC) Single ended mode
#define 	AT91C_ADC_DIFF2_DIFFERENTIAL         (0x1UL << 18)      // (TSC) Fully differential mode
#define AT91C_ADC_DIFF3           (0x1UL << 19) // (TSC) Differential inputs for channel 3
#define 	AT91C_ADC_DIFF3_SINGLE               (0x0UL << 19)      // (TSC) Single ended mode
#define 	AT91C_ADC_DIFF3_DIFFERENTIAL         (0x1UL << 19)      // (TSC) Fully differential mode
#define AT91C_ADC_DIFF4           (0x1UL << 20) // (TSC) Differential inputs for channel 4
#define 	AT91C_ADC_DIFF4_SINGLE               (0x0UL << 20)      // (TSC) Single ended mode
#define 	AT91C_ADC_DIFF4_DIFFERENTIAL         (0x1UL << 20)      // (TSC) Fully differential mode
#define AT91C_ADC_DIFF5           (0x1UL << 21) // (TSC) Differential inputs for channel 5
#define 	AT91C_ADC_DIFF5_SINGLE               (0x0UL << 21)      // (TSC) Single ended mode
#define 	AT91C_ADC_DIFF5_DIFFERENTIAL         (0x1UL << 21)      // (TSC) Fully differential mode
#define AT91C_ADC_DIFF6           (0x1UL << 22) // (TSC) Differential inputs for channel 6
#define 	AT91C_ADC_DIFF6_SINGLE               (0x0UL << 22)      // (TSC) Single ended mode
#define 	AT91C_ADC_DIFF6_DIFFERENTIAL         (0x1UL << 22)      // (TSC) Fully differential mode
#define AT91C_ADC_DIFF7           (0x1UL << 23) // (TSC) Differential inputs for channel 7
#define 	AT91C_ADC_DIFF7_SINGLE               (0x0UL << 23)      // (TSC) Single ended mode
#define 	AT91C_ADC_DIFF7_DIFFERENTIAL         (0x1UL << 23)      // (TSC) Fully differential mode
#define AT91C_ADC_DIFF9           (0x1UL << 25) // (TSC) Differential inputs for channel 9
#define 	AT91C_ADC_DIFF9_SINGLE               (0x0UL << 25)      // (TSC) Single ended mode
#define 	AT91C_ADC_DIFF9_DIFFERENTIAL         (0x1UL << 25)      // (TSC) Fully differential mode
#define AT91C_ADC_DIFF10          (0x1UL << 26) // (TSC) Differential inputs for channel 10
#define 	AT91C_ADC_DIFF10_SINGLE               (0x0UL << 26)     // (TSC) Single ended mode
#define 	AT91C_ADC_DIFF10_DIFFERENTIAL         (0x1UL << 26)     // (TSC) Fully differential mode
#define AT91C_ADC_DIFF11          (0x1UL << 27) // (TSC) Differential inputs for channel 11
#define 	AT91C_ADC_DIFF11_SINGLE               (0x0UL << 27)     // (TSC) Single ended mode
#define 	AT91C_ADC_DIFF11_DIFFERENTIAL         (0x1UL << 27)     // (TSC) Fully differential mode
#define AT91C_ADC_DIFF12          (0x1UL << 28) // (TSC) Differential inputs for channel 12
#define 	AT91C_ADC_DIFF12_SINGLE               (0x0UL << 28)     // (TSC) Single ended mode
#define 	AT91C_ADC_DIFF12_DIFFERENTIAL         (0x1UL << 28)     // (TSC) Fully differential mode
#define AT91C_ADC_DIFF13          (0x1UL << 29) // (TSC) Differential inputs for channel 13
#define 	AT91C_ADC_DIFF13_SINGLE               (0x0UL << 29)     // (TSC) Single ended mode
#define 	AT91C_ADC_DIFF13_DIFFERENTIAL         (0x1UL << 29)     // (TSC) Fully differential mode
#define AT91C_ADC_DIFF14          (0x1UL << 30) // (TSC) Differential inputs for channel 14
#define 	AT91C_ADC_DIFF14_SINGLE               (0x0UL << 30)     // (TSC) Single ended mode
#define 	AT91C_ADC_DIFF14_DIFFERENTIAL         (0x1UL << 30)     // (TSC) Fully differential mode
#define AT91C_ADC_DIFF15          (0x1UL << 31) // (TSC) Differential inputs for channel 15
#define 	AT91C_ADC_DIFF15_SINGLE               (0x0UL << 31)     // (TSC) Single ended mode
#define 	AT91C_ADC_DIFF15_DIFFERENTIAL         (0x1UL << 31)     // (TSC) Fully differential mode
// -------- ADC_CDR0 : (TSC Offset: 0x50) ADC Channel Data Register 0 -------- 
#define AT91C_ADC_DATA            (0x3FFUL <<  0)       // (TSC) Converted Data
// -------- ADC_CDR1 : (TSC Offset: 0x54) ADC Channel Data Register 1 -------- 
// -------- ADC_CDR2 : (TSC Offset: 0x58) ADC Channel Data Register 2 -------- 
// -------- ADC_CDR3 : (TSC Offset: 0x5c) ADC Channel Data Register 3 -------- 
// -------- ADC_CDR4 : (TSC Offset: 0x60) ADC Channel Data Register 4 -------- 
// -------- ADC_CDR5 : (TSC Offset: 0x64) ADC Channel Data Register 5 -------- 
// -------- ADC_CDR6 : (TSC Offset: 0x68) ADC Channel Data Register 6 -------- 
// -------- ADC_CDR7 : (TSC Offset: 0x6c) ADC Channel Data Register 7 -------- 
// -------- ADC_CDR8 : (TSC Offset: 0x70) ADC Channel Data Register 8 -------- 
// -------- ADC_CDR9 : (TSC Offset: 0x74) ADC Channel Data Register 9 -------- 
// -------- ADC_CDR10 : (TSC Offset: 0x78) ADC Channel Data Register 10 -------- 
// -------- ADC_CDR11 : (TSC Offset: 0x7c) ADC Channel Data Register 11 -------- 
// -------- ADC_TSMR : (TSC Offset: 0xb0) ADC Touch Screen Mode Register -------- 
#define AT91C_ADC_TSMODE          (0x3UL <<  0) // (TSC) Touch Screen Mode
#define 	AT91C_ADC_TSMODE_NO                   (0x0UL)   // (TSC) No Touch Screen
#define 	AT91C_ADC_TSMODE_4WIRE_NO_PRESS       (0x1UL)   // (TSC) 4-wire Touch Screen without pressure measurement
#define 	AT91C_ADC_TSMODE_4WIRE_PRESS          (0x2UL)   // (TSC) 4-wire Touch Screen with pressure measurement
#define 	AT91C_ADC_TSMODE_5WIRE                (0x3UL)   // (TSC) 5-wire Touch Screen
#define AT91C_ADC_TSAV            (0x3UL <<  4) // (TSC) Touch Screen Average
#define 	AT91C_ADC_TSAV_1                    (0x0UL <<  4)       // (TSC) No filtering. Only one conversion ADC per measure
#define 	AT91C_ADC_TSAV_2                    (0x1UL <<  4)       // (TSC) Averages 2 ADC conversions
#define 	AT91C_ADC_TSAV_4                    (0x2UL <<  4)       // (TSC) Averages 4 ADC conversions
#define 	AT91C_ADC_TSAV_8                    (0x3UL <<  4)       // (TSC) Averages 8 ADC conversions
#define AT91C_ADC_TSFREQ          (0xFUL <<  8) // (TSC) Touch Screen Frequency
#define AT91C_ADC_TSSCTIM         (0xFUL << 16) // (TSC) Touch Screen switches closure time
#define AT91C_ADC_PENDET          (0x1UL << 24) // (TSC) Pen Contact Detection Enable
#define 	AT91C_ADC_PENDET_DIS                  (0x0UL << 24)     // (TSC) Pen contact detection disable
#define 	AT91C_ADC_PENDET_ENA                  (0x1UL << 24)     // (TSC) Pen contact detection enable
#define AT91C_ADC_PENDBC          (0xFUL << 28) // (TSC) Pen Detect Debuncing Period
#define 	AT91C_ADC_PENDBC_DIS                  (0x0UL << 28)     // (TSC) Pen contact detection disable
#define 	AT91C_ADC_PENDBC_ENA                  (0x1UL << 28)     // (TSC) Pen contact detection enable
// -------- ADC_XPOSR : (TSC Offset: 0xb4) Touch Screen X Position Register -------- 
#define AT91C_ADC_XPOS            (0x3FFUL <<  0)       // (TSC) X Position
#define AT91C_ADC_XSCALE          (0x3FFUL << 16)       // (TSC) Scale of X Position
// -------- ADC_YPOSR : (TSC Offset: 0xb8) Touch Screen Y Position Register -------- 
#define AT91C_ADC_YPOS            (0x3FFUL <<  0)       // (TSC) Y Position
#define AT91C_ADC_YSCALE          (0x3FFUL << 16)       // (TSC) Scale of Y Position
// -------- ADC_PRESSR : (TSC Offset: 0xbc) ADC Touch Screen Pressure Register -------- 
#define AT91C_ADC_Z1              (0x3FFUL <<  0)       // (TSC) Data of Z1 measurement
#define AT91C_ADC_Z2              (0x3FFUL << 16)       // (TSC) Data of Z2 measurement
// -------- ADC_TRGR : (TSC Offset: 0xc0) ADC Trigger Register -------- 
#define AT91C_ADC_TRGMODE         (0x7UL <<  0) // (TSC) Trigger mode
#define 	AT91C_ADC_TRGMODE_SOFT_ONLY            (0x0UL)  // (TSC) No trigger, only software trigger can start conversions
#define 	AT91C_ADC_TRGMODE_EXT_RISING           (0x1UL)  // (TSC) External trigger rising edge
#define 	AT91C_ADC_TRGMODE_EXT_FALLING          (0x2UL)  // (TSC) External trigger falling edge
#define 	AT91C_ADC_TRGMODE_EXT_ANY              (0x3UL)  // (TSC) External trigger any edge
#define 	AT91C_ADC_TRGMODE_PEN                  (0x4UL)  // (TSC) Pen detect trigger
#define 	AT91C_ADC_TRGMODE_PERIODIC             (0x5UL)  // (TSC) Periodic trigger
#define 	AT91C_ADC_TRGMODE_CONTINUOUS           (0x6UL)  // (TSC) Continuous mode
#define AT91C_ADC_TRGPER          (0xFFFFUL << 16)      // (TSC) Define the periodic trigger period
// -------- ADC_VER : (TSC Offset: 0xfc) ADC VER -------- 
#define AT91C_ADC_VER             (0xFUL <<  0) // (TSC) ADC VER

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Control Area Network MailBox Interface
// *****************************************************************************
// *** Register offset in AT91S_CAN_MB structure ***
#define CAN_MB_MMR      ( 0)    // MailBox Mode Register
#define CAN_MB_MAM      ( 4)    // MailBox Acceptance Mask Register
#define CAN_MB_MID      ( 8)    // MailBox ID Register
#define CAN_MB_MFID     (12)    // MailBox Family ID Register
#define CAN_MB_MSR      (16)    // MailBox Status Register
#define CAN_MB_MDL      (20)    // MailBox Data Low Register
#define CAN_MB_MDH      (24)    // MailBox Data High Register
#define CAN_MB_MCR      (28)    // MailBox Control Register
// -------- CAN_MMR : (CAN_MB Offset: 0x0) CAN Message Mode Register -------- 
#define AT91C_CAN_MTIMEMARK       (0xFFFFUL <<  0)      // (CAN_MB) Mailbox Timemark
#define AT91C_CAN_PRIOR           (0xFUL << 16) // (CAN_MB) Mailbox Priority
#define AT91C_CAN_MOT             (0x7UL << 24) // (CAN_MB) Mailbox Object Type
#define 	AT91C_CAN_MOT_DIS                  (0x0UL << 24)        // (CAN_MB)
#define 	AT91C_CAN_MOT_RX                   (0x1UL << 24)        // (CAN_MB)
#define 	AT91C_CAN_MOT_RXOVERWRITE          (0x2UL << 24)        // (CAN_MB)
#define 	AT91C_CAN_MOT_TX                   (0x3UL << 24)        // (CAN_MB)
#define 	AT91C_CAN_MOT_CONSUMER             (0x4UL << 24)        // (CAN_MB)
#define 	AT91C_CAN_MOT_PRODUCER             (0x5UL << 24)        // (CAN_MB)
// -------- CAN_MAM : (CAN_MB Offset: 0x4) CAN Message Acceptance Mask Register -------- 
#define AT91C_CAN_MIDvB           (0x3FFFFUL <<  0)     // (CAN_MB) Complementary bits for identifier in extended mode
#define AT91C_CAN_MIDvA           (0x7FFUL << 18)       // (CAN_MB) Identifier for standard frame mode
#define AT91C_CAN_MIDE            (0x1UL << 29) // (CAN_MB) Identifier Version
// -------- CAN_MID : (CAN_MB Offset: 0x8) CAN Message ID Register -------- 
// -------- CAN_MFID : (CAN_MB Offset: 0xc) CAN Message Family ID Register -------- 
// -------- CAN_MSR : (CAN_MB Offset: 0x10) CAN Message Status Register -------- 
#define AT91C_CAN_MTIMESTAMP      (0xFFFFUL <<  0)      // (CAN_MB) Timer Value
#define AT91C_CAN_MDLC            (0xFUL << 16) // (CAN_MB) Mailbox Data Length Code
#define AT91C_CAN_MRTR            (0x1UL << 20) // (CAN_MB) Mailbox Remote Transmission Request
#define AT91C_CAN_MABT            (0x1UL << 22) // (CAN_MB) Mailbox Message Abort
#define AT91C_CAN_MRDY            (0x1UL << 23) // (CAN_MB) Mailbox Ready
#define AT91C_CAN_MMI             (0x1UL << 24) // (CAN_MB) Mailbox Message Ignored
// -------- CAN_MDL : (CAN_MB Offset: 0x14) CAN Message Data Low Register -------- 
// -------- CAN_MDH : (CAN_MB Offset: 0x18) CAN Message Data High Register -------- 
// -------- CAN_MCR : (CAN_MB Offset: 0x1c) CAN Message Control Register -------- 
#define AT91C_CAN_MACR            (0x1UL << 22) // (CAN_MB) Abort Request for Mailbox
#define AT91C_CAN_MTCR            (0x1UL << 23) // (CAN_MB) Mailbox Transfer Command

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Control Area Network Interface
// *****************************************************************************
// *** Register offset in AT91S_CAN structure ***
#define CAN_MR          ( 0)    // Mode Register
#define CAN_IER         ( 4)    // Interrupt Enable Register
#define CAN_IDR         ( 8)    // Interrupt Disable Register
#define CAN_IMR         (12)    // Interrupt Mask Register
#define CAN_SR          (16)    // Status Register
#define CAN_BR          (20)    // Baudrate Register
#define CAN_TIM         (24)    // Timer Register
#define CAN_TIMESTP     (28)    // Time Stamp Register
#define CAN_ECR         (32)    // Error Counter Register
#define CAN_TCR         (36)    // Transfer Command Register
#define CAN_ACR         (40)    // Abort Command Register
#define CAN_VR          (252)   // Version Register
#define CAN_MB0         (512)   // CAN Mailbox 0
#define CAN_MB1         (544)   // CAN Mailbox 1
#define CAN_MB2         (576)   // CAN Mailbox 2
#define CAN_MB3         (608)   // CAN Mailbox 3
#define CAN_MB4         (640)   // CAN Mailbox 4
#define CAN_MB5         (672)   // CAN Mailbox 5
#define CAN_MB6         (704)   // CAN Mailbox 6
#define CAN_MB7         (736)   // CAN Mailbox 7
#define CAN_MB8         (768)   // CAN Mailbox 8
#define CAN_MB9         (800)   // CAN Mailbox 9
#define CAN_MB10        (832)   // CAN Mailbox 10
#define CAN_MB11        (864)   // CAN Mailbox 11
#define CAN_MB12        (896)   // CAN Mailbox 12
#define CAN_MB13        (928)   // CAN Mailbox 13
#define CAN_MB14        (960)   // CAN Mailbox 14
#define CAN_MB15        (992)   // CAN Mailbox 15
// -------- CAN_MR : (CAN Offset: 0x0) CAN Mode Register -------- 
#define AT91C_CAN_CANEN           (0x1UL <<  0) // (CAN) CAN Controller Enable
#define AT91C_CAN_LPM             (0x1UL <<  1) // (CAN) Disable/Enable Low Power Mode
#define AT91C_CAN_ABM             (0x1UL <<  2) // (CAN) Disable/Enable Autobaud/Listen Mode
#define AT91C_CAN_OVL             (0x1UL <<  3) // (CAN) Disable/Enable Overload Frame
#define AT91C_CAN_TEOF            (0x1UL <<  4) // (CAN) Time Stamp messages at each end of Frame
#define AT91C_CAN_TTM             (0x1UL <<  5) // (CAN) Disable/Enable Time Trigger Mode
#define AT91C_CAN_TIMFRZ          (0x1UL <<  6) // (CAN) Enable Timer Freeze
#define AT91C_CAN_DRPT            (0x1UL <<  7) // (CAN) Disable Repeat
// -------- CAN_IER : (CAN Offset: 0x4) CAN Interrupt Enable Register -------- 
#define AT91C_CAN_MB0             (0x1UL <<  0) // (CAN) Mailbox 0 Flag
#define AT91C_CAN_MB1             (0x1UL <<  1) // (CAN) Mailbox 1 Flag
#define AT91C_CAN_MB2             (0x1UL <<  2) // (CAN) Mailbox 2 Flag
#define AT91C_CAN_MB3             (0x1UL <<  3) // (CAN) Mailbox 3 Flag
#define AT91C_CAN_MB4             (0x1UL <<  4) // (CAN) Mailbox 4 Flag
#define AT91C_CAN_MB5             (0x1UL <<  5) // (CAN) Mailbox 5 Flag
#define AT91C_CAN_MB6             (0x1UL <<  6) // (CAN) Mailbox 6 Flag
#define AT91C_CAN_MB7             (0x1UL <<  7) // (CAN) Mailbox 7 Flag
#define AT91C_CAN_MB8             (0x1UL <<  8) // (CAN) Mailbox 8 Flag
#define AT91C_CAN_MB9             (0x1UL <<  9) // (CAN) Mailbox 9 Flag
#define AT91C_CAN_MB10            (0x1UL << 10) // (CAN) Mailbox 10 Flag
#define AT91C_CAN_MB11            (0x1UL << 11) // (CAN) Mailbox 11 Flag
#define AT91C_CAN_MB12            (0x1UL << 12) // (CAN) Mailbox 12 Flag
#define AT91C_CAN_MB13            (0x1UL << 13) // (CAN) Mailbox 13 Flag
#define AT91C_CAN_MB14            (0x1UL << 14) // (CAN) Mailbox 14 Flag
#define AT91C_CAN_MB15            (0x1UL << 15) // (CAN) Mailbox 15 Flag
#define AT91C_CAN_ERRA            (0x1UL << 16) // (CAN) Error Active Mode Flag
#define AT91C_CAN_WARN            (0x1UL << 17) // (CAN) Warning Limit Flag
#define AT91C_CAN_ERRP            (0x1UL << 18) // (CAN) Error Passive Mode Flag
#define AT91C_CAN_BOFF            (0x1UL << 19) // (CAN) Bus Off Mode Flag
#define AT91C_CAN_SLEEP           (0x1UL << 20) // (CAN) Sleep Flag
#define AT91C_CAN_WAKEUP          (0x1UL << 21) // (CAN) Wakeup Flag
#define AT91C_CAN_TOVF            (0x1UL << 22) // (CAN) Timer Overflow Flag
#define AT91C_CAN_TSTP            (0x1UL << 23) // (CAN) Timestamp Flag
#define AT91C_CAN_CERR            (0x1UL << 24) // (CAN) CRC Error
#define AT91C_CAN_SERR            (0x1UL << 25) // (CAN) Stuffing Error
#define AT91C_CAN_AERR            (0x1UL << 26) // (CAN) Acknowledgment Error
#define AT91C_CAN_FERR            (0x1UL << 27) // (CAN) Form Error
#define AT91C_CAN_BERR            (0x1UL << 28) // (CAN) Bit Error
// -------- CAN_IDR : (CAN Offset: 0x8) CAN Interrupt Disable Register -------- 
// -------- CAN_IMR : (CAN Offset: 0xc) CAN Interrupt Mask Register -------- 
// -------- CAN_SR : (CAN Offset: 0x10) CAN Status Register -------- 
#define AT91C_CAN_RBSY            (0x1UL << 29) // (CAN) Receiver Busy
#define AT91C_CAN_TBSY            (0x1UL << 30) // (CAN) Transmitter Busy
#define AT91C_CAN_OVLY            (0x1UL << 31) // (CAN) Overload Busy
// -------- CAN_BR : (CAN Offset: 0x14) CAN Baudrate Register -------- 
#define AT91C_CAN_PHASE2          (0x7UL <<  0) // (CAN) Phase 2 segment
#define AT91C_CAN_PHASE1          (0x7UL <<  4) // (CAN) Phase 1 segment
#define AT91C_CAN_PROPAG          (0x7UL <<  8) // (CAN) Programmation time segment
#define AT91C_CAN_SYNC            (0x3UL << 12) // (CAN) Re-synchronization jump width segment
#define AT91C_CAN_BRP             (0x7FUL << 16)        // (CAN) Baudrate Prescaler
#define AT91C_CAN_SMP             (0x1UL << 24) // (CAN) Sampling mode
// -------- CAN_TIM : (CAN Offset: 0x18) CAN Timer Register -------- 
#define AT91C_CAN_TIMER           (0xFFFFUL <<  0)      // (CAN) Timer field
// -------- CAN_TIMESTP : (CAN Offset: 0x1c) CAN Timestamp Register -------- 
// -------- CAN_ECR : (CAN Offset: 0x20) CAN Error Counter Register -------- 
#define AT91C_CAN_REC             (0xFFUL <<  0)        // (CAN) Receive Error Counter
#define AT91C_CAN_TEC             (0xFFUL << 16)        // (CAN) Transmit Error Counter
// -------- CAN_TCR : (CAN Offset: 0x24) CAN Transfer Command Register -------- 
#define AT91C_CAN_TIMRST          (0x1UL << 31) // (CAN) Timer Reset Field
// -------- CAN_ACR : (CAN Offset: 0x28) CAN Abort Command Register -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR HSSD Channel Interface
// *****************************************************************************
// *** Register offset in AT91S_HSSD structure ***
#define HSSD_POPR       ( 0)    //
#define HSSD_REV        ( 4)    //
#define HSSD_WRAP       ( 8)    //
#define HSSD_DRIVE      (12)    //
#define HSSD_ADJ        (16)    //
#define HSSD_SAMCO      (20)    //
#define HSSD_AUX        (24)    //
#define HSSD_PULSE      (28)    //
#define HSSD_DATA1L     (32)    //
#define HSSD_DATA1H     (36)    //
#define HSSD_CTRL1L     (40)    //
#define HSSD_CTRL1H     (44)    //
#define HSSD_DATA2L     (48)    //
#define HSSD_DATA2H     (52)    //
#define HSSD_CTRL2      (56)    //
#define HSSD_TRIM       (60)    //
#define HSSD_FIFOCTRL   (64)    //
#define HSSD_LVL        (68)    //
#define HSSD_ENB        (72)    //
#define HSSD_TXFIFO     (80)    //
#define HSSD_RXFIFO     (84)    //
// -------- HSSD_CONTROL_POPR : (HSSD Offset: 0x0) HSSD Control/Pop Removal Register -------- 
#define AT91C_HSSD_CONTROL_0      (0x1UL <<  0) // (HSSD) HSSD Serializer/Deserializer and DMA Engine Operation Enable
#define AT91C_HSSD_CONTROL_1      (0x1UL <<  1) // (HSSD) HSSD Power Clock Generation Enable.
#define AT91C_HSSD_CONTROL_2      (0x1UL <<  2) // (HSSD) HSSD_STATUS[2] Interrupt Enable.
#define AT91C_HSSD_CONTROL_3      (0x1UL <<  3) // (HSSD) HSSD_STATUS[3] Interrupt Enable.
#define AT91C_HSSD_CONTROL_4      (0x1UL <<  4) // (HSSD) HSSD_STATUS[4] Interrupt Enable.
#define AT91C_HSSD_CONTROL_5      (0x1UL <<  5) // (HSSD) HSSD_STATUS[5] Interrupt Enable.
#define AT91C_HSSD_CONTROL_6      (0x1UL <<  6) // (HSSD) HSSD_STATUS[6] Interrupt Enable.
#define AT91C_HSSD_CONTROL_7      (0x1UL <<  7) // (HSSD) HSSD_STATUS[7] Interrupt Enable.
// -------- HSSD_STATUS_REV : (HSSD Offset: 0x4) HSSD Status/Revision Register -------- 
#define AT91C_HSSD_STATUS0        (0x1UL <<  0) // (HSSD) HSSD Monitoring ADC Value Stored in HSSD_CTRL2[7:0]
#define AT91C_HSSD_STATUS1        (0x1UL <<  1) // (HSSD) HSSD Data Transfer Completed Across DIB Interface.
#define AT91C_HSSD_STATUS2        (0x1UL <<  2) // (HSSD) HSSD Parity Error in CTRL2
#define AT91C_HSSD_STATUS3        (0x1UL <<  3) // (HSSD) HSSD Control Data Sent Through DIB.
#define AT91C_HSSD_STATUS4        (0x1UL <<  4) // (HSSD) HSSD RX FIFO Overflow
#define AT91C_HSSD_STATUS5        (0x1UL <<  5) // (HSSD) HSSD TX FIFO Overflow
#define AT91C_HSSD_STATUS6        (0x1UL <<  6) // (HSSD) HSSD RX FIFO Not Empty.
#define AT91C_HSSD_STATUS7        (0x1UL <<  7) // (HSSD) HSSD TX FIFO Not Full
// -------- HSSD_WRAP : (HSSD Offset: 0x8) HSSD Disable Register -------- 
#define AT91C_HSSD_WRAP0T1        (0x3UL <<  0) // (HSSD) HSSD Number of Frame Bits.
#define AT91C_HSSD_WRAP2T7        (0x3FUL <<  2)        // (HSSD) HSSD Power Settings.
// -------- HSSD_DRIVE : (HSSD Offset: 0xc)  -------- 
#define AT91C_HSSD_DRIVE_0        (0x1UL <<  0) // (HSSD) SSD_STATUS[0] Interrupt Enable.
#define AT91C_HSSD_DRIVE_1        (0x1UL <<  1) // (HSSD) Direct Control of PWRCLKP, PWRCLKN Pins Enable
#define AT91C_HSSD_DRIVE_2        (0x1UL <<  2) // (HSSD) PWRCLKP Pin Value.
#define AT91C_HSSD_DRIVE_3        (0x1UL <<  3) // (HSSD) PWRCLKP Pin Value.
#define AT91C_HSSD_DRIVE_4T5      (0x3UL <<  4) // (HSSD) PWRCLKN Pin Control Select
#define AT91C_HSSD_DRIVE_6T7      (0x3UL <<  6) // (HSSD) PWRCLKP Pin Control Select.
// -------- HSSD_ADJ : (HSSD Offset: 0x10)  -------- 
#define AT91C_HSSD_ADJ_0T1        (0x3UL <<  0) // (HSSD) Register Synchronization Adjust Select
#define AT91C_HSSD_ADJ_2          (0x1UL <<  2) // (HSSD) Data Channel Operation Enable
#define AT91C_HSSD_ADJ_3          (0x1UL <<  3) // (HSSD) Power Clock Frequency Derivation Select
#define AT91C_HSSD_ADJ_4T5        (0x3UL <<  4) // (HSSD) PWM Adjust for PWRCLK
#define AT91C_HSSD_ADJ_6          (0x1UL <<  6) // (HSSD) Address Location Offset Select.
#define AT91C_HSSD_ADJ_7          (0x1UL <<  7) // (HSSD) PWRCLKP and PWRCLKN Function Swap.
// -------- HSSD_VOLC_SAMCO : (HSSD Offset: 0x14)  -------- 
#define AT91C_HSSD_VOLC_SAMCO     (0xFFUL <<  0)        // (HSSD) Primary HSSD Sample Counter.
// -------- HSSD_AUX : (HSSD Offset: 0x18)  -------- 
#define AT91C_HSSD_AUX_0          (0x1UL <<  0) // (HSSD) DMA Access Enable
#define AT91C_HSSD_AUX_1          (0x1UL <<  1) // (HSSD) Ring Detection State Machine Enable.
#define AT91C_HSSD_AUX_2          (0x1UL <<  2) // (HSSD) Ring Detect Wake Up Enable.
#define AT91C_HSSD_AUX_3          (0x1UL <<  3) // (HSSD) HSSD_AUX[6] Interrupt Enable.
#define AT91C_HSSD_AUX_4          (0x1UL <<  4) // (HSSD) Extension Pickup Wake Up Enable
#define AT91C_HSSD_AUX_5          (0x1UL <<  5) // (HSSD) HSSD_AUX[7] Interrupt Enable
#define AT91C_HSSD_AUX_6          (0x1UL <<  6) // (HSSD) Ring Detected.
#define AT91C_HSSD_AUX_7          (0x1UL <<  7) // (HSSD) Extension Handset Pickup Detected.
// -------- HSSD_PULSE : (HSSD Offset: 0x1c)  -------- 
#define AT91C_HSSD_PULSE_0T3      (0xFUL <<  0) // (HSSD) Number of Dialing Pulses
#define AT91C_HSSD_PULSE_4        (0x1UL <<  4) // (HSSD) HSSD_PULSE[6] Interrupt Enable.
#define AT91C_HSSD_PULSE_5        (0x1UL <<  5) // (HSSD) HSSD_PULSE[7] Interrupt Enable.
#define AT91C_HSSD_PULSE_6        (0x1UL <<  6) // (HSSD) Pulse Dialing Failed
#define AT91C_HSSD_PULSE_7        (0x1UL <<  7) // (HSSD) Pulse Dialing Completed Successfully.
// -------- HSSD_DATA1L : (HSSD Offset: 0x20)  -------- 
#define AT91C_HSSD_DATA1L         (0xFFUL <<  0)        // (HSSD) TX FIFO Lower Byte
// -------- HSSD_DATA1H : (HSSD Offset: 0x24)  -------- 
#define AT91C_HSSD_DATA1_H        (0xFFUL <<  8)        // (HSSD) TX FIFO Upper Byte
// -------- HSSD_CTRL1L : (HSSD Offset: 0x28)  -------- 
#define AT91C_HSSD_CTRL1_L        (0xFFUL <<  0)        // (HSSD) Control Channel Command Lower Byte.
// -------- HSSD_CTRL1H : (HSSD Offset: 0x2c)  -------- 
#define AT91C_HSSD_CTRL1_H        (0xFFUL <<  8)        // (HSSD) Control Channel Command Upper Byte
// -------- HSSD_DATA2L : (HSSD Offset: 0x30)  -------- 
#define AT91C_HSSD_DATA2_L        (0xFFUL <<  0)        // (HSSD) Data 2 Lower Byte.
// -------- HSSD_DATA2H : (HSSD Offset: 0x34)  -------- 
#define AT91C_HSSD_DATA2_H        (0xFFUL <<  8)        // (HSSD) Data 2 Upper Byte.
// -------- HSSD_CTRL2 : (HSSD Offset: 0x38)  -------- 
#define AT91C_HSSD_CTRL2          (0xFFUL <<  0)        // (HSSD) Control 2 Channel Response
// -------- HSSD_PARAM_TRIM : (HSSD Offset: 0x3c)  -------- 
#define AT91C_HSSD_PARAM_TRIM     (0xFFUL <<  0)        // (HSSD)
// -------- HSSD_FIFOCTRL : (HSSD Offset: 0x40)  -------- 
#define AT91C_HSSD_ENB_DMACONT_RX (0x1UL <<  2) // (HSSD) Enable DMA Continue for the HSSD RXFIFO.
#define AT91C_HSSD_ENB_DMACONT_TX (0x1UL <<  3) // (HSSD) Enable DMA Continue for the HSSD TXFIFO
#define AT91C_HSSD_RX_FLUSH       (0x1UL <<  6) // (HSSD) Flush the HSSD RXFIFO.
#define AT91C_HSSD_TX_FLUSH       (0x1UL <<  7) // (HSSD) Flush the HSSD TXFIFO.
#define AT91C_HSSD_ENB_FIFOIRQ    (0x1UL <<  8) // (HSSD) FIFO Interrupt Enable
#define AT91C_HSSD_FIFOIRQ_STATUS (0x1UL <<  9) // (HSSD) FIFO Interrupt.
// -------- HSSD_IRQ_LVL : (HSSD Offset: 0x44)  -------- 
#define AT91C_HSSD_IRQ_LVL        (0xFFUL <<  0)        // (HSSD) IRQ Count Level
// -------- HSSD_LPWR_CLK_ENB : (HSSD Offset: 0x48)  -------- 
#define AT91C_HSSD_LPWR_CLK_ENB   (0x1UL <<  0) // (HSSD)
#define AT91C_HSSD_LPWR_DIFF      (0x1UL <<  2) // (HSSD) HSSD Low Power Differential Receive Disable.
// -------- HSSD_TXFIFO : (HSSD Offset: 0x50)  -------- 
#define AT91C_HSSD_TXFIFO         (0xFFUL <<  0)        // (HSSD)
// -------- HSSD_RXFIFO : (HSSD Offset: 0x54)  -------- 
#define AT91C_HSSD_RXFIFO         (0xFFUL <<  0)        // (HSSD)

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR UDPHS Enpoint FIFO data register
// *****************************************************************************
// *** Register offset in AT91S_UDPHS_EPTFIFO structure ***
#define UDPHS_READEPT0  ( 0)    // FIFO Endpoint Data Register 0
#define UDPHS_READEPT1  (65536) // FIFO Endpoint Data Register 1
#define UDPHS_READEPT2  (131072)        // FIFO Endpoint Data Register 2
#define UDPHS_READEPT3  (196608)        // FIFO Endpoint Data Register 3
#define UDPHS_READEPT4  (262144)        // FIFO Endpoint Data Register 4
#define UDPHS_READEPT5  (327680)        // FIFO Endpoint Data Register 5
#define UDPHS_READEPT6  (393216)        // FIFO Endpoint Data Register 6

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR UDPHS Endpoint struct
// *****************************************************************************
// *** Register offset in AT91S_UDPHS_EPT structure ***
#define UDPHS_EPTCFG    ( 0)    // UDPHS Endpoint Config Register
#define UDPHS_EPTCTLENB ( 4)    // UDPHS Endpoint Control Enable Register
#define UDPHS_EPTCTLDIS ( 8)    // UDPHS Endpoint Control Disable Register
#define UDPHS_EPTCTL    (12)    // UDPHS Endpoint Control Register
#define UDPHS_EPTSETSTA (20)    // UDPHS Endpoint Set Status Register
#define UDPHS_EPTCLRSTA (24)    // UDPHS Endpoint Clear Status Register
#define UDPHS_EPTSTA    (28)    // UDPHS Endpoint Status Register
// -------- UDPHS_EPTCFG : (UDPHS_EPT Offset: 0x0) UDPHS Endpoint Config Register -------- 
#define AT91C_UDPHS_EPT_SIZE      (0x7UL <<  0) // (UDPHS_EPT) Endpoint Size
#define 	AT91C_UDPHS_EPT_SIZE_8                    (0x0UL)       // (UDPHS_EPT)    8 bytes
#define 	AT91C_UDPHS_EPT_SIZE_16                   (0x1UL)       // (UDPHS_EPT)   16 bytes
#define 	AT91C_UDPHS_EPT_SIZE_32                   (0x2UL)       // (UDPHS_EPT)   32 bytes
#define 	AT91C_UDPHS_EPT_SIZE_64                   (0x3UL)       // (UDPHS_EPT)   64 bytes
#define 	AT91C_UDPHS_EPT_SIZE_128                  (0x4UL)       // (UDPHS_EPT)  128 bytes
#define 	AT91C_UDPHS_EPT_SIZE_256                  (0x5UL)       // (UDPHS_EPT)  256 bytes (if possible)
#define 	AT91C_UDPHS_EPT_SIZE_512                  (0x6UL)       // (UDPHS_EPT)  512 bytes (if possible)
#define 	AT91C_UDPHS_EPT_SIZE_1024                 (0x7UL)       // (UDPHS_EPT) 1024 bytes (if possible)
#define AT91C_UDPHS_EPT_DIR       (0x1UL <<  3) // (UDPHS_EPT) Endpoint Direction 0:OUT, 1:IN
#define 	AT91C_UDPHS_EPT_DIR_OUT                  (0x0UL <<  3)  // (UDPHS_EPT) Direction OUT
#define 	AT91C_UDPHS_EPT_DIR_IN                   (0x1UL <<  3)  // (UDPHS_EPT) Direction IN
#define AT91C_UDPHS_EPT_TYPE      (0x3UL <<  4) // (UDPHS_EPT) Endpoint Type
#define 	AT91C_UDPHS_EPT_TYPE_CTL_EPT              (0x0UL <<  4) // (UDPHS_EPT) Control endpoint
#define 	AT91C_UDPHS_EPT_TYPE_ISO_EPT              (0x1UL <<  4) // (UDPHS_EPT) Isochronous endpoint
#define 	AT91C_UDPHS_EPT_TYPE_BUL_EPT              (0x2UL <<  4) // (UDPHS_EPT) Bulk endpoint
#define 	AT91C_UDPHS_EPT_TYPE_INT_EPT              (0x3UL <<  4) // (UDPHS_EPT) Interrupt endpoint
#define AT91C_UDPHS_BK_NUMBER     (0x3UL <<  6) // (UDPHS_EPT) Number of Banks
#define 	AT91C_UDPHS_BK_NUMBER_0                    (0x0UL <<  6)        // (UDPHS_EPT) Zero Bank, the EndPoint is not mapped in memory
#define 	AT91C_UDPHS_BK_NUMBER_1                    (0x1UL <<  6)        // (UDPHS_EPT) One Bank (Bank0)
#define 	AT91C_UDPHS_BK_NUMBER_2                    (0x2UL <<  6)        // (UDPHS_EPT) Double bank (Ping-Pong : Bank0 / Bank1)
#define 	AT91C_UDPHS_BK_NUMBER_3                    (0x3UL <<  6)        // (UDPHS_EPT) Triple Bank (Bank0 / Bank1 / Bank2) (if possible)
#define AT91C_UDPHS_NB_TRANS      (0x3UL <<  8) // (UDPHS_EPT) Number Of Transaction per Micro-Frame (High-Bandwidth iso only)
#define AT91C_UDPHS_EPT_MAPD      (0x1UL << 31) // (UDPHS_EPT) Endpoint Mapped (read only
// -------- UDPHS_EPTCTLENB : (UDPHS_EPT Offset: 0x4) UDPHS Endpoint Control Enable Register -------- 
#define AT91C_UDPHS_EPT_ENABL     (0x1UL <<  0) // (UDPHS_EPT) Endpoint Enable
#define AT91C_UDPHS_AUTO_VALID    (0x1UL <<  1) // (UDPHS_EPT) Packet Auto-Valid Enable/Disable
#define AT91C_UDPHS_INTDIS_DMA    (0x1UL <<  3) // (UDPHS_EPT) Endpoint Interrupts DMA Request Enable/Disable
#define AT91C_UDPHS_NYET_DIS      (0x1UL <<  4) // (UDPHS_EPT) NYET Enable/Disable
#define AT91C_UDPHS_DATAX_RX      (0x1UL <<  6) // (UDPHS_EPT) DATAx Interrupt Enable/Disable
#define AT91C_UDPHS_MDATA_RX      (0x1UL <<  7) // (UDPHS_EPT) MDATA Interrupt Enabled/Disable
#define AT91C_UDPHS_ERR_OVFLW     (0x1UL <<  8) // (UDPHS_EPT) OverFlow Error Interrupt Enable/Disable/Status
#define AT91C_UDPHS_RX_BK_RDY     (0x1UL <<  9) // (UDPHS_EPT) Received OUT Data
#define AT91C_UDPHS_TX_COMPLT     (0x1UL << 10) // (UDPHS_EPT) Transmitted IN Data Complete Interrupt Enable/Disable or Transmitted IN Data Complete (clear)
#define AT91C_UDPHS_ERR_TRANS     (0x1UL << 11) // (UDPHS_EPT) Transaction Error Interrupt Enable/Disable
#define AT91C_UDPHS_TX_PK_RDY     (0x1UL << 11) // (UDPHS_EPT) TX Packet Ready Interrupt Enable/Disable
#define AT91C_UDPHS_RX_SETUP      (0x1UL << 12) // (UDPHS_EPT) Received SETUP Interrupt Enable/Disable
#define AT91C_UDPHS_ERR_FL_ISO    (0x1UL << 12) // (UDPHS_EPT) Error Flow Clear/Interrupt Enable/Disable
#define AT91C_UDPHS_STALL_SNT     (0x1UL << 13) // (UDPHS_EPT) Stall Sent Clear
#define AT91C_UDPHS_ERR_CRISO     (0x1UL << 13) // (UDPHS_EPT) CRC error / Error NB Trans / Interrupt Enable/Disable
#define AT91C_UDPHS_NAK_IN        (0x1UL << 14) // (UDPHS_EPT) NAKIN ERROR FLUSH / Clear / Interrupt Enable/Disable
#define AT91C_UDPHS_NAK_OUT       (0x1UL << 15) // (UDPHS_EPT) NAKOUT / Clear / Interrupt Enable/Disable
#define AT91C_UDPHS_BUSY_BANK     (0x1UL << 18) // (UDPHS_EPT) Busy Bank Interrupt Enable/Disable
#define AT91C_UDPHS_SHRT_PCKT     (0x1UL << 31) // (UDPHS_EPT) Short Packet / Interrupt Enable/Disable
// -------- UDPHS_EPTCTLDIS : (UDPHS_EPT Offset: 0x8) UDPHS Endpoint Control Disable Register -------- 
#define AT91C_UDPHS_EPT_DISABL    (0x1UL <<  0) // (UDPHS_EPT) Endpoint Disable
// -------- UDPHS_EPTCTL : (UDPHS_EPT Offset: 0xc) UDPHS Endpoint Control Register -------- 
// -------- UDPHS_EPTSETSTA : (UDPHS_EPT Offset: 0x14) UDPHS Endpoint Set Status Register -------- 
#define AT91C_UDPHS_FRCESTALL     (0x1UL <<  5) // (UDPHS_EPT) Stall Handshake Request Set/Clear/Status
#define AT91C_UDPHS_KILL_BANK     (0x1UL <<  9) // (UDPHS_EPT) KILL Bank
// -------- UDPHS_EPTCLRSTA : (UDPHS_EPT Offset: 0x18) UDPHS Endpoint Clear Status Register -------- 
#define AT91C_UDPHS_TOGGLESQ      (0x1UL <<  6) // (UDPHS_EPT) Data Toggle Clear
// -------- UDPHS_EPTSTA : (UDPHS_EPT Offset: 0x1c) UDPHS Endpoint Status Register -------- 
#define AT91C_UDPHS_TOGGLESQ_STA  (0x3UL <<  6) // (UDPHS_EPT) Toggle Sequencing
#define 	AT91C_UDPHS_TOGGLESQ_STA_00                   (0x0UL <<  6)     // (UDPHS_EPT) Data0
#define 	AT91C_UDPHS_TOGGLESQ_STA_01                   (0x1UL <<  6)     // (UDPHS_EPT) Data1
#define 	AT91C_UDPHS_TOGGLESQ_STA_10                   (0x2UL <<  6)     // (UDPHS_EPT) Data2 (only for High-Bandwidth Isochronous EndPoint)
#define 	AT91C_UDPHS_TOGGLESQ_STA_11                   (0x3UL <<  6)     // (UDPHS_EPT) MData (only for High-Bandwidth Isochronous EndPoint)
#define AT91C_UDPHS_CONTROL_DIR   (0x3UL << 16) // (UDPHS_EPT)
#define 	AT91C_UDPHS_CONTROL_DIR_00                   (0x0UL << 16)      // (UDPHS_EPT) Bank 0
#define 	AT91C_UDPHS_CONTROL_DIR_01                   (0x1UL << 16)      // (UDPHS_EPT) Bank 1
#define 	AT91C_UDPHS_CONTROL_DIR_10                   (0x2UL << 16)      // (UDPHS_EPT) Bank 2
#define 	AT91C_UDPHS_CONTROL_DIR_11                   (0x3UL << 16)      // (UDPHS_EPT) Invalid
#define AT91C_UDPHS_CURRENT_BANK  (0x3UL << 16) // (UDPHS_EPT)
#define 	AT91C_UDPHS_CURRENT_BANK_00                   (0x0UL << 16)     // (UDPHS_EPT) Bank 0
#define 	AT91C_UDPHS_CURRENT_BANK_01                   (0x1UL << 16)     // (UDPHS_EPT) Bank 1
#define 	AT91C_UDPHS_CURRENT_BANK_10                   (0x2UL << 16)     // (UDPHS_EPT) Bank 2
#define 	AT91C_UDPHS_CURRENT_BANK_11                   (0x3UL << 16)     // (UDPHS_EPT) Invalid
#define AT91C_UDPHS_BUSY_BANK_STA (0x3UL << 18) // (UDPHS_EPT) Busy Bank Number
#define 	AT91C_UDPHS_BUSY_BANK_STA_00                   (0x0UL << 18)    // (UDPHS_EPT) All banks are free
#define 	AT91C_UDPHS_BUSY_BANK_STA_01                   (0x1UL << 18)    // (UDPHS_EPT) 1 busy bank
#define 	AT91C_UDPHS_BUSY_BANK_STA_10                   (0x2UL << 18)    // (UDPHS_EPT) 2 busy banks
#define 	AT91C_UDPHS_BUSY_BANK_STA_11                   (0x3UL << 18)    // (UDPHS_EPT) 3 busy banks (if possible)
#define AT91C_UDPHS_BYTE_COUNT    (0x7FFUL << 20)       // (UDPHS_EPT) UDPHS Byte Count

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR UDPHS DMA struct
// *****************************************************************************
// *** Register offset in AT91S_UDPHS_DMA structure ***
#define UDPHS_DMANXTDSC ( 0)    // UDPHS DMA Channel Next Descriptor Address
#define UDPHS_DMAADDRESS ( 4)   // UDPHS DMA Channel Address Register
#define UDPHS_DMACONTROL ( 8)   // UDPHS DMA Channel Control Register
#define UDPHS_DMASTATUS (12)    // UDPHS DMA Channel Status Register
// -------- UDPHS_DMANXTDSC : (UDPHS_DMA Offset: 0x0) UDPHS DMA Next Descriptor Address Register -------- 
#define AT91C_UDPHS_NXT_DSC_ADD   (0xFFFFFFFUL <<  4)   // (UDPHS_DMA) next Channel Descriptor
// -------- UDPHS_DMAADDRESS : (UDPHS_DMA Offset: 0x4) UDPHS DMA Channel Address Register -------- 
#define AT91C_UDPHS_BUFF_ADD      (0x0UL <<  0) // (UDPHS_DMA) starting address of a DMA Channel transfer
// -------- UDPHS_DMACONTROL : (UDPHS_DMA Offset: 0x8) UDPHS DMA Channel Control Register -------- 
#define AT91C_UDPHS_CHANN_ENB     (0x1UL <<  0) // (UDPHS_DMA) Channel Enabled
#define AT91C_UDPHS_LDNXT_DSC     (0x1UL <<  1) // (UDPHS_DMA) Load Next Channel Transfer Descriptor Enable
#define AT91C_UDPHS_END_TR_EN     (0x1UL <<  2) // (UDPHS_DMA) Buffer Close Input Enable
#define AT91C_UDPHS_END_B_EN      (0x1UL <<  3) // (UDPHS_DMA) End of DMA Buffer Packet Validation
#define AT91C_UDPHS_END_TR_IT     (0x1UL <<  4) // (UDPHS_DMA) End Of Transfer Interrupt Enable
#define AT91C_UDPHS_END_BUFFIT    (0x1UL <<  5) // (UDPHS_DMA) End Of Channel Buffer Interrupt Enable
#define AT91C_UDPHS_DESC_LD_IT    (0x1UL <<  6) // (UDPHS_DMA) Descriptor Loaded Interrupt Enable
#define AT91C_UDPHS_BURST_LCK     (0x1UL <<  7) // (UDPHS_DMA) Burst Lock Enable
#define AT91C_UDPHS_BUFF_LENGTH   (0xFFFFUL << 16)      // (UDPHS_DMA) Buffer Byte Length (write only)
// -------- UDPHS_DMASTATUS : (UDPHS_DMA Offset: 0xc) UDPHS DMA Channelx Status Register -------- 
#define AT91C_UDPHS_CHANN_ACT     (0x1UL <<  1) // (UDPHS_DMA)
#define AT91C_UDPHS_END_TR_ST     (0x1UL <<  4) // (UDPHS_DMA)
#define AT91C_UDPHS_END_BF_ST     (0x1UL <<  5) // (UDPHS_DMA)
#define AT91C_UDPHS_DESC_LDST     (0x1UL <<  6) // (UDPHS_DMA)
#define AT91C_UDPHS_BUFF_COUNT    (0xFFFFUL << 16)      // (UDPHS_DMA)

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR UDPHS High Speed Device Interface
// *****************************************************************************
// *** Register offset in AT91S_UDPHS structure ***
#define UDPHS_CTRL      ( 0)    // UDPHS Control Register
#define UDPHS_FNUM      ( 4)    // UDPHS Frame Number Register
#define UDPHS_IEN       (16)    // UDPHS Interrupt Enable Register
#define UDPHS_INTSTA    (20)    // UDPHS Interrupt Status Register
#define UDPHS_CLRINT    (24)    // UDPHS Clear Interrupt Register
#define UDPHS_EPTRST    (28)    // UDPHS Endpoints Reset Register
#define UDPHS_TSTSOFCNT (208)   // UDPHS Test SOF Counter Register
#define UDPHS_TSTCNTA   (212)   // UDPHS Test A Counter Register
#define UDPHS_TSTCNTB   (216)   // UDPHS Test B Counter Register
#define UDPHS_TSTMODREG (220)   // UDPHS Test Mode Register
#define UDPHS_TST       (224)   // UDPHS Test Register
#define UDPHS_RIPPADDRSIZE (236)        // UDPHS PADDRSIZE Register
#define UDPHS_RIPNAME1  (240)   // UDPHS Name1 Register
#define UDPHS_RIPNAME2  (244)   // UDPHS Name2 Register
#define UDPHS_IPFEATURES (248)  // UDPHS Features Register
#define UDPHS_IPVERSION (252)   // UDPHS Version Register
#define UDPHS_EPT       (256)   // UDPHS Endpoint struct
#define UDPHS_DMA       (768)   // UDPHS DMA channel struct (not use [0])
// -------- UDPHS_CTRL : (UDPHS Offset: 0x0) UDPHS Control Register -------- 
#define AT91C_UDPHS_DEV_ADDR      (0x7FUL <<  0)        // (UDPHS) UDPHS Address
#define AT91C_UDPHS_FADDR_EN      (0x1UL <<  7) // (UDPHS) Function Address Enable
#define AT91C_UDPHS_EN_UDPHS      (0x1UL <<  8) // (UDPHS) UDPHS Enable
#define AT91C_UDPHS_DETACH        (0x1UL <<  9) // (UDPHS) Detach Command
#define AT91C_UDPHS_REWAKEUP      (0x1UL << 10) // (UDPHS) Send Remote Wake Up
#define AT91C_UDPHS_PULLD_DIS     (0x1UL << 11) // (UDPHS) PullDown Disable
// -------- UDPHS_FNUM : (UDPHS Offset: 0x4) UDPHS Frame Number Register -------- 
#define AT91C_UDPHS_MICRO_FRAME_NUM (0x7UL <<  0)       // (UDPHS) Micro Frame Number
#define AT91C_UDPHS_FRAME_NUMBER  (0x7FFUL <<  3)       // (UDPHS) Frame Number as defined in the Packet Field Formats
#define AT91C_UDPHS_FNUM_ERR      (0x1UL << 31) // (UDPHS) Frame Number CRC Error
// -------- UDPHS_IEN : (UDPHS Offset: 0x10) UDPHS Interrupt Enable Register -------- 
#define AT91C_UDPHS_DET_SUSPD     (0x1UL <<  1) // (UDPHS) Suspend Interrupt Enable/Clear/Status
#define AT91C_UDPHS_MICRO_SOF     (0x1UL <<  2) // (UDPHS) Micro-SOF Interrupt Enable/Clear/Status
#define AT91C_UDPHS_IEN_SOF       (0x1UL <<  3) // (UDPHS) SOF Interrupt Enable/Clear/Status
#define AT91C_UDPHS_ENDRESET      (0x1UL <<  4) // (UDPHS) End Of Reset Interrupt Enable/Clear/Status
#define AT91C_UDPHS_WAKE_UP       (0x1UL <<  5) // (UDPHS) Wake Up CPU Interrupt Enable/Clear/Status
#define AT91C_UDPHS_ENDOFRSM      (0x1UL <<  6) // (UDPHS) End Of Resume Interrupt Enable/Clear/Status
#define AT91C_UDPHS_UPSTR_RES     (0x1UL <<  7) // (UDPHS) Upstream Resume Interrupt Enable/Clear/Status
#define AT91C_UDPHS_EPT_INT_0     (0x1UL <<  8) // (UDPHS) Endpoint 0 Interrupt Enable/Status
#define AT91C_UDPHS_EPT_INT_1     (0x1UL <<  9) // (UDPHS) Endpoint 1 Interrupt Enable/Status
#define AT91C_UDPHS_EPT_INT_2     (0x1UL << 10) // (UDPHS) Endpoint 2 Interrupt Enable/Status
#define AT91C_UDPHS_EPT_INT_3     (0x1UL << 11) // (UDPHS) Endpoint 3 Interrupt Enable/Status
#define AT91C_UDPHS_EPT_INT_4     (0x1UL << 12) // (UDPHS) Endpoint 4 Interrupt Enable/Status
#define AT91C_UDPHS_EPT_INT_5     (0x1UL << 13) // (UDPHS) Endpoint 5 Interrupt Enable/Status
#define AT91C_UDPHS_EPT_INT_6     (0x1UL << 14) // (UDPHS) Endpoint 6 Interrupt Enable/Status
#define AT91C_UDPHS_DMA_INT_1     (0x1UL << 25) // (UDPHS) DMA Channel 1 Interrupt Enable/Status
#define AT91C_UDPHS_DMA_INT_2     (0x1UL << 26) // (UDPHS) DMA Channel 2 Interrupt Enable/Status
#define AT91C_UDPHS_DMA_INT_3     (0x1UL << 27) // (UDPHS) DMA Channel 3 Interrupt Enable/Status
#define AT91C_UDPHS_DMA_INT_4     (0x1UL << 28) // (UDPHS) DMA Channel 4 Interrupt Enable/Status
#define AT91C_UDPHS_DMA_INT_5     (0x1UL << 29) // (UDPHS) DMA Channel 5 Interrupt Enable/Status
#define AT91C_UDPHS_DMA_INT_6     (0x1UL << 30) // (UDPHS) DMA Channel 6 Interrupt Enable/Status
// -------- UDPHS_INTSTA : (UDPHS Offset: 0x14) UDPHS Interrupt Status Register -------- 
#define AT91C_UDPHS_SPEED         (0x1UL <<  0) // (UDPHS) Speed Status
// -------- UDPHS_CLRINT : (UDPHS Offset: 0x18) UDPHS Clear Interrupt Register -------- 
// -------- UDPHS_EPTRST : (UDPHS Offset: 0x1c) UDPHS Endpoints Reset Register -------- 
#define AT91C_UDPHS_RST_EPT_0     (0x1UL <<  0) // (UDPHS) Endpoint Reset 0
#define AT91C_UDPHS_RST_EPT_1     (0x1UL <<  1) // (UDPHS) Endpoint Reset 1
#define AT91C_UDPHS_RST_EPT_2     (0x1UL <<  2) // (UDPHS) Endpoint Reset 2
#define AT91C_UDPHS_RST_EPT_3     (0x1UL <<  3) // (UDPHS) Endpoint Reset 3
#define AT91C_UDPHS_RST_EPT_4     (0x1UL <<  4) // (UDPHS) Endpoint Reset 4
#define AT91C_UDPHS_RST_EPT_5     (0x1UL <<  5) // (UDPHS) Endpoint Reset 5
#define AT91C_UDPHS_RST_EPT_6     (0x1UL <<  6) // (UDPHS) Endpoint Reset 6
// -------- UDPHS_TSTSOFCNT : (UDPHS Offset: 0xd0) UDPHS Test SOF Counter Register -------- 
#define AT91C_UDPHS_SOFCNTMAX     (0x3UL <<  0) // (UDPHS) SOF Counter Max Value
#define AT91C_UDPHS_SOFCTLOAD     (0x1UL <<  7) // (UDPHS) SOF Counter Load
// -------- UDPHS_TSTCNTA : (UDPHS Offset: 0xd4) UDPHS Test A Counter Register -------- 
#define AT91C_UDPHS_CNTAMAX       (0x7FFFUL <<  0)      // (UDPHS) A Counter Max Value
#define AT91C_UDPHS_CNTALOAD      (0x1UL << 15) // (UDPHS) A Counter Load
// -------- UDPHS_TSTCNTB : (UDPHS Offset: 0xd8) UDPHS Test B Counter Register -------- 
#define AT91C_UDPHS_CNTBMAX       (0x7FFFUL <<  0)      // (UDPHS) B Counter Max Value
#define AT91C_UDPHS_CNTBLOAD      (0x1UL << 15) // (UDPHS) B Counter Load
// -------- UDPHS_TSTMODREG : (UDPHS Offset: 0xdc) UDPHS Test Mode Register -------- 
#define AT91C_UDPHS_TSTMODE       (0x1FUL <<  1)        // (UDPHS) UDPHS Core TestModeReg
// -------- UDPHS_TST : (UDPHS Offset: 0xe0) UDPHS Test Register -------- 
#define AT91C_UDPHS_SPEED_CFG     (0x3UL <<  0) // (UDPHS) Speed Configuration
#define 	AT91C_UDPHS_SPEED_CFG_NM                   (0x0UL)      // (UDPHS) Normal Mode
#define 	AT91C_UDPHS_SPEED_CFG_RS                   (0x1UL)      // (UDPHS) Reserved
#define 	AT91C_UDPHS_SPEED_CFG_HS                   (0x2UL)      // (UDPHS) Force High Speed
#define 	AT91C_UDPHS_SPEED_CFG_FS                   (0x3UL)      // (UDPHS) Force Full-Speed
#define AT91C_UDPHS_TST_J         (0x1UL <<  2) // (UDPHS) TestJMode
#define AT91C_UDPHS_TST_K         (0x1UL <<  3) // (UDPHS) TestKMode
#define AT91C_UDPHS_TST_PKT       (0x1UL <<  4) // (UDPHS) TestPacketMode
#define AT91C_UDPHS_OPMODE2       (0x1UL <<  5) // (UDPHS) OpMode2
// -------- UDPHS_RIPPADDRSIZE : (UDPHS Offset: 0xec) UDPHS PADDRSIZE Register -------- 
#define AT91C_UDPHS_IPPADDRSIZE   (0x0UL <<  0) // (UDPHS) 2^UDPHSDEV_PADDR_SIZE
// -------- UDPHS_RIPNAME1 : (UDPHS Offset: 0xf0) UDPHS Name Register -------- 
#define AT91C_UDPHS_IPNAME1       (0x0UL <<  0) // (UDPHS) ASCII string HUSB
// -------- UDPHS_RIPNAME2 : (UDPHS Offset: 0xf4) UDPHS Name Register -------- 
#define AT91C_UDPHS_IPNAME2       (0x0UL <<  0) // (UDPHS) ASCII string 2DEV
// -------- UDPHS_IPFEATURES : (UDPHS Offset: 0xf8) UDPHS Features Register -------- 
#define AT91C_UDPHS_EPT_NBR_MAX   (0xFUL <<  0) // (UDPHS) Max Number of Endpoints
#define AT91C_UDPHS_DMA_CHANNEL_NBR (0x7UL <<  4)       // (UDPHS) Number of DMA Channels
#define AT91C_UDPHS_DMA_B_SIZ     (0x1UL <<  7) // (UDPHS) DMA Buffer Size
#define AT91C_UDPHS_DMA_FIFO_WORD_DEPTH (0xFUL <<  8)   // (UDPHS) DMA FIFO Depth in words
#define AT91C_UDPHS_FIFO_MAX_SIZE (0x7UL << 12) // (UDPHS) DPRAM size
#define AT91C_UDPHS_BW_DPRAM      (0x1UL << 15) // (UDPHS) DPRAM byte write capability
#define AT91C_UDPHS_DATAB16_8     (0x1UL << 16) // (UDPHS) UTMI DataBus16_8
#define AT91C_UDPHS_ISO_EPT_1     (0x1UL << 17) // (UDPHS) Endpoint 1 High Bandwidth Isochronous Capability
#define AT91C_UDPHS_ISO_EPT_2     (0x1UL << 18) // (UDPHS) Endpoint 2 High Bandwidth Isochronous Capability
#define AT91C_UDPHS_ISO_EPT_5     (0x1UL << 21) // (UDPHS) Endpoint 5 High Bandwidth Isochronous Capability
#define AT91C_UDPHS_ISO_EPT_6     (0x1UL << 22) // (UDPHS) Endpoint 6 High Bandwidth Isochronous Capability
// -------- UDPHS_IPVERSION : (UDPHS Offset: 0xfc) UDPHS Version Register -------- 
#define AT91C_UDPHS_VERSION_NUM   (0xFFFFUL <<  0)      // (UDPHS) Give the IP version
#define AT91C_UDPHS_METAL_FIX_NUM (0x7UL << 16) // (UDPHS) Give the number of metal fixes

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR 
// *****************************************************************************
// *** Register offset in AT91S_ structure ***

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR HDMA Channel structure
// *****************************************************************************
// *** Register offset in AT91S_HDMA_CH structure ***
#define HDMA_SADDR      ( 0)    // HDMA Channel Source Address Register
#define HDMA_DADDR      ( 4)    // HDMA Channel Destination Address Register
#define HDMA_DSCR       ( 8)    // HDMA Channel Descriptor Address Register
#define HDMA_CTRLA      (12)    // HDMA Channel Control A Register
#define HDMA_CTRLB      (16)    // HDMA Channel Control B Register
#define HDMA_CFG        (20)    // HDMA Channel Configuration Register
#define HDMA_SPIP       (24)    // HDMA Channel Source Picture in Picture Configuration Register
#define HDMA_DPIP       (28)    // HDMA Channel Destination Picture in Picture Configuration Register
#define HDMA_BDSCR      (32)    // HDMA Reserved
#define HDMA_CADDR      (36)    // HDMA Reserved
// -------- HDMA_SADDR : (HDMA_CH Offset: 0x0)  -------- 
#define AT91C_SADDR               (0x0UL <<  0) // (HDMA_CH)
// -------- HDMA_DADDR : (HDMA_CH Offset: 0x4)  -------- 
#define AT91C_DADDR               (0x0UL <<  0) // (HDMA_CH)
// -------- HDMA_DSCR : (HDMA_CH Offset: 0x8)  -------- 
#define AT91C_HDMA_DSCR_IF        (0x3UL <<  0) // (HDMA_CH) Select AHB-Lite Interface for current channel
#define 	AT91C_HDMA_DSCR_IF_0                    (0x0UL) // (HDMA_CH) The Buffer Transfer descriptor is fetched via AHB-Lite Interface 0.
#define 	AT91C_HDMA_DSCR_IF_1                    (0x1UL) // (HDMA_CH) The Buffer Transfer descriptor is fetched via AHB-Lite Interface 1.
#define 	AT91C_HDMA_DSCR_IF_2                    (0x2UL) // (HDMA_CH) The Buffer Transfer descriptor is fetched via AHB-Lite Interface 2.
#define 	AT91C_HDMA_DSCR_IF_3                    (0x3UL) // (HDMA_CH) The Buffer Transfer descriptor is fetched via AHB-Lite Interface 3.
#define AT91C_HDMA_DSCR           (0x3FFFFFFFUL <<  2)  // (HDMA_CH) Buffer Transfer descriptor address. This address is word aligned.
// -------- HDMA_CTRLA : (HDMA_CH Offset: 0xc)  -------- 
#define AT91C_HDMA_BTSIZE         (0xFFFFUL <<  0)      // (HDMA_CH) Buffer Transfer Size.
#define AT91C_HDMA_SCSIZE         (0x7UL << 16) // (HDMA_CH) Source Chunk Transfer Size.
#define 	AT91C_HDMA_SCSIZE_1                    (0x0UL << 16)    // (HDMA_CH) 1.
#define 	AT91C_HDMA_SCSIZE_4                    (0x1UL << 16)    // (HDMA_CH) 4.
#define 	AT91C_HDMA_SCSIZE_8                    (0x2UL << 16)    // (HDMA_CH) 8.
#define 	AT91C_HDMA_SCSIZE_16                   (0x3UL << 16)    // (HDMA_CH) 16.
#define 	AT91C_HDMA_SCSIZE_32                   (0x4UL << 16)    // (HDMA_CH) 32.
#define 	AT91C_HDMA_SCSIZE_64                   (0x5UL << 16)    // (HDMA_CH) 64.
#define 	AT91C_HDMA_SCSIZE_128                  (0x6UL << 16)    // (HDMA_CH) 128.
#define 	AT91C_HDMA_SCSIZE_256                  (0x7UL << 16)    // (HDMA_CH) 256.
#define AT91C_HDMA_DCSIZE         (0x7UL << 20) // (HDMA_CH) Destination Chunk Transfer Size
#define 	AT91C_HDMA_DCSIZE_1                    (0x0UL << 20)    // (HDMA_CH) 1.
#define 	AT91C_HDMA_DCSIZE_4                    (0x1UL << 20)    // (HDMA_CH) 4.
#define 	AT91C_HDMA_DCSIZE_8                    (0x2UL << 20)    // (HDMA_CH) 8.
#define 	AT91C_HDMA_DCSIZE_16                   (0x3UL << 20)    // (HDMA_CH) 16.
#define 	AT91C_HDMA_DCSIZE_32                   (0x4UL << 20)    // (HDMA_CH) 32.
#define 	AT91C_HDMA_DCSIZE_64                   (0x5UL << 20)    // (HDMA_CH) 64.
#define 	AT91C_HDMA_DCSIZE_128                  (0x6UL << 20)    // (HDMA_CH) 128.
#define 	AT91C_HDMA_DCSIZE_256                  (0x7UL << 20)    // (HDMA_CH) 256.
#define AT91C_HDMA_SRC_WIDTH      (0x3UL << 24) // (HDMA_CH) Source Single Transfer Size
#define 	AT91C_HDMA_SRC_WIDTH_BYTE                 (0x0UL << 24) // (HDMA_CH) BYTE.
#define 	AT91C_HDMA_SRC_WIDTH_HALFWORD             (0x1UL << 24) // (HDMA_CH) HALF-WORD.
#define 	AT91C_HDMA_SRC_WIDTH_WORD                 (0x2UL << 24) // (HDMA_CH) WORD.
#define AT91C_HDMA_DST_WIDTH      (0x3UL << 28) // (HDMA_CH) Destination Single Transfer Size
#define 	AT91C_HDMA_DST_WIDTH_BYTE                 (0x0UL << 28) // (HDMA_CH) BYTE.
#define 	AT91C_HDMA_DST_WIDTH_HALFWORD             (0x1UL << 28) // (HDMA_CH) HALF-WORD.
#define 	AT91C_HDMA_DST_WIDTH_WORD                 (0x2UL << 28) // (HDMA_CH) WORD.
#define AT91C_HDMA_DONE           (0x1UL << 31) // (HDMA_CH)
// -------- HDMA_CTRLB : (HDMA_CH Offset: 0x10)  -------- 
#define AT91C_HDMA_SIF            (0x3UL <<  0) // (HDMA_CH) Source Interface Selection Field.
#define 	AT91C_HDMA_SIF_0                    (0x0UL)     // (HDMA_CH) The Source Transfer is done via AHB-Lite Interface 0.
#define 	AT91C_HDMA_SIF_1                    (0x1UL)     // (HDMA_CH) The Source Transfer is done via AHB-Lite Interface 1.
#define 	AT91C_HDMA_SIF_2                    (0x2UL)     // (HDMA_CH) The Source Transfer is done via AHB-Lite Interface 2.
#define 	AT91C_HDMA_SIF_3                    (0x3UL)     // (HDMA_CH) The Source Transfer is done via AHB-Lite Interface 3.
#define AT91C_HDMA_DIF            (0x3UL <<  4) // (HDMA_CH) Destination Interface Selection Field.
#define 	AT91C_HDMA_DIF_0                    (0x0UL <<  4)       // (HDMA_CH) The Destination Transfer is done via AHB-Lite Interface 0.
#define 	AT91C_HDMA_DIF_1                    (0x1UL <<  4)       // (HDMA_CH) The Destination Transfer is done via AHB-Lite Interface 1.
#define 	AT91C_HDMA_DIF_2                    (0x2UL <<  4)       // (HDMA_CH) The Destination Transfer is done via AHB-Lite Interface 2.
#define 	AT91C_HDMA_DIF_3                    (0x3UL <<  4)       // (HDMA_CH) The Destination Transfer is done via AHB-Lite Interface 3.
#define AT91C_HDMA_SRC_PIP        (0x1UL <<  8) // (HDMA_CH) Source Picture-in-Picture Mode
#define 	AT91C_HDMA_SRC_PIP_DISABLE              (0x0UL <<  8)   // (HDMA_CH) Source Picture-in-Picture mode is disabled.
#define 	AT91C_HDMA_SRC_PIP_ENABLE               (0x1UL <<  8)   // (HDMA_CH) Source Picture-in-Picture mode is enabled.
#define AT91C_HDMA_DST_PIP        (0x1UL << 12) // (HDMA_CH) Destination Picture-in-Picture Mode
#define 	AT91C_HDMA_DST_PIP_DISABLE              (0x0UL << 12)   // (HDMA_CH) Destination Picture-in-Picture mode is disabled.
#define 	AT91C_HDMA_DST_PIP_ENABLE               (0x1UL << 12)   // (HDMA_CH) Destination Picture-in-Picture mode is enabled.
#define AT91C_HDMA_SRC_DSCR       (0x1UL << 16) // (HDMA_CH) Source Buffer Descriptor Fetch operation
#define 	AT91C_HDMA_SRC_DSCR_FETCH_FROM_MEM       (0x0UL << 16)  // (HDMA_CH) Source address is updated when the descriptor is fetched from the memory.
#define 	AT91C_HDMA_SRC_DSCR_FETCH_DISABLE        (0x1UL << 16)  // (HDMA_CH) Buffer Descriptor Fetch operation is disabled for the Source.
#define AT91C_HDMA_DST_DSCR       (0x1UL << 20) // (HDMA_CH) Destination Buffer Descriptor operation
#define 	AT91C_HDMA_DST_DSCR_FETCH_FROM_MEM       (0x0UL << 20)  // (HDMA_CH) Destination address is updated when the descriptor is fetched from the memory.
#define 	AT91C_HDMA_DST_DSCR_FETCH_DISABLE        (0x1UL << 20)  // (HDMA_CH) Buffer Descriptor Fetch operation is disabled for the destination.
#define AT91C_HDMA_FC             (0x7UL << 21) // (HDMA_CH) This field defines which devices controls the size of the buffer transfer, also referred as to the Flow Controller.
#define 	AT91C_HDMA_FC_MEM2MEM              (0x0UL << 21)        // (HDMA_CH) Memory-to-Memory (DMA Controller).
#define 	AT91C_HDMA_FC_MEM2PER              (0x1UL << 21)        // (HDMA_CH) Memory-to-Peripheral (DMA Controller).
#define 	AT91C_HDMA_FC_PER2MEM              (0x2UL << 21)        // (HDMA_CH) Peripheral-to-Memory (DMA Controller).
#define 	AT91C_HDMA_FC_PER2PER              (0x3UL << 21)        // (HDMA_CH) Peripheral-to-Peripheral (DMA Controller).
#define 	AT91C_HDMA_FC_PER2MEM_PER          (0x4UL << 21)        // (HDMA_CH) Peripheral-to-Memory (Peripheral).
#define 	AT91C_HDMA_FC_MEM2PER_PER          (0x5UL << 21)        // (HDMA_CH) Memory-to-Peripheral (Peripheral).
#define 	AT91C_HDMA_FC_PER2PER_PER          (0x6UL << 21)        // (HDMA_CH) Peripheral-to-Peripheral (Source Peripheral).
#define AT91C_HDMA_SRC_ADDRESS_MODE (0x3UL << 24)       // (HDMA_CH) Type of addressing mode
#define 	AT91C_HDMA_SRC_ADDRESS_MODE_INCR                 (0x0UL << 24)  // (HDMA_CH) Incrementing Mode.
#define 	AT91C_HDMA_SRC_ADDRESS_MODE_DECR                 (0x1UL << 24)  // (HDMA_CH) Decrementing Mode.
#define 	AT91C_HDMA_SRC_ADDRESS_MODE_FIXED                (0x2UL << 24)  // (HDMA_CH) Fixed Mode.
#define AT91C_HDMA_DST_ADDRESS_MODE (0x3UL << 28)       // (HDMA_CH) Type of addressing mode
#define 	AT91C_HDMA_DST_ADDRESS_MODE_INCR                 (0x0UL << 28)  // (HDMA_CH) Incrementing Mode.
#define 	AT91C_HDMA_DST_ADDRESS_MODE_DECR                 (0x1UL << 28)  // (HDMA_CH) Decrementing Mode.
#define 	AT91C_HDMA_DST_ADDRESS_MODE_FIXED                (0x2UL << 28)  // (HDMA_CH) Fixed Mode.
#define AT91C_HDMA_AUTO           (0x1UL << 31) // (HDMA_CH) Automatic multiple buffer transfer enable
#define 	AT91C_HDMA_AUTO_DISABLE              (0x0UL << 31)      // (HDMA_CH) Automatic multiple buffer transfer is disabled.
#define 	AT91C_HDMA_AUTO_ENABLE               (0x1UL << 31)      // (HDMA_CH) Automatic multiple buffer transfer is enabled. This enables replay mode or contiguous mode when several buffers are transferred.
// -------- HDMA_CFG : (HDMA_CH Offset: 0x14)  -------- 
#define AT91C_HDMA_SRC_PER        (0xFUL <<  0) // (HDMA_CH) Channel Source Request is associated with peripheral identifier coded SRC_PER handshaking interface.
#define 	AT91C_HDMA_SRC_PER_0                    (0x0UL) // (HDMA_CH) HW Handshaking Interface number 0.
#define 	AT91C_HDMA_SRC_PER_1                    (0x1UL) // (HDMA_CH) HW Handshaking Interface number 1.
#define 	AT91C_HDMA_SRC_PER_2                    (0x2UL) // (HDMA_CH) HW Handshaking Interface number 2.
#define 	AT91C_HDMA_SRC_PER_3                    (0x3UL) // (HDMA_CH) HW Handshaking Interface number 3.
#define 	AT91C_HDMA_SRC_PER_4                    (0x4UL) // (HDMA_CH) HW Handshaking Interface number 4.
#define 	AT91C_HDMA_SRC_PER_5                    (0x5UL) // (HDMA_CH) HW Handshaking Interface number 5.
#define 	AT91C_HDMA_SRC_PER_6                    (0x6UL) // (HDMA_CH) HW Handshaking Interface number 6.
#define 	AT91C_HDMA_SRC_PER_7                    (0x7UL) // (HDMA_CH) HW Handshaking Interface number 7.
#define 	AT91C_HDMA_SRC_PER_8                    (0x8UL) // (HDMA_CH) HW Handshaking Interface number 8.
#define 	AT91C_HDMA_SRC_PER_9                    (0x9UL) // (HDMA_CH) HW Handshaking Interface number 9.
#define 	AT91C_HDMA_SRC_PER_10                   (0xAUL) // (HDMA_CH) HW Handshaking Interface number 10.
#define 	AT91C_HDMA_SRC_PER_11                   (0xBUL) // (HDMA_CH) HW Handshaking Interface number 11.
#define 	AT91C_HDMA_SRC_PER_12                   (0xCUL) // (HDMA_CH) HW Handshaking Interface number 12.
#define 	AT91C_HDMA_SRC_PER_13                   (0xDUL) // (HDMA_CH) HW Handshaking Interface number 13.
#define 	AT91C_HDMA_SRC_PER_14                   (0xEUL) // (HDMA_CH) HW Handshaking Interface number 14.
#define 	AT91C_HDMA_SRC_PER_15                   (0xFUL) // (HDMA_CH) HW Handshaking Interface number 15.
#define AT91C_HDMA_DST_PER        (0xFUL <<  4) // (HDMA_CH) Channel Destination Request is associated with peripheral identifier coded DST_PER handshaking interface.
#define 	AT91C_HDMA_DST_PER_0                    (0x0UL <<  4)   // (HDMA_CH) HW Handshaking Interface number 0.
#define 	AT91C_HDMA_DST_PER_1                    (0x1UL <<  4)   // (HDMA_CH) HW Handshaking Interface number 1.
#define 	AT91C_HDMA_DST_PER_2                    (0x2UL <<  4)   // (HDMA_CH) HW Handshaking Interface number 2.
#define 	AT91C_HDMA_DST_PER_3                    (0x3UL <<  4)   // (HDMA_CH) HW Handshaking Interface number 3.
#define 	AT91C_HDMA_DST_PER_4                    (0x4UL <<  4)   // (HDMA_CH) HW Handshaking Interface number 4.
#define 	AT91C_HDMA_DST_PER_5                    (0x5UL <<  4)   // (HDMA_CH) HW Handshaking Interface number 5.
#define 	AT91C_HDMA_DST_PER_6                    (0x6UL <<  4)   // (HDMA_CH) HW Handshaking Interface number 6.
#define 	AT91C_HDMA_DST_PER_7                    (0x7UL <<  4)   // (HDMA_CH) HW Handshaking Interface number 7.
#define 	AT91C_HDMA_DST_PER_8                    (0x8UL <<  4)   // (HDMA_CH) HW Handshaking Interface number 8.
#define 	AT91C_HDMA_DST_PER_9                    (0x9UL <<  4)   // (HDMA_CH) HW Handshaking Interface number 9.
#define 	AT91C_HDMA_DST_PER_10                   (0xAUL <<  4)   // (HDMA_CH) HW Handshaking Interface number 10.
#define 	AT91C_HDMA_DST_PER_11                   (0xBUL <<  4)   // (HDMA_CH) HW Handshaking Interface number 11.
#define 	AT91C_HDMA_DST_PER_12                   (0xCUL <<  4)   // (HDMA_CH) HW Handshaking Interface number 12.
#define 	AT91C_HDMA_DST_PER_13                   (0xDUL <<  4)   // (HDMA_CH) HW Handshaking Interface number 13.
#define 	AT91C_HDMA_DST_PER_14                   (0xEUL <<  4)   // (HDMA_CH) HW Handshaking Interface number 14.
#define 	AT91C_HDMA_DST_PER_15                   (0xFUL <<  4)   // (HDMA_CH) HW Handshaking Interface number 15.
#define AT91C_HDMA_SRC_REP        (0x1UL <<  8) // (HDMA_CH) Source Replay Mode
#define 	AT91C_HDMA_SRC_REP_CONTIGUOUS_ADDR      (0x0UL <<  8)   // (HDMA_CH) When automatic mode is activated, source address is contiguous between two buffers.
#define 	AT91C_HDMA_SRC_REP_RELOAD_ADDR          (0x1UL <<  8)   // (HDMA_CH) When automatic mode is activated, the source address and the control register are reloaded from previous transfer..
#define AT91C_HDMA_SRC_H2SEL      (0x1UL <<  9) // (HDMA_CH) Source Handshaking Mode
#define 	AT91C_HDMA_SRC_H2SEL_SW                   (0x0UL <<  9) // (HDMA_CH) Software handshaking interface is used to trigger a transfer request.
#define 	AT91C_HDMA_SRC_H2SEL_HW                   (0x1UL <<  9) // (HDMA_CH) Hardware handshaking interface is used to trigger a transfer request.
#define AT91C_HDMA_DST_REP        (0x1UL << 12) // (HDMA_CH) Destination Replay Mode
#define 	AT91C_HDMA_DST_REP_CONTIGUOUS_ADDR      (0x0UL << 12)   // (HDMA_CH) When automatic mode is activated, destination address is contiguous between two buffers.
#define 	AT91C_HDMA_DST_REP_RELOAD_ADDR          (0x1UL << 12)   // (HDMA_CH) When automatic mode is activated, the destination address and the control register are reloaded from previous transfer..
#define AT91C_HDMA_DST_H2SEL      (0x1UL << 13) // (HDMA_CH) Destination Handshaking Mode
#define 	AT91C_HDMA_DST_H2SEL_SW                   (0x0UL << 13) // (HDMA_CH) Software handshaking interface is used to trigger a transfer request.
#define 	AT91C_HDMA_DST_H2SEL_HW                   (0x1UL << 13) // (HDMA_CH) Hardware handshaking interface is used to trigger a transfer request.
#define AT91C_HDMA_SOD            (0x1UL << 16) // (HDMA_CH) STOP ON DONE
#define 	AT91C_HDMA_SOD_DISABLE              (0x0UL << 16)       // (HDMA_CH) STOP ON DONE disabled, the descriptor fetch operation ignores DONE Field of CTRLA register.
#define 	AT91C_HDMA_SOD_ENABLE               (0x1UL << 16)       // (HDMA_CH) STOP ON DONE activated, the DMAC module is automatically disabled if DONE FIELD is set to 1.
#define AT91C_HDMA_LOCK_IF        (0x1UL << 20) // (HDMA_CH) Interface Lock
#define 	AT91C_HDMA_LOCK_IF_DISABLE              (0x0UL << 20)   // (HDMA_CH) Interface Lock capability is disabled.
#define 	AT91C_HDMA_LOCK_IF_ENABLE               (0x1UL << 20)   // (HDMA_CH) Interface Lock capability is enabled.
#define AT91C_HDMA_LOCK_B         (0x1UL << 21) // (HDMA_CH) AHB Bus Lock
#define 	AT91C_HDMA_LOCK_B_DISABLE              (0x0UL << 21)    // (HDMA_CH) AHB Bus Locking capability is disabled.
#define 	AT91C_HDMA_LOCK_B_ENABLE               (0x1UL << 21)    // (HDMA_CH) AHB Bus Locking capability is enabled.
#define AT91C_HDMA_LOCK_IF_L      (0x1UL << 22) // (HDMA_CH) Master Interface Arbiter Lock
#define 	AT91C_HDMA_LOCK_IF_L_CHUNK                (0x0UL << 22) // (HDMA_CH) The Master Interface Arbiter is locked by the channel x for a chunk transfer.
#define 	AT91C_HDMA_LOCK_IF_L_BUFFER               (0x1UL << 22) // (HDMA_CH) The Master Interface Arbiter is locked by the channel x for a buffer transfer.
#define AT91C_HDMA_AHB_PROT       (0x7UL << 24) // (HDMA_CH) AHB Prot
#define AT91C_HDMA_FIFOCFG        (0x3UL << 28) // (HDMA_CH) FIFO Request Configuration
#define 	AT91C_HDMA_FIFOCFG_LARGESTBURST         (0x0UL << 28)   // (HDMA_CH) The largest defined length AHB burst is performed on the destination AHB interface.
#define 	AT91C_HDMA_FIFOCFG_HALFFIFO             (0x1UL << 28)   // (HDMA_CH) When half fifo size is available/filled a source/destination request is serviced.
#define 	AT91C_HDMA_FIFOCFG_ENOUGHSPACE          (0x2UL << 28)   // (HDMA_CH) When there is enough space/data available to perfom a single AHB access then the request is serviced.
// -------- HDMA_SPIP : (HDMA_CH Offset: 0x18)  -------- 
#define AT91C_SPIP_HOLE           (0xFFFFUL <<  0)      // (HDMA_CH) This field indicates the value to add to the address when the programmable boundary has been reached.
#define AT91C_SPIP_BOUNDARY       (0x3FFUL << 16)       // (HDMA_CH) This field indicates the number of source transfers to perform before the automatic address increment operation.
// -------- HDMA_DPIP : (HDMA_CH Offset: 0x1c)  -------- 
#define AT91C_DPIP_HOLE           (0xFFFFUL <<  0)      // (HDMA_CH) This field indicates the value to add to the address when the programmable boundary has been reached.
#define AT91C_DPIP_BOUNDARY       (0x3FFUL << 16)       // (HDMA_CH) This field indicates the number of source transfers to perform before the automatic address increment operation.
// -------- HDMA_BDSCR : (HDMA_CH Offset: 0x20)  -------- 
// -------- HDMA_CADDR : (HDMA_CH Offset: 0x24)  -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR HDMA controller
// *****************************************************************************
// *** Register offset in AT91S_HDMA structure ***
#define HDMA_GCFG       ( 0)    // HDMA Global Configuration Register
#define HDMA_EN         ( 4)    // HDMA Controller Enable Register
#define HDMA_SREQ       ( 8)    // HDMA Software Single Request Register
#define HDMA_CREQ       (12)    // HDMA Software Chunk Transfer Request Register
#define HDMA_LAST       (16)    // HDMA Software Last Transfer Flag Register
#define HDMA_SYNC       (20)    // HDMA Request Synchronization Register
#define HDMA_EBCIER     (24)    // HDMA Error, Chained Buffer transfer completed and Buffer transfer completed Interrupt Enable register
#define HDMA_EBCIDR     (28)    // HDMA Error, Chained Buffer transfer completed and Buffer transfer completed Interrupt Disable register
#define HDMA_EBCIMR     (32)    // HDMA Error, Chained Buffer transfer completed and Buffer transfer completed Mask Register
#define HDMA_EBCISR     (36)    // HDMA Error, Chained Buffer transfer completed and Buffer transfer completed Status Register
#define HDMA_CHER       (40)    // HDMA Channel Handler Enable Register
#define HDMA_CHDR       (44)    // HDMA Channel Handler Disable Register
#define HDMA_CHSR       (48)    // HDMA Channel Handler Status Register
#define HDMA_RSVD0      (52)    // HDMA Reserved
#define HDMA_RSVD1      (56)    // HDMA Reserved
#define HDMA_CH         (60)    // HDMA Channel structure
#define HDMA_ADDRSIZE   (492)   // HDMA ADDRSIZE REGISTER
#define HDMA_IPNAME1    (496)   // HDMA IPNAME1 REGISTER
#define HDMA_IPNAME2    (500)   // HDMA IPNAME2 REGISTER
#define HDMA_FEATURES   (504)   // HDMA FEATURES REGISTER
#define HDMA_VER        (508)   // HDMA VERSION REGISTER
// -------- HDMA_GCFG : (HDMA Offset: 0x0)  -------- 
#define AT91C_HDMA_IF0_BIGEND     (0x1UL <<  0) // (HDMA) AHB-Lite Interface 0 endian mode.
#define 	AT91C_HDMA_IF0_BIGEND_IS_LITTLE_ENDIAN     (0x0UL)      // (HDMA) AHB-Lite Interface 0 is little endian.
#define 	AT91C_HDMA_IF0_BIGEND_IS_BIG_ENDIAN        (0x1UL)      // (HDMA) AHB-Lite Interface 0 is big endian.
#define AT91C_HDMA_IF1_BIGEND     (0x1UL <<  1) // (HDMA) AHB-Lite Interface 1 endian mode.
#define 	AT91C_HDMA_IF1_BIGEND_IS_LITTLE_ENDIAN     (0x0UL <<  1)        // (HDMA) AHB-Lite Interface 1 is little endian.
#define 	AT91C_HDMA_IF1_BIGEND_IS_BIG_ENDIAN        (0x1UL <<  1)        // (HDMA) AHB-Lite Interface 1 is big endian.
#define AT91C_HDMA_IF2_BIGEND     (0x1UL <<  2) // (HDMA) AHB-Lite Interface 2 endian mode.
#define 	AT91C_HDMA_IF2_BIGEND_IS_LITTLE_ENDIAN     (0x0UL <<  2)        // (HDMA) AHB-Lite Interface 2 is little endian.
#define 	AT91C_HDMA_IF2_BIGEND_IS_BIG_ENDIAN        (0x1UL <<  2)        // (HDMA) AHB-Lite Interface 2 is big endian.
#define AT91C_HDMA_IF3_BIGEND     (0x1UL <<  3) // (HDMA) AHB-Lite Interface 3 endian mode.
#define 	AT91C_HDMA_IF3_BIGEND_IS_LITTLE_ENDIAN     (0x0UL <<  3)        // (HDMA) AHB-Lite Interface 3 is little endian.
#define 	AT91C_HDMA_IF3_BIGEND_IS_BIG_ENDIAN        (0x1UL <<  3)        // (HDMA) AHB-Lite Interface 3 is big endian.
#define AT91C_HDMA_ARB_CFG        (0x1UL <<  4) // (HDMA) Arbiter mode.
#define 	AT91C_HDMA_ARB_CFG_FIXED                (0x0UL <<  4)   // (HDMA) Fixed priority arbiter.
#define 	AT91C_HDMA_ARB_CFG_ROUND_ROBIN          (0x1UL <<  4)   // (HDMA) Modified round robin arbiter.
// -------- HDMA_EN : (HDMA Offset: 0x4)  -------- 
#define AT91C_HDMA_ENABLE         (0x1UL <<  0) // (HDMA)
#define 	AT91C_HDMA_ENABLE_DISABLE              (0x0UL)  // (HDMA) Disables HDMA.
#define 	AT91C_HDMA_ENABLE_ENABLE               (0x1UL)  // (HDMA) Enables HDMA.
// -------- HDMA_SREQ : (HDMA Offset: 0x8)  -------- 
#define AT91C_HDMA_SSREQ0         (0x1UL <<  0) // (HDMA) Request a source single transfer on channel 0
#define 	AT91C_HDMA_SSREQ0_0                    (0x0UL)  // (HDMA) No effect.
#define 	AT91C_HDMA_SSREQ0_1                    (0x1UL)  // (HDMA) Request a source single transfer on channel 0.
#define AT91C_HDMA_DSREQ0         (0x1UL <<  1) // (HDMA) Request a destination single transfer on channel 0
#define 	AT91C_HDMA_DSREQ0_0                    (0x0UL <<  1)    // (HDMA) No effect.
#define 	AT91C_HDMA_DSREQ0_1                    (0x1UL <<  1)    // (HDMA) Request a destination single transfer on channel 0.
#define AT91C_HDMA_SSREQ1         (0x1UL <<  2) // (HDMA) Request a source single transfer on channel 1
#define 	AT91C_HDMA_SSREQ1_0                    (0x0UL <<  2)    // (HDMA) No effect.
#define 	AT91C_HDMA_SSREQ1_1                    (0x1UL <<  2)    // (HDMA) Request a source single transfer on channel 1.
#define AT91C_HDMA_DSREQ1         (0x1UL <<  3) // (HDMA) Request a destination single transfer on channel 1
#define 	AT91C_HDMA_DSREQ1_0                    (0x0UL <<  3)    // (HDMA) No effect.
#define 	AT91C_HDMA_DSREQ1_1                    (0x1UL <<  3)    // (HDMA) Request a destination single transfer on channel 1.
#define AT91C_HDMA_SSREQ2         (0x1UL <<  4) // (HDMA) Request a source single transfer on channel 2
#define 	AT91C_HDMA_SSREQ2_0                    (0x0UL <<  4)    // (HDMA) No effect.
#define 	AT91C_HDMA_SSREQ2_1                    (0x1UL <<  4)    // (HDMA) Request a source single transfer on channel 2.
#define AT91C_HDMA_DSREQ2         (0x1UL <<  5) // (HDMA) Request a destination single transfer on channel 2
#define 	AT91C_HDMA_DSREQ2_0                    (0x0UL <<  5)    // (HDMA) No effect.
#define 	AT91C_HDMA_DSREQ2_1                    (0x1UL <<  5)    // (HDMA) Request a destination single transfer on channel 2.
#define AT91C_HDMA_SSREQ3         (0x1UL <<  6) // (HDMA) Request a source single transfer on channel 3
#define 	AT91C_HDMA_SSREQ3_0                    (0x0UL <<  6)    // (HDMA) No effect.
#define 	AT91C_HDMA_SSREQ3_1                    (0x1UL <<  6)    // (HDMA) Request a source single transfer on channel 3.
#define AT91C_HDMA_DSREQ3         (0x1UL <<  7) // (HDMA) Request a destination single transfer on channel 3
#define 	AT91C_HDMA_DSREQ3_0                    (0x0UL <<  7)    // (HDMA) No effect.
#define 	AT91C_HDMA_DSREQ3_1                    (0x1UL <<  7)    // (HDMA) Request a destination single transfer on channel 3.
#define AT91C_HDMA_SSREQ4         (0x1UL <<  8) // (HDMA) Request a source single transfer on channel 4
#define 	AT91C_HDMA_SSREQ4_0                    (0x0UL <<  8)    // (HDMA) No effect.
#define 	AT91C_HDMA_SSREQ4_1                    (0x1UL <<  8)    // (HDMA) Request a source single transfer on channel 4.
#define AT91C_HDMA_DSREQ4         (0x1UL <<  9) // (HDMA) Request a destination single transfer on channel 4
#define 	AT91C_HDMA_DSREQ4_0                    (0x0UL <<  9)    // (HDMA) No effect.
#define 	AT91C_HDMA_DSREQ4_1                    (0x1UL <<  9)    // (HDMA) Request a destination single transfer on channel 4.
#define AT91C_HDMA_SSREQ5         (0x1UL << 10) // (HDMA) Request a source single transfer on channel 5
#define 	AT91C_HDMA_SSREQ5_0                    (0x0UL << 10)    // (HDMA) No effect.
#define 	AT91C_HDMA_SSREQ5_1                    (0x1UL << 10)    // (HDMA) Request a source single transfer on channel 5.
#define AT91C_HDMA_DSREQ6         (0x1UL << 11) // (HDMA) Request a destination single transfer on channel 5
#define 	AT91C_HDMA_DSREQ6_0                    (0x0UL << 11)    // (HDMA) No effect.
#define 	AT91C_HDMA_DSREQ6_1                    (0x1UL << 11)    // (HDMA) Request a destination single transfer on channel 5.
#define AT91C_HDMA_SSREQ6         (0x1UL << 12) // (HDMA) Request a source single transfer on channel 6
#define 	AT91C_HDMA_SSREQ6_0                    (0x0UL << 12)    // (HDMA) No effect.
#define 	AT91C_HDMA_SSREQ6_1                    (0x1UL << 12)    // (HDMA) Request a source single transfer on channel 6.
#define AT91C_HDMA_SSREQ7         (0x1UL << 14) // (HDMA) Request a source single transfer on channel 7
#define 	AT91C_HDMA_SSREQ7_0                    (0x0UL << 14)    // (HDMA) No effect.
#define 	AT91C_HDMA_SSREQ7_1                    (0x1UL << 14)    // (HDMA) Request a source single transfer on channel 7.
#define AT91C_HDMA_DSREQ7         (0x1UL << 15) // (HDMA) Request a destination single transfer on channel 7
#define 	AT91C_HDMA_DSREQ7_0                    (0x0UL << 15)    // (HDMA) No effect.
#define 	AT91C_HDMA_DSREQ7_1                    (0x1UL << 15)    // (HDMA) Request a destination single transfer on channel 7.
// -------- HDMA_CREQ : (HDMA Offset: 0xc)  -------- 
#define AT91C_HDMA_SCREQ0         (0x1UL <<  0) // (HDMA) Request a source chunk transfer on channel 0
#define 	AT91C_HDMA_SCREQ0_0                    (0x0UL)  // (HDMA) No effect.
#define 	AT91C_HDMA_SCREQ0_1                    (0x1UL)  // (HDMA) Request a source chunk transfer on channel 0.
#define AT91C_HDMA_DCREQ0         (0x1UL <<  1) // (HDMA) Request a destination chunk transfer on channel 0
#define 	AT91C_HDMA_DCREQ0_0                    (0x0UL <<  1)    // (HDMA) No effect.
#define 	AT91C_HDMA_DCREQ0_1                    (0x1UL <<  1)    // (HDMA) Request a destination chunk transfer on channel 0.
#define AT91C_HDMA_SCREQ1         (0x1UL <<  2) // (HDMA) Request a source chunk transfer on channel 1
#define 	AT91C_HDMA_SCREQ1_0                    (0x0UL <<  2)    // (HDMA) No effect.
#define 	AT91C_HDMA_SCREQ1_1                    (0x1UL <<  2)    // (HDMA) Request a source chunk transfer on channel 1.
#define AT91C_HDMA_DCREQ1         (0x1UL <<  3) // (HDMA) Request a destination chunk transfer on channel 1
#define 	AT91C_HDMA_DCREQ1_0                    (0x0UL <<  3)    // (HDMA) No effect.
#define 	AT91C_HDMA_DCREQ1_1                    (0x1UL <<  3)    // (HDMA) Request a destination chunk transfer on channel 1.
#define AT91C_HDMA_SCREQ2         (0x1UL <<  4) // (HDMA) Request a source chunk transfer on channel 2
#define 	AT91C_HDMA_SCREQ2_0                    (0x0UL <<  4)    // (HDMA) No effect.
#define 	AT91C_HDMA_SCREQ2_1                    (0x1UL <<  4)    // (HDMA) Request a source chunk transfer on channel 2.
#define AT91C_HDMA_DCREQ2         (0x1UL <<  5) // (HDMA) Request a destination chunk transfer on channel 2
#define 	AT91C_HDMA_DCREQ2_0                    (0x0UL <<  5)    // (HDMA) No effect.
#define 	AT91C_HDMA_DCREQ2_1                    (0x1UL <<  5)    // (HDMA) Request a destination chunk transfer on channel 2.
#define AT91C_HDMA_SCREQ3         (0x1UL <<  6) // (HDMA) Request a source chunk transfer on channel 3
#define 	AT91C_HDMA_SCREQ3_0                    (0x0UL <<  6)    // (HDMA) No effect.
#define 	AT91C_HDMA_SCREQ3_1                    (0x1UL <<  6)    // (HDMA) Request a source chunk transfer on channel 3.
#define AT91C_HDMA_DCREQ3         (0x1UL <<  7) // (HDMA) Request a destination chunk transfer on channel 3
#define 	AT91C_HDMA_DCREQ3_0                    (0x0UL <<  7)    // (HDMA) No effect.
#define 	AT91C_HDMA_DCREQ3_1                    (0x1UL <<  7)    // (HDMA) Request a destination chunk transfer on channel 3.
#define AT91C_HDMA_SCREQ4         (0x1UL <<  8) // (HDMA) Request a source chunk transfer on channel 4
#define 	AT91C_HDMA_SCREQ4_0                    (0x0UL <<  8)    // (HDMA) No effect.
#define 	AT91C_HDMA_SCREQ4_1                    (0x1UL <<  8)    // (HDMA) Request a source chunk transfer on channel 4.
#define AT91C_HDMA_DCREQ4         (0x1UL <<  9) // (HDMA) Request a destination chunk transfer on channel 4
#define 	AT91C_HDMA_DCREQ4_0                    (0x0UL <<  9)    // (HDMA) No effect.
#define 	AT91C_HDMA_DCREQ4_1                    (0x1UL <<  9)    // (HDMA) Request a destination chunk transfer on channel 4.
#define AT91C_HDMA_SCREQ5         (0x1UL << 10) // (HDMA) Request a source chunk transfer on channel 5
#define 	AT91C_HDMA_SCREQ5_0                    (0x0UL << 10)    // (HDMA) No effect.
#define 	AT91C_HDMA_SCREQ5_1                    (0x1UL << 10)    // (HDMA) Request a source chunk transfer on channel 5.
#define AT91C_HDMA_DCREQ6         (0x1UL << 11) // (HDMA) Request a destination chunk transfer on channel 5
#define 	AT91C_HDMA_DCREQ6_0                    (0x0UL << 11)    // (HDMA) No effect.
#define 	AT91C_HDMA_DCREQ6_1                    (0x1UL << 11)    // (HDMA) Request a destination chunk transfer on channel 5.
#define AT91C_HDMA_SCREQ6         (0x1UL << 12) // (HDMA) Request a source chunk transfer on channel 6
#define 	AT91C_HDMA_SCREQ6_0                    (0x0UL << 12)    // (HDMA) No effect.
#define 	AT91C_HDMA_SCREQ6_1                    (0x1UL << 12)    // (HDMA) Request a source chunk transfer on channel 6.
#define AT91C_HDMA_SCREQ7         (0x1UL << 14) // (HDMA) Request a source chunk transfer on channel 7
#define 	AT91C_HDMA_SCREQ7_0                    (0x0UL << 14)    // (HDMA) No effect.
#define 	AT91C_HDMA_SCREQ7_1                    (0x1UL << 14)    // (HDMA) Request a source chunk transfer on channel 7.
#define AT91C_HDMA_DCREQ7         (0x1UL << 15) // (HDMA) Request a destination chunk transfer on channel 7
#define 	AT91C_HDMA_DCREQ7_0                    (0x0UL << 15)    // (HDMA) No effect.
#define 	AT91C_HDMA_DCREQ7_1                    (0x1UL << 15)    // (HDMA) Request a destination chunk transfer on channel 7.
// -------- HDMA_LAST : (HDMA Offset: 0x10)  -------- 
#define AT91C_HDMA_SLAST0         (0x1UL <<  0) // (HDMA) Indicates that this source request is the last transfer of the buffer on channel 0
#define 	AT91C_HDMA_SLAST0_0                    (0x0UL)  // (HDMA) No effect.
#define 	AT91C_HDMA_SLAST0_1                    (0x1UL)  // (HDMA) Writing one to SLASTx prior to writing one to SSREQx or SCREQx indicates that this source request is the last transfer of the buffer on channel 0.
#define AT91C_HDMA_DLAST0         (0x1UL <<  1) // (HDMA) Indicates that this destination request is the last transfer of the buffer on channel 0
#define 	AT91C_HDMA_DLAST0_0                    (0x0UL <<  1)    // (HDMA) No effect.
#define 	AT91C_HDMA_DLAST0_1                    (0x1UL <<  1)    // (HDMA) Writing one to DLASTx prior to writing one to DSREQx or DCREQx indicates that this destination request is the last transfer of the buffer on channel 0.
#define AT91C_HDMA_SLAST1         (0x1UL <<  2) // (HDMA) Indicates that this source request is the last transfer of the buffer on channel 1
#define 	AT91C_HDMA_SLAST1_0                    (0x0UL <<  2)    // (HDMA) No effect.
#define 	AT91C_HDMA_SLAST1_1                    (0x1UL <<  2)    // (HDMA) Writing one to SLASTx prior to writing one to SSREQx or SCREQx indicates that this source request is the last transfer of the buffer on channel 1.
#define AT91C_HDMA_DLAST1         (0x1UL <<  3) // (HDMA) Indicates that this destination request is the last transfer of the buffer on channel 1
#define 	AT91C_HDMA_DLAST1_0                    (0x0UL <<  3)    // (HDMA) No effect.
#define 	AT91C_HDMA_DLAST1_1                    (0x1UL <<  3)    // (HDMA) Writing one to DLASTx prior to writing one to DSREQx or DCREQx indicates that this destination request is the last transfer of the buffer on channel 1.
#define AT91C_HDMA_SLAST2         (0x1UL <<  4) // (HDMA) Indicates that this source request is the last transfer of the buffer on channel 2
#define 	AT91C_HDMA_SLAST2_0                    (0x0UL <<  4)    // (HDMA) No effect.
#define 	AT91C_HDMA_SLAST2_1                    (0x1UL <<  4)    // (HDMA) Writing one to SLASTx prior to writing one to SSREQx or SCREQx indicates that this source request is the last transfer of the buffer on channel 2.
#define AT91C_HDMA_DLAST2         (0x1UL <<  5) // (HDMA) Indicates that this destination request is the last transfer of the buffer on channel 2
#define 	AT91C_HDMA_DLAST2_0                    (0x0UL <<  5)    // (HDMA) No effect.
#define 	AT91C_HDMA_DLAST2_1                    (0x1UL <<  5)    // (HDMA) Writing one to DLASTx prior to writing one to DSREQx or DCREQx indicates that this destination request is the last transfer of the buffer on channel 2.
#define AT91C_HDMA_SLAST3         (0x1UL <<  6) // (HDMA) Indicates that this source request is the last transfer of the buffer on channel 3
#define 	AT91C_HDMA_SLAST3_0                    (0x0UL <<  6)    // (HDMA) No effect.
#define 	AT91C_HDMA_SLAST3_1                    (0x1UL <<  6)    // (HDMA) Writing one to SLASTx prior to writing one to SSREQx or SCREQx indicates that this source request is the last transfer of the buffer on channel 3.
#define AT91C_HDMA_DLAST3         (0x1UL <<  7) // (HDMA) Indicates that this destination request is the last transfer of the buffer on channel 3
#define 	AT91C_HDMA_DLAST3_0                    (0x0UL <<  7)    // (HDMA) No effect.
#define 	AT91C_HDMA_DLAST3_1                    (0x1UL <<  7)    // (HDMA) Writing one to DLASTx prior to writing one to DSREQx or DCREQx indicates that this destination request is the last transfer of the buffer on channel 3.
#define AT91C_HDMA_SLAST4         (0x1UL <<  8) // (HDMA) Indicates that this source request is the last transfer of the buffer on channel 4
#define 	AT91C_HDMA_SLAST4_0                    (0x0UL <<  8)    // (HDMA) No effect.
#define 	AT91C_HDMA_SLAST4_1                    (0x1UL <<  8)    // (HDMA) Writing one to SLASTx prior to writing one to SSREQx or SCREQx indicates that this source request is the last transfer of the buffer on channel 4.
#define AT91C_HDMA_DLAST4         (0x1UL <<  9) // (HDMA) Indicates that this destination request is the last transfer of the buffer on channel 4
#define 	AT91C_HDMA_DLAST4_0                    (0x0UL <<  9)    // (HDMA) No effect.
#define 	AT91C_HDMA_DLAST4_1                    (0x1UL <<  9)    // (HDMA) Writing one to DLASTx prior to writing one to DSREQx or DCREQx indicates that this destination request is the last transfer of the buffer on channel 4.
#define AT91C_HDMA_SLAST5         (0x1UL << 10) // (HDMA) Indicates that this source request is the last transfer of the buffer on channel 5
#define 	AT91C_HDMA_SLAST5_0                    (0x0UL << 10)    // (HDMA) No effect.
#define 	AT91C_HDMA_SLAST5_1                    (0x1UL << 10)    // (HDMA) Writing one to SLASTx prior to writing one to SSREQx or SCREQx indicates that this source request is the last transfer of the buffer on channel 5.
#define AT91C_HDMA_DLAST6         (0x1UL << 11) // (HDMA) Indicates that this destination request is the last transfer of the buffer on channel 5
#define 	AT91C_HDMA_DLAST6_0                    (0x0UL << 11)    // (HDMA) No effect.
#define 	AT91C_HDMA_DLAST6_1                    (0x1UL << 11)    // (HDMA) Writing one to DLASTx prior to writing one to DSREQx or DCREQx indicates that this destination request is the last transfer of the buffer on channel 5.
#define AT91C_HDMA_SLAST6         (0x1UL << 12) // (HDMA) Indicates that this source request is the last transfer of the buffer on channel 6
#define 	AT91C_HDMA_SLAST6_0                    (0x0UL << 12)    // (HDMA) No effect.
#define 	AT91C_HDMA_SLAST6_1                    (0x1UL << 12)    // (HDMA) Writing one to SLASTx prior to writing one to SSREQx or SCREQx indicates that this source request is the last transfer of the buffer on channel 6.
#define AT91C_HDMA_SLAST7         (0x1UL << 14) // (HDMA) Indicates that this source request is the last transfer of the buffer on channel 7
#define 	AT91C_HDMA_SLAST7_0                    (0x0UL << 14)    // (HDMA) No effect.
#define 	AT91C_HDMA_SLAST7_1                    (0x1UL << 14)    // (HDMA) Writing one to SLASTx prior to writing one to SSREQx or SCREQx indicates that this source request is the last transfer of the buffer on channel 7.
#define AT91C_HDMA_DLAST7         (0x1UL << 15) // (HDMA) Indicates that this destination request is the last transfer of the buffer on channel 7
#define 	AT91C_HDMA_DLAST7_0                    (0x0UL << 15)    // (HDMA) No effect.
#define 	AT91C_HDMA_DLAST7_1                    (0x1UL << 15)    // (HDMA) Writing one to DLASTx prior to writing one to DSREQx or DCREQx indicates that this destination request is the last transfer of the buffer on channel 7.
// -------- HDMA_SYNC : (HDMA Offset: 0x14)  -------- 
#define AT91C_SYNC_REQ            (0xFFFFUL <<  0)      // (HDMA)
// -------- HDMA_EBCIER : (HDMA Offset: 0x18) Buffer Transfer Completed/Chained Buffer Transfer Completed/Access Error Interrupt Enable Register -------- 
#define AT91C_HDMA_BTC0           (0x1UL <<  0) // (HDMA) Buffer Transfer Completed Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_BTC1           (0x1UL <<  1) // (HDMA) Buffer Transfer Completed Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_BTC2           (0x1UL <<  2) // (HDMA) Buffer Transfer Completed Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_BTC3           (0x1UL <<  3) // (HDMA) Buffer Transfer Completed Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_BTC4           (0x1UL <<  4) // (HDMA) Buffer Transfer Completed Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_BTC5           (0x1UL <<  5) // (HDMA) Buffer Transfer Completed Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_BTC6           (0x1UL <<  6) // (HDMA) Buffer Transfer Completed Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_BTC7           (0x1UL <<  7) // (HDMA) Buffer Transfer Completed Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_CBTC0          (0x1UL <<  8) // (HDMA) Chained Buffer Transfer Completed Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_CBTC1          (0x1UL <<  9) // (HDMA) Chained Buffer Transfer Completed Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_CBTC2          (0x1UL << 10) // (HDMA) Chained Buffer Transfer Completed Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_CBTC3          (0x1UL << 11) // (HDMA) Chained Buffer Transfer Completed Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_CBTC4          (0x1UL << 12) // (HDMA) Chained Buffer Transfer Completed Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_CBTC5          (0x1UL << 13) // (HDMA) Chained Buffer Transfer Completed Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_CBTC6          (0x1UL << 14) // (HDMA) Chained Buffer Transfer Completed Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_CBTC7          (0x1UL << 15) // (HDMA) Chained Buffer Transfer Completed Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_ERR0           (0x1UL << 16) // (HDMA) Access HDMA_Error Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_ERR1           (0x1UL << 17) // (HDMA) Access HDMA_Error Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_ERR2           (0x1UL << 18) // (HDMA) Access HDMA_Error Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_ERR3           (0x1UL << 19) // (HDMA) Access HDMA_Error Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_ERR4           (0x1UL << 20) // (HDMA) Access HDMA_Error Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_ERR5           (0x1UL << 21) // (HDMA) Access HDMA_Error Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_ERR6           (0x1UL << 22) // (HDMA) Access HDMA_Error Interrupt Enable/Disable/Status Register
#define AT91C_HDMA_ERR7           (0x1UL << 23) // (HDMA) Access HDMA_Error Interrupt Enable/Disable/Status Register
// -------- HDMA_EBCIDR : (HDMA Offset: 0x1c)  -------- 
// -------- HDMA_EBCIMR : (HDMA Offset: 0x20)  -------- 
// -------- HDMA_EBCISR : (HDMA Offset: 0x24)  -------- 
// -------- HDMA_CHER : (HDMA Offset: 0x28)  -------- 
#define AT91C_HDMA_ENA0           (0x1UL <<  0) // (HDMA) When set, channel 0 enabled.
#define 	AT91C_HDMA_ENA0_0                    (0x0UL)    // (HDMA) No effect.
#define 	AT91C_HDMA_ENA0_1                    (0x1UL)    // (HDMA) Channel 0 enabled.
#define AT91C_HDMA_ENA1           (0x1UL <<  1) // (HDMA) When set, channel 1 enabled.
#define 	AT91C_HDMA_ENA1_0                    (0x0UL <<  1)      // (HDMA) No effect.
#define 	AT91C_HDMA_ENA1_1                    (0x1UL <<  1)      // (HDMA) Channel 1 enabled.
#define AT91C_HDMA_ENA2           (0x1UL <<  2) // (HDMA) When set, channel 2 enabled.
#define 	AT91C_HDMA_ENA2_0                    (0x0UL <<  2)      // (HDMA) No effect.
#define 	AT91C_HDMA_ENA2_1                    (0x1UL <<  2)      // (HDMA) Channel 2 enabled.
#define AT91C_HDMA_ENA3           (0x1UL <<  3) // (HDMA) When set, channel 3 enabled.
#define 	AT91C_HDMA_ENA3_0                    (0x0UL <<  3)      // (HDMA) No effect.
#define 	AT91C_HDMA_ENA3_1                    (0x1UL <<  3)      // (HDMA) Channel 3 enabled.
#define AT91C_HDMA_ENA4           (0x1UL <<  4) // (HDMA) When set, channel 4 enabled.
#define 	AT91C_HDMA_ENA4_0                    (0x0UL <<  4)      // (HDMA) No effect.
#define 	AT91C_HDMA_ENA4_1                    (0x1UL <<  4)      // (HDMA) Channel 4 enabled.
#define AT91C_HDMA_ENA5           (0x1UL <<  5) // (HDMA) When set, channel 5 enabled.
#define 	AT91C_HDMA_ENA5_0                    (0x0UL <<  5)      // (HDMA) No effect.
#define 	AT91C_HDMA_ENA5_1                    (0x1UL <<  5)      // (HDMA) Channel 5 enabled.
#define AT91C_HDMA_ENA6           (0x1UL <<  6) // (HDMA) When set, channel 6 enabled.
#define 	AT91C_HDMA_ENA6_0                    (0x0UL <<  6)      // (HDMA) No effect.
#define 	AT91C_HDMA_ENA6_1                    (0x1UL <<  6)      // (HDMA) Channel 6 enabled.
#define AT91C_HDMA_ENA7           (0x1UL <<  7) // (HDMA) When set, channel 7 enabled.
#define 	AT91C_HDMA_ENA7_0                    (0x0UL <<  7)      // (HDMA) No effect.
#define 	AT91C_HDMA_ENA7_1                    (0x1UL <<  7)      // (HDMA) Channel 7 enabled.
#define AT91C_HDMA_SUSP0          (0x1UL <<  8) // (HDMA) When set, channel 0 freezed and its current context.
#define 	AT91C_HDMA_SUSP0_0                    (0x0UL <<  8)     // (HDMA) No effect.
#define 	AT91C_HDMA_SUSP0_1                    (0x1UL <<  8)     // (HDMA) Channel 0 freezed.
#define AT91C_HDMA_SUSP1          (0x1UL <<  9) // (HDMA) When set, channel 1 freezed and its current context.
#define 	AT91C_HDMA_SUSP1_0                    (0x0UL <<  9)     // (HDMA) No effect.
#define 	AT91C_HDMA_SUSP1_1                    (0x1UL <<  9)     // (HDMA) Channel 1 freezed.
#define AT91C_HDMA_SUSP2          (0x1UL << 10) // (HDMA) When set, channel 2 freezed and its current context.
#define 	AT91C_HDMA_SUSP2_0                    (0x0UL << 10)     // (HDMA) No effect.
#define 	AT91C_HDMA_SUSP2_1                    (0x1UL << 10)     // (HDMA) Channel 2 freezed.
#define AT91C_HDMA_SUSP3          (0x1UL << 11) // (HDMA) When set, channel 3 freezed and its current context.
#define 	AT91C_HDMA_SUSP3_0                    (0x0UL << 11)     // (HDMA) No effect.
#define 	AT91C_HDMA_SUSP3_1                    (0x1UL << 11)     // (HDMA) Channel 3 freezed.
#define AT91C_HDMA_SUSP4          (0x1UL << 12) // (HDMA) When set, channel 4 freezed and its current context.
#define 	AT91C_HDMA_SUSP4_0                    (0x0UL << 12)     // (HDMA) No effect.
#define 	AT91C_HDMA_SUSP4_1                    (0x1UL << 12)     // (HDMA) Channel 4 freezed.
#define AT91C_HDMA_SUSP5          (0x1UL << 13) // (HDMA) When set, channel 5 freezed and its current context.
#define 	AT91C_HDMA_SUSP5_0                    (0x0UL << 13)     // (HDMA) No effect.
#define 	AT91C_HDMA_SUSP5_1                    (0x1UL << 13)     // (HDMA) Channel 5 freezed.
#define AT91C_HDMA_SUSP6          (0x1UL << 14) // (HDMA) When set, channel 6 freezed and its current context.
#define 	AT91C_HDMA_SUSP6_0                    (0x0UL << 14)     // (HDMA) No effect.
#define 	AT91C_HDMA_SUSP6_1                    (0x1UL << 14)     // (HDMA) Channel 6 freezed.
#define AT91C_HDMA_SUSP7          (0x1UL << 15) // (HDMA) When set, channel 7 freezed and its current context.
#define 	AT91C_HDMA_SUSP7_0                    (0x0UL << 15)     // (HDMA) No effect.
#define 	AT91C_HDMA_SUSP7_1                    (0x1UL << 15)     // (HDMA) Channel 7 freezed.
#define AT91C_HDMA_KEEP0          (0x1UL << 24) // (HDMA) When set, it resumes the channel 0 from an automatic stall state.
#define 	AT91C_HDMA_KEEP0_0                    (0x0UL << 24)     // (HDMA) No effect.
#define 	AT91C_HDMA_KEEP0_1                    (0x1UL << 24)     // (HDMA) Resumes the channel 0.
#define AT91C_HDMA_KEEP1          (0x1UL << 25) // (HDMA) When set, it resumes the channel 1 from an automatic stall state.
#define 	AT91C_HDMA_KEEP1_0                    (0x0UL << 25)     // (HDMA) No effect.
#define 	AT91C_HDMA_KEEP1_1                    (0x1UL << 25)     // (HDMA) Resumes the channel 1.
#define AT91C_HDMA_KEEP2          (0x1UL << 26) // (HDMA) When set, it resumes the channel 2 from an automatic stall state.
#define 	AT91C_HDMA_KEEP2_0                    (0x0UL << 26)     // (HDMA) No effect.
#define 	AT91C_HDMA_KEEP2_1                    (0x1UL << 26)     // (HDMA) Resumes the channel 2.
#define AT91C_HDMA_KEEP3          (0x1UL << 27) // (HDMA) When set, it resumes the channel 3 from an automatic stall state.
#define 	AT91C_HDMA_KEEP3_0                    (0x0UL << 27)     // (HDMA) No effect.
#define 	AT91C_HDMA_KEEP3_1                    (0x1UL << 27)     // (HDMA) Resumes the channel 3.
#define AT91C_HDMA_KEEP4          (0x1UL << 28) // (HDMA) When set, it resumes the channel 4 from an automatic stall state.
#define 	AT91C_HDMA_KEEP4_0                    (0x0UL << 28)     // (HDMA) No effect.
#define 	AT91C_HDMA_KEEP4_1                    (0x1UL << 28)     // (HDMA) Resumes the channel 4.
#define AT91C_HDMA_KEEP5          (0x1UL << 29) // (HDMA) When set, it resumes the channel 5 from an automatic stall state.
#define 	AT91C_HDMA_KEEP5_0                    (0x0UL << 29)     // (HDMA) No effect.
#define 	AT91C_HDMA_KEEP5_1                    (0x1UL << 29)     // (HDMA) Resumes the channel 5.
#define AT91C_HDMA_KEEP6          (0x1UL << 30) // (HDMA) When set, it resumes the channel 6 from an automatic stall state.
#define 	AT91C_HDMA_KEEP6_0                    (0x0UL << 30)     // (HDMA) No effect.
#define 	AT91C_HDMA_KEEP6_1                    (0x1UL << 30)     // (HDMA) Resumes the channel 6.
#define AT91C_HDMA_KEEP7          (0x1UL << 31) // (HDMA) When set, it resumes the channel 7 from an automatic stall state.
#define 	AT91C_HDMA_KEEP7_0                    (0x0UL << 31)     // (HDMA) No effect.
#define 	AT91C_HDMA_KEEP7_1                    (0x1UL << 31)     // (HDMA) Resumes the channel 7.
// -------- HDMA_CHDR : (HDMA Offset: 0x2c)  -------- 
#define AT91C_HDMA_DIS0           (0x1UL <<  0) // (HDMA) Write one to this field to disable the channel 0.
#define 	AT91C_HDMA_DIS0_0                    (0x0UL)    // (HDMA) No effect.
#define 	AT91C_HDMA_DIS0_1                    (0x1UL)    // (HDMA) Disables the channel 0.
#define AT91C_HDMA_DIS1           (0x1UL <<  1) // (HDMA) Write one to this field to disable the channel 1.
#define 	AT91C_HDMA_DIS1_0                    (0x0UL <<  1)      // (HDMA) No effect.
#define 	AT91C_HDMA_DIS1_1                    (0x1UL <<  1)      // (HDMA) Disables the channel 1.
#define AT91C_HDMA_DIS2           (0x1UL <<  2) // (HDMA) Write one to this field to disable the channel 2.
#define 	AT91C_HDMA_DIS2_0                    (0x0UL <<  2)      // (HDMA) No effect.
#define 	AT91C_HDMA_DIS2_1                    (0x1UL <<  2)      // (HDMA) Disables the channel 2.
#define AT91C_HDMA_DIS3           (0x1UL <<  3) // (HDMA) Write one to this field to disable the channel 3.
#define 	AT91C_HDMA_DIS3_0                    (0x0UL <<  3)      // (HDMA) No effect.
#define 	AT91C_HDMA_DIS3_1                    (0x1UL <<  3)      // (HDMA) Disables the channel 3.
#define AT91C_HDMA_DIS4           (0x1UL <<  4) // (HDMA) Write one to this field to disable the channel 4.
#define 	AT91C_HDMA_DIS4_0                    (0x0UL <<  4)      // (HDMA) No effect.
#define 	AT91C_HDMA_DIS4_1                    (0x1UL <<  4)      // (HDMA) Disables the channel 4.
#define AT91C_HDMA_DIS5           (0x1UL <<  5) // (HDMA) Write one to this field to disable the channel 5.
#define 	AT91C_HDMA_DIS5_0                    (0x0UL <<  5)      // (HDMA) No effect.
#define 	AT91C_HDMA_DIS5_1                    (0x1UL <<  5)      // (HDMA) Disables the channel 5.
#define AT91C_HDMA_DIS6           (0x1UL <<  6) // (HDMA) Write one to this field to disable the channel 6.
#define 	AT91C_HDMA_DIS6_0                    (0x0UL <<  6)      // (HDMA) No effect.
#define 	AT91C_HDMA_DIS6_1                    (0x1UL <<  6)      // (HDMA) Disables the channel 6.
#define AT91C_HDMA_DIS7           (0x1UL <<  7) // (HDMA) Write one to this field to disable the channel 7.
#define 	AT91C_HDMA_DIS7_0                    (0x0UL <<  7)      // (HDMA) No effect.
#define 	AT91C_HDMA_DIS7_1                    (0x1UL <<  7)      // (HDMA) Disables the channel 7.
#define AT91C_HDMA_RES0           (0x1UL <<  8) // (HDMA) Write one to this field to resume the channel 0 transfer restoring its context.
#define 	AT91C_HDMA_RES0_0                    (0x0UL <<  8)      // (HDMA) No effect.
#define 	AT91C_HDMA_RES0_1                    (0x1UL <<  8)      // (HDMA) Resumes the channel 0.
#define AT91C_HDMA_RES1           (0x1UL <<  9) // (HDMA) Write one to this field to resume the channel 1 transfer restoring its context.
#define 	AT91C_HDMA_RES1_0                    (0x0UL <<  9)      // (HDMA) No effect.
#define 	AT91C_HDMA_RES1_1                    (0x1UL <<  9)      // (HDMA) Resumes the channel 1.
#define AT91C_HDMA_RES2           (0x1UL << 10) // (HDMA) Write one to this field to resume the channel 2 transfer restoring its context.
#define 	AT91C_HDMA_RES2_0                    (0x0UL << 10)      // (HDMA) No effect.
#define 	AT91C_HDMA_RES2_1                    (0x1UL << 10)      // (HDMA) Resumes the channel 2.
#define AT91C_HDMA_RES3           (0x1UL << 11) // (HDMA) Write one to this field to resume the channel 3 transfer restoring its context.
#define 	AT91C_HDMA_RES3_0                    (0x0UL << 11)      // (HDMA) No effect.
#define 	AT91C_HDMA_RES3_1                    (0x1UL << 11)      // (HDMA) Resumes the channel 3.
#define AT91C_HDMA_RES4           (0x1UL << 12) // (HDMA) Write one to this field to resume the channel 4 transfer restoring its context.
#define 	AT91C_HDMA_RES4_0                    (0x0UL << 12)      // (HDMA) No effect.
#define 	AT91C_HDMA_RES4_1                    (0x1UL << 12)      // (HDMA) Resumes the channel 4.
#define AT91C_HDMA_RES5           (0x1UL << 13) // (HDMA) Write one to this field to resume the channel 5 transfer restoring its context.
#define 	AT91C_HDMA_RES5_0                    (0x0UL << 13)      // (HDMA) No effect.
#define 	AT91C_HDMA_RES5_1                    (0x1UL << 13)      // (HDMA) Resumes the channel 5.
#define AT91C_HDMA_RES6           (0x1UL << 14) // (HDMA) Write one to this field to resume the channel 6 transfer restoring its context.
#define 	AT91C_HDMA_RES6_0                    (0x0UL << 14)      // (HDMA) No effect.
#define 	AT91C_HDMA_RES6_1                    (0x1UL << 14)      // (HDMA) Resumes the channel 6.
#define AT91C_HDMA_RES7           (0x1UL << 15) // (HDMA) Write one to this field to resume the channel 7 transfer restoring its context.
#define 	AT91C_HDMA_RES7_0                    (0x0UL << 15)      // (HDMA) No effect.
#define 	AT91C_HDMA_RES7_1                    (0x1UL << 15)      // (HDMA) Resumes the channel 7.
// -------- HDMA_CHSR : (HDMA Offset: 0x30)  -------- 
#define AT91C_HDMA_EMPT0          (0x1UL << 16) // (HDMA) When set, channel 0 is empty.
#define 	AT91C_HDMA_EMPT0_0                    (0x0UL << 16)     // (HDMA) No effect.
#define 	AT91C_HDMA_EMPT0_1                    (0x1UL << 16)     // (HDMA) Channel 0 empty.
#define AT91C_HDMA_EMPT1          (0x1UL << 17) // (HDMA) When set, channel 1 is empty.
#define 	AT91C_HDMA_EMPT1_0                    (0x0UL << 17)     // (HDMA) No effect.
#define 	AT91C_HDMA_EMPT1_1                    (0x1UL << 17)     // (HDMA) Channel 1 empty.
#define AT91C_HDMA_EMPT2          (0x1UL << 18) // (HDMA) When set, channel 2 is empty.
#define 	AT91C_HDMA_EMPT2_0                    (0x0UL << 18)     // (HDMA) No effect.
#define 	AT91C_HDMA_EMPT2_1                    (0x1UL << 18)     // (HDMA) Channel 2 empty.
#define AT91C_HDMA_EMPT3          (0x1UL << 19) // (HDMA) When set, channel 3 is empty.
#define 	AT91C_HDMA_EMPT3_0                    (0x0UL << 19)     // (HDMA) No effect.
#define 	AT91C_HDMA_EMPT3_1                    (0x1UL << 19)     // (HDMA) Channel 3 empty.
#define AT91C_HDMA_EMPT4          (0x1UL << 20) // (HDMA) When set, channel 4 is empty.
#define 	AT91C_HDMA_EMPT4_0                    (0x0UL << 20)     // (HDMA) No effect.
#define 	AT91C_HDMA_EMPT4_1                    (0x1UL << 20)     // (HDMA) Channel 4 empty.
#define AT91C_HDMA_EMPT5          (0x1UL << 21) // (HDMA) When set, channel 5 is empty.
#define 	AT91C_HDMA_EMPT5_0                    (0x0UL << 21)     // (HDMA) No effect.
#define 	AT91C_HDMA_EMPT5_1                    (0x1UL << 21)     // (HDMA) Channel 5 empty.
#define AT91C_HDMA_EMPT6          (0x1UL << 22) // (HDMA) When set, channel 6 is empty.
#define 	AT91C_HDMA_EMPT6_0                    (0x0UL << 22)     // (HDMA) No effect.
#define 	AT91C_HDMA_EMPT6_1                    (0x1UL << 22)     // (HDMA) Channel 6 empty.
#define AT91C_HDMA_EMPT7          (0x1UL << 23) // (HDMA) When set, channel 7 is empty.
#define 	AT91C_HDMA_EMPT7_0                    (0x0UL << 23)     // (HDMA) No effect.
#define 	AT91C_HDMA_EMPT7_1                    (0x1UL << 23)     // (HDMA) Channel 7 empty.
#define AT91C_HDMA_STAL0          (0x1UL << 24) // (HDMA) When set, channel 0 is stalled.
#define 	AT91C_HDMA_STAL0_0                    (0x0UL << 24)     // (HDMA) No effect.
#define 	AT91C_HDMA_STAL0_1                    (0x1UL << 24)     // (HDMA) Channel 0 stalled.
#define AT91C_HDMA_STAL1          (0x1UL << 25) // (HDMA) When set, channel 1 is stalled.
#define 	AT91C_HDMA_STAL1_0                    (0x0UL << 25)     // (HDMA) No effect.
#define 	AT91C_HDMA_STAL1_1                    (0x1UL << 25)     // (HDMA) Channel 1 stalled.
#define AT91C_HDMA_STAL2          (0x1UL << 26) // (HDMA) When set, channel 2 is stalled.
#define 	AT91C_HDMA_STAL2_0                    (0x0UL << 26)     // (HDMA) No effect.
#define 	AT91C_HDMA_STAL2_1                    (0x1UL << 26)     // (HDMA) Channel 2 stalled.
#define AT91C_HDMA_STAL3          (0x1UL << 27) // (HDMA) When set, channel 3 is stalled.
#define 	AT91C_HDMA_STAL3_0                    (0x0UL << 27)     // (HDMA) No effect.
#define 	AT91C_HDMA_STAL3_1                    (0x1UL << 27)     // (HDMA) Channel 3 stalled.
#define AT91C_HDMA_STAL4          (0x1UL << 28) // (HDMA) When set, channel 4 is stalled.
#define 	AT91C_HDMA_STAL4_0                    (0x0UL << 28)     // (HDMA) No effect.
#define 	AT91C_HDMA_STAL4_1                    (0x1UL << 28)     // (HDMA) Channel 4 stalled.
#define AT91C_HDMA_STAL5          (0x1UL << 29) // (HDMA) When set, channel 5 is stalled.
#define 	AT91C_HDMA_STAL5_0                    (0x0UL << 29)     // (HDMA) No effect.
#define 	AT91C_HDMA_STAL5_1                    (0x1UL << 29)     // (HDMA) Channel 5 stalled.
#define AT91C_HDMA_STAL6          (0x1UL << 30) // (HDMA) When set, channel 6 is stalled.
#define 	AT91C_HDMA_STAL6_0                    (0x0UL << 30)     // (HDMA) No effect.
#define 	AT91C_HDMA_STAL6_1                    (0x1UL << 30)     // (HDMA) Channel 6 stalled.
#define AT91C_HDMA_STAL7          (0x1UL << 31) // (HDMA) When set, channel 7 is stalled.
#define 	AT91C_HDMA_STAL7_0                    (0x0UL << 31)     // (HDMA) No effect.
#define 	AT91C_HDMA_STAL7_1                    (0x1UL << 31)     // (HDMA) Channel 7 stalled.
// -------- HDMA_RSVD : (HDMA Offset: 0x34)  -------- 
// -------- HDMA_RSVD : (HDMA Offset: 0x38)  -------- 
// -------- HDMA_VER : (HDMA Offset: 0x1fc)  -------- 

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR BCH Redundancy Registers
// *****************************************************************************
// *** Register offset in AT91S_BCH_ECC structure ***
#define BCH_ECC_PMECC0  ( 0)    // PMECC BCH Redundancy  0 Register
#define BCH_ECC_PMECC1  ( 4)    // PMECC BCH Redundancy  1 Register
#define BCH_ECC_PMECC2  ( 8)    // PMECC BCH Redundancy  2 Register
#define BCH_ECC_PMECC3  (12)    // PMECC BCH Redundancy  3 Register
#define BCH_ECC_PMECC4  (16)    // PMECC BCH Redundancy  4 Register
#define BCH_ECC_PMECC5  (20)    // PMECC BCH Redundancy  5 Register
#define BCH_ECC_PMECC6  (24)    // PMECC BCH Redundancy  6 Register
#define BCH_ECC_PMECC7  (28)    // PMECC BCH Redundancy  7 Register
#define BCH_ECC_PMECC8  (32)    // PMECC BCH Redundancy  8 Register
#define BCH_ECC_PMECC9  (36)    // PMECC BCH Redundancy  9 Register
#define BCH_ECC_PMECC10 (40)    // PMECC BCH Redundancy 10 Register
#define BCH_ECC_PMECC11 (44)    // PMECC BCH Redundancy 11 Register
#define BCH_ECC_PMECC12 (48)    // PMECC BCH Redundancy 12 Register
#define BCH_ECC_PMECC13 (52)    // PMECC BCH Redundancy 13 Register
#define BCH_ECC_PMECC14 (56)    // PMECC BCH Redundancy 14 Register
#define BCH_ECC_PMECC15 (60)    // PMECC BCH Redundancy 15 Register
// -------- BCH_PMECC0 : (BCH_ECC Offset: 0x0) ECC 0 register -------- 
#define AT91C_BCH_ECC0            (0x0UL <<  0) // (BCH_ECC) BCH redundancy 0
// -------- BCH_PMECC1 : (BCH_ECC Offset: 0x4) ECC 1 register -------- 
#define AT91C_BCH_ECC1            (0x0UL <<  0) // (BCH_ECC) BCH redundancy 1
// -------- BCH_PMECC2 : (BCH_ECC Offset: 0x8) ECC 2 register -------- 
#define AT91C_BCH_ECC2            (0x0UL <<  0) // (BCH_ECC) BCH redundancy 2
// -------- BCH_PMECC3 : (BCH_ECC Offset: 0xc) ECC 3 register -------- 
#define AT91C_BCH_ECC3            (0x0UL <<  0) // (BCH_ECC) BCH redundancy 3
// -------- BCH_PMECC4 : (BCH_ECC Offset: 0x10) ECC 4 register -------- 
#define AT91C_BCH_ECC4            (0x0UL <<  0) // (BCH_ECC) BCH redundancy 4
// -------- BCH_PMECC5 : (BCH_ECC Offset: 0x14) ECC 5 register -------- 
#define AT91C_BCH_ECC5            (0x0UL <<  0) // (BCH_ECC) BCH redundancy 5
// -------- BCH_PMECC6 : (BCH_ECC Offset: 0x18) ECC 6 register -------- 
#define AT91C_BCH_ECC6            (0x0UL <<  0) // (BCH_ECC) BCH redundancy 6
// -------- BCH_PMECC7 : (BCH_ECC Offset: 0x1c) ECC 7 register -------- 
#define AT91C_BCH_ECC7            (0x0UL <<  0) // (BCH_ECC) BCH redundancy 7
// -------- BCH_PMECC8 : (BCH_ECC Offset: 0x20) ECC 8 register -------- 
#define AT91C_BCH_ECC8            (0x0UL <<  0) // (BCH_ECC) BCH redundancy 8
// -------- BCH_PMECC9 : (BCH_ECC Offset: 0x24) ECC 9 register -------- 
#define AT91C_BCH_ECC9            (0x0UL <<  0) // (BCH_ECC) BCH redundancy 9
// -------- BCH_PMECC10 : (BCH_ECC Offset: 0x28) ECC 10 register -------- 
#define AT91C_BCH_ECC10           (0x0UL <<  0) // (BCH_ECC) BCH redundancy 10
// -------- BCH_PMECC11 : (BCH_ECC Offset: 0x2c) ECC 11 register -------- 
#define AT91C_BCH_ECC11           (0x0UL <<  0) // (BCH_ECC) BCH redundancy 11
// -------- BCH_PMECC12 : (BCH_ECC Offset: 0x30) ECC 12 register -------- 
#define AT91C_BCH_ECC12           (0x0UL <<  0) // (BCH_ECC) BCH redundancy 12
// -------- BCH_PMECC13 : (BCH_ECC Offset: 0x34) ECC 13 register -------- 
#define AT91C_BCH_ECC13           (0x0UL <<  0) // (BCH_ECC) BCH redundancy 13
// -------- BCH_PMECC14 : (BCH_ECC Offset: 0x38) ECC 14 register -------- 
#define AT91C_BCH_ECC14           (0x0UL <<  0) // (BCH_ECC) BCH redundancy 14
// -------- BCH_PMECC15 : (BCH_ECC Offset: 0x3c) ECC 15 register -------- 
#define AT91C_BCH_ECC15           (0x0UL <<  0) // (BCH_ECC) BCH redundancy 15

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR BCH Syndromes Registers
// *****************************************************************************
// *** Register offset in AT91S_BCH_SYN structure ***
#define BCH_SYN_PMECCSYN0 ( 0)  // PMECC Syndrome  0 Register
#define BCH_SYN_PMECCSYN1 ( 4)  // PMECC Syndrome  1 Register
#define BCH_SYN_PMECCSYN2 ( 8)  // PMECC Syndrome  2 Register
#define BCH_SYN_PMECCSYN3 (12)  // PMECC Syndrome  3 Register
#define BCH_SYN_PMECCSYN4 (16)  // PMECC Syndrome  4 Register
#define BCH_SYN_PMECCSYN5 (20)  // PMECC Syndrome  5 Register
#define BCH_SYN_PMECCSYN6 (24)  // PMECC Syndrome  6 Register
#define BCH_SYN_PMECCSYN7 (28)  // PMECC Syndrome  7 Register
#define BCH_SYN_PMECCSYN8 (32)  // PMECC Syndrome  8 Register
#define BCH_SYN_PMECCSYN9 (36)  // PMECC Syndrome  9 Register
#define BCH_SYN_PMECCSYN10 (40) // PMECC Syndrome 10 Register
#define BCH_SYN_PMECCSYN11 (44) // PMECC Syndrome 11 Register
#define BCH_SYN_Reserved (48)   // Reserved
// -------- BCH_PMECCSYN0 : (BCH_SYN Offset: 0x0) PMECC Syndrome 0 Register -------- 
#define AT91C_BCH_SYN0            (0x0UL <<  0) // (BCH_SYN) PMECC Syndrome 0
// -------- BCH_PMECCSYN1 : (BCH_SYN Offset: 0x4) PMECC Syndrome 1 Register -------- 
#define AT91C_BCH_SYN1            (0x0UL <<  0) // (BCH_SYN) PMECC Syndrome 1
// -------- BCH_PMECCSYN2 : (BCH_SYN Offset: 0x8) PMECC Syndrome 2 Register -------- 
#define AT91C_BCH_SYN2            (0x0UL <<  0) // (BCH_SYN) PMECC Syndrome 2
// -------- BCH_PMECCSYN3 : (BCH_SYN Offset: 0xc) PMECC Syndrome 3 Register -------- 
#define AT91C_BCH_SYN3            (0x0UL <<  0) // (BCH_SYN) PMECC Syndrome 3
// -------- BCH_PMECCSYN4 : (BCH_SYN Offset: 0x10) PMECC Syndrome 4 Register -------- 
#define AT91C_BCH_SYN4            (0x0UL <<  0) // (BCH_SYN) PMECC Syndrome 4
// -------- BCH_PMECCSYN5 : (BCH_SYN Offset: 0x14) PMECC Syndrome 5 Register -------- 
#define AT91C_BCH_SYN5            (0x0UL <<  0) // (BCH_SYN) PMECC Syndrome 5
// -------- BCH_PMECCSYN6 : (BCH_SYN Offset: 0x18) PMECC Syndrome 6 Register -------- 
#define AT91C_BCH_SYN6            (0x0UL <<  0) // (BCH_SYN) PMECC Syndrome 6
// -------- BCH_PMECCSYN7 : (BCH_SYN Offset: 0x1c) PMECC Syndrome 7 Register -------- 
#define AT91C_BCH_SYN7            (0x0UL <<  0) // (BCH_SYN) PMECC Syndrome 7
// -------- BCH_PMECCSYN8 : (BCH_SYN Offset: 0x20) PMECC Syndrome 8 Register -------- 
#define AT91C_BCH_SYN8            (0x0UL <<  0) // (BCH_SYN) PMECC Syndrome 8
// -------- BCH_PMECCSYN9 : (BCH_SYN Offset: 0x24) PMECC Syndrome 9 Register -------- 
#define AT91C_BCH_SYN9            (0x0UL <<  0) // (BCH_SYN) PMECC Syndrome 9
// -------- BCH_PMECCSYN10 : (BCH_SYN Offset: 0x28) PMECC Syndrome 10 Register -------- 
#define AT91C_BCH_SYN10           (0x0UL <<  0) // (BCH_SYN) PMECC Syndrome 10
// -------- BCH_PMECCSYN11 : (BCH_SYN Offset: 0x2c) PMECC Syndrome 11 Register -------- 
#define AT91C_BCH_SYN11           (0x0UL <<  0) // (BCH_SYN) PMECC Syndrome 11
// -------- BCH_SYN_RESERVED : (BCH_SYN Offset: 0x30) Reserved -------- 
#define AT91C_BCH_RESERVED        (0x0UL <<  0) // (BCH_SYN) BCH RESERVED

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Programmable Multibit ECC for MLC Device Interface
// *****************************************************************************
// *** Register offset in AT91S_BCH structure ***
#define BCH_PMECCFG0    ( 0)    // PMECC Configuration 0 Register
#define BCH_PMECCFG1    ( 4)    // PMECC Configuration 1 Register
#define BCH_PMECCFG2    ( 8)    // PMECC Configuration 2 Register
#define BCH_PMECCFG3    (12)    // PMECC Configuration 3 Register
#define BCH_PMECCFG4    (16)    // PMECC Configuration 4 Register
#define BCH_PMECCTRL    (20)    // PMECC Control Register
#define BCH_PMECCSR     (24)    // PMECC Status Register
#define BCH_PMECCIER    (28)    // PMECC Interrupt Enable Register
#define BCH_PMECCIDR    (32)    // PMECC Interrupt Disable Register
#define BCH_PMECCIMR    (36)    // PMECC Interrupt Mask Register
#define BCH_PMECCISR    (40)    // PMECC Interrupt Status Register
#define BCH_ECC         (64)    // BCH Redundancy structure
#define BCH_SYN         (576)   // BCH Syndrome   structure
// -------- BCH_PMECCFG0 : (BCH Offset: 0x0) PMECC BCH Redundancy 0 Register -------- 
#define AT91C_BCH_BCHTT           (0x7UL <<  0) // (BCH) Error correcting capability
#define 	AT91C_BCH_BCHTT_2                    (0x0UL)    // (BCH) 2  bits by block can be corrected
#define 	AT91C_BCH_BCHTT_4                    (0x1UL)    // (BCH) 4  bits by block can be corrected
#define 	AT91C_BCH_BCHTT_8                    (0x2UL)    // (BCH) 8  bits by block can be corrected
#define 	AT91C_BCH_BCHTT_16                   (0x3UL)    // (BCH) 16 bits by block can be corrected
#define 	AT91C_BCH_BCHTT_24                   (0x4UL)    // (BCH) 24 bits by block can be corrected
#define AT91C_BCH_BLKSIZE         (0x1UL <<  4) // (BCH) Block size
#define 	AT91C_BCH_BLKSIZE_512                  (0x0UL <<  4)    // (BCH) The ECC computation is based on a  512 bytes block
#define 	AT91C_BCH_BLKSIZE_1024                 (0x1UL <<  4)    // (BCH) The ECC computation is based on a 1024 bytes block
#define AT91C_BCH_PAGESIZE        (0x3UL <<  8) // (BCH) Page size
#define 	AT91C_BCH_PAGESIZE_1                    (0x0UL <<  8)   // (BCH) Page size is 1 block
#define 	AT91C_BCH_PAGESIZE_2                    (0x1UL <<  8)   // (BCH) Page size is 2 blocks
#define 	AT91C_BCH_PAGESIZE_4                    (0x2UL <<  8)   // (BCH) Page size is 4 blocks
#define 	AT91C_BCH_PAGESIZE_8                    (0x3UL <<  8)   // (BCH) Page size is 8 blocks
#define AT91C_BCH_NANDWR          (0x1UL << 12) // (BCH) Nand Write Access
#define 	AT91C_BCH_NANDWR_0                    (0x0UL << 12)     // (BCH) NANDWR is 0
#define 	AT91C_BCH_NANDWR_1                    (0x1UL << 12)     // (BCH) NANDWR is 1
#define AT91C_BCH_SPAREENA        (0x1UL << 16) // (BCH) Nand Write Access
#define 	AT91C_BCH_SPAREENA_DIS                  (0x0UL << 16)   // (BCH) The spare area is skipped in read or write accesses
#define 	AT91C_BCH_SPAREENA_ENA                  (0x1UL << 16)   // (BCH) if NANDWR = 1, the spare area is protected with the last block of data. If NANDWR is 0, the spare area contains protected data or only redundancy code
#define AT91C_BCH_AUTO            (0x1UL << 20) // (BCH) Automatic mode enable
#define 	AT91C_BCH_AUTO_DIS                  (0x0UL << 20)       // (BCH) Automatic mode disabled
#define 	AT91C_BCH_AUTO_ENA                  (0x1UL << 20)       // (BCH) Automatic mode enabled
// -------- BCH_PMECCFG1 : (BCH Offset: 0x4) PMECC BCH Redundancy 1 Register -------- 
#define AT91C_BCH_SPARESIZE       (0x1FFUL <<  0)       // (BCH) Spare size in bytes
// -------- BCH_PMECCFG2 : (BCH Offset: 0x8) PMECC BCH Redundancy 2 Register -------- 
#define AT91C_BCH_STARTADD        (0x1FFUL <<  0)       // (BCH) ECC area start address
// -------- BCH_PMECCFG3 : (BCH Offset: 0xc) PMECC BCH Redundancy 3 Register -------- 
#define AT91C_BCH_ENDADD          (0x1FFUL <<  0)       // (BCH) ECC area end address
// -------- BCH_PMECCFG4 : (BCH Offset: 0x10) PMECC BCH Redundancy 4 Register -------- 
#define AT91C_BCH_CLKCTRL         (0x7UL <<  0) // (BCH) Required number of wait states
// -------- BCH_PMECCTRL : (BCH Offset: 0x14) PMECC Control Register -------- 
#define AT91C_BCH_RST             (0x1UL <<  0) // (BCH) Reset the PMECC module
#define AT91C_BCH_DATAMODE        (0x1UL <<  1) // (BCH) Start a data phase
#define AT91C_BCH_USRMODE         (0x1UL <<  2) // (BCH) Start a user mode phase
#define AT91C_BCH_ENABLE          (0x1UL <<  4) // (BCH) Enable BCH function
#define AT91C_BCH_DISABLE         (0x1UL <<  5) // (BCH) Disable BCH function
// -------- BCH_PMECCSR : (BCH Offset: 0x18) PMECC Status Register -------- 
#define AT91C_BCH_BUSY            (0x1UL <<  0) // (BCH) The Kernel of the PMECC is busy
// -------- BCH_PMECCIER : (BCH Offset: 0x1c) PMECC Interrupt Enable Register -------- 
#define AT91C_BCH_ERRIE           (0xFFUL <<  0)        // (BCH) Error interrupt enable
// -------- BCH_PMECCIDR : (BCH Offset: 0x20) PMECC Interrupt Disable Register -------- 
#define AT91C_BCH_ERRID           (0xFFUL <<  0)        // (BCH) Error interrupt disable
// -------- BCH_PMECCIMR : (BCH Offset: 0x24) PMECC Interrupt Mask Register -------- 
#define AT91C_BCH_ERRIM           (0xFFUL <<  0)        // (BCH) Error interrupt Mask
// -------- BCH_PMECCISR : (BCH Offset: 0x28) PMECC Interrupt Status Register -------- 
#define AT91C_BCH_ERRIS           (0xFFUL <<  0)        // (BCH) Error interrupt Status

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Programmable Multibit ECC for MLC Device Error Location Interface
// *****************************************************************************
// *** Register offset in AT91S_BCHEL structure ***
#define BCHEL_PMECCELCR ( 0)    // PMECC Error Location Configuration     Register
#define BCHEL_PMECCELPR ( 4)    // PMECC Error Location Primitiv          Register
#define BCHEL_PMECCELER ( 8)    // PMECC Error Location Enable            Register
#define BCHEL_PMECCELDR (12)    // PMECC Error Location Disable           Register
#define BCHEL_PMECCELSR (16)    // PMECC Error Location Status            Register
#define BCHEL_PMECCELIER (20)   // PMECC Error Location Interrupt Enable  Register
#define BCHEL_PMECCELIDR (24)   // PMECC Error Location Interrupt Disable Register
#define BCHEL_PMECCELIMR (28)   // PMECC Error Location Interrupt Mask    Register
#define BCHEL_PMECCELISR (32)   // PMECC Error Location Interrupt Status  Register
#define BCHEL_PMECCELSIG0 (40)  // PMECC Error Location Sigma  0 Register
#define BCHEL_PMECCELSIG1 (44)  // PMECC Error Location Sigma  1 Register
#define BCHEL_PMECCELSIG2 (48)  // PMECC Error Location Sigma  2 Register
#define BCHEL_PMECCELSIG3 (52)  // PMECC Error Location Sigma  3 Register
#define BCHEL_PMECCELSIG4 (56)  // PMECC Error Location Sigma  4 Register
#define BCHEL_PMECCELSIG5 (60)  // PMECC Error Location Sigma  5 Register
#define BCHEL_PMECCELSIG6 (64)  // PMECC Error Location Sigma  6 Register
#define BCHEL_PMECCELSIG7 (68)  // PMECC Error Location Sigma  7 Register
#define BCHEL_PMECCELSIG8 (72)  // PMECC Error Location Sigma  8 Register
#define BCHEL_PMECCELSIG9 (76)  // PMECC Error Location Sigma  9 Register
#define BCHEL_PMECCELSIG10 (80) // PMECC Error Location Sigma 10 Register
#define BCHEL_PMECCELSIG11 (84) // PMECC Error Location Sigma 11 Register
#define BCHEL_PMECCELSIG12 (88) // PMECC Error Location Sigma 12 Register
#define BCHEL_PMECCELSIG13 (92) // PMECC Error Location Sigma 13 Register
#define BCHEL_PMECCELSIG14 (96) // PMECC Error Location Sigma 14 Register
#define BCHEL_PMECCELSIG15 (100)        // PMECC Error Location Sigma 15 Register
#define BCHEL_PMECCELSIG16 (104)        // PMECC Error Location Sigma 16 Register
#define BCHEL_PMECCELSIG17 (108)        // PMECC Error Location Sigma 17 Register
#define BCHEL_PMECCELSIG18 (112)        // PMECC Error Location Sigma 18 Register
#define BCHEL_PMECCELSIG19 (116)        // PMECC Error Location Sigma 19 Register
#define BCHEL_PMECCELSIG20 (120)        // PMECC Error Location Sigma 20 Register
#define BCHEL_PMECCELSIG21 (124)        // PMECC Error Location Sigma 21 Register
#define BCHEL_PMECCELSIG22 (128)        // PMECC Error Location Sigma 22 Register
#define BCHEL_PMECCELSIG23 (132)        // PMECC Error Location Sigma 23 Register
#define BCHEL_PMECCELERR0 (136) // PMECC Error Location Error position  0 Register
#define BCHEL_PMECCELERR1 (140) // PMECC Error Location Error position  1 Register
#define BCHEL_PMECCELERR2 (144) // PMECC Error Location Error position  2 Register
#define BCHEL_PMECCELERR3 (148) // PMECC Error Location Error position  3 Register
#define BCHEL_PMECCELERR4 (152) // PMECC Error Location Error position  4 Register
#define BCHEL_PMECCELERR5 (156) // PMECC Error Location Error position  5 Register
#define BCHEL_PMECCELERR6 (160) // PMECC Error Location Error position  6 Register
#define BCHEL_PMECCELERR7 (164) // PMECC Error Location Error position  7 Register
#define BCHEL_PMECCELERR8 (168) // PMECC Error Location Error position  8 Register
#define BCHEL_PMECCELERR9 (172) // PMECC Error Location Error position  9 Register
#define BCHEL_PMECCELERR10 (176)        // PMECC Error Location Error position 10 Register
#define BCHEL_PMECCELERR11 (180)        // PMECC Error Location Error position 11 Register
#define BCHEL_PMECCELERR12 (184)        // PMECC Error Location Error position 12 Register
#define BCHEL_PMECCELERR13 (188)        // PMECC Error Location Error position 13 Register
#define BCHEL_PMECCELERR14 (192)        // PMECC Error Location Error position 14 Register
#define BCHEL_PMECCELERR15 (196)        // PMECC Error Location Error position 15 Register
#define BCHEL_PMECCELERR16 (200)        // PMECC Error Location Error position 16 Register
#define BCHEL_PMECCELERR17 (204)        // PMECC Error Location Error position 17 Register
#define BCHEL_PMECCELERR18 (208)        // PMECC Error Location Error position 18 Register
#define BCHEL_PMECCELERR19 (212)        // PMECC Error Location Error position 19 Register
#define BCHEL_PMECCELERR20 (216)        // PMECC Error Location Error position 20 Register
#define BCHEL_PMECCELERR21 (220)        // PMECC Error Location Error position 21 Register
#define BCHEL_PMECCELERR22 (224)        // PMECC Error Location Error position 22 Register
#define BCHEL_PMECCELERR23 (228)        // PMECC Error Location Error position 23 Register
// -------- BCH_PMECCELCR : (BCHEL Offset: 0x0) PMECC Error Location Configuration Register -------- 
#define AT91C_BCH_ELBLKSIZE       (0x1UL <<  0) // (BCHEL) Block size
#define 	AT91C_BCH_ELBLKSIZE_512                  (0x0UL)        // (BCHEL) The ECC computation is based on a  512 bytes block
#define 	AT91C_BCH_ELBLKSIZE_1024                 (0x1UL)        // (BCHEL) The ECC computation is based on a 1024 bytes block
#define AT91C_BCH_ELBCHTT         (0x7UL << 16) // (BCHEL) Error correcting capability
#define 	AT91C_BCH_ELBCHTT_2                    (0x0UL << 16)    // (BCHEL) 2 bits by block can be corrected
#define 	AT91C_BCH_ELBCHTT_4                    (0x1UL << 16)    // (BCHEL) 4 bits by block can be corrected
#define 	AT91C_BCH_ELBCHTT_8                    (0x2UL << 16)    // (BCHEL) 8 bits by block can be corrected
#define 	AT91C_BCH_ELBCHTT_16                   (0x3UL << 16)    // (BCHEL) 16 bits by block can be corrected
#define 	AT91C_BCH_ELBCHTT_24                   (0x4UL << 16)    // (BCHEL) 24 bits by block can be corrected
// -------- BCH_PMECCELPR : (BCHEL Offset: 0x4) PMECC Error Location Primitiv Register -------- 
#define AT91C_BCH_ELPRIMITIV      (0xFFFFUL <<  0)      // (BCHEL) Primitiv polynom
// -------- BCH_PMECCELER : (BCHEL Offset: 0x8) PMECC Error Location Enable Register -------- 
#define AT91C_BCH_ELENA           (0x1UL <<  0) // (BCHEL) Enable Error Location Engine
// -------- BCH_PMECCELDR : (BCHEL Offset: 0xc) PMECC Error Location Disable Register -------- 
#define AT91C_BCH_ELDIS           (0x1UL <<  0) // (BCHEL) Disable Error Location Engine
// -------- BCH_PMECCELSR : (BCHEL Offset: 0x10) PMECC Error Location Status Register -------- 
#define AT91C_BCH_ELBUSY          (0x1UL <<  0) // (BCHEL) Disable Error Engine Busy
// -------- BCH_PMECCELIER : (BCHEL Offset: 0x14) PMECC Error Location Interrupt Enable Register -------- 
#define AT91C_BCH_ELIERDONE       (0x1UL <<  0) // (BCHEL) Computation Terminated Interrupt Enable
// -------- BCH_PMECCELIDR : (BCHEL Offset: 0x18) PMECC Error Location Interrupt Disable Register -------- 
#define AT91C_BCH_ELIDRDONE       (0x1UL <<  0) // (BCHEL) Computation Terminated Interrupt Disable
// -------- BCH_PMECCELIMR : (BCHEL Offset: 0x1c) PMECC Error Location Interrupt Mask Register -------- 
#define AT91C_BCH_ELIMRDONE       (0x1UL <<  0) // (BCHEL) Computation Terminated Interrupt Mask
// -------- BCH_PMECCELISR : (BCHEL Offset: 0x20) PMECC Error Location Interrupt Status Register -------- 
#define AT91C_BCH_ELISRDONE       (0x1UL <<  0) // (BCHEL) Computation Terminated Interrupt Status
#define AT91C_BCH_ELISRERR        (0x1FUL <<  8)        // (BCHEL) Number of the polymonial roots
// -------- BCH_PMECCELSIG0 : (BCHEL Offset: 0x28) PMECC Error Location Sigma 0 Register -------- 
#define AT91C_BCH_ELSIGMA0        (0x3FFFUL <<  0)      // (BCHEL) SIGMA 0 register
// -------- BCH_PMECCELSIG1 : (BCHEL Offset: 0x2c) PMECC Error Location Sigma 1 Register -------- 
#define AT91C_BCH_ELSIGMA1        (0x3FFFUL <<  0)      // (BCHEL) SIGMA 1 register
// -------- BCH_PMECCELSIG2 : (BCHEL Offset: 0x30) PMECC Error Location Sigma 2 Register -------- 
#define AT91C_BCH_ELSIGMA2        (0x3FFFUL <<  0)      // (BCHEL) SIGMA 2 register
// -------- BCH_PMECCELSIG3 : (BCHEL Offset: 0x34) PMECC Error Location Sigma 3 Register -------- 
#define AT91C_BCH_ELSIGMA3        (0x3FFFUL <<  0)      // (BCHEL) SIGMA 3 register
// -------- BCH_PMECCELSIG4 : (BCHEL Offset: 0x38) PMECC Error Location Sigma 4 Register -------- 
#define AT91C_BCH_ELSIGMA4        (0x3FFFUL <<  0)      // (BCHEL) SIGMA 4 register
// -------- BCH_PMECCELSIG5 : (BCHEL Offset: 0x3c) PMECC Error Location Sigma 5 Register -------- 
#define AT91C_BCH_ELSIGMA5        (0x3FFFUL <<  0)      // (BCHEL) SIGMA 5 register
// -------- BCH_PMECCELSIG6 : (BCHEL Offset: 0x40) PMECC Error Location Sigma 6 Register -------- 
#define AT91C_BCH_ELSIGMA6        (0x3FFFUL <<  0)      // (BCHEL) SIGMA 6 register
// -------- BCH_PMECCELSIG7 : (BCHEL Offset: 0x44) PMECC Error Location Sigma 7 Register -------- 
#define AT91C_BCH_ELSIGMA7        (0x3FFFUL <<  0)      // (BCHEL) SIGMA 7 register
// -------- BCH_PMECCELSIG8 : (BCHEL Offset: 0x48) PMECC Error Location Sigma 8 Register -------- 
#define AT91C_BCH_ELSIGMA8        (0x3FFFUL <<  0)      // (BCHEL) SIGMA 8 register
// -------- BCH_PMECCELSIG9 : (BCHEL Offset: 0x4c) PMECC Error Location Sigma 9 Register -------- 
#define AT91C_BCH_ELSIGMA9        (0x3FFFUL <<  0)      // (BCHEL) SIGMA 9 register
// -------- BCH_PMECCELSIG10 : (BCHEL Offset: 0x50) PMECC Error Location Sigma 10 Register -------- 
#define AT91C_BCH_ELSIGMA10       (0x3FFFUL <<  0)      // (BCHEL) SIGMA 10 register
// -------- BCH_PMECCELSIG11 : (BCHEL Offset: 0x54) PMECC Error Location Sigma 11 Register -------- 
#define AT91C_BCH_ELSIGMA11       (0x3FFFUL <<  0)      // (BCHEL) SIGMA 11 register
// -------- BCH_PMECCELSIG12 : (BCHEL Offset: 0x58) PMECC Error Location Sigma 12 Register -------- 
#define AT91C_BCH_ELSIGMA12       (0x3FFFUL <<  0)      // (BCHEL) SIGMA 12 register
// -------- BCH_PMECCELSIG13 : (BCHEL Offset: 0x5c) PMECC Error Location Sigma 13 Register -------- 
#define AT91C_BCH_ELSIGMA13       (0x3FFFUL <<  0)      // (BCHEL) SIGMA 13 register
// -------- BCH_PMECCELSIG14 : (BCHEL Offset: 0x60) PMECC Error Location Sigma 14 Register -------- 
#define AT91C_BCH_ELSIGMA14       (0x3FFFUL <<  0)      // (BCHEL) SIGMA 14 register
// -------- BCH_PMECCELSIG15 : (BCHEL Offset: 0x64) PMECC Error Location Sigma 15 Register -------- 
#define AT91C_BCH_ELSIGMA15       (0x3FFFUL <<  0)      // (BCHEL) SIGMA 15 register
// -------- BCH_PMECCELSIG16 : (BCHEL Offset: 0x68) PMECC Error Location Sigma 16 Register -------- 
#define AT91C_BCH_ELSIGMA16       (0x3FFFUL <<  0)      // (BCHEL) SIGMA 16 register
// -------- BCH_PMECCELSIG17 : (BCHEL Offset: 0x6c) PMECC Error Location Sigma 17 Register -------- 
#define AT91C_BCH_ELSIGMA17       (0x3FFFUL <<  0)      // (BCHEL) SIGMA 17 register
// -------- BCH_PMECCELSIG18 : (BCHEL Offset: 0x70) PMECC Error Location Sigma 18 Register -------- 
#define AT91C_BCH_ELSIGMA18       (0x3FFFUL <<  0)      // (BCHEL) SIGMA 18 register
// -------- BCH_PMECCELSIG19 : (BCHEL Offset: 0x74) PMECC Error Location Sigma 19 Register -------- 
#define AT91C_BCH_ELSIGMA19       (0x3FFFUL <<  0)      // (BCHEL) SIGMA 19 register
// -------- BCH_PMECCELSIG20 : (BCHEL Offset: 0x78) PMECC Error Location Sigma 20 Register -------- 
#define AT91C_BCH_ELSIGMA20       (0x3FFFUL <<  0)      // (BCHEL) SIGMA 20 register
// -------- BCH_PMECCELSIG21 : (BCHEL Offset: 0x7c) PMECC Error Location Sigma 21 Register -------- 
#define AT91C_BCH_ELSIGMA21       (0x3FFFUL <<  0)      // (BCHEL) SIGMA 21 register
// -------- BCH_PMECCELSIG22 : (BCHEL Offset: 0x80) PMECC Error Location Sigma 22 Register -------- 
#define AT91C_BCH_ELSIGMA22       (0x3FFFUL <<  0)      // (BCHEL) SIGMA 22 register
// -------- BCH_PMECCELSIG23 : (BCHEL Offset: 0x84) PMECC Error Location Sigma 23 Register -------- 
#define AT91C_BCH_ELSIGMA23       (0x3FFFUL <<  0)      // (BCHEL) SIGMA 23 register
// -------- BCH_PMECCELERR0 : (BCHEL Offset: 0x88) PMECC Error Location Error position 0 Register -------- 
#define AT91C_BCH_ELERR0          (0x3FFFUL <<  0)      // (BCHEL) Error Position 0 register
// -------- BCH_PMECCELERR1 : (BCHEL Offset: 0x8c) PMECC Error Location Error position 1 Register -------- 
#define AT91C_BCH_ELERR1          (0x3FFFUL <<  0)      // (BCHEL) Error Position 1 register
// -------- BCH_PMECCELERR2 : (BCHEL Offset: 0x90) PMECC Error Location Error position 2 Register -------- 
#define AT91C_BCH_ELERR2          (0x3FFFUL <<  0)      // (BCHEL) Error Position 2 register
// -------- BCH_PMECCELERR3 : (BCHEL Offset: 0x94) PMECC Error Location Error position 3 Register -------- 
#define AT91C_BCH_ELERR3          (0x3FFFUL <<  0)      // (BCHEL) Error Position 3 register
// -------- BCH_PMECCELERR4 : (BCHEL Offset: 0x98) PMECC Error Location Error position 4 Register -------- 
#define AT91C_BCH_ELERR4          (0x3FFFUL <<  0)      // (BCHEL) Error Position 4 register
// -------- BCH_PMECCELERR5 : (BCHEL Offset: 0x9c) PMECC Error Location Error position 5 Register -------- 
#define AT91C_BCH_ELERR5          (0x3FFFUL <<  0)      // (BCHEL) Error Position 5 register
// -------- BCH_PMECCELERR6 : (BCHEL Offset: 0xa0) PMECC Error Location Error position 6 Register -------- 
#define AT91C_BCH_ELERR6          (0x3FFFUL <<  0)      // (BCHEL) Error Position 6 register
// -------- BCH_PMECCELERR7 : (BCHEL Offset: 0xa4) PMECC Error Location Error position 7 Register -------- 
#define AT91C_BCH_ELERR7          (0x3FFFUL <<  0)      // (BCHEL) Error Position 7 register
// -------- BCH_PMECCELERR8 : (BCHEL Offset: 0xa8) PMECC Error Location Error position 8 Register -------- 
#define AT91C_BCH_ELERR8          (0x3FFFUL <<  0)      // (BCHEL) Error Position 8 register
// -------- BCH_PMECCELERR9 : (BCHEL Offset: 0xac) PMECC Error Location Error position 9 Register -------- 
#define AT91C_BCH_ELERR9          (0x3FFFUL <<  0)      // (BCHEL) Error Position 9 register
// -------- BCH_PMECCELERR10 : (BCHEL Offset: 0xb0) PMECC Error Location Error position 10 Register -------- 
#define AT91C_BCH_ELERR10         (0x3FFFUL <<  0)      // (BCHEL) Error Position 10 register
// -------- BCH_PMECCELERR11 : (BCHEL Offset: 0xb4) PMECC Error Location Error position 11 Register -------- 
#define AT91C_BCH_ELERR11         (0x3FFFUL <<  0)      // (BCHEL) Error Position 11 register
// -------- BCH_PMECCELERR12 : (BCHEL Offset: 0xb8) PMECC Error Location Error position 12 Register -------- 
#define AT91C_BCH_ELERR12         (0x3FFFUL <<  0)      // (BCHEL) Error Position 12 register
// -------- BCH_PMECCELERR13 : (BCHEL Offset: 0xbc) PMECC Error Location Error position 13 Register -------- 
#define AT91C_BCH_ELERR13         (0x3FFFUL <<  0)      // (BCHEL) Error Position 13 register
// -------- BCH_PMECCELERR14 : (BCHEL Offset: 0xc0) PMECC Error Location Error position 14 Register -------- 
#define AT91C_BCH_ELERR14         (0x3FFFUL <<  0)      // (BCHEL) Error Position 14 register
// -------- BCH_PMECCELERR15 : (BCHEL Offset: 0xc4) PMECC Error Location Error position 15 Register -------- 
#define AT91C_BCH_ELERR15         (0x3FFFUL <<  0)      // (BCHEL) Error Position 15 register
// -------- BCH_PMECCELERR16 : (BCHEL Offset: 0xc8) PMECC Error Location Error position 16 Register -------- 
#define AT91C_BCH_ELERR16         (0x3FFFUL <<  0)      // (BCHEL) Error Position 16 register
// -------- BCH_PMECCELERR17 : (BCHEL Offset: 0xcc) PMECC Error Location Error position 17 Register -------- 
#define AT91C_BCH_ELERR17         (0x3FFFUL <<  0)      // (BCHEL) Error Position 17 register
// -------- BCH_PMECCELERR18 : (BCHEL Offset: 0xd0) PMECC Error Location Error position 18 Register -------- 
#define AT91C_BCH_ELERR18         (0x3FFFUL <<  0)      // (BCHEL) Error Position 18 register
// -------- BCH_PMECCELERR19 : (BCHEL Offset: 0xd4) PMECC Error Location Error position 19 Register -------- 
#define AT91C_BCH_ELERR19         (0x3FFFUL <<  0)      // (BCHEL) Error Position 19 register
// -------- BCH_PMECCELERR20 : (BCHEL Offset: 0xd8) PMECC Error Location Error position 20 Register -------- 
#define AT91C_BCH_ELERR20         (0x3FFFUL <<  0)      // (BCHEL) Error Position 20 register
// -------- BCH_PMECCELERR21 : (BCHEL Offset: 0xdc) PMECC Error Location Error position 21 Register -------- 
#define AT91C_BCH_ELERR21         (0x3FFFUL <<  0)      // (BCHEL) Error Position 21 register
// -------- BCH_PMECCELERR22 : (BCHEL Offset: 0xe0) PMECC Error Location Error position 22 Register -------- 
#define AT91C_BCH_ELERR22         (0x3FFFUL <<  0)      // (BCHEL) Error Position 22 register
// -------- BCH_PMECCELERR23 : (BCHEL Offset: 0xe4) PMECC Error Location Error position 23 Register -------- 
#define AT91C_BCH_ELERR23         (0x3FFFUL <<  0)      // (BCHEL) Error Position 23 register

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Ethernet MAC 10/100
// *****************************************************************************
// *** Register offset in AT91S_EMAC structure ***
#define EMAC_NCR        ( 0)    // Network Control Register
#define EMAC_NCFGR      ( 4)    // Network Configuration Register
#define EMAC_NSR        ( 8)    // Network Status Register
#define EMAC_TSR        (20)    // Transmit Status Register
#define EMAC_RBQP       (24)    // Receive Buffer Queue Pointer
#define EMAC_TBQP       (28)    // Transmit Buffer Queue Pointer
#define EMAC_RSR        (32)    // Receive Status Register
#define EMAC_ISR        (36)    // Interrupt Status Register
#define EMAC_IER        (40)    // Interrupt Enable Register
#define EMAC_IDR        (44)    // Interrupt Disable Register
#define EMAC_IMR        (48)    // Interrupt Mask Register
#define EMAC_MAN        (52)    // PHY Maintenance Register
#define EMAC_PTR        (56)    // Pause Time Register
#define EMAC_PFR        (60)    // Pause Frames received Register
#define EMAC_FTO        (64)    // Frames Transmitted OK Register
#define EMAC_SCF        (68)    // Single Collision Frame Register
#define EMAC_MCF        (72)    // Multiple Collision Frame Register
#define EMAC_FRO        (76)    // Frames Received OK Register
#define EMAC_FCSE       (80)    // Frame Check Sequence Error Register
#define EMAC_ALE        (84)    // Alignment Error Register
#define EMAC_DTF        (88)    // Deferred Transmission Frame Register
#define EMAC_LCOL       (92)    // Late Collision Register
#define EMAC_ECOL       (96)    // Excessive Collision Register
#define EMAC_TUND       (100)   // Transmit Underrun Error Register
#define EMAC_CSE        (104)   // Carrier Sense Error Register
#define EMAC_RRE        (108)   // Receive Ressource Error Register
#define EMAC_ROV        (112)   // Receive Overrun Errors Register
#define EMAC_RSE        (116)   // Receive Symbol Errors Register
#define EMAC_ELE        (120)   // Excessive Length Errors Register
#define EMAC_RJA        (124)   // Receive Jabbers Register
#define EMAC_USF        (128)   // Undersize Frames Register
#define EMAC_STE        (132)   // SQE Test Error Register
#define EMAC_RLE        (136)   // Receive Length Field Mismatch Register
#define EMAC_TPF        (140)   // Transmitted Pause Frames Register
#define EMAC_HRB        (144)   // Hash Address Bottom[31:0]
#define EMAC_HRT        (148)   // Hash Address Top[63:32]
#define EMAC_SA1L       (152)   // Specific Address 1 Bottom, First 4 bytes
#define EMAC_SA1H       (156)   // Specific Address 1 Top, Last 2 bytes
#define EMAC_SA2L       (160)   // Specific Address 2 Bottom, First 4 bytes
#define EMAC_SA2H       (164)   // Specific Address 2 Top, Last 2 bytes
#define EMAC_SA3L       (168)   // Specific Address 3 Bottom, First 4 bytes
#define EMAC_SA3H       (172)   // Specific Address 3 Top, Last 2 bytes
#define EMAC_SA4L       (176)   // Specific Address 4 Bottom, First 4 bytes
#define EMAC_SA4H       (180)   // Specific Address 4 Top, Last 2 bytes
#define EMAC_TID        (184)   // Type ID Checking Register
#define EMAC_TPQ        (188)   // Transmit Pause Quantum Register
#define EMAC_USRIO      (192)   // USER Input/Output Register
#define EMAC_WOL        (196)   // Wake On LAN Register
#define EMAC_REV        (252)   // Revision Register
// -------- EMAC_NCR : (EMAC Offset: 0x0)  -------- 
#define AT91C_EMAC_LB             (0x1UL <<  0) // (EMAC) Loopback. Optional. When set, loopback signal is at high level.
#define AT91C_EMAC_LLB            (0x1UL <<  1) // (EMAC) Loopback local.
#define AT91C_EMAC_RE             (0x1UL <<  2) // (EMAC) Receive enable.
#define AT91C_EMAC_TE             (0x1UL <<  3) // (EMAC) Transmit enable.
#define AT91C_EMAC_MPE            (0x1UL <<  4) // (EMAC) Management port enable.
#define AT91C_EMAC_CLRSTAT        (0x1UL <<  5) // (EMAC) Clear statistics registers.
#define AT91C_EMAC_INCSTAT        (0x1UL <<  6) // (EMAC) Increment statistics registers.
#define AT91C_EMAC_WESTAT         (0x1UL <<  7) // (EMAC) Write enable for statistics registers.
#define AT91C_EMAC_BP             (0x1UL <<  8) // (EMAC) Back pressure.
#define AT91C_EMAC_TSTART         (0x1UL <<  9) // (EMAC) Start Transmission.
#define AT91C_EMAC_THALT          (0x1UL << 10) // (EMAC) Transmission Halt.
#define AT91C_EMAC_TPFR           (0x1UL << 11) // (EMAC) Transmit pause frame
#define AT91C_EMAC_TZQ            (0x1UL << 12) // (EMAC) Transmit zero quantum pause frame
// -------- EMAC_NCFGR : (EMAC Offset: 0x4) Network Configuration Register -------- 
#define AT91C_EMAC_SPD            (0x1UL <<  0) // (EMAC) Speed.
#define AT91C_EMAC_FD             (0x1UL <<  1) // (EMAC) Full duplex.
#define AT91C_EMAC_JFRAME         (0x1UL <<  3) // (EMAC) Jumbo Frames.
#define AT91C_EMAC_CAF            (0x1UL <<  4) // (EMAC) Copy all frames.
#define AT91C_EMAC_NBC            (0x1UL <<  5) // (EMAC) No broadcast.
#define AT91C_EMAC_MTI            (0x1UL <<  6) // (EMAC) Multicast hash event enable
#define AT91C_EMAC_UNI            (0x1UL <<  7) // (EMAC) Unicast hash enable.
#define AT91C_EMAC_BIG            (0x1UL <<  8) // (EMAC) Receive 1522 bytes.
#define AT91C_EMAC_EAE            (0x1UL <<  9) // (EMAC) External address match enable.
#define AT91C_EMAC_CLK            (0x3UL << 10) // (EMAC)
#define 	AT91C_EMAC_CLK_HCLK_8               (0x0UL << 10)       // (EMAC) HCLK divided by 8
#define 	AT91C_EMAC_CLK_HCLK_16              (0x1UL << 10)       // (EMAC) HCLK divided by 16
#define 	AT91C_EMAC_CLK_HCLK_32              (0x2UL << 10)       // (EMAC) HCLK divided by 32
#define 	AT91C_EMAC_CLK_HCLK_64              (0x3UL << 10)       // (EMAC) HCLK divided by 64
#define AT91C_EMAC_RTY            (0x1UL << 12) // (EMAC)
#define AT91C_EMAC_PAE            (0x1UL << 13) // (EMAC)
#define AT91C_EMAC_RBOF           (0x3UL << 14) // (EMAC)
#define 	AT91C_EMAC_RBOF_OFFSET_0             (0x0UL << 14)      // (EMAC) no offset from start of receive buffer
#define 	AT91C_EMAC_RBOF_OFFSET_1             (0x1UL << 14)      // (EMAC) one byte offset from start of receive buffer
#define 	AT91C_EMAC_RBOF_OFFSET_2             (0x2UL << 14)      // (EMAC) two bytes offset from start of receive buffer
#define 	AT91C_EMAC_RBOF_OFFSET_3             (0x3UL << 14)      // (EMAC) three bytes offset from start of receive buffer
#define AT91C_EMAC_RLCE           (0x1UL << 16) // (EMAC) Receive Length field Checking Enable
#define AT91C_EMAC_DRFCS          (0x1UL << 17) // (EMAC) Discard Receive FCS
#define AT91C_EMAC_EFRHD          (0x1UL << 18) // (EMAC)
#define AT91C_EMAC_IRXFCS         (0x1UL << 19) // (EMAC) Ignore RX FCS
// -------- EMAC_NSR : (EMAC Offset: 0x8) Network Status Register -------- 
#define AT91C_EMAC_LINKR          (0x1UL <<  0) // (EMAC)
#define AT91C_EMAC_MDIO           (0x1UL <<  1) // (EMAC)
#define AT91C_EMAC_IDLE           (0x1UL <<  2) // (EMAC)
// -------- EMAC_TSR : (EMAC Offset: 0x14) Transmit Status Register -------- 
#define AT91C_EMAC_UBR            (0x1UL <<  0) // (EMAC)
#define AT91C_EMAC_COL            (0x1UL <<  1) // (EMAC)
#define AT91C_EMAC_RLES           (0x1UL <<  2) // (EMAC)
#define AT91C_EMAC_TGO            (0x1UL <<  3) // (EMAC) Transmit Go
#define AT91C_EMAC_BEX            (0x1UL <<  4) // (EMAC) Buffers exhausted mid frame
#define AT91C_EMAC_COMP           (0x1UL <<  5) // (EMAC)
#define AT91C_EMAC_UND            (0x1UL <<  6) // (EMAC)
// -------- EMAC_RSR : (EMAC Offset: 0x20) Receive Status Register -------- 
#define AT91C_EMAC_BNA            (0x1UL <<  0) // (EMAC)
#define AT91C_EMAC_REC            (0x1UL <<  1) // (EMAC)
#define AT91C_EMAC_OVR            (0x1UL <<  2) // (EMAC)
// -------- EMAC_ISR : (EMAC Offset: 0x24) Interrupt Status Register -------- 
#define AT91C_EMAC_MFD            (0x1UL <<  0) // (EMAC)
#define AT91C_EMAC_RCOMP          (0x1UL <<  1) // (EMAC)
#define AT91C_EMAC_RXUBR          (0x1UL <<  2) // (EMAC)
#define AT91C_EMAC_TXUBR          (0x1UL <<  3) // (EMAC)
#define AT91C_EMAC_TUNDR          (0x1UL <<  4) // (EMAC)
#define AT91C_EMAC_RLEX           (0x1UL <<  5) // (EMAC)
#define AT91C_EMAC_TXERR          (0x1UL <<  6) // (EMAC)
#define AT91C_EMAC_TCOMP          (0x1UL <<  7) // (EMAC)
#define AT91C_EMAC_LINK           (0x1UL <<  9) // (EMAC)
#define AT91C_EMAC_ROVR           (0x1UL << 10) // (EMAC)
#define AT91C_EMAC_HRESP          (0x1UL << 11) // (EMAC)
#define AT91C_EMAC_PFRE           (0x1UL << 12) // (EMAC)
#define AT91C_EMAC_PTZ            (0x1UL << 13) // (EMAC)
#define AT91C_EMAC_WOLEV          (0x1UL << 14) // (EMAC)
// -------- EMAC_IER : (EMAC Offset: 0x28) Interrupt Enable Register -------- 
// -------- EMAC_IDR : (EMAC Offset: 0x2c) Interrupt Disable Register -------- 
// -------- EMAC_IMR : (EMAC Offset: 0x30) Interrupt Mask Register -------- 
// -------- EMAC_MAN : (EMAC Offset: 0x34) PHY Maintenance Register -------- 
#define AT91C_EMAC_DATA           (0xFFFFUL <<  0)      // (EMAC)
#define AT91C_EMAC_CODE           (0x3UL << 16) // (EMAC)
#define AT91C_EMAC_REGA           (0x1FUL << 18)        // (EMAC)
#define AT91C_EMAC_PHYA           (0x1FUL << 23)        // (EMAC)
#define AT91C_EMAC_RW             (0x3UL << 28) // (EMAC)
#define AT91C_EMAC_SOF            (0x3UL << 30) // (EMAC)
// -------- EMAC_USRIO : (EMAC Offset: 0xc0) USER Input Output Register -------- 
#define AT91C_EMAC_RMII           (0x1UL <<  0) // (EMAC) Reduce MII
#define AT91C_EMAC_CLKEN          (0x1UL <<  1) // (EMAC) Clock Enable
// -------- EMAC_WOL : (EMAC Offset: 0xc4) Wake On LAN Register -------- 
#define AT91C_EMAC_IP             (0xFFFFUL <<  0)      // (EMAC) ARP request IP address
#define AT91C_EMAC_MAG            (0x1UL << 16) // (EMAC) Magic packet event enable
#define AT91C_EMAC_ARP            (0x1UL << 17) // (EMAC) ARP request event enable
#define AT91C_EMAC_SA1            (0x1UL << 18) // (EMAC) Specific address register 1 event enable
// -------- EMAC_REV : (EMAC Offset: 0xfc) Revision Register -------- 
#define AT91C_EMAC_REVREF         (0xFFFFUL <<  0)      // (EMAC)
#define AT91C_EMAC_PARTREF        (0xFFFFUL << 16)      // (EMAC)

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR Image Sensor Interface
// *****************************************************************************
// *** Register offset in AT91S_ISI structure ***
#define ISI_CFG1        ( 0)    // Configuration Register 1
#define ISI_CFG2        ( 4)    // Configuration Register 2
#define ISI_PSIZE       ( 8)    // Preview Size Register
#define ISI_PDECF       (12)    // Preview Decimation Factor Register
#define ISI_Y2RSET0     (16)    // Color Space Conversion YCrCb to RGB Register
#define ISI_Y2RSET1     (20)    // Color Space Conversion YCrCb to RGB Register
#define ISI_R2YSET0     (24)    // Color Space Conversion RGB to YCrCb Register
#define ISI_R2YSET1     (28)    // Color Space Conversion RGB to YCrCb Register
#define ISI_R2YSET2     (32)    // Color Space Conversion RGB to YCrCb Register
#define ISI_CTRL        (36)    // Control Register
#define ISI_SR          (40)    // Status Register
#define ISI_IER         (44)    // Interrupt Enable Register
#define ISI_IDR         (48)    // Interrupt Disable Register
#define ISI_IMR         (52)    // Interrupt Mask Register
#define ISI_DMACHER     (56)    // DMA Channel Enable Register
#define ISI_DMACHDR     (60)    // DMA Channel Disable Register
#define ISI_DMACHSR     (64)    // DMA Channel Status Register
#define ISI_DMAPADDR    (68)    // DMA Preview Base Address Register
#define ISI_DMAPCTRL    (72)    // DMA Preview Control Register
#define ISI_DMAPDSCR    (76)    // DMA Preview Descriptor Address Register
#define ISI_DMACADDR    (80)    // DMA Codec Base Address Register
#define ISI_DMACCTRL    (84)    // DMA Codec Control Register
#define ISI_DMACDSCR    (88)    // DMA Codec Descriptor Address Register
#define ISI_WPCR        (228)   // Write Protection Control Register
#define ISI_WPSR        (232)   // Write Protection Status Register
#define ISI_VER         (252)   // Version Register
// -------- ISI_CFG1 : (ISI Offset: 0x0) ISI Configuration Register 1 -------- 
#define AT91C_ISI_HSYNC_POL       (0x1UL <<  2) // (ISI) Horizontal synchronization polarity
#define 	AT91C_ISI_HSYNC_POL_ACTIVE_HIGH          (0x0UL <<  2)  // (ISI) HSYNC active high.
#define 	AT91C_ISI_HSYNC_POL_ACTIVE_LOW           (0x1UL <<  2)  // (ISI) HSYNC active low.
#define AT91C_ISI_VSYNC_POL       (0x1UL <<  3) // (ISI) Vertical synchronization polarity
#define 	AT91C_ISI_VSYNC_POL_ACTIVE_HIGH          (0x0UL <<  3)  // (ISI) VSYNC active high.
#define 	AT91C_ISI_VSYNC_POL_ACTIVE_LOW           (0x1UL <<  3)  // (ISI) VSYNC active low.
#define AT91C_ISI_PIXCLK_POL      (0x1UL <<  4) // (ISI) Pixel Clock Polarity
#define 	AT91C_ISI_PIXCLK_POL_RISING_EDGE          (0x0UL <<  4) // (ISI) Data is sampled on rising edge of pixel clock.
#define 	AT91C_ISI_PIXCLK_POL_FALLING_EDGE         (0x1UL <<  4) // (ISI) Data is sampled on falling edge of pixel clock.
#define AT91C_ISI_EMB_SYNC        (0x1UL <<  6) // (ISI) Embedded synchronisation
#define 	AT91C_ISI_EMB_SYNC_HSYNC_VSYNC          (0x0UL <<  6)   // (ISI) Synchronization by HSYNC, VSYNC.
#define 	AT91C_ISI_EMB_SYNC_SAV_EAV              (0x1UL <<  6)   // (ISI) Synchronisation by Embedded Synchronization Sequence SAV/EAV.
#define AT91C_ISI_CRC_SYNC        (0x1UL <<  7) // (ISI) CRC correction
#define 	AT91C_ISI_CRC_SYNC_CORRECTION_OFF       (0x0UL <<  7)   // (ISI) No CRC correction performed on embedded synchronization.
#define 	AT91C_ISI_CRC_SYNC_CORRECTION_ON        (0x1UL <<  7)   // (ISI) CRC correction is performed.
#define AT91C_ISI_FRATE           (0x7UL <<  8) // (ISI) Frame rate capture
#define AT91C_ISI_FULL            (0x1UL << 12) // (ISI) Full mode is allowed
#define 	AT91C_ISI_FULL_MODE_DISABLE         (0x0UL << 12)       // (ISI) Full mode disabled.
#define 	AT91C_ISI_FULL_MODE_ENABLE          (0x1UL << 12)       // (ISI) both codec and preview datapath are working simultaneously.
#define AT91C_ISI_THMASK          (0x3UL << 13) // (ISI) DMA Burst Mask
#define 	AT91C_ISI_THMASK_4_BURST              (0x0UL << 13)     // (ISI) Only 4 beats AHB bursts are allowed
#define 	AT91C_ISI_THMASK_4_8_BURST            (0x1UL << 13)     // (ISI) Only 4 and 8 beats AHB bursts are allowed
#define 	AT91C_ISI_THMASK_4_8_16_BURST         (0x2UL << 13)     // (ISI) 4, 8 and 16 beats AHB bursts are allowed
#define AT91C_ISI_SLD             (0xFFUL << 16)        // (ISI) Start of Line Delay
#define AT91C_ISI_SFD             (0xFFUL << 24)        // (ISI) Start of frame Delay
// -------- ISI_CFG2 : (ISI Offset: 0x4) ISI Control Register 2 -------- 
#define AT91C_ISI_IM_VSIZE        (0x7FFUL <<  0)       // (ISI) Vertical size of the Image sensor [0..2047]
#define AT91C_ISI_GS_MODE         (0x1UL << 11) // (ISI) Grayscale Memory Mode
#define 	AT91C_ISI_GS_MODE_2_PIXELS             (0x0UL << 11)    // (ISI) 2 pixels per word.
#define 	AT91C_ISI_GS_MODE_1_PIXEL              (0x1UL << 11)    // (ISI) 1 pixel per word.
#define AT91C_ISI_RGB_MODE        (0x1UL << 12) // (ISI) RGB mode
#define 	AT91C_ISI_RGB_MODE_RGB_888              (0x0UL << 12)   // (ISI) RGB 8:8:8 24 bits
#define 	AT91C_ISI_RGB_MODE_RGB_565              (0x1UL << 12)   // (ISI) RGB 5:6:5 16 bits
#define AT91C_ISI_GRAYSCALE       (0x1UL << 13) // (ISI) Grayscale Mode
#define 	AT91C_ISI_GRAYSCALE_DISABLE              (0x0UL << 13)  // (ISI) Grayscale mode is disabled
#define 	AT91C_ISI_GRAYSCALE_ENABLE               (0x1UL << 13)  // (ISI) Input image is assumed to be grayscale coded
#define AT91C_ISI_RGB_SWAP        (0x1UL << 14) // (ISI) RGB Swap
#define 	AT91C_ISI_RGB_SWAP_DISABLE              (0x0UL << 14)   // (ISI) D7 -> R7
#define 	AT91C_ISI_RGB_SWAP_ENABLE               (0x1UL << 14)   // (ISI) D0 -> R7
#define AT91C_ISI_COL_SPACE       (0x1UL << 15) // (ISI) Color space for the image data
#define 	AT91C_ISI_COL_SPACE_YCBCR                (0x0UL << 15)  // (ISI) YCbCr
#define 	AT91C_ISI_COL_SPACE_RGB                  (0x1UL << 15)  // (ISI) RGB
#define AT91C_ISI_IM_HSIZE        (0x7FFUL << 16)       // (ISI) Horizontal size of the Image sensor [0..2047]
#define AT91C_ISI_YCC_SWAP        (0x3UL << 28) // (ISI) Ycc swap
#define 	AT91C_ISI_YCC_SWAP_YCC_DEFAULT          (0x0UL << 28)   // (ISI) Cb(i) Y(i) Cr(i) Y(i+1)
#define 	AT91C_ISI_YCC_SWAP_YCC_MODE1            (0x1UL << 28)   // (ISI) Cr(i) Y(i) Cb(i) Y(i+1)
#define 	AT91C_ISI_YCC_SWAP_YCC_MODE2            (0x2UL << 28)   // (ISI) Y(i) Cb(i) Y(i+1) Cr(i)
#define 	AT91C_ISI_YCC_SWAP_YCC_MODE3            (0x3UL << 28)   // (ISI) Y(i) Cr(i) Y(i+1) Cb(i)
#define AT91C_ISI_RGB_CFG         (0x3UL << 30) // (ISI) RGB configuration
#define 	AT91C_ISI_RGB_CFG_RGB_DEFAULT          (0x0UL << 30)    // (ISI) R/G(MSB)  G(LSB)/B  R/G(MSB)  G(LSB)/B
#define 	AT91C_ISI_RGB_CFG_RGB_MODE1            (0x1UL << 30)    // (ISI) B/G(MSB)  G(LSB)/R  B/G(MSB)  G(LSB)/R
#define 	AT91C_ISI_RGB_CFG_RGB_MODE2            (0x2UL << 30)    // (ISI) G(LSB)/R  B/G(MSB)  G(LSB)/R  B/G(MSB)
#define 	AT91C_ISI_RGB_CFG_RGB_MODE3            (0x3UL << 30)    // (ISI) G(LSB)/B  R/G(MSB)  G(LSB)/B  R/G(MSB)
// -------- ISI_PSIZE : (ISI Offset: 0x8) ISI Preview Register -------- 
#define AT91C_ISI_PREV_VSIZE      (0x3FFUL <<  0)       // (ISI) Vertical size for the preview path
#define AT91C_ISI_PREV_HSIZE      (0x3FFUL << 16)       // (ISI) Horizontal size for the preview path
// -------- ISI_PDECF : (ISI Offset: 0xc) ISI Preview Decimation Factor Register -------- 
#define AT91C_ISI_DEC_FACTOR      (0xFFUL <<  0)        // (ISI) Decimation factor
// -------- ISI_Y2RSET0 : (ISI Offset: 0x10) Color Space Conversion YCrCb to RGB Register -------- 
#define AT91C_ISI_Y2R_C0          (0xFFUL <<  0)        // (ISI) Color Space Conversion Matrix Coefficient C0
#define AT91C_ISI_Y2R_C1          (0xFFUL <<  8)        // (ISI) Color Space Conversion Matrix Coefficient C1
#define AT91C_ISI_Y2R_C2          (0xFFUL << 16)        // (ISI) Color Space Conversion Matrix Coefficient C2
#define AT91C_ISI_Y2R_C3          (0xFFUL << 24)        // (ISI) Color Space Conversion Matrix Coefficient C3
// -------- ISI_Y2RSET1 : (ISI Offset: 0x14) ISI Color Space Conversion YCrCb to RGB set 1 Register -------- 
#define AT91C_ISI_Y2R_C4          (0x1FFUL <<  0)       // (ISI) Color Space Conversion Matrix Coefficient C4
#define AT91C_ISI_Y2R_YOFF        (0x1UL << 12) // (ISI) Color Space Conversion Luninance default offset
#define 	AT91C_ISI_Y2R_YOFF_0                    (0x0UL << 12)   // (ISI) Offset is 0
#define 	AT91C_ISI_Y2R_YOFF_128                  (0x1UL << 12)   // (ISI) Offset is 128
#define AT91C_ISI_Y2R_CROFF       (0x1UL << 13) // (ISI) Color Space Conversion Red Chrominance default offset
#define 	AT91C_ISI_Y2R_CROFF_0                    (0x0UL << 13)  // (ISI) Offset is 0
#define 	AT91C_ISI_Y2R_CROFF_16                   (0x1UL << 13)  // (ISI) Offset is 16
#define AT91C_ISI_Y2R_CBOFF       (0x1UL << 14) // (ISI) Color Space Conversion Blue Chrominance default offset
#define 	AT91C_ISI_Y2R_CBOFF_0                    (0x0UL << 14)  // (ISI) Offset is 0
#define 	AT91C_ISI_Y2R_CBOFF_16                   (0x1UL << 14)  // (ISI) Offset is 16
// -------- ISI_R2YSET0 : (ISI Offset: 0x18) Color Space Conversion RGB to YCrCb set 0 register -------- 
#define AT91C_ISI_R2Y_C0          (0x7FUL <<  0)        // (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C0
#define AT91C_ISI_R2Y_C1          (0x7FUL <<  8)        // (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C1
#define AT91C_ISI_R2Y_C2          (0x7FUL << 16)        // (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C2
#define AT91C_ISI_R2Y_ROFF        (0x1UL << 24) // (ISI) Color Space Conversion Red component offset
#define 	AT91C_ISI_R2Y_ROFF_0                    (0x0UL << 24)   // (ISI) Offset is 0
#define 	AT91C_ISI_R2Y_ROFF_16                   (0x1UL << 24)   // (ISI) Offset is 16
// -------- ISI_R2YSET1 : (ISI Offset: 0x1c) Color Space Conversion RGB to YCrCb set 1 register -------- 
#define AT91C_ISI_R2Y_C3          (0x7FUL <<  0)        // (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C3
#define AT91C_ISI_R2Y_C4          (0x7FUL <<  8)        // (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C4
#define AT91C_ISI_R2Y_C5          (0x7FUL << 16)        // (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C5
#define AT91C_ISI_R2Y_GOFF        (0x1UL << 24) // (ISI) Color Space Conversion Green component offset
#define 	AT91C_ISI_R2Y_GOFF_0                    (0x0UL << 24)   // (ISI) Offset is 0
#define 	AT91C_ISI_R2Y_GOFF_128                  (0x1UL << 24)   // (ISI) Offset is 128
// -------- ISI_R2YSET2 : (ISI Offset: 0x20) Color Space Conversion RGB to YCrCb set 2 register -------- 
#define AT91C_ISI_R2Y_C6          (0x7FUL <<  0)        // (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C6
#define AT91C_ISI_R2Y_C7          (0x7FUL <<  8)        // (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C7
#define AT91C_ISI_R2Y_C8          (0x7FUL << 16)        // (ISI) Color Space Conversion RGB to YCrCb Matrix coefficient C8
#define AT91C_ISI_R2Y_BOFF        (0x1UL << 24) // (ISI) Color Space Conversion Blue component offset
#define 	AT91C_ISI_R2Y_BOFF_0                    (0x0UL << 24)   // (ISI) Offset is 0
#define 	AT91C_ISI_R2Y_BOFF_128                  (0x1UL << 24)   // (ISI) Offset is 128
// -------- ISI_CTRL : (ISI Offset: 0x24) ISI Control Register -------- 
#define AT91C_ISI_EN              (0x1UL <<  0) // (ISI) Image Sensor Interface Enable Request
#define 	AT91C_ISI_EN_0                    (0x0UL)       // (ISI) No effect
#define 	AT91C_ISI_EN_1                    (0x1UL)       // (ISI) Enable the module and the capture
#define AT91C_ISI_DIS             (0x1UL <<  1) // (ISI) Image Sensor Interface Disable Request
#define 	AT91C_ISI_DIS_0                    (0x0UL <<  1)        // (ISI) No effect
#define 	AT91C_ISI_DIS_1                    (0x1UL <<  1)        // (ISI) Disable the module and the capture
#define AT91C_ISI_SRST            (0x1UL <<  2) // (ISI) Software Reset Request
#define 	AT91C_ISI_SRST_0                    (0x0UL <<  2)       // (ISI) No effect
#define 	AT91C_ISI_SRST_1                    (0x1UL <<  2)       // (ISI) Reset the module
#define AT91C_ISI_CDC             (0x1UL <<  8) // (ISI) Codec Request
#define 	AT91C_ISI_CDC_0                    (0x0UL <<  8)        // (ISI) No effect
#define 	AT91C_ISI_CDC_1                    (0x1UL <<  8)        // (ISI) Enable the Codec
// -------- ISI_SR : (ISI Offset: 0x28) ISI Status Register -------- 
#define AT91C_ISI_VSYNC           (0x1UL << 10) // (ISI) Vertical Synchronization
#define 	AT91C_ISI_VSYNC_0                    (0x0UL << 10)      // (ISI) No effect
#define 	AT91C_ISI_VSYNC_1                    (0x1UL << 10)      // (ISI) Indicates that a Vertical Synchronization has been detected since last read
#define AT91C_ISI_PXFR_DONE       (0x1UL << 16) // (ISI) Preview DMA transfer terminated
#define 	AT91C_ISI_PXFR_DONE_0                    (0x0UL << 16)  // (ISI) No effect
#define 	AT91C_ISI_PXFR_DONE_1                    (0x1UL << 16)  // (ISI) Indicates that DATA transfer on preview channel has completed since last read
#define AT91C_ISI_CXFR_DONE       (0x1UL << 17) // (ISI) Codec DMA transfer terminated
#define 	AT91C_ISI_CXFR_DONE_0                    (0x0UL << 17)  // (ISI) No effect
#define 	AT91C_ISI_CXFR_DONE_1                    (0x1UL << 17)  // (ISI) Indicates that DATA transfer on preview channel has completed since last read
#define AT91C_ISI_SIP             (0x1UL << 19) // (ISI) Synchronization In Progress
#define 	AT91C_ISI_SIP_0                    (0x0UL << 19)        // (ISI) No effect
#define 	AT91C_ISI_SIP_1                    (0x1UL << 19)        // (ISI) Indicates that Synchronization is in progress
#define AT91C_ISI_P_OVR           (0x1UL << 24) // (ISI) Fifo Preview Overflow
#define 	AT91C_ISI_P_OVR_0                    (0x0UL << 24)      // (ISI) No error
#define 	AT91C_ISI_P_OVR_1                    (0x1UL << 24)      // (ISI) An overrun condition has occurred in input FIFO on the preview path
#define AT91C_ISI_C_OVR           (0x1UL << 25) // (ISI) Fifo Codec Overflow
#define 	AT91C_ISI_C_OVR_0                    (0x0UL << 25)      // (ISI) No error
#define 	AT91C_ISI_C_OVR_1                    (0x1UL << 25)      // (ISI) An overrun condition has occurred in input FIFO on the codec path
#define AT91C_ISI_CRC_ERR         (0x1UL << 26) // (ISI) CRC synchronisation error
#define 	AT91C_ISI_CRC_ERR_0                    (0x0UL << 26)    // (ISI) No error
#define 	AT91C_ISI_CRC_ERR_1                    (0x1UL << 26)    // (ISI) CRC_SYNC is enabled in the control register and an error has been detected and not corrected. The frame is discarded and the ISI waits for a new one.
#define AT91C_ISI_FR_OVR          (0x1UL << 27) // (ISI) Frame rate overun
#define 	AT91C_ISI_FR_OVR_0                    (0x0UL << 27)     // (ISI) No error
#define 	AT91C_ISI_FR_OVR_1                    (0x1UL << 27)     // (ISI) Frame overrun, the current frame is being skipped because a vsync signal has been detected while flushing FIFOs.
// -------- ISI_IER : (ISI Offset: 0x2c) ISI Interrupt Enable Register -------- 
// -------- ISI_IDR : (ISI Offset: 0x30) ISI Interrupt Disable Register -------- 
// -------- ISI_IMR : (ISI Offset: 0x34) ISI Interrupt Mask Register -------- 
// -------- ISI_DMACHER : (ISI Offset: 0x38) DMA Channel Enable Register -------- 
#define AT91C_ISI_P_CH_EN         (0x1UL <<  0) // (ISI) Preview Channel Enable
#define 	AT91C_ISI_P_CH_EN_0                    (0x0UL)  // (ISI) No effect
#define 	AT91C_ISI_P_CH_EN_1                    (0x1UL)  // (ISI) Enable the Preview Channel
#define AT91C_ISI_C_CH_EN         (0x1UL <<  1) // (ISI) Codec Channel Enable
#define 	AT91C_ISI_C_CH_EN_0                    (0x0UL <<  1)    // (ISI) No effect
#define 	AT91C_ISI_C_CH_EN_1                    (0x1UL <<  1)    // (ISI) Enable the Codec Channel
// -------- ISI_DMACHDR : (ISI Offset: 0x3c) DMA Channel Enable Register -------- 
#define AT91C_ISI_P_CH_DIS        (0x1UL <<  0) // (ISI) Preview Channel Disable
#define 	AT91C_ISI_P_CH_DIS_0                    (0x0UL) // (ISI) No effect
#define 	AT91C_ISI_P_CH_DIS_1                    (0x1UL) // (ISI) Disable the Preview Channel
#define AT91C_ISI_C_CH_DIS        (0x1UL <<  1) // (ISI) Codec Channel Disable
#define 	AT91C_ISI_C_CH_DIS_0                    (0x0UL <<  1)   // (ISI) No effect
#define 	AT91C_ISI_C_CH_DIS_1                    (0x1UL <<  1)   // (ISI) Disable the Codec Channel
// -------- ISI_DMACHSR : (ISI Offset: 0x40) DMA Channel Status Register -------- 
#define AT91C_ISI_P_CH_S          (0x1UL <<  0) // (ISI) Preview Channel Disable
#define 	AT91C_ISI_P_CH_S_0                    (0x0UL)   // (ISI) Preview Channel is disabled
#define 	AT91C_ISI_P_CH_S_1                    (0x1UL)   // (ISI) Preview Channel is enabled
#define AT91C_ISI_C_CH_S          (0x1UL <<  1) // (ISI) Codec Channel Disable
#define 	AT91C_ISI_C_CH_S_0                    (0x0UL <<  1)     // (ISI) Codec Channel is disabled
#define 	AT91C_ISI_C_CH_S_1                    (0x1UL <<  1)     // (ISI) Codec Channel is enabled
// -------- ISI_DMAPCTRL : (ISI Offset: 0x48) DMA Preview Control Register -------- 
#define AT91C_ISI_P_FETCH         (0x1UL <<  0) // (ISI) Preview Descriptor Fetch Control Field
#define 	AT91C_ISI_P_FETCH_DISABLE              (0x0UL)  // (ISI) Preview Channel Fetch Operation is disabled
#define 	AT91C_ISI_P_FETCH_ENABLE               (0x1UL)  // (ISI) Preview Channel Fetch Operation is enabled
#define AT91C_ISI_P_DONE          (0x1UL <<  1) // (ISI) Preview Transfer Done Flag
#define 	AT91C_ISI_P_DONE_0                    (0x0UL <<  1)     // (ISI) Preview Transfer has not been performed
#define 	AT91C_ISI_P_DONE_1                    (0x1UL <<  1)     // (ISI) Preview Transfer has completed
// -------- ISI_DMACCTRL : (ISI Offset: 0x54) DMA Codec Control Register -------- 
#define AT91C_ISI_C_FETCH         (0x1UL <<  0) // (ISI) Codec Descriptor Fetch Control Field
#define 	AT91C_ISI_C_FETCH_DISABLE              (0x0UL)  // (ISI) Codec Channel Fetch Operation is disabled
#define 	AT91C_ISI_C_FETCH_ENABLE               (0x1UL)  // (ISI) Codec Channel Fetch Operation is enabled
#define AT91C_ISI_C_DONE          (0x1UL <<  1) // (ISI) Codec Transfer Done Flag
#define 	AT91C_ISI_C_DONE_0                    (0x0UL <<  1)     // (ISI) Codec Transfer has not been performed
#define 	AT91C_ISI_C_DONE_1                    (0x1UL <<  1)     // (ISI) Codec Transfer has completed
// -------- ISI_WPCR : (ISI Offset: 0xe4) Write Protection Control Register -------- 
#define AT91C_ISI_WP_EN           (0x1UL <<  0) // (ISI) Write Protection Enable
#define 	AT91C_ISI_WP_EN_DISABLE              (0x0UL)    // (ISI) Write Operation is disabled (if WP_KEY corresponds)
#define 	AT91C_ISI_WP_EN_ENABLE               (0x1UL)    // (ISI) Write Operation is enabled (if WP_KEY corresponds)
#define AT91C_ISI_WP_KEY          (0xFFFFFFUL <<  8)    // (ISI) Write Protection Key
// -------- ISI_WPSR : (ISI Offset: 0xe8) Write Protection Status Register -------- 
#define AT91C_ISI_WP_VS           (0xFUL <<  0) // (ISI) Write Protection Violation Status
#define 	AT91C_ISI_WP_VS_NO_VIOLATION         (0x0UL)    // (ISI) No Write Protection Violation detected since last read
#define 	AT91C_ISI_WP_VS_ON_WRITE             (0x1UL)    // (ISI) Write Protection Violation detected since last read
#define 	AT91C_ISI_WP_VS_ON_RESET             (0x2UL)    // (ISI) Software Reset Violation detected since last read
#define 	AT91C_ISI_WP_VS_ON_BOTH              (0x3UL)    // (ISI) Write Protection and Software Reset Violation detected since last read
#define AT91C_ISI_WP_VSRC         (0xFUL <<  8) // (ISI) Write Protection Violation Source
#define 	AT91C_ISI_WP_VSRC_NO_VIOLATION         (0x0UL <<  8)    // (ISI) No Write Protection Violation detected since last read
#define 	AT91C_ISI_WP_VSRC_ISI_CFG1             (0x1UL <<  8)    // (ISI) Write Protection Violation detected on ISI_CFG1 since last read
#define 	AT91C_ISI_WP_VSRC_ISI_CFG2             (0x2UL <<  8)    // (ISI) Write Protection Violation detected on ISI_CFG2 since last read
#define 	AT91C_ISI_WP_VSRC_ISI_PSIZE            (0x3UL <<  8)    // (ISI) Write Protection Violation detected on ISI_PSIZE since last read
#define 	AT91C_ISI_WP_VSRC_ISI_PDECF            (0x4UL <<  8)    // (ISI) Write Protection Violation detected on ISI_PDECF since last read
#define 	AT91C_ISI_WP_VSRC_ISI_Y2RSET0          (0x5UL <<  8)    // (ISI) Write Protection Violation detected on ISI_Y2RSET0 since last read
#define 	AT91C_ISI_WP_VSRC_ISI_Y2RSET1          (0x6UL <<  8)    // (ISI) Write Protection Violation detected on ISI_Y2RSET1 since last read
#define 	AT91C_ISI_WP_VSRC_ISI_R2YSET0          (0x7UL <<  8)    // (ISI) Write Protection Violation detected on ISI_R2YSET0 since last read
#define 	AT91C_ISI_WP_VSRC_ISI_R2YSET1          (0x8UL <<  8)    // (ISI) Write Protection Violation detected on ISI_R2YSET1 since last read
#define 	AT91C_ISI_WP_VSRC_ISI_R2YSET2          (0x9UL <<  8)    // (ISI) Write Protection Violation detected on ISI_R2YSET2 since last read

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR USB Host Interface
// *****************************************************************************
// *** Register offset in AT91S_UHPHS_OHCI structure ***
#define UHPHS_OHCI_HcRevision ( 0)      // Revision
#define UHPHS_OHCI_HcControl ( 4)       // Operating modes for the Host Controller
#define UHPHS_OHCI_HcCommandStatus ( 8) // Command & status Register
#define UHPHS_OHCI_HcInterruptStatus (12)       // Interrupt Status Register
#define UHPHS_OHCI_HcInterruptEnable (16)       // Interrupt Enable Register
#define UHPHS_OHCI_HcInterruptDisable (20)      // Interrupt Disable Register
#define UHPHS_OHCI_HcHCCA (24)  // Pointer to the Host Controller Communication Area
#define UHPHS_OHCI_HcPeriodCurrentED (28)       // Current Isochronous or Interrupt Endpoint Descriptor
#define UHPHS_OHCI_HcControlHeadED (32) // First Endpoint Descriptor of the Control list
#define UHPHS_OHCI_HcControlCurrentED (36)      // Endpoint Control and Status Register
#define UHPHS_OHCI_HcBulkHeadED (40)    // First endpoint register of the Bulk list
#define UHPHS_OHCI_HcBulkCurrentED (44) // Current endpoint of the Bulk list
#define UHPHS_OHCI_HcBulkDoneHead (48)  // Last completed transfer descriptor
#define UHPHS_OHCI_HcFmInterval (52)    // Bit time between 2 consecutive SOFs
#define UHPHS_OHCI_HcFmRemaining (56)   // Bit time remaining in the current Frame
#define UHPHS_OHCI_HcFmNumber (60)      // Frame number
#define UHPHS_OHCI_HcPeriodicStart (64) // Periodic Start
#define UHPHS_OHCI_HcLSThreshold (68)   // LS Threshold
#define UHPHS_OHCI_HcRhDescriptorA (72) // Root Hub characteristics A
#define UHPHS_OHCI_HcRhDescriptorB (76) // Root Hub characteristics B
#define UHPHS_OHCI_HcRhStatus (80)      // Root Hub Status register
#define UHPHS_OHCI_HcRhPortStatus (84)  // Root Hub Port Status Register

// *****************************************************************************
//              SOFTWARE API DEFINITION  FOR USB Host Interface
// *****************************************************************************
// *** Register offset in AT91S_UHPHS_EHCI structure ***
#define UHPHS_EHCI_VERSION ( 0) //
#define UHPHS_EHCI_HCSPARAMS ( 4)       //
#define UHPHS_EHCI_HCCPARAMS ( 8)       //
#define UHPHS_EHCI_HCSPPORTROUTE (12)   //
#define UHPHS_EHCI_USBCMD (16)  //
#define UHPHS_EHCI_USBSTS (20)  //
#define UHPHS_EHCI_USBINTR (24) //
#define UHPHS_EHCI_FRINDEX (28) //
#define UHPHS_EHCI_CTRLDSSEGMENT (32)   //
#define UHPHS_EHCI_PERIODICLISTBASE (36)        //
#define UHPHS_EHCI_ASYNCLISTADDR (40)   //
#define UHPHS_EHCI_CONFIGFLAG (80)      //
#define UHPHS_EHCI_PORTSC (84)  //
#define UHPHS_EHCI_INSNREG00 (144)      //
#define UHPHS_EHCI_INSNREG01 (148)      //
#define UHPHS_EHCI_INSNREG02 (152)      //
#define UHPHS_EHCI_INSNREG03 (156)      //
#define UHPHS_EHCI_INSNREG04 (160)      //
#define UHPHS_EHCI_INSNREG05 (164)      //
// -------- VERSION : (UHPHS_EHCI Offset: 0x0)  -------- 
#define AT91C_UHPHS_CAPLENGTH     (0xFFUL <<  0)        // (UHPHS_EHCI) CapLength : Offset for control registers
#define AT91C_UHPHS_HCIVERSION    (0xFFUL << 16)        // (UHPHS_EHCI) Hci Version

// *****************************************************************************
//               REGISTER ADDRESS DEFINITION FOR AT91SAM9GX5
// *****************************************************************************
// ========== Register definition for SFR peripheral ========== 
#define AT91C_SFR_EBIDELAY        (0xF805000C)  // (SFR) EBI DDR controller clock delay
#define AT91C_SFR_EMA             (0xF8050000)  // (SFR) memory Extra Margin Adjustment control
#define AT91C_SFR_UTMICFG         (0xF8050010)  // (SFR) UTMI Software Reset, and OHCI suspend interrupt control
#define AT91C_SFR_INT             (0xF8050014)  // (SFR) OHCI suspend Interrupt status
#define AT91C_SFR_DDRCFG          (0xF8050004)  // (SFR) DDR2 SSTL18 control
// ========== Register definition for SYS peripheral ========== 
#define AT91C_SYS_SLCKSEL         (0xFFFFFE50)  // (SYS) Slow Clock Selection Register
#define AT91C_SYS_GPBR            (0xFFFFFE60)  // (SYS) General Purpose Register
#define AT91C_SYS_BSCR            (0xFFFFFE54)  // (SYS) Boot Sequence Control Register
// ========== Register definition for EBI peripheral ========== 
#define AT91C_EBI_DUMMY           (0xFFFFE000)  // (EBI) Dummy register - Do not use
// ========== Register definition for DDR2C peripheral ========== 
#define AT91C_DDR2C_WPCR          (0xFFFFE8E4)  // (DDR2C) High Speed Register
#define AT91C_DDR2C_WPSR          (0xFFFFE8E8)  // (DDR2C) High Speed Register
#define AT91C_DDR2C_REF           (0xFFFFE830)  // (DDR2C) Adjust Refresh Register
#define AT91C_DDR2C_VER           (0xFFFFE828)  // (DDR2C) DLL Version Register
#define AT91C_DDR2C_LPR           (0xFFFFE81C)  // (DDR2C) Low-power Register
#define AT91C_DDR2C_T0PR          (0xFFFFE80C)  // (DDR2C) Timing0 Register
#define AT91C_DDR2C_DLL           (0xFFFFE824)  // (DDR2C) DLL Information Register
#define AT91C_DDR2C_VERSION       (0xFFFFE8FC)  // (DDR2C) Version Register
#define AT91C_DDR2C_MDR           (0xFFFFE820)  // (DDR2C) Memory Device Register
#define AT91C_DDR2C_T3PR          (0xFFFFE818)  // (DDR2C) Timing3 Register
#define AT91C_DDR2C_DELAY8        (0xFFFFE850)  // (DDR2C) Pad delay8 Register
#define AT91C_DDR2C_T2PR          (0xFFFFE814)  // (DDR2C) Timing2 Register
#define AT91C_DDR2C_HS            (0xFFFFE82C)  // (DDR2C) High Speed Register
#define AT91C_DDR2C_DELAY5        (0xFFFFE844)  // (DDR2C) Pad delay5 Register
#define AT91C_DDR2C_DELAY3        (0xFFFFE83C)  // (DDR2C) Pad delay3 Register
#define AT91C_DDR2C_CR            (0xFFFFE808)  // (DDR2C) Configuration Register
#define AT91C_DDR2C_T1PR          (0xFFFFE810)  // (DDR2C) Timing1 Register
#define AT91C_DDR2C_DELAY4        (0xFFFFE840)  // (DDR2C) Pad delay4 Register
#define AT91C_DDR2C_DRIVESTRENGTH (0xFFFFE854)  // (DDR2C) Drive Strength I/O Register
#define AT91C_DDR2C_DELAY2        (0xFFFFE838)  // (DDR2C) Pad delay2 Register
#define AT91C_DDR2C_MR            (0xFFFFE800)  // (DDR2C) Mode Register
#define AT91C_DDR2C_DELAY7        (0xFFFFE84C)  // (DDR2C) Pad delay7 Register
#define AT91C_DDR2C_RTR           (0xFFFFE804)  // (DDR2C) Refresh Timer Register
#define AT91C_DDR2C_DELAY1        (0xFFFFE834)  // (DDR2C) Pad delay1 Register
#define AT91C_DDR2C_DELAY6        (0xFFFFE848)  // (DDR2C) Pad delay6 Register
// ========== Register definition for SMC peripheral ========== 
#define AT91C_SMC_PULSE4          (0xFFFFEA44)  // (SMC)  Pulse Register for CS 4
#define AT91C_SMC_DELAY1          (0xFFFFEAC0)  // (SMC) SMC Delay Control Register
#define AT91C_SMC_SETUP2          (0xFFFFEA20)  // (SMC)  Setup Register for CS 2
#define AT91C_SMC_CYCLE0          (0xFFFFEA08)  // (SMC)  Cycle Register for CS 0
#define AT91C_SMC_DELAY5          (0xFFFFEAD0)  // (SMC) SMC Delay Control Register
#define AT91C_SMC_DELAY4          (0xFFFFEACC)  // (SMC) SMC Delay Control Register
#define AT91C_SMC_SETUP7          (0xFFFFEA70)  // (SMC)  Setup Register for CS 7
#define AT91C_SMC_PULSE7          (0xFFFFEA74)  // (SMC)  Pulse Register for CS 7
#define AT91C_SMC_CTRL0           (0xFFFFEA0C)  // (SMC)  Control Register for CS 0
#define AT91C_SMC_SETUP3          (0xFFFFEA30)  // (SMC)  Setup Register for CS 3
#define AT91C_SMC_DELAY8          (0xFFFFEADC)  // (SMC) SMC Delay Control Register
#define AT91C_SMC_SETUP4          (0xFFFFEA40)  // (SMC)  Setup Register for CS 4
#define AT91C_SMC_CYCLE6          (0xFFFFEA68)  // (SMC)  Cycle Register for CS 6
#define AT91C_SMC_CTRL1           (0xFFFFEA1C)  // (SMC)  Control Register for CS 1
#define AT91C_SMC_CYCLE3          (0xFFFFEA38)  // (SMC)  Cycle Register for CS 3
#define AT91C_SMC_CTRL5           (0xFFFFEA5C)  // (SMC)  Control Register for CS 5
#define AT91C_SMC_CTRL3           (0xFFFFEA3C)  // (SMC)  Control Register for CS 3
#define AT91C_SMC_CYCLE4          (0xFFFFEA48)  // (SMC)  Cycle Register for CS 4
#define AT91C_SMC_SETUP6          (0xFFFFEA60)  // (SMC)  Setup Register for CS 6
#define AT91C_SMC_PULSE3          (0xFFFFEA34)  // (SMC)  Pulse Register for CS 3
#define AT91C_SMC_CTRL7           (0xFFFFEA7C)  // (SMC)  Control Register for CS 7
#define AT91C_SMC_SETUP1          (0xFFFFEA10)  // (SMC)  Setup Register for CS 1
#define AT91C_SMC_PULSE5          (0xFFFFEA54)  // (SMC)  Pulse Register for CS 5
#define AT91C_SMC_PULSE0          (0xFFFFEA04)  // (SMC)  Pulse Register for CS 0
#define AT91C_SMC_CYCLE5          (0xFFFFEA58)  // (SMC)  Cycle Register for CS 5
#define AT91C_SMC_PULSE6          (0xFFFFEA64)  // (SMC)  Pulse Register for CS 6
#define AT91C_SMC_SETUP5          (0xFFFFEA50)  // (SMC)  Setup Register for CS 5
#define AT91C_SMC_DELAY3          (0xFFFFEAC8)  // (SMC) SMC Delay Control Register
#define AT91C_SMC_CTRL6           (0xFFFFEA6C)  // (SMC)  Control Register for CS 6
#define AT91C_SMC_CTRL2           (0xFFFFEA2C)  // (SMC)  Control Register for CS 2
#define AT91C_SMC_SETUP0          (0xFFFFEA00)  // (SMC)  Setup Register for CS 0
#define AT91C_SMC_CYCLE7          (0xFFFFEA78)  // (SMC)  Cycle Register for CS 7
#define AT91C_SMC_CYCLE1          (0xFFFFEA18)  // (SMC)  Cycle Register for CS 1
#define AT91C_SMC_DELAY6          (0xFFFFEAD4)  // (SMC) SMC Delay Control Register
#define AT91C_SMC_DELAY7          (0xFFFFEAD8)  // (SMC) SMC Delay Control Register
#define AT91C_SMC_DELAY2          (0xFFFFEAC4)  // (SMC) SMC Delay Control Register
#define AT91C_SMC_PULSE2          (0xFFFFEA24)  // (SMC)  Pulse Register for CS 2
#define AT91C_SMC_PULSE1          (0xFFFFEA14)  // (SMC)  Pulse Register for CS 1
#define AT91C_SMC_CYCLE2          (0xFFFFEA28)  // (SMC)  Cycle Register for CS 2
#define AT91C_SMC_CTRL4           (0xFFFFEA4C)  // (SMC)  Control Register for CS 4
// ========== Register definition for MATRIX peripheral ========== 
#define AT91C_MATRIX_VER          (0xFFFFDFFC)  // (MATRIX) HMATRIX2 VERSION REGISTER
#define AT91C_MATRIX_SCFG2        (0xFFFFDE48)  // (MATRIX)  Slave Configuration Register 2  : SMD
#define AT91C_MATRIX_SFR10        (0xFFFFDF38)  // (MATRIX)  Special Function Register 10
#define AT91C_MATRIX_SFR8         (0xFFFFDF30)  // (MATRIX)  Special Function Register 8
#define AT91C_MATRIX_SCFG4        (0xFFFFDE50)  // (MATRIX)  Slave Configuration Register 4  ; EBI
#define AT91C_MATRIX_SCFG3        (0xFFFFDE4C)  // (MATRIX)  Slave Configuration Register 3  : USB Slaves
#define AT91C_MATRIX_MCFG8        (0xFFFFDE20)  // (MATRIX)  Master Configuration Register 8  : USB Host OHCI
#define AT91C_MATRIX_SFR7         (0xFFFFDF2C)  // (MATRIX)  Special Function Register 7
#define AT91C_MATRIX_PRBS9        (0xFFFFDECC)  // (MATRIX)  PRBS9  : Peripheral Bridge 1
#define AT91C_MATRIX_SFR0         (0xFFFFDF10)  // (MATRIX)  Special Function Register 0
#define AT91C_MATRIX_PRAS6        (0xFFFFDEB0)  // (MATRIX)  PRAS6  : DDR2 S2
#define AT91C_MATRIX_SCFG5        (0xFFFFDE54)  // (MATRIX)  Slave Configuration Register 5  : DDR2 S1
#define AT91C_MATRIX_PRBS0        (0xFFFFDE84)  // (MATRIX)  PRBS0  : SRAM
#define AT91C_MATRIX_PRBS7        (0xFFFFDEBC)  // (MATRIX)  PRBS7  : DDR2 S3
#define AT91C_MATRIX_SFR11        (0xFFFFDF3C)  // (MATRIX)  Special Function Register 11
#define AT91C_MATRIX_PRAS5        (0xFFFFDEA8)  // (MATRIX)  PRAS5  : DDR2 S1
#define AT91C_MATRIX_SCFG8        (0xFFFFDE60)  // (MATRIX)  Slave Configuration Register 8  : Peripheral Bridge 0
#define AT91C_MATRIX_MRCR         (0xFFFFDF00)  // (MATRIX)  Master Remap Control Register
#define AT91C_MATRIX_PRBS5        (0xFFFFDEAC)  // (MATRIX)  PRBS5  : DDR2 S1
#define AT91C_MATRIX_WRPROTEN     (0xFFFFDFE4)  // (MATRIX)  Write Protection Control Register
#define AT91C_MATRIX_PRAS9        (0xFFFFDEC8)  // (MATRIX)  PRAS9  : Peripheral Bridge 1
#define AT91C_MATRIX_MCFG10       (0xFFFFDE28)  // (MATRIX)  Master Configuration Register 10 : eMAC0
#define AT91C_MATRIX_IPNAME1      (0xFFFFDFF0)  // (MATRIX) HMATRIX2 IPNAME1 REGISTER
#define AT91C_MATRIX_MCFG5        (0xFFFFDE14)  // (MATRIX)  Master Configuration Register 5  : DMA1 Master Port 1
#define AT91C_MATRIX_SFR4         (0xFFFFDF20)  // (MATRIX)  Special Function Register 4
#define AT91C_MATRIX_MCFG2        (0xFFFFDE08)  // (MATRIX)  Master Configuration Register 2  : DMA0 Master Port 0
#define AT91C_MATRIX_SFR2         (0xFFFFDF18)  // (MATRIX)  Special Function Register 2
#define AT91C_MATRIX_PRBS2        (0xFFFFDE94)  // (MATRIX)  PRBS2  : SMD
#define AT91C_MATRIX_PRBS8        (0xFFFFDEC4)  // (MATRIX)  PRBS8  : Peripheral Bridge 0
#define AT91C_MATRIX_SFR1         (0xFFFFDF14)  // (MATRIX)  Special Function Register 1
#define AT91C_MATRIX_SCFG0        (0xFFFFDE40)  // (MATRIX)  Slave Configuration Register 0  : SRAM
#define AT91C_MATRIX_PRAS3        (0xFFFFDE98)  // (MATRIX)  PRAS3  : USB Slaves
#define AT91C_MATRIX_SFR6         (0xFFFFDF28)  // (MATRIX)  Special Function Register 6
#define AT91C_MATRIX_FEATURES     (0xFFFFDFF8)  // (MATRIX) HMATRIX2 FEATURES REGISTER
#define AT91C_MATRIX_PRBS6        (0xFFFFDEB4)  // (MATRIX)  PRBS6  : DDR2 S2
#define AT91C_MATRIX_PRBS1        (0xFFFFDE8C)  // (MATRIX)  PRBS1  : ROM
#define AT91C_MATRIX_PRBS3        (0xFFFFDE9C)  // (MATRIX)  PRBS3  : USB Slaves
#define AT91C_MATRIX_MCFG1        (0xFFFFDE04)  // (MATRIX)  Master Configuration Register 1  ; ARM-D
#define AT91C_MATRIX_SCFG1        (0xFFFFDE44)  // (MATRIX)  Slave Configuration Register 1  : ROM
#define AT91C_MATRIX_PRAS4        (0xFFFFDEA0)  // (MATRIX)  PRAS4  : EBI
#define AT91C_MATRIX_SFR13        (0xFFFFDF44)  // (MATRIX)  Special Function Register 13
#define AT91C_MATRIX_MCFG3        (0xFFFFDE0C)  // (MATRIX)  Master Configuration Register 3  : DMA0 Master Port 1
#define AT91C_MATRIX_WRPROTST     (0xFFFFDFE8)  // (MATRIX)  Write Protection Status Register
#define AT91C_MATRIX_IPNAME2      (0xFFFFDFF4)  // (MATRIX) HMATRIX2 IPNAME2 REGISTER
#define AT91C_MATRIX_MCFG0        (0xFFFFDE00)  // (MATRIX)  Master Configuration Register 0  : ARM-I
#define AT91C_MATRIX_PRBS4        (0xFFFFDEA4)  // (MATRIX)  PRBS4  : EBI
#define AT91C_MATRIX_MCFG7        (0xFFFFDE1C)  // (MATRIX)  Master Configuration Register 7  : USB Host EHCI
#define AT91C_MATRIX_MCFG6        (0xFFFFDE18)  // (MATRIX)  Master Configuration Register 6  : USB Device
#define AT91C_MATRIX_SFR14        (0xFFFFDF48)  // (MATRIX)  Special Function Register 14
#define AT91C_MATRIX_PRAS0        (0xFFFFDE80)  // (MATRIX)  PRAS0  : SRAM
#define AT91C_MATRIX_PRAS8        (0xFFFFDEC0)  // (MATRIX)  PRAS8  : Peripheral Bridge 0
#define AT91C_MATRIX_SFR3         (0xFFFFDF1C)  // (MATRIX)  Special Function Register 3
#define AT91C_MATRIX_MCFG4        (0xFFFFDE10)  // (MATRIX)  Master Configuration Register 4  : DMA1 Master Port 0
#define AT91C_MATRIX_PRAS1        (0xFFFFDE88)  // (MATRIX)  PRAS1  : ROM
#define AT91C_MATRIX_SFR15        (0xFFFFDF4C)  // (MATRIX)  Special Function Register 15
#define AT91C_MATRIX_SFR9         (0xFFFFDF34)  // (MATRIX)  Special Function Register 9
#define AT91C_MATRIX_SCFG7        (0xFFFFDE5C)  // (MATRIX)  Slave Configuration Register 7  : DDR2 S3
#define AT91C_MATRIX_MCFG9        (0xFFFFDE24)  // (MATRIX)  Master Configuration Register 9  : hisi/lcdc
#define AT91C_MATRIX_PRAS7        (0xFFFFDEB8)  // (MATRIX)  PRAS7  : DDR2 S3
#define AT91C_MATRIX_ADDRSIZE     (0xFFFFDFEC)  // (MATRIX) HMATRIX2 ADDRSIZE REGISTER
#define AT91C_MATRIX_SCFG9        (0xFFFFDE64)  // (MATRIX)  Slave Configuration Register 9  : Peripheral Bridge 1
#define AT91C_MATRIX_MCFG11       (0xFFFFDE2C)  // (MATRIX)  Master Configuration Register 11 : eMAC1
#define AT91C_MATRIX_SFR12        (0xFFFFDF40)  // (MATRIX)  Special Function Register 12
#define AT91C_MATRIX_PRAS2        (0xFFFFDE90)  // (MATRIX)  PRAS2  : SMD
#define AT91C_MATRIX_SFR5         (0xFFFFDF24)  // (MATRIX)  Special Function Register 5
#define AT91C_MATRIX_SCFG6        (0xFFFFDE58)  // (MATRIX)  Slave Configuration Register 6  : DDR2 S2
// ========== Register definition for CCFG peripheral ========== 
#define AT91C_CCFG_MATRIXVERSION  (0xFFFFDFFC)  // (CCFG)  Version Register
#define AT91C_CCFG_EBICSA         (0xFFFFDF20)  // (CCFG)  EBI Chip Select Assignement Register
#define AT91C_CCFG_ROM            (0xFFFFDF14)  // (CCFG)  Slave 1 (ROM) Wait-State Configuration Register
#define AT91C_CCFG_UDPHS          (0xFFFFDF1C)  // (CCFG)  USB Device HS configuration Register
// ========== Register definition for AIC peripheral ========== 
#define AT91C_AIC_IVR             (0xFFFFF100)  // (AIC) IRQ Vector Register
#define AT91C_AIC_SMR             (0xFFFFF000)  // (AIC) Source Mode Register
#define AT91C_AIC_FVR             (0xFFFFF104)  // (AIC) FIQ Vector Register
#define AT91C_AIC_DCR             (0xFFFFF138)  // (AIC) Debug Control Register (Protect)
#define AT91C_AIC_EOICR           (0xFFFFF130)  // (AIC) End of Interrupt Command Register
#define AT91C_AIC_SVR             (0xFFFFF080)  // (AIC) Source Vector Register
#define AT91C_AIC_FFSR            (0xFFFFF148)  // (AIC) Fast Forcing Status Register
#define AT91C_AIC_ICCR            (0xFFFFF128)  // (AIC) Interrupt Clear Command Register
#define AT91C_AIC_ISR             (0xFFFFF108)  // (AIC) Interrupt Status Register
#define AT91C_AIC_IMR             (0xFFFFF110)  // (AIC) Interrupt Mask Register
#define AT91C_AIC_IPR             (0xFFFFF10C)  // (AIC) Interrupt Pending Register
#define AT91C_AIC_FFER            (0xFFFFF140)  // (AIC) Fast Forcing Enable Register
#define AT91C_AIC_IECR            (0xFFFFF120)  // (AIC) Interrupt Enable Command Register
#define AT91C_AIC_ISCR            (0xFFFFF12C)  // (AIC) Interrupt Set Command Register
#define AT91C_AIC_FFDR            (0xFFFFF144)  // (AIC) Fast Forcing Disable Register
#define AT91C_AIC_CISR            (0xFFFFF114)  // (AIC) Core Interrupt Status Register
#define AT91C_AIC_IDCR            (0xFFFFF124)  // (AIC) Interrupt Disable Command Register
#define AT91C_AIC_SPU             (0xFFFFF134)  // (AIC) Spurious Vector Register
// ========== Register definition for DBGU peripheral ========== 
#define AT91C_DBGU_ADDRSIZE       (0xFFFFF2EC)  // (DBGU) DBGU ADDRSIZE REGISTER
#define AT91C_DBGU_IDR            (0xFFFFF20C)  // (DBGU) Interrupt Disable Register
#define AT91C_DBGU_MR             (0xFFFFF204)  // (DBGU) Mode Register
#define AT91C_DBGU_FNTR           (0xFFFFF248)  // (DBGU) Force NTRST Register
#define AT91C_DBGU_RHR            (0xFFFFF218)  // (DBGU) Receiver Holding Register
#define AT91C_DBGU_IPNAME1        (0xFFFFF2F0)  // (DBGU) DBGU IPNAME1 REGISTER
#define AT91C_DBGU_FEATURES       (0xFFFFF2F8)  // (DBGU) DBGU FEATURES REGISTER
#define AT91C_DBGU_BRGR           (0xFFFFF220)  // (DBGU) Baud Rate Generator Register
#define AT91C_DBGU_EXID           (0xFFFFF244)  // (DBGU) Chip ID Extension Register
#define AT91C_DBGU_CIDR           (0xFFFFF240)  // (DBGU) Chip ID Register
#define AT91C_DBGU_CSR            (0xFFFFF214)  // (DBGU) Channel Status Register
#define AT91C_DBGU_IMR            (0xFFFFF210)  // (DBGU) Interrupt Mask Register
#define AT91C_DBGU_CR             (0xFFFFF200)  // (DBGU) Control Register
#define AT91C_DBGU_THR            (0xFFFFF21C)  // (DBGU) Transmitter Holding Register
#define AT91C_DBGU_IPNAME2        (0xFFFFF2F4)  // (DBGU) DBGU IPNAME2 REGISTER
#define AT91C_DBGU_VER            (0xFFFFF2FC)  // (DBGU) DBGU VERSION REGISTER
#define AT91C_DBGU_IER            (0xFFFFF208)  // (DBGU) Interrupt Enable Register
// ========== Register definition for PIOA peripheral ========== 
#define AT91C_PIOA_SENMR          (0xFFFFF550)  // (PIOA) Sensor Mode Register
#define AT91C_PIOA_ODR            (0xFFFFF414)  // (PIOA) Output Disable Registerr
#define AT91C_PIOA_SODR           (0xFFFFF430)  // (PIOA) Set Output Data Register
#define AT91C_PIOA_DRIVE2         (0xFFFFF518)  // (PIOA) PIO DRIVE2  Register
#define AT91C_PIOA_ISR            (0xFFFFF44C)  // (PIOA) Interrupt Status Register
#define AT91C_PIOA_ABSR           (0xFFFFF478)  // (PIOA) AB Select Status Register
#define AT91C_PIOA_IMR            (0xFFFFF448)  // (PIOA) Interrupt Mask Register
#define AT91C_PIOA_MDSR           (0xFFFFF458)  // (PIOA) Multi-driver Status Register
#define AT91C_PIOA_DRIVE1         (0xFFFFF514)  // (PIOA) PIO DRIVE1  Register
#define AT91C_PIOA_FEATURES       (0xFFFFF4F8)  // (PIOA) PIO FEATURES REGISTER
#define AT91C_PIOA_PPUSR          (0xFFFFF468)  // (PIOA) Pull-up Status Register
#define AT91C_PIOA_PDSR           (0xFFFFF43C)  // (PIOA) Pin Data Status Register
#define AT91C_PIOA_MDDR           (0xFFFFF454)  // (PIOA) Multi-driver Disable Register
#define AT91C_PIOA_CODR           (0xFFFFF434)  // (PIOA) Clear Output Data Register
#define AT91C_PIOA_MDER           (0xFFFFF450)  // (PIOA) Multi-driver Enable Register
#define AT91C_PIOA_PDR            (0xFFFFF404)  // (PIOA) PIO Disable Register
#define AT91C_PIOA_IFSR           (0xFFFFF428)  // (PIOA) Input Filter Status Register
#define AT91C_PIOA_PSR            (0xFFFFF408)  // (PIOA) PIO Status Register
#define AT91C_PIOA_SENISR         (0xFFFFF560)  // (PIOA) Sensor Interrupt Status Register
#define AT91C_PIOA_SENIER         (0xFFFFF554)  // (PIOA) Sensor Interrupt Enable Register
#define AT91C_PIOA_SENIDR         (0xFFFFF558)  // (PIOA) Sensor Interrupt Disable Register
#define AT91C_PIOA_IER            (0xFFFFF440)  // (PIOA) Interrupt Enable Register
#define AT91C_PIOA_PPUDR          (0xFFFFF460)  // (PIOA) Pull-up Disable Register
#define AT91C_PIOA_PER            (0xFFFFF400)  // (PIOA) PIO Enable Register
#define AT91C_PIOA_SCHMITT        (0xFFFFF500)  // (PIOA) PIO SCHMITT Register
#define AT91C_PIOA_ADDRSIZE       (0xFFFFF4EC)  // (PIOA) PIO ADDRSIZE REGISTER
#define AT91C_PIOA_SENIMR         (0xFFFFF55C)  // (PIOA) Sensor Interrupt Mask Register
#define AT91C_PIOA_PPDSR          (0xFFFFF498)  // (PIOA) Pull-down Status Register
#define AT91C_PIOA_IFDR           (0xFFFFF424)  // (PIOA) Input Filter Disable Register
#define AT91C_PIOA_IDR            (0xFFFFF444)  // (PIOA) Interrupt Disable Register
#define AT91C_PIOA_OWDR           (0xFFFFF4A4)  // (PIOA) Output Write Disable Register
#define AT91C_PIOA_ODSR           (0xFFFFF438)  // (PIOA) Output Data Status Register
#define AT91C_PIOA_IPNAME2        (0xFFFFF4F4)  // (PIOA) PIO IPNAME2  REGISTER
#define AT91C_PIOA_OWSR           (0xFFFFF4A8)  // (PIOA) Output Write Status Register
#define AT91C_PIOA_SP2            (0xFFFFF474)  // (PIOA) Select Peripheral 2 Register
#define AT91C_PIOA_IFER           (0xFFFFF420)  // (PIOA) Input Filter Enable Register
#define AT91C_PIOA_OWER           (0xFFFFF4A0)  // (PIOA) Output Write Enable Register
#define AT91C_PIOA_PPUER          (0xFFFFF464)  // (PIOA) Pull-up Enable Register
#define AT91C_PIOA_OSR            (0xFFFFF418)  // (PIOA) Output Status Register
#define AT91C_PIOA_PPDDR          (0xFFFFF490)  // (PIOA) Pull-down Disable Register
#define AT91C_PIOA_SP1            (0xFFFFF470)  // (PIOA) Select Peripheral 1 Register
#define AT91C_PIOA_OER            (0xFFFFF410)  // (PIOA) Output Enable Register
#define AT91C_PIOA_PPDER          (0xFFFFF494)  // (PIOA) Pull-down Enable Register
#define AT91C_PIOA_VER            (0xFFFFF4FC)  // (PIOA) PIO VERSION  REGISTER
#define AT91C_PIOA_SENDATA        (0xFFFFF564)  // (PIOA) Sensor Data Register
#define AT91C_PIOA_DELAY1         (0xFFFFF510)  // (PIOA) PIO DELAY1  Register
#define AT91C_PIOA_IPNAME1        (0xFFFFF4F0)  // (PIOA) PIO IPNAME1  REGISTER
// ========== Register definition for PIOB peripheral ========== 
#define AT91C_PIOB_OWDR           (0xFFFFF6A4)  // (PIOB) Output Write Disable Register
#define AT91C_PIOB_PPDDR          (0xFFFFF690)  // (PIOB) Pull-down Disable Register
#define AT91C_PIOB_SENIMR         (0xFFFFF75C)  // (PIOB) Sensor Interrupt Mask Register
#define AT91C_PIOB_IMR            (0xFFFFF648)  // (PIOB) Interrupt Mask Register
#define AT91C_PIOB_SP1            (0xFFFFF670)  // (PIOB) Select Peripheral 1 Register
#define AT91C_PIOB_PPUDR          (0xFFFFF660)  // (PIOB) Pull-up Disable Register
#define AT91C_PIOB_CODR           (0xFFFFF634)  // (PIOB) Clear Output Data Register
#define AT91C_PIOB_OWER           (0xFFFFF6A0)  // (PIOB) Output Write Enable Register
#define AT91C_PIOB_ABSR           (0xFFFFF678)  // (PIOB) AB Select Status Register
#define AT91C_PIOB_IFDR           (0xFFFFF624)  // (PIOB) Input Filter Disable Register
#define AT91C_PIOB_VER            (0xFFFFF6FC)  // (PIOB) PIO VERSION  REGISTER
#define AT91C_PIOB_ADDRSIZE       (0xFFFFF6EC)  // (PIOB) PIO ADDRSIZE REGISTER
#define AT91C_PIOB_SENIDR         (0xFFFFF758)  // (PIOB) Sensor Interrupt Disable Register
#define AT91C_PIOB_PPDER          (0xFFFFF694)  // (PIOB) Pull-down Enable Register
#define AT91C_PIOB_ODR            (0xFFFFF614)  // (PIOB) Output Disable Registerr
#define AT91C_PIOB_PPUER          (0xFFFFF664)  // (PIOB) Pull-up Enable Register
#define AT91C_PIOB_SODR           (0xFFFFF630)  // (PIOB) Set Output Data Register
#define AT91C_PIOB_ISR            (0xFFFFF64C)  // (PIOB) Interrupt Status Register
#define AT91C_PIOB_OSR            (0xFFFFF618)  // (PIOB) Output Status Register
#define AT91C_PIOB_MDSR           (0xFFFFF658)  // (PIOB) Multi-driver Status Register
#define AT91C_PIOB_IFER           (0xFFFFF620)  // (PIOB) Input Filter Enable Register
#define AT91C_PIOB_DRIVE1         (0xFFFFF714)  // (PIOB) PIO DRIVE1  Register
#define AT91C_PIOB_SCHMITT        (0xFFFFF700)  // (PIOB) PIO SCHMITT Register
#define AT91C_PIOB_SENISR         (0xFFFFF760)  // (PIOB) Sensor Interrupt Status Register
#define AT91C_PIOB_MDER           (0xFFFFF650)  // (PIOB) Multi-driver Enable Register
#define AT91C_PIOB_PPUSR          (0xFFFFF668)  // (PIOB) Pull-up Status Register
#define AT91C_PIOB_PPDSR          (0xFFFFF698)  // (PIOB) Pull-down Status Register
#define AT91C_PIOB_PSR            (0xFFFFF608)  // (PIOB) PIO Status Register
#define AT91C_PIOB_DRIVE2         (0xFFFFF718)  // (PIOB) PIO DRIVE2  Register
#define AT91C_PIOB_IER            (0xFFFFF640)  // (PIOB) Interrupt Enable Register
#define AT91C_PIOB_FEATURES       (0xFFFFF6F8)  // (PIOB) PIO FEATURES REGISTER
#define AT91C_PIOB_SENDATA        (0xFFFFF764)  // (PIOB) Sensor Data Register
#define AT91C_PIOB_IDR            (0xFFFFF644)  // (PIOB) Interrupt Disable Register
#define AT91C_PIOB_PDSR           (0xFFFFF63C)  // (PIOB) Pin Data Status Register
#define AT91C_PIOB_PDR            (0xFFFFF604)  // (PIOB) PIO Disable Register
#define AT91C_PIOB_OWSR           (0xFFFFF6A8)  // (PIOB) Output Write Status Register
#define AT91C_PIOB_IFSR           (0xFFFFF628)  // (PIOB) Input Filter Status Register
#define AT91C_PIOB_SENIER         (0xFFFFF754)  // (PIOB) Sensor Interrupt Enable Register
#define AT91C_PIOB_ODSR           (0xFFFFF638)  // (PIOB) Output Data Status Register
#define AT91C_PIOB_IPNAME1        (0xFFFFF6F0)  // (PIOB) PIO IPNAME1  REGISTER
#define AT91C_PIOB_DELAY1         (0xFFFFF710)  // (PIOB) PIO DELAY1  Register
#define AT91C_PIOB_IPNAME2        (0xFFFFF6F4)  // (PIOB) PIO IPNAME2  REGISTER
#define AT91C_PIOB_OER            (0xFFFFF610)  // (PIOB) Output Enable Register
#define AT91C_PIOB_MDDR           (0xFFFFF654)  // (PIOB) Multi-driver Disable Register
#define AT91C_PIOB_SP2            (0xFFFFF674)  // (PIOB) Select Peripheral 2 Register
#define AT91C_PIOB_SENMR          (0xFFFFF750)  // (PIOB) Sensor Mode Register
#define AT91C_PIOB_PER            (0xFFFFF600)  // (PIOB) PIO Enable Register
// ========== Register definition for PIOC peripheral ========== 
#define AT91C_PIOC_SENIMR         (0xFFFFF95C)  // (PIOC) Sensor Interrupt Mask Register
#define AT91C_PIOC_OWDR           (0xFFFFF8A4)  // (PIOC) Output Write Disable Register
#define AT91C_PIOC_SODR           (0xFFFFF830)  // (PIOC) Set Output Data Register
#define AT91C_PIOC_PPUER          (0xFFFFF864)  // (PIOC) Pull-up Enable Register
#define AT91C_PIOC_CODR           (0xFFFFF834)  // (PIOC) Clear Output Data Register
#define AT91C_PIOC_PPDDR          (0xFFFFF890)  // (PIOC) Pull-down Disable Register
#define AT91C_PIOC_PPDER          (0xFFFFF894)  // (PIOC) Pull-down Enable Register
#define AT91C_PIOC_PSR            (0xFFFFF808)  // (PIOC) PIO Status Register
#define AT91C_PIOC_PDR            (0xFFFFF804)  // (PIOC) PIO Disable Register
#define AT91C_PIOC_ODR            (0xFFFFF814)  // (PIOC) Output Disable Registerr
#define AT91C_PIOC_SENDATA        (0xFFFFF964)  // (PIOC) Sensor Data Register
#define AT91C_PIOC_SENMR          (0xFFFFF950)  // (PIOC) Sensor Mode Register
#define AT91C_PIOC_DRIVE1         (0xFFFFF914)  // (PIOC) PIO DRIVE1  Register
#define AT91C_PIOC_PPUSR          (0xFFFFF868)  // (PIOC) Pull-up Status Register
#define AT91C_PIOC_SENIDR         (0xFFFFF958)  // (PIOC) Sensor Interrupt Disable Register
#define AT91C_PIOC_IFSR           (0xFFFFF828)  // (PIOC) Input Filter Status Register
#define AT91C_PIOC_DELAY1         (0xFFFFF910)  // (PIOC) PIO DELAY1  Register
#define AT91C_PIOC_IMR            (0xFFFFF848)  // (PIOC) Interrupt Mask Register
#define AT91C_PIOC_SENIER         (0xFFFFF954)  // (PIOC) Sensor Interrupt Enable Register
#define AT91C_PIOC_SP1            (0xFFFFF870)  // (PIOC) Select Peripheral 1 Register
#define AT91C_PIOC_OWSR           (0xFFFFF8A8)  // (PIOC) Output Write Status Register
#define AT91C_PIOC_PER            (0xFFFFF800)  // (PIOC) PIO Enable Register
#define AT91C_PIOC_MDER           (0xFFFFF850)  // (PIOC) Multi-driver Enable Register
#define AT91C_PIOC_PDSR           (0xFFFFF83C)  // (PIOC) Pin Data Status Register
#define AT91C_PIOC_MDSR           (0xFFFFF858)  // (PIOC) Multi-driver Status Register
#define AT91C_PIOC_OWER           (0xFFFFF8A0)  // (PIOC) Output Write Enable Register
#define AT91C_PIOC_SP2            (0xFFFFF874)  // (PIOC) Select Peripheral 2 Register
#define AT91C_PIOC_IFDR           (0xFFFFF824)  // (PIOC) Input Filter Disable Register
#define AT91C_PIOC_IPNAME2        (0xFFFFF8F4)  // (PIOC) PIO IPNAME2  REGISTER
#define AT91C_PIOC_FEATURES       (0xFFFFF8F8)  // (PIOC) PIO FEATURES REGISTER
#define AT91C_PIOC_ADDRSIZE       (0xFFFFF8EC)  // (PIOC) PIO ADDRSIZE REGISTER
#define AT91C_PIOC_IPNAME1        (0xFFFFF8F0)  // (PIOC) PIO IPNAME1  REGISTER
#define AT91C_PIOC_ABSR           (0xFFFFF878)  // (PIOC) AB Select Status Register
#define AT91C_PIOC_SCHMITT        (0xFFFFF900)  // (PIOC) PIO SCHMITT Register
#define AT91C_PIOC_PPDSR          (0xFFFFF898)  // (PIOC) Pull-down Status Register
#define AT91C_PIOC_OER            (0xFFFFF810)  // (PIOC) Output Enable Register
#define AT91C_PIOC_SENISR         (0xFFFFF960)  // (PIOC) Sensor Interrupt Status Register
#define AT91C_PIOC_MDDR           (0xFFFFF854)  // (PIOC) Multi-driver Disable Register
#define AT91C_PIOC_IDR            (0xFFFFF844)  // (PIOC) Interrupt Disable Register
#define AT91C_PIOC_IER            (0xFFFFF840)  // (PIOC) Interrupt Enable Register
#define AT91C_PIOC_PPUDR          (0xFFFFF860)  // (PIOC) Pull-up Disable Register
#define AT91C_PIOC_VER            (0xFFFFF8FC)  // (PIOC) PIO VERSION  REGISTER
#define AT91C_PIOC_DRIVE2         (0xFFFFF918)  // (PIOC) PIO DRIVE2  Register
#define AT91C_PIOC_ISR            (0xFFFFF84C)  // (PIOC) Interrupt Status Register
#define AT91C_PIOC_ODSR           (0xFFFFF838)  // (PIOC) Output Data Status Register
#define AT91C_PIOC_OSR            (0xFFFFF818)  // (PIOC) Output Status Register
#define AT91C_PIOC_IFER           (0xFFFFF820)  // (PIOC) Input Filter Enable Register
// ========== Register definition for PIOD peripheral ========== 
#define AT91C_PIOD_ODSR           (0xFFFFFA38)  // (PIOD) Output Data Status Register
#define AT91C_PIOD_PPDSR          (0xFFFFFA98)  // (PIOD) Pull-down Status Register
#define AT91C_PIOD_SENMR          (0xFFFFFB50)  // (PIOD) Sensor Mode Register
#define AT91C_PIOD_ABSR           (0xFFFFFA78)  // (PIOD) AB Select Status Register
#define AT91C_PIOD_SCHMITT        (0xFFFFFB00)  // (PIOD) PIO SCHMITT Register
#define AT91C_PIOD_PSR            (0xFFFFFA08)  // (PIOD) PIO Status Register
#define AT91C_PIOD_FEATURES       (0xFFFFFAF8)  // (PIOD) PIO FEATURES REGISTER
#define AT91C_PIOD_PPDER          (0xFFFFFA94)  // (PIOD) Pull-down Enable Register
#define AT91C_PIOD_PPUDR          (0xFFFFFA60)  // (PIOD) Pull-up Disable Register
#define AT91C_PIOD_OER            (0xFFFFFA10)  // (PIOD) Output Enable Register
#define AT91C_PIOD_IFSR           (0xFFFFFA28)  // (PIOD) Input Filter Status Register
#define AT91C_PIOD_IFER           (0xFFFFFA20)  // (PIOD) Input Filter Enable Register
#define AT91C_PIOD_ODR            (0xFFFFFA14)  // (PIOD) Output Disable Registerr
#define AT91C_PIOD_SENIMR         (0xFFFFFB5C)  // (PIOD) Sensor Interrupt Mask Register
#define AT91C_PIOD_IDR            (0xFFFFFA44)  // (PIOD) Interrupt Disable Register
#define AT91C_PIOD_IPNAME1        (0xFFFFFAF0)  // (PIOD) PIO IPNAME1  REGISTER
#define AT91C_PIOD_DRIVE2         (0xFFFFFB18)  // (PIOD) PIO DRIVE2  Register
#define AT91C_PIOD_SENISR         (0xFFFFFB60)  // (PIOD) Sensor Interrupt Status Register
#define AT91C_PIOD_OSR            (0xFFFFFA18)  // (PIOD) Output Status Register
#define AT91C_PIOD_CODR           (0xFFFFFA34)  // (PIOD) Clear Output Data Register
#define AT91C_PIOD_VER            (0xFFFFFAFC)  // (PIOD) PIO VERSION  REGISTER
#define AT91C_PIOD_MDSR           (0xFFFFFA58)  // (PIOD) Multi-driver Status Register
#define AT91C_PIOD_SENDATA        (0xFFFFFB64)  // (PIOD) Sensor Data Register
#define AT91C_PIOD_PDR            (0xFFFFFA04)  // (PIOD) PIO Disable Register
#define AT91C_PIOD_IER            (0xFFFFFA40)  // (PIOD) Interrupt Enable Register
#define AT91C_PIOD_OWSR           (0xFFFFFAA8)  // (PIOD) Output Write Status Register
#define AT91C_PIOD_SP2            (0xFFFFFA74)  // (PIOD) Select Peripheral 2 Register
#define AT91C_PIOD_SENIDR         (0xFFFFFB58)  // (PIOD) Sensor Interrupt Disable Register
#define AT91C_PIOD_DRIVE1         (0xFFFFFB14)  // (PIOD) PIO DRIVE1  Register
#define AT91C_PIOD_IPNAME2        (0xFFFFFAF4)  // (PIOD) PIO IPNAME2  REGISTER
#define AT91C_PIOD_PER            (0xFFFFFA00)  // (PIOD) PIO Enable Register
#define AT91C_PIOD_OWDR           (0xFFFFFAA4)  // (PIOD) Output Write Disable Register
#define AT91C_PIOD_ADDRSIZE       (0xFFFFFAEC)  // (PIOD) PIO ADDRSIZE REGISTER
#define AT91C_PIOD_IFDR           (0xFFFFFA24)  // (PIOD) Input Filter Disable Register
#define AT91C_PIOD_PPUSR          (0xFFFFFA68)  // (PIOD) Pull-up Status Register
#define AT91C_PIOD_PDSR           (0xFFFFFA3C)  // (PIOD) Pin Data Status Register
#define AT91C_PIOD_PPUER          (0xFFFFFA64)  // (PIOD) Pull-up Enable Register
#define AT91C_PIOD_DELAY1         (0xFFFFFB10)  // (PIOD) PIO DELAY1  Register
#define AT91C_PIOD_MDDR           (0xFFFFFA54)  // (PIOD) Multi-driver Disable Register
#define AT91C_PIOD_SENIER         (0xFFFFFB54)  // (PIOD) Sensor Interrupt Enable Register
#define AT91C_PIOD_ISR            (0xFFFFFA4C)  // (PIOD) Interrupt Status Register
#define AT91C_PIOD_SODR           (0xFFFFFA30)  // (PIOD) Set Output Data Register
#define AT91C_PIOD_SP1            (0xFFFFFA70)  // (PIOD) Select Peripheral 1 Register
#define AT91C_PIOD_PPDDR          (0xFFFFFA90)  // (PIOD) Pull-down Disable Register
#define AT91C_PIOD_IMR            (0xFFFFFA48)  // (PIOD) Interrupt Mask Register
#define AT91C_PIOD_OWER           (0xFFFFFAA0)  // (PIOD) Output Write Enable Register
#define AT91C_PIOD_MDER           (0xFFFFFA50)  // (PIOD) Multi-driver Enable Register
// ========== Register definition for PMC peripheral ========== 
#define AT91C_PMC_ADDRSIZE        (0xFFFFFCEC)  // (PMC)
#define AT91C_PMC_PCER            (0xFFFFFC10)  // (PMC) Peripheral Clock Enable Register  (0:31 PERI_ID)
#define AT91C_PMC_PCKR            (0xFFFFFC40)  // (PMC) Programmable Clock 0 Register
#define AT91C_PMC_MCKR            (0xFFFFFC30)  // (PMC) Master Clock Register
#define AT91C_PMC_PLLAR           (0xFFFFFC28)  // (PMC) PLL A Register
#define AT91C_PMC_NAME2           (0xFFFFFCF4)  // (PMC)
#define AT91C_PMC_FOCR            (0xFFFFFC78)  // (PMC) Fault Output Clear Register
#define AT91C_PMC_PCDR            (0xFFFFFC14)  // (PMC) Peripheral Clock Disable Register (0:31 PERI_ID)
#define AT91C_PMC_SCSR            (0xFFFFFC08)  // (PMC) System Clock Status Register
#define AT91C_PMC_MCFR            (0xFFFFFC24)  // (PMC) Main Clock  Frequency Register
#define AT91C_PMC_PCSR1           (0xFFFFFD08)  // (PMC) Peripheral Clock Status Register  32:63 PERI_ID
#define AT91C_PMC_FEATURES        (0xFFFFFCF8)  // (PMC)
#define AT91C_PMC_PLLICPR         (0xFFFFFC80)  // (PMC) PLL Charge Pump Current Register
#define AT91C_PMC_IMR             (0xFFFFFC6C)  // (PMC) Interrupt Mask Register
#define AT91C_PMC_IER             (0xFFFFFC60)  // (PMC) Interrupt Enable Register
#define AT91C_PMC_UCKR            (0xFFFFFC1C)  // (PMC) UTMI Clock Configuration Register
#define AT91C_PMC_PCR             (0xFFFFFD0C)  // (PMC) Peripheral Control Register
#define AT91C_PMC_PCER1           (0xFFFFFD00)  // (PMC) Peripheral Clock Enable Register  32:63 PERI_ID
#define AT91C_PMC_USB             (0xFFFFFC38)  // (PMC) USB clock register
#define AT91C_PMC_FSPR            (0xFFFFFC74)  // (PMC) Fast Startup Polarity Register
#define AT91C_PMC_MOR             (0xFFFFFC20)  // (PMC) Main Oscillator Register
#define AT91C_PMC_SMD             (0xFFFFFC3C)  // (PMC) SMD clock register
#define AT91C_PMC_IDR             (0xFFFFFC64)  // (PMC) Interrupt Disable Register
#define AT91C_PMC_PLLBR           (0xFFFFFC2C)  // (PMC) PLL B Register
#define AT91C_PMC_NAME1           (0xFFFFFCF0)  // (PMC)
#define AT91C_PMC_SCDR            (0xFFFFFC04)  // (PMC) System Clock Disable Register
#define AT91C_PMC_PCDR1           (0xFFFFFD04)  // (PMC) Peripheral Clock Disable Register 32:63 PERI_ID
#define AT91C_PMC_PCSR            (0xFFFFFC18)  // (PMC) Peripheral Clock Status Register  (0:31 PERI_ID)
#define AT91C_PMC_FSMR            (0xFFFFFC70)  // (PMC) Fast Startup Mode Register
#define AT91C_PMC_SCER            (0xFFFFFC00)  // (PMC) System Clock Enable Register
#define AT91C_PMC_VERSION         (0xFFFFFCFC)  // (PMC)
#define AT91C_PMC_SR              (0xFFFFFC68)  // (PMC) Status Register
// ========== Register definition for CKGR peripheral ========== 
#define AT91C_CKGR_MOR            (0xFFFFFC20)  // (CKGR) Main Oscillator Register
#define AT91C_CKGR_PLLBR          (0xFFFFFC2C)  // (CKGR) PLL B Register
#define AT91C_CKGR_MCFR           (0xFFFFFC24)  // (CKGR) Main Clock Frequency Register
#define AT91C_CKGR_PLLAR          (0xFFFFFC28)  // (CKGR) PLL A Register
#define AT91C_CKGR_UCKR           (0xFFFFFC1C)  // (CKGR) UTMI Clock Configuration Register
// ========== Register definition for RSTC peripheral ========== 
#define AT91C_RSTC_VER            (0xFFFFFEFC)  // (RSTC) Version Register
#define AT91C_RSTC_RSR            (0xFFFFFE04)  // (RSTC) Reset Status Register
#define AT91C_RSTC_RCR            (0xFFFFFE00)  // (RSTC) Reset Control Register
#define AT91C_RSTC_RMR            (0xFFFFFE08)  // (RSTC) Reset Mode Register
// ========== Register definition for SHDWC peripheral ========== 
#define AT91C_SHDWC_SHMR          (0xFFFFFE14)  // (SHDWC) Shut Down Mode Register
#define AT91C_SHDWC_SHSR          (0xFFFFFE18)  // (SHDWC) Shut Down Status Register
#define AT91C_SHDWC_SHCR          (0xFFFFFE10)  // (SHDWC) Shut Down Control Register
// ========== Register definition for RTTC peripheral ========== 
#define AT91C_RTTC_RTSR           (0xFFFFFE2C)  // (RTTC) Real-time Status Register
#define AT91C_RTTC_RTAR           (0xFFFFFE24)  // (RTTC) Real-time Alarm Register
#define AT91C_RTTC_RTMR           (0xFFFFFE20)  // (RTTC) Real-time Mode Register
#define AT91C_RTTC_RTVR           (0xFFFFFE28)  // (RTTC) Real-time Value Register
// ========== Register definition for PITC peripheral ========== 
#define AT91C_PITC_PIMR           (0xFFFFFE30)  // (PITC) Period Interval Mode Register
#define AT91C_PITC_PIIR           (0xFFFFFE3C)  // (PITC) Period Interval Image Register
#define AT91C_PITC_PISR           (0xFFFFFE34)  // (PITC) Period Interval Status Register
#define AT91C_PITC_PIVR           (0xFFFFFE38)  // (PITC) Period Interval Value Register
// ========== Register definition for WDTC peripheral ========== 
#define AT91C_WDTC_WDCR           (0xFFFFFE40)  // (WDTC) Watchdog Control Register
#define AT91C_WDTC_WDSR           (0xFFFFFE48)  // (WDTC) Watchdog Status Register
#define AT91C_WDTC_WDMR           (0xFFFFFE44)  // (WDTC) Watchdog Mode Register
// ========== Register definition for RTC peripheral ========== 
#define AT91C_RTC_MR              (0xFFFFFEB4)  // (RTC) Mode Register
#define AT91C_RTC_CALR            (0xFFFFFEBC)  // (RTC) Calendar Register
#define AT91C_RTC_CR              (0xFFFFFEB0)  // (RTC) Control Register
#define AT91C_RTC_IDR             (0xFFFFFED4)  // (RTC) Interrupt Disable Register
#define AT91C_RTC_VER             (0xFFFFFEDC)  // (RTC) Valid Entry Register
#define AT91C_RTC_IER             (0xFFFFFED0)  // (RTC) Interrupt Enable Register
#define AT91C_RTC_TIMR            (0xFFFFFEB8)  // (RTC) Time Register
#define AT91C_RTC_TIMALR          (0xFFFFFEC0)  // (RTC) Time Alarm Register
#define AT91C_RTC_IMR             (0xFFFFFED8)  // (RTC) Interrupt Mask Register
#define AT91C_RTC_CALALR          (0xFFFFFEC4)  // (RTC) Calendar Alarm Register
#define AT91C_RTC_SCCR            (0xFFFFFECC)  // (RTC) Status Clear Command Register
#define AT91C_RTC_SR              (0xFFFFFEC8)  // (RTC) Status Register
// ========== Register definition for TC0 peripheral ========== 
#define AT91C_TC0_CMR             (0xF8008004)  // (TC0) Channel Mode Register (Capture Mode / Waveform Mode)
#define AT91C_TC0_IDR             (0xF8008028)  // (TC0) Interrupt Disable Register
#define AT91C_TC0_CV              (0xF8008010)  // (TC0) Counter Value
#define AT91C_TC0_RB              (0xF8008018)  // (TC0) Register B
#define AT91C_TC0_RC              (0xF800801C)  // (TC0) Register C
#define AT91C_TC0_SR              (0xF8008020)  // (TC0) Status Register
#define AT91C_TC0_IMR             (0xF800802C)  // (TC0) Interrupt Mask Register
#define AT91C_TC0_CCR             (0xF8008000)  // (TC0) Channel Control Register
#define AT91C_TC0_RA              (0xF8008014)  // (TC0) Register A
#define AT91C_TC0_IER             (0xF8008024)  // (TC0) Interrupt Enable Register
// ========== Register definition for TC1 peripheral ========== 
#define AT91C_TC1_RB              (0xF8008058)  // (TC1) Register B
#define AT91C_TC1_CV              (0xF8008050)  // (TC1) Counter Value
#define AT91C_TC1_CMR             (0xF8008044)  // (TC1) Channel Mode Register (Capture Mode / Waveform Mode)
#define AT91C_TC1_RA              (0xF8008054)  // (TC1) Register A
#define AT91C_TC1_CCR             (0xF8008040)  // (TC1) Channel Control Register
#define AT91C_TC1_IMR             (0xF800806C)  // (TC1) Interrupt Mask Register
#define AT91C_TC1_IDR             (0xF8008068)  // (TC1) Interrupt Disable Register
#define AT91C_TC1_SR              (0xF8008060)  // (TC1) Status Register
#define AT91C_TC1_IER             (0xF8008064)  // (TC1) Interrupt Enable Register
#define AT91C_TC1_RC              (0xF800805C)  // (TC1) Register C
// ========== Register definition for TC2 peripheral ========== 
#define AT91C_TC2_IER             (0xF80080A4)  // (TC2) Interrupt Enable Register
#define AT91C_TC2_RB              (0xF8008098)  // (TC2) Register B
#define AT91C_TC2_CMR             (0xF8008084)  // (TC2) Channel Mode Register (Capture Mode / Waveform Mode)
#define AT91C_TC2_CCR             (0xF8008080)  // (TC2) Channel Control Register
#define AT91C_TC2_RA              (0xF8008094)  // (TC2) Register A
#define AT91C_TC2_IDR             (0xF80080A8)  // (TC2) Interrupt Disable Register
#define AT91C_TC2_RC              (0xF800809C)  // (TC2) Register C
#define AT91C_TC2_IMR             (0xF80080AC)  // (TC2) Interrupt Mask Register
#define AT91C_TC2_SR              (0xF80080A0)  // (TC2) Status Register
#define AT91C_TC2_CV              (0xF8008090)  // (TC2) Counter Value
// ========== Register definition for TC3 peripheral ========== 
#define AT91C_TC3_RC              (0xF800C01C)  // (TC3) Register C
#define AT91C_TC3_CV              (0xF800C010)  // (TC3) Counter Value
#define AT91C_TC3_RA              (0xF800C014)  // (TC3) Register A
#define AT91C_TC3_CCR             (0xF800C000)  // (TC3) Channel Control Register
#define AT91C_TC3_CMR             (0xF800C004)  // (TC3) Channel Mode Register (Capture Mode / Waveform Mode)
#define AT91C_TC3_IMR             (0xF800C02C)  // (TC3) Interrupt Mask Register
#define AT91C_TC3_IDR             (0xF800C028)  // (TC3) Interrupt Disable Register
#define AT91C_TC3_SR              (0xF800C020)  // (TC3) Status Register
#define AT91C_TC3_IER             (0xF800C024)  // (TC3) Interrupt Enable Register
#define AT91C_TC3_RB              (0xF800C018)  // (TC3) Register B
// ========== Register definition for TC4 peripheral ========== 
#define AT91C_TC4_IMR             (0xF800C06C)  // (TC4) Interrupt Mask Register
#define AT91C_TC4_CMR             (0xF800C044)  // (TC4) Channel Mode Register (Capture Mode / Waveform Mode)
#define AT91C_TC4_IER             (0xF800C064)  // (TC4) Interrupt Enable Register
#define AT91C_TC4_RA              (0xF800C054)  // (TC4) Register A
#define AT91C_TC4_RB              (0xF800C058)  // (TC4) Register B
#define AT91C_TC4_RC              (0xF800C05C)  // (TC4) Register C
#define AT91C_TC4_CCR             (0xF800C040)  // (TC4) Channel Control Register
#define AT91C_TC4_SR              (0xF800C060)  // (TC4) Status Register
#define AT91C_TC4_CV              (0xF800C050)  // (TC4) Counter Value
#define AT91C_TC4_IDR             (0xF800C068)  // (TC4) Interrupt Disable Register
// ========== Register definition for TC5 peripheral ========== 
#define AT91C_TC5_RB              (0xF800C098)  // (TC5) Register B
#define AT91C_TC5_CMR             (0xF800C084)  // (TC5) Channel Mode Register (Capture Mode / Waveform Mode)
#define AT91C_TC5_IDR             (0xF800C0A8)  // (TC5) Interrupt Disable Register
#define AT91C_TC5_IER             (0xF800C0A4)  // (TC5) Interrupt Enable Register
#define AT91C_TC5_CCR             (0xF800C080)  // (TC5) Channel Control Register
#define AT91C_TC5_SR              (0xF800C0A0)  // (TC5) Status Register
#define AT91C_TC5_IMR             (0xF800C0AC)  // (TC5) Interrupt Mask Register
#define AT91C_TC5_RC              (0xF800C09C)  // (TC5) Register C
#define AT91C_TC5_CV              (0xF800C090)  // (TC5) Counter Value
#define AT91C_TC5_RA              (0xF800C094)  // (TC5) Register A
// ========== Register definition for TCB0 peripheral ========== 
#define AT91C_TCB0_BMR            (0xF80080C4)  // (TCB0) TC Block Mode Register
#define AT91C_TCB0_IPNAME2        (0xF80080F4)  // (TCB0) TC IPNAME2 REGISTER
#define AT91C_TCB0_IPNAME1        (0xF80080F0)  // (TCB0) TC IPNAME1 REGISTER
#define AT91C_TCB0_ADDRSIZE       (0xF80080EC)  // (TCB0) TC ADDRSIZE REGISTER
#define AT91C_TCB0_FEATURES       (0xF80080F8)  // (TCB0) TC FEATURES REGISTER
#define AT91C_TCB0_BCR            (0xF80080C0)  // (TCB0) TC Block Control Register
#define AT91C_TCB0_VER            (0xF80080FC)  // (TCB0)  Version Register
// ========== Register definition for TCB1 peripheral ========== 
#define AT91C_TCB1_VER            (0xF800813C)  // (TCB1)  Version Register
#define AT91C_TCB1_ADDRSIZE       (0xF800812C)  // (TCB1) TC ADDRSIZE REGISTER
#define AT91C_TCB1_BMR            (0xF8008104)  // (TCB1) TC Block Mode Register
#define AT91C_TCB1_FEATURES       (0xF8008138)  // (TCB1) TC FEATURES REGISTER
#define AT91C_TCB1_IPNAME2        (0xF8008134)  // (TCB1) TC IPNAME2 REGISTER
#define AT91C_TCB1_IPNAME1        (0xF8008130)  // (TCB1) TC IPNAME1 REGISTER
#define AT91C_TCB1_BCR            (0xF8008100)  // (TCB1) TC Block Control Register
// ========== Register definition for TCB2 peripheral ========== 
#define AT91C_TCB2_IPNAME1        (0xF8008170)  // (TCB2) TC IPNAME1 REGISTER
#define AT91C_TCB2_FEATURES       (0xF8008178)  // (TCB2) TC FEATURES REGISTER
#define AT91C_TCB2_IPNAME2        (0xF8008174)  // (TCB2) TC IPNAME2 REGISTER
#define AT91C_TCB2_BCR            (0xF8008140)  // (TCB2) TC Block Control Register
#define AT91C_TCB2_BMR            (0xF8008144)  // (TCB2) TC Block Mode Register
#define AT91C_TCB2_VER            (0xF800817C)  // (TCB2)  Version Register
#define AT91C_TCB2_ADDRSIZE       (0xF800816C)  // (TCB2) TC ADDRSIZE REGISTER
// ========== Register definition for TCB3 peripheral ========== 
#define AT91C_TCB3_ADDRSIZE       (0xF800C0EC)  // (TCB3) TC ADDRSIZE REGISTER
#define AT91C_TCB3_FEATURES       (0xF800C0F8)  // (TCB3) TC FEATURES REGISTER
#define AT91C_TCB3_VER            (0xF800C0FC)  // (TCB3)  Version Register
#define AT91C_TCB3_BCR            (0xF800C0C0)  // (TCB3) TC Block Control Register
#define AT91C_TCB3_IPNAME2        (0xF800C0F4)  // (TCB3) TC IPNAME2 REGISTER
#define AT91C_TCB3_IPNAME1        (0xF800C0F0)  // (TCB3) TC IPNAME1 REGISTER
#define AT91C_TCB3_BMR            (0xF800C0C4)  // (TCB3) TC Block Mode Register
// ========== Register definition for TCB4 peripheral ========== 
#define AT91C_TCB4_FEATURES       (0xF800C138)  // (TCB4) TC FEATURES REGISTER
#define AT91C_TCB4_IPNAME2        (0xF800C134)  // (TCB4) TC IPNAME2 REGISTER
#define AT91C_TCB4_BCR            (0xF800C100)  // (TCB4) TC Block Control Register
#define AT91C_TCB4_VER            (0xF800C13C)  // (TCB4)  Version Register
#define AT91C_TCB4_ADDRSIZE       (0xF800C12C)  // (TCB4) TC ADDRSIZE REGISTER
#define AT91C_TCB4_BMR            (0xF800C104)  // (TCB4) TC Block Mode Register
#define AT91C_TCB4_IPNAME1        (0xF800C130)  // (TCB4) TC IPNAME1 REGISTER
// ========== Register definition for TCB5 peripheral ========== 
#define AT91C_TCB5_BCR            (0xF800C140)  // (TCB5) TC Block Control Register
#define AT91C_TCB5_BMR            (0xF800C144)  // (TCB5) TC Block Mode Register
#define AT91C_TCB5_IPNAME2        (0xF800C174)  // (TCB5) TC IPNAME2 REGISTER
#define AT91C_TCB5_VER            (0xF800C17C)  // (TCB5)  Version Register
#define AT91C_TCB5_FEATURES       (0xF800C178)  // (TCB5) TC FEATURES REGISTER
#define AT91C_TCB5_ADDRSIZE       (0xF800C16C)  // (TCB5) TC ADDRSIZE REGISTER
#define AT91C_TCB5_IPNAME1        (0xF800C170)  // (TCB5) TC IPNAME1 REGISTER
// ========== Register definition for MCI0 peripheral ========== 
#define AT91C_MCI0_IPNAME2        (0xF00080F4)  // (MCI0) MCI IPNAME2 REGISTER
#define AT91C_MCI0_DTOR           (0xF0008008)  // (MCI0) MCI Data Timeout Register
#define AT91C_MCI0_CR             (0xF0008000)  // (MCI0) MCI Control Register
#define AT91C_MCI0_FIFO           (0xF0008200)  // (MCI0) MCI FIFO Aperture Register
#define AT91C_MCI0_RSPR           (0xF0008020)  // (MCI0) MCI Response Register
#define AT91C_MCI0_CSTOR          (0xF000801C)  // (MCI0) MCI Completion Signal Timeout Register
#define AT91C_MCI0_IPNAME1        (0xF00080F0)  // (MCI0) MCI IPNAME1 REGISTER
#define AT91C_MCI0_CFG            (0xF0008054)  // (MCI0) MCI Configuration Register
#define AT91C_MCI0_IMR            (0xF000804C)  // (MCI0) MCI Interrupt Mask Register
#define AT91C_MCI0_VER            (0xF00080FC)  // (MCI0) MCI VERSION REGISTER
#define AT91C_MCI0_RDR            (0xF0008030)  // (MCI0) MCI Receive Data Register
#define AT91C_MCI0_CMDR           (0xF0008014)  // (MCI0) MCI Command Register
#define AT91C_MCI0_SDCR           (0xF000800C)  // (MCI0) MCI SD/SDIO Card Register
#define AT91C_MCI0_FEATURES       (0xF00080F8)  // (MCI0) MCI FEATURES REGISTER
#define AT91C_MCI0_IER            (0xF0008044)  // (MCI0) MCI Interrupt Enable Register
#define AT91C_MCI0_ADDRSIZE       (0xF00080EC)  // (MCI0) MCI ADDRSIZE REGISTER
#define AT91C_MCI0_MR             (0xF0008004)  // (MCI0) MCI Mode Register
#define AT91C_MCI0_IDR            (0xF0008048)  // (MCI0) MCI Interrupt Disable Register
#define AT91C_MCI0_WPCR           (0xF00080E4)  // (MCI0) MCI Write Protection Control Register
#define AT91C_MCI0_BLKR           (0xF0008018)  // (MCI0) MCI Block Register
#define AT91C_MCI0_ARGR           (0xF0008010)  // (MCI0) MCI Argument Register
#define AT91C_MCI0_SR             (0xF0008040)  // (MCI0) MCI Status Register
#define AT91C_MCI0_WPSR           (0xF00080E8)  // (MCI0) MCI Write Protection Status Register
#define AT91C_MCI0_TDR            (0xF0008034)  // (MCI0) MCI Transmit Data Register
#define AT91C_MCI0_DMA            (0xF0008050)  // (MCI0) MCI DMA Configuration Register
// ========== Register definition for MCI1 peripheral ========== 
#define AT91C_MCI1_ARGR           (0xF000C010)  // (MCI1) MCI Argument Register
#define AT91C_MCI1_TDR            (0xF000C034)  // (MCI1) MCI Transmit Data Register
#define AT91C_MCI1_RDR            (0xF000C030)  // (MCI1) MCI Receive Data Register
#define AT91C_MCI1_BLKR           (0xF000C018)  // (MCI1) MCI Block Register
#define AT91C_MCI1_IPNAME2        (0xF000C0F4)  // (MCI1) MCI IPNAME2 REGISTER
#define AT91C_MCI1_CSTOR          (0xF000C01C)  // (MCI1) MCI Completion Signal Timeout Register
#define AT91C_MCI1_RSPR           (0xF000C020)  // (MCI1) MCI Response Register
#define AT91C_MCI1_VER            (0xF000C0FC)  // (MCI1) MCI VERSION REGISTER
#define AT91C_MCI1_CR             (0xF000C000)  // (MCI1) MCI Control Register
#define AT91C_MCI1_DMA            (0xF000C050)  // (MCI1) MCI DMA Configuration Register
#define AT91C_MCI1_IDR            (0xF000C048)  // (MCI1) MCI Interrupt Disable Register
#define AT91C_MCI1_IER            (0xF000C044)  // (MCI1) MCI Interrupt Enable Register
#define AT91C_MCI1_WPCR           (0xF000C0E4)  // (MCI1) MCI Write Protection Control Register
#define AT91C_MCI1_CMDR           (0xF000C014)  // (MCI1) MCI Command Register
#define AT91C_MCI1_SDCR           (0xF000C00C)  // (MCI1) MCI SD/SDIO Card Register
#define AT91C_MCI1_ADDRSIZE       (0xF000C0EC)  // (MCI1) MCI ADDRSIZE REGISTER
#define AT91C_MCI1_IPNAME1        (0xF000C0F0)  // (MCI1) MCI IPNAME1 REGISTER
#define AT91C_MCI1_MR             (0xF000C004)  // (MCI1) MCI Mode Register
#define AT91C_MCI1_FEATURES       (0xF000C0F8)  // (MCI1) MCI FEATURES REGISTER
#define AT91C_MCI1_SR             (0xF000C040)  // (MCI1) MCI Status Register
#define AT91C_MCI1_IMR            (0xF000C04C)  // (MCI1) MCI Interrupt Mask Register
#define AT91C_MCI1_CFG            (0xF000C054)  // (MCI1) MCI Configuration Register
#define AT91C_MCI1_DTOR           (0xF000C008)  // (MCI1) MCI Data Timeout Register
#define AT91C_MCI1_FIFO           (0xF000C200)  // (MCI1) MCI FIFO Aperture Register
#define AT91C_MCI1_WPSR           (0xF000C0E8)  // (MCI1) MCI Write Protection Status Register
// ========== Register definition for TWI0 peripheral ========== 
#define AT91C_TWI0_FEATURES       (0xF80100F8)  // (TWI0) TWI FEATURES REGISTER
#define AT91C_TWI0_IDR            (0xF8010028)  // (TWI0) Interrupt Disable Register
#define AT91C_TWI0_IPNAME2        (0xF80100F4)  // (TWI0) TWI IPNAME2 REGISTER
#define AT91C_TWI0_MMR            (0xF8010004)  // (TWI0) Master Mode Register
#define AT91C_TWI0_RHR            (0xF8010030)  // (TWI0) Receive Holding Register
#define AT91C_TWI0_IPNAME1        (0xF80100F0)  // (TWI0) TWI IPNAME1 REGISTER
#define AT91C_TWI0_SR             (0xF8010020)  // (TWI0) Status Register
#define AT91C_TWI0_CR             (0xF8010000)  // (TWI0) Control Register
#define AT91C_TWI0_IADR           (0xF801000C)  // (TWI0) Internal Address Register
#define AT91C_TWI0_IER            (0xF8010024)  // (TWI0) Interrupt Enable Register
#define AT91C_TWI0_IMR            (0xF801002C)  // (TWI0) Interrupt Mask Register
#define AT91C_TWI0_SMR            (0xF8010008)  // (TWI0) Slave Mode Register
#define AT91C_TWI0_THR            (0xF8010034)  // (TWI0) Transmit Holding Register
#define AT91C_TWI0_VER            (0xF80100FC)  // (TWI0) Version Register
#define AT91C_TWI0_CWGR           (0xF8010010)  // (TWI0) Clock Waveform Generator Register
#define AT91C_TWI0_ADDRSIZE       (0xF80100EC)  // (TWI0) TWI ADDRSIZE REGISTER
// ========== Register definition for TWI1 peripheral ========== 
#define AT91C_TWI1_IPNAME2        (0xF80140F4)  // (TWI1) TWI IPNAME2 REGISTER
#define AT91C_TWI1_IER            (0xF8014024)  // (TWI1) Interrupt Enable Register
#define AT91C_TWI1_VER            (0xF80140FC)  // (TWI1) Version Register
#define AT91C_TWI1_IDR            (0xF8014028)  // (TWI1) Interrupt Disable Register
#define AT91C_TWI1_SMR            (0xF8014008)  // (TWI1) Slave Mode Register
#define AT91C_TWI1_CR             (0xF8014000)  // (TWI1) Control Register
#define AT91C_TWI1_FEATURES       (0xF80140F8)  // (TWI1) TWI FEATURES REGISTER
#define AT91C_TWI1_RHR            (0xF8014030)  // (TWI1) Receive Holding Register
#define AT91C_TWI1_IPNAME1        (0xF80140F0)  // (TWI1) TWI IPNAME1 REGISTER
#define AT91C_TWI1_THR            (0xF8014034)  // (TWI1) Transmit Holding Register
#define AT91C_TWI1_IADR           (0xF801400C)  // (TWI1) Internal Address Register
#define AT91C_TWI1_SR             (0xF8014020)  // (TWI1) Status Register
#define AT91C_TWI1_CWGR           (0xF8014010)  // (TWI1) Clock Waveform Generator Register
#define AT91C_TWI1_ADDRSIZE       (0xF80140EC)  // (TWI1) TWI ADDRSIZE REGISTER
#define AT91C_TWI1_IMR            (0xF801402C)  // (TWI1) Interrupt Mask Register
#define AT91C_TWI1_MMR            (0xF8014004)  // (TWI1) Master Mode Register
// ========== Register definition for TWI2 peripheral ========== 
#define AT91C_TWI2_THR            (0xF8018034)  // (TWI2) Transmit Holding Register
#define AT91C_TWI2_ADDRSIZE       (0xF80180EC)  // (TWI2) TWI ADDRSIZE REGISTER
#define AT91C_TWI2_SMR            (0xF8018008)  // (TWI2) Slave Mode Register
#define AT91C_TWI2_FEATURES       (0xF80180F8)  // (TWI2) TWI FEATURES REGISTER
#define AT91C_TWI2_IPNAME2        (0xF80180F4)  // (TWI2) TWI IPNAME2 REGISTER
#define AT91C_TWI2_SR             (0xF8018020)  // (TWI2) Status Register
#define AT91C_TWI2_IADR           (0xF801800C)  // (TWI2) Internal Address Register
#define AT91C_TWI2_MMR            (0xF8018004)  // (TWI2) Master Mode Register
#define AT91C_TWI2_VER            (0xF80180FC)  // (TWI2) Version Register
#define AT91C_TWI2_IPNAME1        (0xF80180F0)  // (TWI2) TWI IPNAME1 REGISTER
#define AT91C_TWI2_CWGR           (0xF8018010)  // (TWI2) Clock Waveform Generator Register
#define AT91C_TWI2_CR             (0xF8018000)  // (TWI2) Control Register
#define AT91C_TWI2_IMR            (0xF801802C)  // (TWI2) Interrupt Mask Register
#define AT91C_TWI2_IER            (0xF8018024)  // (TWI2) Interrupt Enable Register
#define AT91C_TWI2_RHR            (0xF8018030)  // (TWI2) Receive Holding Register
#define AT91C_TWI2_IDR            (0xF8018028)  // (TWI2) Interrupt Disable Register
// ========== Register definition for US0 peripheral ========== 
#define AT91C_US0_CSR             (0xF801C014)  // (US0) Channel Status Register
#define AT91C_US0_RHR             (0xF801C018)  // (US0) Receiver Holding Register
#define AT91C_US0_IER             (0xF801C008)  // (US0) Interrupt Enable Register
#define AT91C_US0_IPNAME2         (0xF801C0F4)  // (US0) US IPNAME2 REGISTER
#define AT91C_US0_BRGR            (0xF801C020)  // (US0) Baud Rate Generator Register
#define AT91C_US0_FEATURES        (0xF801C0F8)  // (US0) US FEATURES REGISTER
#define AT91C_US0_CR              (0xF801C000)  // (US0) Control Register
#define AT91C_US0_NER             (0xF801C044)  // (US0) Nb Errors Register
#define AT91C_US0_IPNAME1         (0xF801C0F0)  // (US0) US IPNAME1 REGISTER
#define AT91C_US0_IMR             (0xF801C010)  // (US0) Interrupt Mask Register
#define AT91C_US0_IF              (0xF801C04C)  // (US0) IRDA_FILTER Register
#define AT91C_US0_VER             (0xF801C0FC)  // (US0) VERSION Register
#define AT91C_US0_MR              (0xF801C004)  // (US0) Mode Register
#define AT91C_US0_IDR             (0xF801C00C)  // (US0) Interrupt Disable Register
#define AT91C_US0_FIDI            (0xF801C040)  // (US0) FI_DI_Ratio Register
#define AT91C_US0_RTOR            (0xF801C024)  // (US0) Receiver Time-out Register
#define AT91C_US0_THR             (0xF801C01C)  // (US0) Transmitter Holding Register
#define AT91C_US0_ADDRSIZE        (0xF801C0EC)  // (US0) US ADDRSIZE REGISTER
#define AT91C_US0_TTGR            (0xF801C028)  // (US0) Transmitter Time-guard Register
#define AT91C_US0_MAN             (0xF801C050)  // (US0) Manchester Encoder Decoder Register
// ========== Register definition for US1 peripheral ========== 
#define AT91C_US1_VER             (0xF80200FC)  // (US1) VERSION Register
#define AT91C_US1_ADDRSIZE        (0xF80200EC)  // (US1) US ADDRSIZE REGISTER
#define AT91C_US1_IMR             (0xF8020010)  // (US1) Interrupt Mask Register
#define AT91C_US1_IDR             (0xF802000C)  // (US1) Interrupt Disable Register
#define AT91C_US1_IPNAME2         (0xF80200F4)  // (US1) US IPNAME2 REGISTER
#define AT91C_US1_NER             (0xF8020044)  // (US1) Nb Errors Register
#define AT91C_US1_IER             (0xF8020008)  // (US1) Interrupt Enable Register
#define AT91C_US1_TTGR            (0xF8020028)  // (US1) Transmitter Time-guard Register
#define AT91C_US1_CR              (0xF8020000)  // (US1) Control Register
#define AT91C_US1_RHR             (0xF8020018)  // (US1) Receiver Holding Register
#define AT91C_US1_CSR             (0xF8020014)  // (US1) Channel Status Register
#define AT91C_US1_BRGR            (0xF8020020)  // (US1) Baud Rate Generator Register
#define AT91C_US1_MR              (0xF8020004)  // (US1) Mode Register
#define AT91C_US1_IF              (0xF802004C)  // (US1) IRDA_FILTER Register
#define AT91C_US1_RTOR            (0xF8020024)  // (US1) Receiver Time-out Register
#define AT91C_US1_FIDI            (0xF8020040)  // (US1) FI_DI_Ratio Register
#define AT91C_US1_IPNAME1         (0xF80200F0)  // (US1) US IPNAME1 REGISTER
#define AT91C_US1_FEATURES        (0xF80200F8)  // (US1) US FEATURES REGISTER
#define AT91C_US1_THR             (0xF802001C)  // (US1) Transmitter Holding Register
#define AT91C_US1_MAN             (0xF8020050)  // (US1) Manchester Encoder Decoder Register
// ========== Register definition for US2 peripheral ========== 
#define AT91C_US2_IF              (0xF802404C)  // (US2) IRDA_FILTER Register
#define AT91C_US2_IER             (0xF8024008)  // (US2) Interrupt Enable Register
#define AT91C_US2_MR              (0xF8024004)  // (US2) Mode Register
#define AT91C_US2_FIDI            (0xF8024040)  // (US2) FI_DI_Ratio Register
#define AT91C_US2_RTOR            (0xF8024024)  // (US2) Receiver Time-out Register
#define AT91C_US2_BRGR            (0xF8024020)  // (US2) Baud Rate Generator Register
#define AT91C_US2_NER             (0xF8024044)  // (US2) Nb Errors Register
#define AT91C_US2_CSR             (0xF8024014)  // (US2) Channel Status Register
#define AT91C_US2_IPNAME1         (0xF80240F0)  // (US2) US IPNAME1 REGISTER
#define AT91C_US2_CR              (0xF8024000)  // (US2) Control Register
#define AT91C_US2_IPNAME2         (0xF80240F4)  // (US2) US IPNAME2 REGISTER
#define AT91C_US2_IMR             (0xF8024010)  // (US2) Interrupt Mask Register
#define AT91C_US2_IDR             (0xF802400C)  // (US2) Interrupt Disable Register
#define AT91C_US2_TTGR            (0xF8024028)  // (US2) Transmitter Time-guard Register
#define AT91C_US2_THR             (0xF802401C)  // (US2) Transmitter Holding Register
#define AT91C_US2_VER             (0xF80240FC)  // (US2) VERSION Register
#define AT91C_US2_FEATURES        (0xF80240F8)  // (US2) US FEATURES REGISTER
#define AT91C_US2_RHR             (0xF8024018)  // (US2) Receiver Holding Register
#define AT91C_US2_MAN             (0xF8024050)  // (US2) Manchester Encoder Decoder Register
#define AT91C_US2_ADDRSIZE        (0xF80240EC)  // (US2) US ADDRSIZE REGISTER
// ========== Register definition for US3 peripheral ========== 
#define AT91C_US3_IPNAME1         (0xF80280F0)  // (US3) US IPNAME1 REGISTER
#define AT91C_US3_IF              (0xF802804C)  // (US3) IRDA_FILTER Register
#define AT91C_US3_IER             (0xF8028008)  // (US3) Interrupt Enable Register
#define AT91C_US3_IMR             (0xF8028010)  // (US3) Interrupt Mask Register
#define AT91C_US3_IDR             (0xF802800C)  // (US3) Interrupt Disable Register
#define AT91C_US3_FEATURES        (0xF80280F8)  // (US3) US FEATURES REGISTER
#define AT91C_US3_ADDRSIZE        (0xF80280EC)  // (US3) US ADDRSIZE REGISTER
#define AT91C_US3_RTOR            (0xF8028024)  // (US3) Receiver Time-out Register
#define AT91C_US3_THR             (0xF802801C)  // (US3) Transmitter Holding Register
#define AT91C_US3_CSR             (0xF8028014)  // (US3) Channel Status Register
#define AT91C_US3_MR              (0xF8028004)  // (US3) Mode Register
#define AT91C_US3_MAN             (0xF8028050)  // (US3) Manchester Encoder Decoder Register
#define AT91C_US3_CR              (0xF8028000)  // (US3) Control Register
#define AT91C_US3_FIDI            (0xF8028040)  // (US3) FI_DI_Ratio Register
#define AT91C_US3_IPNAME2         (0xF80280F4)  // (US3) US IPNAME2 REGISTER
#define AT91C_US3_TTGR            (0xF8028028)  // (US3) Transmitter Time-guard Register
#define AT91C_US3_VER             (0xF80280FC)  // (US3) VERSION Register
#define AT91C_US3_RHR             (0xF8028018)  // (US3) Receiver Holding Register
#define AT91C_US3_NER             (0xF8028044)  // (US3) Nb Errors Register
#define AT91C_US3_BRGR            (0xF8028020)  // (US3) Baud Rate Generator Register
// ========== Register definition for SSC peripheral ========== 
#define AT91C_SSC_RSHR            (0xF0010030)  // (SSC) Receive Sync Holding Register
#define AT91C_SSC_RHR             (0xF0010020)  // (SSC) Receive Holding Register
#define AT91C_SSC_IMR             (0xF001004C)  // (SSC) Interrupt Mask Register
#define AT91C_SSC_RFMR            (0xF0010014)  // (SSC) Receive Frame Mode Register
#define AT91C_SSC_ADDRSIZE        (0xF00100EC)  // (SSC) SSC ADDRSIZE REGISTER
#define AT91C_SSC_CMR             (0xF0010004)  // (SSC) Clock Mode Register
#define AT91C_SSC_RCMR            (0xF0010010)  // (SSC) Receive Clock ModeRegister
#define AT91C_SSC_IPNAME1         (0xF00100F0)  // (SSC) SSC IPNAME1 REGISTER
#define AT91C_SSC_TSHR            (0xF0010034)  // (SSC) Transmit Sync Holding Register
#define AT91C_SSC_TCMR            (0xF0010018)  // (SSC) Transmit Clock Mode Register
#define AT91C_SSC_VER             (0xF00100FC)  // (SSC) Version Register
#define AT91C_SSC_FEATURES        (0xF00100F8)  // (SSC) SSC FEATURES REGISTER
#define AT91C_SSC_IER             (0xF0010044)  // (SSC) Interrupt Enable Register
#define AT91C_SSC_CR              (0xF0010000)  // (SSC) Control Register
#define AT91C_SSC_TFMR            (0xF001001C)  // (SSC) Transmit Frame Mode Register
#define AT91C_SSC_SR              (0xF0010040)  // (SSC) Status Register
#define AT91C_SSC_IPNAME2         (0xF00100F4)  // (SSC) SSC IPNAME2 REGISTER
#define AT91C_SSC_THR             (0xF0010024)  // (SSC) Transmit Holding Register
#define AT91C_SSC_IDR             (0xF0010048)  // (SSC) Interrupt Disable Register
// ========== Register definition for PWMC_CH0 peripheral ========== 
#define AT91C_PWMC_CH0_Reserved   (0xF8034214)  // (PWMC_CH0) Reserved
#define AT91C_PWMC_CH0_CPRDR      (0xF8034208)  // (PWMC_CH0) Channel Period Register
#define AT91C_PWMC_CH0_CDTYR      (0xF8034204)  // (PWMC_CH0) Channel Duty Cycle Register
#define AT91C_PWMC_CH0_CCNTR      (0xF803420C)  // (PWMC_CH0) Channel Counter Register
#define AT91C_PWMC_CH0_CUPDR      (0xF8034210)  // (PWMC_CH0) Channel Update Register
#define AT91C_PWMC_CH0_CMR        (0xF8034200)  // (PWMC_CH0) Channel Mode Register
// ========== Register definition for PWMC_CH1 peripheral ========== 
#define AT91C_PWMC_CH1_CUPDR      (0xF8034230)  // (PWMC_CH1) Channel Update Register
#define AT91C_PWMC_CH1_CPRDR      (0xF8034228)  // (PWMC_CH1) Channel Period Register
#define AT91C_PWMC_CH1_CDTYR      (0xF8034224)  // (PWMC_CH1) Channel Duty Cycle Register
#define AT91C_PWMC_CH1_Reserved   (0xF8034234)  // (PWMC_CH1) Reserved
#define AT91C_PWMC_CH1_CMR        (0xF8034220)  // (PWMC_CH1) Channel Mode Register
#define AT91C_PWMC_CH1_CCNTR      (0xF803422C)  // (PWMC_CH1) Channel Counter Register
// ========== Register definition for PWMC_CH2 peripheral ========== 
#define AT91C_PWMC_CH2_CPRDR      (0xF8034248)  // (PWMC_CH2) Channel Period Register
#define AT91C_PWMC_CH2_Reserved   (0xF8034254)  // (PWMC_CH2) Reserved
#define AT91C_PWMC_CH2_CCNTR      (0xF803424C)  // (PWMC_CH2) Channel Counter Register
#define AT91C_PWMC_CH2_CUPDR      (0xF8034250)  // (PWMC_CH2) Channel Update Register
#define AT91C_PWMC_CH2_CDTYR      (0xF8034244)  // (PWMC_CH2) Channel Duty Cycle Register
#define AT91C_PWMC_CH2_CMR        (0xF8034240)  // (PWMC_CH2) Channel Mode Register
// ========== Register definition for PWMC_CH3 peripheral ========== 
#define AT91C_PWMC_CH3_Reserved   (0xF8034274)  // (PWMC_CH3) Reserved
#define AT91C_PWMC_CH3_CCNTR      (0xF803426C)  // (PWMC_CH3) Channel Counter Register
#define AT91C_PWMC_CH3_CUPDR      (0xF8034270)  // (PWMC_CH3) Channel Update Register
#define AT91C_PWMC_CH3_CDTYR      (0xF8034264)  // (PWMC_CH3) Channel Duty Cycle Register
#define AT91C_PWMC_CH3_CPRDR      (0xF8034268)  // (PWMC_CH3) Channel Period Register
#define AT91C_PWMC_CH3_CMR        (0xF8034260)  // (PWMC_CH3) Channel Mode Register
// ========== Register definition for PWMC peripheral ========== 
#define AT91C_PWMC_IER            (0xF8034010)  // (PWMC) PWMC Interrupt Enable Register
#define AT91C_PWMC_ENA            (0xF8034004)  // (PWMC) PWMC Enable Register
#define AT91C_PWMC_VR             (0xF80340FC)  // (PWMC) PWMC Version Register
#define AT91C_PWMC_MR             (0xF8034000)  // (PWMC) PWMC Mode Register
#define AT91C_PWMC_SR             (0xF803400C)  // (PWMC) PWMC Status Register
#define AT91C_PWMC_DIS            (0xF8034008)  // (PWMC) PWMC Disable Register
#define AT91C_PWMC_ISR            (0xF803401C)  // (PWMC) PWMC Interrupt Status Register
#define AT91C_PWMC_IMR            (0xF8034018)  // (PWMC) PWMC Interrupt Mask Register
#define AT91C_PWMC_IDR            (0xF8034014)  // (PWMC) PWMC Interrupt Disable Register
// ========== Register definition for SPI0 peripheral ========== 
#define AT91C_SPI0_IPNAME2        (0xF00000F4)  // (SPI0) SPI IPNAME2 REGISTER
#define AT91C_SPI0_IER            (0xF0000014)  // (SPI0) Interrupt Enable Register
#define AT91C_SPI0_IDR            (0xF0000018)  // (SPI0) Interrupt Disable Register
#define AT91C_SPI0_RDR            (0xF0000008)  // (SPI0) Receive Data Register
#define AT91C_SPI0_CR             (0xF0000000)  // (SPI0) Control Register
#define AT91C_SPI0_CSR            (0xF0000030)  // (SPI0) Chip Select Register
#define AT91C_SPI0_IMR            (0xF000001C)  // (SPI0) Interrupt Mask Register
#define AT91C_SPI0_VER            (0xF00000FC)  // (SPI0) Version Register
#define AT91C_SPI0_SR             (0xF0000010)  // (SPI0) Status Register
#define AT91C_SPI0_IPNAME1        (0xF00000F0)  // (SPI0) SPI IPNAME1 REGISTER
#define AT91C_SPI0_ADDRSIZE       (0xF00000EC)  // (SPI0) SPI ADDRSIZE REGISTER
#define AT91C_SPI0_TDR            (0xF000000C)  // (SPI0) Transmit Data Register
#define AT91C_SPI0_MR             (0xF0000004)  // (SPI0) Mode Register
#define AT91C_SPI0_FEATURES       (0xF00000F8)  // (SPI0) SPI FEATURES REGISTER
// ========== Register definition for SPI1 peripheral ========== 
#define AT91C_SPI1_ADDRSIZE       (0xF00040EC)  // (SPI1) SPI ADDRSIZE REGISTER
#define AT91C_SPI1_VER            (0xF00040FC)  // (SPI1) Version Register
#define AT91C_SPI1_IPNAME1        (0xF00040F0)  // (SPI1) SPI IPNAME1 REGISTER
#define AT91C_SPI1_FEATURES       (0xF00040F8)  // (SPI1) SPI FEATURES REGISTER
#define AT91C_SPI1_IER            (0xF0004014)  // (SPI1) Interrupt Enable Register
#define AT91C_SPI1_IMR            (0xF000401C)  // (SPI1) Interrupt Mask Register
#define AT91C_SPI1_CR             (0xF0004000)  // (SPI1) Control Register
#define AT91C_SPI1_IDR            (0xF0004018)  // (SPI1) Interrupt Disable Register
#define AT91C_SPI1_CSR            (0xF0004030)  // (SPI1) Chip Select Register
#define AT91C_SPI1_RDR            (0xF0004008)  // (SPI1) Receive Data Register
#define AT91C_SPI1_TDR            (0xF000400C)  // (SPI1) Transmit Data Register
#define AT91C_SPI1_SR             (0xF0004010)  // (SPI1) Status Register
#define AT91C_SPI1_MR             (0xF0004004)  // (SPI1) Mode Register
#define AT91C_SPI1_IPNAME2        (0xF00040F4)  // (SPI1) SPI IPNAME2 REGISTER
// ========== Register definition for TSADC peripheral ========== 
#define AT91C_TSADC_TSMR          (0xF804C0B0)  // (TSADC) ADC Touch Screen Mode Register
#define AT91C_TSADC_EMR           (0xF804C040)  // (TSADC) ADC Extended Mode Register
#define AT91C_TSADC_COR           (0xF804C04C)  // (TSADC) ADC Channel Offset Register
#define AT91C_TSADC_IER           (0xF804C024)  // (TSADC) ADC Interrupt Enable Register
#define AT91C_TSADC_SEQ2R         (0xF804C00C)  // (TSADC) Channel Sequence 2 Register
#define AT91C_TSADC_CDR4          (0xF804C060)  // (TSADC) ADC Channel Data Register 4
#define AT91C_TSADC_CDR1          (0xF804C054)  // (TSADC) ADC Channel Data Register 1
#define AT91C_TSADC_CR            (0xF804C000)  // (TSADC) ADC Control Register
#define AT91C_TSADC_LCDR          (0xF804C020)  // (TSADC) ADC Last Converted Data Register
#define AT91C_TSADC_CDR10         (0xF804C078)  // (TSADC) ADC Channel Data Register 10
#define AT91C_TSADC_PRESSR        (0xF804C0BC)  // (TSADC) ADC Touch Screen Pressure Register
#define AT91C_TSADC_CDR8          (0xF804C070)  // (TSADC) ADC Channel Data Register 8
#define AT91C_TSADC_CHSR          (0xF804C018)  // (TSADC) ADC Channel Status Register
#define AT91C_TSADC_ISR           (0xF804C030)  // (TSADC) ADC Interrupt Status Register
#define AT91C_TSADC_CDR0          (0xF804C050)  // (TSADC) ADC Channel Data Register 0
#define AT91C_TSADC_CDR9          (0xF804C074)  // (TSADC) ADC Channel Data Register 9
#define AT91C_TSADC_CHDR          (0xF804C014)  // (TSADC) ADC Channel Disable Register
#define AT91C_TSADC_OVER          (0xF804C03C)  // (TSADC) ADC Overrun Status Register
#define AT91C_TSADC_CDR11         (0xF804C07C)  // (TSADC) ADC Channel Data Register 11
#define AT91C_TSADC_TRGR          (0xF804C0C0)  // (TSADC) ADC Trigger Register
#define AT91C_TSADC_CDR2          (0xF804C058)  // (TSADC) ADC Channel Data Register 2
#define AT91C_TSADC_XPOSR         (0xF804C0B4)  // (TSADC) ADC Touch Screen X Posistion Register
#define AT91C_TSADC_CDR7          (0xF804C06C)  // (TSADC) ADC Channel Data Register 7
#define AT91C_TSADC_IDR           (0xF804C028)  // (TSADC) ADC Interrupt Disable Register
#define AT91C_TSADC_CDR3          (0xF804C05C)  // (TSADC) ADC Channel Data Register 3
#define AT91C_TSADC_IMR           (0xF804C02C)  // (TSADC) ADC Interrupt Mask Register
#define AT91C_TSADC_CHER          (0xF804C010)  // (TSADC) ADC Channel Enable Register
#define AT91C_TSADC_CDR5          (0xF804C064)  // (TSADC) ADC Channel Data Register 5
#define AT91C_TSADC_CWR           (0xF804C044)  // (TSADC) ADC Compare Window Register
#define AT91C_TSADC_CGR           (0xF804C048)  // (TSADC) ADC Channel Gain Register
#define AT91C_TSADC_VER           (0xF804C0FC)  // (TSADC) ADC VERSION REGISTER
#define AT91C_TSADC_MR            (0xF804C004)  // (TSADC) ADC Mode Register
#define AT91C_TSADC_CDR6          (0xF804C068)  // (TSADC) ADC Channel Data Register 6
#define AT91C_TSADC_SEQ1R         (0xF804C008)  // (TSADC) Channel Sequence 1 Register
#define AT91C_TSADC_YPOSR         (0xF804C0B8)  // (TSADC) ADC Touch Screen Y Posistion Register
// ========== Register definition for UART0 peripheral ========== 
#define AT91C_UART0_VER           (0xF80400FC)  // (UART0) DBGU VERSION REGISTER
#define AT91C_UART0_CR            (0xF8040000)  // (UART0) Control Register
#define AT91C_UART0_CIDR          (0xF8040040)  // (UART0) Chip ID Register
#define AT91C_UART0_ADDRSIZE      (0xF80400EC)  // (UART0) DBGU ADDRSIZE REGISTER
#define AT91C_UART0_IPNAME2       (0xF80400F4)  // (UART0) DBGU IPNAME2 REGISTER
#define AT91C_UART0_IMR           (0xF8040010)  // (UART0) Interrupt Mask Register
#define AT91C_UART0_FNTR          (0xF8040048)  // (UART0) Force NTRST Register
#define AT91C_UART0_THR           (0xF804001C)  // (UART0) Transmitter Holding Register
#define AT91C_UART0_FEATURES      (0xF80400F8)  // (UART0) DBGU FEATURES REGISTER
#define AT91C_UART0_IER           (0xF8040008)  // (UART0) Interrupt Enable Register
#define AT91C_UART0_MR            (0xF8040004)  // (UART0) Mode Register
#define AT91C_UART0_IPNAME1       (0xF80400F0)  // (UART0) DBGU IPNAME1 REGISTER
#define AT91C_UART0_CSR           (0xF8040014)  // (UART0) Channel Status Register
#define AT91C_UART0_RHR           (0xF8040018)  // (UART0) Receiver Holding Register
#define AT91C_UART0_IDR           (0xF804000C)  // (UART0) Interrupt Disable Register
#define AT91C_UART0_BRGR          (0xF8040020)  // (UART0) Baud Rate Generator Register
#define AT91C_UART0_EXID          (0xF8040044)  // (UART0) Chip ID Extension Register
// ========== Register definition for UART1 peripheral ========== 
#define AT91C_UART1_RHR           (0xF8044018)  // (UART1) Receiver Holding Register
#define AT91C_UART1_FEATURES      (0xF80440F8)  // (UART1) DBGU FEATURES REGISTER
#define AT91C_UART1_EXID          (0xF8044044)  // (UART1) Chip ID Extension Register
#define AT91C_UART1_CSR           (0xF8044014)  // (UART1) Channel Status Register
#define AT91C_UART1_IER           (0xF8044008)  // (UART1) Interrupt Enable Register
#define AT91C_UART1_VER           (0xF80440FC)  // (UART1) DBGU VERSION REGISTER
#define AT91C_UART1_MR            (0xF8044004)  // (UART1) Mode Register
#define AT91C_UART1_THR           (0xF804401C)  // (UART1) Transmitter Holding Register
#define AT91C_UART1_IMR           (0xF8044010)  // (UART1) Interrupt Mask Register
#define AT91C_UART1_CIDR          (0xF8044040)  // (UART1) Chip ID Register
#define AT91C_UART1_ADDRSIZE      (0xF80440EC)  // (UART1) DBGU ADDRSIZE REGISTER
#define AT91C_UART1_IDR           (0xF804400C)  // (UART1) Interrupt Disable Register
#define AT91C_UART1_IPNAME2       (0xF80440F4)  // (UART1) DBGU IPNAME2 REGISTER
#define AT91C_UART1_IPNAME1       (0xF80440F0)  // (UART1) DBGU IPNAME1 REGISTER
#define AT91C_UART1_FNTR          (0xF8044048)  // (UART1) Force NTRST Register
#define AT91C_UART1_BRGR          (0xF8044020)  // (UART1) Baud Rate Generator Register
#define AT91C_UART1_CR            (0xF8044000)  // (UART1) Control Register
// ========== Register definition for CAN0_MB0 peripheral ========== 
#define AT91C_CAN0_MB0_MFID       (0xF800020C)  // (CAN0_MB0) MailBox Family ID Register
#define AT91C_CAN0_MB0_MMR        (0xF8000200)  // (CAN0_MB0) MailBox Mode Register
#define AT91C_CAN0_MB0_MCR        (0xF800021C)  // (CAN0_MB0) MailBox Control Register
#define AT91C_CAN0_MB0_MSR        (0xF8000210)  // (CAN0_MB0) MailBox Status Register
#define AT91C_CAN0_MB0_MAM        (0xF8000204)  // (CAN0_MB0) MailBox Acceptance Mask Register
#define AT91C_CAN0_MB0_MID        (0xF8000208)  // (CAN0_MB0) MailBox ID Register
#define AT91C_CAN0_MB0_MDL        (0xF8000214)  // (CAN0_MB0) MailBox Data Low Register
#define AT91C_CAN0_MB0_MDH        (0xF8000218)  // (CAN0_MB0) MailBox Data High Register
// ========== Register definition for CAN0_MB1 peripheral ========== 
#define AT91C_CAN0_MB1_MDL        (0xF8000234)  // (CAN0_MB1) MailBox Data Low Register
#define AT91C_CAN0_MB1_MDH        (0xF8000238)  // (CAN0_MB1) MailBox Data High Register
#define AT91C_CAN0_MB1_MFID       (0xF800022C)  // (CAN0_MB1) MailBox Family ID Register
#define AT91C_CAN0_MB1_MAM        (0xF8000224)  // (CAN0_MB1) MailBox Acceptance Mask Register
#define AT91C_CAN0_MB1_MID        (0xF8000228)  // (CAN0_MB1) MailBox ID Register
#define AT91C_CAN0_MB1_MCR        (0xF800023C)  // (CAN0_MB1) MailBox Control Register
#define AT91C_CAN0_MB1_MMR        (0xF8000220)  // (CAN0_MB1) MailBox Mode Register
#define AT91C_CAN0_MB1_MSR        (0xF8000230)  // (CAN0_MB1) MailBox Status Register
// ========== Register definition for CAN0_MB2 peripheral ========== 
#define AT91C_CAN0_MB2_MDH        (0xF8000258)  // (CAN0_MB2) MailBox Data High Register
#define AT91C_CAN0_MB2_MID        (0xF8000248)  // (CAN0_MB2) MailBox ID Register
#define AT91C_CAN0_MB2_MCR        (0xF800025C)  // (CAN0_MB2) MailBox Control Register
#define AT91C_CAN0_MB2_MDL        (0xF8000254)  // (CAN0_MB2) MailBox Data Low Register
#define AT91C_CAN0_MB2_MSR        (0xF8000250)  // (CAN0_MB2) MailBox Status Register
#define AT91C_CAN0_MB2_MMR        (0xF8000240)  // (CAN0_MB2) MailBox Mode Register
#define AT91C_CAN0_MB2_MFID       (0xF800024C)  // (CAN0_MB2) MailBox Family ID Register
#define AT91C_CAN0_MB2_MAM        (0xF8000244)  // (CAN0_MB2) MailBox Acceptance Mask Register
// ========== Register definition for CAN0_MB3 peripheral ========== 
#define AT91C_CAN0_MB3_MAM        (0xF8000264)  // (CAN0_MB3) MailBox Acceptance Mask Register
#define AT91C_CAN0_MB3_MCR        (0xF800027C)  // (CAN0_MB3) MailBox Control Register
#define AT91C_CAN0_MB3_MDH        (0xF8000278)  // (CAN0_MB3) MailBox Data High Register
#define AT91C_CAN0_MB3_MDL        (0xF8000274)  // (CAN0_MB3) MailBox Data Low Register
#define AT91C_CAN0_MB3_MFID       (0xF800026C)  // (CAN0_MB3) MailBox Family ID Register
#define AT91C_CAN0_MB3_MSR        (0xF8000270)  // (CAN0_MB3) MailBox Status Register
#define AT91C_CAN0_MB3_MID        (0xF8000268)  // (CAN0_MB3) MailBox ID Register
#define AT91C_CAN0_MB3_MMR        (0xF8000260)  // (CAN0_MB3) MailBox Mode Register
// ========== Register definition for CAN0_MB4 peripheral ========== 
#define AT91C_CAN0_MB4_MDH        (0xF8000298)  // (CAN0_MB4) MailBox Data High Register
#define AT91C_CAN0_MB4_MMR        (0xF8000280)  // (CAN0_MB4) MailBox Mode Register
#define AT91C_CAN0_MB4_MFID       (0xF800028C)  // (CAN0_MB4) MailBox Family ID Register
#define AT91C_CAN0_MB4_MSR        (0xF8000290)  // (CAN0_MB4) MailBox Status Register
#define AT91C_CAN0_MB4_MID        (0xF8000288)  // (CAN0_MB4) MailBox ID Register
#define AT91C_CAN0_MB4_MDL        (0xF8000294)  // (CAN0_MB4) MailBox Data Low Register
#define AT91C_CAN0_MB4_MAM        (0xF8000284)  // (CAN0_MB4) MailBox Acceptance Mask Register
#define AT91C_CAN0_MB4_MCR        (0xF800029C)  // (CAN0_MB4) MailBox Control Register
// ========== Register definition for CAN0_MB5 peripheral ========== 
#define AT91C_CAN0_MB5_MDH        (0xF80002B8)  // (CAN0_MB5) MailBox Data High Register
#define AT91C_CAN0_MB5_MMR        (0xF80002A0)  // (CAN0_MB5) MailBox Mode Register
#define AT91C_CAN0_MB5_MID        (0xF80002A8)  // (CAN0_MB5) MailBox ID Register
#define AT91C_CAN0_MB5_MCR        (0xF80002BC)  // (CAN0_MB5) MailBox Control Register
#define AT91C_CAN0_MB5_MAM        (0xF80002A4)  // (CAN0_MB5) MailBox Acceptance Mask Register
#define AT91C_CAN0_MB5_MDL        (0xF80002B4)  // (CAN0_MB5) MailBox Data Low Register
#define AT91C_CAN0_MB5_MSR        (0xF80002B0)  // (CAN0_MB5) MailBox Status Register
#define AT91C_CAN0_MB5_MFID       (0xF80002AC)  // (CAN0_MB5) MailBox Family ID Register
// ========== Register definition for CAN0_MB6 peripheral ========== 
#define AT91C_CAN0_MB6_MFID       (0xF80002CC)  // (CAN0_MB6) MailBox Family ID Register
#define AT91C_CAN0_MB6_MAM        (0xF80002C4)  // (CAN0_MB6) MailBox Acceptance Mask Register
#define AT91C_CAN0_MB6_MSR        (0xF80002D0)  // (CAN0_MB6) MailBox Status Register
#define AT91C_CAN0_MB6_MDL        (0xF80002D4)  // (CAN0_MB6) MailBox Data Low Register
#define AT91C_CAN0_MB6_MID        (0xF80002C8)  // (CAN0_MB6) MailBox ID Register
#define AT91C_CAN0_MB6_MMR        (0xF80002C0)  // (CAN0_MB6) MailBox Mode Register
#define AT91C_CAN0_MB6_MCR        (0xF80002DC)  // (CAN0_MB6) MailBox Control Register
#define AT91C_CAN0_MB6_MDH        (0xF80002D8)  // (CAN0_MB6) MailBox Data High Register
// ========== Register definition for CAN0_MB7 peripheral ========== 
#define AT91C_CAN0_MB7_MMR        (0xF80002E0)  // (CAN0_MB7) MailBox Mode Register
#define AT91C_CAN0_MB7_MFID       (0xF80002EC)  // (CAN0_MB7) MailBox Family ID Register
#define AT91C_CAN0_MB7_MDL        (0xF80002F4)  // (CAN0_MB7) MailBox Data Low Register
#define AT91C_CAN0_MB7_MID        (0xF80002E8)  // (CAN0_MB7) MailBox ID Register
#define AT91C_CAN0_MB7_MCR        (0xF80002FC)  // (CAN0_MB7) MailBox Control Register
#define AT91C_CAN0_MB7_MAM        (0xF80002E4)  // (CAN0_MB7) MailBox Acceptance Mask Register
#define AT91C_CAN0_MB7_MSR        (0xF80002F0)  // (CAN0_MB7) MailBox Status Register
#define AT91C_CAN0_MB7_MDH        (0xF80002F8)  // (CAN0_MB7) MailBox Data High Register
// ========== Register definition for CAN0 peripheral ========== 
#define AT91C_CAN0_VR             (0xF80000FC)  // (CAN0) Version Register
#define AT91C_CAN0_IER            (0xF8000004)  // (CAN0) Interrupt Enable Register
#define AT91C_CAN0_IMR            (0xF800000C)  // (CAN0) Interrupt Mask Register
#define AT91C_CAN0_TCR            (0xF8000024)  // (CAN0) Transfer Command Register
#define AT91C_CAN0_SR             (0xF8000010)  // (CAN0) Status Register
#define AT91C_CAN0_TIM            (0xF8000018)  // (CAN0) Timer Register
#define AT91C_CAN0_IDR            (0xF8000008)  // (CAN0) Interrupt Disable Register
#define AT91C_CAN0_BR             (0xF8000014)  // (CAN0) Baudrate Register
#define AT91C_CAN0_ACR            (0xF8000028)  // (CAN0) Abort Command Register
#define AT91C_CAN0_MR             (0xF8000000)  // (CAN0) Mode Register
#define AT91C_CAN0_ECR            (0xF8000020)  // (CAN0) Error Counter Register
#define AT91C_CAN0_TIMESTP        (0xF800001C)  // (CAN0) Time Stamp Register
// ========== Register definition for CAN1_MB0 peripheral ========== 
#define AT91C_CAN1_MB0_MSR        (0xF8004210)  // (CAN1_MB0) MailBox Status Register
#define AT91C_CAN1_MB0_MMR        (0xF8004200)  // (CAN1_MB0) MailBox Mode Register
#define AT91C_CAN1_MB0_MCR        (0xF800421C)  // (CAN1_MB0) MailBox Control Register
#define AT91C_CAN1_MB0_MAM        (0xF8004204)  // (CAN1_MB0) MailBox Acceptance Mask Register
#define AT91C_CAN1_MB0_MDH        (0xF8004218)  // (CAN1_MB0) MailBox Data High Register
#define AT91C_CAN1_MB0_MID        (0xF8004208)  // (CAN1_MB0) MailBox ID Register
#define AT91C_CAN1_MB0_MDL        (0xF8004214)  // (CAN1_MB0) MailBox Data Low Register
#define AT91C_CAN1_MB0_MFID       (0xF800420C)  // (CAN1_MB0) MailBox Family ID Register
// ========== Register definition for CAN1_MB1 peripheral ========== 
#define AT91C_CAN1_MB1_MFID       (0xF800422C)  // (CAN1_MB1) MailBox Family ID Register
#define AT91C_CAN1_MB1_MID        (0xF8004228)  // (CAN1_MB1) MailBox ID Register
#define AT91C_CAN1_MB1_MDH        (0xF8004238)  // (CAN1_MB1) MailBox Data High Register
#define AT91C_CAN1_MB1_MAM        (0xF8004224)  // (CAN1_MB1) MailBox Acceptance Mask Register
#define AT91C_CAN1_MB1_MDL        (0xF8004234)  // (CAN1_MB1) MailBox Data Low Register
#define AT91C_CAN1_MB1_MCR        (0xF800423C)  // (CAN1_MB1) MailBox Control Register
#define AT91C_CAN1_MB1_MMR        (0xF8004220)  // (CAN1_MB1) MailBox Mode Register
#define AT91C_CAN1_MB1_MSR        (0xF8004230)  // (CAN1_MB1) MailBox Status Register
// ========== Register definition for CAN1_MB2 peripheral ========== 
#define AT91C_CAN1_MB2_MDL        (0xF8004254)  // (CAN1_MB2) MailBox Data Low Register
#define AT91C_CAN1_MB2_MAM        (0xF8004244)  // (CAN1_MB2) MailBox Acceptance Mask Register
#define AT91C_CAN1_MB2_MCR        (0xF800425C)  // (CAN1_MB2) MailBox Control Register
#define AT91C_CAN1_MB2_MFID       (0xF800424C)  // (CAN1_MB2) MailBox Family ID Register
#define AT91C_CAN1_MB2_MSR        (0xF8004250)  // (CAN1_MB2) MailBox Status Register
#define AT91C_CAN1_MB2_MDH        (0xF8004258)  // (CAN1_MB2) MailBox Data High Register
#define AT91C_CAN1_MB2_MID        (0xF8004248)  // (CAN1_MB2) MailBox ID Register
#define AT91C_CAN1_MB2_MMR        (0xF8004240)  // (CAN1_MB2) MailBox Mode Register
// ========== Register definition for CAN1_MB3 peripheral ========== 
#define AT91C_CAN1_MB3_MDL        (0xF8004274)  // (CAN1_MB3) MailBox Data Low Register
#define AT91C_CAN1_MB3_MDH        (0xF8004278)  // (CAN1_MB3) MailBox Data High Register
#define AT91C_CAN1_MB3_MMR        (0xF8004260)  // (CAN1_MB3) MailBox Mode Register
#define AT91C_CAN1_MB3_MID        (0xF8004268)  // (CAN1_MB3) MailBox ID Register
#define AT91C_CAN1_MB3_MCR        (0xF800427C)  // (CAN1_MB3) MailBox Control Register
#define AT91C_CAN1_MB3_MFID       (0xF800426C)  // (CAN1_MB3) MailBox Family ID Register
#define AT91C_CAN1_MB3_MAM        (0xF8004264)  // (CAN1_MB3) MailBox Acceptance Mask Register
#define AT91C_CAN1_MB3_MSR        (0xF8004270)  // (CAN1_MB3) MailBox Status Register
// ========== Register definition for CAN1_MB4 peripheral ========== 
#define AT91C_CAN1_MB4_MMR        (0xF8004280)  // (CAN1_MB4) MailBox Mode Register
#define AT91C_CAN1_MB4_MDH        (0xF8004298)  // (CAN1_MB4) MailBox Data High Register
#define AT91C_CAN1_MB4_MFID       (0xF800428C)  // (CAN1_MB4) MailBox Family ID Register
#define AT91C_CAN1_MB4_MAM        (0xF8004284)  // (CAN1_MB4) MailBox Acceptance Mask Register
#define AT91C_CAN1_MB4_MCR        (0xF800429C)  // (CAN1_MB4) MailBox Control Register
#define AT91C_CAN1_MB4_MSR        (0xF8004290)  // (CAN1_MB4) MailBox Status Register
#define AT91C_CAN1_MB4_MDL        (0xF8004294)  // (CAN1_MB4) MailBox Data Low Register
#define AT91C_CAN1_MB4_MID        (0xF8004288)  // (CAN1_MB4) MailBox ID Register
// ========== Register definition for CAN1_MB5 peripheral ========== 
#define AT91C_CAN1_MB5_MDH        (0xF80042B8)  // (CAN1_MB5) MailBox Data High Register
#define AT91C_CAN1_MB5_MID        (0xF80042A8)  // (CAN1_MB5) MailBox ID Register
#define AT91C_CAN1_MB5_MFID       (0xF80042AC)  // (CAN1_MB5) MailBox Family ID Register
#define AT91C_CAN1_MB5_MMR        (0xF80042A0)  // (CAN1_MB5) MailBox Mode Register
#define AT91C_CAN1_MB5_MCR        (0xF80042BC)  // (CAN1_MB5) MailBox Control Register
#define AT91C_CAN1_MB5_MAM        (0xF80042A4)  // (CAN1_MB5) MailBox Acceptance Mask Register
#define AT91C_CAN1_MB5_MDL        (0xF80042B4)  // (CAN1_MB5) MailBox Data Low Register
#define AT91C_CAN1_MB5_MSR        (0xF80042B0)  // (CAN1_MB5) MailBox Status Register
// ========== Register definition for CAN1_MB6 peripheral ========== 
#define AT91C_CAN1_MB6_MCR        (0xF80042DC)  // (CAN1_MB6) MailBox Control Register
#define AT91C_CAN1_MB6_MMR        (0xF80042C0)  // (CAN1_MB6) MailBox Mode Register
#define AT91C_CAN1_MB6_MSR        (0xF80042D0)  // (CAN1_MB6) MailBox Status Register
#define AT91C_CAN1_MB6_MID        (0xF80042C8)  // (CAN1_MB6) MailBox ID Register
#define AT91C_CAN1_MB6_MAM        (0xF80042C4)  // (CAN1_MB6) MailBox Acceptance Mask Register
#define AT91C_CAN1_MB6_MDL        (0xF80042D4)  // (CAN1_MB6) MailBox Data Low Register
#define AT91C_CAN1_MB6_MDH        (0xF80042D8)  // (CAN1_MB6) MailBox Data High Register
#define AT91C_CAN1_MB6_MFID       (0xF80042CC)  // (CAN1_MB6) MailBox Family ID Register
// ========== Register definition for CAN1_MB7 peripheral ========== 
#define AT91C_CAN1_MB7_MID        (0xF80042E8)  // (CAN1_MB7) MailBox ID Register
#define AT91C_CAN1_MB7_MDL        (0xF80042F4)  // (CAN1_MB7) MailBox Data Low Register
#define AT91C_CAN1_MB7_MFID       (0xF80042EC)  // (CAN1_MB7) MailBox Family ID Register
#define AT91C_CAN1_MB7_MAM        (0xF80042E4)  // (CAN1_MB7) MailBox Acceptance Mask Register
#define AT91C_CAN1_MB7_MCR        (0xF80042FC)  // (CAN1_MB7) MailBox Control Register
#define AT91C_CAN1_MB7_MMR        (0xF80042E0)  // (CAN1_MB7) MailBox Mode Register
#define AT91C_CAN1_MB7_MDH        (0xF80042F8)  // (CAN1_MB7) MailBox Data High Register
#define AT91C_CAN1_MB7_MSR        (0xF80042F0)  // (CAN1_MB7) MailBox Status Register
// ========== Register definition for CAN1 peripheral ========== 
#define AT91C_CAN1_TIM            (0xF8004018)  // (CAN1) Timer Register
#define AT91C_CAN1_ECR            (0xF8004020)  // (CAN1) Error Counter Register
#define AT91C_CAN1_VR             (0xF80040FC)  // (CAN1) Version Register
#define AT91C_CAN1_IMR            (0xF800400C)  // (CAN1) Interrupt Mask Register
#define AT91C_CAN1_TCR            (0xF8004024)  // (CAN1) Transfer Command Register
#define AT91C_CAN1_IDR            (0xF8004008)  // (CAN1) Interrupt Disable Register
#define AT91C_CAN1_MR             (0xF8004000)  // (CAN1) Mode Register
#define AT91C_CAN1_TIMESTP        (0xF800401C)  // (CAN1) Time Stamp Register
#define AT91C_CAN1_SR             (0xF8004010)  // (CAN1) Status Register
#define AT91C_CAN1_BR             (0xF8004014)  // (CAN1) Baudrate Register
#define AT91C_CAN1_ACR            (0xF8004028)  // (CAN1) Abort Command Register
#define AT91C_CAN1_IER            (0xF8004004)  // (CAN1) Interrupt Enable Register
// ========== Register definition for HSSD peripheral ========== 
#define AT91C_HSSD_DATA2H         (0x00400034)  // (HSSD)
#define AT91C_HSSD_AUX            (0x00400018)  // (HSSD)
#define AT91C_HSSD_DATA2L         (0x00400030)  // (HSSD)
#define AT91C_HSSD_CTRL1H         (0x0040002C)  // (HSSD)
#define AT91C_HSSD_WRAP           (0x00400008)  // (HSSD)
#define AT91C_HSSD_REV            (0x00400004)  // (HSSD)
#define AT91C_HSSD_FIFOCTRL       (0x00400040)  // (HSSD)
#define AT91C_HSSD_ADJ            (0x00400010)  // (HSSD)
#define AT91C_HSSD_ENB            (0x00400048)  // (HSSD)
#define AT91C_HSSD_LVL            (0x00400044)  // (HSSD)
#define AT91C_HSSD_DATA1H         (0x00400024)  // (HSSD)
#define AT91C_HSSD_POPR           (0x00400000)  // (HSSD)
#define AT91C_HSSD_PULSE          (0x0040001C)  // (HSSD)
#define AT91C_HSSD_CTRL1L         (0x00400028)  // (HSSD)
#define AT91C_HSSD_TRIM           (0x0040003C)  // (HSSD)
#define AT91C_HSSD_SAMCO          (0x00400014)  // (HSSD)
#define AT91C_HSSD_DRIVE          (0x0040000C)  // (HSSD)
// ========== Register definition for UDPHS_EPTFIFO peripheral ========== 
#define AT91C_UDPHS_EPTFIFO_READEPT6 (0x00560000)       // (UDPHS_EPTFIFO) FIFO Endpoint Data Register 6
#define AT91C_UDPHS_EPTFIFO_READEPT5 (0x00550000)       // (UDPHS_EPTFIFO) FIFO Endpoint Data Register 5
#define AT91C_UDPHS_EPTFIFO_READEPT3 (0x00530000)       // (UDPHS_EPTFIFO) FIFO Endpoint Data Register 3
#define AT91C_UDPHS_EPTFIFO_READEPT1 (0x00510000)       // (UDPHS_EPTFIFO) FIFO Endpoint Data Register 1
#define AT91C_UDPHS_EPTFIFO_READEPT2 (0x00520000)       // (UDPHS_EPTFIFO) FIFO Endpoint Data Register 2
#define AT91C_UDPHS_EPTFIFO_READEPT0 (0x00500000)       // (UDPHS_EPTFIFO) FIFO Endpoint Data Register 0
#define AT91C_UDPHS_EPTFIFO_READEPT4 (0x00540000)       // (UDPHS_EPTFIFO) FIFO Endpoint Data Register 4
// ========== Register definition for UDPHS_EPT_0 peripheral ========== 
#define AT91C_UDPHS_EPT_0_EPTCTLENB (0xF803C104)        // (UDPHS_EPT_0) UDPHS Endpoint Control Enable Register
#define AT91C_UDPHS_EPT_0_EPTSTA  (0xF803C11C)  // (UDPHS_EPT_0) UDPHS Endpoint Status Register
#define AT91C_UDPHS_EPT_0_EPTCLRSTA (0xF803C118)        // (UDPHS_EPT_0) UDPHS Endpoint Clear Status Register
#define AT91C_UDPHS_EPT_0_EPTCFG  (0xF803C100)  // (UDPHS_EPT_0) UDPHS Endpoint Config Register
#define AT91C_UDPHS_EPT_0_EPTSETSTA (0xF803C114)        // (UDPHS_EPT_0) UDPHS Endpoint Set Status Register
#define AT91C_UDPHS_EPT_0_EPTCTLDIS (0xF803C108)        // (UDPHS_EPT_0) UDPHS Endpoint Control Disable Register
#define AT91C_UDPHS_EPT_0_EPTCTL  (0xF803C10C)  // (UDPHS_EPT_0) UDPHS Endpoint Control Register
// ========== Register definition for UDPHS_EPT_1 peripheral ========== 
#define AT91C_UDPHS_EPT_1_EPTCTL  (0xF803C12C)  // (UDPHS_EPT_1) UDPHS Endpoint Control Register
#define AT91C_UDPHS_EPT_1_EPTCLRSTA (0xF803C138)        // (UDPHS_EPT_1) UDPHS Endpoint Clear Status Register
#define AT91C_UDPHS_EPT_1_EPTSETSTA (0xF803C134)        // (UDPHS_EPT_1) UDPHS Endpoint Set Status Register
#define AT91C_UDPHS_EPT_1_EPTCTLENB (0xF803C124)        // (UDPHS_EPT_1) UDPHS Endpoint Control Enable Register
#define AT91C_UDPHS_EPT_1_EPTCFG  (0xF803C120)  // (UDPHS_EPT_1) UDPHS Endpoint Config Register
#define AT91C_UDPHS_EPT_1_EPTCTLDIS (0xF803C128)        // (UDPHS_EPT_1) UDPHS Endpoint Control Disable Register
#define AT91C_UDPHS_EPT_1_EPTSTA  (0xF803C13C)  // (UDPHS_EPT_1) UDPHS Endpoint Status Register
// ========== Register definition for UDPHS_EPT_2 peripheral ========== 
#define AT91C_UDPHS_EPT_2_EPTSTA  (0xF803C15C)  // (UDPHS_EPT_2) UDPHS Endpoint Status Register
#define AT91C_UDPHS_EPT_2_EPTSETSTA (0xF803C154)        // (UDPHS_EPT_2) UDPHS Endpoint Set Status Register
#define AT91C_UDPHS_EPT_2_EPTCTLDIS (0xF803C148)        // (UDPHS_EPT_2) UDPHS Endpoint Control Disable Register
#define AT91C_UDPHS_EPT_2_EPTCTLENB (0xF803C144)        // (UDPHS_EPT_2) UDPHS Endpoint Control Enable Register
#define AT91C_UDPHS_EPT_2_EPTCLRSTA (0xF803C158)        // (UDPHS_EPT_2) UDPHS Endpoint Clear Status Register
#define AT91C_UDPHS_EPT_2_EPTCFG  (0xF803C140)  // (UDPHS_EPT_2) UDPHS Endpoint Config Register
#define AT91C_UDPHS_EPT_2_EPTCTL  (0xF803C14C)  // (UDPHS_EPT_2) UDPHS Endpoint Control Register
// ========== Register definition for UDPHS_EPT_3 peripheral ========== 
#define AT91C_UDPHS_EPT_3_EPTSETSTA (0xF803C174)        // (UDPHS_EPT_3) UDPHS Endpoint Set Status Register
#define AT91C_UDPHS_EPT_3_EPTCTLENB (0xF803C164)        // (UDPHS_EPT_3) UDPHS Endpoint Control Enable Register
#define AT91C_UDPHS_EPT_3_EPTSTA  (0xF803C17C)  // (UDPHS_EPT_3) UDPHS Endpoint Status Register
#define AT91C_UDPHS_EPT_3_EPTCTLDIS (0xF803C168)        // (UDPHS_EPT_3) UDPHS Endpoint Control Disable Register
#define AT91C_UDPHS_EPT_3_EPTCLRSTA (0xF803C178)        // (UDPHS_EPT_3) UDPHS Endpoint Clear Status Register
#define AT91C_UDPHS_EPT_3_EPTCFG  (0xF803C160)  // (UDPHS_EPT_3) UDPHS Endpoint Config Register
#define AT91C_UDPHS_EPT_3_EPTCTL  (0xF803C16C)  // (UDPHS_EPT_3) UDPHS Endpoint Control Register
// ========== Register definition for UDPHS_EPT_4 peripheral ========== 
#define AT91C_UDPHS_EPT_4_EPTSTA  (0xF803C19C)  // (UDPHS_EPT_4) UDPHS Endpoint Status Register
#define AT91C_UDPHS_EPT_4_EPTSETSTA (0xF803C194)        // (UDPHS_EPT_4) UDPHS Endpoint Set Status Register
#define AT91C_UDPHS_EPT_4_EPTCTLENB (0xF803C184)        // (UDPHS_EPT_4) UDPHS Endpoint Control Enable Register
#define AT91C_UDPHS_EPT_4_EPTCTLDIS (0xF803C188)        // (UDPHS_EPT_4) UDPHS Endpoint Control Disable Register
#define AT91C_UDPHS_EPT_4_EPTCFG  (0xF803C180)  // (UDPHS_EPT_4) UDPHS Endpoint Config Register
#define AT91C_UDPHS_EPT_4_EPTCTL  (0xF803C18C)  // (UDPHS_EPT_4) UDPHS Endpoint Control Register
#define AT91C_UDPHS_EPT_4_EPTCLRSTA (0xF803C198)        // (UDPHS_EPT_4) UDPHS Endpoint Clear Status Register
// ========== Register definition for UDPHS_EPT_5 peripheral ========== 
#define AT91C_UDPHS_EPT_5_EPTCTLDIS (0xF803C1A8)        // (UDPHS_EPT_5) UDPHS Endpoint Control Disable Register
#define AT91C_UDPHS_EPT_5_EPTCLRSTA (0xF803C1B8)        // (UDPHS_EPT_5) UDPHS Endpoint Clear Status Register
#define AT91C_UDPHS_EPT_5_EPTCTL  (0xF803C1AC)  // (UDPHS_EPT_5) UDPHS Endpoint Control Register
#define AT91C_UDPHS_EPT_5_EPTSETSTA (0xF803C1B4)        // (UDPHS_EPT_5) UDPHS Endpoint Set Status Register
#define AT91C_UDPHS_EPT_5_EPTCTLENB (0xF803C1A4)        // (UDPHS_EPT_5) UDPHS Endpoint Control Enable Register
#define AT91C_UDPHS_EPT_5_EPTCFG  (0xF803C1A0)  // (UDPHS_EPT_5) UDPHS Endpoint Config Register
#define AT91C_UDPHS_EPT_5_EPTSTA  (0xF803C1BC)  // (UDPHS_EPT_5) UDPHS Endpoint Status Register
// ========== Register definition for UDPHS_EPT_6 peripheral ========== 
#define AT91C_UDPHS_EPT_6_EPTSETSTA (0xF803C1D4)        // (UDPHS_EPT_6) UDPHS Endpoint Set Status Register
#define AT91C_UDPHS_EPT_6_EPTSTA  (0xF803C1DC)  // (UDPHS_EPT_6) UDPHS Endpoint Status Register
#define AT91C_UDPHS_EPT_6_EPTCTLENB (0xF803C1C4)        // (UDPHS_EPT_6) UDPHS Endpoint Control Enable Register
#define AT91C_UDPHS_EPT_6_EPTCTLDIS (0xF803C1C8)        // (UDPHS_EPT_6) UDPHS Endpoint Control Disable Register
#define AT91C_UDPHS_EPT_6_EPTCFG  (0xF803C1C0)  // (UDPHS_EPT_6) UDPHS Endpoint Config Register
#define AT91C_UDPHS_EPT_6_EPTCLRSTA (0xF803C1D8)        // (UDPHS_EPT_6) UDPHS Endpoint Clear Status Register
#define AT91C_UDPHS_EPT_6_EPTCTL  (0xF803C1CC)  // (UDPHS_EPT_6) UDPHS Endpoint Control Register
// ========== Register definition for UDPHS_DMA_1 peripheral ========== 
#define AT91C_UDPHS_DMA_1_DMASTATUS (0xF803C31C)        // (UDPHS_DMA_1) UDPHS DMA Channel Status Register
#define AT91C_UDPHS_DMA_1_DMAADDRESS (0xF803C314)       // (UDPHS_DMA_1) UDPHS DMA Channel Address Register
#define AT91C_UDPHS_DMA_1_DMACONTROL (0xF803C318)       // (UDPHS_DMA_1) UDPHS DMA Channel Control Register
#define AT91C_UDPHS_DMA_1_DMANXTDSC (0xF803C310)        // (UDPHS_DMA_1) UDPHS DMA Channel Next Descriptor Address
// ========== Register definition for UDPHS_DMA_2 peripheral ========== 
#define AT91C_UDPHS_DMA_2_DMANXTDSC (0xF803C320)        // (UDPHS_DMA_2) UDPHS DMA Channel Next Descriptor Address
#define AT91C_UDPHS_DMA_2_DMASTATUS (0xF803C32C)        // (UDPHS_DMA_2) UDPHS DMA Channel Status Register
#define AT91C_UDPHS_DMA_2_DMAADDRESS (0xF803C324)       // (UDPHS_DMA_2) UDPHS DMA Channel Address Register
#define AT91C_UDPHS_DMA_2_DMACONTROL (0xF803C328)       // (UDPHS_DMA_2) UDPHS DMA Channel Control Register
// ========== Register definition for UDPHS_DMA_3 peripheral ========== 
#define AT91C_UDPHS_DMA_3_DMASTATUS (0xF803C33C)        // (UDPHS_DMA_3) UDPHS DMA Channel Status Register
#define AT91C_UDPHS_DMA_3_DMANXTDSC (0xF803C330)        // (UDPHS_DMA_3) UDPHS DMA Channel Next Descriptor Address
#define AT91C_UDPHS_DMA_3_DMACONTROL (0xF803C338)       // (UDPHS_DMA_3) UDPHS DMA Channel Control Register
#define AT91C_UDPHS_DMA_3_DMAADDRESS (0xF803C334)       // (UDPHS_DMA_3) UDPHS DMA Channel Address Register
// ========== Register definition for UDPHS_DMA_4 peripheral ========== 
#define AT91C_UDPHS_DMA_4_DMASTATUS (0xF803C34C)        // (UDPHS_DMA_4) UDPHS DMA Channel Status Register
#define AT91C_UDPHS_DMA_4_DMACONTROL (0xF803C348)       // (UDPHS_DMA_4) UDPHS DMA Channel Control Register
#define AT91C_UDPHS_DMA_4_DMANXTDSC (0xF803C340)        // (UDPHS_DMA_4) UDPHS DMA Channel Next Descriptor Address
#define AT91C_UDPHS_DMA_4_DMAADDRESS (0xF803C344)       // (UDPHS_DMA_4) UDPHS DMA Channel Address Register
// ========== Register definition for UDPHS_DMA_5 peripheral ========== 
#define AT91C_UDPHS_DMA_5_DMAADDRESS (0xF803C354)       // (UDPHS_DMA_5) UDPHS DMA Channel Address Register
#define AT91C_UDPHS_DMA_5_DMACONTROL (0xF803C358)       // (UDPHS_DMA_5) UDPHS DMA Channel Control Register
#define AT91C_UDPHS_DMA_5_DMASTATUS (0xF803C35C)        // (UDPHS_DMA_5) UDPHS DMA Channel Status Register
#define AT91C_UDPHS_DMA_5_DMANXTDSC (0xF803C350)        // (UDPHS_DMA_5) UDPHS DMA Channel Next Descriptor Address
// ========== Register definition for UDPHS_DMA_6 peripheral ========== 
#define AT91C_UDPHS_DMA_6_DMASTATUS (0xF803C36C)        // (UDPHS_DMA_6) UDPHS DMA Channel Status Register
#define AT91C_UDPHS_DMA_6_DMAADDRESS (0xF803C364)       // (UDPHS_DMA_6) UDPHS DMA Channel Address Register
#define AT91C_UDPHS_DMA_6_DMACONTROL (0xF803C368)       // (UDPHS_DMA_6) UDPHS DMA Channel Control Register
#define AT91C_UDPHS_DMA_6_DMANXTDSC (0xF803C360)        // (UDPHS_DMA_6) UDPHS DMA Channel Next Descriptor Address
// ========== Register definition for UDPHS peripheral ========== 
#define AT91C_UDPHS_CTRL          (0xF803C000)  // (UDPHS) UDPHS Control Register
#define AT91C_UDPHS_TSTCNTA       (0xF803C0D4)  // (UDPHS) UDPHS Test A Counter Register
#define AT91C_UDPHS_IPVERSION     (0xF803C0FC)  // (UDPHS) UDPHS Version Register
#define AT91C_UDPHS_RIPNAME1      (0xF803C0F0)  // (UDPHS) UDPHS Name1 Register
#define AT91C_UDPHS_RIPNAME2      (0xF803C0F4)  // (UDPHS) UDPHS Name2 Register
#define AT91C_UDPHS_IEN           (0xF803C010)  // (UDPHS) UDPHS Interrupt Enable Register
#define AT91C_UDPHS_CLRINT        (0xF803C018)  // (UDPHS) UDPHS Clear Interrupt Register
#define AT91C_UDPHS_FNUM          (0xF803C004)  // (UDPHS) UDPHS Frame Number Register
#define AT91C_UDPHS_TSTMODREG     (0xF803C0DC)  // (UDPHS) UDPHS Test Mode Register
#define AT91C_UDPHS_TSTCNTB       (0xF803C0D8)  // (UDPHS) UDPHS Test B Counter Register
#define AT91C_UDPHS_EPTRST        (0xF803C01C)  // (UDPHS) UDPHS Endpoints Reset Register
#define AT91C_UDPHS_TST           (0xF803C0E0)  // (UDPHS) UDPHS Test Register
#define AT91C_UDPHS_TSTSOFCNT     (0xF803C0D0)  // (UDPHS) UDPHS Test SOF Counter Register
#define AT91C_UDPHS_INTSTA        (0xF803C014)  // (UDPHS) UDPHS Interrupt Status Register
#define AT91C_UDPHS_RIPPADDRSIZE  (0xF803C0EC)  // (UDPHS) UDPHS PADDRSIZE Register
#define AT91C_UDPHS_IPFEATURES    (0xF803C0F8)  // (UDPHS) UDPHS Features Register
// ========== Register definition for HLCDC4 peripheral ========== 
// ========== Register definition for HDMA0_CH_0 peripheral ========== 
#define AT91C_HDMA0_CH_0_BDSCR    (0xFFFFEC5C)  // (HDMA0_CH_0) HDMA Reserved
#define AT91C_HDMA0_CH_0_DADDR    (0xFFFFEC40)  // (HDMA0_CH_0) HDMA Channel Destination Address Register
#define AT91C_HDMA0_CH_0_DPIP     (0xFFFFEC58)  // (HDMA0_CH_0) HDMA Channel Destination Picture in Picture Configuration Register
#define AT91C_HDMA0_CH_0_DSCR     (0xFFFFEC44)  // (HDMA0_CH_0) HDMA Channel Descriptor Address Register
#define AT91C_HDMA0_CH_0_CFG      (0xFFFFEC50)  // (HDMA0_CH_0) HDMA Channel Configuration Register
#define AT91C_HDMA0_CH_0_SPIP     (0xFFFFEC54)  // (HDMA0_CH_0) HDMA Channel Source Picture in Picture Configuration Register
#define AT91C_HDMA0_CH_0_CADDR    (0xFFFFEC60)  // (HDMA0_CH_0) HDMA Reserved
#define AT91C_HDMA0_CH_0_CTRLA    (0xFFFFEC48)  // (HDMA0_CH_0) HDMA Channel Control A Register
#define AT91C_HDMA0_CH_0_CTRLB    (0xFFFFEC4C)  // (HDMA0_CH_0) HDMA Channel Control B Register
#define AT91C_HDMA0_CH_0_SADDR    (0xFFFFEC3C)  // (HDMA0_CH_0) HDMA Channel Source Address Register
// ========== Register definition for HDMA0_CH_1 peripheral ========== 
#define AT91C_HDMA0_CH_1_CADDR    (0xFFFFEC88)  // (HDMA0_CH_1) HDMA Reserved
#define AT91C_HDMA0_CH_1_DPIP     (0xFFFFEC80)  // (HDMA0_CH_1) HDMA Channel Destination Picture in Picture Configuration Register
#define AT91C_HDMA0_CH_1_CTRLB    (0xFFFFEC74)  // (HDMA0_CH_1) HDMA Channel Control B Register
#define AT91C_HDMA0_CH_1_SADDR    (0xFFFFEC64)  // (HDMA0_CH_1) HDMA Channel Source Address Register
#define AT91C_HDMA0_CH_1_BDSCR    (0xFFFFEC84)  // (HDMA0_CH_1) HDMA Reserved
#define AT91C_HDMA0_CH_1_CFG      (0xFFFFEC78)  // (HDMA0_CH_1) HDMA Channel Configuration Register
#define AT91C_HDMA0_CH_1_DSCR     (0xFFFFEC6C)  // (HDMA0_CH_1) HDMA Channel Descriptor Address Register
#define AT91C_HDMA0_CH_1_DADDR    (0xFFFFEC68)  // (HDMA0_CH_1) HDMA Channel Destination Address Register
#define AT91C_HDMA0_CH_1_CTRLA    (0xFFFFEC70)  // (HDMA0_CH_1) HDMA Channel Control A Register
#define AT91C_HDMA0_CH_1_SPIP     (0xFFFFEC7C)  // (HDMA0_CH_1) HDMA Channel Source Picture in Picture Configuration Register
// ========== Register definition for HDMA0_CH_2 peripheral ========== 
#define AT91C_HDMA0_CH_2_SADDR    (0xFFFFEC8C)  // (HDMA0_CH_2) HDMA Channel Source Address Register
#define AT91C_HDMA0_CH_2_BDSCR    (0xFFFFECAC)  // (HDMA0_CH_2) HDMA Reserved
#define AT91C_HDMA0_CH_2_DPIP     (0xFFFFECA8)  // (HDMA0_CH_2) HDMA Channel Destination Picture in Picture Configuration Register
#define AT91C_HDMA0_CH_2_SPIP     (0xFFFFECA4)  // (HDMA0_CH_2) HDMA Channel Source Picture in Picture Configuration Register
#define AT91C_HDMA0_CH_2_DADDR    (0xFFFFEC90)  // (HDMA0_CH_2) HDMA Channel Destination Address Register
#define AT91C_HDMA0_CH_2_DSCR     (0xFFFFEC94)  // (HDMA0_CH_2) HDMA Channel Descriptor Address Register
#define AT91C_HDMA0_CH_2_CTRLA    (0xFFFFEC98)  // (HDMA0_CH_2) HDMA Channel Control A Register
#define AT91C_HDMA0_CH_2_CADDR    (0xFFFFECB0)  // (HDMA0_CH_2) HDMA Reserved
#define AT91C_HDMA0_CH_2_CFG      (0xFFFFECA0)  // (HDMA0_CH_2) HDMA Channel Configuration Register
#define AT91C_HDMA0_CH_2_CTRLB    (0xFFFFEC9C)  // (HDMA0_CH_2) HDMA Channel Control B Register
// ========== Register definition for HDMA0_CH_3 peripheral ========== 
#define AT91C_HDMA0_CH_3_SPIP     (0xFFFFECCC)  // (HDMA0_CH_3) HDMA Channel Source Picture in Picture Configuration Register
#define AT91C_HDMA0_CH_3_CTRLA    (0xFFFFECC0)  // (HDMA0_CH_3) HDMA Channel Control A Register
#define AT91C_HDMA0_CH_3_DPIP     (0xFFFFECD0)  // (HDMA0_CH_3) HDMA Channel Destination Picture in Picture Configuration Register
#define AT91C_HDMA0_CH_3_CTRLB    (0xFFFFECC4)  // (HDMA0_CH_3) HDMA Channel Control B Register
#define AT91C_HDMA0_CH_3_BDSCR    (0xFFFFECD4)  // (HDMA0_CH_3) HDMA Reserved
#define AT91C_HDMA0_CH_3_DSCR     (0xFFFFECBC)  // (HDMA0_CH_3) HDMA Channel Descriptor Address Register
#define AT91C_HDMA0_CH_3_CADDR    (0xFFFFECD8)  // (HDMA0_CH_3) HDMA Reserved
#define AT91C_HDMA0_CH_3_CFG      (0xFFFFECC8)  // (HDMA0_CH_3) HDMA Channel Configuration Register
#define AT91C_HDMA0_CH_3_DADDR    (0xFFFFECB8)  // (HDMA0_CH_3) HDMA Channel Destination Address Register
#define AT91C_HDMA0_CH_3_SADDR    (0xFFFFECB4)  // (HDMA0_CH_3) HDMA Channel Source Address Register
// ========== Register definition for HDMA0_CH_4 peripheral ========== 
#define AT91C_HDMA0_CH_4_CFG      (0xFFFFECF0)  // (HDMA0_CH_4) HDMA Channel Configuration Register
#define AT91C_HDMA0_CH_4_BDSCR    (0xFFFFECFC)  // (HDMA0_CH_4) HDMA Reserved
#define AT91C_HDMA0_CH_4_CADDR    (0xFFFFED00)  // (HDMA0_CH_4) HDMA Reserved
#define AT91C_HDMA0_CH_4_DADDR    (0xFFFFECE0)  // (HDMA0_CH_4) HDMA Channel Destination Address Register
#define AT91C_HDMA0_CH_4_CTRLA    (0xFFFFECE8)  // (HDMA0_CH_4) HDMA Channel Control A Register
#define AT91C_HDMA0_CH_4_SADDR    (0xFFFFECDC)  // (HDMA0_CH_4) HDMA Channel Source Address Register
#define AT91C_HDMA0_CH_4_CTRLB    (0xFFFFECEC)  // (HDMA0_CH_4) HDMA Channel Control B Register
#define AT91C_HDMA0_CH_4_DSCR     (0xFFFFECE4)  // (HDMA0_CH_4) HDMA Channel Descriptor Address Register
#define AT91C_HDMA0_CH_4_SPIP     (0xFFFFECF4)  // (HDMA0_CH_4) HDMA Channel Source Picture in Picture Configuration Register
#define AT91C_HDMA0_CH_4_DPIP     (0xFFFFECF8)  // (HDMA0_CH_4) HDMA Channel Destination Picture in Picture Configuration Register
// ========== Register definition for HDMA0_CH_5 peripheral ========== 
#define AT91C_HDMA0_CH_5_CTRLB    (0xFFFFED14)  // (HDMA0_CH_5) HDMA Channel Control B Register
#define AT91C_HDMA0_CH_5_DADDR    (0xFFFFED08)  // (HDMA0_CH_5) HDMA Channel Destination Address Register
#define AT91C_HDMA0_CH_5_SPIP     (0xFFFFED1C)  // (HDMA0_CH_5) HDMA Channel Source Picture in Picture Configuration Register
#define AT91C_HDMA0_CH_5_DSCR     (0xFFFFED0C)  // (HDMA0_CH_5) HDMA Channel Descriptor Address Register
#define AT91C_HDMA0_CH_5_DPIP     (0xFFFFED20)  // (HDMA0_CH_5) HDMA Channel Destination Picture in Picture Configuration Register
#define AT91C_HDMA0_CH_5_CFG      (0xFFFFED18)  // (HDMA0_CH_5) HDMA Channel Configuration Register
#define AT91C_HDMA0_CH_5_CADDR    (0xFFFFED28)  // (HDMA0_CH_5) HDMA Reserved
#define AT91C_HDMA0_CH_5_SADDR    (0xFFFFED04)  // (HDMA0_CH_5) HDMA Channel Source Address Register
#define AT91C_HDMA0_CH_5_BDSCR    (0xFFFFED24)  // (HDMA0_CH_5) HDMA Reserved
#define AT91C_HDMA0_CH_5_CTRLA    (0xFFFFED10)  // (HDMA0_CH_5) HDMA Channel Control A Register
// ========== Register definition for HDMA0_CH_6 peripheral ========== 
#define AT91C_HDMA0_CH_6_SADDR    (0xFFFFED2C)  // (HDMA0_CH_6) HDMA Channel Source Address Register
#define AT91C_HDMA0_CH_6_BDSCR    (0xFFFFED4C)  // (HDMA0_CH_6) HDMA Reserved
#define AT91C_HDMA0_CH_6_CADDR    (0xFFFFED50)  // (HDMA0_CH_6) HDMA Reserved
#define AT91C_HDMA0_CH_6_SPIP     (0xFFFFED44)  // (HDMA0_CH_6) HDMA Channel Source Picture in Picture Configuration Register
#define AT91C_HDMA0_CH_6_CTRLB    (0xFFFFED3C)  // (HDMA0_CH_6) HDMA Channel Control B Register
#define AT91C_HDMA0_CH_6_DSCR     (0xFFFFED34)  // (HDMA0_CH_6) HDMA Channel Descriptor Address Register
#define AT91C_HDMA0_CH_6_CFG      (0xFFFFED40)  // (HDMA0_CH_6) HDMA Channel Configuration Register
#define AT91C_HDMA0_CH_6_DPIP     (0xFFFFED48)  // (HDMA0_CH_6) HDMA Channel Destination Picture in Picture Configuration Register
#define AT91C_HDMA0_CH_6_DADDR    (0xFFFFED30)  // (HDMA0_CH_6) HDMA Channel Destination Address Register
#define AT91C_HDMA0_CH_6_CTRLA    (0xFFFFED38)  // (HDMA0_CH_6) HDMA Channel Control A Register
// ========== Register definition for HDMA0_CH_7 peripheral ========== 
#define AT91C_HDMA0_CH_7_CADDR    (0xFFFFED78)  // (HDMA0_CH_7) HDMA Reserved
#define AT91C_HDMA0_CH_7_CFG      (0xFFFFED68)  // (HDMA0_CH_7) HDMA Channel Configuration Register
#define AT91C_HDMA0_CH_7_DADDR    (0xFFFFED58)  // (HDMA0_CH_7) HDMA Channel Destination Address Register
#define AT91C_HDMA0_CH_7_CTRLB    (0xFFFFED64)  // (HDMA0_CH_7) HDMA Channel Control B Register
#define AT91C_HDMA0_CH_7_DSCR     (0xFFFFED5C)  // (HDMA0_CH_7) HDMA Channel Descriptor Address Register
#define AT91C_HDMA0_CH_7_DPIP     (0xFFFFED70)  // (HDMA0_CH_7) HDMA Channel Destination Picture in Picture Configuration Register
#define AT91C_HDMA0_CH_7_CTRLA    (0xFFFFED60)  // (HDMA0_CH_7) HDMA Channel Control A Register
#define AT91C_HDMA0_CH_7_BDSCR    (0xFFFFED74)  // (HDMA0_CH_7) HDMA Reserved
#define AT91C_HDMA0_CH_7_SPIP     (0xFFFFED6C)  // (HDMA0_CH_7) HDMA Channel Source Picture in Picture Configuration Register
#define AT91C_HDMA0_CH_7_SADDR    (0xFFFFED54)  // (HDMA0_CH_7) HDMA Channel Source Address Register
// ========== Register definition for HDMA0 peripheral ========== 
#define AT91C_HDMA0_EBCIDR        (0xFFFFEC1C)  // (HDMA0) HDMA Error, Chained Buffer transfer completed and Buffer transfer completed Interrupt Disable register
#define AT91C_HDMA0_RSVD0         (0xFFFFEC34)  // (HDMA0) HDMA Reserved
#define AT91C_HDMA0_FEATURES      (0xFFFFEDF8)  // (HDMA0) HDMA FEATURES REGISTER
#define AT91C_HDMA0_CHER          (0xFFFFEC28)  // (HDMA0) HDMA Channel Handler Enable Register
#define AT91C_HDMA0_CHDR          (0xFFFFEC2C)  // (HDMA0) HDMA Channel Handler Disable Register
#define AT91C_HDMA0_CREQ          (0xFFFFEC0C)  // (HDMA0) HDMA Software Chunk Transfer Request Register
#define AT91C_HDMA0_SYNC          (0xFFFFEC14)  // (HDMA0) HDMA Request Synchronization Register
#define AT91C_HDMA0_EN            (0xFFFFEC04)  // (HDMA0) HDMA Controller Enable Register
#define AT91C_HDMA0_ADDRSIZE      (0xFFFFEDEC)  // (HDMA0) HDMA ADDRSIZE REGISTER
#define AT91C_HDMA0_VER           (0xFFFFEDFC)  // (HDMA0) HDMA VERSION REGISTER
#define AT91C_HDMA0_LAST          (0xFFFFEC10)  // (HDMA0) HDMA Software Last Transfer Flag Register
#define AT91C_HDMA0_SREQ          (0xFFFFEC08)  // (HDMA0) HDMA Software Single Request Register
#define AT91C_HDMA0_EBCIER        (0xFFFFEC18)  // (HDMA0) HDMA Error, Chained Buffer transfer completed and Buffer transfer completed Interrupt Enable register
#define AT91C_HDMA0_GCFG          (0xFFFFEC00)  // (HDMA0) HDMA Global Configuration Register
#define AT91C_HDMA0_EBCIMR        (0xFFFFEC20)  // (HDMA0) HDMA Error, Chained Buffer transfer completed and Buffer transfer completed Mask Register
#define AT91C_HDMA0_RSVD1         (0xFFFFEC38)  // (HDMA0) HDMA Reserved
#define AT91C_HDMA0_IPNAME2       (0xFFFFEDF4)  // (HDMA0) HDMA IPNAME2 REGISTER
#define AT91C_HDMA0_IPNAME1       (0xFFFFEDF0)  // (HDMA0) HDMA IPNAME1 REGISTER
#define AT91C_HDMA0_EBCISR        (0xFFFFEC24)  // (HDMA0) HDMA Error, Chained Buffer transfer completed and Buffer transfer completed Status Register
#define AT91C_HDMA0_CHSR          (0xFFFFEC30)  // (HDMA0) HDMA Channel Handler Status Register
// ========== Register definition for HDMA1_CH_0 peripheral ========== 
#define AT91C_HDMA1_CH_0_CADDR    (0xFFFFEE60)  // (HDMA1_CH_0) HDMA Reserved
#define AT91C_HDMA1_CH_0_DSCR     (0xFFFFEE44)  // (HDMA1_CH_0) HDMA Channel Descriptor Address Register
#define AT91C_HDMA1_CH_0_BDSCR    (0xFFFFEE5C)  // (HDMA1_CH_0) HDMA Reserved
#define AT91C_HDMA1_CH_0_CTRLA    (0xFFFFEE48)  // (HDMA1_CH_0) HDMA Channel Control A Register
#define AT91C_HDMA1_CH_0_SADDR    (0xFFFFEE3C)  // (HDMA1_CH_0) HDMA Channel Source Address Register
#define AT91C_HDMA1_CH_0_CTRLB    (0xFFFFEE4C)  // (HDMA1_CH_0) HDMA Channel Control B Register
#define AT91C_HDMA1_CH_0_DADDR    (0xFFFFEE40)  // (HDMA1_CH_0) HDMA Channel Destination Address Register
#define AT91C_HDMA1_CH_0_CFG      (0xFFFFEE50)  // (HDMA1_CH_0) HDMA Channel Configuration Register
#define AT91C_HDMA1_CH_0_SPIP     (0xFFFFEE54)  // (HDMA1_CH_0) HDMA Channel Source Picture in Picture Configuration Register
#define AT91C_HDMA1_CH_0_DPIP     (0xFFFFEE58)  // (HDMA1_CH_0) HDMA Channel Destination Picture in Picture Configuration Register
// ========== Register definition for HDMA1_CH_1 peripheral ========== 
#define AT91C_HDMA1_CH_1_DADDR    (0xFFFFEE68)  // (HDMA1_CH_1) HDMA Channel Destination Address Register
#define AT91C_HDMA1_CH_1_DPIP     (0xFFFFEE80)  // (HDMA1_CH_1) HDMA Channel Destination Picture in Picture Configuration Register
#define AT91C_HDMA1_CH_1_CADDR    (0xFFFFEE88)  // (HDMA1_CH_1) HDMA Reserved
#define AT91C_HDMA1_CH_1_SPIP     (0xFFFFEE7C)  // (HDMA1_CH_1) HDMA Channel Source Picture in Picture Configuration Register
#define AT91C_HDMA1_CH_1_DSCR     (0xFFFFEE6C)  // (HDMA1_CH_1) HDMA Channel Descriptor Address Register
#define AT91C_HDMA1_CH_1_BDSCR    (0xFFFFEE84)  // (HDMA1_CH_1) HDMA Reserved
#define AT91C_HDMA1_CH_1_CTRLB    (0xFFFFEE74)  // (HDMA1_CH_1) HDMA Channel Control B Register
#define AT91C_HDMA1_CH_1_CFG      (0xFFFFEE78)  // (HDMA1_CH_1) HDMA Channel Configuration Register
#define AT91C_HDMA1_CH_1_CTRLA    (0xFFFFEE70)  // (HDMA1_CH_1) HDMA Channel Control A Register
#define AT91C_HDMA1_CH_1_SADDR    (0xFFFFEE64)  // (HDMA1_CH_1) HDMA Channel Source Address Register
// ========== Register definition for HDMA1_CH_2 peripheral ========== 
#define AT91C_HDMA1_CH_2_CTRLA    (0xFFFFEE98)  // (HDMA1_CH_2) HDMA Channel Control A Register
#define AT91C_HDMA1_CH_2_DPIP     (0xFFFFEEA8)  // (HDMA1_CH_2) HDMA Channel Destination Picture in Picture Configuration Register
#define AT91C_HDMA1_CH_2_DADDR    (0xFFFFEE90)  // (HDMA1_CH_2) HDMA Channel Destination Address Register
#define AT91C_HDMA1_CH_2_SPIP     (0xFFFFEEA4)  // (HDMA1_CH_2) HDMA Channel Source Picture in Picture Configuration Register
#define AT91C_HDMA1_CH_2_CFG      (0xFFFFEEA0)  // (HDMA1_CH_2) HDMA Channel Configuration Register
#define AT91C_HDMA1_CH_2_BDSCR    (0xFFFFEEAC)  // (HDMA1_CH_2) HDMA Reserved
#define AT91C_HDMA1_CH_2_DSCR     (0xFFFFEE94)  // (HDMA1_CH_2) HDMA Channel Descriptor Address Register
#define AT91C_HDMA1_CH_2_CADDR    (0xFFFFEEB0)  // (HDMA1_CH_2) HDMA Reserved
#define AT91C_HDMA1_CH_2_CTRLB    (0xFFFFEE9C)  // (HDMA1_CH_2) HDMA Channel Control B Register
#define AT91C_HDMA1_CH_2_SADDR    (0xFFFFEE8C)  // (HDMA1_CH_2) HDMA Channel Source Address Register
// ========== Register definition for HDMA1_CH_3 peripheral ========== 
#define AT91C_HDMA1_CH_3_DSCR     (0xFFFFEEBC)  // (HDMA1_CH_3) HDMA Channel Descriptor Address Register
#define AT91C_HDMA1_CH_3_BDSCR    (0xFFFFEED4)  // (HDMA1_CH_3) HDMA Reserved
#define AT91C_HDMA1_CH_3_DPIP     (0xFFFFEED0)  // (HDMA1_CH_3) HDMA Channel Destination Picture in Picture Configuration Register
#define AT91C_HDMA1_CH_3_SADDR    (0xFFFFEEB4)  // (HDMA1_CH_3) HDMA Channel Source Address Register
#define AT91C_HDMA1_CH_3_CTRLB    (0xFFFFEEC4)  // (HDMA1_CH_3) HDMA Channel Control B Register
#define AT91C_HDMA1_CH_3_CTRLA    (0xFFFFEEC0)  // (HDMA1_CH_3) HDMA Channel Control A Register
#define AT91C_HDMA1_CH_3_DADDR    (0xFFFFEEB8)  // (HDMA1_CH_3) HDMA Channel Destination Address Register
#define AT91C_HDMA1_CH_3_CADDR    (0xFFFFEED8)  // (HDMA1_CH_3) HDMA Reserved
#define AT91C_HDMA1_CH_3_CFG      (0xFFFFEEC8)  // (HDMA1_CH_3) HDMA Channel Configuration Register
#define AT91C_HDMA1_CH_3_SPIP     (0xFFFFEECC)  // (HDMA1_CH_3) HDMA Channel Source Picture in Picture Configuration Register
// ========== Register definition for HDMA1_CH_4 peripheral ========== 
#define AT91C_HDMA1_CH_4_CTRLB    (0xFFFFEEEC)  // (HDMA1_CH_4) HDMA Channel Control B Register
#define AT91C_HDMA1_CH_4_DADDR    (0xFFFFEEE0)  // (HDMA1_CH_4) HDMA Channel Destination Address Register
#define AT91C_HDMA1_CH_4_DSCR     (0xFFFFEEE4)  // (HDMA1_CH_4) HDMA Channel Descriptor Address Register
#define AT91C_HDMA1_CH_4_DPIP     (0xFFFFEEF8)  // (HDMA1_CH_4) HDMA Channel Destination Picture in Picture Configuration Register
#define AT91C_HDMA1_CH_4_SADDR    (0xFFFFEEDC)  // (HDMA1_CH_4) HDMA Channel Source Address Register
#define AT91C_HDMA1_CH_4_BDSCR    (0xFFFFEEFC)  // (HDMA1_CH_4) HDMA Reserved
#define AT91C_HDMA1_CH_4_SPIP     (0xFFFFEEF4)  // (HDMA1_CH_4) HDMA Channel Source Picture in Picture Configuration Register
#define AT91C_HDMA1_CH_4_CTRLA    (0xFFFFEEE8)  // (HDMA1_CH_4) HDMA Channel Control A Register
#define AT91C_HDMA1_CH_4_CADDR    (0xFFFFEF00)  // (HDMA1_CH_4) HDMA Reserved
#define AT91C_HDMA1_CH_4_CFG      (0xFFFFEEF0)  // (HDMA1_CH_4) HDMA Channel Configuration Register
// ========== Register definition for HDMA1_CH_5 peripheral ========== 
#define AT91C_HDMA1_CH_5_CADDR    (0xFFFFEF28)  // (HDMA1_CH_5) HDMA Reserved
#define AT91C_HDMA1_CH_5_DPIP     (0xFFFFEF20)  // (HDMA1_CH_5) HDMA Channel Destination Picture in Picture Configuration Register
#define AT91C_HDMA1_CH_5_SADDR    (0xFFFFEF04)  // (HDMA1_CH_5) HDMA Channel Source Address Register
#define AT91C_HDMA1_CH_5_DSCR     (0xFFFFEF0C)  // (HDMA1_CH_5) HDMA Channel Descriptor Address Register
#define AT91C_HDMA1_CH_5_CTRLB    (0xFFFFEF14)  // (HDMA1_CH_5) HDMA Channel Control B Register
#define AT91C_HDMA1_CH_5_CFG      (0xFFFFEF18)  // (HDMA1_CH_5) HDMA Channel Configuration Register
#define AT91C_HDMA1_CH_5_CTRLA    (0xFFFFEF10)  // (HDMA1_CH_5) HDMA Channel Control A Register
#define AT91C_HDMA1_CH_5_BDSCR    (0xFFFFEF24)  // (HDMA1_CH_5) HDMA Reserved
#define AT91C_HDMA1_CH_5_DADDR    (0xFFFFEF08)  // (HDMA1_CH_5) HDMA Channel Destination Address Register
#define AT91C_HDMA1_CH_5_SPIP     (0xFFFFEF1C)  // (HDMA1_CH_5) HDMA Channel Source Picture in Picture Configuration Register
// ========== Register definition for HDMA1_CH_6 peripheral ========== 
#define AT91C_HDMA1_CH_6_SPIP     (0xFFFFEF44)  // (HDMA1_CH_6) HDMA Channel Source Picture in Picture Configuration Register
#define AT91C_HDMA1_CH_6_CTRLA    (0xFFFFEF38)  // (HDMA1_CH_6) HDMA Channel Control A Register
#define AT91C_HDMA1_CH_6_CFG      (0xFFFFEF40)  // (HDMA1_CH_6) HDMA Channel Configuration Register
#define AT91C_HDMA1_CH_6_BDSCR    (0xFFFFEF4C)  // (HDMA1_CH_6) HDMA Reserved
#define AT91C_HDMA1_CH_6_CTRLB    (0xFFFFEF3C)  // (HDMA1_CH_6) HDMA Channel Control B Register
#define AT91C_HDMA1_CH_6_DSCR     (0xFFFFEF34)  // (HDMA1_CH_6) HDMA Channel Descriptor Address Register
#define AT91C_HDMA1_CH_6_CADDR    (0xFFFFEF50)  // (HDMA1_CH_6) HDMA Reserved
#define AT91C_HDMA1_CH_6_DADDR    (0xFFFFEF30)  // (HDMA1_CH_6) HDMA Channel Destination Address Register
#define AT91C_HDMA1_CH_6_SADDR    (0xFFFFEF2C)  // (HDMA1_CH_6) HDMA Channel Source Address Register
#define AT91C_HDMA1_CH_6_DPIP     (0xFFFFEF48)  // (HDMA1_CH_6) HDMA Channel Destination Picture in Picture Configuration Register
// ========== Register definition for HDMA1_CH_7 peripheral ========== 
#define AT91C_HDMA1_CH_7_BDSCR    (0xFFFFEF74)  // (HDMA1_CH_7) HDMA Reserved
#define AT91C_HDMA1_CH_7_DSCR     (0xFFFFEF5C)  // (HDMA1_CH_7) HDMA Channel Descriptor Address Register
#define AT91C_HDMA1_CH_7_DADDR    (0xFFFFEF58)  // (HDMA1_CH_7) HDMA Channel Destination Address Register
#define AT91C_HDMA1_CH_7_CTRLA    (0xFFFFEF60)  // (HDMA1_CH_7) HDMA Channel Control A Register
#define AT91C_HDMA1_CH_7_CFG      (0xFFFFEF68)  // (HDMA1_CH_7) HDMA Channel Configuration Register
#define AT91C_HDMA1_CH_7_SPIP     (0xFFFFEF6C)  // (HDMA1_CH_7) HDMA Channel Source Picture in Picture Configuration Register
#define AT91C_HDMA1_CH_7_DPIP     (0xFFFFEF70)  // (HDMA1_CH_7) HDMA Channel Destination Picture in Picture Configuration Register
#define AT91C_HDMA1_CH_7_CADDR    (0xFFFFEF78)  // (HDMA1_CH_7) HDMA Reserved
#define AT91C_HDMA1_CH_7_SADDR    (0xFFFFEF54)  // (HDMA1_CH_7) HDMA Channel Source Address Register
#define AT91C_HDMA1_CH_7_CTRLB    (0xFFFFEF64)  // (HDMA1_CH_7) HDMA Channel Control B Register
// ========== Register definition for HDMA1 peripheral ========== 
#define AT91C_HDMA1_EBCIMR        (0xFFFFEE20)  // (HDMA1) HDMA Error, Chained Buffer transfer completed and Buffer transfer completed Mask Register
#define AT91C_HDMA1_GCFG          (0xFFFFEE00)  // (HDMA1) HDMA Global Configuration Register
#define AT91C_HDMA1_EBCIDR        (0xFFFFEE1C)  // (HDMA1) HDMA Error, Chained Buffer transfer completed and Buffer transfer completed Interrupt Disable register
#define AT91C_HDMA1_CHSR          (0xFFFFEE30)  // (HDMA1) HDMA Channel Handler Status Register
#define AT91C_HDMA1_LAST          (0xFFFFEE10)  // (HDMA1) HDMA Software Last Transfer Flag Register
#define AT91C_HDMA1_VER           (0xFFFFEFFC)  // (HDMA1) HDMA VERSION REGISTER
#define AT91C_HDMA1_SREQ          (0xFFFFEE08)  // (HDMA1) HDMA Software Single Request Register
#define AT91C_HDMA1_CHER          (0xFFFFEE28)  // (HDMA1) HDMA Channel Handler Enable Register
#define AT91C_HDMA1_EBCIER        (0xFFFFEE18)  // (HDMA1) HDMA Error, Chained Buffer transfer completed and Buffer transfer completed Interrupt Enable register
#define AT91C_HDMA1_ADDRSIZE      (0xFFFFEFEC)  // (HDMA1) HDMA ADDRSIZE REGISTER
#define AT91C_HDMA1_RSVD0         (0xFFFFEE34)  // (HDMA1) HDMA Reserved
#define AT91C_HDMA1_FEATURES      (0xFFFFEFF8)  // (HDMA1) HDMA FEATURES REGISTER
#define AT91C_HDMA1_RSVD1         (0xFFFFEE38)  // (HDMA1) HDMA Reserved
#define AT91C_HDMA1_CREQ          (0xFFFFEE0C)  // (HDMA1) HDMA Software Chunk Transfer Request Register
#define AT91C_HDMA1_CHDR          (0xFFFFEE2C)  // (HDMA1) HDMA Channel Handler Disable Register
#define AT91C_HDMA1_EBCISR        (0xFFFFEE24)  // (HDMA1) HDMA Error, Chained Buffer transfer completed and Buffer transfer completed Status Register
#define AT91C_HDMA1_SYNC          (0xFFFFEE14)  // (HDMA1) HDMA Request Synchronization Register
#define AT91C_HDMA1_IPNAME2       (0xFFFFEFF4)  // (HDMA1) HDMA IPNAME2 REGISTER
#define AT91C_HDMA1_EN            (0xFFFFEE04)  // (HDMA1) HDMA Controller Enable Register
#define AT91C_HDMA1_IPNAME1       (0xFFFFEFF0)  // (HDMA1) HDMA IPNAME1 REGISTER
// ========== Register definition for BCH_ECC_0 peripheral ========== 
#define AT91C_BCH_ECC_0_PMECC7    (0xFFFFE05C)  // (BCH_ECC_0) PMECC BCH Redundancy  7 Register
#define AT91C_BCH_ECC_0_PMECC4    (0xFFFFE050)  // (BCH_ECC_0) PMECC BCH Redundancy  4 Register
#define AT91C_BCH_ECC_0_PMECC10   (0xFFFFE068)  // (BCH_ECC_0) PMECC BCH Redundancy 10 Register
#define AT91C_BCH_ECC_0_PMECC14   (0xFFFFE078)  // (BCH_ECC_0) PMECC BCH Redundancy 14 Register
#define AT91C_BCH_ECC_0_PMECC11   (0xFFFFE06C)  // (BCH_ECC_0) PMECC BCH Redundancy 11 Register
#define AT91C_BCH_ECC_0_PMECC3    (0xFFFFE04C)  // (BCH_ECC_0) PMECC BCH Redundancy  3 Register
#define AT91C_BCH_ECC_0_PMECC15   (0xFFFFE07C)  // (BCH_ECC_0) PMECC BCH Redundancy 15 Register
#define AT91C_BCH_ECC_0_PMECC2    (0xFFFFE048)  // (BCH_ECC_0) PMECC BCH Redundancy  2 Register
#define AT91C_BCH_ECC_0_PMECC1    (0xFFFFE044)  // (BCH_ECC_0) PMECC BCH Redundancy  1 Register
#define AT91C_BCH_ECC_0_PMECC8    (0xFFFFE060)  // (BCH_ECC_0) PMECC BCH Redundancy  8 Register
#define AT91C_BCH_ECC_0_PMECC12   (0xFFFFE070)  // (BCH_ECC_0) PMECC BCH Redundancy 12 Register
#define AT91C_BCH_ECC_0_PMECC5    (0xFFFFE054)  // (BCH_ECC_0) PMECC BCH Redundancy  5 Register
#define AT91C_BCH_ECC_0_PMECC13   (0xFFFFE074)  // (BCH_ECC_0) PMECC BCH Redundancy 13 Register
#define AT91C_BCH_ECC_0_PMECC0    (0xFFFFE040)  // (BCH_ECC_0) PMECC BCH Redundancy  0 Register
#define AT91C_BCH_ECC_0_PMECC9    (0xFFFFE064)  // (BCH_ECC_0) PMECC BCH Redundancy  9 Register
#define AT91C_BCH_ECC_0_PMECC6    (0xFFFFE058)  // (BCH_ECC_0) PMECC BCH Redundancy  6 Register
// ========== Register definition for BCH_ECC_1 peripheral ========== 
#define AT91C_BCH_ECC_1_PMECC6    (0xFFFFE098)  // (BCH_ECC_1) PMECC BCH Redundancy  6 Register
#define AT91C_BCH_ECC_1_PMECC1    (0xFFFFE084)  // (BCH_ECC_1) PMECC BCH Redundancy  1 Register
#define AT91C_BCH_ECC_1_PMECC7    (0xFFFFE09C)  // (BCH_ECC_1) PMECC BCH Redundancy  7 Register
#define AT91C_BCH_ECC_1_PMECC10   (0xFFFFE0A8)  // (BCH_ECC_1) PMECC BCH Redundancy 10 Register
#define AT91C_BCH_ECC_1_PMECC2    (0xFFFFE088)  // (BCH_ECC_1) PMECC BCH Redundancy  2 Register
#define AT91C_BCH_ECC_1_PMECC14   (0xFFFFE0B8)  // (BCH_ECC_1) PMECC BCH Redundancy 14 Register
#define AT91C_BCH_ECC_1_PMECC8    (0xFFFFE0A0)  // (BCH_ECC_1) PMECC BCH Redundancy  8 Register
#define AT91C_BCH_ECC_1_PMECC3    (0xFFFFE08C)  // (BCH_ECC_1) PMECC BCH Redundancy  3 Register
#define AT91C_BCH_ECC_1_PMECC0    (0xFFFFE080)  // (BCH_ECC_1) PMECC BCH Redundancy  0 Register
#define AT91C_BCH_ECC_1_PMECC9    (0xFFFFE0A4)  // (BCH_ECC_1) PMECC BCH Redundancy  9 Register
#define AT91C_BCH_ECC_1_PMECC13   (0xFFFFE0B4)  // (BCH_ECC_1) PMECC BCH Redundancy 13 Register
#define AT91C_BCH_ECC_1_PMECC4    (0xFFFFE090)  // (BCH_ECC_1) PMECC BCH Redundancy  4 Register
#define AT91C_BCH_ECC_1_PMECC12   (0xFFFFE0B0)  // (BCH_ECC_1) PMECC BCH Redundancy 12 Register
#define AT91C_BCH_ECC_1_PMECC11   (0xFFFFE0AC)  // (BCH_ECC_1) PMECC BCH Redundancy 11 Register
#define AT91C_BCH_ECC_1_PMECC5    (0xFFFFE094)  // (BCH_ECC_1) PMECC BCH Redundancy  5 Register
#define AT91C_BCH_ECC_1_PMECC15   (0xFFFFE0BC)  // (BCH_ECC_1) PMECC BCH Redundancy 15 Register
// ========== Register definition for BCH_ECC_2 peripheral ========== 
#define AT91C_BCH_ECC_2_PMECC14   (0xFFFFE0F8)  // (BCH_ECC_2) PMECC BCH Redundancy 14 Register
#define AT91C_BCH_ECC_2_PMECC6    (0xFFFFE0D8)  // (BCH_ECC_2) PMECC BCH Redundancy  6 Register
#define AT91C_BCH_ECC_2_PMECC15   (0xFFFFE0FC)  // (BCH_ECC_2) PMECC BCH Redundancy 15 Register
#define AT91C_BCH_ECC_2_PMECC9    (0xFFFFE0E4)  // (BCH_ECC_2) PMECC BCH Redundancy  9 Register
#define AT91C_BCH_ECC_2_PMECC0    (0xFFFFE0C0)  // (BCH_ECC_2) PMECC BCH Redundancy  0 Register
#define AT91C_BCH_ECC_2_PMECC5    (0xFFFFE0D4)  // (BCH_ECC_2) PMECC BCH Redundancy  5 Register
#define AT91C_BCH_ECC_2_PMECC13   (0xFFFFE0F4)  // (BCH_ECC_2) PMECC BCH Redundancy 13 Register
#define AT91C_BCH_ECC_2_PMECC8    (0xFFFFE0E0)  // (BCH_ECC_2) PMECC BCH Redundancy  8 Register
#define AT91C_BCH_ECC_2_PMECC11   (0xFFFFE0EC)  // (BCH_ECC_2) PMECC BCH Redundancy 11 Register
#define AT91C_BCH_ECC_2_PMECC1    (0xFFFFE0C4)  // (BCH_ECC_2) PMECC BCH Redundancy  1 Register
#define AT91C_BCH_ECC_2_PMECC7    (0xFFFFE0DC)  // (BCH_ECC_2) PMECC BCH Redundancy  7 Register
#define AT91C_BCH_ECC_2_PMECC4    (0xFFFFE0D0)  // (BCH_ECC_2) PMECC BCH Redundancy  4 Register
#define AT91C_BCH_ECC_2_PMECC3    (0xFFFFE0CC)  // (BCH_ECC_2) PMECC BCH Redundancy  3 Register
#define AT91C_BCH_ECC_2_PMECC2    (0xFFFFE0C8)  // (BCH_ECC_2) PMECC BCH Redundancy  2 Register
#define AT91C_BCH_ECC_2_PMECC10   (0xFFFFE0E8)  // (BCH_ECC_2) PMECC BCH Redundancy 10 Register
#define AT91C_BCH_ECC_2_PMECC12   (0xFFFFE0F0)  // (BCH_ECC_2) PMECC BCH Redundancy 12 Register
// ========== Register definition for BCH_ECC_3 peripheral ========== 
#define AT91C_BCH_ECC_3_PMECC1    (0xFFFFE104)  // (BCH_ECC_3) PMECC BCH Redundancy  1 Register
#define AT91C_BCH_ECC_3_PMECC11   (0xFFFFE12C)  // (BCH_ECC_3) PMECC BCH Redundancy 11 Register
#define AT91C_BCH_ECC_3_PMECC15   (0xFFFFE13C)  // (BCH_ECC_3) PMECC BCH Redundancy 15 Register
#define AT91C_BCH_ECC_3_PMECC8    (0xFFFFE120)  // (BCH_ECC_3) PMECC BCH Redundancy  8 Register
#define AT91C_BCH_ECC_3_PMECC5    (0xFFFFE114)  // (BCH_ECC_3) PMECC BCH Redundancy  5 Register
#define AT91C_BCH_ECC_3_PMECC14   (0xFFFFE138)  // (BCH_ECC_3) PMECC BCH Redundancy 14 Register
#define AT91C_BCH_ECC_3_PMECC3    (0xFFFFE10C)  // (BCH_ECC_3) PMECC BCH Redundancy  3 Register
#define AT91C_BCH_ECC_3_PMECC12   (0xFFFFE130)  // (BCH_ECC_3) PMECC BCH Redundancy 12 Register
#define AT91C_BCH_ECC_3_PMECC10   (0xFFFFE128)  // (BCH_ECC_3) PMECC BCH Redundancy 10 Register
#define AT91C_BCH_ECC_3_PMECC2    (0xFFFFE108)  // (BCH_ECC_3) PMECC BCH Redundancy  2 Register
#define AT91C_BCH_ECC_3_PMECC13   (0xFFFFE134)  // (BCH_ECC_3) PMECC BCH Redundancy 13 Register
#define AT91C_BCH_ECC_3_PMECC4    (0xFFFFE110)  // (BCH_ECC_3) PMECC BCH Redundancy  4 Register
#define AT91C_BCH_ECC_3_PMECC7    (0xFFFFE11C)  // (BCH_ECC_3) PMECC BCH Redundancy  7 Register
#define AT91C_BCH_ECC_3_PMECC9    (0xFFFFE124)  // (BCH_ECC_3) PMECC BCH Redundancy  9 Register
#define AT91C_BCH_ECC_3_PMECC6    (0xFFFFE118)  // (BCH_ECC_3) PMECC BCH Redundancy  6 Register
#define AT91C_BCH_ECC_3_PMECC0    (0xFFFFE100)  // (BCH_ECC_3) PMECC BCH Redundancy  0 Register
// ========== Register definition for BCH_ECC_4 peripheral ========== 
#define AT91C_BCH_ECC_4_PMECC12   (0xFFFFE170)  // (BCH_ECC_4) PMECC BCH Redundancy 12 Register
#define AT91C_BCH_ECC_4_PMECC7    (0xFFFFE15C)  // (BCH_ECC_4) PMECC BCH Redundancy  7 Register
#define AT91C_BCH_ECC_4_PMECC9    (0xFFFFE164)  // (BCH_ECC_4) PMECC BCH Redundancy  9 Register
#define AT91C_BCH_ECC_4_PMECC10   (0xFFFFE168)  // (BCH_ECC_4) PMECC BCH Redundancy 10 Register
#define AT91C_BCH_ECC_4_PMECC4    (0xFFFFE150)  // (BCH_ECC_4) PMECC BCH Redundancy  4 Register
#define AT91C_BCH_ECC_4_PMECC14   (0xFFFFE178)  // (BCH_ECC_4) PMECC BCH Redundancy 14 Register
#define AT91C_BCH_ECC_4_PMECC11   (0xFFFFE16C)  // (BCH_ECC_4) PMECC BCH Redundancy 11 Register
#define AT91C_BCH_ECC_4_PMECC1    (0xFFFFE144)  // (BCH_ECC_4) PMECC BCH Redundancy  1 Register
#define AT91C_BCH_ECC_4_PMECC0    (0xFFFFE140)  // (BCH_ECC_4) PMECC BCH Redundancy  0 Register
#define AT91C_BCH_ECC_4_PMECC2    (0xFFFFE148)  // (BCH_ECC_4) PMECC BCH Redundancy  2 Register
#define AT91C_BCH_ECC_4_PMECC15   (0xFFFFE17C)  // (BCH_ECC_4) PMECC BCH Redundancy 15 Register
#define AT91C_BCH_ECC_4_PMECC13   (0xFFFFE174)  // (BCH_ECC_4) PMECC BCH Redundancy 13 Register
#define AT91C_BCH_ECC_4_PMECC5    (0xFFFFE154)  // (BCH_ECC_4) PMECC BCH Redundancy  5 Register
#define AT91C_BCH_ECC_4_PMECC6    (0xFFFFE158)  // (BCH_ECC_4) PMECC BCH Redundancy  6 Register
#define AT91C_BCH_ECC_4_PMECC8    (0xFFFFE160)  // (BCH_ECC_4) PMECC BCH Redundancy  8 Register
#define AT91C_BCH_ECC_4_PMECC3    (0xFFFFE14C)  // (BCH_ECC_4) PMECC BCH Redundancy  3 Register
// ========== Register definition for BCH_ECC_5 peripheral ========== 
#define AT91C_BCH_ECC_5_PMECC5    (0xFFFFE194)  // (BCH_ECC_5) PMECC BCH Redundancy  5 Register
#define AT91C_BCH_ECC_5_PMECC6    (0xFFFFE198)  // (BCH_ECC_5) PMECC BCH Redundancy  6 Register
#define AT91C_BCH_ECC_5_PMECC10   (0xFFFFE1A8)  // (BCH_ECC_5) PMECC BCH Redundancy 10 Register
#define AT91C_BCH_ECC_5_PMECC4    (0xFFFFE190)  // (BCH_ECC_5) PMECC BCH Redundancy  4 Register
#define AT91C_BCH_ECC_5_PMECC2    (0xFFFFE188)  // (BCH_ECC_5) PMECC BCH Redundancy  2 Register
#define AT91C_BCH_ECC_5_PMECC12   (0xFFFFE1B0)  // (BCH_ECC_5) PMECC BCH Redundancy 12 Register
#define AT91C_BCH_ECC_5_PMECC13   (0xFFFFE1B4)  // (BCH_ECC_5) PMECC BCH Redundancy 13 Register
#define AT91C_BCH_ECC_5_PMECC9    (0xFFFFE1A4)  // (BCH_ECC_5) PMECC BCH Redundancy  9 Register
#define AT91C_BCH_ECC_5_PMECC15   (0xFFFFE1BC)  // (BCH_ECC_5) PMECC BCH Redundancy 15 Register
#define AT91C_BCH_ECC_5_PMECC8    (0xFFFFE1A0)  // (BCH_ECC_5) PMECC BCH Redundancy  8 Register
#define AT91C_BCH_ECC_5_PMECC1    (0xFFFFE184)  // (BCH_ECC_5) PMECC BCH Redundancy  1 Register
#define AT91C_BCH_ECC_5_PMECC3    (0xFFFFE18C)  // (BCH_ECC_5) PMECC BCH Redundancy  3 Register
#define AT91C_BCH_ECC_5_PMECC0    (0xFFFFE180)  // (BCH_ECC_5) PMECC BCH Redundancy  0 Register
#define AT91C_BCH_ECC_5_PMECC11   (0xFFFFE1AC)  // (BCH_ECC_5) PMECC BCH Redundancy 11 Register
#define AT91C_BCH_ECC_5_PMECC14   (0xFFFFE1B8)  // (BCH_ECC_5) PMECC BCH Redundancy 14 Register
#define AT91C_BCH_ECC_5_PMECC7    (0xFFFFE19C)  // (BCH_ECC_5) PMECC BCH Redundancy  7 Register
// ========== Register definition for BCH_ECC_6 peripheral ========== 
#define AT91C_BCH_ECC_6_PMECC10   (0xFFFFE1E8)  // (BCH_ECC_6) PMECC BCH Redundancy 10 Register
#define AT91C_BCH_ECC_6_PMECC8    (0xFFFFE1E0)  // (BCH_ECC_6) PMECC BCH Redundancy  8 Register
#define AT91C_BCH_ECC_6_PMECC4    (0xFFFFE1D0)  // (BCH_ECC_6) PMECC BCH Redundancy  4 Register
#define AT91C_BCH_ECC_6_PMECC14   (0xFFFFE1F8)  // (BCH_ECC_6) PMECC BCH Redundancy 14 Register
#define AT91C_BCH_ECC_6_PMECC13   (0xFFFFE1F4)  // (BCH_ECC_6) PMECC BCH Redundancy 13 Register
#define AT91C_BCH_ECC_6_PMECC2    (0xFFFFE1C8)  // (BCH_ECC_6) PMECC BCH Redundancy  2 Register
#define AT91C_BCH_ECC_6_PMECC0    (0xFFFFE1C0)  // (BCH_ECC_6) PMECC BCH Redundancy  0 Register
#define AT91C_BCH_ECC_6_PMECC3    (0xFFFFE1CC)  // (BCH_ECC_6) PMECC BCH Redundancy  3 Register
#define AT91C_BCH_ECC_6_PMECC11   (0xFFFFE1EC)  // (BCH_ECC_6) PMECC BCH Redundancy 11 Register
#define AT91C_BCH_ECC_6_PMECC6    (0xFFFFE1D8)  // (BCH_ECC_6) PMECC BCH Redundancy  6 Register
#define AT91C_BCH_ECC_6_PMECC7    (0xFFFFE1DC)  // (BCH_ECC_6) PMECC BCH Redundancy  7 Register
#define AT91C_BCH_ECC_6_PMECC15   (0xFFFFE1FC)  // (BCH_ECC_6) PMECC BCH Redundancy 15 Register
#define AT91C_BCH_ECC_6_PMECC12   (0xFFFFE1F0)  // (BCH_ECC_6) PMECC BCH Redundancy 12 Register
#define AT91C_BCH_ECC_6_PMECC9    (0xFFFFE1E4)  // (BCH_ECC_6) PMECC BCH Redundancy  9 Register
#define AT91C_BCH_ECC_6_PMECC1    (0xFFFFE1C4)  // (BCH_ECC_6) PMECC BCH Redundancy  1 Register
#define AT91C_BCH_ECC_6_PMECC5    (0xFFFFE1D4)  // (BCH_ECC_6) PMECC BCH Redundancy  5 Register
// ========== Register definition for BCH_ECC_7 peripheral ========== 
#define AT91C_BCH_ECC_7_PMECC7    (0xFFFFE21C)  // (BCH_ECC_7) PMECC BCH Redundancy  7 Register
#define AT91C_BCH_ECC_7_PMECC3    (0xFFFFE20C)  // (BCH_ECC_7) PMECC BCH Redundancy  3 Register
#define AT91C_BCH_ECC_7_PMECC1    (0xFFFFE204)  // (BCH_ECC_7) PMECC BCH Redundancy  1 Register
#define AT91C_BCH_ECC_7_PMECC13   (0xFFFFE234)  // (BCH_ECC_7) PMECC BCH Redundancy 13 Register
#define AT91C_BCH_ECC_7_PMECC11   (0xFFFFE22C)  // (BCH_ECC_7) PMECC BCH Redundancy 11 Register
#define AT91C_BCH_ECC_7_PMECC2    (0xFFFFE208)  // (BCH_ECC_7) PMECC BCH Redundancy  2 Register
#define AT91C_BCH_ECC_7_PMECC0    (0xFFFFE200)  // (BCH_ECC_7) PMECC BCH Redundancy  0 Register
#define AT91C_BCH_ECC_7_PMECC4    (0xFFFFE210)  // (BCH_ECC_7) PMECC BCH Redundancy  4 Register
#define AT91C_BCH_ECC_7_PMECC9    (0xFFFFE224)  // (BCH_ECC_7) PMECC BCH Redundancy  9 Register
#define AT91C_BCH_ECC_7_PMECC14   (0xFFFFE238)  // (BCH_ECC_7) PMECC BCH Redundancy 14 Register
#define AT91C_BCH_ECC_7_PMECC6    (0xFFFFE218)  // (BCH_ECC_7) PMECC BCH Redundancy  6 Register
#define AT91C_BCH_ECC_7_PMECC10   (0xFFFFE228)  // (BCH_ECC_7) PMECC BCH Redundancy 10 Register
#define AT91C_BCH_ECC_7_PMECC15   (0xFFFFE23C)  // (BCH_ECC_7) PMECC BCH Redundancy 15 Register
#define AT91C_BCH_ECC_7_PMECC8    (0xFFFFE220)  // (BCH_ECC_7) PMECC BCH Redundancy  8 Register
#define AT91C_BCH_ECC_7_PMECC5    (0xFFFFE214)  // (BCH_ECC_7) PMECC BCH Redundancy  5 Register
#define AT91C_BCH_ECC_7_PMECC12   (0xFFFFE230)  // (BCH_ECC_7) PMECC BCH Redundancy 12 Register
// ========== Register definition for BCH_SYN_0 peripheral ========== 
#define AT91C_BCH_SYN_0_PMECCSYN10 (0xFFFFE268) // (BCH_SYN_0) PMECC Syndrome 10 Register
#define AT91C_BCH_SYN_0_PMECCSYN9 (0xFFFFE264)  // (BCH_SYN_0) PMECC Syndrome  9 Register
#define AT91C_BCH_SYN_0_Reserved  (0xFFFFE270)  // (BCH_SYN_0) Reserved
#define AT91C_BCH_SYN_0_PMECCSYN0 (0xFFFFE240)  // (BCH_SYN_0) PMECC Syndrome  0 Register
#define AT91C_BCH_SYN_0_PMECCSYN3 (0xFFFFE24C)  // (BCH_SYN_0) PMECC Syndrome  3 Register
#define AT91C_BCH_SYN_0_PMECCSYN7 (0xFFFFE25C)  // (BCH_SYN_0) PMECC Syndrome  7 Register
#define AT91C_BCH_SYN_0_PMECCSYN8 (0xFFFFE260)  // (BCH_SYN_0) PMECC Syndrome  8 Register
#define AT91C_BCH_SYN_0_PMECCSYN1 (0xFFFFE244)  // (BCH_SYN_0) PMECC Syndrome  1 Register
#define AT91C_BCH_SYN_0_PMECCSYN2 (0xFFFFE248)  // (BCH_SYN_0) PMECC Syndrome  2 Register
#define AT91C_BCH_SYN_0_PMECCSYN5 (0xFFFFE254)  // (BCH_SYN_0) PMECC Syndrome  5 Register
#define AT91C_BCH_SYN_0_PMECCSYN11 (0xFFFFE26C) // (BCH_SYN_0) PMECC Syndrome 11 Register
#define AT91C_BCH_SYN_0_PMECCSYN4 (0xFFFFE250)  // (BCH_SYN_0) PMECC Syndrome  4 Register
#define AT91C_BCH_SYN_0_PMECCSYN6 (0xFFFFE258)  // (BCH_SYN_0) PMECC Syndrome  6 Register
// ========== Register definition for BCH_SYN_1 peripheral ========== 
#define AT91C_BCH_SYN_1_Reserved  (0xFFFFE2B0)  // (BCH_SYN_1) Reserved
#define AT91C_BCH_SYN_1_PMECCSYN9 (0xFFFFE2A4)  // (BCH_SYN_1) PMECC Syndrome  9 Register
#define AT91C_BCH_SYN_1_PMECCSYN4 (0xFFFFE290)  // (BCH_SYN_1) PMECC Syndrome  4 Register
#define AT91C_BCH_SYN_1_PMECCSYN0 (0xFFFFE280)  // (BCH_SYN_1) PMECC Syndrome  0 Register
#define AT91C_BCH_SYN_1_PMECCSYN2 (0xFFFFE288)  // (BCH_SYN_1) PMECC Syndrome  2 Register
#define AT91C_BCH_SYN_1_PMECCSYN11 (0xFFFFE2AC) // (BCH_SYN_1) PMECC Syndrome 11 Register
#define AT91C_BCH_SYN_1_PMECCSYN5 (0xFFFFE294)  // (BCH_SYN_1) PMECC Syndrome  5 Register
#define AT91C_BCH_SYN_1_PMECCSYN1 (0xFFFFE284)  // (BCH_SYN_1) PMECC Syndrome  1 Register
#define AT91C_BCH_SYN_1_PMECCSYN7 (0xFFFFE29C)  // (BCH_SYN_1) PMECC Syndrome  7 Register
#define AT91C_BCH_SYN_1_PMECCSYN10 (0xFFFFE2A8) // (BCH_SYN_1) PMECC Syndrome 10 Register
#define AT91C_BCH_SYN_1_PMECCSYN6 (0xFFFFE298)  // (BCH_SYN_1) PMECC Syndrome  6 Register
#define AT91C_BCH_SYN_1_PMECCSYN3 (0xFFFFE28C)  // (BCH_SYN_1) PMECC Syndrome  3 Register
#define AT91C_BCH_SYN_1_PMECCSYN8 (0xFFFFE2A0)  // (BCH_SYN_1) PMECC Syndrome  8 Register
// ========== Register definition for BCH_SYN_2 peripheral ========== 
#define AT91C_BCH_SYN_2_PMECCSYN10 (0xFFFFE2E8) // (BCH_SYN_2) PMECC Syndrome 10 Register
#define AT91C_BCH_SYN_2_PMECCSYN9 (0xFFFFE2E4)  // (BCH_SYN_2) PMECC Syndrome  9 Register
#define AT91C_BCH_SYN_2_PMECCSYN1 (0xFFFFE2C4)  // (BCH_SYN_2) PMECC Syndrome  1 Register
#define AT91C_BCH_SYN_2_PMECCSYN11 (0xFFFFE2EC) // (BCH_SYN_2) PMECC Syndrome 11 Register
#define AT91C_BCH_SYN_2_Reserved  (0xFFFFE2F0)  // (BCH_SYN_2) Reserved
#define AT91C_BCH_SYN_2_PMECCSYN8 (0xFFFFE2E0)  // (BCH_SYN_2) PMECC Syndrome  8 Register
#define AT91C_BCH_SYN_2_PMECCSYN2 (0xFFFFE2C8)  // (BCH_SYN_2) PMECC Syndrome  2 Register
#define AT91C_BCH_SYN_2_PMECCSYN6 (0xFFFFE2D8)  // (BCH_SYN_2) PMECC Syndrome  6 Register
#define AT91C_BCH_SYN_2_PMECCSYN0 (0xFFFFE2C0)  // (BCH_SYN_2) PMECC Syndrome  0 Register
#define AT91C_BCH_SYN_2_PMECCSYN5 (0xFFFFE2D4)  // (BCH_SYN_2) PMECC Syndrome  5 Register
#define AT91C_BCH_SYN_2_PMECCSYN3 (0xFFFFE2CC)  // (BCH_SYN_2) PMECC Syndrome  3 Register
#define AT91C_BCH_SYN_2_PMECCSYN7 (0xFFFFE2DC)  // (BCH_SYN_2) PMECC Syndrome  7 Register
#define AT91C_BCH_SYN_2_PMECCSYN4 (0xFFFFE2D0)  // (BCH_SYN_2) PMECC Syndrome  4 Register
// ========== Register definition for BCH_SYN_3 peripheral ========== 
#define AT91C_BCH_SYN_3_PMECCSYN8 (0xFFFFE320)  // (BCH_SYN_3) PMECC Syndrome  8 Register
#define AT91C_BCH_SYN_3_PMECCSYN5 (0xFFFFE314)  // (BCH_SYN_3) PMECC Syndrome  5 Register
#define AT91C_BCH_SYN_3_PMECCSYN0 (0xFFFFE300)  // (BCH_SYN_3) PMECC Syndrome  0 Register
#define AT91C_BCH_SYN_3_PMECCSYN10 (0xFFFFE328) // (BCH_SYN_3) PMECC Syndrome 10 Register
#define AT91C_BCH_SYN_3_PMECCSYN6 (0xFFFFE318)  // (BCH_SYN_3) PMECC Syndrome  6 Register
#define AT91C_BCH_SYN_3_Reserved  (0xFFFFE330)  // (BCH_SYN_3) Reserved
#define AT91C_BCH_SYN_3_PMECCSYN4 (0xFFFFE310)  // (BCH_SYN_3) PMECC Syndrome  4 Register
#define AT91C_BCH_SYN_3_PMECCSYN7 (0xFFFFE31C)  // (BCH_SYN_3) PMECC Syndrome  7 Register
#define AT91C_BCH_SYN_3_PMECCSYN3 (0xFFFFE30C)  // (BCH_SYN_3) PMECC Syndrome  3 Register
#define AT91C_BCH_SYN_3_PMECCSYN11 (0xFFFFE32C) // (BCH_SYN_3) PMECC Syndrome 11 Register
#define AT91C_BCH_SYN_3_PMECCSYN9 (0xFFFFE324)  // (BCH_SYN_3) PMECC Syndrome  9 Register
#define AT91C_BCH_SYN_3_PMECCSYN2 (0xFFFFE308)  // (BCH_SYN_3) PMECC Syndrome  2 Register
#define AT91C_BCH_SYN_3_PMECCSYN1 (0xFFFFE304)  // (BCH_SYN_3) PMECC Syndrome  1 Register
// ========== Register definition for BCH_SYN_4 peripheral ========== 
#define AT91C_BCH_SYN_4_PMECCSYN3 (0xFFFFE34C)  // (BCH_SYN_4) PMECC Syndrome  3 Register
#define AT91C_BCH_SYN_4_PMECCSYN8 (0xFFFFE360)  // (BCH_SYN_4) PMECC Syndrome  8 Register
#define AT91C_BCH_SYN_4_PMECCSYN4 (0xFFFFE350)  // (BCH_SYN_4) PMECC Syndrome  4 Register
#define AT91C_BCH_SYN_4_PMECCSYN2 (0xFFFFE348)  // (BCH_SYN_4) PMECC Syndrome  2 Register
#define AT91C_BCH_SYN_4_PMECCSYN1 (0xFFFFE344)  // (BCH_SYN_4) PMECC Syndrome  1 Register
#define AT91C_BCH_SYN_4_PMECCSYN9 (0xFFFFE364)  // (BCH_SYN_4) PMECC Syndrome  9 Register
#define AT91C_BCH_SYN_4_PMECCSYN10 (0xFFFFE368) // (BCH_SYN_4) PMECC Syndrome 10 Register
#define AT91C_BCH_SYN_4_PMECCSYN6 (0xFFFFE358)  // (BCH_SYN_4) PMECC Syndrome  6 Register
#define AT91C_BCH_SYN_4_PMECCSYN11 (0xFFFFE36C) // (BCH_SYN_4) PMECC Syndrome 11 Register
#define AT91C_BCH_SYN_4_PMECCSYN5 (0xFFFFE354)  // (BCH_SYN_4) PMECC Syndrome  5 Register
#define AT91C_BCH_SYN_4_Reserved  (0xFFFFE370)  // (BCH_SYN_4) Reserved
#define AT91C_BCH_SYN_4_PMECCSYN0 (0xFFFFE340)  // (BCH_SYN_4) PMECC Syndrome  0 Register
#define AT91C_BCH_SYN_4_PMECCSYN7 (0xFFFFE35C)  // (BCH_SYN_4) PMECC Syndrome  7 Register
// ========== Register definition for BCH_SYN_5 peripheral ========== 
#define AT91C_BCH_SYN_5_PMECCSYN8 (0xFFFFE3A0)  // (BCH_SYN_5) PMECC Syndrome  8 Register
#define AT91C_BCH_SYN_5_PMECCSYN2 (0xFFFFE388)  // (BCH_SYN_5) PMECC Syndrome  2 Register
#define AT91C_BCH_SYN_5_Reserved  (0xFFFFE3B0)  // (BCH_SYN_5) Reserved
#define AT91C_BCH_SYN_5_PMECCSYN7 (0xFFFFE39C)  // (BCH_SYN_5) PMECC Syndrome  7 Register
#define AT91C_BCH_SYN_5_PMECCSYN1 (0xFFFFE384)  // (BCH_SYN_5) PMECC Syndrome  1 Register
#define AT91C_BCH_SYN_5_PMECCSYN6 (0xFFFFE398)  // (BCH_SYN_5) PMECC Syndrome  6 Register
#define AT91C_BCH_SYN_5_PMECCSYN0 (0xFFFFE380)  // (BCH_SYN_5) PMECC Syndrome  0 Register
#define AT91C_BCH_SYN_5_PMECCSYN9 (0xFFFFE3A4)  // (BCH_SYN_5) PMECC Syndrome  9 Register
#define AT91C_BCH_SYN_5_PMECCSYN4 (0xFFFFE390)  // (BCH_SYN_5) PMECC Syndrome  4 Register
#define AT91C_BCH_SYN_5_PMECCSYN10 (0xFFFFE3A8) // (BCH_SYN_5) PMECC Syndrome 10 Register
#define AT91C_BCH_SYN_5_PMECCSYN5 (0xFFFFE394)  // (BCH_SYN_5) PMECC Syndrome  5 Register
#define AT91C_BCH_SYN_5_PMECCSYN11 (0xFFFFE3AC) // (BCH_SYN_5) PMECC Syndrome 11 Register
#define AT91C_BCH_SYN_5_PMECCSYN3 (0xFFFFE38C)  // (BCH_SYN_5) PMECC Syndrome  3 Register
// ========== Register definition for BCH_SYN_6 peripheral ========== 
#define AT91C_BCH_SYN_6_PMECCSYN6 (0xFFFFE3D8)  // (BCH_SYN_6) PMECC Syndrome  6 Register
#define AT91C_BCH_SYN_6_PMECCSYN9 (0xFFFFE3E4)  // (BCH_SYN_6) PMECC Syndrome  9 Register
#define AT91C_BCH_SYN_6_PMECCSYN1 (0xFFFFE3C4)  // (BCH_SYN_6) PMECC Syndrome  1 Register
#define AT91C_BCH_SYN_6_Reserved  (0xFFFFE3F0)  // (BCH_SYN_6) Reserved
#define AT91C_BCH_SYN_6_PMECCSYN11 (0xFFFFE3EC) // (BCH_SYN_6) PMECC Syndrome 11 Register
#define AT91C_BCH_SYN_6_PMECCSYN8 (0xFFFFE3E0)  // (BCH_SYN_6) PMECC Syndrome  8 Register
#define AT91C_BCH_SYN_6_PMECCSYN5 (0xFFFFE3D4)  // (BCH_SYN_6) PMECC Syndrome  5 Register
#define AT91C_BCH_SYN_6_PMECCSYN4 (0xFFFFE3D0)  // (BCH_SYN_6) PMECC Syndrome  4 Register
#define AT91C_BCH_SYN_6_PMECCSYN3 (0xFFFFE3CC)  // (BCH_SYN_6) PMECC Syndrome  3 Register
#define AT91C_BCH_SYN_6_PMECCSYN10 (0xFFFFE3E8) // (BCH_SYN_6) PMECC Syndrome 10 Register
#define AT91C_BCH_SYN_6_PMECCSYN0 (0xFFFFE3C0)  // (BCH_SYN_6) PMECC Syndrome  0 Register
#define AT91C_BCH_SYN_6_PMECCSYN2 (0xFFFFE3C8)  // (BCH_SYN_6) PMECC Syndrome  2 Register
#define AT91C_BCH_SYN_6_PMECCSYN7 (0xFFFFE3DC)  // (BCH_SYN_6) PMECC Syndrome  7 Register
// ========== Register definition for BCH_SYN_7 peripheral ========== 
#define AT91C_BCH_SYN_7_PMECCSYN10 (0xFFFFE428) // (BCH_SYN_7) PMECC Syndrome 10 Register
#define AT91C_BCH_SYN_7_PMECCSYN7 (0xFFFFE41C)  // (BCH_SYN_7) PMECC Syndrome  7 Register
#define AT91C_BCH_SYN_7_PMECCSYN2 (0xFFFFE408)  // (BCH_SYN_7) PMECC Syndrome  2 Register
#define AT91C_BCH_SYN_7_PMECCSYN6 (0xFFFFE418)  // (BCH_SYN_7) PMECC Syndrome  6 Register
#define AT91C_BCH_SYN_7_PMECCSYN0 (0xFFFFE400)  // (BCH_SYN_7) PMECC Syndrome  0 Register
#define AT91C_BCH_SYN_7_PMECCSYN11 (0xFFFFE42C) // (BCH_SYN_7) PMECC Syndrome 11 Register
#define AT91C_BCH_SYN_7_PMECCSYN5 (0xFFFFE414)  // (BCH_SYN_7) PMECC Syndrome  5 Register
#define AT91C_BCH_SYN_7_PMECCSYN8 (0xFFFFE420)  // (BCH_SYN_7) PMECC Syndrome  8 Register
#define AT91C_BCH_SYN_7_PMECCSYN1 (0xFFFFE404)  // (BCH_SYN_7) PMECC Syndrome  1 Register
#define AT91C_BCH_SYN_7_Reserved  (0xFFFFE430)  // (BCH_SYN_7) Reserved
#define AT91C_BCH_SYN_7_PMECCSYN3 (0xFFFFE40C)  // (BCH_SYN_7) PMECC Syndrome  3 Register
#define AT91C_BCH_SYN_7_PMECCSYN9 (0xFFFFE424)  // (BCH_SYN_7) PMECC Syndrome  9 Register
#define AT91C_BCH_SYN_7_PMECCSYN4 (0xFFFFE410)  // (BCH_SYN_7) PMECC Syndrome  4 Register
// ========== Register definition for BCH peripheral ========== 
#define AT91C_BCH_PMECCTRL        (0xFFFFE014)  // (BCH) PMECC Control Register
#define AT91C_BCH_PMECCSR         (0xFFFFE018)  // (BCH) PMECC Status Register
#define AT91C_BCH_PMECCFG0        (0xFFFFE000)  // (BCH) PMECC Configuration 0 Register
#define AT91C_BCH_PMECCIER        (0xFFFFE01C)  // (BCH) PMECC Interrupt Enable Register
#define AT91C_BCH_PMECCFG1        (0xFFFFE004)  // (BCH) PMECC Configuration 1 Register
#define AT91C_BCH_PMECCFG4        (0xFFFFE010)  // (BCH) PMECC Configuration 4 Register
#define AT91C_BCH_PMECCFG2        (0xFFFFE008)  // (BCH) PMECC Configuration 2 Register
#define AT91C_BCH_PMECCISR        (0xFFFFE028)  // (BCH) PMECC Interrupt Status Register
#define AT91C_BCH_PMECCIMR        (0xFFFFE024)  // (BCH) PMECC Interrupt Mask Register
#define AT91C_BCH_PMECCFG3        (0xFFFFE00C)  // (BCH) PMECC Configuration 3 Register
#define AT91C_BCH_PMECCIDR        (0xFFFFE020)  // (BCH) PMECC Interrupt Disable Register
// ========== Register definition for BCHEL peripheral ========== 
#define AT91C_BCHEL_PMECCELSIG16  (0xFFFFE668)  // (BCHEL) PMECC Error Location Sigma 16 Register
#define AT91C_BCHEL_PMECCELSIG10  (0xFFFFE650)  // (BCHEL) PMECC Error Location Sigma 10 Register
#define AT91C_BCHEL_PMECCELSIG9   (0xFFFFE64C)  // (BCHEL) PMECC Error Location Sigma  9 Register
#define AT91C_BCHEL_PMECCELSIG0   (0xFFFFE628)  // (BCHEL) PMECC Error Location Sigma  0 Register
#define AT91C_BCHEL_PMECCELPR     (0xFFFFE604)  // (BCHEL) PMECC Error Location Primitiv          Register
#define AT91C_BCHEL_PMECCELDR     (0xFFFFE60C)  // (BCHEL) PMECC Error Location Disable           Register
#define AT91C_BCHEL_PMECCELSIG20  (0xFFFFE678)  // (BCHEL) PMECC Error Location Sigma 20 Register
#define AT91C_BCHEL_PMECCELERR14  (0xFFFFE6C0)  // (BCHEL) PMECC Error Location Error position 14 Register
#define AT91C_BCHEL_PMECCELERR9   (0xFFFFE6AC)  // (BCHEL) PMECC Error Location Error position  9 Register
#define AT91C_BCHEL_PMECCELERR5   (0xFFFFE69C)  // (BCHEL) PMECC Error Location Error position  5 Register
#define AT91C_BCHEL_PMECCELIER    (0xFFFFE614)  // (BCHEL) PMECC Error Location Interrupt Enable  Register
#define AT91C_BCHEL_PMECCELERR16  (0xFFFFE6C8)  // (BCHEL) PMECC Error Location Error position 16 Register
#define AT91C_BCHEL_PMECCELSIG14  (0xFFFFE660)  // (BCHEL) PMECC Error Location Sigma 14 Register
#define AT91C_BCHEL_PMECCELERR13  (0xFFFFE6BC)  // (BCHEL) PMECC Error Location Error position 13 Register
#define AT91C_BCHEL_PMECCELERR21  (0xFFFFE6DC)  // (BCHEL) PMECC Error Location Error position 21 Register
#define AT91C_BCHEL_PMECCELERR17  (0xFFFFE6CC)  // (BCHEL) PMECC Error Location Error position 17 Register
#define AT91C_BCHEL_PMECCELSIG23  (0xFFFFE684)  // (BCHEL) PMECC Error Location Sigma 23 Register
#define AT91C_BCHEL_PMECCELERR6   (0xFFFFE6A0)  // (BCHEL) PMECC Error Location Error position  6 Register
#define AT91C_BCHEL_PMECCELSIG13  (0xFFFFE65C)  // (BCHEL) PMECC Error Location Sigma 13 Register
#define AT91C_BCHEL_PMECCELCR     (0xFFFFE600)  // (BCHEL) PMECC Error Location Configuration     Register
#define AT91C_BCHEL_PMECCELERR20  (0xFFFFE6D8)  // (BCHEL) PMECC Error Location Error position 20 Register
#define AT91C_BCHEL_PMECCELERR8   (0xFFFFE6A8)  // (BCHEL) PMECC Error Location Error position  8 Register
#define AT91C_BCHEL_PMECCELERR7   (0xFFFFE6A4)  // (BCHEL) PMECC Error Location Error position  7 Register
#define AT91C_BCHEL_PMECCELERR12  (0xFFFFE6B8)  // (BCHEL) PMECC Error Location Error position 12 Register
#define AT91C_BCHEL_PMECCELSIG6   (0xFFFFE640)  // (BCHEL) PMECC Error Location Sigma  6 Register
#define AT91C_BCHEL_PMECCELERR22  (0xFFFFE6E0)  // (BCHEL) PMECC Error Location Error position 22 Register
#define AT91C_BCHEL_PMECCELERR18  (0xFFFFE6D0)  // (BCHEL) PMECC Error Location Error position 18 Register
#define AT91C_BCHEL_PMECCELIMR    (0xFFFFE61C)  // (BCHEL) PMECC Error Location Interrupt Mask    Register
#define AT91C_BCHEL_PMECCELERR4   (0xFFFFE698)  // (BCHEL) PMECC Error Location Error position  4 Register
#define AT91C_BCHEL_PMECCELERR1   (0xFFFFE68C)  // (BCHEL) PMECC Error Location Error position  1 Register
#define AT91C_BCHEL_PMECCELSIG1   (0xFFFFE62C)  // (BCHEL) PMECC Error Location Sigma  1 Register
#define AT91C_BCHEL_PMECCELSIG3   (0xFFFFE634)  // (BCHEL) PMECC Error Location Sigma  3 Register
#define AT91C_BCHEL_PMECCELSIG11  (0xFFFFE654)  // (BCHEL) PMECC Error Location Sigma 11 Register
#define AT91C_BCHEL_PMECCELSIG19  (0xFFFFE674)  // (BCHEL) PMECC Error Location Sigma 19 Register
#define AT91C_BCHEL_PMECCELERR19  (0xFFFFE6D4)  // (BCHEL) PMECC Error Location Error position 19 Register
#define AT91C_BCHEL_PMECCELSIG15  (0xFFFFE664)  // (BCHEL) PMECC Error Location Sigma 15 Register
#define AT91C_BCHEL_PMECCELERR0   (0xFFFFE688)  // (BCHEL) PMECC Error Location Error position  0 Register
#define AT91C_BCHEL_PMECCELSR     (0xFFFFE610)  // (BCHEL) PMECC Error Location Status            Register
#define AT91C_BCHEL_PMECCELSIG2   (0xFFFFE630)  // (BCHEL) PMECC Error Location Sigma  2 Register
#define AT91C_BCHEL_PMECCELERR11  (0xFFFFE6B4)  // (BCHEL) PMECC Error Location Error position 11 Register
#define AT91C_BCHEL_PMECCELISR    (0xFFFFE620)  // (BCHEL) PMECC Error Location Interrupt Status  Register
#define AT91C_BCHEL_PMECCELSIG12  (0xFFFFE658)  // (BCHEL) PMECC Error Location Sigma 12 Register
#define AT91C_BCHEL_PMECCELSIG7   (0xFFFFE644)  // (BCHEL) PMECC Error Location Sigma  7 Register
#define AT91C_BCHEL_PMECCELERR10  (0xFFFFE6B0)  // (BCHEL) PMECC Error Location Error position 10 Register
#define AT91C_BCHEL_PMECCELSIG18  (0xFFFFE670)  // (BCHEL) PMECC Error Location Sigma 18 Register
#define AT91C_BCHEL_PMECCELSIG5   (0xFFFFE63C)  // (BCHEL) PMECC Error Location Sigma  5 Register
#define AT91C_BCHEL_PMECCELERR3   (0xFFFFE694)  // (BCHEL) PMECC Error Location Error position  3 Register
#define AT91C_BCHEL_PMECCELERR2   (0xFFFFE690)  // (BCHEL) PMECC Error Location Error position  2 Register
#define AT91C_BCHEL_PMECCELERR23  (0xFFFFE6E4)  // (BCHEL) PMECC Error Location Error position 23 Register
#define AT91C_BCHEL_PMECCELSIG4   (0xFFFFE638)  // (BCHEL) PMECC Error Location Sigma  4 Register
#define AT91C_BCHEL_PMECCELER     (0xFFFFE608)  // (BCHEL) PMECC Error Location Enable            Register
#define AT91C_BCHEL_PMECCELERR15  (0xFFFFE6C4)  // (BCHEL) PMECC Error Location Error position 15 Register
#define AT91C_BCHEL_PMECCELIDR    (0xFFFFE618)  // (BCHEL) PMECC Error Location Interrupt Disable Register
#define AT91C_BCHEL_PMECCELSIG8   (0xFFFFE648)  // (BCHEL) PMECC Error Location Sigma  8 Register
#define AT91C_BCHEL_PMECCELSIG21  (0xFFFFE67C)  // (BCHEL) PMECC Error Location Sigma 21 Register
#define AT91C_BCHEL_PMECCELSIG17  (0xFFFFE66C)  // (BCHEL) PMECC Error Location Sigma 17 Register
#define AT91C_BCHEL_PMECCELSIG22  (0xFFFFE680)  // (BCHEL) PMECC Error Location Sigma 22 Register
// ========== Register definition for EMACB0 peripheral ========== 
#define AT91C_EMACB0_ELE          (0xF802C078)  // (EMACB0) Excessive Length Errors Register
#define AT91C_EMACB0_HRT          (0xF802C094)  // (EMACB0) Hash Address Top[63:32]
#define AT91C_EMACB0_NCFGR        (0xF802C004)  // (EMACB0) Network Configuration Register
#define AT91C_EMACB0_TPQ          (0xF802C0BC)  // (EMACB0) Transmit Pause Quantum Register
#define AT91C_EMACB0_ROV          (0xF802C070)  // (EMACB0) Receive Overrun Errors Register
#define AT91C_EMACB0_ALE          (0xF802C054)  // (EMACB0) Alignment Error Register
#define AT91C_EMACB0_SA4H         (0xF802C0B4)  // (EMACB0) Specific Address 4 Top, Last 2 bytes
#define AT91C_EMACB0_RJA          (0xF802C07C)  // (EMACB0) Receive Jabbers Register
#define AT91C_EMACB0_FCSE         (0xF802C050)  // (EMACB0) Frame Check Sequence Error Register
#define AT91C_EMACB0_RBQP         (0xF802C018)  // (EMACB0) Receive Buffer Queue Pointer
#define AT91C_EMACB0_STE          (0xF802C084)  // (EMACB0) SQE Test Error Register
#define AT91C_EMACB0_SA3H         (0xF802C0AC)  // (EMACB0) Specific Address 3 Top, Last 2 bytes
#define AT91C_EMACB0_ISR          (0xF802C024)  // (EMACB0) Interrupt Status Register
#define AT91C_EMACB0_NCR          (0xF802C000)  // (EMACB0) Network Control Register
#define AT91C_EMACB0_TSR          (0xF802C014)  // (EMACB0) Transmit Status Register
#define AT91C_EMACB0_RSR          (0xF802C020)  // (EMACB0) Receive Status Register
#define AT91C_EMACB0_SA1H         (0xF802C09C)  // (EMACB0) Specific Address 1 Top, Last 2 bytes
#define AT91C_EMACB0_DTF          (0xF802C058)  // (EMACB0) Deferred Transmission Frame Register
#define AT91C_EMACB0_MCF          (0xF802C048)  // (EMACB0) Multiple Collision Frame Register
#define AT91C_EMACB0_SA2L         (0xF802C0A0)  // (EMACB0) Specific Address 2 Bottom, First 4 bytes
#define AT91C_EMACB0_USRIO        (0xF802C0C0)  // (EMACB0) USER Input/Output Register
#define AT91C_EMACB0_IMR          (0xF802C030)  // (EMACB0) Interrupt Mask Register
#define AT91C_EMACB0_REV          (0xF802C0FC)  // (EMACB0) Revision Register
#define AT91C_EMACB0_ECOL         (0xF802C060)  // (EMACB0) Excessive Collision Register
#define AT91C_EMACB0_RSE          (0xF802C074)  // (EMACB0) Receive Symbol Errors Register
#define AT91C_EMACB0_IDR          (0xF802C02C)  // (EMACB0) Interrupt Disable Register
#define AT91C_EMACB0_PTR          (0xF802C038)  // (EMACB0) Pause Time Register
#define AT91C_EMACB0_RLE          (0xF802C088)  // (EMACB0) Receive Length Field Mismatch Register
#define AT91C_EMACB0_TID          (0xF802C0B8)  // (EMACB0) Type ID Checking Register
#define AT91C_EMACB0_SA2H         (0xF802C0A4)  // (EMACB0) Specific Address 2 Top, Last 2 bytes
#define AT91C_EMACB0_FRO          (0xF802C04C)  // (EMACB0) Frames Received OK Register
#define AT91C_EMACB0_LCOL         (0xF802C05C)  // (EMACB0) Late Collision Register
#define AT91C_EMACB0_USF          (0xF802C080)  // (EMACB0) Undersize Frames Register
#define AT91C_EMACB0_TBQP         (0xF802C01C)  // (EMACB0) Transmit Buffer Queue Pointer
#define AT91C_EMACB0_IER          (0xF802C028)  // (EMACB0) Interrupt Enable Register
#define AT91C_EMACB0_SA1L         (0xF802C098)  // (EMACB0) Specific Address 1 Bottom, First 4 bytes
#define AT91C_EMACB0_FTO          (0xF802C040)  // (EMACB0) Frames Transmitted OK Register
#define AT91C_EMACB0_TPF          (0xF802C08C)  // (EMACB0) Transmitted Pause Frames Register
#define AT91C_EMACB0_MAN          (0xF802C034)  // (EMACB0) PHY Maintenance Register
#define AT91C_EMACB0_RRE          (0xF802C06C)  // (EMACB0) Receive Ressource Error Register
#define AT91C_EMACB0_TUND         (0xF802C064)  // (EMACB0) Transmit Underrun Error Register
#define AT91C_EMACB0_HRB          (0xF802C090)  // (EMACB0) Hash Address Bottom[31:0]
#define AT91C_EMACB0_WOL          (0xF802C0C4)  // (EMACB0) Wake On LAN Register
#define AT91C_EMACB0_SA4L         (0xF802C0B0)  // (EMACB0) Specific Address 4 Bottom, First 4 bytes
#define AT91C_EMACB0_SA3L         (0xF802C0A8)  // (EMACB0) Specific Address 3 Bottom, First 4 bytes
#define AT91C_EMACB0_SCF          (0xF802C044)  // (EMACB0) Single Collision Frame Register
#define AT91C_EMACB0_PFR          (0xF802C03C)  // (EMACB0) Pause Frames received Register
#define AT91C_EMACB0_CSE          (0xF802C068)  // (EMACB0) Carrier Sense Error Register
#define AT91C_EMACB0_NSR          (0xF802C008)  // (EMACB0) Network Status Register
// ========== Register definition for EMACB1 peripheral ========== 
#define AT91C_EMACB1_RBQP         (0xF8030018)  // (EMACB1) Receive Buffer Queue Pointer
#define AT91C_EMACB1_TUND         (0xF8030064)  // (EMACB1) Transmit Underrun Error Register
#define AT91C_EMACB1_SCF          (0xF8030044)  // (EMACB1) Single Collision Frame Register
#define AT91C_EMACB1_HRB          (0xF8030090)  // (EMACB1) Hash Address Bottom[31:0]
#define AT91C_EMACB1_MAN          (0xF8030034)  // (EMACB1) PHY Maintenance Register
#define AT91C_EMACB1_IMR          (0xF8030030)  // (EMACB1) Interrupt Mask Register
#define AT91C_EMACB1_TPQ          (0xF80300BC)  // (EMACB1) Transmit Pause Quantum Register
#define AT91C_EMACB1_ROV          (0xF8030070)  // (EMACB1) Receive Overrun Errors Register
#define AT91C_EMACB1_NSR          (0xF8030008)  // (EMACB1) Network Status Register
#define AT91C_EMACB1_SA4H         (0xF80300B4)  // (EMACB1) Specific Address 4 Top, Last 2 bytes
#define AT91C_EMACB1_RLE          (0xF8030088)  // (EMACB1) Receive Length Field Mismatch Register
#define AT91C_EMACB1_STE          (0xF8030084)  // (EMACB1) SQE Test Error Register
#define AT91C_EMACB1_RSR          (0xF8030020)  // (EMACB1) Receive Status Register
#define AT91C_EMACB1_RJA          (0xF803007C)  // (EMACB1) Receive Jabbers Register
#define AT91C_EMACB1_HRT          (0xF8030094)  // (EMACB1) Hash Address Top[63:32]
#define AT91C_EMACB1_MCF          (0xF8030048)  // (EMACB1) Multiple Collision Frame Register
#define AT91C_EMACB1_SA2H         (0xF80300A4)  // (EMACB1) Specific Address 2 Top, Last 2 bytes
#define AT91C_EMACB1_SA1H         (0xF803009C)  // (EMACB1) Specific Address 1 Top, Last 2 bytes
#define AT91C_EMACB1_FRO          (0xF803004C)  // (EMACB1) Frames Received OK Register
#define AT91C_EMACB1_TID          (0xF80300B8)  // (EMACB1) Type ID Checking Register
#define AT91C_EMACB1_RRE          (0xF803006C)  // (EMACB1) Receive Ressource Error Register
#define AT91C_EMACB1_ALE          (0xF8030054)  // (EMACB1) Alignment Error Register
#define AT91C_EMACB1_ECOL         (0xF8030060)  // (EMACB1) Excessive Collision Register
#define AT91C_EMACB1_NCFGR        (0xF8030004)  // (EMACB1) Network Configuration Register
#define AT91C_EMACB1_IER          (0xF8030028)  // (EMACB1) Interrupt Enable Register
#define AT91C_EMACB1_SA3L         (0xF80300A8)  // (EMACB1) Specific Address 3 Bottom, First 4 bytes
#define AT91C_EMACB1_USF          (0xF8030080)  // (EMACB1) Undersize Frames Register
#define AT91C_EMACB1_TPF          (0xF803008C)  // (EMACB1) Transmitted Pause Frames Register
#define AT91C_EMACB1_WOL          (0xF80300C4)  // (EMACB1) Wake On LAN Register
#define AT91C_EMACB1_RSE          (0xF8030074)  // (EMACB1) Receive Symbol Errors Register
#define AT91C_EMACB1_ISR          (0xF8030024)  // (EMACB1) Interrupt Status Register
#define AT91C_EMACB1_REV          (0xF80300FC)  // (EMACB1) Revision Register
#define AT91C_EMACB1_LCOL         (0xF803005C)  // (EMACB1) Late Collision Register
#define AT91C_EMACB1_SA1L         (0xF8030098)  // (EMACB1) Specific Address 1 Bottom, First 4 bytes
#define AT91C_EMACB1_PTR          (0xF8030038)  // (EMACB1) Pause Time Register
#define AT91C_EMACB1_SA4L         (0xF80300B0)  // (EMACB1) Specific Address 4 Bottom, First 4 bytes
#define AT91C_EMACB1_NCR          (0xF8030000)  // (EMACB1) Network Control Register
#define AT91C_EMACB1_USRIO        (0xF80300C0)  // (EMACB1) USER Input/Output Register
#define AT91C_EMACB1_TSR          (0xF8030014)  // (EMACB1) Transmit Status Register
#define AT91C_EMACB1_FTO          (0xF8030040)  // (EMACB1) Frames Transmitted OK Register
#define AT91C_EMACB1_SA2L         (0xF80300A0)  // (EMACB1) Specific Address 2 Bottom, First 4 bytes
#define AT91C_EMACB1_CSE          (0xF8030068)  // (EMACB1) Carrier Sense Error Register
#define AT91C_EMACB1_IDR          (0xF803002C)  // (EMACB1) Interrupt Disable Register
#define AT91C_EMACB1_PFR          (0xF803003C)  // (EMACB1) Pause Frames received Register
#define AT91C_EMACB1_FCSE         (0xF8030050)  // (EMACB1) Frame Check Sequence Error Register
#define AT91C_EMACB1_DTF          (0xF8030058)  // (EMACB1) Deferred Transmission Frame Register
#define AT91C_EMACB1_SA3H         (0xF80300AC)  // (EMACB1) Specific Address 3 Top, Last 2 bytes
#define AT91C_EMACB1_ELE          (0xF8030078)  // (EMACB1) Excessive Length Errors Register
#define AT91C_EMACB1_TBQP         (0xF803001C)  // (EMACB1) Transmit Buffer Queue Pointer
// ========== Register definition for ISI peripheral ========== 
#define AT91C_ISI_DMACHDR         (0xF804803C)  // (ISI) DMA Channel Disable Register
#define AT91C_ISI_DMAPCTRL        (0xF8048048)  // (ISI) DMA Preview Control Register
#define AT91C_ISI_IER             (0xF804802C)  // (ISI) Interrupt Enable Register
#define AT91C_ISI_R2YSET0         (0xF8048018)  // (ISI) Color Space Conversion RGB to YCrCb Register
#define AT91C_ISI_DMAPDSCR        (0xF804804C)  // (ISI) DMA Preview Descriptor Address Register
#define AT91C_ISI_PSIZE           (0xF8048008)  // (ISI) Preview Size Register
#define AT91C_ISI_DMACCTRL        (0xF8048054)  // (ISI) DMA Codec Control Register
#define AT91C_ISI_CTRL            (0xF8048024)  // (ISI) Control Register
#define AT91C_ISI_Y2RSET0         (0xF8048010)  // (ISI) Color Space Conversion YCrCb to RGB Register
#define AT91C_ISI_IDR             (0xF8048030)  // (ISI) Interrupt Disable Register
#define AT91C_ISI_VER             (0xF80480FC)  // (ISI) Version Register
#define AT91C_ISI_DMACHER         (0xF8048038)  // (ISI) DMA Channel Enable Register
#define AT91C_ISI_SR              (0xF8048028)  // (ISI) Status Register
#define AT91C_ISI_DMACADDR        (0xF8048050)  // (ISI) DMA Codec Base Address Register
#define AT91C_ISI_DMAPADDR        (0xF8048044)  // (ISI) DMA Preview Base Address Register
#define AT91C_ISI_DMACHSR         (0xF8048040)  // (ISI) DMA Channel Status Register
#define AT91C_ISI_R2YSET2         (0xF8048020)  // (ISI) Color Space Conversion RGB to YCrCb Register
#define AT91C_ISI_WPSR            (0xF80480E8)  // (ISI) Write Protection Status Register
#define AT91C_ISI_Y2RSET1         (0xF8048014)  // (ISI) Color Space Conversion YCrCb to RGB Register
#define AT91C_ISI_R2YSET1         (0xF804801C)  // (ISI) Color Space Conversion RGB to YCrCb Register
#define AT91C_ISI_PDECF           (0xF804800C)  // (ISI) Preview Decimation Factor Register
#define AT91C_ISI_IMR             (0xF8048034)  // (ISI) Interrupt Mask Register
#define AT91C_ISI_CFG1            (0xF8048000)  // (ISI) Configuration Register 1
#define AT91C_ISI_DMACDSCR        (0xF8048058)  // (ISI) DMA Codec Descriptor Address Register
#define AT91C_ISI_CFG2            (0xF8048004)  // (ISI) Configuration Register 2
#define AT91C_ISI_WPCR            (0xF80480E4)  // (ISI) Write Protection Control Register
// ========== Register definition for UHPHS_OHCI peripheral ========== 
#define AT91C_OHCI_HcControlCurrentED (0x00600024)      // (UHPHS_OHCI) Endpoint Control and Status Register
#define AT91C_OHCI_HcRhDescriptorA (0x00600048) // (UHPHS_OHCI) Root Hub characteristics A
#define AT91C_OHCI_HcHCCA         (0x00600018)  // (UHPHS_OHCI) Pointer to the Host Controller Communication Area
#define AT91C_OHCI_HcFmNumber     (0x0060003C)  // (UHPHS_OHCI) Frame number
#define AT91C_OHCI_HcFmRemaining  (0x00600038)  // (UHPHS_OHCI) Bit time remaining in the current Frame
#define AT91C_OHCI_HcLSThreshold  (0x00600044)  // (UHPHS_OHCI) LS Threshold
#define AT91C_OHCI_HcCommandStatus (0x00600008) // (UHPHS_OHCI) Command & status Register
#define AT91C_OHCI_HcRhDescriptorB (0x0060004C) // (UHPHS_OHCI) Root Hub characteristics B
#define AT91C_OHCI_HcBulkDoneHead (0x00600030)  // (UHPHS_OHCI) Last completed transfer descriptor
#define AT91C_OHCI_HcInterruptEnable (0x00600010)       // (UHPHS_OHCI) Interrupt Enable Register
#define AT91C_OHCI_HcRevision     (0x00600000)  // (UHPHS_OHCI) Revision
#define AT91C_OHCI_HcControl      (0x00600004)  // (UHPHS_OHCI) Operating modes for the Host Controller
#define AT91C_OHCI_HcPeriodCurrentED (0x0060001C)       // (UHPHS_OHCI) Current Isochronous or Interrupt Endpoint Descriptor
#define AT91C_OHCI_HcPeriodicStart (0x00600040) // (UHPHS_OHCI) Periodic Start
#define AT91C_OHCI_HcControlHeadED (0x00600020) // (UHPHS_OHCI) First Endpoint Descriptor of the Control list
#define AT91C_OHCI_HcRhStatus     (0x00600050)  // (UHPHS_OHCI) Root Hub Status register
#define AT91C_OHCI_HcBulkHeadED   (0x00600028)  // (UHPHS_OHCI) First endpoint register of the Bulk list
#define AT91C_OHCI_HcFmInterval   (0x00600034)  // (UHPHS_OHCI) Bit time between 2 consecutive SOFs
#define AT91C_OHCI_HcInterruptDisable (0x00600014)      // (UHPHS_OHCI) Interrupt Disable Register
#define AT91C_OHCI_HcInterruptStatus (0x0060000C)       // (UHPHS_OHCI) Interrupt Status Register
#define AT91C_OHCI_HcBulkCurrentED (0x0060002C) // (UHPHS_OHCI) Current endpoint of the Bulk list
#define AT91C_OHCI_HcRhPortStatus (0x00600054)  // (UHPHS_OHCI) Root Hub Port Status Register
// ========== Register definition for UHPHS_EHCI peripheral ========== 
#define AT91C_EHCI_PORTSC         (0x00700054)  // (UHPHS_EHCI)
#define AT91C_EHCI_USBCMD         (0x00700010)  // (UHPHS_EHCI)
#define AT91C_EHCI_HCSPARAMS      (0x00700004)  // (UHPHS_EHCI)
#define AT91C_EHCI_INSNREG04      (0x007000A0)  // (UHPHS_EHCI)
#define AT91C_EHCI_INSNREG01      (0x00700094)  // (UHPHS_EHCI)
#define AT91C_EHCI_INSNREG02      (0x00700098)  // (UHPHS_EHCI)
#define AT91C_EHCI_HCSPPORTROUTE  (0x0070000C)  // (UHPHS_EHCI)
#define AT91C_EHCI_INSNREG00      (0x00700090)  // (UHPHS_EHCI)
#define AT91C_EHCI_USBSTS         (0x00700014)  // (UHPHS_EHCI)
#define AT91C_EHCI_FRINDEX        (0x0070001C)  // (UHPHS_EHCI)
#define AT91C_EHCI_CONFIGFLAG     (0x00700050)  // (UHPHS_EHCI)
#define AT91C_EHCI_CTRLDSSEGMENT  (0x00700020)  // (UHPHS_EHCI)
#define AT91C_EHCI_VERSION        (0x00700000)  // (UHPHS_EHCI)
#define AT91C_EHCI_ASYNCLISTADDR  (0x00700028)  // (UHPHS_EHCI)
#define AT91C_EHCI_INSNREG05      (0x007000A4)  // (UHPHS_EHCI)
#define AT91C_EHCI_INSNREG03      (0x0070009C)  // (UHPHS_EHCI)
#define AT91C_EHCI_USBINTR        (0x00700018)  // (UHPHS_EHCI)
#define AT91C_EHCI_HCCPARAMS      (0x00700008)  // (UHPHS_EHCI)
#define AT91C_EHCI_PERIODICLISTBASE (0x00700024)        // (UHPHS_EHCI)

// *****************************************************************************
//               PIO DEFINITIONS FOR AT91SAM9GX5
// *****************************************************************************
#define AT91C_PIO_PA0             (1UL <<  0)   // Pin Controlled by PA0
#define AT91C_PA0_TXD0            (AT91C_PIO_PA0)       //  USART 0 Transmit Data
#define AT91C_PA0_SPI1_NPCS1      (AT91C_PIO_PA0)       //  SPI 1 Peripheral Chip Select 1
#define AT91C_PIO_PA1             (1UL <<  1)   // Pin Controlled by PA1
#define AT91C_PA1_RXD0            (AT91C_PIO_PA1)       //  USART 0 Receive Data
#define AT91C_PA1_SPI0_NPCS2      (AT91C_PIO_PA1)       //  SPI 0 Peripheral Chip Select 2
#define AT91C_PIO_PA10            (1UL << 10)   // Pin Controlled by PA10
#define AT91C_PA10_DTXD           (AT91C_PIO_PA10)      //  DEBUG Transmit Data
#define AT91C_PA10_CANTX0         (AT91C_PIO_PA10)      //  CAN 0 Transmit Output
#define AT91C_PIO_PA11            (1UL << 11)   // Pin Controlled by PA11
#define AT91C_PA11_SPI0_MISO      (AT91C_PIO_PA11)      //  SPI 0 Master In Slave Out
#define AT91C_PA11_MCI1_DA0       (AT91C_PIO_PA11)      //  Multimedia Card 1, Slot A Data bit 0
#define AT91C_PIO_PA12            (1UL << 12)   // Pin Controlled by PA12
#define AT91C_PA12_SPI0_MOSI      (AT91C_PIO_PA12)      //  SPI 0 Master Out Slave In
#define AT91C_PA12_MCI1_CDA       (AT91C_PIO_PA12)      //  Multimedia Card 1, Slot A Command
#define AT91C_PIO_PA13            (1UL << 13)   // Pin Controlled by PA13
#define AT91C_PA13_SPI0_SPCK      (AT91C_PIO_PA13)      //  SPI 0 Serial Clock
#define AT91C_PA13_MCI1_CK        (AT91C_PIO_PA13)      //  Multimedia Card 1 ClocK
#define AT91C_PIO_PA14            (1UL << 14)   // Pin Controlled by PA14
#define AT91C_PA14_SPI0_NPCS0     (AT91C_PIO_PA14)      //  SPI 0 Peripheral Chip Select 0
#define AT91C_PIO_PA15            (1UL << 15)   // Pin Controlled by PA15
#define AT91C_PA15_MCI0_DA0       (AT91C_PIO_PA15)      //  Multimedia Card 0, Slot A Data bit 0
#define AT91C_PIO_PA16            (1UL << 16)   // Pin Controlled by PA16
#define AT91C_PA16_MCI0_CDA       (AT91C_PIO_PA16)      //  Multimedia Card 0, Slot A Command
#define AT91C_PIO_PA17            (1UL << 17)   // Pin Controlled by PA17
#define AT91C_PA17_MCI0_CK        (AT91C_PIO_PA17)      //  Multimedia Card 0 ClocK
#define AT91C_PIO_PA18            (1UL << 18)   // Pin Controlled by PA18
#define AT91C_PA18_MCI0_DA1       (AT91C_PIO_PA18)      //  Multimedia Card 0, Slot A Data bit 1
#define AT91C_PIO_PA19            (1UL << 19)   // Pin Controlled by PA19
#define AT91C_PA19_MCI0_DA2       (AT91C_PIO_PA19)      //  Multimedia Card 0, Slot A Data bit 2
#define AT91C_PIO_PA2             (1UL <<  2)   // Pin Controlled by PA2
#define AT91C_PA2_RTS0            (AT91C_PIO_PA2)       //  USART 0 Request To Send
#define AT91C_PA2_MCI1_DA1        (AT91C_PIO_PA2)       //  Multimedia Card 1, Slot A Data bit 1
#define AT91C_PA2_EMAC0_ETX0      (AT91C_PIO_PA2)       //  Ethernet MAC 0, Transmit Data 0
#define AT91C_PIO_PA20            (1UL << 20)   // Pin Controlled by PA20
#define AT91C_PA20_MCI0_DA3       (AT91C_PIO_PA20)      //  Multimedia Card 0, Slot A Data bit 3
#define AT91C_PIO_PA21            (1UL << 21)   // Pin Controlled by PA21
#define AT91C_PA21_TIOA0          (AT91C_PIO_PA21)      //  TC Channel 0, I/O line A
#define AT91C_PA21_SPI1_MISO      (AT91C_PIO_PA21)      //  SPI 1 Master In Slave Out
#define AT91C_PIO_PA22            (1UL << 22)   // Pin Controlled by PA22
#define AT91C_PA22_TIOA1          (AT91C_PIO_PA22)      //  TC Channel 1, I/O line A
#define AT91C_PA22_SPI1_MOSI      (AT91C_PIO_PA22)      //  SPI 1 Master Out Slave In
#define AT91C_PIO_PA23            (1UL << 23)   // Pin Controlled by PA23
#define AT91C_PA23_TIOA2          (AT91C_PIO_PA23)      //  TC Channel 2, I/O line A
#define AT91C_PA23_SPI1_SPCK      (AT91C_PIO_PA23)      //  SPI 1 Serial ClocK
#define AT91C_PIO_PA24            (1UL << 24)   // Pin Controlled by PA24
#define AT91C_PA24_TCLK0          (AT91C_PIO_PA24)      //  TC Channel 0, external ClocK input
#define AT91C_PA24_TK             (AT91C_PIO_PA24)      //  SSC Transmit clocK
#define AT91C_PIO_PA25            (1UL << 25)   // Pin Controlled by PA25
#define AT91C_PA25_TCLK1          (AT91C_PIO_PA25)      //  TC Channel 1, external ClocK input
#define AT91C_PA25_TF             (AT91C_PIO_PA25)      //  SSC Transmit Frame Sync
#define AT91C_PIO_PA26            (1UL << 26)   // Pin Controlled by PA26
#define AT91C_PA26_TCLK2          (AT91C_PIO_PA26)      //  TC Channel 2, external ClocK input
#define AT91C_PA26_TD             (AT91C_PIO_PA26)      //  SSC Transmit Data
#define AT91C_PIO_PA27            (1UL << 27)   // Pin Controlled by PA27
#define AT91C_PA27_TIOB0          (AT91C_PIO_PA27)      //  TC Channel 0, I/O line B
#define AT91C_PA27_RD             (AT91C_PIO_PA27)      //  SSC Receive Data
#define AT91C_PIO_PA28            (1UL << 28)   // Pin Controlled by PA28
#define AT91C_PA28_TIOB1          (AT91C_PIO_PA28)      //  TC Channel 1, I/O line B
#define AT91C_PA28_RK             (AT91C_PIO_PA28)      //  SSC Receive clocK
#define AT91C_PIO_PA29            (1UL << 29)   // Pin Controlled by PA29
#define AT91C_PA29_TIOB2          (AT91C_PIO_PA29)      //  TC Channel 2, I/O line B
#define AT91C_PA29_RF             (AT91C_PIO_PA29)      //  SSC Receive Frame Sync
#define AT91C_PIO_PA3             (1UL <<  3)   // Pin Controlled by PA3
#define AT91C_PA3_CTS0            (AT91C_PIO_PA3)       //  USART 0 Clear To Send
#define AT91C_PA3_MCI1_DA2        (AT91C_PIO_PA3)       //  Multimedia Card 1, Slot A Data bit 2
#define AT91C_PA3_EMAC0_ETX1      (AT91C_PIO_PA3)       //  Ethernet MAC 0, Transmit Data 1
#define AT91C_PIO_PA30            (1UL << 30)   // Pin Controlled by PA30
#define AT91C_PA30_TWD0           (AT91C_PIO_PA30)      //  Two-Wire Interface 0, Serial Data
#define AT91C_PA30_SPI1_NPCS3     (AT91C_PIO_PA30)      //  SPI 1 Peripheral Chip Select 3
#define AT91C_PA30_EMAC0_EMDC     (AT91C_PIO_PA30)      //  Ethernet MAC 0, Management Data Clock
#define AT91C_PIO_PA31            (1UL << 31)   // Pin Controlled by PA31
#define AT91C_PA31_TWCK0          (AT91C_PIO_PA31)      //  Two-Wire Interface 0, Serial ClocK
#define AT91C_PA31_SPI1_NPCS2     (AT91C_PIO_PA31)      //  SPI 1 Peripheral Chip Select 2
#define AT91C_PA31_EMAC0_ETXEN    (AT91C_PIO_PA31)      //  Ethernet MAC 0, Transmit Enable
#define AT91C_PIO_PA4             (1UL <<  4)   // Pin Controlled by PA4
#define AT91C_PA4_SCK0            (AT91C_PIO_PA4)       //  USART 0 Serial ClocK
#define AT91C_PA4_MCI1_DA3        (AT91C_PIO_PA4)       //  Multimedia Card 1, Slot A Data bit 3
#define AT91C_PA4_EMAC0_ETXER     (AT91C_PIO_PA4)       //  Ethernet MAC 0, Transmit Coding ERror
#define AT91C_PIO_PA5             (1UL <<  5)   // Pin Controlled by PA5
#define AT91C_PA5_TXD1            (AT91C_PIO_PA5)       //  USART 1 Transmit Data
#define AT91C_PA5_CANTX1          (AT91C_PIO_PA5)       //  CAN 1 Transmit Output
#define AT91C_PIO_PA6             (1UL <<  6)   // Pin Controlled by PA6
#define AT91C_PA6_RXD1            (AT91C_PIO_PA6)       //  USART 1 Receive Data
#define AT91C_PA6_CANRX1          (AT91C_PIO_PA6)       //  CAN 1 Receive Input
#define AT91C_PIO_PA7             (1UL <<  7)   // Pin Controlled by PA7
#define AT91C_PA7_TXD2            (AT91C_PIO_PA7)       //  USART 2 Transmit Data
#define AT91C_PA7_SPI0_NPCS1      (AT91C_PIO_PA7)       //  SPI 0 Peripheral Chip Select 1
#define AT91C_PIO_PA8             (1UL <<  8)   // Pin Controlled by PA8
#define AT91C_PA8_RXD2            (AT91C_PIO_PA8)       //  USART 2 Receive Data
#define AT91C_PA8_SPI1_NPCS0      (AT91C_PIO_PA8)       //  SPI 1 Peripheral Chip Select 0
#define AT91C_PIO_PA9             (1UL <<  9)   // Pin Controlled by PA9
#define AT91C_PA9_DRXD            (AT91C_PIO_PA9)       //  DEBUG Receive Data
#define AT91C_PA9_CANRX0          (AT91C_PIO_PA9)       //  CAN 0 Receive Input
#define AT91C_PIO_PB0             (1UL <<  0)   // Pin Controlled by PB0
#define AT91C_PB0_EMAC0_ERX0      (AT91C_PIO_PB0)       //  Ethernet MAC 0, Receive Data 0
#define AT91C_PB0_RTS2            (AT91C_PIO_PB0)       //  USART 2 Request To Send
#define AT91C_PIO_PB1             (1UL <<  1)   // Pin Controlled by PB1
#define AT91C_PB1_EMAC0_ERX1      (AT91C_PIO_PB1)       //  Ethernet MAC 0, Receive Data 1
#define AT91C_PB1_CTS2            (AT91C_PIO_PB1)       //  USART 2 Clear To Send
#define AT91C_PIO_PB10            (1UL << 10)   // Pin Controlled by PB10
#define AT91C_PB10_EMAC0_ETX1     (AT91C_PIO_PB10)      //  Ethernet MAC 0, Transmit Data 1
#define AT91C_PB10_PCK0           (AT91C_PIO_PB10)      //  Programmable Clock Output 0
#define AT91C_PIO_PB11            (1UL << 11)   // Pin Controlled by PB11
#define AT91C_PB11_EMAC0_ETX2     (AT91C_PIO_PB11)      //  Ethernet MAC 0, Transmit Data 2
#define AT91C_PB11_PWM0           (AT91C_PIO_PB11)      //  Pulse Width Modulation Channel 0 Output
#define AT91C_PIO_PB12            (1UL << 12)   // Pin Controlled by PB12
#define AT91C_PB12_EMAC0_ETX3     (AT91C_PIO_PB12)      //  Ethernet MAC 0, Transmit Data 3
#define AT91C_PB12_PWM1           (AT91C_PIO_PB12)      //  Pulse Width Modulation Channel 1 Output
#define AT91C_PIO_PB13            (1UL << 13)   // Pin Controlled by PB13
#define AT91C_PB13_EMAC0_ERX2     (AT91C_PIO_PB13)      //  Ethernet MAC 0, Receive Data 2
#define AT91C_PB13_PWM2           (AT91C_PIO_PB13)      //  Pulse Width Modulation Channel 2 Output
#define AT91C_PIO_PB14            (1UL << 14)   // Pin Controlled by PB14
#define AT91C_PB14_EMAC0_ERX3     (AT91C_PIO_PB14)      //  Ethernet MAC 0, Receive Data 3
#define AT91C_PB14_PWM3           (AT91C_PIO_PB14)      //  Pulse Width Modulation Channel 3 Output
#define AT91C_PIO_PB15            (1UL << 15)   // Pin Controlled by PB15
#define AT91C_PB15_EMAC0_ERXCK    (AT91C_PIO_PB15)      //  Ethernet MAC 0, Receive ClocK
#define AT91C_PIO_PB16            (1UL << 16)   // Pin Controlled by PB16
#define AT91C_PB16_EMAC0_ECRS     (AT91C_PIO_PB16)      //  Ethernet MAC 0, Carrier Sense and Data Valid
#define AT91C_PIO_PB17            (1UL << 17)   // Pin Controlled by PB17
#define AT91C_PB17_EMAC0_ECOL     (AT91C_PIO_PB17)      //  Ethernet MAC 0, Collision Detect
#define AT91C_PIO_PB18            (1UL << 18)   // Pin Controlled by PB18
#define AT91C_PB18_IRQ            (AT91C_PIO_PB18)      //  External Interrupt Input
#define AT91C_PB18_TSADTRG        (AT91C_PIO_PB18)      //  ADC Trigger
#define AT91C_PIO_PB2             (1UL <<  2)   // Pin Controlled by PB2
#define AT91C_PB2_EMAC0_ERXER     (AT91C_PIO_PB2)       //  Ethernet MAC 0, Receive ERror
#define AT91C_PB2_SCK2            (AT91C_PIO_PB2)       //  USART 2 Serial ClocK
#define AT91C_PIO_PB3             (1UL <<  3)   // Pin Controlled by PB3
#define AT91C_PB3_EMAC0_ERXDV     (AT91C_PIO_PB3)       //  Ethernet MAC 0, Receive Data Valid
#define AT91C_PB3_SPI0_NPCS3      (AT91C_PIO_PB3)       //  SPI 0 Peripheral Chip Select 3
#define AT91C_PIO_PB4             (1UL <<  4)   // Pin Controlled by PB4
#define AT91C_PB4_EMAC0_ETXCK     (AT91C_PIO_PB4)       //  Ethernet MAC 0, Transmit Clock or Reference Clock
#define AT91C_PB4_TWD2            (AT91C_PIO_PB4)       //  Two-Wire Interface 2, Serial Data
#define AT91C_PIO_PB5             (1UL <<  5)   // Pin Controlled by PB5
#define AT91C_PB5_EMAC0_EMDIO     (AT91C_PIO_PB5)       //  Ethernet MAC 0, Management Data Input/Output
#define AT91C_PB5_TWCK2           (AT91C_PIO_PB5)       //  Two-Wire Interface 2, Serial ClocK
#define AT91C_PIO_PB6             (1UL <<  6)   // Pin Controlled by PB6
#define AT91C_PB6_EMAC0_EMDC      (AT91C_PIO_PB6)       //  Ethernet MAC 0, Management Data Clock
#define AT91C_PIO_PB7             (1UL <<  7)   // Pin Controlled by PB7
#define AT91C_PB7_EMAC0_ETXEN     (AT91C_PIO_PB7)       //  Ethernet MAC 0, Transmit Enable
#define AT91C_PIO_PB8             (1UL <<  8)   // Pin Controlled by PB8
#define AT91C_PB8_EMAC0_ETXER     (AT91C_PIO_PB8)       //  Ethernet MAC 0, Transmit Coding ERror
#define AT91C_PIO_PB9             (1UL <<  9)   // Pin Controlled by PB9
#define AT91C_PB9_EMAC0_ETX0      (AT91C_PIO_PB9)       //  Ethernet MAC 0, Transmit Data 0
#define AT91C_PB9_PCK1            (AT91C_PIO_PB9)       //  Programmable Clock Output 1
#define AT91C_PIO_PC0             (1UL <<  0)   // Pin Controlled by PC0
#define AT91C_PC0_LCDD0           (AT91C_PIO_PC0)       //  LCD Data bus, bit 0
#define AT91C_PC0_ISI_D0          (AT91C_PIO_PC0)       //  Image Sensor Data, bit 0
#define AT91C_PC0_TWD1            (AT91C_PIO_PC0)       //  Two-Wire Interface 1, Serial Data
#define AT91C_PIO_PC1             (1UL <<  1)   // Pin Controlled by PC1
#define AT91C_PC1_LCDD1           (AT91C_PIO_PC1)       //  LCD Data bus, bit 1
#define AT91C_PC1_ISI_D1          (AT91C_PIO_PC1)       //  Image Sensor Data, bit 1
#define AT91C_PC1_TWCK1           (AT91C_PIO_PC1)       //  Two-Wire Interface 1, Serial ClocK
#define AT91C_PIO_PC10            (1UL << 10)   // Pin Controlled by PC10
#define AT91C_PC10_LCDD10         (AT91C_PIO_PC10)      //  LCD Data bus, bit 10
#define AT91C_PC10_ISI_D10        (AT91C_PIO_PC10)      //  Image Sensor Data, bit 10
#define AT91C_PC10_PWM0           (AT91C_PIO_PC10)      //  Pulse Width Modulation Channel 0 Output
#define AT91C_PIO_PC11            (1UL << 11)   // Pin Controlled by PC11
#define AT91C_PC11_LCDD11         (AT91C_PIO_PC11)      //  LCD Data bus, bit 11
#define AT91C_PC11_ISI_D11        (AT91C_PIO_PC11)      //  Image Sensor Data, bit 11
#define AT91C_PC11_PWM1           (AT91C_PIO_PC11)      //  Pulse Width Modulation Channel 1 Output
#define AT91C_PIO_PC12            (1UL << 12)   // Pin Controlled by PC12
#define AT91C_PC12_LCDD12         (AT91C_PIO_PC12)      //  LCD Data bus, bit 12
#define AT91C_PC12_ISI_PCK        (AT91C_PIO_PC12)      //  Image Sensor Data ClocK
#define AT91C_PC12_TIOA5          (AT91C_PIO_PC12)      //  TC Channel 5, I/O line A
#define AT91C_PIO_PC13            (1UL << 13)   // Pin Controlled by PC13
#define AT91C_PC13_LCDD13         (AT91C_PIO_PC13)      //  LCD Data bus, bit 13
#define AT91C_PC13_ISI_VSYNC      (AT91C_PIO_PC13)      //  Image Sensor Vertical Synchro
#define AT91C_PC13_TIOB5          (AT91C_PIO_PC13)      //  TC Channel 5, I/O line B
#define AT91C_PIO_PC14            (1UL << 14)   // Pin Controlled by PC14
#define AT91C_PC14_LCDD14         (AT91C_PIO_PC14)      //  LCD Data bus, bit 14
#define AT91C_PC14_ISI_HSYNC      (AT91C_PIO_PC14)      //  Image Sensor Horizontal Synchro
#define AT91C_PC14_TCLK5          (AT91C_PIO_PC14)      //  TC Channel 5, external ClocK input
#define AT91C_PIO_PC15            (1UL << 15)   // Pin Controlled by PC15
#define AT91C_PC15_LCDD15         (AT91C_PIO_PC15)      //  LCD Data bus, bit 15
#define AT91C_PC15_               (AT91C_PIO_PC15)      //
#define AT91C_PC15_PCK0           (AT91C_PIO_PC15)      //  Programmable Clock Output 0
#define AT91C_PIO_PC16            (1UL << 16)   // Pin Controlled by PC16
#define AT91C_PC16_LCDD16         (AT91C_PIO_PC16)      //  LCD Data bus, bit 16
#define AT91C_PC16_EMAC1_ERXER    (AT91C_PIO_PC16)      //  Ethernet MAC 1, Receive ERror
#define AT91C_PC16_UTXD1          (AT91C_PIO_PC16)      //  UART 1 Transmit Data
#define AT91C_PIO_PC17            (1UL << 17)   // Pin Controlled by PC17
#define AT91C_PC17_LCDD17         (AT91C_PIO_PC17)      //  LCD Data bus, bit 17
#define AT91C_PC17_               (AT91C_PIO_PC17)      //
#define AT91C_PC17_URXD1          (AT91C_PIO_PC17)      //  UART 1 Receive Data
#define AT91C_PIO_PC18            (1UL << 18)   // Pin Controlled by PC18
#define AT91C_PC18_LCDD18         (AT91C_PIO_PC18)      //  LCD Data bus, bit 18
#define AT91C_PC18_EMAC1_ETX0     (AT91C_PIO_PC18)      //  Ethernet MAC 1, Transmit Data 0
#define AT91C_PC18_PWM0           (AT91C_PIO_PC18)      //  Pulse Width Modulation Channel 0 Output
#define AT91C_PIO_PC19            (1UL << 19)   // Pin Controlled by PC19
#define AT91C_PC19_LCDD19         (AT91C_PIO_PC19)      //  LCD Data bus, bit 19
#define AT91C_PC19_EMAC1_ETX1     (AT91C_PIO_PC19)      //  Ethernet MAC 1, Transmit Data 1
#define AT91C_PC19_PWM1           (AT91C_PIO_PC19)      //  Pulse Width Modulation Channel 1 Output
#define AT91C_PIO_PC2             (1UL <<  2)   // Pin Controlled by PC2
#define AT91C_PC2_LCDD2           (AT91C_PIO_PC2)       //  LCD Data bus, bit 2
#define AT91C_PC2_ISI_D2          (AT91C_PIO_PC2)       //  Image Sensor Data, bit 2
#define AT91C_PC2_TIOA3           (AT91C_PIO_PC2)       //  TC Channel 3, I/O line A
#define AT91C_PIO_PC20            (1UL << 20)   // Pin Controlled by PC20
#define AT91C_PC20_LCDD20         (AT91C_PIO_PC20)      //  LCD Data bus, bit 20
#define AT91C_PC20_EMAC1_ERX0     (AT91C_PIO_PC20)      //  Ethernet MAC 1, Receive Data 0
#define AT91C_PC20_PWM2           (AT91C_PIO_PC20)      //  Pulse Width Modulation Channel 2 Output
#define AT91C_PIO_PC21            (1UL << 21)   // Pin Controlled by PC21
#define AT91C_PC21_LCDD21         (AT91C_PIO_PC21)      //  LCD Data bus, bit 21
#define AT91C_PC21_EMAC1_ERX1     (AT91C_PIO_PC21)      //  Ethernet MAC 1, Receive Data 1
#define AT91C_PC21_PWM3           (AT91C_PIO_PC21)      //  Pulse Width Modulation Channel 3 Output
#define AT91C_PIO_PC22            (1UL << 22)   // Pin Controlled by PC22
#define AT91C_PC22_LCDD22         (AT91C_PIO_PC22)      //  LCD Data bus, bit 22
#define AT91C_PC22_TXD3           (AT91C_PIO_PC22)      //  USART 3 Transmit Data
#define AT91C_PIO_PC23            (1UL << 23)   // Pin Controlled by PC23
#define AT91C_PC23_LCDD23         (AT91C_PIO_PC23)      //  LCD Data bus, bit 23
#define AT91C_PC23_RXD3           (AT91C_PIO_PC23)      //  USART 3 Receive Data
#define AT91C_PIO_PC24            (1UL << 24)   // Pin Controlled by PC24
#define AT91C_PC24_LCDDISP        (AT91C_PIO_PC24)      //  LCD Disable
#define AT91C_PC24_RTS3           (AT91C_PIO_PC24)      //  USART 3 Request To Send
#define AT91C_PIO_PC25            (1UL << 25)   // Pin Controlled by PC25
#define AT91C_PC25_               (AT91C_PIO_PC25)      //
#define AT91C_PC25_CTS3           (AT91C_PIO_PC25)      //  USART 3 Clear To Send
#define AT91C_PIO_PC26            (1UL << 26)   // Pin Controlled by PC26
#define AT91C_PC26_LCDPWM         (AT91C_PIO_PC26)      //  LCD MODulation signal
#define AT91C_PC26_SCK3           (AT91C_PIO_PC26)      //  USART 3 Serial ClocK
#define AT91C_PIO_PC27            (1UL << 27)   // Pin Controlled by PC27
#define AT91C_PC27_LCDVSYNC       (AT91C_PIO_PC27)      //  LCD Vertical Synchronization
#define AT91C_PC27_EMAC1_ETXEN    (AT91C_PIO_PC27)      //  Ethernet MAC 1, Transmit Enable
#define AT91C_PC27_RTS1           (AT91C_PIO_PC27)      //  USART 1 Request To Send
#define AT91C_PIO_PC28            (1UL << 28)   // Pin Controlled by PC28
#define AT91C_PC28_LCDHSYNC       (AT91C_PIO_PC28)      //  LCD Horizontal Synchronization
#define AT91C_PC28_EMAC1_ERXDV    (AT91C_PIO_PC28)      //  Ethernet MAC 1, Receive Data Valid
#define AT91C_PC28_CTS1           (AT91C_PIO_PC28)      //  USART 1 Clear To Send
#define AT91C_PIO_PC29            (1UL << 29)   // Pin Controlled by PC29
#define AT91C_PC29_LCDDEN         (AT91C_PIO_PC29)      //  LCD Horizontal Synchronization
#define AT91C_PC29_EMAC1_ETXCK    (AT91C_PIO_PC29)      //  Ethernet MAC 1, Transmit Clock or Reference Clock
#define AT91C_PC29_SCK1           (AT91C_PIO_PC29)      //  USART 1 Serial ClocK
#define AT91C_PIO_PC3             (1UL <<  3)   // Pin Controlled by PC3
#define AT91C_PC3_LCDD3           (AT91C_PIO_PC3)       //  LCD Data bus, bit 3
#define AT91C_PC3_ISI_D3          (AT91C_PIO_PC3)       //  Image Sensor Data, bit 3
#define AT91C_PC3_TIOB3           (AT91C_PIO_PC3)       //  TC Channel 3, I/O line B
#define AT91C_PIO_PC30            (1UL << 30)   // Pin Controlled by PC30
#define AT91C_PC30_LCDPCK         (AT91C_PIO_PC30)      //  LCD  ClocK
#define AT91C_PC30_EMAC1_EMDC     (AT91C_PIO_PC30)      //  Ethernet MAC 1, Management Data Clock
#define AT91C_PIO_PC31            (1UL << 31)   // Pin Controlled by PC31
#define AT91C_PC31_FIQ            (AT91C_PIO_PC31)      //  Fast Interrupt Input
#define AT91C_PC31_EMAC1_EMDIO    (AT91C_PIO_PC31)      //  Ethernet MAC 1, Management Data Input/Output
#define AT91C_PC31_PCK1           (AT91C_PIO_PC31)      //  Programmable Clock Output 1
#define AT91C_PIO_PC4             (1UL <<  4)   // Pin Controlled by PC4
#define AT91C_PC4_LCDD4           (AT91C_PIO_PC4)       //  LCD Data bus, bit 4
#define AT91C_PC4_ISI_D4          (AT91C_PIO_PC4)       //  Image Sensor Data, bit 4
#define AT91C_PC4_TCLK3           (AT91C_PIO_PC4)       //  TC Channel 3, external ClocK input
#define AT91C_PIO_PC5             (1UL <<  5)   // Pin Controlled by PC5
#define AT91C_PC5_LCDD5           (AT91C_PIO_PC5)       //  LCD Data bus, bit 5
#define AT91C_PC5_ISI_D5          (AT91C_PIO_PC5)       //  Image Sensor Data, bit 5
#define AT91C_PC5_TIOA4           (AT91C_PIO_PC5)       //  TC Channel 4, I/O line A
#define AT91C_PIO_PC6             (1UL <<  6)   // Pin Controlled by PC6
#define AT91C_PC6_LCDD6           (AT91C_PIO_PC6)       //  LCD Data bus, bit 6
#define AT91C_PC6_ISI_D6          (AT91C_PIO_PC6)       //  Image Sensor Data, bit 6
#define AT91C_PC6_TIOB4           (AT91C_PIO_PC6)       //  TC Channel 4, I/O line B
#define AT91C_PIO_PC7             (1UL <<  7)   // Pin Controlled by PC7
#define AT91C_PC7_LCDD7           (AT91C_PIO_PC7)       //  LCD Data bus, bit 7
#define AT91C_PC7_ISI_D7          (AT91C_PIO_PC7)       //  Image Sensor Data, bit 7
#define AT91C_PC7_TCLK4           (AT91C_PIO_PC7)       //  TC Channel 4, external ClocK input
#define AT91C_PIO_PC8             (1UL <<  8)   // Pin Controlled by PC8
#define AT91C_PC8_LCDD8           (AT91C_PIO_PC8)       //  LCD Data bus, bit 8
#define AT91C_PC8_ISI_D8          (AT91C_PIO_PC8)       //  Image Sensor Data, bit 8
#define AT91C_PC8_UTXD0           (AT91C_PIO_PC8)       //  UART 0 Transmit Data
#define AT91C_PIO_PC9             (1UL <<  9)   // Pin Controlled by PC9
#define AT91C_PC9_LCDD9           (AT91C_PIO_PC9)       //  LCD Data bus, bit 9
#define AT91C_PC9_ISI_D9          (AT91C_PIO_PC9)       //  Image Sensor Data, bit 9
#define AT91C_PC9_URXD0           (AT91C_PIO_PC9)       //  UART 0 Receive Data
#define AT91C_PIO_PD0             (1UL <<  0)   // Pin Controlled by PD0
#define AT91C_PD0_NANDOE          (AT91C_PIO_PD0)       //  NAND Flash Output Enable
#define AT91C_PIO_PD1             (1UL <<  1)   // Pin Controlled by PD1
#define AT91C_PD1_NANDWE          (AT91C_PIO_PD1)       //  NAND Flash Write Enable
#define AT91C_PIO_PD10            (1UL << 10)   // Pin Controlled by PD10
#define AT91C_PD10_D20            (AT91C_PIO_PD10)      //  EBI Data Bus, bit 20
#define AT91C_PIO_PD11            (1UL << 11)   // Pin Controlled by PD11
#define AT91C_PD11_D21            (AT91C_PIO_PD11)      //  EBI Data Bus, bit 21
#define AT91C_PIO_PD12            (1UL << 12)   // Pin Controlled by PD12
#define AT91C_PD12_D22            (AT91C_PIO_PD12)      //  EBI Data Bus, bit 22
#define AT91C_PIO_PD13            (1UL << 13)   // Pin Controlled by PD13
#define AT91C_PD13_D23            (AT91C_PIO_PD13)      //  EBI Data Bus, bit 23
#define AT91C_PIO_PD14            (1UL << 14)   // Pin Controlled by PD14
#define AT91C_PD14_D24            (AT91C_PIO_PD14)      //  EBI Data Bus, bit 24
#define AT91C_PIO_PD15            (1UL << 15)   // Pin Controlled by PD15
#define AT91C_PD15_D25            (AT91C_PIO_PD15)      //  EBI Data Bus, bit 25
#define AT91C_PD15_A20            (AT91C_PIO_PD15)      //  EBI Address Bus, bit 20
#define AT91C_PIO_PD16            (1UL << 16)   // Pin Controlled by PD16
#define AT91C_PD16_D26            (AT91C_PIO_PD16)      //  EBI Data Bus, bit 26
#define AT91C_PD16_A23            (AT91C_PIO_PD16)      //  EBI Address Bus, bit 23
#define AT91C_PIO_PD17            (1UL << 17)   // Pin Controlled by PD17
#define AT91C_PD17_D27            (AT91C_PIO_PD17)      //  EBI Data Bus, bit 27
#define AT91C_PD17_A24            (AT91C_PIO_PD17)      //  EBI Address Bus, bit 24
#define AT91C_PIO_PD18            (1UL << 18)   // Pin Controlled by PD18
#define AT91C_PD18_D28            (AT91C_PIO_PD18)      //  EBI Data Bus, bit 28
#define AT91C_PD18_A25            (AT91C_PIO_PD18)      //  EBI Address Bus, bit 25
#define AT91C_PIO_PD19            (1UL << 19)   // Pin Controlled by PD19
#define AT91C_PD19_D29            (AT91C_PIO_PD19)      //  EBI Data Bus, bit 29
#define AT91C_PD19_NCS2           (AT91C_PIO_PD19)      //  EBI SMC Chip Select Line 2
#define AT91C_PIO_PD2             (1UL <<  2)   // Pin Controlled by PD2
#define AT91C_PD2_A21_NANDALE     (AT91C_PIO_PD2)       //
#define AT91C_PIO_PD20            (1UL << 20)   // Pin Controlled by PD20
#define AT91C_PD20_D30            (AT91C_PIO_PD20)      //  EBI Data Bus, bit 30
#define AT91C_PD20_NCS4           (AT91C_PIO_PD20)      //  EBI SMC Chip Select Line 4
#define AT91C_PIO_PD21            (1UL << 21)   // Pin Controlled by PD21
#define AT91C_PD21_D31            (AT91C_PIO_PD21)      //  EBI Data Bus, bit 31
#define AT91C_PD21_NCS5           (AT91C_PIO_PD21)      //  EBI SMC Chip Select Line 5
#define AT91C_PIO_PD3             (1UL <<  3)   // Pin Controlled by PD3
#define AT91C_PD3_A22_NANDCLE     (AT91C_PIO_PD3)       //
#define AT91C_PIO_PD4             (1UL <<  4)   // Pin Controlled by PD4
#define AT91C_PD4_NCS3_NANDCS     (AT91C_PIO_PD4)       //
#define AT91C_PIO_PD5             (1UL <<  5)   // Pin Controlled by PD5
#define AT91C_PD5_NWAIT           (AT91C_PIO_PD5)       //  External Wait signal
#define AT91C_PIO_PD6             (1UL <<  6)   // Pin Controlled by PD6
#define AT91C_PD6_D16             (AT91C_PIO_PD6)       //  EBI Data Bus, bit 16
#define AT91C_PIO_PD7             (1UL <<  7)   // Pin Controlled by PD7
#define AT91C_PD7_D17             (AT91C_PIO_PD7)       //  EBI Data Bus, bit 17
#define AT91C_PIO_PD8             (1UL <<  8)   // Pin Controlled by PD8
#define AT91C_PD8_D18             (AT91C_PIO_PD8)       //  EBI Data Bus, bit 18
#define AT91C_PIO_PD9             (1UL <<  9)   // Pin Controlled by PD9
#define AT91C_PD9_D19             (AT91C_PIO_PD9)       //  EBI Data Bus, bit 19

// *****************************************************************************
//               PERIPHERAL ID DEFINITIONS FOR AT91SAM9GX5
// *****************************************************************************
#define AT91C_ID_FIQ              ( 0)  // Advanced Interrupt Controller (FIQ)
#define AT91C_ID_SYS              ( 1)  // System Controller
#define AT91C_ID_PIOA_B           ( 2)  // Parallel IO Controller A and B
#define AT91C_ID_PIOC_D           ( 3)  // Parallel IO Controller C and D
#define AT91C_ID_SSD              ( 4)  // Software Modem
#define AT91C_ID_US0              ( 5)  // USART 0
#define AT91C_ID_US1              ( 6)  // USART 1
#define AT91C_ID_US2              ( 7)  // USART 2
#define AT91C_ID_US3              ( 8)  // USART 3
#define AT91C_ID_TWI0             ( 9)  // TWI 0
#define AT91C_ID_TWI1             (10)  // TWI 1
#define AT91C_ID_TWI2             (11)  // TWI 2
#define AT91C_ID_MCI0             (12)  // Multimedia Card Interface 0
#define AT91C_ID_SPI0             (13)  // Serial Peripheral Interface 0
#define AT91C_ID_SPI1             (14)  // Serial Peripheral Interface 1
#define AT91C_ID_UART0            (15)  // UART 0
#define AT91C_ID_UART1            (16)  // UART 1
#define AT91C_ID_TC               (17)  // Timer Counter 0, 1, 2, 3, 4, 5
#define AT91C_ID_PWMC             (18)  // Pulse Width Modulation Controller
#define AT91C_ID_TSADC            (19)  // Touch Screen Controller
#define AT91C_ID_HDMA0            (20)  // DMA Controller 0
#define AT91C_ID_HDMA1            (21)  // DMA Controller 1
#define AT91C_ID_HDMA             (20)  // DMA Controller 0
#define AT91C_ID_UHPHS            (22)  // USB Host High Speed
#define AT91C_ID_UDPHS            (23)  // USB Device HS
#define AT91C_ID_EMAC0            (24)  // Ethernet MAC 0
#define AT91C_ID_LCDC_ISI         (25)  // LCD Controller or Image Sensor Interface
#define AT91C_ID_MCI1             (26)  // Multimedia Card Interface 1
#define AT91C_ID_EMAC1            (27)  // Ethernet MAC 1
#define AT91C_ID_SSC              (28)  // Serial Synchronous Controller
#define AT91C_ID_CAN0             (29)  // CAN 0
#define AT91C_ID_CAN1             (30)  // CAN 1
#define AT91C_ID_IRQ              (31)  // Advanced Interrupt Controller (IRQ)
#define AT91C_ALL_INT             (0xFFFFFFFF)  // ALL VALID INTERRUPTS

// *****************************************************************************
//               BASE ADDRESS DEFINITIONS FOR AT91SAM9GX5
// *****************************************************************************
#define AT91C_BASE_SFR            (0xF8050000)  // (SFR) Base Address
#define AT91C_BASE_SYS            (0xFFFFC000)  // (SYS) Base Address
#define AT91C_BASE_EBI            (0xFFFFE000)  // (EBI) Base Address
#define AT91C_BASE_DDR2C          (0xFFFFE800)  // (DDR2C) Base Address
#define AT91C_BASE_SMC            (0xFFFFEA00)  // (SMC) Base Address
#define AT91C_BASE_MATRIX         (0xFFFFDE00)  // (MATRIX) Base Address
#define AT91C_BASE_CCFG           (0xFFFFDF10)  // (CCFG) Base Address
#define AT91C_BASE_AIC            (0xFFFFF000)  // (AIC) Base Address
#define AT91C_BASE_DBGU           (0xFFFFF200)  // (DBGU) Base Address
#define AT91C_BASE_PIOA           (0xFFFFF400)  // (PIOA) Base Address
#define AT91C_BASE_PIOB           (0xFFFFF600)  // (PIOB) Base Address
#define AT91C_BASE_PIOC           (0xFFFFF800)  // (PIOC) Base Address
#define AT91C_BASE_PIOD           (0xFFFFFA00)  // (PIOD) Base Address
#define AT91C_BASE_PMC            (0xFFFFFC00)  // (PMC) Base Address
#define AT91C_BASE_CKGR           (0xFFFFFC1C)  // (CKGR) Base Address
#define AT91C_BASE_RSTC           (0xFFFFFE00)  // (RSTC) Base Address
#define AT91C_BASE_SHDWC          (0xFFFFFE10)  // (SHDWC) Base Address
#define AT91C_BASE_RTTC           (0xFFFFFE20)  // (RTTC) Base Address
#define AT91C_BASE_PITC           (0xFFFFFE30)  // (PITC) Base Address
#define AT91C_BASE_WDTC           (0xFFFFFE40)  // (WDTC) Base Address
#define AT91C_BASE_RTC            (0xFFFFFEB0)  // (RTC) Base Address
#define AT91C_BASE_TC0            (0xF8008000)  // (TC0) Base Address
#define AT91C_BASE_TC1            (0xF8008040)  // (TC1) Base Address
#define AT91C_BASE_TC2            (0xF8008080)  // (TC2) Base Address
#define AT91C_BASE_TC3            (0xF800C000)  // (TC3) Base Address
#define AT91C_BASE_TC4            (0xF800C040)  // (TC4) Base Address
#define AT91C_BASE_TC5            (0xF800C080)  // (TC5) Base Address
#define AT91C_BASE_TCB0           (0xF8008000)  // (TCB0) Base Address
#define AT91C_BASE_TCB1           (0xF8008040)  // (TCB1) Base Address
#define AT91C_BASE_TCB2           (0xF8008080)  // (TCB2) Base Address
#define AT91C_BASE_TCB3           (0xF800C000)  // (TCB3) Base Address
#define AT91C_BASE_TCB4           (0xF800C040)  // (TCB4) Base Address
#define AT91C_BASE_TCB5           (0xF800C080)  // (TCB5) Base Address
#define AT91C_BASE_MCI0           (0xF0008000)  // (MCI0) Base Address
#define AT91C_BASE_MCI1           (0xF000C000)  // (MCI1) Base Address
#define AT91C_BASE_TWI0           (0xF8010000)  // (TWI0) Base Address
#define AT91C_BASE_TWI1           (0xF8014000)  // (TWI1) Base Address
#define AT91C_BASE_TWI2           (0xF8018000)  // (TWI2) Base Address
#define AT91C_BASE_US0            (0xF801C000)  // (US0) Base Address
#define AT91C_BASE_US1            (0xF8020000)  // (US1) Base Address
#define AT91C_BASE_US2            (0xF8024000)  // (US2) Base Address
#define AT91C_BASE_US3            (0xF8028000)  // (US3) Base Address
#define AT91C_BASE_SSC            (0xF0010000)  // (SSC) Base Address
#define AT91C_BASE_PWMC_CH0       (0xF8034200)  // (PWMC_CH0) Base Address
#define AT91C_BASE_PWMC_CH1       (0xF8034220)  // (PWMC_CH1) Base Address
#define AT91C_BASE_PWMC_CH2       (0xF8034240)  // (PWMC_CH2) Base Address
#define AT91C_BASE_PWMC_CH3       (0xF8034260)  // (PWMC_CH3) Base Address
#define AT91C_BASE_PWMC           (0xF8034000)  // (PWMC) Base Address
#define AT91C_BASE_SPI0           (0xF0000000)  // (SPI0) Base Address
#define AT91C_BASE_SPI1           (0xF0004000)  // (SPI1) Base Address
#define AT91C_BASE_TSADC          (0xF804C000)  // (TSADC) Base Address
#define AT91C_BASE_UART0          (0xF8040000)  // (UART0) Base Address
#define AT91C_BASE_UART1          (0xF8044000)  // (UART1) Base Address
#define AT91C_BASE_CAN0_MB0       (0xF8000200)  // (CAN0_MB0) Base Address
#define AT91C_BASE_CAN0_MB1       (0xF8000220)  // (CAN0_MB1) Base Address
#define AT91C_BASE_CAN0_MB2       (0xF8000240)  // (CAN0_MB2) Base Address
#define AT91C_BASE_CAN0_MB3       (0xF8000260)  // (CAN0_MB3) Base Address
#define AT91C_BASE_CAN0_MB4       (0xF8000280)  // (CAN0_MB4) Base Address
#define AT91C_BASE_CAN0_MB5       (0xF80002A0)  // (CAN0_MB5) Base Address
#define AT91C_BASE_CAN0_MB6       (0xF80002C0)  // (CAN0_MB6) Base Address
#define AT91C_BASE_CAN0_MB7       (0xF80002E0)  // (CAN0_MB7) Base Address
#define AT91C_BASE_CAN0           (0xF8000000)  // (CAN0) Base Address
#define AT91C_BASE_CAN1_MB0       (0xF8004200)  // (CAN1_MB0) Base Address
#define AT91C_BASE_CAN1_MB1       (0xF8004220)  // (CAN1_MB1) Base Address
#define AT91C_BASE_CAN1_MB2       (0xF8004240)  // (CAN1_MB2) Base Address
#define AT91C_BASE_CAN1_MB3       (0xF8004260)  // (CAN1_MB3) Base Address
#define AT91C_BASE_CAN1_MB4       (0xF8004280)  // (CAN1_MB4) Base Address
#define AT91C_BASE_CAN1_MB5       (0xF80042A0)  // (CAN1_MB5) Base Address
#define AT91C_BASE_CAN1_MB6       (0xF80042C0)  // (CAN1_MB6) Base Address
#define AT91C_BASE_CAN1_MB7       (0xF80042E0)  // (CAN1_MB7) Base Address
#define AT91C_BASE_CAN1           (0xF8004000)  // (CAN1) Base Address
#define AT91C_BASE_HSSD           (0x00400000)  // (HSSD) Base Address
#define AT91C_BASE_UDPHS_EPTFIFO  (0x00500000)  // (UDPHS_EPTFIFO) Base Address
#define AT91C_BASE_UDPHS_EPT_0    (0xF803C100)  // (UDPHS_EPT_0) Base Address
#define AT91C_BASE_UDPHS_EPT_1    (0xF803C120)  // (UDPHS_EPT_1) Base Address
#define AT91C_BASE_UDPHS_EPT_2    (0xF803C140)  // (UDPHS_EPT_2) Base Address
#define AT91C_BASE_UDPHS_EPT_3    (0xF803C160)  // (UDPHS_EPT_3) Base Address
#define AT91C_BASE_UDPHS_EPT_4    (0xF803C180)  // (UDPHS_EPT_4) Base Address
#define AT91C_BASE_UDPHS_EPT_5    (0xF803C1A0)  // (UDPHS_EPT_5) Base Address
#define AT91C_BASE_UDPHS_EPT_6    (0xF803C1C0)  // (UDPHS_EPT_6) Base Address
#define AT91C_BASE_UDPHS_DMA_1    (0xF803C310)  // (UDPHS_DMA_1) Base Address
#define AT91C_BASE_UDPHS_DMA_2    (0xF803C320)  // (UDPHS_DMA_2) Base Address
#define AT91C_BASE_UDPHS_DMA_3    (0xF803C330)  // (UDPHS_DMA_3) Base Address
#define AT91C_BASE_UDPHS_DMA_4    (0xF803C340)  // (UDPHS_DMA_4) Base Address
#define AT91C_BASE_UDPHS_DMA_5    (0xF803C350)  // (UDPHS_DMA_5) Base Address
#define AT91C_BASE_UDPHS_DMA_6    (0xF803C360)  // (UDPHS_DMA_6) Base Address
#define AT91C_BASE_UDPHS          (0xF803C000)  // (UDPHS) Base Address
#define AT91C_BASE_HLCDC4         (0xF8038000)  // (HLCDC4) Base Address
#define AT91C_BASE_HDMA0_CH_0     (0xFFFFEC3C)  // (HDMA0_CH_0) Base Address
#define AT91C_BASE_HDMA0_CH_1     (0xFFFFEC64)  // (HDMA0_CH_1) Base Address
#define AT91C_BASE_HDMA0_CH_2     (0xFFFFEC8C)  // (HDMA0_CH_2) Base Address
#define AT91C_BASE_HDMA0_CH_3     (0xFFFFECB4)  // (HDMA0_CH_3) Base Address
#define AT91C_BASE_HDMA0_CH_4     (0xFFFFECDC)  // (HDMA0_CH_4) Base Address
#define AT91C_BASE_HDMA0_CH_5     (0xFFFFED04)  // (HDMA0_CH_5) Base Address
#define AT91C_BASE_HDMA0_CH_6     (0xFFFFED2C)  // (HDMA0_CH_6) Base Address
#define AT91C_BASE_HDMA0_CH_7     (0xFFFFED54)  // (HDMA0_CH_7) Base Address
#define AT91C_BASE_HDMA0          (0xFFFFEC00)  // (HDMA0) Base Address
#define AT91C_BASE_HDMA1_CH_0     (0xFFFFEE3C)  // (HDMA1_CH_0) Base Address
#define AT91C_BASE_HDMA1_CH_1     (0xFFFFEE64)  // (HDMA1_CH_1) Base Address
#define AT91C_BASE_HDMA1_CH_2     (0xFFFFEE8C)  // (HDMA1_CH_2) Base Address
#define AT91C_BASE_HDMA1_CH_3     (0xFFFFEEB4)  // (HDMA1_CH_3) Base Address
#define AT91C_BASE_HDMA1_CH_4     (0xFFFFEEDC)  // (HDMA1_CH_4) Base Address
#define AT91C_BASE_HDMA1_CH_5     (0xFFFFEF04)  // (HDMA1_CH_5) Base Address
#define AT91C_BASE_HDMA1_CH_6     (0xFFFFEF2C)  // (HDMA1_CH_6) Base Address
#define AT91C_BASE_HDMA1_CH_7     (0xFFFFEF54)  // (HDMA1_CH_7) Base Address
#define AT91C_BASE_HDMA1          (0xFFFFEE00)  // (HDMA1) Base Address

#define AT91C_BASE_HDMA_CH_0     (0xFFFFEC3C)   // (HDMA_CH_0) Base Address
#define AT91C_BASE_HDMA_CH_1     (0xFFFFEC64)   // (HDMA_CH_1) Base Address
#define AT91C_BASE_HDMA_CH_2     (0xFFFFEC8C)   // (HDMA_CH_2) Base Address
#define AT91C_BASE_HDMA_CH_3     (0xFFFFECB4)   // (HDMA_CH_3) Base Address
#define AT91C_BASE_HDMA_CH_4     (0xFFFFECDC)   // (HDMA_CH_4) Base Address
#define AT91C_BASE_HDMA_CH_5     (0xFFFFED04)   // (HDMA_CH_5) Base Address
#define AT91C_BASE_HDMA_CH_6     (0xFFFFED2C)   // (HDMA_CH_6) Base Address
#define AT91C_BASE_HDMA_CH_7     (0xFFFFED54)   // (HDMA_CH_7) Base Address
#define AT91C_BASE_HDMA          (0xFFFFEC00)   // (HDMA) Base Address

#define AT91C_BASE_BCH_ECC_0      (0xFFFFE040)  // (BCH_ECC_0) Base Address
#define AT91C_BASE_BCH_ECC_1      (0xFFFFE080)  // (BCH_ECC_1) Base Address
#define AT91C_BASE_BCH_ECC_2      (0xFFFFE0C0)  // (BCH_ECC_2) Base Address
#define AT91C_BASE_BCH_ECC_3      (0xFFFFE100)  // (BCH_ECC_3) Base Address
#define AT91C_BASE_BCH_ECC_4      (0xFFFFE140)  // (BCH_ECC_4) Base Address
#define AT91C_BASE_BCH_ECC_5      (0xFFFFE180)  // (BCH_ECC_5) Base Address
#define AT91C_BASE_BCH_ECC_6      (0xFFFFE1C0)  // (BCH_ECC_6) Base Address
#define AT91C_BASE_BCH_ECC_7      (0xFFFFE200)  // (BCH_ECC_7) Base Address
#define AT91C_BASE_BCH_SYN_0      (0xFFFFE240)  // (BCH_SYN_0) Base Address
#define AT91C_BASE_BCH_SYN_1      (0xFFFFE280)  // (BCH_SYN_1) Base Address
#define AT91C_BASE_BCH_SYN_2      (0xFFFFE2C0)  // (BCH_SYN_2) Base Address
#define AT91C_BASE_BCH_SYN_3      (0xFFFFE300)  // (BCH_SYN_3) Base Address
#define AT91C_BASE_BCH_SYN_4      (0xFFFFE340)  // (BCH_SYN_4) Base Address
#define AT91C_BASE_BCH_SYN_5      (0xFFFFE380)  // (BCH_SYN_5) Base Address
#define AT91C_BASE_BCH_SYN_6      (0xFFFFE3C0)  // (BCH_SYN_6) Base Address
#define AT91C_BASE_BCH_SYN_7      (0xFFFFE400)  // (BCH_SYN_7) Base Address
#define AT91C_BASE_BCH            (0xFFFFE000)  // (BCH) Base Address
#define AT91C_BASE_BCHEL          (0xFFFFE600)  // (BCHEL) Base Address
#define AT91C_BASE_EMACB0         (0xF802C000)  // (EMACB0) Base Address
#define AT91C_BASE_EMACB1         (0xF8030000)  // (EMACB1) Base Address
#define AT91C_BASE_ISI            (0xF8048000)  // (ISI) Base Address
#define AT91C_BASE_UHPHS_OHCI     (0x00600000)  // (UHPHS_OHCI) Base Address
#define AT91C_BASE_UHPHS_EHCI     (0x00700000)  // (UHPHS_EHCI) Base Address

// *****************************************************************************
//               MEMORY MAPPING DEFINITIONS FOR AT91SAM9GX5
// *****************************************************************************
// IRAM_MIN
#define AT91C_IRAM_MIN	           (0x00300000) // Internal SRAM base address
#define AT91C_IRAM_MIN_SIZE	      (0x00008000)      // Internal SRAM size in byte (32 Kbytes)
// IROM
#define AT91C_IROM 	              (0x00100000)      // Internal ROM base address
#define AT91C_IROM_SIZE	          (0x00020000)  // Internal ROM size in byte (128 Kbytes)
// EBI_CS0
#define AT91C_EBI_CS0	            (0x10000000)        // EBI Chip Select 0 base address
#define AT91C_EBI_CS0_SIZE	       (0x10000000)     // EBI Chip Select 0 size in byte (262144 Kbytes)
// EBI_CS1
#define AT91C_EBI_CS1	            (0x20000000)        // EBI Chip Select 1 base address
#define AT91C_EBI_CS1_SIZE	       (0x10000000)     // EBI Chip Select 1 size in byte (262144 Kbytes)
// EBI_SDRAM
#define AT91C_EBI_SDRAM	          (0x20000000)  // SDRAM on EBI Chip Select 1 base address
#define AT91C_EBI_SDRAM_SIZE	     (0x10000000)       // SDRAM on EBI Chip Select 1 size in byte (262144 Kbytes)
// EBI_SDRAM_16BIT
#define AT91C_EBI_SDRAM_16BIT	    (0x20000000)        // SDRAM on EBI Chip Select 1 base address
#define AT91C_EBI_SDRAM_16BIT_SIZE	 (0x02000000)   // SDRAM on EBI Chip Select 1 size in byte (32768 Kbytes)
// EBI_SDRAM_32BIT
#define AT91C_EBI_SDRAM_32BIT	    (0x20000000)        // SDRAM on EBI Chip Select 1 base address
#define AT91C_EBI_SDRAM_32BIT_SIZE	 (0x04000000)   // SDRAM on EBI Chip Select 1 size in byte (65536 Kbytes)
// EBI_CS2
#define AT91C_EBI_CS2	            (0x30000000)        // EBI Chip Select 2 base address
#define AT91C_EBI_CS2_SIZE	       (0x10000000)     // EBI Chip Select 2 size in byte (262144 Kbytes)
// EBI_CS3
#define AT91C_EBI_CS3	            (0x40000000)        // EBI Chip Select 3 base address
#define AT91C_EBI_CS3_SIZE	       (0x10000000)     // EBI Chip Select 3 size in byte (262144 Kbytes)
// EBI_SM
#define AT91C_EBI_SM	             (0x40000000)       // NANDFLASH on EBI Chip Select 3 base address
#define AT91C_EBI_SM_SIZE	        (0x10000000)    // NANDFLASH on EBI Chip Select 3 size in byte (262144 Kbytes)
// EBI_CS4
#define AT91C_EBI_CS4	            (0x50000000)        // EBI Chip Select 4 base address
#define AT91C_EBI_CS4_SIZE	       (0x10000000)     // EBI Chip Select 4 size in byte (262144 Kbytes)
// EBI_CS5
#define AT91C_EBI_CS5	            (0x60000000)        // EBI Chip Select 5 base address
#define AT91C_EBI_CS5_SIZE	       (0x10000000)     // EBI Chip Select 5 size in byte (262144 Kbytes)

#define MCI2_INTERFACE

#define CHIP_DMA_CHANNEL_NUM   8

#define BOARD_SD_DMA_HW_SRC_REQ_ID      0
#define BOARD_SD_DMA_HW_DEST_REQ_ID     (0x0 <<  4)

#define BOARD_MCI_DMA_CHANNEL       0

#define BOARD_SD_MCI_BASE AT91C_BASE_MCI0
#define BOARD_SD_MCI_ID             AT91C_ID_MCI0
#define BOARD_SD_SLOT               MCI_SD_SLOTA
#define BOARD_SD_MCI_ID_USE			0

#define CHIP_SRAM0_BASEADDR 0x300000
