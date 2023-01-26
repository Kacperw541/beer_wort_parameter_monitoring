/**
 * @file mpu6050.cpp
 * @author Kacper Wiśniewski (kwisniewski541@gmail.com)
 * @version 1.0
 * @date 2022-10-18
 */

//--------------------------------------------------------------------------------

#include <Arduino.h>
#include <Wire.h>
#include <mpu6050.h>

//------------------------------------------------------------------------
/* SMPRT_DIV (0X19) register. */

void MPU6050::set_sample_rate_divider(uint8_t smplrt_div)
{
    write_register_byte(MPU6050_REGISTER_SMPLRT_DIV, smplrt_div);
}

uint8_t MPU6050::get_sample_rate_divider()
{
    read_register_byte(MPU6050_REGISTER_SMPLRT_DIV, &temp_register);
    return temp_register;
}

//------------------------------------------------------------------------
/* CONFIG (0x1A register). */

void MPU6050::set_ext_sync(mpu6050_config_ext_sync_set ext_sync)
{
    write_register_byte(MPU6050_REGISTER_CONFIG, ext_sync, MPU6050_CONFIG_EXT_SYNS_POSITION, MPU6050_CONFIG_EXT_SYNS_BITMASK);
}

mpu6050_config_ext_sync_set MPU6050::get_ext_sync(void)
{
    read_register_byte(MPU6050_REGISTER_CONFIG, &temp_register, MPU6050_CONFIG_EXT_SYNS_POSITION, MPU6050_CONFIG_EXT_SYNS_BITMASK);
    return (mpu6050_config_ext_sync_set)temp_register;
}

void MPU6050::set_dlpf_mode(mpu6050_config_dlpf_cfg dlpf)
{
    write_register_byte(MPU6050_REGISTER_CONFIG, dlpf, MPU6050_CONFIG_DLPF_POSITION, MPU6050_CONFIG_DLPF_BITMASK);
}

mpu6050_config_dlpf_cfg MPU6050::get_dlpf_mode(void)
{
    read_register_byte(MPU6050_REGISTER_CONFIG, &temp_register, MPU6050_CONFIG_DLPF_POSITION, MPU6050_CONFIG_DLPF_BITMASK);
    return mpu6050_config_dlpf_cfg(temp_register);
}

//------------------------------------------------------------------------
/* GYRO_CONFIG (0x1B) register */

void MPU6050::set_gyro_scale(mpu6050_gyro_config_fs_sel gyro_scale)
{
    write_register_byte(MPU6050_REGISTER_GYRO_CONFIG, gyro_scale, MPU6050_GYRO_CONFIG_FS_SEL_POSITION, MPU6050_GYRO_CONFIG_FS_SEL_BITMASK);
}

mpu6050_gyro_config_fs_sel MPU6050::get_gyro_scale(void)
{
    read_register_byte(MPU6050_REGISTER_GYRO_CONFIG, &temp_register, MPU6050_GYRO_CONFIG_FS_SEL_POSITION, MPU6050_GYRO_CONFIG_FS_SEL_BITMASK);
    return (mpu6050_gyro_config_fs_sel)temp_register;
}

void MPU6050::set_gyro_x_self_test(bool state)
{
    write_register_bit(MPU6050_REGISTER_GYRO_CONFIG, MPU6050_GYRO_CONFIG_XG_ST, state);
}

bool MPU6050::get_gyro_x_self_test(void)
{
    read_register_bit(MPU6050_REGISTER_GYRO_CONFIG, MPU6050_GYRO_CONFIG_XG_ST, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_gyro_y_self_test(bool state)
{
    write_register_bit(MPU6050_REGISTER_GYRO_CONFIG, MPU6050_GYRO_CONFIG_YG_ST, state);
}

bool MPU6050::get_gyro_y_self_test(void)
{
    read_register_bit(MPU6050_REGISTER_GYRO_CONFIG, MPU6050_GYRO_CONFIG_YG_ST, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_gyro_z_self_test(bool state)
{
    write_register_bit(MPU6050_REGISTER_GYRO_CONFIG, MPU6050_GYRO_CONFIG_ZG_ST, state);
}

bool MPU6050::get_gyro_z_self_test(void)
{
    read_register_bit(MPU6050_REGISTER_GYRO_CONFIG, MPU6050_GYRO_CONFIG_ZG_ST, &temp_register_bit_state);
    return temp_register_bit_state;
}

//------------------------------------------------------------------------
/* ACCEL_CONFIG (0x1C register) */

void MPU6050::set_accel_range(mpu6050_accel_config_afs_sel range)
{
    write_register_byte(MPU6050_REGISTER_ACCEL_CONFIG, range, MPU6050_ACCEL_CONFIG_AFS_SEL_POSITION, MPU6050_ACCEL_CONFIG_AFS_SEL_BITMASK);
}

mpu6050_accel_config_afs_sel MPU6050::get_accel_range(void)
{
    read_register_byte(MPU6050_REGISTER_ACCEL_CONFIG, &temp_register, MPU6050_ACCEL_CONFIG_AFS_SEL_POSITION, MPU6050_ACCEL_CONFIG_AFS_SEL_BITMASK);
    return (mpu6050_accel_config_afs_sel)temp_register;
}

void MPU6050::set_accel_x_self_test(bool state)
{
    write_register_bit(MPU6050_REGISTER_ACCEL_CONFIG, MPU6050_ACCEL_CONFIG_XA_ST, state);
}

bool MPU6050::get_accel_x_self_test(void)
{
    read_register_bit(MPU6050_REGISTER_ACCEL_CONFIG, MPU6050_ACCEL_CONFIG_XA_ST, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_accel_y_self_test(bool state)
{
    write_register_bit(MPU6050_REGISTER_ACCEL_CONFIG, MPU6050_ACCEL_CONFIG_YA_ST, state);
}

bool MPU6050::get_accel_y_self_test(void)
{
    read_register_bit(MPU6050_REGISTER_ACCEL_CONFIG, MPU6050_ACCEL_CONFIG_YA_ST, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_accel_z_self_test(bool state)
{
    write_register_bit(MPU6050_REGISTER_ACCEL_CONFIG, MPU6050_ACCEL_CONFIG_ZA_ST, state);
}

bool MPU6050::get_accel_z_self_test(void)
{
    read_register_bit(MPU6050_REGISTER_ACCEL_CONFIG, MPU6050_ACCEL_CONFIG_ZA_ST, &temp_register_bit_state);
    return temp_register_bit_state;
}

//------------------------------------------------------------------------
/* FIFO_EN (0x23) register */

void MPU6050::set_fifo_en_slv0(bool state)
{
    write_register_bit(MPU6050_REGISTER_FIFO_EN, MPU6050_FIFO_EN_SLV0_FIFO_EN, state);
}

bool MPU6050::get_fifo_en_slv0(void)
{
    read_register_bit(MPU6050_REGISTER_FIFO_EN, MPU6050_FIFO_EN_SLV0_FIFO_EN, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_fifo_en_slv1(bool state)
{
    write_register_bit(MPU6050_REGISTER_FIFO_EN, MPU6050_FIFO_EN_SLV1_FIFO_EN, state);
}

bool MPU6050::get_fifo_en_slv1(void)
{
    read_register_bit(MPU6050_REGISTER_FIFO_EN, MPU6050_FIFO_EN_SLV1_FIFO_EN, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_fifo_en_slv2(bool state)
{
    write_register_bit(MPU6050_REGISTER_FIFO_EN, MPU6050_FIFO_EN_SLV2_FIFO_EN, state);
}

bool MPU6050::get_fifo_en_slv2(void)
{
    read_register_bit(MPU6050_REGISTER_FIFO_EN, MPU6050_FIFO_EN_SLV2_FIFO_EN, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_fifo_en_accel(bool state)
{
    write_register_bit(MPU6050_REGISTER_FIFO_EN, MPU6050_FIFO_EN_ACCEL_FIFO_EN, state);
}

bool MPU6050::get_fifo_en_accel(void)
{
    read_register_bit(MPU6050_REGISTER_FIFO_EN, MPU6050_FIFO_EN_ACCEL_FIFO_EN, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_fifo_en_xg(bool state)
{
    write_register_bit(MPU6050_REGISTER_FIFO_EN, MPU6050_FIFO_EN_XG_FIFO_EN, state);
}

bool MPU6050::get_fifo_en_xg(void)
{
    read_register_bit(MPU6050_REGISTER_FIFO_EN, MPU6050_FIFO_EN_XG_FIFO_EN, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_fifo_en_yg(bool state)
{
    write_register_bit(MPU6050_REGISTER_FIFO_EN, MPU6050_FIFO_EN_YG_FIFO_EN, state);
}

bool MPU6050::get_fifo_en_yg(void)
{
    read_register_bit(MPU6050_REGISTER_FIFO_EN, MPU6050_FIFO_EN_YG_FIFO_EN, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_fifo_en_zg(bool state)
{
    write_register_bit(MPU6050_REGISTER_FIFO_EN, MPU6050_FIFO_EN_ZG_FIFO_EN, state);
}

bool MPU6050::get_fifo_en_zg(void)
{
    read_register_bit(MPU6050_REGISTER_FIFO_EN, MPU6050_FIFO_EN_ZG_FIFO_EN, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_fifo_en_temp(bool state)
{
    write_register_bit(MPU6050_REGISTER_FIFO_EN, MPU6050_FIFO_EN_TEMP_FIFO_EN, state);
}

bool MPU6050::get_fifo_en_temp(void)
{
    read_register_bit(MPU6050_REGISTER_FIFO_EN, MPU6050_FIFO_EN_TEMP_FIFO_EN, &temp_register_bit_state);
    return temp_register_bit_state;
}

//------------------------------------------------------------------------
/* TODO: Registers 0x24 to 0x36. */


//------------------------------------------------------------------------
/* INT_PIN_CFG (0x37) register */ 

void MPU6050::set_int_level(bool state)
{
    write_register_bit(MPU6050_REGISTER_INT_PIN_CFG, MPU6050_INT_PIN_CFG_INT_LEVEL, state);
}

bool MPU6050::get_int_level(void)
{
    read_register_bit(MPU6050_REGISTER_INT_PIN_CFG, MPU6050_INT_PIN_CFG_INT_LEVEL, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_int_open(bool state)
{
    write_register_bit(MPU6050_REGISTER_INT_PIN_CFG, MPU6050_INT_PIN_CFG_INT_OPEN, state);
}

bool MPU6050::get_int_open(void)
{
    read_register_bit(MPU6050_REGISTER_INT_PIN_CFG, MPU6050_INT_PIN_CFG_INT_OPEN, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_latch_int_en(bool state)
{
    write_register_bit(MPU6050_REGISTER_INT_PIN_CFG, MPU6050_INT_PIN_CFG_LATCH_INT_EN, state);
}

bool MPU6050::get_latch_int_en(void)
{
    read_register_bit(MPU6050_REGISTER_INT_PIN_CFG, MPU6050_INT_PIN_CFG_LATCH_INT_EN, &temp_register_bit_state);
    return temp_register_bit_state;
}
void MPU6050::set_int_rd_clear(bool state)
{
    write_register_bit(MPU6050_REGISTER_INT_PIN_CFG, MPU6050_INT_PIN_CFG_INT_RD_CLEAR, state);
}

bool MPU6050::get_int_rd_clear(void)
{
    read_register_bit(MPU6050_REGISTER_INT_PIN_CFG, MPU6050_INT_PIN_CFG_INT_RD_CLEAR, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_fsync_int_level(bool state)
{
    write_register_bit(MPU6050_REGISTER_INT_PIN_CFG, MPU6050_INT_PIN_CFG_FSYNC_INT_LEVEL, state);
}

bool MPU6050::get_fsync_int_level(void)
{
    read_register_bit(MPU6050_REGISTER_INT_PIN_CFG, MPU6050_INT_PIN_CFG_FSYNC_INT_LEVEL, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_fsync_int_en(bool state)
{
    write_register_bit(MPU6050_REGISTER_INT_PIN_CFG, MPU6050_INT_PIN_CFG_FSYNC_INT_EN, state);
}

bool MPU6050::get_fsync_int_en(void)
{
    read_register_bit(MPU6050_REGISTER_INT_PIN_CFG, MPU6050_INT_PIN_CFG_FSYNC_INT_EN, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_i2c_bypass_en(bool state)
{
    write_register_bit(MPU6050_REGISTER_INT_PIN_CFG, MPU6050_INT_PIN_CFG_I2C_BYPASS_EN, state);
}

bool MPU6050::get_i2c_bypass_en(void)
{
    read_register_bit(MPU6050_REGISTER_INT_PIN_CFG, MPU6050_INT_PIN_CFG_I2C_BYPASS_EN, &temp_register_bit_state);
    return temp_register_bit_state;
}

//------------------------------------------------------------------------
/* INT_ENABLE (0x38) register */

void MPU6050::set_int_enable_data_rdy(bool state)
{
    write_register_bit(MPU6050_REGISTER_INT_ENABLE, MPU6050_INT_ENABLE_DATA_RDY_EN, state);
}

bool MPU6050::get_int_enable_data_rdy(void)
{
    read_register_bit(MPU6050_REGISTER_INT_ENABLE, MPU6050_INT_ENABLE_DATA_RDY_EN, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_int_enable_i2c_mst(bool state)
{
    write_register_bit(MPU6050_REGISTER_INT_ENABLE, MPU6050_INT_ENABLE_I2C_MST_INT_EN, state);
}

bool MPU6050::get_int_enable_i2c_mst(void)
{
    read_register_bit(MPU6050_REGISTER_INT_ENABLE, MPU6050_INT_ENABLE_I2C_MST_INT_EN, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_int_enable_fifo_oflow(bool state)
{
    write_register_bit(MPU6050_REGISTER_INT_ENABLE, MPU6050_INT_ENABLE_FIFO_OFLOW_EN, state);
}

bool MPU6050::get_int_enable_fifo_oflow(void)
{
    read_register_bit(MPU6050_REGISTER_INT_ENABLE, MPU6050_INT_ENABLE_FIFO_OFLOW_EN, &temp_register_bit_state);
    return temp_register_bit_state;
}

//------------------------------------------------------------------------
/* INT_STATUS (0x3A) register (Read only) */

bool MPU6050::get_int_status_data_rdy(void)
{
    read_register_bit(MPU6050_REGISTER_INT_STATUS, MPU6050_INT_STATUS_DATA_RDY_INT, &temp_register_bit_state);
    return temp_register_bit_state;
}

bool MPU6050::get_int_status_i2c_mst(void)
{
    read_register_bit(MPU6050_REGISTER_INT_STATUS, MPU6050_INT_STATUS_I2C_MST_INT_INT, &temp_register_bit_state);
    return temp_register_bit_state;
}

bool MPU6050::get_int_status_fifo_oflow(void)
{
    read_register_bit(MPU6050_REGISTER_INT_STATUS, MPU6050_INT_STATUS_FIFO_OFLOW_INT, &temp_register_bit_state);
    return temp_register_bit_state;
}

//------------------------------------------------------------------------
/* Accelerometer measurements, 0x3B to 0x40 registers (Read only)  */ 

vector MPU6050::get_accel_data(void)
{
    Wire.beginTransmission(MPU6050_DEFAULT_ADRESS);
    if (!Wire.write(MPU6050_REGISTER_ACCEL_XOUT_H) || (Wire.endTransmission() == 2))
        return MPU6050_VECTOR_READ_ERROR;

    Wire.beginTransmission(MPU6050_DEFAULT_ADRESS);
    Wire.requestFrom(MPU6050_DEFAULT_ADRESS, 6);

    while (Wire.available() < 6);
    
    accel_data.x_axis = (int16_t)(Wire.read() << 8) | Wire.read();
    accel_data.y_axis = (int16_t)(Wire.read() << 8) | Wire.read();
    accel_data.z_axis = (int16_t)(Wire.read() << 8) | Wire.read();

    return accel_data;
}

int16_t MPU6050::get_accel_x_axis(void)
{
    return read_register_word(MPU6050_REGISTER_ACCEL_XOUT_H, &temp_register_word) ? temp_register_word : MPU6050_REGISTER_READ_ERROR;
}

int16_t MPU6050::get_accel_y_axis(void)
{
    return read_register_word(MPU6050_REGISTER_ACCEL_YOUT_H, &temp_register_word) ? temp_register_word : MPU6050_REGISTER_READ_ERROR;
}

int16_t MPU6050::get_accel_z_axis(void)
{
    return read_register_word(MPU6050_REGISTER_ACCEL_ZOUT_H, &temp_register_word) ? temp_register_word : MPU6050_REGISTER_READ_ERROR;
}


//------------------------------------------------------------------------
/* Temperature measurement, registers 0x41 and 0x42 (Read only) */

int16_t MPU6050::get_temperature(void)
{
    read_register_word(MPU6050_REGISTER_TEMP_OUT_H, &temp_register_word);
    return (int16_t)temp_register_word;
}

//------------------------------------------------------------------------
/* Gyroscope measurements, 0x43 to 0x48 registers (Read only) */

vector MPU6050::get_gyro_data(void)
{
    Wire.beginTransmission(MPU6050_DEFAULT_ADRESS);
    Wire.write(MPU6050_REGISTER_GYRO_XOUT_H);
    Wire.endTransmission();

    Wire.beginTransmission(MPU6050_DEFAULT_ADRESS);
    Wire.requestFrom(MPU6050_DEFAULT_ADRESS, 6);

    while(Wire.available() < 6);
    
    gyro_data.x_axis = (int16_t)(Wire.read() << 8) | Wire.read();
    gyro_data.y_axis = (int16_t)(Wire.read() << 8) | Wire.read();
    gyro_data.z_axis = (int16_t)(Wire.read() << 8) | Wire.read();

    return gyro_data;
}

//------------------------------------------------------------------------
/* TODO: External Sensor Data, registers 0x49 to 0x60*/

//------------------------------------------------------------------------
/* SIGNAL_PATH_RESET (0x68) register (Write only) */

void MPU6050::set_temp_reset(bool state)
{
    write_register_bit(MPU6050_REGISTER_SIGNAL_PATH_RESET, MPU6050_SIGNAL_PATH_RESET_TEMP_RESET, state);
}

void MPU6050::set_accel_reset(bool state)
{
    write_register_bit(MPU6050_REGISTER_SIGNAL_PATH_RESET, MPU6050_SIGNAL_PATH_RESET_ACCEL_RESET, state);
}

void MPU6050::set_gyro_reset(bool state)
{
    write_register_bit(MPU6050_REGISTER_SIGNAL_PATH_RESET, MPU6050_SIGNAL_PATH_RESET_GYRO_RESET, state);
}

//------------------------------------------------------------------------
/* USER_CTRL (0x6A) register */ 

void MPU6050::set_sig_cond_reset(bool state)
{
    write_register_bit(MPU6050_REGISTER_USER_CTRL, MPU6050_USER_CTRL_SIG_COND_RESET, state);
}

bool MPU6050::get_sig_cond_reset(void)
{
    read_register_bit(MPU6050_REGISTER_USER_CTRL, MPU6050_USER_CTRL_SIG_COND_RESET, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_i2c_mst_reset(bool state)
{
    write_register_bit(MPU6050_REGISTER_USER_CTRL, MPU6050_USER_CTRL_I2C_MST_RESET, state);
}

bool MPU6050::get_i2c_mst_reset(void)
{
    read_register_bit(MPU6050_REGISTER_USER_CTRL, MPU6050_USER_CTRL_I2C_MST_RESET, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_fifo_reset(bool state)
{
    write_register_bit(MPU6050_REGISTER_USER_CTRL, MPU6050_USER_CTRL_FIFO_RESET, state);
}

bool MPU6050::get_fifo_reset(void)
{
    read_register_bit(MPU6050_REGISTER_USER_CTRL, MPU6050_USER_CTRL_FIFO_RESET, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_i2c_if_dis(bool state)
{
    write_register_bit(MPU6050_REGISTER_USER_CTRL, MPU6050_USER_CTRL_I2C_IF_DIS, state);
}

bool MPU6050::get_i2c_if_dis(void)
{
    read_register_bit(MPU6050_REGISTER_USER_CTRL, MPU6050_USER_CTRL_I2C_IF_DIS, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_i2c_mst_en(bool state)
{
    write_register_bit(MPU6050_REGISTER_USER_CTRL, MPU6050_USER_CTRL_I2C_MST_EN, state);
}

bool MPU6050::get_i2c_mst_en(void)
{
    read_register_bit(MPU6050_REGISTER_USER_CTRL, MPU6050_USER_CTRL_I2C_MST_EN, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_fifo_en(bool state)
{
    write_register_bit(MPU6050_REGISTER_USER_CTRL, MPU6050_USER_CTRL_FIFO_EN, state);
}

bool MPU6050::get_fifo_en(void)
{
    read_register_bit(MPU6050_REGISTER_USER_CTRL, MPU6050_USER_CTRL_FIFO_EN, &temp_register_bit_state);
    return temp_register_bit_state;
}

//------------------------------------------------------------------------
/* PWM_MGMT_1 (0x6B) register */

void MPU6050::set_clock_source(mpu6050_pwr_mgmt_1_clksel clk_source)
{
    write_register_byte(MPU6050_REGISTER_PWR_MGMT_1, clk_source, MPU6050_PWR_MGMT_CLKSEL_POSITION, MPU6050_PWR_MGMT_1_CLKSEL_BITMASK);
}

mpu6050_pwr_mgmt_1_clksel MPU6050::get_clock_source(void)
{
    read_register_byte(MPU6050_REGISTER_PWR_MGMT_1, &temp_register, MPU6050_PWR_MGMT_CLKSEL_POSITION, MPU6050_PWR_MGMT_1_CLKSEL_BITMASK);
    return (mpu6050_pwr_mgmt_1_clksel)temp_register;
}

void MPU6050::set_temp_dis(bool state)
{
    write_register_bit(MPU6050_REGISTER_PWR_MGMT_1, MPU6050_PWR_MGMT_1_TEMP_DIS, state);
}

bool MPU6050::get_temp_dis(void)
{
    read_register_bit(MPU6050_REGISTER_PWR_MGMT_1, MPU6050_PWR_MGMT_1_TEMP_DIS, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_cycle(bool state)
{
    write_register_bit(MPU6050_REGISTER_PWR_MGMT_1, MPU6050_PWR_MGMT_1_CYCLE, state);
}

bool MPU6050::get_cycle(void)
{
    read_register_bit(MPU6050_REGISTER_PWR_MGMT_1, MPU6050_PWR_MGMT_1_CYCLE, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_sleep(bool state)
{
    write_register_bit(MPU6050_REGISTER_PWR_MGMT_1, MPU6050_PWR_MGMT_1_SLEEP, state);
}

bool MPU6050::get_sleep(void)
{
    read_register_bit(MPU6050_REGISTER_PWR_MGMT_1, MPU6050_PWR_MGMT_1_SLEEP, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_device_reset(bool state)
{
    write_register_bit(MPU6050_REGISTER_PWR_MGMT_1, MPU6050_PWR_MGMT_1_DEVICE_RESET, state);
}

bool MPU6050::get_device_reset(void)
{
    read_register_bit(MPU6050_REGISTER_PWR_MGMT_1, MPU6050_PWR_MGMT_1_DEVICE_RESET, &temp_register_bit_state);
    return temp_register_bit_state;
}

//------------------------------------------------------------------------
/* PWR_MGMT_2 (0x6C) register */

void MPU6050::set_lp_wake_ctrl(mpu6050_pwr_mgmt_2_lp_wake_ctrl lp_wake_ctrl)
{
    write_register_byte(MPU6050_REGISTER_PWR_MGMT_2, lp_wake_ctrl, MPU6050_PWR_MGMT_2_WAKE_CTRL_POSITION, MPU6050_PWR_MGMT_2_WAKE_CTRL_BITMASK);
}

mpu6050_pwr_mgmt_2_lp_wake_ctrl MPU6050::get_lp_wake_ctrl(void)
{
    read_register_byte(MPU6050_REGISTER_PWR_MGMT_2, &temp_register, MPU6050_PWR_MGMT_2_WAKE_CTRL_POSITION, MPU6050_PWR_MGMT_2_WAKE_CTRL_BITMASK);
    return (mpu6050_pwr_mgmt_2_lp_wake_ctrl)temp_register;
}

void MPU6050::set_stby_xa(bool state)
{
    write_register_bit(MPU6050_REGISTER_PWR_MGMT_2, MPU6050_PWR_MGMT_2_STBY_XA, state);
}

bool MPU6050::get_stby_xa(void)
{
    read_register_bit(MPU6050_REGISTER_PWR_MGMT_2, MPU6050_PWR_MGMT_2_STBY_XA, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_stby_ya(bool state)
{
    write_register_bit(MPU6050_REGISTER_PWR_MGMT_2, MPU6050_PWR_MGMT_2_STBY_YA, state);
}

bool MPU6050::get_stby_ya(void)
{
    read_register_bit(MPU6050_REGISTER_PWR_MGMT_2, MPU6050_PWR_MGMT_2_STBY_YA, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_stby_za(bool state)
{
    write_register_bit(MPU6050_REGISTER_PWR_MGMT_2, MPU6050_PWR_MGMT_2_STBY_ZA, state);
}

bool MPU6050::get_stby_za(void)
{
    read_register_bit(MPU6050_REGISTER_PWR_MGMT_2, MPU6050_PWR_MGMT_2_STBY_ZA, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_stby_xg(bool state)
{
    write_register_bit(MPU6050_REGISTER_PWR_MGMT_2, MPU6050_PWR_MGMT_2_STBY_XG, state);
}

bool MPU6050::get_stby_xg(void)
{
    read_register_bit(MPU6050_REGISTER_PWR_MGMT_2, MPU6050_PWR_MGMT_2_STBY_XG, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_stby_yg(bool state)
{
    write_register_bit(MPU6050_REGISTER_PWR_MGMT_2, MPU6050_PWR_MGMT_2_STBY_YG, state);
}

bool MPU6050::get_stby_yg(void)
{
    read_register_bit(MPU6050_REGISTER_PWR_MGMT_2, MPU6050_PWR_MGMT_2_STBY_YG, &temp_register_bit_state);
    return temp_register_bit_state;
}

void MPU6050::set_stby_zg(bool state)
{
    write_register_bit(MPU6050_REGISTER_PWR_MGMT_2, MPU6050_PWR_MGMT_2_STBY_ZG, state);
}

bool MPU6050::get_stby_zg(void)
{
    read_register_bit(MPU6050_REGISTER_PWR_MGMT_2, MPU6050_PWR_MGMT_2_STBY_ZG, &temp_register_bit_state);
    return temp_register_bit_state;
}

//------------------------------------------------------------------------
/* FIFO_COUNT (0x72 and 0x73) registers (Read only) */ 

uint16_t MPU6050::get_fifo_count(void)
{
    read_register_word(MPU6050_REGISTER_FIFO_COUNTH, &temp_register_word);
    return temp_register_word;
}

//------------------------------------------------------------------------
/* FIFO_R_W (0x74) register */ 

void MPU6050::fifo_write(uint8_t data)
{
    write_register_byte(MPU6050_REGISTER_FIFO_R_W, data);
}

uint8_t MPU6050::fifo_read(void)
{
    read_register_byte(MPU6050_REGISTER_FIFO_R_W, &temp_register);
    return temp_register;
}

//------------------------------------------------------------------------
/* WHO_AM_I (0x75) register (Read only) */

uint8_t MPU6050::get_who_am_i(void)
{
    return read_register_byte(MPU6050_REGISTER_WHO_AM_I, &temp_register) ? temp_register : MPU6050_REGISTER_READ_ERROR;
}

//------------------------------------------------------------------------

bool MPU6050::write_register_byte(uint8_t reg, uint8_t value, uint8_t position, uint8_t bitmask)
{
    uint8_t temp_value = 0;

    if(!read_register_byte(reg, &temp_value))
        return false;
    
    if (bitmask)
    {
        temp_value &= bitmask;
        temp_value |= (value << position);
    }

    Wire.beginTransmission(MPU6050_DEFAULT_ADRESS);
    Wire.write(reg);
    Wire.write(temp_value);
    Wire.endTransmission();

    return true;
}

bool MPU6050::write_register_byte(uint8_t reg, uint8_t value)
{
    Wire.beginTransmission(MPU6050_DEFAULT_ADRESS);
    if (!Wire.write(reg))
        return false;

    Wire.write(value);
    Wire.endTransmission();

    return true;
}

bool MPU6050::read_register_byte(uint8_t reg, uint8_t *value, uint8_t position, uint8_t bitmask)
{
    if((reg == 0) || (value == NULL))
        return false;

    uint8_t temp_value = 0;

    Wire.beginTransmission(MPU6050_DEFAULT_ADRESS);
    if (!Wire.write(reg))
        return false;

    if (Wire.endTransmission() == 2) // if received NACK on transmit of address
        return false;

    Wire.beginTransmission(MPU6050_DEFAULT_ADRESS);
    Wire.requestFrom(MPU6050_DEFAULT_ADRESS, 1);

    while(!Wire.available());

    temp_value = Wire.read();
    Wire.endTransmission();

    if (temp_value == -1)
        return false;

    if (bitmask)
    {
        temp_value &= (~bitmask);
        temp_value >>= position;
    }

    *value = temp_value;
    return true;
}


bool MPU6050::read_register_byte(uint8_t reg, uint8_t *value)
{
    if((reg == 0) || (value == NULL))
        return false;

    Wire.beginTransmission(MPU6050_DEFAULT_ADRESS);
    if (Wire.write(reg) == 0)
        return false;

    if (Wire.endTransmission() == 2) // if received NACK on transmit of address
        return false;

    Wire.beginTransmission(MPU6050_DEFAULT_ADRESS);
    Wire.requestFrom(MPU6050_DEFAULT_ADRESS, 1);

    while(!Wire.available());

    *value = Wire.read();
    Wire.endTransmission();
    return true;
}

bool MPU6050::write_register_bit(uint8_t reg, uint8_t position, bool state)
{
    uint8_t temp_value = 0;
    if(!read_register_byte(reg, &temp_value))
        return false;

    state ? temp_value |= (1 << position) : temp_value &= ~(1 << position);

    Wire.beginTransmission(MPU6050_DEFAULT_ADRESS);
    Wire.write(reg);
    Wire.write(temp_value);
    Wire.endTransmission();

    return true;
}

bool MPU6050::read_register_bit(uint8_t reg, uint8_t position, bool *state)
{
    uint8_t temp_value = 0;

    if(!read_register_byte(reg, &temp_value))
        return false;
    
    *state = (temp_value >> position) & 1;
    
    return true;
}

bool MPU6050::read_register_word(uint8_t reg, uint16_t *value)
{
    if ((reg == 0) || (value == NULL))
        return false;
    
    Wire.beginTransmission(MPU6050_DEFAULT_ADRESS);
    if (!Wire.write(reg))
        return false;

    if (Wire.endTransmission() == 2) // if received NACK on transmit of address
        return false;

    Wire.beginTransmission(MPU6050_DEFAULT_ADRESS);
    Wire.requestFrom(MPU6050_DEFAULT_ADRESS, 2);
    while (!Wire.available());

    *value = Wire.read() << 8 | Wire.read();

    Wire.endTransmission();
    return true;
}

bool MPU6050::write_register_word(uint8_t reg, uint16_t value)
{
    if (!reg)
        return false;

    Wire.beginTransmission(MPU6050_DEFAULT_ADRESS);

    if (!Wire.write(reg))
        return false;

    Wire.write((uint8_t)(value >> 8));
    Wire.write((uint8_t)(value));

    Wire.endTransmission();
    return true;
}