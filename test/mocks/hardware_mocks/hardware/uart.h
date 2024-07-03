#ifndef UART_H
#define UART_H

#include <stdint.h>

#define uart0 ((uart_inst_t *)0x00000000)

typedef struct uart_inst uart_inst_t;

uint uart_init(uart_inst_t *uart, int baud_rate);
void uart_tx_wait_blocking(uart_inst_t *uart);
bool uart_is_readable(uart_inst_t *uart);
uint8_t uart_getc(uart_inst_t *uart);

#endif // UART_H