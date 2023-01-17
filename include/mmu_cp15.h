// Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#ifndef MMU_CP15_H_
#define MMU_CP15_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 *        Exported definitions
 *----------------------------------------------------------------------------*/

/* TTB descriptor type for Section descriptor */
#define TTB_TYPE_SECT              (2 << 0)

/* TTB Section Descriptor: Buffered/Non-Buffered (B) */
#define TTB_SECT_WRITE_THROUGH     (0 << 2)
#define TTB_SECT_WRITE_BACK        (1 << 2)

/* TTB Section Descriptor: Cacheable/Non-Cacheable (C) */
#define TTB_SECT_NON_CACHEABLE     (0 << 3)
#define TTB_SECT_CACHEABLE         (1 << 3)

#define TTB_SECT_STRONGLY_ORDERED  (TTB_SECT_NON_CACHEABLE | TTB_SECT_WRITE_THROUGH)
#define TTB_SECT_SHAREABLE_DEVICE  (TTB_SECT_NON_CACHEABLE | TTB_SECT_WRITE_BACK)
#define TTB_SECT_CACHEABLE_WT      (TTB_SECT_CACHEABLE | TTB_SECT_WRITE_THROUGH)
#define TTB_SECT_CACHEABLE_WB      (TTB_SECT_CACHEABLE | TTB_SECT_WRITE_BACK)

/* TTB Section Descriptor: Domain */
#define TTB_SECT_DOMAIN(x)         (((x) & 15) << 5)

#if defined(CONFIG_CORE_ARM926EJS)

/* TTB Section Descriptor: Should-Be-One (SBO) */
#define TTB_SECT_SBO               (1 << 4)

/* TTB Section Descriptor: Access Privilege (AP) */
#define TTB_SECT_AP_PRIV_ONLY      (1 << 10)
#define TTB_SECT_AP_NO_USER_WRITE  (2 << 10)
#define TTB_SECT_AP_FULL_ACCESS    (3 << 10)

#elif defined(CONFIG_CORE_CORTEX_A5)

/* TTB Section Descriptor: Execute/Execute-Never (XN) */
#define TTB_SECT_EXEC              (0 << 4)
#define TTB_SECT_EXEC_NEVER        (1 << 4)

/* TTB Section Descriptor: Access Privilege (AP) */
#define TTB_SECT_AP_PRIV_ONLY      ((0 << 15) | (1 << 10))
#define TTB_SECT_AP_NO_USER_WRITE  ((0 << 15) | (2 << 10))
#define TTB_SECT_AP_FULL_ACCESS    ((0 << 15) | (3 << 10))
#define TTB_SECT_AP_PRIV_READ_ONLY ((1 << 15) | (1 << 10))
#define TTB_SECT_AP_READ_ONLY      ((1 << 15) | (2 << 10))

#endif /* CONFIG_ARCH_* */

/* TTB Section Descriptor: Section Base Address */
#define TTB_SECT_ADDR(x)           ((x) & 0xFFF00000)

#endif  /* MMU_CP15_H_ */
