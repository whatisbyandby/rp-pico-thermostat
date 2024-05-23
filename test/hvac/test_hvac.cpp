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


IGNORE_TEST(HVACTestGroup, SetHeaterOn)
{
    mock().actualCall("Switch::turnOn").onObject(heater);
    mock().actualCall("Switch::turnOff").onObject(ac);
    mock().actualCall("Switch::turnOff").onObject(fan);
    mock().actualCall("Switch::isOn").onObject(heater).returnBoolValueOrDefault(true);
    mock().actualCall("Switch::isOn").onObject(ac).returnBoolValueOrDefault(false);
    mock().actualCall("Switch::isOn").onObject(fan).returnBoolValueOrDefault(false);
    CHECK_EQUAL(THERMOSTAT_OK, hvac->setDesiredState(HEATER_ON));
    CHECK_EQUAL(HEATER_ON, hvac->getCurrentState());
    mock().checkExpectations();
}

IGNORE_TEST(HVACTestGroup, SetIdleMode)
{
    mock().expectOneCall("Switch::turnOff").onObject(heater);
    mock().expectOneCall("Switch::turnOff").onObject(ac);
    mock().expectOneCall("Switch::turnOff").onObject(fan);
    mock().actualCall("Switch::isOn").onObject(heater).returnBoolValueOrDefault(false);
    mock().actualCall("Switch::isOn").onObject(ac).returnBoolValueOrDefault(false);
    mock().actualCall("Switch::isOn").onObject(fan).returnBoolValueOrDefault(false);
    CHECK_EQUAL(THERMOSTAT_OK, hvac->setDesiredState(IDLE));
    CHECK_EQUAL(IDLE, hvac->getCurrentState());
    mock().checkExpectations();
}
