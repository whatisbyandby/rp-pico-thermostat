#include "hardware/watchdog.h"
#include <iostream>

#include "watchdog.hpp"

Watchdog::Watchdog()
{
}

Watchdog::~Watchdog()
{
}

ThermostatError Watchdog::initialize()
{
	timeout = 1000;
	return THERMOSTAT_OK;
}

ThermostatError Watchdog::initialize(int newTimeout)
{	
	timeout = newTimeout;
	return THERMOSTAT_OK;
}

ThermostatError Watchdog::feed()
{
	watchdog_update();
	return THERMOSTAT_OK;
}


ThermostatError Watchdog::disable()
{	
	return THERMOSTAT_OK;
}

ThermostatError Watchdog::enable()
{
	watchdog_enable(timeout, 1);
	return THERMOSTAT_OK;
}

void Watchdog::reset()
{
	std::cout << "Resetting" << std::endl;
	watchdog_enable(5000, 1);
	while(true) {
		tight_loop_contents();
	}
}

bool Watchdog::causedReboot()
{
	return watchdog_caused_reboot();
}

bool Watchdog::isEnabled()
{
	return true;
}
