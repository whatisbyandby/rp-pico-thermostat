#ifndef MQTT_HPP
#define MQTT_HPP

#include "thermostat_common.hpp"
#include "configuration.hpp"

class Mqtt {
    public:
        Mqtt();
        ~Mqtt();
        ThermostatError initialize(Configuration *configuration);
        ThermostatError connect();
        ThermostatError publish(const char *topic, char *message);
        ThermostatError subscribe(const char *topic);
        bool isConnected();
    private:
        bool initalized;
        Configuration *configuration;

};

#endif // MQTT_HPP