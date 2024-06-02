#include "repl.hpp"
#include <iostream>

Repl::Repl(ThermostatController *controller, CommandParser *parser) {
    thermostatController = controller;
    commandParser = parser;
    
}

Repl::~Repl() {
}

ThermostatError Repl::read(ThermostatCommand *command) {
    std::cout << "-> ";
    std::string input;
    std::getline(std::cin, input);

    commandParser->parseString(input, command);

    return THERMOSTAT_OK;
    
}

ThermostatError Repl::evaluate(ThermostatCommand *command) {
    thermostatController->executeCommand(command);
    return THERMOSTAT_OK;
}

ThermostatError Repl::print(ThermostatCommand *command) {
    std::cout << command->resultString << std::endl;
    return THERMOSTAT_OK;
}