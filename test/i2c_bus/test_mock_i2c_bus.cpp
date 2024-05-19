#include "CppUTest/TestHarness.h"
#include <CppUTestExt/MockSupport.h>
#include "i2c_bus.hpp"

TEST_GROUP(MockI2CTestGroup)
{
    void setup()
   {
   }

   void teardown()
   {
        mock().clear();
   }
};

TEST(MockI2CTestGroup, TestMockRead){
    
    I2CBus *i2cBus = new I2CBus();

    I2CDevice *i2cDevice = new I2CDevice(i2cBus, 0x01);

    uint8_t read_data[2] = {0x02, 0x02};
    uint8_t read_buffer[2] = {0x00, 0x00};

    mock()
        .expectOneCall("I2CDevice::read")
        .withParameter("length", 2)
        .withOutputParameterReturning("data", read_data, 2)
        .andReturnValue(I2C_OK);

    i2cDevice->read(read_buffer, 2);

    MEMCMP_EQUAL(read_data, read_buffer, 2);

    mock().checkExpectations();

    delete i2cDevice;
    delete i2cBus;
    
}

TEST(MockI2CTestGroup, TestMockWrite){
    
    I2CBus *i2cBus = new I2CBus();

    I2CDevice *i2cDevice = new I2CDevice(i2cBus, 0x01);

    uint8_t write_buffer[2] = {0x02, 0x02};
    uint8_t written_data[2] = {0x00, 0x00};

    mock()
        .expectOneCall("I2CDevice::write")
        .withParameter("length", 2)
        .withOutputParameterReturning("data", written_data, 2)
        .andReturnValue(I2C_OK);

    i2cDevice->write(write_buffer, 2);

    MEMCMP_EQUAL(write_buffer, written_data, 2);

    mock().checkExpectations();

    delete i2cDevice;
    delete i2cBus;
    
}