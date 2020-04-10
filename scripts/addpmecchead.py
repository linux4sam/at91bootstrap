#!/usr/bin/env python3

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
    if find_in_file(dot_config_path, "CONFIG_NANDFLASH=y"):
        if not (os.path.exists(binaries_path)):
            os.mkdir(binaries_path)
        if find_in_file(dot_config_path, "CONFIG_SAMA5D2_PTC_EK=y"):
            pmecc_word = pmecc_head.gen_pmecc_header(2048, 64, 4, 512)
        elif find_in_file(dot_config_path, "CONFIG_SAMA5D3XEK=y"):
            pmecc_word = pmecc_head.gen_pmecc_header(2048, 64, 4, 512)
        elif find_in_file(dot_config_path, "CONFIG_SAMA5D3_XPLAINED=y"):
            pmecc_word = pmecc_head.gen_pmecc_header(2048, 64, 4, 512)
        elif find_in_file(dot_config_path, "CONFIG_SAMA5D4EK=y"):
            pmecc_word = pmecc_head.gen_pmecc_header(4096, 224, 8, 512)
        elif find_in_file(dot_config_path, "CONFIG_SAMA5D4_XPLAINED=y"):
            pmecc_word = pmecc_head.gen_pmecc_header(4096, 224, 8, 512)
        elif find_in_file(dot_config_path, "CONFIG_AT91SAM9X5EK=y"):
            pmecc_word = pmecc_head.gen_pmecc_header(2048, 64, 2, 512)
        elif find_in_file(dot_config_path, "CONFIG_AT91SAM9N12EK=y"):
            pmecc_word = pmecc_head.gen_pmecc_header(2048, 64, 2, 512)
        elif find_in_file(dot_config_path, "CONFIG_SAM9X60EK=y"):
            pmecc_word = pmecc_head.gen_pmecc_header(4096, 224, 8, 512)
        elif find_in_file(dot_config_path, "CONFIG_SAM9X60_DDR2_SIP_EB=y"):
            pmecc_word = pmecc_head.gen_pmecc_header(4096, 224, 8, 512)
        elif find_in_file(dot_config_path, "CONFIG_SAM9X60_SDR_SIP_EB=y"):
            pmecc_word = pmecc_head.gen_pmecc_header(2048, 64, 2, 512)
        else:
            return
    else:
        return

    vec = struct.pack("<I", pmecc_word)
    # generate a new file with pmecc header
    fd = open(header, "wb")
    for i in range(0, 52):
        fd.write(vec)
    fd.close()

if __name__ == "__main__":
    pmecchead(sys.argv[1], sys.argv[2])
