#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "hvac.hpp"
#include "thermostat_common.hpp"
#include "gpio.hpp"
#include <CppUTestExt/MockExpectedCall.h>

static HVAC *hvac;
static Switch *heater;
static Switch *ac;
static Switch *fan;

TEST_GROUP(HVACTestGroup)
{
    void setup()
    {
        hvac = new HVAC();
        heater = new Switch(1);
        ac = new Switch(2);
        fan = new Switch(3);

        hvac->setHeater(heater);
        hvac->setAC(ac);
        hvac->setFan(fan);
    }

    void teardown()
    {
        delete hvac;
        delete heater;
        delete ac;
        delete fan;
        mock().clear();
    }
};

TEST(HVACTestGroup, HVACConstructor)
{
    HVAC *testHvac = new HVAC();

    delete testHvac;
    
}


TEST(HVACTestGroup, SetHeaterOn)
{
    mock().expectOneCall("Switch::turnOn").onObject(heater);
    mock().expectOneCall("Switch::turnOff").onObject(ac);
    mock().expectOneCall("Switch::turnOff").onObject(fan);

    mock().expectOneCall("Switch::isOn").onObject(heater).andReturnValue(true);
    mock().expectOneCall("Switch::isOn").onObject(ac).andReturnValue(false);
    mock().expectOneCall("Switch::isOn").onObject(fan).andReturnValue(false);

    CHECK_EQUAL(THERMOSTAT_OK, hvac->setDesiredState(HEATER_ON));
    CHECK_EQUAL(HEATER_ON, hvac->getCurrentState());
}

TEST(HVACTestGroup, SetIdleMode)
{
    mock().expectOneCall("Switch::turnOff").onObject(heater);
    mock().expectOneCall("Switch::turnOff").onObject(ac);
    mock().expectOneCall("Switch::turnOff").onObject(fan);

    mock().expectOneCall("Switch::isOn").onObject(heater).andReturnValue(false);
    mock().expectOneCall("Switch::isOn").onObject(ac).andReturnValue(false);
    mock().expectOneCall("Switch::isOn").onObject(fan).andReturnValue(false);

    CHECK_EQUAL(THERMOSTAT_OK, hvac->setDesiredState(IDLE));
    CHECK_EQUAL(IDLE, hvac->getCurrentState());
}
