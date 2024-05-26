#include "thermostat.hpp"
#include "gpio.hpp"

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
        ThermostatController(Thermostat *thermostat, Button *upButton);
        ThermostatError executeCommand(ThermostatCommand *command);
        ThermostatError update();

    private:
        Thermostat *thermostat;
        Button *upButton;
};