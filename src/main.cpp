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
#include "thermostat_controller.hpp"
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

static Thermostat *thermostat_inst;

void commandLoop()
{
    stdio_init_all();

    ThermostatController controller = ThermostatController(thermostat_inst);
    CommandParser parser = CommandParser();

    Repl repl(&parser);

    ThermostatError err = repl.init();

    while (true)
    {
        ThermostatCommand command;
        err = repl.read(&command);
        if (err == THERMOSTAT_OK)
        {
            err = controller.executeCommand(&command);
            err = repl.print(&command);
            std::cout << "-> ";
        }
    }
}

int main()
{
    stdio_init_all();
    Watchdog watchdog;

    if (watchdog.causedReboot())
    {
        std::cout << "Watchdog caused reboot" << std::endl;
        std::cout << "Delaying for 30 seconds before trying to recover" << std::endl;
        sleep_ms(30000);
    }


    Configuration configuration;
    configuration.load();


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

    thermostat.setMode(HEAT);

    ThermostatError err = thermostat.initialize();

    if (err != THERMOSTAT_OK)
    {
        std::cout << "Error initializing thermostat" << std::endl;
        char errorMessage[256];
        thermostat.getCurrentErrorMessage(errorMessage);
        std::cout << errorMessage << std::endl;
        watchdog.reset();

    }

    Wifi wifi;
    err = wifi.initalize();

    ConfigValues values;
    configuration.getConfig(&values);
    
    
    err = wifi.connect(values.ssid, values.password);

    Mqtt mqtt(&configuration);
    err = mqtt.initalize();
    err = mqtt.connect();

    Producer producer(&wifi, &mqtt);
    err = producer.initalize();

    if (err != THERMOSTAT_OK)
    {
        std::cout << "Error initializing producer" << std::endl;
        char errorMessage[256];
        thermostat.getCurrentErrorMessage(errorMessage);
        std::cout << errorMessage << std::endl;
        while (true) {
            tight_loop_contents();
        }
    }

    multicore_launch_core1(commandLoop);

    watchdog.initalize(6000);

    while (true)
    {
        err = thermostat.update();
        if (err != THERMOSTAT_OK)
        {
            std::cout << "Error updating thermostat" << std::endl;
            char errorMessage[256];
            thermostat.getCurrentErrorMessage(errorMessage);
            std::cout << errorMessage << std::endl;
            watchdog.reset();
        }
        ThermostatData currentData;
        thermostat.getData(&currentData);
        producer.update(&currentData);
        watchdog.feed();
        sleep_ms(5000);
    }
}
