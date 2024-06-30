#include "CppUTest/TestHarness.h"
#include "json.hpp"
#include "thermostat_common.hpp"

TEST_GROUP(JsonTestGroup)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(JsonTestGroup, SerializeThermostatData)
{

    ThermostatData state;
    state.currentTemperature = 22.1;
    state.currentHumidity = 50.1;
    state.targetTemperature = 22.1;
    state.currentTemperatureStandardUnits = 22.1;
    state.targetTemperatureStandardUnits = 22.1;
    state.temperatureRange = 1.1;
    state.temperatureState = OVER_TEMPERATURE;
    state.temperatureUnits = CELSIUS;
    state.hvacState = HEATING;
    state.mode = HEAT;
    state.error = THERMOSTAT_OK;
    
    size_t len = 1024;
    char buffer[len];

    serialize(buffer, len, &state);

    STRCMP_EQUAL("{\"currentTemperature\":22.1,"
    "\"currentHumidity\":50.1,"
    "\"targetTemperature\":22.1,"
    "\"currentTemperatureStandardUnits\":22.1,"
    "\"targetTemperatureStandardUnits\":22.1,"
    "\"temperatureRange\":1.1,"
    "\"temperatureState\":\"OVER_TEMPERATURE\","
    "\"temperatureUnits\":\"CELSIUS\","
    "\"hvacState\":\"HEATER_ON\","
    "\"mode\":\"HEATING\","
    "\"error\":\"THERMOSTAT_OK\"}", 
    buffer);

    

}