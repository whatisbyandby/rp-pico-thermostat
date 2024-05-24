#include "hvac.hpp"

HVAC::HVAC() {

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
        return IDLE;
    }
}

ThermostatError HVAC::setDesiredState(HVACState state) {

    if (state == currentState) {
        return THERMOSTAT_OK;
    }

    if (state == IDLE) {
        heater->turnOff();
        ac->turnOff();
        fan->turnOff();
        currentState = readCurrentState();
        // currentState = state;
        return THERMOSTAT_OK;
    } 

    if (state == HEATER_ON) {
        heater->turnOn();
        ac->turnOff();
        fan->turnOff();
        currentState = readCurrentState();
        // currentState = state;
        return THERMOSTAT_OK;
    }

    if (state == COOLER_ON) {
        heater->turnOff();
        ac->turnOn();
        fan->turnOff();
        currentState = readCurrentState();
        // currentState = state;
        return THERMOSTAT_OK;
    }

    if (state == FAN_ON) {
        heater->turnOff();
        ac->turnOff();
        fan->turnOn();
        currentState = readCurrentState();
        // currentState = state;
        return THERMOSTAT_OK;
    }

    return THERMOSTAT_ERROR;
}

HVACState HVAC::getCurrentState() {
    return currentState;
}

void HVAC::setHeater(Switch *heater) {
    this->heater = heater;
}

void HVAC::setAC(Switch *ac) {
    this->ac = ac;
}

void HVAC::setFan(Switch *fan) {
    this->fan = fan;
}

