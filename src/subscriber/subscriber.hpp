#include "wifi.hpp"
#include "mqtt.hpp"

class Subscriber {
    public: 
        Subscriber(Wifi* wifi, Mqtt* mqtt);
        ~Subscriber();

        void subscribe(const char *topic);

    private:
        Wifi *wifi;
        Mqtt *mqtt;
};