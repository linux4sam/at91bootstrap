/* ******************************************************************* */
/* PMC Settings                                                        */
/*                                                                     */
/* The main oscillator is enabled as soon as possible in the c_startup */
/* and MCK is switched on the main oscillator.                         */
/* PLL initialization is done later in the hw_init() function          */
/* ******************************************************************* */
#define PLL_LOCK_TIMEOUT	1000000

#define PLLA_180MHz

#ifdef PLLA_200MHz
#define PLLA_SETTINGS	0x2060BF09
#define MASTER_CLOCK		(198656000/2)
#endif

#ifdef PLLA_180MHz
#define PLLA_SETTINGS	0x2125BF1E      /* 180MHz */
#define MASTER_CLOCK		(179999198/2)   /* 180MHz MCK=90MHz */
#endif

#ifdef PLLA_120MHz
//#define PLLA_SETTINGS 0x2125BF2d /* 120MHz */
//#define MASTER_CLOCK          (119999322) /* 120MHz MCK=60MHz*/
#define PLLA_SETTINGS	0x2125BF2d      /* 120MHz */
#define MASTER_CLOCK		(119999465/2)   /* 120MHz MCK=60MHz */
#endif

#if !defined(PLLA_180MHz) && !defined(PLLA_120MHz)
#error Define PLLA frequency
#endif
#define PLLB_SETTINGS	0x10483F0E

/* Switch MCK on PLLA output PCK = PLLA = 2 * MCK */
#define MCKR_SETTINGS	(AT91C_PMC_CSS_PLLA_CLK | AT91C_PMC_PRES_CLK | AT91C_PMC_MDIV_2)
