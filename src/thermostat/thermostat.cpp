#include "thermostat.hpp"
#include "thermostat_common.hpp"
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>


Thermostat::Thermostat(EnvironmentSensor *environmentSensor, TemperatureController *temperatureController, HVAC *hvac)
{
    temperatureUnits = FAHRENHEIT;
    initalized = false;
    mode = OFF;

    this->environmentSensor = environmentSensor;
    this->temperatureController = temperatureController;
    this->hvac = hvac;
}

Thermostat::~Thermostat()
{
}


ThermostatError Thermostat::initialize()
{
    if (environmentSensor == NULL || temperatureController == NULL || hvac == NULL)
    {
        return THERMOSTAT_ERROR;
    }
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

ThermostatMode Thermostat::getMode()
{
    return mode;
}

ThermostatError Thermostat::setMode(ThermostatMode newMode)
{

    ThermostatError err = validateThermostatMode(newMode);
    if (err != THERMOSTAT_OK)
    {
        return err;
    }
    mode = newMode;
    return THERMOSTAT_OK;
}

ThermostatError Thermostat::setTargetTemperature(double targetTemperature) {
    double temperatureInStandardUnits = getTemperatureInStandardUnits(targetTemperature);
    return temperatureController->setTargetTemperature(temperatureInStandardUnits);
}

double Thermostat::getTargetTemperature() {
    double temperatureInStandardUnits = temperatureController->getTargetTemperature();
    return getTemperatureInCurrentUnits(temperatureInStandardUnits);
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

HVACState Thermostat::getDesiredHVACState(TemperatureState temperatureState, HVACState currentHVACState)
{

    if (mode == OFF)
    {
        return ALL_OFF;
    }

    if (mode == ERROR)
    {
        return ALL_OFF;
    }

    if (mode == FAN_ONLY)
    {
        return FAN_ON;
    }

    if (mode == HEATING)
    {
        if (temperatureState == UNDER_TEMPERATURE)
        {
            return HEATER_ON;
        }
        if (temperatureState == UNDER_TEMPERATURE_IN_RANGE && currentHVACState == HEATER_ON)
        {
            return HEATER_ON;
        }
    }

    if (mode == COOLING)
    {
        if (temperatureState == OVER_TEMPERATURE)
        {
            return COOLER_ON;
        }
        if (temperatureState == OVER_TEMPERATURE_IN_RANGE && currentHVACState == COOLER_ON)
        {
            return COOLER_ON;
        }
    }

    return ALL_OFF;
}


ThermostatError Thermostat::update() {
    // if (!isInitialized())
    // {
    //     return THERMOSTAT_ERROR;
    // }


    environmentSensor->readTemperatureHumidity(&currentTemperature, &currentHumidity);

    TemperatureState temperatureState = temperatureController->checkTemperature(currentTemperature);

    HVACState desiredState = getDesiredHVACState(temperatureState, hvac->getCurrentState());

    hvac->setDesiredState(desiredState);


    return THERMOSTAT_OK;
}

ThermostatError Thermostat::printState(std::string *output) {

    std::ostringstream oss;

    oss << "Current Temperature: " << getTemperatureInCurrentUnits(currentTemperature) << std::endl;
    oss << "Target Temperature " << getTemperatureInCurrentUnits(temperatureController->getTargetTemperature()) << std::endl;
    oss << "Current Humidity: " << currentHumidity << std::endl;
    oss << "Current HVAC State: " <<  hvacStateToString(hvac->getCurrentState()) << std::endl;
    oss << "Current Thermostat Mode: " << thermostatModeToString(mode) << std::endl;
    oss << "Current Temperature Units: " << temperatureUnitsToString(temperatureUnits) << std::endl;

    *output = oss.str();
    return THERMOSTAT_OK;
}
