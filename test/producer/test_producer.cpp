#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "producer.hpp"

static Producer *producer;
static Wifi *wifi;
static Mqtt *mqtt;
static Configuration *config;

TEST_GROUP(TestGroupProducer)
{
    void setup()
    {   
        config = new Configuration();
        wifi = new Wifi();
        mqtt = new Mqtt(config);
        producer = new Producer(mqtt);
    }

    void teardown()
    {   
        delete producer;
        delete wifi;
        delete mqtt;
        delete config;
        mock().checkExpectations();
        mock().clear();
    }
};

TEST(TestGroupProducer, ProducerConstructor)
{
    Producer testProducer(NULL);
}

TEST(TestGroupProducer, ProducerInitalize) {
    CHECK(true);
}
