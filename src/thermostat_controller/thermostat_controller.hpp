#ifndef THERMOSTAT_CONTROLLER_HPP
#define THERMOSTAT_CONTROLLER_HPP


#include "thermostat.hpp"
#include "thermostat_common.hpp"


class ThermostatController {

    public: 
        ThermostatController(Thermostat *thermostat);
        ThermostatError executeCommand(ThermostatCommand *command);

    private:
        Thermostat *thermostat;
};

#endif