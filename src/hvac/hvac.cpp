#include "hvac.hpp"

Hvac::Hvac()
{
}

ThermostatError Hvac::initialize(ThermostatContext *context)
{
    this->context = context;
    currentState = IDLE;
    return THERMOSTAT_OK;
}

ThermostatState Hvac::readCurrentState()
{
    bool heaterState = context->heatSwitch->isOn();
    bool acState = context->coolSwitch->isOn();
    bool fanState = context->fanSwitch->isOn();

    if (heaterState)
    {
        return HEATING;
    }
    else if (acState)
    {
        return COOLING;
    }
    else if (fanState)
    {
        return FAN_ON;
    }
    else
    {
        return IDLE;
    }
}

ThermostatError Hvac::setDesiredState(ThermostatState state)
{

    if (state == IDLE)
    {
        context->heatSwitch->turnOff();
        context->coolSwitch->turnOff();
        context->fanSwitch->turnOff();
        currentState = readCurrentState();
        return THERMOSTAT_OK;
    }

    if (state == HEATING)
    {
        context->heatSwitch->turnOn();
        context->coolSwitch->turnOff();
        context->fanSwitch->turnOff();
        currentState = readCurrentState();
        return THERMOSTAT_OK;
    }

    if (state == COOLING)
    {
        context->heatSwitch->turnOff();
        context->coolSwitch->turnOn();
        context->fanSwitch->turnOff();
        currentState = readCurrentState();
        return THERMOSTAT_OK;
    }

    if (state == FAN_ON)
    {
        context->heatSwitch->turnOff();
        context->coolSwitch->turnOff();
        context->fanSwitch->turnOn();
        currentState = readCurrentState();
        return THERMOSTAT_OK;
    }

    context->heatSwitch->turnOff();
    context->coolSwitch->turnOff();
    context->fanSwitch->turnOff();
    currentState = readCurrentState();
    return THERMOSTAT_ERROR;
}

ThermostatState Hvac::getCurrentState()
{
    return currentState;
}
