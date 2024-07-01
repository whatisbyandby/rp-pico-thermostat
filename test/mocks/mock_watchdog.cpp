#include <CppUTestExt/MockSupport.h>

#include "watchdog.hpp"


Watchdog::Watchdog()
{
}

Watchdog::~Watchdog()
{
}



ThermostatError Watchdog::initalize()
{
	return (ThermostatError) mock().actualCall("Watchdog::initialize").returnIntValueOrDefault(THERMOSTAT_OK);
}

ThermostatError Watchdog::initalize(int timeout)
{
	return (ThermostatError) mock().actualCall("Watchdog::initialize").returnIntValueOrDefault(THERMOSTAT_OK);
}


ThermostatError Watchdog::feed()
{
	return (ThermostatError) mock().actualCall("Watchdog::feed").returnIntValueOrDefault(THERMOSTAT_OK);
}

ThermostatError Watchdog::disable()
{
	return (ThermostatError) mock().actualCall("Watchdog::disable").returnIntValueOrDefault(THERMOSTAT_OK);
}

ThermostatError Watchdog::enable()
{
	return (ThermostatError) mock().actualCall("Watchdog::enable").returnIntValueOrDefault(THERMOSTAT_OK);
}

void Watchdog::reset()
{
	mock().actualCall("Watchdog::reset");
}

bool Watchdog::isEnabled()
{
	return mock().actualCall("Watchdog::isEnabled").returnBoolValueOrDefault(true);
}

bool Watchdog::causedReboot()
{
	return mock().actualCall("Watchdog::causedReboot").returnBoolValueOrDefault(true);
}
