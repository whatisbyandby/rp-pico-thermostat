#include <iostream>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"

#include "environment_sensor.hpp"
#include "i2c_bus.hpp"
#include "hvac.hpp"
#include "thermostat.hpp"
#include "temperature_controller.hpp"
#include "thermostat_common.hpp"
#include "command_parser.hpp"
#include "pins.h"
#include "gpio.hpp"
#include "repl.hpp"
#include "display.hpp"
#include "producer.hpp"
#include "configuration.hpp"
#include "wifi.hpp"
#include "mqtt.hpp"
#include "watchdog.hpp"


void commandLoop()
{
    
}

int main()
{   
    stdio_init_all();
    Configuration config;

    I2CBus i2cBus;
    I2CDevice i2cDevice;
    EnvironmentSensor environmentSensor;
    TemperatureController temperatureController;

    Switch heatSwitch(HEATER_PIN);
    Switch coolSwitch(COOLER_PIN);
    Switch fanSwitch(FAN_PIN);

    Hvac hvac;
    Wifi wifi;
    Mqtt mqtt;
    Watchdog watchdog;
    Producer producer;
    Thermostat thermostat;
    CommandParser commandParser;
    Repl repl;


    // Set up the application context
    ThermostatContext context;
    context.config = &config;
    context.i2cBus = &i2cBus;
    context.i2cDevice = &i2cDevice;
    context.sensor = &environmentSensor;
    context.tempController = &temperatureController;
    context.heatSwitch = &heatSwitch;
    context.coolSwitch = &coolSwitch;
    context.fanSwitch = &fanSwitch;
    context.hvac = &hvac;
    context.wifi = &wifi;
    context.mqtt = &mqtt;
    context.watchdog = &watchdog;
    context.producer = &producer;
    context.commandParser = &commandParser;
    context.repl = &repl;


    ThermostatError err = context.initialize();
    thermostat.initialize(&context);

    err = thermostat.connect();
    
    while (true) {
        ThermostatCommand command;
        ThermostatError err = repl.read(&command);
        if (err == THERMOSTAT_OK) {
            thermostat.executeCommand(&command);
            repl.print(&command);
        }
        thermostat.update();
        ThermostatData currentData;
        thermostat.getData(&currentData);
        producer.update(&currentData);
        sleep_ms(1000);
    }
}
