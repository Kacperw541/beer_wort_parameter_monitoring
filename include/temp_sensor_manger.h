/**
 * @file temp_sensor_manger.h
 * @author Kacper Wiśniewski
 * @version 1.0
 * @date 2022-11-27
 */

//--------------------------------------------------------------------------------

#ifndef TEMP_SENSOR_MANAGER_H_
#define TEMP_SENSOR_MANAGER_H_

//--------------------------------------------------------------------------------

#include <OneWire.h>
#include <DallasTemperature.h>
#include "log_debug.h"

//--------------------------------------------------------------------------------

#define DS18B20_RESOLUTION (int)12

//--------------------------------------------------------------------------------

/** @brief Class for handling the DS18B20 temperature sensor. */
class Temperature
{
public:

    /** @brief Construct a new Temperature object. */
    Temperature();

    /** @brief Destroy the Temperature object. */
    ~Temperature();

    /**
     * @brief Sensor initialization and communication.
     * @param [in] pin - Pin responsible for one wire communication.
     */
    void init(uint8_t pin);

    /**
     * @brief Get the temperature measurement.
     * @return float - value of the measured temperature in degrees Celsius.
     */
    float get_temp();

    /** @brief One wire communication depower. */
    void sleep();

private:

    bool initialized;               /**< Flag indicating sensor initialization status. */
    OneWire *one_wire;              /**< Pointer to OneWire responsible for communication */
    DallasTemperature *temp_sensor; /**< Pointer to dallasTemperature, responsible for low-level handling of the sensor. */
    uint8_t device_address;         /**< Sensor address. */
};

//--------------------------------------------------------------------------------

#endif /* TEMP_SENSOR_MANAGER_H_ */