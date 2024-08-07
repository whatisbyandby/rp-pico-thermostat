#ifndef THERMOSTAT_COMMON_HPP
#define THERMOSTAT_COMMON_HPP

#include <string>

#define THERMOSTAT_VERSION "1.0.0"

typedef enum ThermostatError
{
    THERMOSTAT_OK = 0,
    THERMOSTAT_NO_DATA,
    THERMOSTAT_ERROR,
    THERMOSTAT_INVALID_INPUT,
    THERMOSTAT_NOT_INITALIZED,
    THERMOSTAT_INIT_FAILED,
    THERMOSTAT_SENSOR_ERROR,
    THERMOSTAT_UNKNOWN_COMMAND,
    THERMOSTAT_CONNECTION_ERROR
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

enum ThermostatCommandType
{
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

class ThermostatCommand
{
public:
    ThermostatCommandType command_type;
    double parameter;
    std::string command_string;
    std::string resultString;
};

typedef void (*CommandCallback)(ThermostatCommand *command, void *arg);

typedef enum TemperatureState
{
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

typedef enum ThermostatState
{
    HEATING,
    COOLING,
    FAN_ON,
    IDLE,
    ERROR
} ThermostatState;

inline const char *hvacStateToString(ThermostatState state)
{
    switch (state)
    {
    case HEATING:
        return "HEATER_ON";
    case COOLING:
        return "COOLER_ON";
    case FAN_ON:
        return "FAN_ON";
    case IDLE:
        return "ALL_OFF";
    default:
        return "UNKNOWN";
    }
}

typedef enum ThermostatMode
{
    HEAT,
    COOL,
    FAN_ONLY,
    OFF
} ThermostatMode;

inline ThermostatError validateThermostatMode(ThermostatMode mode)
{
    switch (mode)
    {
    case HEAT:
    case COOL:
    case FAN_ONLY:
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
    case HEAT:
        return "HEATING";
    case COOL:
        return "COOLING";
    case FAN_ONLY:
        return "FAN_ONLY";
    case OFF:
        return "OFF";
    default:
        return "UNKNOWN";
    }
}

typedef enum TemperatureUnits
{
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

struct ThermostatData
{
    double currentTemperature;
    double targetTemperature;
    double temperatureRange;
    double currentTemperatureStandardUnits;
    double targetTemperatureStandardUnits;
    double currentHumidity;
    TemperatureState temperatureState;
    ThermostatState hvacState;
    ThermostatMode mode;
    TemperatureUnits temperatureUnits;
    ThermostatError error;
};

#endif // THERMOSTAT_COMMON_HPP