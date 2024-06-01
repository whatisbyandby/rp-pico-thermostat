#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

bool isInputAvailable() {
    return uart_is_readable(uart0);
}

int main() {
    // Initialize stdio for USB (or use uart_init for UART)
    stdio_init_all();

    // Give some time for the USB to be ready
    sleep_ms(2000);

    while (true) {
        if (isInputAvailable()) {
            
        } else {
            // Do other non-blocking work here
            printf("No input available. Doing other work...\n");
            sleep_ms(100); // Sleep for 100ms to avoid busy waiting
        }
    }

    return 0;
}
