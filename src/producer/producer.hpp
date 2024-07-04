#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include "thermostat_common.hpp"
#include "wifi.hpp"
#include "mqtt.hpp"

class Producer {
public:
    Producer();
    ~Producer();
    ThermostatError initalize(Mqtt *mqtt);

    ThermostatError update(ThermostatData *data);

    private:
        Mqtt *mqtt;
};

#endif
