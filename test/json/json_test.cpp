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

TEST(JsonTestGroup, SerializeThermostatState)
{

    ThermostatState state;
    state.currentTemperature = 22.1;
    state.currentHumidity = 50.1;
    
    size_t len = 1024;
    char buffer[len];

    serialize(buffer, len, &state);
    

    STRCMP_EQUAL("{\"currentTemperature\":22.1,\"currentHumidity\":50.1}", buffer);
}