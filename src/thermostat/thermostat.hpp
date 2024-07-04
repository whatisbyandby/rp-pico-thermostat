#ifndef THERMOSTAT_HPP
#define THERMOSTAT_HPP

#include "environment_sensor.hpp"
#include "hvac.hpp"
#include "wifi.hpp"
#include "mqtt.hpp"
#include "watchdog.hpp"
#include "thermostat_common.hpp"
#include "thermostat_context.hpp"
#include <iostream>

class Thermostat {
public:
    Thermostat();
    ~Thermostat();

    ThermostatError initialize(ThermostatContext *context);
    bool isInitialized();
    ThermostatError connect();
    ThermostatError setTemperatureUnits(TemperatureUnits temperatureUnits);
    TemperatureUnits getTemperatureUnits();
    ThermostatState getDesiredHVACState(TemperatureState temperatureState, ThermostatState currentHVACState);
    ThermostatMode getMode();
    ThermostatError setMode(ThermostatMode mode);
    ThermostatError setTargetTemperature(double targetTemperature);
    double getTargetTemperature();
    double getTemperatureInStandardUnits(double temperature);
    double getTemperatureInCurrentUnits(double temperatureInStandardUnits);
    ThermostatError update();
    ThermostatError getData(ThermostatData *currentState);
    ThermostatError getCurrentError();
    ThermostatError getCurrentErrorMessage(char *errorString);
    ThermostatError printState(std::string *output);
    ThermostatError executeCommand(ThermostatCommand *command);

private:
    TemperatureUnits temperatureUnits;
    ThermostatMode mode;
    bool initialized;

    ThermostatContext *context;

    double currentTemperature;
    double currentHumidity;
    ThermostatError currentError;
    char errorString[256];

    ThermostatError updateTemperatureHumidity();
    ThermostatError validateReading();
    // ThermostatError validateArguments();
};

#endif // THERMOSTAT_HPP
