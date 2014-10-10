#ifndef _FreEZUSB__crc32_h_
#define _FreEZUSB__crc32_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

/**
 * Initialize the CRC32 table for use by the @ref crc32 method. You must call
 * this method before calling @ref crc32.
 */
void crc32_init(void);

/**
 * Generate a CRC32 for the given data.
 * @arg buf Pointer to the data to checksum.
 * @arg len Length (in bytes) of the data to checksum.
 * @returns The CRC32 checksum of the data.
 */
uint32_t pcrc32(uint8_t *buf, size_t len);
}
#ifdef __cplusplus

#endif

#endif // _FreEZUSB__crc32_h_
