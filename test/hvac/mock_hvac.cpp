
#include <CppUTestExt/MockSupport.h>
#include "hvac.hpp"

Hvac::Hvac()
{
    currentState = IDLE;
}

ThermostatError Hvac::setDesiredState(ThermostatState state) {
    return (ThermostatError) mock().actualCall("HVAC::setDesiredState").withParameter("state", state).returnIntValueOrDefault(THERMOSTAT_OK);
}

ThermostatState Hvac::getCurrentState() {
    return (ThermostatState) mock().actualCall("HVAC::getCurrentState").returnIntValueOrDefault(IDLE);
}