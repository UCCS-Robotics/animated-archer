// Code modified from example implementation retrieved on Feb 22, 2013 from:
// http://en.wikipedia.org/wiki/Cyclic_redundancy_check#CRC-32

#include <stdlib.h>
#include <stdint.h>

static uint32_t crc32_table[256];

void crc32_init(void)
{
	uint32_t i;
	int j;

	for(i = 0; i < 256; i++)
	{
		uint32_t c = i;

		for(j = 0; j < 8; j++)
			c = (c & 1) ? (0xEDB88320 ^ (c >> 1)) : (c >> 1);

		crc32_table[i] = c;
	}
}

uint32_t pcrc32(uint8_t *buf, size_t len)
{
	size_t i;
	uint32_t c = 0xFFFFFFFF;

    for(i = 0; i < len; i++)
        c = crc32_table[(c ^ buf[i]) & 0xFF] ^ (c >> 8);

	return c ^ 0xFFFFFFFF;
}
