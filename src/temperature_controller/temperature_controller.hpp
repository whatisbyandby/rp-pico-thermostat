#ifndef TEMPERATURE_CONTROLLER_HPP
#define TEMPERATURE_CONTROLLER_HPP

#include "thermostat_common.hpp"

class TemperatureController {
    public:
        TemperatureController();
        ~TemperatureController();

        ThermostatError setTargetTemperature(double targetTemperature);
        double getTargetTemperature();

        ThermostatError setTemperatureRange(double temperatureRange);
        double getTemperatureRange();

        TemperatureState checkTemperature(double currentTemperature);
    private:
        double targetTemperature;
        double temperatureRange;
        ThermostatError validateTargetTemperature(double targetTemperature);
        ThermostatError validateTemperatureRange(double temperatureRange);
};

#endif // TEMPERATURE_CONTROLLER_HPP