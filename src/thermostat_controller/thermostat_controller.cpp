#include "thermostat_controller.hpp"
#include <iostream>
#include "repl.hpp"



ThermostatController::ThermostatController(Thermostat *thermostat)
{
    this->thermostat = thermostat;
}

ThermostatError ThermostatController::executeCommand(ThermostatCommand *command)
{   
    ThermostatError error = THERMOSTAT_OK;
    switch (command->command_type) {
        case HELP:
            printError(error);
            std::cout << "Printing help: " << std::endl;
            std::cout << "set_temperature <temperature> - Set the target temperature in the current units" << std::endl;
            std::cout << "set_mode <mode> - Set the mode of operation" << std::endl;
            std::cout << "set_units <units> - Set the units of the thermostat" << std::endl;
            std::cout << "print_state - Print the current state of the thermostat" << std::endl;
            return THERMOSTAT_OK;
        case SET_TEMPERATURE:
            error = thermostat->setTargetTemperature(command->parameter);
            printError(error);
            std::cout << "Target Temperature set to " << thermostat->getTargetTemperature();
            return error;
        case SET_MODE:
        {
            int parsedValue = (int)command->parameter;
            error = thermostat->setMode((ThermostatMode)parsedValue);
            printError(error);
            std::cout << "Mode set to " << thermostatModeToString(thermostat->getMode());
            return error;
        }
        case PRINT_STATE:
        {
            std::string stateString;
            error = thermostat->printState(&stateString);
            printError(error);
            std::cout << stateString;
            return error;
        }
        default: 
            printError(THERMOSTAT_UNKNOWN_COMMAND);
            return THERMOSTAT_UNKNOWN_COMMAND;
            
    }
}

