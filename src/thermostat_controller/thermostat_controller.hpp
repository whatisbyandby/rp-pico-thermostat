#include "thermostat.hpp"

enum ThermostatCommandType {
    SET_TARGET_TEMPERATURE,
    SET_MODE,
    SET_TEMPERATURE_UNITS
};

struct ThermostatCommand {
    ThermostatCommandType type;
    double value;
};


class ThermostatController {

    public: 
        ThermostatController(Thermostat *thermostat);
        ThermostatError executeCommand(ThermostatCommand *command);

    private:
        Thermostat *thermostat;
};