/*
 * Copyright (C) 2020 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __PUBL_H__
#define __PUBL_H__

void publ_init(void);
int publ_idone(void);
int publ_start(void);
int publ_train(void);

#ifdef CONFIG_BACKUP_MODE
int publ_bypass_zq_calibration(void);
int publ_override_zq_calibration(void);
int publ_prepare_train_corrupted_data_restore(unsigned int bl);
int publ_zq_recalibrate(void);
int publ_train_corrupted_data_restore(void);
#endif /* CONFIG_BACKUP_MODE */

#endif
