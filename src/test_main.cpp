#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "json-maker/json-maker.h"
#include <iostream>

struct weather {
    int temp;
    int hum;
};

int main() {
    // Initialize stdio for USB (or use uart_init for UART)
    stdio_init_all();

    while (true) {


        size_t len = 100;
        size_t remaining = 100;
        char buffer[len];
        char *dest = buffer;

    
        dest = json_objOpen( dest, NULL, &remaining);              // --> "name":{\0
        dest = json_int( dest, "temp", 12, &remaining ); // --> "name":{"temp":22,\0
        dest = json_int( dest, "hum", 55, &remaining );   // --> "name":{"temp":22,"hum":45,\0
        dest = json_objClose( dest, &remaining );                   // --> "name":{"temp":22,"hum":45},\0

        dest = json_end( dest, &remaining );                        // --> "name":{"temp":22,"hum":45}
    

        std::cout << buffer << std::endl;
        sleep_ms(1000);
    }

    return 0;
}
