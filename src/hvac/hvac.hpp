#include "thermostat_common.hpp"
#include "gpio.hpp"

class HVAC {
    public:
        HVAC();
        ThermostatError setDesiredState(HVACState state);
        HVACState getCurrentState();
        void setHeater(Switch *heater);
        void setAC(Switch *ac);
        void setFan(Switch *fan);
        

    private:
        HVACState currentState;
        HVACState readCurrentState();
        Switch *heater;
        Switch *ac;
        Switch *fan;
};