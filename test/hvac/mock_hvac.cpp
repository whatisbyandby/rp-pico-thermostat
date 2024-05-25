
#include <CppUTestExt/MockSupport.h>
#include "hvac.hpp"

HVAC::HVAC(Switch *heater, Switch *ac, Switch *fan)
{
    currentState = ALL_OFF;
}

ThermostatError HVAC::setDesiredState(HVACState state) {
    return (ThermostatError) mock().actualCall("HVAC::setDesiredState").withParameter("state", state).returnIntValueOrDefault(THERMOSTAT_OK);
}

HVACState HVAC::getCurrentState() {
    return (HVACState) mock().actualCall("HVAC::getCurrentState").returnIntValueOrDefault(ALL_OFF);
}