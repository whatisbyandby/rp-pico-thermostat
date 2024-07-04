#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "repl.hpp"
#include "command_parser.hpp"
#include "thermostat_common.hpp"

static Repl *repl;
static CommandParser *parser;

TEST_GROUP(TestGroupRepl){
    void setup(){
        parser = new CommandParser();
repl = new Repl();
}

void teardown()
{
    delete parser;
    delete repl;
    mock().checkExpectations();
    mock().clear();
}
}
;

TEST(TestGroupRepl, ReplTestReadNoData)
{

    mock().expectOneCall("uart_is_readable").ignoreOtherParameters().andReturnValue(false);

    ThermostatCommand command;
    ENUMS_EQUAL_INT(THERMOSTAT_NO_DATA, repl->read(&command));
}

TEST(TestGroupRepl, ReplTestReadData)
{

    mock().expectOneCall("uart_is_readable").ignoreOtherParameters().andReturnValue(true);

    mock().expectOneCall("uart_is_readable").ignoreOtherParameters().andReturnValue(true);

    mock().expectOneCall("uart_getc").ignoreOtherParameters().andReturnValue('t');

    mock().expectOneCall("uart_is_readable").ignoreOtherParameters().andReturnValue(true);

    mock().expectOneCall("uart_getc").ignoreOtherParameters().andReturnValue('e');

    mock().expectOneCall("uart_is_readable").ignoreOtherParameters().andReturnValue(true);

    mock().expectOneCall("uart_getc").ignoreOtherParameters().andReturnValue('s');

    mock().expectOneCall("uart_is_readable").ignoreOtherParameters().andReturnValue(true);

    mock().expectOneCall("uart_getc").ignoreOtherParameters().andReturnValue('t');

    mock().expectOneCall("uart_is_readable").ignoreOtherParameters().andReturnValue(true);

    mock().expectOneCall("uart_getc").ignoreOtherParameters().andReturnValue('\n');

    ThermostatCommand command;
    ENUMS_EQUAL_INT(THERMOSTAT_OK, repl->read(&command));

    STRCMP_EQUAL("test", command.command_string.c_str());
}
