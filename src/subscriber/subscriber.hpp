#ifndef SUBSCRIBER_HPP
#define SUBSCRIBER_HPP

#include "wifi.hpp"
#include "mqtt.hpp"

class Subscriber {
    public: 
        Subscriber();
        ~Subscriber();

        ThermostatError initialize(Wifi* wifi, Mqtt* mqtt);
        void subscribe(const char *topic);

    private:
        Wifi *wifi;
        Mqtt *mqtt;
};

#endif // SUBSCRIBER_HPP