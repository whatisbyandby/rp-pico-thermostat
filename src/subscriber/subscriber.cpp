#include "subscriber.hpp"

Subscriber::Subscriber() {
}

Subscriber::~Subscriber() {
}

ThermostatError Subscriber::initialize(Wifi *wifi, Mqtt *mqtt) {
    this->wifi = wifi;
    this->mqtt = mqtt;
    return THERMOSTAT_OK;
}


void Subscriber::subscribe(const char *topic) {
    this->mqtt->subscribe(topic);
}