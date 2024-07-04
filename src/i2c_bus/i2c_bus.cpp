#include "i2c_bus.hpp" 
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"

#define SDA_PIN 20
#define SCL_PIN 21

I2CBus::I2CBus() {

}

I2CBus::~I2CBus() {

}

bool I2CBus::isInitialized() {
    return initialized;
}

I2CError I2CBus::initialize() {

    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(SDA_PIN, SCL_PIN, GPIO_FUNC_I2C));

    initialized = true;
    return I2C_OK;
}

I2CDevice::I2CDevice() {
    
}



I2CDevice::~I2CDevice() {

}

bool I2CDevice::isInitialized() {
    return initialized;
}

I2CError I2CDevice::initialize(I2CBus *bus, uint8_t address) {

    this->bus = bus;
    this->address = address;

    initialized = true;
    return I2C_OK;
}

I2CError I2CDevice::read(uint8_t *data, uint8_t length) {
    i2c_read_blocking(i2c_default, address, data, length, false);
    return I2C_OK;
}

I2CError I2CDevice::write(uint8_t *data, uint8_t length) {
    i2c_write_blocking(i2c_default, address, data, length, false);
    return I2C_OK;
}


