#ifndef TEMPERATURE_CONTROLLER_HPP
#define TEMPERATURE_CONTROLLER_HPP

#include "thermostat_common.hpp"

class TemperatureController {
    public:
        TemperatureController();
        ~TemperatureController();

        ThermostatError setTargetTemperature(double targetTemperature);
        double getTargetTemperature();
    private:
        double targetTemperature;
        ThermostatError validateTargetTemperature(double targetTemperature);
};

#endif // TEMPERATURE_CONTROLLER_HPP