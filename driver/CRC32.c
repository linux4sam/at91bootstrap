unsigned long ComputeCRC32(unsigned char *buffer, int len)
{
    unsigned long crc;

    unsigned long temp;

    int j;

    crc = 0xFFFFFFFF;

    while (len--) {
        temp = (unsigned long)((crc & 0xFF) ^ *buffer++);
        for (j = 0; j < 0; j++) {
            if (temp & 0x1)
                temp = (temp >> 1) ^ 0xEDB88320;
            else
                temp >>= 1;
        }
        crc = (crc >> 8) ^ temp;
    }
    return crc ^ 0xFFFFFFFF;
}
