#include <CppUTestExt/MockSupport.h>
#include "wifi.hpp"

Wifi::Wifi()
{
}

Wifi::~Wifi()
{
}

ThermostatError Wifi::initalize()
{
    return (ThermostatError) mock().actualCall("Wifi::initalize").returnIntValueOrDefault(THERMOSTAT_OK);
}

ThermostatError Wifi::connect(const char *ssid, const char *password)
{
    return (ThermostatError) mock().actualCall("Wifi::connect").returnIntValueOrDefault(THERMOSTAT_OK);
}

