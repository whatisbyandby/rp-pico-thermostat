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
            std::cout << "->" << std::endl;
        }
    }
}

int main()
 {
    stdio_init_all();

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

    thermostat.setMode(HEATING);

    ThermostatError err = thermostat.initialize();

    if (err != THERMOSTAT_OK)
    {
        std::cout << "Error initializing thermostat" << std::endl;
        char errorMessage[256];
        thermostat.getCurrentErrorMessage(errorMessage);
        std::cout << errorMessage << std::endl;
        while (true) {
            tight_loop_contents();
        }
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

    multicore_launch_core1(commandLoop);

    while (true)
    {
        thermostat.update();
        ThermostatState currentState;
        thermostat.getState(&currentState);

        producer.update(&currentState);
        sleep_ms(5000);
    }
}
