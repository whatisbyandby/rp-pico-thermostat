#ifndef REPL_HPP
#define REPL_HPP

#include "thermostat_common.hpp"
#include "command_parser.hpp"

class Repl
{
public:
    Repl(CommandParser *parser);
    ~Repl();
    ThermostatError init();
    ThermostatError read(ThermostatCommand *command);
    ThermostatError print(ThermostatCommand *command);
private:
    CommandParser *commandParser;

};

#endif
