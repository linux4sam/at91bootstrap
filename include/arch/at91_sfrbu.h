/*
 * Copyright (C) 2016 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __AT91_SFRBU_H__
#define __AT91_SFRBU_H__

/*
 * Register Offset
 */
#define SFRBU_DDRBUMCR	0x10	/* DDR BU Mode Control Register */

/*
 * Register Fields
 */

/*--- SFRBU_DDRMCR: (offset: 0x10) DDR BU Mode Control Register ---*/
#define AT91C_DDRBUMCR_BUMEN	0x01	/* Force DDR_DQ Input Buffer Always On */

#endif /* #ifndef __AT91_SFRBU_H__ */
