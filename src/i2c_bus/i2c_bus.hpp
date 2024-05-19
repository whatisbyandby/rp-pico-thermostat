#pragma once
#include <stdint.h>

typedef enum I2CError {
    I2C_READ_ERROR,
    I2C_WRITE_ERROR,
    I2C_OK
} I2CError;


class I2CBus {
    public:
        I2CBus();
        ~I2CBus();

        I2CError initialize();
        bool isInitialized();

    private:
        bool initialized;
};

class I2CDevice {
    public:
        I2CDevice(I2CBus *bus, uint8_t address);
        ~I2CDevice();

        I2CError initialize();
        bool isInitialized();

        I2CError read(uint8_t *data, uint8_t length);
        I2CError write(uint8_t *data, uint8_t length);

    private:
        I2CBus *bus;
        uint8_t address;
        bool initialized;
};