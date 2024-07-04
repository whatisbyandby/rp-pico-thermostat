#include <CppUTestExt/MockSupport.h>
#include "i2c_bus.hpp"
#include <string.h>

I2CBus::I2CBus() {
}

I2CBus::~I2CBus() {

}


I2CError I2CBus::initialize() {
    return (I2CError) mock().actualCall("I2CBus::initialize").returnIntValueOrDefault(I2C_OK);
}

bool I2CBus::isInitialized() {
   return mock().actualCall("I2CBus::isInitialized").returnBoolValue();
}


I2CDevice::I2CDevice() {

}

I2CDevice::~I2CDevice() {
}


I2CError I2CDevice::initialize(I2CBus *bus, uint8_t address) {
    return (I2CError) mock().actualCall("I2CDevice::initialize").returnIntValueOrDefault(I2C_OK);
}

bool I2CDevice::isInitialized() {
    return mock().actualCall("I2CDevice::isInitialized").returnBoolValueOrDefault(true);
}

I2CError I2CDevice::read(uint8_t *data, uint8_t length) {
    return (I2CError) mock()
        .actualCall("I2CDevice::read")
        .withParameter("length", length)
        .withOutputParameter("data", data)
        .returnIntValueOrDefault(I2C_OK);
}

I2CError I2CDevice::write(uint8_t *data, uint8_t length) {
    return (I2CError) mock()
        .actualCall("I2CDevice::write")
        .withParameter("length", length)
        .withOutputParameter("data", data)
        .returnIntValueOrDefault(I2C_OK);
}