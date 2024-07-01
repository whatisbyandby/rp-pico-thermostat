#include "producer.hpp"
#include "json.hpp"


Producer::Producer(Mqtt *mqtt)
{
    this->mqtt = mqtt;
}

Producer::~Producer()
{
}


ThermostatError Producer::initalize()
{

    return THERMOSTAT_OK;
}

ThermostatError Producer::update(ThermostatData *data)
{
    char buffer[1024];
    serialize(buffer, sizeof(buffer), data);
    ThermostatError err = mqtt->publish("home/thermostat/state", buffer);

    return THERMOSTAT_OK;
}