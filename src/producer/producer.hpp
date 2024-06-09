#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include "thermostat_common.hpp"
#include "wifi.hpp"
#include "mqtt.hpp"

class Producer {
public:
    Producer(Wifi *wifi, Mqtt *mqtt);

    ~Producer();

    ThermostatError initalize();

    ThermostatError update(ThermostatState *state);

    private:
        Wifi *wifi;
        Mqtt *mqtt;
};

#endif
