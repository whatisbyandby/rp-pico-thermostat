#include <CppUTestExt/MockSupport.h>
#include "producer.hpp"

Producer::Producer(Wifi *wifi, Mqtt *mqtt)
{
    this->wifi = wifi;
    this->mqtt = mqtt;
}

Producer::~Producer()
{
}

ThermostatError Producer::initalize()
{   
    return (ThermostatError) mock().actualCall("Producer::initalize").returnIntValueOrDefault(THERMOSTAT_OK);
   
}


ThermostatError Producer::update(ThermostatState *state)
{
    return (ThermostatError) mock().actualCall("Producer::update").withPointerParameter("state", state).returnIntValueOrDefault(THERMOSTAT_OK);
}

