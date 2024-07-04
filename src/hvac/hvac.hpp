#ifndef HVAC_HPP
#define HVAC_HPP

#include "thermostat_context.hpp"
#include "thermostat_common.hpp"
#include "gpio.hpp"



class Hvac {
    public:
        Hvac();
        ThermostatError initialize(ThermostatContext *context);
        ThermostatError setDesiredState(ThermostatState state);
        ThermostatState getCurrentState();

    private:
        ThermostatState currentState;
        ThermostatState readCurrentState();
        ThermostatContext *context;
};

#endif // HVAC_HPP