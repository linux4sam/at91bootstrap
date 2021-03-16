/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2021, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "hardware.h"
#include "board.h"
#include "string.h"
#include "arch/at91_lcdc.h"
#include "debug.h"
#include "div.h"
#include "pmc.h"

//#define LCDC_RGBDEF 0x000000 // Background color, format is 0xRRGGBB
//#define LCDC_SCALE  4        // Up scaling step is 0.125 (1/8), 0 means no scaling
//#define LCDC_BL     255      // Back light, from 0 ~ 255

#define LCDC_DMA_ADDR TOP_OF_MEMORY
#define LCDC_BMP_ADDR (TOP_OF_MEMORY + sizeof(struct dma_desc))
#define LCDC_RGB_MODE LAYER_RGB_888_PACKED
#define LCDC_XPHIDEF  4
#define LCDC_YPHIDEF  4

#define BMP_LINE_ALIGN 4

struct dma_desc {
	u32 addr;
	u32 ctrl;
	u32 next;
	u32 reserved;
};

struct lcdc_desc {
	u16 width;     /**< Display image width */
	u16 height;    /**< Display image height */
	u16 framerate; /**< Frame rate in Hz */

	u16 timing_vfp; /**< Vertical front porch in number of lines */
	u16 timing_vbp; /**< Vertical back porch in number of lines */
	u16 timing_vpw; /**< Vertical pulse width in number of lines */
	u16 timing_hfp; /**< Horizontal front porch in LCDDOTCLK cycles */
	u16 timing_hbp; /**< Horizontal back porch in LCDDOTCLK cycles */
	u16 timing_hpw; /**< Horizontal pulse width in LCDDOTCLK cycles */

	u16 ovr_mode;
	u16 ovr_width;
	u16 ovr_height;
	u16 ovr_sc_width;
	u16 ovr_sc_height;
	u16 ovr_xpos;
	u16 ovr_ypos;
	u32 ovr_xstride;
	u32 ovr_pstride;
	struct dma_desc *ovr_dma;
	u8 *ovr_buf;

	struct bmp_desc *bmp;
};

struct bmp_desc {
	u8  bf_type[2];
	u32 bf_size;
	u16 bf_reserved1;
	u16 bf_reserver2;
	u32 bf_offbits;

	u32 bi_size;
	u32 bi_width;
	u32 bi_height;
	u16 bi_planes;
	u16 bi_bitcount;
	u32 bi_compression;
	u32 bi_sizeimage;
	u32 bi_xpelspermeter;
	u32 bi_ypelspermeter;
	u32 bi_clrused;
	u32 bi_clrimportant;
	u32 clut[];
} __attribute__ ((packed, aligned(1)));

static struct lcdc_desc lcdc = {
	.width       = BOARD_LCD_WIDTH,
	.height      = BOARD_LCD_HEIGHT,
	.framerate   = BOARD_LCD_FRAMERATE,
	.timing_vfp  = BOARD_LCD_TIMING_VFP,
	.timing_vbp  = BOARD_LCD_TIMING_VBP,
	.timing_vpw  = BOARD_LCD_TIMING_VPW,
	.timing_hfp  = BOARD_LCD_TIMING_HFP,
	.timing_hbp  = BOARD_LCD_TIMING_HBP,
	.timing_hpw  = BOARD_LCD_TIMING_HPW,

	.ovr_dma     = (struct dma_desc *)LCDC_DMA_ADDR,
	.bmp         = (struct bmp_desc *)(LCDC_BMP_ADDR),
};

static u32 heo_upscaling_xcoef[] = {
	0xf74949f7,
	0x00000000,
	0xf55f33fb,
	0x000000fe,
	0xf5701efe,
	0x000000ff,
	0xf87c0dff,
	0x00000000,
	0x00800000,
	0x00000000,
	0x0d7cf800,
	0x000000ff,
	0x1e70f5ff,
	0x000000fe,
	0x335ff5fe,
	0x000000fb,
};

static u32 heo_upscaling_ycoef[] = {
	0x00004040,
	0x00075920,
	0x00056f0c,
	0x00027b03,
	0x00008000,
	0x00037b02,
	0x000c6f05,
	0x00205907,
};

static inline unsigned int lcdc_get_base(void)
{
	return CONFIG_SYS_BASE_LCDC;
}

static unsigned int lcdc_readl(unsigned int reg)
{
	return readl(lcdc_get_base() + reg);
}

static void lcdc_writel(unsigned int reg, unsigned int value)
{
	writel(value, lcdc_get_base() + reg);
}

static void wait_for_clock_domain_sync(void)
{
	while (lcdc_readl(LCDC_SR) & LCDC_SR_SIPSTS);
}

static void set_phicoeff(u32 reg_base, const u32 *coeff_tab, u16 size)
{
	u32 i;

	for (i = 0; i < size; i++)
		lcdc_writel(reg_base + (i * 4), coeff_tab[i]);
}

static void set_clut(u32 reg_base, const u8 *clut, u16 size)
{
	u32 i;

	for (i = 0; i < size*4; i += 4)
		lcdc_writel(reg_base + i, clut[i] | clut[i+1]<<8 | clut[i+2]<<16); 
}

static u32 get_factor(u32 srcsize, u32 dstsize, u32 phidef)
{
	u32 factor, max_memsize;

	factor = div((256 * ((8 * (srcsize - 1)) - phidef)), (dstsize - 1));
	max_memsize = ((factor * (dstsize - 1)) + (256 * phidef)) / 2048;

	if (max_memsize > srcsize - 1)
		factor--;

	return factor;
}

static void lcdc_set_backlight(u8 level)
{
	u32 cfg = lcdc_readl(LCDC_CFG(6)) & ~LCDC_CFG6_PWMCVAL_MASK;
	lcdc_writel(LCDC_CFG(6), cfg | LCDC_CFG6_PWMCVAL(level));
}

static void lcdc_off(void)
{
	lcdc_writel(LCDC_DIS, LCDC_DIS_PWMDIS);
	while (lcdc_readl(LCDC_SR) & LCDC_SR_PWMSTS);

	lcdc_writel(LCDC_DIS, LCDC_DIS_DISPDIS);
	while (lcdc_readl(LCDC_SR) & LCDC_SR_DISPSTS);

	lcdc_writel(LCDC_DIS, LCDC_DIS_SYNCDIS);
	while (lcdc_readl(LCDC_SR) & LCDC_SR_LCDSTS);

	lcdc_writel(LCDC_DIS, LCDC_DIS_CLKDIS);
	while (lcdc_readl(LCDC_SR) & LCDC_SR_CLKSTS);
}

static void lcdc_on(void)
{
	u32 pixel_clock = lcdc.framerate;
	u32 lcd_clock = pmc_get_generic_clock(CONFIG_SYS_ID_LCDC);

	pixel_clock *= lcdc.timing_hpw + lcdc.timing_hbp +
		lcdc.width + lcdc.timing_hfp;
	pixel_clock *= lcdc.timing_vpw + lcdc.timing_vbp +
		lcdc.height + lcdc.timing_vfp; 

	wait_for_clock_domain_sync();
	lcdc_writel(LCDC_CFG(0), LCDC_CFG0_CLKDIV(div(lcd_clock, pixel_clock) - 2) |
				 LCDC_CFG0_CGDISPP | 
				 LCDC_CFG0_CGDISHEO |
				 LCDC_CFG0_CGDISBASE |
				 LCDC_CFG0_CLKPWMSEL);

	wait_for_clock_domain_sync();
	lcdc_writel(LCDC_CFG(1), LCDC_CFG1_VSPW(lcdc.timing_vpw - 1) |
				 LCDC_CFG1_HSPW(lcdc.timing_hpw - 1));

	wait_for_clock_domain_sync();
	lcdc_writel(LCDC_CFG(2), LCDC_CFG2_VBPW(lcdc.timing_vbp) |
				 LCDC_CFG2_VFPW(lcdc.timing_vfp - 1));

	wait_for_clock_domain_sync();
	lcdc_writel(LCDC_CFG(3), LCDC_CFG3_HBPW(lcdc.timing_hbp - 1) |
				 LCDC_CFG3_HFPW(lcdc.timing_hfp - 1));

	wait_for_clock_domain_sync();
	lcdc_writel(LCDC_CFG(4), LCDC_CFG4_RPF(lcdc.height - 1) |
				 LCDC_CFG4_PPL(lcdc.width - 1));

	wait_for_clock_domain_sync();
	lcdc_writel(LCDC_CFG(5), LCDC_CFG5_GUARDTIME(30) |
				 LCDC_CFG5_MODE_OUTPUT_24BPP |
				 LCDC_CFG5_DISPDLY |
				 LCDC_CFG5_VSPDLYS |
				 LCDC_CFG5_VSPOL |
				 LCDC_CFG5_HSPOL);

	wait_for_clock_domain_sync();
	lcdc_writel(LCDC_CFG(6), LCDC_CFG6_PWMCVAL(0) |
				 LCDC_CFG6_PWMPOL |
				 LCDC_CFG6_PWMPS(6));

	wait_for_clock_domain_sync();
	lcdc_writel(LCDC_EN, LCDC_EN_CLKEN);
	while (!(lcdc_readl(LCDC_SR) & LCDC_SR_CLKSTS));

	wait_for_clock_domain_sync();
	lcdc_writel(LCDC_EN, LCDC_EN_SYNCEN);
	while (!(lcdc_readl(LCDC_SR) & LCDC_SR_LCDSTS));

	wait_for_clock_domain_sync();
	lcdc_writel(LCDC_EN, LCDC_EN_DISPEN);
	while (!(lcdc_readl(LCDC_SR) & LCDC_SR_DISPSTS));

	wait_for_clock_domain_sync();
	lcdc_writel(LCDC_EN, LCDC_EN_PWMEN);
}

void lcdc_show_base(void)
{
	lcdc_writel(LCDC_BASECFG(1), LAYER_RGB_888_PACKED);
	lcdc_writel(LCDC_BASECFG(3), LAYER_RGB(LOGO_RGBDEF));
	lcdc_writel(LCDC_BASECHER, LAYER_UPDATE | LAYER_CH);
}

void lcdc_show_heo(void)
{
	/* Base configuration */
	lcdc_writel(LCDC_HEOCFG(0), LAYER_ROT);
	lcdc_writel(LCDC_HEOCFG(1), lcdc.ovr_mode);
	lcdc_writel(LCDC_HEOCFG(2), LAYER_POS(lcdc.ovr_xpos, lcdc.ovr_ypos));
	lcdc_writel(LCDC_HEOCFG(3), LAYER_SIZE(lcdc.ovr_sc_width, lcdc.ovr_sc_height)); 
	lcdc_writel(LCDC_HEOCFG(4), LAYER_SIZE(lcdc.ovr_width, lcdc.ovr_height));
	if (lcdc.ovr_xstride)
		lcdc_writel(LCDC_HEOCFG(5), LAYER_STRIDE(lcdc.ovr_xstride));
	if (lcdc.ovr_pstride)
		lcdc_writel(LCDC_HEOCFG(6), LAYER_STRIDE(lcdc.ovr_pstride));
	lcdc_writel(LCDC_HEOCFG(9), LAYER_RGB(LOGO_RGBDEF));

	/* Configure CULT if needed */
	if (lcdc.ovr_mode | LAYER_CLUT)
		set_clut(LCDC_HEOCLUT(0), (u8 *)lcdc.bmp->clut, 256);

	/* Configure scaler if needed */
	if (lcdc.ovr_width != lcdc.ovr_sc_width) {
		set_phicoeff(LCDC_HEOCFG(17), heo_upscaling_xcoef, sizeof(heo_upscaling_xcoef) / sizeof(u32));
		set_phicoeff(LCDC_HEOCFG(33), heo_upscaling_ycoef, sizeof(heo_upscaling_ycoef) / sizeof(u32));
		lcdc_writel(LCDC_HEOCFG(13), LAYER_SCAL | 
			(get_factor(lcdc.ovr_height, lcdc.ovr_sc_height, LCDC_YPHIDEF) << 16) | 
			(get_factor(lcdc.ovr_width, lcdc.ovr_sc_width, LCDC_XPHIDEF) << 0));
	}

	lcdc_writel(LCDC_HEOADDR, (u32)lcdc.ovr_buf);
	lcdc_writel(LCDC_HEOCTRL, LAYER_DFETCH);
	lcdc_writel(LCDC_HEONEXT, (u32)lcdc.ovr_dma);
	lcdc_writel(LCDC_HEOCFG(12), LAYER_GA(0xff) | LAYER_DMA | LAYER_OVR | LAYER_GAEN);

	lcdc_writel(LCDC_HEOCHER, LAYER_UPDATE | LAYER_CH);
}

void lcdc_init(void)
{
	/* Invalidate bmp struct buffer */
	lcdc.bmp->bf_type[0] = 0;
	lcdc.bmp->bf_type[1] = 0; 

	at91_lcdc_hw_init();
	lcdc_off();
	lcdc_on();
}

int lcdc_display(void)
{
	u8 pixel_bytes;
	u8 line_padding;

	if ((lcdc.bmp->bf_type[0] != 'B') || (lcdc.bmp->bf_type[1] != 'M')) {
		dbg_printf("ERROR: bmp file not found\n\r");
		return -1;
	}

	if (lcdc.bmp->bi_bitcount == 24) {
		lcdc.ovr_mode = LAYER_RGB_888_PACKED;
		pixel_bytes = 3;
	} else if (lcdc.bmp->bi_bitcount == 8) {
		lcdc.ovr_mode = LAYER_CLUT_8BPP | LAYER_CLUT;
		pixel_bytes = 1;
	} else {
		dbg_printf("ERROR: unsupported bmp format, bitcount=%d\n\r", lcdc.bmp->bi_bitcount);
		return -1;
	}
	line_padding = lcdc.bmp->bi_width & (BMP_LINE_ALIGN - 1); 
	if (line_padding)
		line_padding = BMP_LINE_ALIGN - line_padding;

	lcdc.ovr_buf    = (u8 *)(LCDC_BMP_ADDR + lcdc.bmp->bf_offbits);
	lcdc.ovr_width  = lcdc.bmp->bi_width;
	if (((int)lcdc.bmp->bi_height) > 0) {
		lcdc.ovr_height  = lcdc.bmp->bi_height;
		lcdc.ovr_xstride = -(lcdc.ovr_width * pixel_bytes * 2 + line_padding);
		lcdc.ovr_buf     += (lcdc.ovr_width * pixel_bytes + line_padding) * (lcdc.ovr_height - 1);
	} else {
		lcdc.ovr_height  = -lcdc.bmp->bi_height;
		lcdc.ovr_xstride = line_padding;
	}

	lcdc.ovr_sc_width  = (LOGO_SCALE == 0) ? lcdc.ovr_width : (lcdc.ovr_width * (8 + LOGO_SCALE) / 8);
	lcdc.ovr_sc_height = (LOGO_SCALE == 0) ? lcdc.ovr_height : (lcdc.ovr_height * (8 + LOGO_SCALE) / 8);
	lcdc.ovr_xpos      = (lcdc.ovr_sc_width >= lcdc.width) ? 0 : ((lcdc.width - lcdc.ovr_sc_width) / 2);
	lcdc.ovr_ypos      = (lcdc.ovr_sc_height >= lcdc.height) ? 0 : ((lcdc.height - lcdc.ovr_sc_height) / 2);

	lcdc.ovr_dma->addr = (u32)lcdc.ovr_buf;
	lcdc.ovr_dma->ctrl = LAYER_DFETCH;
	lcdc.ovr_dma->next = (u32)lcdc.ovr_dma;
	lcdc.ovr_dma->reserved = 0;

	lcdc_show_base();
	lcdc_show_heo();
	lcdc_set_backlight(LOGO_BL);

	return 0;
}
