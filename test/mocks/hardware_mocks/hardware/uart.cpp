#include <CppUTestExt/MockSupport.h>

#include "uart.h"

uint uart_init(uart_inst_t *uart, int baud_rate)
{
    return mock().actualCall("uart_init")
        .withPointerParameter("uart", uart)
        .withIntParameter("baud_rate", baud_rate)
        .returnUnsignedIntValueOrDefault(0);
}


bool uart_is_readable(uart_inst_t *uart)
{
    return mock().actualCall("uart_is_readable")
        .withPointerParameter("uart", uart)
        .returnBoolValueOrDefault(false);
}

uint8_t uart_getc(uart_inst_t *uart)
{
    return mock().actualCall("uart_getc")
        .withPointerParameter("uart", uart)
        .returnUnsignedIntValueOrDefault(0);
}