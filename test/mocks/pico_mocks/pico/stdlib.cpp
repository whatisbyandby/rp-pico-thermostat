#include <CppUTestExt/MockSupport.h>

#include "stdlib.h"

void gpio_set_function(uint gpio, enum gpio_function fn){
    mock().actualCall("gpio_set_function")
        .withUnsignedIntParameter("gpio", gpio)
        .withIntParameter("fn", fn);
}