#ifndef MQTT_HPP
#define MQTT_HPP

#include "thermostat_common.hpp"

class Mqtt {
    public:
        Mqtt();
        ~Mqtt();
        ThermostatError initalize();
        ThermostatError connect();
        ThermostatError publish(const char *topic, char *message);
        ThermostatError subscribe();
        bool isConnected();
    private:
        bool initalized;

};

#endif // MQTT_HPP