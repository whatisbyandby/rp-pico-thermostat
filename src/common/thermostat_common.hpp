#ifndef THERMOSTAT_COMMON_HPP
#define THERMOSTAT_COMMON_HPP


typedef enum ThermostatError {
    THERMOSTAT_OK = 0,
    THERMOSTAT_ERROR,
    THERMOSTAT_INVALID_INPUT,
    THERMOSTAT_UNKNOWN_COMMAND
} ThermostatError;

inline const char *thermostatErrorToString(ThermostatError error)
{
    switch (error)
    {
    case THERMOSTAT_ERROR:
        return "THERMOSTAT_ERROR";
    case THERMOSTAT_INVALID_INPUT:
        return "THERMOSTAT_INVALID_INPUT";
    case THERMOSTAT_OK:
        return "THERMOSTAT_OK";
    case THERMOSTAT_UNKNOWN_COMMAND:
        return "THERMOSTAT_UNKNOWN_COMMAND";
    default:
        return "UNKNOWN";
    }
}

enum ThermostatCommandType {
    SET_TEMPERATURE,
    SET_MODE,
    SET_UNITS,
    PRINT_STATE,
    GET_STATE,
    GET_HVAC_STATE,
    GET_ERROR,
    VERSION,
    HELP,
    INVALID_COMMAND
};

struct ThermostatCommand {
    ThermostatCommandType command_type;
    double parameter;
};

typedef enum TemperatureState {
    OVER_TEMPERATURE,
    UNDER_TEMPERATURE,
    UNDER_TEMPERATURE_IN_RANGE,
    OVER_TEMPERATURE_IN_RANGE,
    IN_RANGE
} TemperatureState;

inline const char *temperatureStateToString(TemperatureState state)
{
    switch (state)
    {
    case OVER_TEMPERATURE:
        return "OVER_TEMPERATURE";
    case UNDER_TEMPERATURE:
        return "UNDER_TEMPERATURE";
    case UNDER_TEMPERATURE_IN_RANGE:
        return "UNDER_TEMPERATURE_IN_RANGE";
    case OVER_TEMPERATURE_IN_RANGE:
        return "OVER_TEMPERATURE_IN_RANGE";
    case IN_RANGE:
        return "IN_RANGE";
    default:
        return "UNKNOWN";
    }
}

typedef enum HVACState {
    HEATER_ON,
    COOLER_ON,
    FAN_ON,
    ALL_OFF
} HVACState;

inline const char *hvacStateToString(HVACState state)
{
    switch (state)
    {
    case HEATER_ON:
        return "HEATER_ON";
    case COOLER_ON:
        return "COOLER_ON";
    case FAN_ON:
        return "FAN_ON";
    case ALL_OFF:
        return "ALL_OFF";
    default:
        return "UNKNOWN";
    }
}

typedef enum ThermostatMode {
    HEATING,
    COOLING,
    FAN_ONLY,
    ERROR,
    OFF
} ThermostatMode;

inline ThermostatError validateThermostatMode(ThermostatMode mode)
{
    switch (mode)
    {
    case HEATING:
    case COOLING:
    case FAN_ONLY:
    case ERROR:
    case OFF:
        return THERMOSTAT_OK;
    default:
        return THERMOSTAT_INVALID_INPUT;
    }
}

inline const char *thermostatModeToString(ThermostatMode mode)
{
    switch (mode)
    {
    case HEATING:
        return "HEATING";
    case COOLING:
        return "COOLING";
    case FAN_ONLY:
        return "FAN_ONLY";
    case ERROR:
        return "ERROR";
    case OFF:
        return "OFF";
    default:
        return "UNKNOWN";
    }
}

typedef enum TemperatureUnits {
    FAHRENHEIT,
    CELSIUS
} TemperatureUnits;

inline const char *temperatureUnitsToString(TemperatureUnits units)
{
    switch (units)
    {
    case FAHRENHEIT:
        return "FAHRENHEIT";
    case CELSIUS:
        return "CELSIUS";
    default:
        return "UNKNOWN";
    }
}


double convertFahrenheitToCelsius(double fahrenheit);
double convertCelsiusToFahrenheit(double celsius);

inline double convertFahrenheitToCelsius(double fahrenheit)
{
    return (fahrenheit - 32) * 5.0 / 9.0;
}

inline double convertCelsiusToFahrenheit(double celsius)
{
    return celsius * 9.0 / 5.0 + 32;
}

#endif // THERMOSTAT_COMMON_HPP