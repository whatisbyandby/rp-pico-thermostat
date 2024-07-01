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


void commandLoop()
{
    
}

int main()
{   
    Configuration config;
    I2CBus i2cBus;
    I2CDevice i2cDevice(&i2cBus, 0x76);
    EnvironmentSensor environmentSensor(&i2cDevice);
    TemperatureController temperatureController;

    Switch heatSwitch(HEATER_PIN);
    Switch coolSwitch(COOLER_PIN);
    Switch fanSwitch(FAN_PIN);

    HVAC hvac(&heatSwitch, &coolSwitch, &fanSwitch);
    Wifi wifi;
    Mqtt mqtt(&config);
    Watchdog watchdog;
    Producer producer(&mqtt);
    Thermostat thermostat(&environmentSensor, &temperatureController, &hvac, &wifi, &mqtt, &watchdog);
}
