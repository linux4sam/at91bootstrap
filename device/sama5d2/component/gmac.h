/*
 * Component description for GMAC
 *
 * Copyright (c) 2023 Microchip Technology Inc. and its subsidiaries.
 *
 * Subject to your compliance with these terms, you may use Microchip software and any derivatives
 * exclusively with Microchip products. It is your responsibility to comply with third party license
 * terms applicable to your use of third party software (including open source software) that may
 * accompany Microchip software.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY,
 * APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND
 * FITNESS FOR A PARTICULAR PURPOSE.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, INCIDENTAL OR CONSEQUENTIAL
 * LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF
 * MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE FULLEST EXTENT
 * ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT
 * EXCEED THE AMOUNT OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/* file generated from device description version 2022-11-18T13:40:01Z */
#ifndef _SAMA5D_GMAC_COMPONENT_H_
#define _SAMA5D_GMAC_COMPONENT_H_

/* ************************************************************************** */
/*   SOFTWARE API DEFINITION FOR GMAC                                         */
/* ************************************************************************** */

/* -------- GMAC_SAB : (GMAC Offset: 0x00) (R/W 32) Specific Address 1 Bottom Register -------- */
#define GMAC_SAB_ADDR_Pos                     _UINT32_(0)                                          /* (GMAC_SAB) Specific Address 1 Position */
#define GMAC_SAB_ADDR_Msk                     (_UINT32_(0xFFFFFFFF) << GMAC_SAB_ADDR_Pos)          /* (GMAC_SAB) Specific Address 1 Mask */
#define GMAC_SAB_ADDR(value)                  (GMAC_SAB_ADDR_Msk & (_UINT32_(value) << GMAC_SAB_ADDR_Pos)) /* Assigment of value for ADDR in the GMAC_SAB register */
#define GMAC_SAB_Msk                          _UINT32_(0xFFFFFFFF)                                 /* (GMAC_SAB) Register Mask  */


/* -------- GMAC_SAT : (GMAC Offset: 0x04) (R/W 32) Specific Address 1 Top Register -------- */
#define GMAC_SAT_ADDR_Pos                     _UINT32_(0)                                          /* (GMAC_SAT) Specific Address 2 Position */
#define GMAC_SAT_ADDR_Msk                     (_UINT32_(0xFFFF) << GMAC_SAT_ADDR_Pos)              /* (GMAC_SAT) Specific Address 2 Mask */
#define GMAC_SAT_ADDR(value)                  (GMAC_SAT_ADDR_Msk & (_UINT32_(value) << GMAC_SAT_ADDR_Pos)) /* Assigment of value for ADDR in the GMAC_SAT register */
#define GMAC_SAT_FILTSORD_Pos                 _UINT32_(16)                                         /* (GMAC_SAT) Filter Source or Destination MAC Address Position */
#define GMAC_SAT_FILTSORD_Msk                 (_UINT32_(0x1) << GMAC_SAT_FILTSORD_Pos)             /* (GMAC_SAT) Filter Source or Destination MAC Address Mask */
#define GMAC_SAT_FILTSORD(value)              (GMAC_SAT_FILTSORD_Msk & (_UINT32_(value) << GMAC_SAT_FILTSORD_Pos)) /* Assigment of value for FILTSORD in the GMAC_SAT register */
#define   GMAC_SAT_FILTSORD_0_Val             _UINT32_(0x0)                                        /* (GMAC_SAT) The filter is a destination address filter.  */
#define   GMAC_SAT_FILTSORD_1_Val             _UINT32_(0x1)                                        /* (GMAC_SAT) The filter is a source address filter.  */
#define GMAC_SAT_FILTSORD_0                   (GMAC_SAT_FILTSORD_0_Val << GMAC_SAT_FILTSORD_Pos)   /* (GMAC_SAT) The filter is a destination address filter. Position  */
#define GMAC_SAT_FILTSORD_1                   (GMAC_SAT_FILTSORD_1_Val << GMAC_SAT_FILTSORD_Pos)   /* (GMAC_SAT) The filter is a source address filter. Position  */
#define GMAC_SAT_FILTBMASK_Pos                _UINT32_(24)                                         /* (GMAC_SAT) Filter Bytes Mask Position */
#define GMAC_SAT_FILTBMASK_Msk                (_UINT32_(0x3F) << GMAC_SAT_FILTBMASK_Pos)           /* (GMAC_SAT) Filter Bytes Mask Mask */
#define GMAC_SAT_FILTBMASK(value)             (GMAC_SAT_FILTBMASK_Msk & (_UINT32_(value) << GMAC_SAT_FILTBMASK_Pos)) /* Assigment of value for FILTBMASK in the GMAC_SAT register */
#define   GMAC_SAT_FILTBMASK_BIT1_Val         _UINT32_(0x1)                                        /* (GMAC_SAT) Controls whether the first byte has been received.  */
#define   GMAC_SAT_FILTBMASK_BIT2_Val         _UINT32_(0x2)                                        /* (GMAC_SAT) Controls whether the second byte has been received.  */
#define   GMAC_SAT_FILTBMASK_BIT3_Val         _UINT32_(0x4)                                        /* (GMAC_SAT) Controls whether the third byte has been received.  */
#define   GMAC_SAT_FILTBMASK_BIT4_Val         _UINT32_(0x8)                                        /* (GMAC_SAT) Controls whether the fourth byte has been received.  */
#define   GMAC_SAT_FILTBMASK_BIT5_Val         _UINT32_(0x10)                                       /* (GMAC_SAT) Controls whether the fifth byte has been received.  */
#define   GMAC_SAT_FILTBMASK_BIT6_Val         _UINT32_(0x20)                                       /* (GMAC_SAT) Controls whether the sixth byte has been received  */
#define GMAC_SAT_FILTBMASK_BIT1               (GMAC_SAT_FILTBMASK_BIT1_Val << GMAC_SAT_FILTBMASK_Pos) /* (GMAC_SAT) Controls whether the first byte has been received. Position  */
#define GMAC_SAT_FILTBMASK_BIT2               (GMAC_SAT_FILTBMASK_BIT2_Val << GMAC_SAT_FILTBMASK_Pos) /* (GMAC_SAT) Controls whether the second byte has been received. Position  */
#define GMAC_SAT_FILTBMASK_BIT3               (GMAC_SAT_FILTBMASK_BIT3_Val << GMAC_SAT_FILTBMASK_Pos) /* (GMAC_SAT) Controls whether the third byte has been received. Position  */
#define GMAC_SAT_FILTBMASK_BIT4               (GMAC_SAT_FILTBMASK_BIT4_Val << GMAC_SAT_FILTBMASK_Pos) /* (GMAC_SAT) Controls whether the fourth byte has been received. Position  */
#define GMAC_SAT_FILTBMASK_BIT5               (GMAC_SAT_FILTBMASK_BIT5_Val << GMAC_SAT_FILTBMASK_Pos) /* (GMAC_SAT) Controls whether the fifth byte has been received. Position  */
#define GMAC_SAT_FILTBMASK_BIT6               (GMAC_SAT_FILTBMASK_BIT6_Val << GMAC_SAT_FILTBMASK_Pos) /* (GMAC_SAT) Controls whether the sixth byte has been received Position  */
#define GMAC_SAT_Msk                          _UINT32_(0x3F01FFFF)                                 /* (GMAC_SAT) Register Mask  */


/* -------- GMAC_ST2CW0 : (GMAC Offset: 0x00) (R/W 32) Screening Type 2 Compare Word 0 Register  -------- */
#define GMAC_ST2CW0_RESETVALUE                _UINT32_(0x00)                                       /*  (GMAC_ST2CW0) Screening Type 2 Compare Word 0 Register   Reset Value */

#define GMAC_ST2CW0_MASKVAL_Pos               _UINT32_(0)                                          /* (GMAC_ST2CW0) Mask Value Position */
#define GMAC_ST2CW0_MASKVAL_Msk               (_UINT32_(0xFFFF) << GMAC_ST2CW0_MASKVAL_Pos)        /* (GMAC_ST2CW0) Mask Value Mask */
#define GMAC_ST2CW0_MASKVAL(value)            (GMAC_ST2CW0_MASKVAL_Msk & (_UINT32_(value) << GMAC_ST2CW0_MASKVAL_Pos)) /* Assigment of value for MASKVAL in the GMAC_ST2CW0 register */
#define GMAC_ST2CW0_COMPVAL_Pos               _UINT32_(16)                                         /* (GMAC_ST2CW0) Compare Value Position */
#define GMAC_ST2CW0_COMPVAL_Msk               (_UINT32_(0xFFFF) << GMAC_ST2CW0_COMPVAL_Pos)        /* (GMAC_ST2CW0) Compare Value Mask */
#define GMAC_ST2CW0_COMPVAL(value)            (GMAC_ST2CW0_COMPVAL_Msk & (_UINT32_(value) << GMAC_ST2CW0_COMPVAL_Pos)) /* Assigment of value for COMPVAL in the GMAC_ST2CW0 register */
#define GMAC_ST2CW0_Msk                       _UINT32_(0xFFFFFFFF)                                 /* (GMAC_ST2CW0) Register Mask  */


/* -------- GMAC_ST2CW1 : (GMAC Offset: 0x04) (R/W 32) Screening Type 2 Compare Word 1 Register  -------- */
#define GMAC_ST2CW1_RESETVALUE                _UINT32_(0x00)                                       /*  (GMAC_ST2CW1) Screening Type 2 Compare Word 1 Register   Reset Value */

#define GMAC_ST2CW1_OFFSVAL_Pos               _UINT32_(0)                                          /* (GMAC_ST2CW1) Offset Value in Bytes Position */
#define GMAC_ST2CW1_OFFSVAL_Msk               (_UINT32_(0x7F) << GMAC_ST2CW1_OFFSVAL_Pos)          /* (GMAC_ST2CW1) Offset Value in Bytes Mask */
#define GMAC_ST2CW1_OFFSVAL(value)            (GMAC_ST2CW1_OFFSVAL_Msk & (_UINT32_(value) << GMAC_ST2CW1_OFFSVAL_Pos)) /* Assigment of value for OFFSVAL in the GMAC_ST2CW1 register */
#define GMAC_ST2CW1_OFFSSTRT_Pos              _UINT32_(7)                                          /* (GMAC_ST2CW1) Ethernet Frame Offset Start Position */
#define GMAC_ST2CW1_OFFSSTRT_Msk              (_UINT32_(0x3) << GMAC_ST2CW1_OFFSSTRT_Pos)          /* (GMAC_ST2CW1) Ethernet Frame Offset Start Mask */
#define GMAC_ST2CW1_OFFSSTRT(value)           (GMAC_ST2CW1_OFFSSTRT_Msk & (_UINT32_(value) << GMAC_ST2CW1_OFFSSTRT_Pos)) /* Assigment of value for OFFSSTRT in the GMAC_ST2CW1 register */
#define   GMAC_ST2CW1_OFFSSTRT_FRAMESTART_Val _UINT32_(0x0)                                        /* (GMAC_ST2CW1) Offset from the start of the frame  */
#define   GMAC_ST2CW1_OFFSSTRT_ETHERTYPE_Val  _UINT32_(0x1)                                        /* (GMAC_ST2CW1) Offset from the byte after the EtherType field  */
#define   GMAC_ST2CW1_OFFSSTRT_IP_Val         _UINT32_(0x2)                                        /* (GMAC_ST2CW1) Offset from the byte after the IP header field  */
#define   GMAC_ST2CW1_OFFSSTRT_TCP_UDP_Val    _UINT32_(0x3)                                        /* (GMAC_ST2CW1) Offset from the byte after the TCP/UDP header field  */
#define GMAC_ST2CW1_OFFSSTRT_FRAMESTART       (GMAC_ST2CW1_OFFSSTRT_FRAMESTART_Val << GMAC_ST2CW1_OFFSSTRT_Pos) /* (GMAC_ST2CW1) Offset from the start of the frame Position  */
#define GMAC_ST2CW1_OFFSSTRT_ETHERTYPE        (GMAC_ST2CW1_OFFSSTRT_ETHERTYPE_Val << GMAC_ST2CW1_OFFSSTRT_Pos) /* (GMAC_ST2CW1) Offset from the byte after the EtherType field Position  */
#define GMAC_ST2CW1_OFFSSTRT_IP               (GMAC_ST2CW1_OFFSSTRT_IP_Val << GMAC_ST2CW1_OFFSSTRT_Pos) /* (GMAC_ST2CW1) Offset from the byte after the IP header field Position  */
#define GMAC_ST2CW1_OFFSSTRT_TCP_UDP          (GMAC_ST2CW1_OFFSSTRT_TCP_UDP_Val << GMAC_ST2CW1_OFFSSTRT_Pos) /* (GMAC_ST2CW1) Offset from the byte after the TCP/UDP header field Position  */
#define GMAC_ST2CW1_DISMASK_Pos               _UINT32_(9)                                          /* (GMAC_ST2CW1) Disable Mask Position */
#define GMAC_ST2CW1_DISMASK_Msk               (_UINT32_(0x1) << GMAC_ST2CW1_DISMASK_Pos)           /* (GMAC_ST2CW1) Disable Mask Mask */
#define GMAC_ST2CW1_DISMASK(value)            (GMAC_ST2CW1_DISMASK_Msk & (_UINT32_(value) << GMAC_ST2CW1_DISMASK_Pos)) /* Assigment of value for DISMASK in the GMAC_ST2CW1 register */
#define   GMAC_ST2CW1_DISMASK_0_Val           _UINT32_(0x0)                                        /* (GMAC_ST2CW1) GMAC_ST2CW0R contains a 2-byte compare value with a 2-byte mask value.  */
#define   GMAC_ST2CW1_DISMASK_1_Val           _UINT32_(0x1)                                        /* (GMAC_ST2CW1) GMAC_ST2CW0R contains a 4-byte compare value.  */
#define GMAC_ST2CW1_DISMASK_0                 (GMAC_ST2CW1_DISMASK_0_Val << GMAC_ST2CW1_DISMASK_Pos) /* (GMAC_ST2CW1) GMAC_ST2CW0R contains a 2-byte compare value with a 2-byte mask value. Position  */
#define GMAC_ST2CW1_DISMASK_1                 (GMAC_ST2CW1_DISMASK_1_Val << GMAC_ST2CW1_DISMASK_Pos) /* (GMAC_ST2CW1) GMAC_ST2CW0R contains a 4-byte compare value. Position  */
#define GMAC_ST2CW1_Msk                       _UINT32_(0x000003FF)                                 /* (GMAC_ST2CW1) Register Mask  */


/* -------- GMAC_NCR : (GMAC Offset: 0x00) (R/W 32) Network Control Register -------- */
#define GMAC_NCR_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_NCR) Network Control Register  Reset Value */

#define GMAC_NCR_LBL_Pos                      _UINT32_(1)                                          /* (GMAC_NCR) Loop Back Local Position */
#define GMAC_NCR_LBL_Msk                      (_UINT32_(0x1) << GMAC_NCR_LBL_Pos)                  /* (GMAC_NCR) Loop Back Local Mask */
#define GMAC_NCR_LBL(value)                   (GMAC_NCR_LBL_Msk & (_UINT32_(value) << GMAC_NCR_LBL_Pos)) /* Assigment of value for LBL in the GMAC_NCR register */
#define   GMAC_NCR_LBL_0_Val                  _UINT32_(0x0)                                        /* (GMAC_NCR) Normal operating mode (no loop back).  */
#define   GMAC_NCR_LBL_1_Val                  _UINT32_(0x1)                                        /* (GMAC_NCR) Connects GTX to GRX, GTXEN to GRXDV and forces Full Duplex mode. GRXCK and GTXCK may malfunction as the GMAC is switched into and out of internal loop back. It is important that receive and transmit circuits have already been disabled when making the switch into and out of internal loop back.  */
#define GMAC_NCR_LBL_0                        (GMAC_NCR_LBL_0_Val << GMAC_NCR_LBL_Pos)             /* (GMAC_NCR) Normal operating mode (no loop back). Position  */
#define GMAC_NCR_LBL_1                        (GMAC_NCR_LBL_1_Val << GMAC_NCR_LBL_Pos)             /* (GMAC_NCR) Connects GTX to GRX, GTXEN to GRXDV and forces Full Duplex mode. GRXCK and GTXCK may malfunction as the GMAC is switched into and out of internal loop back. It is important that receive and transmit circuits have already been disabled when making the switch into and out of internal loop back. Position  */
#define GMAC_NCR_RXEN_Pos                     _UINT32_(2)                                          /* (GMAC_NCR) Receive Enable Position */
#define GMAC_NCR_RXEN_Msk                     (_UINT32_(0x1) << GMAC_NCR_RXEN_Pos)                 /* (GMAC_NCR) Receive Enable Mask */
#define GMAC_NCR_RXEN(value)                  (GMAC_NCR_RXEN_Msk & (_UINT32_(value) << GMAC_NCR_RXEN_Pos)) /* Assigment of value for RXEN in the GMAC_NCR register */
#define   GMAC_NCR_RXEN_0_Val                 _UINT32_(0x0)                                        /* (GMAC_NCR) Stops frame reception immediately and the receive pipeline will be cleared. The Receive Queue Pointer register is unaffected.  */
#define   GMAC_NCR_RXEN_1_Val                 _UINT32_(0x1)                                        /* (GMAC_NCR) Enables the GMAC to receive data.  */
#define GMAC_NCR_RXEN_0                       (GMAC_NCR_RXEN_0_Val << GMAC_NCR_RXEN_Pos)           /* (GMAC_NCR) Stops frame reception immediately and the receive pipeline will be cleared. The Receive Queue Pointer register is unaffected. Position  */
#define GMAC_NCR_RXEN_1                       (GMAC_NCR_RXEN_1_Val << GMAC_NCR_RXEN_Pos)           /* (GMAC_NCR) Enables the GMAC to receive data. Position  */
#define GMAC_NCR_TXEN_Pos                     _UINT32_(3)                                          /* (GMAC_NCR) Transmit Enable Position */
#define GMAC_NCR_TXEN_Msk                     (_UINT32_(0x1) << GMAC_NCR_TXEN_Pos)                 /* (GMAC_NCR) Transmit Enable Mask */
#define GMAC_NCR_TXEN(value)                  (GMAC_NCR_TXEN_Msk & (_UINT32_(value) << GMAC_NCR_TXEN_Pos)) /* Assigment of value for TXEN in the GMAC_NCR register */
#define   GMAC_NCR_TXEN_0_Val                 _UINT32_(0x0)                                        /* (GMAC_NCR) Stops transmission immediately, the transmit pipeline and control registers will be cleared and the Transmit Queue Pointer Register will reset to point to the start of the transmit descriptor list.  */
#define   GMAC_NCR_TXEN_1_Val                 _UINT32_(0x1)                                        /* (GMAC_NCR) Enables the GMAC transmitter to send data.  */
#define GMAC_NCR_TXEN_0                       (GMAC_NCR_TXEN_0_Val << GMAC_NCR_TXEN_Pos)           /* (GMAC_NCR) Stops transmission immediately, the transmit pipeline and control registers will be cleared and the Transmit Queue Pointer Register will reset to point to the start of the transmit descriptor list. Position  */
#define GMAC_NCR_TXEN_1                       (GMAC_NCR_TXEN_1_Val << GMAC_NCR_TXEN_Pos)           /* (GMAC_NCR) Enables the GMAC transmitter to send data. Position  */
#define GMAC_NCR_MPE_Pos                      _UINT32_(4)                                          /* (GMAC_NCR) Management Port Enable Position */
#define GMAC_NCR_MPE_Msk                      (_UINT32_(0x1) << GMAC_NCR_MPE_Pos)                  /* (GMAC_NCR) Management Port Enable Mask */
#define GMAC_NCR_MPE(value)                   (GMAC_NCR_MPE_Msk & (_UINT32_(value) << GMAC_NCR_MPE_Pos)) /* Assigment of value for MPE in the GMAC_NCR register */
#define   GMAC_NCR_MPE_0_Val                  _UINT32_(0x0)                                        /* (GMAC_NCR) Forces GMDIO to high impedance state and MDC low.  */
#define   GMAC_NCR_MPE_1_Val                  _UINT32_(0x1)                                        /* (GMAC_NCR) Enables the management port.  */
#define GMAC_NCR_MPE_0                        (GMAC_NCR_MPE_0_Val << GMAC_NCR_MPE_Pos)             /* (GMAC_NCR) Forces GMDIO to high impedance state and MDC low. Position  */
#define GMAC_NCR_MPE_1                        (GMAC_NCR_MPE_1_Val << GMAC_NCR_MPE_Pos)             /* (GMAC_NCR) Enables the management port. Position  */
#define GMAC_NCR_CLRSTAT_Pos                  _UINT32_(5)                                          /* (GMAC_NCR) Clear Statistics Registers (Write-only) Position */
#define GMAC_NCR_CLRSTAT_Msk                  (_UINT32_(0x1) << GMAC_NCR_CLRSTAT_Pos)              /* (GMAC_NCR) Clear Statistics Registers (Write-only) Mask */
#define GMAC_NCR_CLRSTAT(value)               (GMAC_NCR_CLRSTAT_Msk & (_UINT32_(value) << GMAC_NCR_CLRSTAT_Pos)) /* Assigment of value for CLRSTAT in the GMAC_NCR register */
#define   GMAC_NCR_CLRSTAT_0_Val              _UINT32_(0x0)                                        /* (GMAC_NCR) No effect.  */
#define   GMAC_NCR_CLRSTAT_1_Val              _UINT32_(0x1)                                        /* (GMAC_NCR) Clears the statistics registers.  */
#define GMAC_NCR_CLRSTAT_0                    (GMAC_NCR_CLRSTAT_0_Val << GMAC_NCR_CLRSTAT_Pos)     /* (GMAC_NCR) No effect. Position  */
#define GMAC_NCR_CLRSTAT_1                    (GMAC_NCR_CLRSTAT_1_Val << GMAC_NCR_CLRSTAT_Pos)     /* (GMAC_NCR) Clears the statistics registers. Position  */
#define GMAC_NCR_INCSTAT_Pos                  _UINT32_(6)                                          /* (GMAC_NCR) Increment Statistics Registers (Write-only) Position */
#define GMAC_NCR_INCSTAT_Msk                  (_UINT32_(0x1) << GMAC_NCR_INCSTAT_Pos)              /* (GMAC_NCR) Increment Statistics Registers (Write-only) Mask */
#define GMAC_NCR_INCSTAT(value)               (GMAC_NCR_INCSTAT_Msk & (_UINT32_(value) << GMAC_NCR_INCSTAT_Pos)) /* Assigment of value for INCSTAT in the GMAC_NCR register */
#define GMAC_NCR_WESTAT_Pos                   _UINT32_(7)                                          /* (GMAC_NCR) Write Enable for Statistics Registers Position */
#define GMAC_NCR_WESTAT_Msk                   (_UINT32_(0x1) << GMAC_NCR_WESTAT_Pos)               /* (GMAC_NCR) Write Enable for Statistics Registers Mask */
#define GMAC_NCR_WESTAT(value)                (GMAC_NCR_WESTAT_Msk & (_UINT32_(value) << GMAC_NCR_WESTAT_Pos)) /* Assigment of value for WESTAT in the GMAC_NCR register */
#define   GMAC_NCR_WESTAT_0_Val               _UINT32_(0x0)                                        /* (GMAC_NCR) Forces the statistics registers to be in read-only mode for normal operation mode.  */
#define   GMAC_NCR_WESTAT_1_Val               _UINT32_(0x1)                                        /* (GMAC_NCR) Makes the statistics registers writable for functional test purposes.  */
#define GMAC_NCR_WESTAT_0                     (GMAC_NCR_WESTAT_0_Val << GMAC_NCR_WESTAT_Pos)       /* (GMAC_NCR) Forces the statistics registers to be in read-only mode for normal operation mode. Position  */
#define GMAC_NCR_WESTAT_1                     (GMAC_NCR_WESTAT_1_Val << GMAC_NCR_WESTAT_Pos)       /* (GMAC_NCR) Makes the statistics registers writable for functional test purposes. Position  */
#define GMAC_NCR_BP_Pos                       _UINT32_(8)                                          /* (GMAC_NCR) Back Pressure Position */
#define GMAC_NCR_BP_Msk                       (_UINT32_(0x1) << GMAC_NCR_BP_Pos)                   /* (GMAC_NCR) Back Pressure Mask */
#define GMAC_NCR_BP(value)                    (GMAC_NCR_BP_Msk & (_UINT32_(value) << GMAC_NCR_BP_Pos)) /* Assigment of value for BP in the GMAC_NCR register */
#define   GMAC_NCR_BP_0_Val                   _UINT32_(0x0)                                        /* (GMAC_NCR) No effect  */
#define   GMAC_NCR_BP_1_Val                   _UINT32_(0x1)                                        /* (GMAC_NCR) When the MAC is set in 10M or 100M Half Duplex mode, forces collisions on all received frames.  */
#define GMAC_NCR_BP_0                         (GMAC_NCR_BP_0_Val << GMAC_NCR_BP_Pos)               /* (GMAC_NCR) No effect Position  */
#define GMAC_NCR_BP_1                         (GMAC_NCR_BP_1_Val << GMAC_NCR_BP_Pos)               /* (GMAC_NCR) When the MAC is set in 10M or 100M Half Duplex mode, forces collisions on all received frames. Position  */
#define GMAC_NCR_TSTART_Pos                   _UINT32_(9)                                          /* (GMAC_NCR) Start Transmission (Write-only) Position */
#define GMAC_NCR_TSTART_Msk                   (_UINT32_(0x1) << GMAC_NCR_TSTART_Pos)               /* (GMAC_NCR) Start Transmission (Write-only) Mask */
#define GMAC_NCR_TSTART(value)                (GMAC_NCR_TSTART_Msk & (_UINT32_(value) << GMAC_NCR_TSTART_Pos)) /* Assigment of value for TSTART in the GMAC_NCR register */
#define   GMAC_NCR_TSTART_0_Val               _UINT32_(0x0)                                        /* (GMAC_NCR) No effect.  */
#define   GMAC_NCR_TSTART_1_Val               _UINT32_(0x1)                                        /* (GMAC_NCR) Starts transmission.  */
#define GMAC_NCR_TSTART_0                     (GMAC_NCR_TSTART_0_Val << GMAC_NCR_TSTART_Pos)       /* (GMAC_NCR) No effect. Position  */
#define GMAC_NCR_TSTART_1                     (GMAC_NCR_TSTART_1_Val << GMAC_NCR_TSTART_Pos)       /* (GMAC_NCR) Starts transmission. Position  */
#define GMAC_NCR_THALT_Pos                    _UINT32_(10)                                         /* (GMAC_NCR) Transmit Halt (Write-only) Position */
#define GMAC_NCR_THALT_Msk                    (_UINT32_(0x1) << GMAC_NCR_THALT_Pos)                /* (GMAC_NCR) Transmit Halt (Write-only) Mask */
#define GMAC_NCR_THALT(value)                 (GMAC_NCR_THALT_Msk & (_UINT32_(value) << GMAC_NCR_THALT_Pos)) /* Assigment of value for THALT in the GMAC_NCR register */
#define   GMAC_NCR_THALT_0_Val                _UINT32_(0x0)                                        /* (GMAC_NCR) No effect.  */
#define   GMAC_NCR_THALT_1_Val                _UINT32_(0x1)                                        /* (GMAC_NCR) Halts transmission as soon as any ongoing frame transmission ends.  */
#define GMAC_NCR_THALT_0                      (GMAC_NCR_THALT_0_Val << GMAC_NCR_THALT_Pos)         /* (GMAC_NCR) No effect. Position  */
#define GMAC_NCR_THALT_1                      (GMAC_NCR_THALT_1_Val << GMAC_NCR_THALT_Pos)         /* (GMAC_NCR) Halts transmission as soon as any ongoing frame transmission ends. Position  */
#define GMAC_NCR_TXPF_Pos                     _UINT32_(11)                                         /* (GMAC_NCR) Transmit Pause Frame (Write-only) Position */
#define GMAC_NCR_TXPF_Msk                     (_UINT32_(0x1) << GMAC_NCR_TXPF_Pos)                 /* (GMAC_NCR) Transmit Pause Frame (Write-only) Mask */
#define GMAC_NCR_TXPF(value)                  (GMAC_NCR_TXPF_Msk & (_UINT32_(value) << GMAC_NCR_TXPF_Pos)) /* Assigment of value for TXPF in the GMAC_NCR register */
#define   GMAC_NCR_TXPF_0_Val                 _UINT32_(0x0)                                        /* (GMAC_NCR) No effect.  */
#define   GMAC_NCR_TXPF_1_Val                 _UINT32_(0x1)                                        /* (GMAC_NCR) Generates a pause frame to be transmitted.  */
#define GMAC_NCR_TXPF_0                       (GMAC_NCR_TXPF_0_Val << GMAC_NCR_TXPF_Pos)           /* (GMAC_NCR) No effect. Position  */
#define GMAC_NCR_TXPF_1                       (GMAC_NCR_TXPF_1_Val << GMAC_NCR_TXPF_Pos)           /* (GMAC_NCR) Generates a pause frame to be transmitted. Position  */
#define GMAC_NCR_TXZQPF_Pos                   _UINT32_(12)                                         /* (GMAC_NCR) Transmit Zero Quantum Pause Frame (Write-only) Position */
#define GMAC_NCR_TXZQPF_Msk                   (_UINT32_(0x1) << GMAC_NCR_TXZQPF_Pos)               /* (GMAC_NCR) Transmit Zero Quantum Pause Frame (Write-only) Mask */
#define GMAC_NCR_TXZQPF(value)                (GMAC_NCR_TXZQPF_Msk & (_UINT32_(value) << GMAC_NCR_TXZQPF_Pos)) /* Assigment of value for TXZQPF in the GMAC_NCR register */
#define   GMAC_NCR_TXZQPF_0_Val               _UINT32_(0x0)                                        /* (GMAC_NCR) No effect.  */
#define   GMAC_NCR_TXZQPF_1_Val               _UINT32_(0x1)                                        /* (GMAC_NCR) Generates a pause frame with zero quantum to be transmitted.  */
#define GMAC_NCR_TXZQPF_0                     (GMAC_NCR_TXZQPF_0_Val << GMAC_NCR_TXZQPF_Pos)       /* (GMAC_NCR) No effect. Position  */
#define GMAC_NCR_TXZQPF_1                     (GMAC_NCR_TXZQPF_1_Val << GMAC_NCR_TXZQPF_Pos)       /* (GMAC_NCR) Generates a pause frame with zero quantum to be transmitted. Position  */
#define GMAC_NCR_SRTSM_Pos                    _UINT32_(15)                                         /* (GMAC_NCR) Store Receive Timestamp to Memory Position */
#define GMAC_NCR_SRTSM_Msk                    (_UINT32_(0x1) << GMAC_NCR_SRTSM_Pos)                /* (GMAC_NCR) Store Receive Timestamp to Memory Mask */
#define GMAC_NCR_SRTSM(value)                 (GMAC_NCR_SRTSM_Msk & (_UINT32_(value) << GMAC_NCR_SRTSM_Pos)) /* Assigment of value for SRTSM in the GMAC_NCR register */
#define   GMAC_NCR_SRTSM_0_Val                _UINT32_(0x0)                                        /* (GMAC_NCR) No effect.  */
#define   GMAC_NCR_SRTSM_1_Val                _UINT32_(0x1)                                        /* (GMAC_NCR) Causes the CRC of every received frame to be replaced with the value of the nanoseconds field of the 1588 timer that was captured as the receive frame passed the message timestamp point. Note that bit RFCS in register GMAC_NCFGR may not be set to 1 when the timer should be captured.  */
#define GMAC_NCR_SRTSM_0                      (GMAC_NCR_SRTSM_0_Val << GMAC_NCR_SRTSM_Pos)         /* (GMAC_NCR) No effect. Position  */
#define GMAC_NCR_SRTSM_1                      (GMAC_NCR_SRTSM_1_Val << GMAC_NCR_SRTSM_Pos)         /* (GMAC_NCR) Causes the CRC of every received frame to be replaced with the value of the nanoseconds field of the 1588 timer that was captured as the receive frame passed the message timestamp point. Note that bit RFCS in register GMAC_NCFGR may not be set to 1 when the timer should be captured. Position  */
#define GMAC_NCR_ENPBPR_Pos                   _UINT32_(16)                                         /* (GMAC_NCR) Enable PFC Priority-based Pause Reception Position */
#define GMAC_NCR_ENPBPR_Msk                   (_UINT32_(0x1) << GMAC_NCR_ENPBPR_Pos)               /* (GMAC_NCR) Enable PFC Priority-based Pause Reception Mask */
#define GMAC_NCR_ENPBPR(value)                (GMAC_NCR_ENPBPR_Msk & (_UINT32_(value) << GMAC_NCR_ENPBPR_Pos)) /* Assigment of value for ENPBPR in the GMAC_NCR register */
#define GMAC_NCR_TXPBPF_Pos                   _UINT32_(17)                                         /* (GMAC_NCR) Transmit PFC Priority-based Pause Frame Position */
#define GMAC_NCR_TXPBPF_Msk                   (_UINT32_(0x1) << GMAC_NCR_TXPBPF_Pos)               /* (GMAC_NCR) Transmit PFC Priority-based Pause Frame Mask */
#define GMAC_NCR_TXPBPF(value)                (GMAC_NCR_TXPBPF_Msk & (_UINT32_(value) << GMAC_NCR_TXPBPF_Pos)) /* Assigment of value for TXPBPF in the GMAC_NCR register */
#define   GMAC_NCR_TXPBPF_0_Val               _UINT32_(0x0)                                        /* (GMAC_NCR) No effect.  */
#define   GMAC_NCR_TXPBPF_1_Val               _UINT32_(0x1)                                        /* (GMAC_NCR) Takes the values stored in the Transmit PFC Pause Register.  */
#define GMAC_NCR_TXPBPF_0                     (GMAC_NCR_TXPBPF_0_Val << GMAC_NCR_TXPBPF_Pos)       /* (GMAC_NCR) No effect. Position  */
#define GMAC_NCR_TXPBPF_1                     (GMAC_NCR_TXPBPF_1_Val << GMAC_NCR_TXPBPF_Pos)       /* (GMAC_NCR) Takes the values stored in the Transmit PFC Pause Register. Position  */
#define GMAC_NCR_FNP_Pos                      _UINT32_(18)                                         /* (GMAC_NCR) Flush Next Packet Position */
#define GMAC_NCR_FNP_Msk                      (_UINT32_(0x1) << GMAC_NCR_FNP_Pos)                  /* (GMAC_NCR) Flush Next Packet Mask */
#define GMAC_NCR_FNP(value)                   (GMAC_NCR_FNP_Msk & (_UINT32_(value) << GMAC_NCR_FNP_Pos)) /* Assigment of value for FNP in the GMAC_NCR register */
#define   GMAC_NCR_FNP_0_Val                  _UINT32_(0x0)                                        /* (GMAC_NCR) No effect.  */
#define   GMAC_NCR_FNP_1_Val                  _UINT32_(0x1)                                        /* (GMAC_NCR) Flushes the next packet from the receive memory. This will only have an effect if the DMA is not currently writing a packet already stored in the receive memory to system memory.  */
#define GMAC_NCR_FNP_0                        (GMAC_NCR_FNP_0_Val << GMAC_NCR_FNP_Pos)             /* (GMAC_NCR) No effect. Position  */
#define GMAC_NCR_FNP_1                        (GMAC_NCR_FNP_1_Val << GMAC_NCR_FNP_Pos)             /* (GMAC_NCR) Flushes the next packet from the receive memory. This will only have an effect if the DMA is not currently writing a packet already stored in the receive memory to system memory. Position  */
#define GMAC_NCR_TXLPIEN_Pos                  _UINT32_(19)                                         /* (GMAC_NCR) Enable LPI Transmission Position */
#define GMAC_NCR_TXLPIEN_Msk                  (_UINT32_(0x1) << GMAC_NCR_TXLPIEN_Pos)              /* (GMAC_NCR) Enable LPI Transmission Mask */
#define GMAC_NCR_TXLPIEN(value)               (GMAC_NCR_TXLPIEN_Msk & (_UINT32_(value) << GMAC_NCR_TXLPIEN_Pos)) /* Assigment of value for TXLPIEN in the GMAC_NCR register */
#define GMAC_NCR_PTPUNIENA_Pos                _UINT32_(20)                                         /* (GMAC_NCR) Detection of Unicast PTP Frames Enable Position */
#define GMAC_NCR_PTPUNIENA_Msk                (_UINT32_(0x1) << GMAC_NCR_PTPUNIENA_Pos)            /* (GMAC_NCR) Detection of Unicast PTP Frames Enable Mask */
#define GMAC_NCR_PTPUNIENA(value)             (GMAC_NCR_PTPUNIENA_Msk & (_UINT32_(value) << GMAC_NCR_PTPUNIENA_Pos)) /* Assigment of value for PTPUNIENA in the GMAC_NCR register */
#define   GMAC_NCR_PTPUNIENA_0_Val            _UINT32_(0x0)                                        /* (GMAC_NCR) Disables detection of unicast PTP frames.  */
#define   GMAC_NCR_PTPUNIENA_1_Val            _UINT32_(0x1)                                        /* (GMAC_NCR) Enables detection of unicast PTP frames.  */
#define GMAC_NCR_PTPUNIENA_0                  (GMAC_NCR_PTPUNIENA_0_Val << GMAC_NCR_PTPUNIENA_Pos) /* (GMAC_NCR) Disables detection of unicast PTP frames. Position  */
#define GMAC_NCR_PTPUNIENA_1                  (GMAC_NCR_PTPUNIENA_1_Val << GMAC_NCR_PTPUNIENA_Pos) /* (GMAC_NCR) Enables detection of unicast PTP frames. Position  */
#define GMAC_NCR_STUDPOFFSET_Pos              _UINT32_(22)                                         /* (GMAC_NCR) Store UDP Offset Position */
#define GMAC_NCR_STUDPOFFSET_Msk              (_UINT32_(0x1) << GMAC_NCR_STUDPOFFSET_Pos)          /* (GMAC_NCR) Store UDP Offset Mask */
#define GMAC_NCR_STUDPOFFSET(value)           (GMAC_NCR_STUDPOFFSET_Msk & (_UINT32_(value) << GMAC_NCR_STUDPOFFSET_Pos)) /* Assigment of value for STUDPOFFSET in the GMAC_NCR register */
#define   GMAC_NCR_STUDPOFFSET_0_Val          _UINT32_(0x0)                                        /* (GMAC_NCR) Normal operations.  */
#define   GMAC_NCR_STUDPOFFSET_1_Val          _UINT32_(0x1)                                        /* (GMAC_NCR) The upper 16 bits of the CRC of every received frame are replaced with the offset from start of frame to the beginning of the UDP or TCP header. The lower 16 bits of the CRC are replaced with zero and reserved for future use. The offset is measured in units of 2 bytes.  */
#define GMAC_NCR_STUDPOFFSET_0                (GMAC_NCR_STUDPOFFSET_0_Val << GMAC_NCR_STUDPOFFSET_Pos) /* (GMAC_NCR) Normal operations. Position  */
#define GMAC_NCR_STUDPOFFSET_1                (GMAC_NCR_STUDPOFFSET_1_Val << GMAC_NCR_STUDPOFFSET_Pos) /* (GMAC_NCR) The upper 16 bits of the CRC of every received frame are replaced with the offset from start of frame to the beginning of the UDP or TCP header. The lower 16 bits of the CRC are replaced with zero and reserved for future use. The offset is measured in units of 2 bytes. Position  */
#define GMAC_NCR_OSSMODE_Pos                  _UINT32_(24)                                         /* (GMAC_NCR) One Step Sync Mode Position */
#define GMAC_NCR_OSSMODE_Msk                  (_UINT32_(0x1) << GMAC_NCR_OSSMODE_Pos)              /* (GMAC_NCR) One Step Sync Mode Mask */
#define GMAC_NCR_OSSMODE(value)               (GMAC_NCR_OSSMODE_Msk & (_UINT32_(value) << GMAC_NCR_OSSMODE_Pos)) /* Assigment of value for OSSMODE in the GMAC_NCR register */
#define   GMAC_NCR_OSSMODE_0_Val              _UINT32_(0x0)                                        /* (GMAC_NCR) 1588 One Step Sync Mode is disabled.  */
#define   GMAC_NCR_OSSMODE_1_Val              _UINT32_(0x1)                                        /* (GMAC_NCR) 1588 One Step Sync Mode is enabled. Replaces timestamp field in the 1588 header for TX Sync Frames with the current TSU timer value.  */
#define GMAC_NCR_OSSMODE_0                    (GMAC_NCR_OSSMODE_0_Val << GMAC_NCR_OSSMODE_Pos)     /* (GMAC_NCR) 1588 One Step Sync Mode is disabled. Position  */
#define GMAC_NCR_OSSMODE_1                    (GMAC_NCR_OSSMODE_1_Val << GMAC_NCR_OSSMODE_Pos)     /* (GMAC_NCR) 1588 One Step Sync Mode is enabled. Replaces timestamp field in the 1588 header for TX Sync Frames with the current TSU timer value. Position  */
#define GMAC_NCR_PFCCTL_Pos                   _UINT32_(25)                                         /* (GMAC_NCR) Multiple PFC Pause quantum Enable Position */
#define GMAC_NCR_PFCCTL_Msk                   (_UINT32_(0x1) << GMAC_NCR_PFCCTL_Pos)               /* (GMAC_NCR) Multiple PFC Pause quantum Enable Mask */
#define GMAC_NCR_PFCCTL(value)                (GMAC_NCR_PFCCTL_Msk & (_UINT32_(value) << GMAC_NCR_PFCCTL_Pos)) /* Assigment of value for PFCCTL in the GMAC_NCR register */
#define   GMAC_NCR_PFCCTL_0_Val               _UINT32_(0x0)                                        /* (GMAC_NCR) Disables multiple PFC pause quantums.  */
#define   GMAC_NCR_PFCCTL_1_Val               _UINT32_(0x1)                                        /* (GMAC_NCR) Enables multiple PFC pause quantums, one per pause priority.  */
#define GMAC_NCR_PFCCTL_0                     (GMAC_NCR_PFCCTL_0_Val << GMAC_NCR_PFCCTL_Pos)       /* (GMAC_NCR) Disables multiple PFC pause quantums. Position  */
#define GMAC_NCR_PFCCTL_1                     (GMAC_NCR_PFCCTL_1_Val << GMAC_NCR_PFCCTL_Pos)       /* (GMAC_NCR) Enables multiple PFC pause quantums, one per pause priority. Position  */
#define GMAC_NCR_EXTSELRQEN_Pos               _UINT32_(26)                                         /* (GMAC_NCR) External Selection of Receive Queue Enable Position */
#define GMAC_NCR_EXTSELRQEN_Msk               (_UINT32_(0x1) << GMAC_NCR_EXTSELRQEN_Pos)           /* (GMAC_NCR) External Selection of Receive Queue Enable Mask */
#define GMAC_NCR_EXTSELRQEN(value)            (GMAC_NCR_EXTSELRQEN_Msk & (_UINT32_(value) << GMAC_NCR_EXTSELRQEN_Pos)) /* Assigment of value for EXTSELRQEN in the GMAC_NCR register */
#define   GMAC_NCR_EXTSELRQEN_0_Val           _UINT32_(0x0)                                        /* (GMAC_NCR) Disables external selection of receive queue.  */
#define   GMAC_NCR_EXTSELRQEN_1_Val           _UINT32_(0x1)                                        /* (GMAC_NCR) Enables external selection of receive queue.  */
#define GMAC_NCR_EXTSELRQEN_0                 (GMAC_NCR_EXTSELRQEN_0_Val << GMAC_NCR_EXTSELRQEN_Pos) /* (GMAC_NCR) Disables external selection of receive queue. Position  */
#define GMAC_NCR_EXTSELRQEN_1                 (GMAC_NCR_EXTSELRQEN_1_Val << GMAC_NCR_EXTSELRQEN_Pos) /* (GMAC_NCR) Enables external selection of receive queue. Position  */
#define GMAC_NCR_OSSCORR_Pos                  _UINT32_(27)                                         /* (GMAC_NCR) OSS Correction Field Position */
#define GMAC_NCR_OSSCORR_Msk                  (_UINT32_(0x1) << GMAC_NCR_OSSCORR_Pos)              /* (GMAC_NCR) OSS Correction Field Mask */
#define GMAC_NCR_OSSCORR(value)               (GMAC_NCR_OSSCORR_Msk & (_UINT32_(value) << GMAC_NCR_OSSCORR_Pos)) /* Assigment of value for OSSCORR in the GMAC_NCR register */
#define GMAC_NCR_MIIONRGMII_Pos               _UINT32_(28)                                         /* (GMAC_NCR) MII Control Position */
#define GMAC_NCR_MIIONRGMII_Msk               (_UINT32_(0x1) << GMAC_NCR_MIIONRGMII_Pos)           /* (GMAC_NCR) MII Control Mask */
#define GMAC_NCR_MIIONRGMII(value)            (GMAC_NCR_MIIONRGMII_Msk & (_UINT32_(value) << GMAC_NCR_MIIONRGMII_Pos)) /* Assigment of value for MIIONRGMII in the GMAC_NCR register */
#define   GMAC_NCR_MIIONRGMII_0_Val           _UINT32_(0x0)                                        /* (GMAC_NCR) Disables MII operation.  */
#define GMAC_NCR_MIIONRGMII_0                 (GMAC_NCR_MIIONRGMII_0_Val << GMAC_NCR_MIIONRGMII_Pos) /* (GMAC_NCR) Disables MII operation. Position  */
#define GMAC_NCR_IFGQAVCRED_Pos               _UINT32_(30)                                         /* (GMAC_NCR) Credit-Based Shaping Algorithm Modification Position */
#define GMAC_NCR_IFGQAVCRED_Msk               (_UINT32_(0x1) << GMAC_NCR_IFGQAVCRED_Pos)           /* (GMAC_NCR) Credit-Based Shaping Algorithm Modification Mask */
#define GMAC_NCR_IFGQAVCRED(value)            (GMAC_NCR_IFGQAVCRED_Msk & (_UINT32_(value) << GMAC_NCR_IFGQAVCRED_Pos)) /* Assigment of value for IFGQAVCRED in the GMAC_NCR register */
#define   GMAC_NCR_IFGQAVCRED_0_Val           _UINT32_(0x0)                                        /* (GMAC_NCR) No modification of the CBS algorithm.  */
#define   GMAC_NCR_IFGQAVCRED_1_Val           _UINT32_(0x1)                                        /* (GMAC_NCR) Modifies the CBS algorithm so the IFG/IPG associated with a transmit frame counts towards its 802.1Qav credit.  */
#define GMAC_NCR_IFGQAVCRED_0                 (GMAC_NCR_IFGQAVCRED_0_Val << GMAC_NCR_IFGQAVCRED_Pos) /* (GMAC_NCR) No modification of the CBS algorithm. Position  */
#define GMAC_NCR_IFGQAVCRED_1                 (GMAC_NCR_IFGQAVCRED_1_Val << GMAC_NCR_IFGQAVCRED_Pos) /* (GMAC_NCR) Modifies the CBS algorithm so the IFG/IPG associated with a transmit frame counts towards its 802.1Qav credit. Position  */
#define GMAC_NCR_Msk                          _UINT32_(0x5F5F9FFE)                                 /* (GMAC_NCR) Register Mask  */


/* -------- GMAC_NCFGR : (GMAC Offset: 0x04) (R/W 32) Network Configuration Register -------- */
#define GMAC_NCFGR_RESETVALUE                 _UINT32_(0x80000)                                    /*  (GMAC_NCFGR) Network Configuration Register  Reset Value */

#define GMAC_NCFGR_SPD_Pos                    _UINT32_(0)                                          /* (GMAC_NCFGR) Speed Position */
#define GMAC_NCFGR_SPD_Msk                    (_UINT32_(0x1) << GMAC_NCFGR_SPD_Pos)                /* (GMAC_NCFGR) Speed Mask */
#define GMAC_NCFGR_SPD(value)                 (GMAC_NCFGR_SPD_Msk & (_UINT32_(value) << GMAC_NCFGR_SPD_Pos)) /* Assigment of value for SPD in the GMAC_NCFGR register */
#define GMAC_NCFGR_FD_Pos                     _UINT32_(1)                                          /* (GMAC_NCFGR) Full Duplex Position */
#define GMAC_NCFGR_FD_Msk                     (_UINT32_(0x1) << GMAC_NCFGR_FD_Pos)                 /* (GMAC_NCFGR) Full Duplex Mask */
#define GMAC_NCFGR_FD(value)                  (GMAC_NCFGR_FD_Msk & (_UINT32_(value) << GMAC_NCFGR_FD_Pos)) /* Assigment of value for FD in the GMAC_NCFGR register */
#define GMAC_NCFGR_DNVLAN_Pos                 _UINT32_(2)                                          /* (GMAC_NCFGR) Discard Non-VLAN FRAMES Position */
#define GMAC_NCFGR_DNVLAN_Msk                 (_UINT32_(0x1) << GMAC_NCFGR_DNVLAN_Pos)             /* (GMAC_NCFGR) Discard Non-VLAN FRAMES Mask */
#define GMAC_NCFGR_DNVLAN(value)              (GMAC_NCFGR_DNVLAN_Msk & (_UINT32_(value) << GMAC_NCFGR_DNVLAN_Pos)) /* Assigment of value for DNVLAN in the GMAC_NCFGR register */
#define GMAC_NCFGR_JFRAME_Pos                 _UINT32_(3)                                          /* (GMAC_NCFGR) Jumbo Frame Size Position */
#define GMAC_NCFGR_JFRAME_Msk                 (_UINT32_(0x1) << GMAC_NCFGR_JFRAME_Pos)             /* (GMAC_NCFGR) Jumbo Frame Size Mask */
#define GMAC_NCFGR_JFRAME(value)              (GMAC_NCFGR_JFRAME_Msk & (_UINT32_(value) << GMAC_NCFGR_JFRAME_Pos)) /* Assigment of value for JFRAME in the GMAC_NCFGR register */
#define GMAC_NCFGR_CAF_Pos                    _UINT32_(4)                                          /* (GMAC_NCFGR) Copy All Frames Position */
#define GMAC_NCFGR_CAF_Msk                    (_UINT32_(0x1) << GMAC_NCFGR_CAF_Pos)                /* (GMAC_NCFGR) Copy All Frames Mask */
#define GMAC_NCFGR_CAF(value)                 (GMAC_NCFGR_CAF_Msk & (_UINT32_(value) << GMAC_NCFGR_CAF_Pos)) /* Assigment of value for CAF in the GMAC_NCFGR register */
#define GMAC_NCFGR_NBC_Pos                    _UINT32_(5)                                          /* (GMAC_NCFGR) No Broadcast Position */
#define GMAC_NCFGR_NBC_Msk                    (_UINT32_(0x1) << GMAC_NCFGR_NBC_Pos)                /* (GMAC_NCFGR) No Broadcast Mask */
#define GMAC_NCFGR_NBC(value)                 (GMAC_NCFGR_NBC_Msk & (_UINT32_(value) << GMAC_NCFGR_NBC_Pos)) /* Assigment of value for NBC in the GMAC_NCFGR register */
#define GMAC_NCFGR_MTIHEN_Pos                 _UINT32_(6)                                          /* (GMAC_NCFGR) Multicast Hash Enable Position */
#define GMAC_NCFGR_MTIHEN_Msk                 (_UINT32_(0x1) << GMAC_NCFGR_MTIHEN_Pos)             /* (GMAC_NCFGR) Multicast Hash Enable Mask */
#define GMAC_NCFGR_MTIHEN(value)              (GMAC_NCFGR_MTIHEN_Msk & (_UINT32_(value) << GMAC_NCFGR_MTIHEN_Pos)) /* Assigment of value for MTIHEN in the GMAC_NCFGR register */
#define GMAC_NCFGR_UNIHEN_Pos                 _UINT32_(7)                                          /* (GMAC_NCFGR) Unicast Hash Enable Position */
#define GMAC_NCFGR_UNIHEN_Msk                 (_UINT32_(0x1) << GMAC_NCFGR_UNIHEN_Pos)             /* (GMAC_NCFGR) Unicast Hash Enable Mask */
#define GMAC_NCFGR_UNIHEN(value)              (GMAC_NCFGR_UNIHEN_Msk & (_UINT32_(value) << GMAC_NCFGR_UNIHEN_Pos)) /* Assigment of value for UNIHEN in the GMAC_NCFGR register */
#define GMAC_NCFGR_MAXFS_Pos                  _UINT32_(8)                                          /* (GMAC_NCFGR) 1536 Maximum Frame Size Position */
#define GMAC_NCFGR_MAXFS_Msk                  (_UINT32_(0x1) << GMAC_NCFGR_MAXFS_Pos)              /* (GMAC_NCFGR) 1536 Maximum Frame Size Mask */
#define GMAC_NCFGR_MAXFS(value)               (GMAC_NCFGR_MAXFS_Msk & (_UINT32_(value) << GMAC_NCFGR_MAXFS_Pos)) /* Assigment of value for MAXFS in the GMAC_NCFGR register */
#define GMAC_NCFGR_RTY_Pos                    _UINT32_(12)                                         /* (GMAC_NCFGR) Retry Test0 Position */
#define GMAC_NCFGR_RTY_Msk                    (_UINT32_(0x1) << GMAC_NCFGR_RTY_Pos)                /* (GMAC_NCFGR) Retry Test0 Mask */
#define GMAC_NCFGR_RTY(value)                 (GMAC_NCFGR_RTY_Msk & (_UINT32_(value) << GMAC_NCFGR_RTY_Pos)) /* Assigment of value for RTY in the GMAC_NCFGR register */
#define GMAC_NCFGR_PEN_Pos                    _UINT32_(13)                                         /* (GMAC_NCFGR) Pause Enable Position */
#define GMAC_NCFGR_PEN_Msk                    (_UINT32_(0x1) << GMAC_NCFGR_PEN_Pos)                /* (GMAC_NCFGR) Pause Enable Mask */
#define GMAC_NCFGR_PEN(value)                 (GMAC_NCFGR_PEN_Msk & (_UINT32_(value) << GMAC_NCFGR_PEN_Pos)) /* Assigment of value for PEN in the GMAC_NCFGR register */
#define GMAC_NCFGR_RXBUFO_Pos                 _UINT32_(14)                                         /* (GMAC_NCFGR) Receive Buffer Offset Position */
#define GMAC_NCFGR_RXBUFO_Msk                 (_UINT32_(0x3) << GMAC_NCFGR_RXBUFO_Pos)             /* (GMAC_NCFGR) Receive Buffer Offset Mask */
#define GMAC_NCFGR_RXBUFO(value)              (GMAC_NCFGR_RXBUFO_Msk & (_UINT32_(value) << GMAC_NCFGR_RXBUFO_Pos)) /* Assigment of value for RXBUFO in the GMAC_NCFGR register */
#define GMAC_NCFGR_LFERD_Pos                  _UINT32_(16)                                         /* (GMAC_NCFGR) Length Field Error Frame Discard Position */
#define GMAC_NCFGR_LFERD_Msk                  (_UINT32_(0x1) << GMAC_NCFGR_LFERD_Pos)              /* (GMAC_NCFGR) Length Field Error Frame Discard Mask */
#define GMAC_NCFGR_LFERD(value)               (GMAC_NCFGR_LFERD_Msk & (_UINT32_(value) << GMAC_NCFGR_LFERD_Pos)) /* Assigment of value for LFERD in the GMAC_NCFGR register */
#define GMAC_NCFGR_RFCS_Pos                   _UINT32_(17)                                         /* (GMAC_NCFGR) Remove FCS Position */
#define GMAC_NCFGR_RFCS_Msk                   (_UINT32_(0x1) << GMAC_NCFGR_RFCS_Pos)               /* (GMAC_NCFGR) Remove FCS Mask */
#define GMAC_NCFGR_RFCS(value)                (GMAC_NCFGR_RFCS_Msk & (_UINT32_(value) << GMAC_NCFGR_RFCS_Pos)) /* Assigment of value for RFCS in the GMAC_NCFGR register */
#define GMAC_NCFGR_CLK_Pos                    _UINT32_(18)                                         /* (GMAC_NCFGR) MDC CLock Division Position */
#define GMAC_NCFGR_CLK_Msk                    (_UINT32_(0x7) << GMAC_NCFGR_CLK_Pos)                /* (GMAC_NCFGR) MDC CLock Division Mask */
#define GMAC_NCFGR_CLK(value)                 (GMAC_NCFGR_CLK_Msk & (_UINT32_(value) << GMAC_NCFGR_CLK_Pos)) /* Assigment of value for CLK in the GMAC_NCFGR register */
#define   GMAC_NCFGR_CLK_MCK_8_Val            _UINT32_(0x0)                                        /* (GMAC_NCFGR) MCK divided by 8 (MCK up to 20 MHz)  */
#define   GMAC_NCFGR_CLK_MCK_16_Val           _UINT32_(0x1)                                        /* (GMAC_NCFGR) MCK divided by 16 (MCK up to 40 MHz)  */
#define   GMAC_NCFGR_CLK_MCK_32_Val           _UINT32_(0x2)                                        /* (GMAC_NCFGR) MCK divided by 32 (MCK up to 80 MHz)  */
#define   GMAC_NCFGR_CLK_MCK_48_Val           _UINT32_(0x3)                                        /* (GMAC_NCFGR) MCK divided by 48 (MCK up to 120 MHz)  */
#define   GMAC_NCFGR_CLK_MCK_64_Val           _UINT32_(0x4)                                        /* (GMAC_NCFGR) MCK divided by 64 (MCK up to 160 MHz)  */
#define   GMAC_NCFGR_CLK_MCK_96_Val           _UINT32_(0x5)                                        /* (GMAC_NCFGR) MCK divided by 96 (MCK up to 240 MHz)  */
#define GMAC_NCFGR_CLK_MCK_8                  (GMAC_NCFGR_CLK_MCK_8_Val << GMAC_NCFGR_CLK_Pos)     /* (GMAC_NCFGR) MCK divided by 8 (MCK up to 20 MHz) Position  */
#define GMAC_NCFGR_CLK_MCK_16                 (GMAC_NCFGR_CLK_MCK_16_Val << GMAC_NCFGR_CLK_Pos)    /* (GMAC_NCFGR) MCK divided by 16 (MCK up to 40 MHz) Position  */
#define GMAC_NCFGR_CLK_MCK_32                 (GMAC_NCFGR_CLK_MCK_32_Val << GMAC_NCFGR_CLK_Pos)    /* (GMAC_NCFGR) MCK divided by 32 (MCK up to 80 MHz) Position  */
#define GMAC_NCFGR_CLK_MCK_48                 (GMAC_NCFGR_CLK_MCK_48_Val << GMAC_NCFGR_CLK_Pos)    /* (GMAC_NCFGR) MCK divided by 48 (MCK up to 120 MHz) Position  */
#define GMAC_NCFGR_CLK_MCK_64                 (GMAC_NCFGR_CLK_MCK_64_Val << GMAC_NCFGR_CLK_Pos)    /* (GMAC_NCFGR) MCK divided by 64 (MCK up to 160 MHz) Position  */
#define GMAC_NCFGR_CLK_MCK_96                 (GMAC_NCFGR_CLK_MCK_96_Val << GMAC_NCFGR_CLK_Pos)    /* (GMAC_NCFGR) MCK divided by 96 (MCK up to 240 MHz) Position  */
#define GMAC_NCFGR_DBW_Pos                    _UINT32_(21)                                         /* (GMAC_NCFGR) Data Bus Width Position */
#define GMAC_NCFGR_DBW_Msk                    (_UINT32_(0x3) << GMAC_NCFGR_DBW_Pos)                /* (GMAC_NCFGR) Data Bus Width Mask */
#define GMAC_NCFGR_DBW(value)                 (GMAC_NCFGR_DBW_Msk & (_UINT32_(value) << GMAC_NCFGR_DBW_Pos)) /* Assigment of value for DBW in the GMAC_NCFGR register */
#define GMAC_NCFGR_DCPF_Pos                   _UINT32_(23)                                         /* (GMAC_NCFGR) Disable Copy of Pause Frames Position */
#define GMAC_NCFGR_DCPF_Msk                   (_UINT32_(0x1) << GMAC_NCFGR_DCPF_Pos)               /* (GMAC_NCFGR) Disable Copy of Pause Frames Mask */
#define GMAC_NCFGR_DCPF(value)                (GMAC_NCFGR_DCPF_Msk & (_UINT32_(value) << GMAC_NCFGR_DCPF_Pos)) /* Assigment of value for DCPF in the GMAC_NCFGR register */
#define GMAC_NCFGR_RXCOEN_Pos                 _UINT32_(24)                                         /* (GMAC_NCFGR) Receive Checksum Offload Enable Position */
#define GMAC_NCFGR_RXCOEN_Msk                 (_UINT32_(0x1) << GMAC_NCFGR_RXCOEN_Pos)             /* (GMAC_NCFGR) Receive Checksum Offload Enable Mask */
#define GMAC_NCFGR_RXCOEN(value)              (GMAC_NCFGR_RXCOEN_Msk & (_UINT32_(value) << GMAC_NCFGR_RXCOEN_Pos)) /* Assigment of value for RXCOEN in the GMAC_NCFGR register */
#define GMAC_NCFGR_EFRHD_Pos                  _UINT32_(25)                                         /* (GMAC_NCFGR) Enable Frames Received in Half Duplex Position */
#define GMAC_NCFGR_EFRHD_Msk                  (_UINT32_(0x1) << GMAC_NCFGR_EFRHD_Pos)              /* (GMAC_NCFGR) Enable Frames Received in Half Duplex Mask */
#define GMAC_NCFGR_EFRHD(value)               (GMAC_NCFGR_EFRHD_Msk & (_UINT32_(value) << GMAC_NCFGR_EFRHD_Pos)) /* Assigment of value for EFRHD in the GMAC_NCFGR register */
#define GMAC_NCFGR_IRXFCS_Pos                 _UINT32_(26)                                         /* (GMAC_NCFGR) Ignore RX FCS Position */
#define GMAC_NCFGR_IRXFCS_Msk                 (_UINT32_(0x1) << GMAC_NCFGR_IRXFCS_Pos)             /* (GMAC_NCFGR) Ignore RX FCS Mask */
#define GMAC_NCFGR_IRXFCS(value)              (GMAC_NCFGR_IRXFCS_Msk & (_UINT32_(value) << GMAC_NCFGR_IRXFCS_Pos)) /* Assigment of value for IRXFCS in the GMAC_NCFGR register */
#define GMAC_NCFGR_IPGSEN_Pos                 _UINT32_(28)                                         /* (GMAC_NCFGR) IP Stretch Enable Position */
#define GMAC_NCFGR_IPGSEN_Msk                 (_UINT32_(0x1) << GMAC_NCFGR_IPGSEN_Pos)             /* (GMAC_NCFGR) IP Stretch Enable Mask */
#define GMAC_NCFGR_IPGSEN(value)              (GMAC_NCFGR_IPGSEN_Msk & (_UINT32_(value) << GMAC_NCFGR_IPGSEN_Pos)) /* Assigment of value for IPGSEN in the GMAC_NCFGR register */
#define GMAC_NCFGR_RXBP_Pos                   _UINT32_(29)                                         /* (GMAC_NCFGR) Receive Bad Preamble Position */
#define GMAC_NCFGR_RXBP_Msk                   (_UINT32_(0x1) << GMAC_NCFGR_RXBP_Pos)               /* (GMAC_NCFGR) Receive Bad Preamble Mask */
#define GMAC_NCFGR_RXBP(value)                (GMAC_NCFGR_RXBP_Msk & (_UINT32_(value) << GMAC_NCFGR_RXBP_Pos)) /* Assigment of value for RXBP in the GMAC_NCFGR register */
#define GMAC_NCFGR_IRXER_Pos                  _UINT32_(30)                                         /* (GMAC_NCFGR) Ignore Receive Error from PHY Position */
#define GMAC_NCFGR_IRXER_Msk                  (_UINT32_(0x1) << GMAC_NCFGR_IRXER_Pos)              /* (GMAC_NCFGR) Ignore Receive Error from PHY Mask */
#define GMAC_NCFGR_IRXER(value)               (GMAC_NCFGR_IRXER_Msk & (_UINT32_(value) << GMAC_NCFGR_IRXER_Pos)) /* Assigment of value for IRXER in the GMAC_NCFGR register */
#define GMAC_NCFGR_Msk                        _UINT32_(0x77FFF1FF)                                 /* (GMAC_NCFGR) Register Mask  */


/* -------- GMAC_NSR : (GMAC Offset: 0x08) ( R/ 32) Network Status Register -------- */
#define GMAC_NSR_MDIO_Pos                     _UINT32_(1)                                          /* (GMAC_NSR) MDIO Input Status Position */
#define GMAC_NSR_MDIO_Msk                     (_UINT32_(0x1) << GMAC_NSR_MDIO_Pos)                 /* (GMAC_NSR) MDIO Input Status Mask */
#define GMAC_NSR_MDIO(value)                  (GMAC_NSR_MDIO_Msk & (_UINT32_(value) << GMAC_NSR_MDIO_Pos)) /* Assigment of value for MDIO in the GMAC_NSR register */
#define GMAC_NSR_IDLE_Pos                     _UINT32_(2)                                          /* (GMAC_NSR) PHY Management Logic Idle Position */
#define GMAC_NSR_IDLE_Msk                     (_UINT32_(0x1) << GMAC_NSR_IDLE_Pos)                 /* (GMAC_NSR) PHY Management Logic Idle Mask */
#define GMAC_NSR_IDLE(value)                  (GMAC_NSR_IDLE_Msk & (_UINT32_(value) << GMAC_NSR_IDLE_Pos)) /* Assigment of value for IDLE in the GMAC_NSR register */
#define GMAC_NSR_PFCPAUSN_Pos                 _UINT32_(6)                                          /* (GMAC_NSR) PFC Pause Negotiated Position */
#define GMAC_NSR_PFCPAUSN_Msk                 (_UINT32_(0x1) << GMAC_NSR_PFCPAUSN_Pos)             /* (GMAC_NSR) PFC Pause Negotiated Mask */
#define GMAC_NSR_PFCPAUSN(value)              (GMAC_NSR_PFCPAUSN_Msk & (_UINT32_(value) << GMAC_NSR_PFCPAUSN_Pos)) /* Assigment of value for PFCPAUSN in the GMAC_NSR register */
#define GMAC_NSR_RXLPIS_Pos                   _UINT32_(7)                                          /* (GMAC_NSR) LPI Indication Position */
#define GMAC_NSR_RXLPIS_Msk                   (_UINT32_(0x1) << GMAC_NSR_RXLPIS_Pos)               /* (GMAC_NSR) LPI Indication Mask */
#define GMAC_NSR_RXLPIS(value)                (GMAC_NSR_RXLPIS_Msk & (_UINT32_(value) << GMAC_NSR_RXLPIS_Pos)) /* Assigment of value for RXLPIS in the GMAC_NSR register */
#define GMAC_NSR_Msk                          _UINT32_(0x000000C6)                                 /* (GMAC_NSR) Register Mask  */


/* -------- GMAC_UR : (GMAC Offset: 0x0C) (R/W 32) User Register -------- */
#define GMAC_UR_RESETVALUE                    _UINT32_(0x00)                                       /*  (GMAC_UR) User Register  Reset Value */

#define GMAC_UR_RMII_Pos                      _UINT32_(0)                                          /* (GMAC_UR) Reduced MII Mode Position */
#define GMAC_UR_RMII_Msk                      (_UINT32_(0x1) << GMAC_UR_RMII_Pos)                  /* (GMAC_UR) Reduced MII Mode Mask */
#define GMAC_UR_RMII(value)                   (GMAC_UR_RMII_Msk & (_UINT32_(value) << GMAC_UR_RMII_Pos)) /* Assigment of value for RMII in the GMAC_UR register */
#define   GMAC_UR_RMII_1_Val                  _UINT32_(0x1)                                        /* (GMAC_UR) RMII mode is selected.  */
#define GMAC_UR_RMII_1                        (GMAC_UR_RMII_1_Val << GMAC_UR_RMII_Pos)             /* (GMAC_UR) RMII mode is selected. Position  */
#define GMAC_UR_HDFLCTLEN_Pos                 _UINT32_(6)                                          /* (GMAC_UR) Half Duplex Flow Control Enable Position */
#define GMAC_UR_HDFLCTLEN_Msk                 (_UINT32_(0x1) << GMAC_UR_HDFLCTLEN_Pos)             /* (GMAC_UR) Half Duplex Flow Control Enable Mask */
#define GMAC_UR_HDFLCTLEN(value)              (GMAC_UR_HDFLCTLEN_Msk & (_UINT32_(value) << GMAC_UR_HDFLCTLEN_Pos)) /* Assigment of value for HDFLCTLEN in the GMAC_UR register */
#define   GMAC_UR_HDFLCTLEN_0_Val             _UINT32_(0x0)                                        /* (GMAC_UR) Half duplex flow control is disabled.  */
#define   GMAC_UR_HDFLCTLEN_1_Val             _UINT32_(0x1)                                        /* (GMAC_UR) Half duplex flow control is enabled.  */
#define GMAC_UR_HDFLCTLEN_0                   (GMAC_UR_HDFLCTLEN_0_Val << GMAC_UR_HDFLCTLEN_Pos)   /* (GMAC_UR) Half duplex flow control is disabled. Position  */
#define GMAC_UR_HDFLCTLEN_1                   (GMAC_UR_HDFLCTLEN_1_Val << GMAC_UR_HDFLCTLEN_Pos)   /* (GMAC_UR) Half duplex flow control is enabled. Position  */
#define GMAC_UR_Msk                           _UINT32_(0x00000041)                                 /* (GMAC_UR) Register Mask  */


/* -------- GMAC_DCFGR : (GMAC Offset: 0x10) (R/W 32) DMA Configuration Register -------- */
#define GMAC_DCFGR_RESETVALUE                 _UINT32_(0x20004)                                    /*  (GMAC_DCFGR) DMA Configuration Register  Reset Value */

#define GMAC_DCFGR_FBLDO_Pos                  _UINT32_(0)                                          /* (GMAC_DCFGR) Fixed Burst Length for DMA Data Operations: Position */
#define GMAC_DCFGR_FBLDO_Msk                  (_UINT32_(0x1F) << GMAC_DCFGR_FBLDO_Pos)             /* (GMAC_DCFGR) Fixed Burst Length for DMA Data Operations: Mask */
#define GMAC_DCFGR_FBLDO(value)               (GMAC_DCFGR_FBLDO_Msk & (_UINT32_(value) << GMAC_DCFGR_FBLDO_Pos)) /* Assigment of value for FBLDO in the GMAC_DCFGR register */
#define   GMAC_DCFGR_FBLDO_SINGLE_Val         _UINT32_(0x1)                                        /* (GMAC_DCFGR) Always use single access on system bus  */
#define   GMAC_DCFGR_FBLDO_INCR4_Val          _UINT32_(0x4)                                        /* (GMAC_DCFGR) Attempt to use 4-beat bursts on system bus (Default)  */
#define   GMAC_DCFGR_FBLDO_INCR8_Val          _UINT32_(0x8)                                        /* (GMAC_DCFGR) Attempt to use 8-beat bursts on system bus bursts  */
#define   GMAC_DCFGR_FBLDO_INCR16_Val         _UINT32_(0x10)                                       /* (GMAC_DCFGR) Attempt to use 16-beat bursts on system bus bursts  */
#define GMAC_DCFGR_FBLDO_SINGLE               (GMAC_DCFGR_FBLDO_SINGLE_Val << GMAC_DCFGR_FBLDO_Pos) /* (GMAC_DCFGR) Always use single access on system bus Position  */
#define GMAC_DCFGR_FBLDO_INCR4                (GMAC_DCFGR_FBLDO_INCR4_Val << GMAC_DCFGR_FBLDO_Pos) /* (GMAC_DCFGR) Attempt to use 4-beat bursts on system bus (Default) Position  */
#define GMAC_DCFGR_FBLDO_INCR8                (GMAC_DCFGR_FBLDO_INCR8_Val << GMAC_DCFGR_FBLDO_Pos) /* (GMAC_DCFGR) Attempt to use 8-beat bursts on system bus bursts Position  */
#define GMAC_DCFGR_FBLDO_INCR16               (GMAC_DCFGR_FBLDO_INCR16_Val << GMAC_DCFGR_FBLDO_Pos) /* (GMAC_DCFGR) Attempt to use 16-beat bursts on system bus bursts Position  */
#define GMAC_DCFGR_ESMA_Pos                   _UINT32_(6)                                          /* (GMAC_DCFGR) Endian Swap Mode Enable for Management Descriptor Accesses Position */
#define GMAC_DCFGR_ESMA_Msk                   (_UINT32_(0x1) << GMAC_DCFGR_ESMA_Pos)               /* (GMAC_DCFGR) Endian Swap Mode Enable for Management Descriptor Accesses Mask */
#define GMAC_DCFGR_ESMA(value)                (GMAC_DCFGR_ESMA_Msk & (_UINT32_(value) << GMAC_DCFGR_ESMA_Pos)) /* Assigment of value for ESMA in the GMAC_DCFGR register */
#define   GMAC_DCFGR_ESMA_LITTLE_ENDIAN_Val   _UINT32_(0x0)                                        /* (GMAC_DCFGR) Selects Little-endian endianism for system bus transfers.  */
#define   GMAC_DCFGR_ESMA_BIG_ENDIAN_Val      _UINT32_(0x1)                                        /* (GMAC_DCFGR) Selects swapped endianism for system bus transfers.  */
#define GMAC_DCFGR_ESMA_LITTLE_ENDIAN         (GMAC_DCFGR_ESMA_LITTLE_ENDIAN_Val << GMAC_DCFGR_ESMA_Pos) /* (GMAC_DCFGR) Selects Little-endian endianism for system bus transfers. Position  */
#define GMAC_DCFGR_ESMA_BIG_ENDIAN            (GMAC_DCFGR_ESMA_BIG_ENDIAN_Val << GMAC_DCFGR_ESMA_Pos) /* (GMAC_DCFGR) Selects swapped endianism for system bus transfers. Position  */
#define GMAC_DCFGR_ESPA_Pos                   _UINT32_(7)                                          /* (GMAC_DCFGR) Endian Swap Mode Enable for Packet Data Accesses Position */
#define GMAC_DCFGR_ESPA_Msk                   (_UINT32_(0x1) << GMAC_DCFGR_ESPA_Pos)               /* (GMAC_DCFGR) Endian Swap Mode Enable for Packet Data Accesses Mask */
#define GMAC_DCFGR_ESPA(value)                (GMAC_DCFGR_ESPA_Msk & (_UINT32_(value) << GMAC_DCFGR_ESPA_Pos)) /* Assigment of value for ESPA in the GMAC_DCFGR register */
#define   GMAC_DCFGR_ESPA_LITTLE_ENDIAN_Val   _UINT32_(0x0)                                        /* (GMAC_DCFGR) Selects Little-endian endianism for system bus transfers.  */
#define   GMAC_DCFGR_ESPA_BIG_ENDIAN_Val      _UINT32_(0x1)                                        /* (GMAC_DCFGR) Selects swapped endianism for system bus transfers.  */
#define GMAC_DCFGR_ESPA_LITTLE_ENDIAN         (GMAC_DCFGR_ESPA_LITTLE_ENDIAN_Val << GMAC_DCFGR_ESPA_Pos) /* (GMAC_DCFGR) Selects Little-endian endianism for system bus transfers. Position  */
#define GMAC_DCFGR_ESPA_BIG_ENDIAN            (GMAC_DCFGR_ESPA_BIG_ENDIAN_Val << GMAC_DCFGR_ESPA_Pos) /* (GMAC_DCFGR) Selects swapped endianism for system bus transfers. Position  */
#define GMAC_DCFGR_RXBMS_Pos                  _UINT32_(8)                                          /* (GMAC_DCFGR) Receiver Packet Buffer Memory Size Select Position */
#define GMAC_DCFGR_RXBMS_Msk                  (_UINT32_(0x3) << GMAC_DCFGR_RXBMS_Pos)              /* (GMAC_DCFGR) Receiver Packet Buffer Memory Size Select Mask */
#define GMAC_DCFGR_RXBMS(value)               (GMAC_DCFGR_RXBMS_Msk & (_UINT32_(value) << GMAC_DCFGR_RXBMS_Pos)) /* Assigment of value for RXBMS in the GMAC_DCFGR register */
#define   GMAC_DCFGR_RXBMS_EIGHTH_Val         _UINT32_(0x0)                                        /* (GMAC_DCFGR) 4/8 Kbyte Memory Size  */
#define   GMAC_DCFGR_RXBMS_QUARTER_Val        _UINT32_(0x1)                                        /* (GMAC_DCFGR) 4/4 Kbytes Memory Size  */
#define   GMAC_DCFGR_RXBMS_HALF_Val           _UINT32_(0x2)                                        /* (GMAC_DCFGR) 4/2 Kbytes Memory Size  */
#define   GMAC_DCFGR_RXBMS_FULL_Val           _UINT32_(0x3)                                        /* (GMAC_DCFGR) 4 Kbytes Memory Size  */
#define GMAC_DCFGR_RXBMS_EIGHTH               (GMAC_DCFGR_RXBMS_EIGHTH_Val << GMAC_DCFGR_RXBMS_Pos) /* (GMAC_DCFGR) 4/8 Kbyte Memory Size Position  */
#define GMAC_DCFGR_RXBMS_QUARTER              (GMAC_DCFGR_RXBMS_QUARTER_Val << GMAC_DCFGR_RXBMS_Pos) /* (GMAC_DCFGR) 4/4 Kbytes Memory Size Position  */
#define GMAC_DCFGR_RXBMS_HALF                 (GMAC_DCFGR_RXBMS_HALF_Val << GMAC_DCFGR_RXBMS_Pos)  /* (GMAC_DCFGR) 4/2 Kbytes Memory Size Position  */
#define GMAC_DCFGR_RXBMS_FULL                 (GMAC_DCFGR_RXBMS_FULL_Val << GMAC_DCFGR_RXBMS_Pos)  /* (GMAC_DCFGR) 4 Kbytes Memory Size Position  */
#define GMAC_DCFGR_TXPBMS_Pos                 _UINT32_(10)                                         /* (GMAC_DCFGR) Transmitter Packet Buffer Memory Size Select Position */
#define GMAC_DCFGR_TXPBMS_Msk                 (_UINT32_(0x1) << GMAC_DCFGR_TXPBMS_Pos)             /* (GMAC_DCFGR) Transmitter Packet Buffer Memory Size Select Mask */
#define GMAC_DCFGR_TXPBMS(value)              (GMAC_DCFGR_TXPBMS_Msk & (_UINT32_(value) << GMAC_DCFGR_TXPBMS_Pos)) /* Assigment of value for TXPBMS in the GMAC_DCFGR register */
#define   GMAC_DCFGR_TXPBMS_TWO_KB_Val        _UINT32_(0x0)                                        /* (GMAC_DCFGR) Do not use top address bit (2 Kbytes).  */
#define   GMAC_DCFGR_TXPBMS_FOUR_KB_Val       _UINT32_(0x1)                                        /* (GMAC_DCFGR) Use full configured addressable space (4 Kbytes).  */
#define GMAC_DCFGR_TXPBMS_TWO_KB              (GMAC_DCFGR_TXPBMS_TWO_KB_Val << GMAC_DCFGR_TXPBMS_Pos) /* (GMAC_DCFGR) Do not use top address bit (2 Kbytes). Position  */
#define GMAC_DCFGR_TXPBMS_FOUR_KB             (GMAC_DCFGR_TXPBMS_FOUR_KB_Val << GMAC_DCFGR_TXPBMS_Pos) /* (GMAC_DCFGR) Use full configured addressable space (4 Kbytes). Position  */
#define GMAC_DCFGR_TXCOEN_Pos                 _UINT32_(11)                                         /* (GMAC_DCFGR) Transmitter Checksum Generation Offload Enable Position */
#define GMAC_DCFGR_TXCOEN_Msk                 (_UINT32_(0x1) << GMAC_DCFGR_TXCOEN_Pos)             /* (GMAC_DCFGR) Transmitter Checksum Generation Offload Enable Mask */
#define GMAC_DCFGR_TXCOEN(value)              (GMAC_DCFGR_TXCOEN_Msk & (_UINT32_(value) << GMAC_DCFGR_TXCOEN_Pos)) /* Assigment of value for TXCOEN in the GMAC_DCFGR register */
#define GMAC_DCFGR_INFLASTEN_Pos              _UINT32_(12)                                         /* (GMAC_DCFGR) Infinite Size for Last Buffer Enable Position */
#define GMAC_DCFGR_INFLASTEN_Msk              (_UINT32_(0x1) << GMAC_DCFGR_INFLASTEN_Pos)          /* (GMAC_DCFGR) Infinite Size for Last Buffer Enable Mask */
#define GMAC_DCFGR_INFLASTEN(value)           (GMAC_DCFGR_INFLASTEN_Msk & (_UINT32_(value) << GMAC_DCFGR_INFLASTEN_Pos)) /* Assigment of value for INFLASTEN in the GMAC_DCFGR register */
#define GMAC_DCFGR_CRCERRREP_Pos              _UINT32_(13)                                         /* (GMAC_DCFGR) CRC Errors Report Position */
#define GMAC_DCFGR_CRCERRREP_Msk              (_UINT32_(0x1) << GMAC_DCFGR_CRCERRREP_Pos)          /* (GMAC_DCFGR) CRC Errors Report Mask */
#define GMAC_DCFGR_CRCERRREP(value)           (GMAC_DCFGR_CRCERRREP_Msk & (_UINT32_(value) << GMAC_DCFGR_CRCERRREP_Pos)) /* Assigment of value for CRCERRREP in the GMAC_DCFGR register */
#define   GMAC_DCFGR_CRCERRREP_0_Val          _UINT32_(0x0)                                        /* (GMAC_DCFGR) Bit 16 of the receive buffer descriptor represents the Canonical format indicator (CFI) bit as extracted from the receive frame (if the receive buffer descriptor is pointing to the last data buffer of the receive frame and the received frame was VLAN tagged).  */
#define   GMAC_DCFGR_CRCERRREP_1_Val          _UINT32_(0x1)                                        /* (GMAC_DCFGR) Bit 16 of the receive buffer descriptor represents the FCS/CRC error (only if frames with FCS are copied to memory as enabled by bit 26 in the Network Configuration register).  */
#define GMAC_DCFGR_CRCERRREP_0                (GMAC_DCFGR_CRCERRREP_0_Val << GMAC_DCFGR_CRCERRREP_Pos) /* (GMAC_DCFGR) Bit 16 of the receive buffer descriptor represents the Canonical format indicator (CFI) bit as extracted from the receive frame (if the receive buffer descriptor is pointing to the last data buffer of the receive frame and the received frame was VLAN tagged). Position  */
#define GMAC_DCFGR_CRCERRREP_1                (GMAC_DCFGR_CRCERRREP_1_Val << GMAC_DCFGR_CRCERRREP_Pos) /* (GMAC_DCFGR) Bit 16 of the receive buffer descriptor represents the FCS/CRC error (only if frames with FCS are copied to memory as enabled by bit 26 in the Network Configuration register). Position  */
#define GMAC_DCFGR_DRBS_Pos                   _UINT32_(16)                                         /* (GMAC_DCFGR) DMA Receive Buffer Size Position */
#define GMAC_DCFGR_DRBS_Msk                   (_UINT32_(0xFF) << GMAC_DCFGR_DRBS_Pos)              /* (GMAC_DCFGR) DMA Receive Buffer Size Mask */
#define GMAC_DCFGR_DRBS(value)                (GMAC_DCFGR_DRBS_Msk & (_UINT32_(value) << GMAC_DCFGR_DRBS_Pos)) /* Assigment of value for DRBS in the GMAC_DCFGR register */
#define   GMAC_DCFGR_DRBS_0x02_Val            _UINT32_(0x2)                                        /* (GMAC_DCFGR) 128 bytes  */
#define   GMAC_DCFGR_DRBS_0x18_Val            _UINT32_(0x18)                                       /* (GMAC_DCFGR) 1536 bytes (1 x max length frame/buffer)  */
#define   GMAC_DCFGR_DRBS_0xA0_Val            _UINT32_(0xA0)                                       /* (GMAC_DCFGR) 10240 bytes (1 x 10K jumbo frame/buffer)  */
#define GMAC_DCFGR_DRBS_0x02                  (GMAC_DCFGR_DRBS_0x02_Val << GMAC_DCFGR_DRBS_Pos)    /* (GMAC_DCFGR) 128 bytes Position  */
#define GMAC_DCFGR_DRBS_0x18                  (GMAC_DCFGR_DRBS_0x18_Val << GMAC_DCFGR_DRBS_Pos)    /* (GMAC_DCFGR) 1536 bytes (1 x max length frame/buffer) Position  */
#define GMAC_DCFGR_DRBS_0xA0                  (GMAC_DCFGR_DRBS_0xA0_Val << GMAC_DCFGR_DRBS_Pos)    /* (GMAC_DCFGR) 10240 bytes (1 x 10K jumbo frame/buffer) Position  */
#define GMAC_DCFGR_DDRP_Pos                   _UINT32_(24)                                         /* (GMAC_DCFGR) DMA Discard Receive Packets Position */
#define GMAC_DCFGR_DDRP_Msk                   (_UINT32_(0x1) << GMAC_DCFGR_DDRP_Pos)               /* (GMAC_DCFGR) DMA Discard Receive Packets Mask */
#define GMAC_DCFGR_DDRP(value)                (GMAC_DCFGR_DDRP_Msk & (_UINT32_(value) << GMAC_DCFGR_DDRP_Pos)) /* Assigment of value for DDRP in the GMAC_DCFGR register */
#define GMAC_DCFGR_RXFOMAXB_Pos               _UINT32_(25)                                         /* (GMAC_DCFGR) Force Receive Max Burst Length Position */
#define GMAC_DCFGR_RXFOMAXB_Msk               (_UINT32_(0x1) << GMAC_DCFGR_RXFOMAXB_Pos)           /* (GMAC_DCFGR) Force Receive Max Burst Length Mask */
#define GMAC_DCFGR_RXFOMAXB(value)            (GMAC_DCFGR_RXFOMAXB_Msk & (_UINT32_(value) << GMAC_DCFGR_RXFOMAXB_Pos)) /* Assigment of value for RXFOMAXB in the GMAC_DCFGR register */
#define GMAC_DCFGR_TXFOMAXB_Pos               _UINT32_(26)                                         /* (GMAC_DCFGR) Force Transmit Max Burst Length Position */
#define GMAC_DCFGR_TXFOMAXB_Msk               (_UINT32_(0x1) << GMAC_DCFGR_TXFOMAXB_Pos)           /* (GMAC_DCFGR) Force Transmit Max Burst Length Mask */
#define GMAC_DCFGR_TXFOMAXB(value)            (GMAC_DCFGR_TXFOMAXB_Msk & (_UINT32_(value) << GMAC_DCFGR_TXFOMAXB_Pos)) /* Assigment of value for TXFOMAXB in the GMAC_DCFGR register */
#define GMAC_DCFGR_RXBD_EXTENDED_Pos          _UINT32_(28)                                         /* (GMAC_DCFGR) Receive Buffer Descriptor Extended Mode Position */
#define GMAC_DCFGR_RXBD_EXTENDED_Msk          (_UINT32_(0x1) << GMAC_DCFGR_RXBD_EXTENDED_Pos)      /* (GMAC_DCFGR) Receive Buffer Descriptor Extended Mode Mask */
#define GMAC_DCFGR_RXBD_EXTENDED(value)       (GMAC_DCFGR_RXBD_EXTENDED_Msk & (_UINT32_(value) << GMAC_DCFGR_RXBD_EXTENDED_Pos)) /* Assigment of value for RXBD_EXTENDED in the GMAC_DCFGR register */
#define   GMAC_DCFGR_RXBD_EXTENDED_0_Val      _UINT32_(0x0)                                        /* (GMAC_DCFGR) Disables Receive Buffer Data Extended mode.  */
#define   GMAC_DCFGR_RXBD_EXTENDED_1_Val      _UINT32_(0x1)                                        /* (GMAC_DCFGR) Enables Receive Buffer Data Extended mode.  */
#define GMAC_DCFGR_RXBD_EXTENDED_0            (GMAC_DCFGR_RXBD_EXTENDED_0_Val << GMAC_DCFGR_RXBD_EXTENDED_Pos) /* (GMAC_DCFGR) Disables Receive Buffer Data Extended mode. Position  */
#define GMAC_DCFGR_RXBD_EXTENDED_1            (GMAC_DCFGR_RXBD_EXTENDED_1_Val << GMAC_DCFGR_RXBD_EXTENDED_Pos) /* (GMAC_DCFGR) Enables Receive Buffer Data Extended mode. Position  */
#define GMAC_DCFGR_TXBD_EXTENDED_Pos          _UINT32_(29)                                         /* (GMAC_DCFGR) Transmit Buffer Descriptor Extended Mode Position */
#define GMAC_DCFGR_TXBD_EXTENDED_Msk          (_UINT32_(0x1) << GMAC_DCFGR_TXBD_EXTENDED_Pos)      /* (GMAC_DCFGR) Transmit Buffer Descriptor Extended Mode Mask */
#define GMAC_DCFGR_TXBD_EXTENDED(value)       (GMAC_DCFGR_TXBD_EXTENDED_Msk & (_UINT32_(value) << GMAC_DCFGR_TXBD_EXTENDED_Pos)) /* Assigment of value for TXBD_EXTENDED in the GMAC_DCFGR register */
#define   GMAC_DCFGR_TXBD_EXTENDED_0_Val      _UINT32_(0x0)                                        /* (GMAC_DCFGR) Disables Transmit Buffer Data Extended mode.  */
#define   GMAC_DCFGR_TXBD_EXTENDED_1_Val      _UINT32_(0x1)                                        /* (GMAC_DCFGR) Enables Transmit Buffer Data Extended mode.  */
#define GMAC_DCFGR_TXBD_EXTENDED_0            (GMAC_DCFGR_TXBD_EXTENDED_0_Val << GMAC_DCFGR_TXBD_EXTENDED_Pos) /* (GMAC_DCFGR) Disables Transmit Buffer Data Extended mode. Position  */
#define GMAC_DCFGR_TXBD_EXTENDED_1            (GMAC_DCFGR_TXBD_EXTENDED_1_Val << GMAC_DCFGR_TXBD_EXTENDED_Pos) /* (GMAC_DCFGR) Enables Transmit Buffer Data Extended mode. Position  */
#define GMAC_DCFGR_Msk                        _UINT32_(0x37FF3FDF)                                 /* (GMAC_DCFGR) Register Mask  */


/* -------- GMAC_TSR : (GMAC Offset: 0x14) (R/W 32) Transmit Status Register -------- */
#define GMAC_TSR_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_TSR) Transmit Status Register  Reset Value */

#define GMAC_TSR_UBR_Pos                      _UINT32_(0)                                          /* (GMAC_TSR) Used Bit Read Position */
#define GMAC_TSR_UBR_Msk                      (_UINT32_(0x1) << GMAC_TSR_UBR_Pos)                  /* (GMAC_TSR) Used Bit Read Mask */
#define GMAC_TSR_UBR(value)                   (GMAC_TSR_UBR_Msk & (_UINT32_(value) << GMAC_TSR_UBR_Pos)) /* Assigment of value for UBR in the GMAC_TSR register */
#define GMAC_TSR_COL_Pos                      _UINT32_(1)                                          /* (GMAC_TSR) Collision Occurred Position */
#define GMAC_TSR_COL_Msk                      (_UINT32_(0x1) << GMAC_TSR_COL_Pos)                  /* (GMAC_TSR) Collision Occurred Mask */
#define GMAC_TSR_COL(value)                   (GMAC_TSR_COL_Msk & (_UINT32_(value) << GMAC_TSR_COL_Pos)) /* Assigment of value for COL in the GMAC_TSR register */
#define GMAC_TSR_RLE_Pos                      _UINT32_(2)                                          /* (GMAC_TSR) Retry Limit Exceeded Position */
#define GMAC_TSR_RLE_Msk                      (_UINT32_(0x1) << GMAC_TSR_RLE_Pos)                  /* (GMAC_TSR) Retry Limit Exceeded Mask */
#define GMAC_TSR_RLE(value)                   (GMAC_TSR_RLE_Msk & (_UINT32_(value) << GMAC_TSR_RLE_Pos)) /* Assigment of value for RLE in the GMAC_TSR register */
#define GMAC_TSR_TXGO_Pos                     _UINT32_(3)                                          /* (GMAC_TSR) Transmit Go (Read only) Position */
#define GMAC_TSR_TXGO_Msk                     (_UINT32_(0x1) << GMAC_TSR_TXGO_Pos)                 /* (GMAC_TSR) Transmit Go (Read only) Mask */
#define GMAC_TSR_TXGO(value)                  (GMAC_TSR_TXGO_Msk & (_UINT32_(value) << GMAC_TSR_TXGO_Pos)) /* Assigment of value for TXGO in the GMAC_TSR register */
#define GMAC_TSR_TFC_Pos                      _UINT32_(4)                                          /* (GMAC_TSR) Transmit Frame Corruption Due to System Bus Error Position */
#define GMAC_TSR_TFC_Msk                      (_UINT32_(0x1) << GMAC_TSR_TFC_Pos)                  /* (GMAC_TSR) Transmit Frame Corruption Due to System Bus Error Mask */
#define GMAC_TSR_TFC(value)                   (GMAC_TSR_TFC_Msk & (_UINT32_(value) << GMAC_TSR_TFC_Pos)) /* Assigment of value for TFC in the GMAC_TSR register */
#define GMAC_TSR_TXCOMP_Pos                   _UINT32_(5)                                          /* (GMAC_TSR) Transmit Complete Position */
#define GMAC_TSR_TXCOMP_Msk                   (_UINT32_(0x1) << GMAC_TSR_TXCOMP_Pos)               /* (GMAC_TSR) Transmit Complete Mask */
#define GMAC_TSR_TXCOMP(value)                (GMAC_TSR_TXCOMP_Msk & (_UINT32_(value) << GMAC_TSR_TXCOMP_Pos)) /* Assigment of value for TXCOMP in the GMAC_TSR register */
#define GMAC_TSR_HRESP_Pos                    _UINT32_(8)                                          /* (GMAC_TSR) System Bus Response Position */
#define GMAC_TSR_HRESP_Msk                    (_UINT32_(0x1) << GMAC_TSR_HRESP_Pos)                /* (GMAC_TSR) System Bus Response Mask */
#define GMAC_TSR_HRESP(value)                 (GMAC_TSR_HRESP_Msk & (_UINT32_(value) << GMAC_TSR_HRESP_Pos)) /* Assigment of value for HRESP in the GMAC_TSR register */
#define GMAC_TSR_Msk                          _UINT32_(0x0000013F)                                 /* (GMAC_TSR) Register Mask  */


/* -------- GMAC_RBQB : (GMAC Offset: 0x18) (R/W 32) Receive Buffer Queue Base Address Register -------- */
#define GMAC_RBQB_RESETVALUE                  _UINT32_(0x00)                                       /*  (GMAC_RBQB) Receive Buffer Queue Base Address Register  Reset Value */

#define GMAC_RBQB_RXQDIS_Pos                  _UINT32_(0)                                          /* (GMAC_RBQB) Receive Queue Disable Position */
#define GMAC_RBQB_RXQDIS_Msk                  (_UINT32_(0x1) << GMAC_RBQB_RXQDIS_Pos)              /* (GMAC_RBQB) Receive Queue Disable Mask */
#define GMAC_RBQB_RXQDIS(value)               (GMAC_RBQB_RXQDIS_Msk & (_UINT32_(value) << GMAC_RBQB_RXQDIS_Pos)) /* Assigment of value for RXQDIS in the GMAC_RBQB register */
#define   GMAC_RBQB_RXQDIS_0_Val              _UINT32_(0x0)                                        /* (GMAC_RBQB) Queue is enabled.  */
#define   GMAC_RBQB_RXQDIS_1_Val              _UINT32_(0x1)                                        /* (GMAC_RBQB) Queue is disabled. Used to reduce the number of active queues and should only be changed while receive is not enabled.  */
#define GMAC_RBQB_RXQDIS_0                    (GMAC_RBQB_RXQDIS_0_Val << GMAC_RBQB_RXQDIS_Pos)     /* (GMAC_RBQB) Queue is enabled. Position  */
#define GMAC_RBQB_RXQDIS_1                    (GMAC_RBQB_RXQDIS_1_Val << GMAC_RBQB_RXQDIS_Pos)     /* (GMAC_RBQB) Queue is disabled. Used to reduce the number of active queues and should only be changed while receive is not enabled. Position  */
#define GMAC_RBQB_ADDR_Pos                    _UINT32_(2)                                          /* (GMAC_RBQB) Receive Buffer Queue Base Address Position */
#define GMAC_RBQB_ADDR_Msk                    (_UINT32_(0x3FFFFFFF) << GMAC_RBQB_ADDR_Pos)         /* (GMAC_RBQB) Receive Buffer Queue Base Address Mask */
#define GMAC_RBQB_ADDR(value)                 (GMAC_RBQB_ADDR_Msk & (_UINT32_(value) << GMAC_RBQB_ADDR_Pos)) /* Assigment of value for ADDR in the GMAC_RBQB register */
#define GMAC_RBQB_Msk                         _UINT32_(0xFFFFFFFD)                                 /* (GMAC_RBQB) Register Mask  */


/* -------- GMAC_TBQB : (GMAC Offset: 0x1C) (R/W 32) Transmit Buffer Queue Base Address Register -------- */
#define GMAC_TBQB_RESETVALUE                  _UINT32_(0x00)                                       /*  (GMAC_TBQB) Transmit Buffer Queue Base Address Register  Reset Value */

#define GMAC_TBQB_TXQDIS_Pos                  _UINT32_(0)                                          /* (GMAC_TBQB) Transmit Queue Disable Position */
#define GMAC_TBQB_TXQDIS_Msk                  (_UINT32_(0x1) << GMAC_TBQB_TXQDIS_Pos)              /* (GMAC_TBQB) Transmit Queue Disable Mask */
#define GMAC_TBQB_TXQDIS(value)               (GMAC_TBQB_TXQDIS_Msk & (_UINT32_(value) << GMAC_TBQB_TXQDIS_Pos)) /* Assigment of value for TXQDIS in the GMAC_TBQB register */
#define   GMAC_TBQB_TXQDIS_0_Val              _UINT32_(0x0)                                        /* (GMAC_TBQB) Queue is enabled.  */
#define   GMAC_TBQB_TXQDIS_1_Val              _UINT32_(0x1)                                        /* (GMAC_TBQB) Queue is disabled. Used to reduce the number of active queues and should only be changed while transmit is not enabled.  */
#define GMAC_TBQB_TXQDIS_0                    (GMAC_TBQB_TXQDIS_0_Val << GMAC_TBQB_TXQDIS_Pos)     /* (GMAC_TBQB) Queue is enabled. Position  */
#define GMAC_TBQB_TXQDIS_1                    (GMAC_TBQB_TXQDIS_1_Val << GMAC_TBQB_TXQDIS_Pos)     /* (GMAC_TBQB) Queue is disabled. Used to reduce the number of active queues and should only be changed while transmit is not enabled. Position  */
#define GMAC_TBQB_ADDR_Pos                    _UINT32_(2)                                          /* (GMAC_TBQB) Transmit Buffer Queue Base Address Position */
#define GMAC_TBQB_ADDR_Msk                    (_UINT32_(0x3FFFFFFF) << GMAC_TBQB_ADDR_Pos)         /* (GMAC_TBQB) Transmit Buffer Queue Base Address Mask */
#define GMAC_TBQB_ADDR(value)                 (GMAC_TBQB_ADDR_Msk & (_UINT32_(value) << GMAC_TBQB_ADDR_Pos)) /* Assigment of value for ADDR in the GMAC_TBQB register */
#define GMAC_TBQB_Msk                         _UINT32_(0xFFFFFFFD)                                 /* (GMAC_TBQB) Register Mask  */


/* -------- GMAC_RSR : (GMAC Offset: 0x20) (R/W 32) Receive Status Register -------- */
#define GMAC_RSR_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_RSR) Receive Status Register  Reset Value */

#define GMAC_RSR_BNA_Pos                      _UINT32_(0)                                          /* (GMAC_RSR) Buffer Not Available Position */
#define GMAC_RSR_BNA_Msk                      (_UINT32_(0x1) << GMAC_RSR_BNA_Pos)                  /* (GMAC_RSR) Buffer Not Available Mask */
#define GMAC_RSR_BNA(value)                   (GMAC_RSR_BNA_Msk & (_UINT32_(value) << GMAC_RSR_BNA_Pos)) /* Assigment of value for BNA in the GMAC_RSR register */
#define GMAC_RSR_REC_Pos                      _UINT32_(1)                                          /* (GMAC_RSR) Frame Received Position */
#define GMAC_RSR_REC_Msk                      (_UINT32_(0x1) << GMAC_RSR_REC_Pos)                  /* (GMAC_RSR) Frame Received Mask */
#define GMAC_RSR_REC(value)                   (GMAC_RSR_REC_Msk & (_UINT32_(value) << GMAC_RSR_REC_Pos)) /* Assigment of value for REC in the GMAC_RSR register */
#define GMAC_RSR_RXOVR_Pos                    _UINT32_(2)                                          /* (GMAC_RSR) Receive Overrun Position */
#define GMAC_RSR_RXOVR_Msk                    (_UINT32_(0x1) << GMAC_RSR_RXOVR_Pos)                /* (GMAC_RSR) Receive Overrun Mask */
#define GMAC_RSR_RXOVR(value)                 (GMAC_RSR_RXOVR_Msk & (_UINT32_(value) << GMAC_RSR_RXOVR_Pos)) /* Assigment of value for RXOVR in the GMAC_RSR register */
#define GMAC_RSR_HNO_Pos                      _UINT32_(3)                                          /* (GMAC_RSR) System Bus Error Position */
#define GMAC_RSR_HNO_Msk                      (_UINT32_(0x1) << GMAC_RSR_HNO_Pos)                  /* (GMAC_RSR) System Bus Error Mask */
#define GMAC_RSR_HNO(value)                   (GMAC_RSR_HNO_Msk & (_UINT32_(value) << GMAC_RSR_HNO_Pos)) /* Assigment of value for HNO in the GMAC_RSR register */
#define GMAC_RSR_Msk                          _UINT32_(0x0000000F)                                 /* (GMAC_RSR) Register Mask  */


/* -------- GMAC_ISR : (GMAC Offset: 0x24) ( R/ 32) Interrupt Status Register -------- */
#define GMAC_ISR_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_ISR) Interrupt Status Register  Reset Value */

#define GMAC_ISR_MFS_Pos                      _UINT32_(0)                                          /* (GMAC_ISR) Management Frame Sent (Cleared on read) Position */
#define GMAC_ISR_MFS_Msk                      (_UINT32_(0x1) << GMAC_ISR_MFS_Pos)                  /* (GMAC_ISR) Management Frame Sent (Cleared on read) Mask */
#define GMAC_ISR_MFS(value)                   (GMAC_ISR_MFS_Msk & (_UINT32_(value) << GMAC_ISR_MFS_Pos)) /* Assigment of value for MFS in the GMAC_ISR register */
#define GMAC_ISR_RCOMP_Pos                    _UINT32_(1)                                          /* (GMAC_ISR) Receive Complete (Cleared on read) Position */
#define GMAC_ISR_RCOMP_Msk                    (_UINT32_(0x1) << GMAC_ISR_RCOMP_Pos)                /* (GMAC_ISR) Receive Complete (Cleared on read) Mask */
#define GMAC_ISR_RCOMP(value)                 (GMAC_ISR_RCOMP_Msk & (_UINT32_(value) << GMAC_ISR_RCOMP_Pos)) /* Assigment of value for RCOMP in the GMAC_ISR register */
#define GMAC_ISR_RXUBR_Pos                    _UINT32_(2)                                          /* (GMAC_ISR) RX Used Bit Read (Cleared on read) Position */
#define GMAC_ISR_RXUBR_Msk                    (_UINT32_(0x1) << GMAC_ISR_RXUBR_Pos)                /* (GMAC_ISR) RX Used Bit Read (Cleared on read) Mask */
#define GMAC_ISR_RXUBR(value)                 (GMAC_ISR_RXUBR_Msk & (_UINT32_(value) << GMAC_ISR_RXUBR_Pos)) /* Assigment of value for RXUBR in the GMAC_ISR register */
#define GMAC_ISR_TXUBR_Pos                    _UINT32_(3)                                          /* (GMAC_ISR) TX Used Bit Read (Cleared on read) Position */
#define GMAC_ISR_TXUBR_Msk                    (_UINT32_(0x1) << GMAC_ISR_TXUBR_Pos)                /* (GMAC_ISR) TX Used Bit Read (Cleared on read) Mask */
#define GMAC_ISR_TXUBR(value)                 (GMAC_ISR_TXUBR_Msk & (_UINT32_(value) << GMAC_ISR_TXUBR_Pos)) /* Assigment of value for TXUBR in the GMAC_ISR register */
#define GMAC_ISR_TUR_Pos                      _UINT32_(4)                                          /* (GMAC_ISR) Transmit Underrun (Cleared on read) Position */
#define GMAC_ISR_TUR_Msk                      (_UINT32_(0x1) << GMAC_ISR_TUR_Pos)                  /* (GMAC_ISR) Transmit Underrun (Cleared on read) Mask */
#define GMAC_ISR_TUR(value)                   (GMAC_ISR_TUR_Msk & (_UINT32_(value) << GMAC_ISR_TUR_Pos)) /* Assigment of value for TUR in the GMAC_ISR register */
#define GMAC_ISR_RLEX_Pos                     _UINT32_(5)                                          /* (GMAC_ISR) Retry Limit Exceeded(Cleared on read) Position */
#define GMAC_ISR_RLEX_Msk                     (_UINT32_(0x1) << GMAC_ISR_RLEX_Pos)                 /* (GMAC_ISR) Retry Limit Exceeded(Cleared on read) Mask */
#define GMAC_ISR_RLEX(value)                  (GMAC_ISR_RLEX_Msk & (_UINT32_(value) << GMAC_ISR_RLEX_Pos)) /* Assigment of value for RLEX in the GMAC_ISR register */
#define GMAC_ISR_TFC_Pos                      _UINT32_(6)                                          /* (GMAC_ISR) Transmit Frame Corruption Due to System Bus Error (Cleared on read) Position */
#define GMAC_ISR_TFC_Msk                      (_UINT32_(0x1) << GMAC_ISR_TFC_Pos)                  /* (GMAC_ISR) Transmit Frame Corruption Due to System Bus Error (Cleared on read) Mask */
#define GMAC_ISR_TFC(value)                   (GMAC_ISR_TFC_Msk & (_UINT32_(value) << GMAC_ISR_TFC_Pos)) /* Assigment of value for TFC in the GMAC_ISR register */
#define GMAC_ISR_TCOMP_Pos                    _UINT32_(7)                                          /* (GMAC_ISR) Transmit Complete (Cleared on read) Position */
#define GMAC_ISR_TCOMP_Msk                    (_UINT32_(0x1) << GMAC_ISR_TCOMP_Pos)                /* (GMAC_ISR) Transmit Complete (Cleared on read) Mask */
#define GMAC_ISR_TCOMP(value)                 (GMAC_ISR_TCOMP_Msk & (_UINT32_(value) << GMAC_ISR_TCOMP_Pos)) /* Assigment of value for TCOMP in the GMAC_ISR register */
#define GMAC_ISR_ROVR_Pos                     _UINT32_(10)                                         /* (GMAC_ISR) Receive Overrun (Cleared on read) Position */
#define GMAC_ISR_ROVR_Msk                     (_UINT32_(0x1) << GMAC_ISR_ROVR_Pos)                 /* (GMAC_ISR) Receive Overrun (Cleared on read) Mask */
#define GMAC_ISR_ROVR(value)                  (GMAC_ISR_ROVR_Msk & (_UINT32_(value) << GMAC_ISR_ROVR_Pos)) /* Assigment of value for ROVR in the GMAC_ISR register */
#define GMAC_ISR_HRESP_Pos                    _UINT32_(11)                                         /* (GMAC_ISR) System Bus Error (Cleared on read) Position */
#define GMAC_ISR_HRESP_Msk                    (_UINT32_(0x1) << GMAC_ISR_HRESP_Pos)                /* (GMAC_ISR) System Bus Error (Cleared on read) Mask */
#define GMAC_ISR_HRESP(value)                 (GMAC_ISR_HRESP_Msk & (_UINT32_(value) << GMAC_ISR_HRESP_Pos)) /* Assigment of value for HRESP in the GMAC_ISR register */
#define GMAC_ISR_PFNZ_Pos                     _UINT32_(12)                                         /* (GMAC_ISR) Pause Frame with Non-zero Pause Quantum Received (Cleared on read) Position */
#define GMAC_ISR_PFNZ_Msk                     (_UINT32_(0x1) << GMAC_ISR_PFNZ_Pos)                 /* (GMAC_ISR) Pause Frame with Non-zero Pause Quantum Received (Cleared on read) Mask */
#define GMAC_ISR_PFNZ(value)                  (GMAC_ISR_PFNZ_Msk & (_UINT32_(value) << GMAC_ISR_PFNZ_Pos)) /* Assigment of value for PFNZ in the GMAC_ISR register */
#define GMAC_ISR_PTZ_Pos                      _UINT32_(13)                                         /* (GMAC_ISR) Pause Time Zero (Cleared on read) Position */
#define GMAC_ISR_PTZ_Msk                      (_UINT32_(0x1) << GMAC_ISR_PTZ_Pos)                  /* (GMAC_ISR) Pause Time Zero (Cleared on read) Mask */
#define GMAC_ISR_PTZ(value)                   (GMAC_ISR_PTZ_Msk & (_UINT32_(value) << GMAC_ISR_PTZ_Pos)) /* Assigment of value for PTZ in the GMAC_ISR register */
#define GMAC_ISR_PFTR_Pos                     _UINT32_(14)                                         /* (GMAC_ISR) Pause Frame Transmitted (Cleared on read) Position */
#define GMAC_ISR_PFTR_Msk                     (_UINT32_(0x1) << GMAC_ISR_PFTR_Pos)                 /* (GMAC_ISR) Pause Frame Transmitted (Cleared on read) Mask */
#define GMAC_ISR_PFTR(value)                  (GMAC_ISR_PFTR_Msk & (_UINT32_(value) << GMAC_ISR_PFTR_Pos)) /* Assigment of value for PFTR in the GMAC_ISR register */
#define GMAC_ISR_DRQFR_Pos                    _UINT32_(18)                                         /* (GMAC_ISR) PTP Delay Request Frame Received (Cleared on read) Position */
#define GMAC_ISR_DRQFR_Msk                    (_UINT32_(0x1) << GMAC_ISR_DRQFR_Pos)                /* (GMAC_ISR) PTP Delay Request Frame Received (Cleared on read) Mask */
#define GMAC_ISR_DRQFR(value)                 (GMAC_ISR_DRQFR_Msk & (_UINT32_(value) << GMAC_ISR_DRQFR_Pos)) /* Assigment of value for DRQFR in the GMAC_ISR register */
#define GMAC_ISR_SFR_Pos                      _UINT32_(19)                                         /* (GMAC_ISR) PTP Sync Frame Received (Cleared on read) Position */
#define GMAC_ISR_SFR_Msk                      (_UINT32_(0x1) << GMAC_ISR_SFR_Pos)                  /* (GMAC_ISR) PTP Sync Frame Received (Cleared on read) Mask */
#define GMAC_ISR_SFR(value)                   (GMAC_ISR_SFR_Msk & (_UINT32_(value) << GMAC_ISR_SFR_Pos)) /* Assigment of value for SFR in the GMAC_ISR register */
#define GMAC_ISR_DRQFT_Pos                    _UINT32_(20)                                         /* (GMAC_ISR) PTP Delay Request Frame Transmitted (Cleared on read) Position */
#define GMAC_ISR_DRQFT_Msk                    (_UINT32_(0x1) << GMAC_ISR_DRQFT_Pos)                /* (GMAC_ISR) PTP Delay Request Frame Transmitted (Cleared on read) Mask */
#define GMAC_ISR_DRQFT(value)                 (GMAC_ISR_DRQFT_Msk & (_UINT32_(value) << GMAC_ISR_DRQFT_Pos)) /* Assigment of value for DRQFT in the GMAC_ISR register */
#define GMAC_ISR_SFT_Pos                      _UINT32_(21)                                         /* (GMAC_ISR) PTP Sync Frame Transmitted (Cleared on read) Position */
#define GMAC_ISR_SFT_Msk                      (_UINT32_(0x1) << GMAC_ISR_SFT_Pos)                  /* (GMAC_ISR) PTP Sync Frame Transmitted (Cleared on read) Mask */
#define GMAC_ISR_SFT(value)                   (GMAC_ISR_SFT_Msk & (_UINT32_(value) << GMAC_ISR_SFT_Pos)) /* Assigment of value for SFT in the GMAC_ISR register */
#define GMAC_ISR_PDRQFR_Pos                   _UINT32_(22)                                         /* (GMAC_ISR) PDelay Request Frame Received (Cleared on read) Position */
#define GMAC_ISR_PDRQFR_Msk                   (_UINT32_(0x1) << GMAC_ISR_PDRQFR_Pos)               /* (GMAC_ISR) PDelay Request Frame Received (Cleared on read) Mask */
#define GMAC_ISR_PDRQFR(value)                (GMAC_ISR_PDRQFR_Msk & (_UINT32_(value) << GMAC_ISR_PDRQFR_Pos)) /* Assigment of value for PDRQFR in the GMAC_ISR register */
#define GMAC_ISR_PDRSFR_Pos                   _UINT32_(23)                                         /* (GMAC_ISR) PDelay Response Frame Received (Cleared on read) Position */
#define GMAC_ISR_PDRSFR_Msk                   (_UINT32_(0x1) << GMAC_ISR_PDRSFR_Pos)               /* (GMAC_ISR) PDelay Response Frame Received (Cleared on read) Mask */
#define GMAC_ISR_PDRSFR(value)                (GMAC_ISR_PDRSFR_Msk & (_UINT32_(value) << GMAC_ISR_PDRSFR_Pos)) /* Assigment of value for PDRSFR in the GMAC_ISR register */
#define GMAC_ISR_PDRQFT_Pos                   _UINT32_(24)                                         /* (GMAC_ISR) PDelay Request Frame Transmitted (Cleared on read) Position */
#define GMAC_ISR_PDRQFT_Msk                   (_UINT32_(0x1) << GMAC_ISR_PDRQFT_Pos)               /* (GMAC_ISR) PDelay Request Frame Transmitted (Cleared on read) Mask */
#define GMAC_ISR_PDRQFT(value)                (GMAC_ISR_PDRQFT_Msk & (_UINT32_(value) << GMAC_ISR_PDRQFT_Pos)) /* Assigment of value for PDRQFT in the GMAC_ISR register */
#define GMAC_ISR_PDRSFT_Pos                   _UINT32_(25)                                         /* (GMAC_ISR) PDelay Response Frame Transmitted (Cleared on read) Position */
#define GMAC_ISR_PDRSFT_Msk                   (_UINT32_(0x1) << GMAC_ISR_PDRSFT_Pos)               /* (GMAC_ISR) PDelay Response Frame Transmitted (Cleared on read) Mask */
#define GMAC_ISR_PDRSFT(value)                (GMAC_ISR_PDRSFT_Msk & (_UINT32_(value) << GMAC_ISR_PDRSFT_Pos)) /* Assigment of value for PDRSFT in the GMAC_ISR register */
#define GMAC_ISR_SRI_Pos                      _UINT32_(26)                                         /* (GMAC_ISR) TSU Seconds Register Increment (Cleared on read) Position */
#define GMAC_ISR_SRI_Msk                      (_UINT32_(0x1) << GMAC_ISR_SRI_Pos)                  /* (GMAC_ISR) TSU Seconds Register Increment (Cleared on read) Mask */
#define GMAC_ISR_SRI(value)                   (GMAC_ISR_SRI_Msk & (_UINT32_(value) << GMAC_ISR_SRI_Pos)) /* Assigment of value for SRI in the GMAC_ISR register */
#define GMAC_ISR_RXLPISBC_Pos                 _UINT32_(27)                                         /* (GMAC_ISR) Receive LPI indication Status Bit Change (Cleared on read) Position */
#define GMAC_ISR_RXLPISBC_Msk                 (_UINT32_(0x1) << GMAC_ISR_RXLPISBC_Pos)             /* (GMAC_ISR) Receive LPI indication Status Bit Change (Cleared on read) Mask */
#define GMAC_ISR_RXLPISBC(value)              (GMAC_ISR_RXLPISBC_Msk & (_UINT32_(value) << GMAC_ISR_RXLPISBC_Pos)) /* Assigment of value for RXLPISBC in the GMAC_ISR register */
#define GMAC_ISR_WOL_Pos                      _UINT32_(28)                                         /* (GMAC_ISR) Wake On LAN Position */
#define GMAC_ISR_WOL_Msk                      (_UINT32_(0x1) << GMAC_ISR_WOL_Pos)                  /* (GMAC_ISR) Wake On LAN Mask */
#define GMAC_ISR_WOL(value)                   (GMAC_ISR_WOL_Msk & (_UINT32_(value) << GMAC_ISR_WOL_Pos)) /* Assigment of value for WOL in the GMAC_ISR register */
#define GMAC_ISR_TSUTIMCOMP_Pos               _UINT32_(29)                                         /* (GMAC_ISR) TSU Timer Comparison (Cleared on read) Position */
#define GMAC_ISR_TSUTIMCOMP_Msk               (_UINT32_(0x1) << GMAC_ISR_TSUTIMCOMP_Pos)           /* (GMAC_ISR) TSU Timer Comparison (Cleared on read) Mask */
#define GMAC_ISR_TSUTIMCOMP(value)            (GMAC_ISR_TSUTIMCOMP_Msk & (_UINT32_(value) << GMAC_ISR_TSUTIMCOMP_Pos)) /* Assigment of value for TSUTIMCOMP in the GMAC_ISR register */
#define GMAC_ISR_Msk                          _UINT32_(0x3FFC7CFF)                                 /* (GMAC_ISR) Register Mask  */


/* -------- GMAC_IER : (GMAC Offset: 0x28) ( /W 32) Interrupt Enable Register -------- */
#define GMAC_IER_MFS_Pos                      _UINT32_(0)                                          /* (GMAC_IER) Management Frame Sent Position */
#define GMAC_IER_MFS_Msk                      (_UINT32_(0x1) << GMAC_IER_MFS_Pos)                  /* (GMAC_IER) Management Frame Sent Mask */
#define GMAC_IER_MFS(value)                   (GMAC_IER_MFS_Msk & (_UINT32_(value) << GMAC_IER_MFS_Pos)) /* Assigment of value for MFS in the GMAC_IER register */
#define GMAC_IER_RCOMP_Pos                    _UINT32_(1)                                          /* (GMAC_IER) Receive Complete Position */
#define GMAC_IER_RCOMP_Msk                    (_UINT32_(0x1) << GMAC_IER_RCOMP_Pos)                /* (GMAC_IER) Receive Complete Mask */
#define GMAC_IER_RCOMP(value)                 (GMAC_IER_RCOMP_Msk & (_UINT32_(value) << GMAC_IER_RCOMP_Pos)) /* Assigment of value for RCOMP in the GMAC_IER register */
#define GMAC_IER_RXUBR_Pos                    _UINT32_(2)                                          /* (GMAC_IER) RX Used Bit Read Position */
#define GMAC_IER_RXUBR_Msk                    (_UINT32_(0x1) << GMAC_IER_RXUBR_Pos)                /* (GMAC_IER) RX Used Bit Read Mask */
#define GMAC_IER_RXUBR(value)                 (GMAC_IER_RXUBR_Msk & (_UINT32_(value) << GMAC_IER_RXUBR_Pos)) /* Assigment of value for RXUBR in the GMAC_IER register */
#define GMAC_IER_TXUBR_Pos                    _UINT32_(3)                                          /* (GMAC_IER) TX Used Bit Read Position */
#define GMAC_IER_TXUBR_Msk                    (_UINT32_(0x1) << GMAC_IER_TXUBR_Pos)                /* (GMAC_IER) TX Used Bit Read Mask */
#define GMAC_IER_TXUBR(value)                 (GMAC_IER_TXUBR_Msk & (_UINT32_(value) << GMAC_IER_TXUBR_Pos)) /* Assigment of value for TXUBR in the GMAC_IER register */
#define GMAC_IER_TUR_Pos                      _UINT32_(4)                                          /* (GMAC_IER) Transmit Underrun Position */
#define GMAC_IER_TUR_Msk                      (_UINT32_(0x1) << GMAC_IER_TUR_Pos)                  /* (GMAC_IER) Transmit Underrun Mask */
#define GMAC_IER_TUR(value)                   (GMAC_IER_TUR_Msk & (_UINT32_(value) << GMAC_IER_TUR_Pos)) /* Assigment of value for TUR in the GMAC_IER register */
#define GMAC_IER_RLEX_Pos                     _UINT32_(5)                                          /* (GMAC_IER) Retry Limit Exceeded or Late Collision Position */
#define GMAC_IER_RLEX_Msk                     (_UINT32_(0x1) << GMAC_IER_RLEX_Pos)                 /* (GMAC_IER) Retry Limit Exceeded or Late Collision Mask */
#define GMAC_IER_RLEX(value)                  (GMAC_IER_RLEX_Msk & (_UINT32_(value) << GMAC_IER_RLEX_Pos)) /* Assigment of value for RLEX in the GMAC_IER register */
#define GMAC_IER_TFC_Pos                      _UINT32_(6)                                          /* (GMAC_IER) Transmit Frame Corruption Due to System Bus Error Position */
#define GMAC_IER_TFC_Msk                      (_UINT32_(0x1) << GMAC_IER_TFC_Pos)                  /* (GMAC_IER) Transmit Frame Corruption Due to System Bus Error Mask */
#define GMAC_IER_TFC(value)                   (GMAC_IER_TFC_Msk & (_UINT32_(value) << GMAC_IER_TFC_Pos)) /* Assigment of value for TFC in the GMAC_IER register */
#define GMAC_IER_TCOMP_Pos                    _UINT32_(7)                                          /* (GMAC_IER) Transmit Complete Position */
#define GMAC_IER_TCOMP_Msk                    (_UINT32_(0x1) << GMAC_IER_TCOMP_Pos)                /* (GMAC_IER) Transmit Complete Mask */
#define GMAC_IER_TCOMP(value)                 (GMAC_IER_TCOMP_Msk & (_UINT32_(value) << GMAC_IER_TCOMP_Pos)) /* Assigment of value for TCOMP in the GMAC_IER register */
#define GMAC_IER_ROVR_Pos                     _UINT32_(10)                                         /* (GMAC_IER) Receive Overrun Position */
#define GMAC_IER_ROVR_Msk                     (_UINT32_(0x1) << GMAC_IER_ROVR_Pos)                 /* (GMAC_IER) Receive Overrun Mask */
#define GMAC_IER_ROVR(value)                  (GMAC_IER_ROVR_Msk & (_UINT32_(value) << GMAC_IER_ROVR_Pos)) /* Assigment of value for ROVR in the GMAC_IER register */
#define GMAC_IER_HRESP_Pos                    _UINT32_(11)                                         /* (GMAC_IER) System Bus Error Position */
#define GMAC_IER_HRESP_Msk                    (_UINT32_(0x1) << GMAC_IER_HRESP_Pos)                /* (GMAC_IER) System Bus Error Mask */
#define GMAC_IER_HRESP(value)                 (GMAC_IER_HRESP_Msk & (_UINT32_(value) << GMAC_IER_HRESP_Pos)) /* Assigment of value for HRESP in the GMAC_IER register */
#define GMAC_IER_PFNZ_Pos                     _UINT32_(12)                                         /* (GMAC_IER) Pause Frame with Non-zero Pause Quantum Received Position */
#define GMAC_IER_PFNZ_Msk                     (_UINT32_(0x1) << GMAC_IER_PFNZ_Pos)                 /* (GMAC_IER) Pause Frame with Non-zero Pause Quantum Received Mask */
#define GMAC_IER_PFNZ(value)                  (GMAC_IER_PFNZ_Msk & (_UINT32_(value) << GMAC_IER_PFNZ_Pos)) /* Assigment of value for PFNZ in the GMAC_IER register */
#define GMAC_IER_PTZ_Pos                      _UINT32_(13)                                         /* (GMAC_IER) Pause Time Zero Position */
#define GMAC_IER_PTZ_Msk                      (_UINT32_(0x1) << GMAC_IER_PTZ_Pos)                  /* (GMAC_IER) Pause Time Zero Mask */
#define GMAC_IER_PTZ(value)                   (GMAC_IER_PTZ_Msk & (_UINT32_(value) << GMAC_IER_PTZ_Pos)) /* Assigment of value for PTZ in the GMAC_IER register */
#define GMAC_IER_PFTR_Pos                     _UINT32_(14)                                         /* (GMAC_IER) Pause Frame Transmitted Position */
#define GMAC_IER_PFTR_Msk                     (_UINT32_(0x1) << GMAC_IER_PFTR_Pos)                 /* (GMAC_IER) Pause Frame Transmitted Mask */
#define GMAC_IER_PFTR(value)                  (GMAC_IER_PFTR_Msk & (_UINT32_(value) << GMAC_IER_PFTR_Pos)) /* Assigment of value for PFTR in the GMAC_IER register */
#define GMAC_IER_EXINT_Pos                    _UINT32_(15)                                         /* (GMAC_IER) External Interrupt Position */
#define GMAC_IER_EXINT_Msk                    (_UINT32_(0x1) << GMAC_IER_EXINT_Pos)                /* (GMAC_IER) External Interrupt Mask */
#define GMAC_IER_EXINT(value)                 (GMAC_IER_EXINT_Msk & (_UINT32_(value) << GMAC_IER_EXINT_Pos)) /* Assigment of value for EXINT in the GMAC_IER register */
#define GMAC_IER_DRQFR_Pos                    _UINT32_(18)                                         /* (GMAC_IER) PTP Delay Request Frame Received Position */
#define GMAC_IER_DRQFR_Msk                    (_UINT32_(0x1) << GMAC_IER_DRQFR_Pos)                /* (GMAC_IER) PTP Delay Request Frame Received Mask */
#define GMAC_IER_DRQFR(value)                 (GMAC_IER_DRQFR_Msk & (_UINT32_(value) << GMAC_IER_DRQFR_Pos)) /* Assigment of value for DRQFR in the GMAC_IER register */
#define GMAC_IER_SFR_Pos                      _UINT32_(19)                                         /* (GMAC_IER) PTP Sync Frame Received Position */
#define GMAC_IER_SFR_Msk                      (_UINT32_(0x1) << GMAC_IER_SFR_Pos)                  /* (GMAC_IER) PTP Sync Frame Received Mask */
#define GMAC_IER_SFR(value)                   (GMAC_IER_SFR_Msk & (_UINT32_(value) << GMAC_IER_SFR_Pos)) /* Assigment of value for SFR in the GMAC_IER register */
#define GMAC_IER_DRQFT_Pos                    _UINT32_(20)                                         /* (GMAC_IER) PTP Delay Request Frame Transmitted Position */
#define GMAC_IER_DRQFT_Msk                    (_UINT32_(0x1) << GMAC_IER_DRQFT_Pos)                /* (GMAC_IER) PTP Delay Request Frame Transmitted Mask */
#define GMAC_IER_DRQFT(value)                 (GMAC_IER_DRQFT_Msk & (_UINT32_(value) << GMAC_IER_DRQFT_Pos)) /* Assigment of value for DRQFT in the GMAC_IER register */
#define GMAC_IER_SFT_Pos                      _UINT32_(21)                                         /* (GMAC_IER) PTP Sync Frame Transmitted Position */
#define GMAC_IER_SFT_Msk                      (_UINT32_(0x1) << GMAC_IER_SFT_Pos)                  /* (GMAC_IER) PTP Sync Frame Transmitted Mask */
#define GMAC_IER_SFT(value)                   (GMAC_IER_SFT_Msk & (_UINT32_(value) << GMAC_IER_SFT_Pos)) /* Assigment of value for SFT in the GMAC_IER register */
#define GMAC_IER_PDRQFR_Pos                   _UINT32_(22)                                         /* (GMAC_IER) PDelay Request Frame Received Position */
#define GMAC_IER_PDRQFR_Msk                   (_UINT32_(0x1) << GMAC_IER_PDRQFR_Pos)               /* (GMAC_IER) PDelay Request Frame Received Mask */
#define GMAC_IER_PDRQFR(value)                (GMAC_IER_PDRQFR_Msk & (_UINT32_(value) << GMAC_IER_PDRQFR_Pos)) /* Assigment of value for PDRQFR in the GMAC_IER register */
#define GMAC_IER_PDRSFR_Pos                   _UINT32_(23)                                         /* (GMAC_IER) PDelay Response Frame Received Position */
#define GMAC_IER_PDRSFR_Msk                   (_UINT32_(0x1) << GMAC_IER_PDRSFR_Pos)               /* (GMAC_IER) PDelay Response Frame Received Mask */
#define GMAC_IER_PDRSFR(value)                (GMAC_IER_PDRSFR_Msk & (_UINT32_(value) << GMAC_IER_PDRSFR_Pos)) /* Assigment of value for PDRSFR in the GMAC_IER register */
#define GMAC_IER_PDRQFT_Pos                   _UINT32_(24)                                         /* (GMAC_IER) PDelay Request Frame Transmitted Position */
#define GMAC_IER_PDRQFT_Msk                   (_UINT32_(0x1) << GMAC_IER_PDRQFT_Pos)               /* (GMAC_IER) PDelay Request Frame Transmitted Mask */
#define GMAC_IER_PDRQFT(value)                (GMAC_IER_PDRQFT_Msk & (_UINT32_(value) << GMAC_IER_PDRQFT_Pos)) /* Assigment of value for PDRQFT in the GMAC_IER register */
#define GMAC_IER_PDRSFT_Pos                   _UINT32_(25)                                         /* (GMAC_IER) PDelay Response Frame Transmitted Position */
#define GMAC_IER_PDRSFT_Msk                   (_UINT32_(0x1) << GMAC_IER_PDRSFT_Pos)               /* (GMAC_IER) PDelay Response Frame Transmitted Mask */
#define GMAC_IER_PDRSFT(value)                (GMAC_IER_PDRSFT_Msk & (_UINT32_(value) << GMAC_IER_PDRSFT_Pos)) /* Assigment of value for PDRSFT in the GMAC_IER register */
#define GMAC_IER_SRI_Pos                      _UINT32_(26)                                         /* (GMAC_IER) TSU Seconds Register Increment Position */
#define GMAC_IER_SRI_Msk                      (_UINT32_(0x1) << GMAC_IER_SRI_Pos)                  /* (GMAC_IER) TSU Seconds Register Increment Mask */
#define GMAC_IER_SRI(value)                   (GMAC_IER_SRI_Msk & (_UINT32_(value) << GMAC_IER_SRI_Pos)) /* Assigment of value for SRI in the GMAC_IER register */
#define GMAC_IER_RXLPISBC_Pos                 _UINT32_(27)                                         /* (GMAC_IER) Enable RX LPI Indication Position */
#define GMAC_IER_RXLPISBC_Msk                 (_UINT32_(0x1) << GMAC_IER_RXLPISBC_Pos)             /* (GMAC_IER) Enable RX LPI Indication Mask */
#define GMAC_IER_RXLPISBC(value)              (GMAC_IER_RXLPISBC_Msk & (_UINT32_(value) << GMAC_IER_RXLPISBC_Pos)) /* Assigment of value for RXLPISBC in the GMAC_IER register */
#define GMAC_IER_WOL_Pos                      _UINT32_(28)                                         /* (GMAC_IER) Wake On LAN Position */
#define GMAC_IER_WOL_Msk                      (_UINT32_(0x1) << GMAC_IER_WOL_Pos)                  /* (GMAC_IER) Wake On LAN Mask */
#define GMAC_IER_WOL(value)                   (GMAC_IER_WOL_Msk & (_UINT32_(value) << GMAC_IER_WOL_Pos)) /* Assigment of value for WOL in the GMAC_IER register */
#define GMAC_IER_TSUTIMCOMP_Pos               _UINT32_(29)                                         /* (GMAC_IER) TSU Timer Comparison Position */
#define GMAC_IER_TSUTIMCOMP_Msk               (_UINT32_(0x1) << GMAC_IER_TSUTIMCOMP_Pos)           /* (GMAC_IER) TSU Timer Comparison Mask */
#define GMAC_IER_TSUTIMCOMP(value)            (GMAC_IER_TSUTIMCOMP_Msk & (_UINT32_(value) << GMAC_IER_TSUTIMCOMP_Pos)) /* Assigment of value for TSUTIMCOMP in the GMAC_IER register */
#define GMAC_IER_Msk                          _UINT32_(0x3FFCFCFF)                                 /* (GMAC_IER) Register Mask  */


/* -------- GMAC_IDR : (GMAC Offset: 0x2C) ( /W 32) Interrupt Disable Register -------- */
#define GMAC_IDR_MFS_Pos                      _UINT32_(0)                                          /* (GMAC_IDR) Management Frame Sent Position */
#define GMAC_IDR_MFS_Msk                      (_UINT32_(0x1) << GMAC_IDR_MFS_Pos)                  /* (GMAC_IDR) Management Frame Sent Mask */
#define GMAC_IDR_MFS(value)                   (GMAC_IDR_MFS_Msk & (_UINT32_(value) << GMAC_IDR_MFS_Pos)) /* Assigment of value for MFS in the GMAC_IDR register */
#define GMAC_IDR_RCOMP_Pos                    _UINT32_(1)                                          /* (GMAC_IDR) Receive Complete Position */
#define GMAC_IDR_RCOMP_Msk                    (_UINT32_(0x1) << GMAC_IDR_RCOMP_Pos)                /* (GMAC_IDR) Receive Complete Mask */
#define GMAC_IDR_RCOMP(value)                 (GMAC_IDR_RCOMP_Msk & (_UINT32_(value) << GMAC_IDR_RCOMP_Pos)) /* Assigment of value for RCOMP in the GMAC_IDR register */
#define GMAC_IDR_RXUBR_Pos                    _UINT32_(2)                                          /* (GMAC_IDR) RX Used Bit Read Position */
#define GMAC_IDR_RXUBR_Msk                    (_UINT32_(0x1) << GMAC_IDR_RXUBR_Pos)                /* (GMAC_IDR) RX Used Bit Read Mask */
#define GMAC_IDR_RXUBR(value)                 (GMAC_IDR_RXUBR_Msk & (_UINT32_(value) << GMAC_IDR_RXUBR_Pos)) /* Assigment of value for RXUBR in the GMAC_IDR register */
#define GMAC_IDR_TXUBR_Pos                    _UINT32_(3)                                          /* (GMAC_IDR) TX Used Bit Read Position */
#define GMAC_IDR_TXUBR_Msk                    (_UINT32_(0x1) << GMAC_IDR_TXUBR_Pos)                /* (GMAC_IDR) TX Used Bit Read Mask */
#define GMAC_IDR_TXUBR(value)                 (GMAC_IDR_TXUBR_Msk & (_UINT32_(value) << GMAC_IDR_TXUBR_Pos)) /* Assigment of value for TXUBR in the GMAC_IDR register */
#define GMAC_IDR_TUR_Pos                      _UINT32_(4)                                          /* (GMAC_IDR) Transmit Underrun Position */
#define GMAC_IDR_TUR_Msk                      (_UINT32_(0x1) << GMAC_IDR_TUR_Pos)                  /* (GMAC_IDR) Transmit Underrun Mask */
#define GMAC_IDR_TUR(value)                   (GMAC_IDR_TUR_Msk & (_UINT32_(value) << GMAC_IDR_TUR_Pos)) /* Assigment of value for TUR in the GMAC_IDR register */
#define GMAC_IDR_RLEX_Pos                     _UINT32_(5)                                          /* (GMAC_IDR) Retry Limit Exceeded or Late Collision Position */
#define GMAC_IDR_RLEX_Msk                     (_UINT32_(0x1) << GMAC_IDR_RLEX_Pos)                 /* (GMAC_IDR) Retry Limit Exceeded or Late Collision Mask */
#define GMAC_IDR_RLEX(value)                  (GMAC_IDR_RLEX_Msk & (_UINT32_(value) << GMAC_IDR_RLEX_Pos)) /* Assigment of value for RLEX in the GMAC_IDR register */
#define GMAC_IDR_TFC_Pos                      _UINT32_(6)                                          /* (GMAC_IDR) Transmit Frame Corruption Due to System Bus Error Position */
#define GMAC_IDR_TFC_Msk                      (_UINT32_(0x1) << GMAC_IDR_TFC_Pos)                  /* (GMAC_IDR) Transmit Frame Corruption Due to System Bus Error Mask */
#define GMAC_IDR_TFC(value)                   (GMAC_IDR_TFC_Msk & (_UINT32_(value) << GMAC_IDR_TFC_Pos)) /* Assigment of value for TFC in the GMAC_IDR register */
#define GMAC_IDR_TCOMP_Pos                    _UINT32_(7)                                          /* (GMAC_IDR) Transmit Complete Position */
#define GMAC_IDR_TCOMP_Msk                    (_UINT32_(0x1) << GMAC_IDR_TCOMP_Pos)                /* (GMAC_IDR) Transmit Complete Mask */
#define GMAC_IDR_TCOMP(value)                 (GMAC_IDR_TCOMP_Msk & (_UINT32_(value) << GMAC_IDR_TCOMP_Pos)) /* Assigment of value for TCOMP in the GMAC_IDR register */
#define GMAC_IDR_ROVR_Pos                     _UINT32_(10)                                         /* (GMAC_IDR) Receive Overrun Position */
#define GMAC_IDR_ROVR_Msk                     (_UINT32_(0x1) << GMAC_IDR_ROVR_Pos)                 /* (GMAC_IDR) Receive Overrun Mask */
#define GMAC_IDR_ROVR(value)                  (GMAC_IDR_ROVR_Msk & (_UINT32_(value) << GMAC_IDR_ROVR_Pos)) /* Assigment of value for ROVR in the GMAC_IDR register */
#define GMAC_IDR_HRESP_Pos                    _UINT32_(11)                                         /* (GMAC_IDR) System Bus Error Position */
#define GMAC_IDR_HRESP_Msk                    (_UINT32_(0x1) << GMAC_IDR_HRESP_Pos)                /* (GMAC_IDR) System Bus Error Mask */
#define GMAC_IDR_HRESP(value)                 (GMAC_IDR_HRESP_Msk & (_UINT32_(value) << GMAC_IDR_HRESP_Pos)) /* Assigment of value for HRESP in the GMAC_IDR register */
#define GMAC_IDR_PFNZ_Pos                     _UINT32_(12)                                         /* (GMAC_IDR) Pause Frame with Non-zero Pause Quantum Received Position */
#define GMAC_IDR_PFNZ_Msk                     (_UINT32_(0x1) << GMAC_IDR_PFNZ_Pos)                 /* (GMAC_IDR) Pause Frame with Non-zero Pause Quantum Received Mask */
#define GMAC_IDR_PFNZ(value)                  (GMAC_IDR_PFNZ_Msk & (_UINT32_(value) << GMAC_IDR_PFNZ_Pos)) /* Assigment of value for PFNZ in the GMAC_IDR register */
#define GMAC_IDR_PTZ_Pos                      _UINT32_(13)                                         /* (GMAC_IDR) Pause Time Zero Position */
#define GMAC_IDR_PTZ_Msk                      (_UINT32_(0x1) << GMAC_IDR_PTZ_Pos)                  /* (GMAC_IDR) Pause Time Zero Mask */
#define GMAC_IDR_PTZ(value)                   (GMAC_IDR_PTZ_Msk & (_UINT32_(value) << GMAC_IDR_PTZ_Pos)) /* Assigment of value for PTZ in the GMAC_IDR register */
#define GMAC_IDR_PFTR_Pos                     _UINT32_(14)                                         /* (GMAC_IDR) Pause Frame Transmitted Position */
#define GMAC_IDR_PFTR_Msk                     (_UINT32_(0x1) << GMAC_IDR_PFTR_Pos)                 /* (GMAC_IDR) Pause Frame Transmitted Mask */
#define GMAC_IDR_PFTR(value)                  (GMAC_IDR_PFTR_Msk & (_UINT32_(value) << GMAC_IDR_PFTR_Pos)) /* Assigment of value for PFTR in the GMAC_IDR register */
#define GMAC_IDR_EXINT_Pos                    _UINT32_(15)                                         /* (GMAC_IDR) External Interrupt Position */
#define GMAC_IDR_EXINT_Msk                    (_UINT32_(0x1) << GMAC_IDR_EXINT_Pos)                /* (GMAC_IDR) External Interrupt Mask */
#define GMAC_IDR_EXINT(value)                 (GMAC_IDR_EXINT_Msk & (_UINT32_(value) << GMAC_IDR_EXINT_Pos)) /* Assigment of value for EXINT in the GMAC_IDR register */
#define GMAC_IDR_DRQFR_Pos                    _UINT32_(18)                                         /* (GMAC_IDR) PTP Delay Request Frame Received Position */
#define GMAC_IDR_DRQFR_Msk                    (_UINT32_(0x1) << GMAC_IDR_DRQFR_Pos)                /* (GMAC_IDR) PTP Delay Request Frame Received Mask */
#define GMAC_IDR_DRQFR(value)                 (GMAC_IDR_DRQFR_Msk & (_UINT32_(value) << GMAC_IDR_DRQFR_Pos)) /* Assigment of value for DRQFR in the GMAC_IDR register */
#define GMAC_IDR_SFR_Pos                      _UINT32_(19)                                         /* (GMAC_IDR) PTP Sync Frame Received Position */
#define GMAC_IDR_SFR_Msk                      (_UINT32_(0x1) << GMAC_IDR_SFR_Pos)                  /* (GMAC_IDR) PTP Sync Frame Received Mask */
#define GMAC_IDR_SFR(value)                   (GMAC_IDR_SFR_Msk & (_UINT32_(value) << GMAC_IDR_SFR_Pos)) /* Assigment of value for SFR in the GMAC_IDR register */
#define GMAC_IDR_DRQFT_Pos                    _UINT32_(20)                                         /* (GMAC_IDR) PTP Delay Request Frame Transmitted Position */
#define GMAC_IDR_DRQFT_Msk                    (_UINT32_(0x1) << GMAC_IDR_DRQFT_Pos)                /* (GMAC_IDR) PTP Delay Request Frame Transmitted Mask */
#define GMAC_IDR_DRQFT(value)                 (GMAC_IDR_DRQFT_Msk & (_UINT32_(value) << GMAC_IDR_DRQFT_Pos)) /* Assigment of value for DRQFT in the GMAC_IDR register */
#define GMAC_IDR_SFT_Pos                      _UINT32_(21)                                         /* (GMAC_IDR) PTP Sync Frame Transmitted Position */
#define GMAC_IDR_SFT_Msk                      (_UINT32_(0x1) << GMAC_IDR_SFT_Pos)                  /* (GMAC_IDR) PTP Sync Frame Transmitted Mask */
#define GMAC_IDR_SFT(value)                   (GMAC_IDR_SFT_Msk & (_UINT32_(value) << GMAC_IDR_SFT_Pos)) /* Assigment of value for SFT in the GMAC_IDR register */
#define GMAC_IDR_PDRQFR_Pos                   _UINT32_(22)                                         /* (GMAC_IDR) PDelay Request Frame Received Position */
#define GMAC_IDR_PDRQFR_Msk                   (_UINT32_(0x1) << GMAC_IDR_PDRQFR_Pos)               /* (GMAC_IDR) PDelay Request Frame Received Mask */
#define GMAC_IDR_PDRQFR(value)                (GMAC_IDR_PDRQFR_Msk & (_UINT32_(value) << GMAC_IDR_PDRQFR_Pos)) /* Assigment of value for PDRQFR in the GMAC_IDR register */
#define GMAC_IDR_PDRSFR_Pos                   _UINT32_(23)                                         /* (GMAC_IDR) PDelay Response Frame Received Position */
#define GMAC_IDR_PDRSFR_Msk                   (_UINT32_(0x1) << GMAC_IDR_PDRSFR_Pos)               /* (GMAC_IDR) PDelay Response Frame Received Mask */
#define GMAC_IDR_PDRSFR(value)                (GMAC_IDR_PDRSFR_Msk & (_UINT32_(value) << GMAC_IDR_PDRSFR_Pos)) /* Assigment of value for PDRSFR in the GMAC_IDR register */
#define GMAC_IDR_PDRQFT_Pos                   _UINT32_(24)                                         /* (GMAC_IDR) PDelay Request Frame Transmitted Position */
#define GMAC_IDR_PDRQFT_Msk                   (_UINT32_(0x1) << GMAC_IDR_PDRQFT_Pos)               /* (GMAC_IDR) PDelay Request Frame Transmitted Mask */
#define GMAC_IDR_PDRQFT(value)                (GMAC_IDR_PDRQFT_Msk & (_UINT32_(value) << GMAC_IDR_PDRQFT_Pos)) /* Assigment of value for PDRQFT in the GMAC_IDR register */
#define GMAC_IDR_PDRSFT_Pos                   _UINT32_(25)                                         /* (GMAC_IDR) PDelay Response Frame Transmitted Position */
#define GMAC_IDR_PDRSFT_Msk                   (_UINT32_(0x1) << GMAC_IDR_PDRSFT_Pos)               /* (GMAC_IDR) PDelay Response Frame Transmitted Mask */
#define GMAC_IDR_PDRSFT(value)                (GMAC_IDR_PDRSFT_Msk & (_UINT32_(value) << GMAC_IDR_PDRSFT_Pos)) /* Assigment of value for PDRSFT in the GMAC_IDR register */
#define GMAC_IDR_SRI_Pos                      _UINT32_(26)                                         /* (GMAC_IDR) TSU Seconds Register Increment Position */
#define GMAC_IDR_SRI_Msk                      (_UINT32_(0x1) << GMAC_IDR_SRI_Pos)                  /* (GMAC_IDR) TSU Seconds Register Increment Mask */
#define GMAC_IDR_SRI(value)                   (GMAC_IDR_SRI_Msk & (_UINT32_(value) << GMAC_IDR_SRI_Pos)) /* Assigment of value for SRI in the GMAC_IDR register */
#define GMAC_IDR_RXLPISBC_Pos                 _UINT32_(27)                                         /* (GMAC_IDR) Enable RX LPI Indication Position */
#define GMAC_IDR_RXLPISBC_Msk                 (_UINT32_(0x1) << GMAC_IDR_RXLPISBC_Pos)             /* (GMAC_IDR) Enable RX LPI Indication Mask */
#define GMAC_IDR_RXLPISBC(value)              (GMAC_IDR_RXLPISBC_Msk & (_UINT32_(value) << GMAC_IDR_RXLPISBC_Pos)) /* Assigment of value for RXLPISBC in the GMAC_IDR register */
#define GMAC_IDR_WOL_Pos                      _UINT32_(28)                                         /* (GMAC_IDR) Wake On LAN Position */
#define GMAC_IDR_WOL_Msk                      (_UINT32_(0x1) << GMAC_IDR_WOL_Pos)                  /* (GMAC_IDR) Wake On LAN Mask */
#define GMAC_IDR_WOL(value)                   (GMAC_IDR_WOL_Msk & (_UINT32_(value) << GMAC_IDR_WOL_Pos)) /* Assigment of value for WOL in the GMAC_IDR register */
#define GMAC_IDR_TSUTIMCOMP_Pos               _UINT32_(29)                                         /* (GMAC_IDR) TSU Timer Comparison Position */
#define GMAC_IDR_TSUTIMCOMP_Msk               (_UINT32_(0x1) << GMAC_IDR_TSUTIMCOMP_Pos)           /* (GMAC_IDR) TSU Timer Comparison Mask */
#define GMAC_IDR_TSUTIMCOMP(value)            (GMAC_IDR_TSUTIMCOMP_Msk & (_UINT32_(value) << GMAC_IDR_TSUTIMCOMP_Pos)) /* Assigment of value for TSUTIMCOMP in the GMAC_IDR register */
#define GMAC_IDR_Msk                          _UINT32_(0x3FFCFCFF)                                 /* (GMAC_IDR) Register Mask  */


/* -------- GMAC_IMR : (GMAC Offset: 0x30) (R/W 32) Interrupt Mask Register -------- */
#define GMAC_IMR_RESETVALUE                   _UINT32_(0x7FFFFFF)                                  /*  (GMAC_IMR) Interrupt Mask Register  Reset Value */

#define GMAC_IMR_MFS_Pos                      _UINT32_(0)                                          /* (GMAC_IMR) Management Frame Sent Position */
#define GMAC_IMR_MFS_Msk                      (_UINT32_(0x1) << GMAC_IMR_MFS_Pos)                  /* (GMAC_IMR) Management Frame Sent Mask */
#define GMAC_IMR_MFS(value)                   (GMAC_IMR_MFS_Msk & (_UINT32_(value) << GMAC_IMR_MFS_Pos)) /* Assigment of value for MFS in the GMAC_IMR register */
#define GMAC_IMR_RCOMP_Pos                    _UINT32_(1)                                          /* (GMAC_IMR) Receive Complete Position */
#define GMAC_IMR_RCOMP_Msk                    (_UINT32_(0x1) << GMAC_IMR_RCOMP_Pos)                /* (GMAC_IMR) Receive Complete Mask */
#define GMAC_IMR_RCOMP(value)                 (GMAC_IMR_RCOMP_Msk & (_UINT32_(value) << GMAC_IMR_RCOMP_Pos)) /* Assigment of value for RCOMP in the GMAC_IMR register */
#define GMAC_IMR_RXUBR_Pos                    _UINT32_(2)                                          /* (GMAC_IMR) RX Used Bit Read Position */
#define GMAC_IMR_RXUBR_Msk                    (_UINT32_(0x1) << GMAC_IMR_RXUBR_Pos)                /* (GMAC_IMR) RX Used Bit Read Mask */
#define GMAC_IMR_RXUBR(value)                 (GMAC_IMR_RXUBR_Msk & (_UINT32_(value) << GMAC_IMR_RXUBR_Pos)) /* Assigment of value for RXUBR in the GMAC_IMR register */
#define GMAC_IMR_TXUBR_Pos                    _UINT32_(3)                                          /* (GMAC_IMR) TX Used Bit Read Position */
#define GMAC_IMR_TXUBR_Msk                    (_UINT32_(0x1) << GMAC_IMR_TXUBR_Pos)                /* (GMAC_IMR) TX Used Bit Read Mask */
#define GMAC_IMR_TXUBR(value)                 (GMAC_IMR_TXUBR_Msk & (_UINT32_(value) << GMAC_IMR_TXUBR_Pos)) /* Assigment of value for TXUBR in the GMAC_IMR register */
#define GMAC_IMR_TUR_Pos                      _UINT32_(4)                                          /* (GMAC_IMR) Transmit Underrun Position */
#define GMAC_IMR_TUR_Msk                      (_UINT32_(0x1) << GMAC_IMR_TUR_Pos)                  /* (GMAC_IMR) Transmit Underrun Mask */
#define GMAC_IMR_TUR(value)                   (GMAC_IMR_TUR_Msk & (_UINT32_(value) << GMAC_IMR_TUR_Pos)) /* Assigment of value for TUR in the GMAC_IMR register */
#define GMAC_IMR_RLEX_Pos                     _UINT32_(5)                                          /* (GMAC_IMR) Retry Limit Exceeded Position */
#define GMAC_IMR_RLEX_Msk                     (_UINT32_(0x1) << GMAC_IMR_RLEX_Pos)                 /* (GMAC_IMR) Retry Limit Exceeded Mask */
#define GMAC_IMR_RLEX(value)                  (GMAC_IMR_RLEX_Msk & (_UINT32_(value) << GMAC_IMR_RLEX_Pos)) /* Assigment of value for RLEX in the GMAC_IMR register */
#define GMAC_IMR_TFC_Pos                      _UINT32_(6)                                          /* (GMAC_IMR) Transmit Frame Corruption Due to System Bus Error Position */
#define GMAC_IMR_TFC_Msk                      (_UINT32_(0x1) << GMAC_IMR_TFC_Pos)                  /* (GMAC_IMR) Transmit Frame Corruption Due to System Bus Error Mask */
#define GMAC_IMR_TFC(value)                   (GMAC_IMR_TFC_Msk & (_UINT32_(value) << GMAC_IMR_TFC_Pos)) /* Assigment of value for TFC in the GMAC_IMR register */
#define GMAC_IMR_TCOMP_Pos                    _UINT32_(7)                                          /* (GMAC_IMR) Transmit Complete Position */
#define GMAC_IMR_TCOMP_Msk                    (_UINT32_(0x1) << GMAC_IMR_TCOMP_Pos)                /* (GMAC_IMR) Transmit Complete Mask */
#define GMAC_IMR_TCOMP(value)                 (GMAC_IMR_TCOMP_Msk & (_UINT32_(value) << GMAC_IMR_TCOMP_Pos)) /* Assigment of value for TCOMP in the GMAC_IMR register */
#define GMAC_IMR_ROVR_Pos                     _UINT32_(10)                                         /* (GMAC_IMR) Receive Overrun Position */
#define GMAC_IMR_ROVR_Msk                     (_UINT32_(0x1) << GMAC_IMR_ROVR_Pos)                 /* (GMAC_IMR) Receive Overrun Mask */
#define GMAC_IMR_ROVR(value)                  (GMAC_IMR_ROVR_Msk & (_UINT32_(value) << GMAC_IMR_ROVR_Pos)) /* Assigment of value for ROVR in the GMAC_IMR register */
#define GMAC_IMR_HRESP_Pos                    _UINT32_(11)                                         /* (GMAC_IMR) System Bus Error Position */
#define GMAC_IMR_HRESP_Msk                    (_UINT32_(0x1) << GMAC_IMR_HRESP_Pos)                /* (GMAC_IMR) System Bus Error Mask */
#define GMAC_IMR_HRESP(value)                 (GMAC_IMR_HRESP_Msk & (_UINT32_(value) << GMAC_IMR_HRESP_Pos)) /* Assigment of value for HRESP in the GMAC_IMR register */
#define GMAC_IMR_PFNZ_Pos                     _UINT32_(12)                                         /* (GMAC_IMR) Pause Frame with Non-zero Pause Quantum Received Position */
#define GMAC_IMR_PFNZ_Msk                     (_UINT32_(0x1) << GMAC_IMR_PFNZ_Pos)                 /* (GMAC_IMR) Pause Frame with Non-zero Pause Quantum Received Mask */
#define GMAC_IMR_PFNZ(value)                  (GMAC_IMR_PFNZ_Msk & (_UINT32_(value) << GMAC_IMR_PFNZ_Pos)) /* Assigment of value for PFNZ in the GMAC_IMR register */
#define GMAC_IMR_PTZ_Pos                      _UINT32_(13)                                         /* (GMAC_IMR) Pause Time Zero Position */
#define GMAC_IMR_PTZ_Msk                      (_UINT32_(0x1) << GMAC_IMR_PTZ_Pos)                  /* (GMAC_IMR) Pause Time Zero Mask */
#define GMAC_IMR_PTZ(value)                   (GMAC_IMR_PTZ_Msk & (_UINT32_(value) << GMAC_IMR_PTZ_Pos)) /* Assigment of value for PTZ in the GMAC_IMR register */
#define GMAC_IMR_PFTR_Pos                     _UINT32_(14)                                         /* (GMAC_IMR) Pause Frame Transmitted Position */
#define GMAC_IMR_PFTR_Msk                     (_UINT32_(0x1) << GMAC_IMR_PFTR_Pos)                 /* (GMAC_IMR) Pause Frame Transmitted Mask */
#define GMAC_IMR_PFTR(value)                  (GMAC_IMR_PFTR_Msk & (_UINT32_(value) << GMAC_IMR_PFTR_Pos)) /* Assigment of value for PFTR in the GMAC_IMR register */
#define GMAC_IMR_EXINT_Pos                    _UINT32_(15)                                         /* (GMAC_IMR) External Interrupt Position */
#define GMAC_IMR_EXINT_Msk                    (_UINT32_(0x1) << GMAC_IMR_EXINT_Pos)                /* (GMAC_IMR) External Interrupt Mask */
#define GMAC_IMR_EXINT(value)                 (GMAC_IMR_EXINT_Msk & (_UINT32_(value) << GMAC_IMR_EXINT_Pos)) /* Assigment of value for EXINT in the GMAC_IMR register */
#define GMAC_IMR_DRQFR_Pos                    _UINT32_(18)                                         /* (GMAC_IMR) PTP Delay Request Frame Received Position */
#define GMAC_IMR_DRQFR_Msk                    (_UINT32_(0x1) << GMAC_IMR_DRQFR_Pos)                /* (GMAC_IMR) PTP Delay Request Frame Received Mask */
#define GMAC_IMR_DRQFR(value)                 (GMAC_IMR_DRQFR_Msk & (_UINT32_(value) << GMAC_IMR_DRQFR_Pos)) /* Assigment of value for DRQFR in the GMAC_IMR register */
#define GMAC_IMR_SFR_Pos                      _UINT32_(19)                                         /* (GMAC_IMR) PTP Sync Frame Received Position */
#define GMAC_IMR_SFR_Msk                      (_UINT32_(0x1) << GMAC_IMR_SFR_Pos)                  /* (GMAC_IMR) PTP Sync Frame Received Mask */
#define GMAC_IMR_SFR(value)                   (GMAC_IMR_SFR_Msk & (_UINT32_(value) << GMAC_IMR_SFR_Pos)) /* Assigment of value for SFR in the GMAC_IMR register */
#define GMAC_IMR_DRQFT_Pos                    _UINT32_(20)                                         /* (GMAC_IMR) PTP Delay Request Frame Transmitted Position */
#define GMAC_IMR_DRQFT_Msk                    (_UINT32_(0x1) << GMAC_IMR_DRQFT_Pos)                /* (GMAC_IMR) PTP Delay Request Frame Transmitted Mask */
#define GMAC_IMR_DRQFT(value)                 (GMAC_IMR_DRQFT_Msk & (_UINT32_(value) << GMAC_IMR_DRQFT_Pos)) /* Assigment of value for DRQFT in the GMAC_IMR register */
#define GMAC_IMR_SFT_Pos                      _UINT32_(21)                                         /* (GMAC_IMR) PTP Sync Frame Transmitted Position */
#define GMAC_IMR_SFT_Msk                      (_UINT32_(0x1) << GMAC_IMR_SFT_Pos)                  /* (GMAC_IMR) PTP Sync Frame Transmitted Mask */
#define GMAC_IMR_SFT(value)                   (GMAC_IMR_SFT_Msk & (_UINT32_(value) << GMAC_IMR_SFT_Pos)) /* Assigment of value for SFT in the GMAC_IMR register */
#define GMAC_IMR_PDRQFR_Pos                   _UINT32_(22)                                         /* (GMAC_IMR) PDelay Request Frame Received Position */
#define GMAC_IMR_PDRQFR_Msk                   (_UINT32_(0x1) << GMAC_IMR_PDRQFR_Pos)               /* (GMAC_IMR) PDelay Request Frame Received Mask */
#define GMAC_IMR_PDRQFR(value)                (GMAC_IMR_PDRQFR_Msk & (_UINT32_(value) << GMAC_IMR_PDRQFR_Pos)) /* Assigment of value for PDRQFR in the GMAC_IMR register */
#define GMAC_IMR_PDRSFR_Pos                   _UINT32_(23)                                         /* (GMAC_IMR) PDelay Response Frame Received Position */
#define GMAC_IMR_PDRSFR_Msk                   (_UINT32_(0x1) << GMAC_IMR_PDRSFR_Pos)               /* (GMAC_IMR) PDelay Response Frame Received Mask */
#define GMAC_IMR_PDRSFR(value)                (GMAC_IMR_PDRSFR_Msk & (_UINT32_(value) << GMAC_IMR_PDRSFR_Pos)) /* Assigment of value for PDRSFR in the GMAC_IMR register */
#define GMAC_IMR_PDRQFT_Pos                   _UINT32_(24)                                         /* (GMAC_IMR) PDelay Request Frame Transmitted Position */
#define GMAC_IMR_PDRQFT_Msk                   (_UINT32_(0x1) << GMAC_IMR_PDRQFT_Pos)               /* (GMAC_IMR) PDelay Request Frame Transmitted Mask */
#define GMAC_IMR_PDRQFT(value)                (GMAC_IMR_PDRQFT_Msk & (_UINT32_(value) << GMAC_IMR_PDRQFT_Pos)) /* Assigment of value for PDRQFT in the GMAC_IMR register */
#define GMAC_IMR_PDRSFT_Pos                   _UINT32_(25)                                         /* (GMAC_IMR) PDelay Response Frame Transmitted Position */
#define GMAC_IMR_PDRSFT_Msk                   (_UINT32_(0x1) << GMAC_IMR_PDRSFT_Pos)               /* (GMAC_IMR) PDelay Response Frame Transmitted Mask */
#define GMAC_IMR_PDRSFT(value)                (GMAC_IMR_PDRSFT_Msk & (_UINT32_(value) << GMAC_IMR_PDRSFT_Pos)) /* Assigment of value for PDRSFT in the GMAC_IMR register */
#define GMAC_IMR_SRI_Pos                      _UINT32_(26)                                         /* (GMAC_IMR) TSU Seconds Register Increment Position */
#define GMAC_IMR_SRI_Msk                      (_UINT32_(0x1) << GMAC_IMR_SRI_Pos)                  /* (GMAC_IMR) TSU Seconds Register Increment Mask */
#define GMAC_IMR_SRI(value)                   (GMAC_IMR_SRI_Msk & (_UINT32_(value) << GMAC_IMR_SRI_Pos)) /* Assigment of value for SRI in the GMAC_IMR register */
#define GMAC_IMR_RXLPISBC_Pos                 _UINT32_(27)                                         /* (GMAC_IMR) Enable RX LPI Indication Position */
#define GMAC_IMR_RXLPISBC_Msk                 (_UINT32_(0x1) << GMAC_IMR_RXLPISBC_Pos)             /* (GMAC_IMR) Enable RX LPI Indication Mask */
#define GMAC_IMR_RXLPISBC(value)              (GMAC_IMR_RXLPISBC_Msk & (_UINT32_(value) << GMAC_IMR_RXLPISBC_Pos)) /* Assigment of value for RXLPISBC in the GMAC_IMR register */
#define GMAC_IMR_WOL_Pos                      _UINT32_(28)                                         /* (GMAC_IMR) Wake On LAN Position */
#define GMAC_IMR_WOL_Msk                      (_UINT32_(0x1) << GMAC_IMR_WOL_Pos)                  /* (GMAC_IMR) Wake On LAN Mask */
#define GMAC_IMR_WOL(value)                   (GMAC_IMR_WOL_Msk & (_UINT32_(value) << GMAC_IMR_WOL_Pos)) /* Assigment of value for WOL in the GMAC_IMR register */
#define GMAC_IMR_TSUTIMCOMP_Pos               _UINT32_(29)                                         /* (GMAC_IMR) TSU Timer Comparison Position */
#define GMAC_IMR_TSUTIMCOMP_Msk               (_UINT32_(0x1) << GMAC_IMR_TSUTIMCOMP_Pos)           /* (GMAC_IMR) TSU Timer Comparison Mask */
#define GMAC_IMR_TSUTIMCOMP(value)            (GMAC_IMR_TSUTIMCOMP_Msk & (_UINT32_(value) << GMAC_IMR_TSUTIMCOMP_Pos)) /* Assigment of value for TSUTIMCOMP in the GMAC_IMR register */
#define GMAC_IMR_Msk                          _UINT32_(0x3FFCFCFF)                                 /* (GMAC_IMR) Register Mask  */


/* -------- GMAC_MAN : (GMAC Offset: 0x34) (R/W 32) PHY Maintenance Register -------- */
#define GMAC_MAN_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_MAN) PHY Maintenance Register  Reset Value */

#define GMAC_MAN_DATA_Pos                     _UINT32_(0)                                          /* (GMAC_MAN) PHY Data Position */
#define GMAC_MAN_DATA_Msk                     (_UINT32_(0xFFFF) << GMAC_MAN_DATA_Pos)              /* (GMAC_MAN) PHY Data Mask */
#define GMAC_MAN_DATA(value)                  (GMAC_MAN_DATA_Msk & (_UINT32_(value) << GMAC_MAN_DATA_Pos)) /* Assigment of value for DATA in the GMAC_MAN register */
#define GMAC_MAN_WTN_Pos                      _UINT32_(16)                                         /* (GMAC_MAN) Write Ten Position */
#define GMAC_MAN_WTN_Msk                      (_UINT32_(0x3) << GMAC_MAN_WTN_Pos)                  /* (GMAC_MAN) Write Ten Mask */
#define GMAC_MAN_WTN(value)                   (GMAC_MAN_WTN_Msk & (_UINT32_(value) << GMAC_MAN_WTN_Pos)) /* Assigment of value for WTN in the GMAC_MAN register */
#define GMAC_MAN_REGA_Pos                     _UINT32_(18)                                         /* (GMAC_MAN) Register Address Position */
#define GMAC_MAN_REGA_Msk                     (_UINT32_(0x1F) << GMAC_MAN_REGA_Pos)                /* (GMAC_MAN) Register Address Mask */
#define GMAC_MAN_REGA(value)                  (GMAC_MAN_REGA_Msk & (_UINT32_(value) << GMAC_MAN_REGA_Pos)) /* Assigment of value for REGA in the GMAC_MAN register */
#define GMAC_MAN_PHYA_Pos                     _UINT32_(23)                                         /* (GMAC_MAN) PHY Address Position */
#define GMAC_MAN_PHYA_Msk                     (_UINT32_(0x1F) << GMAC_MAN_PHYA_Pos)                /* (GMAC_MAN) PHY Address Mask */
#define GMAC_MAN_PHYA(value)                  (GMAC_MAN_PHYA_Msk & (_UINT32_(value) << GMAC_MAN_PHYA_Pos)) /* Assigment of value for PHYA in the GMAC_MAN register */
#define GMAC_MAN_OP_Pos                       _UINT32_(28)                                         /* (GMAC_MAN) Operation Position */
#define GMAC_MAN_OP_Msk                       (_UINT32_(0x3) << GMAC_MAN_OP_Pos)                   /* (GMAC_MAN) Operation Mask */
#define GMAC_MAN_OP(value)                    (GMAC_MAN_OP_Msk & (_UINT32_(value) << GMAC_MAN_OP_Pos)) /* Assigment of value for OP in the GMAC_MAN register */
#define   GMAC_MAN_OP_1_Val                   _UINT32_(0x1)                                        /* (GMAC_MAN) Write  */
#define   GMAC_MAN_OP_2_Val                   _UINT32_(0x2)                                        /* (GMAC_MAN) Read  */
#define GMAC_MAN_OP_1                         (GMAC_MAN_OP_1_Val << GMAC_MAN_OP_Pos)               /* (GMAC_MAN) Write Position  */
#define GMAC_MAN_OP_2                         (GMAC_MAN_OP_2_Val << GMAC_MAN_OP_Pos)               /* (GMAC_MAN) Read Position  */
#define GMAC_MAN_CLTTO_Pos                    _UINT32_(30)                                         /* (GMAC_MAN) Clause 22 Operation Position */
#define GMAC_MAN_CLTTO_Msk                    (_UINT32_(0x1) << GMAC_MAN_CLTTO_Pos)                /* (GMAC_MAN) Clause 22 Operation Mask */
#define GMAC_MAN_CLTTO(value)                 (GMAC_MAN_CLTTO_Msk & (_UINT32_(value) << GMAC_MAN_CLTTO_Pos)) /* Assigment of value for CLTTO in the GMAC_MAN register */
#define   GMAC_MAN_CLTTO_0_Val                _UINT32_(0x0)                                        /* (GMAC_MAN) Clause 45 operation  */
#define   GMAC_MAN_CLTTO_1_Val                _UINT32_(0x1)                                        /* (GMAC_MAN) Clause 22 operation  */
#define GMAC_MAN_CLTTO_0                      (GMAC_MAN_CLTTO_0_Val << GMAC_MAN_CLTTO_Pos)         /* (GMAC_MAN) Clause 45 operation Position  */
#define GMAC_MAN_CLTTO_1                      (GMAC_MAN_CLTTO_1_Val << GMAC_MAN_CLTTO_Pos)         /* (GMAC_MAN) Clause 22 operation Position  */
#define GMAC_MAN_WZO_Pos                      _UINT32_(31)                                         /* (GMAC_MAN) Write ZERO Position */
#define GMAC_MAN_WZO_Msk                      (_UINT32_(0x1) << GMAC_MAN_WZO_Pos)                  /* (GMAC_MAN) Write ZERO Mask */
#define GMAC_MAN_WZO(value)                   (GMAC_MAN_WZO_Msk & (_UINT32_(value) << GMAC_MAN_WZO_Pos)) /* Assigment of value for WZO in the GMAC_MAN register */
#define GMAC_MAN_Msk                          _UINT32_(0xFFFFFFFF)                                 /* (GMAC_MAN) Register Mask  */


/* -------- GMAC_RPQ : (GMAC Offset: 0x38) ( R/ 32) Receive Pause Quantum Register -------- */
#define GMAC_RPQ_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_RPQ) Receive Pause Quantum Register  Reset Value */

#define GMAC_RPQ_RPQ_Pos                      _UINT32_(0)                                          /* (GMAC_RPQ) Received Pause Quantum Position */
#define GMAC_RPQ_RPQ_Msk                      (_UINT32_(0xFFFF) << GMAC_RPQ_RPQ_Pos)               /* (GMAC_RPQ) Received Pause Quantum Mask */
#define GMAC_RPQ_RPQ(value)                   (GMAC_RPQ_RPQ_Msk & (_UINT32_(value) << GMAC_RPQ_RPQ_Pos)) /* Assigment of value for RPQ in the GMAC_RPQ register */
#define GMAC_RPQ_Msk                          _UINT32_(0x0000FFFF)                                 /* (GMAC_RPQ) Register Mask  */


/* -------- GMAC_TPQ : (GMAC Offset: 0x3C) (R/W 32) Transmit Pause Quantum Register -------- */
#define GMAC_TPQ_RESETVALUE                   _UINT32_(0xFFFFFFFF)                                 /*  (GMAC_TPQ) Transmit Pause Quantum Register  Reset Value */

#define GMAC_TPQ_TPQ_Pos                      _UINT32_(0)                                          /* (GMAC_TPQ) Transmit Pause Quantum Position */
#define GMAC_TPQ_TPQ_Msk                      (_UINT32_(0xFFFF) << GMAC_TPQ_TPQ_Pos)               /* (GMAC_TPQ) Transmit Pause Quantum Mask */
#define GMAC_TPQ_TPQ(value)                   (GMAC_TPQ_TPQ_Msk & (_UINT32_(value) << GMAC_TPQ_TPQ_Pos)) /* Assigment of value for TPQ in the GMAC_TPQ register */
#define GMAC_TPQ_P1TPQ_Pos                    _UINT32_(16)                                         /* (GMAC_TPQ) Priority 1 Transmit Pause Quantum Position */
#define GMAC_TPQ_P1TPQ_Msk                    (_UINT32_(0xFFFF) << GMAC_TPQ_P1TPQ_Pos)             /* (GMAC_TPQ) Priority 1 Transmit Pause Quantum Mask */
#define GMAC_TPQ_P1TPQ(value)                 (GMAC_TPQ_P1TPQ_Msk & (_UINT32_(value) << GMAC_TPQ_P1TPQ_Pos)) /* Assigment of value for P1TPQ in the GMAC_TPQ register */
#define GMAC_TPQ_Msk                          _UINT32_(0xFFFFFFFF)                                 /* (GMAC_TPQ) Register Mask  */


/* -------- GMAC_RJFML : (GMAC Offset: 0x48) (R/W 32) RX Jumbo Frame Max Length Register -------- */
#define GMAC_RJFML_RESETVALUE                 _UINT32_(0x3FFF)                                     /*  (GMAC_RJFML) RX Jumbo Frame Max Length Register  Reset Value */

#define GMAC_RJFML_FML_Pos                    _UINT32_(0)                                          /* (GMAC_RJFML) Frame Max Length Position */
#define GMAC_RJFML_FML_Msk                    (_UINT32_(0x3FFF) << GMAC_RJFML_FML_Pos)             /* (GMAC_RJFML) Frame Max Length Mask */
#define GMAC_RJFML_FML(value)                 (GMAC_RJFML_FML_Msk & (_UINT32_(value) << GMAC_RJFML_FML_Pos)) /* Assigment of value for FML in the GMAC_RJFML register */
#define GMAC_RJFML_Msk                        _UINT32_(0x00003FFF)                                 /* (GMAC_RJFML) Register Mask  */


/* -------- GMAC_INTM : (GMAC Offset: 0x5C) (R/W 32) Interrupt Moderation Register -------- */
#define GMAC_INTM_RESETVALUE                  _UINT32_(0x00)                                       /*  (GMAC_INTM) Interrupt Moderation Register  Reset Value */

#define GMAC_INTM_RXINTMOD_Pos                _UINT32_(0)                                          /* (GMAC_INTM) Receive Interrupt Moderation Position */
#define GMAC_INTM_RXINTMOD_Msk                (_UINT32_(0xFF) << GMAC_INTM_RXINTMOD_Pos)           /* (GMAC_INTM) Receive Interrupt Moderation Mask */
#define GMAC_INTM_RXINTMOD(value)             (GMAC_INTM_RXINTMOD_Msk & (_UINT32_(value) << GMAC_INTM_RXINTMOD_Pos)) /* Assigment of value for RXINTMOD in the GMAC_INTM register */
#define GMAC_INTM_TXINTMOD_Pos                _UINT32_(16)                                         /* (GMAC_INTM) Transmit Interrupt Moderation Position */
#define GMAC_INTM_TXINTMOD_Msk                (_UINT32_(0xFF) << GMAC_INTM_TXINTMOD_Pos)           /* (GMAC_INTM) Transmit Interrupt Moderation Mask */
#define GMAC_INTM_TXINTMOD(value)             (GMAC_INTM_TXINTMOD_Msk & (_UINT32_(value) << GMAC_INTM_TXINTMOD_Pos)) /* Assigment of value for TXINTMOD in the GMAC_INTM register */
#define GMAC_INTM_Msk                         _UINT32_(0x00FF00FF)                                 /* (GMAC_INTM) Register Mask  */


/* -------- GMAC_SYSWT : (GMAC Offset: 0x60) (R/W 32) System Wake-Up Time Register -------- */
#define GMAC_SYSWT_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_SYSWT) System Wake-Up Time Register  Reset Value */

#define GMAC_SYSWT_SYSWKUPTIME_Pos            _UINT32_(0)                                          /* (GMAC_SYSWT) System Wake-up Time Position */
#define GMAC_SYSWT_SYSWKUPTIME_Msk            (_UINT32_(0xFFFF) << GMAC_SYSWT_SYSWKUPTIME_Pos)     /* (GMAC_SYSWT) System Wake-up Time Mask */
#define GMAC_SYSWT_SYSWKUPTIME(value)         (GMAC_SYSWT_SYSWKUPTIME_Msk & (_UINT32_(value) << GMAC_SYSWT_SYSWKUPTIME_Pos)) /* Assigment of value for SYSWKUPTIME in the GMAC_SYSWT register */
#define GMAC_SYSWT_Msk                        _UINT32_(0x0000FFFF)                                 /* (GMAC_SYSWT) Register Mask  */


/* -------- GMAC_HRB : (GMAC Offset: 0x80) (R/W 32) Hash Register Bottom -------- */
#define GMAC_HRB_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_HRB) Hash Register Bottom  Reset Value */

#define GMAC_HRB_ADDR_Pos                     _UINT32_(0)                                          /* (GMAC_HRB) Hash Address Position */
#define GMAC_HRB_ADDR_Msk                     (_UINT32_(0xFFFFFFFF) << GMAC_HRB_ADDR_Pos)          /* (GMAC_HRB) Hash Address Mask */
#define GMAC_HRB_ADDR(value)                  (GMAC_HRB_ADDR_Msk & (_UINT32_(value) << GMAC_HRB_ADDR_Pos)) /* Assigment of value for ADDR in the GMAC_HRB register */
#define GMAC_HRB_Msk                          _UINT32_(0xFFFFFFFF)                                 /* (GMAC_HRB) Register Mask  */


/* -------- GMAC_HRT : (GMAC Offset: 0x84) (R/W 32) Hash Register Top -------- */
#define GMAC_HRT_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_HRT) Hash Register Top  Reset Value */

#define GMAC_HRT_ADDR_Pos                     _UINT32_(0)                                          /* (GMAC_HRT) Hash Address Position */
#define GMAC_HRT_ADDR_Msk                     (_UINT32_(0xFFFFFFFF) << GMAC_HRT_ADDR_Pos)          /* (GMAC_HRT) Hash Address Mask */
#define GMAC_HRT_ADDR(value)                  (GMAC_HRT_ADDR_Msk & (_UINT32_(value) << GMAC_HRT_ADDR_Pos)) /* Assigment of value for ADDR in the GMAC_HRT register */
#define GMAC_HRT_Msk                          _UINT32_(0xFFFFFFFF)                                 /* (GMAC_HRT) Register Mask  */


/* -------- GMAC_TIDM1 : (GMAC Offset: 0xA8) (R/W 32) Type ID Match 1 Register -------- */
#define GMAC_TIDM1_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_TIDM1) Type ID Match 1 Register  Reset Value */

#define GMAC_TIDM1_TID_Pos                    _UINT32_(0)                                          /* (GMAC_TIDM1) Type ID Match 1 Position */
#define GMAC_TIDM1_TID_Msk                    (_UINT32_(0xFFFF) << GMAC_TIDM1_TID_Pos)             /* (GMAC_TIDM1) Type ID Match 1 Mask */
#define GMAC_TIDM1_TID(value)                 (GMAC_TIDM1_TID_Msk & (_UINT32_(value) << GMAC_TIDM1_TID_Pos)) /* Assigment of value for TID in the GMAC_TIDM1 register */
#define GMAC_TIDM1_ENID1_Pos                  _UINT32_(31)                                         /* (GMAC_TIDM1) Enable Copying of TID Matched Frames Position */
#define GMAC_TIDM1_ENID1_Msk                  (_UINT32_(0x1) << GMAC_TIDM1_ENID1_Pos)              /* (GMAC_TIDM1) Enable Copying of TID Matched Frames Mask */
#define GMAC_TIDM1_ENID1(value)               (GMAC_TIDM1_ENID1_Msk & (_UINT32_(value) << GMAC_TIDM1_ENID1_Pos)) /* Assigment of value for ENID1 in the GMAC_TIDM1 register */
#define   GMAC_TIDM1_ENID1_0_Val              _UINT32_(0x0)                                        /* (GMAC_TIDM1) TID is not part of the comparison match.  */
#define   GMAC_TIDM1_ENID1_1_Val              _UINT32_(0x1)                                        /* (GMAC_TIDM1) TID is processed for the comparison match.  */
#define GMAC_TIDM1_ENID1_0                    (GMAC_TIDM1_ENID1_0_Val << GMAC_TIDM1_ENID1_Pos)     /* (GMAC_TIDM1) TID is not part of the comparison match. Position  */
#define GMAC_TIDM1_ENID1_1                    (GMAC_TIDM1_ENID1_1_Val << GMAC_TIDM1_ENID1_Pos)     /* (GMAC_TIDM1) TID is processed for the comparison match. Position  */
#define GMAC_TIDM1_Msk                        _UINT32_(0x8000FFFF)                                 /* (GMAC_TIDM1) Register Mask  */

#define GMAC_TIDM1_ENID_Pos                   _UINT32_(31)                                         /* (GMAC_TIDM1 Position) Enable Copying of TID Matched Frames */
#define GMAC_TIDM1_ENID_Msk                   (_UINT32_(0x1) << GMAC_TIDM1_ENID_Pos)               /* (GMAC_TIDM1 Mask) ENID */
#define GMAC_TIDM1_ENID(value)                (GMAC_TIDM1_ENID_Msk & (_UINT32_(value) << GMAC_TIDM1_ENID_Pos)) 

/* -------- GMAC_TIDM2 : (GMAC Offset: 0xAC) (R/W 32) Type ID Match 2 Register -------- */
#define GMAC_TIDM2_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_TIDM2) Type ID Match 2 Register  Reset Value */

#define GMAC_TIDM2_TID_Pos                    _UINT32_(0)                                          /* (GMAC_TIDM2) Type ID Match 2 Position */
#define GMAC_TIDM2_TID_Msk                    (_UINT32_(0xFFFF) << GMAC_TIDM2_TID_Pos)             /* (GMAC_TIDM2) Type ID Match 2 Mask */
#define GMAC_TIDM2_TID(value)                 (GMAC_TIDM2_TID_Msk & (_UINT32_(value) << GMAC_TIDM2_TID_Pos)) /* Assigment of value for TID in the GMAC_TIDM2 register */
#define GMAC_TIDM2_ENID2_Pos                  _UINT32_(31)                                         /* (GMAC_TIDM2) Enable Copying of TID Matched Frames Position */
#define GMAC_TIDM2_ENID2_Msk                  (_UINT32_(0x1) << GMAC_TIDM2_ENID2_Pos)              /* (GMAC_TIDM2) Enable Copying of TID Matched Frames Mask */
#define GMAC_TIDM2_ENID2(value)               (GMAC_TIDM2_ENID2_Msk & (_UINT32_(value) << GMAC_TIDM2_ENID2_Pos)) /* Assigment of value for ENID2 in the GMAC_TIDM2 register */
#define   GMAC_TIDM2_ENID2_0_Val              _UINT32_(0x0)                                        /* (GMAC_TIDM2) TID is not part of the comparison match.  */
#define   GMAC_TIDM2_ENID2_1_Val              _UINT32_(0x1)                                        /* (GMAC_TIDM2) TID is processed for the comparison match.  */
#define GMAC_TIDM2_ENID2_0                    (GMAC_TIDM2_ENID2_0_Val << GMAC_TIDM2_ENID2_Pos)     /* (GMAC_TIDM2) TID is not part of the comparison match. Position  */
#define GMAC_TIDM2_ENID2_1                    (GMAC_TIDM2_ENID2_1_Val << GMAC_TIDM2_ENID2_Pos)     /* (GMAC_TIDM2) TID is processed for the comparison match. Position  */
#define GMAC_TIDM2_Msk                        _UINT32_(0x8000FFFF)                                 /* (GMAC_TIDM2) Register Mask  */

#define GMAC_TIDM2_ENID_Pos                   _UINT32_(31)                                         /* (GMAC_TIDM2 Position) Enable Copying of TID Matched Frames */
#define GMAC_TIDM2_ENID_Msk                   (_UINT32_(0x1) << GMAC_TIDM2_ENID_Pos)               /* (GMAC_TIDM2 Mask) ENID */
#define GMAC_TIDM2_ENID(value)                (GMAC_TIDM2_ENID_Msk & (_UINT32_(value) << GMAC_TIDM2_ENID_Pos)) 

/* -------- GMAC_TIDM3 : (GMAC Offset: 0xB0) (R/W 32) Type ID Match 3 Register -------- */
#define GMAC_TIDM3_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_TIDM3) Type ID Match 3 Register  Reset Value */

#define GMAC_TIDM3_TID_Pos                    _UINT32_(0)                                          /* (GMAC_TIDM3) Type ID Match 3 Position */
#define GMAC_TIDM3_TID_Msk                    (_UINT32_(0xFFFF) << GMAC_TIDM3_TID_Pos)             /* (GMAC_TIDM3) Type ID Match 3 Mask */
#define GMAC_TIDM3_TID(value)                 (GMAC_TIDM3_TID_Msk & (_UINT32_(value) << GMAC_TIDM3_TID_Pos)) /* Assigment of value for TID in the GMAC_TIDM3 register */
#define GMAC_TIDM3_ENID3_Pos                  _UINT32_(31)                                         /* (GMAC_TIDM3) Enable Copying of TID Matched Frames Position */
#define GMAC_TIDM3_ENID3_Msk                  (_UINT32_(0x1) << GMAC_TIDM3_ENID3_Pos)              /* (GMAC_TIDM3) Enable Copying of TID Matched Frames Mask */
#define GMAC_TIDM3_ENID3(value)               (GMAC_TIDM3_ENID3_Msk & (_UINT32_(value) << GMAC_TIDM3_ENID3_Pos)) /* Assigment of value for ENID3 in the GMAC_TIDM3 register */
#define   GMAC_TIDM3_ENID3_0_Val              _UINT32_(0x0)                                        /* (GMAC_TIDM3) TID is not part of the comparison match.  */
#define   GMAC_TIDM3_ENID3_1_Val              _UINT32_(0x1)                                        /* (GMAC_TIDM3) TID is processed for the comparison match.  */
#define GMAC_TIDM3_ENID3_0                    (GMAC_TIDM3_ENID3_0_Val << GMAC_TIDM3_ENID3_Pos)     /* (GMAC_TIDM3) TID is not part of the comparison match. Position  */
#define GMAC_TIDM3_ENID3_1                    (GMAC_TIDM3_ENID3_1_Val << GMAC_TIDM3_ENID3_Pos)     /* (GMAC_TIDM3) TID is processed for the comparison match. Position  */
#define GMAC_TIDM3_Msk                        _UINT32_(0x8000FFFF)                                 /* (GMAC_TIDM3) Register Mask  */

#define GMAC_TIDM3_ENID_Pos                   _UINT32_(31)                                         /* (GMAC_TIDM3 Position) Enable Copying of TID Matched Frames */
#define GMAC_TIDM3_ENID_Msk                   (_UINT32_(0x1) << GMAC_TIDM3_ENID_Pos)               /* (GMAC_TIDM3 Mask) ENID */
#define GMAC_TIDM3_ENID(value)                (GMAC_TIDM3_ENID_Msk & (_UINT32_(value) << GMAC_TIDM3_ENID_Pos)) 

/* -------- GMAC_TIDM4 : (GMAC Offset: 0xB4) (R/W 32) Type ID Match 4 Register -------- */
#define GMAC_TIDM4_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_TIDM4) Type ID Match 4 Register  Reset Value */

#define GMAC_TIDM4_TID_Pos                    _UINT32_(0)                                          /* (GMAC_TIDM4) Type ID Match 4 Position */
#define GMAC_TIDM4_TID_Msk                    (_UINT32_(0xFFFF) << GMAC_TIDM4_TID_Pos)             /* (GMAC_TIDM4) Type ID Match 4 Mask */
#define GMAC_TIDM4_TID(value)                 (GMAC_TIDM4_TID_Msk & (_UINT32_(value) << GMAC_TIDM4_TID_Pos)) /* Assigment of value for TID in the GMAC_TIDM4 register */
#define GMAC_TIDM4_ENID4_Pos                  _UINT32_(31)                                         /* (GMAC_TIDM4) Enable Copying of TID Matched Frames Position */
#define GMAC_TIDM4_ENID4_Msk                  (_UINT32_(0x1) << GMAC_TIDM4_ENID4_Pos)              /* (GMAC_TIDM4) Enable Copying of TID Matched Frames Mask */
#define GMAC_TIDM4_ENID4(value)               (GMAC_TIDM4_ENID4_Msk & (_UINT32_(value) << GMAC_TIDM4_ENID4_Pos)) /* Assigment of value for ENID4 in the GMAC_TIDM4 register */
#define   GMAC_TIDM4_ENID4_0_Val              _UINT32_(0x0)                                        /* (GMAC_TIDM4) TID is not part of the comparison match.  */
#define   GMAC_TIDM4_ENID4_1_Val              _UINT32_(0x1)                                        /* (GMAC_TIDM4) TID is processed for the comparison match.  */
#define GMAC_TIDM4_ENID4_0                    (GMAC_TIDM4_ENID4_0_Val << GMAC_TIDM4_ENID4_Pos)     /* (GMAC_TIDM4) TID is not part of the comparison match. Position  */
#define GMAC_TIDM4_ENID4_1                    (GMAC_TIDM4_ENID4_1_Val << GMAC_TIDM4_ENID4_Pos)     /* (GMAC_TIDM4) TID is processed for the comparison match. Position  */
#define GMAC_TIDM4_Msk                        _UINT32_(0x8000FFFF)                                 /* (GMAC_TIDM4) Register Mask  */

#define GMAC_TIDM4_ENID_Pos                   _UINT32_(31)                                         /* (GMAC_TIDM4 Position) Enable Copying of TID Matched Frames */
#define GMAC_TIDM4_ENID_Msk                   (_UINT32_(0x1) << GMAC_TIDM4_ENID_Pos)               /* (GMAC_TIDM4 Mask) ENID */
#define GMAC_TIDM4_ENID(value)                (GMAC_TIDM4_ENID_Msk & (_UINT32_(value) << GMAC_TIDM4_ENID_Pos)) 

/* -------- GMAC_WOL : (GMAC Offset: 0xB8) (R/W 32) Wake on LAN Register -------- */
#define GMAC_WOL_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_WOL) Wake on LAN Register  Reset Value */

#define GMAC_WOL_IP_Pos                       _UINT32_(0)                                          /* (GMAC_WOL) ARP Request IP Address Position */
#define GMAC_WOL_IP_Msk                       (_UINT32_(0xFFFF) << GMAC_WOL_IP_Pos)                /* (GMAC_WOL) ARP Request IP Address Mask */
#define GMAC_WOL_IP(value)                    (GMAC_WOL_IP_Msk & (_UINT32_(value) << GMAC_WOL_IP_Pos)) /* Assigment of value for IP in the GMAC_WOL register */
#define GMAC_WOL_MAG_Pos                      _UINT32_(16)                                         /* (GMAC_WOL) Magic Packet Event Enable Position */
#define GMAC_WOL_MAG_Msk                      (_UINT32_(0x1) << GMAC_WOL_MAG_Pos)                  /* (GMAC_WOL) Magic Packet Event Enable Mask */
#define GMAC_WOL_MAG(value)                   (GMAC_WOL_MAG_Msk & (_UINT32_(value) << GMAC_WOL_MAG_Pos)) /* Assigment of value for MAG in the GMAC_WOL register */
#define GMAC_WOL_ARP_Pos                      _UINT32_(17)                                         /* (GMAC_WOL) ARP Request Event Enable Position */
#define GMAC_WOL_ARP_Msk                      (_UINT32_(0x1) << GMAC_WOL_ARP_Pos)                  /* (GMAC_WOL) ARP Request Event Enable Mask */
#define GMAC_WOL_ARP(value)                   (GMAC_WOL_ARP_Msk & (_UINT32_(value) << GMAC_WOL_ARP_Pos)) /* Assigment of value for ARP in the GMAC_WOL register */
#define GMAC_WOL_SA1_Pos                      _UINT32_(18)                                         /* (GMAC_WOL) Specific Address Register 1 Event Enable Position */
#define GMAC_WOL_SA1_Msk                      (_UINT32_(0x1) << GMAC_WOL_SA1_Pos)                  /* (GMAC_WOL) Specific Address Register 1 Event Enable Mask */
#define GMAC_WOL_SA1(value)                   (GMAC_WOL_SA1_Msk & (_UINT32_(value) << GMAC_WOL_SA1_Pos)) /* Assigment of value for SA1 in the GMAC_WOL register */
#define GMAC_WOL_MTI_Pos                      _UINT32_(19)                                         /* (GMAC_WOL) Multicast Hash Event Enable Position */
#define GMAC_WOL_MTI_Msk                      (_UINT32_(0x1) << GMAC_WOL_MTI_Pos)                  /* (GMAC_WOL) Multicast Hash Event Enable Mask */
#define GMAC_WOL_MTI(value)                   (GMAC_WOL_MTI_Msk & (_UINT32_(value) << GMAC_WOL_MTI_Pos)) /* Assigment of value for MTI in the GMAC_WOL register */
#define GMAC_WOL_Msk                          _UINT32_(0x000FFFFF)                                 /* (GMAC_WOL) Register Mask  */

#define GMAC_WOL_SA_Pos                       _UINT32_(18)                                         /* (GMAC_WOL Position) Specific Address Register x Event Enable */
#define GMAC_WOL_SA_Msk                       (_UINT32_(0x1) << GMAC_WOL_SA_Pos)                   /* (GMAC_WOL Mask) SA */
#define GMAC_WOL_SA(value)                    (GMAC_WOL_SA_Msk & (_UINT32_(value) << GMAC_WOL_SA_Pos)) 

/* -------- GMAC_IPGS : (GMAC Offset: 0xBC) (R/W 32) IPG Stretch Register -------- */
#define GMAC_IPGS_RESETVALUE                  _UINT32_(0x00)                                       /*  (GMAC_IPGS) IPG Stretch Register  Reset Value */

#define GMAC_IPGS_FL_Pos                      _UINT32_(0)                                          /* (GMAC_IPGS) Frame Length Position */
#define GMAC_IPGS_FL_Msk                      (_UINT32_(0xFFFF) << GMAC_IPGS_FL_Pos)               /* (GMAC_IPGS) Frame Length Mask */
#define GMAC_IPGS_FL(value)                   (GMAC_IPGS_FL_Msk & (_UINT32_(value) << GMAC_IPGS_FL_Pos)) /* Assigment of value for FL in the GMAC_IPGS register */
#define GMAC_IPGS_Msk                         _UINT32_(0x0000FFFF)                                 /* (GMAC_IPGS) Register Mask  */


/* -------- GMAC_SVLAN : (GMAC Offset: 0xC0) (R/W 32) Stacked VLAN Register -------- */
#define GMAC_SVLAN_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_SVLAN) Stacked VLAN Register  Reset Value */

#define GMAC_SVLAN_VLAN_TYPE_Pos              _UINT32_(0)                                          /* (GMAC_SVLAN) User Defined VLAN_TYPE Field Position */
#define GMAC_SVLAN_VLAN_TYPE_Msk              (_UINT32_(0xFFFF) << GMAC_SVLAN_VLAN_TYPE_Pos)       /* (GMAC_SVLAN) User Defined VLAN_TYPE Field Mask */
#define GMAC_SVLAN_VLAN_TYPE(value)           (GMAC_SVLAN_VLAN_TYPE_Msk & (_UINT32_(value) << GMAC_SVLAN_VLAN_TYPE_Pos)) /* Assigment of value for VLAN_TYPE in the GMAC_SVLAN register */
#define GMAC_SVLAN_ESVLAN_Pos                 _UINT32_(31)                                         /* (GMAC_SVLAN) Enable Stacked VLAN Processing Mode Position */
#define GMAC_SVLAN_ESVLAN_Msk                 (_UINT32_(0x1) << GMAC_SVLAN_ESVLAN_Pos)             /* (GMAC_SVLAN) Enable Stacked VLAN Processing Mode Mask */
#define GMAC_SVLAN_ESVLAN(value)              (GMAC_SVLAN_ESVLAN_Msk & (_UINT32_(value) << GMAC_SVLAN_ESVLAN_Pos)) /* Assigment of value for ESVLAN in the GMAC_SVLAN register */
#define   GMAC_SVLAN_ESVLAN_0_Val             _UINT32_(0x0)                                        /* (GMAC_SVLAN) Disable the stacked VLAN Processing mode  */
#define   GMAC_SVLAN_ESVLAN_1_Val             _UINT32_(0x1)                                        /* (GMAC_SVLAN) Enable the stacked VLAN Processing mode  */
#define GMAC_SVLAN_ESVLAN_0                   (GMAC_SVLAN_ESVLAN_0_Val << GMAC_SVLAN_ESVLAN_Pos)   /* (GMAC_SVLAN) Disable the stacked VLAN Processing mode Position  */
#define GMAC_SVLAN_ESVLAN_1                   (GMAC_SVLAN_ESVLAN_1_Val << GMAC_SVLAN_ESVLAN_Pos)   /* (GMAC_SVLAN) Enable the stacked VLAN Processing mode Position  */
#define GMAC_SVLAN_Msk                        _UINT32_(0x8000FFFF)                                 /* (GMAC_SVLAN) Register Mask  */


/* -------- GMAC_TPFCP : (GMAC Offset: 0xC4) (R/W 32) Transmit PFC Pause Register -------- */
#define GMAC_TPFCP_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_TPFCP) Transmit PFC Pause Register  Reset Value */

#define GMAC_TPFCP_PEV_Pos                    _UINT32_(0)                                          /* (GMAC_TPFCP) Priority Enable Vector Position */
#define GMAC_TPFCP_PEV_Msk                    (_UINT32_(0xFF) << GMAC_TPFCP_PEV_Pos)               /* (GMAC_TPFCP) Priority Enable Vector Mask */
#define GMAC_TPFCP_PEV(value)                 (GMAC_TPFCP_PEV_Msk & (_UINT32_(value) << GMAC_TPFCP_PEV_Pos)) /* Assigment of value for PEV in the GMAC_TPFCP register */
#define GMAC_TPFCP_PQ_Pos                     _UINT32_(8)                                          /* (GMAC_TPFCP) Pause Quantum Position */
#define GMAC_TPFCP_PQ_Msk                     (_UINT32_(0xFF) << GMAC_TPFCP_PQ_Pos)                /* (GMAC_TPFCP) Pause Quantum Mask */
#define GMAC_TPFCP_PQ(value)                  (GMAC_TPFCP_PQ_Msk & (_UINT32_(value) << GMAC_TPFCP_PQ_Pos)) /* Assigment of value for PQ in the GMAC_TPFCP register */
#define GMAC_TPFCP_Msk                        _UINT32_(0x0000FFFF)                                 /* (GMAC_TPFCP) Register Mask  */


/* -------- GMAC_SAMB1 : (GMAC Offset: 0xC8) (R/W 32) Specific Address 1 Mask Bottom Register -------- */
#define GMAC_SAMB1_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_SAMB1) Specific Address 1 Mask Bottom Register  Reset Value */

#define GMAC_SAMB1_ADDR_Pos                   _UINT32_(0)                                          /* (GMAC_SAMB1) Specific Address 1 Mask Position */
#define GMAC_SAMB1_ADDR_Msk                   (_UINT32_(0xFFFFFFFF) << GMAC_SAMB1_ADDR_Pos)        /* (GMAC_SAMB1) Specific Address 1 Mask Mask */
#define GMAC_SAMB1_ADDR(value)                (GMAC_SAMB1_ADDR_Msk & (_UINT32_(value) << GMAC_SAMB1_ADDR_Pos)) /* Assigment of value for ADDR in the GMAC_SAMB1 register */
#define GMAC_SAMB1_Msk                        _UINT32_(0xFFFFFFFF)                                 /* (GMAC_SAMB1) Register Mask  */


/* -------- GMAC_SAMT1 : (GMAC Offset: 0xCC) (R/W 32) Specific Address 1 Mask Top Register -------- */
#define GMAC_SAMT1_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_SAMT1) Specific Address 1 Mask Top Register  Reset Value */

#define GMAC_SAMT1_ADDR_Pos                   _UINT32_(0)                                          /* (GMAC_SAMT1) Specific Address 1 Mask Position */
#define GMAC_SAMT1_ADDR_Msk                   (_UINT32_(0xFFFF) << GMAC_SAMT1_ADDR_Pos)            /* (GMAC_SAMT1) Specific Address 1 Mask Mask */
#define GMAC_SAMT1_ADDR(value)                (GMAC_SAMT1_ADDR_Msk & (_UINT32_(value) << GMAC_SAMT1_ADDR_Pos)) /* Assigment of value for ADDR in the GMAC_SAMT1 register */
#define GMAC_SAMT1_Msk                        _UINT32_(0x0000FFFF)                                 /* (GMAC_SAMT1) Register Mask  */


/* -------- GMAC_AMRX : (GMAC Offset: 0xD0) (R/W 32) System Memory Address Mask for RX Data Buffer Accesses Register -------- */
#define GMAC_AMRX_RESETVALUE                  _UINT32_(0x00)                                       /*  (GMAC_AMRX) System Memory Address Mask for RX Data Buffer Accesses Register  Reset Value */

#define GMAC_AMRX_MSBADDRMSK_Pos              _UINT32_(0)                                          /* (GMAC_AMRX) Mask of the Receive Data Buffer Address Position */
#define GMAC_AMRX_MSBADDRMSK_Msk              (_UINT32_(0xF) << GMAC_AMRX_MSBADDRMSK_Pos)          /* (GMAC_AMRX) Mask of the Receive Data Buffer Address Mask */
#define GMAC_AMRX_MSBADDRMSK(value)           (GMAC_AMRX_MSBADDRMSK_Msk & (_UINT32_(value) << GMAC_AMRX_MSBADDRMSK_Pos)) /* Assigment of value for MSBADDRMSK in the GMAC_AMRX register */
#define GMAC_AMRX_MSBADDR_Pos                 _UINT32_(28)                                         /* (GMAC_AMRX) MSB of the Receive Data Buffer Address Position */
#define GMAC_AMRX_MSBADDR_Msk                 (_UINT32_(0xF) << GMAC_AMRX_MSBADDR_Pos)             /* (GMAC_AMRX) MSB of the Receive Data Buffer Address Mask */
#define GMAC_AMRX_MSBADDR(value)              (GMAC_AMRX_MSBADDR_Msk & (_UINT32_(value) << GMAC_AMRX_MSBADDR_Pos)) /* Assigment of value for MSBADDR in the GMAC_AMRX register */
#define GMAC_AMRX_Msk                         _UINT32_(0xF000000F)                                 /* (GMAC_AMRX) Register Mask  */


/* -------- GMAC_RXUDAR : (GMAC Offset: 0xD4) (R/W 32) PTP RX Unicast IP Destination Address Register -------- */
#define GMAC_RXUDAR_RESETVALUE                _UINT32_(0x00)                                       /*  (GMAC_RXUDAR) PTP RX Unicast IP Destination Address Register  Reset Value */

#define GMAC_RXUDAR_RXUDA_Pos                 _UINT32_(0)                                          /* (GMAC_RXUDAR) Receive Unicast Destination Address Position */
#define GMAC_RXUDAR_RXUDA_Msk                 (_UINT32_(0xFFFFFFFF) << GMAC_RXUDAR_RXUDA_Pos)      /* (GMAC_RXUDAR) Receive Unicast Destination Address Mask */
#define GMAC_RXUDAR_RXUDA(value)              (GMAC_RXUDAR_RXUDA_Msk & (_UINT32_(value) << GMAC_RXUDAR_RXUDA_Pos)) /* Assigment of value for RXUDA in the GMAC_RXUDAR register */
#define GMAC_RXUDAR_Msk                       _UINT32_(0xFFFFFFFF)                                 /* (GMAC_RXUDAR) Register Mask  */


/* -------- GMAC_TXUDAR : (GMAC Offset: 0xD8) (R/W 32) PTP TX Unicast IP Destination Address Register -------- */
#define GMAC_TXUDAR_RESETVALUE                _UINT32_(0x00)                                       /*  (GMAC_TXUDAR) PTP TX Unicast IP Destination Address Register  Reset Value */

#define GMAC_TXUDAR_TXUDA_Pos                 _UINT32_(0)                                          /* (GMAC_TXUDAR) Transmit Unicast Destination Address Position */
#define GMAC_TXUDAR_TXUDA_Msk                 (_UINT32_(0xFFFFFFFF) << GMAC_TXUDAR_TXUDA_Pos)      /* (GMAC_TXUDAR) Transmit Unicast Destination Address Mask */
#define GMAC_TXUDAR_TXUDA(value)              (GMAC_TXUDAR_TXUDA_Msk & (_UINT32_(value) << GMAC_TXUDAR_TXUDA_Pos)) /* Assigment of value for TXUDA in the GMAC_TXUDAR register */
#define GMAC_TXUDAR_Msk                       _UINT32_(0xFFFFFFFF)                                 /* (GMAC_TXUDAR) Register Mask  */


/* -------- GMAC_NSC : (GMAC Offset: 0xDC) (R/W 32) 1588 Timer Nanosecond Comparison Register -------- */
#define GMAC_NSC_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_NSC) 1588 Timer Nanosecond Comparison Register  Reset Value */

#define GMAC_NSC_NANOSEC_Pos                  _UINT32_(0)                                          /* (GMAC_NSC) 1588 Timer Nanosecond Comparison Value Position */
#define GMAC_NSC_NANOSEC_Msk                  (_UINT32_(0x3FFFFF) << GMAC_NSC_NANOSEC_Pos)         /* (GMAC_NSC) 1588 Timer Nanosecond Comparison Value Mask */
#define GMAC_NSC_NANOSEC(value)               (GMAC_NSC_NANOSEC_Msk & (_UINT32_(value) << GMAC_NSC_NANOSEC_Pos)) /* Assigment of value for NANOSEC in the GMAC_NSC register */
#define GMAC_NSC_Msk                          _UINT32_(0x003FFFFF)                                 /* (GMAC_NSC) Register Mask  */


/* -------- GMAC_SCL : (GMAC Offset: 0xE0) (R/W 32) 1588 Timer Second Comparison Low Register -------- */
#define GMAC_SCL_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_SCL) 1588 Timer Second Comparison Low Register  Reset Value */

#define GMAC_SCL_SEC_Pos                      _UINT32_(0)                                          /* (GMAC_SCL) 1588 Timer Second Comparison Value Position */
#define GMAC_SCL_SEC_Msk                      (_UINT32_(0xFFFFFFFF) << GMAC_SCL_SEC_Pos)           /* (GMAC_SCL) 1588 Timer Second Comparison Value Mask */
#define GMAC_SCL_SEC(value)                   (GMAC_SCL_SEC_Msk & (_UINT32_(value) << GMAC_SCL_SEC_Pos)) /* Assigment of value for SEC in the GMAC_SCL register */
#define GMAC_SCL_Msk                          _UINT32_(0xFFFFFFFF)                                 /* (GMAC_SCL) Register Mask  */


/* -------- GMAC_SCH : (GMAC Offset: 0xE4) (R/W 32) 1588 Timer Second Comparison High Register -------- */
#define GMAC_SCH_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_SCH) 1588 Timer Second Comparison High Register  Reset Value */

#define GMAC_SCH_SEC_Pos                      _UINT32_(0)                                          /* (GMAC_SCH) 1588 Timer Second Comparison Value Position */
#define GMAC_SCH_SEC_Msk                      (_UINT32_(0xFFFF) << GMAC_SCH_SEC_Pos)               /* (GMAC_SCH) 1588 Timer Second Comparison Value Mask */
#define GMAC_SCH_SEC(value)                   (GMAC_SCH_SEC_Msk & (_UINT32_(value) << GMAC_SCH_SEC_Pos)) /* Assigment of value for SEC in the GMAC_SCH register */
#define GMAC_SCH_Msk                          _UINT32_(0x0000FFFF)                                 /* (GMAC_SCH) Register Mask  */


/* -------- GMAC_EFTSH : (GMAC Offset: 0xE8) ( R/ 32) PTP Event Frame Transmitted Seconds High Register -------- */
#define GMAC_EFTSH_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_EFTSH) PTP Event Frame Transmitted Seconds High Register  Reset Value */

#define GMAC_EFTSH_RUD_Pos                    _UINT32_(0)                                          /* (GMAC_EFTSH) Register Update Position */
#define GMAC_EFTSH_RUD_Msk                    (_UINT32_(0xFFFF) << GMAC_EFTSH_RUD_Pos)             /* (GMAC_EFTSH) Register Update Mask */
#define GMAC_EFTSH_RUD(value)                 (GMAC_EFTSH_RUD_Msk & (_UINT32_(value) << GMAC_EFTSH_RUD_Pos)) /* Assigment of value for RUD in the GMAC_EFTSH register */
#define GMAC_EFTSH_Msk                        _UINT32_(0x0000FFFF)                                 /* (GMAC_EFTSH) Register Mask  */


/* -------- GMAC_EFRSH : (GMAC Offset: 0xEC) ( R/ 32) PTP Event Frame Received Seconds High Register -------- */
#define GMAC_EFRSH_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_EFRSH) PTP Event Frame Received Seconds High Register  Reset Value */

#define GMAC_EFRSH_RUD_Pos                    _UINT32_(0)                                          /* (GMAC_EFRSH) Register Update Position */
#define GMAC_EFRSH_RUD_Msk                    (_UINT32_(0xFFFF) << GMAC_EFRSH_RUD_Pos)             /* (GMAC_EFRSH) Register Update Mask */
#define GMAC_EFRSH_RUD(value)                 (GMAC_EFRSH_RUD_Msk & (_UINT32_(value) << GMAC_EFRSH_RUD_Pos)) /* Assigment of value for RUD in the GMAC_EFRSH register */
#define GMAC_EFRSH_Msk                        _UINT32_(0x0000FFFF)                                 /* (GMAC_EFRSH) Register Mask  */


/* -------- GMAC_PEFTSH : (GMAC Offset: 0xF0) ( R/ 32) PTP Peer Event Frame Transmitted Seconds High Register -------- */
#define GMAC_PEFTSH_RESETVALUE                _UINT32_(0x00)                                       /*  (GMAC_PEFTSH) PTP Peer Event Frame Transmitted Seconds High Register  Reset Value */

#define GMAC_PEFTSH_RUD_Pos                   _UINT32_(0)                                          /* (GMAC_PEFTSH) Register Update Position */
#define GMAC_PEFTSH_RUD_Msk                   (_UINT32_(0xFFFF) << GMAC_PEFTSH_RUD_Pos)            /* (GMAC_PEFTSH) Register Update Mask */
#define GMAC_PEFTSH_RUD(value)                (GMAC_PEFTSH_RUD_Msk & (_UINT32_(value) << GMAC_PEFTSH_RUD_Pos)) /* Assigment of value for RUD in the GMAC_PEFTSH register */
#define GMAC_PEFTSH_Msk                       _UINT32_(0x0000FFFF)                                 /* (GMAC_PEFTSH) Register Mask  */


/* -------- GMAC_PEFRSH : (GMAC Offset: 0xF4) ( R/ 32) PTP Peer Event Frame Received Seconds High Register -------- */
#define GMAC_PEFRSH_RESETVALUE                _UINT32_(0x00)                                       /*  (GMAC_PEFRSH) PTP Peer Event Frame Received Seconds High Register  Reset Value */

#define GMAC_PEFRSH_RUD_Pos                   _UINT32_(0)                                          /* (GMAC_PEFRSH) Register Update Position */
#define GMAC_PEFRSH_RUD_Msk                   (_UINT32_(0xFFFF) << GMAC_PEFRSH_RUD_Pos)            /* (GMAC_PEFRSH) Register Update Mask */
#define GMAC_PEFRSH_RUD(value)                (GMAC_PEFRSH_RUD_Msk & (_UINT32_(value) << GMAC_PEFRSH_RUD_Pos)) /* Assigment of value for RUD in the GMAC_PEFRSH register */
#define GMAC_PEFRSH_Msk                       _UINT32_(0x0000FFFF)                                 /* (GMAC_PEFRSH) Register Mask  */


/* -------- GMAC_OTLO : (GMAC Offset: 0x100) ( R/ 32) Octets Transmitted Low Register -------- */
#define GMAC_OTLO_RESETVALUE                  _UINT32_(0x00)                                       /*  (GMAC_OTLO) Octets Transmitted Low Register  Reset Value */

#define GMAC_OTLO_TXO_Pos                     _UINT32_(0)                                          /* (GMAC_OTLO) Transmitted Octets Position */
#define GMAC_OTLO_TXO_Msk                     (_UINT32_(0xFFFFFFFF) << GMAC_OTLO_TXO_Pos)          /* (GMAC_OTLO) Transmitted Octets Mask */
#define GMAC_OTLO_TXO(value)                  (GMAC_OTLO_TXO_Msk & (_UINT32_(value) << GMAC_OTLO_TXO_Pos)) /* Assigment of value for TXO in the GMAC_OTLO register */
#define GMAC_OTLO_Msk                         _UINT32_(0xFFFFFFFF)                                 /* (GMAC_OTLO) Register Mask  */


/* -------- GMAC_OTHI : (GMAC Offset: 0x104) ( R/ 32) Octets Transmitted High Register -------- */
#define GMAC_OTHI_RESETVALUE                  _UINT32_(0x00)                                       /*  (GMAC_OTHI) Octets Transmitted High Register  Reset Value */

#define GMAC_OTHI_TXO_Pos                     _UINT32_(0)                                          /* (GMAC_OTHI) Transmitted Octets Position */
#define GMAC_OTHI_TXO_Msk                     (_UINT32_(0xFFFF) << GMAC_OTHI_TXO_Pos)              /* (GMAC_OTHI) Transmitted Octets Mask */
#define GMAC_OTHI_TXO(value)                  (GMAC_OTHI_TXO_Msk & (_UINT32_(value) << GMAC_OTHI_TXO_Pos)) /* Assigment of value for TXO in the GMAC_OTHI register */
#define GMAC_OTHI_Msk                         _UINT32_(0x0000FFFF)                                 /* (GMAC_OTHI) Register Mask  */


/* -------- GMAC_FT : (GMAC Offset: 0x108) ( R/ 32) Frames Transmitted Register -------- */
#define GMAC_FT_RESETVALUE                    _UINT32_(0x00)                                       /*  (GMAC_FT) Frames Transmitted Register  Reset Value */

#define GMAC_FT_FTX_Pos                       _UINT32_(0)                                          /* (GMAC_FT) Frames Transmitted without Error Position */
#define GMAC_FT_FTX_Msk                       (_UINT32_(0xFFFFFFFF) << GMAC_FT_FTX_Pos)            /* (GMAC_FT) Frames Transmitted without Error Mask */
#define GMAC_FT_FTX(value)                    (GMAC_FT_FTX_Msk & (_UINT32_(value) << GMAC_FT_FTX_Pos)) /* Assigment of value for FTX in the GMAC_FT register */
#define GMAC_FT_Msk                           _UINT32_(0xFFFFFFFF)                                 /* (GMAC_FT) Register Mask  */


/* -------- GMAC_BCFT : (GMAC Offset: 0x10C) ( R/ 32) Broadcast Frames Transmitted Register -------- */
#define GMAC_BCFT_RESETVALUE                  _UINT32_(0x00)                                       /*  (GMAC_BCFT) Broadcast Frames Transmitted Register  Reset Value */

#define GMAC_BCFT_BFTX_Pos                    _UINT32_(0)                                          /* (GMAC_BCFT) Broadcast Frames Transmitted without Error Position */
#define GMAC_BCFT_BFTX_Msk                    (_UINT32_(0xFFFFFFFF) << GMAC_BCFT_BFTX_Pos)         /* (GMAC_BCFT) Broadcast Frames Transmitted without Error Mask */
#define GMAC_BCFT_BFTX(value)                 (GMAC_BCFT_BFTX_Msk & (_UINT32_(value) << GMAC_BCFT_BFTX_Pos)) /* Assigment of value for BFTX in the GMAC_BCFT register */
#define GMAC_BCFT_Msk                         _UINT32_(0xFFFFFFFF)                                 /* (GMAC_BCFT) Register Mask  */


/* -------- GMAC_MFT : (GMAC Offset: 0x110) ( R/ 32) Multicast Frames Transmitted Register -------- */
#define GMAC_MFT_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_MFT) Multicast Frames Transmitted Register  Reset Value */

#define GMAC_MFT_MFTX_Pos                     _UINT32_(0)                                          /* (GMAC_MFT) Multicast Frames Transmitted without Error Position */
#define GMAC_MFT_MFTX_Msk                     (_UINT32_(0xFFFFFFFF) << GMAC_MFT_MFTX_Pos)          /* (GMAC_MFT) Multicast Frames Transmitted without Error Mask */
#define GMAC_MFT_MFTX(value)                  (GMAC_MFT_MFTX_Msk & (_UINT32_(value) << GMAC_MFT_MFTX_Pos)) /* Assigment of value for MFTX in the GMAC_MFT register */
#define GMAC_MFT_Msk                          _UINT32_(0xFFFFFFFF)                                 /* (GMAC_MFT) Register Mask  */


/* -------- GMAC_PFT : (GMAC Offset: 0x114) ( R/ 32) Pause Frames Transmitted Register -------- */
#define GMAC_PFT_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_PFT) Pause Frames Transmitted Register  Reset Value */

#define GMAC_PFT_PFTX_Pos                     _UINT32_(0)                                          /* (GMAC_PFT) Pause Frames Transmitted Register Position */
#define GMAC_PFT_PFTX_Msk                     (_UINT32_(0xFFFF) << GMAC_PFT_PFTX_Pos)              /* (GMAC_PFT) Pause Frames Transmitted Register Mask */
#define GMAC_PFT_PFTX(value)                  (GMAC_PFT_PFTX_Msk & (_UINT32_(value) << GMAC_PFT_PFTX_Pos)) /* Assigment of value for PFTX in the GMAC_PFT register */
#define GMAC_PFT_Msk                          _UINT32_(0x0000FFFF)                                 /* (GMAC_PFT) Register Mask  */


/* -------- GMAC_BFT64 : (GMAC Offset: 0x118) ( R/ 32) 64 Byte Frames Transmitted Register -------- */
#define GMAC_BFT64_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_BFT64) 64 Byte Frames Transmitted Register  Reset Value */

#define GMAC_BFT64_NFTX_Pos                   _UINT32_(0)                                          /* (GMAC_BFT64) 64 Byte Frames Transmitted without Error Position */
#define GMAC_BFT64_NFTX_Msk                   (_UINT32_(0xFFFFFFFF) << GMAC_BFT64_NFTX_Pos)        /* (GMAC_BFT64) 64 Byte Frames Transmitted without Error Mask */
#define GMAC_BFT64_NFTX(value)                (GMAC_BFT64_NFTX_Msk & (_UINT32_(value) << GMAC_BFT64_NFTX_Pos)) /* Assigment of value for NFTX in the GMAC_BFT64 register */
#define GMAC_BFT64_Msk                        _UINT32_(0xFFFFFFFF)                                 /* (GMAC_BFT64) Register Mask  */


/* -------- GMAC_TBFT127 : (GMAC Offset: 0x11C) ( R/ 32) 65 to 127 Byte Frames Transmitted Register -------- */
#define GMAC_TBFT127_RESETVALUE               _UINT32_(0x00)                                       /*  (GMAC_TBFT127) 65 to 127 Byte Frames Transmitted Register  Reset Value */

#define GMAC_TBFT127_NFTX_Pos                 _UINT32_(0)                                          /* (GMAC_TBFT127) 65 to 127 Byte Frames Transmitted without Error Position */
#define GMAC_TBFT127_NFTX_Msk                 (_UINT32_(0xFFFFFFFF) << GMAC_TBFT127_NFTX_Pos)      /* (GMAC_TBFT127) 65 to 127 Byte Frames Transmitted without Error Mask */
#define GMAC_TBFT127_NFTX(value)              (GMAC_TBFT127_NFTX_Msk & (_UINT32_(value) << GMAC_TBFT127_NFTX_Pos)) /* Assigment of value for NFTX in the GMAC_TBFT127 register */
#define GMAC_TBFT127_Msk                      _UINT32_(0xFFFFFFFF)                                 /* (GMAC_TBFT127) Register Mask  */


/* -------- GMAC_TBFT255 : (GMAC Offset: 0x120) ( R/ 32) 128 to 255 Byte Frames Transmitted Register -------- */
#define GMAC_TBFT255_RESETVALUE               _UINT32_(0x00)                                       /*  (GMAC_TBFT255) 128 to 255 Byte Frames Transmitted Register  Reset Value */

#define GMAC_TBFT255_NFTX_Pos                 _UINT32_(0)                                          /* (GMAC_TBFT255) 128 to 255 Byte Frames Transmitted without Error Position */
#define GMAC_TBFT255_NFTX_Msk                 (_UINT32_(0xFFFFFFFF) << GMAC_TBFT255_NFTX_Pos)      /* (GMAC_TBFT255) 128 to 255 Byte Frames Transmitted without Error Mask */
#define GMAC_TBFT255_NFTX(value)              (GMAC_TBFT255_NFTX_Msk & (_UINT32_(value) << GMAC_TBFT255_NFTX_Pos)) /* Assigment of value for NFTX in the GMAC_TBFT255 register */
#define GMAC_TBFT255_Msk                      _UINT32_(0xFFFFFFFF)                                 /* (GMAC_TBFT255) Register Mask  */


/* -------- GMAC_TBFT511 : (GMAC Offset: 0x124) ( R/ 32) 256 to 511 Byte Frames Transmitted Register -------- */
#define GMAC_TBFT511_RESETVALUE               _UINT32_(0x00)                                       /*  (GMAC_TBFT511) 256 to 511 Byte Frames Transmitted Register  Reset Value */

#define GMAC_TBFT511_NFTX_Pos                 _UINT32_(0)                                          /* (GMAC_TBFT511) 256 to 511 Byte Frames Transmitted without Error Position */
#define GMAC_TBFT511_NFTX_Msk                 (_UINT32_(0xFFFFFFFF) << GMAC_TBFT511_NFTX_Pos)      /* (GMAC_TBFT511) 256 to 511 Byte Frames Transmitted without Error Mask */
#define GMAC_TBFT511_NFTX(value)              (GMAC_TBFT511_NFTX_Msk & (_UINT32_(value) << GMAC_TBFT511_NFTX_Pos)) /* Assigment of value for NFTX in the GMAC_TBFT511 register */
#define GMAC_TBFT511_Msk                      _UINT32_(0xFFFFFFFF)                                 /* (GMAC_TBFT511) Register Mask  */


/* -------- GMAC_TBFT1023 : (GMAC Offset: 0x128) ( R/ 32) 512 to 1023 Byte Frames Transmitted Register -------- */
#define GMAC_TBFT1023_RESETVALUE              _UINT32_(0x00)                                       /*  (GMAC_TBFT1023) 512 to 1023 Byte Frames Transmitted Register  Reset Value */

#define GMAC_TBFT1023_NFTX_Pos                _UINT32_(0)                                          /* (GMAC_TBFT1023) 512 to 1023 Byte Frames Transmitted without Error Position */
#define GMAC_TBFT1023_NFTX_Msk                (_UINT32_(0xFFFFFFFF) << GMAC_TBFT1023_NFTX_Pos)     /* (GMAC_TBFT1023) 512 to 1023 Byte Frames Transmitted without Error Mask */
#define GMAC_TBFT1023_NFTX(value)             (GMAC_TBFT1023_NFTX_Msk & (_UINT32_(value) << GMAC_TBFT1023_NFTX_Pos)) /* Assigment of value for NFTX in the GMAC_TBFT1023 register */
#define GMAC_TBFT1023_Msk                     _UINT32_(0xFFFFFFFF)                                 /* (GMAC_TBFT1023) Register Mask  */


/* -------- GMAC_TBFT1518 : (GMAC Offset: 0x12C) ( R/ 32) 1024 to 1518 Byte Frames Transmitted Register -------- */
#define GMAC_TBFT1518_RESETVALUE              _UINT32_(0x00)                                       /*  (GMAC_TBFT1518) 1024 to 1518 Byte Frames Transmitted Register  Reset Value */

#define GMAC_TBFT1518_NFTX_Pos                _UINT32_(0)                                          /* (GMAC_TBFT1518) 1024 to 1518 Byte Frames Transmitted without Error Position */
#define GMAC_TBFT1518_NFTX_Msk                (_UINT32_(0xFFFFFFFF) << GMAC_TBFT1518_NFTX_Pos)     /* (GMAC_TBFT1518) 1024 to 1518 Byte Frames Transmitted without Error Mask */
#define GMAC_TBFT1518_NFTX(value)             (GMAC_TBFT1518_NFTX_Msk & (_UINT32_(value) << GMAC_TBFT1518_NFTX_Pos)) /* Assigment of value for NFTX in the GMAC_TBFT1518 register */
#define GMAC_TBFT1518_Msk                     _UINT32_(0xFFFFFFFF)                                 /* (GMAC_TBFT1518) Register Mask  */


/* -------- GMAC_GTBFT1518 : (GMAC Offset: 0x130) ( R/ 32) Greater Than 1518 Byte Frames Transmitted Register -------- */
#define GMAC_GTBFT1518_RESETVALUE             _UINT32_(0x00)                                       /*  (GMAC_GTBFT1518) Greater Than 1518 Byte Frames Transmitted Register  Reset Value */

#define GMAC_GTBFT1518_NFTX_Pos               _UINT32_(0)                                          /* (GMAC_GTBFT1518) Greater than 1518 Byte Frames Transmitted without Error Position */
#define GMAC_GTBFT1518_NFTX_Msk               (_UINT32_(0xFFFFFFFF) << GMAC_GTBFT1518_NFTX_Pos)    /* (GMAC_GTBFT1518) Greater than 1518 Byte Frames Transmitted without Error Mask */
#define GMAC_GTBFT1518_NFTX(value)            (GMAC_GTBFT1518_NFTX_Msk & (_UINT32_(value) << GMAC_GTBFT1518_NFTX_Pos)) /* Assigment of value for NFTX in the GMAC_GTBFT1518 register */
#define GMAC_GTBFT1518_Msk                    _UINT32_(0xFFFFFFFF)                                 /* (GMAC_GTBFT1518) Register Mask  */


/* -------- GMAC_TUR : (GMAC Offset: 0x134) ( R/ 32) Transmit Underruns Register -------- */
#define GMAC_TUR_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_TUR) Transmit Underruns Register  Reset Value */

#define GMAC_TUR_TXUNR_Pos                    _UINT32_(0)                                          /* (GMAC_TUR) Transmit Underruns Position */
#define GMAC_TUR_TXUNR_Msk                    (_UINT32_(0x3FF) << GMAC_TUR_TXUNR_Pos)              /* (GMAC_TUR) Transmit Underruns Mask */
#define GMAC_TUR_TXUNR(value)                 (GMAC_TUR_TXUNR_Msk & (_UINT32_(value) << GMAC_TUR_TXUNR_Pos)) /* Assigment of value for TXUNR in the GMAC_TUR register */
#define GMAC_TUR_Msk                          _UINT32_(0x000003FF)                                 /* (GMAC_TUR) Register Mask  */


/* -------- GMAC_SCF : (GMAC Offset: 0x138) ( R/ 32) Single Collision Frames Register -------- */
#define GMAC_SCF_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_SCF) Single Collision Frames Register  Reset Value */

#define GMAC_SCF_SCOL_Pos                     _UINT32_(0)                                          /* (GMAC_SCF) Single Collision Position */
#define GMAC_SCF_SCOL_Msk                     (_UINT32_(0x3FFFF) << GMAC_SCF_SCOL_Pos)             /* (GMAC_SCF) Single Collision Mask */
#define GMAC_SCF_SCOL(value)                  (GMAC_SCF_SCOL_Msk & (_UINT32_(value) << GMAC_SCF_SCOL_Pos)) /* Assigment of value for SCOL in the GMAC_SCF register */
#define GMAC_SCF_Msk                          _UINT32_(0x0003FFFF)                                 /* (GMAC_SCF) Register Mask  */


/* -------- GMAC_MCF : (GMAC Offset: 0x13C) ( R/ 32) Multiple Collision Frames Register -------- */
#define GMAC_MCF_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_MCF) Multiple Collision Frames Register  Reset Value */

#define GMAC_MCF_MCOL_Pos                     _UINT32_(0)                                          /* (GMAC_MCF) Multiple Collision Position */
#define GMAC_MCF_MCOL_Msk                     (_UINT32_(0x3FFFF) << GMAC_MCF_MCOL_Pos)             /* (GMAC_MCF) Multiple Collision Mask */
#define GMAC_MCF_MCOL(value)                  (GMAC_MCF_MCOL_Msk & (_UINT32_(value) << GMAC_MCF_MCOL_Pos)) /* Assigment of value for MCOL in the GMAC_MCF register */
#define GMAC_MCF_Msk                          _UINT32_(0x0003FFFF)                                 /* (GMAC_MCF) Register Mask  */


/* -------- GMAC_EC : (GMAC Offset: 0x140) ( R/ 32) Excessive Collisions Register -------- */
#define GMAC_EC_RESETVALUE                    _UINT32_(0x00)                                       /*  (GMAC_EC) Excessive Collisions Register  Reset Value */

#define GMAC_EC_XCOL_Pos                      _UINT32_(0)                                          /* (GMAC_EC) Excessive Collisions Position */
#define GMAC_EC_XCOL_Msk                      (_UINT32_(0x3FF) << GMAC_EC_XCOL_Pos)                /* (GMAC_EC) Excessive Collisions Mask */
#define GMAC_EC_XCOL(value)                   (GMAC_EC_XCOL_Msk & (_UINT32_(value) << GMAC_EC_XCOL_Pos)) /* Assigment of value for XCOL in the GMAC_EC register */
#define GMAC_EC_Msk                           _UINT32_(0x000003FF)                                 /* (GMAC_EC) Register Mask  */


/* -------- GMAC_LC : (GMAC Offset: 0x144) ( R/ 32) Late Collisions Register -------- */
#define GMAC_LC_RESETVALUE                    _UINT32_(0x00)                                       /*  (GMAC_LC) Late Collisions Register  Reset Value */

#define GMAC_LC_LCOL_Pos                      _UINT32_(0)                                          /* (GMAC_LC) Late Collisions Position */
#define GMAC_LC_LCOL_Msk                      (_UINT32_(0x3FF) << GMAC_LC_LCOL_Pos)                /* (GMAC_LC) Late Collisions Mask */
#define GMAC_LC_LCOL(value)                   (GMAC_LC_LCOL_Msk & (_UINT32_(value) << GMAC_LC_LCOL_Pos)) /* Assigment of value for LCOL in the GMAC_LC register */
#define GMAC_LC_Msk                           _UINT32_(0x000003FF)                                 /* (GMAC_LC) Register Mask  */


/* -------- GMAC_DTF : (GMAC Offset: 0x148) ( R/ 32) Deferred Transmission Frames Register -------- */
#define GMAC_DTF_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_DTF) Deferred Transmission Frames Register  Reset Value */

#define GMAC_DTF_DEFT_Pos                     _UINT32_(0)                                          /* (GMAC_DTF) Deferred Transmission Position */
#define GMAC_DTF_DEFT_Msk                     (_UINT32_(0x3FFFF) << GMAC_DTF_DEFT_Pos)             /* (GMAC_DTF) Deferred Transmission Mask */
#define GMAC_DTF_DEFT(value)                  (GMAC_DTF_DEFT_Msk & (_UINT32_(value) << GMAC_DTF_DEFT_Pos)) /* Assigment of value for DEFT in the GMAC_DTF register */
#define GMAC_DTF_Msk                          _UINT32_(0x0003FFFF)                                 /* (GMAC_DTF) Register Mask  */


/* -------- GMAC_CSE : (GMAC Offset: 0x14C) ( R/ 32) Carrier Sense Errors Register -------- */
#define GMAC_CSE_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_CSE) Carrier Sense Errors Register  Reset Value */

#define GMAC_CSE_CSR_Pos                      _UINT32_(0)                                          /* (GMAC_CSE) Carrier Sense Error Position */
#define GMAC_CSE_CSR_Msk                      (_UINT32_(0x3FF) << GMAC_CSE_CSR_Pos)                /* (GMAC_CSE) Carrier Sense Error Mask */
#define GMAC_CSE_CSR(value)                   (GMAC_CSE_CSR_Msk & (_UINT32_(value) << GMAC_CSE_CSR_Pos)) /* Assigment of value for CSR in the GMAC_CSE register */
#define GMAC_CSE_Msk                          _UINT32_(0x000003FF)                                 /* (GMAC_CSE) Register Mask  */


/* -------- GMAC_ORLO : (GMAC Offset: 0x150) ( R/ 32) Octets Received Low Received Register -------- */
#define GMAC_ORLO_RESETVALUE                  _UINT32_(0x00)                                       /*  (GMAC_ORLO) Octets Received Low Received Register  Reset Value */

#define GMAC_ORLO_RXO_Pos                     _UINT32_(0)                                          /* (GMAC_ORLO) Received Octets Position */
#define GMAC_ORLO_RXO_Msk                     (_UINT32_(0xFFFFFFFF) << GMAC_ORLO_RXO_Pos)          /* (GMAC_ORLO) Received Octets Mask */
#define GMAC_ORLO_RXO(value)                  (GMAC_ORLO_RXO_Msk & (_UINT32_(value) << GMAC_ORLO_RXO_Pos)) /* Assigment of value for RXO in the GMAC_ORLO register */
#define GMAC_ORLO_Msk                         _UINT32_(0xFFFFFFFF)                                 /* (GMAC_ORLO) Register Mask  */


/* -------- GMAC_ORHI : (GMAC Offset: 0x154) ( R/ 32) Octets Received High Received Register -------- */
#define GMAC_ORHI_RESETVALUE                  _UINT32_(0x00)                                       /*  (GMAC_ORHI) Octets Received High Received Register  Reset Value */

#define GMAC_ORHI_RXO_Pos                     _UINT32_(0)                                          /* (GMAC_ORHI) Received Octets Position */
#define GMAC_ORHI_RXO_Msk                     (_UINT32_(0xFFFF) << GMAC_ORHI_RXO_Pos)              /* (GMAC_ORHI) Received Octets Mask */
#define GMAC_ORHI_RXO(value)                  (GMAC_ORHI_RXO_Msk & (_UINT32_(value) << GMAC_ORHI_RXO_Pos)) /* Assigment of value for RXO in the GMAC_ORHI register */
#define GMAC_ORHI_Msk                         _UINT32_(0x0000FFFF)                                 /* (GMAC_ORHI) Register Mask  */


/* -------- GMAC_FR : (GMAC Offset: 0x158) ( R/ 32) Frames Received Register -------- */
#define GMAC_FR_RESETVALUE                    _UINT32_(0x00)                                       /*  (GMAC_FR) Frames Received Register  Reset Value */

#define GMAC_FR_FRX_Pos                       _UINT32_(0)                                          /* (GMAC_FR) Frames Received without Error Position */
#define GMAC_FR_FRX_Msk                       (_UINT32_(0xFFFFFFFF) << GMAC_FR_FRX_Pos)            /* (GMAC_FR) Frames Received without Error Mask */
#define GMAC_FR_FRX(value)                    (GMAC_FR_FRX_Msk & (_UINT32_(value) << GMAC_FR_FRX_Pos)) /* Assigment of value for FRX in the GMAC_FR register */
#define GMAC_FR_Msk                           _UINT32_(0xFFFFFFFF)                                 /* (GMAC_FR) Register Mask  */


/* -------- GMAC_BCFR : (GMAC Offset: 0x15C) ( R/ 32) Broadcast Frames Received Register -------- */
#define GMAC_BCFR_RESETVALUE                  _UINT32_(0x00)                                       /*  (GMAC_BCFR) Broadcast Frames Received Register  Reset Value */

#define GMAC_BCFR_BFRX_Pos                    _UINT32_(0)                                          /* (GMAC_BCFR) Broadcast Frames Received without Error Position */
#define GMAC_BCFR_BFRX_Msk                    (_UINT32_(0xFFFFFFFF) << GMAC_BCFR_BFRX_Pos)         /* (GMAC_BCFR) Broadcast Frames Received without Error Mask */
#define GMAC_BCFR_BFRX(value)                 (GMAC_BCFR_BFRX_Msk & (_UINT32_(value) << GMAC_BCFR_BFRX_Pos)) /* Assigment of value for BFRX in the GMAC_BCFR register */
#define GMAC_BCFR_Msk                         _UINT32_(0xFFFFFFFF)                                 /* (GMAC_BCFR) Register Mask  */


/* -------- GMAC_MFR : (GMAC Offset: 0x160) ( R/ 32) Multicast Frames Received Register -------- */
#define GMAC_MFR_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_MFR) Multicast Frames Received Register  Reset Value */

#define GMAC_MFR_MFRX_Pos                     _UINT32_(0)                                          /* (GMAC_MFR) Multicast Frames Received without Error Position */
#define GMAC_MFR_MFRX_Msk                     (_UINT32_(0xFFFFFFFF) << GMAC_MFR_MFRX_Pos)          /* (GMAC_MFR) Multicast Frames Received without Error Mask */
#define GMAC_MFR_MFRX(value)                  (GMAC_MFR_MFRX_Msk & (_UINT32_(value) << GMAC_MFR_MFRX_Pos)) /* Assigment of value for MFRX in the GMAC_MFR register */
#define GMAC_MFR_Msk                          _UINT32_(0xFFFFFFFF)                                 /* (GMAC_MFR) Register Mask  */


/* -------- GMAC_PFR : (GMAC Offset: 0x164) ( R/ 32) Pause Frames Received Register -------- */
#define GMAC_PFR_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_PFR) Pause Frames Received Register  Reset Value */

#define GMAC_PFR_PFRX_Pos                     _UINT32_(0)                                          /* (GMAC_PFR) Pause Frames Received Register Position */
#define GMAC_PFR_PFRX_Msk                     (_UINT32_(0xFFFF) << GMAC_PFR_PFRX_Pos)              /* (GMAC_PFR) Pause Frames Received Register Mask */
#define GMAC_PFR_PFRX(value)                  (GMAC_PFR_PFRX_Msk & (_UINT32_(value) << GMAC_PFR_PFRX_Pos)) /* Assigment of value for PFRX in the GMAC_PFR register */
#define GMAC_PFR_Msk                          _UINT32_(0x0000FFFF)                                 /* (GMAC_PFR) Register Mask  */


/* -------- GMAC_BFR64 : (GMAC Offset: 0x168) ( R/ 32) 64 Byte Frames Received Register -------- */
#define GMAC_BFR64_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_BFR64) 64 Byte Frames Received Register  Reset Value */

#define GMAC_BFR64_NFRX_Pos                   _UINT32_(0)                                          /* (GMAC_BFR64) 64 Byte Frames Received without Error Position */
#define GMAC_BFR64_NFRX_Msk                   (_UINT32_(0xFFFFFFFF) << GMAC_BFR64_NFRX_Pos)        /* (GMAC_BFR64) 64 Byte Frames Received without Error Mask */
#define GMAC_BFR64_NFRX(value)                (GMAC_BFR64_NFRX_Msk & (_UINT32_(value) << GMAC_BFR64_NFRX_Pos)) /* Assigment of value for NFRX in the GMAC_BFR64 register */
#define GMAC_BFR64_Msk                        _UINT32_(0xFFFFFFFF)                                 /* (GMAC_BFR64) Register Mask  */


/* -------- GMAC_TBFR127 : (GMAC Offset: 0x16C) ( R/ 32) 65 to 127 Byte Frames Received Register -------- */
#define GMAC_TBFR127_RESETVALUE               _UINT32_(0x00)                                       /*  (GMAC_TBFR127) 65 to 127 Byte Frames Received Register  Reset Value */

#define GMAC_TBFR127_NFRX_Pos                 _UINT32_(0)                                          /* (GMAC_TBFR127) 65 to 127 Byte Frames Received without Error Position */
#define GMAC_TBFR127_NFRX_Msk                 (_UINT32_(0xFFFFFFFF) << GMAC_TBFR127_NFRX_Pos)      /* (GMAC_TBFR127) 65 to 127 Byte Frames Received without Error Mask */
#define GMAC_TBFR127_NFRX(value)              (GMAC_TBFR127_NFRX_Msk & (_UINT32_(value) << GMAC_TBFR127_NFRX_Pos)) /* Assigment of value for NFRX in the GMAC_TBFR127 register */
#define GMAC_TBFR127_Msk                      _UINT32_(0xFFFFFFFF)                                 /* (GMAC_TBFR127) Register Mask  */


/* -------- GMAC_TBFR255 : (GMAC Offset: 0x170) ( R/ 32) 128 to 255 Byte Frames Received Register -------- */
#define GMAC_TBFR255_RESETVALUE               _UINT32_(0x00)                                       /*  (GMAC_TBFR255) 128 to 255 Byte Frames Received Register  Reset Value */

#define GMAC_TBFR255_NFRX_Pos                 _UINT32_(0)                                          /* (GMAC_TBFR255) 128 to 255 Byte Frames Received without Error Position */
#define GMAC_TBFR255_NFRX_Msk                 (_UINT32_(0xFFFFFFFF) << GMAC_TBFR255_NFRX_Pos)      /* (GMAC_TBFR255) 128 to 255 Byte Frames Received without Error Mask */
#define GMAC_TBFR255_NFRX(value)              (GMAC_TBFR255_NFRX_Msk & (_UINT32_(value) << GMAC_TBFR255_NFRX_Pos)) /* Assigment of value for NFRX in the GMAC_TBFR255 register */
#define GMAC_TBFR255_Msk                      _UINT32_(0xFFFFFFFF)                                 /* (GMAC_TBFR255) Register Mask  */


/* -------- GMAC_TBFR511 : (GMAC Offset: 0x174) ( R/ 32) 256 to 511 Byte Frames Received Register -------- */
#define GMAC_TBFR511_RESETVALUE               _UINT32_(0x00)                                       /*  (GMAC_TBFR511) 256 to 511 Byte Frames Received Register  Reset Value */

#define GMAC_TBFR511_NFRX_Pos                 _UINT32_(0)                                          /* (GMAC_TBFR511) 256 to 511 Byte Frames Received without Error Position */
#define GMAC_TBFR511_NFRX_Msk                 (_UINT32_(0xFFFFFFFF) << GMAC_TBFR511_NFRX_Pos)      /* (GMAC_TBFR511) 256 to 511 Byte Frames Received without Error Mask */
#define GMAC_TBFR511_NFRX(value)              (GMAC_TBFR511_NFRX_Msk & (_UINT32_(value) << GMAC_TBFR511_NFRX_Pos)) /* Assigment of value for NFRX in the GMAC_TBFR511 register */
#define GMAC_TBFR511_Msk                      _UINT32_(0xFFFFFFFF)                                 /* (GMAC_TBFR511) Register Mask  */


/* -------- GMAC_TBFR1023 : (GMAC Offset: 0x178) ( R/ 32) 512 to 1023 Byte Frames Received Register -------- */
#define GMAC_TBFR1023_RESETVALUE              _UINT32_(0x00)                                       /*  (GMAC_TBFR1023) 512 to 1023 Byte Frames Received Register  Reset Value */

#define GMAC_TBFR1023_NFRX_Pos                _UINT32_(0)                                          /* (GMAC_TBFR1023) 512 to 1023 Byte Frames Received without Error Position */
#define GMAC_TBFR1023_NFRX_Msk                (_UINT32_(0xFFFFFFFF) << GMAC_TBFR1023_NFRX_Pos)     /* (GMAC_TBFR1023) 512 to 1023 Byte Frames Received without Error Mask */
#define GMAC_TBFR1023_NFRX(value)             (GMAC_TBFR1023_NFRX_Msk & (_UINT32_(value) << GMAC_TBFR1023_NFRX_Pos)) /* Assigment of value for NFRX in the GMAC_TBFR1023 register */
#define GMAC_TBFR1023_Msk                     _UINT32_(0xFFFFFFFF)                                 /* (GMAC_TBFR1023) Register Mask  */


/* -------- GMAC_TBFR1518 : (GMAC Offset: 0x17C) ( R/ 32) 1024 to 1518 Byte Frames Received Register -------- */
#define GMAC_TBFR1518_RESETVALUE              _UINT32_(0x00)                                       /*  (GMAC_TBFR1518) 1024 to 1518 Byte Frames Received Register  Reset Value */

#define GMAC_TBFR1518_NFRX_Pos                _UINT32_(0)                                          /* (GMAC_TBFR1518) 1024 to 1518 Byte Frames Received without Error Position */
#define GMAC_TBFR1518_NFRX_Msk                (_UINT32_(0xFFFFFFFF) << GMAC_TBFR1518_NFRX_Pos)     /* (GMAC_TBFR1518) 1024 to 1518 Byte Frames Received without Error Mask */
#define GMAC_TBFR1518_NFRX(value)             (GMAC_TBFR1518_NFRX_Msk & (_UINT32_(value) << GMAC_TBFR1518_NFRX_Pos)) /* Assigment of value for NFRX in the GMAC_TBFR1518 register */
#define GMAC_TBFR1518_Msk                     _UINT32_(0xFFFFFFFF)                                 /* (GMAC_TBFR1518) Register Mask  */


/* -------- GMAC_TMXBFR : (GMAC Offset: 0x180) ( R/ 32) 1519 to Maximum Byte Frames Received Register -------- */
#define GMAC_TMXBFR_RESETVALUE                _UINT32_(0x00)                                       /*  (GMAC_TMXBFR) 1519 to Maximum Byte Frames Received Register  Reset Value */

#define GMAC_TMXBFR_NFRX_Pos                  _UINT32_(0)                                          /* (GMAC_TMXBFR) 1519 to Maximum Byte Frames Received without Error Position */
#define GMAC_TMXBFR_NFRX_Msk                  (_UINT32_(0xFFFFFFFF) << GMAC_TMXBFR_NFRX_Pos)       /* (GMAC_TMXBFR) 1519 to Maximum Byte Frames Received without Error Mask */
#define GMAC_TMXBFR_NFRX(value)               (GMAC_TMXBFR_NFRX_Msk & (_UINT32_(value) << GMAC_TMXBFR_NFRX_Pos)) /* Assigment of value for NFRX in the GMAC_TMXBFR register */
#define GMAC_TMXBFR_Msk                       _UINT32_(0xFFFFFFFF)                                 /* (GMAC_TMXBFR) Register Mask  */


/* -------- GMAC_UFR : (GMAC Offset: 0x184) ( R/ 32) Undersize Frames Received Register -------- */
#define GMAC_UFR_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_UFR) Undersize Frames Received Register  Reset Value */

#define GMAC_UFR_UFRX_Pos                     _UINT32_(0)                                          /* (GMAC_UFR) Undersize Frames Received Position */
#define GMAC_UFR_UFRX_Msk                     (_UINT32_(0x3FF) << GMAC_UFR_UFRX_Pos)               /* (GMAC_UFR) Undersize Frames Received Mask */
#define GMAC_UFR_UFRX(value)                  (GMAC_UFR_UFRX_Msk & (_UINT32_(value) << GMAC_UFR_UFRX_Pos)) /* Assigment of value for UFRX in the GMAC_UFR register */
#define GMAC_UFR_Msk                          _UINT32_(0x000003FF)                                 /* (GMAC_UFR) Register Mask  */


/* -------- GMAC_OFR : (GMAC Offset: 0x188) ( R/ 32) Oversize Frames Received Register -------- */
#define GMAC_OFR_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_OFR) Oversize Frames Received Register  Reset Value */

#define GMAC_OFR_OFRX_Pos                     _UINT32_(0)                                          /* (GMAC_OFR) Oversized Frames Received Position */
#define GMAC_OFR_OFRX_Msk                     (_UINT32_(0x3FF) << GMAC_OFR_OFRX_Pos)               /* (GMAC_OFR) Oversized Frames Received Mask */
#define GMAC_OFR_OFRX(value)                  (GMAC_OFR_OFRX_Msk & (_UINT32_(value) << GMAC_OFR_OFRX_Pos)) /* Assigment of value for OFRX in the GMAC_OFR register */
#define GMAC_OFR_Msk                          _UINT32_(0x000003FF)                                 /* (GMAC_OFR) Register Mask  */


/* -------- GMAC_JR : (GMAC Offset: 0x18C) ( R/ 32) Jabbers Received Register -------- */
#define GMAC_JR_RESETVALUE                    _UINT32_(0x00)                                       /*  (GMAC_JR) Jabbers Received Register  Reset Value */

#define GMAC_JR_JRX_Pos                       _UINT32_(0)                                          /* (GMAC_JR) Jabbers Received Position */
#define GMAC_JR_JRX_Msk                       (_UINT32_(0x3FF) << GMAC_JR_JRX_Pos)                 /* (GMAC_JR) Jabbers Received Mask */
#define GMAC_JR_JRX(value)                    (GMAC_JR_JRX_Msk & (_UINT32_(value) << GMAC_JR_JRX_Pos)) /* Assigment of value for JRX in the GMAC_JR register */
#define GMAC_JR_Msk                           _UINT32_(0x000003FF)                                 /* (GMAC_JR) Register Mask  */


/* -------- GMAC_FCSE : (GMAC Offset: 0x190) ( R/ 32) Frame Check Sequence Errors Register -------- */
#define GMAC_FCSE_RESETVALUE                  _UINT32_(0x00)                                       /*  (GMAC_FCSE) Frame Check Sequence Errors Register  Reset Value */

#define GMAC_FCSE_FCKR_Pos                    _UINT32_(0)                                          /* (GMAC_FCSE) Frame Check Sequence Errors Position */
#define GMAC_FCSE_FCKR_Msk                    (_UINT32_(0x3FF) << GMAC_FCSE_FCKR_Pos)              /* (GMAC_FCSE) Frame Check Sequence Errors Mask */
#define GMAC_FCSE_FCKR(value)                 (GMAC_FCSE_FCKR_Msk & (_UINT32_(value) << GMAC_FCSE_FCKR_Pos)) /* Assigment of value for FCKR in the GMAC_FCSE register */
#define GMAC_FCSE_Msk                         _UINT32_(0x000003FF)                                 /* (GMAC_FCSE) Register Mask  */


/* -------- GMAC_LFFE : (GMAC Offset: 0x194) ( R/ 32) Length Field Frame Errors Register -------- */
#define GMAC_LFFE_RESETVALUE                  _UINT32_(0x00)                                       /*  (GMAC_LFFE) Length Field Frame Errors Register  Reset Value */

#define GMAC_LFFE_LFER_Pos                    _UINT32_(0)                                          /* (GMAC_LFFE) Length Field Frame Errors Position */
#define GMAC_LFFE_LFER_Msk                    (_UINT32_(0x3FF) << GMAC_LFFE_LFER_Pos)              /* (GMAC_LFFE) Length Field Frame Errors Mask */
#define GMAC_LFFE_LFER(value)                 (GMAC_LFFE_LFER_Msk & (_UINT32_(value) << GMAC_LFFE_LFER_Pos)) /* Assigment of value for LFER in the GMAC_LFFE register */
#define GMAC_LFFE_Msk                         _UINT32_(0x000003FF)                                 /* (GMAC_LFFE) Register Mask  */


/* -------- GMAC_RSE : (GMAC Offset: 0x198) ( R/ 32) Receive Symbol Errors Register -------- */
#define GMAC_RSE_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_RSE) Receive Symbol Errors Register  Reset Value */

#define GMAC_RSE_RXSE_Pos                     _UINT32_(0)                                          /* (GMAC_RSE) Receive Symbol Errors Position */
#define GMAC_RSE_RXSE_Msk                     (_UINT32_(0x3FF) << GMAC_RSE_RXSE_Pos)               /* (GMAC_RSE) Receive Symbol Errors Mask */
#define GMAC_RSE_RXSE(value)                  (GMAC_RSE_RXSE_Msk & (_UINT32_(value) << GMAC_RSE_RXSE_Pos)) /* Assigment of value for RXSE in the GMAC_RSE register */
#define GMAC_RSE_Msk                          _UINT32_(0x000003FF)                                 /* (GMAC_RSE) Register Mask  */


/* -------- GMAC_AE : (GMAC Offset: 0x19C) ( R/ 32) Alignment Errors Register -------- */
#define GMAC_AE_RESETVALUE                    _UINT32_(0x00)                                       /*  (GMAC_AE) Alignment Errors Register  Reset Value */

#define GMAC_AE_AER_Pos                       _UINT32_(0)                                          /* (GMAC_AE) Alignment Errors Position */
#define GMAC_AE_AER_Msk                       (_UINT32_(0x3FF) << GMAC_AE_AER_Pos)                 /* (GMAC_AE) Alignment Errors Mask */
#define GMAC_AE_AER(value)                    (GMAC_AE_AER_Msk & (_UINT32_(value) << GMAC_AE_AER_Pos)) /* Assigment of value for AER in the GMAC_AE register */
#define GMAC_AE_Msk                           _UINT32_(0x000003FF)                                 /* (GMAC_AE) Register Mask  */


/* -------- GMAC_RRE : (GMAC Offset: 0x1A0) ( R/ 32) Receive Resource Errors Register -------- */
#define GMAC_RRE_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_RRE) Receive Resource Errors Register  Reset Value */

#define GMAC_RRE_RXRER_Pos                    _UINT32_(0)                                          /* (GMAC_RRE) Receive Resource Errors Position */
#define GMAC_RRE_RXRER_Msk                    (_UINT32_(0x3FFFF) << GMAC_RRE_RXRER_Pos)            /* (GMAC_RRE) Receive Resource Errors Mask */
#define GMAC_RRE_RXRER(value)                 (GMAC_RRE_RXRER_Msk & (_UINT32_(value) << GMAC_RRE_RXRER_Pos)) /* Assigment of value for RXRER in the GMAC_RRE register */
#define GMAC_RRE_Msk                          _UINT32_(0x0003FFFF)                                 /* (GMAC_RRE) Register Mask  */


/* -------- GMAC_ROE : (GMAC Offset: 0x1A4) ( R/ 32) Receive Overrun Register -------- */
#define GMAC_ROE_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_ROE) Receive Overrun Register  Reset Value */

#define GMAC_ROE_RXOVR_Pos                    _UINT32_(0)                                          /* (GMAC_ROE) Receive Overruns Position */
#define GMAC_ROE_RXOVR_Msk                    (_UINT32_(0x3FF) << GMAC_ROE_RXOVR_Pos)              /* (GMAC_ROE) Receive Overruns Mask */
#define GMAC_ROE_RXOVR(value)                 (GMAC_ROE_RXOVR_Msk & (_UINT32_(value) << GMAC_ROE_RXOVR_Pos)) /* Assigment of value for RXOVR in the GMAC_ROE register */
#define GMAC_ROE_Msk                          _UINT32_(0x000003FF)                                 /* (GMAC_ROE) Register Mask  */


/* -------- GMAC_IHCE : (GMAC Offset: 0x1A8) ( R/ 32) IP Header Checksum Errors Register -------- */
#define GMAC_IHCE_RESETVALUE                  _UINT32_(0x00)                                       /*  (GMAC_IHCE) IP Header Checksum Errors Register  Reset Value */

#define GMAC_IHCE_HCKER_Pos                   _UINT32_(0)                                          /* (GMAC_IHCE) IP Header Checksum Errors Position */
#define GMAC_IHCE_HCKER_Msk                   (_UINT32_(0xFF) << GMAC_IHCE_HCKER_Pos)              /* (GMAC_IHCE) IP Header Checksum Errors Mask */
#define GMAC_IHCE_HCKER(value)                (GMAC_IHCE_HCKER_Msk & (_UINT32_(value) << GMAC_IHCE_HCKER_Pos)) /* Assigment of value for HCKER in the GMAC_IHCE register */
#define GMAC_IHCE_Msk                         _UINT32_(0x000000FF)                                 /* (GMAC_IHCE) Register Mask  */


/* -------- GMAC_TCE : (GMAC Offset: 0x1AC) ( R/ 32) TCP Checksum Errors Register -------- */
#define GMAC_TCE_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_TCE) TCP Checksum Errors Register  Reset Value */

#define GMAC_TCE_TCKER_Pos                    _UINT32_(0)                                          /* (GMAC_TCE) TCP Checksum Errors Position */
#define GMAC_TCE_TCKER_Msk                    (_UINT32_(0xFF) << GMAC_TCE_TCKER_Pos)               /* (GMAC_TCE) TCP Checksum Errors Mask */
#define GMAC_TCE_TCKER(value)                 (GMAC_TCE_TCKER_Msk & (_UINT32_(value) << GMAC_TCE_TCKER_Pos)) /* Assigment of value for TCKER in the GMAC_TCE register */
#define GMAC_TCE_Msk                          _UINT32_(0x000000FF)                                 /* (GMAC_TCE) Register Mask  */


/* -------- GMAC_UCE : (GMAC Offset: 0x1B0) ( R/ 32) UDP Checksum Errors Register -------- */
#define GMAC_UCE_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_UCE) UDP Checksum Errors Register  Reset Value */

#define GMAC_UCE_UCKER_Pos                    _UINT32_(0)                                          /* (GMAC_UCE) UDP Checksum Errors Position */
#define GMAC_UCE_UCKER_Msk                    (_UINT32_(0xFF) << GMAC_UCE_UCKER_Pos)               /* (GMAC_UCE) UDP Checksum Errors Mask */
#define GMAC_UCE_UCKER(value)                 (GMAC_UCE_UCKER_Msk & (_UINT32_(value) << GMAC_UCE_UCKER_Pos)) /* Assigment of value for UCKER in the GMAC_UCE register */
#define GMAC_UCE_Msk                          _UINT32_(0x000000FF)                                 /* (GMAC_UCE) Register Mask  */


/* -------- GMAC_FLRXPCR : (GMAC Offset: 0x1B4) ( R/ 32) Flushed Received Packets Counter Register -------- */
#define GMAC_FLRXPCR_RESETVALUE               _UINT32_(0x00)                                       /*  (GMAC_FLRXPCR) Flushed Received Packets Counter Register  Reset Value */

#define GMAC_FLRXPCR_COUNT_Pos                _UINT32_(0)                                          /* (GMAC_FLRXPCR) Flushed Received Packets Count (cleared on read) Position */
#define GMAC_FLRXPCR_COUNT_Msk                (_UINT32_(0xFFFF) << GMAC_FLRXPCR_COUNT_Pos)         /* (GMAC_FLRXPCR) Flushed Received Packets Count (cleared on read) Mask */
#define GMAC_FLRXPCR_COUNT(value)             (GMAC_FLRXPCR_COUNT_Msk & (_UINT32_(value) << GMAC_FLRXPCR_COUNT_Pos)) /* Assigment of value for COUNT in the GMAC_FLRXPCR register */
#define GMAC_FLRXPCR_Msk                      _UINT32_(0x0000FFFF)                                 /* (GMAC_FLRXPCR) Register Mask  */


/* -------- GMAC_TISUBN : (GMAC Offset: 0x1BC) (R/W 32) 1588 Timer Increment Sub-nanoseconds Register -------- */
#define GMAC_TISUBN_RESETVALUE                _UINT32_(0x00)                                       /*  (GMAC_TISUBN) 1588 Timer Increment Sub-nanoseconds Register  Reset Value */

#define GMAC_TISUBN_MSBTIR_Pos                _UINT32_(0)                                          /* (GMAC_TISUBN) Most Significant Bits of Timer Increment Register Position */
#define GMAC_TISUBN_MSBTIR_Msk                (_UINT32_(0xFFFF) << GMAC_TISUBN_MSBTIR_Pos)         /* (GMAC_TISUBN) Most Significant Bits of Timer Increment Register Mask */
#define GMAC_TISUBN_MSBTIR(value)             (GMAC_TISUBN_MSBTIR_Msk & (_UINT32_(value) << GMAC_TISUBN_MSBTIR_Pos)) /* Assigment of value for MSBTIR in the GMAC_TISUBN register */
#define GMAC_TISUBN_LSBTIR_Pos                _UINT32_(24)                                         /* (GMAC_TISUBN) Lower Significant Bits of Timer Increment Register Position */
#define GMAC_TISUBN_LSBTIR_Msk                (_UINT32_(0xFF) << GMAC_TISUBN_LSBTIR_Pos)           /* (GMAC_TISUBN) Lower Significant Bits of Timer Increment Register Mask */
#define GMAC_TISUBN_LSBTIR(value)             (GMAC_TISUBN_LSBTIR_Msk & (_UINT32_(value) << GMAC_TISUBN_LSBTIR_Pos)) /* Assigment of value for LSBTIR in the GMAC_TISUBN register */
#define GMAC_TISUBN_Msk                       _UINT32_(0xFF00FFFF)                                 /* (GMAC_TISUBN) Register Mask  */


/* -------- GMAC_TSH : (GMAC Offset: 0x1C0) (R/W 32) 1588 Timer Seconds High Register -------- */
#define GMAC_TSH_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_TSH) 1588 Timer Seconds High Register  Reset Value */

#define GMAC_TSH_TCS_Pos                      _UINT32_(0)                                          /* (GMAC_TSH) Timer Count in Seconds Position */
#define GMAC_TSH_TCS_Msk                      (_UINT32_(0xFFFF) << GMAC_TSH_TCS_Pos)               /* (GMAC_TSH) Timer Count in Seconds Mask */
#define GMAC_TSH_TCS(value)                   (GMAC_TSH_TCS_Msk & (_UINT32_(value) << GMAC_TSH_TCS_Pos)) /* Assigment of value for TCS in the GMAC_TSH register */
#define GMAC_TSH_Msk                          _UINT32_(0x0000FFFF)                                 /* (GMAC_TSH) Register Mask  */


/* -------- GMAC_TSL : (GMAC Offset: 0x1D0) (R/W 32) 1588 Timer Seconds Low Register -------- */
#define GMAC_TSL_RESETVALUE                   _UINT32_(0x00)                                       /*  (GMAC_TSL) 1588 Timer Seconds Low Register  Reset Value */

#define GMAC_TSL_TCS_Pos                      _UINT32_(0)                                          /* (GMAC_TSL) Timer Count in Seconds Position */
#define GMAC_TSL_TCS_Msk                      (_UINT32_(0xFFFFFFFF) << GMAC_TSL_TCS_Pos)           /* (GMAC_TSL) Timer Count in Seconds Mask */
#define GMAC_TSL_TCS(value)                   (GMAC_TSL_TCS_Msk & (_UINT32_(value) << GMAC_TSL_TCS_Pos)) /* Assigment of value for TCS in the GMAC_TSL register */
#define GMAC_TSL_Msk                          _UINT32_(0xFFFFFFFF)                                 /* (GMAC_TSL) Register Mask  */


/* -------- GMAC_TN : (GMAC Offset: 0x1D4) (R/W 32) 1588 Timer Nanoseconds Register -------- */
#define GMAC_TN_RESETVALUE                    _UINT32_(0x00)                                       /*  (GMAC_TN) 1588 Timer Nanoseconds Register  Reset Value */

#define GMAC_TN_TNS_Pos                       _UINT32_(0)                                          /* (GMAC_TN) Timer Count in Nanoseconds Position */
#define GMAC_TN_TNS_Msk                       (_UINT32_(0x3FFFFFFF) << GMAC_TN_TNS_Pos)            /* (GMAC_TN) Timer Count in Nanoseconds Mask */
#define GMAC_TN_TNS(value)                    (GMAC_TN_TNS_Msk & (_UINT32_(value) << GMAC_TN_TNS_Pos)) /* Assigment of value for TNS in the GMAC_TN register */
#define GMAC_TN_Msk                           _UINT32_(0x3FFFFFFF)                                 /* (GMAC_TN) Register Mask  */


/* -------- GMAC_TA : (GMAC Offset: 0x1D8) ( /W 32) 1588 Timer Adjust Register -------- */
#define GMAC_TA_ITDT_Pos                      _UINT32_(0)                                          /* (GMAC_TA) Increment/Decrement Position */
#define GMAC_TA_ITDT_Msk                      (_UINT32_(0x3FFFFFFF) << GMAC_TA_ITDT_Pos)           /* (GMAC_TA) Increment/Decrement Mask */
#define GMAC_TA_ITDT(value)                   (GMAC_TA_ITDT_Msk & (_UINT32_(value) << GMAC_TA_ITDT_Pos)) /* Assigment of value for ITDT in the GMAC_TA register */
#define GMAC_TA_ADJ_Pos                       _UINT32_(31)                                         /* (GMAC_TA) Adjust 1588 Timer Position */
#define GMAC_TA_ADJ_Msk                       (_UINT32_(0x1) << GMAC_TA_ADJ_Pos)                   /* (GMAC_TA) Adjust 1588 Timer Mask */
#define GMAC_TA_ADJ(value)                    (GMAC_TA_ADJ_Msk & (_UINT32_(value) << GMAC_TA_ADJ_Pos)) /* Assigment of value for ADJ in the GMAC_TA register */
#define GMAC_TA_Msk                           _UINT32_(0xBFFFFFFF)                                 /* (GMAC_TA) Register Mask  */


/* -------- GMAC_TI : (GMAC Offset: 0x1DC) (R/W 32) 1588 Timer Increment Register -------- */
#define GMAC_TI_RESETVALUE                    _UINT32_(0x00)                                       /*  (GMAC_TI) 1588 Timer Increment Register  Reset Value */

#define GMAC_TI_CNS_Pos                       _UINT32_(0)                                          /* (GMAC_TI) Count Nanoseconds Position */
#define GMAC_TI_CNS_Msk                       (_UINT32_(0xFF) << GMAC_TI_CNS_Pos)                  /* (GMAC_TI) Count Nanoseconds Mask */
#define GMAC_TI_CNS(value)                    (GMAC_TI_CNS_Msk & (_UINT32_(value) << GMAC_TI_CNS_Pos)) /* Assigment of value for CNS in the GMAC_TI register */
#define GMAC_TI_ACNS_Pos                      _UINT32_(8)                                          /* (GMAC_TI) Alternative Count Nanoseconds Position */
#define GMAC_TI_ACNS_Msk                      (_UINT32_(0xFF) << GMAC_TI_ACNS_Pos)                 /* (GMAC_TI) Alternative Count Nanoseconds Mask */
#define GMAC_TI_ACNS(value)                   (GMAC_TI_ACNS_Msk & (_UINT32_(value) << GMAC_TI_ACNS_Pos)) /* Assigment of value for ACNS in the GMAC_TI register */
#define GMAC_TI_NIT_Pos                       _UINT32_(16)                                         /* (GMAC_TI) Number of Increments Position */
#define GMAC_TI_NIT_Msk                       (_UINT32_(0xFF) << GMAC_TI_NIT_Pos)                  /* (GMAC_TI) Number of Increments Mask */
#define GMAC_TI_NIT(value)                    (GMAC_TI_NIT_Msk & (_UINT32_(value) << GMAC_TI_NIT_Pos)) /* Assigment of value for NIT in the GMAC_TI register */
#define GMAC_TI_Msk                           _UINT32_(0x00FFFFFF)                                 /* (GMAC_TI) Register Mask  */


/* -------- GMAC_EFTSL : (GMAC Offset: 0x1E0) ( R/ 32) PTP Event Frame Transmitted Seconds Low Register -------- */
#define GMAC_EFTSL_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_EFTSL) PTP Event Frame Transmitted Seconds Low Register  Reset Value */

#define GMAC_EFTSL_RUD_Pos                    _UINT32_(0)                                          /* (GMAC_EFTSL) Register Update Position */
#define GMAC_EFTSL_RUD_Msk                    (_UINT32_(0xFFFFFFFF) << GMAC_EFTSL_RUD_Pos)         /* (GMAC_EFTSL) Register Update Mask */
#define GMAC_EFTSL_RUD(value)                 (GMAC_EFTSL_RUD_Msk & (_UINT32_(value) << GMAC_EFTSL_RUD_Pos)) /* Assigment of value for RUD in the GMAC_EFTSL register */
#define GMAC_EFTSL_Msk                        _UINT32_(0xFFFFFFFF)                                 /* (GMAC_EFTSL) Register Mask  */


/* -------- GMAC_EFTN : (GMAC Offset: 0x1E4) ( R/ 32) PTP Event Frame Transmitted Nanoseconds Register -------- */
#define GMAC_EFTN_RESETVALUE                  _UINT32_(0x00)                                       /*  (GMAC_EFTN) PTP Event Frame Transmitted Nanoseconds Register  Reset Value */

#define GMAC_EFTN_RUD_Pos                     _UINT32_(0)                                          /* (GMAC_EFTN) Register Update Position */
#define GMAC_EFTN_RUD_Msk                     (_UINT32_(0x3FFFFFFF) << GMAC_EFTN_RUD_Pos)          /* (GMAC_EFTN) Register Update Mask */
#define GMAC_EFTN_RUD(value)                  (GMAC_EFTN_RUD_Msk & (_UINT32_(value) << GMAC_EFTN_RUD_Pos)) /* Assigment of value for RUD in the GMAC_EFTN register */
#define GMAC_EFTN_Msk                         _UINT32_(0x3FFFFFFF)                                 /* (GMAC_EFTN) Register Mask  */


/* -------- GMAC_EFRSL : (GMAC Offset: 0x1E8) ( R/ 32) PTP Event Frame Received Seconds Low Register -------- */
#define GMAC_EFRSL_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_EFRSL) PTP Event Frame Received Seconds Low Register  Reset Value */

#define GMAC_EFRSL_RUD_Pos                    _UINT32_(0)                                          /* (GMAC_EFRSL) Register Update Position */
#define GMAC_EFRSL_RUD_Msk                    (_UINT32_(0xFFFFFFFF) << GMAC_EFRSL_RUD_Pos)         /* (GMAC_EFRSL) Register Update Mask */
#define GMAC_EFRSL_RUD(value)                 (GMAC_EFRSL_RUD_Msk & (_UINT32_(value) << GMAC_EFRSL_RUD_Pos)) /* Assigment of value for RUD in the GMAC_EFRSL register */
#define GMAC_EFRSL_Msk                        _UINT32_(0xFFFFFFFF)                                 /* (GMAC_EFRSL) Register Mask  */


/* -------- GMAC_EFRN : (GMAC Offset: 0x1EC) ( R/ 32) PTP Event Frame Received Nanoseconds Register -------- */
#define GMAC_EFRN_RESETVALUE                  _UINT32_(0x00)                                       /*  (GMAC_EFRN) PTP Event Frame Received Nanoseconds Register  Reset Value */

#define GMAC_EFRN_RUD_Pos                     _UINT32_(0)                                          /* (GMAC_EFRN) Register Update Position */
#define GMAC_EFRN_RUD_Msk                     (_UINT32_(0x3FFFFFFF) << GMAC_EFRN_RUD_Pos)          /* (GMAC_EFRN) Register Update Mask */
#define GMAC_EFRN_RUD(value)                  (GMAC_EFRN_RUD_Msk & (_UINT32_(value) << GMAC_EFRN_RUD_Pos)) /* Assigment of value for RUD in the GMAC_EFRN register */
#define GMAC_EFRN_Msk                         _UINT32_(0x3FFFFFFF)                                 /* (GMAC_EFRN) Register Mask  */


/* -------- GMAC_PEFTSL : (GMAC Offset: 0x1F0) ( R/ 32) PTP Peer Event Frame Transmitted Seconds Low Register -------- */
#define GMAC_PEFTSL_RESETVALUE                _UINT32_(0x00)                                       /*  (GMAC_PEFTSL) PTP Peer Event Frame Transmitted Seconds Low Register  Reset Value */

#define GMAC_PEFTSL_RUD_Pos                   _UINT32_(0)                                          /* (GMAC_PEFTSL) Register Update Position */
#define GMAC_PEFTSL_RUD_Msk                   (_UINT32_(0xFFFFFFFF) << GMAC_PEFTSL_RUD_Pos)        /* (GMAC_PEFTSL) Register Update Mask */
#define GMAC_PEFTSL_RUD(value)                (GMAC_PEFTSL_RUD_Msk & (_UINT32_(value) << GMAC_PEFTSL_RUD_Pos)) /* Assigment of value for RUD in the GMAC_PEFTSL register */
#define GMAC_PEFTSL_Msk                       _UINT32_(0xFFFFFFFF)                                 /* (GMAC_PEFTSL) Register Mask  */


/* -------- GMAC_PEFTN : (GMAC Offset: 0x1F4) ( R/ 32) PTP Peer Event Frame Transmitted Nanoseconds Register -------- */
#define GMAC_PEFTN_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_PEFTN) PTP Peer Event Frame Transmitted Nanoseconds Register  Reset Value */

#define GMAC_PEFTN_RUD_Pos                    _UINT32_(0)                                          /* (GMAC_PEFTN) Register Update Position */
#define GMAC_PEFTN_RUD_Msk                    (_UINT32_(0x3FFFFFFF) << GMAC_PEFTN_RUD_Pos)         /* (GMAC_PEFTN) Register Update Mask */
#define GMAC_PEFTN_RUD(value)                 (GMAC_PEFTN_RUD_Msk & (_UINT32_(value) << GMAC_PEFTN_RUD_Pos)) /* Assigment of value for RUD in the GMAC_PEFTN register */
#define GMAC_PEFTN_Msk                        _UINT32_(0x3FFFFFFF)                                 /* (GMAC_PEFTN) Register Mask  */


/* -------- GMAC_PEFRSL : (GMAC Offset: 0x1F8) ( R/ 32) PTP Peer Event Frame Received Seconds Low Register -------- */
#define GMAC_PEFRSL_RESETVALUE                _UINT32_(0x00)                                       /*  (GMAC_PEFRSL) PTP Peer Event Frame Received Seconds Low Register  Reset Value */

#define GMAC_PEFRSL_RUD_Pos                   _UINT32_(0)                                          /* (GMAC_PEFRSL) Register Update Position */
#define GMAC_PEFRSL_RUD_Msk                   (_UINT32_(0xFFFFFFFF) << GMAC_PEFRSL_RUD_Pos)        /* (GMAC_PEFRSL) Register Update Mask */
#define GMAC_PEFRSL_RUD(value)                (GMAC_PEFRSL_RUD_Msk & (_UINT32_(value) << GMAC_PEFRSL_RUD_Pos)) /* Assigment of value for RUD in the GMAC_PEFRSL register */
#define GMAC_PEFRSL_Msk                       _UINT32_(0xFFFFFFFF)                                 /* (GMAC_PEFRSL) Register Mask  */


/* -------- GMAC_PEFRN : (GMAC Offset: 0x1FC) ( R/ 32) PTP Peer Event Frame Received Nanoseconds Register -------- */
#define GMAC_PEFRN_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_PEFRN) PTP Peer Event Frame Received Nanoseconds Register  Reset Value */

#define GMAC_PEFRN_RUD_Pos                    _UINT32_(0)                                          /* (GMAC_PEFRN) Register Update Position */
#define GMAC_PEFRN_RUD_Msk                    (_UINT32_(0x3FFFFFFF) << GMAC_PEFRN_RUD_Pos)         /* (GMAC_PEFRN) Register Update Mask */
#define GMAC_PEFRN_RUD(value)                 (GMAC_PEFRN_RUD_Msk & (_UINT32_(value) << GMAC_PEFRN_RUD_Pos)) /* Assigment of value for RUD in the GMAC_PEFRN register */
#define GMAC_PEFRN_Msk                        _UINT32_(0x3FFFFFFF)                                 /* (GMAC_PEFRN) Register Mask  */


/* -------- GMAC_RXLPI : (GMAC Offset: 0x270) ( R/ 32) Received LPI Transitions -------- */
#define GMAC_RXLPI_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_RXLPI) Received LPI Transitions  Reset Value */

#define GMAC_RXLPI_COUNT_Pos                  _UINT32_(0)                                          /* (GMAC_RXLPI) Count of Received LPI transitions (cleared on read) Position */
#define GMAC_RXLPI_COUNT_Msk                  (_UINT32_(0xFFFF) << GMAC_RXLPI_COUNT_Pos)           /* (GMAC_RXLPI) Count of Received LPI transitions (cleared on read) Mask */
#define GMAC_RXLPI_COUNT(value)               (GMAC_RXLPI_COUNT_Msk & (_UINT32_(value) << GMAC_RXLPI_COUNT_Pos)) /* Assigment of value for COUNT in the GMAC_RXLPI register */
#define GMAC_RXLPI_Msk                        _UINT32_(0x0000FFFF)                                 /* (GMAC_RXLPI) Register Mask  */


/* -------- GMAC_RXLPITIME : (GMAC Offset: 0x274) ( R/ 32) Received LPI Time -------- */
#define GMAC_RXLPITIME_RESETVALUE             _UINT32_(0x00)                                       /*  (GMAC_RXLPITIME) Received LPI Time  Reset Value */

#define GMAC_RXLPITIME_LPITIME_Pos            _UINT32_(0)                                          /* (GMAC_RXLPITIME) Time in LPI (cleared on read) Position */
#define GMAC_RXLPITIME_LPITIME_Msk            (_UINT32_(0xFFFFFF) << GMAC_RXLPITIME_LPITIME_Pos)   /* (GMAC_RXLPITIME) Time in LPI (cleared on read) Mask */
#define GMAC_RXLPITIME_LPITIME(value)         (GMAC_RXLPITIME_LPITIME_Msk & (_UINT32_(value) << GMAC_RXLPITIME_LPITIME_Pos)) /* Assigment of value for LPITIME in the GMAC_RXLPITIME register */
#define GMAC_RXLPITIME_Msk                    _UINT32_(0x00FFFFFF)                                 /* (GMAC_RXLPITIME) Register Mask  */


/* -------- GMAC_TXLPI : (GMAC Offset: 0x278) ( R/ 32) Transmit LPI Transitions -------- */
#define GMAC_TXLPI_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_TXLPI) Transmit LPI Transitions  Reset Value */

#define GMAC_TXLPI_COUNT_Pos                  _UINT32_(0)                                          /* (GMAC_TXLPI) Count of LPI transitions (cleared on read) Position */
#define GMAC_TXLPI_COUNT_Msk                  (_UINT32_(0xFFFF) << GMAC_TXLPI_COUNT_Pos)           /* (GMAC_TXLPI) Count of LPI transitions (cleared on read) Mask */
#define GMAC_TXLPI_COUNT(value)               (GMAC_TXLPI_COUNT_Msk & (_UINT32_(value) << GMAC_TXLPI_COUNT_Pos)) /* Assigment of value for COUNT in the GMAC_TXLPI register */
#define GMAC_TXLPI_Msk                        _UINT32_(0x0000FFFF)                                 /* (GMAC_TXLPI) Register Mask  */


/* -------- GMAC_TXLPITIME : (GMAC Offset: 0x27C) ( R/ 32) Transmit LPI Time -------- */
#define GMAC_TXLPITIME_RESETVALUE             _UINT32_(0x00)                                       /*  (GMAC_TXLPITIME) Transmit LPI Time  Reset Value */

#define GMAC_TXLPITIME_LPITIME_Pos            _UINT32_(0)                                          /* (GMAC_TXLPITIME) Time in LPI (cleared on read) Position */
#define GMAC_TXLPITIME_LPITIME_Msk            (_UINT32_(0xFFFFFF) << GMAC_TXLPITIME_LPITIME_Pos)   /* (GMAC_TXLPITIME) Time in LPI (cleared on read) Mask */
#define GMAC_TXLPITIME_LPITIME(value)         (GMAC_TXLPITIME_LPITIME_Msk & (_UINT32_(value) << GMAC_TXLPITIME_LPITIME_Pos)) /* Assigment of value for LPITIME in the GMAC_TXLPITIME register */
#define GMAC_TXLPITIME_Msk                    _UINT32_(0x00FFFFFF)                                 /* (GMAC_TXLPITIME) Register Mask  */


/* -------- GMAC_ISRPQ : (GMAC Offset: 0x400) ( R/ 32) Interrupt Status Register Priority Queue (index = 1) -------- */
#define GMAC_ISRPQ_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_ISRPQ) Interrupt Status Register Priority Queue (index = 1)  Reset Value */

#define GMAC_ISRPQ_RCOMP_Pos                  _UINT32_(1)                                          /* (GMAC_ISRPQ) Receive Complete Position */
#define GMAC_ISRPQ_RCOMP_Msk                  (_UINT32_(0x1) << GMAC_ISRPQ_RCOMP_Pos)              /* (GMAC_ISRPQ) Receive Complete Mask */
#define GMAC_ISRPQ_RCOMP(value)               (GMAC_ISRPQ_RCOMP_Msk & (_UINT32_(value) << GMAC_ISRPQ_RCOMP_Pos)) /* Assigment of value for RCOMP in the GMAC_ISRPQ register */
#define GMAC_ISRPQ_RXUBR_Pos                  _UINT32_(2)                                          /* (GMAC_ISRPQ) RX Used Bit Read Position */
#define GMAC_ISRPQ_RXUBR_Msk                  (_UINT32_(0x1) << GMAC_ISRPQ_RXUBR_Pos)              /* (GMAC_ISRPQ) RX Used Bit Read Mask */
#define GMAC_ISRPQ_RXUBR(value)               (GMAC_ISRPQ_RXUBR_Msk & (_UINT32_(value) << GMAC_ISRPQ_RXUBR_Pos)) /* Assigment of value for RXUBR in the GMAC_ISRPQ register */
#define GMAC_ISRPQ_RLEX_Pos                   _UINT32_(5)                                          /* (GMAC_ISRPQ) Retry Limit Exceeded or Late Collision Position */
#define GMAC_ISRPQ_RLEX_Msk                   (_UINT32_(0x1) << GMAC_ISRPQ_RLEX_Pos)               /* (GMAC_ISRPQ) Retry Limit Exceeded or Late Collision Mask */
#define GMAC_ISRPQ_RLEX(value)                (GMAC_ISRPQ_RLEX_Msk & (_UINT32_(value) << GMAC_ISRPQ_RLEX_Pos)) /* Assigment of value for RLEX in the GMAC_ISRPQ register */
#define GMAC_ISRPQ_TFC_Pos                    _UINT32_(6)                                          /* (GMAC_ISRPQ) Transmit Frame Corruption Due to System Bus Error Position */
#define GMAC_ISRPQ_TFC_Msk                    (_UINT32_(0x1) << GMAC_ISRPQ_TFC_Pos)                /* (GMAC_ISRPQ) Transmit Frame Corruption Due to System Bus Error Mask */
#define GMAC_ISRPQ_TFC(value)                 (GMAC_ISRPQ_TFC_Msk & (_UINT32_(value) << GMAC_ISRPQ_TFC_Pos)) /* Assigment of value for TFC in the GMAC_ISRPQ register */
#define GMAC_ISRPQ_TCOMP_Pos                  _UINT32_(7)                                          /* (GMAC_ISRPQ) Transmit Complete Position */
#define GMAC_ISRPQ_TCOMP_Msk                  (_UINT32_(0x1) << GMAC_ISRPQ_TCOMP_Pos)              /* (GMAC_ISRPQ) Transmit Complete Mask */
#define GMAC_ISRPQ_TCOMP(value)               (GMAC_ISRPQ_TCOMP_Msk & (_UINT32_(value) << GMAC_ISRPQ_TCOMP_Pos)) /* Assigment of value for TCOMP in the GMAC_ISRPQ register */
#define GMAC_ISRPQ_HRESP_Pos                  _UINT32_(11)                                         /* (GMAC_ISRPQ) System Bus Error Position */
#define GMAC_ISRPQ_HRESP_Msk                  (_UINT32_(0x1) << GMAC_ISRPQ_HRESP_Pos)              /* (GMAC_ISRPQ) System Bus Error Mask */
#define GMAC_ISRPQ_HRESP(value)               (GMAC_ISRPQ_HRESP_Msk & (_UINT32_(value) << GMAC_ISRPQ_HRESP_Pos)) /* Assigment of value for HRESP in the GMAC_ISRPQ register */
#define GMAC_ISRPQ_Msk                        _UINT32_(0x000008E6)                                 /* (GMAC_ISRPQ) Register Mask  */


/* -------- GMAC_TBQBAPQ : (GMAC Offset: 0x440) (R/W 32) Transmit Buffer Queue Base Address Register Priority Queue (index = 1) -------- */
#define GMAC_TBQBAPQ_RESETVALUE               _UINT32_(0x00)                                       /*  (GMAC_TBQBAPQ) Transmit Buffer Queue Base Address Register Priority Queue (index = 1)  Reset Value */

#define GMAC_TBQBAPQ_TXBQBA_Pos               _UINT32_(2)                                          /* (GMAC_TBQBAPQ) Transmit Buffer Queue Base Address Position */
#define GMAC_TBQBAPQ_TXBQBA_Msk               (_UINT32_(0x3FFFFFFF) << GMAC_TBQBAPQ_TXBQBA_Pos)    /* (GMAC_TBQBAPQ) Transmit Buffer Queue Base Address Mask */
#define GMAC_TBQBAPQ_TXBQBA(value)            (GMAC_TBQBAPQ_TXBQBA_Msk & (_UINT32_(value) << GMAC_TBQBAPQ_TXBQBA_Pos)) /* Assigment of value for TXBQBA in the GMAC_TBQBAPQ register */
#define GMAC_TBQBAPQ_Msk                      _UINT32_(0xFFFFFFFC)                                 /* (GMAC_TBQBAPQ) Register Mask  */


/* -------- GMAC_RBQBAPQ : (GMAC Offset: 0x480) (R/W 32) Receive Buffer Queue Base Address Register Priority Queue (index = 1) -------- */
#define GMAC_RBQBAPQ_RESETVALUE               _UINT32_(0x00)                                       /*  (GMAC_RBQBAPQ) Receive Buffer Queue Base Address Register Priority Queue (index = 1)  Reset Value */

#define GMAC_RBQBAPQ_RXBQBA_Pos               _UINT32_(2)                                          /* (GMAC_RBQBAPQ) Receive Buffer Queue Base Address Position */
#define GMAC_RBQBAPQ_RXBQBA_Msk               (_UINT32_(0x3FFFFFFF) << GMAC_RBQBAPQ_RXBQBA_Pos)    /* (GMAC_RBQBAPQ) Receive Buffer Queue Base Address Mask */
#define GMAC_RBQBAPQ_RXBQBA(value)            (GMAC_RBQBAPQ_RXBQBA_Msk & (_UINT32_(value) << GMAC_RBQBAPQ_RXBQBA_Pos)) /* Assigment of value for RXBQBA in the GMAC_RBQBAPQ register */
#define GMAC_RBQBAPQ_Msk                      _UINT32_(0xFFFFFFFC)                                 /* (GMAC_RBQBAPQ) Register Mask  */


/* -------- GMAC_RBSRPQ : (GMAC Offset: 0x4A0) (R/W 32) Receive Buffer Size Register Priority Queue (index = 1) -------- */
#define GMAC_RBSRPQ_RESETVALUE                _UINT32_(0x02)                                       /*  (GMAC_RBSRPQ) Receive Buffer Size Register Priority Queue (index = 1)  Reset Value */

#define GMAC_RBSRPQ_RBS_Pos                   _UINT32_(0)                                          /* (GMAC_RBSRPQ) Receive Buffer Size Position */
#define GMAC_RBSRPQ_RBS_Msk                   (_UINT32_(0xFF) << GMAC_RBSRPQ_RBS_Pos)              /* (GMAC_RBSRPQ) Receive Buffer Size Mask */
#define GMAC_RBSRPQ_RBS(value)                (GMAC_RBSRPQ_RBS_Msk & (_UINT32_(value) << GMAC_RBSRPQ_RBS_Pos)) /* Assigment of value for RBS in the GMAC_RBSRPQ register */
#define   GMAC_RBSRPQ_RBS_0x02_Val            _UINT32_(0x2)                                        /* (GMAC_RBSRPQ) 128 bytes  */
#define   GMAC_RBSRPQ_RBS_0x18_Val            _UINT32_(0x18)                                       /* (GMAC_RBSRPQ) 1536 bytes (1 x max length frame/buffer)  */
#define   GMAC_RBSRPQ_RBS_0xA0_Val            _UINT32_(0xA0)                                       /* (GMAC_RBSRPQ) 10240 bytes (1 x 10K jumbo frame/buffer)  */
#define GMAC_RBSRPQ_RBS_0x02                  (GMAC_RBSRPQ_RBS_0x02_Val << GMAC_RBSRPQ_RBS_Pos)    /* (GMAC_RBSRPQ) 128 bytes Position  */
#define GMAC_RBSRPQ_RBS_0x18                  (GMAC_RBSRPQ_RBS_0x18_Val << GMAC_RBSRPQ_RBS_Pos)    /* (GMAC_RBSRPQ) 1536 bytes (1 x max length frame/buffer) Position  */
#define GMAC_RBSRPQ_RBS_0xA0                  (GMAC_RBSRPQ_RBS_0xA0_Val << GMAC_RBSRPQ_RBS_Pos)    /* (GMAC_RBSRPQ) 10240 bytes (1 x 10K jumbo frame/buffer) Position  */
#define GMAC_RBSRPQ_Msk                       _UINT32_(0x000000FF)                                 /* (GMAC_RBSRPQ) Register Mask  */


/* -------- GMAC_CBSCR : (GMAC Offset: 0x4BC) (R/W 32) Credit-Based Shaping Control Register -------- */
#define GMAC_CBSCR_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_CBSCR) Credit-Based Shaping Control Register  Reset Value */

#define GMAC_CBSCR_QAE_Pos                    _UINT32_(0)                                          /* (GMAC_CBSCR) Queue A CBS Enable Position */
#define GMAC_CBSCR_QAE_Msk                    (_UINT32_(0x1) << GMAC_CBSCR_QAE_Pos)                /* (GMAC_CBSCR) Queue A CBS Enable Mask */
#define GMAC_CBSCR_QAE(value)                 (GMAC_CBSCR_QAE_Msk & (_UINT32_(value) << GMAC_CBSCR_QAE_Pos)) /* Assigment of value for QAE in the GMAC_CBSCR register */
#define   GMAC_CBSCR_QAE_0_Val                _UINT32_(0x0)                                        /* (GMAC_CBSCR) Credit-based shaping on the second highest priority queue (queue A) is disabled.  */
#define   GMAC_CBSCR_QAE_1_Val                _UINT32_(0x1)                                        /* (GMAC_CBSCR) Credit-based shaping on the second highest priority queue (queue A) is enabled.  */
#define GMAC_CBSCR_QAE_0                      (GMAC_CBSCR_QAE_0_Val << GMAC_CBSCR_QAE_Pos)         /* (GMAC_CBSCR) Credit-based shaping on the second highest priority queue (queue A) is disabled. Position  */
#define GMAC_CBSCR_QAE_1                      (GMAC_CBSCR_QAE_1_Val << GMAC_CBSCR_QAE_Pos)         /* (GMAC_CBSCR) Credit-based shaping on the second highest priority queue (queue A) is enabled. Position  */
#define GMAC_CBSCR_QBE_Pos                    _UINT32_(1)                                          /* (GMAC_CBSCR) Queue B CBS Enable Position */
#define GMAC_CBSCR_QBE_Msk                    (_UINT32_(0x1) << GMAC_CBSCR_QBE_Pos)                /* (GMAC_CBSCR) Queue B CBS Enable Mask */
#define GMAC_CBSCR_QBE(value)                 (GMAC_CBSCR_QBE_Msk & (_UINT32_(value) << GMAC_CBSCR_QBE_Pos)) /* Assigment of value for QBE in the GMAC_CBSCR register */
#define   GMAC_CBSCR_QBE_0_Val                _UINT32_(0x0)                                        /* (GMAC_CBSCR) Credit-based shaping on the highest priority queue (queue B) is disabled.  */
#define   GMAC_CBSCR_QBE_1_Val                _UINT32_(0x1)                                        /* (GMAC_CBSCR) Credit-based shaping on the highest priority queue (queue B) is enabled.  */
#define GMAC_CBSCR_QBE_0                      (GMAC_CBSCR_QBE_0_Val << GMAC_CBSCR_QBE_Pos)         /* (GMAC_CBSCR) Credit-based shaping on the highest priority queue (queue B) is disabled. Position  */
#define GMAC_CBSCR_QBE_1                      (GMAC_CBSCR_QBE_1_Val << GMAC_CBSCR_QBE_Pos)         /* (GMAC_CBSCR) Credit-based shaping on the highest priority queue (queue B) is enabled. Position  */
#define GMAC_CBSCR_Msk                        _UINT32_(0x00000003)                                 /* (GMAC_CBSCR) Register Mask  */


/* -------- GMAC_CBSISQA : (GMAC Offset: 0x4C0) (R/W 32) Credit-Based Shaping IdleSlope Register for Queue A -------- */
#define GMAC_CBSISQA_RESETVALUE               _UINT32_(0x00)                                       /*  (GMAC_CBSISQA) Credit-Based Shaping IdleSlope Register for Queue A  Reset Value */

#define GMAC_CBSISQA_IS_Pos                   _UINT32_(0)                                          /* (GMAC_CBSISQA) IdleSlope Position */
#define GMAC_CBSISQA_IS_Msk                   (_UINT32_(0xFFFFFFFF) << GMAC_CBSISQA_IS_Pos)        /* (GMAC_CBSISQA) IdleSlope Mask */
#define GMAC_CBSISQA_IS(value)                (GMAC_CBSISQA_IS_Msk & (_UINT32_(value) << GMAC_CBSISQA_IS_Pos)) /* Assigment of value for IS in the GMAC_CBSISQA register */
#define GMAC_CBSISQA_Msk                      _UINT32_(0xFFFFFFFF)                                 /* (GMAC_CBSISQA) Register Mask  */


/* -------- GMAC_CBSISQB : (GMAC Offset: 0x4C4) (R/W 32) Credit-Based Shaping IdleSlope Register for Queue B -------- */
#define GMAC_CBSISQB_RESETVALUE               _UINT32_(0x00)                                       /*  (GMAC_CBSISQB) Credit-Based Shaping IdleSlope Register for Queue B  Reset Value */

#define GMAC_CBSISQB_IS_Pos                   _UINT32_(0)                                          /* (GMAC_CBSISQB) IdleSlope Position */
#define GMAC_CBSISQB_IS_Msk                   (_UINT32_(0xFFFFFFFF) << GMAC_CBSISQB_IS_Pos)        /* (GMAC_CBSISQB) IdleSlope Mask */
#define GMAC_CBSISQB_IS(value)                (GMAC_CBSISQB_IS_Msk & (_UINT32_(value) << GMAC_CBSISQB_IS_Pos)) /* Assigment of value for IS in the GMAC_CBSISQB register */
#define GMAC_CBSISQB_Msk                      _UINT32_(0xFFFFFFFF)                                 /* (GMAC_CBSISQB) Register Mask  */


/* -------- GMAC_TQUBA : (GMAC Offset: 0x4C8) (R/W 32) 32 MSB Transmit Buffer Descriptor Queue Base Address Register -------- */
#define GMAC_TQUBA_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_TQUBA) 32 MSB Transmit Buffer Descriptor Queue Base Address Register  Reset Value */

#define GMAC_TQUBA_TQUBA_Pos                  _UINT32_(0)                                          /* (GMAC_TQUBA) Transmit Queue Upper Buffer Address Position */
#define GMAC_TQUBA_TQUBA_Msk                  (_UINT32_(0xFFFFFFFF) << GMAC_TQUBA_TQUBA_Pos)       /* (GMAC_TQUBA) Transmit Queue Upper Buffer Address Mask */
#define GMAC_TQUBA_TQUBA(value)               (GMAC_TQUBA_TQUBA_Msk & (_UINT32_(value) << GMAC_TQUBA_TQUBA_Pos)) /* Assigment of value for TQUBA in the GMAC_TQUBA register */
#define GMAC_TQUBA_Msk                        _UINT32_(0xFFFFFFFF)                                 /* (GMAC_TQUBA) Register Mask  */


/* -------- GMAC_TXBDCTRL : (GMAC Offset: 0x4CC) (R/W 32) Transmit Buffer Data Control Register -------- */
#define GMAC_TXBDCTRL_RESETVALUE              _UINT32_(0x00)                                       /*  (GMAC_TXBDCTRL) Transmit Buffer Data Control Register  Reset Value */

#define GMAC_TXBDCTRL_TSMODE_Pos              _UINT32_(4)                                          /* (GMAC_TXBDCTRL) Transmit Descriptor Timestamp Insertion Mode Position */
#define GMAC_TXBDCTRL_TSMODE_Msk              (_UINT32_(0x3) << GMAC_TXBDCTRL_TSMODE_Pos)          /* (GMAC_TXBDCTRL) Transmit Descriptor Timestamp Insertion Mode Mask */
#define GMAC_TXBDCTRL_TSMODE(value)           (GMAC_TXBDCTRL_TSMODE_Msk & (_UINT32_(value) << GMAC_TXBDCTRL_TSMODE_Pos)) /* Assigment of value for TSMODE in the GMAC_TXBDCTRL register */
#define   GMAC_TXBDCTRL_TSMODE_DISABLE_Val    _UINT32_(0x0)                                        /* (GMAC_TXBDCTRL) Timestamp insertion disable.  */
#define   GMAC_TXBDCTRL_TSMODE_PTPEVENT_Val   _UINT32_(0x1)                                        /* (GMAC_TXBDCTRL) Timestamp inserted for PTP Event Frames only.  */
#define   GMAC_TXBDCTRL_TSMODE_PTPALL_Val     _UINT32_(0x2)                                        /* (GMAC_TXBDCTRL) Timestamp inserted for All PTP Frames only.  */
#define   GMAC_TXBDCTRL_TSMODE_ALL_Val        _UINT32_(0x3)                                        /* (GMAC_TXBDCTRL) Timestamp inserted for All Frames.  */
#define GMAC_TXBDCTRL_TSMODE_DISABLE          (GMAC_TXBDCTRL_TSMODE_DISABLE_Val << GMAC_TXBDCTRL_TSMODE_Pos) /* (GMAC_TXBDCTRL) Timestamp insertion disable. Position  */
#define GMAC_TXBDCTRL_TSMODE_PTPEVENT         (GMAC_TXBDCTRL_TSMODE_PTPEVENT_Val << GMAC_TXBDCTRL_TSMODE_Pos) /* (GMAC_TXBDCTRL) Timestamp inserted for PTP Event Frames only. Position  */
#define GMAC_TXBDCTRL_TSMODE_PTPALL           (GMAC_TXBDCTRL_TSMODE_PTPALL_Val << GMAC_TXBDCTRL_TSMODE_Pos) /* (GMAC_TXBDCTRL) Timestamp inserted for All PTP Frames only. Position  */
#define GMAC_TXBDCTRL_TSMODE_ALL              (GMAC_TXBDCTRL_TSMODE_ALL_Val << GMAC_TXBDCTRL_TSMODE_Pos) /* (GMAC_TXBDCTRL) Timestamp inserted for All Frames. Position  */
#define GMAC_TXBDCTRL_Msk                     _UINT32_(0x00000030)                                 /* (GMAC_TXBDCTRL) Register Mask  */


/* -------- GMAC_RXBDCTRL : (GMAC Offset: 0x4D0) (R/W 32) Receive Buffer Data Control Register -------- */
#define GMAC_RXBDCTRL_RESETVALUE              _UINT32_(0x00)                                       /*  (GMAC_RXBDCTRL) Receive Buffer Data Control Register  Reset Value */

#define GMAC_RXBDCTRL_TSMODE_Pos              _UINT32_(4)                                          /* (GMAC_RXBDCTRL) Receive Descriptor Timestamp Insertion Mode Position */
#define GMAC_RXBDCTRL_TSMODE_Msk              (_UINT32_(0x3) << GMAC_RXBDCTRL_TSMODE_Pos)          /* (GMAC_RXBDCTRL) Receive Descriptor Timestamp Insertion Mode Mask */
#define GMAC_RXBDCTRL_TSMODE(value)           (GMAC_RXBDCTRL_TSMODE_Msk & (_UINT32_(value) << GMAC_RXBDCTRL_TSMODE_Pos)) /* Assigment of value for TSMODE in the GMAC_RXBDCTRL register */
#define   GMAC_RXBDCTRL_TSMODE_DISABLE_Val    _UINT32_(0x0)                                        /* (GMAC_RXBDCTRL) Timestamp insertion disable.  */
#define   GMAC_RXBDCTRL_TSMODE_PTPEVENT_Val   _UINT32_(0x1)                                        /* (GMAC_RXBDCTRL) Timestamp inserted for PTP Event Frames only.  */
#define   GMAC_RXBDCTRL_TSMODE_PTPALL_Val     _UINT32_(0x2)                                        /* (GMAC_RXBDCTRL) Timestamp inserted for All PTP Frames only.  */
#define   GMAC_RXBDCTRL_TSMODE_ALL_Val        _UINT32_(0x3)                                        /* (GMAC_RXBDCTRL) Timestamp inserted for All Frames.  */
#define GMAC_RXBDCTRL_TSMODE_DISABLE          (GMAC_RXBDCTRL_TSMODE_DISABLE_Val << GMAC_RXBDCTRL_TSMODE_Pos) /* (GMAC_RXBDCTRL) Timestamp insertion disable. Position  */
#define GMAC_RXBDCTRL_TSMODE_PTPEVENT         (GMAC_RXBDCTRL_TSMODE_PTPEVENT_Val << GMAC_RXBDCTRL_TSMODE_Pos) /* (GMAC_RXBDCTRL) Timestamp inserted for PTP Event Frames only. Position  */
#define GMAC_RXBDCTRL_TSMODE_PTPALL           (GMAC_RXBDCTRL_TSMODE_PTPALL_Val << GMAC_RXBDCTRL_TSMODE_Pos) /* (GMAC_RXBDCTRL) Timestamp inserted for All PTP Frames only. Position  */
#define GMAC_RXBDCTRL_TSMODE_ALL              (GMAC_RXBDCTRL_TSMODE_ALL_Val << GMAC_RXBDCTRL_TSMODE_Pos) /* (GMAC_RXBDCTRL) Timestamp inserted for All Frames. Position  */
#define GMAC_RXBDCTRL_Msk                     _UINT32_(0x00000030)                                 /* (GMAC_RXBDCTRL) Register Mask  */


/* -------- GMAC_RQUBA : (GMAC Offset: 0x4D4) (R/W 32) 32 MSB Receive Buffer Descriptor Queue Base Address Register -------- */
#define GMAC_RQUBA_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_RQUBA) 32 MSB Receive Buffer Descriptor Queue Base Address Register  Reset Value */

#define GMAC_RQUBA_RQUBA_Pos                  _UINT32_(0)                                          /* (GMAC_RQUBA) Receive Queue Upper Buffer Address Position */
#define GMAC_RQUBA_RQUBA_Msk                  (_UINT32_(0xFFFFFFFF) << GMAC_RQUBA_RQUBA_Pos)       /* (GMAC_RQUBA) Receive Queue Upper Buffer Address Mask */
#define GMAC_RQUBA_RQUBA(value)               (GMAC_RQUBA_RQUBA_Msk & (_UINT32_(value) << GMAC_RQUBA_RQUBA_Pos)) /* Assigment of value for RQUBA in the GMAC_RQUBA register */
#define GMAC_RQUBA_Msk                        _UINT32_(0xFFFFFFFF)                                 /* (GMAC_RQUBA) Register Mask  */


/* -------- GMAC_ST1RPQ : (GMAC Offset: 0x500) (R/W 32) Screening Type 1 Register Priority Queue (index = 0) -------- */
#define GMAC_ST1RPQ_RESETVALUE                _UINT32_(0x00)                                       /*  (GMAC_ST1RPQ) Screening Type 1 Register Priority Queue (index = 0)  Reset Value */

#define GMAC_ST1RPQ_QNB_Pos                   _UINT32_(0)                                          /* (GMAC_ST1RPQ) Queue Number (0-2) Position */
#define GMAC_ST1RPQ_QNB_Msk                   (_UINT32_(0x7) << GMAC_ST1RPQ_QNB_Pos)               /* (GMAC_ST1RPQ) Queue Number (0-2) Mask */
#define GMAC_ST1RPQ_QNB(value)                (GMAC_ST1RPQ_QNB_Msk & (_UINT32_(value) << GMAC_ST1RPQ_QNB_Pos)) /* Assigment of value for QNB in the GMAC_ST1RPQ register */
#define GMAC_ST1RPQ_DSTCM_Pos                 _UINT32_(4)                                          /* (GMAC_ST1RPQ) Differentiated Services or Traffic Class Match Position */
#define GMAC_ST1RPQ_DSTCM_Msk                 (_UINT32_(0xFF) << GMAC_ST1RPQ_DSTCM_Pos)            /* (GMAC_ST1RPQ) Differentiated Services or Traffic Class Match Mask */
#define GMAC_ST1RPQ_DSTCM(value)              (GMAC_ST1RPQ_DSTCM_Msk & (_UINT32_(value) << GMAC_ST1RPQ_DSTCM_Pos)) /* Assigment of value for DSTCM in the GMAC_ST1RPQ register */
#define GMAC_ST1RPQ_UDPM_Pos                  _UINT32_(12)                                         /* (GMAC_ST1RPQ) UDP Port Match Position */
#define GMAC_ST1RPQ_UDPM_Msk                  (_UINT32_(0xFFFF) << GMAC_ST1RPQ_UDPM_Pos)           /* (GMAC_ST1RPQ) UDP Port Match Mask */
#define GMAC_ST1RPQ_UDPM(value)               (GMAC_ST1RPQ_UDPM_Msk & (_UINT32_(value) << GMAC_ST1RPQ_UDPM_Pos)) /* Assigment of value for UDPM in the GMAC_ST1RPQ register */
#define GMAC_ST1RPQ_DSTCE_Pos                 _UINT32_(28)                                         /* (GMAC_ST1RPQ) Differentiated Services or Traffic Class Match Enable Position */
#define GMAC_ST1RPQ_DSTCE_Msk                 (_UINT32_(0x1) << GMAC_ST1RPQ_DSTCE_Pos)             /* (GMAC_ST1RPQ) Differentiated Services or Traffic Class Match Enable Mask */
#define GMAC_ST1RPQ_DSTCE(value)              (GMAC_ST1RPQ_DSTCE_Msk & (_UINT32_(value) << GMAC_ST1RPQ_DSTCE_Pos)) /* Assigment of value for DSTCE in the GMAC_ST1RPQ register */
#define GMAC_ST1RPQ_UDPE_Pos                  _UINT32_(29)                                         /* (GMAC_ST1RPQ) UDP Port Match Enable Position */
#define GMAC_ST1RPQ_UDPE_Msk                  (_UINT32_(0x1) << GMAC_ST1RPQ_UDPE_Pos)              /* (GMAC_ST1RPQ) UDP Port Match Enable Mask */
#define GMAC_ST1RPQ_UDPE(value)               (GMAC_ST1RPQ_UDPE_Msk & (_UINT32_(value) << GMAC_ST1RPQ_UDPE_Pos)) /* Assigment of value for UDPE in the GMAC_ST1RPQ register */
#define GMAC_ST1RPQ_Msk                       _UINT32_(0x3FFFFFF7)                                 /* (GMAC_ST1RPQ) Register Mask  */


/* -------- GMAC_ST2RPQ : (GMAC Offset: 0x540) (R/W 32) Screening Type 2 Register Priority Queue (index = 0) -------- */
#define GMAC_ST2RPQ_RESETVALUE                _UINT32_(0x00)                                       /*  (GMAC_ST2RPQ) Screening Type 2 Register Priority Queue (index = 0)  Reset Value */

#define GMAC_ST2RPQ_QNB_Pos                   _UINT32_(0)                                          /* (GMAC_ST2RPQ) Queue Number (0-2) Position */
#define GMAC_ST2RPQ_QNB_Msk                   (_UINT32_(0x7) << GMAC_ST2RPQ_QNB_Pos)               /* (GMAC_ST2RPQ) Queue Number (0-2) Mask */
#define GMAC_ST2RPQ_QNB(value)                (GMAC_ST2RPQ_QNB_Msk & (_UINT32_(value) << GMAC_ST2RPQ_QNB_Pos)) /* Assigment of value for QNB in the GMAC_ST2RPQ register */
#define GMAC_ST2RPQ_VLANP_Pos                 _UINT32_(4)                                          /* (GMAC_ST2RPQ) VLAN Priority Position */
#define GMAC_ST2RPQ_VLANP_Msk                 (_UINT32_(0x7) << GMAC_ST2RPQ_VLANP_Pos)             /* (GMAC_ST2RPQ) VLAN Priority Mask */
#define GMAC_ST2RPQ_VLANP(value)              (GMAC_ST2RPQ_VLANP_Msk & (_UINT32_(value) << GMAC_ST2RPQ_VLANP_Pos)) /* Assigment of value for VLANP in the GMAC_ST2RPQ register */
#define GMAC_ST2RPQ_VLANE_Pos                 _UINT32_(8)                                          /* (GMAC_ST2RPQ) VLAN Enable Position */
#define GMAC_ST2RPQ_VLANE_Msk                 (_UINT32_(0x1) << GMAC_ST2RPQ_VLANE_Pos)             /* (GMAC_ST2RPQ) VLAN Enable Mask */
#define GMAC_ST2RPQ_VLANE(value)              (GMAC_ST2RPQ_VLANE_Msk & (_UINT32_(value) << GMAC_ST2RPQ_VLANE_Pos)) /* Assigment of value for VLANE in the GMAC_ST2RPQ register */
#define   GMAC_ST2RPQ_VLANE_0_Val             _UINT32_(0x0)                                        /* (GMAC_ST2RPQ) VLAN match is disabled.  */
#define   GMAC_ST2RPQ_VLANE_1_Val             _UINT32_(0x1)                                        /* (GMAC_ST2RPQ) VLAN match is enabled.  */
#define GMAC_ST2RPQ_VLANE_0                   (GMAC_ST2RPQ_VLANE_0_Val << GMAC_ST2RPQ_VLANE_Pos)   /* (GMAC_ST2RPQ) VLAN match is disabled. Position  */
#define GMAC_ST2RPQ_VLANE_1                   (GMAC_ST2RPQ_VLANE_1_Val << GMAC_ST2RPQ_VLANE_Pos)   /* (GMAC_ST2RPQ) VLAN match is enabled. Position  */
#define GMAC_ST2RPQ_I2ETH_Pos                 _UINT32_(9)                                          /* (GMAC_ST2RPQ) Index of Screening Type 2 EtherType register Position */
#define GMAC_ST2RPQ_I2ETH_Msk                 (_UINT32_(0x7) << GMAC_ST2RPQ_I2ETH_Pos)             /* (GMAC_ST2RPQ) Index of Screening Type 2 EtherType register Mask */
#define GMAC_ST2RPQ_I2ETH(value)              (GMAC_ST2RPQ_I2ETH_Msk & (_UINT32_(value) << GMAC_ST2RPQ_I2ETH_Pos)) /* Assigment of value for I2ETH in the GMAC_ST2RPQ register */
#define GMAC_ST2RPQ_ETHE_Pos                  _UINT32_(12)                                         /* (GMAC_ST2RPQ) EtherType Enable Position */
#define GMAC_ST2RPQ_ETHE_Msk                  (_UINT32_(0x1) << GMAC_ST2RPQ_ETHE_Pos)              /* (GMAC_ST2RPQ) EtherType Enable Mask */
#define GMAC_ST2RPQ_ETHE(value)               (GMAC_ST2RPQ_ETHE_Msk & (_UINT32_(value) << GMAC_ST2RPQ_ETHE_Pos)) /* Assigment of value for ETHE in the GMAC_ST2RPQ register */
#define   GMAC_ST2RPQ_ETHE_0_Val              _UINT32_(0x0)                                        /* (GMAC_ST2RPQ) EtherType match with bits 15:0 in the register designated by the value of I2ETH is disabled.  */
#define   GMAC_ST2RPQ_ETHE_1_Val              _UINT32_(0x1)                                        /* (GMAC_ST2RPQ) EtherType match with bits 15:0 in the register designated by the value of I2ETH is enabled.  */
#define GMAC_ST2RPQ_ETHE_0                    (GMAC_ST2RPQ_ETHE_0_Val << GMAC_ST2RPQ_ETHE_Pos)     /* (GMAC_ST2RPQ) EtherType match with bits 15:0 in the register designated by the value of I2ETH is disabled. Position  */
#define GMAC_ST2RPQ_ETHE_1                    (GMAC_ST2RPQ_ETHE_1_Val << GMAC_ST2RPQ_ETHE_Pos)     /* (GMAC_ST2RPQ) EtherType match with bits 15:0 in the register designated by the value of I2ETH is enabled. Position  */
#define GMAC_ST2RPQ_COMPA_Pos                 _UINT32_(13)                                         /* (GMAC_ST2RPQ) Index of Screening Type 2 Compare Word 0/Word 1 register Position */
#define GMAC_ST2RPQ_COMPA_Msk                 (_UINT32_(0x1F) << GMAC_ST2RPQ_COMPA_Pos)            /* (GMAC_ST2RPQ) Index of Screening Type 2 Compare Word 0/Word 1 register Mask */
#define GMAC_ST2RPQ_COMPA(value)              (GMAC_ST2RPQ_COMPA_Msk & (_UINT32_(value) << GMAC_ST2RPQ_COMPA_Pos)) /* Assigment of value for COMPA in the GMAC_ST2RPQ register */
#define GMAC_ST2RPQ_COMPAE_Pos                _UINT32_(18)                                         /* (GMAC_ST2RPQ) Compare A Enable Position */
#define GMAC_ST2RPQ_COMPAE_Msk                (_UINT32_(0x1) << GMAC_ST2RPQ_COMPAE_Pos)            /* (GMAC_ST2RPQ) Compare A Enable Mask */
#define GMAC_ST2RPQ_COMPAE(value)             (GMAC_ST2RPQ_COMPAE_Msk & (_UINT32_(value) << GMAC_ST2RPQ_COMPAE_Pos)) /* Assigment of value for COMPAE in the GMAC_ST2RPQ register */
#define   GMAC_ST2RPQ_COMPAE_0_Val            _UINT32_(0x0)                                        /* (GMAC_ST2RPQ) Comparison via the register designated by index COMPA is disabled.  */
#define   GMAC_ST2RPQ_COMPAE_1_Val            _UINT32_(0x1)                                        /* (GMAC_ST2RPQ) Comparison via the register designated by index COMPA is enabled.  */
#define GMAC_ST2RPQ_COMPAE_0                  (GMAC_ST2RPQ_COMPAE_0_Val << GMAC_ST2RPQ_COMPAE_Pos) /* (GMAC_ST2RPQ) Comparison via the register designated by index COMPA is disabled. Position  */
#define GMAC_ST2RPQ_COMPAE_1                  (GMAC_ST2RPQ_COMPAE_1_Val << GMAC_ST2RPQ_COMPAE_Pos) /* (GMAC_ST2RPQ) Comparison via the register designated by index COMPA is enabled. Position  */
#define GMAC_ST2RPQ_COMPB_Pos                 _UINT32_(19)                                         /* (GMAC_ST2RPQ) Index of Screening Type 2 Compare Word 0/Word 1 register Position */
#define GMAC_ST2RPQ_COMPB_Msk                 (_UINT32_(0x1F) << GMAC_ST2RPQ_COMPB_Pos)            /* (GMAC_ST2RPQ) Index of Screening Type 2 Compare Word 0/Word 1 register Mask */
#define GMAC_ST2RPQ_COMPB(value)              (GMAC_ST2RPQ_COMPB_Msk & (_UINT32_(value) << GMAC_ST2RPQ_COMPB_Pos)) /* Assigment of value for COMPB in the GMAC_ST2RPQ register */
#define GMAC_ST2RPQ_COMPBE_Pos                _UINT32_(24)                                         /* (GMAC_ST2RPQ) Compare B Enable Position */
#define GMAC_ST2RPQ_COMPBE_Msk                (_UINT32_(0x1) << GMAC_ST2RPQ_COMPBE_Pos)            /* (GMAC_ST2RPQ) Compare B Enable Mask */
#define GMAC_ST2RPQ_COMPBE(value)             (GMAC_ST2RPQ_COMPBE_Msk & (_UINT32_(value) << GMAC_ST2RPQ_COMPBE_Pos)) /* Assigment of value for COMPBE in the GMAC_ST2RPQ register */
#define   GMAC_ST2RPQ_COMPBE_0_Val            _UINT32_(0x0)                                        /* (GMAC_ST2RPQ) Comparison via the register designated by index COMPB is disabled.  */
#define   GMAC_ST2RPQ_COMPBE_1_Val            _UINT32_(0x1)                                        /* (GMAC_ST2RPQ) Comparison via the register designated by index COMPB is enabled.  */
#define GMAC_ST2RPQ_COMPBE_0                  (GMAC_ST2RPQ_COMPBE_0_Val << GMAC_ST2RPQ_COMPBE_Pos) /* (GMAC_ST2RPQ) Comparison via the register designated by index COMPB is disabled. Position  */
#define GMAC_ST2RPQ_COMPBE_1                  (GMAC_ST2RPQ_COMPBE_1_Val << GMAC_ST2RPQ_COMPBE_Pos) /* (GMAC_ST2RPQ) Comparison via the register designated by index COMPB is enabled. Position  */
#define GMAC_ST2RPQ_COMPC_Pos                 _UINT32_(25)                                         /* (GMAC_ST2RPQ) Index of Screening Type 2 Compare Word 0/Word 1 register Position */
#define GMAC_ST2RPQ_COMPC_Msk                 (_UINT32_(0x1F) << GMAC_ST2RPQ_COMPC_Pos)            /* (GMAC_ST2RPQ) Index of Screening Type 2 Compare Word 0/Word 1 register Mask */
#define GMAC_ST2RPQ_COMPC(value)              (GMAC_ST2RPQ_COMPC_Msk & (_UINT32_(value) << GMAC_ST2RPQ_COMPC_Pos)) /* Assigment of value for COMPC in the GMAC_ST2RPQ register */
#define GMAC_ST2RPQ_COMPCE_Pos                _UINT32_(30)                                         /* (GMAC_ST2RPQ) Compare C Enable Position */
#define GMAC_ST2RPQ_COMPCE_Msk                (_UINT32_(0x1) << GMAC_ST2RPQ_COMPCE_Pos)            /* (GMAC_ST2RPQ) Compare C Enable Mask */
#define GMAC_ST2RPQ_COMPCE(value)             (GMAC_ST2RPQ_COMPCE_Msk & (_UINT32_(value) << GMAC_ST2RPQ_COMPCE_Pos)) /* Assigment of value for COMPCE in the GMAC_ST2RPQ register */
#define   GMAC_ST2RPQ_COMPCE_0_Val            _UINT32_(0x0)                                        /* (GMAC_ST2RPQ) Comparison via the register designated by index COMPC is disabled.  */
#define   GMAC_ST2RPQ_COMPCE_1_Val            _UINT32_(0x1)                                        /* (GMAC_ST2RPQ) Comparison via the register designated by index COMPC is enabled.  */
#define GMAC_ST2RPQ_COMPCE_0                  (GMAC_ST2RPQ_COMPCE_0_Val << GMAC_ST2RPQ_COMPCE_Pos) /* (GMAC_ST2RPQ) Comparison via the register designated by index COMPC is disabled. Position  */
#define GMAC_ST2RPQ_COMPCE_1                  (GMAC_ST2RPQ_COMPCE_1_Val << GMAC_ST2RPQ_COMPCE_Pos) /* (GMAC_ST2RPQ) Comparison via the register designated by index COMPC is enabled. Position  */
#define GMAC_ST2RPQ_Msk                       _UINT32_(0x7FFFFF77)                                 /* (GMAC_ST2RPQ) Register Mask  */


/* -------- GMAC_TSCTL : (GMAC Offset: 0x580) (R/W 32) Transmit Schedule Control Register -------- */
#define GMAC_TSCTL_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_TSCTL) Transmit Schedule Control Register  Reset Value */

#define GMAC_TSCTL_TXSQ0_Pos                  _UINT32_(0)                                          /* (GMAC_TSCTL) Transmit Schedule for Qx Position */
#define GMAC_TSCTL_TXSQ0_Msk                  (_UINT32_(0x3) << GMAC_TSCTL_TXSQ0_Pos)              /* (GMAC_TSCTL) Transmit Schedule for Qx Mask */
#define GMAC_TSCTL_TXSQ0(value)               (GMAC_TSCTL_TXSQ0_Msk & (_UINT32_(value) << GMAC_TSCTL_TXSQ0_Pos)) /* Assigment of value for TXSQ0 in the GMAC_TSCTL register */
#define   GMAC_TSCTL_TXSQ0_FP_Val             _UINT32_(0x0)                                        /* (GMAC_TSCTL) Fixed Priority  */
#define   GMAC_TSCTL_TXSQ0_CBS_Val            _UINT32_(0x1)                                        /* (GMAC_TSCTL) CBS Enabled only valid for top two enabled queues and if CBS capability selected.  */
#define   GMAC_TSCTL_TXSQ0_DWRR_Val           _UINT32_(0x2)                                        /* (GMAC_TSCTL) DWRR enabled  */
#define   GMAC_TSCTL_TXSQ0_ETS_Val            _UINT32_(0x3)                                        /* (GMAC_TSCTL) ETS enabled  */
#define GMAC_TSCTL_TXSQ0_FP                   (GMAC_TSCTL_TXSQ0_FP_Val << GMAC_TSCTL_TXSQ0_Pos)    /* (GMAC_TSCTL) Fixed Priority Position  */
#define GMAC_TSCTL_TXSQ0_CBS                  (GMAC_TSCTL_TXSQ0_CBS_Val << GMAC_TSCTL_TXSQ0_Pos)   /* (GMAC_TSCTL) CBS Enabled only valid for top two enabled queues and if CBS capability selected. Position  */
#define GMAC_TSCTL_TXSQ0_DWRR                 (GMAC_TSCTL_TXSQ0_DWRR_Val << GMAC_TSCTL_TXSQ0_Pos)  /* (GMAC_TSCTL) DWRR enabled Position  */
#define GMAC_TSCTL_TXSQ0_ETS                  (GMAC_TSCTL_TXSQ0_ETS_Val << GMAC_TSCTL_TXSQ0_Pos)   /* (GMAC_TSCTL) ETS enabled Position  */
#define GMAC_TSCTL_TXSQ1_Pos                  _UINT32_(2)                                          /* (GMAC_TSCTL) Transmit Schedule for Qx Position */
#define GMAC_TSCTL_TXSQ1_Msk                  (_UINT32_(0x3) << GMAC_TSCTL_TXSQ1_Pos)              /* (GMAC_TSCTL) Transmit Schedule for Qx Mask */
#define GMAC_TSCTL_TXSQ1(value)               (GMAC_TSCTL_TXSQ1_Msk & (_UINT32_(value) << GMAC_TSCTL_TXSQ1_Pos)) /* Assigment of value for TXSQ1 in the GMAC_TSCTL register */
#define   GMAC_TSCTL_TXSQ1_FP_Val             _UINT32_(0x0)                                        /* (GMAC_TSCTL) Fixed Priority  */
#define   GMAC_TSCTL_TXSQ1_CBS_Val            _UINT32_(0x1)                                        /* (GMAC_TSCTL) CBS Enabled only valid for top two enabled queues and if CBS capability selected.  */
#define   GMAC_TSCTL_TXSQ1_DWRR_Val           _UINT32_(0x2)                                        /* (GMAC_TSCTL) DWRR enabled  */
#define   GMAC_TSCTL_TXSQ1_ETS_Val            _UINT32_(0x3)                                        /* (GMAC_TSCTL) ETS enabled  */
#define GMAC_TSCTL_TXSQ1_FP                   (GMAC_TSCTL_TXSQ1_FP_Val << GMAC_TSCTL_TXSQ1_Pos)    /* (GMAC_TSCTL) Fixed Priority Position  */
#define GMAC_TSCTL_TXSQ1_CBS                  (GMAC_TSCTL_TXSQ1_CBS_Val << GMAC_TSCTL_TXSQ1_Pos)   /* (GMAC_TSCTL) CBS Enabled only valid for top two enabled queues and if CBS capability selected. Position  */
#define GMAC_TSCTL_TXSQ1_DWRR                 (GMAC_TSCTL_TXSQ1_DWRR_Val << GMAC_TSCTL_TXSQ1_Pos)  /* (GMAC_TSCTL) DWRR enabled Position  */
#define GMAC_TSCTL_TXSQ1_ETS                  (GMAC_TSCTL_TXSQ1_ETS_Val << GMAC_TSCTL_TXSQ1_Pos)   /* (GMAC_TSCTL) ETS enabled Position  */
#define GMAC_TSCTL_TXSQ2_Pos                  _UINT32_(4)                                          /* (GMAC_TSCTL) Transmit Schedule for Qx Position */
#define GMAC_TSCTL_TXSQ2_Msk                  (_UINT32_(0x3) << GMAC_TSCTL_TXSQ2_Pos)              /* (GMAC_TSCTL) Transmit Schedule for Qx Mask */
#define GMAC_TSCTL_TXSQ2(value)               (GMAC_TSCTL_TXSQ2_Msk & (_UINT32_(value) << GMAC_TSCTL_TXSQ2_Pos)) /* Assigment of value for TXSQ2 in the GMAC_TSCTL register */
#define   GMAC_TSCTL_TXSQ2_FP_Val             _UINT32_(0x0)                                        /* (GMAC_TSCTL) Fixed Priority  */
#define   GMAC_TSCTL_TXSQ2_CBS_Val            _UINT32_(0x1)                                        /* (GMAC_TSCTL) CBS Enabled only valid for top two enabled queues and if CBS capability selected.  */
#define   GMAC_TSCTL_TXSQ2_DWRR_Val           _UINT32_(0x2)                                        /* (GMAC_TSCTL) DWRR enabled  */
#define   GMAC_TSCTL_TXSQ2_ETS_Val            _UINT32_(0x3)                                        /* (GMAC_TSCTL) ETS enabled  */
#define GMAC_TSCTL_TXSQ2_FP                   (GMAC_TSCTL_TXSQ2_FP_Val << GMAC_TSCTL_TXSQ2_Pos)    /* (GMAC_TSCTL) Fixed Priority Position  */
#define GMAC_TSCTL_TXSQ2_CBS                  (GMAC_TSCTL_TXSQ2_CBS_Val << GMAC_TSCTL_TXSQ2_Pos)   /* (GMAC_TSCTL) CBS Enabled only valid for top two enabled queues and if CBS capability selected. Position  */
#define GMAC_TSCTL_TXSQ2_DWRR                 (GMAC_TSCTL_TXSQ2_DWRR_Val << GMAC_TSCTL_TXSQ2_Pos)  /* (GMAC_TSCTL) DWRR enabled Position  */
#define GMAC_TSCTL_TXSQ2_ETS                  (GMAC_TSCTL_TXSQ2_ETS_Val << GMAC_TSCTL_TXSQ2_Pos)   /* (GMAC_TSCTL) ETS enabled Position  */
#define GMAC_TSCTL_TXSQ3_Pos                  _UINT32_(6)                                          /* (GMAC_TSCTL) Transmit Schedule for Qx Position */
#define GMAC_TSCTL_TXSQ3_Msk                  (_UINT32_(0x3) << GMAC_TSCTL_TXSQ3_Pos)              /* (GMAC_TSCTL) Transmit Schedule for Qx Mask */
#define GMAC_TSCTL_TXSQ3(value)               (GMAC_TSCTL_TXSQ3_Msk & (_UINT32_(value) << GMAC_TSCTL_TXSQ3_Pos)) /* Assigment of value for TXSQ3 in the GMAC_TSCTL register */
#define   GMAC_TSCTL_TXSQ3_FP_Val             _UINT32_(0x0)                                        /* (GMAC_TSCTL) Fixed Priority  */
#define   GMAC_TSCTL_TXSQ3_CBS_Val            _UINT32_(0x1)                                        /* (GMAC_TSCTL) CBS Enabled only valid for top two enabled queues and if CBS capability selected.  */
#define   GMAC_TSCTL_TXSQ3_DWRR_Val           _UINT32_(0x2)                                        /* (GMAC_TSCTL) DWRR enabled  */
#define   GMAC_TSCTL_TXSQ3_ETS_Val            _UINT32_(0x3)                                        /* (GMAC_TSCTL) ETS enabled  */
#define GMAC_TSCTL_TXSQ3_FP                   (GMAC_TSCTL_TXSQ3_FP_Val << GMAC_TSCTL_TXSQ3_Pos)    /* (GMAC_TSCTL) Fixed Priority Position  */
#define GMAC_TSCTL_TXSQ3_CBS                  (GMAC_TSCTL_TXSQ3_CBS_Val << GMAC_TSCTL_TXSQ3_Pos)   /* (GMAC_TSCTL) CBS Enabled only valid for top two enabled queues and if CBS capability selected. Position  */
#define GMAC_TSCTL_TXSQ3_DWRR                 (GMAC_TSCTL_TXSQ3_DWRR_Val << GMAC_TSCTL_TXSQ3_Pos)  /* (GMAC_TSCTL) DWRR enabled Position  */
#define GMAC_TSCTL_TXSQ3_ETS                  (GMAC_TSCTL_TXSQ3_ETS_Val << GMAC_TSCTL_TXSQ3_Pos)   /* (GMAC_TSCTL) ETS enabled Position  */
#define GMAC_TSCTL_TXSQ4_Pos                  _UINT32_(8)                                          /* (GMAC_TSCTL) Transmit Schedule for Qx Position */
#define GMAC_TSCTL_TXSQ4_Msk                  (_UINT32_(0x3) << GMAC_TSCTL_TXSQ4_Pos)              /* (GMAC_TSCTL) Transmit Schedule for Qx Mask */
#define GMAC_TSCTL_TXSQ4(value)               (GMAC_TSCTL_TXSQ4_Msk & (_UINT32_(value) << GMAC_TSCTL_TXSQ4_Pos)) /* Assigment of value for TXSQ4 in the GMAC_TSCTL register */
#define   GMAC_TSCTL_TXSQ4_FP_Val             _UINT32_(0x0)                                        /* (GMAC_TSCTL) Fixed Priority  */
#define   GMAC_TSCTL_TXSQ4_CBS_Val            _UINT32_(0x1)                                        /* (GMAC_TSCTL) CBS Enabled only valid for top two enabled queues and if CBS capability selected.  */
#define   GMAC_TSCTL_TXSQ4_DWRR_Val           _UINT32_(0x2)                                        /* (GMAC_TSCTL) DWRR enabled  */
#define   GMAC_TSCTL_TXSQ4_ETS_Val            _UINT32_(0x3)                                        /* (GMAC_TSCTL) ETS enabled  */
#define GMAC_TSCTL_TXSQ4_FP                   (GMAC_TSCTL_TXSQ4_FP_Val << GMAC_TSCTL_TXSQ4_Pos)    /* (GMAC_TSCTL) Fixed Priority Position  */
#define GMAC_TSCTL_TXSQ4_CBS                  (GMAC_TSCTL_TXSQ4_CBS_Val << GMAC_TSCTL_TXSQ4_Pos)   /* (GMAC_TSCTL) CBS Enabled only valid for top two enabled queues and if CBS capability selected. Position  */
#define GMAC_TSCTL_TXSQ4_DWRR                 (GMAC_TSCTL_TXSQ4_DWRR_Val << GMAC_TSCTL_TXSQ4_Pos)  /* (GMAC_TSCTL) DWRR enabled Position  */
#define GMAC_TSCTL_TXSQ4_ETS                  (GMAC_TSCTL_TXSQ4_ETS_Val << GMAC_TSCTL_TXSQ4_Pos)   /* (GMAC_TSCTL) ETS enabled Position  */
#define GMAC_TSCTL_TXSQ5_Pos                  _UINT32_(10)                                         /* (GMAC_TSCTL) Transmit Schedule for Qx Position */
#define GMAC_TSCTL_TXSQ5_Msk                  (_UINT32_(0x3) << GMAC_TSCTL_TXSQ5_Pos)              /* (GMAC_TSCTL) Transmit Schedule for Qx Mask */
#define GMAC_TSCTL_TXSQ5(value)               (GMAC_TSCTL_TXSQ5_Msk & (_UINT32_(value) << GMAC_TSCTL_TXSQ5_Pos)) /* Assigment of value for TXSQ5 in the GMAC_TSCTL register */
#define   GMAC_TSCTL_TXSQ5_FP_Val             _UINT32_(0x0)                                        /* (GMAC_TSCTL) Fixed Priority  */
#define   GMAC_TSCTL_TXSQ5_CBS_Val            _UINT32_(0x1)                                        /* (GMAC_TSCTL) CBS Enabled only valid for top two enabled queues and if CBS capability selected.  */
#define   GMAC_TSCTL_TXSQ5_DWRR_Val           _UINT32_(0x2)                                        /* (GMAC_TSCTL) DWRR enabled  */
#define   GMAC_TSCTL_TXSQ5_ETS_Val            _UINT32_(0x3)                                        /* (GMAC_TSCTL) ETS enabled  */
#define GMAC_TSCTL_TXSQ5_FP                   (GMAC_TSCTL_TXSQ5_FP_Val << GMAC_TSCTL_TXSQ5_Pos)    /* (GMAC_TSCTL) Fixed Priority Position  */
#define GMAC_TSCTL_TXSQ5_CBS                  (GMAC_TSCTL_TXSQ5_CBS_Val << GMAC_TSCTL_TXSQ5_Pos)   /* (GMAC_TSCTL) CBS Enabled only valid for top two enabled queues and if CBS capability selected. Position  */
#define GMAC_TSCTL_TXSQ5_DWRR                 (GMAC_TSCTL_TXSQ5_DWRR_Val << GMAC_TSCTL_TXSQ5_Pos)  /* (GMAC_TSCTL) DWRR enabled Position  */
#define GMAC_TSCTL_TXSQ5_ETS                  (GMAC_TSCTL_TXSQ5_ETS_Val << GMAC_TSCTL_TXSQ5_Pos)   /* (GMAC_TSCTL) ETS enabled Position  */
#define GMAC_TSCTL_Msk                        _UINT32_(0x00000FFF)                                 /* (GMAC_TSCTL) Register Mask  */


/* -------- GMAC_TQBWRL0 : (GMAC Offset: 0x590) (R/W 32) Transmit Queue Bandwidth Rate Limit 0 Register -------- */
#define GMAC_TQBWRL0_RESETVALUE               _UINT32_(0x00)                                       /*  (GMAC_TQBWRL0) Transmit Queue Bandwidth Rate Limit 0 Register  Reset Value */

#define GMAC_TQBWRL0_ALLOCQ0_Pos              _UINT32_(0)                                          /* (GMAC_TQBWRL0) DWRR Weighting or ETS Bandwidth Allocation for Qx Position */
#define GMAC_TQBWRL0_ALLOCQ0_Msk              (_UINT32_(0xFF) << GMAC_TQBWRL0_ALLOCQ0_Pos)         /* (GMAC_TQBWRL0) DWRR Weighting or ETS Bandwidth Allocation for Qx Mask */
#define GMAC_TQBWRL0_ALLOCQ0(value)           (GMAC_TQBWRL0_ALLOCQ0_Msk & (_UINT32_(value) << GMAC_TQBWRL0_ALLOCQ0_Pos)) /* Assigment of value for ALLOCQ0 in the GMAC_TQBWRL0 register */
#define GMAC_TQBWRL0_ALLOCQ1_Pos              _UINT32_(8)                                          /* (GMAC_TQBWRL0) DWRR Weighting or ETS Bandwidth Allocation for Qx Position */
#define GMAC_TQBWRL0_ALLOCQ1_Msk              (_UINT32_(0xFF) << GMAC_TQBWRL0_ALLOCQ1_Pos)         /* (GMAC_TQBWRL0) DWRR Weighting or ETS Bandwidth Allocation for Qx Mask */
#define GMAC_TQBWRL0_ALLOCQ1(value)           (GMAC_TQBWRL0_ALLOCQ1_Msk & (_UINT32_(value) << GMAC_TQBWRL0_ALLOCQ1_Pos)) /* Assigment of value for ALLOCQ1 in the GMAC_TQBWRL0 register */
#define GMAC_TQBWRL0_ALLOCQ2_Pos              _UINT32_(16)                                         /* (GMAC_TQBWRL0) DWRR Weighting or ETS Bandwidth Allocation for Qx Position */
#define GMAC_TQBWRL0_ALLOCQ2_Msk              (_UINT32_(0xFF) << GMAC_TQBWRL0_ALLOCQ2_Pos)         /* (GMAC_TQBWRL0) DWRR Weighting or ETS Bandwidth Allocation for Qx Mask */
#define GMAC_TQBWRL0_ALLOCQ2(value)           (GMAC_TQBWRL0_ALLOCQ2_Msk & (_UINT32_(value) << GMAC_TQBWRL0_ALLOCQ2_Pos)) /* Assigment of value for ALLOCQ2 in the GMAC_TQBWRL0 register */
#define GMAC_TQBWRL0_ALLOCQ3_Pos              _UINT32_(24)                                         /* (GMAC_TQBWRL0) DWRR Weighting or ETS Bandwidth Allocation for Qx Position */
#define GMAC_TQBWRL0_ALLOCQ3_Msk              (_UINT32_(0xFF) << GMAC_TQBWRL0_ALLOCQ3_Pos)         /* (GMAC_TQBWRL0) DWRR Weighting or ETS Bandwidth Allocation for Qx Mask */
#define GMAC_TQBWRL0_ALLOCQ3(value)           (GMAC_TQBWRL0_ALLOCQ3_Msk & (_UINT32_(value) << GMAC_TQBWRL0_ALLOCQ3_Pos)) /* Assigment of value for ALLOCQ3 in the GMAC_TQBWRL0 register */
#define GMAC_TQBWRL0_Msk                      _UINT32_(0xFFFFFFFF)                                 /* (GMAC_TQBWRL0) Register Mask  */


/* -------- GMAC_TQSA : (GMAC Offset: 0x5A0) (R/W 32) Transmit Queue Segment Allocation Register -------- */
#define GMAC_TQSA_RESETVALUE                  _UINT32_(0x00)                                       /*  (GMAC_TQSA) Transmit Queue Segment Allocation Register  Reset Value */

#define GMAC_TQSA_SEGALLOCQ0_Pos              _UINT32_(0)                                          /* (GMAC_TQSA) Segment Allocation for Qx Position */
#define GMAC_TQSA_SEGALLOCQ0_Msk              (_UINT32_(0x7) << GMAC_TQSA_SEGALLOCQ0_Pos)          /* (GMAC_TQSA) Segment Allocation for Qx Mask */
#define GMAC_TQSA_SEGALLOCQ0(value)           (GMAC_TQSA_SEGALLOCQ0_Msk & (_UINT32_(value) << GMAC_TQSA_SEGALLOCQ0_Pos)) /* Assigment of value for SEGALLOCQ0 in the GMAC_TQSA register */
#define GMAC_TQSA_SEGALLOCQ1_Pos              _UINT32_(4)                                          /* (GMAC_TQSA) Segment Allocation for Qx Position */
#define GMAC_TQSA_SEGALLOCQ1_Msk              (_UINT32_(0x7) << GMAC_TQSA_SEGALLOCQ1_Pos)          /* (GMAC_TQSA) Segment Allocation for Qx Mask */
#define GMAC_TQSA_SEGALLOCQ1(value)           (GMAC_TQSA_SEGALLOCQ1_Msk & (_UINT32_(value) << GMAC_TQSA_SEGALLOCQ1_Pos)) /* Assigment of value for SEGALLOCQ1 in the GMAC_TQSA register */
#define GMAC_TQSA_SEGALLOCQ2_Pos              _UINT32_(8)                                          /* (GMAC_TQSA) Segment Allocation for Qx Position */
#define GMAC_TQSA_SEGALLOCQ2_Msk              (_UINT32_(0x7) << GMAC_TQSA_SEGALLOCQ2_Pos)          /* (GMAC_TQSA) Segment Allocation for Qx Mask */
#define GMAC_TQSA_SEGALLOCQ2(value)           (GMAC_TQSA_SEGALLOCQ2_Msk & (_UINT32_(value) << GMAC_TQSA_SEGALLOCQ2_Pos)) /* Assigment of value for SEGALLOCQ2 in the GMAC_TQSA register */
#define GMAC_TQSA_SEGALLOCQ3_Pos              _UINT32_(12)                                         /* (GMAC_TQSA) Segment Allocation for Qx Position */
#define GMAC_TQSA_SEGALLOCQ3_Msk              (_UINT32_(0x7) << GMAC_TQSA_SEGALLOCQ3_Pos)          /* (GMAC_TQSA) Segment Allocation for Qx Mask */
#define GMAC_TQSA_SEGALLOCQ3(value)           (GMAC_TQSA_SEGALLOCQ3_Msk & (_UINT32_(value) << GMAC_TQSA_SEGALLOCQ3_Pos)) /* Assigment of value for SEGALLOCQ3 in the GMAC_TQSA register */
#define GMAC_TQSA_SEGALLOCQ4_Pos              _UINT32_(16)                                         /* (GMAC_TQSA) Segment Allocation for Qx Position */
#define GMAC_TQSA_SEGALLOCQ4_Msk              (_UINT32_(0x7) << GMAC_TQSA_SEGALLOCQ4_Pos)          /* (GMAC_TQSA) Segment Allocation for Qx Mask */
#define GMAC_TQSA_SEGALLOCQ4(value)           (GMAC_TQSA_SEGALLOCQ4_Msk & (_UINT32_(value) << GMAC_TQSA_SEGALLOCQ4_Pos)) /* Assigment of value for SEGALLOCQ4 in the GMAC_TQSA register */
#define GMAC_TQSA_SEGALLOCQ5_Pos              _UINT32_(20)                                         /* (GMAC_TQSA) Segment Allocation for Qx Position */
#define GMAC_TQSA_SEGALLOCQ5_Msk              (_UINT32_(0x7) << GMAC_TQSA_SEGALLOCQ5_Pos)          /* (GMAC_TQSA) Segment Allocation for Qx Mask */
#define GMAC_TQSA_SEGALLOCQ5(value)           (GMAC_TQSA_SEGALLOCQ5_Msk & (_UINT32_(value) << GMAC_TQSA_SEGALLOCQ5_Pos)) /* Assigment of value for SEGALLOCQ5 in the GMAC_TQSA register */
#define GMAC_TQSA_Msk                         _UINT32_(0x00777777)                                 /* (GMAC_TQSA) Register Mask  */


/* -------- GMAC_IERPQ : (GMAC Offset: 0x600) ( /W 32) Interrupt Enable Register Priority Queue (index = 1) -------- */
#define GMAC_IERPQ_RCOMP_Pos                  _UINT32_(1)                                          /* (GMAC_IERPQ) Receive Complete Position */
#define GMAC_IERPQ_RCOMP_Msk                  (_UINT32_(0x1) << GMAC_IERPQ_RCOMP_Pos)              /* (GMAC_IERPQ) Receive Complete Mask */
#define GMAC_IERPQ_RCOMP(value)               (GMAC_IERPQ_RCOMP_Msk & (_UINT32_(value) << GMAC_IERPQ_RCOMP_Pos)) /* Assigment of value for RCOMP in the GMAC_IERPQ register */
#define GMAC_IERPQ_RXUBR_Pos                  _UINT32_(2)                                          /* (GMAC_IERPQ) RX Used Bit Read Position */
#define GMAC_IERPQ_RXUBR_Msk                  (_UINT32_(0x1) << GMAC_IERPQ_RXUBR_Pos)              /* (GMAC_IERPQ) RX Used Bit Read Mask */
#define GMAC_IERPQ_RXUBR(value)               (GMAC_IERPQ_RXUBR_Msk & (_UINT32_(value) << GMAC_IERPQ_RXUBR_Pos)) /* Assigment of value for RXUBR in the GMAC_IERPQ register */
#define GMAC_IERPQ_RLEX_Pos                   _UINT32_(5)                                          /* (GMAC_IERPQ) Retry Limit Exceeded or Late Collision Position */
#define GMAC_IERPQ_RLEX_Msk                   (_UINT32_(0x1) << GMAC_IERPQ_RLEX_Pos)               /* (GMAC_IERPQ) Retry Limit Exceeded or Late Collision Mask */
#define GMAC_IERPQ_RLEX(value)                (GMAC_IERPQ_RLEX_Msk & (_UINT32_(value) << GMAC_IERPQ_RLEX_Pos)) /* Assigment of value for RLEX in the GMAC_IERPQ register */
#define GMAC_IERPQ_TFC_Pos                    _UINT32_(6)                                          /* (GMAC_IERPQ) Transmit Frame Corruption Due to System Bus Error Position */
#define GMAC_IERPQ_TFC_Msk                    (_UINT32_(0x1) << GMAC_IERPQ_TFC_Pos)                /* (GMAC_IERPQ) Transmit Frame Corruption Due to System Bus Error Mask */
#define GMAC_IERPQ_TFC(value)                 (GMAC_IERPQ_TFC_Msk & (_UINT32_(value) << GMAC_IERPQ_TFC_Pos)) /* Assigment of value for TFC in the GMAC_IERPQ register */
#define GMAC_IERPQ_TCOMP_Pos                  _UINT32_(7)                                          /* (GMAC_IERPQ) Transmit Complete Position */
#define GMAC_IERPQ_TCOMP_Msk                  (_UINT32_(0x1) << GMAC_IERPQ_TCOMP_Pos)              /* (GMAC_IERPQ) Transmit Complete Mask */
#define GMAC_IERPQ_TCOMP(value)               (GMAC_IERPQ_TCOMP_Msk & (_UINT32_(value) << GMAC_IERPQ_TCOMP_Pos)) /* Assigment of value for TCOMP in the GMAC_IERPQ register */
#define GMAC_IERPQ_HRESP_Pos                  _UINT32_(11)                                         /* (GMAC_IERPQ) System Bus Error Position */
#define GMAC_IERPQ_HRESP_Msk                  (_UINT32_(0x1) << GMAC_IERPQ_HRESP_Pos)              /* (GMAC_IERPQ) System Bus Error Mask */
#define GMAC_IERPQ_HRESP(value)               (GMAC_IERPQ_HRESP_Msk & (_UINT32_(value) << GMAC_IERPQ_HRESP_Pos)) /* Assigment of value for HRESP in the GMAC_IERPQ register */
#define GMAC_IERPQ_Msk                        _UINT32_(0x000008E6)                                 /* (GMAC_IERPQ) Register Mask  */


/* -------- GMAC_IDRPQ : (GMAC Offset: 0x620) ( /W 32) Interrupt Disable Register Priority Queue (index = 1) -------- */
#define GMAC_IDRPQ_RCOMP_Pos                  _UINT32_(1)                                          /* (GMAC_IDRPQ) Receive Complete Position */
#define GMAC_IDRPQ_RCOMP_Msk                  (_UINT32_(0x1) << GMAC_IDRPQ_RCOMP_Pos)              /* (GMAC_IDRPQ) Receive Complete Mask */
#define GMAC_IDRPQ_RCOMP(value)               (GMAC_IDRPQ_RCOMP_Msk & (_UINT32_(value) << GMAC_IDRPQ_RCOMP_Pos)) /* Assigment of value for RCOMP in the GMAC_IDRPQ register */
#define GMAC_IDRPQ_RXUBR_Pos                  _UINT32_(2)                                          /* (GMAC_IDRPQ) RX Used Bit Read Position */
#define GMAC_IDRPQ_RXUBR_Msk                  (_UINT32_(0x1) << GMAC_IDRPQ_RXUBR_Pos)              /* (GMAC_IDRPQ) RX Used Bit Read Mask */
#define GMAC_IDRPQ_RXUBR(value)               (GMAC_IDRPQ_RXUBR_Msk & (_UINT32_(value) << GMAC_IDRPQ_RXUBR_Pos)) /* Assigment of value for RXUBR in the GMAC_IDRPQ register */
#define GMAC_IDRPQ_RLEX_Pos                   _UINT32_(5)                                          /* (GMAC_IDRPQ) Retry Limit Exceeded or Late Collision Position */
#define GMAC_IDRPQ_RLEX_Msk                   (_UINT32_(0x1) << GMAC_IDRPQ_RLEX_Pos)               /* (GMAC_IDRPQ) Retry Limit Exceeded or Late Collision Mask */
#define GMAC_IDRPQ_RLEX(value)                (GMAC_IDRPQ_RLEX_Msk & (_UINT32_(value) << GMAC_IDRPQ_RLEX_Pos)) /* Assigment of value for RLEX in the GMAC_IDRPQ register */
#define GMAC_IDRPQ_TFC_Pos                    _UINT32_(6)                                          /* (GMAC_IDRPQ) Transmit Frame Corruption Due to System Bus Error Position */
#define GMAC_IDRPQ_TFC_Msk                    (_UINT32_(0x1) << GMAC_IDRPQ_TFC_Pos)                /* (GMAC_IDRPQ) Transmit Frame Corruption Due to System Bus Error Mask */
#define GMAC_IDRPQ_TFC(value)                 (GMAC_IDRPQ_TFC_Msk & (_UINT32_(value) << GMAC_IDRPQ_TFC_Pos)) /* Assigment of value for TFC in the GMAC_IDRPQ register */
#define GMAC_IDRPQ_TCOMP_Pos                  _UINT32_(7)                                          /* (GMAC_IDRPQ) Transmit Complete Position */
#define GMAC_IDRPQ_TCOMP_Msk                  (_UINT32_(0x1) << GMAC_IDRPQ_TCOMP_Pos)              /* (GMAC_IDRPQ) Transmit Complete Mask */
#define GMAC_IDRPQ_TCOMP(value)               (GMAC_IDRPQ_TCOMP_Msk & (_UINT32_(value) << GMAC_IDRPQ_TCOMP_Pos)) /* Assigment of value for TCOMP in the GMAC_IDRPQ register */
#define GMAC_IDRPQ_HRESP_Pos                  _UINT32_(11)                                         /* (GMAC_IDRPQ) System Bus Error Position */
#define GMAC_IDRPQ_HRESP_Msk                  (_UINT32_(0x1) << GMAC_IDRPQ_HRESP_Pos)              /* (GMAC_IDRPQ) System Bus Error Mask */
#define GMAC_IDRPQ_HRESP(value)               (GMAC_IDRPQ_HRESP_Msk & (_UINT32_(value) << GMAC_IDRPQ_HRESP_Pos)) /* Assigment of value for HRESP in the GMAC_IDRPQ register */
#define GMAC_IDRPQ_Msk                        _UINT32_(0x000008E6)                                 /* (GMAC_IDRPQ) Register Mask  */


/* -------- GMAC_IMRPQ : (GMAC Offset: 0x640) (R/W 32) Interrupt Mask Register Priority Queue (index = 1) -------- */
#define GMAC_IMRPQ_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_IMRPQ) Interrupt Mask Register Priority Queue (index = 1)  Reset Value */

#define GMAC_IMRPQ_RCOMP_Pos                  _UINT32_(1)                                          /* (GMAC_IMRPQ) Receive Complete Position */
#define GMAC_IMRPQ_RCOMP_Msk                  (_UINT32_(0x1) << GMAC_IMRPQ_RCOMP_Pos)              /* (GMAC_IMRPQ) Receive Complete Mask */
#define GMAC_IMRPQ_RCOMP(value)               (GMAC_IMRPQ_RCOMP_Msk & (_UINT32_(value) << GMAC_IMRPQ_RCOMP_Pos)) /* Assigment of value for RCOMP in the GMAC_IMRPQ register */
#define GMAC_IMRPQ_RXUBR_Pos                  _UINT32_(2)                                          /* (GMAC_IMRPQ) RX Used Bit Read Position */
#define GMAC_IMRPQ_RXUBR_Msk                  (_UINT32_(0x1) << GMAC_IMRPQ_RXUBR_Pos)              /* (GMAC_IMRPQ) RX Used Bit Read Mask */
#define GMAC_IMRPQ_RXUBR(value)               (GMAC_IMRPQ_RXUBR_Msk & (_UINT32_(value) << GMAC_IMRPQ_RXUBR_Pos)) /* Assigment of value for RXUBR in the GMAC_IMRPQ register */
#define GMAC_IMRPQ_RLEX_Pos                   _UINT32_(5)                                          /* (GMAC_IMRPQ) Retry Limit Exceeded or Late Collision Position */
#define GMAC_IMRPQ_RLEX_Msk                   (_UINT32_(0x1) << GMAC_IMRPQ_RLEX_Pos)               /* (GMAC_IMRPQ) Retry Limit Exceeded or Late Collision Mask */
#define GMAC_IMRPQ_RLEX(value)                (GMAC_IMRPQ_RLEX_Msk & (_UINT32_(value) << GMAC_IMRPQ_RLEX_Pos)) /* Assigment of value for RLEX in the GMAC_IMRPQ register */
#define GMAC_IMRPQ_AHB_Pos                    _UINT32_(6)                                          /* (GMAC_IMRPQ) Transmit Frame Corruption Due to System Bus Error Position */
#define GMAC_IMRPQ_AHB_Msk                    (_UINT32_(0x1) << GMAC_IMRPQ_AHB_Pos)                /* (GMAC_IMRPQ) Transmit Frame Corruption Due to System Bus Error Mask */
#define GMAC_IMRPQ_AHB(value)                 (GMAC_IMRPQ_AHB_Msk & (_UINT32_(value) << GMAC_IMRPQ_AHB_Pos)) /* Assigment of value for AHB in the GMAC_IMRPQ register */
#define GMAC_IMRPQ_TCOMP_Pos                  _UINT32_(7)                                          /* (GMAC_IMRPQ) Transmit Complete Position */
#define GMAC_IMRPQ_TCOMP_Msk                  (_UINT32_(0x1) << GMAC_IMRPQ_TCOMP_Pos)              /* (GMAC_IMRPQ) Transmit Complete Mask */
#define GMAC_IMRPQ_TCOMP(value)               (GMAC_IMRPQ_TCOMP_Msk & (_UINT32_(value) << GMAC_IMRPQ_TCOMP_Pos)) /* Assigment of value for TCOMP in the GMAC_IMRPQ register */
#define GMAC_IMRPQ_HRESP_Pos                  _UINT32_(11)                                         /* (GMAC_IMRPQ) System Bus Error Position */
#define GMAC_IMRPQ_HRESP_Msk                  (_UINT32_(0x1) << GMAC_IMRPQ_HRESP_Pos)              /* (GMAC_IMRPQ) System Bus Error Mask */
#define GMAC_IMRPQ_HRESP(value)               (GMAC_IMRPQ_HRESP_Msk & (_UINT32_(value) << GMAC_IMRPQ_HRESP_Pos)) /* Assigment of value for HRESP in the GMAC_IMRPQ register */
#define GMAC_IMRPQ_Msk                        _UINT32_(0x000008E6)                                 /* (GMAC_IMRPQ) Register Mask  */


/* -------- GMAC_ST2ER : (GMAC Offset: 0x6E0) (R/W 32) Screening Type 2 Ethertype Register (index = 0) -------- */
#define GMAC_ST2ER_RESETVALUE                 _UINT32_(0x00)                                       /*  (GMAC_ST2ER) Screening Type 2 Ethertype Register (index = 0)  Reset Value */

#define GMAC_ST2ER_COMPVAL_Pos                _UINT32_(0)                                          /* (GMAC_ST2ER) Ethertype Compare Value Position */
#define GMAC_ST2ER_COMPVAL_Msk                (_UINT32_(0xFFFF) << GMAC_ST2ER_COMPVAL_Pos)         /* (GMAC_ST2ER) Ethertype Compare Value Mask */
#define GMAC_ST2ER_COMPVAL(value)             (GMAC_ST2ER_COMPVAL_Msk & (_UINT32_(value) << GMAC_ST2ER_COMPVAL_Pos)) /* Assigment of value for COMPVAL in the GMAC_ST2ER register */
#define GMAC_ST2ER_Msk                        _UINT32_(0x0000FFFF)                                 /* (GMAC_ST2ER) Register Mask  */


/** \brief GMAC register offsets definitions */
#define GMAC_SAB_REG_OFST              _UINT32_(0x00)      /* (GMAC_SAB) Specific Address 1 Bottom Register Offset */
#define GMAC_SAT_REG_OFST              _UINT32_(0x04)      /* (GMAC_SAT) Specific Address 1 Top Register Offset */
#define GMAC_ST2CW0_REG_OFST           _UINT32_(0x00)      /* (GMAC_ST2CW0) Screening Type 2 Compare Word 0 Register  Offset */
#define GMAC_ST2CW1_REG_OFST           _UINT32_(0x04)      /* (GMAC_ST2CW1) Screening Type 2 Compare Word 1 Register  Offset */
#define GMAC_NCR_REG_OFST              _UINT32_(0x00)      /* (GMAC_NCR) Network Control Register Offset */
#define GMAC_NCFGR_REG_OFST            _UINT32_(0x04)      /* (GMAC_NCFGR) Network Configuration Register Offset */
#define GMAC_NSR_REG_OFST              _UINT32_(0x08)      /* (GMAC_NSR) Network Status Register Offset */
#define GMAC_UR_REG_OFST               _UINT32_(0x0C)      /* (GMAC_UR) User Register Offset */
#define GMAC_DCFGR_REG_OFST            _UINT32_(0x10)      /* (GMAC_DCFGR) DMA Configuration Register Offset */
#define GMAC_TSR_REG_OFST              _UINT32_(0x14)      /* (GMAC_TSR) Transmit Status Register Offset */
#define GMAC_RBQB_REG_OFST             _UINT32_(0x18)      /* (GMAC_RBQB) Receive Buffer Queue Base Address Register Offset */
#define GMAC_TBQB_REG_OFST             _UINT32_(0x1C)      /* (GMAC_TBQB) Transmit Buffer Queue Base Address Register Offset */
#define GMAC_RSR_REG_OFST              _UINT32_(0x20)      /* (GMAC_RSR) Receive Status Register Offset */
#define GMAC_ISR_REG_OFST              _UINT32_(0x24)      /* (GMAC_ISR) Interrupt Status Register Offset */
#define GMAC_IER_REG_OFST              _UINT32_(0x28)      /* (GMAC_IER) Interrupt Enable Register Offset */
#define GMAC_IDR_REG_OFST              _UINT32_(0x2C)      /* (GMAC_IDR) Interrupt Disable Register Offset */
#define GMAC_IMR_REG_OFST              _UINT32_(0x30)      /* (GMAC_IMR) Interrupt Mask Register Offset */
#define GMAC_MAN_REG_OFST              _UINT32_(0x34)      /* (GMAC_MAN) PHY Maintenance Register Offset */
#define GMAC_RPQ_REG_OFST              _UINT32_(0x38)      /* (GMAC_RPQ) Receive Pause Quantum Register Offset */
#define GMAC_TPQ_REG_OFST              _UINT32_(0x3C)      /* (GMAC_TPQ) Transmit Pause Quantum Register Offset */
#define GMAC_RJFML_REG_OFST            _UINT32_(0x48)      /* (GMAC_RJFML) RX Jumbo Frame Max Length Register Offset */
#define GMAC_INTM_REG_OFST             _UINT32_(0x5C)      /* (GMAC_INTM) Interrupt Moderation Register Offset */
#define GMAC_SYSWT_REG_OFST            _UINT32_(0x60)      /* (GMAC_SYSWT) System Wake-Up Time Register Offset */
#define GMAC_HRB_REG_OFST              _UINT32_(0x80)      /* (GMAC_HRB) Hash Register Bottom Offset */
#define GMAC_HRT_REG_OFST              _UINT32_(0x84)      /* (GMAC_HRT) Hash Register Top Offset */
#define GMAC_TIDM1_REG_OFST            _UINT32_(0xA8)      /* (GMAC_TIDM1) Type ID Match 1 Register Offset */
#define GMAC_TIDM2_REG_OFST            _UINT32_(0xAC)      /* (GMAC_TIDM2) Type ID Match 2 Register Offset */
#define GMAC_TIDM3_REG_OFST            _UINT32_(0xB0)      /* (GMAC_TIDM3) Type ID Match 3 Register Offset */
#define GMAC_TIDM4_REG_OFST            _UINT32_(0xB4)      /* (GMAC_TIDM4) Type ID Match 4 Register Offset */
#define GMAC_WOL_REG_OFST              _UINT32_(0xB8)      /* (GMAC_WOL) Wake on LAN Register Offset */
#define GMAC_IPGS_REG_OFST             _UINT32_(0xBC)      /* (GMAC_IPGS) IPG Stretch Register Offset */
#define GMAC_SVLAN_REG_OFST            _UINT32_(0xC0)      /* (GMAC_SVLAN) Stacked VLAN Register Offset */
#define GMAC_TPFCP_REG_OFST            _UINT32_(0xC4)      /* (GMAC_TPFCP) Transmit PFC Pause Register Offset */
#define GMAC_SAMB1_REG_OFST            _UINT32_(0xC8)      /* (GMAC_SAMB1) Specific Address 1 Mask Bottom Register Offset */
#define GMAC_SAMT1_REG_OFST            _UINT32_(0xCC)      /* (GMAC_SAMT1) Specific Address 1 Mask Top Register Offset */
#define GMAC_AMRX_REG_OFST             _UINT32_(0xD0)      /* (GMAC_AMRX) System Memory Address Mask for RX Data Buffer Accesses Register Offset */
#define GMAC_RXUDAR_REG_OFST           _UINT32_(0xD4)      /* (GMAC_RXUDAR) PTP RX Unicast IP Destination Address Register Offset */
#define GMAC_TXUDAR_REG_OFST           _UINT32_(0xD8)      /* (GMAC_TXUDAR) PTP TX Unicast IP Destination Address Register Offset */
#define GMAC_NSC_REG_OFST              _UINT32_(0xDC)      /* (GMAC_NSC) 1588 Timer Nanosecond Comparison Register Offset */
#define GMAC_SCL_REG_OFST              _UINT32_(0xE0)      /* (GMAC_SCL) 1588 Timer Second Comparison Low Register Offset */
#define GMAC_SCH_REG_OFST              _UINT32_(0xE4)      /* (GMAC_SCH) 1588 Timer Second Comparison High Register Offset */
#define GMAC_EFTSH_REG_OFST            _UINT32_(0xE8)      /* (GMAC_EFTSH) PTP Event Frame Transmitted Seconds High Register Offset */
#define GMAC_EFRSH_REG_OFST            _UINT32_(0xEC)      /* (GMAC_EFRSH) PTP Event Frame Received Seconds High Register Offset */
#define GMAC_PEFTSH_REG_OFST           _UINT32_(0xF0)      /* (GMAC_PEFTSH) PTP Peer Event Frame Transmitted Seconds High Register Offset */
#define GMAC_PEFRSH_REG_OFST           _UINT32_(0xF4)      /* (GMAC_PEFRSH) PTP Peer Event Frame Received Seconds High Register Offset */
#define GMAC_OTLO_REG_OFST             _UINT32_(0x100)     /* (GMAC_OTLO) Octets Transmitted Low Register Offset */
#define GMAC_OTHI_REG_OFST             _UINT32_(0x104)     /* (GMAC_OTHI) Octets Transmitted High Register Offset */
#define GMAC_FT_REG_OFST               _UINT32_(0x108)     /* (GMAC_FT) Frames Transmitted Register Offset */
#define GMAC_BCFT_REG_OFST             _UINT32_(0x10C)     /* (GMAC_BCFT) Broadcast Frames Transmitted Register Offset */
#define GMAC_MFT_REG_OFST              _UINT32_(0x110)     /* (GMAC_MFT) Multicast Frames Transmitted Register Offset */
#define GMAC_PFT_REG_OFST              _UINT32_(0x114)     /* (GMAC_PFT) Pause Frames Transmitted Register Offset */
#define GMAC_BFT64_REG_OFST            _UINT32_(0x118)     /* (GMAC_BFT64) 64 Byte Frames Transmitted Register Offset */
#define GMAC_TBFT127_REG_OFST          _UINT32_(0x11C)     /* (GMAC_TBFT127) 65 to 127 Byte Frames Transmitted Register Offset */
#define GMAC_TBFT255_REG_OFST          _UINT32_(0x120)     /* (GMAC_TBFT255) 128 to 255 Byte Frames Transmitted Register Offset */
#define GMAC_TBFT511_REG_OFST          _UINT32_(0x124)     /* (GMAC_TBFT511) 256 to 511 Byte Frames Transmitted Register Offset */
#define GMAC_TBFT1023_REG_OFST         _UINT32_(0x128)     /* (GMAC_TBFT1023) 512 to 1023 Byte Frames Transmitted Register Offset */
#define GMAC_TBFT1518_REG_OFST         _UINT32_(0x12C)     /* (GMAC_TBFT1518) 1024 to 1518 Byte Frames Transmitted Register Offset */
#define GMAC_GTBFT1518_REG_OFST        _UINT32_(0x130)     /* (GMAC_GTBFT1518) Greater Than 1518 Byte Frames Transmitted Register Offset */
#define GMAC_TUR_REG_OFST              _UINT32_(0x134)     /* (GMAC_TUR) Transmit Underruns Register Offset */
#define GMAC_SCF_REG_OFST              _UINT32_(0x138)     /* (GMAC_SCF) Single Collision Frames Register Offset */
#define GMAC_MCF_REG_OFST              _UINT32_(0x13C)     /* (GMAC_MCF) Multiple Collision Frames Register Offset */
#define GMAC_EC_REG_OFST               _UINT32_(0x140)     /* (GMAC_EC) Excessive Collisions Register Offset */
#define GMAC_LC_REG_OFST               _UINT32_(0x144)     /* (GMAC_LC) Late Collisions Register Offset */
#define GMAC_DTF_REG_OFST              _UINT32_(0x148)     /* (GMAC_DTF) Deferred Transmission Frames Register Offset */
#define GMAC_CSE_REG_OFST              _UINT32_(0x14C)     /* (GMAC_CSE) Carrier Sense Errors Register Offset */
#define GMAC_ORLO_REG_OFST             _UINT32_(0x150)     /* (GMAC_ORLO) Octets Received Low Received Register Offset */
#define GMAC_ORHI_REG_OFST             _UINT32_(0x154)     /* (GMAC_ORHI) Octets Received High Received Register Offset */
#define GMAC_FR_REG_OFST               _UINT32_(0x158)     /* (GMAC_FR) Frames Received Register Offset */
#define GMAC_BCFR_REG_OFST             _UINT32_(0x15C)     /* (GMAC_BCFR) Broadcast Frames Received Register Offset */
#define GMAC_MFR_REG_OFST              _UINT32_(0x160)     /* (GMAC_MFR) Multicast Frames Received Register Offset */
#define GMAC_PFR_REG_OFST              _UINT32_(0x164)     /* (GMAC_PFR) Pause Frames Received Register Offset */
#define GMAC_BFR64_REG_OFST            _UINT32_(0x168)     /* (GMAC_BFR64) 64 Byte Frames Received Register Offset */
#define GMAC_TBFR127_REG_OFST          _UINT32_(0x16C)     /* (GMAC_TBFR127) 65 to 127 Byte Frames Received Register Offset */
#define GMAC_TBFR255_REG_OFST          _UINT32_(0x170)     /* (GMAC_TBFR255) 128 to 255 Byte Frames Received Register Offset */
#define GMAC_TBFR511_REG_OFST          _UINT32_(0x174)     /* (GMAC_TBFR511) 256 to 511 Byte Frames Received Register Offset */
#define GMAC_TBFR1023_REG_OFST         _UINT32_(0x178)     /* (GMAC_TBFR1023) 512 to 1023 Byte Frames Received Register Offset */
#define GMAC_TBFR1518_REG_OFST         _UINT32_(0x17C)     /* (GMAC_TBFR1518) 1024 to 1518 Byte Frames Received Register Offset */
#define GMAC_TMXBFR_REG_OFST           _UINT32_(0x180)     /* (GMAC_TMXBFR) 1519 to Maximum Byte Frames Received Register Offset */
#define GMAC_UFR_REG_OFST              _UINT32_(0x184)     /* (GMAC_UFR) Undersize Frames Received Register Offset */
#define GMAC_OFR_REG_OFST              _UINT32_(0x188)     /* (GMAC_OFR) Oversize Frames Received Register Offset */
#define GMAC_JR_REG_OFST               _UINT32_(0x18C)     /* (GMAC_JR) Jabbers Received Register Offset */
#define GMAC_FCSE_REG_OFST             _UINT32_(0x190)     /* (GMAC_FCSE) Frame Check Sequence Errors Register Offset */
#define GMAC_LFFE_REG_OFST             _UINT32_(0x194)     /* (GMAC_LFFE) Length Field Frame Errors Register Offset */
#define GMAC_RSE_REG_OFST              _UINT32_(0x198)     /* (GMAC_RSE) Receive Symbol Errors Register Offset */
#define GMAC_AE_REG_OFST               _UINT32_(0x19C)     /* (GMAC_AE) Alignment Errors Register Offset */
#define GMAC_RRE_REG_OFST              _UINT32_(0x1A0)     /* (GMAC_RRE) Receive Resource Errors Register Offset */
#define GMAC_ROE_REG_OFST              _UINT32_(0x1A4)     /* (GMAC_ROE) Receive Overrun Register Offset */
#define GMAC_IHCE_REG_OFST             _UINT32_(0x1A8)     /* (GMAC_IHCE) IP Header Checksum Errors Register Offset */
#define GMAC_TCE_REG_OFST              _UINT32_(0x1AC)     /* (GMAC_TCE) TCP Checksum Errors Register Offset */
#define GMAC_UCE_REG_OFST              _UINT32_(0x1B0)     /* (GMAC_UCE) UDP Checksum Errors Register Offset */
#define GMAC_FLRXPCR_REG_OFST          _UINT32_(0x1B4)     /* (GMAC_FLRXPCR) Flushed Received Packets Counter Register Offset */
#define GMAC_TISUBN_REG_OFST           _UINT32_(0x1BC)     /* (GMAC_TISUBN) 1588 Timer Increment Sub-nanoseconds Register Offset */
#define GMAC_TSH_REG_OFST              _UINT32_(0x1C0)     /* (GMAC_TSH) 1588 Timer Seconds High Register Offset */
#define GMAC_TSL_REG_OFST              _UINT32_(0x1D0)     /* (GMAC_TSL) 1588 Timer Seconds Low Register Offset */
#define GMAC_TN_REG_OFST               _UINT32_(0x1D4)     /* (GMAC_TN) 1588 Timer Nanoseconds Register Offset */
#define GMAC_TA_REG_OFST               _UINT32_(0x1D8)     /* (GMAC_TA) 1588 Timer Adjust Register Offset */
#define GMAC_TI_REG_OFST               _UINT32_(0x1DC)     /* (GMAC_TI) 1588 Timer Increment Register Offset */
#define GMAC_EFTSL_REG_OFST            _UINT32_(0x1E0)     /* (GMAC_EFTSL) PTP Event Frame Transmitted Seconds Low Register Offset */
#define GMAC_EFTN_REG_OFST             _UINT32_(0x1E4)     /* (GMAC_EFTN) PTP Event Frame Transmitted Nanoseconds Register Offset */
#define GMAC_EFRSL_REG_OFST            _UINT32_(0x1E8)     /* (GMAC_EFRSL) PTP Event Frame Received Seconds Low Register Offset */
#define GMAC_EFRN_REG_OFST             _UINT32_(0x1EC)     /* (GMAC_EFRN) PTP Event Frame Received Nanoseconds Register Offset */
#define GMAC_PEFTSL_REG_OFST           _UINT32_(0x1F0)     /* (GMAC_PEFTSL) PTP Peer Event Frame Transmitted Seconds Low Register Offset */
#define GMAC_PEFTN_REG_OFST            _UINT32_(0x1F4)     /* (GMAC_PEFTN) PTP Peer Event Frame Transmitted Nanoseconds Register Offset */
#define GMAC_PEFRSL_REG_OFST           _UINT32_(0x1F8)     /* (GMAC_PEFRSL) PTP Peer Event Frame Received Seconds Low Register Offset */
#define GMAC_PEFRN_REG_OFST            _UINT32_(0x1FC)     /* (GMAC_PEFRN) PTP Peer Event Frame Received Nanoseconds Register Offset */
#define GMAC_RXLPI_REG_OFST            _UINT32_(0x270)     /* (GMAC_RXLPI) Received LPI Transitions Offset */
#define GMAC_RXLPITIME_REG_OFST        _UINT32_(0x274)     /* (GMAC_RXLPITIME) Received LPI Time Offset */
#define GMAC_TXLPI_REG_OFST            _UINT32_(0x278)     /* (GMAC_TXLPI) Transmit LPI Transitions Offset */
#define GMAC_TXLPITIME_REG_OFST        _UINT32_(0x27C)     /* (GMAC_TXLPITIME) Transmit LPI Time Offset */
#define GMAC_ISRPQ_REG_OFST            _UINT32_(0x400)     /* (GMAC_ISRPQ) Interrupt Status Register Priority Queue (index = 1) Offset */
#define GMAC_ISRPQ0_REG_OFST           _UINT32_(0x400)     /* (GMAC_ISRPQ0) Interrupt Status Register Priority Queue (index = 1) Offset */
#define GMAC_ISRPQ1_REG_OFST           _UINT32_(0x404)     /* (GMAC_ISRPQ1) Interrupt Status Register Priority Queue (index = 1) Offset */
#define GMAC_TBQBAPQ_REG_OFST          _UINT32_(0x440)     /* (GMAC_TBQBAPQ) Transmit Buffer Queue Base Address Register Priority Queue (index = 1) Offset */
#define GMAC_TBQBAPQ0_REG_OFST         _UINT32_(0x440)     /* (GMAC_TBQBAPQ0) Transmit Buffer Queue Base Address Register Priority Queue (index = 1) Offset */
#define GMAC_TBQBAPQ1_REG_OFST         _UINT32_(0x444)     /* (GMAC_TBQBAPQ1) Transmit Buffer Queue Base Address Register Priority Queue (index = 1) Offset */
#define GMAC_RBQBAPQ_REG_OFST          _UINT32_(0x480)     /* (GMAC_RBQBAPQ) Receive Buffer Queue Base Address Register Priority Queue (index = 1) Offset */
#define GMAC_RBQBAPQ0_REG_OFST         _UINT32_(0x480)     /* (GMAC_RBQBAPQ0) Receive Buffer Queue Base Address Register Priority Queue (index = 1) Offset */
#define GMAC_RBQBAPQ1_REG_OFST         _UINT32_(0x484)     /* (GMAC_RBQBAPQ1) Receive Buffer Queue Base Address Register Priority Queue (index = 1) Offset */
#define GMAC_RBSRPQ_REG_OFST           _UINT32_(0x4A0)     /* (GMAC_RBSRPQ) Receive Buffer Size Register Priority Queue (index = 1) Offset */
#define GMAC_RBSRPQ0_REG_OFST          _UINT32_(0x4A0)     /* (GMAC_RBSRPQ0) Receive Buffer Size Register Priority Queue (index = 1) Offset */
#define GMAC_RBSRPQ1_REG_OFST          _UINT32_(0x4A4)     /* (GMAC_RBSRPQ1) Receive Buffer Size Register Priority Queue (index = 1) Offset */
#define GMAC_CBSCR_REG_OFST            _UINT32_(0x4BC)     /* (GMAC_CBSCR) Credit-Based Shaping Control Register Offset */
#define GMAC_CBSISQA_REG_OFST          _UINT32_(0x4C0)     /* (GMAC_CBSISQA) Credit-Based Shaping IdleSlope Register for Queue A Offset */
#define GMAC_CBSISQB_REG_OFST          _UINT32_(0x4C4)     /* (GMAC_CBSISQB) Credit-Based Shaping IdleSlope Register for Queue B Offset */
#define GMAC_TQUBA_REG_OFST            _UINT32_(0x4C8)     /* (GMAC_TQUBA) 32 MSB Transmit Buffer Descriptor Queue Base Address Register Offset */
#define GMAC_TXBDCTRL_REG_OFST         _UINT32_(0x4CC)     /* (GMAC_TXBDCTRL) Transmit Buffer Data Control Register Offset */
#define GMAC_RXBDCTRL_REG_OFST         _UINT32_(0x4D0)     /* (GMAC_RXBDCTRL) Receive Buffer Data Control Register Offset */
#define GMAC_RQUBA_REG_OFST            _UINT32_(0x4D4)     /* (GMAC_RQUBA) 32 MSB Receive Buffer Descriptor Queue Base Address Register Offset */
#define GMAC_ST1RPQ_REG_OFST           _UINT32_(0x500)     /* (GMAC_ST1RPQ) Screening Type 1 Register Priority Queue (index = 0) Offset */
#define GMAC_ST2RPQ_REG_OFST           _UINT32_(0x540)     /* (GMAC_ST2RPQ) Screening Type 2 Register Priority Queue (index = 0) Offset */
#define GMAC_TSCTL_REG_OFST            _UINT32_(0x580)     /* (GMAC_TSCTL) Transmit Schedule Control Register Offset */
#define GMAC_TQBWRL0_REG_OFST          _UINT32_(0x590)     /* (GMAC_TQBWRL0) Transmit Queue Bandwidth Rate Limit 0 Register Offset */
#define GMAC_TQSA_REG_OFST             _UINT32_(0x5A0)     /* (GMAC_TQSA) Transmit Queue Segment Allocation Register Offset */
#define GMAC_IERPQ_REG_OFST            _UINT32_(0x600)     /* (GMAC_IERPQ) Interrupt Enable Register Priority Queue (index = 1) Offset */
#define GMAC_IERPQ0_REG_OFST           _UINT32_(0x600)     /* (GMAC_IERPQ0) Interrupt Enable Register Priority Queue (index = 1) Offset */
#define GMAC_IERPQ1_REG_OFST           _UINT32_(0x604)     /* (GMAC_IERPQ1) Interrupt Enable Register Priority Queue (index = 1) Offset */
#define GMAC_IDRPQ_REG_OFST            _UINT32_(0x620)     /* (GMAC_IDRPQ) Interrupt Disable Register Priority Queue (index = 1) Offset */
#define GMAC_IDRPQ0_REG_OFST           _UINT32_(0x620)     /* (GMAC_IDRPQ0) Interrupt Disable Register Priority Queue (index = 1) Offset */
#define GMAC_IDRPQ1_REG_OFST           _UINT32_(0x624)     /* (GMAC_IDRPQ1) Interrupt Disable Register Priority Queue (index = 1) Offset */
#define GMAC_IMRPQ_REG_OFST            _UINT32_(0x640)     /* (GMAC_IMRPQ) Interrupt Mask Register Priority Queue (index = 1) Offset */
#define GMAC_IMRPQ0_REG_OFST           _UINT32_(0x640)     /* (GMAC_IMRPQ0) Interrupt Mask Register Priority Queue (index = 1) Offset */
#define GMAC_IMRPQ1_REG_OFST           _UINT32_(0x644)     /* (GMAC_IMRPQ1) Interrupt Mask Register Priority Queue (index = 1) Offset */
#define GMAC_ST2ER_REG_OFST            _UINT32_(0x6E0)     /* (GMAC_ST2ER) Screening Type 2 Ethertype Register (index = 0) Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief GMAC_SA register API structure */
typedef struct
{
  __IO  uint32_t                       GMAC_SAB;           /**< Offset: 0x00 (R/W  32) Specific Address 1 Bottom Register */
  __IO  uint32_t                       GMAC_SAT;           /**< Offset: 0x04 (R/W  32) Specific Address 1 Top Register */
} gmac_sa_registers_t;

/** \brief GMAC_ST2CW register API structure */
typedef struct
{
  __IO  uint32_t                       GMAC_ST2CW0;        /**< Offset: 0x00 (R/W  32) Screening Type 2 Compare Word 0 Register  */
  __IO  uint32_t                       GMAC_ST2CW1;        /**< Offset: 0x04 (R/W  32) Screening Type 2 Compare Word 1 Register  */
} gmac_st2cw_registers_t;

#define GMAC_SA_NUMBER 4

#define GMAC_ST2CW_NUMBER 1

/** \brief GMAC register API structure */
typedef struct
{  /* Gigabit Ethernet MAC */
  __IO  uint32_t                       GMAC_NCR;           /**< Offset: 0x00 (R/W  32) Network Control Register */
  __IO  uint32_t                       GMAC_NCFGR;         /**< Offset: 0x04 (R/W  32) Network Configuration Register */
  __I   uint32_t                       GMAC_NSR;           /**< Offset: 0x08 (R/   32) Network Status Register */
  __IO  uint32_t                       GMAC_UR;            /**< Offset: 0x0C (R/W  32) User Register */
  __IO  uint32_t                       GMAC_DCFGR;         /**< Offset: 0x10 (R/W  32) DMA Configuration Register */
  __IO  uint32_t                       GMAC_TSR;           /**< Offset: 0x14 (R/W  32) Transmit Status Register */
  __IO  uint32_t                       GMAC_RBQB;          /**< Offset: 0x18 (R/W  32) Receive Buffer Queue Base Address Register */
  __IO  uint32_t                       GMAC_TBQB;          /**< Offset: 0x1C (R/W  32) Transmit Buffer Queue Base Address Register */
  __IO  uint32_t                       GMAC_RSR;           /**< Offset: 0x20 (R/W  32) Receive Status Register */
  __I   uint32_t                       GMAC_ISR;           /**< Offset: 0x24 (R/   32) Interrupt Status Register */
  __O   uint32_t                       GMAC_IER;           /**< Offset: 0x28 ( /W  32) Interrupt Enable Register */
  __O   uint32_t                       GMAC_IDR;           /**< Offset: 0x2C ( /W  32) Interrupt Disable Register */
  __IO  uint32_t                       GMAC_IMR;           /**< Offset: 0x30 (R/W  32) Interrupt Mask Register */
  __IO  uint32_t                       GMAC_MAN;           /**< Offset: 0x34 (R/W  32) PHY Maintenance Register */
  __I   uint32_t                       GMAC_RPQ;           /**< Offset: 0x38 (R/   32) Receive Pause Quantum Register */
  __IO  uint32_t                       GMAC_TPQ;           /**< Offset: 0x3C (R/W  32) Transmit Pause Quantum Register */
  __I   uint8_t                        Reserved1[0x08];
  __IO  uint32_t                       GMAC_RJFML;         /**< Offset: 0x48 (R/W  32) RX Jumbo Frame Max Length Register */
  __I   uint8_t                        Reserved2[0x10];
  __IO  uint32_t                       GMAC_INTM;          /**< Offset: 0x5C (R/W  32) Interrupt Moderation Register */
  __IO  uint32_t                       GMAC_SYSWT;         /**< Offset: 0x60 (R/W  32) System Wake-Up Time Register */
  __I   uint8_t                        Reserved3[0x1C];
  __IO  uint32_t                       GMAC_HRB;           /**< Offset: 0x80 (R/W  32) Hash Register Bottom */
  __IO  uint32_t                       GMAC_HRT;           /**< Offset: 0x84 (R/W  32) Hash Register Top */
        gmac_sa_registers_t            GMAC_SA[GMAC_SA_NUMBER]; /**< Offset: 0x88 Specific Address Register */
  __IO  uint32_t                       GMAC_TIDM1;         /**< Offset: 0xA8 (R/W  32) Type ID Match 1 Register */
  __IO  uint32_t                       GMAC_TIDM2;         /**< Offset: 0xAC (R/W  32) Type ID Match 2 Register */
  __IO  uint32_t                       GMAC_TIDM3;         /**< Offset: 0xB0 (R/W  32) Type ID Match 3 Register */
  __IO  uint32_t                       GMAC_TIDM4;         /**< Offset: 0xB4 (R/W  32) Type ID Match 4 Register */
  __IO  uint32_t                       GMAC_WOL;           /**< Offset: 0xB8 (R/W  32) Wake on LAN Register */
  __IO  uint32_t                       GMAC_IPGS;          /**< Offset: 0xBC (R/W  32) IPG Stretch Register */
  __IO  uint32_t                       GMAC_SVLAN;         /**< Offset: 0xC0 (R/W  32) Stacked VLAN Register */
  __IO  uint32_t                       GMAC_TPFCP;         /**< Offset: 0xC4 (R/W  32) Transmit PFC Pause Register */
  __IO  uint32_t                       GMAC_SAMB1;         /**< Offset: 0xC8 (R/W  32) Specific Address 1 Mask Bottom Register */
  __IO  uint32_t                       GMAC_SAMT1;         /**< Offset: 0xCC (R/W  32) Specific Address 1 Mask Top Register */
  __IO  uint32_t                       GMAC_AMRX;          /**< Offset: 0xD0 (R/W  32) System Memory Address Mask for RX Data Buffer Accesses Register */
  __IO  uint32_t                       GMAC_RXUDAR;        /**< Offset: 0xD4 (R/W  32) PTP RX Unicast IP Destination Address Register */
  __IO  uint32_t                       GMAC_TXUDAR;        /**< Offset: 0xD8 (R/W  32) PTP TX Unicast IP Destination Address Register */
  __IO  uint32_t                       GMAC_NSC;           /**< Offset: 0xDC (R/W  32) 1588 Timer Nanosecond Comparison Register */
  __IO  uint32_t                       GMAC_SCL;           /**< Offset: 0xE0 (R/W  32) 1588 Timer Second Comparison Low Register */
  __IO  uint32_t                       GMAC_SCH;           /**< Offset: 0xE4 (R/W  32) 1588 Timer Second Comparison High Register */
  __I   uint32_t                       GMAC_EFTSH;         /**< Offset: 0xE8 (R/   32) PTP Event Frame Transmitted Seconds High Register */
  __I   uint32_t                       GMAC_EFRSH;         /**< Offset: 0xEC (R/   32) PTP Event Frame Received Seconds High Register */
  __I   uint32_t                       GMAC_PEFTSH;        /**< Offset: 0xF0 (R/   32) PTP Peer Event Frame Transmitted Seconds High Register */
  __I   uint32_t                       GMAC_PEFRSH;        /**< Offset: 0xF4 (R/   32) PTP Peer Event Frame Received Seconds High Register */
  __I   uint8_t                        Reserved4[0x08];
  __I   uint32_t                       GMAC_OTLO;          /**< Offset: 0x100 (R/   32) Octets Transmitted Low Register */
  __I   uint32_t                       GMAC_OTHI;          /**< Offset: 0x104 (R/   32) Octets Transmitted High Register */
  __I   uint32_t                       GMAC_FT;            /**< Offset: 0x108 (R/   32) Frames Transmitted Register */
  __I   uint32_t                       GMAC_BCFT;          /**< Offset: 0x10C (R/   32) Broadcast Frames Transmitted Register */
  __I   uint32_t                       GMAC_MFT;           /**< Offset: 0x110 (R/   32) Multicast Frames Transmitted Register */
  __I   uint32_t                       GMAC_PFT;           /**< Offset: 0x114 (R/   32) Pause Frames Transmitted Register */
  __I   uint32_t                       GMAC_BFT64;         /**< Offset: 0x118 (R/   32) 64 Byte Frames Transmitted Register */
  __I   uint32_t                       GMAC_TBFT127;       /**< Offset: 0x11C (R/   32) 65 to 127 Byte Frames Transmitted Register */
  __I   uint32_t                       GMAC_TBFT255;       /**< Offset: 0x120 (R/   32) 128 to 255 Byte Frames Transmitted Register */
  __I   uint32_t                       GMAC_TBFT511;       /**< Offset: 0x124 (R/   32) 256 to 511 Byte Frames Transmitted Register */
  __I   uint32_t                       GMAC_TBFT1023;      /**< Offset: 0x128 (R/   32) 512 to 1023 Byte Frames Transmitted Register */
  __I   uint32_t                       GMAC_TBFT1518;      /**< Offset: 0x12C (R/   32) 1024 to 1518 Byte Frames Transmitted Register */
  __I   uint32_t                       GMAC_GTBFT1518;     /**< Offset: 0x130 (R/   32) Greater Than 1518 Byte Frames Transmitted Register */
  __I   uint32_t                       GMAC_TUR;           /**< Offset: 0x134 (R/   32) Transmit Underruns Register */
  __I   uint32_t                       GMAC_SCF;           /**< Offset: 0x138 (R/   32) Single Collision Frames Register */
  __I   uint32_t                       GMAC_MCF;           /**< Offset: 0x13C (R/   32) Multiple Collision Frames Register */
  __I   uint32_t                       GMAC_EC;            /**< Offset: 0x140 (R/   32) Excessive Collisions Register */
  __I   uint32_t                       GMAC_LC;            /**< Offset: 0x144 (R/   32) Late Collisions Register */
  __I   uint32_t                       GMAC_DTF;           /**< Offset: 0x148 (R/   32) Deferred Transmission Frames Register */
  __I   uint32_t                       GMAC_CSE;           /**< Offset: 0x14C (R/   32) Carrier Sense Errors Register */
  __I   uint32_t                       GMAC_ORLO;          /**< Offset: 0x150 (R/   32) Octets Received Low Received Register */
  __I   uint32_t                       GMAC_ORHI;          /**< Offset: 0x154 (R/   32) Octets Received High Received Register */
  __I   uint32_t                       GMAC_FR;            /**< Offset: 0x158 (R/   32) Frames Received Register */
  __I   uint32_t                       GMAC_BCFR;          /**< Offset: 0x15C (R/   32) Broadcast Frames Received Register */
  __I   uint32_t                       GMAC_MFR;           /**< Offset: 0x160 (R/   32) Multicast Frames Received Register */
  __I   uint32_t                       GMAC_PFR;           /**< Offset: 0x164 (R/   32) Pause Frames Received Register */
  __I   uint32_t                       GMAC_BFR64;         /**< Offset: 0x168 (R/   32) 64 Byte Frames Received Register */
  __I   uint32_t                       GMAC_TBFR127;       /**< Offset: 0x16C (R/   32) 65 to 127 Byte Frames Received Register */
  __I   uint32_t                       GMAC_TBFR255;       /**< Offset: 0x170 (R/   32) 128 to 255 Byte Frames Received Register */
  __I   uint32_t                       GMAC_TBFR511;       /**< Offset: 0x174 (R/   32) 256 to 511 Byte Frames Received Register */
  __I   uint32_t                       GMAC_TBFR1023;      /**< Offset: 0x178 (R/   32) 512 to 1023 Byte Frames Received Register */
  __I   uint32_t                       GMAC_TBFR1518;      /**< Offset: 0x17C (R/   32) 1024 to 1518 Byte Frames Received Register */
  __I   uint32_t                       GMAC_TMXBFR;        /**< Offset: 0x180 (R/   32) 1519 to Maximum Byte Frames Received Register */
  __I   uint32_t                       GMAC_UFR;           /**< Offset: 0x184 (R/   32) Undersize Frames Received Register */
  __I   uint32_t                       GMAC_OFR;           /**< Offset: 0x188 (R/   32) Oversize Frames Received Register */
  __I   uint32_t                       GMAC_JR;            /**< Offset: 0x18C (R/   32) Jabbers Received Register */
  __I   uint32_t                       GMAC_FCSE;          /**< Offset: 0x190 (R/   32) Frame Check Sequence Errors Register */
  __I   uint32_t                       GMAC_LFFE;          /**< Offset: 0x194 (R/   32) Length Field Frame Errors Register */
  __I   uint32_t                       GMAC_RSE;           /**< Offset: 0x198 (R/   32) Receive Symbol Errors Register */
  __I   uint32_t                       GMAC_AE;            /**< Offset: 0x19C (R/   32) Alignment Errors Register */
  __I   uint32_t                       GMAC_RRE;           /**< Offset: 0x1A0 (R/   32) Receive Resource Errors Register */
  __I   uint32_t                       GMAC_ROE;           /**< Offset: 0x1A4 (R/   32) Receive Overrun Register */
  __I   uint32_t                       GMAC_IHCE;          /**< Offset: 0x1A8 (R/   32) IP Header Checksum Errors Register */
  __I   uint32_t                       GMAC_TCE;           /**< Offset: 0x1AC (R/   32) TCP Checksum Errors Register */
  __I   uint32_t                       GMAC_UCE;           /**< Offset: 0x1B0 (R/   32) UDP Checksum Errors Register */
  __I   uint32_t                       GMAC_FLRXPCR;       /**< Offset: 0x1B4 (R/   32) Flushed Received Packets Counter Register */
  __I   uint8_t                        Reserved5[0x04];
  __IO  uint32_t                       GMAC_TISUBN;        /**< Offset: 0x1BC (R/W  32) 1588 Timer Increment Sub-nanoseconds Register */
  __IO  uint32_t                       GMAC_TSH;           /**< Offset: 0x1C0 (R/W  32) 1588 Timer Seconds High Register */
  __I   uint8_t                        Reserved6[0x0C];
  __IO  uint32_t                       GMAC_TSL;           /**< Offset: 0x1D0 (R/W  32) 1588 Timer Seconds Low Register */
  __IO  uint32_t                       GMAC_TN;            /**< Offset: 0x1D4 (R/W  32) 1588 Timer Nanoseconds Register */
  __O   uint32_t                       GMAC_TA;            /**< Offset: 0x1D8 ( /W  32) 1588 Timer Adjust Register */
  __IO  uint32_t                       GMAC_TI;            /**< Offset: 0x1DC (R/W  32) 1588 Timer Increment Register */
  __I   uint32_t                       GMAC_EFTSL;         /**< Offset: 0x1E0 (R/   32) PTP Event Frame Transmitted Seconds Low Register */
  __I   uint32_t                       GMAC_EFTN;          /**< Offset: 0x1E4 (R/   32) PTP Event Frame Transmitted Nanoseconds Register */
  __I   uint32_t                       GMAC_EFRSL;         /**< Offset: 0x1E8 (R/   32) PTP Event Frame Received Seconds Low Register */
  __I   uint32_t                       GMAC_EFRN;          /**< Offset: 0x1EC (R/   32) PTP Event Frame Received Nanoseconds Register */
  __I   uint32_t                       GMAC_PEFTSL;        /**< Offset: 0x1F0 (R/   32) PTP Peer Event Frame Transmitted Seconds Low Register */
  __I   uint32_t                       GMAC_PEFTN;         /**< Offset: 0x1F4 (R/   32) PTP Peer Event Frame Transmitted Nanoseconds Register */
  __I   uint32_t                       GMAC_PEFRSL;        /**< Offset: 0x1F8 (R/   32) PTP Peer Event Frame Received Seconds Low Register */
  __I   uint32_t                       GMAC_PEFRN;         /**< Offset: 0x1FC (R/   32) PTP Peer Event Frame Received Nanoseconds Register */
  __I   uint8_t                        Reserved7[0x70];
  __I   uint32_t                       GMAC_RXLPI;         /**< Offset: 0x270 (R/   32) Received LPI Transitions */
  __I   uint32_t                       GMAC_RXLPITIME;     /**< Offset: 0x274 (R/   32) Received LPI Time */
  __I   uint32_t                       GMAC_TXLPI;         /**< Offset: 0x278 (R/   32) Transmit LPI Transitions */
  __I   uint32_t                       GMAC_TXLPITIME;     /**< Offset: 0x27C (R/   32) Transmit LPI Time */
  __I   uint8_t                        Reserved8[0x180];
  __I   uint32_t                       GMAC_ISRPQ[2];      /**< Offset: 0x400 (R/   32) Interrupt Status Register Priority Queue (index = 1) */
  __I   uint8_t                        Reserved9[0x38];
  __IO  uint32_t                       GMAC_TBQBAPQ[2];    /**< Offset: 0x440 (R/W  32) Transmit Buffer Queue Base Address Register Priority Queue (index = 1) */
  __I   uint8_t                        Reserved10[0x38];
  __IO  uint32_t                       GMAC_RBQBAPQ[2];    /**< Offset: 0x480 (R/W  32) Receive Buffer Queue Base Address Register Priority Queue (index = 1) */
  __I   uint8_t                        Reserved11[0x18];
  __IO  uint32_t                       GMAC_RBSRPQ[2];     /**< Offset: 0x4A0 (R/W  32) Receive Buffer Size Register Priority Queue (index = 1) */
  __I   uint8_t                        Reserved12[0x14];
  __IO  uint32_t                       GMAC_CBSCR;         /**< Offset: 0x4BC (R/W  32) Credit-Based Shaping Control Register */
  __IO  uint32_t                       GMAC_CBSISQA;       /**< Offset: 0x4C0 (R/W  32) Credit-Based Shaping IdleSlope Register for Queue A */
  __IO  uint32_t                       GMAC_CBSISQB;       /**< Offset: 0x4C4 (R/W  32) Credit-Based Shaping IdleSlope Register for Queue B */
  __IO  uint32_t                       GMAC_TQUBA;         /**< Offset: 0x4C8 (R/W  32) 32 MSB Transmit Buffer Descriptor Queue Base Address Register */
  __IO  uint32_t                       GMAC_TXBDCTRL;      /**< Offset: 0x4CC (R/W  32) Transmit Buffer Data Control Register */
  __IO  uint32_t                       GMAC_RXBDCTRL;      /**< Offset: 0x4D0 (R/W  32) Receive Buffer Data Control Register */
  __IO  uint32_t                       GMAC_RQUBA;         /**< Offset: 0x4D4 (R/W  32) 32 MSB Receive Buffer Descriptor Queue Base Address Register */
  __I   uint8_t                        Reserved13[0x28];
  __IO  uint32_t                       GMAC_ST1RPQ;        /**< Offset: 0x500 (R/W  32) Screening Type 1 Register Priority Queue (index = 0) */
  __I   uint8_t                        Reserved14[0x3C];
  __IO  uint32_t                       GMAC_ST2RPQ;        /**< Offset: 0x540 (R/W  32) Screening Type 2 Register Priority Queue (index = 0) */
  __I   uint8_t                        Reserved15[0x3C];
  __IO  uint32_t                       GMAC_TSCTL;         /**< Offset: 0x580 (R/W  32) Transmit Schedule Control Register */
  __I   uint8_t                        Reserved16[0x0C];
  __IO  uint32_t                       GMAC_TQBWRL0;       /**< Offset: 0x590 (R/W  32) Transmit Queue Bandwidth Rate Limit 0 Register */
  __I   uint8_t                        Reserved17[0x0C];
  __IO  uint32_t                       GMAC_TQSA;          /**< Offset: 0x5A0 (R/W  32) Transmit Queue Segment Allocation Register */
  __I   uint8_t                        Reserved18[0x5C];
  __O   uint32_t                       GMAC_IERPQ[2];      /**< Offset: 0x600 ( /W  32) Interrupt Enable Register Priority Queue (index = 1) */
  __I   uint8_t                        Reserved19[0x18];
  __O   uint32_t                       GMAC_IDRPQ[2];      /**< Offset: 0x620 ( /W  32) Interrupt Disable Register Priority Queue (index = 1) */
  __I   uint8_t                        Reserved20[0x18];
  __IO  uint32_t                       GMAC_IMRPQ[2];      /**< Offset: 0x640 (R/W  32) Interrupt Mask Register Priority Queue (index = 1) */
  __I   uint8_t                        Reserved21[0x98];
  __IO  uint32_t                       GMAC_ST2ER;         /**< Offset: 0x6E0 (R/W  32) Screening Type 2 Ethertype Register (index = 0) */
  __I   uint8_t                        Reserved22[0x1C];
        gmac_st2cw_registers_t         GMAC_ST2CW[GMAC_ST2CW_NUMBER]; /**< Offset: 0x700  */
} gmac_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _SAMA5D_GMAC_COMPONENT_H_ */
