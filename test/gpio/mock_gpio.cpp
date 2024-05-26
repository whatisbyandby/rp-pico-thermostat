#include <CppUTestExt/MockSupport.h>
#include "gpio.hpp"

Switch::Switch(int pin) {
    this->pin = pin;
    this->state = false;
}

Switch::~Switch() {
    // nothing to do
}

void Switch::turnOn() {
    mock().actualCall("Switch::turnOn").onObject(this);
}

void Switch::turnOff() {
    mock().actualCall("Switch::turnOff").onObject(this);
}

bool Switch::isOn() {
   return mock().actualCall("Switch::isOn").onObject(this).returnBoolValue();
}


Button::Button(int pin) {
    this->pin = pin;
    this->numOfPresses = 0;
}

Button::~Button() {
    // nothing to do
}

bool Button::isPressed() {
    return mock()
        .actualCall("Button::isPressed")
        .onObject(this)
        .returnBoolValue();
}

int Button::readNumberOfPresses() {
    return mock()
        .actualCall("Button::readNumberOfPresses")
        .onObject(this)
        .returnIntValue();
}