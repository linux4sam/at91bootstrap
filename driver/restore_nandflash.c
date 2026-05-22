/*******************************************************************************
* Copyright (C) 2025 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

#include "bitops.h"
#include "fast_boot.h"
#include "nand.h"

#define PAGE_2K 2048
#define PAGE_4K 4096
#define PAGE_8K 8192

/* Bad-block table with 3 blocks for accessing header and bitmap */
#define BB_TABLE_SIZE 3

struct dev_data {
	struct nand_info *nand;

	unsigned int bb_table[BB_TABLE_SIZE];
	unsigned int block_start;
	unsigned int block_end;
};

static unsigned int bb_page(struct block_dev *dev, unsigned int page)
{
	struct dev_data *data = dev->priv;
	struct align_info *block = &dev->align;

	return (data->bb_table[page >> block->shift] << block->shift) +
	       (page & block->mask);
}

static int find_next(struct dev_data *data, unsigned int block)
{
	for (int i = data->block_start + block; i < data->block_end; i++) {
		if (!nand_block_is_bad(data->nand, i))
			return i - data->block_start;

		log_dbg("skip bad block %d\n", i);
	}

	return -1;
}

static int update_bb_table(struct block_dev *dev)
{
	struct dev_data *data = dev->priv;
	int ret;

	for (int i = 0; i < BB_TABLE_SIZE; i++) {
		ret = find_next(data, i ? data->bb_table[i - 1] + 1 : 0);
		if (ret < 0) {
			log_err("no good block for bb_table[%d]\n", i);
			return -1;
		}
		data->bb_table[i] = ret;
		log_dbg("bb_table[%d]=%d\n", i, data->bb_table[i]);
	}

	return 0;
}

static int erase_all(struct block_dev *dev)
{
	struct dev_data *data = dev->priv;
	struct nand_info *nand = data->nand;

	for (int i = data->block_start; i < data->block_end; i++) {
		if (nand_block_is_bad(nand, i))
			continue;

		if (nand_block_erase(nand, i)) {
			log_info("failed to erase block %d, mark as bad\n", i);

			if (nand_block_mark_bad(nand, i)) {
				log_err("mard block %d as bad\n", i);
				return -1;
			}
		}
	}

	return 0;
}

static int block_init(struct block_dev *dev,
		      unsigned int addr, unsigned int size)
{

	struct dev_data *data = dev->priv;
	struct nand_info *nand = data->nand;
	struct align_info *block = &dev->align;
	struct align_info *page = &dev->block;
	unsigned int shift = block->shift + page->shift;
	unsigned int mask = (1 << shift) - 1;

	if ((addr & mask) || (size & mask)) {
		log_err("non-block-aligned address:%x or size:%x\n", addr, size);
		return -1;
	}

	if (((addr >> shift) + (size >> shift)) > nand->numblocks) {
		log_err("assigned blocks(%d ~ %d) is out of range(0 ~ %d)\n",
			addr >> shift,
			(addr >> shift) + (size >> shift) - 1,
			nand->numblocks - 1);
		return -1;
	}
	
	dev->start = addr >> page->shift;
	dev->count = size >> page->shift;
	data->block_start = addr >> shift;
	data->block_end = data->block_start + (size >> shift);

	if (update_bb_table(dev))
		return -1;
	dev->offset = bb_page(dev, 0);

	return 0;
}

static int _block_access(struct block_dev *dev,
			 unsigned int page, void *buf,
			 unsigned int count, int is_read)
{
	struct dev_data *data = dev->priv;
	struct nand_info *nand = data->nand;
	struct align_info *block = &dev->align;

	if (((page >> block->shift) >= BB_TABLE_SIZE) ||
	    (((page + count - 1) >> block->shift) >= BB_TABLE_SIZE)) {
		/*
		   TODO It is not expected to access data out of bb_table[].
		*/
		log_err("TODO %s() page=%d\n", __func__, page);
		return -1;
	}

	if (is_read) {
		return nand_page_read(nand, dev->start + bb_page(dev, page),
				      count, buf);
	} else {
		return nand_page_write(nand, dev->start + bb_page(dev, page),
				       count, buf);
	}
}

static int block_read(struct block_dev *dev,
		      unsigned int page, void *buf, unsigned int count)
{
	return _block_access(dev, page, (void *)buf, count, 1);
}

static int block_write(struct block_dev *dev,
		       unsigned int page, const void *buf, unsigned int count)
{
	return _block_access(dev, page, (void *)buf, count, 0);
}

static int block_erase(struct block_dev *dev, enum erase_flag flag)
{
	struct dev_data *data = dev->priv;
	struct nand_info *nand = data->nand;

	if (flag == ERASE_HEADER) {
		return nand_block_erase(nand,
					data->block_start + data->bb_table[0]);
	} else if (flag == ERASE_ALL) {
		if (erase_all(dev))
			return -1;

		if (update_bb_table(dev))
			return -1;
		dev->offset = bb_page(dev, 0);

		return 0;
	}

	return -1;
}

static int block_seek(struct block_dev *dev, unsigned long offset)
{
	struct align_info *block = &dev->align;

	if ((offset >> block->shift) >= BB_TABLE_SIZE) {
		/*
		   TODO It is not expected to seek out of bb_table[].
		*/
		log_err("TODO %s() offset=%d\n", __func__, offset);
		return -1;
	}

	dev->offset = bb_page(dev, offset);
	log_dbg("seek to %d:%d\n", offset, dev->offset);

	return 0;
}

static int _block_io_access(struct block_dev *dev,
			    void *buf, unsigned int count, int is_read)
{
	struct dev_data *data = dev->priv;
	struct nand_info *nand = data->nand;
	struct align_info *block = &dev->align;
	struct align_info *page = &dev->block;
	unsigned int pages, remain;
	int ret;

	if ((dev->offset + count) > dev->count) {
		log_err("offset %d count %d is out of range\n", dev->offset, count);
		return -1;
	}

	for (unsigned int i = 0; i < count;) {
		remain = block->size - (dev->offset & block->mask);
		pages = remain >= (count - i) ? (count - i) : remain;

		if (is_read) {
			ret = nand_page_read(nand, dev->start + dev->offset, pages, buf);
		} else {
			ret = nand_page_write(nand, dev->start + dev->offset, pages, buf);
		}

		if (ret) {
			log_err("%s page %d\n",
				is_read ? "read" : "write",
				dev->offset);
			return -1;
		}

		dev->offset += pages;
		if (!(dev->offset & block->mask)) {
			ret = find_next(data, dev->offset >> block->shift);
			if (ret < 0) {
				log_err("no good block for io accessing\n");
				return -1;
			}

			dev->offset = ret << block->shift;
		}

		i += pages;
		buf += pages << page->shift;
	}

	return 0;
}

static int block_io_read(struct block_dev *dev,
			 void *buf, unsigned int count)
{
	return _block_io_access(dev, buf, count, 1);
}

static int block_io_write(struct block_dev *dev,
			  const void *buf, unsigned int count)
{
	return _block_io_access(dev, (void *)buf, count, 0);
}

static struct block_dev dev = {
	.init     = block_init,
	.read     = block_read,
	.write    = block_write,
	.erase    = block_erase,
	.seek     = block_seek,
	.io_read  = block_io_read,
	.io_write = block_io_write
};

static unsigned int call_with_2k(struct fast_config *conf,
				 struct block_dev *dev,
				 struct image_info *image)
{
	unsigned char buffer[PAGE_2K];

	dev->buffer = buffer;
	return fast_boot(conf, dev, image);
}

static unsigned int call_with_4k(struct fast_config *conf,
				 struct block_dev *dev,
				 struct image_info *image)
{
	unsigned char buffer[PAGE_4K];

	dev->buffer = buffer;
	return fast_boot(conf, dev, image);
}

static unsigned int call_with_8k(struct fast_config *conf,
				 struct block_dev *dev,
				 struct image_info *image)
{
	unsigned char buffer[PAGE_8K];

	dev->buffer = buffer;
	return fast_boot(conf, dev, image);
}

unsigned int nandflash_fast_boot(struct nand_info *nand, struct image_info *image)
{
	struct fast_config *conf = &(struct fast_config){0};
	struct dev_data *data = &(struct dev_data){0}; 

	log_info("%s\n", __func__);
	fast_boot_init_config(conf);

	data->nand = nand;
	dev.priv = data;
	/* NAND Flash page alignment */
	dev.block.size = nand->pagesize;
	dev.block.shift = fls(nand->pagesize) - 1;
	dev.block.mask = nand->pagesize - 1;
	/* NAND Flash page-to-block alignment */
	dev.align.size = nand->pages_block;
	dev.align.shift = fls(nand->pages_block) - 1;
	dev.align.mask = nand->pages_block - 1;

	if (nand->pagesize == PAGE_2K) {
		return call_with_2k(conf, &dev, image);
	} else if (nand->pagesize == PAGE_4K) {
		return call_with_4k(conf, &dev, image);
	} else if (nand->pagesize == PAGE_8K) {
		return call_with_8k(conf, &dev, image);
	} else {
		log_err("unsupported page size %d\n", nand->pagesize);
		return 0;
	}
}
