#include "stdint.h"
typedef typeof(sizeof(0)) size_t; // valid since C23

#define _u(x) x ## u

#define XIP_BASE _u(0x10000000)

#define PICO_FLASH_SIZE_BYTES (2 * 1024 * 1024)

#define FLASH_PAGE_SIZE (1u << 8)
#define FLASH_SECTOR_SIZE (1u << 12)
#define FLASH_BLOCK_SIZE (1u << 16)

void flash_range_erase(uint32_t flash_offs, size_t count);
void flash_range_program(uint32_t flash_offs, const uint8_t *data, size_t count);
