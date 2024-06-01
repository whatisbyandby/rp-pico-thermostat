#include "command_parser.hpp"
#include <iostream>
#include <sstream>
#include <string>

CommandParser::CommandParser()
{
}

CommandParser::~CommandParser()
{
}

ThermostatError CommandParser::parseString(std::string command, ThermostatCommand *thermostat_command)
{
    std::istringstream iss(command);
    std::string cmd;
    double value;

    // Extract the command part
    iss >> cmd;

    if (cmd == "help") {
        thermostat_command->command_type = HELP;
        return THERMOSTAT_OK;
    }

    if (cmd == "set_temperature")
    {
        if (!(iss >> value)) {
            thermostat_command->command_type = INVALID_COMMAND;
            return THERMOSTAT_INVALID_INPUT;
        }
        thermostat_command->command_type = SET_TEMPERATURE;
        thermostat_command->parameter = value;
        return THERMOSTAT_OK;
    }

    if (cmd == "set_mode")
    {
        if (!(iss >> value)) {
            thermostat_command->command_type = INVALID_COMMAND;
            return THERMOSTAT_INVALID_INPUT;
        }
        thermostat_command->command_type = SET_MODE;
        thermostat_command->parameter = value;
        return THERMOSTAT_OK;
    }

    if (cmd == "state") {
        thermostat_command->command_type = PRINT_STATE;
        return THERMOSTAT_OK;
    }
   
    thermostat_command->command_type = INVALID_COMMAND;
    return THERMOSTAT_UNKNOWN_COMMAND;
}

ThermostatError CommandParser::parseJson(std::string command, ThermostatCommand *thermostat_command)
{
    return THERMOSTAT_OK;
}

void CommandParser::printCommand()
{
}
