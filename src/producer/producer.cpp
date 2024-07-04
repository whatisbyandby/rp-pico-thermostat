#include "producer.hpp"
#include "json.hpp"


Producer::Producer()
{
    
}

Producer::~Producer()
{
}


ThermostatError Producer::initalize(Mqtt *mqtt)
{
    this->mqtt = mqtt;
    return THERMOSTAT_OK;
}

ThermostatError Producer::update(ThermostatData *data)
{
    char buffer[1024];
    serialize(buffer, sizeof(buffer), data);
    ThermostatError err = mqtt->publish("home/thermostat/state", buffer);

    return THERMOSTAT_OK;
}