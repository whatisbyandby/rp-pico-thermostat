#include "thermostat.hpp"
#include "thermostat_common.hpp"
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string.h>


Thermostat::Thermostat(EnvironmentSensor *environmentSensor, TemperatureController *temperatureController, HVAC *hvac, Wifi *wifi, Mqtt *mqtt, Watchdog *watchdog)
{
    temperatureUnits = FAHRENHEIT;
    initalized = false;
    mode = OFF;

    this->environmentSensor = environmentSensor;
    this->temperatureController = temperatureController;
    this->hvac = hvac;
    this->wifi = wifi;
    this->mqtt = mqtt;
    this->watchdog = watchdog;
    this->currentError = THERMOSTAT_OK;
    this->currentHumidity = -1;
    this->currentTemperature = -1;
    memset(this->errorString, 0, sizeof(this->errorString));
}

Thermostat::~Thermostat()
{
}


ThermostatError Thermostat::initialize()
{
    if (environmentSensor == NULL)
    {
        strcpy(errorString, "Environment Sensor is NULL");
        currentError = THERMOSTAT_INIT_FAILED;
        return currentError;
    }

    if (temperatureController == NULL)
    {
        strcpy(errorString, "Temperature Controller is NULL");
        currentError = THERMOSTAT_INIT_FAILED;
        return currentError;
    }

    if (hvac == NULL)
    {
        strcpy(errorString, "HVAC is NULL");
        currentError = THERMOSTAT_INIT_FAILED;
        return currentError;
    }

    initalized = true;

    currentError = updateTemperatureHumidity();
    

    if (currentError != THERMOSTAT_OK)
    {
        initalized = false;
        return currentError;
    }
    
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

ThermostatError Thermostat::getCurrentError()
{
    return currentError;
}

ThermostatError Thermostat::getCurrentErrorMessage(char *errorString)
{
    strcpy(errorString, this->errorString);
    return THERMOSTAT_OK;
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

ThermostatState Thermostat::getDesiredHVACState(TemperatureState temperatureState, ThermostatState currentHVACState)
{

    if (mode == OFF)
    {
        return IDLE;
    }

    if (mode == FAN_ONLY)
    {
        return FAN_ON;
    }

    if (mode == HEAT)
    {
        if (temperatureState == UNDER_TEMPERATURE)
        {
            return HEATING;
        }
        if (temperatureState == UNDER_TEMPERATURE_IN_RANGE && currentHVACState == HEATING)
        {
            return HEATING;
        }
    }

    if (mode == COOL)
    {
        if (temperatureState == OVER_TEMPERATURE)
        {
            return COOLING;
        }
        if (temperatureState == OVER_TEMPERATURE_IN_RANGE && currentHVACState == COOLING)
        {
            return COOLING;
        }
    }

    return IDLE;
}

ThermostatError Thermostat::updateTemperatureHumidity()
{
    if (!isInitialized())
    {
        currentError = THERMOSTAT_NOT_INITALIZED;
        return currentError;
    }

    environmentSensor->readTemperatureHumidity(&currentTemperature, &currentHumidity);

    return validateReading();
}


ThermostatError Thermostat::validateReading() {

    if (currentHumidity < 0 || currentTemperature < 0)
    {   
        strcpy(errorString, "Temperature or Humidity values are under a reasonable value");
        currentError = THERMOSTAT_SENSOR_ERROR;
        return currentError;
    }

    if (currentHumidity > 100 || currentTemperature > 100)
    {   
        strcpy(errorString, "Temperature or Humidity values are over a reasonable value");
        currentError = THERMOSTAT_SENSOR_ERROR;
        return currentError;
    }

    return THERMOSTAT_OK;
}


ThermostatError Thermostat::update() {

    if (!isInitialized())
    {
        currentError = THERMOSTAT_NOT_INITALIZED;
        return currentError;
    }


    updateTemperatureHumidity();

    if (currentError != THERMOSTAT_OK)
    {
        return currentError;
    }

    TemperatureState temperatureState = temperatureController->checkTemperature(currentTemperature);

    ThermostatState desiredState = getDesiredHVACState(temperatureState, hvac->getCurrentState());

    currentError = hvac->setDesiredState(desiredState);

    return currentError;
}

ThermostatError Thermostat::getData(ThermostatData *currentState) {
    currentState->mode = this->getMode();
    currentState->temperatureUnits = this->getTemperatureUnits();
    currentState->currentTemperature = this->getTemperatureInCurrentUnits(currentTemperature);
    currentState->currentTemperatureStandardUnits = this->currentTemperature;
    currentState->targetTemperature = this->getTargetTemperature();
    currentState->targetTemperatureStandardUnits = temperatureController->getTargetTemperature();
    currentState->temperatureRange = temperatureController->getTemperatureRange();
    currentState->currentHumidity = this->currentHumidity;
    currentState->hvacState = hvac->getCurrentState();
    currentState->error = currentError;

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
