#ifndef WATCHDOG_HPP
#define WATCHDOG_HPP

#include "thermostat_common.hpp"

class Watchdog {
	public:
		Watchdog();
		~Watchdog();
		ThermostatError initialize();
		ThermostatError initialize(int timeout);
		ThermostatError feed();
		ThermostatError disable();
		ThermostatError enable();
		void reset();
		bool isEnabled();
		bool causedReboot();
	private:
		int timeout;
		bool initalized;
};

#endif // WATCHDOG_HPP