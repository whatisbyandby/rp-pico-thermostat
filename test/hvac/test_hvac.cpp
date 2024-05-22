#include "CppUTest/TestHarness.h"
#include "hvac.hpp"
#include "thermostat_common.hpp"

static HVAC *hvac;

TEST_GROUP(HVACTestGroup)
{
    void setup()
    {
        hvac = new HVAC();
    }

    void teardown()
    {
        delete hvac;
    }
};

TEST(HVACTestGroup, HVACConstructor)
{
    HVAC *testHvac = new HVAC();

    delete testHvac;
    
}

TEST(HVACTestGroup, HVACSetDesiredState)
{
    CHECK_EQUAL(THERMOSTAT_OK, hvac->setDesiredState(HEATER_ON));
    CHECK_EQUAL(HEATER_ON, hvac->getCurrentState());
}
