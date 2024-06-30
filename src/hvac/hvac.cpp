#include "hvac.hpp"

HVAC::HVAC(Switch *heater, Switch *ac, Switch *fan)
{
    this->heater = heater;
    this->ac = ac;
    this->fan = fan;
    currentState = IDLE;
}

ThermostatState HVAC::readCurrentState() {
    bool heaterState = heater->isOn();
    bool acState = ac->isOn();
    bool fanState = fan->isOn();
    
    if (heaterState) {
        return HEATING;
    } else if (acState) {
        return COOLING;
    } else if (fanState) {
        return FAN_ON;
    } else {
        return IDLE;
    }
}

ThermostatError HVAC::setDesiredState(ThermostatState state) {


    if (state == IDLE) {
        heater->turnOff();
        ac->turnOff();
        fan->turnOff();
        currentState = readCurrentState();
        return THERMOSTAT_OK;
    } 

    if (state == HEATING) {
        heater->turnOn();
        ac->turnOff();
        fan->turnOff();
        currentState = readCurrentState();
        return THERMOSTAT_OK;
    }

    if (state == COOLING) {
        heater->turnOff();
        ac->turnOn();
        fan->turnOff();
        currentState = readCurrentState();
        return THERMOSTAT_OK;
    }

    if (state == FAN_ON) {
        heater->turnOff();
        ac->turnOff();
        fan->turnOn();
        currentState = readCurrentState();
        return THERMOSTAT_OK;
    }

    heater->turnOff();
    ac->turnOff();
    fan->turnOff();
    currentState = readCurrentState();
    return THERMOSTAT_ERROR;
}

ThermostatState HVAC::getCurrentState() {
    return currentState;
}

