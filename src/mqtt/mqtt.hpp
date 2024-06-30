#ifndef MQTT_HPP
#define MQTT_HPP

#include "thermostat_common.hpp"
#include "configuration.hpp"

class Mqtt {
    public:
        Mqtt(Configuration *configuration);
        ~Mqtt();
        ThermostatError initalize();
        ThermostatError connect();
        ThermostatError publish(const char *topic, char *message);
        ThermostatError subscribe(const char *topic);
        bool isConnected();
    private:
        bool initalized;
        Configuration *configuration;

};

#endif // MQTT_HPP