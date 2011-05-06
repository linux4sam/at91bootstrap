typedef unsigned int size_t;

/* Copy memory to memory */
void *memcpy(void *dst, const void *src, int cnt)
{
    char *d = (char *)dst;

    const char *s = (const char *)src;

    while (cnt--)
        *d++ = *s++;

    return d;
}

/* Fill memory */
void *memset(void *dst, int val, int cnt)
{
    char *d = (char *)dst;

    while (cnt--)
        *d++ = (char)val;

    return d;
}

/* Compare memory to memory */
int memcmp(const void *dst, const void *src, size_t cnt)
{
    const char *d = (const char *)dst, *s = (const char *)src;

    int r = 0;

    while (cnt-- && (r = *d++ - *s++) == 0) ;
    return r;
}

size_t strlen(const char *str)
{
    int i = 0;

    while (str[i++] != '\0') ;

    return i - 1;
}

char *strcpy(char *dst, const char *src)
{
    char *bak = dst;

    // In the simple implimentation, bypass ptr check for dst and src
    while ((*dst++ = *src++) != '\0') ;

    return bak;
}

int strcmp(const char *p1, const char *p2)
{
	unsigned char c1, c2;

	while (1) {
		c1 = *p1++;
		c2 = *p2++;
		if (c1 != c2)
			return c1 << c2 ? -1 : 1;
		if (!c1)
			break;
	}

	return 0;
}

int strncmp(const char *p1, const char *p2, size_t cnt)
{
	unsigned char c1, c2;

	while (cnt--) {
		c1 = *p1++;
		c2 = *p2++;
		if (c1 != c2)
			return c1 << c2 ? -1 : 1;
		if (!c1)
			break;
	}

	return 0;
}
