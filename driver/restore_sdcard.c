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

#include "fast_boot.h"
#include "media.h"
#include "debug.h"

#define SECTOR_SHIFT	9
#define SECTOR_SIZE	(1 << SECTOR_SHIFT)
#define SECTOR_MASK	(SECTOR_SIZE - 1)

#define OFFSET_TABLE	446
#define OFFSET_SIG_55	510
#define OFFSET_SIG_AA	511
#define BOOT_SIGNATURE	0xAA55
#define MAX_PRIMARY	4
#define ACTIVE		0x80

#define TYPE_ID_EMPTY	0x0
#define TYPE_ID_EXT	0x5

struct partition_entry {
	unsigned char active;
	unsigned char chs_start[3];
	unsigned char type;
	unsigned char chs_end[3];
	unsigned int lba_start;
	unsigned int sectors;
} __attribute__((packed));

static struct partition_entry * read_mbr(unsigned char *buf, unsigned int addr)
{
	if (buf == NULL)
		return NULL;

	if (sdcard_block_read(addr, 1, (void *)buf) != 1) {
		log_dbg("Failed to read MBR/EBR sector at %d\n", addr);
		return NULL;
	}

	if ((buf[OFFSET_SIG_AA] << 8 | buf[OFFSET_SIG_55]) != BOOT_SIGNATURE) {
		log_dbg("Error no valid boot signature in the MBR/EBR\n");
		return NULL;
	}

	return (struct partition_entry *)&buf[OFFSET_TABLE];
}

static unsigned int partition_base(unsigned int partition,
				   unsigned int *sectors)
{
	unsigned char buf[SECTOR_SIZE];
	struct partition_entry *table;
	unsigned int ext_base, ebr_addr;
	int id = partition - 1;
	int i;

	if (partition <= 0) {
		log_dbg("Error invalid partition number %d\n", partition);
		return 0;
	}

	table = read_mbr(buf, 0);
	if (table == NULL)
		return 0;

	if ((partition <= MAX_PRIMARY) && (table[id].type != TYPE_ID_EXT)) {
		if (table[id].type != TYPE_ID_EMPTY) {
			if (sectors != NULL)
				*sectors = table[id].sectors;

			return table[id].lba_start;
		} else {
			return 0;
		}
	} else if (partition > MAX_PRIMARY) {
		for (i = 0; i < MAX_PRIMARY; i++) {
			if (table[i].type == TYPE_ID_EXT)
				break;
		}

		if (i >= MAX_PRIMARY) {
			log_dbg("Error not found extended partition\n");
			return 0;
		}

		ext_base = table[i].lba_start;
		ebr_addr = ext_base;
		for (i = MAX_PRIMARY; i <= id; i++) {
			table = read_mbr(buf, ebr_addr);
			if (table == NULL)
				return 0;

			if (i < id) {
				ebr_addr = ext_base + table[1].lba_start;
			} else {
				if (table[0].type != TYPE_ID_EMPTY) {
					if (sectors != NULL)
						*sectors = table[0].sectors;

					return ebr_addr + table[0].lba_start;
				} else {
					return 0;
				}
			}

			if (table[1].type == TYPE_ID_EMPTY)
				break;
		}
	}

	return 0;
}

static int block_init(struct block_dev *dev, unsigned int partition,
		      __attribute__((unused)) unsigned int unused)
{
	dev->start = partition_base(partition, &dev->count);
	if ((dev->start == 0) || (dev->count == 0)) {
		log_err("failed to get partition %d base address\n", partition);
		return -1;
	}

	return 0;
}

static int block_read(struct block_dev *dev,
		      unsigned int block, void *buf, unsigned int count)
{
	if ((block + count) > dev->count) {
		log_err("block %d count %d is out of range\n", block, count);
		return -1;
	}

	return sdcard_block_read(dev->start + block, count, buf) == count
	       ? 0 : -1;
}

static int block_write(struct block_dev *dev,
		       unsigned int block, const void *buf, unsigned int count)
{
	if ((block + count) > dev->count) {
		log_err("block %d count %d is out of range\n", block, count);
		return -1;
	}

	return sdcard_block_write(dev->start + block, count, buf) == count
	       ? 0 : -1;
}

static int block_seek(struct block_dev *dev, unsigned long offset)
{
	if (offset > dev->count) {
		log_err("offset %ld is out of range\n", offset);
		return -1;
	}

	dev->offset = offset;
	return 0;
}

static int block_io_read(struct block_dev *dev,
			 void *buf, unsigned int count)
{
	if (block_read(dev, dev->offset, buf, count))
		return -1;

	dev->offset += count;
	return 0;
}

static int block_io_write(struct block_dev *dev,
			  const void *buf, unsigned int count)
{
	if (block_write(dev, dev->offset, buf, count))
		return -1;

	dev->offset += count;
	return 0;
}

static struct block_dev dev = {
	.block = {
		.shift = SECTOR_SHIFT,
		.size  = SECTOR_SIZE,
		.mask  = SECTOR_MASK,
	},
	.init     = block_init,
	.read     = block_read,
	.write    = block_write,
	.seek     = block_seek,
	.io_read  = block_io_read,
	.io_write = block_io_write
};

unsigned int sdcard_fast_boot(struct image_info *image)
{
	struct fast_config *conf = &(struct fast_config){0};
	unsigned char buffer[SECTOR_SIZE];

	dev.buffer = buffer;

	log_info("%s\n", __func__);
	fast_boot_init_config(conf);

	return fast_boot(conf, &dev, image);
}
