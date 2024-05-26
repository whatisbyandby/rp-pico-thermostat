#include "thermostat_controller.hpp"



ThermostatController::ThermostatController(Thermostat *thermostat, Button *upButton)
{
    this->thermostat = thermostat;
    this->upButton = upButton;
}

ThermostatError ThermostatController::executeCommand(ThermostatCommand *command)
{
    switch (command->type) {
        case SET_TARGET_TEMPERATURE:
            return thermostat->setTargetTemperature(command->value);
        case SET_MODE:
        {
            int parsedValue = (int)command->value;
            return thermostat->setMode((ThermostatMode)parsedValue);
        }
        default: 
            return THERMOSTAT_ERROR;
            
    }
}

ThermostatError ThermostatController::update() {

}