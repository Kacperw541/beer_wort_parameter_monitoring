/**
 * @file accelgyro_manager.h
 * @author Kacper Wiśniewski (kwisniewski541@gmail.com)
 * @version 1.0
 * @date 2022-10-12
 */

//--------------------------------------------------------------------------------

#ifndef ACCELGYRO_M_H_
#define ACCELGYRO_M_H_

//--------------------------------------------------------------------------------

#include <Arduino.h>
#include <Wire.h>
#include <math.h>
#include <mpu6050.h>
#include <config_manager.h>
#include <log_debug.h>

//--------------------------------------------------------------------------------
/* Error codes .*/

#define ACCEL_TILT_ERROR        (-127)
#define ACCEL_TEMPERATURE_ERROR (-127)

//--------------------------------------------------------------------------------

/**
 * @brief Class for handling the mpu6050 sensor and processing data received from this sensor.
 */
class Accelgyro
{
public:

    /**
     * @brief Construct a new Accelgyro object
     * @param mpu6050 - pointer to the MPU6050
     */
    Accelgyro(MPU6050 *mpu6050 = nullptr)
    {
        this->mpu6050 = mpu6050 ?: new MPU6050;
    }

    /** @brief Destroy the Accelgyro object. */
    ~Accelgyro() 
    {
        delete mpu6050;
    }

    /**
     * @brief Initialization of the MPU6050 sensor and communication
     * @note  this function must be called before using accelgyro
     * @param [in] pin_scl - serial clock pin 
     * @param [in] pin_sda - serial data pin 
     */
    void init(uint8_t pin_scl, uint8_t pin_sda);

    /** @brief Puts the sensor into sleep mode to save power. */
    void sleep();

    /**
     * @brief Calculates and returns plato degrees of the concentration of dissolved solids in a brewery wort
     * @param [in] temperature - used to calibrate solution density.
     * @return float - Degrees Plato (°P) 
     */
    float get_plato(float temperature);

    /**
     * @brief Performs the measurement through the temperature sensor in mpu6050.
     * @return float - temperature in degrees Celsius
     */
    float get_temperature();

private:

    /**
     * @brief Performs the position measurement using the accelerometer
     *        and calculates the tilt using the given formula.
     */
    void measure_tilt();

    /**
     * @brief Calculates degrees Plato using tilt and correction based on temperature.
     * @param [in] temperature - variable responsible for correcting solution density
     */
    void calculate_plato(float temperature);

    MPU6050 *mpu6050;   /**< Pointer to the MPU6050 class. */
    vector accel;       /**< Buffer for accelerometer data. */
    double coeff_a;     /**< The coefficient of the function that calculates the density of the solution. */
    double coeff_b;     /**< The coefficient of the function that calculates the density of the solution. */
    double coeff_c;     /**< The coefficient of the function that calculates the density of the solution. */
    double coeff_d;     /**< The coefficient of the function that calculates the density of the solution. */
    double coeff_e;     /**< The coefficient of the function that calculates the density of the solution. */
    float temperature;  /**< Stores the measured temperature. */
    float tilt;         /**< Stores the calculated tilt. */
    float plato;        /**< Stores the calculated degrees Plato. */
    bool initialized;   /**< Flag indicating whether the sensor has been initialized and is ready for measurements.*/

};

//--------------------------------------------------------------------------------

#endif /* ACCELGYRO_M_H_ */