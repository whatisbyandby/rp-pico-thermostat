/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"


#define UART_ID uart0
#define BAUD_RATE 115200

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

int main() {
    stdio_init_all();

    // Set up our UART with the required speed.
    uart_init(UART_ID, BAUD_RATE);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);



    while (true) {
        if(uart_is_readable(UART_ID)) {
            int i = 0;
            uint8_t buffer[100];
            while (uart_is_readable(UART_ID)) {
                uint8_t character = uart_getc(UART_ID);
                buffer[i] = character;
                i++;
            }

            printf("Received: %s\n", buffer);
        }
        sleep_ms(1000);
    }
}

