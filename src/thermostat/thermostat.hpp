#ifndef THERMOSTAT_HPP
#define THERMOSTAT_HPP

#include "environment_sensor.hpp"
#include "thermostat_common.hpp"


class Thermostat {
    public:
        Thermostat();
        ~Thermostat();

        ThermostatError initialize();
        bool isInitialized();


        ThermostatError setTemperatureUnits(TemperatureUnits temperatureUnits);
        TemperatureUnits getTemperatureUnits();

        HVACState getDesiredHVACState(TemperatureState temperatureState, ThermostatMode thermostatMode, HVACState currentHVACState);

    
    private:
        double targetTemperature;
        TemperatureUnits temperatureUnits;
        double getTemperatureInStandardUnits(double temperature);
        double getTemperatureInCurrentUnits(double temperatureInStandardUnits);
        bool initalized;
        
};

#endif // THERMOSTAT_HPP