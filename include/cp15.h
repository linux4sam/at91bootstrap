// Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#ifndef CP15_H_
#define CP15_H_

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/* SCTLR: I - I-cache enable/disable
 * 0 = I-cache disabled
 * 1 = I-cache enabled
 */
#define CP15_SCTLR_I (1u << 12)

/* SCTLR: C - D-cache enable/disable
 * 0 = D-cache disabled
 * 1 = D-cache enabled
 */
#define CP15_SCTLR_C (1u << 2)

/* SCTLR: A - Alignment fault enable/disable
 * 0 = Data address alignment fault checking disabled
 * 1 = Data address alignment fault checking enabled
 */
#define CP15_SCTLR_A (1u << 1)

/* SCTLR: M - MMU enable/disable
 * 0 = disabled
 * 1 = enabled
 */
#define CP15_SCTLR_M (1u << 0)

/* ACTLR: EXCL - Exclusive L1/L2 cache control.
 * 0 = non-exclusive
 * 1 = exclusive
 */
#define CP15_ACTLR_EXCL (1u << 7)

/* No access: Any access generates a domain fault. */
#define CP15_DACR_NO_ACCESS(x) (0u << (2 * ((x) & 15)))

/* Client: Accesses are checked against the access permission bits in the
 * section or page descriptor. */
#define CP15_DACR_CLIENT_ACCESS(x) (1u << (2 * ((x) & 15)))

/* Manager: Accesses are not checked against the access permission bits so a
 * permission fault cannot be generated. */
#define CP15_DACR_MANAGER_ACCESS(x) (3u << (2 * ((x) & 15)))

/*------------------------------------------------------------------------------ */
/*         Exported functions */
/*------------------------------------------------------------------------------ */
unsigned int cp15_read_sctlr(void);
void cp15_write_sctlr(unsigned int value);
void cp15_write_ttbr0(unsigned int value);
void cp15_write_dacr(unsigned int value);
void cp15_icache_invalidate(void);
void cp15_dcache_invalidate_setway(unsigned int setway);
void cp15_dcache_clean_setway(unsigned int setway);
void cp15_dcache_invalidate_mva(unsigned int mva);

#endif /* CP15_H_ */
