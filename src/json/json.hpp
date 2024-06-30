#ifndef JSON_HPP
#define JSON_HPP

#include "thermostat_common.hpp"

ThermostatError parse(char *buffer, ThermostatCommand *command);

ThermostatError serialize(char *buffer, size_t len, ThermostatData *data);



#endif // JSON_HPP
