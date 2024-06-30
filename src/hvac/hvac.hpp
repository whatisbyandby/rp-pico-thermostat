#ifndef HVAC_HPP
#define HVAC_HPP

#include "thermostat_common.hpp"
#include "gpio.hpp"



class HVAC {
    public:
        HVAC(Switch *heater, Switch *ac, Switch *fan);
        ThermostatError setDesiredState(ThermostatState state);
        ThermostatState getCurrentState();

    private:
        ThermostatState currentState;
        ThermostatState readCurrentState();
        Switch *heater;
        Switch *ac;
        Switch *fan;
};

#endif // HVAC_HPP