#include "temperature_controller.hpp"

TemperatureController::TemperatureController()
{
    targetTemperature = 20.0;
    temperatureRange = 1.0;
}

TemperatureController::~TemperatureController()
{
}

ThermostatError TemperatureController::validateTemperatureRange(double temperatureRange)
{
    if (temperatureRange < 0.5 || temperatureRange > 2)
    {
        return THERMOSTAT_INVALID_INPUT;
    }
    return THERMOSTAT_OK;
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

ThermostatError TemperatureController::setTemperatureRange(double newTemperatureRange)
{

    ThermostatError error = validateTemperatureRange(newTemperatureRange);
    if (error != THERMOSTAT_OK)
    {
        return error;
    }
    temperatureRange = newTemperatureRange;
    return THERMOSTAT_OK;
}

double TemperatureController::getTemperatureRange()
{
    return temperatureRange;
}

TemperatureState TemperatureController::checkTemperature(double currentTemperature)
{
    if (currentTemperature < targetTemperature - temperatureRange)
    {
        return UNDER_TEMPERATURE;
    }
    else if (currentTemperature > targetTemperature + temperatureRange)
    {
        return OVER_TEMPERATURE;
    }
    return IN_RANGE;
}