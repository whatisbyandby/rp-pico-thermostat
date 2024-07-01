#ifndef THERMOSTAT_HPP
#define THERMOSTAT_HPP

#include "environment_sensor.hpp"
#include "temperature_controller.hpp"
#include "hvac.hpp"
#include "wifi.hpp"
#include "mqtt.hpp"
#include "watchdog.hpp"
#include "thermostat_common.hpp"
#include <iostream>


class Thermostat {
    public:
        Thermostat(EnvironmentSensor *environmentSensor, TemperatureController *temperatureController, HVAC *hvac, Wifi *wifi, Mqtt *mqtt, Watchdog *watchdog);
        ~Thermostat();

        ThermostatError initialize();
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

    
    private:
        TemperatureUnits temperatureUnits;
        
        ThermostatMode mode;
        bool initalized;

        EnvironmentSensor *environmentSensor;
        TemperatureController *temperatureController;
        HVAC *hvac;
        Wifi *wifi;
        Mqtt *mqtt;
        Watchdog *watchdog;

        double currentTemperature;
        double currentHumidity;
        ThermostatError currentError;
        char errorString[256];

        ThermostatError updateTemperatureHumidity();
        ThermostatError validateReading();
};

#endif // THERMOSTAT_HPP