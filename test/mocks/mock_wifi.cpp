#include <CppUTestExt/MockSupport.h>
#include "wifi.hpp"
#include "configuration.hpp"

Wifi::Wifi()
{
}

Wifi::~Wifi()
{
}

ThermostatError Wifi::initialize(Configuration *config)
{
    return (ThermostatError) mock().actualCall("Wifi::initialize").returnIntValueOrDefault(THERMOSTAT_OK);
}


ThermostatError Wifi::connect()
{
    return (ThermostatError) mock().actualCall("Wifi::connect").returnIntValueOrDefault(THERMOSTAT_OK);
}

