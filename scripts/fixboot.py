#!/usr/bin/env python

import struct, sys

#print sys.argv[1]

fd = open(sys.argv[1], "r")

line = fd.read()
fd.close()

# print len(line)

vec = struct.pack("<I", len(line))

fd = open(sys.argv[1]+".fixboot", "w")
fd.write(line[0:20]+vec+line[24:])
fd.close()
