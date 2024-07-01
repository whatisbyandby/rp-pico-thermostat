#include "mqtt.hpp"
#include <CppUTestExt/MockSupport.h>

Mqtt::Mqtt(Configuration *config)
{
}

Mqtt::~Mqtt()
{
}

ThermostatError Mqtt::initialize()
{   
    return (ThermostatError) mock().actualCall("Mqtt::initialize").returnIntValueOrDefault(THERMOSTAT_OK);
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

ThermostatError Mqtt::subscribe(const char *topic)
{
    return (ThermostatError) mock()
        .actualCall("Mqtt::subscribe")
        .withStringParameter("topic", topic)
        .returnIntValueOrDefault(THERMOSTAT_OK);
}