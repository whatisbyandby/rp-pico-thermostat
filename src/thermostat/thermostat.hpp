#include "environment_sensor.hpp"

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

class Thermostat {
    public:
        Thermostat();
        ~Thermostat();

        ThermostatError initialize();
        bool isInitialized();

        ThermostatError setTargetTemperature(double targetTemperature);
        double getTargetTemperature();

        ThermostatError setTemperatureUnits(TemperatureUnits temperatureUnits);
        TemperatureUnits getTemperatureUnits();

        ThermostatError setEnvironmentSensor(EnvironmentSensor *environmentSensor);
    
    private:
        double targetTemperature;
        TemperatureUnits temperatureUnits;
        ThermostatError validateTargetTemperature(double targetTemperatureCelcius);
        double getTemperatureInStandardUnits(double temperature);
        double getTemperatureInCurrentUnits(double temperatureInStandardUnits);
        EnvironmentSensor *environmentSensor;
        bool initalized;
        
};