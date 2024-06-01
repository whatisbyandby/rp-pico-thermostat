#include "repl.hpp"
#include <iostream>

void printPrompt() {
    std::cout << std::endl << "-> " << std::flush;
}

void printError(ThermostatError err) {
    if (err == THERMOSTAT_OK) {
        std::cout << "[OK] ";
    } else {
        std::cout << "[ERROR] " << thermostatErrorToString(err) << " ";
    }
}