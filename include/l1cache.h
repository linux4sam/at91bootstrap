// Copyright (C) 2022 Microchip Technology Inc. and its subsidiaries
//
// SPDX-License-Identifier: MIT

#ifndef L1CACHE_H_
#define L1CACHE_H_

/*
 * Functions related to L1 cache maintenance (I-Cache and D-Cache).
 */

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/**
 * \brief Invalidate all instruction cache.
 */
void icache_invalidate(void);

/**
 * \brief Enable instruction cache.
 */
void icache_enable(void);

/**
 * \brief Disable instruction cache.
 */
void icache_disable(void);

/**
 * \brief Enable data cache.
 */
void dcache_enable(void);

/**
 * \brief Disable the data cache.
 */
void dcache_disable(void);

/**
 * \brief Clean the data cache.
 */
void dcache_clean(void);

/**
 * \brief Invalidate the data cache.
 */
void dcache_invalidate(void);

#endif /* L1CACHE_H_ */
