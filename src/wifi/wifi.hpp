#include "thermostat_common.hpp"

#ifndef WIFI_HPP
#define WIFI_HPP

class Wifi {
    public:
        Wifi();
        ~Wifi();
        ThermostatError initalize();
        ThermostatError initalize(const char *ssid, const char *password);
        ThermostatError scan();
        ThermostatError connect(const char *ssid, const char *password);
        ThermostatError connect();
        ThermostatError disconnect();
        ThermostatError deinitalize();
        bool isConnected();
    private:
        bool initalized;
        char ssid[128];
        char password[128];

};

#endif