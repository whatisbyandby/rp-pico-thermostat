#include "thermostat.hpp"
#include "thermostat_common.hpp"
#include <cstddef>


Thermostat::Thermostat()
{
    // Defaults to 20°C (68°F)
    temperatureUnits = FAHRENHEIT;
    initalized = false;
}

Thermostat::~Thermostat()
{
}


ThermostatError Thermostat::initialize()
{
    initalized = true;
    return THERMOSTAT_OK;
}

bool Thermostat::isInitialized()
{
    return initalized;

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

HVACState Thermostat::getDesiredHVACState(TemperatureState temperatureState, ThermostatMode thermostatMode, HVACState currentHVACState)
{

    if (thermostatMode == OFF)
    {
        return ALL_OFF;
    }

    if (thermostatMode == ERROR)
    {
        return ALL_OFF;
    }

    if (thermostatMode == FAN_ONLY)
    {
        return FAN_ON;
    }

    if (thermostatMode == HEATING)
    {
        if (temperatureState == UNDER_TEMPERATURE)
        {
            return HEATER_ON;
        }
        if (temperatureState == IN_RANGE && currentHVACState == HEATER_ON)
        {
            return HEATER_ON;
        }
        if (temperatureState == OVER_TEMPERATURE)
        {
            return IDLE;
        }
    }

    if (thermostatMode == COOLING)
    {
        if (temperatureState == OVER_TEMPERATURE)
        {
            return COOLER_ON;
        }
        if (temperatureState == IN_RANGE && currentHVACState == COOLER_ON)
        {
            return COOLER_ON;
        }
        if (temperatureState == UNDER_TEMPERATURE)
        {
            return IDLE;
        }
    }

    return ALL_OFF;
}

