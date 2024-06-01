#include "CppUTest/TestHarness.h"
#include <CppUTestExt/MockSupport.h>
#include "command_parser.hpp"

static CommandParser *command_parser;


TEST_GROUP(CommandParserTestGroup)
{
    void setup()
    {
        command_parser = new CommandParser();
        
    }

    void teardown()
    {   
        mock().checkExpectations();
        mock().clear();
        delete command_parser;
    }
};

TEST(CommandParserTestGroup, TestCommandParser_SetTemperature)
{
    CommandParser command_parser;
    ThermostatCommand thermostat_command;

    ENUMS_EQUAL_INT(THERMOSTAT_OK, command_parser.parseString("set_temperature 20.0", &thermostat_command));
    ENUMS_EQUAL_INT(SET_TEMPERATURE, thermostat_command.command_type);
    DOUBLES_EQUAL(20.0, thermostat_command.parameter, 0.01);
}

TEST(CommandParserTestGroup, TestCommandParser_SetTemperature_NoParameter)
{
    CommandParser command_parser;
    ThermostatCommand thermostat_command;

    ENUMS_EQUAL_INT(THERMOSTAT_INVALID_INPUT, command_parser.parseString("set_temperature", &thermostat_command));
    ENUMS_EQUAL_INT(INVALID_COMMAND, thermostat_command.command_type);
}

TEST(CommandParserTestGroup, TestCommandParser_SetMode_Vaid) {
    CommandParser command_parser;
    ThermostatCommand thermostat_command;

    ENUMS_EQUAL_INT(THERMOSTAT_OK, command_parser.parseString("set_mode 1", &thermostat_command));
    ENUMS_EQUAL_INT(SET_MODE, thermostat_command.command_type);
    DOUBLES_EQUAL(1.0, thermostat_command.parameter, 0.01);

}

TEST(CommandParserTestGroup, TestCommandParser_SetMode_NoParameter) {
    CommandParser command_parser;
    ThermostatCommand thermostat_command;

    ENUMS_EQUAL_INT(THERMOSTAT_INVALID_INPUT, command_parser.parseString("set_mode", &thermostat_command));
    ENUMS_EQUAL_INT(INVALID_COMMAND, thermostat_command.command_type);

}

TEST(CommandParserTestGroup, TestCommandParser_State) {
    CommandParser command_parser;
    ThermostatCommand thermostat_command;

    ENUMS_EQUAL_INT(THERMOSTAT_OK, command_parser.parseString("state", &thermostat_command));
}

TEST(CommandParserTestGroup, TestCommandParser_InvalidCommand)
{
    CommandParser command_parser;
    ThermostatCommand thermostat_command;

    ENUMS_EQUAL_INT(THERMOSTAT_UNKNOWN_COMMAND, command_parser.parseString("Not Real", &thermostat_command));
}