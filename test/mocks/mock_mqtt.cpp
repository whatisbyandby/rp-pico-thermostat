#include "mqtt.hpp"
#include <CppUTestExt/MockSupport.h>

Mqtt::Mqtt()
{
}

Mqtt::~Mqtt()
{
}

ThermostatError Mqtt::initalize()
{   
    return (ThermostatError) mock().actualCall("Mqtt::initalize").returnIntValueOrDefault(THERMOSTAT_OK);
}

ThermostatError Mqtt::connect()
{
    return (ThermostatError) mock().actualCall("Mqtt::connect").returnIntValueOrDefault(THERMOSTAT_OK);
}

ThermostatError Mqtt::publish(const char *topic, char *message)
{
    return (ThermostatError) mock()
        .actualCall("Mqtt::publish")
        .withStringParameter("topic", topic)
        .withStringParameter("message", message)
        .returnIntValueOrDefault(THERMOSTAT_OK);
}