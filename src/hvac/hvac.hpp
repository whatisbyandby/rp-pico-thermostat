#include "thermostat_common.hpp"

class HVAC {
    public:
        HVAC();
        ThermostatError setDesiredState(HVACState state);
        HVACState getCurrentState();

    private:
        HVACState currentState;
};