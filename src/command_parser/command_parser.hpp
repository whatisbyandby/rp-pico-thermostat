#include <string>
#include "thermostat_common.hpp"
#include <stdint.h>



class CommandParser {
    public:
        CommandParser();
        ~CommandParser();
        ThermostatError parseString(std::string command, ThermostatCommand *thermostat_command);
        ThermostatError parseJson(std::string command, ThermostatCommand *thermostat_command);
        void printCommand();
};