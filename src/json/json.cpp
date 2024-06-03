#include "json.hpp"
#include "json-maker/json-maker.h"
#include <string>


ThermostatError parse(std::string json, ThermostatCommand *command)
{
    return THERMOSTAT_OK;
}

ThermostatError serialize(char *buffer, size_t len, ThermostatState *state)
{

    buffer = json_objOpen( buffer, NULL, &len);
    buffer = json_double( buffer, "currentTemperature", state->currentTemperature, &len);
    buffer = json_double( buffer, "currentHumidity", state->currentHumidity, &len);
    buffer = json_objClose( buffer, &len);
    buffer = json_end( buffer, &len);
    
    return THERMOSTAT_OK;
}