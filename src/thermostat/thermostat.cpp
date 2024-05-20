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

