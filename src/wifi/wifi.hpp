#include "thermostat_common.hpp"

#ifndef WIFI_HPP
#define WIFI_HPP

class Wifi {
    public:
        Wifi();
        ~Wifi();
        ThermostatError initalize();
        ThermostatError connect(const char *ssid, const char *password);
        ThermostatError disconnect();
        ThermostatError deinitalize();
        bool isConnected();
    private:
        bool initalized;

};

#endif