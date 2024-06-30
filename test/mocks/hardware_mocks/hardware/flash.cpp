#include <CppUTestExt/MockSupport.h>
#include "flash.h"

void flash_range_erase(uint32_t flash_offs, size_t count)
{
	mock().actualCall("flash_range_erase")
		.withUnsignedIntParameter("flash_offs", flash_offs)
		.withUnsignedIntParameter("count", count);
}

void flash_range_program(uint32_t flash_offs, const uint8_t *data, size_t count)
{
	mock().actualCall("flash_range_program")
		.withUnsignedIntParameter("flash_offs", flash_offs)
		.withMemoryBufferParameter("data", data, count)
		.withUnsignedIntParameter("count", count);
}

