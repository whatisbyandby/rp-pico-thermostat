#include "temperature_controller.hpp"

TemperatureController::TemperatureController()
{
}

TemperatureController::~TemperatureController()
{
}

ThermostatError TemperatureController::initialize()
{
    targetTemperature = 20.0;
    temperatureRange = 1.0;
    return THERMOSTAT_OK;
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
    if (targetTemperature < 7 || targetTemperature > 35)
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
    if (currentTemperature < targetTemperature)
    {
        return UNDER_TEMPERATURE_IN_RANGE;
    }
    if (currentTemperature > targetTemperature + temperatureRange)
    {
        return OVER_TEMPERATURE;
    }
    if (currentTemperature > targetTemperature)
    {
        return OVER_TEMPERATURE_IN_RANGE;
    }
    return IN_RANGE;
}