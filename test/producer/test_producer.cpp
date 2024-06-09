#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "producer.hpp"

static Producer *producer;
static Wifi *wifi;
static Mqtt *mqtt;

TEST_GROUP(TestGroupProducer)
{
    void setup()
    {
        wifi = new Wifi();
        mqtt = new Mqtt();
        producer = new Producer(wifi, mqtt);
    }

    void teardown()
    {   
        delete producer;
        delete wifi;
        delete mqtt;
        mock().checkExpectations();
        mock().clear();
    }
};

TEST(TestGroupProducer, ProducerConstructor)
{
    Producer testProducer(NULL, NULL);
}

TEST(TestGroupProducer, ProducerInitalize) {
    mock().expectOneCall("Wifi::initalize").andReturnValue(THERMOSTAT_OK);
    mock().expectOneCall("Wifi::connect").andReturnValue(THERMOSTAT_OK);
    mock().expectOneCall("Mqtt::initalize").andReturnValue(THERMOSTAT_OK);
    mock().expectOneCall("Mqtt::connect").andReturnValue(THERMOSTAT_OK);
    ThermostatError result = producer->initalize();
    ENUMS_EQUAL_INT(THERMOSTAT_OK, result);
}

TEST(TestGroupProducer, ProducerInitalize_WifiFailed) {
    mock().expectOneCall("Wifi::initalize").andReturnValue(THERMOSTAT_OK);
    mock().expectOneCall("Wifi::connect").andReturnValue(THERMOSTAT_ERROR);
    ThermostatError result = producer->initalize();
    ENUMS_EQUAL_INT(THERMOSTAT_INIT_FAILED, result);
}

TEST(TestGroupProducer, ProducerInitalize_MqttFailed) {
    mock().expectOneCall("Wifi::initalize").andReturnValue(THERMOSTAT_OK);
    mock().expectOneCall("Wifi::connect").andReturnValue(THERMOSTAT_OK);
    mock().expectOneCall("Mqtt::initalize").andReturnValue(THERMOSTAT_OK);
    mock().expectOneCall("Mqtt::connect").andReturnValue(THERMOSTAT_ERROR);
    ThermostatError result = producer->initalize();
    ENUMS_EQUAL_INT(THERMOSTAT_INIT_FAILED, result);
}

