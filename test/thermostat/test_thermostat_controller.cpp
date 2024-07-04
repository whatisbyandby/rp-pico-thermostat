#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "thermostat.hpp"
#include "temperature_controller.hpp"

static Thermostat *thermostat;
static TemperatureController *tempController;
static ThermostatContext *context;

TEST_GROUP(ThermostatControllerTestGroup)
{
    void setup()
    {   
        tempController = new TemperatureController();
        thermostat = new Thermostat();

        context = new ThermostatContext();
        context->tempController = tempController;

        thermostat->initialize(context);
    }

    void teardown()
    {
        mock().checkExpectations();
        mock().clear();
        delete thermostat;
        delete tempController;
        delete context;
    }
};


TEST(ThermostatControllerTestGroup, ExecuteCommandSetTemperature_Valid) {

    ThermostatCommand validCommand {
        SET_TEMPERATURE,
        25.0
    };

    thermostat->setTemperatureUnits(CELSIUS);


    ENUMS_EQUAL_TYPE(ThermostatError, THERMOSTAT_OK, thermostat->executeCommand(&validCommand));
    DOUBLES_EQUAL(25.0, thermostat->getTargetTemperature(), 0.01);

}

TEST(ThermostatControllerTestGroup, ExecuteCommandSetTemperature_Invalid) {


     ThermostatCommand invalidCommand {
        SET_TEMPERATURE,
        6.9
    };

    ENUMS_EQUAL_TYPE(ThermostatError, THERMOSTAT_INVALID_INPUT, thermostat->executeCommand(&invalidCommand));
}

TEST(ThermostatControllerTestGroup, ExecuteCommandSetMode_Valid) {

    ThermostatCommand validCommand {
        SET_MODE,
        HEAT
    };

    ENUMS_EQUAL_TYPE(ThermostatError, THERMOSTAT_OK, thermostat->executeCommand(&validCommand));

}

TEST(ThermostatControllerTestGroup, ExecuteCommandSetUnits_Valid) {

    ThermostatCommand validCommand {
        SET_UNITS,
        CELSIUS
    };

    ENUMS_EQUAL_TYPE(ThermostatError, THERMOSTAT_OK, thermostat->executeCommand(&validCommand));
    ENUMS_EQUAL_TYPE(TemperatureUnits, CELSIUS, thermostat->getTemperatureUnits());

}

TEST(ThermostatControllerTestGroup, ExecuteCommand_PrintState) {

    ThermostatCommand validCommand {
        PRINT_STATE,
        0
    };

    mock().expectOneCall("HVAC::getCurrentState");

    ENUMS_EQUAL_TYPE(ThermostatError, THERMOSTAT_OK, thermostat->executeCommand(&validCommand));

}

TEST(ThermostatControllerTestGroup, ExecuteCommandSetMode_Invalid) {


    ThermostatCommand validCommand {
        SET_MODE,
        47.0 // Invalid mode
    };

    ENUMS_EQUAL_TYPE(ThermostatError, THERMOSTAT_INVALID_INPUT, thermostat->executeCommand(&validCommand));
}

