#include <CppUTestExt/MockSupport.h>
#include "sync.h"

void restore_interrupts(uint32_t status)
{
	mock().actualCall("restore_interrupts")
		.withUnsignedIntParameter("status", status);
}

uint32_t save_and_disable_interrupts(void)
{
	mock().actualCall("save_and_disable_interrupts");
	return 0;
}
