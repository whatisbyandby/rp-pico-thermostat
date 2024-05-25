#ifndef THERMOSTAT_HPP
#define THERMOSTAT_HPP

#include "environment_sensor.hpp"
#include "temperature_controller.hpp"
#include "hvac.hpp"
#include "thermostat_common.hpp"


class Thermostat {
    public:
        Thermostat(EnvironmentSensor *environmentSensor, TemperatureController *temperatureController, HVAC *hvac);
        ~Thermostat();

        ThermostatError initialize();
        bool isInitialized();


        ThermostatError setTemperatureUnits(TemperatureUnits temperatureUnits);
        TemperatureUnits getTemperatureUnits();

        HVACState getDesiredHVACState(TemperatureState temperatureState, HVACState currentHVACState);

        ThermostatMode getMode();
        ThermostatError setMode(ThermostatMode mode);

        double getTemperatureInStandardUnits(double temperature);
        double getTemperatureInCurrentUnits(double temperatureInStandardUnits);

        ThermostatError update();

        void printState();

    
    private:
        TemperatureUnits temperatureUnits;
        
        ThermostatMode mode;
        bool initalized;
        EnvironmentSensor *environmentSensor;
        TemperatureController *temperatureController;
        HVAC *hvac;

        double currentTemperature;
        double currentHumidity;
        
};

#endif // THERMOSTAT_HPP