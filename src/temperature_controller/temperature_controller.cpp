#include "temperature_controller.hpp"

TemperatureController::TemperatureController()
{
}

TemperatureController::~TemperatureController()
{
}


ThermostatError TemperatureController::setTargetTemperature(double newTargetTemperature)
{   
    ThermostatError error = validateTargetTemperature(newTargetTemperature);
    if (error != THERMOSTAT_OK)
    {
        return error;
    }
    targetTemperature = newTargetTemperature;
    return THERMOSTAT_OK;
}

double TemperatureController::getTargetTemperature()
{
    return targetTemperature;
}

ThermostatError TemperatureController::validateTargetTemperature(double targetTemperature)
{
    if (targetTemperature < 10 || targetTemperature > 30)
    {
        return THERMOSTAT_INVALID_INPUT;
    }
    return THERMOSTAT_OK;
}