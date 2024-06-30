
#include <CppUTestExt/MockSupport.h>
#include "hvac.hpp"

HVAC::HVAC(Switch *heater, Switch *ac, Switch *fan)
{
    currentState = IDLE;
}

ThermostatError HVAC::setDesiredState(ThermostatState state) {
    return (ThermostatError) mock().actualCall("HVAC::setDesiredState").withParameter("state", state).returnIntValueOrDefault(THERMOSTAT_OK);
}

ThermostatState HVAC::getCurrentState() {
    return (ThermostatState) mock().actualCall("HVAC::getCurrentState").returnIntValueOrDefault(IDLE);
}