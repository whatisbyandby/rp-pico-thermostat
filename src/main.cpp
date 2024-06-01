#include <iostream>
#include "pico/stdlib.h"
#include "pico/multicore.h"

#include "environment_sensor.hpp"
#include "i2c_bus.hpp"
#include "hvac.hpp"
#include "thermostat.hpp"
#include "temperature_controller.hpp"
#include "thermostat_common.hpp"
#include "thermostat_controller.hpp"
#include "command_parser.hpp"
#include "pins.h"
#include "gpio.hpp"
#include "repl.hpp"

static Thermostat *thermostat_inst;


void commandLoop() {
    stdio_init_all();
    std::string command;
    CommandParser commandParser;
    ThermostatController thermostatController(thermostat_inst);
    ThermostatCommand thermostatCommand;

    printPrompt();

    while (true) {
        ThermostatError err;
        std::getline(std::cin, command);
        err = commandParser.parseString(command, &thermostatCommand);
        if (err != THERMOSTAT_OK) {
            printError(err);
            printPrompt();
            continue;
        }
        err = thermostatController.executeCommand(&thermostatCommand);
        printPrompt();
    }
}


int main()
{

    I2CBus i2cBus;
    i2cBus.initialize();
    I2CDevice i2cDevice(&i2cBus, 0x38);
    EnvironmentSensor environmentSensor(&i2cDevice);
    TemperatureController temperatureController;


    Switch heater(HEATER_PIN);
    Switch cooler(COOLER_PIN);
    Switch fan(FAN_PIN);

    HVAC hvac(&heater, &cooler, &fan);

    Thermostat thermostat(&environmentSensor, &temperatureController, &hvac);

    thermostat_inst = &thermostat;

    thermostat.setMode(HEATING);

    thermostat.initialize();

    multicore_launch_core1(commandLoop);



    while (true)
    {
        ThermostatError err = thermostat.update();

        if (err != THERMOSTAT_OK) {
            std::cout << "Error: " << err << std::endl;
        }

        sleep_ms(1000);
    }
}