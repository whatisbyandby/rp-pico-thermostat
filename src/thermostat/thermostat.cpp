#include "thermostat.hpp"
#include <cstddef>

double convertFahrenheitToCelsius(double fahrenheit)
{
    return (fahrenheit - 32) * 5.0 / 9.0;
}

double convertCelsiusToFahrenheit(double celsius)
{
    return celsius * 9.0 / 5.0 + 32;
}

Thermostat::Thermostat()
{
    // Defaults to 20°C (68°F)
    targetTemperature = 20.0;
    temperatureUnits = FAHRENHEIT;
    environmentSensor = NULL;
    initalized = false;
}

Thermostat::~Thermostat()
{
    if (environmentSensor != NULL)
    {
        delete environmentSensor;
    }
}

ThermostatError Thermostat::setEnvironmentSensor(EnvironmentSensor *newEnvironmentSensor)
{
    if (newEnvironmentSensor == NULL)
    {
        return THERMOSTAT_INVALID_INPUT;
    }
    environmentSensor = newEnvironmentSensor;
    return THERMOSTAT_OK;
}

ThermostatError Thermostat::initialize()
{
    if (environmentSensor == NULL) {
        return THERMOSTAT_ERROR;
    }
    initalized = true;
    return THERMOSTAT_OK;
}

bool Thermostat::isInitialized()
{
    return initalized;

}


ThermostatError Thermostat::setTargetTemperature(double newTemperature)
{   
    newTemperature = getTemperatureInStandardUnits(newTemperature);

    ThermostatError error = validateTargetTemperature(newTemperature);
    if (error != THERMOSTAT_OK)
    {
        return error;
    }

    targetTemperature = newTemperature;
    return THERMOSTAT_OK;
}

double Thermostat::getTargetTemperature()
{
    return getTemperatureInCurrentUnits(targetTemperature);
}

ThermostatError Thermostat::setTemperatureUnits(TemperatureUnits newUnits)
{
    temperatureUnits = newUnits;
    return THERMOSTAT_OK;
}

TemperatureUnits Thermostat::getTemperatureUnits()
{
    return temperatureUnits;
}

ThermostatError Thermostat::validateTargetTemperature(double newTemperature)
{
    if (newTemperature < 10 || newTemperature > 30)
    {
        return THERMOSTAT_INVALID_INPUT;
    }
    return THERMOSTAT_OK;
}

double Thermostat::getTemperatureInStandardUnits(double temperature)
{
    if (temperatureUnits == FAHRENHEIT)
    {
        return convertFahrenheitToCelsius(temperature);
    }
    return temperature;
}

double Thermostat::getTemperatureInCurrentUnits(double temperatureInStandardUnits)
{
    if (temperatureUnits == FAHRENHEIT)
    {
        return convertCelsiusToFahrenheit(temperatureInStandardUnits);
    }
    return temperatureInStandardUnits;
}

