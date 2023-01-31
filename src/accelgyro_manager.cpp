/**
 * @file accelgyro_manager.cpp
 * @author Kacper Wiśniewski (kwisniewski541@gmail.com)
 * @version 1.0
 * @date 2022-10-12
 */

//-------------------------------------------------------------------------------- 

#include <accelgyro_manager.h>

//--------------------------------------------------------------------------------

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif
#define ACCEL_CLOCK         MPU6050_DEFAULT_CLOCK
#define ACCEL_RANGE         MPU6050_DEFAULT_ACCEL_RANGE 

//--------------------------------------------------------------------------------

static bool operator ==(vector a, vector b);

//--------------------------------------------------------------------------------

void Accelgyro::init(uint8_t pin_scl, uint8_t pin_sda)
{
    Wire.begin(pin_sda, pin_scl);
    uint8_t wire_status = Wire.status();
    
    if (wire_status != (I2C_OK))
    {
        LOG("[ACCELGYRO_MANAGER] ERROR: I2C STATUS: " + String(wire_status));
        initialized = false;
        return;
    }

    uint8_t sensor_address = this->mpu6050->get_who_am_i();
    if ((sensor_address != MPU6050_DEFAULT_ADRESS) || (sensor_address == MPU6050_REGISTER_READ_ERROR))
    {
        LOG("[ACCELGYRO_MANAGER] MPU6050 Sensor initialization failed.");
        initialized = false;
        return;
    }

    this->mpu6050->set_clock_source(ACCEL_CLOCK);
    this->mpu6050->set_accel_range(ACCEL_RANGE);

    /* Put MPU6050 into Accelerometer Only Low Power Mode. */
    this->mpu6050->set_cycle(true);
    this->mpu6050->set_sleep(false);
    this->mpu6050->set_temp_dis(true);
    this->mpu6050->set_stby_xg(true);
    this->mpu6050->set_stby_yg(true);
    this->mpu6050->set_stby_zg(true);
    this->mpu6050->set_lp_wake_ctrl(MPU6050_WAKE_CTRL_5HZ);

    ConfigManager& config = ConfigManager::get_instance();
    config.get(COEFFICIENT_A, &this->coeff_a);
    config.get(COEFFICIENT_B, &this->coeff_b);
    config.get(COEFFICIENT_C, &this->coeff_c);
    config.get(COEFFICIENT_D, &this->coeff_d);
    config.get(COEFFICIENT_E, &this->coeff_e);

    initialized = true;
    LOG("[ACCELGYRO_MANAGER] MPU6050 Sensor initialization successful");
}

void Accelgyro::sleep()
{
    this->mpu6050->set_sleep(true);
}

float Accelgyro::get_plato(float temperature)
{
    calculate_plato(temperature);
    LOG("[ACCELGYRO_MANAGER] Plato read : " + String(plato));
    return plato;
}

float Accelgyro::get_temperature()
{
    if (!initialized)
        return ACCEL_TEMPERATURE_ERROR;

    return ((float)mpu6050->get_temperature() / 340) + 36.53;
}

void Accelgyro::measure_tilt()
{
    if (!initialized)
    {
        LOG("[ACCELGYRO_MANAGER] Accelerometer data cannot be retrieved. Sensor is not initialized.");
        tilt = -127;
        return;
    }

    accel = this->mpu6050->get_accel_data();
    
    if (this->accel == MPU6050_VECTOR_READ_ERROR)
    {
        tilt = ACCEL_TILT_ERROR;
        LOG("[ACCELGYRO_MANAGER] Failed reading data from accelerometer!");
        return;
    }

    /* Calculation of the Tilt Angle from vertical axis, in this case it is Y axis.
     * https://www.nxp.com/docs/en/application-note/AN3461.pdf
     */
    tilt = acos(abs(accel.y_axis) / sqrt((accel.x_axis * accel.x_axis) + (accel.y_axis * accel.y_axis)
                                       + (accel.z_axis * accel.z_axis))) * 180.0 / M_PI;
}

void Accelgyro::calculate_plato(float temperature)
{
    measure_tilt();

    /* Gravity calculated using the formula: a*tilt^4 + b*tilt^3 + c*tilt^2 + d*tilt + e */
    double gravity = (tilt != ACCEL_TILT_ERROR) ? (coeff_a * tilt * tilt * tilt * tilt) +
                                                  (coeff_b * tilt * tilt * tilt) +
                                                  (coeff_c * tilt * tilt) + (coeff_d *tilt) + coeff_e
                                                : ACCEL_TILT_ERROR;

    /* Gravity correction depending on the temperature, if temperature read ok.
       source : https://www.homebrewersassociation.org/attachments/0000/2497/Math_in_Mash_SummerZym95.pdf  */
    if (temperature != -127)
    {
        double t = (temperature * 1.8) + 32;  /**< Temperature in Fahrenheit. */
        double sg_correction_factor = 1.00130346 - 1.34722124 * 10e-04 * t +
                                    2.04052596 * 10e-06 * t * t - 2.32820948 * 10e-09 * t * t * t;
        gravity *= sg_correction_factor;
    }

    /* Math in  mash SummerZym95 <- formula (7). */
    plato = (-1 * 665.362) + (1262.45 * gravity) - (776.43 * gravity * gravity) + (182.94 * gravity * gravity * gravity);
}

/**
 * @brief Comparison of two structures containing axis data.
 * @return true when the axes are in the same position, otherwise false.
 */
static bool operator ==(vector a, vector b)
{
    return ((a.x_axis == b.x_axis) &&
            (a.y_axis == b.y_axis) &&
            (a.z_axis == b.z_axis));
}
