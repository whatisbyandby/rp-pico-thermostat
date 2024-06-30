#include "json.hpp"
#include "json-maker/json-maker.h"
#include <string>


ThermostatError parse(std::string json, ThermostatCommand *command)
{
    return THERMOSTAT_OK;
}

ThermostatError serialize(char *buffer, size_t len, ThermostatData *data)
{

    buffer = json_objOpen( buffer, NULL, &len);
    buffer = json_double( buffer, "currentTemperature", data->currentTemperature, &len);
    buffer = json_double( buffer, "currentHumidity", data->currentHumidity, &len);
    buffer = json_double( buffer, "targetTemperature", data->targetTemperature, &len);
    buffer = json_double( buffer, "currentTemperatureStandardUnits", data->currentTemperatureStandardUnits, &len);
    buffer = json_double( buffer, "targetTemperatureStandardUnits", data->targetTemperatureStandardUnits, &len);
    buffer = json_double( buffer, "temperatureRange", data->temperatureRange, &len);
    buffer = json_str( buffer, "temperatureState", temperatureStateToString(data->temperatureState), &len);
    buffer = json_str( buffer, "temperatureUnits", temperatureUnitsToString(data->temperatureUnits), &len);
    buffer = json_str( buffer, "hvacState", hvacStateToString(data->hvacState), &len);
    buffer = json_str( buffer, "mode", thermostatModeToString(data->mode), &len);
    buffer = json_str( buffer, "error", thermostatErrorToString(data->error), &len);
    buffer = json_objClose( buffer, &len);
    buffer = json_end( buffer, &len);
    
    return THERMOSTAT_OK;
}