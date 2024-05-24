#include "pico/stdlib.h"
#include "gpio.hpp"
// class Switch {
//     public:
//         Switch(int pin);
//         ~Switch();
//         void turnOn();
//         void turnOff();
//         bool isOn();
//     private:
//         int pin;
//         bool state;
// };

Switch::Switch(int pin) {

    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
    gpio_put(pin, 0);

    this->pin = pin;
    this->state = false;
}

Switch::~Switch() {
    gpio_deinit(pin);
}

void Switch::turnOn() {
    gpio_put(pin, 1);
    this->state = true;
}

void Switch::turnOff() {
    gpio_put(pin, 0);
    this->state = false;
}

bool Switch::isOn() {
    return this->state;
}
