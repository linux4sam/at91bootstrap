// Copyright (C) 2013 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#include "common.h"
#include "hardware.h"
#include "arch/at91_pmc/pmc.h"
#include "pmc.h"
#include "arch/tz_matrix.h"
#include "debug.h"

#define SECURITY_TYPE_AS	1
#define SECURITY_TYPE_NS	2
#define	SECURITY_TYPE_PS	3

struct peri_security {
	unsigned int	peri_id;
	unsigned int	matrix_base;
	unsigned int	security_type;
};

static const struct peri_security peri_security_array[] = {
#ifdef CONFIG_SAMA5D4
	{
		.peri_id = AT91C_ID_FIQ,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_SYS,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_ARM,
		.matrix_base = AT91C_BASE_MATRIX64,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_PIT,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_WDT,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_PIOD,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_USART0,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_USART1,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_XDMAC0,
		.matrix_base = AT91C_BASE_MATRIX64,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_ICM,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_PKCC,
		.matrix_base = AT91C_BASE_MATRIX64,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_SCI,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_AES,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_AESB,
		.matrix_base = AT91C_BASE_MATRIX64,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_TDES,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_SHA,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_MPDDRC,
		.matrix_base = AT91C_BASE_MATRIX64,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_MATRIX1,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_MATRIX0,
		.matrix_base = AT91C_BASE_MATRIX64,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_VDEC,
		.matrix_base = AT91C_BASE_MATRIX64,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_SECUMOD,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_MSADCC,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_HSMC,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_PIOA,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_PIOB,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_PIOC,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_PIOE,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_UART0,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_UART1,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_USART2,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_USART3,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_USART4,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_TWI0,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_TWI1,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_TWI2,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_HSMCI0,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_HSMCI1,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_SPI0,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_SPI1,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_SPI2,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_TC0,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_TC1,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_TC2,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_PWM,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_ADC,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_DBGU,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_UHPHS,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_UDPHS,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_SSC0,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_SSC1,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_XDMAC1,
		.matrix_base = AT91C_BASE_MATRIX64,
		.security_type = SECURITY_TYPE_NS,
	},
	{
		.peri_id = AT91C_ID_LCDC,
		.matrix_base = AT91C_BASE_MATRIX64,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_ISI,
		.matrix_base = AT91C_BASE_MATRIX64,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_TRNG,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_GMAC,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_GMAC1,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_IRQ,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_NS,
	},
	{
		.peri_id = AT91C_ID_SFC,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_SECURAM,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_CTB,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_SMD,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_TWI3,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_PS,
	},
	{
		.peri_id = AT91C_ID_CATB,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_SFR,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_AIC,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_NS,
	},
	{
		.peri_id = AT91C_ID_SAIC,
		.matrix_base = AT91C_BASE_MATRIX32,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_L2CC,
		.matrix_base = AT91C_BASE_MATRIX64,
		.security_type = SECURITY_TYPE_AS,
	},
	{
		.peri_id = AT91C_ID_PMC,
		.matrix_base = AT91C_BASE_MATRIX64,
		.security_type = SECURITY_TYPE_AS,
	},
#endif /* CONFIG_SAMA5D4 */
};


static inline void matrix_write(unsigned int base,
				unsigned int offset,
				const unsigned int value)
{
	writel(value, offset + base);
}

static inline unsigned int matrix_read(int base, unsigned int offset)
{
	return readl(offset + base);
}

void matrix_write_protect_enable(unsigned int matrix_base)
{
	matrix_write(matrix_base, MATRIX_WPMR,
		(MATRIX_WPMR_WPKEY_PASSWD | MATRIX_WPMR_WPEN_ENABLE));
}

void matrix_write_protect_disable(unsigned int matrix_base)
{
	matrix_write(matrix_base, MATRIX_WPMR, MATRIX_WPMR_WPKEY_PASSWD);
}

void matrix_configure_slave_security(unsigned int matrix_base,
				unsigned int slave,
				unsigned int srtop_setting,
				unsigned int srsplit_setting,
				unsigned int ssr_setting)
{
	matrix_write(matrix_base, MATRIX_SSR(slave), ssr_setting);
	matrix_write(matrix_base, MATRIX_SRTSR(slave), srtop_setting);
	matrix_write(matrix_base, MATRIX_SASSR(slave), srsplit_setting);
}

void matrix_read_slave_security(unsigned int matrix_base, unsigned int nslaves)
{
	unsigned int i;

	dbg_very_loud("\n\nRead Slave security for MATRIX at = %x:\n",
		      matrix_base);

	for (i = 0; i < nslaves; i++)
		dbg_very_loud("MATRIX_SRTSR%d: %x, MATRIX_SASSR%d: %x, MATRIX_SSR%d: %x\n",
			      i, matrix_read(matrix_base, MATRIX_SRTSR(i)),
			      i, matrix_read(matrix_base, MATRIX_SASSR(i)),
			      i, matrix_read(matrix_base, MATRIX_SSR(i)));
}

void matrix_read_peripheral_security(unsigned int matrix_base)
{
	unsigned int i;

	dbg_very_loud("\n\nRead Peripheral security for MATRIX at = %x:\n",
		      matrix_base);

	for (i = 0; i < MATRIX_SPSELR_COUNT; i++)
		dbg_very_loud("MATRIX_SPSELR(%d): %x\n",
			      i, matrix_read(matrix_base, MATRIX_SPSELR(i)));
}

static struct peri_security *get_peri_security(unsigned int peri_id)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(peri_security_array); i++) {
		if (peri_id == peri_security_array[i].peri_id)
			break;
	}

	return ((i == ARRAY_SIZE(peri_security_array))) ?
			NULL : (struct peri_security *)&peri_security_array[i];
}

static int matrix_set_peri_security(unsigned int matrix_base, unsigned peri_id)
{
	unsigned int spselr;
	unsigned int idx;
	unsigned int bit;

	/* A base address of value zero is usually assigned to ROM. */
	if (!matrix_base)
		return -1;

	idx = peri_id / 32;
	if (idx > 3)
		return -1;

	bit = (0x01 << (peri_id % 32));

	spselr = matrix_read(matrix_base, MATRIX_SPSELR(idx));
	spselr |= bit;
	matrix_write(matrix_base, MATRIX_SPSELR(idx), spselr);

	return 0;
}

int matrix_configure_peri_security(unsigned int *peri_id, unsigned int size)
{
	struct peri_security *peripheral_sec;
	unsigned int i;
	int ret;

	if (!peri_id || !size)
		return -1;

	for (i = 0; i < size; i++) {
		peripheral_sec = get_peri_security(*(peri_id + i));
		if (peripheral_sec == NULL)
			return -1;

		if (peripheral_sec->security_type != SECURITY_TYPE_PS)
			return -1;

		ret = matrix_set_peri_security(peripheral_sec->matrix_base,
					       peripheral_sec->peri_id);
		if (ret)
			return -1;
	}

	return 0;
}

#ifdef CONFIG_SAMA5D4
/*
 * is_peripheral_secure - tell if the peripheral is in secure mode
 * @periph_id: the peripheral id that is checked
 *
 * Check security of a particular peripheral by providing its ID.
 * Note that a wrong preripheral ID leads to the "true" return code.
 */
int is_peripheral_secure(unsigned int periph_id)
{
	struct peri_security *peripheral_sec;
	unsigned int mask;

	if ((periph_id > AT91C_ID_FIQ) && (periph_id < AT91C_ID_COUNTS)) {
		/* special cases here */
		if ((periph_id == AT91C_ID_IRQ)
		 || (periph_id == AT91C_ID_AIC)
		 || (periph_id == AT91C_ID_XDMAC1))
			return 0;

		peripheral_sec = get_peri_security(periph_id);
		if (peripheral_sec == NULL)
			return -1;

		/* A base address of value zero is usually assigned to ROM. */
		if (!peripheral_sec->matrix_base)
			return -1;

		mask = 1 << (periph_id % 32);
		if (matrix_read(peripheral_sec->matrix_base,
				MATRIX_SPSELR(periph_id / 32)) & mask)
			return 0;

	}
	return 1;
}

int is_sys_clk_secure(unsigned int sys_mask)
{
	unsigned int periph_id = sys_mask_to_per_id(sys_mask);

	return is_peripheral_secure(periph_id);
}

int is_pck_clk_secure(unsigned int pck_mask)
{
	switch (pck_mask) {
	case AT91C_PMC_PCK0:
	case AT91C_PMC_PCK1:
	case AT91C_PMC_PCK2:
		return 0;
	default:
		return 1;
	}
}

int is_usb_hs_secure(void)
{
	return is_peripheral_secure(AT91C_ID_UHPHS)
		|| is_peripheral_secure(AT91C_ID_UDPHS);
}

int is_usb_host_secure(void)
{
	return is_peripheral_secure(AT91C_ID_UHPHS);
}

int is_switching_clock_forbiden(unsigned int periph_id, unsigned int is_on, unsigned int *silent)
{
	/* disable console clock : forbiden */
	if ((periph_id == AT91C_ID_USART3) && (is_on == 0)) {
		/* keep it silent */
		*silent = 1;
		return 1;
	} else {
		return 0;
	}
}
#endif /* CONFIG_SAMA5D4 */

#ifdef CONFIG_SAMA7G5

void matrix_configure_default_qos()
{
	unsigned int amp_mask = MATRIX_PRAS_M0PR_MASK | MATRIX_PRAS_M1PR_MASK |
		MATRIX_PRAS_M2PR_MASK | MATRIX_PRAS_M3PR_MASK |
		MATRIX_PRAS_M4PR_MASK | MATRIX_PRAS_M5PR_MASK |
		MATRIX_PRAS_M6PR_MASK | MATRIX_PRAS_M7PR_MASK;
	unsigned int bmp_mask = MATRIX_PRAS_M8PR_MASK | MATRIX_PRAS_M9PR_MASK |
		MATRIX_PRAS_M10PR_MASK | MATRIX_PRAS_M11PR_MASK |
		MATRIX_PRAS_M12PR_MASK | MATRIX_PRAS_M13PR_MASK |
		MATRIX_PRAS_M14PR_MASK;
	unsigned int amp_val = MATRIX_PRAS_M0PR(RESET_DEFAULT_MASTER_SQOS0) |
				MATRIX_PRAS_M1PR(RESET_DEFAULT_MASTER_SQOS1) |
				MATRIX_PRAS_M2PR(RESET_DEFAULT_MASTER_SQOS2) |
				MATRIX_PRAS_M3PR(RESET_DEFAULT_MASTER_SQOS3) |
				MATRIX_PRAS_M4PR(RESET_DEFAULT_MASTER_SQOS4) |
				MATRIX_PRAS_M5PR(RESET_DEFAULT_MASTER_SQOS5) |
				MATRIX_PRAS_M6PR(RESET_DEFAULT_MASTER_SQOS6) |
				MATRIX_PRAS_M7PR(RESET_DEFAULT_MASTER_SQOS7);
	unsigned int bmp_val = MATRIX_PRBS_M8PR (RESET_DEFAULT_MASTER_SQOS8 ) |
				MATRIX_PRBS_M9PR (RESET_DEFAULT_MASTER_SQOS9 ) |
				MATRIX_PRBS_M10PR(RESET_DEFAULT_MASTER_SQOS10) |
				MATRIX_PRBS_M11PR(RESET_DEFAULT_MASTER_SQOS11) |
				MATRIX_PRBS_M12PR(RESET_DEFAULT_MASTER_SQOS12) |
				MATRIX_PRBS_M13PR(RESET_DEFAULT_MASTER_SQOS13) |
				MATRIX_PRBS_M14PR(RESET_DEFAULT_MASTER_SQOS14) |
				MATRIX_PRBS_M15PR(RESET_DEFAULT_MASTER_SQOS15);
	unsigned int pras, prbs;

	/* clear the Master Priority fields */
	pras = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRAS0);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRAS0, pras & ~amp_mask);
	pras = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRAS1);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRAS1, pras & ~amp_mask);
	pras = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRAS2);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRAS2, pras & ~amp_mask);
	pras = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRAS3);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRAS3, pras & ~amp_mask);
	pras = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRAS4);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRAS4, pras & ~amp_mask);
	pras = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRAS5);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRAS5, pras & ~amp_mask);
	pras = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRAS6);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRAS6, pras & ~amp_mask);
	pras = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRAS7);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRAS7, pras & ~amp_mask);

	prbs = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRBS0);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRBS0, prbs & ~bmp_mask);
	prbs = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRBS1);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRBS1, prbs & ~bmp_mask);
	prbs = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRBS2);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRBS2, prbs & ~bmp_mask);
	prbs = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRBS3);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRBS3, prbs & ~bmp_mask);
	prbs = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRBS4);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRBS4, prbs & ~bmp_mask);
	prbs = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRBS5);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRBS5, prbs & ~bmp_mask);
	prbs = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRBS6);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRBS6, prbs & ~bmp_mask);
	prbs = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRBS7);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRBS7, prbs & ~bmp_mask);

	/* set the Master Priority fields */
	pras = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRAS0);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRAS0, pras | amp_val);
	pras = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRAS1);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRAS1, pras | amp_val);
	pras = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRAS2);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRAS2, pras | amp_val);
	pras = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRAS3);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRAS3, pras | amp_val);
	pras = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRAS4);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRAS4, pras | amp_val);
	pras = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRAS5);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRAS5, pras | amp_val);
	pras = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRAS6);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRAS6, pras | amp_val);
	pras = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRAS7);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRAS7, pras | amp_val);

	prbs = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRBS0);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRBS0, prbs | bmp_val);
	prbs = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRBS1);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRBS1, prbs | bmp_val);
	prbs = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRBS2);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRBS2, prbs | bmp_val);
	prbs = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRBS3);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRBS3, prbs | bmp_val);
	prbs = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRBS4);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRBS4, prbs | bmp_val);
	prbs = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRBS5);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRBS5, prbs | bmp_val);
	prbs = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRBS6);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRBS6, prbs | bmp_val);
	prbs = matrix_read(AT91C_BASE_MATRIX, MATRIX_PRBS7);
	matrix_write(AT91C_BASE_MATRIX, MATRIX_PRBS7, prbs | bmp_val);
}

#endif /* CONFIG_SAMA7G5 */
