/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012, Atmel Corporation

 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaiimer below.
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
#include "common.h"
#include "string.h"
#include "debug.h"

#define OF_DT_MAGIC		0xd00dfeed

#define OF_DT_TOKEN_NODE_BEGIN	0x1
#define OF_DT_TOKEN_NODE_END	0x2
#define OF_DT_TOKEN_PROP	0x3
#define OF_DT_TOKEN_NOP		0x4
#define OF_DT_END		0x9

#define ALIGN(x, a)		(((x) + (a) - 1) & ~((a) - 1))
#define OF_ALIGN(x)		ALIGN(x, 4)

struct of_dt_header {
	unsigned int	magic;
	unsigned int	totalsize;
	unsigned int	off_dt_struct;
	unsigned int	off_dt_strings;
	unsigned int	off_dt_rsvmap;
	unsigned int	version;
	unsigned int	last_comp_version;

	/* version 2 field */
	unsigned int	boot_cpuid_id;

	/* version 3 field */
	unsigned int	size_dt_strings;

	/* version 17 field */
	unsigned int	size_dt_struct;
};

static inline unsigned int of_get_magic(void *blob)
{
	struct of_dt_header *header = (struct of_dt_header *)blob;

	return be32_to_cpu(header->magic);
}

static inline unsigned int of_get_version(void *blob)
{
	struct of_dt_header *header = (struct of_dt_header *)blob;

	return be32_to_cpu(header->version);
}

static inline unsigned int of_get_last_compversion(void *blob)
{
	struct of_dt_header *header = (struct of_dt_header *)blob;

	return be32_to_cpu(header->last_comp_version);
}

static inline unsigned int of_get_off_dt_strings(void *blob)
{
	struct of_dt_header *header = (struct of_dt_header *)blob;

	return be32_to_cpu(header->off_dt_strings);
}

static inline void of_set_off_dt_strings(void *blob, unsigned int offset)
{
	struct of_dt_header *header = (struct of_dt_header *)blob;

	header->off_dt_strings = cpu_to_be32(offset);
}

static inline char *of_dt_strings_offset(void *blob, unsigned int offset)
{
	return (char *)((unsigned int)blob
				+ of_get_off_dt_strings(blob) + offset);
}

static inline unsigned int of_get_off_dt_struct(void *blob)
{
	struct of_dt_header *header = (struct of_dt_header *)blob;

	return be32_to_cpu(header->off_dt_struct);
}

static inline unsigned int of_dt_struct_offset(void *blob, unsigned int offset)
{
	return (unsigned int)blob + of_get_off_dt_struct(blob) + offset;
}

static inline unsigned int of_get_totalsize(void *blob)
{
	struct of_dt_header *header = (struct of_dt_header *)blob;

	return be32_to_cpu(header->totalsize);
}

static inline void of_set_totalsize(void *blob, unsigned int size)
{
	struct of_dt_header *header = (struct of_dt_header *)blob;

	header->totalsize = cpu_to_be32(size);
}

static inline unsigned int of_get_size_dt_strings(void *blob)
{
	struct of_dt_header *header = (struct of_dt_header *)blob;

	return be32_to_cpu(header->size_dt_strings);
}

static inline void of_set_size_dt_strings(void *blob, unsigned int size)
{
	struct of_dt_header *header = (struct of_dt_header *)blob;

	header->size_dt_strings = cpu_to_be32(size);
}

static inline unsigned int of_get_size_dt_struct(void *blob)
{
	struct of_dt_header *header = (struct of_dt_header *)blob;

	return be32_to_cpu(header->size_dt_struct);
}

static inline void of_set_size_dt_struct(void *blob, unsigned int size)
{
	struct of_dt_header *header = (struct of_dt_header *)blob;

	header->size_dt_struct = cpu_to_be32(size);
}

static inline int of_blob_data_size(void *blob)
{

	return (unsigned int)of_get_off_dt_strings(blob)
			+ of_get_size_dt_strings(blob);
}

static int of_nodename_is_equal(void *blob,
				int offset,
				const char *name,
				int namelen)
{
	const char *p = (char *)of_dt_struct_offset(blob, (offset + 4));



	if (memcmp(p, name, namelen) != 0)
		return 0;

	if (p[namelen] == '\0')
		return 1;

	return 0;
}

static int of_propertyname_is_equal(void *blob,
				int nameoffset,
				const char *name,
				int namelen)
{
	char *p = of_dt_strings_offset(blob, nameoffset);

	if ((strlen(p) == namelen) && (memcmp(p, name, namelen) == 0))
		return 1;
	else
		return 0;
}

/* return the token and the next token offset */
static int of_find_nextoffset_token(void *blob,
					int startoffset,
					int *nextoffset,
					unsigned int *token)
{
	const unsigned int *p, *lenp;
	unsigned int tag;
	const char *tmp;
	unsigned int offset = startoffset;

	*nextoffset = -1;

	if (offset % 4) {
		dbg_log(1, "DT: the token offset is not aligned\n\r");
		return -1;
	}

	/* Get the token */
	p = (unsigned int *)of_dt_struct_offset(blob, offset);
	tag = be32_to_cpu(*p);

	/* Prepare offset for the next token */
	offset += 4;
	if (tag  == OF_DT_TOKEN_NODE_BEGIN) {
		/* node name */
		tmp = (char *)of_dt_struct_offset(blob, offset);
		do {
			tmp++;
			offset++;
		} while (*tmp != '\0');
	} else if (tag == OF_DT_TOKEN_PROP) {
		/* the property value size */
		lenp = (unsigned int *)of_dt_struct_offset(blob, offset);
		/* name offset + value size + value */
		offset += be32_to_cpu(*lenp) + 8;
	} else if ((tag != OF_DT_TOKEN_NODE_END)
			&& (tag != OF_DT_TOKEN_NOP)
			&& (tag != OF_DT_END))
		return -1;

	*nextoffset = OF_ALIGN(offset);
	*token = tag;

	return 0;
}

static int of_nextnode_offset(void *blob,
				int start_offset,
				int *offset,
				int *nextoffset,
				int *depth)
{
	int next_offset = 0;
	int nodeoffset = start_offset;
	unsigned int token;
	int ret;

	do {
		ret = of_find_nextoffset_token(blob, nodeoffset,
						&next_offset, &token);
		if (ret)
			return -1;

		if (token == OF_DT_TOKEN_NODE_BEGIN) {
			if (depth)
				(*depth)++;
		} else {
			nodeoffset = next_offset;

			if (token ==  OF_DT_TOKEN_PROP)
				continue;
			else if (token == OF_DT_TOKEN_NOP)
				continue;
			else if (token == OF_DT_TOKEN_NODE_END) {
				if (depth)
					(*depth)--;
				if ((*depth) < 0)
					return next_offset;
			} else if (token == OF_DT_END) {
				return next_offset;
			}
		}
	} while (token != OF_DT_TOKEN_NODE_BEGIN);

	*offset = nodeoffset;
	*nextoffset = next_offset;

	return 0;
}

static int of_nodeoffset_by_name(void *blob,
				int start_offset,
				const char *name,
				int namelen,
				int *offset)
{
	int depth = 0;
	int nodeoffset = 0;
	int nextoffset = 0;
	int ret = 1;

	for (;;) {
		ret = of_nextnode_offset(blob, start_offset,
					&nodeoffset, &nextoffset, &depth);
		if (ret)
			return ret;

		if (depth == 1) {
			if (of_nodename_is_equal(blob, nodeoffset,
						name, namelen)) {
				ret = 0;
				break;
			}
		}

		if (depth < 0)
			return -1;

		start_offset = nextoffset;
	}

	*offset = nextoffset;
	return ret;
}

static int of_blob_splice(void *blob,
			void *splicepoint,
			int oldlen,
			int newlen)
{
	char *p = splicepoint;
	char *end = (char *)blob + of_blob_data_size(blob);

	if ((end - oldlen + newlen) > ((char *)blob + of_get_totalsize(blob)))
		return -1;

	memmove((p + newlen), (p + oldlen), (end - p - oldlen));

	return 0;
}

static int of_blob_splice_dt_struct(void *blob,
					void *splicepoint,
					int oldlen,
					int newlen)
{
	int delta = newlen - oldlen;
	int ret;

	ret = of_blob_splice(blob, splicepoint, oldlen, newlen);
	if (ret)
		return ret;

	of_set_size_dt_struct(blob, of_get_size_dt_struct(blob) + delta);
	of_set_off_dt_strings(blob, of_get_off_dt_strings(blob) + delta);

	return 0;
}

static int of_blob_splice_dt_string(void *blob, int newlen)
{
	void *splicepoint = (void *)((unsigned int)blob
				+ of_get_off_dt_strings(blob)
				+ of_get_size_dt_strings(blob));
	int ret;

	ret = of_blob_splice(blob, splicepoint, 0, newlen);
	if (ret)
		return ret;

	of_set_size_dt_strings(blob, of_get_size_dt_strings(blob) + newlen);

	return 0;
}

static int of_get_node_offset(void *blob, char *path, int *offset)
{
	const char *end = path + strlen(path);
	const char *p = path;
	const char *q;
	unsigned int len;
	int nodeoffset = 0;
	int nextoffset = 0;
	unsigned int token;
	int ret;

	ret = of_find_nextoffset_token(blob, 0, &nodeoffset, &token);
	if (ret)
		return -1;

	while (*p) {
		while (*p == '/')
			p++;

		if (!*p) {
			*offset = nodeoffset;
			return 0;
		}

		q = strchr(p, '/');
		if (!q)
			q = end;

		len = q-p;

		ret = of_nodeoffset_by_name(blob, nodeoffset,
					p, len, &nextoffset);
		if (!ret)
			break;
		else if (ret == -1)
			return ret;

		nodeoffset = nextoffset;
		p = q;
	}

	*offset = nextoffset;
	return 0;
}

static int of_next_property_offset(void *blob,
				int startoffset,
				int *offset,
				int *nextprop)
{
	unsigned int token;
	int nextoffset;
	int ret;

	do {
		ret = of_find_nextoffset_token(blob, startoffset,
						&nextoffset, &token);
		if (ret)
			return ret;

		if (token == OF_DT_TOKEN_PROP) {
			*offset = startoffset;
			*nextprop = nextoffset;
			return 0;
		} else if (token == OF_DT_TOKEN_NODE_END)
			return -1;

		startoffset = nextoffset;
	} while (token == OF_DT_TOKEN_NOP);

	return -1;
}

static int of_get_property_offset_by_name(void *blob,
					unsigned int nodeoffset,
					char *name,
					int *offset)
{
	unsigned int nameoffset;
	unsigned int *p;
	unsigned int namelen = strlen(name);
	int startoffset = nodeoffset;
	int propoffset;
	int nextoffset = 0;
	int ret;

	*offset = 0;

	for (; ; ) {
		ret = of_next_property_offset(blob, startoffset,
					&propoffset, &nextoffset);
		if (ret)
			return ret;

		p = (unsigned int *)of_dt_struct_offset(blob, propoffset + 8);
		nameoffset = be32_to_cpu(*p);

		if (of_propertyname_is_equal(blob, nameoffset, name, namelen)) {
			*offset = propoffset;
			return 0;
		}
		startoffset = nextoffset;
	}

	return -1;
}

static int of_string_is_find_blob(void *blob,
				const char *string,
				int *offset)
{
	char *string_table = (char *)blob + of_get_off_dt_strings(blob);
	int table_size = of_get_size_dt_strings(blob);
	int len = strlen(string) + 1;
	char *last = string_table + table_size - len;
	char *p;

	for (p = string_table; p <= last; p++) {
		if (memcmp(p, string, len) == 0) {
			*offset = p - string_table;
			return 0;
		}
	}

	return -1;
}

static int of_add_dt_strings(void *blob,
			const char *string,
			int *name_offset)
{
	char *string_table = (char *)blob + of_get_off_dt_strings(blob);
	char *new_string;
	int len = strlen(string) + 1;
	int ret;

	new_string = string_table + of_get_size_dt_strings(blob);
	ret = of_blob_splice_dt_string(blob, len);
	if (ret)
		return ret;

	memcpy(new_string, string, len);

	*name_offset = new_string - string_table;

	return 0;
}

static int of_update_property(void *blob,
				int propoffset,
				const void *value,
				int valuelen)
{
	int oldlen;
	int newlen = valuelen;
	int offset = propoffset;
	unsigned int *lenp
		= (unsigned int *)of_dt_struct_offset(blob, offset + 4);
	unsigned char *valuep
		= (unsigned char *)of_dt_struct_offset(blob, offset + 12);
	void *point = (void *)valuep;
	int ret;

	oldlen = be32_to_cpu(*lenp);

	ret = of_blob_splice_dt_struct(blob, point,
			OF_ALIGN(oldlen), OF_ALIGN(newlen));
	if (ret)
		return ret;

	*lenp = cpu_to_be32(newlen);

	memcpy(valuep, value, newlen);

	return 0;
}

static int of_add_property(void *blob,
				int nextoffset,
				const char *prop_name,
				const void *value,
				int valuelen)
{
	int string_offset;
	unsigned int *p;
	unsigned int addr;
	int len;
	int ret;

	ret = of_string_is_find_blob(blob, prop_name, &string_offset);
	if (ret) {
		ret = of_add_dt_strings(blob, prop_name, &string_offset);
		if (ret)
			return ret;
	}

	len = 12 + OF_ALIGN(valuelen);
	addr = of_dt_struct_offset(blob, nextoffset);
	ret = of_blob_splice_dt_struct(blob, (void *)addr, 0, len);
	if (ret)
		return ret;

	p = (unsigned int *)addr;
	*p++ = cpu_to_be32(OF_DT_TOKEN_PROP);
	*p++ = cpu_to_be32(valuelen);
	*p++ = cpu_to_be32(string_offset);
	memcpy((unsigned char *)p, value, valuelen);

	return 0;
}

static int of_set_property(void *blob,
				int nodeoffset,
				char *prop_name,
				void *value,
				int valuelen)
{
	int propoffset;
	int ret;

	ret = of_get_property_offset_by_name(blob, nodeoffset,
					prop_name, &propoffset);
	if (ret) {
		ret = of_add_property(blob, nodeoffset,
				prop_name, value, valuelen);
		if (ret)
			dbg_log(1, "DT: fail to add property\n\r");

		return ret;
	}

	ret = of_update_property(blob, propoffset, value, valuelen);
	if (ret) {
		dbg_log(1, "DT: fail to update property\n\r");
		return ret;
	}

	return 0;
}

static int of_get_cells_len(void *blob, int *addrcells_len, int *sizecells_len)
{
	int offset;
	int nextoffset;
	unsigned int token;
	unsigned int *cellp;
	int ret;

	/* find the root node*/
	ret = of_find_nextoffset_token(blob, 0, &nextoffset, &token);
	if (ret)
		return -1;

	if (token != OF_DT_TOKEN_NODE_BEGIN)
		return -1;

	/* #address-cells */
	ret = of_get_property_offset_by_name(blob, nextoffset,
					"#address-cells", &offset);
	if (ret)
		return ret;

	cellp = (unsigned int *)of_dt_struct_offset(blob, offset);
	if (be32_to_cpu(*cellp) == 2)
		*addrcells_len = 8;
	else
		*addrcells_len = 4;

	/* #size-cells */
	ret = of_get_property_offset_by_name(blob, nextoffset,
					"#size-cells", &offset);
	if (ret)
		return ret;

	cellp = (unsigned int *)of_dt_struct_offset(blob, offset);
	if (be32_to_cpu(*cellp) == 2)
		*sizecells_len = 8;
	else
		*sizecells_len = 4;

	return 0;
}

/* write a 4 or 8 byte big endian cell */
static void write_cell(unsigned char *addr, unsigned long value, int size)
{
	int shift = (size - 1) * 8;
	while (size-- > 0) {
		*addr++ = (value >> shift) & 0xff;
		shift -= 8;
	}
}

int of_check_dt_header(void *blob)
{
	if (of_get_magic(blob) != OF_DT_MAGIC)
		return -1;

	if (of_get_version(blob) < 17)
		return -1;

	return 0;
}

#define CONFIG_SYS_BLOB_LEN_PAD		0x3000

unsigned int of_expand_blob(void *blob, unsigned int *of_size)
{
	unsigned int total_size = of_get_totalsize(blob);

	total_size += CONFIG_SYS_BLOB_LEN_PAD;
	of_set_totalsize(blob, total_size);

	*of_size = total_size;

	return 0;
}

int of_fixup_chosen_node(void *blob, char *bootargs)
{
	int nodeoffset;
	char *value = bootargs;
	int valuelen = strlen(value) + 1;
	int ret;

	ret = of_get_node_offset(blob, "/chosen", &nodeoffset);
	if (ret) {
		dbg_log(1, "DT: doesn't support add node\n\r");
		return ret;
	}

	/*
	 * if the property doesn't exit, add it
	 * if the property exists, update it.
	 */
	ret = of_set_property(blob, nodeoffset, "bootargs", value, valuelen);
	if (ret) {
		dbg_log(1, "fail to set bootargs property\n\r");
		return ret;
	}

	return 0;
}

int of_fixup_memory_node(void *blob,
				unsigned int start[],
				unsigned int size[],
				int banks)
{
	int nodeoffset;
	int addr_cells_len, size_cells_len;
	int len;
	unsigned char tmp[banks * 16]; /* Up to 64-bit address + 64-bit size */
	int bank;
	int ret;

	ret = of_get_node_offset(blob, "/memory", &nodeoffset);
	if (ret) {
		dbg_log(1, "DT: doesn't support add node\n\r");
		return ret;
	}

	/*
	 * if the property doesn't exit, add it
	 * if the property exists, update it.
	 */
	/* set "device_type" property */
	ret = of_set_property(blob, nodeoffset,
			"device_type", "memory", sizeof("memory"));
	if (ret) {
		dbg_log(1, "DT: could not set device_type property\n\r");
		return ret;
	}

	ret = of_get_cells_len(blob, &addr_cells_len, &size_cells_len);
	if (ret)
		return ret;

	for (bank = 0, len = 0; bank < banks; bank++) {
		write_cell(tmp + len, start[bank], addr_cells_len);
		len += addr_cells_len;

		write_cell(tmp + len, size[bank], size_cells_len);
		len += size_cells_len;
	}

	ret = of_set_property(blob, nodeoffset, "reg", tmp, len);
	if (ret) {
		dbg_log(1, "DT: could not set reg property\n\r");
		return ret;
	}

	return 0;
}
