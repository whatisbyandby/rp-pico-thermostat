#include "hvac.hpp"

HVAC::HVAC() {

}

ThermostatError HVAC::setDesiredState(HVACState state) {
    currentState = state;
    return THERMOSTAT_OK;
}

HVACState HVAC::getCurrentState() {
    return currentState;
}

