#include <CppUTestExt/MockSupport.h>
#include "json.hpp"

ThermostatError serialize(char *buffer, size_t size, ThermostatState *state)
{
  return (ThermostatError) mock()
    .actualCall("serialize")
    .withPointerParameter("state", state)
    .withPointerParameter("buffer", buffer)
    .withIntParameter("size", size)
    .returnIntValueOrDefault(THERMOSTAT_OK);
}

ThermostatError parse(char *buffer, ThermostatCommand *command)
{
  return (ThermostatError) mock()
    .actualCall("parse")
    .withPointerParameter("buffer", buffer)
    .withPointerParameter("command", command)
    .returnIntValueOrDefault(THERMOSTAT_OK);
}
