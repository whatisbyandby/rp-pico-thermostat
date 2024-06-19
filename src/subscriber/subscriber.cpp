#include "subscriber.hpp"

Subscriber::Subscriber(Wifi *wifi, Mqtt *mqtt) {
    this->wifi = wifi;
    this->mqtt = mqtt;
}

Subscriber::~Subscriber() {
}

void Subscriber::subscribe(const char *topic) {
    this->mqtt->subscribe(topic);
}