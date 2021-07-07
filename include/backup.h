/*
 * Copyright (C) 2016 Microchip Technology Inc. and its subsidiaries
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef __BACKUP_H__
#define __BACKUP_H__

extern unsigned long backup_mode_resume(void);

#ifdef CONFIG_BACKUP_MODE
	int backup_resume(void);
#ifdef CONFIG_PUBL
	void backup_get_calibration_data(unsigned int *data, unsigned int len);
#else
	static inline void backup_get_calibration_data(unsigned int *data, unsigned int len) { }
#endif /* CONFIG_PUBL */
#else
	static inline int backup_resume(void) { return 0; }
	static inline void backup_get_calibration_data(unsigned int *data, unsigned int len) { }
#endif

#endif	/* #ifndef __BACKUP_H__ */

