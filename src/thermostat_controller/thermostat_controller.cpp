#include "thermostat_controller.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include "repl.hpp"



ThermostatController::ThermostatController(Thermostat *thermostat)
{
    this->thermostat = thermostat;
}

ThermostatError ThermostatController::executeCommand(ThermostatCommand *command)
{   
    ThermostatError error = THERMOSTAT_OK;
    std::ostringstream oss;
    switch (command->command_type) {
        case HELP:
            oss << "[OK] ";
            oss << "Printing help: " << std::endl;
            oss << "set_temperature <temperature> - Set the target temperature in the current units" << std::endl;
            oss << "set_mode <mode> - Set the mode of operation" << std::endl;
            oss << "set_units <units> - Set the units of the thermostat" << std::endl;
            oss << "print_state - Print the current state of the thermostat" << std::endl;

            command->resultString = oss.str();
            return THERMOSTAT_OK;
        case SET_TEMPERATURE:
            error = thermostat->setTargetTemperature(command->parameter);
            oss << "Target Temperature set to " << thermostat->getTargetTemperature();
            command->resultString = oss.str();
            return error;
        case SET_MODE:
        {
            int parsedValue = (int)command->parameter;
            error = thermostat->setMode((ThermostatMode)parsedValue);
            std::cout << "Mode set to " << thermostatModeToString(thermostat->getMode());
            return error;
        }
        case PRINT_STATE:
        {
            std::string stateString;
            error = thermostat->printState(&stateString);
            std::cout << stateString;
            return error;
        }
        default: 
            return THERMOSTAT_UNKNOWN_COMMAND;
            
    }
}

