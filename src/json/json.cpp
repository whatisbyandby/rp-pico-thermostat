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
    buffer = json_double( buffer, "targetTemperature", state->targetTemperature, &len);
    buffer = json_double( buffer, "currentTemperatureStandardUnits", state->currentTemperatureStandardUnits, &len);
    buffer = json_double( buffer, "targetTemperatureStandardUnits", state->targetTemperatureStandardUnits, &len);
    buffer = json_double( buffer, "temperatureRange", state->temperatureRange, &len);
    buffer = json_str( buffer, "temperatureState", temperatureStateToString(state->temperatureState), &len);
    buffer = json_str( buffer, "temperatureUnits", temperatureUnitsToString(state->temperatureUnits), &len);
    buffer = json_str( buffer, "hvacState", hvacStateToString(state->hvacState), &len);
    buffer = json_str( buffer, "mode", thermostatModeToString(state->mode), &len);
    buffer = json_str( buffer, "error", thermostatErrorToString(state->error), &len);
    buffer = json_objClose( buffer, &len);
    buffer = json_end( buffer, &len);
    
    return THERMOSTAT_OK;
}