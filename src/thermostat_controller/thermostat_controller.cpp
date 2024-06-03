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
    if (command->command_type == INVALID_COMMAND) {
        command->resultString = "[ERROR] Invalid command";
        return THERMOSTAT_OK;
    }
    ThermostatError error = THERMOSTAT_OK;
    std::ostringstream oss;
    switch (command->command_type) {
        case HELP:
            oss << "[OK] ";
            oss << "Printing help: " << std::endl;
            oss << "set_temperature <temperature> - Set the target temperature in the current units" << std::endl;
            oss << "set_mode <mode> - Set the mode of operation" << std::endl;
            oss << "set_units <units> - Set the units of the thermostat" << std::endl;
            oss << "state - Print the current state of the thermostat" << std::endl;

            command->resultString = oss.str();
            return THERMOSTAT_OK;
        case SET_TEMPERATURE:
            error = thermostat->setTargetTemperature(command->parameter);
            if (error != THERMOSTAT_OK) {
                oss << "[ERROR] Error setting target temperature ";
                command->resultString = oss.str();
                return error;
            }
            oss << "[OK] Target Temperature set to " << thermostat->getTargetTemperature();
            command->resultString = oss.str();
            return error;
        case SET_MODE:
        {
            int parsedValue = (int)command->parameter;
            error = thermostat->setMode((ThermostatMode)parsedValue);
            if (error != THERMOSTAT_OK) {
                oss << "[ERROR] Error setting mode ";
                command->resultString = oss.str();
                return error;
            }
            oss << "[OK] Mode set to " << thermostatModeToString(thermostat->getMode());
            command->resultString = oss.str();
            return error;
        }
        
        case SET_UNITS:
        {
            int parsedValue = (int)command->parameter;
            error = thermostat->setTemperatureUnits((TemperatureUnits)parsedValue);
            if (error != THERMOSTAT_OK) {
                oss << "[ERROR] Error setting units ";
                command->resultString = oss.str();
                return error;
            }
            oss << "[OK] Units set to " << temperatureUnitsToString(thermostat->getTemperatureUnits());
            command->resultString = oss.str();
            return error;
        }

        case PRINT_STATE:
        {
            std::string stateString;
            error = thermostat->printState(&stateString);
            oss << "[OK]" << std::endl << stateString;
            command->resultString = oss.str();
            return error;
        }
        default:
            command->resultString = "[ERROR] Unknown command";
            return THERMOSTAT_UNKNOWN_COMMAND; 
    }
}

