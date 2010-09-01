/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
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
 * ----------------------------------------------------------------------------
 */

#if defined(CONFIG_SDCARD) && !defined(CONFIG_SDCARD_HS)

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include "mci.h"
#include "part.h"
#include "dbgu.h"
#include "debug.h"
//------------------------------------------------------------------------------
//         Local constants
//------------------------------------------------------------------------------

/// Bit mask for status register errors.
#define STATUS_ERRORS (AT91C_MCI_UNRE  \
                       | AT91C_MCI_OVRE \
                       | AT91C_MCI_DTOE \
                       | AT91C_MCI_DCRCE \
                       | AT91C_MCI_RTOE \
                       | AT91C_MCI_RENDE \
                       | AT91C_MCI_RCRCE \
                       | AT91C_MCI_RDIRE \
                       | AT91C_MCI_RINDE)

/// MCI data timeout configuration with 1048576 MCK cycles between 2 data transfers.
#define DTOR_1MEGA_CYCLES           (AT91C_MCI_DTOCYC | AT91C_MCI_DTOMUL)

/// MCI MR: disable MCI Clock when FIFO is full
#ifndef AT91C_MCI_WRPROOF
#define AT91C_MCI_WRPROOF 0
#endif
#ifndef AT91C_MCI_RDPROOF
#define AT91C_MCI_RDPROOF 0
#endif

#define SDCARD_APP_OP_COND_CMD      (41 | AT91C_MCI_SPCMD_NONE  | AT91C_MCI_RSPTYP_48   | AT91C_MCI_TRCMD_NO )
#define MMC_SEND_OP_COND_CMD        (1  | AT91C_MCI_TRCMD_NO    | AT91C_MCI_SPCMD_NONE  | AT91C_MCI_RSPTYP_48 | AT91C_MCI_OPDCMD)

#define DISABLE    0            // Disable MCI interface
#define ENABLE     1            // Enable MCI interface

//------------------------------------------------------------------------------
//         Local macros
//------------------------------------------------------------------------------

/// Used to write in PMC registers.
#define WRITE_PMC(pPmc, regName, value)     (*(volatile unsigned int *)(pPmc + regName)) = (value)

/// Used to write in MCI registers.
#define WRITE_MCI(pMci, regName, value)     (*(volatile unsigned int *)(pMci + regName)) = (value)

/// Used to read from MCI registers.
#define READ_MCI(pMci, regName)             (*(volatile unsigned int *)(pMci + regName))

/// Enable MCI Peripheral
#define PERIPH_ENABLE(mciId)   WRITE_PMC(AT91C_BASE_PMC, PMC_PCER, (1 << mciId))
/// Disable MCI Peripheral
#define PERIPH_DISABLE(mciId)  WRITE_PMC(AT91C_BASE_PMC, PMC_PCDR, (1 << mciId))

/// Enable MCI
#define MCI_ENABLE(pMciHw)     WRITE_MCI(pMciHw, MCI_CR, AT91C_MCI_MCIEN)
/// Disable MCI
#define MCI_DISABLE(pMciHw)    WRITE_MCI(pMciHw, MCI_CR, AT91C_MCI_MCIDIS)
/// Reset MCI
#define MCI_RESET(pMciHw)      WRITE_MCI(pMciHw, MCI_CR, AT91C_MCI_SWRST)

//------------------------------------------------------------------------------
//         External functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//         Internal functions
//------------------------------------------------------------------------------
/*
//------------------------------------------------------------------------------
/// Reset MCI interface and disable it.
/// \param keepSettings Keep old register settings, including _MR, _SDCR, _DTOR
//------------------------------------------------------------------------------
static void MCI_Reset(AT91PS_MCI pMciHw, unsigned char keepSettings)
{
    if (keepSettings) {

        unsigned int mciMr, mciSdcr, mciDtor;

        mciMr = READ_MCI(pMciHw, MCI_MR);
        mciSdcr = READ_MCI(pMciHw, MCI_SDCR);
        mciDtor = READ_MCI(pMciHw, MCI_DTOR);

        WRITE_MCI(pMciHw, MCI_CR, AT91C_MCI_SWRST);

        WRITE_MCI(pMciHw, MCI_CR, AT91C_MCI_MCIDIS | AT91C_MCI_PWSDIS);
        WRITE_MCI(pMciHw, MCI_MR, mciMr);
        WRITE_MCI(pMciHw, MCI_SDCR, mciSdcr);
        WRITE_MCI(pMciHw, MCI_DTOR, mciDtor);
    }
    else {

        WRITE_MCI(pMciHw, MCI_CR, AT91C_MCI_SWRST);
        WRITE_MCI(pMciHw, MCI_CR, AT91C_MCI_MCIDIS | AT91C_MCI_PWSDIS);
    }
}
*/

//------------------------------------------------------------------------------
/// Delay some loop
//------------------------------------------------------------------------------
void Delay(volatile unsigned int loop);

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Enable/disable a MCI driver instance.
/// \param pMci  Pointer to a MCI driver instance.
/// \param enb  0 for disable MCI and 1 for enable MCI.
//------------------------------------------------------------------------------
void MCI_Enable(Mci * pMci, unsigned char enb)
{
    unsigned int pMciHw = pMci->pMciHw;

    // Set the Control Register: Enable/Disable MCI interface clock
    if (enb == DISABLE) {
        MCI_DISABLE(pMciHw);
    } else {
        MCI_ENABLE(pMciHw);
    }
}

//------------------------------------------------------------------------------
/// Initializes a MCI driver instance and the underlying peripheral.
/// \param pMci  Pointer to a MCI driver instance.
/// \param pMciHw  Pointer to a MCI peripheral.
/// \param mciId  MCI peripheral identifier.
/// \param mode  Slot and type of connected card.
//------------------------------------------------------------------------------
void MCI_Init(Mci * pMci,
              unsigned int pMciHw,
              unsigned char mciId, unsigned int mode, unsigned int bPolling)
{
#if !defined(OP_BOOTSTRAP_MCI_on) || defined(at91sam9g20) || defined(at91sam9g10) || defined(at91sam9263)
    unsigned short clkDiv;
#endif

    // Initialize the MCI driver structure
    pMci->pMciHw = pMciHw;
    pMci->mciId = mciId;
    pMci->mciMode = mode;
    pMci->bPolling = bPolling;
    pMci->semaphore = 1;
    pMci->pCommand = 0;

#if !defined(OP_BOOTSTRAP_MCI_on) || defined(at91sam9g20) || defined(at91sam9g10) || defined(at91sam9263)
    // Enable the MCI peripheral
    PERIPH_ENABLE(mciId);

    // Reset the MCI
    WRITE_MCI(pMciHw, MCI_CR, AT91C_MCI_SWRST);

    // Disable the MCI
    WRITE_MCI(pMciHw, MCI_CR, AT91C_MCI_MCIDIS | AT91C_MCI_PWSDIS);

    // Disable all the interrupts
    WRITE_MCI(pMciHw, MCI_IDR, 0xFFFFFFFF);

    // Set the Data Timeout Register
    WRITE_MCI(pMciHw, MCI_DTOR, DTOR_1MEGA_CYCLES);

    // Set the Mode Register: 400KHz for MCK = 48MHz (CLKDIV = 58)
    clkDiv = (MASTER_CLOCK / (MCI_INITIAL_SPEED * 2)) - 1;
    WRITE_MCI(pMciHw, MCI_MR, (clkDiv | (AT91C_MCI_PWSDIV & (0x7 << 8))));

    // Set the SDCard Register
    WRITE_MCI(pMciHw, MCI_SDCR, mode);

    // Enable the MCI and the Power Saving
    WRITE_MCI(pMciHw, MCI_CR, AT91C_MCI_MCIEN);

    // Disable the MCI peripheral clock.
    PERIPH_DISABLE(mciId);
#else
    // Assume ROM code initialize the MCI already
    //   TRACE_INFO("SD bootstrap not init mci!\n\r");
#endif
}

#if 0
//------------------------------------------------------------------------------
/// Get the  MCI CLKDIV in the MCI_MR register. The max. for MCI clock is
/// MCK/2 and corresponds to CLKDIV = 0
/// \param pMci     Pointer to the low level MCI driver.
/// \return The current speed used, 0 for fail.
//------------------------------------------------------------------------------
unsigned int MCI_GetSpeed(Mci * pMci, unsigned int *mciDiv)
{
    unsigned int pMciHw = pMci->pMciHw;

    unsigned int mciMr;

    // Get the Mode Register
    mciMr = READ_MCI(pMciHw, MCI_MR);
    mciMr &= AT91C_MCI_CLKDIV;
    if (mciDiv)
        *mciDiv = mciMr;
    return (MASTER_CLOCK / 2 / (mciMr + 1));
}
#endif

//------------------------------------------------------------------------------
/// Configure the  MCI CLKDIV in the MCI_MR register. The max. for MCI clock is
/// MCK/2 and corresponds to CLKDIV = 0
/// \param pMci  Pointer to the low level MCI driver.
/// \param mciSpeed  MCI clock speed in Hz.
/// \param mciLimit  MCI clock limit in Hz, if not limit, set mciLimit to zero.
/// \param mck       MCK to generate MCI Clock, in Hz
/// \return The actual speed used, 0 for fail.
//------------------------------------------------------------------------------
unsigned int MCI_SetSpeed(Mci * pMci,
                          unsigned int mciSpeed,
                          unsigned int mciLimit, unsigned int mck)
{
    unsigned int pMciHw = pMci->pMciHw;

    unsigned int mciMr;

    unsigned int clkdiv;

    unsigned int divLimit = 0;

    unsigned int comparevalue = 0;

    mciMr = READ_MCI(pMciHw, MCI_MR) & (~AT91C_MCI_CLKDIV);
//      dbg_print("pos2.4.2\r\n");

//      dbg_printnum("mciLimit:", mciLimit);

    // Multimedia Card Interface clock (MCCK or MCI_CK) is Master Clock (MCK)
    // divided by (2*(CLKDIV+1))
    // mciSpeed = MCK / (2*(CLKDIV+1))
    if (mciLimit) {

//        divLimit = (mck / 2 / mciLimit);
        divLimit = (mck / 2);
        divLimit = (divLimit / mciLimit);
//              dbg_printnum("mck1:", mck);
//        if ((mck / 2) % mciLimit) divLimit ++;

        comparevalue = (mck / 2);
        comparevalue = (comparevalue % mciLimit);

        if (comparevalue)
            divLimit++;
    }
//      dbg_printnum("mck:", mck);
    if (mciSpeed > 0) {
        /*
         * mciSpeed = 0x8000000;
         * clkdiv = mck/mciSpeed;
         */

//        clkdiv = (mck / 2 / mciSpeed);
        clkdiv = (mck / 2);
        clkdiv = (clkdiv / mciSpeed);

        if (mciLimit && clkdiv < divLimit)
            clkdiv = divLimit;
        if (clkdiv > 0)
            clkdiv -= 1;

    }

    else
        clkdiv = 0;

    // Actual MCI speed
//    mciSpeed = mck / 2 / (clkdiv + 1);
    mciSpeed = (mck / 2);
    mciSpeed = (mciSpeed / (clkdiv + 1));

    // Set the Data Timeout Register & Completion Timeout
    // Data timeout is 500ms, completion timeout 1s.
    //MCI_SetTimeout(pMciHw, mciSpeed / 2, mciSpeed);

    WRITE_MCI(pMciHw, MCI_MR, mciMr | clkdiv);
//      dbg_print("pos2.4.3\r\n");
    return (mciSpeed);
}

//------------------------------------------------------------------------------
/// Configure the MCI_CFG to enable the HS mode (MCI2 only)
/// \param pMci     Pointer to the low level MCI driver.
/// \param hsEnable 1 to enable, 0 to disable HS mode.
//------------------------------------------------------------------------------
void MCI_EnableHsMode(Mci * pMci, unsigned char hsEnable)
{
}

//------------------------------------------------------------------------------
/// Configure the  MCI SDCBUS in the MCI_SDCR register. Only two modes available
///
/// \param pMci  Pointer to the low level MCI driver.
/// \param busWidth  MCI bus width mode.
//------------------------------------------------------------------------------
void MCI_SetBusWidth(Mci * pMci, unsigned char busWidth)
{
    unsigned int pMciHw = pMci->pMciHw;

    unsigned int mciSdcr;

    mciSdcr = (READ_MCI(pMciHw, MCI_SDCR) & ~(AT91C_MCI_SCDBUS));

    WRITE_MCI(pMciHw, MCI_SDCR, mciSdcr | busWidth);
}

//------------------------------------------------------------------------------
/// Starts a MCI  transfer. This is a non blocking function. It will return
/// as soon as the transfer is started.
/// Return 0 if successful; otherwise returns MCI_ERROR_LOCK if the driver is
/// already in use.
/// \param pMci  Pointer to an MCI driver instance.
/// \param pCommand  Pointer to the command to execute.
//------------------------------------------------------------------------------
unsigned char MCI_SendCommand(Mci * pMci, MciCmd * pCommand)
{
    unsigned int pMciHw = pMci->pMciHw;

    unsigned int mciIer, mciMr;

    // Try to acquire the MCI semaphore
    if (pMci->semaphore == 0) {

        return MCI_ERROR_LOCK;
    }
    pMci->semaphore--;
    // TRACE_DEBUG("MCI_SendCommand %x %d\n\r", READ_MCI(pMciHw, MCI_SR), pCommand->cmd & 0x3f);

    // Command is now being executed
    pMci->pCommand = pCommand;
    pCommand->status = MCI_STATUS_PENDING;

    // Enable the MCI Peripheral clock
    WRITE_PMC(AT91C_BASE_PMC, PMC_PCER, (1 << pMci->mciId));

    // Disable transmitter and receiver
    WRITE_MCI(pMciHw, MCI_PTCR, AT91C_PDC_RXTDIS | AT91C_PDC_TXTDIS);

    mciMr = READ_MCI(pMciHw, MCI_MR) & (~(AT91C_MCI_WRPROOF
                                          | AT91C_MCI_RDPROOF
                                          | AT91C_MCI_BLKLEN
                                          | AT91C_MCI_PDCMODE));

    // Command with DATA stage
    if (pCommand->blockSize && pCommand->nbBlock) {
        // Enable PDC mode and set block size
        if (pCommand->tranType != MCI_CONTINUE_TRANSFER) {

            WRITE_MCI(pMciHw, MCI_MR, mciMr | AT91C_MCI_PDCMODE
                      | AT91C_MCI_RDPROOF
                      | AT91C_MCI_WRPROOF | ((pCommand->blockSize) << 16));
        }
        // Sanity check
        if (pCommand->nbBlock == 0)
            pCommand->nbBlock = 1;

        // DATA transfer from card to host
        if (pCommand->isRead) {
            //check whether this is a remapped address      
            if ((((unsigned int)(pCommand->pData)) & 0xFFF00000)) {
                WRITE_MCI(pMciHw, MCI_RPR, (unsigned int)(pCommand->pData));
            } else {
                WRITE_MCI(pMciHw, MCI_RPR,
                          (unsigned int)(pCommand->pData +
                                         CHIP_SRAM0_BASEADDR));
            }

            // Update the PDC counter
            if ((pCommand->blockSize & 0x3) != 0) {
                WRITE_MCI(pMciHw, MCI_RCR,
                          (pCommand->nbBlock * pCommand->blockSize) / 4 + 1);
            } else {
                WRITE_MCI(pMciHw, MCI_RCR,
                          (pCommand->nbBlock * pCommand->blockSize) / 4);
            }
            WRITE_MCI(pMciHw, MCI_RNCR, 0);
            WRITE_MCI(pMciHw, MCI_PTCR, AT91C_PDC_RXTEN);
            mciIer = AT91C_MCI_ENDRX | STATUS_ERRORS;
        }
        // DATA transfer from host to card
        else {
            //check whether this is a remapped address
            if ((((unsigned int)(pCommand->pData)) & 0xFFF00000)) {
                WRITE_MCI(pMciHw, MCI_TPR, (int)pCommand->pData);
            } else {
                WRITE_MCI(pMciHw, MCI_RPR,
                          (unsigned int)(pCommand->pData +
                                         CHIP_SRAM0_BASEADDR));
            }
            // Update the PDC counter
            if ((pCommand->blockSize & 0x3) != 0) {
                WRITE_MCI(pMciHw, MCI_TCR,
                          (pCommand->nbBlock * pCommand->blockSize) / 4 + 1);
            } else {
                WRITE_MCI(pMciHw, MCI_TCR,
                          (pCommand->nbBlock * pCommand->blockSize) / 4);
            }
            // MCI_BLKE notifies the end of Multiblock command
            mciIer = AT91C_MCI_ENDTX | STATUS_ERRORS;
        }
    }
    // Start an infinite block transfer (but no data in current command)
    else if (pCommand->dataTran) {
        // Set block size
        WRITE_MCI(pMciHw, MCI_MR, mciMr | AT91C_MCI_RDPROOF
                  | AT91C_MCI_WRPROOF | (pCommand->blockSize << 16));
        // Set data length: 0, no PDC operation
        mciIer = AT91C_MCI_CMDRDY | STATUS_ERRORS;
    }
    // No data transfer: stop at the end of the command
    else {
        WRITE_MCI(pMciHw, MCI_MR, mciMr);
        mciIer = AT91C_MCI_CMDRDY | STATUS_ERRORS;
    }
    // Enable MCI clock
    MCI_ENABLE(pMciHw);
    // Send the command
    if ((pCommand->tranType != MCI_CONTINUE_TRANSFER)
        || (pCommand->blockSize == 0)) {

        WRITE_MCI(pMciHw, MCI_ARGR, pCommand->arg);
        WRITE_MCI(pMciHw, MCI_CMDR, pCommand->cmd);
    }
    // In case of transmit, the PDC shall be enabled after sending the command
    if (pCommand->blockSize > 0) {
        if (!pCommand->isRead) {
            WRITE_MCI(pMciHw, MCI_PTCR, AT91C_PDC_TXTEN);
        }
    }
    // Ignore data error
    mciIer &= ~(AT91C_MCI_UNRE | AT91C_MCI_OVRE
                | AT91C_MCI_DTOE | AT91C_MCI_DCRCE);

    // Interrupt enable shall be done after PDC TXTEN and RXTEN
    WRITE_MCI(pMciHw, MCI_IER, mciIer);

    return 0;
}

//------------------------------------------------------------------------------
/// Check NOTBUSY and DTIP bits of status register on the given MCI driver.
/// Return value, 0 for bus ready, 1 for bus busy
/// \param pMci  Pointer to a MCI driver instance.
//------------------------------------------------------------------------------
#if 0
unsigned char MCI_CheckBusy(Mci * pMci)
{
    unsigned int pMciHw = pMci->pMciHw;

    unsigned int status;

    // Enable MCI clock
    PERIPH_ENABLE(pMci->mciId);
    MCI_ENABLE(pMciHw);

    status = READ_MCI(pMciHw, MCI_SR);
    // TRACE_DEBUG("status %x\n\r",status);

    if (((status & AT91C_MCI_NOTBUSY) != 0)
        && ((status & AT91C_MCI_DTIP) == 0)) {

        // Disable MCI clock
        MCI_DISABLE(pMciHw);
        PERIPH_DISABLE(pMci->mciId);

        return 0;
    } else {
        return 1;
    }
}
#endif
//------------------------------------------------------------------------------
/// Processes pending events on the given MCI driver.
/// \param pMci  Pointer to a MCI driver instance.
//------------------------------------------------------------------------------
void MCI_Handler(Mci * pMci)
{
    unsigned int pMciHw = pMci->pMciHw;

    MciCmd *pCommand = pMci->pCommand;

    unsigned int status, status0, mask;

    unsigned char i;

    // Read the status register
    status0 = READ_MCI(pMciHw, MCI_SR);
    mask = READ_MCI(pMciHw, MCI_IMR);
    status = status0 & mask;

    // Check if an error has occured
    if ((status & STATUS_ERRORS) != 0) {

        // Check error code
        if ((status & STATUS_ERRORS) == AT91C_MCI_RTOE) {

            pCommand->status = MCI_STATUS_NORESPONSE;
        }
        // if the command is SEND_OP_COND the CRC error flag is always present
        // (cf : R3 response)
        else if (((status & STATUS_ERRORS) != AT91C_MCI_RCRCE)
                 || ((pCommand->cmd != SDCARD_APP_OP_COND_CMD)
                     && (pCommand->cmd != MMC_SEND_OP_COND_CMD))) {

            pCommand->status = MCI_STATUS_ERROR;
        }
    }
    // Check if writing end
    if (((status & AT91C_MCI_ENDTX) != 0)
        || ((status & AT91C_MCI_TXBUFE) != 0)) {
        if ((status0 & AT91C_MCI_BLKE) == 0)
            WRITE_MCI(pMciHw, MCI_IER, AT91C_MCI_BLKE);
        else
            status |= AT91C_MCI_BLKE;
    }
    // Check if a transfer has been completed
    if (((status & AT91C_MCI_CMDRDY) != 0)
        || ((status & AT91C_MCI_ENDRX) != 0)
        || ((status & AT91C_MCI_RXBUFF) != 0)
        || ((status & AT91C_MCI_BLKE) != 0)
        || ((status & AT91C_MCI_RTOE) != 0)) {

        // Store the card response in the provided buffer
        if (pCommand->pResp) {
            unsigned char resSize;

            switch (pCommand->resType) {
            case 2:
                resSize = 4;
                break;

            case 1:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                resSize = 1;
                break;

            default:
                resSize = 0;
                break;
            }
            for (i = 0; i < resSize; i++) {

                pCommand->pResp[i] = READ_MCI(pMciHw, MCI_RSPR);

            }
        }

        Delay(1000);

        // If no RD proof, FIFO may have dummy bytes
        // Reset the MCI to clear these dummy data
#if (AT91C_MCI_RDPROOF == 0)
        if ((pCommand->cmd & AT91C_MCI_TRCMD_STOP) != 0) {
            unsigned int /*mciCr, */ mciSdcr, mciMr, mciDtor;

            mciMr = READ_MCI(pMciHw, MCI_MR);
            mciSdcr = READ_MCI(pMciHw, MCI_SDCR);
            mciDtor = READ_MCI(pMciHw, MCI_DTOR);
            WRITE_MCI(pMciHw, MCI_CR, AT91C_MCI_SWRST);
            WRITE_MCI(pMciHw, MCI_CR, AT91C_MCI_MCIDIS | AT91C_MCI_PWSDIS);
            WRITE_MCI(pMciHw, MCI_MR, mciMr);
            WRITE_MCI(pMciHw, MCI_SDCR, mciSdcr);
            WRITE_MCI(pMciHw, MCI_DTOR, mciDtor);
        }
#endif

        // Disable MCI
        MCI_DISABLE(pMciHw);

        // If no error occured, the transfer is successful
        if (pCommand->status == MCI_STATUS_PENDING) {
            pCommand->status = 0;
        }
#if 0
        if ((status & AT91C_MCI_CMDRDY) != 0)
            TRACE_DEBUG_WP(".");
        if ((status & AT91C_MCI_ENDRX) != 0)
            TRACE_DEBUG_WP("<");
        if ((status & AT91C_MCI_ENDTX) != 0)
            TRACE_DEBUG_WP("-");
        if ((status & AT91C_MCI_BLKE) != 0)
            TRACE_DEBUG_WP(">");
        TRACE_DEBUG_WP("\n\r");
#endif

        // Disable interrupts
        WRITE_MCI(pMciHw, MCI_IDR, 0xFFFFFFFF);

        // Disable peripheral
        PERIPH_DISABLE(pMci->mciId);

        // Release the semaphore
        pMci->semaphore++;

        // Invoke the callback associated with the current command (if any)
        if (pCommand->callback) {
            (pCommand->callback) (pCommand->status, pCommand);
        }
    }
}

//------------------------------------------------------------------------------
/// Returns 1 if the given MCI transfer is complete; otherwise returns 0.
/// \param pCommand  Pointer to a MciCmd instance.
//------------------------------------------------------------------------------
unsigned char MCI_IsTxComplete(Mci * pMci)
{
    MciCmd *pCommand = pMci->pCommand;

    if (pMci->bPolling == MCI_POLLING_MODE) {
        MCI_Handler(pMci);
    }

    if (pCommand->status != MCI_STATUS_PENDING) {
        if (pCommand->status != 0) {

        }
        return 1;
    } else {
        return 0;
    }
}

#endif
