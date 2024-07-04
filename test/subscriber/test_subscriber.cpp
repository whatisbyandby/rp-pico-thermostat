#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "subscriber.hpp"


TEST_GROUP(TestGroupSubscriber)
{
    void setup()
    {
    }

    void teardown()
    {   
        mock().checkExpectations();
        mock().clear();
    }
};

TEST(TestGroupSubscriber, SubscriberConstructor)
{
    Subscriber testSubscriber;
}

TEST(TestGroupSubscriber, SubscriberSubscribe)
{   
    Configuration config;
    Mqtt mqtt;
    Subscriber testSubscriber;

    mock().expectOneCall("Mqtt::subscribe")
        .withStringParameter("topic", "test/topic")
        .andReturnValue(THERMOSTAT_OK);

    testSubscriber.subscribe("test/topic");
}