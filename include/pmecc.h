/*
 * Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __PMECC_H__
#define __PMECC_H__

#include "nand.h"

#define TT_MAX			25

/* The PMECC descripter structure */
struct _PMECC_paramDesc_struct {
	unsigned int pageSize;
	unsigned int spareSize;
	unsigned int sectorSize;
	unsigned int errBitNbrCapability;
	unsigned int eccSizeByte;
	unsigned int eccStartAddress;
	unsigned int eccEndAddress;
	unsigned int version;

	unsigned int nandWR;
	unsigned int spareEna;
	unsigned int modeAuto;
	unsigned int clkCtrl;
	unsigned int interrupt;

	int tt;
	int mm;
	int nn;

	short *alpha_to;
	short *index_of;

	short partialSyn[100];
	short si[100];

	/* sigma table */
	short smu[TT_MAX + 2][2 * TT_MAX + 1];
	/* polynom order */
	short lmu[TT_MAX + 1];

};

extern int get_pmecc_bytes(unsigned int sector_size, unsigned int ecc_bits);
extern int choose_pmecc_info(struct nand_info *nand, struct nand_chip *chip);
extern int init_pmecc(struct nand_info *nand);
extern void pmecc_enable(void);
extern void pmecc_start_data_phase(void);
extern int pmecc_process(struct nand_info *nand, unsigned char *buffer);

#endif
