#ifndef REPL_HPP
#define REPL_HPP


#include <iostream>
#include "thermostat_common.hpp"
#include "thermostat_controller.hpp"
#include "thermostat_common.hpp"
#include "command_parser.hpp"

class Repl
{
public:
    Repl(ThermostatController *controller, CommandParser *parser);
    ~Repl();
    ThermostatError read(ThermostatCommand *command);
    ThermostatError evaluate(ThermostatCommand *command);
    ThermostatError print(ThermostatCommand *command);
private:
    ThermostatController *thermostatController;
    CommandParser *commandParser;

};

#endif
