#include "configuration.hpp"
#include "hardware/flash.h"
#include "hardware/sync.h"
#include <cstring>

#define FLASH_TARGET_OFFSET (PICO_FLASH_SIZE_BYTES - FLASH_SECTOR_SIZE)

// Constructor
Configuration::Configuration() {
   memset(ssid, 0, sizeof(ssid));
    memset(password, 0, sizeof(password));
    memset(mqtt_host, 0, sizeof(mqtt_host));
    mqtt_port = 0;
    memset(mqtt_username, 0, sizeof(mqtt_username));
    memset(mqtt_password, 0, sizeof(mqtt_password));
}

// Destructor
Configuration::~Configuration() {
    // Clean up if needed
}

// Load configuration from flash memory
ThermostatError Configuration::load() {
    // Calculate the flash memory address
    const uint8_t* flash_data = (const uint8_t*)(XIP_BASE + FLASH_TARGET_OFFSET);

    ConfigValues config;
    // Copy data from flash to the configuration object
    memcpy(&config, flash_data, sizeof(ConfigValues));

    // Set the configuration values
    setConfig(&config);
    
    return THERMOSTAT_OK; // Replace with appropriate error handling
}

// Save configuration to flash memory
ThermostatError Configuration::save() {
    // Disable interrupts to safely write to flash
    uint32_t ints = save_and_disable_interrupts();
    
    // Erase the flash sector
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);

    ConfigValues config;
    getConfig(&config);
    
    // Write the configuration data to flash
    flash_range_program(FLASH_TARGET_OFFSET, (const uint8_t*)&config, sizeof(ConfigValues));
    
    // Restore interrupts
    restore_interrupts(ints);
    
    return THERMOSTAT_OK; // Replace with appropriate error handling
}

// Set the configuration values
ThermostatError Configuration::setConfig(ConfigValues *newConfig) {
    // Copy the new configuration values
    strcpy(ssid, newConfig->ssid);
    strcpy(password, newConfig->password);
    strcpy(mqtt_host, newConfig->mqtt_host);
    mqtt_port = newConfig->mqtt_port;
    strcpy(mqtt_username, newConfig->mqtt_username);
    strcpy(mqtt_password, newConfig->mqtt_password);
    
    return THERMOSTAT_OK; // Replace with appropriate error handling
}

// Get the configuration values
ThermostatError Configuration::getConfig(ConfigValues *config) {
    // Copy the configuration values
    strcpy(config->ssid, ssid);
    strcpy(config->password, password);
    strcpy(config->mqtt_host, mqtt_host);
    config->mqtt_port = mqtt_port;
    strcpy(config->mqtt_username, mqtt_username);
    strcpy(config->mqtt_password, mqtt_password);
    
    return THERMOSTAT_OK; // Replace with appropriate error handling
}


void Configuration::print() {
    // Print the configuration data
    printf("SSID: %s\n", ssid);
    printf("Password: %s\n", password);
    printf("MQTT Host: %s\n", mqtt_host);
    printf("MQTT Port: %d\n", mqtt_port);
    printf("MQTT Username: %s\n", mqtt_username);
    printf("MQTT Password: %s\n", mqtt_password);
}
