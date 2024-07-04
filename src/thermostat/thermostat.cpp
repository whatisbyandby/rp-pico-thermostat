#include "thermostat.hpp"
#include "temperature_controller.hpp"
#include "thermostat_common.hpp"
#include <cstddef>
#include <iostream>
#include <sstream>
#include <string.h>

Thermostat::Thermostat()
{

}

Thermostat::~Thermostat()
{
}

ThermostatError Thermostat::initialize(ThermostatContext *context)
{

    this->context = context;

    temperatureUnits = FAHRENHEIT;
    initialized = false;
    mode = OFF;

    this->currentError = THERMOSTAT_OK;
    this->currentHumidity = -1;
    this->currentTemperature = -1;
    memset(this->errorString, 0, sizeof(this->errorString));

    initialized = true;
    return THERMOSTAT_OK;
}

bool Thermostat::isInitialized()
{
    return initialized;
}

ThermostatError Thermostat::connect() {
    int num_retries = 0;
    while (context->wifi->connect() != THERMOSTAT_OK) {
        if (num_retries > 3) {
            return THERMOSTAT_CONNECTION_ERROR;
        }
        num_retries++;
    }

    context->mqtt->connect();

    return THERMOSTAT_OK;
}

ThermostatError Thermostat::setTemperatureUnits(TemperatureUnits newUnits)
{
    //TODO need to add validation to ensure it's not possible to set invalid units
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

ThermostatError Thermostat::setTargetTemperature(double targetTemperature)
{
    double temperatureInStandardUnits = getTemperatureInStandardUnits(targetTemperature);
    return context->tempController->setTargetTemperature(temperatureInStandardUnits);
}

double Thermostat::getTargetTemperature()
{
    double temperatureInStandardUnits = context->tempController->getTargetTemperature();
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

    context->sensor->readTemperatureHumidity(&currentTemperature, &currentHumidity);

    return validateReading();
}

ThermostatError Thermostat::validateReading()
{

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

ThermostatError Thermostat::update()
{

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

    TemperatureState temperatureState = context->tempController->checkTemperature(currentTemperature);

    ThermostatState desiredState = getDesiredHVACState(temperatureState, context->hvac->getCurrentState());

    currentError = context->hvac->setDesiredState(desiredState);

    return currentError;
}

ThermostatError Thermostat::getData(ThermostatData *currentState)
{
    currentState->mode = this->getMode();
    currentState->temperatureUnits = this->getTemperatureUnits();
    currentState->currentTemperature = this->getTemperatureInCurrentUnits(currentTemperature);
    currentState->currentTemperatureStandardUnits = this->currentTemperature;
    currentState->targetTemperature = this->getTargetTemperature();
    currentState->targetTemperatureStandardUnits = context->tempController->getTargetTemperature();
    currentState->temperatureRange = context->tempController->getTemperatureRange();
    currentState->currentHumidity = this->currentHumidity;
    currentState->temperatureState = context->tempController->checkTemperature(currentTemperature);
    currentState->hvacState = context->hvac->getCurrentState();
    currentState->error = currentError;

    return THERMOSTAT_OK;
}

ThermostatError Thermostat::printState(std::string *output)
{

    std::ostringstream oss;

    oss << "Current Temperature: " << getTemperatureInCurrentUnits(currentTemperature) << std::endl;
    oss << "Target Temperature " << getTemperatureInCurrentUnits(context->tempController->getTargetTemperature()) << std::endl;
    oss << "Current Humidity: " << currentHumidity << std::endl;
    oss << "Current HVAC State: " << hvacStateToString(context->hvac->getCurrentState()) << std::endl;
    oss << "Current Thermostat Mode: " << thermostatModeToString(mode) << std::endl;
    oss << "Current Temperature Units: " << temperatureUnitsToString(temperatureUnits) << std::endl;

    *output = oss.str();
    return THERMOSTAT_OK;
}

// ThermostatError Thermostat::validateArguments()
// {
//     if (environmentSensor == NULL)
//     {
//         strcpy(errorString, "Environment Sensor is NULL");
//         currentError = THERMOSTAT_INIT_FAILED;
//         return currentError;
//     }

//     if (temperatureController == NULL)
//     {
//         strcpy(errorString, "Temperature Controller is NULL");
//         currentError = THERMOSTAT_INIT_FAILED;
//         return currentError;
//     }

//     if (hvac == NULL)
//     {
//         strcpy(errorString, "HVAC is NULL");
//         currentError = THERMOSTAT_INIT_FAILED;
//         return currentError;
//     }

//     if (wifi == NULL)
//     {
//         strcpy(errorString, "Wifi is NULL");
//         currentError = THERMOSTAT_INIT_FAILED;
//         return currentError;
//     }

//     if (mqtt == NULL)
//     {
//         strcpy(errorString, "Mqtt is NULL");
//         currentError = THERMOSTAT_INIT_FAILED;
//         return currentError;
//     }

//     if (watchdog == NULL)
//     {
//         strcpy(errorString, "Watchdog is NULL");
//         currentError = THERMOSTAT_INIT_FAILED;
//         return currentError;
//     }

//      if (config == NULL)
//     {
//         strcpy(errorString, "Configuration is NULL");
//         currentError = THERMOSTAT_INIT_FAILED;
//         return currentError;
//     }

//     return THERMOSTAT_OK;
// }

ThermostatError Thermostat::executeCommand(ThermostatCommand *command)
{   
    if (command->command_type == INVALID_COMMAND) {
        command->resultString = "[ERROR] Invalid command";
        return THERMOSTAT_OK;
    }
    ThermostatError error = THERMOSTAT_OK;
    std::ostringstream oss;
    switch (command->command_type) {
        case HELP:
            oss << "[OK] ";
            oss << "Printing help: " << std::endl;
            oss << "temperature <temperature> - Set the target temperature in the current units" << std::endl;
            oss << "mode <mode> - Set the mode of operation" << std::endl;
            oss << "units <units> - Set the units of the thermostat" << std::endl;
            oss << "state - Print the current state of the thermostat" << std::endl;

            command->resultString = oss.str();
            return THERMOSTAT_OK;
        case SET_TEMPERATURE:
            error = this->setTargetTemperature(command->parameter);
            if (error != THERMOSTAT_OK) {
                oss << "[ERROR] Error setting target temperature ";
                command->resultString = oss.str();
                return error;
            }
            oss << "[OK] Target Temperature set to " << this->getTargetTemperature();
            command->resultString = oss.str();
            return error;
        case SET_MODE:
        {
            int parsedValue = (int)command->parameter;
            error = this->setMode((ThermostatMode)parsedValue);
            if (error != THERMOSTAT_OK) {
                oss << "[ERROR] Error setting mode ";
                command->resultString = oss.str();
                return error;
            }
            oss << "[OK] Mode set to " << thermostatModeToString(this->getMode());
            command->resultString = oss.str();
            return error;
        }
        
        case SET_UNITS:
        {
            int parsedValue = (int)command->parameter;
            error = this->setTemperatureUnits((TemperatureUnits)parsedValue);
            if (error != THERMOSTAT_OK) {
                oss << "[ERROR] Error setting units ";
                command->resultString = oss.str();
                return error;
            }
            oss << "[OK] Units set to " << temperatureUnitsToString(this->getTemperatureUnits());
            command->resultString = oss.str();
            return error;
        }

        case PRINT_STATE:
        {
            std::string stateString;
            error = this->printState(&stateString);
            oss << "[OK]" << std::endl << stateString;
            command->resultString = oss.str();
            return error;
        }
        default:
            command->resultString = "[ERROR] Unknown command";
            return THERMOSTAT_UNKNOWN_COMMAND; 
    }
}
