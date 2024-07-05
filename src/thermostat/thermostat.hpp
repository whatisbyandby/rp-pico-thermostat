#ifndef THERMOSTAT_HPP
#define THERMOSTAT_HPP

#include <iostream>

#include "environment_sensor.hpp"
#include "hvac.hpp"
#include "temperature_controller.hpp"
#include "thermostat_common.hpp"


class Thermostat {
public:
    Thermostat();
    ~Thermostat();

    ThermostatError initialize(EnvironmentSensor *environmentSensor, TemperatureController *tempController, Hvac *hvac);
    bool isInitialized();
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

    EnvironmentSensor *environmentSensor;
    TemperatureController *tempController;
    Hvac *hvac;

    double currentTemperature;
    double currentHumidity;
    ThermostatError currentError;
    char errorString[256];

    ThermostatError updateTemperatureHumidity();
    ThermostatError validateReading();
    // ThermostatError validateArguments();
};

#endif // THERMOSTAT_HPP
