

#ifndef WIFI_HPP
#define WIFI_HPP
#include "thermostat_common.hpp"
#include "configuration.hpp"

class Wifi {
    public:
        Wifi();
        ~Wifi();
        ThermostatError initialize(Configuration *config);
        ThermostatError scan();
        ThermostatError connect();
        ThermostatError disconnect();
        ThermostatError deinitalize();
        bool isConnected();
    private:
        bool initalized;
        Configuration *config;

};

#endif