#!/usr/bin/env python3

# Copyright (C) 2006 Microchip Technology Inc. and its subsidiaries
#
# SPDX-License-Identifier: MIT

import struct, sys
import os
import pmecc_head
import re

def find_in_file(file, pattern):
    if os.path.exists(file):
        with open(file) as f:
            result = re.search(pattern, f.read())
            f.close()
        return result

def pmecchead(dot_config_path, binaries_path):
    header = os.path.join(binaries_path, "pmecc.tmp")
    if os.path.isfile(header):
        os.remove(header)
    if find_in_file(dot_config_path, "CONFIG_NANDFLASH=y"):
        if not (os.path.exists(binaries_path)):
            os.makedirs(binaries_path)
        if find_in_file(dot_config_path, "CONFIG_PMECC_PAGESIZE_512=y"):
            pagesize = 512
        elif find_in_file(dot_config_path, "CONFIG_PMECC_PAGESIZE_1024=y"):
            pagesize = 1024
        elif find_in_file(dot_config_path, "CONFIG_PMECC_PAGESIZE_2048=y"):
            pagesize = 2048
        elif find_in_file(dot_config_path, "CONFIG_PMECC_PAGESIZE_4096=y"):
            pagesize = 4096
        elif find_in_file(dot_config_path, "CONFIG_PMECC_PAGESIZE_8192=y"):
            pagesize = 8192
        else:
            if find_in_file(dot_config_path, "CONFIG_SAMA5D2=y"):
                pagesize = 2048
            elif find_in_file(dot_config_path, "CONFIG_SAMA5D3X=y"):
                pagesize = 2048
            elif find_in_file(dot_config_path, "CONFIG_SAMA5D4=y"):
                pagesize = 4096
            elif find_in_file(dot_config_path, "CONFIG_SAM9X60=y"):
                pagesize = 4096
            elif find_in_file(dot_config_path, "CONFIG_SAM9X7=y"):
                pagesize = 2048
            else:
                return
        if find_in_file(dot_config_path, "CONFIG_PMECC_OOB_16=y"):
            oob = 16
        elif find_in_file(dot_config_path, "CONFIG_PMECC_OOB_32=y"):
            oob = 32
        elif find_in_file(dot_config_path, "CONFIG_PMECC_OOB_64=y"):
            oob = 64
        elif find_in_file(dot_config_path, "CONFIG_PMECC_OOB_128=y"):
            oob = 128
        elif find_in_file(dot_config_path, "CONFIG_PMECC_OOB_224=y"):
            oob = 224
        elif find_in_file(dot_config_path, "CONFIG_PMECC_OOB_256=y"):
            oob = 256
        else:
            if find_in_file(dot_config_path, "CONFIG_SAMA5D2=y"):
                oob = 64
            elif find_in_file(dot_config_path, "CONFIG_SAMA5D3X=y"):
                oob = 64
            elif find_in_file(dot_config_path, "CONFIG_SAMA5D4=y"):
                oob = 224
            elif find_in_file(dot_config_path, "CONFIG_SAM9X60=y"):
                oob = 224
            elif find_in_file(dot_config_path, "CONFIG_SAM9X7=y"):
                oob = 64
            else:
                return
        if find_in_file(dot_config_path, "CONFIG_PMECC_CORRECT_BITS_2=y"):
            correct = 2
        elif find_in_file(dot_config_path, "CONFIG_PMECC_CORRECT_BITS_4=y"):
            correct = 4
        elif find_in_file(dot_config_path, "CONFIG_PMECC_CORRECT_BITS_8=y"):
            correct = 8
        elif find_in_file(dot_config_path, "CONFIG_PMECC_CORRECT_BITS_12=y"):
            correct = 12
        elif find_in_file(dot_config_path, "CONFIG_PMECC_CORRECT_BITS_24=y"):
            correct = 24
        elif find_in_file(dot_config_path, "CONFIG_PMECC_CORRECT_BITS_32=y"):
            correct = 32
        else:
            if find_in_file(dot_config_path, "CONFIG_SAMA5D2=y"):
                correct = 4
            elif find_in_file(dot_config_path, "CONFIG_SAMA5D3X=y"):
                correct = 4
            elif find_in_file(dot_config_path, "CONFIG_SAMA5D4=y"):
                correct = 8
            elif find_in_file(dot_config_path, "CONFIG_SAM9X60=y"):
                correct = 8
            elif find_in_file(dot_config_path, "CONFIG_SAM9X7=y"):
                correct = 4
            else:
                return
        if find_in_file(dot_config_path, "CONFIG_PMECC_SECTOR_SIZE_512=y"):
            sector = 512
        elif find_in_file(dot_config_path, "CONFIG_PMECC_SECTOR_SIZE_1024=y"):
            sector = 1024
        else:
             sector = 512
    else:
        return
    pmecc_word = pmecc_head.gen_pmecc_header(pagesize, oob, correct, sector)
    vec = struct.pack("<I", pmecc_word)
    # generate a new file with pmecc header
    fd = open(header, "wb")
    for i in range(0, 52):
        fd.write(vec)
    fd.close()

if __name__ == "__main__":
    pmecchead(sys.argv[1], sys.argv[2])
