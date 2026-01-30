/*
 * Component description for MCAN
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
#ifndef _SAMA5D_MCAN_COMPONENT_H_
#define _SAMA5D_MCAN_COMPONENT_H_

/* ************************************************************************** */
/*   SOFTWARE API DEFINITION FOR MCAN                                         */
/* ************************************************************************** */

/* -------- MCAN_RXBE_0 : (MCAN Offset: 0x00) (R/W 32) Rx Buffer Element 0 -------- */
#define MCAN_RXBE_0_ID_Pos                    _UINT32_(0)                                          /* (MCAN_RXBE_0) Identifier Position */
#define MCAN_RXBE_0_ID_Msk                    (_UINT32_(0x1FFFFFFF) << MCAN_RXBE_0_ID_Pos)         /* (MCAN_RXBE_0) Identifier Mask */
#define MCAN_RXBE_0_ID(value)                 (MCAN_RXBE_0_ID_Msk & (_UINT32_(value) << MCAN_RXBE_0_ID_Pos)) /* Assigment of value for ID in the MCAN_RXBE_0 register */
#define MCAN_RXBE_0_RTR_Pos                   _UINT32_(29)                                         /* (MCAN_RXBE_0) Remote Transmission Request Position */
#define MCAN_RXBE_0_RTR_Msk                   (_UINT32_(0x1) << MCAN_RXBE_0_RTR_Pos)               /* (MCAN_RXBE_0) Remote Transmission Request Mask */
#define MCAN_RXBE_0_RTR(value)                (MCAN_RXBE_0_RTR_Msk & (_UINT32_(value) << MCAN_RXBE_0_RTR_Pos)) /* Assigment of value for RTR in the MCAN_RXBE_0 register */
#define MCAN_RXBE_0_XTD_Pos                   _UINT32_(30)                                         /* (MCAN_RXBE_0) Extended Identifier Position */
#define MCAN_RXBE_0_XTD_Msk                   (_UINT32_(0x1) << MCAN_RXBE_0_XTD_Pos)               /* (MCAN_RXBE_0) Extended Identifier Mask */
#define MCAN_RXBE_0_XTD(value)                (MCAN_RXBE_0_XTD_Msk & (_UINT32_(value) << MCAN_RXBE_0_XTD_Pos)) /* Assigment of value for XTD in the MCAN_RXBE_0 register */
#define MCAN_RXBE_0_ESI_Pos                   _UINT32_(31)                                         /* (MCAN_RXBE_0) Error State Indicator Position */
#define MCAN_RXBE_0_ESI_Msk                   (_UINT32_(0x1) << MCAN_RXBE_0_ESI_Pos)               /* (MCAN_RXBE_0) Error State Indicator Mask */
#define MCAN_RXBE_0_ESI(value)                (MCAN_RXBE_0_ESI_Msk & (_UINT32_(value) << MCAN_RXBE_0_ESI_Pos)) /* Assigment of value for ESI in the MCAN_RXBE_0 register */
#define MCAN_RXBE_0_Msk                       _UINT32_(0xFFFFFFFF)                                 /* (MCAN_RXBE_0) Register Mask  */


/* -------- MCAN_RXBE_1 : (MCAN Offset: 0x04) (R/W 32) Rx Buffer Element 1 -------- */
#define MCAN_RXBE_1_RXTS_Pos                  _UINT32_(0)                                          /* (MCAN_RXBE_1) Rx Timestamp Position */
#define MCAN_RXBE_1_RXTS_Msk                  (_UINT32_(0xFFFF) << MCAN_RXBE_1_RXTS_Pos)           /* (MCAN_RXBE_1) Rx Timestamp Mask */
#define MCAN_RXBE_1_RXTS(value)               (MCAN_RXBE_1_RXTS_Msk & (_UINT32_(value) << MCAN_RXBE_1_RXTS_Pos)) /* Assigment of value for RXTS in the MCAN_RXBE_1 register */
#define MCAN_RXBE_1_DLC_Pos                   _UINT32_(16)                                         /* (MCAN_RXBE_1) Data Length Code Position */
#define MCAN_RXBE_1_DLC_Msk                   (_UINT32_(0xF) << MCAN_RXBE_1_DLC_Pos)               /* (MCAN_RXBE_1) Data Length Code Mask */
#define MCAN_RXBE_1_DLC(value)                (MCAN_RXBE_1_DLC_Msk & (_UINT32_(value) << MCAN_RXBE_1_DLC_Pos)) /* Assigment of value for DLC in the MCAN_RXBE_1 register */
#define MCAN_RXBE_1_BRS_Pos                   _UINT32_(20)                                         /* (MCAN_RXBE_1) Bit Rate Switch Position */
#define MCAN_RXBE_1_BRS_Msk                   (_UINT32_(0x1) << MCAN_RXBE_1_BRS_Pos)               /* (MCAN_RXBE_1) Bit Rate Switch Mask */
#define MCAN_RXBE_1_BRS(value)                (MCAN_RXBE_1_BRS_Msk & (_UINT32_(value) << MCAN_RXBE_1_BRS_Pos)) /* Assigment of value for BRS in the MCAN_RXBE_1 register */
#define MCAN_RXBE_1_FDF_Pos                   _UINT32_(21)                                         /* (MCAN_RXBE_1) FD Format Position */
#define MCAN_RXBE_1_FDF_Msk                   (_UINT32_(0x1) << MCAN_RXBE_1_FDF_Pos)               /* (MCAN_RXBE_1) FD Format Mask */
#define MCAN_RXBE_1_FDF(value)                (MCAN_RXBE_1_FDF_Msk & (_UINT32_(value) << MCAN_RXBE_1_FDF_Pos)) /* Assigment of value for FDF in the MCAN_RXBE_1 register */
#define MCAN_RXBE_1_FIDX_Pos                  _UINT32_(24)                                         /* (MCAN_RXBE_1) Filter Index Position */
#define MCAN_RXBE_1_FIDX_Msk                  (_UINT32_(0x7F) << MCAN_RXBE_1_FIDX_Pos)             /* (MCAN_RXBE_1) Filter Index Mask */
#define MCAN_RXBE_1_FIDX(value)               (MCAN_RXBE_1_FIDX_Msk & (_UINT32_(value) << MCAN_RXBE_1_FIDX_Pos)) /* Assigment of value for FIDX in the MCAN_RXBE_1 register */
#define MCAN_RXBE_1_ANMF_Pos                  _UINT32_(31)                                         /* (MCAN_RXBE_1) Accepted Non-matching Frame Position */
#define MCAN_RXBE_1_ANMF_Msk                  (_UINT32_(0x1) << MCAN_RXBE_1_ANMF_Pos)              /* (MCAN_RXBE_1) Accepted Non-matching Frame Mask */
#define MCAN_RXBE_1_ANMF(value)               (MCAN_RXBE_1_ANMF_Msk & (_UINT32_(value) << MCAN_RXBE_1_ANMF_Pos)) /* Assigment of value for ANMF in the MCAN_RXBE_1 register */
#define MCAN_RXBE_1_Msk                       _UINT32_(0xFF3FFFFF)                                 /* (MCAN_RXBE_1) Register Mask  */


/* -------- MCAN_RXBE_DATA : (MCAN Offset: 0x08) (R/W 32) Rx Buffer Element Data -------- */
#define MCAN_RXBE_DATA_DB0_Pos                _UINT32_(0)                                          /* (MCAN_RXBE_DATA) Data Byte 0 Position */
#define MCAN_RXBE_DATA_DB0_Msk                (_UINT32_(0xFF) << MCAN_RXBE_DATA_DB0_Pos)           /* (MCAN_RXBE_DATA) Data Byte 0 Mask */
#define MCAN_RXBE_DATA_DB0(value)             (MCAN_RXBE_DATA_DB0_Msk & (_UINT32_(value) << MCAN_RXBE_DATA_DB0_Pos)) /* Assigment of value for DB0 in the MCAN_RXBE_DATA register */
#define MCAN_RXBE_DATA_DB1_Pos                _UINT32_(8)                                          /* (MCAN_RXBE_DATA) Data Byte 1 Position */
#define MCAN_RXBE_DATA_DB1_Msk                (_UINT32_(0xFF) << MCAN_RXBE_DATA_DB1_Pos)           /* (MCAN_RXBE_DATA) Data Byte 1 Mask */
#define MCAN_RXBE_DATA_DB1(value)             (MCAN_RXBE_DATA_DB1_Msk & (_UINT32_(value) << MCAN_RXBE_DATA_DB1_Pos)) /* Assigment of value for DB1 in the MCAN_RXBE_DATA register */
#define MCAN_RXBE_DATA_DB2_Pos                _UINT32_(16)                                         /* (MCAN_RXBE_DATA) Data Byte 2 Position */
#define MCAN_RXBE_DATA_DB2_Msk                (_UINT32_(0xFF) << MCAN_RXBE_DATA_DB2_Pos)           /* (MCAN_RXBE_DATA) Data Byte 2 Mask */
#define MCAN_RXBE_DATA_DB2(value)             (MCAN_RXBE_DATA_DB2_Msk & (_UINT32_(value) << MCAN_RXBE_DATA_DB2_Pos)) /* Assigment of value for DB2 in the MCAN_RXBE_DATA register */
#define MCAN_RXBE_DATA_DB3_Pos                _UINT32_(24)                                         /* (MCAN_RXBE_DATA) Data Byte 3 Position */
#define MCAN_RXBE_DATA_DB3_Msk                (_UINT32_(0xFF) << MCAN_RXBE_DATA_DB3_Pos)           /* (MCAN_RXBE_DATA) Data Byte 3 Mask */
#define MCAN_RXBE_DATA_DB3(value)             (MCAN_RXBE_DATA_DB3_Msk & (_UINT32_(value) << MCAN_RXBE_DATA_DB3_Pos)) /* Assigment of value for DB3 in the MCAN_RXBE_DATA register */
#define MCAN_RXBE_DATA_Msk                    _UINT32_(0xFFFFFFFF)                                 /* (MCAN_RXBE_DATA) Register Mask  */


/* -------- MCAN_RXF0E_0 : (MCAN Offset: 0x00) (R/W 32) Rx FIFO 0 Element 0 -------- */
#define MCAN_RXF0E_0_ID_Pos                   _UINT32_(0)                                          /* (MCAN_RXF0E_0) Identifier Position */
#define MCAN_RXF0E_0_ID_Msk                   (_UINT32_(0x1FFFFFFF) << MCAN_RXF0E_0_ID_Pos)        /* (MCAN_RXF0E_0) Identifier Mask */
#define MCAN_RXF0E_0_ID(value)                (MCAN_RXF0E_0_ID_Msk & (_UINT32_(value) << MCAN_RXF0E_0_ID_Pos)) /* Assigment of value for ID in the MCAN_RXF0E_0 register */
#define MCAN_RXF0E_0_RTR_Pos                  _UINT32_(29)                                         /* (MCAN_RXF0E_0) Remote Transmission Request Position */
#define MCAN_RXF0E_0_RTR_Msk                  (_UINT32_(0x1) << MCAN_RXF0E_0_RTR_Pos)              /* (MCAN_RXF0E_0) Remote Transmission Request Mask */
#define MCAN_RXF0E_0_RTR(value)               (MCAN_RXF0E_0_RTR_Msk & (_UINT32_(value) << MCAN_RXF0E_0_RTR_Pos)) /* Assigment of value for RTR in the MCAN_RXF0E_0 register */
#define MCAN_RXF0E_0_XTD_Pos                  _UINT32_(30)                                         /* (MCAN_RXF0E_0) Extended Identifier Position */
#define MCAN_RXF0E_0_XTD_Msk                  (_UINT32_(0x1) << MCAN_RXF0E_0_XTD_Pos)              /* (MCAN_RXF0E_0) Extended Identifier Mask */
#define MCAN_RXF0E_0_XTD(value)               (MCAN_RXF0E_0_XTD_Msk & (_UINT32_(value) << MCAN_RXF0E_0_XTD_Pos)) /* Assigment of value for XTD in the MCAN_RXF0E_0 register */
#define MCAN_RXF0E_0_ESI_Pos                  _UINT32_(31)                                         /* (MCAN_RXF0E_0) Error State Indicator Position */
#define MCAN_RXF0E_0_ESI_Msk                  (_UINT32_(0x1) << MCAN_RXF0E_0_ESI_Pos)              /* (MCAN_RXF0E_0) Error State Indicator Mask */
#define MCAN_RXF0E_0_ESI(value)               (MCAN_RXF0E_0_ESI_Msk & (_UINT32_(value) << MCAN_RXF0E_0_ESI_Pos)) /* Assigment of value for ESI in the MCAN_RXF0E_0 register */
#define MCAN_RXF0E_0_Msk                      _UINT32_(0xFFFFFFFF)                                 /* (MCAN_RXF0E_0) Register Mask  */


/* -------- MCAN_RXF0E_1 : (MCAN Offset: 0x04) (R/W 32) Rx FIFO 0 Element 1 -------- */
#define MCAN_RXF0E_1_RXTS_Pos                 _UINT32_(0)                                          /* (MCAN_RXF0E_1) Rx Timestamp Position */
#define MCAN_RXF0E_1_RXTS_Msk                 (_UINT32_(0xFFFF) << MCAN_RXF0E_1_RXTS_Pos)          /* (MCAN_RXF0E_1) Rx Timestamp Mask */
#define MCAN_RXF0E_1_RXTS(value)              (MCAN_RXF0E_1_RXTS_Msk & (_UINT32_(value) << MCAN_RXF0E_1_RXTS_Pos)) /* Assigment of value for RXTS in the MCAN_RXF0E_1 register */
#define MCAN_RXF0E_1_DLC_Pos                  _UINT32_(16)                                         /* (MCAN_RXF0E_1) Data Length Code Position */
#define MCAN_RXF0E_1_DLC_Msk                  (_UINT32_(0xF) << MCAN_RXF0E_1_DLC_Pos)              /* (MCAN_RXF0E_1) Data Length Code Mask */
#define MCAN_RXF0E_1_DLC(value)               (MCAN_RXF0E_1_DLC_Msk & (_UINT32_(value) << MCAN_RXF0E_1_DLC_Pos)) /* Assigment of value for DLC in the MCAN_RXF0E_1 register */
#define MCAN_RXF0E_1_BRS_Pos                  _UINT32_(20)                                         /* (MCAN_RXF0E_1) Bit Rate Switch Position */
#define MCAN_RXF0E_1_BRS_Msk                  (_UINT32_(0x1) << MCAN_RXF0E_1_BRS_Pos)              /* (MCAN_RXF0E_1) Bit Rate Switch Mask */
#define MCAN_RXF0E_1_BRS(value)               (MCAN_RXF0E_1_BRS_Msk & (_UINT32_(value) << MCAN_RXF0E_1_BRS_Pos)) /* Assigment of value for BRS in the MCAN_RXF0E_1 register */
#define MCAN_RXF0E_1_FDF_Pos                  _UINT32_(21)                                         /* (MCAN_RXF0E_1) FD Format Position */
#define MCAN_RXF0E_1_FDF_Msk                  (_UINT32_(0x1) << MCAN_RXF0E_1_FDF_Pos)              /* (MCAN_RXF0E_1) FD Format Mask */
#define MCAN_RXF0E_1_FDF(value)               (MCAN_RXF0E_1_FDF_Msk & (_UINT32_(value) << MCAN_RXF0E_1_FDF_Pos)) /* Assigment of value for FDF in the MCAN_RXF0E_1 register */
#define MCAN_RXF0E_1_FIDX_Pos                 _UINT32_(24)                                         /* (MCAN_RXF0E_1) Filter Index Position */
#define MCAN_RXF0E_1_FIDX_Msk                 (_UINT32_(0x7F) << MCAN_RXF0E_1_FIDX_Pos)            /* (MCAN_RXF0E_1) Filter Index Mask */
#define MCAN_RXF0E_1_FIDX(value)              (MCAN_RXF0E_1_FIDX_Msk & (_UINT32_(value) << MCAN_RXF0E_1_FIDX_Pos)) /* Assigment of value for FIDX in the MCAN_RXF0E_1 register */
#define MCAN_RXF0E_1_ANMF_Pos                 _UINT32_(31)                                         /* (MCAN_RXF0E_1) Accepted Non-matching Frame Position */
#define MCAN_RXF0E_1_ANMF_Msk                 (_UINT32_(0x1) << MCAN_RXF0E_1_ANMF_Pos)             /* (MCAN_RXF0E_1) Accepted Non-matching Frame Mask */
#define MCAN_RXF0E_1_ANMF(value)              (MCAN_RXF0E_1_ANMF_Msk & (_UINT32_(value) << MCAN_RXF0E_1_ANMF_Pos)) /* Assigment of value for ANMF in the MCAN_RXF0E_1 register */
#define MCAN_RXF0E_1_Msk                      _UINT32_(0xFF3FFFFF)                                 /* (MCAN_RXF0E_1) Register Mask  */


/* -------- MCAN_RXF0E_DATA : (MCAN Offset: 0x08) (R/W 32) Rx FIFO 0 Element Data -------- */
#define MCAN_RXF0E_DATA_DB0_Pos               _UINT32_(0)                                          /* (MCAN_RXF0E_DATA) Data Byte 0 Position */
#define MCAN_RXF0E_DATA_DB0_Msk               (_UINT32_(0xFF) << MCAN_RXF0E_DATA_DB0_Pos)          /* (MCAN_RXF0E_DATA) Data Byte 0 Mask */
#define MCAN_RXF0E_DATA_DB0(value)            (MCAN_RXF0E_DATA_DB0_Msk & (_UINT32_(value) << MCAN_RXF0E_DATA_DB0_Pos)) /* Assigment of value for DB0 in the MCAN_RXF0E_DATA register */
#define MCAN_RXF0E_DATA_DB1_Pos               _UINT32_(8)                                          /* (MCAN_RXF0E_DATA) Data Byte 1 Position */
#define MCAN_RXF0E_DATA_DB1_Msk               (_UINT32_(0xFF) << MCAN_RXF0E_DATA_DB1_Pos)          /* (MCAN_RXF0E_DATA) Data Byte 1 Mask */
#define MCAN_RXF0E_DATA_DB1(value)            (MCAN_RXF0E_DATA_DB1_Msk & (_UINT32_(value) << MCAN_RXF0E_DATA_DB1_Pos)) /* Assigment of value for DB1 in the MCAN_RXF0E_DATA register */
#define MCAN_RXF0E_DATA_DB2_Pos               _UINT32_(16)                                         /* (MCAN_RXF0E_DATA) Data Byte 2 Position */
#define MCAN_RXF0E_DATA_DB2_Msk               (_UINT32_(0xFF) << MCAN_RXF0E_DATA_DB2_Pos)          /* (MCAN_RXF0E_DATA) Data Byte 2 Mask */
#define MCAN_RXF0E_DATA_DB2(value)            (MCAN_RXF0E_DATA_DB2_Msk & (_UINT32_(value) << MCAN_RXF0E_DATA_DB2_Pos)) /* Assigment of value for DB2 in the MCAN_RXF0E_DATA register */
#define MCAN_RXF0E_DATA_DB3_Pos               _UINT32_(24)                                         /* (MCAN_RXF0E_DATA) Data Byte 3 Position */
#define MCAN_RXF0E_DATA_DB3_Msk               (_UINT32_(0xFF) << MCAN_RXF0E_DATA_DB3_Pos)          /* (MCAN_RXF0E_DATA) Data Byte 3 Mask */
#define MCAN_RXF0E_DATA_DB3(value)            (MCAN_RXF0E_DATA_DB3_Msk & (_UINT32_(value) << MCAN_RXF0E_DATA_DB3_Pos)) /* Assigment of value for DB3 in the MCAN_RXF0E_DATA register */
#define MCAN_RXF0E_DATA_Msk                   _UINT32_(0xFFFFFFFF)                                 /* (MCAN_RXF0E_DATA) Register Mask  */


/* -------- MCAN_RXF1E_0 : (MCAN Offset: 0x00) (R/W 32) Rx FIFO 1 Element 0 -------- */
#define MCAN_RXF1E_0_ID_Pos                   _UINT32_(0)                                          /* (MCAN_RXF1E_0) Identifier Position */
#define MCAN_RXF1E_0_ID_Msk                   (_UINT32_(0x1FFFFFFF) << MCAN_RXF1E_0_ID_Pos)        /* (MCAN_RXF1E_0) Identifier Mask */
#define MCAN_RXF1E_0_ID(value)                (MCAN_RXF1E_0_ID_Msk & (_UINT32_(value) << MCAN_RXF1E_0_ID_Pos)) /* Assigment of value for ID in the MCAN_RXF1E_0 register */
#define MCAN_RXF1E_0_RTR_Pos                  _UINT32_(29)                                         /* (MCAN_RXF1E_0) Remote Transmission Request Position */
#define MCAN_RXF1E_0_RTR_Msk                  (_UINT32_(0x1) << MCAN_RXF1E_0_RTR_Pos)              /* (MCAN_RXF1E_0) Remote Transmission Request Mask */
#define MCAN_RXF1E_0_RTR(value)               (MCAN_RXF1E_0_RTR_Msk & (_UINT32_(value) << MCAN_RXF1E_0_RTR_Pos)) /* Assigment of value for RTR in the MCAN_RXF1E_0 register */
#define MCAN_RXF1E_0_XTD_Pos                  _UINT32_(30)                                         /* (MCAN_RXF1E_0) Extended Identifier Position */
#define MCAN_RXF1E_0_XTD_Msk                  (_UINT32_(0x1) << MCAN_RXF1E_0_XTD_Pos)              /* (MCAN_RXF1E_0) Extended Identifier Mask */
#define MCAN_RXF1E_0_XTD(value)               (MCAN_RXF1E_0_XTD_Msk & (_UINT32_(value) << MCAN_RXF1E_0_XTD_Pos)) /* Assigment of value for XTD in the MCAN_RXF1E_0 register */
#define MCAN_RXF1E_0_ESI_Pos                  _UINT32_(31)                                         /* (MCAN_RXF1E_0) Error State Indicator Position */
#define MCAN_RXF1E_0_ESI_Msk                  (_UINT32_(0x1) << MCAN_RXF1E_0_ESI_Pos)              /* (MCAN_RXF1E_0) Error State Indicator Mask */
#define MCAN_RXF1E_0_ESI(value)               (MCAN_RXF1E_0_ESI_Msk & (_UINT32_(value) << MCAN_RXF1E_0_ESI_Pos)) /* Assigment of value for ESI in the MCAN_RXF1E_0 register */
#define MCAN_RXF1E_0_Msk                      _UINT32_(0xFFFFFFFF)                                 /* (MCAN_RXF1E_0) Register Mask  */


/* -------- MCAN_RXF1E_1 : (MCAN Offset: 0x04) (R/W 32) Rx FIFO 1 Element 1 -------- */
#define MCAN_RXF1E_1_RXTS_Pos                 _UINT32_(0)                                          /* (MCAN_RXF1E_1) Rx Timestamp Position */
#define MCAN_RXF1E_1_RXTS_Msk                 (_UINT32_(0xFFFF) << MCAN_RXF1E_1_RXTS_Pos)          /* (MCAN_RXF1E_1) Rx Timestamp Mask */
#define MCAN_RXF1E_1_RXTS(value)              (MCAN_RXF1E_1_RXTS_Msk & (_UINT32_(value) << MCAN_RXF1E_1_RXTS_Pos)) /* Assigment of value for RXTS in the MCAN_RXF1E_1 register */
#define MCAN_RXF1E_1_DLC_Pos                  _UINT32_(16)                                         /* (MCAN_RXF1E_1) Data Length Code Position */
#define MCAN_RXF1E_1_DLC_Msk                  (_UINT32_(0xF) << MCAN_RXF1E_1_DLC_Pos)              /* (MCAN_RXF1E_1) Data Length Code Mask */
#define MCAN_RXF1E_1_DLC(value)               (MCAN_RXF1E_1_DLC_Msk & (_UINT32_(value) << MCAN_RXF1E_1_DLC_Pos)) /* Assigment of value for DLC in the MCAN_RXF1E_1 register */
#define MCAN_RXF1E_1_BRS_Pos                  _UINT32_(20)                                         /* (MCAN_RXF1E_1) Bit Rate Switch Position */
#define MCAN_RXF1E_1_BRS_Msk                  (_UINT32_(0x1) << MCAN_RXF1E_1_BRS_Pos)              /* (MCAN_RXF1E_1) Bit Rate Switch Mask */
#define MCAN_RXF1E_1_BRS(value)               (MCAN_RXF1E_1_BRS_Msk & (_UINT32_(value) << MCAN_RXF1E_1_BRS_Pos)) /* Assigment of value for BRS in the MCAN_RXF1E_1 register */
#define MCAN_RXF1E_1_FDF_Pos                  _UINT32_(21)                                         /* (MCAN_RXF1E_1) FD Format Position */
#define MCAN_RXF1E_1_FDF_Msk                  (_UINT32_(0x1) << MCAN_RXF1E_1_FDF_Pos)              /* (MCAN_RXF1E_1) FD Format Mask */
#define MCAN_RXF1E_1_FDF(value)               (MCAN_RXF1E_1_FDF_Msk & (_UINT32_(value) << MCAN_RXF1E_1_FDF_Pos)) /* Assigment of value for FDF in the MCAN_RXF1E_1 register */
#define MCAN_RXF1E_1_FIDX_Pos                 _UINT32_(24)                                         /* (MCAN_RXF1E_1) Filter Index Position */
#define MCAN_RXF1E_1_FIDX_Msk                 (_UINT32_(0x7F) << MCAN_RXF1E_1_FIDX_Pos)            /* (MCAN_RXF1E_1) Filter Index Mask */
#define MCAN_RXF1E_1_FIDX(value)              (MCAN_RXF1E_1_FIDX_Msk & (_UINT32_(value) << MCAN_RXF1E_1_FIDX_Pos)) /* Assigment of value for FIDX in the MCAN_RXF1E_1 register */
#define MCAN_RXF1E_1_ANMF_Pos                 _UINT32_(31)                                         /* (MCAN_RXF1E_1) Accepted Non-matching Frame Position */
#define MCAN_RXF1E_1_ANMF_Msk                 (_UINT32_(0x1) << MCAN_RXF1E_1_ANMF_Pos)             /* (MCAN_RXF1E_1) Accepted Non-matching Frame Mask */
#define MCAN_RXF1E_1_ANMF(value)              (MCAN_RXF1E_1_ANMF_Msk & (_UINT32_(value) << MCAN_RXF1E_1_ANMF_Pos)) /* Assigment of value for ANMF in the MCAN_RXF1E_1 register */
#define MCAN_RXF1E_1_Msk                      _UINT32_(0xFF3FFFFF)                                 /* (MCAN_RXF1E_1) Register Mask  */


/* -------- MCAN_RXF1E_DATA : (MCAN Offset: 0x08) (R/W 32) Rx FIFO 1 Element Data -------- */
#define MCAN_RXF1E_DATA_DB0_Pos               _UINT32_(0)                                          /* (MCAN_RXF1E_DATA) Data Byte 0 Position */
#define MCAN_RXF1E_DATA_DB0_Msk               (_UINT32_(0xFF) << MCAN_RXF1E_DATA_DB0_Pos)          /* (MCAN_RXF1E_DATA) Data Byte 0 Mask */
#define MCAN_RXF1E_DATA_DB0(value)            (MCAN_RXF1E_DATA_DB0_Msk & (_UINT32_(value) << MCAN_RXF1E_DATA_DB0_Pos)) /* Assigment of value for DB0 in the MCAN_RXF1E_DATA register */
#define MCAN_RXF1E_DATA_DB1_Pos               _UINT32_(8)                                          /* (MCAN_RXF1E_DATA) Data Byte 1 Position */
#define MCAN_RXF1E_DATA_DB1_Msk               (_UINT32_(0xFF) << MCAN_RXF1E_DATA_DB1_Pos)          /* (MCAN_RXF1E_DATA) Data Byte 1 Mask */
#define MCAN_RXF1E_DATA_DB1(value)            (MCAN_RXF1E_DATA_DB1_Msk & (_UINT32_(value) << MCAN_RXF1E_DATA_DB1_Pos)) /* Assigment of value for DB1 in the MCAN_RXF1E_DATA register */
#define MCAN_RXF1E_DATA_DB2_Pos               _UINT32_(16)                                         /* (MCAN_RXF1E_DATA) Data Byte 2 Position */
#define MCAN_RXF1E_DATA_DB2_Msk               (_UINT32_(0xFF) << MCAN_RXF1E_DATA_DB2_Pos)          /* (MCAN_RXF1E_DATA) Data Byte 2 Mask */
#define MCAN_RXF1E_DATA_DB2(value)            (MCAN_RXF1E_DATA_DB2_Msk & (_UINT32_(value) << MCAN_RXF1E_DATA_DB2_Pos)) /* Assigment of value for DB2 in the MCAN_RXF1E_DATA register */
#define MCAN_RXF1E_DATA_DB3_Pos               _UINT32_(24)                                         /* (MCAN_RXF1E_DATA) Data Byte 3 Position */
#define MCAN_RXF1E_DATA_DB3_Msk               (_UINT32_(0xFF) << MCAN_RXF1E_DATA_DB3_Pos)          /* (MCAN_RXF1E_DATA) Data Byte 3 Mask */
#define MCAN_RXF1E_DATA_DB3(value)            (MCAN_RXF1E_DATA_DB3_Msk & (_UINT32_(value) << MCAN_RXF1E_DATA_DB3_Pos)) /* Assigment of value for DB3 in the MCAN_RXF1E_DATA register */
#define MCAN_RXF1E_DATA_Msk                   _UINT32_(0xFFFFFFFF)                                 /* (MCAN_RXF1E_DATA) Register Mask  */


/* -------- MCAN_TXBE_0 : (MCAN Offset: 0x00) (R/W 32) Tx Buffer Element 0 -------- */
#define MCAN_TXBE_0_ID_Pos                    _UINT32_(0)                                          /* (MCAN_TXBE_0) Identifier Position */
#define MCAN_TXBE_0_ID_Msk                    (_UINT32_(0x1FFFFFFF) << MCAN_TXBE_0_ID_Pos)         /* (MCAN_TXBE_0) Identifier Mask */
#define MCAN_TXBE_0_ID(value)                 (MCAN_TXBE_0_ID_Msk & (_UINT32_(value) << MCAN_TXBE_0_ID_Pos)) /* Assigment of value for ID in the MCAN_TXBE_0 register */
#define MCAN_TXBE_0_RTR_Pos                   _UINT32_(29)                                         /* (MCAN_TXBE_0) Remote Transmission Request Position */
#define MCAN_TXBE_0_RTR_Msk                   (_UINT32_(0x1) << MCAN_TXBE_0_RTR_Pos)               /* (MCAN_TXBE_0) Remote Transmission Request Mask */
#define MCAN_TXBE_0_RTR(value)                (MCAN_TXBE_0_RTR_Msk & (_UINT32_(value) << MCAN_TXBE_0_RTR_Pos)) /* Assigment of value for RTR in the MCAN_TXBE_0 register */
#define MCAN_TXBE_0_XTD_Pos                   _UINT32_(30)                                         /* (MCAN_TXBE_0) Extended Identifier Position */
#define MCAN_TXBE_0_XTD_Msk                   (_UINT32_(0x1) << MCAN_TXBE_0_XTD_Pos)               /* (MCAN_TXBE_0) Extended Identifier Mask */
#define MCAN_TXBE_0_XTD(value)                (MCAN_TXBE_0_XTD_Msk & (_UINT32_(value) << MCAN_TXBE_0_XTD_Pos)) /* Assigment of value for XTD in the MCAN_TXBE_0 register */
#define MCAN_TXBE_0_ESI_Pos                   _UINT32_(31)                                         /* (MCAN_TXBE_0) Error State Indicator Position */
#define MCAN_TXBE_0_ESI_Msk                   (_UINT32_(0x1) << MCAN_TXBE_0_ESI_Pos)               /* (MCAN_TXBE_0) Error State Indicator Mask */
#define MCAN_TXBE_0_ESI(value)                (MCAN_TXBE_0_ESI_Msk & (_UINT32_(value) << MCAN_TXBE_0_ESI_Pos)) /* Assigment of value for ESI in the MCAN_TXBE_0 register */
#define MCAN_TXBE_0_Msk                       _UINT32_(0xFFFFFFFF)                                 /* (MCAN_TXBE_0) Register Mask  */


/* -------- MCAN_TXBE_1 : (MCAN Offset: 0x04) (R/W 32) Tx Buffer Element 1 -------- */
#define MCAN_TXBE_1_DLC_Pos                   _UINT32_(16)                                         /* (MCAN_TXBE_1) Data Length Code Position */
#define MCAN_TXBE_1_DLC_Msk                   (_UINT32_(0xF) << MCAN_TXBE_1_DLC_Pos)               /* (MCAN_TXBE_1) Data Length Code Mask */
#define MCAN_TXBE_1_DLC(value)                (MCAN_TXBE_1_DLC_Msk & (_UINT32_(value) << MCAN_TXBE_1_DLC_Pos)) /* Assigment of value for DLC in the MCAN_TXBE_1 register */
#define MCAN_TXBE_1_BRS_Pos                   _UINT32_(20)                                         /* (MCAN_TXBE_1) Bit Rate Switch Position */
#define MCAN_TXBE_1_BRS_Msk                   (_UINT32_(0x1) << MCAN_TXBE_1_BRS_Pos)               /* (MCAN_TXBE_1) Bit Rate Switch Mask */
#define MCAN_TXBE_1_BRS(value)                (MCAN_TXBE_1_BRS_Msk & (_UINT32_(value) << MCAN_TXBE_1_BRS_Pos)) /* Assigment of value for BRS in the MCAN_TXBE_1 register */
#define MCAN_TXBE_1_FDF_Pos                   _UINT32_(21)                                         /* (MCAN_TXBE_1) FD Format Position */
#define MCAN_TXBE_1_FDF_Msk                   (_UINT32_(0x1) << MCAN_TXBE_1_FDF_Pos)               /* (MCAN_TXBE_1) FD Format Mask */
#define MCAN_TXBE_1_FDF(value)                (MCAN_TXBE_1_FDF_Msk & (_UINT32_(value) << MCAN_TXBE_1_FDF_Pos)) /* Assigment of value for FDF in the MCAN_TXBE_1 register */
#define MCAN_TXBE_1_EFC_Pos                   _UINT32_(23)                                         /* (MCAN_TXBE_1) Event FIFO Control Position */
#define MCAN_TXBE_1_EFC_Msk                   (_UINT32_(0x1) << MCAN_TXBE_1_EFC_Pos)               /* (MCAN_TXBE_1) Event FIFO Control Mask */
#define MCAN_TXBE_1_EFC(value)                (MCAN_TXBE_1_EFC_Msk & (_UINT32_(value) << MCAN_TXBE_1_EFC_Pos)) /* Assigment of value for EFC in the MCAN_TXBE_1 register */
#define MCAN_TXBE_1_MM_Pos                    _UINT32_(24)                                         /* (MCAN_TXBE_1) Message Marker Position */
#define MCAN_TXBE_1_MM_Msk                    (_UINT32_(0xFF) << MCAN_TXBE_1_MM_Pos)               /* (MCAN_TXBE_1) Message Marker Mask */
#define MCAN_TXBE_1_MM(value)                 (MCAN_TXBE_1_MM_Msk & (_UINT32_(value) << MCAN_TXBE_1_MM_Pos)) /* Assigment of value for MM in the MCAN_TXBE_1 register */
#define MCAN_TXBE_1_Msk                       _UINT32_(0xFFBF0000)                                 /* (MCAN_TXBE_1) Register Mask  */


/* -------- MCAN_TXBE_DATA : (MCAN Offset: 0x08) (R/W 32) Tx Buffer Element Data -------- */
#define MCAN_TXBE_DATA_DB0_Pos                _UINT32_(0)                                          /* (MCAN_TXBE_DATA) Data Byte 0 Position */
#define MCAN_TXBE_DATA_DB0_Msk                (_UINT32_(0xFF) << MCAN_TXBE_DATA_DB0_Pos)           /* (MCAN_TXBE_DATA) Data Byte 0 Mask */
#define MCAN_TXBE_DATA_DB0(value)             (MCAN_TXBE_DATA_DB0_Msk & (_UINT32_(value) << MCAN_TXBE_DATA_DB0_Pos)) /* Assigment of value for DB0 in the MCAN_TXBE_DATA register */
#define MCAN_TXBE_DATA_DB1_Pos                _UINT32_(8)                                          /* (MCAN_TXBE_DATA) Data Byte 1 Position */
#define MCAN_TXBE_DATA_DB1_Msk                (_UINT32_(0xFF) << MCAN_TXBE_DATA_DB1_Pos)           /* (MCAN_TXBE_DATA) Data Byte 1 Mask */
#define MCAN_TXBE_DATA_DB1(value)             (MCAN_TXBE_DATA_DB1_Msk & (_UINT32_(value) << MCAN_TXBE_DATA_DB1_Pos)) /* Assigment of value for DB1 in the MCAN_TXBE_DATA register */
#define MCAN_TXBE_DATA_DB2_Pos                _UINT32_(16)                                         /* (MCAN_TXBE_DATA) Data Byte 2 Position */
#define MCAN_TXBE_DATA_DB2_Msk                (_UINT32_(0xFF) << MCAN_TXBE_DATA_DB2_Pos)           /* (MCAN_TXBE_DATA) Data Byte 2 Mask */
#define MCAN_TXBE_DATA_DB2(value)             (MCAN_TXBE_DATA_DB2_Msk & (_UINT32_(value) << MCAN_TXBE_DATA_DB2_Pos)) /* Assigment of value for DB2 in the MCAN_TXBE_DATA register */
#define MCAN_TXBE_DATA_DB3_Pos                _UINT32_(24)                                         /* (MCAN_TXBE_DATA) Data Byte 3 Position */
#define MCAN_TXBE_DATA_DB3_Msk                (_UINT32_(0xFF) << MCAN_TXBE_DATA_DB3_Pos)           /* (MCAN_TXBE_DATA) Data Byte 3 Mask */
#define MCAN_TXBE_DATA_DB3(value)             (MCAN_TXBE_DATA_DB3_Msk & (_UINT32_(value) << MCAN_TXBE_DATA_DB3_Pos)) /* Assigment of value for DB3 in the MCAN_TXBE_DATA register */
#define MCAN_TXBE_DATA_Msk                    _UINT32_(0xFFFFFFFF)                                 /* (MCAN_TXBE_DATA) Register Mask  */


/* -------- MCAN_TXEFE_0 : (MCAN Offset: 0x00) (R/W 32) Tx Event FIFO Element 0 -------- */
#define MCAN_TXEFE_0_ID_Pos                   _UINT32_(0)                                          /* (MCAN_TXEFE_0) Identifier Position */
#define MCAN_TXEFE_0_ID_Msk                   (_UINT32_(0x1FFFFFFF) << MCAN_TXEFE_0_ID_Pos)        /* (MCAN_TXEFE_0) Identifier Mask */
#define MCAN_TXEFE_0_ID(value)                (MCAN_TXEFE_0_ID_Msk & (_UINT32_(value) << MCAN_TXEFE_0_ID_Pos)) /* Assigment of value for ID in the MCAN_TXEFE_0 register */
#define MCAN_TXEFE_0_RTR_Pos                  _UINT32_(29)                                         /* (MCAN_TXEFE_0) Remote Transmission Request Position */
#define MCAN_TXEFE_0_RTR_Msk                  (_UINT32_(0x1) << MCAN_TXEFE_0_RTR_Pos)              /* (MCAN_TXEFE_0) Remote Transmission Request Mask */
#define MCAN_TXEFE_0_RTR(value)               (MCAN_TXEFE_0_RTR_Msk & (_UINT32_(value) << MCAN_TXEFE_0_RTR_Pos)) /* Assigment of value for RTR in the MCAN_TXEFE_0 register */
#define MCAN_TXEFE_0_XTD_Pos                  _UINT32_(30)                                         /* (MCAN_TXEFE_0) Extended Identifier Position */
#define MCAN_TXEFE_0_XTD_Msk                  (_UINT32_(0x1) << MCAN_TXEFE_0_XTD_Pos)              /* (MCAN_TXEFE_0) Extended Identifier Mask */
#define MCAN_TXEFE_0_XTD(value)               (MCAN_TXEFE_0_XTD_Msk & (_UINT32_(value) << MCAN_TXEFE_0_XTD_Pos)) /* Assigment of value for XTD in the MCAN_TXEFE_0 register */
#define MCAN_TXEFE_0_ESI_Pos                  _UINT32_(31)                                         /* (MCAN_TXEFE_0) Error State Indicator Position */
#define MCAN_TXEFE_0_ESI_Msk                  (_UINT32_(0x1) << MCAN_TXEFE_0_ESI_Pos)              /* (MCAN_TXEFE_0) Error State Indicator Mask */
#define MCAN_TXEFE_0_ESI(value)               (MCAN_TXEFE_0_ESI_Msk & (_UINT32_(value) << MCAN_TXEFE_0_ESI_Pos)) /* Assigment of value for ESI in the MCAN_TXEFE_0 register */
#define MCAN_TXEFE_0_Msk                      _UINT32_(0xFFFFFFFF)                                 /* (MCAN_TXEFE_0) Register Mask  */


/* -------- MCAN_TXEFE_1 : (MCAN Offset: 0x04) (R/W 32) Tx Event FIFO Element 1 -------- */
#define MCAN_TXEFE_1_TXTS_Pos                 _UINT32_(0)                                          /* (MCAN_TXEFE_1) Tx Timestamp Position */
#define MCAN_TXEFE_1_TXTS_Msk                 (_UINT32_(0xFFFF) << MCAN_TXEFE_1_TXTS_Pos)          /* (MCAN_TXEFE_1) Tx Timestamp Mask */
#define MCAN_TXEFE_1_TXTS(value)              (MCAN_TXEFE_1_TXTS_Msk & (_UINT32_(value) << MCAN_TXEFE_1_TXTS_Pos)) /* Assigment of value for TXTS in the MCAN_TXEFE_1 register */
#define MCAN_TXEFE_1_DLC_Pos                  _UINT32_(16)                                         /* (MCAN_TXEFE_1) Data Length Code Position */
#define MCAN_TXEFE_1_DLC_Msk                  (_UINT32_(0xF) << MCAN_TXEFE_1_DLC_Pos)              /* (MCAN_TXEFE_1) Data Length Code Mask */
#define MCAN_TXEFE_1_DLC(value)               (MCAN_TXEFE_1_DLC_Msk & (_UINT32_(value) << MCAN_TXEFE_1_DLC_Pos)) /* Assigment of value for DLC in the MCAN_TXEFE_1 register */
#define MCAN_TXEFE_1_BRS_Pos                  _UINT32_(20)                                         /* (MCAN_TXEFE_1) Bit Rate Switch Position */
#define MCAN_TXEFE_1_BRS_Msk                  (_UINT32_(0x1) << MCAN_TXEFE_1_BRS_Pos)              /* (MCAN_TXEFE_1) Bit Rate Switch Mask */
#define MCAN_TXEFE_1_BRS(value)               (MCAN_TXEFE_1_BRS_Msk & (_UINT32_(value) << MCAN_TXEFE_1_BRS_Pos)) /* Assigment of value for BRS in the MCAN_TXEFE_1 register */
#define MCAN_TXEFE_1_FDF_Pos                  _UINT32_(21)                                         /* (MCAN_TXEFE_1) FD Format Position */
#define MCAN_TXEFE_1_FDF_Msk                  (_UINT32_(0x1) << MCAN_TXEFE_1_FDF_Pos)              /* (MCAN_TXEFE_1) FD Format Mask */
#define MCAN_TXEFE_1_FDF(value)               (MCAN_TXEFE_1_FDF_Msk & (_UINT32_(value) << MCAN_TXEFE_1_FDF_Pos)) /* Assigment of value for FDF in the MCAN_TXEFE_1 register */
#define MCAN_TXEFE_1_ET_Pos                   _UINT32_(22)                                         /* (MCAN_TXEFE_1) Event Type Position */
#define MCAN_TXEFE_1_ET_Msk                   (_UINT32_(0x3) << MCAN_TXEFE_1_ET_Pos)               /* (MCAN_TXEFE_1) Event Type Mask */
#define MCAN_TXEFE_1_ET(value)                (MCAN_TXEFE_1_ET_Msk & (_UINT32_(value) << MCAN_TXEFE_1_ET_Pos)) /* Assigment of value for ET in the MCAN_TXEFE_1 register */
#define   MCAN_TXEFE_1_ET_TXE_Val             _UINT32_(0x1)                                        /* (MCAN_TXEFE_1) Tx event  */
#define   MCAN_TXEFE_1_ET_TXC_Val             _UINT32_(0x2)                                        /* (MCAN_TXEFE_1) Transmission in spite of cancellation  */
#define MCAN_TXEFE_1_ET_TXE                   (MCAN_TXEFE_1_ET_TXE_Val << MCAN_TXEFE_1_ET_Pos)     /* (MCAN_TXEFE_1) Tx event Position  */
#define MCAN_TXEFE_1_ET_TXC                   (MCAN_TXEFE_1_ET_TXC_Val << MCAN_TXEFE_1_ET_Pos)     /* (MCAN_TXEFE_1) Transmission in spite of cancellation Position  */
#define MCAN_TXEFE_1_MM_Pos                   _UINT32_(24)                                         /* (MCAN_TXEFE_1) Message Marker Position */
#define MCAN_TXEFE_1_MM_Msk                   (_UINT32_(0xFF) << MCAN_TXEFE_1_MM_Pos)              /* (MCAN_TXEFE_1) Message Marker Mask */
#define MCAN_TXEFE_1_MM(value)                (MCAN_TXEFE_1_MM_Msk & (_UINT32_(value) << MCAN_TXEFE_1_MM_Pos)) /* Assigment of value for MM in the MCAN_TXEFE_1 register */
#define MCAN_TXEFE_1_Msk                      _UINT32_(0xFFFFFFFF)                                 /* (MCAN_TXEFE_1) Register Mask  */


/* -------- MCAN_SIDFE_0 : (MCAN Offset: 0x00) (R/W 32) Standard Message ID Filter Element 0 -------- */
#define MCAN_SIDFE_0_SFID2_Pos                _UINT32_(0)                                          /* (MCAN_SIDFE_0) Standard Filter ID 2 Position */
#define MCAN_SIDFE_0_SFID2_Msk                (_UINT32_(0x7FF) << MCAN_SIDFE_0_SFID2_Pos)          /* (MCAN_SIDFE_0) Standard Filter ID 2 Mask */
#define MCAN_SIDFE_0_SFID2(value)             (MCAN_SIDFE_0_SFID2_Msk & (_UINT32_(value) << MCAN_SIDFE_0_SFID2_Pos)) /* Assigment of value for SFID2 in the MCAN_SIDFE_0 register */
#define MCAN_SIDFE_0_SFID1_Pos                _UINT32_(16)                                         /* (MCAN_SIDFE_0) Standard Filter ID 1 Position */
#define MCAN_SIDFE_0_SFID1_Msk                (_UINT32_(0x7FF) << MCAN_SIDFE_0_SFID1_Pos)          /* (MCAN_SIDFE_0) Standard Filter ID 1 Mask */
#define MCAN_SIDFE_0_SFID1(value)             (MCAN_SIDFE_0_SFID1_Msk & (_UINT32_(value) << MCAN_SIDFE_0_SFID1_Pos)) /* Assigment of value for SFID1 in the MCAN_SIDFE_0 register */
#define MCAN_SIDFE_0_SFEC_Pos                 _UINT32_(27)                                         /* (MCAN_SIDFE_0) Standard Filter Element Configuration Position */
#define MCAN_SIDFE_0_SFEC_Msk                 (_UINT32_(0x7) << MCAN_SIDFE_0_SFEC_Pos)             /* (MCAN_SIDFE_0) Standard Filter Element Configuration Mask */
#define MCAN_SIDFE_0_SFEC(value)              (MCAN_SIDFE_0_SFEC_Msk & (_UINT32_(value) << MCAN_SIDFE_0_SFEC_Pos)) /* Assigment of value for SFEC in the MCAN_SIDFE_0 register */
#define   MCAN_SIDFE_0_SFEC_DISABLE_Val       _UINT32_(0x0)                                        /* (MCAN_SIDFE_0) Disable filter element  */
#define   MCAN_SIDFE_0_SFEC_STF0M_Val         _UINT32_(0x1)                                        /* (MCAN_SIDFE_0) Store in Rx FIFO 0 if filter matches  */
#define   MCAN_SIDFE_0_SFEC_STF1M_Val         _UINT32_(0x2)                                        /* (MCAN_SIDFE_0) Store in Rx FIFO 1 if filter matches  */
#define   MCAN_SIDFE_0_SFEC_REJECT_Val        _UINT32_(0x3)                                        /* (MCAN_SIDFE_0) Reject ID if filter matches  */
#define   MCAN_SIDFE_0_SFEC_PRIORITY_Val      _UINT32_(0x4)                                        /* (MCAN_SIDFE_0) Set priority if filter matches  */
#define   MCAN_SIDFE_0_SFEC_PRIF0M_Val        _UINT32_(0x5)                                        /* (MCAN_SIDFE_0) Set priority and store in FIFO 0 if filter matches  */
#define   MCAN_SIDFE_0_SFEC_PRIF1M_Val        _UINT32_(0x6)                                        /* (MCAN_SIDFE_0) Set priority and store in FIFO 1 if filter matches  */
#define   MCAN_SIDFE_0_SFEC_STRXBUF_Val       _UINT32_(0x7)                                        /* (MCAN_SIDFE_0) Store into Rx Buffer  */
#define MCAN_SIDFE_0_SFEC_DISABLE             (MCAN_SIDFE_0_SFEC_DISABLE_Val << MCAN_SIDFE_0_SFEC_Pos) /* (MCAN_SIDFE_0) Disable filter element Position  */
#define MCAN_SIDFE_0_SFEC_STF0M               (MCAN_SIDFE_0_SFEC_STF0M_Val << MCAN_SIDFE_0_SFEC_Pos) /* (MCAN_SIDFE_0) Store in Rx FIFO 0 if filter matches Position  */
#define MCAN_SIDFE_0_SFEC_STF1M               (MCAN_SIDFE_0_SFEC_STF1M_Val << MCAN_SIDFE_0_SFEC_Pos) /* (MCAN_SIDFE_0) Store in Rx FIFO 1 if filter matches Position  */
#define MCAN_SIDFE_0_SFEC_REJECT              (MCAN_SIDFE_0_SFEC_REJECT_Val << MCAN_SIDFE_0_SFEC_Pos) /* (MCAN_SIDFE_0) Reject ID if filter matches Position  */
#define MCAN_SIDFE_0_SFEC_PRIORITY            (MCAN_SIDFE_0_SFEC_PRIORITY_Val << MCAN_SIDFE_0_SFEC_Pos) /* (MCAN_SIDFE_0) Set priority if filter matches Position  */
#define MCAN_SIDFE_0_SFEC_PRIF0M              (MCAN_SIDFE_0_SFEC_PRIF0M_Val << MCAN_SIDFE_0_SFEC_Pos) /* (MCAN_SIDFE_0) Set priority and store in FIFO 0 if filter matches Position  */
#define MCAN_SIDFE_0_SFEC_PRIF1M              (MCAN_SIDFE_0_SFEC_PRIF1M_Val << MCAN_SIDFE_0_SFEC_Pos) /* (MCAN_SIDFE_0) Set priority and store in FIFO 1 if filter matches Position  */
#define MCAN_SIDFE_0_SFEC_STRXBUF             (MCAN_SIDFE_0_SFEC_STRXBUF_Val << MCAN_SIDFE_0_SFEC_Pos) /* (MCAN_SIDFE_0) Store into Rx Buffer Position  */
#define MCAN_SIDFE_0_SFT_Pos                  _UINT32_(30)                                         /* (MCAN_SIDFE_0) Standard Filter Type Position */
#define MCAN_SIDFE_0_SFT_Msk                  (_UINT32_(0x3) << MCAN_SIDFE_0_SFT_Pos)              /* (MCAN_SIDFE_0) Standard Filter Type Mask */
#define MCAN_SIDFE_0_SFT(value)               (MCAN_SIDFE_0_SFT_Msk & (_UINT32_(value) << MCAN_SIDFE_0_SFT_Pos)) /* Assigment of value for SFT in the MCAN_SIDFE_0 register */
#define   MCAN_SIDFE_0_SFT_RANGE_Val          _UINT32_(0x0)                                        /* (MCAN_SIDFE_0) Range filter from SFID1 to SFID2  */
#define   MCAN_SIDFE_0_SFT_DUAL_Val           _UINT32_(0x1)                                        /* (MCAN_SIDFE_0) Dual ID filter for SF1ID or SF2ID  */
#define   MCAN_SIDFE_0_SFT_CLASSIC_Val        _UINT32_(0x2)                                        /* (MCAN_SIDFE_0) Classic filter  */
#define MCAN_SIDFE_0_SFT_RANGE                (MCAN_SIDFE_0_SFT_RANGE_Val << MCAN_SIDFE_0_SFT_Pos) /* (MCAN_SIDFE_0) Range filter from SFID1 to SFID2 Position  */
#define MCAN_SIDFE_0_SFT_DUAL                 (MCAN_SIDFE_0_SFT_DUAL_Val << MCAN_SIDFE_0_SFT_Pos)  /* (MCAN_SIDFE_0) Dual ID filter for SF1ID or SF2ID Position  */
#define MCAN_SIDFE_0_SFT_CLASSIC              (MCAN_SIDFE_0_SFT_CLASSIC_Val << MCAN_SIDFE_0_SFT_Pos) /* (MCAN_SIDFE_0) Classic filter Position  */
#define MCAN_SIDFE_0_Msk                      _UINT32_(0xFFFF07FF)                                 /* (MCAN_SIDFE_0) Register Mask  */


/* -------- MCAN_XIDFE_0 : (MCAN Offset: 0x00) (R/W 32) Extended Message ID Filter Element 0 -------- */
#define MCAN_XIDFE_0_EFID1_Pos                _UINT32_(0)                                          /* (MCAN_XIDFE_0) Extended Filter ID 1 Position */
#define MCAN_XIDFE_0_EFID1_Msk                (_UINT32_(0x1FFFFFFF) << MCAN_XIDFE_0_EFID1_Pos)     /* (MCAN_XIDFE_0) Extended Filter ID 1 Mask */
#define MCAN_XIDFE_0_EFID1(value)             (MCAN_XIDFE_0_EFID1_Msk & (_UINT32_(value) << MCAN_XIDFE_0_EFID1_Pos)) /* Assigment of value for EFID1 in the MCAN_XIDFE_0 register */
#define MCAN_XIDFE_0_EFEC_Pos                 _UINT32_(29)                                         /* (MCAN_XIDFE_0) Extended Filter Element Configuration Position */
#define MCAN_XIDFE_0_EFEC_Msk                 (_UINT32_(0x7) << MCAN_XIDFE_0_EFEC_Pos)             /* (MCAN_XIDFE_0) Extended Filter Element Configuration Mask */
#define MCAN_XIDFE_0_EFEC(value)              (MCAN_XIDFE_0_EFEC_Msk & (_UINT32_(value) << MCAN_XIDFE_0_EFEC_Pos)) /* Assigment of value for EFEC in the MCAN_XIDFE_0 register */
#define   MCAN_XIDFE_0_EFEC_DISABLE_Val       _UINT32_(0x0)                                        /* (MCAN_XIDFE_0) Disable filter element  */
#define   MCAN_XIDFE_0_EFEC_STF0M_Val         _UINT32_(0x1)                                        /* (MCAN_XIDFE_0) Store in Rx FIFO 0 if filter matches  */
#define   MCAN_XIDFE_0_EFEC_STF1M_Val         _UINT32_(0x2)                                        /* (MCAN_XIDFE_0) Store in Rx FIFO 1 if filter matches  */
#define   MCAN_XIDFE_0_EFEC_REJECT_Val        _UINT32_(0x3)                                        /* (MCAN_XIDFE_0) Reject ID if filter matches  */
#define   MCAN_XIDFE_0_EFEC_PRIORITY_Val      _UINT32_(0x4)                                        /* (MCAN_XIDFE_0) Set priority if filter matches  */
#define   MCAN_XIDFE_0_EFEC_PRIF0M_Val        _UINT32_(0x5)                                        /* (MCAN_XIDFE_0) Set priority and store in FIFO 0 if filter matches  */
#define   MCAN_XIDFE_0_EFEC_PRIF1M_Val        _UINT32_(0x6)                                        /* (MCAN_XIDFE_0) Set priority and store in FIFO 1 if filter matches  */
#define   MCAN_XIDFE_0_EFEC_STRXBUF_Val       _UINT32_(0x7)                                        /* (MCAN_XIDFE_0) Store into Rx Buffer  */
#define MCAN_XIDFE_0_EFEC_DISABLE             (MCAN_XIDFE_0_EFEC_DISABLE_Val << MCAN_XIDFE_0_EFEC_Pos) /* (MCAN_XIDFE_0) Disable filter element Position  */
#define MCAN_XIDFE_0_EFEC_STF0M               (MCAN_XIDFE_0_EFEC_STF0M_Val << MCAN_XIDFE_0_EFEC_Pos) /* (MCAN_XIDFE_0) Store in Rx FIFO 0 if filter matches Position  */
#define MCAN_XIDFE_0_EFEC_STF1M               (MCAN_XIDFE_0_EFEC_STF1M_Val << MCAN_XIDFE_0_EFEC_Pos) /* (MCAN_XIDFE_0) Store in Rx FIFO 1 if filter matches Position  */
#define MCAN_XIDFE_0_EFEC_REJECT              (MCAN_XIDFE_0_EFEC_REJECT_Val << MCAN_XIDFE_0_EFEC_Pos) /* (MCAN_XIDFE_0) Reject ID if filter matches Position  */
#define MCAN_XIDFE_0_EFEC_PRIORITY            (MCAN_XIDFE_0_EFEC_PRIORITY_Val << MCAN_XIDFE_0_EFEC_Pos) /* (MCAN_XIDFE_0) Set priority if filter matches Position  */
#define MCAN_XIDFE_0_EFEC_PRIF0M              (MCAN_XIDFE_0_EFEC_PRIF0M_Val << MCAN_XIDFE_0_EFEC_Pos) /* (MCAN_XIDFE_0) Set priority and store in FIFO 0 if filter matches Position  */
#define MCAN_XIDFE_0_EFEC_PRIF1M              (MCAN_XIDFE_0_EFEC_PRIF1M_Val << MCAN_XIDFE_0_EFEC_Pos) /* (MCAN_XIDFE_0) Set priority and store in FIFO 1 if filter matches Position  */
#define MCAN_XIDFE_0_EFEC_STRXBUF             (MCAN_XIDFE_0_EFEC_STRXBUF_Val << MCAN_XIDFE_0_EFEC_Pos) /* (MCAN_XIDFE_0) Store into Rx Buffer Position  */
#define MCAN_XIDFE_0_Msk                      _UINT32_(0xFFFFFFFF)                                 /* (MCAN_XIDFE_0) Register Mask  */


/* -------- MCAN_XIDFE_1 : (MCAN Offset: 0x04) (R/W 32) Extended Message ID Filter Element 1 -------- */
#define MCAN_XIDFE_1_EFID2_Pos                _UINT32_(0)                                          /* (MCAN_XIDFE_1) Extended Filter ID 2 Position */
#define MCAN_XIDFE_1_EFID2_Msk                (_UINT32_(0x1FFFFFFF) << MCAN_XIDFE_1_EFID2_Pos)     /* (MCAN_XIDFE_1) Extended Filter ID 2 Mask */
#define MCAN_XIDFE_1_EFID2(value)             (MCAN_XIDFE_1_EFID2_Msk & (_UINT32_(value) << MCAN_XIDFE_1_EFID2_Pos)) /* Assigment of value for EFID2 in the MCAN_XIDFE_1 register */
#define MCAN_XIDFE_1_EFT_Pos                  _UINT32_(30)                                         /* (MCAN_XIDFE_1) Extended Filter Type Position */
#define MCAN_XIDFE_1_EFT_Msk                  (_UINT32_(0x3) << MCAN_XIDFE_1_EFT_Pos)              /* (MCAN_XIDFE_1) Extended Filter Type Mask */
#define MCAN_XIDFE_1_EFT(value)               (MCAN_XIDFE_1_EFT_Msk & (_UINT32_(value) << MCAN_XIDFE_1_EFT_Pos)) /* Assigment of value for EFT in the MCAN_XIDFE_1 register */
#define   MCAN_XIDFE_1_EFT_RANGE_Val          _UINT32_(0x0)                                        /* (MCAN_XIDFE_1) Range filter from EFID1 to EFID2  */
#define   MCAN_XIDFE_1_EFT_DUAL_Val           _UINT32_(0x1)                                        /* (MCAN_XIDFE_1) Dual ID filter for EFID1 or EFID2  */
#define   MCAN_XIDFE_1_EFT_CLASSIC_Val        _UINT32_(0x2)                                        /* (MCAN_XIDFE_1) Classic filter  */
#define   MCAN_XIDFE_1_EFT_RANGE_NO_XIDAM_Val _UINT32_(0x3)                                        /* (MCAN_XIDFE_1) Range filter from EFID1 to EFID2 with no XIDAM mask  */
#define MCAN_XIDFE_1_EFT_RANGE                (MCAN_XIDFE_1_EFT_RANGE_Val << MCAN_XIDFE_1_EFT_Pos) /* (MCAN_XIDFE_1) Range filter from EFID1 to EFID2 Position  */
#define MCAN_XIDFE_1_EFT_DUAL                 (MCAN_XIDFE_1_EFT_DUAL_Val << MCAN_XIDFE_1_EFT_Pos)  /* (MCAN_XIDFE_1) Dual ID filter for EFID1 or EFID2 Position  */
#define MCAN_XIDFE_1_EFT_CLASSIC              (MCAN_XIDFE_1_EFT_CLASSIC_Val << MCAN_XIDFE_1_EFT_Pos) /* (MCAN_XIDFE_1) Classic filter Position  */
#define MCAN_XIDFE_1_EFT_RANGE_NO_XIDAM       (MCAN_XIDFE_1_EFT_RANGE_NO_XIDAM_Val << MCAN_XIDFE_1_EFT_Pos) /* (MCAN_XIDFE_1) Range filter from EFID1 to EFID2 with no XIDAM mask Position  */
#define MCAN_XIDFE_1_Msk                      _UINT32_(0xDFFFFFFF)                                 /* (MCAN_XIDFE_1) Register Mask  */


/* -------- MCAN_CREL : (MCAN Offset: 0x00) ( R/ 32) Core Release Register -------- */
#define MCAN_CREL_DAY_Pos                     _UINT32_(0)                                          /* (MCAN_CREL) Timestamp Day Position */
#define MCAN_CREL_DAY_Msk                     (_UINT32_(0xFF) << MCAN_CREL_DAY_Pos)                /* (MCAN_CREL) Timestamp Day Mask */
#define MCAN_CREL_DAY(value)                  (MCAN_CREL_DAY_Msk & (_UINT32_(value) << MCAN_CREL_DAY_Pos)) /* Assigment of value for DAY in the MCAN_CREL register */
#define MCAN_CREL_MON_Pos                     _UINT32_(8)                                          /* (MCAN_CREL) Timestamp Month Position */
#define MCAN_CREL_MON_Msk                     (_UINT32_(0xFF) << MCAN_CREL_MON_Pos)                /* (MCAN_CREL) Timestamp Month Mask */
#define MCAN_CREL_MON(value)                  (MCAN_CREL_MON_Msk & (_UINT32_(value) << MCAN_CREL_MON_Pos)) /* Assigment of value for MON in the MCAN_CREL register */
#define MCAN_CREL_YEAR_Pos                    _UINT32_(16)                                         /* (MCAN_CREL) Timestamp Year Position */
#define MCAN_CREL_YEAR_Msk                    (_UINT32_(0xF) << MCAN_CREL_YEAR_Pos)                /* (MCAN_CREL) Timestamp Year Mask */
#define MCAN_CREL_YEAR(value)                 (MCAN_CREL_YEAR_Msk & (_UINT32_(value) << MCAN_CREL_YEAR_Pos)) /* Assigment of value for YEAR in the MCAN_CREL register */
#define MCAN_CREL_SUBSTEP_Pos                 _UINT32_(20)                                         /* (MCAN_CREL) Sub-step of Core Release Position */
#define MCAN_CREL_SUBSTEP_Msk                 (_UINT32_(0xF) << MCAN_CREL_SUBSTEP_Pos)             /* (MCAN_CREL) Sub-step of Core Release Mask */
#define MCAN_CREL_SUBSTEP(value)              (MCAN_CREL_SUBSTEP_Msk & (_UINT32_(value) << MCAN_CREL_SUBSTEP_Pos)) /* Assigment of value for SUBSTEP in the MCAN_CREL register */
#define MCAN_CREL_STEP_Pos                    _UINT32_(24)                                         /* (MCAN_CREL) Step of Core Release Position */
#define MCAN_CREL_STEP_Msk                    (_UINT32_(0xF) << MCAN_CREL_STEP_Pos)                /* (MCAN_CREL) Step of Core Release Mask */
#define MCAN_CREL_STEP(value)                 (MCAN_CREL_STEP_Msk & (_UINT32_(value) << MCAN_CREL_STEP_Pos)) /* Assigment of value for STEP in the MCAN_CREL register */
#define MCAN_CREL_REL_Pos                     _UINT32_(28)                                         /* (MCAN_CREL) Core Release Position */
#define MCAN_CREL_REL_Msk                     (_UINT32_(0xF) << MCAN_CREL_REL_Pos)                 /* (MCAN_CREL) Core Release Mask */
#define MCAN_CREL_REL(value)                  (MCAN_CREL_REL_Msk & (_UINT32_(value) << MCAN_CREL_REL_Pos)) /* Assigment of value for REL in the MCAN_CREL register */
#define MCAN_CREL_Msk                         _UINT32_(0xFFFFFFFF)                                 /* (MCAN_CREL) Register Mask  */


/* -------- MCAN_ENDN : (MCAN Offset: 0x04) ( R/ 32) Endian Register -------- */
#define MCAN_ENDN_ETV_Pos                     _UINT32_(0)                                          /* (MCAN_ENDN) Endianness Test Value Position */
#define MCAN_ENDN_ETV_Msk                     (_UINT32_(0xFFFFFFFF) << MCAN_ENDN_ETV_Pos)          /* (MCAN_ENDN) Endianness Test Value Mask */
#define MCAN_ENDN_ETV(value)                  (MCAN_ENDN_ETV_Msk & (_UINT32_(value) << MCAN_ENDN_ETV_Pos)) /* Assigment of value for ETV in the MCAN_ENDN register */
#define MCAN_ENDN_Msk                         _UINT32_(0xFFFFFFFF)                                 /* (MCAN_ENDN) Register Mask  */


/* -------- MCAN_CUST : (MCAN Offset: 0x08) (R/W 32) Customer Register -------- */
#define MCAN_CUST_CSV_Pos                     _UINT32_(0)                                          /* (MCAN_CUST) Customer-specific Value Position */
#define MCAN_CUST_CSV_Msk                     (_UINT32_(0xFFFFFFFF) << MCAN_CUST_CSV_Pos)          /* (MCAN_CUST) Customer-specific Value Mask */
#define MCAN_CUST_CSV(value)                  (MCAN_CUST_CSV_Msk & (_UINT32_(value) << MCAN_CUST_CSV_Pos)) /* Assigment of value for CSV in the MCAN_CUST register */
#define MCAN_CUST_Msk                         _UINT32_(0xFFFFFFFF)                                 /* (MCAN_CUST) Register Mask  */


/* -------- MCAN_DBTP : (MCAN Offset: 0x0C) (R/W 32) Data Bit Timing and Prescaler Register -------- */
#define MCAN_DBTP_DSJW_Pos                    _UINT32_(0)                                          /* (MCAN_DBTP) Data (Re) Synchronization Jump Width Position */
#define MCAN_DBTP_DSJW_Msk                    (_UINT32_(0x7) << MCAN_DBTP_DSJW_Pos)                /* (MCAN_DBTP) Data (Re) Synchronization Jump Width Mask */
#define MCAN_DBTP_DSJW(value)                 (MCAN_DBTP_DSJW_Msk & (_UINT32_(value) << MCAN_DBTP_DSJW_Pos)) /* Assigment of value for DSJW in the MCAN_DBTP register */
#define MCAN_DBTP_DTSEG2_Pos                  _UINT32_(4)                                          /* (MCAN_DBTP) Data Time Segment After Sample Point Position */
#define MCAN_DBTP_DTSEG2_Msk                  (_UINT32_(0xF) << MCAN_DBTP_DTSEG2_Pos)              /* (MCAN_DBTP) Data Time Segment After Sample Point Mask */
#define MCAN_DBTP_DTSEG2(value)               (MCAN_DBTP_DTSEG2_Msk & (_UINT32_(value) << MCAN_DBTP_DTSEG2_Pos)) /* Assigment of value for DTSEG2 in the MCAN_DBTP register */
#define MCAN_DBTP_DTSEG1_Pos                  _UINT32_(8)                                          /* (MCAN_DBTP) Data Time Segment Before Sample Point Position */
#define MCAN_DBTP_DTSEG1_Msk                  (_UINT32_(0x1F) << MCAN_DBTP_DTSEG1_Pos)             /* (MCAN_DBTP) Data Time Segment Before Sample Point Mask */
#define MCAN_DBTP_DTSEG1(value)               (MCAN_DBTP_DTSEG1_Msk & (_UINT32_(value) << MCAN_DBTP_DTSEG1_Pos)) /* Assigment of value for DTSEG1 in the MCAN_DBTP register */
#define MCAN_DBTP_DBRP_Pos                    _UINT32_(16)                                         /* (MCAN_DBTP) Data Bit Rate Prescaler Position */
#define MCAN_DBTP_DBRP_Msk                    (_UINT32_(0x1F) << MCAN_DBTP_DBRP_Pos)               /* (MCAN_DBTP) Data Bit Rate Prescaler Mask */
#define MCAN_DBTP_DBRP(value)                 (MCAN_DBTP_DBRP_Msk & (_UINT32_(value) << MCAN_DBTP_DBRP_Pos)) /* Assigment of value for DBRP in the MCAN_DBTP register */
#define MCAN_DBTP_TDC_Pos                     _UINT32_(23)                                         /* (MCAN_DBTP) Transmitter Delay Compensation Position */
#define MCAN_DBTP_TDC_Msk                     (_UINT32_(0x1) << MCAN_DBTP_TDC_Pos)                 /* (MCAN_DBTP) Transmitter Delay Compensation Mask */
#define MCAN_DBTP_TDC(value)                  (MCAN_DBTP_TDC_Msk & (_UINT32_(value) << MCAN_DBTP_TDC_Pos)) /* Assigment of value for TDC in the MCAN_DBTP register */
#define   MCAN_DBTP_TDC_DISABLED_Val          _UINT32_(0x0)                                        /* (MCAN_DBTP) Transmitter Delay Compensation disabled.  */
#define   MCAN_DBTP_TDC_ENABLED_Val           _UINT32_(0x1)                                        /* (MCAN_DBTP) Transmitter Delay Compensation enabled.  */
#define MCAN_DBTP_TDC_DISABLED                (MCAN_DBTP_TDC_DISABLED_Val << MCAN_DBTP_TDC_Pos)    /* (MCAN_DBTP) Transmitter Delay Compensation disabled. Position  */
#define MCAN_DBTP_TDC_ENABLED                 (MCAN_DBTP_TDC_ENABLED_Val << MCAN_DBTP_TDC_Pos)     /* (MCAN_DBTP) Transmitter Delay Compensation enabled. Position  */
#define MCAN_DBTP_Msk                         _UINT32_(0x009F1FF7)                                 /* (MCAN_DBTP) Register Mask  */


/* -------- MCAN_TEST : (MCAN Offset: 0x10) (R/W 32) Test Register -------- */
#define MCAN_TEST_LBCK_Pos                    _UINT32_(4)                                          /* (MCAN_TEST) Loop Back Mode (read/write) Position */
#define MCAN_TEST_LBCK_Msk                    (_UINT32_(0x1) << MCAN_TEST_LBCK_Pos)                /* (MCAN_TEST) Loop Back Mode (read/write) Mask */
#define MCAN_TEST_LBCK(value)                 (MCAN_TEST_LBCK_Msk & (_UINT32_(value) << MCAN_TEST_LBCK_Pos)) /* Assigment of value for LBCK in the MCAN_TEST register */
#define   MCAN_TEST_LBCK_DISABLED_Val         _UINT32_(0x0)                                        /* (MCAN_TEST) Reset value. Loop Back mode is disabled.  */
#define   MCAN_TEST_LBCK_ENABLED_Val          _UINT32_(0x1)                                        /* (MCAN_TEST) Loop Back mode is enabled (see Section 6.1.9).  */
#define MCAN_TEST_LBCK_DISABLED               (MCAN_TEST_LBCK_DISABLED_Val << MCAN_TEST_LBCK_Pos)  /* (MCAN_TEST) Reset value. Loop Back mode is disabled. Position  */
#define MCAN_TEST_LBCK_ENABLED                (MCAN_TEST_LBCK_ENABLED_Val << MCAN_TEST_LBCK_Pos)   /* (MCAN_TEST) Loop Back mode is enabled (see Section 6.1.9). Position  */
#define MCAN_TEST_TX_Pos                      _UINT32_(5)                                          /* (MCAN_TEST) Control of Transmit Pin (read/write) Position */
#define MCAN_TEST_TX_Msk                      (_UINT32_(0x3) << MCAN_TEST_TX_Pos)                  /* (MCAN_TEST) Control of Transmit Pin (read/write) Mask */
#define MCAN_TEST_TX(value)                   (MCAN_TEST_TX_Msk & (_UINT32_(value) << MCAN_TEST_TX_Pos)) /* Assigment of value for TX in the MCAN_TEST register */
#define   MCAN_TEST_TX_RESET_Val              _UINT32_(0x0)                                        /* (MCAN_TEST) Reset value, CANTX controlled by the CAN Core, updated at the end of the CAN bit time.  */
#define   MCAN_TEST_TX_SAMPLE_POINT_MONITORING_Val _UINT32_(0x1)                                        /* (MCAN_TEST) Sample Point can be monitored at pin CANTX.  */
#define   MCAN_TEST_TX_DOMINANT_Val           _UINT32_(0x2)                                        /* (MCAN_TEST) Dominant ('0') level at pin CANTX.  */
#define   MCAN_TEST_TX_RECESSIVE_Val          _UINT32_(0x3)                                        /* (MCAN_TEST) Recessive ('1') at pin CANTX.  */
#define MCAN_TEST_TX_RESET                    (MCAN_TEST_TX_RESET_Val << MCAN_TEST_TX_Pos)         /* (MCAN_TEST) Reset value, CANTX controlled by the CAN Core, updated at the end of the CAN bit time. Position  */
#define MCAN_TEST_TX_SAMPLE_POINT_MONITORING  (MCAN_TEST_TX_SAMPLE_POINT_MONITORING_Val << MCAN_TEST_TX_Pos) /* (MCAN_TEST) Sample Point can be monitored at pin CANTX. Position  */
#define MCAN_TEST_TX_DOMINANT                 (MCAN_TEST_TX_DOMINANT_Val << MCAN_TEST_TX_Pos)      /* (MCAN_TEST) Dominant ('0') level at pin CANTX. Position  */
#define MCAN_TEST_TX_RECESSIVE                (MCAN_TEST_TX_RECESSIVE_Val << MCAN_TEST_TX_Pos)     /* (MCAN_TEST) Recessive ('1') at pin CANTX. Position  */
#define MCAN_TEST_RX_Pos                      _UINT32_(7)                                          /* (MCAN_TEST) Receive Pin (read-only) Position */
#define MCAN_TEST_RX_Msk                      (_UINT32_(0x1) << MCAN_TEST_RX_Pos)                  /* (MCAN_TEST) Receive Pin (read-only) Mask */
#define MCAN_TEST_RX(value)                   (MCAN_TEST_RX_Msk & (_UINT32_(value) << MCAN_TEST_RX_Pos)) /* Assigment of value for RX in the MCAN_TEST register */
#define MCAN_TEST_Msk                         _UINT32_(0x000000F0)                                 /* (MCAN_TEST) Register Mask  */


/* -------- MCAN_RWD : (MCAN Offset: 0x14) (R/W 32) RAM Watchdog Register -------- */
#define MCAN_RWD_WDC_Pos                      _UINT32_(0)                                          /* (MCAN_RWD) Watchdog Configuration (read/write) Position */
#define MCAN_RWD_WDC_Msk                      (_UINT32_(0xFF) << MCAN_RWD_WDC_Pos)                 /* (MCAN_RWD) Watchdog Configuration (read/write) Mask */
#define MCAN_RWD_WDC(value)                   (MCAN_RWD_WDC_Msk & (_UINT32_(value) << MCAN_RWD_WDC_Pos)) /* Assigment of value for WDC in the MCAN_RWD register */
#define MCAN_RWD_WDV_Pos                      _UINT32_(8)                                          /* (MCAN_RWD) Watchdog Value (read-only) Position */
#define MCAN_RWD_WDV_Msk                      (_UINT32_(0xFF) << MCAN_RWD_WDV_Pos)                 /* (MCAN_RWD) Watchdog Value (read-only) Mask */
#define MCAN_RWD_WDV(value)                   (MCAN_RWD_WDV_Msk & (_UINT32_(value) << MCAN_RWD_WDV_Pos)) /* Assigment of value for WDV in the MCAN_RWD register */
#define MCAN_RWD_Msk                          _UINT32_(0x0000FFFF)                                 /* (MCAN_RWD) Register Mask  */


/* -------- MCAN_CCCR : (MCAN Offset: 0x18) (R/W 32) CC Control Register -------- */
#define MCAN_CCCR_INIT_Pos                    _UINT32_(0)                                          /* (MCAN_CCCR) Initialization (read/write) Position */
#define MCAN_CCCR_INIT_Msk                    (_UINT32_(0x1) << MCAN_CCCR_INIT_Pos)                /* (MCAN_CCCR) Initialization (read/write) Mask */
#define MCAN_CCCR_INIT(value)                 (MCAN_CCCR_INIT_Msk & (_UINT32_(value) << MCAN_CCCR_INIT_Pos)) /* Assigment of value for INIT in the MCAN_CCCR register */
#define   MCAN_CCCR_INIT_DISABLED_Val         _UINT32_(0x0)                                        /* (MCAN_CCCR) Normal operation.  */
#define   MCAN_CCCR_INIT_ENABLED_Val          _UINT32_(0x1)                                        /* (MCAN_CCCR) Initialization is started.  */
#define MCAN_CCCR_INIT_DISABLED               (MCAN_CCCR_INIT_DISABLED_Val << MCAN_CCCR_INIT_Pos)  /* (MCAN_CCCR) Normal operation. Position  */
#define MCAN_CCCR_INIT_ENABLED                (MCAN_CCCR_INIT_ENABLED_Val << MCAN_CCCR_INIT_Pos)   /* (MCAN_CCCR) Initialization is started. Position  */
#define MCAN_CCCR_CCE_Pos                     _UINT32_(1)                                          /* (MCAN_CCCR) Configuration Change Enable (read/write, write protection) Position */
#define MCAN_CCCR_CCE_Msk                     (_UINT32_(0x1) << MCAN_CCCR_CCE_Pos)                 /* (MCAN_CCCR) Configuration Change Enable (read/write, write protection) Mask */
#define MCAN_CCCR_CCE(value)                  (MCAN_CCCR_CCE_Msk & (_UINT32_(value) << MCAN_CCCR_CCE_Pos)) /* Assigment of value for CCE in the MCAN_CCCR register */
#define   MCAN_CCCR_CCE_PROTECTED_Val         _UINT32_(0x0)                                        /* (MCAN_CCCR) The processor has no write access to the protected configuration registers.  */
#define   MCAN_CCCR_CCE_CONFIGURABLE_Val      _UINT32_(0x1)                                        /* (MCAN_CCCR) The processor has write access to the protected configuration registers (while MCAN_CCCR.INIT = '1').  */
#define MCAN_CCCR_CCE_PROTECTED               (MCAN_CCCR_CCE_PROTECTED_Val << MCAN_CCCR_CCE_Pos)   /* (MCAN_CCCR) The processor has no write access to the protected configuration registers. Position  */
#define MCAN_CCCR_CCE_CONFIGURABLE            (MCAN_CCCR_CCE_CONFIGURABLE_Val << MCAN_CCCR_CCE_Pos) /* (MCAN_CCCR) The processor has write access to the protected configuration registers (while MCAN_CCCR.INIT = '1'). Position  */
#define MCAN_CCCR_ASM_Pos                     _UINT32_(2)                                          /* (MCAN_CCCR) Restricted Operation Mode (read/write, write protection against '1') Position */
#define MCAN_CCCR_ASM_Msk                     (_UINT32_(0x1) << MCAN_CCCR_ASM_Pos)                 /* (MCAN_CCCR) Restricted Operation Mode (read/write, write protection against '1') Mask */
#define MCAN_CCCR_ASM(value)                  (MCAN_CCCR_ASM_Msk & (_UINT32_(value) << MCAN_CCCR_ASM_Pos)) /* Assigment of value for ASM in the MCAN_CCCR register */
#define   MCAN_CCCR_ASM_NORMAL_Val            _UINT32_(0x0)                                        /* (MCAN_CCCR) Normal CAN operation.  */
#define   MCAN_CCCR_ASM_RESTRICTED_Val        _UINT32_(0x1)                                        /* (MCAN_CCCR) Restricted Operation mode active.  */
#define MCAN_CCCR_ASM_NORMAL                  (MCAN_CCCR_ASM_NORMAL_Val << MCAN_CCCR_ASM_Pos)      /* (MCAN_CCCR) Normal CAN operation. Position  */
#define MCAN_CCCR_ASM_RESTRICTED              (MCAN_CCCR_ASM_RESTRICTED_Val << MCAN_CCCR_ASM_Pos)  /* (MCAN_CCCR) Restricted Operation mode active. Position  */
#define MCAN_CCCR_CSA_Pos                     _UINT32_(3)                                          /* (MCAN_CCCR) Clock Stop Acknowledge (read-only) Position */
#define MCAN_CCCR_CSA_Msk                     (_UINT32_(0x1) << MCAN_CCCR_CSA_Pos)                 /* (MCAN_CCCR) Clock Stop Acknowledge (read-only) Mask */
#define MCAN_CCCR_CSA(value)                  (MCAN_CCCR_CSA_Msk & (_UINT32_(value) << MCAN_CCCR_CSA_Pos)) /* Assigment of value for CSA in the MCAN_CCCR register */
#define MCAN_CCCR_CSR_Pos                     _UINT32_(4)                                          /* (MCAN_CCCR) Clock Stop Request (read/write) Position */
#define MCAN_CCCR_CSR_Msk                     (_UINT32_(0x1) << MCAN_CCCR_CSR_Pos)                 /* (MCAN_CCCR) Clock Stop Request (read/write) Mask */
#define MCAN_CCCR_CSR(value)                  (MCAN_CCCR_CSR_Msk & (_UINT32_(value) << MCAN_CCCR_CSR_Pos)) /* Assigment of value for CSR in the MCAN_CCCR register */
#define   MCAN_CCCR_CSR_NO_CLOCK_STOP_Val     _UINT32_(0x0)                                        /* (MCAN_CCCR) No clock stop is requested.  */
#define   MCAN_CCCR_CSR_CLOCK_STOP_Val        _UINT32_(0x1)                                        /* (MCAN_CCCR) Clock stop requested. When clock stop is requested, first INIT and then CSA will be set after all pend-ing transfer requests have been completed and the CAN bus reached idle.  */
#define MCAN_CCCR_CSR_NO_CLOCK_STOP           (MCAN_CCCR_CSR_NO_CLOCK_STOP_Val << MCAN_CCCR_CSR_Pos) /* (MCAN_CCCR) No clock stop is requested. Position  */
#define MCAN_CCCR_CSR_CLOCK_STOP              (MCAN_CCCR_CSR_CLOCK_STOP_Val << MCAN_CCCR_CSR_Pos)  /* (MCAN_CCCR) Clock stop requested. When clock stop is requested, first INIT and then CSA will be set after all pend-ing transfer requests have been completed and the CAN bus reached idle. Position  */
#define MCAN_CCCR_MON_Pos                     _UINT32_(5)                                          /* (MCAN_CCCR) Bus Monitoring Mode (read/write, write protection against '1') Position */
#define MCAN_CCCR_MON_Msk                     (_UINT32_(0x1) << MCAN_CCCR_MON_Pos)                 /* (MCAN_CCCR) Bus Monitoring Mode (read/write, write protection against '1') Mask */
#define MCAN_CCCR_MON(value)                  (MCAN_CCCR_MON_Msk & (_UINT32_(value) << MCAN_CCCR_MON_Pos)) /* Assigment of value for MON in the MCAN_CCCR register */
#define   MCAN_CCCR_MON_DISABLED_Val          _UINT32_(0x0)                                        /* (MCAN_CCCR) Bus Monitoring mode is disabled.  */
#define   MCAN_CCCR_MON_ENABLED_Val           _UINT32_(0x1)                                        /* (MCAN_CCCR) Bus Monitoring mode is enabled.  */
#define MCAN_CCCR_MON_DISABLED                (MCAN_CCCR_MON_DISABLED_Val << MCAN_CCCR_MON_Pos)    /* (MCAN_CCCR) Bus Monitoring mode is disabled. Position  */
#define MCAN_CCCR_MON_ENABLED                 (MCAN_CCCR_MON_ENABLED_Val << MCAN_CCCR_MON_Pos)     /* (MCAN_CCCR) Bus Monitoring mode is enabled. Position  */
#define MCAN_CCCR_DAR_Pos                     _UINT32_(6)                                          /* (MCAN_CCCR) Disable Automatic Retransmission (read/write, write protection) Position */
#define MCAN_CCCR_DAR_Msk                     (_UINT32_(0x1) << MCAN_CCCR_DAR_Pos)                 /* (MCAN_CCCR) Disable Automatic Retransmission (read/write, write protection) Mask */
#define MCAN_CCCR_DAR(value)                  (MCAN_CCCR_DAR_Msk & (_UINT32_(value) << MCAN_CCCR_DAR_Pos)) /* Assigment of value for DAR in the MCAN_CCCR register */
#define   MCAN_CCCR_DAR_AUTO_RETX_Val         _UINT32_(0x0)                                        /* (MCAN_CCCR) Automatic retransmission of messages not transmitted successfully enabled.  */
#define   MCAN_CCCR_DAR_NO_AUTO_RETX_Val      _UINT32_(0x1)                                        /* (MCAN_CCCR) Automatic retransmission disabled.  */
#define MCAN_CCCR_DAR_AUTO_RETX               (MCAN_CCCR_DAR_AUTO_RETX_Val << MCAN_CCCR_DAR_Pos)   /* (MCAN_CCCR) Automatic retransmission of messages not transmitted successfully enabled. Position  */
#define MCAN_CCCR_DAR_NO_AUTO_RETX            (MCAN_CCCR_DAR_NO_AUTO_RETX_Val << MCAN_CCCR_DAR_Pos) /* (MCAN_CCCR) Automatic retransmission disabled. Position  */
#define MCAN_CCCR_TEST_Pos                    _UINT32_(7)                                          /* (MCAN_CCCR) Test Mode Enable (read/write, write protection against '1') Position */
#define MCAN_CCCR_TEST_Msk                    (_UINT32_(0x1) << MCAN_CCCR_TEST_Pos)                /* (MCAN_CCCR) Test Mode Enable (read/write, write protection against '1') Mask */
#define MCAN_CCCR_TEST(value)                 (MCAN_CCCR_TEST_Msk & (_UINT32_(value) << MCAN_CCCR_TEST_Pos)) /* Assigment of value for TEST in the MCAN_CCCR register */
#define   MCAN_CCCR_TEST_DISABLED_Val         _UINT32_(0x0)                                        /* (MCAN_CCCR) Normal operation, MCAN_TEST register holds reset values.  */
#define   MCAN_CCCR_TEST_ENABLED_Val          _UINT32_(0x1)                                        /* (MCAN_CCCR) Test mode, write access to MCAN_TEST register enabled.  */
#define MCAN_CCCR_TEST_DISABLED               (MCAN_CCCR_TEST_DISABLED_Val << MCAN_CCCR_TEST_Pos)  /* (MCAN_CCCR) Normal operation, MCAN_TEST register holds reset values. Position  */
#define MCAN_CCCR_TEST_ENABLED                (MCAN_CCCR_TEST_ENABLED_Val << MCAN_CCCR_TEST_Pos)   /* (MCAN_CCCR) Test mode, write access to MCAN_TEST register enabled. Position  */
#define MCAN_CCCR_FDOE_Pos                    _UINT32_(8)                                          /* (MCAN_CCCR) CAN FD Operation Enable (read/write, write protection) Position */
#define MCAN_CCCR_FDOE_Msk                    (_UINT32_(0x1) << MCAN_CCCR_FDOE_Pos)                /* (MCAN_CCCR) CAN FD Operation Enable (read/write, write protection) Mask */
#define MCAN_CCCR_FDOE(value)                 (MCAN_CCCR_FDOE_Msk & (_UINT32_(value) << MCAN_CCCR_FDOE_Pos)) /* Assigment of value for FDOE in the MCAN_CCCR register */
#define   MCAN_CCCR_FDOE_DISABLED_Val         _UINT32_(0x0)                                        /* (MCAN_CCCR) FD operation disabled.  */
#define   MCAN_CCCR_FDOE_ENABLED_Val          _UINT32_(0x1)                                        /* (MCAN_CCCR) FD operation enabled.  */
#define MCAN_CCCR_FDOE_DISABLED               (MCAN_CCCR_FDOE_DISABLED_Val << MCAN_CCCR_FDOE_Pos)  /* (MCAN_CCCR) FD operation disabled. Position  */
#define MCAN_CCCR_FDOE_ENABLED                (MCAN_CCCR_FDOE_ENABLED_Val << MCAN_CCCR_FDOE_Pos)   /* (MCAN_CCCR) FD operation enabled. Position  */
#define MCAN_CCCR_BRSE_Pos                    _UINT32_(9)                                          /* (MCAN_CCCR) Bit Rate Switching Enable (read/write, write protection) Position */
#define MCAN_CCCR_BRSE_Msk                    (_UINT32_(0x1) << MCAN_CCCR_BRSE_Pos)                /* (MCAN_CCCR) Bit Rate Switching Enable (read/write, write protection) Mask */
#define MCAN_CCCR_BRSE(value)                 (MCAN_CCCR_BRSE_Msk & (_UINT32_(value) << MCAN_CCCR_BRSE_Pos)) /* Assigment of value for BRSE in the MCAN_CCCR register */
#define   MCAN_CCCR_BRSE_DISABLED_Val         _UINT32_(0x0)                                        /* (MCAN_CCCR) Bit rate switching for transmissions disabled.  */
#define   MCAN_CCCR_BRSE_ENABLED_Val          _UINT32_(0x1)                                        /* (MCAN_CCCR) Bit rate switching for transmissions enabled.  */
#define MCAN_CCCR_BRSE_DISABLED               (MCAN_CCCR_BRSE_DISABLED_Val << MCAN_CCCR_BRSE_Pos)  /* (MCAN_CCCR) Bit rate switching for transmissions disabled. Position  */
#define MCAN_CCCR_BRSE_ENABLED                (MCAN_CCCR_BRSE_ENABLED_Val << MCAN_CCCR_BRSE_Pos)   /* (MCAN_CCCR) Bit rate switching for transmissions enabled. Position  */
#define MCAN_CCCR_PXHD_Pos                    _UINT32_(12)                                         /* (MCAN_CCCR) Protocol Exception Event Handling (read/write, write protection) Position */
#define MCAN_CCCR_PXHD_Msk                    (_UINT32_(0x1) << MCAN_CCCR_PXHD_Pos)                /* (MCAN_CCCR) Protocol Exception Event Handling (read/write, write protection) Mask */
#define MCAN_CCCR_PXHD(value)                 (MCAN_CCCR_PXHD_Msk & (_UINT32_(value) << MCAN_CCCR_PXHD_Pos)) /* Assigment of value for PXHD in the MCAN_CCCR register */
#define MCAN_CCCR_EFBI_Pos                    _UINT32_(13)                                         /* (MCAN_CCCR) Edge Filtering during Bus Integration (read/write, write protection) Position */
#define MCAN_CCCR_EFBI_Msk                    (_UINT32_(0x1) << MCAN_CCCR_EFBI_Pos)                /* (MCAN_CCCR) Edge Filtering during Bus Integration (read/write, write protection) Mask */
#define MCAN_CCCR_EFBI(value)                 (MCAN_CCCR_EFBI_Msk & (_UINT32_(value) << MCAN_CCCR_EFBI_Pos)) /* Assigment of value for EFBI in the MCAN_CCCR register */
#define MCAN_CCCR_TXP_Pos                     _UINT32_(14)                                         /* (MCAN_CCCR) Transmit Pause (read/write, write protection) Position */
#define MCAN_CCCR_TXP_Msk                     (_UINT32_(0x1) << MCAN_CCCR_TXP_Pos)                 /* (MCAN_CCCR) Transmit Pause (read/write, write protection) Mask */
#define MCAN_CCCR_TXP(value)                  (MCAN_CCCR_TXP_Msk & (_UINT32_(value) << MCAN_CCCR_TXP_Pos)) /* Assigment of value for TXP in the MCAN_CCCR register */
#define MCAN_CCCR_Msk                         _UINT32_(0x000073FF)                                 /* (MCAN_CCCR) Register Mask  */


/* -------- MCAN_NBTP : (MCAN Offset: 0x1C) (R/W 32) Nominal Bit Timing and Prescaler Register -------- */
#define MCAN_NBTP_NTSEG2_Pos                  _UINT32_(0)                                          /* (MCAN_NBTP) Nominal Time Segment After Sample Point Position */
#define MCAN_NBTP_NTSEG2_Msk                  (_UINT32_(0x7F) << MCAN_NBTP_NTSEG2_Pos)             /* (MCAN_NBTP) Nominal Time Segment After Sample Point Mask */
#define MCAN_NBTP_NTSEG2(value)               (MCAN_NBTP_NTSEG2_Msk & (_UINT32_(value) << MCAN_NBTP_NTSEG2_Pos)) /* Assigment of value for NTSEG2 in the MCAN_NBTP register */
#define MCAN_NBTP_NTSEG1_Pos                  _UINT32_(8)                                          /* (MCAN_NBTP) Nominal Time Segment Before Sample Point Position */
#define MCAN_NBTP_NTSEG1_Msk                  (_UINT32_(0xFF) << MCAN_NBTP_NTSEG1_Pos)             /* (MCAN_NBTP) Nominal Time Segment Before Sample Point Mask */
#define MCAN_NBTP_NTSEG1(value)               (MCAN_NBTP_NTSEG1_Msk & (_UINT32_(value) << MCAN_NBTP_NTSEG1_Pos)) /* Assigment of value for NTSEG1 in the MCAN_NBTP register */
#define MCAN_NBTP_NBRP_Pos                    _UINT32_(16)                                         /* (MCAN_NBTP) Nominal Bit Rate Prescaler Position */
#define MCAN_NBTP_NBRP_Msk                    (_UINT32_(0x1FF) << MCAN_NBTP_NBRP_Pos)              /* (MCAN_NBTP) Nominal Bit Rate Prescaler Mask */
#define MCAN_NBTP_NBRP(value)                 (MCAN_NBTP_NBRP_Msk & (_UINT32_(value) << MCAN_NBTP_NBRP_Pos)) /* Assigment of value for NBRP in the MCAN_NBTP register */
#define MCAN_NBTP_NSJW_Pos                    _UINT32_(25)                                         /* (MCAN_NBTP) Nominal (Re) Synchronization Jump Width Position */
#define MCAN_NBTP_NSJW_Msk                    (_UINT32_(0x7F) << MCAN_NBTP_NSJW_Pos)               /* (MCAN_NBTP) Nominal (Re) Synchronization Jump Width Mask */
#define MCAN_NBTP_NSJW(value)                 (MCAN_NBTP_NSJW_Msk & (_UINT32_(value) << MCAN_NBTP_NSJW_Pos)) /* Assigment of value for NSJW in the MCAN_NBTP register */
#define MCAN_NBTP_Msk                         _UINT32_(0xFFFFFF7F)                                 /* (MCAN_NBTP) Register Mask  */


/* -------- MCAN_TSCC : (MCAN Offset: 0x20) (R/W 32) Timestamp Counter Configuration Register -------- */
#define MCAN_TSCC_TSS_Pos                     _UINT32_(0)                                          /* (MCAN_TSCC) Timestamp Select Position */
#define MCAN_TSCC_TSS_Msk                     (_UINT32_(0x3) << MCAN_TSCC_TSS_Pos)                 /* (MCAN_TSCC) Timestamp Select Mask */
#define MCAN_TSCC_TSS(value)                  (MCAN_TSCC_TSS_Msk & (_UINT32_(value) << MCAN_TSCC_TSS_Pos)) /* Assigment of value for TSS in the MCAN_TSCC register */
#define   MCAN_TSCC_TSS_ALWAYS_0_Val          _UINT32_(0x0)                                        /* (MCAN_TSCC) Timestamp counter value always 0x0000  */
#define   MCAN_TSCC_TSS_TCP_INC_Val           _UINT32_(0x1)                                        /* (MCAN_TSCC) Timestamp counter value incremented according to TCP  */
#define   MCAN_TSCC_TSS_EXT_TIMESTAMP_Val     _UINT32_(0x2)                                        /* (MCAN_TSCC) External timestamp counter value used  */
#define MCAN_TSCC_TSS_ALWAYS_0                (MCAN_TSCC_TSS_ALWAYS_0_Val << MCAN_TSCC_TSS_Pos)    /* (MCAN_TSCC) Timestamp counter value always 0x0000 Position  */
#define MCAN_TSCC_TSS_TCP_INC                 (MCAN_TSCC_TSS_TCP_INC_Val << MCAN_TSCC_TSS_Pos)     /* (MCAN_TSCC) Timestamp counter value incremented according to TCP Position  */
#define MCAN_TSCC_TSS_EXT_TIMESTAMP           (MCAN_TSCC_TSS_EXT_TIMESTAMP_Val << MCAN_TSCC_TSS_Pos) /* (MCAN_TSCC) External timestamp counter value used Position  */
#define MCAN_TSCC_TCP_Pos                     _UINT32_(16)                                         /* (MCAN_TSCC) Timestamp Counter Prescaler Position */
#define MCAN_TSCC_TCP_Msk                     (_UINT32_(0xF) << MCAN_TSCC_TCP_Pos)                 /* (MCAN_TSCC) Timestamp Counter Prescaler Mask */
#define MCAN_TSCC_TCP(value)                  (MCAN_TSCC_TCP_Msk & (_UINT32_(value) << MCAN_TSCC_TCP_Pos)) /* Assigment of value for TCP in the MCAN_TSCC register */
#define MCAN_TSCC_Msk                         _UINT32_(0x000F0003)                                 /* (MCAN_TSCC) Register Mask  */


/* -------- MCAN_TSCV : (MCAN Offset: 0x24) (R/W 32) Timestamp Counter Value Register -------- */
#define MCAN_TSCV_TSC_Pos                     _UINT32_(0)                                          /* (MCAN_TSCV) Timestamp Counter (cleared on write) Position */
#define MCAN_TSCV_TSC_Msk                     (_UINT32_(0xFFFF) << MCAN_TSCV_TSC_Pos)              /* (MCAN_TSCV) Timestamp Counter (cleared on write) Mask */
#define MCAN_TSCV_TSC(value)                  (MCAN_TSCV_TSC_Msk & (_UINT32_(value) << MCAN_TSCV_TSC_Pos)) /* Assigment of value for TSC in the MCAN_TSCV register */
#define MCAN_TSCV_Msk                         _UINT32_(0x0000FFFF)                                 /* (MCAN_TSCV) Register Mask  */


/* -------- MCAN_TOCC : (MCAN Offset: 0x28) (R/W 32) Timeout Counter Configuration Register -------- */
#define MCAN_TOCC_ETOC_Pos                    _UINT32_(0)                                          /* (MCAN_TOCC) Enable Timeout Counter Position */
#define MCAN_TOCC_ETOC_Msk                    (_UINT32_(0x1) << MCAN_TOCC_ETOC_Pos)                /* (MCAN_TOCC) Enable Timeout Counter Mask */
#define MCAN_TOCC_ETOC(value)                 (MCAN_TOCC_ETOC_Msk & (_UINT32_(value) << MCAN_TOCC_ETOC_Pos)) /* Assigment of value for ETOC in the MCAN_TOCC register */
#define   MCAN_TOCC_ETOC_NO_TIMEOUT_Val       _UINT32_(0x0)                                        /* (MCAN_TOCC) Timeout Counter disabled.  */
#define   MCAN_TOCC_ETOC_TOS_CONTROLLED_Val   _UINT32_(0x1)                                        /* (MCAN_TOCC) Timeout Counter enabled.  */
#define MCAN_TOCC_ETOC_NO_TIMEOUT             (MCAN_TOCC_ETOC_NO_TIMEOUT_Val << MCAN_TOCC_ETOC_Pos) /* (MCAN_TOCC) Timeout Counter disabled. Position  */
#define MCAN_TOCC_ETOC_TOS_CONTROLLED         (MCAN_TOCC_ETOC_TOS_CONTROLLED_Val << MCAN_TOCC_ETOC_Pos) /* (MCAN_TOCC) Timeout Counter enabled. Position  */
#define MCAN_TOCC_TOS_Pos                     _UINT32_(1)                                          /* (MCAN_TOCC) Timeout Select Position */
#define MCAN_TOCC_TOS_Msk                     (_UINT32_(0x3) << MCAN_TOCC_TOS_Pos)                 /* (MCAN_TOCC) Timeout Select Mask */
#define MCAN_TOCC_TOS(value)                  (MCAN_TOCC_TOS_Msk & (_UINT32_(value) << MCAN_TOCC_TOS_Pos)) /* Assigment of value for TOS in the MCAN_TOCC register */
#define   MCAN_TOCC_TOS_CONTINUOUS_Val        _UINT32_(0x0)                                        /* (MCAN_TOCC) Continuous operation  */
#define   MCAN_TOCC_TOS_TX_EV_TIMEOUT_Val     _UINT32_(0x1)                                        /* (MCAN_TOCC) Timeout controlled by Tx Event FIFO  */
#define   MCAN_TOCC_TOS_RX0_EV_TIMEOUT_Val    _UINT32_(0x2)                                        /* (MCAN_TOCC) Timeout controlled by Receive FIFO 0  */
#define   MCAN_TOCC_TOS_RX1_EV_TIMEOUT_Val    _UINT32_(0x3)                                        /* (MCAN_TOCC) Timeout controlled by Receive FIFO 1  */
#define MCAN_TOCC_TOS_CONTINUOUS              (MCAN_TOCC_TOS_CONTINUOUS_Val << MCAN_TOCC_TOS_Pos)  /* (MCAN_TOCC) Continuous operation Position  */
#define MCAN_TOCC_TOS_TX_EV_TIMEOUT           (MCAN_TOCC_TOS_TX_EV_TIMEOUT_Val << MCAN_TOCC_TOS_Pos) /* (MCAN_TOCC) Timeout controlled by Tx Event FIFO Position  */
#define MCAN_TOCC_TOS_RX0_EV_TIMEOUT          (MCAN_TOCC_TOS_RX0_EV_TIMEOUT_Val << MCAN_TOCC_TOS_Pos) /* (MCAN_TOCC) Timeout controlled by Receive FIFO 0 Position  */
#define MCAN_TOCC_TOS_RX1_EV_TIMEOUT          (MCAN_TOCC_TOS_RX1_EV_TIMEOUT_Val << MCAN_TOCC_TOS_Pos) /* (MCAN_TOCC) Timeout controlled by Receive FIFO 1 Position  */
#define MCAN_TOCC_TOP_Pos                     _UINT32_(16)                                         /* (MCAN_TOCC) Timeout Period Position */
#define MCAN_TOCC_TOP_Msk                     (_UINT32_(0xFFFF) << MCAN_TOCC_TOP_Pos)              /* (MCAN_TOCC) Timeout Period Mask */
#define MCAN_TOCC_TOP(value)                  (MCAN_TOCC_TOP_Msk & (_UINT32_(value) << MCAN_TOCC_TOP_Pos)) /* Assigment of value for TOP in the MCAN_TOCC register */
#define MCAN_TOCC_Msk                         _UINT32_(0xFFFF0007)                                 /* (MCAN_TOCC) Register Mask  */


/* -------- MCAN_TOCV : (MCAN Offset: 0x2C) (R/W 32) Timeout Counter Value Register -------- */
#define MCAN_TOCV_TOC_Pos                     _UINT32_(0)                                          /* (MCAN_TOCV) Timeout Counter (cleared on write) Position */
#define MCAN_TOCV_TOC_Msk                     (_UINT32_(0xFFFF) << MCAN_TOCV_TOC_Pos)              /* (MCAN_TOCV) Timeout Counter (cleared on write) Mask */
#define MCAN_TOCV_TOC(value)                  (MCAN_TOCV_TOC_Msk & (_UINT32_(value) << MCAN_TOCV_TOC_Pos)) /* Assigment of value for TOC in the MCAN_TOCV register */
#define MCAN_TOCV_Msk                         _UINT32_(0x0000FFFF)                                 /* (MCAN_TOCV) Register Mask  */


/* -------- MCAN_ECR : (MCAN Offset: 0x40) ( R/ 32) Error Counter Register -------- */
#define MCAN_ECR_TEC_Pos                      _UINT32_(0)                                          /* (MCAN_ECR) Transmit Error Counter Position */
#define MCAN_ECR_TEC_Msk                      (_UINT32_(0xFF) << MCAN_ECR_TEC_Pos)                 /* (MCAN_ECR) Transmit Error Counter Mask */
#define MCAN_ECR_TEC(value)                   (MCAN_ECR_TEC_Msk & (_UINT32_(value) << MCAN_ECR_TEC_Pos)) /* Assigment of value for TEC in the MCAN_ECR register */
#define MCAN_ECR_REC_Pos                      _UINT32_(8)                                          /* (MCAN_ECR) Receive Error Counter Position */
#define MCAN_ECR_REC_Msk                      (_UINT32_(0x7F) << MCAN_ECR_REC_Pos)                 /* (MCAN_ECR) Receive Error Counter Mask */
#define MCAN_ECR_REC(value)                   (MCAN_ECR_REC_Msk & (_UINT32_(value) << MCAN_ECR_REC_Pos)) /* Assigment of value for REC in the MCAN_ECR register */
#define MCAN_ECR_RP_Pos                       _UINT32_(15)                                         /* (MCAN_ECR) Receive Error Passive Position */
#define MCAN_ECR_RP_Msk                       (_UINT32_(0x1) << MCAN_ECR_RP_Pos)                   /* (MCAN_ECR) Receive Error Passive Mask */
#define MCAN_ECR_RP(value)                    (MCAN_ECR_RP_Msk & (_UINT32_(value) << MCAN_ECR_RP_Pos)) /* Assigment of value for RP in the MCAN_ECR register */
#define MCAN_ECR_CEL_Pos                      _UINT32_(16)                                         /* (MCAN_ECR) CAN Error Logging (cleared on read) Position */
#define MCAN_ECR_CEL_Msk                      (_UINT32_(0xFF) << MCAN_ECR_CEL_Pos)                 /* (MCAN_ECR) CAN Error Logging (cleared on read) Mask */
#define MCAN_ECR_CEL(value)                   (MCAN_ECR_CEL_Msk & (_UINT32_(value) << MCAN_ECR_CEL_Pos)) /* Assigment of value for CEL in the MCAN_ECR register */
#define MCAN_ECR_Msk                          _UINT32_(0x00FFFFFF)                                 /* (MCAN_ECR) Register Mask  */


/* -------- MCAN_PSR : (MCAN Offset: 0x44) ( R/ 32) Protocol Status Register -------- */
#define MCAN_PSR_LEC_Pos                      _UINT32_(0)                                          /* (MCAN_PSR) Last Error Code (set to 111 on read) Position */
#define MCAN_PSR_LEC_Msk                      (_UINT32_(0x7) << MCAN_PSR_LEC_Pos)                  /* (MCAN_PSR) Last Error Code (set to 111 on read) Mask */
#define MCAN_PSR_LEC(value)                   (MCAN_PSR_LEC_Msk & (_UINT32_(value) << MCAN_PSR_LEC_Pos)) /* Assigment of value for LEC in the MCAN_PSR register */
#define   MCAN_PSR_LEC_NO_ERROR_Val           _UINT32_(0x0)                                        /* (MCAN_PSR) No error occurred since LEC has been reset by successful reception or transmission.  */
#define   MCAN_PSR_LEC_STUFF_ERROR_Val        _UINT32_(0x1)                                        /* (MCAN_PSR) More than 5 equal bits in a sequence have occurred in a part of a received message where this is not allowed.  */
#define   MCAN_PSR_LEC_FORM_ERROR_Val         _UINT32_(0x2)                                        /* (MCAN_PSR) A fixed format part of a received frame has the wrong format.  */
#define   MCAN_PSR_LEC_ACK_ERROR_Val          _UINT32_(0x3)                                        /* (MCAN_PSR) The message transmitted by the MCAN was not acknowledged by another node.  */
#define   MCAN_PSR_LEC_BIT1_ERROR_Val         _UINT32_(0x4)                                        /* (MCAN_PSR) During transmission of a message (with the exception of the arbitration field), the device tried to send a recessive level (bit of logical value '1'), but the monitored bus value was dominant.  */
#define   MCAN_PSR_LEC_BIT0_ERROR_Val         _UINT32_(0x5)                                        /* (MCAN_PSR) During transmission of a message (or acknowledge bit, or active error flag, or overload flag), the device tried to send a dominant level (data or identifier bit logical value '0'), but the monitored bus value was recessive. During Bus_Off recovery, this status is set each time a sequence of 11 recessive bits has been monitored. This enables the processor to monitor the proceeding of the Bus_Off recovery sequence (indicating the bus is not stuck at dominant or continuously disturbed).  */
#define   MCAN_PSR_LEC_CRC_ERROR_Val          _UINT32_(0x6)                                        /* (MCAN_PSR) The CRC check sum of a received message was incorrect. The CRC of an incoming message does not match the CRC calculated from the received data.  */
#define   MCAN_PSR_LEC_NO_CHANGE_Val          _UINT32_(0x7)                                        /* (MCAN_PSR) Any read access to the Protocol Status Register re-initializes the LEC to '7'. When the LEC shows value '7', no CAN bus event was detected since the last processor read access to the Protocol Status Register.  */
#define MCAN_PSR_LEC_NO_ERROR                 (MCAN_PSR_LEC_NO_ERROR_Val << MCAN_PSR_LEC_Pos)      /* (MCAN_PSR) No error occurred since LEC has been reset by successful reception or transmission. Position  */
#define MCAN_PSR_LEC_STUFF_ERROR              (MCAN_PSR_LEC_STUFF_ERROR_Val << MCAN_PSR_LEC_Pos)   /* (MCAN_PSR) More than 5 equal bits in a sequence have occurred in a part of a received message where this is not allowed. Position  */
#define MCAN_PSR_LEC_FORM_ERROR               (MCAN_PSR_LEC_FORM_ERROR_Val << MCAN_PSR_LEC_Pos)    /* (MCAN_PSR) A fixed format part of a received frame has the wrong format. Position  */
#define MCAN_PSR_LEC_ACK_ERROR                (MCAN_PSR_LEC_ACK_ERROR_Val << MCAN_PSR_LEC_Pos)     /* (MCAN_PSR) The message transmitted by the MCAN was not acknowledged by another node. Position  */
#define MCAN_PSR_LEC_BIT1_ERROR               (MCAN_PSR_LEC_BIT1_ERROR_Val << MCAN_PSR_LEC_Pos)    /* (MCAN_PSR) During transmission of a message (with the exception of the arbitration field), the device tried to send a recessive level (bit of logical value '1'), but the monitored bus value was dominant. Position  */
#define MCAN_PSR_LEC_BIT0_ERROR               (MCAN_PSR_LEC_BIT0_ERROR_Val << MCAN_PSR_LEC_Pos)    /* (MCAN_PSR) During transmission of a message (or acknowledge bit, or active error flag, or overload flag), the device tried to send a dominant level (data or identifier bit logical value '0'), but the monitored bus value was recessive. During Bus_Off recovery, this status is set each time a sequence of 11 recessive bits has been monitored. This enables the processor to monitor the proceeding of the Bus_Off recovery sequence (indicating the bus is not stuck at dominant or continuously disturbed). Position  */
#define MCAN_PSR_LEC_CRC_ERROR                (MCAN_PSR_LEC_CRC_ERROR_Val << MCAN_PSR_LEC_Pos)     /* (MCAN_PSR) The CRC check sum of a received message was incorrect. The CRC of an incoming message does not match the CRC calculated from the received data. Position  */
#define MCAN_PSR_LEC_NO_CHANGE                (MCAN_PSR_LEC_NO_CHANGE_Val << MCAN_PSR_LEC_Pos)     /* (MCAN_PSR) Any read access to the Protocol Status Register re-initializes the LEC to '7'. When the LEC shows value '7', no CAN bus event was detected since the last processor read access to the Protocol Status Register. Position  */
#define MCAN_PSR_ACT_Pos                      _UINT32_(3)                                          /* (MCAN_PSR) Activity Position */
#define MCAN_PSR_ACT_Msk                      (_UINT32_(0x3) << MCAN_PSR_ACT_Pos)                  /* (MCAN_PSR) Activity Mask */
#define MCAN_PSR_ACT(value)                   (MCAN_PSR_ACT_Msk & (_UINT32_(value) << MCAN_PSR_ACT_Pos)) /* Assigment of value for ACT in the MCAN_PSR register */
#define   MCAN_PSR_ACT_SYNCHRONIZING_Val      _UINT32_(0x0)                                        /* (MCAN_PSR) Node is synchronizing on CAN communication  */
#define   MCAN_PSR_ACT_IDLE_Val               _UINT32_(0x1)                                        /* (MCAN_PSR) Node is neither receiver nor transmitter  */
#define   MCAN_PSR_ACT_RECEIVER_Val           _UINT32_(0x2)                                        /* (MCAN_PSR) Node is operating as receiver  */
#define   MCAN_PSR_ACT_TRANSMITTER_Val        _UINT32_(0x3)                                        /* (MCAN_PSR) Node is operating as transmitter  */
#define MCAN_PSR_ACT_SYNCHRONIZING            (MCAN_PSR_ACT_SYNCHRONIZING_Val << MCAN_PSR_ACT_Pos) /* (MCAN_PSR) Node is synchronizing on CAN communication Position  */
#define MCAN_PSR_ACT_IDLE                     (MCAN_PSR_ACT_IDLE_Val << MCAN_PSR_ACT_Pos)          /* (MCAN_PSR) Node is neither receiver nor transmitter Position  */
#define MCAN_PSR_ACT_RECEIVER                 (MCAN_PSR_ACT_RECEIVER_Val << MCAN_PSR_ACT_Pos)      /* (MCAN_PSR) Node is operating as receiver Position  */
#define MCAN_PSR_ACT_TRANSMITTER              (MCAN_PSR_ACT_TRANSMITTER_Val << MCAN_PSR_ACT_Pos)   /* (MCAN_PSR) Node is operating as transmitter Position  */
#define MCAN_PSR_EP_Pos                       _UINT32_(5)                                          /* (MCAN_PSR) Error Passive Position */
#define MCAN_PSR_EP_Msk                       (_UINT32_(0x1) << MCAN_PSR_EP_Pos)                   /* (MCAN_PSR) Error Passive Mask */
#define MCAN_PSR_EP(value)                    (MCAN_PSR_EP_Msk & (_UINT32_(value) << MCAN_PSR_EP_Pos)) /* Assigment of value for EP in the MCAN_PSR register */
#define MCAN_PSR_EW_Pos                       _UINT32_(6)                                          /* (MCAN_PSR) Warning Status Position */
#define MCAN_PSR_EW_Msk                       (_UINT32_(0x1) << MCAN_PSR_EW_Pos)                   /* (MCAN_PSR) Warning Status Mask */
#define MCAN_PSR_EW(value)                    (MCAN_PSR_EW_Msk & (_UINT32_(value) << MCAN_PSR_EW_Pos)) /* Assigment of value for EW in the MCAN_PSR register */
#define MCAN_PSR_BO_Pos                       _UINT32_(7)                                          /* (MCAN_PSR) Bus_Off Status Position */
#define MCAN_PSR_BO_Msk                       (_UINT32_(0x1) << MCAN_PSR_BO_Pos)                   /* (MCAN_PSR) Bus_Off Status Mask */
#define MCAN_PSR_BO(value)                    (MCAN_PSR_BO_Msk & (_UINT32_(value) << MCAN_PSR_BO_Pos)) /* Assigment of value for BO in the MCAN_PSR register */
#define MCAN_PSR_DLEC_Pos                     _UINT32_(8)                                          /* (MCAN_PSR) Data Phase Last Error Code (set to 111 on read) Position */
#define MCAN_PSR_DLEC_Msk                     (_UINT32_(0x7) << MCAN_PSR_DLEC_Pos)                 /* (MCAN_PSR) Data Phase Last Error Code (set to 111 on read) Mask */
#define MCAN_PSR_DLEC(value)                  (MCAN_PSR_DLEC_Msk & (_UINT32_(value) << MCAN_PSR_DLEC_Pos)) /* Assigment of value for DLEC in the MCAN_PSR register */
#define MCAN_PSR_RESI_Pos                     _UINT32_(11)                                         /* (MCAN_PSR) ESI Flag of Last Received CAN FD Message (cleared on read) Position */
#define MCAN_PSR_RESI_Msk                     (_UINT32_(0x1) << MCAN_PSR_RESI_Pos)                 /* (MCAN_PSR) ESI Flag of Last Received CAN FD Message (cleared on read) Mask */
#define MCAN_PSR_RESI(value)                  (MCAN_PSR_RESI_Msk & (_UINT32_(value) << MCAN_PSR_RESI_Pos)) /* Assigment of value for RESI in the MCAN_PSR register */
#define MCAN_PSR_RBRS_Pos                     _UINT32_(12)                                         /* (MCAN_PSR) BRS Flag of Last Received CAN FD Message (cleared on read) Position */
#define MCAN_PSR_RBRS_Msk                     (_UINT32_(0x1) << MCAN_PSR_RBRS_Pos)                 /* (MCAN_PSR) BRS Flag of Last Received CAN FD Message (cleared on read) Mask */
#define MCAN_PSR_RBRS(value)                  (MCAN_PSR_RBRS_Msk & (_UINT32_(value) << MCAN_PSR_RBRS_Pos)) /* Assigment of value for RBRS in the MCAN_PSR register */
#define MCAN_PSR_RFDF_Pos                     _UINT32_(13)                                         /* (MCAN_PSR) Received a CAN FD Message (cleared on read) Position */
#define MCAN_PSR_RFDF_Msk                     (_UINT32_(0x1) << MCAN_PSR_RFDF_Pos)                 /* (MCAN_PSR) Received a CAN FD Message (cleared on read) Mask */
#define MCAN_PSR_RFDF(value)                  (MCAN_PSR_RFDF_Msk & (_UINT32_(value) << MCAN_PSR_RFDF_Pos)) /* Assigment of value for RFDF in the MCAN_PSR register */
#define MCAN_PSR_PXE_Pos                      _UINT32_(14)                                         /* (MCAN_PSR) Protocol Exception Event (cleared on read) Position */
#define MCAN_PSR_PXE_Msk                      (_UINT32_(0x1) << MCAN_PSR_PXE_Pos)                  /* (MCAN_PSR) Protocol Exception Event (cleared on read) Mask */
#define MCAN_PSR_PXE(value)                   (MCAN_PSR_PXE_Msk & (_UINT32_(value) << MCAN_PSR_PXE_Pos)) /* Assigment of value for PXE in the MCAN_PSR register */
#define MCAN_PSR_TDCV_Pos                     _UINT32_(16)                                         /* (MCAN_PSR) Transmitter Delay Compensation Value Position */
#define MCAN_PSR_TDCV_Msk                     (_UINT32_(0x7F) << MCAN_PSR_TDCV_Pos)                /* (MCAN_PSR) Transmitter Delay Compensation Value Mask */
#define MCAN_PSR_TDCV(value)                  (MCAN_PSR_TDCV_Msk & (_UINT32_(value) << MCAN_PSR_TDCV_Pos)) /* Assigment of value for TDCV in the MCAN_PSR register */
#define MCAN_PSR_Msk                          _UINT32_(0x007F7FFF)                                 /* (MCAN_PSR) Register Mask  */


/* -------- MCAN_TDCR : (MCAN Offset: 0x48) (R/W 32) Transmit Delay Compensation Register -------- */
#define MCAN_TDCR_TDCF_Pos                    _UINT32_(0)                                          /* (MCAN_TDCR) Transmitter Delay Compensation Filter Position */
#define MCAN_TDCR_TDCF_Msk                    (_UINT32_(0x7F) << MCAN_TDCR_TDCF_Pos)               /* (MCAN_TDCR) Transmitter Delay Compensation Filter Mask */
#define MCAN_TDCR_TDCF(value)                 (MCAN_TDCR_TDCF_Msk & (_UINT32_(value) << MCAN_TDCR_TDCF_Pos)) /* Assigment of value for TDCF in the MCAN_TDCR register */
#define MCAN_TDCR_TDCO_Pos                    _UINT32_(8)                                          /* (MCAN_TDCR) Transmitter Delay Compensation Offset Position */
#define MCAN_TDCR_TDCO_Msk                    (_UINT32_(0x7F) << MCAN_TDCR_TDCO_Pos)               /* (MCAN_TDCR) Transmitter Delay Compensation Offset Mask */
#define MCAN_TDCR_TDCO(value)                 (MCAN_TDCR_TDCO_Msk & (_UINT32_(value) << MCAN_TDCR_TDCO_Pos)) /* Assigment of value for TDCO in the MCAN_TDCR register */
#define MCAN_TDCR_Msk                         _UINT32_(0x00007F7F)                                 /* (MCAN_TDCR) Register Mask  */


/* -------- MCAN_IR : (MCAN Offset: 0x50) (R/W 32) Interrupt Register -------- */
#define MCAN_IR_RF0N_Pos                      _UINT32_(0)                                          /* (MCAN_IR) Receive FIFO 0 New Message Position */
#define MCAN_IR_RF0N_Msk                      (_UINT32_(0x1) << MCAN_IR_RF0N_Pos)                  /* (MCAN_IR) Receive FIFO 0 New Message Mask */
#define MCAN_IR_RF0N(value)                   (MCAN_IR_RF0N_Msk & (_UINT32_(value) << MCAN_IR_RF0N_Pos)) /* Assigment of value for RF0N in the MCAN_IR register */
#define MCAN_IR_RF0W_Pos                      _UINT32_(1)                                          /* (MCAN_IR) Receive FIFO 0 Watermark Reached Position */
#define MCAN_IR_RF0W_Msk                      (_UINT32_(0x1) << MCAN_IR_RF0W_Pos)                  /* (MCAN_IR) Receive FIFO 0 Watermark Reached Mask */
#define MCAN_IR_RF0W(value)                   (MCAN_IR_RF0W_Msk & (_UINT32_(value) << MCAN_IR_RF0W_Pos)) /* Assigment of value for RF0W in the MCAN_IR register */
#define MCAN_IR_RF0F_Pos                      _UINT32_(2)                                          /* (MCAN_IR) Receive FIFO 0 Full Position */
#define MCAN_IR_RF0F_Msk                      (_UINT32_(0x1) << MCAN_IR_RF0F_Pos)                  /* (MCAN_IR) Receive FIFO 0 Full Mask */
#define MCAN_IR_RF0F(value)                   (MCAN_IR_RF0F_Msk & (_UINT32_(value) << MCAN_IR_RF0F_Pos)) /* Assigment of value for RF0F in the MCAN_IR register */
#define MCAN_IR_RF0L_Pos                      _UINT32_(3)                                          /* (MCAN_IR) Receive FIFO 0 Message Lost Position */
#define MCAN_IR_RF0L_Msk                      (_UINT32_(0x1) << MCAN_IR_RF0L_Pos)                  /* (MCAN_IR) Receive FIFO 0 Message Lost Mask */
#define MCAN_IR_RF0L(value)                   (MCAN_IR_RF0L_Msk & (_UINT32_(value) << MCAN_IR_RF0L_Pos)) /* Assigment of value for RF0L in the MCAN_IR register */
#define MCAN_IR_RF1N_Pos                      _UINT32_(4)                                          /* (MCAN_IR) Receive FIFO 1 New Message Position */
#define MCAN_IR_RF1N_Msk                      (_UINT32_(0x1) << MCAN_IR_RF1N_Pos)                  /* (MCAN_IR) Receive FIFO 1 New Message Mask */
#define MCAN_IR_RF1N(value)                   (MCAN_IR_RF1N_Msk & (_UINT32_(value) << MCAN_IR_RF1N_Pos)) /* Assigment of value for RF1N in the MCAN_IR register */
#define MCAN_IR_RF1W_Pos                      _UINT32_(5)                                          /* (MCAN_IR) Receive FIFO 1 Watermark Reached Position */
#define MCAN_IR_RF1W_Msk                      (_UINT32_(0x1) << MCAN_IR_RF1W_Pos)                  /* (MCAN_IR) Receive FIFO 1 Watermark Reached Mask */
#define MCAN_IR_RF1W(value)                   (MCAN_IR_RF1W_Msk & (_UINT32_(value) << MCAN_IR_RF1W_Pos)) /* Assigment of value for RF1W in the MCAN_IR register */
#define MCAN_IR_RF1F_Pos                      _UINT32_(6)                                          /* (MCAN_IR) Receive FIFO 1 Full Position */
#define MCAN_IR_RF1F_Msk                      (_UINT32_(0x1) << MCAN_IR_RF1F_Pos)                  /* (MCAN_IR) Receive FIFO 1 Full Mask */
#define MCAN_IR_RF1F(value)                   (MCAN_IR_RF1F_Msk & (_UINT32_(value) << MCAN_IR_RF1F_Pos)) /* Assigment of value for RF1F in the MCAN_IR register */
#define MCAN_IR_RF1L_Pos                      _UINT32_(7)                                          /* (MCAN_IR) Receive FIFO 1 Message Lost Position */
#define MCAN_IR_RF1L_Msk                      (_UINT32_(0x1) << MCAN_IR_RF1L_Pos)                  /* (MCAN_IR) Receive FIFO 1 Message Lost Mask */
#define MCAN_IR_RF1L(value)                   (MCAN_IR_RF1L_Msk & (_UINT32_(value) << MCAN_IR_RF1L_Pos)) /* Assigment of value for RF1L in the MCAN_IR register */
#define MCAN_IR_HPM_Pos                       _UINT32_(8)                                          /* (MCAN_IR) High Priority Message Position */
#define MCAN_IR_HPM_Msk                       (_UINT32_(0x1) << MCAN_IR_HPM_Pos)                   /* (MCAN_IR) High Priority Message Mask */
#define MCAN_IR_HPM(value)                    (MCAN_IR_HPM_Msk & (_UINT32_(value) << MCAN_IR_HPM_Pos)) /* Assigment of value for HPM in the MCAN_IR register */
#define MCAN_IR_TC_Pos                        _UINT32_(9)                                          /* (MCAN_IR) Transmission Completed Position */
#define MCAN_IR_TC_Msk                        (_UINT32_(0x1) << MCAN_IR_TC_Pos)                    /* (MCAN_IR) Transmission Completed Mask */
#define MCAN_IR_TC(value)                     (MCAN_IR_TC_Msk & (_UINT32_(value) << MCAN_IR_TC_Pos)) /* Assigment of value for TC in the MCAN_IR register */
#define MCAN_IR_TCF_Pos                       _UINT32_(10)                                         /* (MCAN_IR) Transmission Cancellation Finished Position */
#define MCAN_IR_TCF_Msk                       (_UINT32_(0x1) << MCAN_IR_TCF_Pos)                   /* (MCAN_IR) Transmission Cancellation Finished Mask */
#define MCAN_IR_TCF(value)                    (MCAN_IR_TCF_Msk & (_UINT32_(value) << MCAN_IR_TCF_Pos)) /* Assigment of value for TCF in the MCAN_IR register */
#define MCAN_IR_TFE_Pos                       _UINT32_(11)                                         /* (MCAN_IR) Tx FIFO Empty Position */
#define MCAN_IR_TFE_Msk                       (_UINT32_(0x1) << MCAN_IR_TFE_Pos)                   /* (MCAN_IR) Tx FIFO Empty Mask */
#define MCAN_IR_TFE(value)                    (MCAN_IR_TFE_Msk & (_UINT32_(value) << MCAN_IR_TFE_Pos)) /* Assigment of value for TFE in the MCAN_IR register */
#define MCAN_IR_TEFN_Pos                      _UINT32_(12)                                         /* (MCAN_IR) Tx Event FIFO New Entry Position */
#define MCAN_IR_TEFN_Msk                      (_UINT32_(0x1) << MCAN_IR_TEFN_Pos)                  /* (MCAN_IR) Tx Event FIFO New Entry Mask */
#define MCAN_IR_TEFN(value)                   (MCAN_IR_TEFN_Msk & (_UINT32_(value) << MCAN_IR_TEFN_Pos)) /* Assigment of value for TEFN in the MCAN_IR register */
#define MCAN_IR_TEFW_Pos                      _UINT32_(13)                                         /* (MCAN_IR) Tx Event FIFO Watermark Reached Position */
#define MCAN_IR_TEFW_Msk                      (_UINT32_(0x1) << MCAN_IR_TEFW_Pos)                  /* (MCAN_IR) Tx Event FIFO Watermark Reached Mask */
#define MCAN_IR_TEFW(value)                   (MCAN_IR_TEFW_Msk & (_UINT32_(value) << MCAN_IR_TEFW_Pos)) /* Assigment of value for TEFW in the MCAN_IR register */
#define MCAN_IR_TEFF_Pos                      _UINT32_(14)                                         /* (MCAN_IR) Tx Event FIFO Full Position */
#define MCAN_IR_TEFF_Msk                      (_UINT32_(0x1) << MCAN_IR_TEFF_Pos)                  /* (MCAN_IR) Tx Event FIFO Full Mask */
#define MCAN_IR_TEFF(value)                   (MCAN_IR_TEFF_Msk & (_UINT32_(value) << MCAN_IR_TEFF_Pos)) /* Assigment of value for TEFF in the MCAN_IR register */
#define MCAN_IR_TEFL_Pos                      _UINT32_(15)                                         /* (MCAN_IR) Tx Event FIFO Element Lost Position */
#define MCAN_IR_TEFL_Msk                      (_UINT32_(0x1) << MCAN_IR_TEFL_Pos)                  /* (MCAN_IR) Tx Event FIFO Element Lost Mask */
#define MCAN_IR_TEFL(value)                   (MCAN_IR_TEFL_Msk & (_UINT32_(value) << MCAN_IR_TEFL_Pos)) /* Assigment of value for TEFL in the MCAN_IR register */
#define MCAN_IR_TSW_Pos                       _UINT32_(16)                                         /* (MCAN_IR) Timestamp Wraparound Position */
#define MCAN_IR_TSW_Msk                       (_UINT32_(0x1) << MCAN_IR_TSW_Pos)                   /* (MCAN_IR) Timestamp Wraparound Mask */
#define MCAN_IR_TSW(value)                    (MCAN_IR_TSW_Msk & (_UINT32_(value) << MCAN_IR_TSW_Pos)) /* Assigment of value for TSW in the MCAN_IR register */
#define MCAN_IR_MRAF_Pos                      _UINT32_(17)                                         /* (MCAN_IR) Message RAM Access Failure Position */
#define MCAN_IR_MRAF_Msk                      (_UINT32_(0x1) << MCAN_IR_MRAF_Pos)                  /* (MCAN_IR) Message RAM Access Failure Mask */
#define MCAN_IR_MRAF(value)                   (MCAN_IR_MRAF_Msk & (_UINT32_(value) << MCAN_IR_MRAF_Pos)) /* Assigment of value for MRAF in the MCAN_IR register */
#define MCAN_IR_TOO_Pos                       _UINT32_(18)                                         /* (MCAN_IR) Timeout Occurred Position */
#define MCAN_IR_TOO_Msk                       (_UINT32_(0x1) << MCAN_IR_TOO_Pos)                   /* (MCAN_IR) Timeout Occurred Mask */
#define MCAN_IR_TOO(value)                    (MCAN_IR_TOO_Msk & (_UINT32_(value) << MCAN_IR_TOO_Pos)) /* Assigment of value for TOO in the MCAN_IR register */
#define MCAN_IR_DRX_Pos                       _UINT32_(19)                                         /* (MCAN_IR) Message stored to Dedicated Receive Buffer Position */
#define MCAN_IR_DRX_Msk                       (_UINT32_(0x1) << MCAN_IR_DRX_Pos)                   /* (MCAN_IR) Message stored to Dedicated Receive Buffer Mask */
#define MCAN_IR_DRX(value)                    (MCAN_IR_DRX_Msk & (_UINT32_(value) << MCAN_IR_DRX_Pos)) /* Assigment of value for DRX in the MCAN_IR register */
#define MCAN_IR_BEC_Pos                       _UINT32_(20)                                         /* (MCAN_IR) Bit Error Corrected Position */
#define MCAN_IR_BEC_Msk                       (_UINT32_(0x1) << MCAN_IR_BEC_Pos)                   /* (MCAN_IR) Bit Error Corrected Mask */
#define MCAN_IR_BEC(value)                    (MCAN_IR_BEC_Msk & (_UINT32_(value) << MCAN_IR_BEC_Pos)) /* Assigment of value for BEC in the MCAN_IR register */
#define MCAN_IR_BEU_Pos                       _UINT32_(21)                                         /* (MCAN_IR) Bit Error Uncorrected Position */
#define MCAN_IR_BEU_Msk                       (_UINT32_(0x1) << MCAN_IR_BEU_Pos)                   /* (MCAN_IR) Bit Error Uncorrected Mask */
#define MCAN_IR_BEU(value)                    (MCAN_IR_BEU_Msk & (_UINT32_(value) << MCAN_IR_BEU_Pos)) /* Assigment of value for BEU in the MCAN_IR register */
#define MCAN_IR_ELO_Pos                       _UINT32_(22)                                         /* (MCAN_IR) Error Logging Overflow Position */
#define MCAN_IR_ELO_Msk                       (_UINT32_(0x1) << MCAN_IR_ELO_Pos)                   /* (MCAN_IR) Error Logging Overflow Mask */
#define MCAN_IR_ELO(value)                    (MCAN_IR_ELO_Msk & (_UINT32_(value) << MCAN_IR_ELO_Pos)) /* Assigment of value for ELO in the MCAN_IR register */
#define MCAN_IR_EP_Pos                        _UINT32_(23)                                         /* (MCAN_IR) Error Passive Position */
#define MCAN_IR_EP_Msk                        (_UINT32_(0x1) << MCAN_IR_EP_Pos)                    /* (MCAN_IR) Error Passive Mask */
#define MCAN_IR_EP(value)                     (MCAN_IR_EP_Msk & (_UINT32_(value) << MCAN_IR_EP_Pos)) /* Assigment of value for EP in the MCAN_IR register */
#define MCAN_IR_EW_Pos                        _UINT32_(24)                                         /* (MCAN_IR) Warning Status Position */
#define MCAN_IR_EW_Msk                        (_UINT32_(0x1) << MCAN_IR_EW_Pos)                    /* (MCAN_IR) Warning Status Mask */
#define MCAN_IR_EW(value)                     (MCAN_IR_EW_Msk & (_UINT32_(value) << MCAN_IR_EW_Pos)) /* Assigment of value for EW in the MCAN_IR register */
#define MCAN_IR_BO_Pos                        _UINT32_(25)                                         /* (MCAN_IR) Bus_Off Status Position */
#define MCAN_IR_BO_Msk                        (_UINT32_(0x1) << MCAN_IR_BO_Pos)                    /* (MCAN_IR) Bus_Off Status Mask */
#define MCAN_IR_BO(value)                     (MCAN_IR_BO_Msk & (_UINT32_(value) << MCAN_IR_BO_Pos)) /* Assigment of value for BO in the MCAN_IR register */
#define MCAN_IR_WDI_Pos                       _UINT32_(26)                                         /* (MCAN_IR) Watchdog Interrupt Position */
#define MCAN_IR_WDI_Msk                       (_UINT32_(0x1) << MCAN_IR_WDI_Pos)                   /* (MCAN_IR) Watchdog Interrupt Mask */
#define MCAN_IR_WDI(value)                    (MCAN_IR_WDI_Msk & (_UINT32_(value) << MCAN_IR_WDI_Pos)) /* Assigment of value for WDI in the MCAN_IR register */
#define MCAN_IR_PEA_Pos                       _UINT32_(27)                                         /* (MCAN_IR) Protocol Error in Arbitration Phase Position */
#define MCAN_IR_PEA_Msk                       (_UINT32_(0x1) << MCAN_IR_PEA_Pos)                   /* (MCAN_IR) Protocol Error in Arbitration Phase Mask */
#define MCAN_IR_PEA(value)                    (MCAN_IR_PEA_Msk & (_UINT32_(value) << MCAN_IR_PEA_Pos)) /* Assigment of value for PEA in the MCAN_IR register */
#define MCAN_IR_PED_Pos                       _UINT32_(28)                                         /* (MCAN_IR) Protocol Error in Data Phase Position */
#define MCAN_IR_PED_Msk                       (_UINT32_(0x1) << MCAN_IR_PED_Pos)                   /* (MCAN_IR) Protocol Error in Data Phase Mask */
#define MCAN_IR_PED(value)                    (MCAN_IR_PED_Msk & (_UINT32_(value) << MCAN_IR_PED_Pos)) /* Assigment of value for PED in the MCAN_IR register */
#define MCAN_IR_ARA_Pos                       _UINT32_(29)                                         /* (MCAN_IR) Access to Reserved Address Position */
#define MCAN_IR_ARA_Msk                       (_UINT32_(0x1) << MCAN_IR_ARA_Pos)                   /* (MCAN_IR) Access to Reserved Address Mask */
#define MCAN_IR_ARA(value)                    (MCAN_IR_ARA_Msk & (_UINT32_(value) << MCAN_IR_ARA_Pos)) /* Assigment of value for ARA in the MCAN_IR register */
#define MCAN_IR_Msk                           _UINT32_(0x3FFFFFFF)                                 /* (MCAN_IR) Register Mask  */


/* -------- MCAN_IE : (MCAN Offset: 0x54) (R/W 32) Interrupt Enable Register -------- */
#define MCAN_IE_RF0NE_Pos                     _UINT32_(0)                                          /* (MCAN_IE) Receive FIFO 0 New Message Interrupt Enable Position */
#define MCAN_IE_RF0NE_Msk                     (_UINT32_(0x1) << MCAN_IE_RF0NE_Pos)                 /* (MCAN_IE) Receive FIFO 0 New Message Interrupt Enable Mask */
#define MCAN_IE_RF0NE(value)                  (MCAN_IE_RF0NE_Msk & (_UINT32_(value) << MCAN_IE_RF0NE_Pos)) /* Assigment of value for RF0NE in the MCAN_IE register */
#define MCAN_IE_RF0WE_Pos                     _UINT32_(1)                                          /* (MCAN_IE) Receive FIFO 0 Watermark Reached Interrupt Enable Position */
#define MCAN_IE_RF0WE_Msk                     (_UINT32_(0x1) << MCAN_IE_RF0WE_Pos)                 /* (MCAN_IE) Receive FIFO 0 Watermark Reached Interrupt Enable Mask */
#define MCAN_IE_RF0WE(value)                  (MCAN_IE_RF0WE_Msk & (_UINT32_(value) << MCAN_IE_RF0WE_Pos)) /* Assigment of value for RF0WE in the MCAN_IE register */
#define MCAN_IE_RF0FE_Pos                     _UINT32_(2)                                          /* (MCAN_IE) Receive FIFO 0 Full Interrupt Enable Position */
#define MCAN_IE_RF0FE_Msk                     (_UINT32_(0x1) << MCAN_IE_RF0FE_Pos)                 /* (MCAN_IE) Receive FIFO 0 Full Interrupt Enable Mask */
#define MCAN_IE_RF0FE(value)                  (MCAN_IE_RF0FE_Msk & (_UINT32_(value) << MCAN_IE_RF0FE_Pos)) /* Assigment of value for RF0FE in the MCAN_IE register */
#define MCAN_IE_RF0LE_Pos                     _UINT32_(3)                                          /* (MCAN_IE) Receive FIFO 0 Message Lost Interrupt Enable Position */
#define MCAN_IE_RF0LE_Msk                     (_UINT32_(0x1) << MCAN_IE_RF0LE_Pos)                 /* (MCAN_IE) Receive FIFO 0 Message Lost Interrupt Enable Mask */
#define MCAN_IE_RF0LE(value)                  (MCAN_IE_RF0LE_Msk & (_UINT32_(value) << MCAN_IE_RF0LE_Pos)) /* Assigment of value for RF0LE in the MCAN_IE register */
#define MCAN_IE_RF1NE_Pos                     _UINT32_(4)                                          /* (MCAN_IE) Receive FIFO 1 New Message Interrupt Enable Position */
#define MCAN_IE_RF1NE_Msk                     (_UINT32_(0x1) << MCAN_IE_RF1NE_Pos)                 /* (MCAN_IE) Receive FIFO 1 New Message Interrupt Enable Mask */
#define MCAN_IE_RF1NE(value)                  (MCAN_IE_RF1NE_Msk & (_UINT32_(value) << MCAN_IE_RF1NE_Pos)) /* Assigment of value for RF1NE in the MCAN_IE register */
#define MCAN_IE_RF1WE_Pos                     _UINT32_(5)                                          /* (MCAN_IE) Receive FIFO 1 Watermark Reached Interrupt Enable Position */
#define MCAN_IE_RF1WE_Msk                     (_UINT32_(0x1) << MCAN_IE_RF1WE_Pos)                 /* (MCAN_IE) Receive FIFO 1 Watermark Reached Interrupt Enable Mask */
#define MCAN_IE_RF1WE(value)                  (MCAN_IE_RF1WE_Msk & (_UINT32_(value) << MCAN_IE_RF1WE_Pos)) /* Assigment of value for RF1WE in the MCAN_IE register */
#define MCAN_IE_RF1FE_Pos                     _UINT32_(6)                                          /* (MCAN_IE) Receive FIFO 1 Full Interrupt Enable Position */
#define MCAN_IE_RF1FE_Msk                     (_UINT32_(0x1) << MCAN_IE_RF1FE_Pos)                 /* (MCAN_IE) Receive FIFO 1 Full Interrupt Enable Mask */
#define MCAN_IE_RF1FE(value)                  (MCAN_IE_RF1FE_Msk & (_UINT32_(value) << MCAN_IE_RF1FE_Pos)) /* Assigment of value for RF1FE in the MCAN_IE register */
#define MCAN_IE_RF1LE_Pos                     _UINT32_(7)                                          /* (MCAN_IE) Receive FIFO 1 Message Lost Interrupt Enable Position */
#define MCAN_IE_RF1LE_Msk                     (_UINT32_(0x1) << MCAN_IE_RF1LE_Pos)                 /* (MCAN_IE) Receive FIFO 1 Message Lost Interrupt Enable Mask */
#define MCAN_IE_RF1LE(value)                  (MCAN_IE_RF1LE_Msk & (_UINT32_(value) << MCAN_IE_RF1LE_Pos)) /* Assigment of value for RF1LE in the MCAN_IE register */
#define MCAN_IE_HPME_Pos                      _UINT32_(8)                                          /* (MCAN_IE) High Priority Message Interrupt Enable Position */
#define MCAN_IE_HPME_Msk                      (_UINT32_(0x1) << MCAN_IE_HPME_Pos)                  /* (MCAN_IE) High Priority Message Interrupt Enable Mask */
#define MCAN_IE_HPME(value)                   (MCAN_IE_HPME_Msk & (_UINT32_(value) << MCAN_IE_HPME_Pos)) /* Assigment of value for HPME in the MCAN_IE register */
#define MCAN_IE_TCE_Pos                       _UINT32_(9)                                          /* (MCAN_IE) Transmission Completed Interrupt Enable Position */
#define MCAN_IE_TCE_Msk                       (_UINT32_(0x1) << MCAN_IE_TCE_Pos)                   /* (MCAN_IE) Transmission Completed Interrupt Enable Mask */
#define MCAN_IE_TCE(value)                    (MCAN_IE_TCE_Msk & (_UINT32_(value) << MCAN_IE_TCE_Pos)) /* Assigment of value for TCE in the MCAN_IE register */
#define MCAN_IE_TCFE_Pos                      _UINT32_(10)                                         /* (MCAN_IE) Transmission Cancellation Finished Interrupt Enable Position */
#define MCAN_IE_TCFE_Msk                      (_UINT32_(0x1) << MCAN_IE_TCFE_Pos)                  /* (MCAN_IE) Transmission Cancellation Finished Interrupt Enable Mask */
#define MCAN_IE_TCFE(value)                   (MCAN_IE_TCFE_Msk & (_UINT32_(value) << MCAN_IE_TCFE_Pos)) /* Assigment of value for TCFE in the MCAN_IE register */
#define MCAN_IE_TFEE_Pos                      _UINT32_(11)                                         /* (MCAN_IE) Tx FIFO Empty Interrupt Enable Position */
#define MCAN_IE_TFEE_Msk                      (_UINT32_(0x1) << MCAN_IE_TFEE_Pos)                  /* (MCAN_IE) Tx FIFO Empty Interrupt Enable Mask */
#define MCAN_IE_TFEE(value)                   (MCAN_IE_TFEE_Msk & (_UINT32_(value) << MCAN_IE_TFEE_Pos)) /* Assigment of value for TFEE in the MCAN_IE register */
#define MCAN_IE_TEFNE_Pos                     _UINT32_(12)                                         /* (MCAN_IE) Tx Event FIFO New Entry Interrupt Enable Position */
#define MCAN_IE_TEFNE_Msk                     (_UINT32_(0x1) << MCAN_IE_TEFNE_Pos)                 /* (MCAN_IE) Tx Event FIFO New Entry Interrupt Enable Mask */
#define MCAN_IE_TEFNE(value)                  (MCAN_IE_TEFNE_Msk & (_UINT32_(value) << MCAN_IE_TEFNE_Pos)) /* Assigment of value for TEFNE in the MCAN_IE register */
#define MCAN_IE_TEFWE_Pos                     _UINT32_(13)                                         /* (MCAN_IE) Tx Event FIFO Watermark Reached Interrupt Enable Position */
#define MCAN_IE_TEFWE_Msk                     (_UINT32_(0x1) << MCAN_IE_TEFWE_Pos)                 /* (MCAN_IE) Tx Event FIFO Watermark Reached Interrupt Enable Mask */
#define MCAN_IE_TEFWE(value)                  (MCAN_IE_TEFWE_Msk & (_UINT32_(value) << MCAN_IE_TEFWE_Pos)) /* Assigment of value for TEFWE in the MCAN_IE register */
#define MCAN_IE_TEFFE_Pos                     _UINT32_(14)                                         /* (MCAN_IE) Tx Event FIFO Full Interrupt Enable Position */
#define MCAN_IE_TEFFE_Msk                     (_UINT32_(0x1) << MCAN_IE_TEFFE_Pos)                 /* (MCAN_IE) Tx Event FIFO Full Interrupt Enable Mask */
#define MCAN_IE_TEFFE(value)                  (MCAN_IE_TEFFE_Msk & (_UINT32_(value) << MCAN_IE_TEFFE_Pos)) /* Assigment of value for TEFFE in the MCAN_IE register */
#define MCAN_IE_TEFLE_Pos                     _UINT32_(15)                                         /* (MCAN_IE) Tx Event FIFO Event Lost Interrupt Enable Position */
#define MCAN_IE_TEFLE_Msk                     (_UINT32_(0x1) << MCAN_IE_TEFLE_Pos)                 /* (MCAN_IE) Tx Event FIFO Event Lost Interrupt Enable Mask */
#define MCAN_IE_TEFLE(value)                  (MCAN_IE_TEFLE_Msk & (_UINT32_(value) << MCAN_IE_TEFLE_Pos)) /* Assigment of value for TEFLE in the MCAN_IE register */
#define MCAN_IE_TSWE_Pos                      _UINT32_(16)                                         /* (MCAN_IE) Timestamp Wraparound Interrupt Enable Position */
#define MCAN_IE_TSWE_Msk                      (_UINT32_(0x1) << MCAN_IE_TSWE_Pos)                  /* (MCAN_IE) Timestamp Wraparound Interrupt Enable Mask */
#define MCAN_IE_TSWE(value)                   (MCAN_IE_TSWE_Msk & (_UINT32_(value) << MCAN_IE_TSWE_Pos)) /* Assigment of value for TSWE in the MCAN_IE register */
#define MCAN_IE_MRAFE_Pos                     _UINT32_(17)                                         /* (MCAN_IE) Message RAM Access Failure Interrupt Enable Position */
#define MCAN_IE_MRAFE_Msk                     (_UINT32_(0x1) << MCAN_IE_MRAFE_Pos)                 /* (MCAN_IE) Message RAM Access Failure Interrupt Enable Mask */
#define MCAN_IE_MRAFE(value)                  (MCAN_IE_MRAFE_Msk & (_UINT32_(value) << MCAN_IE_MRAFE_Pos)) /* Assigment of value for MRAFE in the MCAN_IE register */
#define MCAN_IE_TOOE_Pos                      _UINT32_(18)                                         /* (MCAN_IE) Timeout Occurred Interrupt Enable Position */
#define MCAN_IE_TOOE_Msk                      (_UINT32_(0x1) << MCAN_IE_TOOE_Pos)                  /* (MCAN_IE) Timeout Occurred Interrupt Enable Mask */
#define MCAN_IE_TOOE(value)                   (MCAN_IE_TOOE_Msk & (_UINT32_(value) << MCAN_IE_TOOE_Pos)) /* Assigment of value for TOOE in the MCAN_IE register */
#define MCAN_IE_DRXE_Pos                      _UINT32_(19)                                         /* (MCAN_IE) Message stored to Dedicated Receive Buffer Interrupt Enable Position */
#define MCAN_IE_DRXE_Msk                      (_UINT32_(0x1) << MCAN_IE_DRXE_Pos)                  /* (MCAN_IE) Message stored to Dedicated Receive Buffer Interrupt Enable Mask */
#define MCAN_IE_DRXE(value)                   (MCAN_IE_DRXE_Msk & (_UINT32_(value) << MCAN_IE_DRXE_Pos)) /* Assigment of value for DRXE in the MCAN_IE register */
#define MCAN_IE_BECE_Pos                      _UINT32_(20)                                         /* (MCAN_IE) Bit Error Corrected Interrupt Enable Position */
#define MCAN_IE_BECE_Msk                      (_UINT32_(0x1) << MCAN_IE_BECE_Pos)                  /* (MCAN_IE) Bit Error Corrected Interrupt Enable Mask */
#define MCAN_IE_BECE(value)                   (MCAN_IE_BECE_Msk & (_UINT32_(value) << MCAN_IE_BECE_Pos)) /* Assigment of value for BECE in the MCAN_IE register */
#define MCAN_IE_BEUE_Pos                      _UINT32_(21)                                         /* (MCAN_IE) Bit Error Uncorrected Interrupt Enable Position */
#define MCAN_IE_BEUE_Msk                      (_UINT32_(0x1) << MCAN_IE_BEUE_Pos)                  /* (MCAN_IE) Bit Error Uncorrected Interrupt Enable Mask */
#define MCAN_IE_BEUE(value)                   (MCAN_IE_BEUE_Msk & (_UINT32_(value) << MCAN_IE_BEUE_Pos)) /* Assigment of value for BEUE in the MCAN_IE register */
#define MCAN_IE_ELOE_Pos                      _UINT32_(22)                                         /* (MCAN_IE) Error Logging Overflow Interrupt Enable Position */
#define MCAN_IE_ELOE_Msk                      (_UINT32_(0x1) << MCAN_IE_ELOE_Pos)                  /* (MCAN_IE) Error Logging Overflow Interrupt Enable Mask */
#define MCAN_IE_ELOE(value)                   (MCAN_IE_ELOE_Msk & (_UINT32_(value) << MCAN_IE_ELOE_Pos)) /* Assigment of value for ELOE in the MCAN_IE register */
#define MCAN_IE_EPE_Pos                       _UINT32_(23)                                         /* (MCAN_IE) Error Passive Interrupt Enable Position */
#define MCAN_IE_EPE_Msk                       (_UINT32_(0x1) << MCAN_IE_EPE_Pos)                   /* (MCAN_IE) Error Passive Interrupt Enable Mask */
#define MCAN_IE_EPE(value)                    (MCAN_IE_EPE_Msk & (_UINT32_(value) << MCAN_IE_EPE_Pos)) /* Assigment of value for EPE in the MCAN_IE register */
#define MCAN_IE_EWE_Pos                       _UINT32_(24)                                         /* (MCAN_IE) Warning Status Interrupt Enable Position */
#define MCAN_IE_EWE_Msk                       (_UINT32_(0x1) << MCAN_IE_EWE_Pos)                   /* (MCAN_IE) Warning Status Interrupt Enable Mask */
#define MCAN_IE_EWE(value)                    (MCAN_IE_EWE_Msk & (_UINT32_(value) << MCAN_IE_EWE_Pos)) /* Assigment of value for EWE in the MCAN_IE register */
#define MCAN_IE_BOE_Pos                       _UINT32_(25)                                         /* (MCAN_IE) Bus_Off Status Interrupt Enable Position */
#define MCAN_IE_BOE_Msk                       (_UINT32_(0x1) << MCAN_IE_BOE_Pos)                   /* (MCAN_IE) Bus_Off Status Interrupt Enable Mask */
#define MCAN_IE_BOE(value)                    (MCAN_IE_BOE_Msk & (_UINT32_(value) << MCAN_IE_BOE_Pos)) /* Assigment of value for BOE in the MCAN_IE register */
#define MCAN_IE_WDIE_Pos                      _UINT32_(26)                                         /* (MCAN_IE) Watchdog Interrupt Enable Position */
#define MCAN_IE_WDIE_Msk                      (_UINT32_(0x1) << MCAN_IE_WDIE_Pos)                  /* (MCAN_IE) Watchdog Interrupt Enable Mask */
#define MCAN_IE_WDIE(value)                   (MCAN_IE_WDIE_Msk & (_UINT32_(value) << MCAN_IE_WDIE_Pos)) /* Assigment of value for WDIE in the MCAN_IE register */
#define MCAN_IE_PEAE_Pos                      _UINT32_(27)                                         /* (MCAN_IE) Protocol Error in Arbitration Phase Enable Position */
#define MCAN_IE_PEAE_Msk                      (_UINT32_(0x1) << MCAN_IE_PEAE_Pos)                  /* (MCAN_IE) Protocol Error in Arbitration Phase Enable Mask */
#define MCAN_IE_PEAE(value)                   (MCAN_IE_PEAE_Msk & (_UINT32_(value) << MCAN_IE_PEAE_Pos)) /* Assigment of value for PEAE in the MCAN_IE register */
#define MCAN_IE_PEDE_Pos                      _UINT32_(28)                                         /* (MCAN_IE) Protocol Error in Data Phase Enable Position */
#define MCAN_IE_PEDE_Msk                      (_UINT32_(0x1) << MCAN_IE_PEDE_Pos)                  /* (MCAN_IE) Protocol Error in Data Phase Enable Mask */
#define MCAN_IE_PEDE(value)                   (MCAN_IE_PEDE_Msk & (_UINT32_(value) << MCAN_IE_PEDE_Pos)) /* Assigment of value for PEDE in the MCAN_IE register */
#define MCAN_IE_ARAE_Pos                      _UINT32_(29)                                         /* (MCAN_IE) Access to Reserved Address Enable Position */
#define MCAN_IE_ARAE_Msk                      (_UINT32_(0x1) << MCAN_IE_ARAE_Pos)                  /* (MCAN_IE) Access to Reserved Address Enable Mask */
#define MCAN_IE_ARAE(value)                   (MCAN_IE_ARAE_Msk & (_UINT32_(value) << MCAN_IE_ARAE_Pos)) /* Assigment of value for ARAE in the MCAN_IE register */
#define MCAN_IE_Msk                           _UINT32_(0x3FFFFFFF)                                 /* (MCAN_IE) Register Mask  */


/* -------- MCAN_ILS : (MCAN Offset: 0x58) (R/W 32) Interrupt Line Select Register -------- */
#define MCAN_ILS_RF0NL_Pos                    _UINT32_(0)                                          /* (MCAN_ILS) Receive FIFO 0 New Message Interrupt Line Position */
#define MCAN_ILS_RF0NL_Msk                    (_UINT32_(0x1) << MCAN_ILS_RF0NL_Pos)                /* (MCAN_ILS) Receive FIFO 0 New Message Interrupt Line Mask */
#define MCAN_ILS_RF0NL(value)                 (MCAN_ILS_RF0NL_Msk & (_UINT32_(value) << MCAN_ILS_RF0NL_Pos)) /* Assigment of value for RF0NL in the MCAN_ILS register */
#define MCAN_ILS_RF0WL_Pos                    _UINT32_(1)                                          /* (MCAN_ILS) Receive FIFO 0 Watermark Reached Interrupt Line Position */
#define MCAN_ILS_RF0WL_Msk                    (_UINT32_(0x1) << MCAN_ILS_RF0WL_Pos)                /* (MCAN_ILS) Receive FIFO 0 Watermark Reached Interrupt Line Mask */
#define MCAN_ILS_RF0WL(value)                 (MCAN_ILS_RF0WL_Msk & (_UINT32_(value) << MCAN_ILS_RF0WL_Pos)) /* Assigment of value for RF0WL in the MCAN_ILS register */
#define MCAN_ILS_RF0FL_Pos                    _UINT32_(2)                                          /* (MCAN_ILS) Receive FIFO 0 Full Interrupt Line Position */
#define MCAN_ILS_RF0FL_Msk                    (_UINT32_(0x1) << MCAN_ILS_RF0FL_Pos)                /* (MCAN_ILS) Receive FIFO 0 Full Interrupt Line Mask */
#define MCAN_ILS_RF0FL(value)                 (MCAN_ILS_RF0FL_Msk & (_UINT32_(value) << MCAN_ILS_RF0FL_Pos)) /* Assigment of value for RF0FL in the MCAN_ILS register */
#define MCAN_ILS_RF0LL_Pos                    _UINT32_(3)                                          /* (MCAN_ILS) Receive FIFO 0 Message Lost Interrupt Line Position */
#define MCAN_ILS_RF0LL_Msk                    (_UINT32_(0x1) << MCAN_ILS_RF0LL_Pos)                /* (MCAN_ILS) Receive FIFO 0 Message Lost Interrupt Line Mask */
#define MCAN_ILS_RF0LL(value)                 (MCAN_ILS_RF0LL_Msk & (_UINT32_(value) << MCAN_ILS_RF0LL_Pos)) /* Assigment of value for RF0LL in the MCAN_ILS register */
#define MCAN_ILS_RF1NL_Pos                    _UINT32_(4)                                          /* (MCAN_ILS) Receive FIFO 1 New Message Interrupt Line Position */
#define MCAN_ILS_RF1NL_Msk                    (_UINT32_(0x1) << MCAN_ILS_RF1NL_Pos)                /* (MCAN_ILS) Receive FIFO 1 New Message Interrupt Line Mask */
#define MCAN_ILS_RF1NL(value)                 (MCAN_ILS_RF1NL_Msk & (_UINT32_(value) << MCAN_ILS_RF1NL_Pos)) /* Assigment of value for RF1NL in the MCAN_ILS register */
#define MCAN_ILS_RF1WL_Pos                    _UINT32_(5)                                          /* (MCAN_ILS) Receive FIFO 1 Watermark Reached Interrupt Line Position */
#define MCAN_ILS_RF1WL_Msk                    (_UINT32_(0x1) << MCAN_ILS_RF1WL_Pos)                /* (MCAN_ILS) Receive FIFO 1 Watermark Reached Interrupt Line Mask */
#define MCAN_ILS_RF1WL(value)                 (MCAN_ILS_RF1WL_Msk & (_UINT32_(value) << MCAN_ILS_RF1WL_Pos)) /* Assigment of value for RF1WL in the MCAN_ILS register */
#define MCAN_ILS_RF1FL_Pos                    _UINT32_(6)                                          /* (MCAN_ILS) Receive FIFO 1 Full Interrupt Line Position */
#define MCAN_ILS_RF1FL_Msk                    (_UINT32_(0x1) << MCAN_ILS_RF1FL_Pos)                /* (MCAN_ILS) Receive FIFO 1 Full Interrupt Line Mask */
#define MCAN_ILS_RF1FL(value)                 (MCAN_ILS_RF1FL_Msk & (_UINT32_(value) << MCAN_ILS_RF1FL_Pos)) /* Assigment of value for RF1FL in the MCAN_ILS register */
#define MCAN_ILS_RF1LL_Pos                    _UINT32_(7)                                          /* (MCAN_ILS) Receive FIFO 1 Message Lost Interrupt Line Position */
#define MCAN_ILS_RF1LL_Msk                    (_UINT32_(0x1) << MCAN_ILS_RF1LL_Pos)                /* (MCAN_ILS) Receive FIFO 1 Message Lost Interrupt Line Mask */
#define MCAN_ILS_RF1LL(value)                 (MCAN_ILS_RF1LL_Msk & (_UINT32_(value) << MCAN_ILS_RF1LL_Pos)) /* Assigment of value for RF1LL in the MCAN_ILS register */
#define MCAN_ILS_HPML_Pos                     _UINT32_(8)                                          /* (MCAN_ILS) High Priority Message Interrupt Line Position */
#define MCAN_ILS_HPML_Msk                     (_UINT32_(0x1) << MCAN_ILS_HPML_Pos)                 /* (MCAN_ILS) High Priority Message Interrupt Line Mask */
#define MCAN_ILS_HPML(value)                  (MCAN_ILS_HPML_Msk & (_UINT32_(value) << MCAN_ILS_HPML_Pos)) /* Assigment of value for HPML in the MCAN_ILS register */
#define MCAN_ILS_TCL_Pos                      _UINT32_(9)                                          /* (MCAN_ILS) Transmission Completed Interrupt Line Position */
#define MCAN_ILS_TCL_Msk                      (_UINT32_(0x1) << MCAN_ILS_TCL_Pos)                  /* (MCAN_ILS) Transmission Completed Interrupt Line Mask */
#define MCAN_ILS_TCL(value)                   (MCAN_ILS_TCL_Msk & (_UINT32_(value) << MCAN_ILS_TCL_Pos)) /* Assigment of value for TCL in the MCAN_ILS register */
#define MCAN_ILS_TCFL_Pos                     _UINT32_(10)                                         /* (MCAN_ILS) Transmission Cancellation Finished Interrupt Line Position */
#define MCAN_ILS_TCFL_Msk                     (_UINT32_(0x1) << MCAN_ILS_TCFL_Pos)                 /* (MCAN_ILS) Transmission Cancellation Finished Interrupt Line Mask */
#define MCAN_ILS_TCFL(value)                  (MCAN_ILS_TCFL_Msk & (_UINT32_(value) << MCAN_ILS_TCFL_Pos)) /* Assigment of value for TCFL in the MCAN_ILS register */
#define MCAN_ILS_TFEL_Pos                     _UINT32_(11)                                         /* (MCAN_ILS) Tx FIFO Empty Interrupt Line Position */
#define MCAN_ILS_TFEL_Msk                     (_UINT32_(0x1) << MCAN_ILS_TFEL_Pos)                 /* (MCAN_ILS) Tx FIFO Empty Interrupt Line Mask */
#define MCAN_ILS_TFEL(value)                  (MCAN_ILS_TFEL_Msk & (_UINT32_(value) << MCAN_ILS_TFEL_Pos)) /* Assigment of value for TFEL in the MCAN_ILS register */
#define MCAN_ILS_TEFNL_Pos                    _UINT32_(12)                                         /* (MCAN_ILS) Tx Event FIFO New Entry Interrupt Line Position */
#define MCAN_ILS_TEFNL_Msk                    (_UINT32_(0x1) << MCAN_ILS_TEFNL_Pos)                /* (MCAN_ILS) Tx Event FIFO New Entry Interrupt Line Mask */
#define MCAN_ILS_TEFNL(value)                 (MCAN_ILS_TEFNL_Msk & (_UINT32_(value) << MCAN_ILS_TEFNL_Pos)) /* Assigment of value for TEFNL in the MCAN_ILS register */
#define MCAN_ILS_TEFWL_Pos                    _UINT32_(13)                                         /* (MCAN_ILS) Tx Event FIFO Watermark Reached Interrupt Line Position */
#define MCAN_ILS_TEFWL_Msk                    (_UINT32_(0x1) << MCAN_ILS_TEFWL_Pos)                /* (MCAN_ILS) Tx Event FIFO Watermark Reached Interrupt Line Mask */
#define MCAN_ILS_TEFWL(value)                 (MCAN_ILS_TEFWL_Msk & (_UINT32_(value) << MCAN_ILS_TEFWL_Pos)) /* Assigment of value for TEFWL in the MCAN_ILS register */
#define MCAN_ILS_TEFFL_Pos                    _UINT32_(14)                                         /* (MCAN_ILS) Tx Event FIFO Full Interrupt Line Position */
#define MCAN_ILS_TEFFL_Msk                    (_UINT32_(0x1) << MCAN_ILS_TEFFL_Pos)                /* (MCAN_ILS) Tx Event FIFO Full Interrupt Line Mask */
#define MCAN_ILS_TEFFL(value)                 (MCAN_ILS_TEFFL_Msk & (_UINT32_(value) << MCAN_ILS_TEFFL_Pos)) /* Assigment of value for TEFFL in the MCAN_ILS register */
#define MCAN_ILS_TEFLL_Pos                    _UINT32_(15)                                         /* (MCAN_ILS) Tx Event FIFO Event Lost Interrupt Line Position */
#define MCAN_ILS_TEFLL_Msk                    (_UINT32_(0x1) << MCAN_ILS_TEFLL_Pos)                /* (MCAN_ILS) Tx Event FIFO Event Lost Interrupt Line Mask */
#define MCAN_ILS_TEFLL(value)                 (MCAN_ILS_TEFLL_Msk & (_UINT32_(value) << MCAN_ILS_TEFLL_Pos)) /* Assigment of value for TEFLL in the MCAN_ILS register */
#define MCAN_ILS_TSWL_Pos                     _UINT32_(16)                                         /* (MCAN_ILS) Timestamp Wraparound Interrupt Line Position */
#define MCAN_ILS_TSWL_Msk                     (_UINT32_(0x1) << MCAN_ILS_TSWL_Pos)                 /* (MCAN_ILS) Timestamp Wraparound Interrupt Line Mask */
#define MCAN_ILS_TSWL(value)                  (MCAN_ILS_TSWL_Msk & (_UINT32_(value) << MCAN_ILS_TSWL_Pos)) /* Assigment of value for TSWL in the MCAN_ILS register */
#define MCAN_ILS_MRAFL_Pos                    _UINT32_(17)                                         /* (MCAN_ILS) Message RAM Access Failure Interrupt Line Position */
#define MCAN_ILS_MRAFL_Msk                    (_UINT32_(0x1) << MCAN_ILS_MRAFL_Pos)                /* (MCAN_ILS) Message RAM Access Failure Interrupt Line Mask */
#define MCAN_ILS_MRAFL(value)                 (MCAN_ILS_MRAFL_Msk & (_UINT32_(value) << MCAN_ILS_MRAFL_Pos)) /* Assigment of value for MRAFL in the MCAN_ILS register */
#define MCAN_ILS_TOOL_Pos                     _UINT32_(18)                                         /* (MCAN_ILS) Timeout Occurred Interrupt Line Position */
#define MCAN_ILS_TOOL_Msk                     (_UINT32_(0x1) << MCAN_ILS_TOOL_Pos)                 /* (MCAN_ILS) Timeout Occurred Interrupt Line Mask */
#define MCAN_ILS_TOOL(value)                  (MCAN_ILS_TOOL_Msk & (_UINT32_(value) << MCAN_ILS_TOOL_Pos)) /* Assigment of value for TOOL in the MCAN_ILS register */
#define MCAN_ILS_DRXL_Pos                     _UINT32_(19)                                         /* (MCAN_ILS) Message stored to Dedicated Receive Buffer Interrupt Line Position */
#define MCAN_ILS_DRXL_Msk                     (_UINT32_(0x1) << MCAN_ILS_DRXL_Pos)                 /* (MCAN_ILS) Message stored to Dedicated Receive Buffer Interrupt Line Mask */
#define MCAN_ILS_DRXL(value)                  (MCAN_ILS_DRXL_Msk & (_UINT32_(value) << MCAN_ILS_DRXL_Pos)) /* Assigment of value for DRXL in the MCAN_ILS register */
#define MCAN_ILS_BECL_Pos                     _UINT32_(20)                                         /* (MCAN_ILS) Bit Error Corrected Interrupt Line Position */
#define MCAN_ILS_BECL_Msk                     (_UINT32_(0x1) << MCAN_ILS_BECL_Pos)                 /* (MCAN_ILS) Bit Error Corrected Interrupt Line Mask */
#define MCAN_ILS_BECL(value)                  (MCAN_ILS_BECL_Msk & (_UINT32_(value) << MCAN_ILS_BECL_Pos)) /* Assigment of value for BECL in the MCAN_ILS register */
#define MCAN_ILS_BEUL_Pos                     _UINT32_(21)                                         /* (MCAN_ILS) Bit Error Uncorrected Interrupt Line Position */
#define MCAN_ILS_BEUL_Msk                     (_UINT32_(0x1) << MCAN_ILS_BEUL_Pos)                 /* (MCAN_ILS) Bit Error Uncorrected Interrupt Line Mask */
#define MCAN_ILS_BEUL(value)                  (MCAN_ILS_BEUL_Msk & (_UINT32_(value) << MCAN_ILS_BEUL_Pos)) /* Assigment of value for BEUL in the MCAN_ILS register */
#define MCAN_ILS_ELOL_Pos                     _UINT32_(22)                                         /* (MCAN_ILS) Error Logging Overflow Interrupt Line Position */
#define MCAN_ILS_ELOL_Msk                     (_UINT32_(0x1) << MCAN_ILS_ELOL_Pos)                 /* (MCAN_ILS) Error Logging Overflow Interrupt Line Mask */
#define MCAN_ILS_ELOL(value)                  (MCAN_ILS_ELOL_Msk & (_UINT32_(value) << MCAN_ILS_ELOL_Pos)) /* Assigment of value for ELOL in the MCAN_ILS register */
#define MCAN_ILS_EPL_Pos                      _UINT32_(23)                                         /* (MCAN_ILS) Error Passive Interrupt Line Position */
#define MCAN_ILS_EPL_Msk                      (_UINT32_(0x1) << MCAN_ILS_EPL_Pos)                  /* (MCAN_ILS) Error Passive Interrupt Line Mask */
#define MCAN_ILS_EPL(value)                   (MCAN_ILS_EPL_Msk & (_UINT32_(value) << MCAN_ILS_EPL_Pos)) /* Assigment of value for EPL in the MCAN_ILS register */
#define MCAN_ILS_EWL_Pos                      _UINT32_(24)                                         /* (MCAN_ILS) Warning Status Interrupt Line Position */
#define MCAN_ILS_EWL_Msk                      (_UINT32_(0x1) << MCAN_ILS_EWL_Pos)                  /* (MCAN_ILS) Warning Status Interrupt Line Mask */
#define MCAN_ILS_EWL(value)                   (MCAN_ILS_EWL_Msk & (_UINT32_(value) << MCAN_ILS_EWL_Pos)) /* Assigment of value for EWL in the MCAN_ILS register */
#define MCAN_ILS_BOL_Pos                      _UINT32_(25)                                         /* (MCAN_ILS) Bus_Off Status Interrupt Line Position */
#define MCAN_ILS_BOL_Msk                      (_UINT32_(0x1) << MCAN_ILS_BOL_Pos)                  /* (MCAN_ILS) Bus_Off Status Interrupt Line Mask */
#define MCAN_ILS_BOL(value)                   (MCAN_ILS_BOL_Msk & (_UINT32_(value) << MCAN_ILS_BOL_Pos)) /* Assigment of value for BOL in the MCAN_ILS register */
#define MCAN_ILS_WDIL_Pos                     _UINT32_(26)                                         /* (MCAN_ILS) Watchdog Interrupt Line Position */
#define MCAN_ILS_WDIL_Msk                     (_UINT32_(0x1) << MCAN_ILS_WDIL_Pos)                 /* (MCAN_ILS) Watchdog Interrupt Line Mask */
#define MCAN_ILS_WDIL(value)                  (MCAN_ILS_WDIL_Msk & (_UINT32_(value) << MCAN_ILS_WDIL_Pos)) /* Assigment of value for WDIL in the MCAN_ILS register */
#define MCAN_ILS_PEAL_Pos                     _UINT32_(27)                                         /* (MCAN_ILS) Protocol Error in Arbitration Phase Line Position */
#define MCAN_ILS_PEAL_Msk                     (_UINT32_(0x1) << MCAN_ILS_PEAL_Pos)                 /* (MCAN_ILS) Protocol Error in Arbitration Phase Line Mask */
#define MCAN_ILS_PEAL(value)                  (MCAN_ILS_PEAL_Msk & (_UINT32_(value) << MCAN_ILS_PEAL_Pos)) /* Assigment of value for PEAL in the MCAN_ILS register */
#define MCAN_ILS_PEDL_Pos                     _UINT32_(28)                                         /* (MCAN_ILS) Protocol Error in Data Phase Line Position */
#define MCAN_ILS_PEDL_Msk                     (_UINT32_(0x1) << MCAN_ILS_PEDL_Pos)                 /* (MCAN_ILS) Protocol Error in Data Phase Line Mask */
#define MCAN_ILS_PEDL(value)                  (MCAN_ILS_PEDL_Msk & (_UINT32_(value) << MCAN_ILS_PEDL_Pos)) /* Assigment of value for PEDL in the MCAN_ILS register */
#define MCAN_ILS_ARAL_Pos                     _UINT32_(29)                                         /* (MCAN_ILS) Access to Reserved Address Line Position */
#define MCAN_ILS_ARAL_Msk                     (_UINT32_(0x1) << MCAN_ILS_ARAL_Pos)                 /* (MCAN_ILS) Access to Reserved Address Line Mask */
#define MCAN_ILS_ARAL(value)                  (MCAN_ILS_ARAL_Msk & (_UINT32_(value) << MCAN_ILS_ARAL_Pos)) /* Assigment of value for ARAL in the MCAN_ILS register */
#define MCAN_ILS_Msk                          _UINT32_(0x3FFFFFFF)                                 /* (MCAN_ILS) Register Mask  */


/* -------- MCAN_ILE : (MCAN Offset: 0x5C) (R/W 32) Interrupt Line Enable Register -------- */
#define MCAN_ILE_EINT0_Pos                    _UINT32_(0)                                          /* (MCAN_ILE) Enable Interrupt Line 0 Position */
#define MCAN_ILE_EINT0_Msk                    (_UINT32_(0x1) << MCAN_ILE_EINT0_Pos)                /* (MCAN_ILE) Enable Interrupt Line 0 Mask */
#define MCAN_ILE_EINT0(value)                 (MCAN_ILE_EINT0_Msk & (_UINT32_(value) << MCAN_ILE_EINT0_Pos)) /* Assigment of value for EINT0 in the MCAN_ILE register */
#define MCAN_ILE_EINT1_Pos                    _UINT32_(1)                                          /* (MCAN_ILE) Enable Interrupt Line 1 Position */
#define MCAN_ILE_EINT1_Msk                    (_UINT32_(0x1) << MCAN_ILE_EINT1_Pos)                /* (MCAN_ILE) Enable Interrupt Line 1 Mask */
#define MCAN_ILE_EINT1(value)                 (MCAN_ILE_EINT1_Msk & (_UINT32_(value) << MCAN_ILE_EINT1_Pos)) /* Assigment of value for EINT1 in the MCAN_ILE register */
#define MCAN_ILE_Msk                          _UINT32_(0x00000003)                                 /* (MCAN_ILE) Register Mask  */

#define MCAN_ILE_EINT_Pos                     _UINT32_(0)                                          /* (MCAN_ILE Position) Enable Interrupt Line x */
#define MCAN_ILE_EINT_Msk                     (_UINT32_(0x3) << MCAN_ILE_EINT_Pos)                 /* (MCAN_ILE Mask) EINT */
#define MCAN_ILE_EINT(value)                  (MCAN_ILE_EINT_Msk & (_UINT32_(value) << MCAN_ILE_EINT_Pos)) 

/* -------- MCAN_GFC : (MCAN Offset: 0x80) (R/W 32) Global Filter Configuration Register -------- */
#define MCAN_GFC_RRFE_Pos                     _UINT32_(0)                                          /* (MCAN_GFC) Reject Remote Frames Extended Position */
#define MCAN_GFC_RRFE_Msk                     (_UINT32_(0x1) << MCAN_GFC_RRFE_Pos)                 /* (MCAN_GFC) Reject Remote Frames Extended Mask */
#define MCAN_GFC_RRFE(value)                  (MCAN_GFC_RRFE_Msk & (_UINT32_(value) << MCAN_GFC_RRFE_Pos)) /* Assigment of value for RRFE in the MCAN_GFC register */
#define   MCAN_GFC_RRFE_FILTER_Val            _UINT32_(0x0)                                        /* (MCAN_GFC) Filter remote frames with 29-bit extended IDs.  */
#define   MCAN_GFC_RRFE_REJECT_Val            _UINT32_(0x1)                                        /* (MCAN_GFC) Reject all remote frames with 29-bit extended IDs.  */
#define MCAN_GFC_RRFE_FILTER                  (MCAN_GFC_RRFE_FILTER_Val << MCAN_GFC_RRFE_Pos)      /* (MCAN_GFC) Filter remote frames with 29-bit extended IDs. Position  */
#define MCAN_GFC_RRFE_REJECT                  (MCAN_GFC_RRFE_REJECT_Val << MCAN_GFC_RRFE_Pos)      /* (MCAN_GFC) Reject all remote frames with 29-bit extended IDs. Position  */
#define MCAN_GFC_RRFS_Pos                     _UINT32_(1)                                          /* (MCAN_GFC) Reject Remote Frames Standard Position */
#define MCAN_GFC_RRFS_Msk                     (_UINT32_(0x1) << MCAN_GFC_RRFS_Pos)                 /* (MCAN_GFC) Reject Remote Frames Standard Mask */
#define MCAN_GFC_RRFS(value)                  (MCAN_GFC_RRFS_Msk & (_UINT32_(value) << MCAN_GFC_RRFS_Pos)) /* Assigment of value for RRFS in the MCAN_GFC register */
#define   MCAN_GFC_RRFS_FILTER_Val            _UINT32_(0x0)                                        /* (MCAN_GFC) Filter remote frames with 11-bit standard IDs.  */
#define   MCAN_GFC_RRFS_REJECT_Val            _UINT32_(0x1)                                        /* (MCAN_GFC) Reject all remote frames with 11-bit standard IDs.  */
#define MCAN_GFC_RRFS_FILTER                  (MCAN_GFC_RRFS_FILTER_Val << MCAN_GFC_RRFS_Pos)      /* (MCAN_GFC) Filter remote frames with 11-bit standard IDs. Position  */
#define MCAN_GFC_RRFS_REJECT                  (MCAN_GFC_RRFS_REJECT_Val << MCAN_GFC_RRFS_Pos)      /* (MCAN_GFC) Reject all remote frames with 11-bit standard IDs. Position  */
#define MCAN_GFC_ANFE_Pos                     _UINT32_(2)                                          /* (MCAN_GFC) Accept Non-matching Frames Extended Position */
#define MCAN_GFC_ANFE_Msk                     (_UINT32_(0x3) << MCAN_GFC_ANFE_Pos)                 /* (MCAN_GFC) Accept Non-matching Frames Extended Mask */
#define MCAN_GFC_ANFE(value)                  (MCAN_GFC_ANFE_Msk & (_UINT32_(value) << MCAN_GFC_ANFE_Pos)) /* Assigment of value for ANFE in the MCAN_GFC register */
#define   MCAN_GFC_ANFE_RX_FIFO_0_Val         _UINT32_(0x0)                                        /* (MCAN_GFC) Accept in Rx FIFO 0  */
#define   MCAN_GFC_ANFE_RX_FIFO_1_Val         _UINT32_(0x1)                                        /* (MCAN_GFC) Accept in Rx FIFO 1  */
#define MCAN_GFC_ANFE_RX_FIFO_0               (MCAN_GFC_ANFE_RX_FIFO_0_Val << MCAN_GFC_ANFE_Pos)   /* (MCAN_GFC) Accept in Rx FIFO 0 Position  */
#define MCAN_GFC_ANFE_RX_FIFO_1               (MCAN_GFC_ANFE_RX_FIFO_1_Val << MCAN_GFC_ANFE_Pos)   /* (MCAN_GFC) Accept in Rx FIFO 1 Position  */
#define MCAN_GFC_ANFS_Pos                     _UINT32_(4)                                          /* (MCAN_GFC) Accept Non-matching Frames Standard Position */
#define MCAN_GFC_ANFS_Msk                     (_UINT32_(0x3) << MCAN_GFC_ANFS_Pos)                 /* (MCAN_GFC) Accept Non-matching Frames Standard Mask */
#define MCAN_GFC_ANFS(value)                  (MCAN_GFC_ANFS_Msk & (_UINT32_(value) << MCAN_GFC_ANFS_Pos)) /* Assigment of value for ANFS in the MCAN_GFC register */
#define   MCAN_GFC_ANFS_RX_FIFO_0_Val         _UINT32_(0x0)                                        /* (MCAN_GFC) Accept in Rx FIFO 0  */
#define   MCAN_GFC_ANFS_RX_FIFO_1_Val         _UINT32_(0x1)                                        /* (MCAN_GFC) Accept in Rx FIFO 1  */
#define MCAN_GFC_ANFS_RX_FIFO_0               (MCAN_GFC_ANFS_RX_FIFO_0_Val << MCAN_GFC_ANFS_Pos)   /* (MCAN_GFC) Accept in Rx FIFO 0 Position  */
#define MCAN_GFC_ANFS_RX_FIFO_1               (MCAN_GFC_ANFS_RX_FIFO_1_Val << MCAN_GFC_ANFS_Pos)   /* (MCAN_GFC) Accept in Rx FIFO 1 Position  */
#define MCAN_GFC_Msk                          _UINT32_(0x0000003F)                                 /* (MCAN_GFC) Register Mask  */


/* -------- MCAN_SIDFC : (MCAN Offset: 0x84) (R/W 32) Standard ID Filter Configuration Register -------- */
#define MCAN_SIDFC_FLSSA_Pos                  _UINT32_(2)                                          /* (MCAN_SIDFC) Filter List Standard Start Address Position */
#define MCAN_SIDFC_FLSSA_Msk                  (_UINT32_(0x3FFF) << MCAN_SIDFC_FLSSA_Pos)           /* (MCAN_SIDFC) Filter List Standard Start Address Mask */
#define MCAN_SIDFC_FLSSA(value)               (MCAN_SIDFC_FLSSA_Msk & (_UINT32_(value) << MCAN_SIDFC_FLSSA_Pos)) /* Assigment of value for FLSSA in the MCAN_SIDFC register */
#define MCAN_SIDFC_LSS_Pos                    _UINT32_(16)                                         /* (MCAN_SIDFC) List Size Standard Position */
#define MCAN_SIDFC_LSS_Msk                    (_UINT32_(0xFF) << MCAN_SIDFC_LSS_Pos)               /* (MCAN_SIDFC) List Size Standard Mask */
#define MCAN_SIDFC_LSS(value)                 (MCAN_SIDFC_LSS_Msk & (_UINT32_(value) << MCAN_SIDFC_LSS_Pos)) /* Assigment of value for LSS in the MCAN_SIDFC register */
#define MCAN_SIDFC_Msk                        _UINT32_(0x00FFFFFC)                                 /* (MCAN_SIDFC) Register Mask  */


/* -------- MCAN_XIDFC : (MCAN Offset: 0x88) (R/W 32) Extended ID Filter Configuration Register -------- */
#define MCAN_XIDFC_FLESA_Pos                  _UINT32_(2)                                          /* (MCAN_XIDFC) Filter List Extended Start Address Position */
#define MCAN_XIDFC_FLESA_Msk                  (_UINT32_(0x3FFF) << MCAN_XIDFC_FLESA_Pos)           /* (MCAN_XIDFC) Filter List Extended Start Address Mask */
#define MCAN_XIDFC_FLESA(value)               (MCAN_XIDFC_FLESA_Msk & (_UINT32_(value) << MCAN_XIDFC_FLESA_Pos)) /* Assigment of value for FLESA in the MCAN_XIDFC register */
#define MCAN_XIDFC_LSE_Pos                    _UINT32_(16)                                         /* (MCAN_XIDFC) List Size Extended Position */
#define MCAN_XIDFC_LSE_Msk                    (_UINT32_(0x7F) << MCAN_XIDFC_LSE_Pos)               /* (MCAN_XIDFC) List Size Extended Mask */
#define MCAN_XIDFC_LSE(value)                 (MCAN_XIDFC_LSE_Msk & (_UINT32_(value) << MCAN_XIDFC_LSE_Pos)) /* Assigment of value for LSE in the MCAN_XIDFC register */
#define MCAN_XIDFC_Msk                        _UINT32_(0x007FFFFC)                                 /* (MCAN_XIDFC) Register Mask  */


/* -------- MCAN_XIDAM : (MCAN Offset: 0x90) (R/W 32) Extended ID AND Mask Register -------- */
#define MCAN_XIDAM_EIDM_Pos                   _UINT32_(0)                                          /* (MCAN_XIDAM) Extended ID Mask Position */
#define MCAN_XIDAM_EIDM_Msk                   (_UINT32_(0x1FFFFFFF) << MCAN_XIDAM_EIDM_Pos)        /* (MCAN_XIDAM) Extended ID Mask Mask */
#define MCAN_XIDAM_EIDM(value)                (MCAN_XIDAM_EIDM_Msk & (_UINT32_(value) << MCAN_XIDAM_EIDM_Pos)) /* Assigment of value for EIDM in the MCAN_XIDAM register */
#define MCAN_XIDAM_Msk                        _UINT32_(0x1FFFFFFF)                                 /* (MCAN_XIDAM) Register Mask  */


/* -------- MCAN_HPMS : (MCAN Offset: 0x94) ( R/ 32) High Priority Message Status Register -------- */
#define MCAN_HPMS_BIDX_Pos                    _UINT32_(0)                                          /* (MCAN_HPMS) Buffer Index Position */
#define MCAN_HPMS_BIDX_Msk                    (_UINT32_(0x3F) << MCAN_HPMS_BIDX_Pos)               /* (MCAN_HPMS) Buffer Index Mask */
#define MCAN_HPMS_BIDX(value)                 (MCAN_HPMS_BIDX_Msk & (_UINT32_(value) << MCAN_HPMS_BIDX_Pos)) /* Assigment of value for BIDX in the MCAN_HPMS register */
#define MCAN_HPMS_MSI_Pos                     _UINT32_(6)                                          /* (MCAN_HPMS) Message Storage Indicator Position */
#define MCAN_HPMS_MSI_Msk                     (_UINT32_(0x3) << MCAN_HPMS_MSI_Pos)                 /* (MCAN_HPMS) Message Storage Indicator Mask */
#define MCAN_HPMS_MSI(value)                  (MCAN_HPMS_MSI_Msk & (_UINT32_(value) << MCAN_HPMS_MSI_Pos)) /* Assigment of value for MSI in the MCAN_HPMS register */
#define   MCAN_HPMS_MSI_NO_FIFO_SEL_Val       _UINT32_(0x0)                                        /* (MCAN_HPMS) No FIFO selected.  */
#define   MCAN_HPMS_MSI_LOST_Val              _UINT32_(0x1)                                        /* (MCAN_HPMS) FIFO message lost.  */
#define   MCAN_HPMS_MSI_FIFO_0_Val            _UINT32_(0x2)                                        /* (MCAN_HPMS) Message stored in FIFO 0.  */
#define   MCAN_HPMS_MSI_FIFO_1_Val            _UINT32_(0x3)                                        /* (MCAN_HPMS) Message stored in FIFO 1.  */
#define MCAN_HPMS_MSI_NO_FIFO_SEL             (MCAN_HPMS_MSI_NO_FIFO_SEL_Val << MCAN_HPMS_MSI_Pos) /* (MCAN_HPMS) No FIFO selected. Position  */
#define MCAN_HPMS_MSI_LOST                    (MCAN_HPMS_MSI_LOST_Val << MCAN_HPMS_MSI_Pos)        /* (MCAN_HPMS) FIFO message lost. Position  */
#define MCAN_HPMS_MSI_FIFO_0                  (MCAN_HPMS_MSI_FIFO_0_Val << MCAN_HPMS_MSI_Pos)      /* (MCAN_HPMS) Message stored in FIFO 0. Position  */
#define MCAN_HPMS_MSI_FIFO_1                  (MCAN_HPMS_MSI_FIFO_1_Val << MCAN_HPMS_MSI_Pos)      /* (MCAN_HPMS) Message stored in FIFO 1. Position  */
#define MCAN_HPMS_FIDX_Pos                    _UINT32_(8)                                          /* (MCAN_HPMS) Filter Index Position */
#define MCAN_HPMS_FIDX_Msk                    (_UINT32_(0x7F) << MCAN_HPMS_FIDX_Pos)               /* (MCAN_HPMS) Filter Index Mask */
#define MCAN_HPMS_FIDX(value)                 (MCAN_HPMS_FIDX_Msk & (_UINT32_(value) << MCAN_HPMS_FIDX_Pos)) /* Assigment of value for FIDX in the MCAN_HPMS register */
#define MCAN_HPMS_FLST_Pos                    _UINT32_(15)                                         /* (MCAN_HPMS) Filter List Position */
#define MCAN_HPMS_FLST_Msk                    (_UINT32_(0x1) << MCAN_HPMS_FLST_Pos)                /* (MCAN_HPMS) Filter List Mask */
#define MCAN_HPMS_FLST(value)                 (MCAN_HPMS_FLST_Msk & (_UINT32_(value) << MCAN_HPMS_FLST_Pos)) /* Assigment of value for FLST in the MCAN_HPMS register */
#define MCAN_HPMS_Msk                         _UINT32_(0x0000FFFF)                                 /* (MCAN_HPMS) Register Mask  */


/* -------- MCAN_NDAT1 : (MCAN Offset: 0x98) (R/W 32) New Data 1 Register -------- */
#define MCAN_NDAT1_ND0_Pos                    _UINT32_(0)                                          /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND0_Msk                    (_UINT32_(0x1) << MCAN_NDAT1_ND0_Pos)                /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND0(value)                 (MCAN_NDAT1_ND0_Msk & (_UINT32_(value) << MCAN_NDAT1_ND0_Pos)) /* Assigment of value for ND0 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND1_Pos                    _UINT32_(1)                                          /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND1_Msk                    (_UINT32_(0x1) << MCAN_NDAT1_ND1_Pos)                /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND1(value)                 (MCAN_NDAT1_ND1_Msk & (_UINT32_(value) << MCAN_NDAT1_ND1_Pos)) /* Assigment of value for ND1 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND2_Pos                    _UINT32_(2)                                          /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND2_Msk                    (_UINT32_(0x1) << MCAN_NDAT1_ND2_Pos)                /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND2(value)                 (MCAN_NDAT1_ND2_Msk & (_UINT32_(value) << MCAN_NDAT1_ND2_Pos)) /* Assigment of value for ND2 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND3_Pos                    _UINT32_(3)                                          /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND3_Msk                    (_UINT32_(0x1) << MCAN_NDAT1_ND3_Pos)                /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND3(value)                 (MCAN_NDAT1_ND3_Msk & (_UINT32_(value) << MCAN_NDAT1_ND3_Pos)) /* Assigment of value for ND3 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND4_Pos                    _UINT32_(4)                                          /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND4_Msk                    (_UINT32_(0x1) << MCAN_NDAT1_ND4_Pos)                /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND4(value)                 (MCAN_NDAT1_ND4_Msk & (_UINT32_(value) << MCAN_NDAT1_ND4_Pos)) /* Assigment of value for ND4 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND5_Pos                    _UINT32_(5)                                          /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND5_Msk                    (_UINT32_(0x1) << MCAN_NDAT1_ND5_Pos)                /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND5(value)                 (MCAN_NDAT1_ND5_Msk & (_UINT32_(value) << MCAN_NDAT1_ND5_Pos)) /* Assigment of value for ND5 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND6_Pos                    _UINT32_(6)                                          /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND6_Msk                    (_UINT32_(0x1) << MCAN_NDAT1_ND6_Pos)                /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND6(value)                 (MCAN_NDAT1_ND6_Msk & (_UINT32_(value) << MCAN_NDAT1_ND6_Pos)) /* Assigment of value for ND6 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND7_Pos                    _UINT32_(7)                                          /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND7_Msk                    (_UINT32_(0x1) << MCAN_NDAT1_ND7_Pos)                /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND7(value)                 (MCAN_NDAT1_ND7_Msk & (_UINT32_(value) << MCAN_NDAT1_ND7_Pos)) /* Assigment of value for ND7 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND8_Pos                    _UINT32_(8)                                          /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND8_Msk                    (_UINT32_(0x1) << MCAN_NDAT1_ND8_Pos)                /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND8(value)                 (MCAN_NDAT1_ND8_Msk & (_UINT32_(value) << MCAN_NDAT1_ND8_Pos)) /* Assigment of value for ND8 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND9_Pos                    _UINT32_(9)                                          /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND9_Msk                    (_UINT32_(0x1) << MCAN_NDAT1_ND9_Pos)                /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND9(value)                 (MCAN_NDAT1_ND9_Msk & (_UINT32_(value) << MCAN_NDAT1_ND9_Pos)) /* Assigment of value for ND9 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND10_Pos                   _UINT32_(10)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND10_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND10_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND10(value)                (MCAN_NDAT1_ND10_Msk & (_UINT32_(value) << MCAN_NDAT1_ND10_Pos)) /* Assigment of value for ND10 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND11_Pos                   _UINT32_(11)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND11_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND11_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND11(value)                (MCAN_NDAT1_ND11_Msk & (_UINT32_(value) << MCAN_NDAT1_ND11_Pos)) /* Assigment of value for ND11 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND12_Pos                   _UINT32_(12)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND12_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND12_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND12(value)                (MCAN_NDAT1_ND12_Msk & (_UINT32_(value) << MCAN_NDAT1_ND12_Pos)) /* Assigment of value for ND12 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND13_Pos                   _UINT32_(13)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND13_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND13_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND13(value)                (MCAN_NDAT1_ND13_Msk & (_UINT32_(value) << MCAN_NDAT1_ND13_Pos)) /* Assigment of value for ND13 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND14_Pos                   _UINT32_(14)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND14_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND14_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND14(value)                (MCAN_NDAT1_ND14_Msk & (_UINT32_(value) << MCAN_NDAT1_ND14_Pos)) /* Assigment of value for ND14 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND15_Pos                   _UINT32_(15)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND15_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND15_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND15(value)                (MCAN_NDAT1_ND15_Msk & (_UINT32_(value) << MCAN_NDAT1_ND15_Pos)) /* Assigment of value for ND15 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND16_Pos                   _UINT32_(16)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND16_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND16_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND16(value)                (MCAN_NDAT1_ND16_Msk & (_UINT32_(value) << MCAN_NDAT1_ND16_Pos)) /* Assigment of value for ND16 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND17_Pos                   _UINT32_(17)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND17_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND17_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND17(value)                (MCAN_NDAT1_ND17_Msk & (_UINT32_(value) << MCAN_NDAT1_ND17_Pos)) /* Assigment of value for ND17 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND18_Pos                   _UINT32_(18)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND18_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND18_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND18(value)                (MCAN_NDAT1_ND18_Msk & (_UINT32_(value) << MCAN_NDAT1_ND18_Pos)) /* Assigment of value for ND18 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND19_Pos                   _UINT32_(19)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND19_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND19_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND19(value)                (MCAN_NDAT1_ND19_Msk & (_UINT32_(value) << MCAN_NDAT1_ND19_Pos)) /* Assigment of value for ND19 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND20_Pos                   _UINT32_(20)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND20_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND20_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND20(value)                (MCAN_NDAT1_ND20_Msk & (_UINT32_(value) << MCAN_NDAT1_ND20_Pos)) /* Assigment of value for ND20 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND21_Pos                   _UINT32_(21)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND21_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND21_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND21(value)                (MCAN_NDAT1_ND21_Msk & (_UINT32_(value) << MCAN_NDAT1_ND21_Pos)) /* Assigment of value for ND21 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND22_Pos                   _UINT32_(22)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND22_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND22_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND22(value)                (MCAN_NDAT1_ND22_Msk & (_UINT32_(value) << MCAN_NDAT1_ND22_Pos)) /* Assigment of value for ND22 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND23_Pos                   _UINT32_(23)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND23_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND23_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND23(value)                (MCAN_NDAT1_ND23_Msk & (_UINT32_(value) << MCAN_NDAT1_ND23_Pos)) /* Assigment of value for ND23 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND24_Pos                   _UINT32_(24)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND24_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND24_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND24(value)                (MCAN_NDAT1_ND24_Msk & (_UINT32_(value) << MCAN_NDAT1_ND24_Pos)) /* Assigment of value for ND24 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND25_Pos                   _UINT32_(25)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND25_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND25_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND25(value)                (MCAN_NDAT1_ND25_Msk & (_UINT32_(value) << MCAN_NDAT1_ND25_Pos)) /* Assigment of value for ND25 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND26_Pos                   _UINT32_(26)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND26_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND26_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND26(value)                (MCAN_NDAT1_ND26_Msk & (_UINT32_(value) << MCAN_NDAT1_ND26_Pos)) /* Assigment of value for ND26 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND27_Pos                   _UINT32_(27)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND27_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND27_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND27(value)                (MCAN_NDAT1_ND27_Msk & (_UINT32_(value) << MCAN_NDAT1_ND27_Pos)) /* Assigment of value for ND27 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND28_Pos                   _UINT32_(28)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND28_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND28_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND28(value)                (MCAN_NDAT1_ND28_Msk & (_UINT32_(value) << MCAN_NDAT1_ND28_Pos)) /* Assigment of value for ND28 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND29_Pos                   _UINT32_(29)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND29_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND29_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND29(value)                (MCAN_NDAT1_ND29_Msk & (_UINT32_(value) << MCAN_NDAT1_ND29_Pos)) /* Assigment of value for ND29 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND30_Pos                   _UINT32_(30)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND30_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND30_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND30(value)                (MCAN_NDAT1_ND30_Msk & (_UINT32_(value) << MCAN_NDAT1_ND30_Pos)) /* Assigment of value for ND30 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_ND31_Pos                   _UINT32_(31)                                         /* (MCAN_NDAT1) New Data Position */
#define MCAN_NDAT1_ND31_Msk                   (_UINT32_(0x1) << MCAN_NDAT1_ND31_Pos)               /* (MCAN_NDAT1) New Data Mask */
#define MCAN_NDAT1_ND31(value)                (MCAN_NDAT1_ND31_Msk & (_UINT32_(value) << MCAN_NDAT1_ND31_Pos)) /* Assigment of value for ND31 in the MCAN_NDAT1 register */
#define MCAN_NDAT1_Msk                        _UINT32_(0xFFFFFFFF)                                 /* (MCAN_NDAT1) Register Mask  */

#define MCAN_NDAT1_ND_Pos                     _UINT32_(0)                                          /* (MCAN_NDAT1 Position) New Data */
#define MCAN_NDAT1_ND_Msk                     (_UINT32_(0xFFFFFFFF) << MCAN_NDAT1_ND_Pos)          /* (MCAN_NDAT1 Mask) ND */
#define MCAN_NDAT1_ND(value)                  (MCAN_NDAT1_ND_Msk & (_UINT32_(value) << MCAN_NDAT1_ND_Pos)) 

/* -------- MCAN_NDAT2 : (MCAN Offset: 0x9C) (R/W 32) New Data 2 Register -------- */
#define MCAN_NDAT2_ND32_Pos                   _UINT32_(0)                                          /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND32_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND32_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND32(value)                (MCAN_NDAT2_ND32_Msk & (_UINT32_(value) << MCAN_NDAT2_ND32_Pos)) /* Assigment of value for ND32 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND33_Pos                   _UINT32_(1)                                          /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND33_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND33_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND33(value)                (MCAN_NDAT2_ND33_Msk & (_UINT32_(value) << MCAN_NDAT2_ND33_Pos)) /* Assigment of value for ND33 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND34_Pos                   _UINT32_(2)                                          /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND34_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND34_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND34(value)                (MCAN_NDAT2_ND34_Msk & (_UINT32_(value) << MCAN_NDAT2_ND34_Pos)) /* Assigment of value for ND34 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND35_Pos                   _UINT32_(3)                                          /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND35_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND35_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND35(value)                (MCAN_NDAT2_ND35_Msk & (_UINT32_(value) << MCAN_NDAT2_ND35_Pos)) /* Assigment of value for ND35 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND36_Pos                   _UINT32_(4)                                          /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND36_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND36_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND36(value)                (MCAN_NDAT2_ND36_Msk & (_UINT32_(value) << MCAN_NDAT2_ND36_Pos)) /* Assigment of value for ND36 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND37_Pos                   _UINT32_(5)                                          /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND37_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND37_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND37(value)                (MCAN_NDAT2_ND37_Msk & (_UINT32_(value) << MCAN_NDAT2_ND37_Pos)) /* Assigment of value for ND37 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND38_Pos                   _UINT32_(6)                                          /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND38_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND38_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND38(value)                (MCAN_NDAT2_ND38_Msk & (_UINT32_(value) << MCAN_NDAT2_ND38_Pos)) /* Assigment of value for ND38 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND39_Pos                   _UINT32_(7)                                          /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND39_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND39_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND39(value)                (MCAN_NDAT2_ND39_Msk & (_UINT32_(value) << MCAN_NDAT2_ND39_Pos)) /* Assigment of value for ND39 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND40_Pos                   _UINT32_(8)                                          /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND40_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND40_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND40(value)                (MCAN_NDAT2_ND40_Msk & (_UINT32_(value) << MCAN_NDAT2_ND40_Pos)) /* Assigment of value for ND40 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND41_Pos                   _UINT32_(9)                                          /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND41_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND41_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND41(value)                (MCAN_NDAT2_ND41_Msk & (_UINT32_(value) << MCAN_NDAT2_ND41_Pos)) /* Assigment of value for ND41 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND42_Pos                   _UINT32_(10)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND42_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND42_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND42(value)                (MCAN_NDAT2_ND42_Msk & (_UINT32_(value) << MCAN_NDAT2_ND42_Pos)) /* Assigment of value for ND42 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND43_Pos                   _UINT32_(11)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND43_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND43_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND43(value)                (MCAN_NDAT2_ND43_Msk & (_UINT32_(value) << MCAN_NDAT2_ND43_Pos)) /* Assigment of value for ND43 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND44_Pos                   _UINT32_(12)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND44_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND44_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND44(value)                (MCAN_NDAT2_ND44_Msk & (_UINT32_(value) << MCAN_NDAT2_ND44_Pos)) /* Assigment of value for ND44 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND45_Pos                   _UINT32_(13)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND45_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND45_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND45(value)                (MCAN_NDAT2_ND45_Msk & (_UINT32_(value) << MCAN_NDAT2_ND45_Pos)) /* Assigment of value for ND45 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND46_Pos                   _UINT32_(14)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND46_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND46_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND46(value)                (MCAN_NDAT2_ND46_Msk & (_UINT32_(value) << MCAN_NDAT2_ND46_Pos)) /* Assigment of value for ND46 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND47_Pos                   _UINT32_(15)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND47_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND47_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND47(value)                (MCAN_NDAT2_ND47_Msk & (_UINT32_(value) << MCAN_NDAT2_ND47_Pos)) /* Assigment of value for ND47 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND48_Pos                   _UINT32_(16)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND48_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND48_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND48(value)                (MCAN_NDAT2_ND48_Msk & (_UINT32_(value) << MCAN_NDAT2_ND48_Pos)) /* Assigment of value for ND48 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND49_Pos                   _UINT32_(17)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND49_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND49_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND49(value)                (MCAN_NDAT2_ND49_Msk & (_UINT32_(value) << MCAN_NDAT2_ND49_Pos)) /* Assigment of value for ND49 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND50_Pos                   _UINT32_(18)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND50_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND50_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND50(value)                (MCAN_NDAT2_ND50_Msk & (_UINT32_(value) << MCAN_NDAT2_ND50_Pos)) /* Assigment of value for ND50 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND51_Pos                   _UINT32_(19)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND51_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND51_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND51(value)                (MCAN_NDAT2_ND51_Msk & (_UINT32_(value) << MCAN_NDAT2_ND51_Pos)) /* Assigment of value for ND51 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND52_Pos                   _UINT32_(20)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND52_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND52_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND52(value)                (MCAN_NDAT2_ND52_Msk & (_UINT32_(value) << MCAN_NDAT2_ND52_Pos)) /* Assigment of value for ND52 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND53_Pos                   _UINT32_(21)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND53_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND53_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND53(value)                (MCAN_NDAT2_ND53_Msk & (_UINT32_(value) << MCAN_NDAT2_ND53_Pos)) /* Assigment of value for ND53 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND54_Pos                   _UINT32_(22)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND54_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND54_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND54(value)                (MCAN_NDAT2_ND54_Msk & (_UINT32_(value) << MCAN_NDAT2_ND54_Pos)) /* Assigment of value for ND54 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND55_Pos                   _UINT32_(23)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND55_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND55_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND55(value)                (MCAN_NDAT2_ND55_Msk & (_UINT32_(value) << MCAN_NDAT2_ND55_Pos)) /* Assigment of value for ND55 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND56_Pos                   _UINT32_(24)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND56_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND56_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND56(value)                (MCAN_NDAT2_ND56_Msk & (_UINT32_(value) << MCAN_NDAT2_ND56_Pos)) /* Assigment of value for ND56 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND57_Pos                   _UINT32_(25)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND57_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND57_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND57(value)                (MCAN_NDAT2_ND57_Msk & (_UINT32_(value) << MCAN_NDAT2_ND57_Pos)) /* Assigment of value for ND57 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND58_Pos                   _UINT32_(26)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND58_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND58_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND58(value)                (MCAN_NDAT2_ND58_Msk & (_UINT32_(value) << MCAN_NDAT2_ND58_Pos)) /* Assigment of value for ND58 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND59_Pos                   _UINT32_(27)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND59_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND59_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND59(value)                (MCAN_NDAT2_ND59_Msk & (_UINT32_(value) << MCAN_NDAT2_ND59_Pos)) /* Assigment of value for ND59 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND60_Pos                   _UINT32_(28)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND60_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND60_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND60(value)                (MCAN_NDAT2_ND60_Msk & (_UINT32_(value) << MCAN_NDAT2_ND60_Pos)) /* Assigment of value for ND60 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND61_Pos                   _UINT32_(29)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND61_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND61_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND61(value)                (MCAN_NDAT2_ND61_Msk & (_UINT32_(value) << MCAN_NDAT2_ND61_Pos)) /* Assigment of value for ND61 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND62_Pos                   _UINT32_(30)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND62_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND62_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND62(value)                (MCAN_NDAT2_ND62_Msk & (_UINT32_(value) << MCAN_NDAT2_ND62_Pos)) /* Assigment of value for ND62 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_ND63_Pos                   _UINT32_(31)                                         /* (MCAN_NDAT2) New Data Position */
#define MCAN_NDAT2_ND63_Msk                   (_UINT32_(0x1) << MCAN_NDAT2_ND63_Pos)               /* (MCAN_NDAT2) New Data Mask */
#define MCAN_NDAT2_ND63(value)                (MCAN_NDAT2_ND63_Msk & (_UINT32_(value) << MCAN_NDAT2_ND63_Pos)) /* Assigment of value for ND63 in the MCAN_NDAT2 register */
#define MCAN_NDAT2_Msk                        _UINT32_(0xFFFFFFFF)                                 /* (MCAN_NDAT2) Register Mask  */

#define MCAN_NDAT2_ND_Pos                     _UINT32_(0)                                          /* (MCAN_NDAT2 Position) New Data */
#define MCAN_NDAT2_ND_Msk                     (_UINT32_(0xFFFFFFFF) << MCAN_NDAT2_ND_Pos)          /* (MCAN_NDAT2 Mask) ND */
#define MCAN_NDAT2_ND(value)                  (MCAN_NDAT2_ND_Msk & (_UINT32_(value) << MCAN_NDAT2_ND_Pos)) 

/* -------- MCAN_RXF0C : (MCAN Offset: 0xA0) (R/W 32) Receive FIFO 0 Configuration Register -------- */
#define MCAN_RXF0C_F0SA_Pos                   _UINT32_(2)                                          /* (MCAN_RXF0C) Receive FIFO 0 Start Address Position */
#define MCAN_RXF0C_F0SA_Msk                   (_UINT32_(0x3FFF) << MCAN_RXF0C_F0SA_Pos)            /* (MCAN_RXF0C) Receive FIFO 0 Start Address Mask */
#define MCAN_RXF0C_F0SA(value)                (MCAN_RXF0C_F0SA_Msk & (_UINT32_(value) << MCAN_RXF0C_F0SA_Pos)) /* Assigment of value for F0SA in the MCAN_RXF0C register */
#define MCAN_RXF0C_F0S_Pos                    _UINT32_(16)                                         /* (MCAN_RXF0C) Receive FIFO 0 Start Address Position */
#define MCAN_RXF0C_F0S_Msk                    (_UINT32_(0x7F) << MCAN_RXF0C_F0S_Pos)               /* (MCAN_RXF0C) Receive FIFO 0 Start Address Mask */
#define MCAN_RXF0C_F0S(value)                 (MCAN_RXF0C_F0S_Msk & (_UINT32_(value) << MCAN_RXF0C_F0S_Pos)) /* Assigment of value for F0S in the MCAN_RXF0C register */
#define MCAN_RXF0C_F0WM_Pos                   _UINT32_(24)                                         /* (MCAN_RXF0C) Receive FIFO 0 Watermark Position */
#define MCAN_RXF0C_F0WM_Msk                   (_UINT32_(0x7F) << MCAN_RXF0C_F0WM_Pos)              /* (MCAN_RXF0C) Receive FIFO 0 Watermark Mask */
#define MCAN_RXF0C_F0WM(value)                (MCAN_RXF0C_F0WM_Msk & (_UINT32_(value) << MCAN_RXF0C_F0WM_Pos)) /* Assigment of value for F0WM in the MCAN_RXF0C register */
#define MCAN_RXF0C_F0OM_Pos                   _UINT32_(31)                                         /* (MCAN_RXF0C) FIFO 0 Operation Mode Position */
#define MCAN_RXF0C_F0OM_Msk                   (_UINT32_(0x1) << MCAN_RXF0C_F0OM_Pos)               /* (MCAN_RXF0C) FIFO 0 Operation Mode Mask */
#define MCAN_RXF0C_F0OM(value)                (MCAN_RXF0C_F0OM_Msk & (_UINT32_(value) << MCAN_RXF0C_F0OM_Pos)) /* Assigment of value for F0OM in the MCAN_RXF0C register */
#define MCAN_RXF0C_Msk                        _UINT32_(0xFF7FFFFC)                                 /* (MCAN_RXF0C) Register Mask  */


/* -------- MCAN_RXF0S : (MCAN Offset: 0xA4) ( R/ 32) Receive FIFO 0 Status Register -------- */
#define MCAN_RXF0S_F0FL_Pos                   _UINT32_(0)                                          /* (MCAN_RXF0S) Receive FIFO 0 Fill Level Position */
#define MCAN_RXF0S_F0FL_Msk                   (_UINT32_(0x7F) << MCAN_RXF0S_F0FL_Pos)              /* (MCAN_RXF0S) Receive FIFO 0 Fill Level Mask */
#define MCAN_RXF0S_F0FL(value)                (MCAN_RXF0S_F0FL_Msk & (_UINT32_(value) << MCAN_RXF0S_F0FL_Pos)) /* Assigment of value for F0FL in the MCAN_RXF0S register */
#define MCAN_RXF0S_F0GI_Pos                   _UINT32_(8)                                          /* (MCAN_RXF0S) Receive FIFO 0 Get Index Position */
#define MCAN_RXF0S_F0GI_Msk                   (_UINT32_(0x3F) << MCAN_RXF0S_F0GI_Pos)              /* (MCAN_RXF0S) Receive FIFO 0 Get Index Mask */
#define MCAN_RXF0S_F0GI(value)                (MCAN_RXF0S_F0GI_Msk & (_UINT32_(value) << MCAN_RXF0S_F0GI_Pos)) /* Assigment of value for F0GI in the MCAN_RXF0S register */
#define MCAN_RXF0S_F0PI_Pos                   _UINT32_(16)                                         /* (MCAN_RXF0S) Receive FIFO 0 Put Index Position */
#define MCAN_RXF0S_F0PI_Msk                   (_UINT32_(0x3F) << MCAN_RXF0S_F0PI_Pos)              /* (MCAN_RXF0S) Receive FIFO 0 Put Index Mask */
#define MCAN_RXF0S_F0PI(value)                (MCAN_RXF0S_F0PI_Msk & (_UINT32_(value) << MCAN_RXF0S_F0PI_Pos)) /* Assigment of value for F0PI in the MCAN_RXF0S register */
#define MCAN_RXF0S_F0F_Pos                    _UINT32_(24)                                         /* (MCAN_RXF0S) Receive FIFO 0 Fill Level Position */
#define MCAN_RXF0S_F0F_Msk                    (_UINT32_(0x1) << MCAN_RXF0S_F0F_Pos)                /* (MCAN_RXF0S) Receive FIFO 0 Fill Level Mask */
#define MCAN_RXF0S_F0F(value)                 (MCAN_RXF0S_F0F_Msk & (_UINT32_(value) << MCAN_RXF0S_F0F_Pos)) /* Assigment of value for F0F in the MCAN_RXF0S register */
#define MCAN_RXF0S_RF0L_Pos                   _UINT32_(25)                                         /* (MCAN_RXF0S) Receive FIFO 0 Message Lost Position */
#define MCAN_RXF0S_RF0L_Msk                   (_UINT32_(0x1) << MCAN_RXF0S_RF0L_Pos)               /* (MCAN_RXF0S) Receive FIFO 0 Message Lost Mask */
#define MCAN_RXF0S_RF0L(value)                (MCAN_RXF0S_RF0L_Msk & (_UINT32_(value) << MCAN_RXF0S_RF0L_Pos)) /* Assigment of value for RF0L in the MCAN_RXF0S register */
#define MCAN_RXF0S_Msk                        _UINT32_(0x033F3F7F)                                 /* (MCAN_RXF0S) Register Mask  */


/* -------- MCAN_RXF0A : (MCAN Offset: 0xA8) (R/W 32) Receive FIFO 0 Acknowledge Register -------- */
#define MCAN_RXF0A_F0AI_Pos                   _UINT32_(0)                                          /* (MCAN_RXF0A) Receive FIFO 0 Acknowledge Index Position */
#define MCAN_RXF0A_F0AI_Msk                   (_UINT32_(0x3F) << MCAN_RXF0A_F0AI_Pos)              /* (MCAN_RXF0A) Receive FIFO 0 Acknowledge Index Mask */
#define MCAN_RXF0A_F0AI(value)                (MCAN_RXF0A_F0AI_Msk & (_UINT32_(value) << MCAN_RXF0A_F0AI_Pos)) /* Assigment of value for F0AI in the MCAN_RXF0A register */
#define MCAN_RXF0A_Msk                        _UINT32_(0x0000003F)                                 /* (MCAN_RXF0A) Register Mask  */


/* -------- MCAN_RXBC : (MCAN Offset: 0xAC) (R/W 32) Receive Rx Buffer Configuration Register -------- */
#define MCAN_RXBC_RBSA_Pos                    _UINT32_(2)                                          /* (MCAN_RXBC) Receive Buffer Start Address Position */
#define MCAN_RXBC_RBSA_Msk                    (_UINT32_(0x3FFF) << MCAN_RXBC_RBSA_Pos)             /* (MCAN_RXBC) Receive Buffer Start Address Mask */
#define MCAN_RXBC_RBSA(value)                 (MCAN_RXBC_RBSA_Msk & (_UINT32_(value) << MCAN_RXBC_RBSA_Pos)) /* Assigment of value for RBSA in the MCAN_RXBC register */
#define MCAN_RXBC_Msk                         _UINT32_(0x0000FFFC)                                 /* (MCAN_RXBC) Register Mask  */


/* -------- MCAN_RXF1C : (MCAN Offset: 0xB0) (R/W 32) Receive FIFO 1 Configuration Register -------- */
#define MCAN_RXF1C_F1SA_Pos                   _UINT32_(2)                                          /* (MCAN_RXF1C) Receive FIFO 1 Start Address Position */
#define MCAN_RXF1C_F1SA_Msk                   (_UINT32_(0x3FFF) << MCAN_RXF1C_F1SA_Pos)            /* (MCAN_RXF1C) Receive FIFO 1 Start Address Mask */
#define MCAN_RXF1C_F1SA(value)                (MCAN_RXF1C_F1SA_Msk & (_UINT32_(value) << MCAN_RXF1C_F1SA_Pos)) /* Assigment of value for F1SA in the MCAN_RXF1C register */
#define MCAN_RXF1C_F1S_Pos                    _UINT32_(16)                                         /* (MCAN_RXF1C) Receive FIFO 1 Start Address Position */
#define MCAN_RXF1C_F1S_Msk                    (_UINT32_(0x7F) << MCAN_RXF1C_F1S_Pos)               /* (MCAN_RXF1C) Receive FIFO 1 Start Address Mask */
#define MCAN_RXF1C_F1S(value)                 (MCAN_RXF1C_F1S_Msk & (_UINT32_(value) << MCAN_RXF1C_F1S_Pos)) /* Assigment of value for F1S in the MCAN_RXF1C register */
#define MCAN_RXF1C_F1WM_Pos                   _UINT32_(24)                                         /* (MCAN_RXF1C) Receive FIFO 1 Watermark Position */
#define MCAN_RXF1C_F1WM_Msk                   (_UINT32_(0x7F) << MCAN_RXF1C_F1WM_Pos)              /* (MCAN_RXF1C) Receive FIFO 1 Watermark Mask */
#define MCAN_RXF1C_F1WM(value)                (MCAN_RXF1C_F1WM_Msk & (_UINT32_(value) << MCAN_RXF1C_F1WM_Pos)) /* Assigment of value for F1WM in the MCAN_RXF1C register */
#define MCAN_RXF1C_F1OM_Pos                   _UINT32_(31)                                         /* (MCAN_RXF1C) FIFO 1 Operation Mode Position */
#define MCAN_RXF1C_F1OM_Msk                   (_UINT32_(0x1) << MCAN_RXF1C_F1OM_Pos)               /* (MCAN_RXF1C) FIFO 1 Operation Mode Mask */
#define MCAN_RXF1C_F1OM(value)                (MCAN_RXF1C_F1OM_Msk & (_UINT32_(value) << MCAN_RXF1C_F1OM_Pos)) /* Assigment of value for F1OM in the MCAN_RXF1C register */
#define MCAN_RXF1C_Msk                        _UINT32_(0xFF7FFFFC)                                 /* (MCAN_RXF1C) Register Mask  */


/* -------- MCAN_RXF1S : (MCAN Offset: 0xB4) ( R/ 32) Receive FIFO 1 Status Register -------- */
#define MCAN_RXF1S_F1FL_Pos                   _UINT32_(0)                                          /* (MCAN_RXF1S) Receive FIFO 1 Fill Level Position */
#define MCAN_RXF1S_F1FL_Msk                   (_UINT32_(0x7F) << MCAN_RXF1S_F1FL_Pos)              /* (MCAN_RXF1S) Receive FIFO 1 Fill Level Mask */
#define MCAN_RXF1S_F1FL(value)                (MCAN_RXF1S_F1FL_Msk & (_UINT32_(value) << MCAN_RXF1S_F1FL_Pos)) /* Assigment of value for F1FL in the MCAN_RXF1S register */
#define MCAN_RXF1S_F1GI_Pos                   _UINT32_(8)                                          /* (MCAN_RXF1S) Receive FIFO 1 Get Index Position */
#define MCAN_RXF1S_F1GI_Msk                   (_UINT32_(0x3F) << MCAN_RXF1S_F1GI_Pos)              /* (MCAN_RXF1S) Receive FIFO 1 Get Index Mask */
#define MCAN_RXF1S_F1GI(value)                (MCAN_RXF1S_F1GI_Msk & (_UINT32_(value) << MCAN_RXF1S_F1GI_Pos)) /* Assigment of value for F1GI in the MCAN_RXF1S register */
#define MCAN_RXF1S_F1PI_Pos                   _UINT32_(16)                                         /* (MCAN_RXF1S) Receive FIFO 1 Put Index Position */
#define MCAN_RXF1S_F1PI_Msk                   (_UINT32_(0x3F) << MCAN_RXF1S_F1PI_Pos)              /* (MCAN_RXF1S) Receive FIFO 1 Put Index Mask */
#define MCAN_RXF1S_F1PI(value)                (MCAN_RXF1S_F1PI_Msk & (_UINT32_(value) << MCAN_RXF1S_F1PI_Pos)) /* Assigment of value for F1PI in the MCAN_RXF1S register */
#define MCAN_RXF1S_F1F_Pos                    _UINT32_(24)                                         /* (MCAN_RXF1S) Receive FIFO 1 Fill Level Position */
#define MCAN_RXF1S_F1F_Msk                    (_UINT32_(0x1) << MCAN_RXF1S_F1F_Pos)                /* (MCAN_RXF1S) Receive FIFO 1 Fill Level Mask */
#define MCAN_RXF1S_F1F(value)                 (MCAN_RXF1S_F1F_Msk & (_UINT32_(value) << MCAN_RXF1S_F1F_Pos)) /* Assigment of value for F1F in the MCAN_RXF1S register */
#define MCAN_RXF1S_RF1L_Pos                   _UINT32_(25)                                         /* (MCAN_RXF1S) Receive FIFO 1 Message Lost Position */
#define MCAN_RXF1S_RF1L_Msk                   (_UINT32_(0x1) << MCAN_RXF1S_RF1L_Pos)               /* (MCAN_RXF1S) Receive FIFO 1 Message Lost Mask */
#define MCAN_RXF1S_RF1L(value)                (MCAN_RXF1S_RF1L_Msk & (_UINT32_(value) << MCAN_RXF1S_RF1L_Pos)) /* Assigment of value for RF1L in the MCAN_RXF1S register */
#define MCAN_RXF1S_DMS_Pos                    _UINT32_(30)                                         /* (MCAN_RXF1S) Debug Message Status Position */
#define MCAN_RXF1S_DMS_Msk                    (_UINT32_(0x3) << MCAN_RXF1S_DMS_Pos)                /* (MCAN_RXF1S) Debug Message Status Mask */
#define MCAN_RXF1S_DMS(value)                 (MCAN_RXF1S_DMS_Msk & (_UINT32_(value) << MCAN_RXF1S_DMS_Pos)) /* Assigment of value for DMS in the MCAN_RXF1S register */
#define   MCAN_RXF1S_DMS_IDLE_Val             _UINT32_(0x0)                                        /* (MCAN_RXF1S) Idle state, wait for reception of debug messages, DMA request is cleared.  */
#define   MCAN_RXF1S_DMS_MSG_A_Val            _UINT32_(0x1)                                        /* (MCAN_RXF1S) Debug message A received.  */
#define   MCAN_RXF1S_DMS_MSG_AB_Val           _UINT32_(0x2)                                        /* (MCAN_RXF1S) Debug messages A, B received.  */
#define   MCAN_RXF1S_DMS_MSG_ABC_Val          _UINT32_(0x3)                                        /* (MCAN_RXF1S) Debug messages A, B, C received, DMA request is set.  */
#define MCAN_RXF1S_DMS_IDLE                   (MCAN_RXF1S_DMS_IDLE_Val << MCAN_RXF1S_DMS_Pos)      /* (MCAN_RXF1S) Idle state, wait for reception of debug messages, DMA request is cleared. Position  */
#define MCAN_RXF1S_DMS_MSG_A                  (MCAN_RXF1S_DMS_MSG_A_Val << MCAN_RXF1S_DMS_Pos)     /* (MCAN_RXF1S) Debug message A received. Position  */
#define MCAN_RXF1S_DMS_MSG_AB                 (MCAN_RXF1S_DMS_MSG_AB_Val << MCAN_RXF1S_DMS_Pos)    /* (MCAN_RXF1S) Debug messages A, B received. Position  */
#define MCAN_RXF1S_DMS_MSG_ABC                (MCAN_RXF1S_DMS_MSG_ABC_Val << MCAN_RXF1S_DMS_Pos)   /* (MCAN_RXF1S) Debug messages A, B, C received, DMA request is set. Position  */
#define MCAN_RXF1S_Msk                        _UINT32_(0xC33F3F7F)                                 /* (MCAN_RXF1S) Register Mask  */


/* -------- MCAN_RXF1A : (MCAN Offset: 0xB8) (R/W 32) Receive FIFO 1 Acknowledge Register -------- */
#define MCAN_RXF1A_F1AI_Pos                   _UINT32_(0)                                          /* (MCAN_RXF1A) Receive FIFO 1 Acknowledge Index Position */
#define MCAN_RXF1A_F1AI_Msk                   (_UINT32_(0x3F) << MCAN_RXF1A_F1AI_Pos)              /* (MCAN_RXF1A) Receive FIFO 1 Acknowledge Index Mask */
#define MCAN_RXF1A_F1AI(value)                (MCAN_RXF1A_F1AI_Msk & (_UINT32_(value) << MCAN_RXF1A_F1AI_Pos)) /* Assigment of value for F1AI in the MCAN_RXF1A register */
#define MCAN_RXF1A_Msk                        _UINT32_(0x0000003F)                                 /* (MCAN_RXF1A) Register Mask  */


/* -------- MCAN_RXESC : (MCAN Offset: 0xBC) (R/W 32) Receive Buffer / FIFO Element Size Configuration Register -------- */
#define MCAN_RXESC_F0DS_Pos                   _UINT32_(0)                                          /* (MCAN_RXESC) Receive FIFO 0 Data Field Size Position */
#define MCAN_RXESC_F0DS_Msk                   (_UINT32_(0x7) << MCAN_RXESC_F0DS_Pos)               /* (MCAN_RXESC) Receive FIFO 0 Data Field Size Mask */
#define MCAN_RXESC_F0DS(value)                (MCAN_RXESC_F0DS_Msk & (_UINT32_(value) << MCAN_RXESC_F0DS_Pos)) /* Assigment of value for F0DS in the MCAN_RXESC register */
#define   MCAN_RXESC_F0DS_8_BYTE_Val          _UINT32_(0x0)                                        /* (MCAN_RXESC) 8-byte data field  */
#define   MCAN_RXESC_F0DS_12_BYTE_Val         _UINT32_(0x1)                                        /* (MCAN_RXESC) 12-byte data field  */
#define   MCAN_RXESC_F0DS_16_BYTE_Val         _UINT32_(0x2)                                        /* (MCAN_RXESC) 16-byte data field  */
#define   MCAN_RXESC_F0DS_20_BYTE_Val         _UINT32_(0x3)                                        /* (MCAN_RXESC) 20-byte data field  */
#define   MCAN_RXESC_F0DS_24_BYTE_Val         _UINT32_(0x4)                                        /* (MCAN_RXESC) 24-byte data field  */
#define   MCAN_RXESC_F0DS_32_BYTE_Val         _UINT32_(0x5)                                        /* (MCAN_RXESC) 32-byte data field  */
#define   MCAN_RXESC_F0DS_48_BYTE_Val         _UINT32_(0x6)                                        /* (MCAN_RXESC) 48-byte data field  */
#define   MCAN_RXESC_F0DS_64_BYTE_Val         _UINT32_(0x7)                                        /* (MCAN_RXESC) 64-byte data field  */
#define MCAN_RXESC_F0DS_8_BYTE                (MCAN_RXESC_F0DS_8_BYTE_Val << MCAN_RXESC_F0DS_Pos)  /* (MCAN_RXESC) 8-byte data field Position  */
#define MCAN_RXESC_F0DS_12_BYTE               (MCAN_RXESC_F0DS_12_BYTE_Val << MCAN_RXESC_F0DS_Pos) /* (MCAN_RXESC) 12-byte data field Position  */
#define MCAN_RXESC_F0DS_16_BYTE               (MCAN_RXESC_F0DS_16_BYTE_Val << MCAN_RXESC_F0DS_Pos) /* (MCAN_RXESC) 16-byte data field Position  */
#define MCAN_RXESC_F0DS_20_BYTE               (MCAN_RXESC_F0DS_20_BYTE_Val << MCAN_RXESC_F0DS_Pos) /* (MCAN_RXESC) 20-byte data field Position  */
#define MCAN_RXESC_F0DS_24_BYTE               (MCAN_RXESC_F0DS_24_BYTE_Val << MCAN_RXESC_F0DS_Pos) /* (MCAN_RXESC) 24-byte data field Position  */
#define MCAN_RXESC_F0DS_32_BYTE               (MCAN_RXESC_F0DS_32_BYTE_Val << MCAN_RXESC_F0DS_Pos) /* (MCAN_RXESC) 32-byte data field Position  */
#define MCAN_RXESC_F0DS_48_BYTE               (MCAN_RXESC_F0DS_48_BYTE_Val << MCAN_RXESC_F0DS_Pos) /* (MCAN_RXESC) 48-byte data field Position  */
#define MCAN_RXESC_F0DS_64_BYTE               (MCAN_RXESC_F0DS_64_BYTE_Val << MCAN_RXESC_F0DS_Pos) /* (MCAN_RXESC) 64-byte data field Position  */
#define MCAN_RXESC_F1DS_Pos                   _UINT32_(4)                                          /* (MCAN_RXESC) Receive FIFO 1 Data Field Size Position */
#define MCAN_RXESC_F1DS_Msk                   (_UINT32_(0x7) << MCAN_RXESC_F1DS_Pos)               /* (MCAN_RXESC) Receive FIFO 1 Data Field Size Mask */
#define MCAN_RXESC_F1DS(value)                (MCAN_RXESC_F1DS_Msk & (_UINT32_(value) << MCAN_RXESC_F1DS_Pos)) /* Assigment of value for F1DS in the MCAN_RXESC register */
#define   MCAN_RXESC_F1DS_8_BYTE_Val          _UINT32_(0x0)                                        /* (MCAN_RXESC) 8-byte data field  */
#define   MCAN_RXESC_F1DS_12_BYTE_Val         _UINT32_(0x1)                                        /* (MCAN_RXESC) 12-byte data field  */
#define   MCAN_RXESC_F1DS_16_BYTE_Val         _UINT32_(0x2)                                        /* (MCAN_RXESC) 16-byte data field  */
#define   MCAN_RXESC_F1DS_20_BYTE_Val         _UINT32_(0x3)                                        /* (MCAN_RXESC) 20-byte data field  */
#define   MCAN_RXESC_F1DS_24_BYTE_Val         _UINT32_(0x4)                                        /* (MCAN_RXESC) 24-byte data field  */
#define   MCAN_RXESC_F1DS_32_BYTE_Val         _UINT32_(0x5)                                        /* (MCAN_RXESC) 32-byte data field  */
#define   MCAN_RXESC_F1DS_48_BYTE_Val         _UINT32_(0x6)                                        /* (MCAN_RXESC) 48-byte data field  */
#define   MCAN_RXESC_F1DS_64_BYTE_Val         _UINT32_(0x7)                                        /* (MCAN_RXESC) 64-byte data field  */
#define MCAN_RXESC_F1DS_8_BYTE                (MCAN_RXESC_F1DS_8_BYTE_Val << MCAN_RXESC_F1DS_Pos)  /* (MCAN_RXESC) 8-byte data field Position  */
#define MCAN_RXESC_F1DS_12_BYTE               (MCAN_RXESC_F1DS_12_BYTE_Val << MCAN_RXESC_F1DS_Pos) /* (MCAN_RXESC) 12-byte data field Position  */
#define MCAN_RXESC_F1DS_16_BYTE               (MCAN_RXESC_F1DS_16_BYTE_Val << MCAN_RXESC_F1DS_Pos) /* (MCAN_RXESC) 16-byte data field Position  */
#define MCAN_RXESC_F1DS_20_BYTE               (MCAN_RXESC_F1DS_20_BYTE_Val << MCAN_RXESC_F1DS_Pos) /* (MCAN_RXESC) 20-byte data field Position  */
#define MCAN_RXESC_F1DS_24_BYTE               (MCAN_RXESC_F1DS_24_BYTE_Val << MCAN_RXESC_F1DS_Pos) /* (MCAN_RXESC) 24-byte data field Position  */
#define MCAN_RXESC_F1DS_32_BYTE               (MCAN_RXESC_F1DS_32_BYTE_Val << MCAN_RXESC_F1DS_Pos) /* (MCAN_RXESC) 32-byte data field Position  */
#define MCAN_RXESC_F1DS_48_BYTE               (MCAN_RXESC_F1DS_48_BYTE_Val << MCAN_RXESC_F1DS_Pos) /* (MCAN_RXESC) 48-byte data field Position  */
#define MCAN_RXESC_F1DS_64_BYTE               (MCAN_RXESC_F1DS_64_BYTE_Val << MCAN_RXESC_F1DS_Pos) /* (MCAN_RXESC) 64-byte data field Position  */
#define MCAN_RXESC_RBDS_Pos                   _UINT32_(8)                                          /* (MCAN_RXESC) Receive Buffer Data Field Size Position */
#define MCAN_RXESC_RBDS_Msk                   (_UINT32_(0x7) << MCAN_RXESC_RBDS_Pos)               /* (MCAN_RXESC) Receive Buffer Data Field Size Mask */
#define MCAN_RXESC_RBDS(value)                (MCAN_RXESC_RBDS_Msk & (_UINT32_(value) << MCAN_RXESC_RBDS_Pos)) /* Assigment of value for RBDS in the MCAN_RXESC register */
#define   MCAN_RXESC_RBDS_8_BYTE_Val          _UINT32_(0x0)                                        /* (MCAN_RXESC) 8-byte data field  */
#define   MCAN_RXESC_RBDS_12_BYTE_Val         _UINT32_(0x1)                                        /* (MCAN_RXESC) 12-byte data field  */
#define   MCAN_RXESC_RBDS_16_BYTE_Val         _UINT32_(0x2)                                        /* (MCAN_RXESC) 16-byte data field  */
#define   MCAN_RXESC_RBDS_20_BYTE_Val         _UINT32_(0x3)                                        /* (MCAN_RXESC) 20-byte data field  */
#define   MCAN_RXESC_RBDS_24_BYTE_Val         _UINT32_(0x4)                                        /* (MCAN_RXESC) 24-byte data field  */
#define   MCAN_RXESC_RBDS_32_BYTE_Val         _UINT32_(0x5)                                        /* (MCAN_RXESC) 32-byte data field  */
#define   MCAN_RXESC_RBDS_48_BYTE_Val         _UINT32_(0x6)                                        /* (MCAN_RXESC) 48-byte data field  */
#define   MCAN_RXESC_RBDS_64_BYTE_Val         _UINT32_(0x7)                                        /* (MCAN_RXESC) 64-byte data field  */
#define MCAN_RXESC_RBDS_8_BYTE                (MCAN_RXESC_RBDS_8_BYTE_Val << MCAN_RXESC_RBDS_Pos)  /* (MCAN_RXESC) 8-byte data field Position  */
#define MCAN_RXESC_RBDS_12_BYTE               (MCAN_RXESC_RBDS_12_BYTE_Val << MCAN_RXESC_RBDS_Pos) /* (MCAN_RXESC) 12-byte data field Position  */
#define MCAN_RXESC_RBDS_16_BYTE               (MCAN_RXESC_RBDS_16_BYTE_Val << MCAN_RXESC_RBDS_Pos) /* (MCAN_RXESC) 16-byte data field Position  */
#define MCAN_RXESC_RBDS_20_BYTE               (MCAN_RXESC_RBDS_20_BYTE_Val << MCAN_RXESC_RBDS_Pos) /* (MCAN_RXESC) 20-byte data field Position  */
#define MCAN_RXESC_RBDS_24_BYTE               (MCAN_RXESC_RBDS_24_BYTE_Val << MCAN_RXESC_RBDS_Pos) /* (MCAN_RXESC) 24-byte data field Position  */
#define MCAN_RXESC_RBDS_32_BYTE               (MCAN_RXESC_RBDS_32_BYTE_Val << MCAN_RXESC_RBDS_Pos) /* (MCAN_RXESC) 32-byte data field Position  */
#define MCAN_RXESC_RBDS_48_BYTE               (MCAN_RXESC_RBDS_48_BYTE_Val << MCAN_RXESC_RBDS_Pos) /* (MCAN_RXESC) 48-byte data field Position  */
#define MCAN_RXESC_RBDS_64_BYTE               (MCAN_RXESC_RBDS_64_BYTE_Val << MCAN_RXESC_RBDS_Pos) /* (MCAN_RXESC) 64-byte data field Position  */
#define MCAN_RXESC_Msk                        _UINT32_(0x00000777)                                 /* (MCAN_RXESC) Register Mask  */


/* -------- MCAN_TXBC : (MCAN Offset: 0xC0) (R/W 32) Transmit Buffer Configuration Register -------- */
#define MCAN_TXBC_TBSA_Pos                    _UINT32_(2)                                          /* (MCAN_TXBC) Tx Buffers Start Address Position */
#define MCAN_TXBC_TBSA_Msk                    (_UINT32_(0x3FFF) << MCAN_TXBC_TBSA_Pos)             /* (MCAN_TXBC) Tx Buffers Start Address Mask */
#define MCAN_TXBC_TBSA(value)                 (MCAN_TXBC_TBSA_Msk & (_UINT32_(value) << MCAN_TXBC_TBSA_Pos)) /* Assigment of value for TBSA in the MCAN_TXBC register */
#define MCAN_TXBC_NDTB_Pos                    _UINT32_(16)                                         /* (MCAN_TXBC) Number of Dedicated Transmit Buffers Position */
#define MCAN_TXBC_NDTB_Msk                    (_UINT32_(0x3F) << MCAN_TXBC_NDTB_Pos)               /* (MCAN_TXBC) Number of Dedicated Transmit Buffers Mask */
#define MCAN_TXBC_NDTB(value)                 (MCAN_TXBC_NDTB_Msk & (_UINT32_(value) << MCAN_TXBC_NDTB_Pos)) /* Assigment of value for NDTB in the MCAN_TXBC register */
#define MCAN_TXBC_TFQS_Pos                    _UINT32_(24)                                         /* (MCAN_TXBC) Transmit FIFO/Queue Size Position */
#define MCAN_TXBC_TFQS_Msk                    (_UINT32_(0x3F) << MCAN_TXBC_TFQS_Pos)               /* (MCAN_TXBC) Transmit FIFO/Queue Size Mask */
#define MCAN_TXBC_TFQS(value)                 (MCAN_TXBC_TFQS_Msk & (_UINT32_(value) << MCAN_TXBC_TFQS_Pos)) /* Assigment of value for TFQS in the MCAN_TXBC register */
#define MCAN_TXBC_TFQM_Pos                    _UINT32_(30)                                         /* (MCAN_TXBC) Tx FIFO/Queue Mode Position */
#define MCAN_TXBC_TFQM_Msk                    (_UINT32_(0x1) << MCAN_TXBC_TFQM_Pos)                /* (MCAN_TXBC) Tx FIFO/Queue Mode Mask */
#define MCAN_TXBC_TFQM(value)                 (MCAN_TXBC_TFQM_Msk & (_UINT32_(value) << MCAN_TXBC_TFQM_Pos)) /* Assigment of value for TFQM in the MCAN_TXBC register */
#define MCAN_TXBC_Msk                         _UINT32_(0x7F3FFFFC)                                 /* (MCAN_TXBC) Register Mask  */


/* -------- MCAN_TXFQS : (MCAN Offset: 0xC4) ( R/ 32) Transmit FIFO/Queue Status Register -------- */
#define MCAN_TXFQS_TFFL_Pos                   _UINT32_(0)                                          /* (MCAN_TXFQS) Tx FIFO Free Level Position */
#define MCAN_TXFQS_TFFL_Msk                   (_UINT32_(0x3F) << MCAN_TXFQS_TFFL_Pos)              /* (MCAN_TXFQS) Tx FIFO Free Level Mask */
#define MCAN_TXFQS_TFFL(value)                (MCAN_TXFQS_TFFL_Msk & (_UINT32_(value) << MCAN_TXFQS_TFFL_Pos)) /* Assigment of value for TFFL in the MCAN_TXFQS register */
#define MCAN_TXFQS_TFGI_Pos                   _UINT32_(8)                                          /* (MCAN_TXFQS) Tx FIFO Get Index Position */
#define MCAN_TXFQS_TFGI_Msk                   (_UINT32_(0x1F) << MCAN_TXFQS_TFGI_Pos)              /* (MCAN_TXFQS) Tx FIFO Get Index Mask */
#define MCAN_TXFQS_TFGI(value)                (MCAN_TXFQS_TFGI_Msk & (_UINT32_(value) << MCAN_TXFQS_TFGI_Pos)) /* Assigment of value for TFGI in the MCAN_TXFQS register */
#define MCAN_TXFQS_TFQPI_Pos                  _UINT32_(16)                                         /* (MCAN_TXFQS) Tx FIFO/Queue Put Index Position */
#define MCAN_TXFQS_TFQPI_Msk                  (_UINT32_(0x1F) << MCAN_TXFQS_TFQPI_Pos)             /* (MCAN_TXFQS) Tx FIFO/Queue Put Index Mask */
#define MCAN_TXFQS_TFQPI(value)               (MCAN_TXFQS_TFQPI_Msk & (_UINT32_(value) << MCAN_TXFQS_TFQPI_Pos)) /* Assigment of value for TFQPI in the MCAN_TXFQS register */
#define MCAN_TXFQS_TFQF_Pos                   _UINT32_(21)                                         /* (MCAN_TXFQS) Tx FIFO/Queue Full Position */
#define MCAN_TXFQS_TFQF_Msk                   (_UINT32_(0x1) << MCAN_TXFQS_TFQF_Pos)               /* (MCAN_TXFQS) Tx FIFO/Queue Full Mask */
#define MCAN_TXFQS_TFQF(value)                (MCAN_TXFQS_TFQF_Msk & (_UINT32_(value) << MCAN_TXFQS_TFQF_Pos)) /* Assigment of value for TFQF in the MCAN_TXFQS register */
#define MCAN_TXFQS_Msk                        _UINT32_(0x003F1F3F)                                 /* (MCAN_TXFQS) Register Mask  */


/* -------- MCAN_TXESC : (MCAN Offset: 0xC8) (R/W 32) Transmit Buffer Element Size Configuration Register -------- */
#define MCAN_TXESC_TBDS_Pos                   _UINT32_(0)                                          /* (MCAN_TXESC) Tx Buffer Data Field Size Position */
#define MCAN_TXESC_TBDS_Msk                   (_UINT32_(0x7) << MCAN_TXESC_TBDS_Pos)               /* (MCAN_TXESC) Tx Buffer Data Field Size Mask */
#define MCAN_TXESC_TBDS(value)                (MCAN_TXESC_TBDS_Msk & (_UINT32_(value) << MCAN_TXESC_TBDS_Pos)) /* Assigment of value for TBDS in the MCAN_TXESC register */
#define   MCAN_TXESC_TBDS_8_BYTE_Val          _UINT32_(0x0)                                        /* (MCAN_TXESC) 8-byte data field  */
#define   MCAN_TXESC_TBDS_12_BYTE_Val         _UINT32_(0x1)                                        /* (MCAN_TXESC) 12-byte data field  */
#define   MCAN_TXESC_TBDS_16_BYTE_Val         _UINT32_(0x2)                                        /* (MCAN_TXESC) 16-byte data field  */
#define   MCAN_TXESC_TBDS_20_BYTE_Val         _UINT32_(0x3)                                        /* (MCAN_TXESC) 20-byte data field  */
#define   MCAN_TXESC_TBDS_24_BYTE_Val         _UINT32_(0x4)                                        /* (MCAN_TXESC) 24-byte data field  */
#define   MCAN_TXESC_TBDS_32_BYTE_Val         _UINT32_(0x5)                                        /* (MCAN_TXESC) 32-byte data field  */
#define   MCAN_TXESC_TBDS_48_BYTE_Val         _UINT32_(0x6)                                        /* (MCAN_TXESC) 48- byte data field  */
#define   MCAN_TXESC_TBDS_64_BYTE_Val         _UINT32_(0x7)                                        /* (MCAN_TXESC) 64-byte data field  */
#define MCAN_TXESC_TBDS_8_BYTE                (MCAN_TXESC_TBDS_8_BYTE_Val << MCAN_TXESC_TBDS_Pos)  /* (MCAN_TXESC) 8-byte data field Position  */
#define MCAN_TXESC_TBDS_12_BYTE               (MCAN_TXESC_TBDS_12_BYTE_Val << MCAN_TXESC_TBDS_Pos) /* (MCAN_TXESC) 12-byte data field Position  */
#define MCAN_TXESC_TBDS_16_BYTE               (MCAN_TXESC_TBDS_16_BYTE_Val << MCAN_TXESC_TBDS_Pos) /* (MCAN_TXESC) 16-byte data field Position  */
#define MCAN_TXESC_TBDS_20_BYTE               (MCAN_TXESC_TBDS_20_BYTE_Val << MCAN_TXESC_TBDS_Pos) /* (MCAN_TXESC) 20-byte data field Position  */
#define MCAN_TXESC_TBDS_24_BYTE               (MCAN_TXESC_TBDS_24_BYTE_Val << MCAN_TXESC_TBDS_Pos) /* (MCAN_TXESC) 24-byte data field Position  */
#define MCAN_TXESC_TBDS_32_BYTE               (MCAN_TXESC_TBDS_32_BYTE_Val << MCAN_TXESC_TBDS_Pos) /* (MCAN_TXESC) 32-byte data field Position  */
#define MCAN_TXESC_TBDS_48_BYTE               (MCAN_TXESC_TBDS_48_BYTE_Val << MCAN_TXESC_TBDS_Pos) /* (MCAN_TXESC) 48- byte data field Position  */
#define MCAN_TXESC_TBDS_64_BYTE               (MCAN_TXESC_TBDS_64_BYTE_Val << MCAN_TXESC_TBDS_Pos) /* (MCAN_TXESC) 64-byte data field Position  */
#define MCAN_TXESC_Msk                        _UINT32_(0x00000007)                                 /* (MCAN_TXESC) Register Mask  */


/* -------- MCAN_TXBRP : (MCAN Offset: 0xCC) ( R/ 32) Transmit Buffer Request Pending Register -------- */
#define MCAN_TXBRP_TRP0_Pos                   _UINT32_(0)                                          /* (MCAN_TXBRP) Transmission Request Pending for Buffer 0 Position */
#define MCAN_TXBRP_TRP0_Msk                   (_UINT32_(0x1) << MCAN_TXBRP_TRP0_Pos)               /* (MCAN_TXBRP) Transmission Request Pending for Buffer 0 Mask */
#define MCAN_TXBRP_TRP0(value)                (MCAN_TXBRP_TRP0_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP0_Pos)) /* Assigment of value for TRP0 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP1_Pos                   _UINT32_(1)                                          /* (MCAN_TXBRP) Transmission Request Pending for Buffer 1 Position */
#define MCAN_TXBRP_TRP1_Msk                   (_UINT32_(0x1) << MCAN_TXBRP_TRP1_Pos)               /* (MCAN_TXBRP) Transmission Request Pending for Buffer 1 Mask */
#define MCAN_TXBRP_TRP1(value)                (MCAN_TXBRP_TRP1_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP1_Pos)) /* Assigment of value for TRP1 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP2_Pos                   _UINT32_(2)                                          /* (MCAN_TXBRP) Transmission Request Pending for Buffer 2 Position */
#define MCAN_TXBRP_TRP2_Msk                   (_UINT32_(0x1) << MCAN_TXBRP_TRP2_Pos)               /* (MCAN_TXBRP) Transmission Request Pending for Buffer 2 Mask */
#define MCAN_TXBRP_TRP2(value)                (MCAN_TXBRP_TRP2_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP2_Pos)) /* Assigment of value for TRP2 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP3_Pos                   _UINT32_(3)                                          /* (MCAN_TXBRP) Transmission Request Pending for Buffer 3 Position */
#define MCAN_TXBRP_TRP3_Msk                   (_UINT32_(0x1) << MCAN_TXBRP_TRP3_Pos)               /* (MCAN_TXBRP) Transmission Request Pending for Buffer 3 Mask */
#define MCAN_TXBRP_TRP3(value)                (MCAN_TXBRP_TRP3_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP3_Pos)) /* Assigment of value for TRP3 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP4_Pos                   _UINT32_(4)                                          /* (MCAN_TXBRP) Transmission Request Pending for Buffer 4 Position */
#define MCAN_TXBRP_TRP4_Msk                   (_UINT32_(0x1) << MCAN_TXBRP_TRP4_Pos)               /* (MCAN_TXBRP) Transmission Request Pending for Buffer 4 Mask */
#define MCAN_TXBRP_TRP4(value)                (MCAN_TXBRP_TRP4_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP4_Pos)) /* Assigment of value for TRP4 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP5_Pos                   _UINT32_(5)                                          /* (MCAN_TXBRP) Transmission Request Pending for Buffer 5 Position */
#define MCAN_TXBRP_TRP5_Msk                   (_UINT32_(0x1) << MCAN_TXBRP_TRP5_Pos)               /* (MCAN_TXBRP) Transmission Request Pending for Buffer 5 Mask */
#define MCAN_TXBRP_TRP5(value)                (MCAN_TXBRP_TRP5_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP5_Pos)) /* Assigment of value for TRP5 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP6_Pos                   _UINT32_(6)                                          /* (MCAN_TXBRP) Transmission Request Pending for Buffer 6 Position */
#define MCAN_TXBRP_TRP6_Msk                   (_UINT32_(0x1) << MCAN_TXBRP_TRP6_Pos)               /* (MCAN_TXBRP) Transmission Request Pending for Buffer 6 Mask */
#define MCAN_TXBRP_TRP6(value)                (MCAN_TXBRP_TRP6_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP6_Pos)) /* Assigment of value for TRP6 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP7_Pos                   _UINT32_(7)                                          /* (MCAN_TXBRP) Transmission Request Pending for Buffer 7 Position */
#define MCAN_TXBRP_TRP7_Msk                   (_UINT32_(0x1) << MCAN_TXBRP_TRP7_Pos)               /* (MCAN_TXBRP) Transmission Request Pending for Buffer 7 Mask */
#define MCAN_TXBRP_TRP7(value)                (MCAN_TXBRP_TRP7_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP7_Pos)) /* Assigment of value for TRP7 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP8_Pos                   _UINT32_(8)                                          /* (MCAN_TXBRP) Transmission Request Pending for Buffer 8 Position */
#define MCAN_TXBRP_TRP8_Msk                   (_UINT32_(0x1) << MCAN_TXBRP_TRP8_Pos)               /* (MCAN_TXBRP) Transmission Request Pending for Buffer 8 Mask */
#define MCAN_TXBRP_TRP8(value)                (MCAN_TXBRP_TRP8_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP8_Pos)) /* Assigment of value for TRP8 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP9_Pos                   _UINT32_(9)                                          /* (MCAN_TXBRP) Transmission Request Pending for Buffer 9 Position */
#define MCAN_TXBRP_TRP9_Msk                   (_UINT32_(0x1) << MCAN_TXBRP_TRP9_Pos)               /* (MCAN_TXBRP) Transmission Request Pending for Buffer 9 Mask */
#define MCAN_TXBRP_TRP9(value)                (MCAN_TXBRP_TRP9_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP9_Pos)) /* Assigment of value for TRP9 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP10_Pos                  _UINT32_(10)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 10 Position */
#define MCAN_TXBRP_TRP10_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP10_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 10 Mask */
#define MCAN_TXBRP_TRP10(value)               (MCAN_TXBRP_TRP10_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP10_Pos)) /* Assigment of value for TRP10 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP11_Pos                  _UINT32_(11)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 11 Position */
#define MCAN_TXBRP_TRP11_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP11_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 11 Mask */
#define MCAN_TXBRP_TRP11(value)               (MCAN_TXBRP_TRP11_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP11_Pos)) /* Assigment of value for TRP11 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP12_Pos                  _UINT32_(12)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 12 Position */
#define MCAN_TXBRP_TRP12_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP12_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 12 Mask */
#define MCAN_TXBRP_TRP12(value)               (MCAN_TXBRP_TRP12_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP12_Pos)) /* Assigment of value for TRP12 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP13_Pos                  _UINT32_(13)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 13 Position */
#define MCAN_TXBRP_TRP13_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP13_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 13 Mask */
#define MCAN_TXBRP_TRP13(value)               (MCAN_TXBRP_TRP13_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP13_Pos)) /* Assigment of value for TRP13 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP14_Pos                  _UINT32_(14)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 14 Position */
#define MCAN_TXBRP_TRP14_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP14_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 14 Mask */
#define MCAN_TXBRP_TRP14(value)               (MCAN_TXBRP_TRP14_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP14_Pos)) /* Assigment of value for TRP14 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP15_Pos                  _UINT32_(15)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 15 Position */
#define MCAN_TXBRP_TRP15_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP15_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 15 Mask */
#define MCAN_TXBRP_TRP15(value)               (MCAN_TXBRP_TRP15_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP15_Pos)) /* Assigment of value for TRP15 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP16_Pos                  _UINT32_(16)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 16 Position */
#define MCAN_TXBRP_TRP16_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP16_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 16 Mask */
#define MCAN_TXBRP_TRP16(value)               (MCAN_TXBRP_TRP16_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP16_Pos)) /* Assigment of value for TRP16 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP17_Pos                  _UINT32_(17)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 17 Position */
#define MCAN_TXBRP_TRP17_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP17_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 17 Mask */
#define MCAN_TXBRP_TRP17(value)               (MCAN_TXBRP_TRP17_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP17_Pos)) /* Assigment of value for TRP17 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP18_Pos                  _UINT32_(18)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 18 Position */
#define MCAN_TXBRP_TRP18_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP18_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 18 Mask */
#define MCAN_TXBRP_TRP18(value)               (MCAN_TXBRP_TRP18_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP18_Pos)) /* Assigment of value for TRP18 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP19_Pos                  _UINT32_(19)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 19 Position */
#define MCAN_TXBRP_TRP19_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP19_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 19 Mask */
#define MCAN_TXBRP_TRP19(value)               (MCAN_TXBRP_TRP19_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP19_Pos)) /* Assigment of value for TRP19 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP20_Pos                  _UINT32_(20)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 20 Position */
#define MCAN_TXBRP_TRP20_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP20_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 20 Mask */
#define MCAN_TXBRP_TRP20(value)               (MCAN_TXBRP_TRP20_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP20_Pos)) /* Assigment of value for TRP20 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP21_Pos                  _UINT32_(21)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 21 Position */
#define MCAN_TXBRP_TRP21_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP21_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 21 Mask */
#define MCAN_TXBRP_TRP21(value)               (MCAN_TXBRP_TRP21_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP21_Pos)) /* Assigment of value for TRP21 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP22_Pos                  _UINT32_(22)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 22 Position */
#define MCAN_TXBRP_TRP22_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP22_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 22 Mask */
#define MCAN_TXBRP_TRP22(value)               (MCAN_TXBRP_TRP22_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP22_Pos)) /* Assigment of value for TRP22 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP23_Pos                  _UINT32_(23)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 23 Position */
#define MCAN_TXBRP_TRP23_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP23_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 23 Mask */
#define MCAN_TXBRP_TRP23(value)               (MCAN_TXBRP_TRP23_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP23_Pos)) /* Assigment of value for TRP23 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP24_Pos                  _UINT32_(24)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 24 Position */
#define MCAN_TXBRP_TRP24_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP24_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 24 Mask */
#define MCAN_TXBRP_TRP24(value)               (MCAN_TXBRP_TRP24_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP24_Pos)) /* Assigment of value for TRP24 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP25_Pos                  _UINT32_(25)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 25 Position */
#define MCAN_TXBRP_TRP25_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP25_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 25 Mask */
#define MCAN_TXBRP_TRP25(value)               (MCAN_TXBRP_TRP25_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP25_Pos)) /* Assigment of value for TRP25 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP26_Pos                  _UINT32_(26)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 26 Position */
#define MCAN_TXBRP_TRP26_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP26_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 26 Mask */
#define MCAN_TXBRP_TRP26(value)               (MCAN_TXBRP_TRP26_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP26_Pos)) /* Assigment of value for TRP26 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP27_Pos                  _UINT32_(27)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 27 Position */
#define MCAN_TXBRP_TRP27_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP27_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 27 Mask */
#define MCAN_TXBRP_TRP27(value)               (MCAN_TXBRP_TRP27_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP27_Pos)) /* Assigment of value for TRP27 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP28_Pos                  _UINT32_(28)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 28 Position */
#define MCAN_TXBRP_TRP28_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP28_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 28 Mask */
#define MCAN_TXBRP_TRP28(value)               (MCAN_TXBRP_TRP28_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP28_Pos)) /* Assigment of value for TRP28 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP29_Pos                  _UINT32_(29)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 29 Position */
#define MCAN_TXBRP_TRP29_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP29_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 29 Mask */
#define MCAN_TXBRP_TRP29(value)               (MCAN_TXBRP_TRP29_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP29_Pos)) /* Assigment of value for TRP29 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP30_Pos                  _UINT32_(30)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 30 Position */
#define MCAN_TXBRP_TRP30_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP30_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 30 Mask */
#define MCAN_TXBRP_TRP30(value)               (MCAN_TXBRP_TRP30_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP30_Pos)) /* Assigment of value for TRP30 in the MCAN_TXBRP register */
#define MCAN_TXBRP_TRP31_Pos                  _UINT32_(31)                                         /* (MCAN_TXBRP) Transmission Request Pending for Buffer 31 Position */
#define MCAN_TXBRP_TRP31_Msk                  (_UINT32_(0x1) << MCAN_TXBRP_TRP31_Pos)              /* (MCAN_TXBRP) Transmission Request Pending for Buffer 31 Mask */
#define MCAN_TXBRP_TRP31(value)               (MCAN_TXBRP_TRP31_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP31_Pos)) /* Assigment of value for TRP31 in the MCAN_TXBRP register */
#define MCAN_TXBRP_Msk                        _UINT32_(0xFFFFFFFF)                                 /* (MCAN_TXBRP) Register Mask  */

#define MCAN_TXBRP_TRP_Pos                    _UINT32_(0)                                          /* (MCAN_TXBRP Position) Transmission Request Pending for Buffer 3x */
#define MCAN_TXBRP_TRP_Msk                    (_UINT32_(0xFFFFFFFF) << MCAN_TXBRP_TRP_Pos)         /* (MCAN_TXBRP Mask) TRP */
#define MCAN_TXBRP_TRP(value)                 (MCAN_TXBRP_TRP_Msk & (_UINT32_(value) << MCAN_TXBRP_TRP_Pos)) 

/* -------- MCAN_TXBAR : (MCAN Offset: 0xD0) (R/W 32) Transmit Buffer Add Request Register -------- */
#define MCAN_TXBAR_AR0_Pos                    _UINT32_(0)                                          /* (MCAN_TXBAR) Add Request for Transmit Buffer 0 Position */
#define MCAN_TXBAR_AR0_Msk                    (_UINT32_(0x1) << MCAN_TXBAR_AR0_Pos)                /* (MCAN_TXBAR) Add Request for Transmit Buffer 0 Mask */
#define MCAN_TXBAR_AR0(value)                 (MCAN_TXBAR_AR0_Msk & (_UINT32_(value) << MCAN_TXBAR_AR0_Pos)) /* Assigment of value for AR0 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR1_Pos                    _UINT32_(1)                                          /* (MCAN_TXBAR) Add Request for Transmit Buffer 1 Position */
#define MCAN_TXBAR_AR1_Msk                    (_UINT32_(0x1) << MCAN_TXBAR_AR1_Pos)                /* (MCAN_TXBAR) Add Request for Transmit Buffer 1 Mask */
#define MCAN_TXBAR_AR1(value)                 (MCAN_TXBAR_AR1_Msk & (_UINT32_(value) << MCAN_TXBAR_AR1_Pos)) /* Assigment of value for AR1 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR2_Pos                    _UINT32_(2)                                          /* (MCAN_TXBAR) Add Request for Transmit Buffer 2 Position */
#define MCAN_TXBAR_AR2_Msk                    (_UINT32_(0x1) << MCAN_TXBAR_AR2_Pos)                /* (MCAN_TXBAR) Add Request for Transmit Buffer 2 Mask */
#define MCAN_TXBAR_AR2(value)                 (MCAN_TXBAR_AR2_Msk & (_UINT32_(value) << MCAN_TXBAR_AR2_Pos)) /* Assigment of value for AR2 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR3_Pos                    _UINT32_(3)                                          /* (MCAN_TXBAR) Add Request for Transmit Buffer 3 Position */
#define MCAN_TXBAR_AR3_Msk                    (_UINT32_(0x1) << MCAN_TXBAR_AR3_Pos)                /* (MCAN_TXBAR) Add Request for Transmit Buffer 3 Mask */
#define MCAN_TXBAR_AR3(value)                 (MCAN_TXBAR_AR3_Msk & (_UINT32_(value) << MCAN_TXBAR_AR3_Pos)) /* Assigment of value for AR3 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR4_Pos                    _UINT32_(4)                                          /* (MCAN_TXBAR) Add Request for Transmit Buffer 4 Position */
#define MCAN_TXBAR_AR4_Msk                    (_UINT32_(0x1) << MCAN_TXBAR_AR4_Pos)                /* (MCAN_TXBAR) Add Request for Transmit Buffer 4 Mask */
#define MCAN_TXBAR_AR4(value)                 (MCAN_TXBAR_AR4_Msk & (_UINT32_(value) << MCAN_TXBAR_AR4_Pos)) /* Assigment of value for AR4 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR5_Pos                    _UINT32_(5)                                          /* (MCAN_TXBAR) Add Request for Transmit Buffer 5 Position */
#define MCAN_TXBAR_AR5_Msk                    (_UINT32_(0x1) << MCAN_TXBAR_AR5_Pos)                /* (MCAN_TXBAR) Add Request for Transmit Buffer 5 Mask */
#define MCAN_TXBAR_AR5(value)                 (MCAN_TXBAR_AR5_Msk & (_UINT32_(value) << MCAN_TXBAR_AR5_Pos)) /* Assigment of value for AR5 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR6_Pos                    _UINT32_(6)                                          /* (MCAN_TXBAR) Add Request for Transmit Buffer 6 Position */
#define MCAN_TXBAR_AR6_Msk                    (_UINT32_(0x1) << MCAN_TXBAR_AR6_Pos)                /* (MCAN_TXBAR) Add Request for Transmit Buffer 6 Mask */
#define MCAN_TXBAR_AR6(value)                 (MCAN_TXBAR_AR6_Msk & (_UINT32_(value) << MCAN_TXBAR_AR6_Pos)) /* Assigment of value for AR6 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR7_Pos                    _UINT32_(7)                                          /* (MCAN_TXBAR) Add Request for Transmit Buffer 7 Position */
#define MCAN_TXBAR_AR7_Msk                    (_UINT32_(0x1) << MCAN_TXBAR_AR7_Pos)                /* (MCAN_TXBAR) Add Request for Transmit Buffer 7 Mask */
#define MCAN_TXBAR_AR7(value)                 (MCAN_TXBAR_AR7_Msk & (_UINT32_(value) << MCAN_TXBAR_AR7_Pos)) /* Assigment of value for AR7 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR8_Pos                    _UINT32_(8)                                          /* (MCAN_TXBAR) Add Request for Transmit Buffer 8 Position */
#define MCAN_TXBAR_AR8_Msk                    (_UINT32_(0x1) << MCAN_TXBAR_AR8_Pos)                /* (MCAN_TXBAR) Add Request for Transmit Buffer 8 Mask */
#define MCAN_TXBAR_AR8(value)                 (MCAN_TXBAR_AR8_Msk & (_UINT32_(value) << MCAN_TXBAR_AR8_Pos)) /* Assigment of value for AR8 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR9_Pos                    _UINT32_(9)                                          /* (MCAN_TXBAR) Add Request for Transmit Buffer 9 Position */
#define MCAN_TXBAR_AR9_Msk                    (_UINT32_(0x1) << MCAN_TXBAR_AR9_Pos)                /* (MCAN_TXBAR) Add Request for Transmit Buffer 9 Mask */
#define MCAN_TXBAR_AR9(value)                 (MCAN_TXBAR_AR9_Msk & (_UINT32_(value) << MCAN_TXBAR_AR9_Pos)) /* Assigment of value for AR9 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR10_Pos                   _UINT32_(10)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 10 Position */
#define MCAN_TXBAR_AR10_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR10_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 10 Mask */
#define MCAN_TXBAR_AR10(value)                (MCAN_TXBAR_AR10_Msk & (_UINT32_(value) << MCAN_TXBAR_AR10_Pos)) /* Assigment of value for AR10 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR11_Pos                   _UINT32_(11)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 11 Position */
#define MCAN_TXBAR_AR11_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR11_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 11 Mask */
#define MCAN_TXBAR_AR11(value)                (MCAN_TXBAR_AR11_Msk & (_UINT32_(value) << MCAN_TXBAR_AR11_Pos)) /* Assigment of value for AR11 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR12_Pos                   _UINT32_(12)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 12 Position */
#define MCAN_TXBAR_AR12_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR12_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 12 Mask */
#define MCAN_TXBAR_AR12(value)                (MCAN_TXBAR_AR12_Msk & (_UINT32_(value) << MCAN_TXBAR_AR12_Pos)) /* Assigment of value for AR12 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR13_Pos                   _UINT32_(13)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 13 Position */
#define MCAN_TXBAR_AR13_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR13_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 13 Mask */
#define MCAN_TXBAR_AR13(value)                (MCAN_TXBAR_AR13_Msk & (_UINT32_(value) << MCAN_TXBAR_AR13_Pos)) /* Assigment of value for AR13 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR14_Pos                   _UINT32_(14)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 14 Position */
#define MCAN_TXBAR_AR14_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR14_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 14 Mask */
#define MCAN_TXBAR_AR14(value)                (MCAN_TXBAR_AR14_Msk & (_UINT32_(value) << MCAN_TXBAR_AR14_Pos)) /* Assigment of value for AR14 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR15_Pos                   _UINT32_(15)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 15 Position */
#define MCAN_TXBAR_AR15_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR15_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 15 Mask */
#define MCAN_TXBAR_AR15(value)                (MCAN_TXBAR_AR15_Msk & (_UINT32_(value) << MCAN_TXBAR_AR15_Pos)) /* Assigment of value for AR15 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR16_Pos                   _UINT32_(16)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 16 Position */
#define MCAN_TXBAR_AR16_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR16_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 16 Mask */
#define MCAN_TXBAR_AR16(value)                (MCAN_TXBAR_AR16_Msk & (_UINT32_(value) << MCAN_TXBAR_AR16_Pos)) /* Assigment of value for AR16 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR17_Pos                   _UINT32_(17)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 17 Position */
#define MCAN_TXBAR_AR17_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR17_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 17 Mask */
#define MCAN_TXBAR_AR17(value)                (MCAN_TXBAR_AR17_Msk & (_UINT32_(value) << MCAN_TXBAR_AR17_Pos)) /* Assigment of value for AR17 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR18_Pos                   _UINT32_(18)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 18 Position */
#define MCAN_TXBAR_AR18_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR18_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 18 Mask */
#define MCAN_TXBAR_AR18(value)                (MCAN_TXBAR_AR18_Msk & (_UINT32_(value) << MCAN_TXBAR_AR18_Pos)) /* Assigment of value for AR18 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR19_Pos                   _UINT32_(19)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 19 Position */
#define MCAN_TXBAR_AR19_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR19_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 19 Mask */
#define MCAN_TXBAR_AR19(value)                (MCAN_TXBAR_AR19_Msk & (_UINT32_(value) << MCAN_TXBAR_AR19_Pos)) /* Assigment of value for AR19 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR20_Pos                   _UINT32_(20)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 20 Position */
#define MCAN_TXBAR_AR20_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR20_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 20 Mask */
#define MCAN_TXBAR_AR20(value)                (MCAN_TXBAR_AR20_Msk & (_UINT32_(value) << MCAN_TXBAR_AR20_Pos)) /* Assigment of value for AR20 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR21_Pos                   _UINT32_(21)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 21 Position */
#define MCAN_TXBAR_AR21_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR21_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 21 Mask */
#define MCAN_TXBAR_AR21(value)                (MCAN_TXBAR_AR21_Msk & (_UINT32_(value) << MCAN_TXBAR_AR21_Pos)) /* Assigment of value for AR21 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR22_Pos                   _UINT32_(22)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 22 Position */
#define MCAN_TXBAR_AR22_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR22_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 22 Mask */
#define MCAN_TXBAR_AR22(value)                (MCAN_TXBAR_AR22_Msk & (_UINT32_(value) << MCAN_TXBAR_AR22_Pos)) /* Assigment of value for AR22 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR23_Pos                   _UINT32_(23)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 23 Position */
#define MCAN_TXBAR_AR23_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR23_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 23 Mask */
#define MCAN_TXBAR_AR23(value)                (MCAN_TXBAR_AR23_Msk & (_UINT32_(value) << MCAN_TXBAR_AR23_Pos)) /* Assigment of value for AR23 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR24_Pos                   _UINT32_(24)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 24 Position */
#define MCAN_TXBAR_AR24_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR24_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 24 Mask */
#define MCAN_TXBAR_AR24(value)                (MCAN_TXBAR_AR24_Msk & (_UINT32_(value) << MCAN_TXBAR_AR24_Pos)) /* Assigment of value for AR24 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR25_Pos                   _UINT32_(25)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 25 Position */
#define MCAN_TXBAR_AR25_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR25_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 25 Mask */
#define MCAN_TXBAR_AR25(value)                (MCAN_TXBAR_AR25_Msk & (_UINT32_(value) << MCAN_TXBAR_AR25_Pos)) /* Assigment of value for AR25 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR26_Pos                   _UINT32_(26)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 26 Position */
#define MCAN_TXBAR_AR26_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR26_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 26 Mask */
#define MCAN_TXBAR_AR26(value)                (MCAN_TXBAR_AR26_Msk & (_UINT32_(value) << MCAN_TXBAR_AR26_Pos)) /* Assigment of value for AR26 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR27_Pos                   _UINT32_(27)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 27 Position */
#define MCAN_TXBAR_AR27_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR27_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 27 Mask */
#define MCAN_TXBAR_AR27(value)                (MCAN_TXBAR_AR27_Msk & (_UINT32_(value) << MCAN_TXBAR_AR27_Pos)) /* Assigment of value for AR27 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR28_Pos                   _UINT32_(28)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 28 Position */
#define MCAN_TXBAR_AR28_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR28_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 28 Mask */
#define MCAN_TXBAR_AR28(value)                (MCAN_TXBAR_AR28_Msk & (_UINT32_(value) << MCAN_TXBAR_AR28_Pos)) /* Assigment of value for AR28 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR29_Pos                   _UINT32_(29)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 29 Position */
#define MCAN_TXBAR_AR29_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR29_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 29 Mask */
#define MCAN_TXBAR_AR29(value)                (MCAN_TXBAR_AR29_Msk & (_UINT32_(value) << MCAN_TXBAR_AR29_Pos)) /* Assigment of value for AR29 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR30_Pos                   _UINT32_(30)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 30 Position */
#define MCAN_TXBAR_AR30_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR30_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 30 Mask */
#define MCAN_TXBAR_AR30(value)                (MCAN_TXBAR_AR30_Msk & (_UINT32_(value) << MCAN_TXBAR_AR30_Pos)) /* Assigment of value for AR30 in the MCAN_TXBAR register */
#define MCAN_TXBAR_AR31_Pos                   _UINT32_(31)                                         /* (MCAN_TXBAR) Add Request for Transmit Buffer 31 Position */
#define MCAN_TXBAR_AR31_Msk                   (_UINT32_(0x1) << MCAN_TXBAR_AR31_Pos)               /* (MCAN_TXBAR) Add Request for Transmit Buffer 31 Mask */
#define MCAN_TXBAR_AR31(value)                (MCAN_TXBAR_AR31_Msk & (_UINT32_(value) << MCAN_TXBAR_AR31_Pos)) /* Assigment of value for AR31 in the MCAN_TXBAR register */
#define MCAN_TXBAR_Msk                        _UINT32_(0xFFFFFFFF)                                 /* (MCAN_TXBAR) Register Mask  */

#define MCAN_TXBAR_AR_Pos                     _UINT32_(0)                                          /* (MCAN_TXBAR Position) Add Request for Transmit Buffer 3x */
#define MCAN_TXBAR_AR_Msk                     (_UINT32_(0xFFFFFFFF) << MCAN_TXBAR_AR_Pos)          /* (MCAN_TXBAR Mask) AR */
#define MCAN_TXBAR_AR(value)                  (MCAN_TXBAR_AR_Msk & (_UINT32_(value) << MCAN_TXBAR_AR_Pos)) 

/* -------- MCAN_TXBCR : (MCAN Offset: 0xD4) (R/W 32) Transmit Buffer Cancellation Request Register -------- */
#define MCAN_TXBCR_CR0_Pos                    _UINT32_(0)                                          /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 0 Position */
#define MCAN_TXBCR_CR0_Msk                    (_UINT32_(0x1) << MCAN_TXBCR_CR0_Pos)                /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 0 Mask */
#define MCAN_TXBCR_CR0(value)                 (MCAN_TXBCR_CR0_Msk & (_UINT32_(value) << MCAN_TXBCR_CR0_Pos)) /* Assigment of value for CR0 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR1_Pos                    _UINT32_(1)                                          /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 1 Position */
#define MCAN_TXBCR_CR1_Msk                    (_UINT32_(0x1) << MCAN_TXBCR_CR1_Pos)                /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 1 Mask */
#define MCAN_TXBCR_CR1(value)                 (MCAN_TXBCR_CR1_Msk & (_UINT32_(value) << MCAN_TXBCR_CR1_Pos)) /* Assigment of value for CR1 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR2_Pos                    _UINT32_(2)                                          /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 2 Position */
#define MCAN_TXBCR_CR2_Msk                    (_UINT32_(0x1) << MCAN_TXBCR_CR2_Pos)                /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 2 Mask */
#define MCAN_TXBCR_CR2(value)                 (MCAN_TXBCR_CR2_Msk & (_UINT32_(value) << MCAN_TXBCR_CR2_Pos)) /* Assigment of value for CR2 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR3_Pos                    _UINT32_(3)                                          /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 3 Position */
#define MCAN_TXBCR_CR3_Msk                    (_UINT32_(0x1) << MCAN_TXBCR_CR3_Pos)                /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 3 Mask */
#define MCAN_TXBCR_CR3(value)                 (MCAN_TXBCR_CR3_Msk & (_UINT32_(value) << MCAN_TXBCR_CR3_Pos)) /* Assigment of value for CR3 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR4_Pos                    _UINT32_(4)                                          /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 4 Position */
#define MCAN_TXBCR_CR4_Msk                    (_UINT32_(0x1) << MCAN_TXBCR_CR4_Pos)                /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 4 Mask */
#define MCAN_TXBCR_CR4(value)                 (MCAN_TXBCR_CR4_Msk & (_UINT32_(value) << MCAN_TXBCR_CR4_Pos)) /* Assigment of value for CR4 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR5_Pos                    _UINT32_(5)                                          /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 5 Position */
#define MCAN_TXBCR_CR5_Msk                    (_UINT32_(0x1) << MCAN_TXBCR_CR5_Pos)                /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 5 Mask */
#define MCAN_TXBCR_CR5(value)                 (MCAN_TXBCR_CR5_Msk & (_UINT32_(value) << MCAN_TXBCR_CR5_Pos)) /* Assigment of value for CR5 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR6_Pos                    _UINT32_(6)                                          /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 6 Position */
#define MCAN_TXBCR_CR6_Msk                    (_UINT32_(0x1) << MCAN_TXBCR_CR6_Pos)                /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 6 Mask */
#define MCAN_TXBCR_CR6(value)                 (MCAN_TXBCR_CR6_Msk & (_UINT32_(value) << MCAN_TXBCR_CR6_Pos)) /* Assigment of value for CR6 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR7_Pos                    _UINT32_(7)                                          /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 7 Position */
#define MCAN_TXBCR_CR7_Msk                    (_UINT32_(0x1) << MCAN_TXBCR_CR7_Pos)                /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 7 Mask */
#define MCAN_TXBCR_CR7(value)                 (MCAN_TXBCR_CR7_Msk & (_UINT32_(value) << MCAN_TXBCR_CR7_Pos)) /* Assigment of value for CR7 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR8_Pos                    _UINT32_(8)                                          /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 8 Position */
#define MCAN_TXBCR_CR8_Msk                    (_UINT32_(0x1) << MCAN_TXBCR_CR8_Pos)                /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 8 Mask */
#define MCAN_TXBCR_CR8(value)                 (MCAN_TXBCR_CR8_Msk & (_UINT32_(value) << MCAN_TXBCR_CR8_Pos)) /* Assigment of value for CR8 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR9_Pos                    _UINT32_(9)                                          /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 9 Position */
#define MCAN_TXBCR_CR9_Msk                    (_UINT32_(0x1) << MCAN_TXBCR_CR9_Pos)                /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 9 Mask */
#define MCAN_TXBCR_CR9(value)                 (MCAN_TXBCR_CR9_Msk & (_UINT32_(value) << MCAN_TXBCR_CR9_Pos)) /* Assigment of value for CR9 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR10_Pos                   _UINT32_(10)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 10 Position */
#define MCAN_TXBCR_CR10_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR10_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 10 Mask */
#define MCAN_TXBCR_CR10(value)                (MCAN_TXBCR_CR10_Msk & (_UINT32_(value) << MCAN_TXBCR_CR10_Pos)) /* Assigment of value for CR10 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR11_Pos                   _UINT32_(11)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 11 Position */
#define MCAN_TXBCR_CR11_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR11_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 11 Mask */
#define MCAN_TXBCR_CR11(value)                (MCAN_TXBCR_CR11_Msk & (_UINT32_(value) << MCAN_TXBCR_CR11_Pos)) /* Assigment of value for CR11 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR12_Pos                   _UINT32_(12)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 12 Position */
#define MCAN_TXBCR_CR12_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR12_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 12 Mask */
#define MCAN_TXBCR_CR12(value)                (MCAN_TXBCR_CR12_Msk & (_UINT32_(value) << MCAN_TXBCR_CR12_Pos)) /* Assigment of value for CR12 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR13_Pos                   _UINT32_(13)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 13 Position */
#define MCAN_TXBCR_CR13_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR13_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 13 Mask */
#define MCAN_TXBCR_CR13(value)                (MCAN_TXBCR_CR13_Msk & (_UINT32_(value) << MCAN_TXBCR_CR13_Pos)) /* Assigment of value for CR13 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR14_Pos                   _UINT32_(14)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 14 Position */
#define MCAN_TXBCR_CR14_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR14_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 14 Mask */
#define MCAN_TXBCR_CR14(value)                (MCAN_TXBCR_CR14_Msk & (_UINT32_(value) << MCAN_TXBCR_CR14_Pos)) /* Assigment of value for CR14 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR15_Pos                   _UINT32_(15)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 15 Position */
#define MCAN_TXBCR_CR15_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR15_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 15 Mask */
#define MCAN_TXBCR_CR15(value)                (MCAN_TXBCR_CR15_Msk & (_UINT32_(value) << MCAN_TXBCR_CR15_Pos)) /* Assigment of value for CR15 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR16_Pos                   _UINT32_(16)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 16 Position */
#define MCAN_TXBCR_CR16_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR16_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 16 Mask */
#define MCAN_TXBCR_CR16(value)                (MCAN_TXBCR_CR16_Msk & (_UINT32_(value) << MCAN_TXBCR_CR16_Pos)) /* Assigment of value for CR16 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR17_Pos                   _UINT32_(17)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 17 Position */
#define MCAN_TXBCR_CR17_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR17_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 17 Mask */
#define MCAN_TXBCR_CR17(value)                (MCAN_TXBCR_CR17_Msk & (_UINT32_(value) << MCAN_TXBCR_CR17_Pos)) /* Assigment of value for CR17 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR18_Pos                   _UINT32_(18)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 18 Position */
#define MCAN_TXBCR_CR18_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR18_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 18 Mask */
#define MCAN_TXBCR_CR18(value)                (MCAN_TXBCR_CR18_Msk & (_UINT32_(value) << MCAN_TXBCR_CR18_Pos)) /* Assigment of value for CR18 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR19_Pos                   _UINT32_(19)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 19 Position */
#define MCAN_TXBCR_CR19_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR19_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 19 Mask */
#define MCAN_TXBCR_CR19(value)                (MCAN_TXBCR_CR19_Msk & (_UINT32_(value) << MCAN_TXBCR_CR19_Pos)) /* Assigment of value for CR19 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR20_Pos                   _UINT32_(20)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 20 Position */
#define MCAN_TXBCR_CR20_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR20_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 20 Mask */
#define MCAN_TXBCR_CR20(value)                (MCAN_TXBCR_CR20_Msk & (_UINT32_(value) << MCAN_TXBCR_CR20_Pos)) /* Assigment of value for CR20 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR21_Pos                   _UINT32_(21)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 21 Position */
#define MCAN_TXBCR_CR21_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR21_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 21 Mask */
#define MCAN_TXBCR_CR21(value)                (MCAN_TXBCR_CR21_Msk & (_UINT32_(value) << MCAN_TXBCR_CR21_Pos)) /* Assigment of value for CR21 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR22_Pos                   _UINT32_(22)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 22 Position */
#define MCAN_TXBCR_CR22_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR22_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 22 Mask */
#define MCAN_TXBCR_CR22(value)                (MCAN_TXBCR_CR22_Msk & (_UINT32_(value) << MCAN_TXBCR_CR22_Pos)) /* Assigment of value for CR22 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR23_Pos                   _UINT32_(23)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 23 Position */
#define MCAN_TXBCR_CR23_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR23_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 23 Mask */
#define MCAN_TXBCR_CR23(value)                (MCAN_TXBCR_CR23_Msk & (_UINT32_(value) << MCAN_TXBCR_CR23_Pos)) /* Assigment of value for CR23 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR24_Pos                   _UINT32_(24)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 24 Position */
#define MCAN_TXBCR_CR24_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR24_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 24 Mask */
#define MCAN_TXBCR_CR24(value)                (MCAN_TXBCR_CR24_Msk & (_UINT32_(value) << MCAN_TXBCR_CR24_Pos)) /* Assigment of value for CR24 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR25_Pos                   _UINT32_(25)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 25 Position */
#define MCAN_TXBCR_CR25_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR25_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 25 Mask */
#define MCAN_TXBCR_CR25(value)                (MCAN_TXBCR_CR25_Msk & (_UINT32_(value) << MCAN_TXBCR_CR25_Pos)) /* Assigment of value for CR25 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR26_Pos                   _UINT32_(26)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 26 Position */
#define MCAN_TXBCR_CR26_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR26_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 26 Mask */
#define MCAN_TXBCR_CR26(value)                (MCAN_TXBCR_CR26_Msk & (_UINT32_(value) << MCAN_TXBCR_CR26_Pos)) /* Assigment of value for CR26 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR27_Pos                   _UINT32_(27)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 27 Position */
#define MCAN_TXBCR_CR27_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR27_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 27 Mask */
#define MCAN_TXBCR_CR27(value)                (MCAN_TXBCR_CR27_Msk & (_UINT32_(value) << MCAN_TXBCR_CR27_Pos)) /* Assigment of value for CR27 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR28_Pos                   _UINT32_(28)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 28 Position */
#define MCAN_TXBCR_CR28_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR28_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 28 Mask */
#define MCAN_TXBCR_CR28(value)                (MCAN_TXBCR_CR28_Msk & (_UINT32_(value) << MCAN_TXBCR_CR28_Pos)) /* Assigment of value for CR28 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR29_Pos                   _UINT32_(29)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 29 Position */
#define MCAN_TXBCR_CR29_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR29_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 29 Mask */
#define MCAN_TXBCR_CR29(value)                (MCAN_TXBCR_CR29_Msk & (_UINT32_(value) << MCAN_TXBCR_CR29_Pos)) /* Assigment of value for CR29 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR30_Pos                   _UINT32_(30)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 30 Position */
#define MCAN_TXBCR_CR30_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR30_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 30 Mask */
#define MCAN_TXBCR_CR30(value)                (MCAN_TXBCR_CR30_Msk & (_UINT32_(value) << MCAN_TXBCR_CR30_Pos)) /* Assigment of value for CR30 in the MCAN_TXBCR register */
#define MCAN_TXBCR_CR31_Pos                   _UINT32_(31)                                         /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 31 Position */
#define MCAN_TXBCR_CR31_Msk                   (_UINT32_(0x1) << MCAN_TXBCR_CR31_Pos)               /* (MCAN_TXBCR) Cancellation Request for Transmit Buffer 31 Mask */
#define MCAN_TXBCR_CR31(value)                (MCAN_TXBCR_CR31_Msk & (_UINT32_(value) << MCAN_TXBCR_CR31_Pos)) /* Assigment of value for CR31 in the MCAN_TXBCR register */
#define MCAN_TXBCR_Msk                        _UINT32_(0xFFFFFFFF)                                 /* (MCAN_TXBCR) Register Mask  */

#define MCAN_TXBCR_CR_Pos                     _UINT32_(0)                                          /* (MCAN_TXBCR Position) Cancellation Request for Transmit Buffer 3x */
#define MCAN_TXBCR_CR_Msk                     (_UINT32_(0xFFFFFFFF) << MCAN_TXBCR_CR_Pos)          /* (MCAN_TXBCR Mask) CR */
#define MCAN_TXBCR_CR(value)                  (MCAN_TXBCR_CR_Msk & (_UINT32_(value) << MCAN_TXBCR_CR_Pos)) 

/* -------- MCAN_TXBTO : (MCAN Offset: 0xD8) ( R/ 32) Transmit Buffer Transmission Occurred Register -------- */
#define MCAN_TXBTO_TO0_Pos                    _UINT32_(0)                                          /* (MCAN_TXBTO) Transmission Occurred for Buffer 0 Position */
#define MCAN_TXBTO_TO0_Msk                    (_UINT32_(0x1) << MCAN_TXBTO_TO0_Pos)                /* (MCAN_TXBTO) Transmission Occurred for Buffer 0 Mask */
#define MCAN_TXBTO_TO0(value)                 (MCAN_TXBTO_TO0_Msk & (_UINT32_(value) << MCAN_TXBTO_TO0_Pos)) /* Assigment of value for TO0 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO1_Pos                    _UINT32_(1)                                          /* (MCAN_TXBTO) Transmission Occurred for Buffer 1 Position */
#define MCAN_TXBTO_TO1_Msk                    (_UINT32_(0x1) << MCAN_TXBTO_TO1_Pos)                /* (MCAN_TXBTO) Transmission Occurred for Buffer 1 Mask */
#define MCAN_TXBTO_TO1(value)                 (MCAN_TXBTO_TO1_Msk & (_UINT32_(value) << MCAN_TXBTO_TO1_Pos)) /* Assigment of value for TO1 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO2_Pos                    _UINT32_(2)                                          /* (MCAN_TXBTO) Transmission Occurred for Buffer 2 Position */
#define MCAN_TXBTO_TO2_Msk                    (_UINT32_(0x1) << MCAN_TXBTO_TO2_Pos)                /* (MCAN_TXBTO) Transmission Occurred for Buffer 2 Mask */
#define MCAN_TXBTO_TO2(value)                 (MCAN_TXBTO_TO2_Msk & (_UINT32_(value) << MCAN_TXBTO_TO2_Pos)) /* Assigment of value for TO2 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO3_Pos                    _UINT32_(3)                                          /* (MCAN_TXBTO) Transmission Occurred for Buffer 3 Position */
#define MCAN_TXBTO_TO3_Msk                    (_UINT32_(0x1) << MCAN_TXBTO_TO3_Pos)                /* (MCAN_TXBTO) Transmission Occurred for Buffer 3 Mask */
#define MCAN_TXBTO_TO3(value)                 (MCAN_TXBTO_TO3_Msk & (_UINT32_(value) << MCAN_TXBTO_TO3_Pos)) /* Assigment of value for TO3 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO4_Pos                    _UINT32_(4)                                          /* (MCAN_TXBTO) Transmission Occurred for Buffer 4 Position */
#define MCAN_TXBTO_TO4_Msk                    (_UINT32_(0x1) << MCAN_TXBTO_TO4_Pos)                /* (MCAN_TXBTO) Transmission Occurred for Buffer 4 Mask */
#define MCAN_TXBTO_TO4(value)                 (MCAN_TXBTO_TO4_Msk & (_UINT32_(value) << MCAN_TXBTO_TO4_Pos)) /* Assigment of value for TO4 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO5_Pos                    _UINT32_(5)                                          /* (MCAN_TXBTO) Transmission Occurred for Buffer 5 Position */
#define MCAN_TXBTO_TO5_Msk                    (_UINT32_(0x1) << MCAN_TXBTO_TO5_Pos)                /* (MCAN_TXBTO) Transmission Occurred for Buffer 5 Mask */
#define MCAN_TXBTO_TO5(value)                 (MCAN_TXBTO_TO5_Msk & (_UINT32_(value) << MCAN_TXBTO_TO5_Pos)) /* Assigment of value for TO5 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO6_Pos                    _UINT32_(6)                                          /* (MCAN_TXBTO) Transmission Occurred for Buffer 6 Position */
#define MCAN_TXBTO_TO6_Msk                    (_UINT32_(0x1) << MCAN_TXBTO_TO6_Pos)                /* (MCAN_TXBTO) Transmission Occurred for Buffer 6 Mask */
#define MCAN_TXBTO_TO6(value)                 (MCAN_TXBTO_TO6_Msk & (_UINT32_(value) << MCAN_TXBTO_TO6_Pos)) /* Assigment of value for TO6 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO7_Pos                    _UINT32_(7)                                          /* (MCAN_TXBTO) Transmission Occurred for Buffer 7 Position */
#define MCAN_TXBTO_TO7_Msk                    (_UINT32_(0x1) << MCAN_TXBTO_TO7_Pos)                /* (MCAN_TXBTO) Transmission Occurred for Buffer 7 Mask */
#define MCAN_TXBTO_TO7(value)                 (MCAN_TXBTO_TO7_Msk & (_UINT32_(value) << MCAN_TXBTO_TO7_Pos)) /* Assigment of value for TO7 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO8_Pos                    _UINT32_(8)                                          /* (MCAN_TXBTO) Transmission Occurred for Buffer 8 Position */
#define MCAN_TXBTO_TO8_Msk                    (_UINT32_(0x1) << MCAN_TXBTO_TO8_Pos)                /* (MCAN_TXBTO) Transmission Occurred for Buffer 8 Mask */
#define MCAN_TXBTO_TO8(value)                 (MCAN_TXBTO_TO8_Msk & (_UINT32_(value) << MCAN_TXBTO_TO8_Pos)) /* Assigment of value for TO8 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO9_Pos                    _UINT32_(9)                                          /* (MCAN_TXBTO) Transmission Occurred for Buffer 9 Position */
#define MCAN_TXBTO_TO9_Msk                    (_UINT32_(0x1) << MCAN_TXBTO_TO9_Pos)                /* (MCAN_TXBTO) Transmission Occurred for Buffer 9 Mask */
#define MCAN_TXBTO_TO9(value)                 (MCAN_TXBTO_TO9_Msk & (_UINT32_(value) << MCAN_TXBTO_TO9_Pos)) /* Assigment of value for TO9 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO10_Pos                   _UINT32_(10)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 10 Position */
#define MCAN_TXBTO_TO10_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO10_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 10 Mask */
#define MCAN_TXBTO_TO10(value)                (MCAN_TXBTO_TO10_Msk & (_UINT32_(value) << MCAN_TXBTO_TO10_Pos)) /* Assigment of value for TO10 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO11_Pos                   _UINT32_(11)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 11 Position */
#define MCAN_TXBTO_TO11_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO11_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 11 Mask */
#define MCAN_TXBTO_TO11(value)                (MCAN_TXBTO_TO11_Msk & (_UINT32_(value) << MCAN_TXBTO_TO11_Pos)) /* Assigment of value for TO11 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO12_Pos                   _UINT32_(12)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 12 Position */
#define MCAN_TXBTO_TO12_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO12_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 12 Mask */
#define MCAN_TXBTO_TO12(value)                (MCAN_TXBTO_TO12_Msk & (_UINT32_(value) << MCAN_TXBTO_TO12_Pos)) /* Assigment of value for TO12 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO13_Pos                   _UINT32_(13)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 13 Position */
#define MCAN_TXBTO_TO13_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO13_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 13 Mask */
#define MCAN_TXBTO_TO13(value)                (MCAN_TXBTO_TO13_Msk & (_UINT32_(value) << MCAN_TXBTO_TO13_Pos)) /* Assigment of value for TO13 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO14_Pos                   _UINT32_(14)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 14 Position */
#define MCAN_TXBTO_TO14_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO14_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 14 Mask */
#define MCAN_TXBTO_TO14(value)                (MCAN_TXBTO_TO14_Msk & (_UINT32_(value) << MCAN_TXBTO_TO14_Pos)) /* Assigment of value for TO14 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO15_Pos                   _UINT32_(15)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 15 Position */
#define MCAN_TXBTO_TO15_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO15_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 15 Mask */
#define MCAN_TXBTO_TO15(value)                (MCAN_TXBTO_TO15_Msk & (_UINT32_(value) << MCAN_TXBTO_TO15_Pos)) /* Assigment of value for TO15 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO16_Pos                   _UINT32_(16)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 16 Position */
#define MCAN_TXBTO_TO16_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO16_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 16 Mask */
#define MCAN_TXBTO_TO16(value)                (MCAN_TXBTO_TO16_Msk & (_UINT32_(value) << MCAN_TXBTO_TO16_Pos)) /* Assigment of value for TO16 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO17_Pos                   _UINT32_(17)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 17 Position */
#define MCAN_TXBTO_TO17_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO17_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 17 Mask */
#define MCAN_TXBTO_TO17(value)                (MCAN_TXBTO_TO17_Msk & (_UINT32_(value) << MCAN_TXBTO_TO17_Pos)) /* Assigment of value for TO17 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO18_Pos                   _UINT32_(18)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 18 Position */
#define MCAN_TXBTO_TO18_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO18_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 18 Mask */
#define MCAN_TXBTO_TO18(value)                (MCAN_TXBTO_TO18_Msk & (_UINT32_(value) << MCAN_TXBTO_TO18_Pos)) /* Assigment of value for TO18 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO19_Pos                   _UINT32_(19)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 19 Position */
#define MCAN_TXBTO_TO19_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO19_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 19 Mask */
#define MCAN_TXBTO_TO19(value)                (MCAN_TXBTO_TO19_Msk & (_UINT32_(value) << MCAN_TXBTO_TO19_Pos)) /* Assigment of value for TO19 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO20_Pos                   _UINT32_(20)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 20 Position */
#define MCAN_TXBTO_TO20_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO20_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 20 Mask */
#define MCAN_TXBTO_TO20(value)                (MCAN_TXBTO_TO20_Msk & (_UINT32_(value) << MCAN_TXBTO_TO20_Pos)) /* Assigment of value for TO20 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO21_Pos                   _UINT32_(21)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 21 Position */
#define MCAN_TXBTO_TO21_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO21_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 21 Mask */
#define MCAN_TXBTO_TO21(value)                (MCAN_TXBTO_TO21_Msk & (_UINT32_(value) << MCAN_TXBTO_TO21_Pos)) /* Assigment of value for TO21 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO22_Pos                   _UINT32_(22)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 22 Position */
#define MCAN_TXBTO_TO22_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO22_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 22 Mask */
#define MCAN_TXBTO_TO22(value)                (MCAN_TXBTO_TO22_Msk & (_UINT32_(value) << MCAN_TXBTO_TO22_Pos)) /* Assigment of value for TO22 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO23_Pos                   _UINT32_(23)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 23 Position */
#define MCAN_TXBTO_TO23_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO23_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 23 Mask */
#define MCAN_TXBTO_TO23(value)                (MCAN_TXBTO_TO23_Msk & (_UINT32_(value) << MCAN_TXBTO_TO23_Pos)) /* Assigment of value for TO23 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO24_Pos                   _UINT32_(24)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 24 Position */
#define MCAN_TXBTO_TO24_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO24_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 24 Mask */
#define MCAN_TXBTO_TO24(value)                (MCAN_TXBTO_TO24_Msk & (_UINT32_(value) << MCAN_TXBTO_TO24_Pos)) /* Assigment of value for TO24 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO25_Pos                   _UINT32_(25)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 25 Position */
#define MCAN_TXBTO_TO25_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO25_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 25 Mask */
#define MCAN_TXBTO_TO25(value)                (MCAN_TXBTO_TO25_Msk & (_UINT32_(value) << MCAN_TXBTO_TO25_Pos)) /* Assigment of value for TO25 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO26_Pos                   _UINT32_(26)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 26 Position */
#define MCAN_TXBTO_TO26_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO26_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 26 Mask */
#define MCAN_TXBTO_TO26(value)                (MCAN_TXBTO_TO26_Msk & (_UINT32_(value) << MCAN_TXBTO_TO26_Pos)) /* Assigment of value for TO26 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO27_Pos                   _UINT32_(27)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 27 Position */
#define MCAN_TXBTO_TO27_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO27_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 27 Mask */
#define MCAN_TXBTO_TO27(value)                (MCAN_TXBTO_TO27_Msk & (_UINT32_(value) << MCAN_TXBTO_TO27_Pos)) /* Assigment of value for TO27 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO28_Pos                   _UINT32_(28)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 28 Position */
#define MCAN_TXBTO_TO28_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO28_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 28 Mask */
#define MCAN_TXBTO_TO28(value)                (MCAN_TXBTO_TO28_Msk & (_UINT32_(value) << MCAN_TXBTO_TO28_Pos)) /* Assigment of value for TO28 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO29_Pos                   _UINT32_(29)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 29 Position */
#define MCAN_TXBTO_TO29_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO29_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 29 Mask */
#define MCAN_TXBTO_TO29(value)                (MCAN_TXBTO_TO29_Msk & (_UINT32_(value) << MCAN_TXBTO_TO29_Pos)) /* Assigment of value for TO29 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO30_Pos                   _UINT32_(30)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 30 Position */
#define MCAN_TXBTO_TO30_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO30_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 30 Mask */
#define MCAN_TXBTO_TO30(value)                (MCAN_TXBTO_TO30_Msk & (_UINT32_(value) << MCAN_TXBTO_TO30_Pos)) /* Assigment of value for TO30 in the MCAN_TXBTO register */
#define MCAN_TXBTO_TO31_Pos                   _UINT32_(31)                                         /* (MCAN_TXBTO) Transmission Occurred for Buffer 31 Position */
#define MCAN_TXBTO_TO31_Msk                   (_UINT32_(0x1) << MCAN_TXBTO_TO31_Pos)               /* (MCAN_TXBTO) Transmission Occurred for Buffer 31 Mask */
#define MCAN_TXBTO_TO31(value)                (MCAN_TXBTO_TO31_Msk & (_UINT32_(value) << MCAN_TXBTO_TO31_Pos)) /* Assigment of value for TO31 in the MCAN_TXBTO register */
#define MCAN_TXBTO_Msk                        _UINT32_(0xFFFFFFFF)                                 /* (MCAN_TXBTO) Register Mask  */

#define MCAN_TXBTO_TO_Pos                     _UINT32_(0)                                          /* (MCAN_TXBTO Position) Transmission Occurred for Buffer 3x */
#define MCAN_TXBTO_TO_Msk                     (_UINT32_(0xFFFFFFFF) << MCAN_TXBTO_TO_Pos)          /* (MCAN_TXBTO Mask) TO */
#define MCAN_TXBTO_TO(value)                  (MCAN_TXBTO_TO_Msk & (_UINT32_(value) << MCAN_TXBTO_TO_Pos)) 

/* -------- MCAN_TXBCF : (MCAN Offset: 0xDC) ( R/ 32) Transmit Buffer Cancellation Finished Register -------- */
#define MCAN_TXBCF_CF0_Pos                    _UINT32_(0)                                          /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 0 Position */
#define MCAN_TXBCF_CF0_Msk                    (_UINT32_(0x1) << MCAN_TXBCF_CF0_Pos)                /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 0 Mask */
#define MCAN_TXBCF_CF0(value)                 (MCAN_TXBCF_CF0_Msk & (_UINT32_(value) << MCAN_TXBCF_CF0_Pos)) /* Assigment of value for CF0 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF1_Pos                    _UINT32_(1)                                          /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 1 Position */
#define MCAN_TXBCF_CF1_Msk                    (_UINT32_(0x1) << MCAN_TXBCF_CF1_Pos)                /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 1 Mask */
#define MCAN_TXBCF_CF1(value)                 (MCAN_TXBCF_CF1_Msk & (_UINT32_(value) << MCAN_TXBCF_CF1_Pos)) /* Assigment of value for CF1 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF2_Pos                    _UINT32_(2)                                          /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 2 Position */
#define MCAN_TXBCF_CF2_Msk                    (_UINT32_(0x1) << MCAN_TXBCF_CF2_Pos)                /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 2 Mask */
#define MCAN_TXBCF_CF2(value)                 (MCAN_TXBCF_CF2_Msk & (_UINT32_(value) << MCAN_TXBCF_CF2_Pos)) /* Assigment of value for CF2 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF3_Pos                    _UINT32_(3)                                          /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 3 Position */
#define MCAN_TXBCF_CF3_Msk                    (_UINT32_(0x1) << MCAN_TXBCF_CF3_Pos)                /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 3 Mask */
#define MCAN_TXBCF_CF3(value)                 (MCAN_TXBCF_CF3_Msk & (_UINT32_(value) << MCAN_TXBCF_CF3_Pos)) /* Assigment of value for CF3 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF4_Pos                    _UINT32_(4)                                          /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 4 Position */
#define MCAN_TXBCF_CF4_Msk                    (_UINT32_(0x1) << MCAN_TXBCF_CF4_Pos)                /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 4 Mask */
#define MCAN_TXBCF_CF4(value)                 (MCAN_TXBCF_CF4_Msk & (_UINT32_(value) << MCAN_TXBCF_CF4_Pos)) /* Assigment of value for CF4 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF5_Pos                    _UINT32_(5)                                          /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 5 Position */
#define MCAN_TXBCF_CF5_Msk                    (_UINT32_(0x1) << MCAN_TXBCF_CF5_Pos)                /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 5 Mask */
#define MCAN_TXBCF_CF5(value)                 (MCAN_TXBCF_CF5_Msk & (_UINT32_(value) << MCAN_TXBCF_CF5_Pos)) /* Assigment of value for CF5 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF6_Pos                    _UINT32_(6)                                          /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 6 Position */
#define MCAN_TXBCF_CF6_Msk                    (_UINT32_(0x1) << MCAN_TXBCF_CF6_Pos)                /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 6 Mask */
#define MCAN_TXBCF_CF6(value)                 (MCAN_TXBCF_CF6_Msk & (_UINT32_(value) << MCAN_TXBCF_CF6_Pos)) /* Assigment of value for CF6 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF7_Pos                    _UINT32_(7)                                          /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 7 Position */
#define MCAN_TXBCF_CF7_Msk                    (_UINT32_(0x1) << MCAN_TXBCF_CF7_Pos)                /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 7 Mask */
#define MCAN_TXBCF_CF7(value)                 (MCAN_TXBCF_CF7_Msk & (_UINT32_(value) << MCAN_TXBCF_CF7_Pos)) /* Assigment of value for CF7 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF8_Pos                    _UINT32_(8)                                          /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 8 Position */
#define MCAN_TXBCF_CF8_Msk                    (_UINT32_(0x1) << MCAN_TXBCF_CF8_Pos)                /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 8 Mask */
#define MCAN_TXBCF_CF8(value)                 (MCAN_TXBCF_CF8_Msk & (_UINT32_(value) << MCAN_TXBCF_CF8_Pos)) /* Assigment of value for CF8 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF9_Pos                    _UINT32_(9)                                          /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 9 Position */
#define MCAN_TXBCF_CF9_Msk                    (_UINT32_(0x1) << MCAN_TXBCF_CF9_Pos)                /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 9 Mask */
#define MCAN_TXBCF_CF9(value)                 (MCAN_TXBCF_CF9_Msk & (_UINT32_(value) << MCAN_TXBCF_CF9_Pos)) /* Assigment of value for CF9 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF10_Pos                   _UINT32_(10)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 10 Position */
#define MCAN_TXBCF_CF10_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF10_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 10 Mask */
#define MCAN_TXBCF_CF10(value)                (MCAN_TXBCF_CF10_Msk & (_UINT32_(value) << MCAN_TXBCF_CF10_Pos)) /* Assigment of value for CF10 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF11_Pos                   _UINT32_(11)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 11 Position */
#define MCAN_TXBCF_CF11_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF11_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 11 Mask */
#define MCAN_TXBCF_CF11(value)                (MCAN_TXBCF_CF11_Msk & (_UINT32_(value) << MCAN_TXBCF_CF11_Pos)) /* Assigment of value for CF11 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF12_Pos                   _UINT32_(12)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 12 Position */
#define MCAN_TXBCF_CF12_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF12_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 12 Mask */
#define MCAN_TXBCF_CF12(value)                (MCAN_TXBCF_CF12_Msk & (_UINT32_(value) << MCAN_TXBCF_CF12_Pos)) /* Assigment of value for CF12 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF13_Pos                   _UINT32_(13)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 13 Position */
#define MCAN_TXBCF_CF13_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF13_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 13 Mask */
#define MCAN_TXBCF_CF13(value)                (MCAN_TXBCF_CF13_Msk & (_UINT32_(value) << MCAN_TXBCF_CF13_Pos)) /* Assigment of value for CF13 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF14_Pos                   _UINT32_(14)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 14 Position */
#define MCAN_TXBCF_CF14_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF14_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 14 Mask */
#define MCAN_TXBCF_CF14(value)                (MCAN_TXBCF_CF14_Msk & (_UINT32_(value) << MCAN_TXBCF_CF14_Pos)) /* Assigment of value for CF14 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF15_Pos                   _UINT32_(15)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 15 Position */
#define MCAN_TXBCF_CF15_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF15_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 15 Mask */
#define MCAN_TXBCF_CF15(value)                (MCAN_TXBCF_CF15_Msk & (_UINT32_(value) << MCAN_TXBCF_CF15_Pos)) /* Assigment of value for CF15 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF16_Pos                   _UINT32_(16)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 16 Position */
#define MCAN_TXBCF_CF16_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF16_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 16 Mask */
#define MCAN_TXBCF_CF16(value)                (MCAN_TXBCF_CF16_Msk & (_UINT32_(value) << MCAN_TXBCF_CF16_Pos)) /* Assigment of value for CF16 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF17_Pos                   _UINT32_(17)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 17 Position */
#define MCAN_TXBCF_CF17_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF17_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 17 Mask */
#define MCAN_TXBCF_CF17(value)                (MCAN_TXBCF_CF17_Msk & (_UINT32_(value) << MCAN_TXBCF_CF17_Pos)) /* Assigment of value for CF17 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF18_Pos                   _UINT32_(18)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 18 Position */
#define MCAN_TXBCF_CF18_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF18_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 18 Mask */
#define MCAN_TXBCF_CF18(value)                (MCAN_TXBCF_CF18_Msk & (_UINT32_(value) << MCAN_TXBCF_CF18_Pos)) /* Assigment of value for CF18 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF19_Pos                   _UINT32_(19)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 19 Position */
#define MCAN_TXBCF_CF19_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF19_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 19 Mask */
#define MCAN_TXBCF_CF19(value)                (MCAN_TXBCF_CF19_Msk & (_UINT32_(value) << MCAN_TXBCF_CF19_Pos)) /* Assigment of value for CF19 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF20_Pos                   _UINT32_(20)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 20 Position */
#define MCAN_TXBCF_CF20_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF20_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 20 Mask */
#define MCAN_TXBCF_CF20(value)                (MCAN_TXBCF_CF20_Msk & (_UINT32_(value) << MCAN_TXBCF_CF20_Pos)) /* Assigment of value for CF20 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF21_Pos                   _UINT32_(21)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 21 Position */
#define MCAN_TXBCF_CF21_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF21_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 21 Mask */
#define MCAN_TXBCF_CF21(value)                (MCAN_TXBCF_CF21_Msk & (_UINT32_(value) << MCAN_TXBCF_CF21_Pos)) /* Assigment of value for CF21 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF22_Pos                   _UINT32_(22)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 22 Position */
#define MCAN_TXBCF_CF22_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF22_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 22 Mask */
#define MCAN_TXBCF_CF22(value)                (MCAN_TXBCF_CF22_Msk & (_UINT32_(value) << MCAN_TXBCF_CF22_Pos)) /* Assigment of value for CF22 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF23_Pos                   _UINT32_(23)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 23 Position */
#define MCAN_TXBCF_CF23_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF23_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 23 Mask */
#define MCAN_TXBCF_CF23(value)                (MCAN_TXBCF_CF23_Msk & (_UINT32_(value) << MCAN_TXBCF_CF23_Pos)) /* Assigment of value for CF23 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF24_Pos                   _UINT32_(24)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 24 Position */
#define MCAN_TXBCF_CF24_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF24_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 24 Mask */
#define MCAN_TXBCF_CF24(value)                (MCAN_TXBCF_CF24_Msk & (_UINT32_(value) << MCAN_TXBCF_CF24_Pos)) /* Assigment of value for CF24 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF25_Pos                   _UINT32_(25)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 25 Position */
#define MCAN_TXBCF_CF25_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF25_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 25 Mask */
#define MCAN_TXBCF_CF25(value)                (MCAN_TXBCF_CF25_Msk & (_UINT32_(value) << MCAN_TXBCF_CF25_Pos)) /* Assigment of value for CF25 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF26_Pos                   _UINT32_(26)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 26 Position */
#define MCAN_TXBCF_CF26_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF26_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 26 Mask */
#define MCAN_TXBCF_CF26(value)                (MCAN_TXBCF_CF26_Msk & (_UINT32_(value) << MCAN_TXBCF_CF26_Pos)) /* Assigment of value for CF26 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF27_Pos                   _UINT32_(27)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 27 Position */
#define MCAN_TXBCF_CF27_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF27_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 27 Mask */
#define MCAN_TXBCF_CF27(value)                (MCAN_TXBCF_CF27_Msk & (_UINT32_(value) << MCAN_TXBCF_CF27_Pos)) /* Assigment of value for CF27 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF28_Pos                   _UINT32_(28)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 28 Position */
#define MCAN_TXBCF_CF28_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF28_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 28 Mask */
#define MCAN_TXBCF_CF28(value)                (MCAN_TXBCF_CF28_Msk & (_UINT32_(value) << MCAN_TXBCF_CF28_Pos)) /* Assigment of value for CF28 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF29_Pos                   _UINT32_(29)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 29 Position */
#define MCAN_TXBCF_CF29_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF29_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 29 Mask */
#define MCAN_TXBCF_CF29(value)                (MCAN_TXBCF_CF29_Msk & (_UINT32_(value) << MCAN_TXBCF_CF29_Pos)) /* Assigment of value for CF29 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF30_Pos                   _UINT32_(30)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 30 Position */
#define MCAN_TXBCF_CF30_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF30_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 30 Mask */
#define MCAN_TXBCF_CF30(value)                (MCAN_TXBCF_CF30_Msk & (_UINT32_(value) << MCAN_TXBCF_CF30_Pos)) /* Assigment of value for CF30 in the MCAN_TXBCF register */
#define MCAN_TXBCF_CF31_Pos                   _UINT32_(31)                                         /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 31 Position */
#define MCAN_TXBCF_CF31_Msk                   (_UINT32_(0x1) << MCAN_TXBCF_CF31_Pos)               /* (MCAN_TXBCF) Cancellation Finished for Transmit Buffer 31 Mask */
#define MCAN_TXBCF_CF31(value)                (MCAN_TXBCF_CF31_Msk & (_UINT32_(value) << MCAN_TXBCF_CF31_Pos)) /* Assigment of value for CF31 in the MCAN_TXBCF register */
#define MCAN_TXBCF_Msk                        _UINT32_(0xFFFFFFFF)                                 /* (MCAN_TXBCF) Register Mask  */

#define MCAN_TXBCF_CF_Pos                     _UINT32_(0)                                          /* (MCAN_TXBCF Position) Cancellation Finished for Transmit Buffer 3x */
#define MCAN_TXBCF_CF_Msk                     (_UINT32_(0xFFFFFFFF) << MCAN_TXBCF_CF_Pos)          /* (MCAN_TXBCF Mask) CF */
#define MCAN_TXBCF_CF(value)                  (MCAN_TXBCF_CF_Msk & (_UINT32_(value) << MCAN_TXBCF_CF_Pos)) 

/* -------- MCAN_TXBTIE : (MCAN Offset: 0xE0) (R/W 32) Transmit Buffer Transmission Interrupt Enable Register -------- */
#define MCAN_TXBTIE_TIE0_Pos                  _UINT32_(0)                                          /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 0 Position */
#define MCAN_TXBTIE_TIE0_Msk                  (_UINT32_(0x1) << MCAN_TXBTIE_TIE0_Pos)              /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 0 Mask */
#define MCAN_TXBTIE_TIE0(value)               (MCAN_TXBTIE_TIE0_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE0_Pos)) /* Assigment of value for TIE0 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE1_Pos                  _UINT32_(1)                                          /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 1 Position */
#define MCAN_TXBTIE_TIE1_Msk                  (_UINT32_(0x1) << MCAN_TXBTIE_TIE1_Pos)              /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 1 Mask */
#define MCAN_TXBTIE_TIE1(value)               (MCAN_TXBTIE_TIE1_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE1_Pos)) /* Assigment of value for TIE1 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE2_Pos                  _UINT32_(2)                                          /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 2 Position */
#define MCAN_TXBTIE_TIE2_Msk                  (_UINT32_(0x1) << MCAN_TXBTIE_TIE2_Pos)              /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 2 Mask */
#define MCAN_TXBTIE_TIE2(value)               (MCAN_TXBTIE_TIE2_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE2_Pos)) /* Assigment of value for TIE2 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE3_Pos                  _UINT32_(3)                                          /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 3 Position */
#define MCAN_TXBTIE_TIE3_Msk                  (_UINT32_(0x1) << MCAN_TXBTIE_TIE3_Pos)              /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 3 Mask */
#define MCAN_TXBTIE_TIE3(value)               (MCAN_TXBTIE_TIE3_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE3_Pos)) /* Assigment of value for TIE3 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE4_Pos                  _UINT32_(4)                                          /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 4 Position */
#define MCAN_TXBTIE_TIE4_Msk                  (_UINT32_(0x1) << MCAN_TXBTIE_TIE4_Pos)              /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 4 Mask */
#define MCAN_TXBTIE_TIE4(value)               (MCAN_TXBTIE_TIE4_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE4_Pos)) /* Assigment of value for TIE4 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE5_Pos                  _UINT32_(5)                                          /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 5 Position */
#define MCAN_TXBTIE_TIE5_Msk                  (_UINT32_(0x1) << MCAN_TXBTIE_TIE5_Pos)              /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 5 Mask */
#define MCAN_TXBTIE_TIE5(value)               (MCAN_TXBTIE_TIE5_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE5_Pos)) /* Assigment of value for TIE5 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE6_Pos                  _UINT32_(6)                                          /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 6 Position */
#define MCAN_TXBTIE_TIE6_Msk                  (_UINT32_(0x1) << MCAN_TXBTIE_TIE6_Pos)              /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 6 Mask */
#define MCAN_TXBTIE_TIE6(value)               (MCAN_TXBTIE_TIE6_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE6_Pos)) /* Assigment of value for TIE6 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE7_Pos                  _UINT32_(7)                                          /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 7 Position */
#define MCAN_TXBTIE_TIE7_Msk                  (_UINT32_(0x1) << MCAN_TXBTIE_TIE7_Pos)              /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 7 Mask */
#define MCAN_TXBTIE_TIE7(value)               (MCAN_TXBTIE_TIE7_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE7_Pos)) /* Assigment of value for TIE7 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE8_Pos                  _UINT32_(8)                                          /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 8 Position */
#define MCAN_TXBTIE_TIE8_Msk                  (_UINT32_(0x1) << MCAN_TXBTIE_TIE8_Pos)              /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 8 Mask */
#define MCAN_TXBTIE_TIE8(value)               (MCAN_TXBTIE_TIE8_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE8_Pos)) /* Assigment of value for TIE8 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE9_Pos                  _UINT32_(9)                                          /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 9 Position */
#define MCAN_TXBTIE_TIE9_Msk                  (_UINT32_(0x1) << MCAN_TXBTIE_TIE9_Pos)              /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 9 Mask */
#define MCAN_TXBTIE_TIE9(value)               (MCAN_TXBTIE_TIE9_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE9_Pos)) /* Assigment of value for TIE9 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE10_Pos                 _UINT32_(10)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 10 Position */
#define MCAN_TXBTIE_TIE10_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE10_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 10 Mask */
#define MCAN_TXBTIE_TIE10(value)              (MCAN_TXBTIE_TIE10_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE10_Pos)) /* Assigment of value for TIE10 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE11_Pos                 _UINT32_(11)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 11 Position */
#define MCAN_TXBTIE_TIE11_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE11_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 11 Mask */
#define MCAN_TXBTIE_TIE11(value)              (MCAN_TXBTIE_TIE11_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE11_Pos)) /* Assigment of value for TIE11 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE12_Pos                 _UINT32_(12)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 12 Position */
#define MCAN_TXBTIE_TIE12_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE12_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 12 Mask */
#define MCAN_TXBTIE_TIE12(value)              (MCAN_TXBTIE_TIE12_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE12_Pos)) /* Assigment of value for TIE12 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE13_Pos                 _UINT32_(13)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 13 Position */
#define MCAN_TXBTIE_TIE13_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE13_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 13 Mask */
#define MCAN_TXBTIE_TIE13(value)              (MCAN_TXBTIE_TIE13_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE13_Pos)) /* Assigment of value for TIE13 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE14_Pos                 _UINT32_(14)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 14 Position */
#define MCAN_TXBTIE_TIE14_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE14_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 14 Mask */
#define MCAN_TXBTIE_TIE14(value)              (MCAN_TXBTIE_TIE14_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE14_Pos)) /* Assigment of value for TIE14 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE15_Pos                 _UINT32_(15)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 15 Position */
#define MCAN_TXBTIE_TIE15_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE15_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 15 Mask */
#define MCAN_TXBTIE_TIE15(value)              (MCAN_TXBTIE_TIE15_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE15_Pos)) /* Assigment of value for TIE15 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE16_Pos                 _UINT32_(16)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 16 Position */
#define MCAN_TXBTIE_TIE16_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE16_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 16 Mask */
#define MCAN_TXBTIE_TIE16(value)              (MCAN_TXBTIE_TIE16_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE16_Pos)) /* Assigment of value for TIE16 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE17_Pos                 _UINT32_(17)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 17 Position */
#define MCAN_TXBTIE_TIE17_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE17_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 17 Mask */
#define MCAN_TXBTIE_TIE17(value)              (MCAN_TXBTIE_TIE17_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE17_Pos)) /* Assigment of value for TIE17 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE18_Pos                 _UINT32_(18)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 18 Position */
#define MCAN_TXBTIE_TIE18_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE18_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 18 Mask */
#define MCAN_TXBTIE_TIE18(value)              (MCAN_TXBTIE_TIE18_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE18_Pos)) /* Assigment of value for TIE18 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE19_Pos                 _UINT32_(19)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 19 Position */
#define MCAN_TXBTIE_TIE19_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE19_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 19 Mask */
#define MCAN_TXBTIE_TIE19(value)              (MCAN_TXBTIE_TIE19_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE19_Pos)) /* Assigment of value for TIE19 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE20_Pos                 _UINT32_(20)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 20 Position */
#define MCAN_TXBTIE_TIE20_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE20_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 20 Mask */
#define MCAN_TXBTIE_TIE20(value)              (MCAN_TXBTIE_TIE20_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE20_Pos)) /* Assigment of value for TIE20 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE21_Pos                 _UINT32_(21)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 21 Position */
#define MCAN_TXBTIE_TIE21_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE21_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 21 Mask */
#define MCAN_TXBTIE_TIE21(value)              (MCAN_TXBTIE_TIE21_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE21_Pos)) /* Assigment of value for TIE21 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE22_Pos                 _UINT32_(22)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 22 Position */
#define MCAN_TXBTIE_TIE22_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE22_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 22 Mask */
#define MCAN_TXBTIE_TIE22(value)              (MCAN_TXBTIE_TIE22_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE22_Pos)) /* Assigment of value for TIE22 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE23_Pos                 _UINT32_(23)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 23 Position */
#define MCAN_TXBTIE_TIE23_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE23_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 23 Mask */
#define MCAN_TXBTIE_TIE23(value)              (MCAN_TXBTIE_TIE23_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE23_Pos)) /* Assigment of value for TIE23 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE24_Pos                 _UINT32_(24)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 24 Position */
#define MCAN_TXBTIE_TIE24_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE24_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 24 Mask */
#define MCAN_TXBTIE_TIE24(value)              (MCAN_TXBTIE_TIE24_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE24_Pos)) /* Assigment of value for TIE24 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE25_Pos                 _UINT32_(25)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 25 Position */
#define MCAN_TXBTIE_TIE25_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE25_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 25 Mask */
#define MCAN_TXBTIE_TIE25(value)              (MCAN_TXBTIE_TIE25_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE25_Pos)) /* Assigment of value for TIE25 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE26_Pos                 _UINT32_(26)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 26 Position */
#define MCAN_TXBTIE_TIE26_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE26_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 26 Mask */
#define MCAN_TXBTIE_TIE26(value)              (MCAN_TXBTIE_TIE26_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE26_Pos)) /* Assigment of value for TIE26 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE27_Pos                 _UINT32_(27)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 27 Position */
#define MCAN_TXBTIE_TIE27_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE27_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 27 Mask */
#define MCAN_TXBTIE_TIE27(value)              (MCAN_TXBTIE_TIE27_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE27_Pos)) /* Assigment of value for TIE27 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE28_Pos                 _UINT32_(28)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 28 Position */
#define MCAN_TXBTIE_TIE28_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE28_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 28 Mask */
#define MCAN_TXBTIE_TIE28(value)              (MCAN_TXBTIE_TIE28_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE28_Pos)) /* Assigment of value for TIE28 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE29_Pos                 _UINT32_(29)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 29 Position */
#define MCAN_TXBTIE_TIE29_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE29_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 29 Mask */
#define MCAN_TXBTIE_TIE29(value)              (MCAN_TXBTIE_TIE29_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE29_Pos)) /* Assigment of value for TIE29 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE30_Pos                 _UINT32_(30)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 30 Position */
#define MCAN_TXBTIE_TIE30_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE30_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 30 Mask */
#define MCAN_TXBTIE_TIE30(value)              (MCAN_TXBTIE_TIE30_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE30_Pos)) /* Assigment of value for TIE30 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_TIE31_Pos                 _UINT32_(31)                                         /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 31 Position */
#define MCAN_TXBTIE_TIE31_Msk                 (_UINT32_(0x1) << MCAN_TXBTIE_TIE31_Pos)             /* (MCAN_TXBTIE) Transmission Interrupt Enable for Buffer 31 Mask */
#define MCAN_TXBTIE_TIE31(value)              (MCAN_TXBTIE_TIE31_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE31_Pos)) /* Assigment of value for TIE31 in the MCAN_TXBTIE register */
#define MCAN_TXBTIE_Msk                       _UINT32_(0xFFFFFFFF)                                 /* (MCAN_TXBTIE) Register Mask  */

#define MCAN_TXBTIE_TIE_Pos                   _UINT32_(0)                                          /* (MCAN_TXBTIE Position) Transmission Interrupt Enable for Buffer 3x */
#define MCAN_TXBTIE_TIE_Msk                   (_UINT32_(0xFFFFFFFF) << MCAN_TXBTIE_TIE_Pos)        /* (MCAN_TXBTIE Mask) TIE */
#define MCAN_TXBTIE_TIE(value)                (MCAN_TXBTIE_TIE_Msk & (_UINT32_(value) << MCAN_TXBTIE_TIE_Pos)) 

/* -------- MCAN_TXBCIE : (MCAN Offset: 0xE4) (R/W 32) Transmit Buffer Cancellation Finished Interrupt Enable Register -------- */
#define MCAN_TXBCIE_CFIE0_Pos                 _UINT32_(0)                                          /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 0 Position */
#define MCAN_TXBCIE_CFIE0_Msk                 (_UINT32_(0x1) << MCAN_TXBCIE_CFIE0_Pos)             /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 0 Mask */
#define MCAN_TXBCIE_CFIE0(value)              (MCAN_TXBCIE_CFIE0_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE0_Pos)) /* Assigment of value for CFIE0 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE1_Pos                 _UINT32_(1)                                          /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 1 Position */
#define MCAN_TXBCIE_CFIE1_Msk                 (_UINT32_(0x1) << MCAN_TXBCIE_CFIE1_Pos)             /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 1 Mask */
#define MCAN_TXBCIE_CFIE1(value)              (MCAN_TXBCIE_CFIE1_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE1_Pos)) /* Assigment of value for CFIE1 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE2_Pos                 _UINT32_(2)                                          /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 2 Position */
#define MCAN_TXBCIE_CFIE2_Msk                 (_UINT32_(0x1) << MCAN_TXBCIE_CFIE2_Pos)             /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 2 Mask */
#define MCAN_TXBCIE_CFIE2(value)              (MCAN_TXBCIE_CFIE2_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE2_Pos)) /* Assigment of value for CFIE2 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE3_Pos                 _UINT32_(3)                                          /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 3 Position */
#define MCAN_TXBCIE_CFIE3_Msk                 (_UINT32_(0x1) << MCAN_TXBCIE_CFIE3_Pos)             /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 3 Mask */
#define MCAN_TXBCIE_CFIE3(value)              (MCAN_TXBCIE_CFIE3_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE3_Pos)) /* Assigment of value for CFIE3 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE4_Pos                 _UINT32_(4)                                          /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 4 Position */
#define MCAN_TXBCIE_CFIE4_Msk                 (_UINT32_(0x1) << MCAN_TXBCIE_CFIE4_Pos)             /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 4 Mask */
#define MCAN_TXBCIE_CFIE4(value)              (MCAN_TXBCIE_CFIE4_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE4_Pos)) /* Assigment of value for CFIE4 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE5_Pos                 _UINT32_(5)                                          /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 5 Position */
#define MCAN_TXBCIE_CFIE5_Msk                 (_UINT32_(0x1) << MCAN_TXBCIE_CFIE5_Pos)             /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 5 Mask */
#define MCAN_TXBCIE_CFIE5(value)              (MCAN_TXBCIE_CFIE5_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE5_Pos)) /* Assigment of value for CFIE5 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE6_Pos                 _UINT32_(6)                                          /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 6 Position */
#define MCAN_TXBCIE_CFIE6_Msk                 (_UINT32_(0x1) << MCAN_TXBCIE_CFIE6_Pos)             /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 6 Mask */
#define MCAN_TXBCIE_CFIE6(value)              (MCAN_TXBCIE_CFIE6_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE6_Pos)) /* Assigment of value for CFIE6 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE7_Pos                 _UINT32_(7)                                          /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 7 Position */
#define MCAN_TXBCIE_CFIE7_Msk                 (_UINT32_(0x1) << MCAN_TXBCIE_CFIE7_Pos)             /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 7 Mask */
#define MCAN_TXBCIE_CFIE7(value)              (MCAN_TXBCIE_CFIE7_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE7_Pos)) /* Assigment of value for CFIE7 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE8_Pos                 _UINT32_(8)                                          /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 8 Position */
#define MCAN_TXBCIE_CFIE8_Msk                 (_UINT32_(0x1) << MCAN_TXBCIE_CFIE8_Pos)             /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 8 Mask */
#define MCAN_TXBCIE_CFIE8(value)              (MCAN_TXBCIE_CFIE8_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE8_Pos)) /* Assigment of value for CFIE8 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE9_Pos                 _UINT32_(9)                                          /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 9 Position */
#define MCAN_TXBCIE_CFIE9_Msk                 (_UINT32_(0x1) << MCAN_TXBCIE_CFIE9_Pos)             /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 9 Mask */
#define MCAN_TXBCIE_CFIE9(value)              (MCAN_TXBCIE_CFIE9_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE9_Pos)) /* Assigment of value for CFIE9 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE10_Pos                _UINT32_(10)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 10 Position */
#define MCAN_TXBCIE_CFIE10_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE10_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 10 Mask */
#define MCAN_TXBCIE_CFIE10(value)             (MCAN_TXBCIE_CFIE10_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE10_Pos)) /* Assigment of value for CFIE10 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE11_Pos                _UINT32_(11)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 11 Position */
#define MCAN_TXBCIE_CFIE11_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE11_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 11 Mask */
#define MCAN_TXBCIE_CFIE11(value)             (MCAN_TXBCIE_CFIE11_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE11_Pos)) /* Assigment of value for CFIE11 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE12_Pos                _UINT32_(12)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 12 Position */
#define MCAN_TXBCIE_CFIE12_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE12_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 12 Mask */
#define MCAN_TXBCIE_CFIE12(value)             (MCAN_TXBCIE_CFIE12_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE12_Pos)) /* Assigment of value for CFIE12 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE13_Pos                _UINT32_(13)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 13 Position */
#define MCAN_TXBCIE_CFIE13_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE13_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 13 Mask */
#define MCAN_TXBCIE_CFIE13(value)             (MCAN_TXBCIE_CFIE13_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE13_Pos)) /* Assigment of value for CFIE13 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE14_Pos                _UINT32_(14)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 14 Position */
#define MCAN_TXBCIE_CFIE14_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE14_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 14 Mask */
#define MCAN_TXBCIE_CFIE14(value)             (MCAN_TXBCIE_CFIE14_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE14_Pos)) /* Assigment of value for CFIE14 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE15_Pos                _UINT32_(15)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 15 Position */
#define MCAN_TXBCIE_CFIE15_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE15_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 15 Mask */
#define MCAN_TXBCIE_CFIE15(value)             (MCAN_TXBCIE_CFIE15_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE15_Pos)) /* Assigment of value for CFIE15 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE16_Pos                _UINT32_(16)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 16 Position */
#define MCAN_TXBCIE_CFIE16_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE16_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 16 Mask */
#define MCAN_TXBCIE_CFIE16(value)             (MCAN_TXBCIE_CFIE16_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE16_Pos)) /* Assigment of value for CFIE16 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE17_Pos                _UINT32_(17)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 17 Position */
#define MCAN_TXBCIE_CFIE17_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE17_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 17 Mask */
#define MCAN_TXBCIE_CFIE17(value)             (MCAN_TXBCIE_CFIE17_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE17_Pos)) /* Assigment of value for CFIE17 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE18_Pos                _UINT32_(18)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 18 Position */
#define MCAN_TXBCIE_CFIE18_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE18_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 18 Mask */
#define MCAN_TXBCIE_CFIE18(value)             (MCAN_TXBCIE_CFIE18_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE18_Pos)) /* Assigment of value for CFIE18 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE19_Pos                _UINT32_(19)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 19 Position */
#define MCAN_TXBCIE_CFIE19_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE19_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 19 Mask */
#define MCAN_TXBCIE_CFIE19(value)             (MCAN_TXBCIE_CFIE19_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE19_Pos)) /* Assigment of value for CFIE19 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE20_Pos                _UINT32_(20)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 20 Position */
#define MCAN_TXBCIE_CFIE20_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE20_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 20 Mask */
#define MCAN_TXBCIE_CFIE20(value)             (MCAN_TXBCIE_CFIE20_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE20_Pos)) /* Assigment of value for CFIE20 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE21_Pos                _UINT32_(21)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 21 Position */
#define MCAN_TXBCIE_CFIE21_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE21_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 21 Mask */
#define MCAN_TXBCIE_CFIE21(value)             (MCAN_TXBCIE_CFIE21_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE21_Pos)) /* Assigment of value for CFIE21 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE22_Pos                _UINT32_(22)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 22 Position */
#define MCAN_TXBCIE_CFIE22_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE22_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 22 Mask */
#define MCAN_TXBCIE_CFIE22(value)             (MCAN_TXBCIE_CFIE22_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE22_Pos)) /* Assigment of value for CFIE22 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE23_Pos                _UINT32_(23)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 23 Position */
#define MCAN_TXBCIE_CFIE23_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE23_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 23 Mask */
#define MCAN_TXBCIE_CFIE23(value)             (MCAN_TXBCIE_CFIE23_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE23_Pos)) /* Assigment of value for CFIE23 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE24_Pos                _UINT32_(24)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 24 Position */
#define MCAN_TXBCIE_CFIE24_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE24_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 24 Mask */
#define MCAN_TXBCIE_CFIE24(value)             (MCAN_TXBCIE_CFIE24_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE24_Pos)) /* Assigment of value for CFIE24 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE25_Pos                _UINT32_(25)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 25 Position */
#define MCAN_TXBCIE_CFIE25_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE25_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 25 Mask */
#define MCAN_TXBCIE_CFIE25(value)             (MCAN_TXBCIE_CFIE25_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE25_Pos)) /* Assigment of value for CFIE25 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE26_Pos                _UINT32_(26)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 26 Position */
#define MCAN_TXBCIE_CFIE26_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE26_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 26 Mask */
#define MCAN_TXBCIE_CFIE26(value)             (MCAN_TXBCIE_CFIE26_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE26_Pos)) /* Assigment of value for CFIE26 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE27_Pos                _UINT32_(27)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 27 Position */
#define MCAN_TXBCIE_CFIE27_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE27_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 27 Mask */
#define MCAN_TXBCIE_CFIE27(value)             (MCAN_TXBCIE_CFIE27_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE27_Pos)) /* Assigment of value for CFIE27 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE28_Pos                _UINT32_(28)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 28 Position */
#define MCAN_TXBCIE_CFIE28_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE28_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 28 Mask */
#define MCAN_TXBCIE_CFIE28(value)             (MCAN_TXBCIE_CFIE28_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE28_Pos)) /* Assigment of value for CFIE28 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE29_Pos                _UINT32_(29)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 29 Position */
#define MCAN_TXBCIE_CFIE29_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE29_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 29 Mask */
#define MCAN_TXBCIE_CFIE29(value)             (MCAN_TXBCIE_CFIE29_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE29_Pos)) /* Assigment of value for CFIE29 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE30_Pos                _UINT32_(30)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 30 Position */
#define MCAN_TXBCIE_CFIE30_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE30_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 30 Mask */
#define MCAN_TXBCIE_CFIE30(value)             (MCAN_TXBCIE_CFIE30_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE30_Pos)) /* Assigment of value for CFIE30 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_CFIE31_Pos                _UINT32_(31)                                         /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 31 Position */
#define MCAN_TXBCIE_CFIE31_Msk                (_UINT32_(0x1) << MCAN_TXBCIE_CFIE31_Pos)            /* (MCAN_TXBCIE) Cancellation Finished Interrupt Enable for Transmit Buffer 31 Mask */
#define MCAN_TXBCIE_CFIE31(value)             (MCAN_TXBCIE_CFIE31_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE31_Pos)) /* Assigment of value for CFIE31 in the MCAN_TXBCIE register */
#define MCAN_TXBCIE_Msk                       _UINT32_(0xFFFFFFFF)                                 /* (MCAN_TXBCIE) Register Mask  */

#define MCAN_TXBCIE_CFIE_Pos                  _UINT32_(0)                                          /* (MCAN_TXBCIE Position) Cancellation Finished Interrupt Enable for Transmit Buffer 3x */
#define MCAN_TXBCIE_CFIE_Msk                  (_UINT32_(0xFFFFFFFF) << MCAN_TXBCIE_CFIE_Pos)       /* (MCAN_TXBCIE Mask) CFIE */
#define MCAN_TXBCIE_CFIE(value)               (MCAN_TXBCIE_CFIE_Msk & (_UINT32_(value) << MCAN_TXBCIE_CFIE_Pos)) 

/* -------- MCAN_TXEFC : (MCAN Offset: 0xF0) (R/W 32) Transmit Event FIFO Configuration Register -------- */
#define MCAN_TXEFC_EFSA_Pos                   _UINT32_(2)                                          /* (MCAN_TXEFC) Event FIFO Start Address Position */
#define MCAN_TXEFC_EFSA_Msk                   (_UINT32_(0x3FFF) << MCAN_TXEFC_EFSA_Pos)            /* (MCAN_TXEFC) Event FIFO Start Address Mask */
#define MCAN_TXEFC_EFSA(value)                (MCAN_TXEFC_EFSA_Msk & (_UINT32_(value) << MCAN_TXEFC_EFSA_Pos)) /* Assigment of value for EFSA in the MCAN_TXEFC register */
#define MCAN_TXEFC_EFS_Pos                    _UINT32_(16)                                         /* (MCAN_TXEFC) Event FIFO Size Position */
#define MCAN_TXEFC_EFS_Msk                    (_UINT32_(0x3F) << MCAN_TXEFC_EFS_Pos)               /* (MCAN_TXEFC) Event FIFO Size Mask */
#define MCAN_TXEFC_EFS(value)                 (MCAN_TXEFC_EFS_Msk & (_UINT32_(value) << MCAN_TXEFC_EFS_Pos)) /* Assigment of value for EFS in the MCAN_TXEFC register */
#define MCAN_TXEFC_EFWM_Pos                   _UINT32_(24)                                         /* (MCAN_TXEFC) Event FIFO Watermark Position */
#define MCAN_TXEFC_EFWM_Msk                   (_UINT32_(0x3F) << MCAN_TXEFC_EFWM_Pos)              /* (MCAN_TXEFC) Event FIFO Watermark Mask */
#define MCAN_TXEFC_EFWM(value)                (MCAN_TXEFC_EFWM_Msk & (_UINT32_(value) << MCAN_TXEFC_EFWM_Pos)) /* Assigment of value for EFWM in the MCAN_TXEFC register */
#define MCAN_TXEFC_Msk                        _UINT32_(0x3F3FFFFC)                                 /* (MCAN_TXEFC) Register Mask  */


/* -------- MCAN_TXEFS : (MCAN Offset: 0xF4) ( R/ 32) Transmit Event FIFO Status Register -------- */
#define MCAN_TXEFS_EFFL_Pos                   _UINT32_(0)                                          /* (MCAN_TXEFS) Event FIFO Fill Level Position */
#define MCAN_TXEFS_EFFL_Msk                   (_UINT32_(0x3F) << MCAN_TXEFS_EFFL_Pos)              /* (MCAN_TXEFS) Event FIFO Fill Level Mask */
#define MCAN_TXEFS_EFFL(value)                (MCAN_TXEFS_EFFL_Msk & (_UINT32_(value) << MCAN_TXEFS_EFFL_Pos)) /* Assigment of value for EFFL in the MCAN_TXEFS register */
#define MCAN_TXEFS_EFGI_Pos                   _UINT32_(8)                                          /* (MCAN_TXEFS) Event FIFO Get Index Position */
#define MCAN_TXEFS_EFGI_Msk                   (_UINT32_(0x1F) << MCAN_TXEFS_EFGI_Pos)              /* (MCAN_TXEFS) Event FIFO Get Index Mask */
#define MCAN_TXEFS_EFGI(value)                (MCAN_TXEFS_EFGI_Msk & (_UINT32_(value) << MCAN_TXEFS_EFGI_Pos)) /* Assigment of value for EFGI in the MCAN_TXEFS register */
#define MCAN_TXEFS_EFPI_Pos                   _UINT32_(16)                                         /* (MCAN_TXEFS) Event FIFO Put Index Position */
#define MCAN_TXEFS_EFPI_Msk                   (_UINT32_(0x1F) << MCAN_TXEFS_EFPI_Pos)              /* (MCAN_TXEFS) Event FIFO Put Index Mask */
#define MCAN_TXEFS_EFPI(value)                (MCAN_TXEFS_EFPI_Msk & (_UINT32_(value) << MCAN_TXEFS_EFPI_Pos)) /* Assigment of value for EFPI in the MCAN_TXEFS register */
#define MCAN_TXEFS_EFF_Pos                    _UINT32_(24)                                         /* (MCAN_TXEFS) Event FIFO Full Position */
#define MCAN_TXEFS_EFF_Msk                    (_UINT32_(0x1) << MCAN_TXEFS_EFF_Pos)                /* (MCAN_TXEFS) Event FIFO Full Mask */
#define MCAN_TXEFS_EFF(value)                 (MCAN_TXEFS_EFF_Msk & (_UINT32_(value) << MCAN_TXEFS_EFF_Pos)) /* Assigment of value for EFF in the MCAN_TXEFS register */
#define MCAN_TXEFS_TEFL_Pos                   _UINT32_(25)                                         /* (MCAN_TXEFS) Tx Event FIFO Element Lost Position */
#define MCAN_TXEFS_TEFL_Msk                   (_UINT32_(0x1) << MCAN_TXEFS_TEFL_Pos)               /* (MCAN_TXEFS) Tx Event FIFO Element Lost Mask */
#define MCAN_TXEFS_TEFL(value)                (MCAN_TXEFS_TEFL_Msk & (_UINT32_(value) << MCAN_TXEFS_TEFL_Pos)) /* Assigment of value for TEFL in the MCAN_TXEFS register */
#define MCAN_TXEFS_Msk                        _UINT32_(0x031F1F3F)                                 /* (MCAN_TXEFS) Register Mask  */


/* -------- MCAN_TXEFA : (MCAN Offset: 0xF8) (R/W 32) Transmit Event FIFO Acknowledge Register -------- */
#define MCAN_TXEFA_EFAI_Pos                   _UINT32_(0)                                          /* (MCAN_TXEFA) Event FIFO Acknowledge Index Position */
#define MCAN_TXEFA_EFAI_Msk                   (_UINT32_(0x1F) << MCAN_TXEFA_EFAI_Pos)              /* (MCAN_TXEFA) Event FIFO Acknowledge Index Mask */
#define MCAN_TXEFA_EFAI(value)                (MCAN_TXEFA_EFAI_Msk & (_UINT32_(value) << MCAN_TXEFA_EFAI_Pos)) /* Assigment of value for EFAI in the MCAN_TXEFA register */
#define MCAN_TXEFA_Msk                        _UINT32_(0x0000001F)                                 /* (MCAN_TXEFA) Register Mask  */


/** \brief MCAN register offsets definitions */
#define MCAN_RXBE_0_REG_OFST           _UINT32_(0x00)      /* (MCAN_RXBE_0) Rx Buffer Element 0 Offset */
#define MCAN_RXBE_1_REG_OFST           _UINT32_(0x04)      /* (MCAN_RXBE_1) Rx Buffer Element 1 Offset */
#define MCAN_RXBE_DATA_REG_OFST        _UINT32_(0x08)      /* (MCAN_RXBE_DATA) Rx Buffer Element Data Offset */
#define MCAN_RXF0E_0_REG_OFST          _UINT32_(0x00)      /* (MCAN_RXF0E_0) Rx FIFO 0 Element 0 Offset */
#define MCAN_RXF0E_1_REG_OFST          _UINT32_(0x04)      /* (MCAN_RXF0E_1) Rx FIFO 0 Element 1 Offset */
#define MCAN_RXF0E_DATA_REG_OFST       _UINT32_(0x08)      /* (MCAN_RXF0E_DATA) Rx FIFO 0 Element Data Offset */
#define MCAN_RXF1E_0_REG_OFST          _UINT32_(0x00)      /* (MCAN_RXF1E_0) Rx FIFO 1 Element 0 Offset */
#define MCAN_RXF1E_1_REG_OFST          _UINT32_(0x04)      /* (MCAN_RXF1E_1) Rx FIFO 1 Element 1 Offset */
#define MCAN_RXF1E_DATA_REG_OFST       _UINT32_(0x08)      /* (MCAN_RXF1E_DATA) Rx FIFO 1 Element Data Offset */
#define MCAN_TXBE_0_REG_OFST           _UINT32_(0x00)      /* (MCAN_TXBE_0) Tx Buffer Element 0 Offset */
#define MCAN_TXBE_1_REG_OFST           _UINT32_(0x04)      /* (MCAN_TXBE_1) Tx Buffer Element 1 Offset */
#define MCAN_TXBE_DATA_REG_OFST        _UINT32_(0x08)      /* (MCAN_TXBE_DATA) Tx Buffer Element Data Offset */
#define MCAN_TXEFE_0_REG_OFST          _UINT32_(0x00)      /* (MCAN_TXEFE_0) Tx Event FIFO Element 0 Offset */
#define MCAN_TXEFE_1_REG_OFST          _UINT32_(0x04)      /* (MCAN_TXEFE_1) Tx Event FIFO Element 1 Offset */
#define MCAN_SIDFE_0_REG_OFST          _UINT32_(0x00)      /* (MCAN_SIDFE_0) Standard Message ID Filter Element 0 Offset */
#define MCAN_XIDFE_0_REG_OFST          _UINT32_(0x00)      /* (MCAN_XIDFE_0) Extended Message ID Filter Element 0 Offset */
#define MCAN_XIDFE_1_REG_OFST          _UINT32_(0x04)      /* (MCAN_XIDFE_1) Extended Message ID Filter Element 1 Offset */
#define MCAN_CREL_REG_OFST             _UINT32_(0x00)      /* (MCAN_CREL) Core Release Register Offset */
#define MCAN_ENDN_REG_OFST             _UINT32_(0x04)      /* (MCAN_ENDN) Endian Register Offset */
#define MCAN_CUST_REG_OFST             _UINT32_(0x08)      /* (MCAN_CUST) Customer Register Offset */
#define MCAN_DBTP_REG_OFST             _UINT32_(0x0C)      /* (MCAN_DBTP) Data Bit Timing and Prescaler Register Offset */
#define MCAN_TEST_REG_OFST             _UINT32_(0x10)      /* (MCAN_TEST) Test Register Offset */
#define MCAN_RWD_REG_OFST              _UINT32_(0x14)      /* (MCAN_RWD) RAM Watchdog Register Offset */
#define MCAN_CCCR_REG_OFST             _UINT32_(0x18)      /* (MCAN_CCCR) CC Control Register Offset */
#define MCAN_NBTP_REG_OFST             _UINT32_(0x1C)      /* (MCAN_NBTP) Nominal Bit Timing and Prescaler Register Offset */
#define MCAN_TSCC_REG_OFST             _UINT32_(0x20)      /* (MCAN_TSCC) Timestamp Counter Configuration Register Offset */
#define MCAN_TSCV_REG_OFST             _UINT32_(0x24)      /* (MCAN_TSCV) Timestamp Counter Value Register Offset */
#define MCAN_TOCC_REG_OFST             _UINT32_(0x28)      /* (MCAN_TOCC) Timeout Counter Configuration Register Offset */
#define MCAN_TOCV_REG_OFST             _UINT32_(0x2C)      /* (MCAN_TOCV) Timeout Counter Value Register Offset */
#define MCAN_ECR_REG_OFST              _UINT32_(0x40)      /* (MCAN_ECR) Error Counter Register Offset */
#define MCAN_PSR_REG_OFST              _UINT32_(0x44)      /* (MCAN_PSR) Protocol Status Register Offset */
#define MCAN_TDCR_REG_OFST             _UINT32_(0x48)      /* (MCAN_TDCR) Transmit Delay Compensation Register Offset */
#define MCAN_IR_REG_OFST               _UINT32_(0x50)      /* (MCAN_IR) Interrupt Register Offset */
#define MCAN_IE_REG_OFST               _UINT32_(0x54)      /* (MCAN_IE) Interrupt Enable Register Offset */
#define MCAN_ILS_REG_OFST              _UINT32_(0x58)      /* (MCAN_ILS) Interrupt Line Select Register Offset */
#define MCAN_ILE_REG_OFST              _UINT32_(0x5C)      /* (MCAN_ILE) Interrupt Line Enable Register Offset */
#define MCAN_GFC_REG_OFST              _UINT32_(0x80)      /* (MCAN_GFC) Global Filter Configuration Register Offset */
#define MCAN_SIDFC_REG_OFST            _UINT32_(0x84)      /* (MCAN_SIDFC) Standard ID Filter Configuration Register Offset */
#define MCAN_XIDFC_REG_OFST            _UINT32_(0x88)      /* (MCAN_XIDFC) Extended ID Filter Configuration Register Offset */
#define MCAN_XIDAM_REG_OFST            _UINT32_(0x90)      /* (MCAN_XIDAM) Extended ID AND Mask Register Offset */
#define MCAN_HPMS_REG_OFST             _UINT32_(0x94)      /* (MCAN_HPMS) High Priority Message Status Register Offset */
#define MCAN_NDAT1_REG_OFST            _UINT32_(0x98)      /* (MCAN_NDAT1) New Data 1 Register Offset */
#define MCAN_NDAT2_REG_OFST            _UINT32_(0x9C)      /* (MCAN_NDAT2) New Data 2 Register Offset */
#define MCAN_RXF0C_REG_OFST            _UINT32_(0xA0)      /* (MCAN_RXF0C) Receive FIFO 0 Configuration Register Offset */
#define MCAN_RXF0S_REG_OFST            _UINT32_(0xA4)      /* (MCAN_RXF0S) Receive FIFO 0 Status Register Offset */
#define MCAN_RXF0A_REG_OFST            _UINT32_(0xA8)      /* (MCAN_RXF0A) Receive FIFO 0 Acknowledge Register Offset */
#define MCAN_RXBC_REG_OFST             _UINT32_(0xAC)      /* (MCAN_RXBC) Receive Rx Buffer Configuration Register Offset */
#define MCAN_RXF1C_REG_OFST            _UINT32_(0xB0)      /* (MCAN_RXF1C) Receive FIFO 1 Configuration Register Offset */
#define MCAN_RXF1S_REG_OFST            _UINT32_(0xB4)      /* (MCAN_RXF1S) Receive FIFO 1 Status Register Offset */
#define MCAN_RXF1A_REG_OFST            _UINT32_(0xB8)      /* (MCAN_RXF1A) Receive FIFO 1 Acknowledge Register Offset */
#define MCAN_RXESC_REG_OFST            _UINT32_(0xBC)      /* (MCAN_RXESC) Receive Buffer / FIFO Element Size Configuration Register Offset */
#define MCAN_TXBC_REG_OFST             _UINT32_(0xC0)      /* (MCAN_TXBC) Transmit Buffer Configuration Register Offset */
#define MCAN_TXFQS_REG_OFST            _UINT32_(0xC4)      /* (MCAN_TXFQS) Transmit FIFO/Queue Status Register Offset */
#define MCAN_TXESC_REG_OFST            _UINT32_(0xC8)      /* (MCAN_TXESC) Transmit Buffer Element Size Configuration Register Offset */
#define MCAN_TXBRP_REG_OFST            _UINT32_(0xCC)      /* (MCAN_TXBRP) Transmit Buffer Request Pending Register Offset */
#define MCAN_TXBAR_REG_OFST            _UINT32_(0xD0)      /* (MCAN_TXBAR) Transmit Buffer Add Request Register Offset */
#define MCAN_TXBCR_REG_OFST            _UINT32_(0xD4)      /* (MCAN_TXBCR) Transmit Buffer Cancellation Request Register Offset */
#define MCAN_TXBTO_REG_OFST            _UINT32_(0xD8)      /* (MCAN_TXBTO) Transmit Buffer Transmission Occurred Register Offset */
#define MCAN_TXBCF_REG_OFST            _UINT32_(0xDC)      /* (MCAN_TXBCF) Transmit Buffer Cancellation Finished Register Offset */
#define MCAN_TXBTIE_REG_OFST           _UINT32_(0xE0)      /* (MCAN_TXBTIE) Transmit Buffer Transmission Interrupt Enable Register Offset */
#define MCAN_TXBCIE_REG_OFST           _UINT32_(0xE4)      /* (MCAN_TXBCIE) Transmit Buffer Cancellation Finished Interrupt Enable Register Offset */
#define MCAN_TXEFC_REG_OFST            _UINT32_(0xF0)      /* (MCAN_TXEFC) Transmit Event FIFO Configuration Register Offset */
#define MCAN_TXEFS_REG_OFST            _UINT32_(0xF4)      /* (MCAN_TXEFS) Transmit Event FIFO Status Register Offset */
#define MCAN_TXEFA_REG_OFST            _UINT32_(0xF8)      /* (MCAN_TXEFA) Transmit Event FIFO Acknowledge Register Offset */

#if !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief MCAN_RXBE register API structure */
typedef struct
{  /* Rx Buffer Element */
  __IO  uint32_t                       MCAN_RXBE_0;        /**< Offset: 0x00 (R/W  32) Rx Buffer Element 0 */
  __IO  uint32_t                       MCAN_RXBE_1;        /**< Offset: 0x04 (R/W  32) Rx Buffer Element 1 */
  __IO  uint32_t                       MCAN_RXBE_DATA;     /**< Offset: 0x08 (R/W  32) Rx Buffer Element Data */
} mcan_rxbe_registers_t
#ifdef __GNUC__
  __attribute__ ((aligned (4)))
#endif
;

/** \brief MCAN_RXF0E register API structure */
typedef struct
{  /* Rx FIFO 0 Element */
  __IO  uint32_t                       MCAN_RXF0E_0;       /**< Offset: 0x00 (R/W  32) Rx FIFO 0 Element 0 */
  __IO  uint32_t                       MCAN_RXF0E_1;       /**< Offset: 0x04 (R/W  32) Rx FIFO 0 Element 1 */
  __IO  uint32_t                       MCAN_RXF0E_DATA;    /**< Offset: 0x08 (R/W  32) Rx FIFO 0 Element Data */
} mcan_rxf0e_registers_t
#ifdef __GNUC__
  __attribute__ ((aligned (4)))
#endif
;

/** \brief MCAN_RXF1E register API structure */
typedef struct
{  /* Rx FIFO 1 Element */
  __IO  uint32_t                       MCAN_RXF1E_0;       /**< Offset: 0x00 (R/W  32) Rx FIFO 1 Element 0 */
  __IO  uint32_t                       MCAN_RXF1E_1;       /**< Offset: 0x04 (R/W  32) Rx FIFO 1 Element 1 */
  __IO  uint32_t                       MCAN_RXF1E_DATA;    /**< Offset: 0x08 (R/W  32) Rx FIFO 1 Element Data */
} mcan_rxf1e_registers_t
#ifdef __GNUC__
  __attribute__ ((aligned (4)))
#endif
;

/** \brief MCAN_TXBE register API structure */
typedef struct
{  /* Tx Buffer Element */
  __IO  uint32_t                       MCAN_TXBE_0;        /**< Offset: 0x00 (R/W  32) Tx Buffer Element 0 */
  __IO  uint32_t                       MCAN_TXBE_1;        /**< Offset: 0x04 (R/W  32) Tx Buffer Element 1 */
  __IO  uint32_t                       MCAN_TXBE_DATA;     /**< Offset: 0x08 (R/W  32) Tx Buffer Element Data */
} mcan_txbe_registers_t
#ifdef __GNUC__
  __attribute__ ((aligned (4)))
#endif
;

/** \brief MCAN_TXEFE register API structure */
typedef struct
{  /* Tx Event FIFO Element */
  __IO  uint32_t                       MCAN_TXEFE_0;       /**< Offset: 0x00 (R/W  32) Tx Event FIFO Element 0 */
  __IO  uint32_t                       MCAN_TXEFE_1;       /**< Offset: 0x04 (R/W  32) Tx Event FIFO Element 1 */
} mcan_txefe_registers_t
#ifdef __GNUC__
  __attribute__ ((aligned (4)))
#endif
;

/** \brief MCAN_SIDFE register API structure */
typedef struct
{  /* Standard Message ID Filter Element */
  __IO  uint32_t                       MCAN_SIDFE_0;       /**< Offset: 0x00 (R/W  32) Standard Message ID Filter Element 0 */
} mcan_sidfe_registers_t
#ifdef __GNUC__
  __attribute__ ((aligned (4)))
#endif
;

/** \brief MCAN_XIDFE register API structure */
typedef struct
{  /* Extended Message ID Filter Element */
  __IO  uint32_t                       MCAN_XIDFE_0;       /**< Offset: 0x00 (R/W  32) Extended Message ID Filter Element 0 */
  __IO  uint32_t                       MCAN_XIDFE_1;       /**< Offset: 0x04 (R/W  32) Extended Message ID Filter Element 1 */
} mcan_xidfe_registers_t
#ifdef __GNUC__
  __attribute__ ((aligned (4)))
#endif
;

/** \brief MCAN register API structure */
typedef struct
{
  __I   uint32_t                       MCAN_CREL;          /**< Offset: 0x00 (R/   32) Core Release Register */
  __I   uint32_t                       MCAN_ENDN;          /**< Offset: 0x04 (R/   32) Endian Register */
  __IO  uint32_t                       MCAN_CUST;          /**< Offset: 0x08 (R/W  32) Customer Register */
  __IO  uint32_t                       MCAN_DBTP;          /**< Offset: 0x0C (R/W  32) Data Bit Timing and Prescaler Register */
  __IO  uint32_t                       MCAN_TEST;          /**< Offset: 0x10 (R/W  32) Test Register */
  __IO  uint32_t                       MCAN_RWD;           /**< Offset: 0x14 (R/W  32) RAM Watchdog Register */
  __IO  uint32_t                       MCAN_CCCR;          /**< Offset: 0x18 (R/W  32) CC Control Register */
  __IO  uint32_t                       MCAN_NBTP;          /**< Offset: 0x1C (R/W  32) Nominal Bit Timing and Prescaler Register */
  __IO  uint32_t                       MCAN_TSCC;          /**< Offset: 0x20 (R/W  32) Timestamp Counter Configuration Register */
  __IO  uint32_t                       MCAN_TSCV;          /**< Offset: 0x24 (R/W  32) Timestamp Counter Value Register */
  __IO  uint32_t                       MCAN_TOCC;          /**< Offset: 0x28 (R/W  32) Timeout Counter Configuration Register */
  __IO  uint32_t                       MCAN_TOCV;          /**< Offset: 0x2C (R/W  32) Timeout Counter Value Register */
  __I   uint8_t                        Reserved1[0x10];
  __I   uint32_t                       MCAN_ECR;           /**< Offset: 0x40 (R/   32) Error Counter Register */
  __I   uint32_t                       MCAN_PSR;           /**< Offset: 0x44 (R/   32) Protocol Status Register */
  __IO  uint32_t                       MCAN_TDCR;          /**< Offset: 0x48 (R/W  32) Transmit Delay Compensation Register */
  __I   uint8_t                        Reserved2[0x04];
  __IO  uint32_t                       MCAN_IR;            /**< Offset: 0x50 (R/W  32) Interrupt Register */
  __IO  uint32_t                       MCAN_IE;            /**< Offset: 0x54 (R/W  32) Interrupt Enable Register */
  __IO  uint32_t                       MCAN_ILS;           /**< Offset: 0x58 (R/W  32) Interrupt Line Select Register */
  __IO  uint32_t                       MCAN_ILE;           /**< Offset: 0x5C (R/W  32) Interrupt Line Enable Register */
  __I   uint8_t                        Reserved3[0x20];
  __IO  uint32_t                       MCAN_GFC;           /**< Offset: 0x80 (R/W  32) Global Filter Configuration Register */
  __IO  uint32_t                       MCAN_SIDFC;         /**< Offset: 0x84 (R/W  32) Standard ID Filter Configuration Register */
  __IO  uint32_t                       MCAN_XIDFC;         /**< Offset: 0x88 (R/W  32) Extended ID Filter Configuration Register */
  __I   uint8_t                        Reserved4[0x04];
  __IO  uint32_t                       MCAN_XIDAM;         /**< Offset: 0x90 (R/W  32) Extended ID AND Mask Register */
  __I   uint32_t                       MCAN_HPMS;          /**< Offset: 0x94 (R/   32) High Priority Message Status Register */
  __IO  uint32_t                       MCAN_NDAT1;         /**< Offset: 0x98 (R/W  32) New Data 1 Register */
  __IO  uint32_t                       MCAN_NDAT2;         /**< Offset: 0x9C (R/W  32) New Data 2 Register */
  __IO  uint32_t                       MCAN_RXF0C;         /**< Offset: 0xA0 (R/W  32) Receive FIFO 0 Configuration Register */
  __I   uint32_t                       MCAN_RXF0S;         /**< Offset: 0xA4 (R/   32) Receive FIFO 0 Status Register */
  __IO  uint32_t                       MCAN_RXF0A;         /**< Offset: 0xA8 (R/W  32) Receive FIFO 0 Acknowledge Register */
  __IO  uint32_t                       MCAN_RXBC;          /**< Offset: 0xAC (R/W  32) Receive Rx Buffer Configuration Register */
  __IO  uint32_t                       MCAN_RXF1C;         /**< Offset: 0xB0 (R/W  32) Receive FIFO 1 Configuration Register */
  __I   uint32_t                       MCAN_RXF1S;         /**< Offset: 0xB4 (R/   32) Receive FIFO 1 Status Register */
  __IO  uint32_t                       MCAN_RXF1A;         /**< Offset: 0xB8 (R/W  32) Receive FIFO 1 Acknowledge Register */
  __IO  uint32_t                       MCAN_RXESC;         /**< Offset: 0xBC (R/W  32) Receive Buffer / FIFO Element Size Configuration Register */
  __IO  uint32_t                       MCAN_TXBC;          /**< Offset: 0xC0 (R/W  32) Transmit Buffer Configuration Register */
  __I   uint32_t                       MCAN_TXFQS;         /**< Offset: 0xC4 (R/   32) Transmit FIFO/Queue Status Register */
  __IO  uint32_t                       MCAN_TXESC;         /**< Offset: 0xC8 (R/W  32) Transmit Buffer Element Size Configuration Register */
  __I   uint32_t                       MCAN_TXBRP;         /**< Offset: 0xCC (R/   32) Transmit Buffer Request Pending Register */
  __IO  uint32_t                       MCAN_TXBAR;         /**< Offset: 0xD0 (R/W  32) Transmit Buffer Add Request Register */
  __IO  uint32_t                       MCAN_TXBCR;         /**< Offset: 0xD4 (R/W  32) Transmit Buffer Cancellation Request Register */
  __I   uint32_t                       MCAN_TXBTO;         /**< Offset: 0xD8 (R/   32) Transmit Buffer Transmission Occurred Register */
  __I   uint32_t                       MCAN_TXBCF;         /**< Offset: 0xDC (R/   32) Transmit Buffer Cancellation Finished Register */
  __IO  uint32_t                       MCAN_TXBTIE;        /**< Offset: 0xE0 (R/W  32) Transmit Buffer Transmission Interrupt Enable Register */
  __IO  uint32_t                       MCAN_TXBCIE;        /**< Offset: 0xE4 (R/W  32) Transmit Buffer Cancellation Finished Interrupt Enable Register */
  __I   uint8_t                        Reserved5[0x08];
  __IO  uint32_t                       MCAN_TXEFC;         /**< Offset: 0xF0 (R/W  32) Transmit Event FIFO Configuration Register */
  __I   uint32_t                       MCAN_TXEFS;         /**< Offset: 0xF4 (R/   32) Transmit Event FIFO Status Register */
  __IO  uint32_t                       MCAN_TXEFA;         /**< Offset: 0xF8 (R/W  32) Transmit Event FIFO Acknowledge Register */
} mcan_registers_t;


#endif /* !(defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__)) */
#endif /* _SAMA5D_MCAN_COMPONENT_H_ */
