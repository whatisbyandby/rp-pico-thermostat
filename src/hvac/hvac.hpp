#ifndef HVAC_HPP
#define HVAC_HPP

#include "thermostat_common.hpp"
#include "gpio.hpp"



class Hvac {
    public:
        Hvac();
        ThermostatError initialize(Switch *heat, Switch *cool, Switch *fan);
        ThermostatError setDesiredState(ThermostatState state);
        ThermostatState getCurrentState();

    private:
        ThermostatState currentState;
        ThermostatState readCurrentState();
        Switch *heatSwitch;
        Switch *coolSwitch;
        Switch *fanSwitch;
};

#endif // HVAC_HPP