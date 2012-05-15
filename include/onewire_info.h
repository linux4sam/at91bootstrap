#ifndef _DS24XX_H_
#define _DS24XX_H_

#include "arch/at91_pio.h"

#define VENDOR_EMBEST		1
#define VENDOR_FLEX		2
#define VENDOR_RONETIX		3
#define VENDOR_COGENT		4

extern void one_wire_hw_init(void);
extern unsigned int get_cm_sn();
extern char get_cm_rev();
extern unsigned int get_cm_vendor();
extern unsigned int get_sys_sn();
extern unsigned int get_sys_rev();
extern void load_1wire_info();
#endif
