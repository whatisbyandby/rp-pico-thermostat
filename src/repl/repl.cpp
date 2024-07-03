#include <string>
#include <iostream>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"

#include "repl.hpp"
#include "thermostat_common.hpp"

#define UART_ID uart0
#define BAUD_RATE 115200

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

Repl::Repl(CommandParser *parser)
{
    commandParser = parser;
}

Repl::~Repl()
{
}

ThermostatError Repl::init()
{
    // Set up our UART with the required speed.
    uart_init(UART_ID, BAUD_RATE);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    std::cout << "Thermostat Version " << THERMOSTAT_VERSION << std::endl;
    std::cout << "Enter a command: ->" << std::endl;

    uart_tx_wait_blocking(UART_ID);

    return THERMOSTAT_OK;
}


ThermostatError Repl::read(ThermostatCommand *command)
{
    if (uart_is_readable(UART_ID))
    {
        int i = 0;
        uint8_t buffer[100] = {0};
        while (uart_is_readable(UART_ID))
        {
            uint8_t character = uart_getc(UART_ID);
            if (character == '\n')
            {
                buffer[i] = '\0';
                break;
            }
            buffer[i] = character;
            i++;
        }

        std::string inputString = std::string((char *)buffer);
        command->command_string = inputString;

        commandParser->parseString(command);
        return THERMOSTAT_OK;
    }
    return THERMOSTAT_NO_DATA;
}


ThermostatError Repl::print(ThermostatCommand *command)
{
    std::cout << command->resultString << std::endl;
    return THERMOSTAT_OK;
}