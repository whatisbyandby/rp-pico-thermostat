#ifndef THERMOSTAT_CONTEXT_HPP
#define THERMOSTAT_CONTEXT_HPP

#include "thermostat_common.hpp"
#include "thermostat.hpp"
#include "gpio.hpp"
#include "temperature_controller.hpp"
#include "hvac.hpp"
#include "watchdog.hpp"
#include "i2c_bus.hpp"
#include "command_parser.hpp"
#include "environment_sensor.hpp"
#include "repl.hpp"
#include "producer.hpp"
#include "configuration.hpp"
#include "wifi.hpp"
#include "mqtt.hpp"

class ThermostatContext
{
public:
    EnvironmentSensor *sensor;
    TemperatureController *tempController;
    Hvac *hvac;
    Wifi *wifi;
    Mqtt *mqtt;
    Watchdog *watchdog;
    Configuration *config;

    I2CBus *i2cBus;
    I2CDevice *i2cDevice;

    Switch *heatSwitch;
    Switch *coolSwitch;
    Switch *fanSwitch;

    CommandParser *commandParser;
    Repl *repl;

    Producer *producer;
    Thermostat *thermostat;

    ThermostatError initialize() {
        tempController->initialize();
        hvac->initialize(heatSwitch, coolSwitch, fanSwitch);
        wifi->initialize(config);
        mqtt->initialize(config);
        watchdog->initialize();
        producer->initalize(mqtt);
        config->load();
        i2cBus->initialize();
        i2cDevice->initialize(i2cBus, 0x38);
        repl->initialize(commandParser);
        sensor->initialize(i2cDevice);
        thermostat->initialize(sensor, tempController, hvac);
        return THERMOSTAT_OK;
    }
};

#endif // THERMOSTAT_CONTEXT_HPP
