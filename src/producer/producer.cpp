#include "producer.hpp"
#include "json.hpp"


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
    ThermostatError error = wifi->initalize();
    error = wifi->connect();
    if (error != THERMOSTAT_OK)
    {
        return THERMOSTAT_INIT_FAILED;
    }
    error = mqtt->initalize();
    error = mqtt->connect();

    if (error != THERMOSTAT_OK)
    {
        return THERMOSTAT_INIT_FAILED;
    }

    return THERMOSTAT_OK;
}

ThermostatError Producer::update(ThermostatState *state)
{
    char buffer[1024];
    serialize(buffer, sizeof(buffer), state);
    ThermostatError err = mqtt->publish("home/thermostat/state", buffer);

    return THERMOSTAT_OK;
}