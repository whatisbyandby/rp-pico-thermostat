#include "hvac.hpp"

HVAC::HVAC(Switch *heater, Switch *ac, Switch *fan)
{
    this->heater = heater;
    this->ac = ac;
    this->fan = fan;
    currentState = ALL_OFF;
}

HVACState HVAC::readCurrentState() {
    bool heaterState = heater->isOn();
    bool acState = ac->isOn();
    bool fanState = fan->isOn();
    
    if (heaterState) {
        return HEATER_ON;
    } else if (acState) {
        return COOLER_ON;
    } else if (fanState) {
        return FAN_ON;
    } else {
        return ALL_OFF;
    }
}

ThermostatError HVAC::setDesiredState(HVACState state) {


    if (state == ALL_OFF) {
        heater->turnOff();
        ac->turnOff();
        fan->turnOff();
        currentState = readCurrentState();
        return THERMOSTAT_OK;
    } 

    if (state == HEATER_ON) {
        heater->turnOn();
        ac->turnOff();
        fan->turnOff();
        currentState = readCurrentState();
        return THERMOSTAT_OK;
    }

    if (state == COOLER_ON) {
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

HVACState HVAC::getCurrentState() {
    return currentState;
}

