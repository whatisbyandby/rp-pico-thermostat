#ifndef THERMOSTAT_CONTEXT_HPP
#define THERMOSTAT_CONTEXT_HPP

class Thermostat;
class Switch;
class TemperatureController;
class Hvac;
class Watchdog;
class I2CBus;
class I2CDevice;
class CommandParser;
class EnvironmentSensor;
class Repl;
class Producer;
class Configuration;
class Wifi;
class Mqtt;


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
};

#endif // THERMOSTAT_CONTEXT_HPP
