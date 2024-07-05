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
        ThermostatError subscribe(const char *topic, CommandCallback, void *arg);
        bool isConnected();
        void executeCallback(ThermostatCommand *command);
        uint8_t commandBuffer[1024];
        uint32_t messageLength;
        uint32_t currentWriteIndex;
    private:
        bool initalized;
        Configuration *configuration;
        CommandCallback commandCallback;
        void *callbackArg;

};

#endif // MQTT_HPP