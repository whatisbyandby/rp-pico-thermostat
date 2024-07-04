#include "hvac.hpp"

Hvac::Hvac()
{
}

ThermostatError Hvac::initialize(Switch *heat, Switch *cool, Switch *fan)
{
    heatSwitch = heat;
    coolSwitch = cool;
    fanSwitch = fan;
    return THERMOSTAT_OK;
}


ThermostatState Hvac::readCurrentState()
{
    bool heaterState = heatSwitch->isOn();
    bool acState = coolSwitch->isOn();
    bool fanState = fanSwitch->isOn();

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
        heatSwitch->turnOff();
        coolSwitch->turnOff();
        fanSwitch->turnOff();
        currentState = readCurrentState();
        return THERMOSTAT_OK;
    }

    if (state == HEATING)
    {
        heatSwitch->turnOn();
        coolSwitch->turnOff();
        fanSwitch->turnOff();
        currentState = readCurrentState();
        return THERMOSTAT_OK;
    }

    if (state == COOLING)
    {
        heatSwitch->turnOff();
        coolSwitch->turnOn();
        fanSwitch->turnOff();
        currentState = readCurrentState();
        return THERMOSTAT_OK;
    }

    if (state == FAN_ON)
    {
        heatSwitch->turnOff();
        coolSwitch->turnOff();
        fanSwitch->turnOn();
        currentState = readCurrentState();
        return THERMOSTAT_OK;
    }

    heatSwitch->turnOff();
    coolSwitch->turnOff();
    fanSwitch->turnOff();
    currentState = readCurrentState();
    return THERMOSTAT_ERROR;
}

ThermostatState Hvac::getCurrentState()
{
    return currentState;
}
