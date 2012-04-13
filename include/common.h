#ifndef _COMMON_H
#define _COMMON_H

extern void delay(unsigned int count);
extern void udelay(unsigned long usec);

#ifndef NULL
#define	NULL	0
#endif

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#endif /* #ifdef _COMMON_H */
