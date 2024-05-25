#include "environment_sensor.hpp"
#include "i2c_bus.hpp"
#include "pico/stdlib.h"
#include "hvac.hpp"
#include "thermostat.hpp"
#include "temperature_controller.hpp"
#include "thermostat_common.hpp"
#include "pins.h"
#include "gpio.hpp"
#include <iostream>


int main()
{
    stdio_init_all();

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

    thermostat.setMode(HEATING);

    thermostat.initialize();



    while (true)
    {
        ThermostatError err = thermostat.update();

        const char *errString = thermostatErrorToString(err);

        std::cout << "Thermostat update: " << errString << std::endl;

        thermostat.printState();

        sleep_ms(1000);
    }
}