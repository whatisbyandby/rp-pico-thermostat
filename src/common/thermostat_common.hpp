#ifndef THERMOSTAT_COMMON_HPP
#define THERMOSTAT_COMMON_HPP

typedef enum ThermostatError {
    THERMOSTAT_ERROR,
    THERMOSTAT_INVALID_INPUT,
    THERMOSTAT_OK
} ThermostatError;

typedef enum TemperatureUnits {
    FAHRENHEIT,
    CELSIUS
} TemperatureUnits;


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