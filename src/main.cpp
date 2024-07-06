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
#include "thermostat_context.hpp"

bool thermostat_timer_callback(struct repeating_timer *t) {
    ThermostatContext *ctx = (ThermostatContext *) t->user_data;
    ctx->thermostat->update();
    ThermostatData data;
    ctx->thermostat->getData(&data);
    ctx->producer->update(&data);
    return true;
}

void command_callback(ThermostatCommand *command, void *arg) {
    ThermostatContext *ctx = (ThermostatContext *) arg;
    ctx->commandParser->parseString(command);
    ctx->thermostat->executeCommand(command);
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
    CommandParser commandParser;
    Repl repl;
    Thermostat thermostat;


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
    context.thermostat = &thermostat;

    ThermostatError err = context.initialize();
    

    err = wifi.connect();
    err = mqtt.connect();

    err = mqtt.subscribe("home/thermostat/command", command_callback, &context);

    struct repeating_timer timer;
    add_repeating_timer_ms(-5000, thermostat_timer_callback, &context, &timer);
    
    while (true) {
        ThermostatCommand command;
        ThermostatError err = repl.read(&command);
        sleep_ms(10);
        if (err == THERMOSTAT_OK) {
            thermostat.executeCommand(&command);
            repl.print(&command);
        }
        
    }
}
