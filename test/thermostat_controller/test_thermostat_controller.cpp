#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "thermostat_controller.hpp"

static Thermostat *thermostat;
static ThermostatController *thermostatController;


TEST_GROUP(ThermostatControllerTestGroup)
{
    void setup()
    {
        thermostat = new Thermostat(NULL, NULL, NULL);
        thermostatController = new ThermostatController(thermostat);
    }

    void teardown()
    {
        mock().checkExpectations();
        mock().clear();
        delete thermostatController;
        delete thermostat;
    }
};

TEST(ThermostatControllerTestGroup, TestThermostatControllerConstructor) {

    Thermostat *testThermostat = new Thermostat(NULL, NULL, NULL);
    ThermostatController *testController = new ThermostatController(testThermostat);

    delete testController;
    delete testThermostat;
}

TEST(ThermostatControllerTestGroup, ExecuteCommandSetTemperature_Valid) {

    ThermostatCommand validCommand {
        SET_TEMPERATURE,
        25.0
    };

    mock().expectOneCall("Thermostat::setTargetTemperature")
        .withParameter("targetTemperature", 25.0)
        .andReturnValue(THERMOSTAT_OK);

    mock().expectOneCall("Thermostat::getTargetTemperature")
        .andReturnValue(25.0);

    ENUMS_EQUAL_TYPE(ThermostatError, THERMOSTAT_OK, thermostatController->executeCommand(&validCommand));

}

TEST(ThermostatControllerTestGroup, ExecuteCommandSetTemperature_Invalid) {


     ThermostatCommand invalidCommand {
        SET_TEMPERATURE,
        9.0
    };

    mock().expectOneCall("Thermostat::setTargetTemperature")
        .withParameter("targetTemperature", 9.0)
        .andReturnValue(THERMOSTAT_INVALID_INPUT);

     mock().expectOneCall("Thermostat::getTargetTemperature")
        .andReturnValue(25.0);

    ENUMS_EQUAL_TYPE(ThermostatError, THERMOSTAT_INVALID_INPUT, thermostatController->executeCommand(&invalidCommand));
}

TEST(ThermostatControllerTestGroup, ExecuteCommandSetMode_Valid) {

    ThermostatCommand validCommand {
        SET_MODE,
        HEATING
    };

    mock().expectOneCall("Thermostat::setMode")
        .withParameter("mode", HEATING).andReturnValue(THERMOSTAT_OK);

    mock().expectOneCall("Thermostat::getMode")
        .andReturnValue(HEATING);

    ENUMS_EQUAL_TYPE(ThermostatError, THERMOSTAT_OK, thermostatController->executeCommand(&validCommand));

}

TEST(ThermostatControllerTestGroup, ExecuteCommand_PrintState) {

    ThermostatCommand validCommand {
        PRINT_STATE,
        0
    };

    mock().expectOneCall("Thermostat::printState").ignoreOtherParameters();

    ENUMS_EQUAL_TYPE(ThermostatError, THERMOSTAT_OK, thermostatController->executeCommand(&validCommand));

}

TEST(ThermostatControllerTestGroup, ExecuteCommandSetMode_Invalid) {


    ThermostatCommand validCommand {
        SET_MODE,
        47.0 // Invalid mode
    };

    mock().expectOneCall("Thermostat::setMode")
        .withParameter("mode", 47).andReturnValue(THERMOSTAT_INVALID_INPUT);

    mock().expectOneCall("Thermostat::getMode")
        .andReturnValue(HEATING);

    ENUMS_EQUAL_TYPE(ThermostatError, THERMOSTAT_INVALID_INPUT, thermostatController->executeCommand(&validCommand));
}

