/**
 * @file mpu6050.h
 * @author Kacper Wiśniewski (kwisniewski541@gmail.com)
 * @version 1.0
 * @date 2022-10-12
 */

//--------------------------------------------------------------------------------

#ifndef MPU6050_H_
#define MPU6050_H_

//--------------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

//--------------------------------------------------------------------------------

/** @brief Adres pin high (VCC). */
#define MPU6050_ADDRESS_HIGH             (0x68) 

/** @brief Adress pin low (GND). */
#define MPU6050_ADDRESS_LOW              (0x69)

//--------------------------------------------------------------------------------
/** MPU6050 registers and registers contents
 *  Register Names ending in _H and _L contain the high and low bytes, respectively, of an internal register value.
 */

#define MPU6050_RESET_REGISTER_VALUE          (0x00)

#define MPU6050_REGISTER_ACCEL_XOFFS_H        (0x06)
#define MPU6050_REGISTER_ACCEL_XOFFS_L        (0x07)
#define MPU6050_REGISTER_ACCEL_YOFFS_H        (0x08)
#define MPU6050_REGISTER_ACCEL_YOFFS_L        (0x09)
#define MPU6050_REGISTER_ACCEL_ZOFFS_H        (0x0A)
#define MPU6050_REGISTER_ACCEL_ZOFFS_L        (0x0B)

/* Registers used for gyro and accelometer self-tests. */
#define MPU6050_REGISTER_SELF_TEST_X 	      (0x0D)     /* [7:5] XA_TEST[4-2], [4:0] XG_TEST[4-0] */
#define MPU6050_REGISTER_SELF_TEST_Y 	      (0x0E)     /* [7:5] YA_TEST[4-2], [4:0] YG_TEST[4-0] */
#define MPU6050_REGISTER_SELF_TEST_Z 	      (0x0F)     /* [7:5] ZA_TEST[4-2], [4:0] ZG_TEST[4-0] */
#define MPU6050_REGISTER_SELF_TEST_A 	      (0x10)     /* [5:4] XA_TEST[1-0], [3:2] YA_TEST[1-0], [1:0] ZA_TEST[1-0] */

#define MPU6050_REGISTER_GYRO_XOFFS_H         (0x13)     /* [15:0] XG_OFFS_USR */
#define MPU6050_REGISTER_GYRO_XOFFS_L         (0x14)
#define MPU6050_REGISTER_GYRO_YOFFS_H         (0x15)     /* [15:0] YG_OFFS_USR */
#define MPU6050_REGISTER_GYRO_YOFFS_L         (0x16)
#define MPU6050_REGISTER_GYRO_ZOFFS_H         (0x17)     /* [15:0] YG_OFFS_USR */
#define MPU6050_REGISTER_GYRO_ZOFFS_L         (0x18)

/**
 * Sample rate divider register.
 * Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
 */
#define MPU6050_REGISTER_SMPLRT_DIV           (0x19)     /* [7:0] SMLPRT_DIV */

/**  FSYNC and DLPF configuration. */
#define MPU6050_REGISTER_CONFIG               (0x1A)     /* [5:3] EXT_SYNS_SET, [2:0] DLPF_CFG*/
#define MPU6050_CONFIG_EXT_SYNS_POSITION      (3)
#define MPU6050_CONFIG_EXT_SYNS_BITMASK       (0b11000111)
#define MPU6050_CONFIG_DLPF_POSITION          (0)
#define MPU6050_CONFIG_DLPF_BITMASK           (0b11111000)

/** Trigger gyro self-test and configure the gyroscopes' full scale range. */
#define MPU6050_REGISTER_GYRO_CONFIG          (0x1B)     /* [7] XG_ST, [6] YG_ST, [5] ZG_ST, [4:3] FS_SEL */
#define MPU6050_GYRO_CONFIG_XG_ST             (7)
#define MPU6050_GYRO_CONFIG_YG_ST             (6)
#define MPU6050_GYRO_CONFIG_ZG_ST             (5)  
#define MPU6050_GYRO_CONFIG_FS_SEL_POSITION   (3)
#define MPU6050_GYRO_CONFIG_FS_SEL_BITMASK    (0b11100111)

/**  Trigger accelerometer self test and configure the accelerometer full scale range. */
#define MPU6050_REGISTER_ACCEL_CONFIG         (0x1C)     /* [7] XA_ST, [6] YA_ST, [5] ZA_ST, [4:3] AFS_SEL */
#define MPU6050_ACCEL_CONFIG_XA_ST            (7)
#define MPU6050_ACCEL_CONFIG_YA_ST            (6)
#define MPU6050_ACCEL_CONFIG_ZA_ST            (5)
#define MPU6050_ACCEL_CONFIG_AFS_SEL_POSITION (3)
#define MPU6050_ACCEL_CONFIG_AFS_SEL_BITMASK  (0b11100111)

#define MPU6050_REGISTER_FF_THRESHOLD         (0x1D)
#define MPU6050_REGISTER_FF_DURATION          (0x1E)
#define MPU6050_REGISTER_MOT_THRESHOLD        (0x1F)
#define MPU6050_REGISTER_MOT_DURATION         (0x20)
#define MPU6050_REGISTER_ZMOT_THRESHOLD       (0x21)
#define MPU6050_REGISTER_ZMOT_DURATION        (0x22)

/** Determines which sensor measurements are loaded into the FIFO buffer.  */
#define MPU6050_REGISTER_FIFO_EN              (0x23)     /* [7] TEMP_FIFO_EN, [6] XG_FIFO_EN, [5] YG_FIFO_EN, [4] ZG_FIFO_EN,       */
#define MPU6050_FIFO_EN_TEMP_FIFO_EN          (7)        /* [3] ACCEL_FIFO_EN, [2] SLV2_FIFO_EN, [1] SLV1_FIFO_EN, [0] SLV0_FIFO_EN */
#define MPU6050_FIFO_EN_XG_FIFO_EN            (6)
#define MPU6050_FIFO_EN_YG_FIFO_EN            (5)
#define MPU6050_FIFO_EN_ZG_FIFO_EN            (4)
#define MPU6050_FIFO_EN_ACCEL_FIFO_EN         (3)
#define MPU6050_FIFO_EN_SLV2_FIFO_EN          (2)
#define MPU6050_FIFO_EN_SLV1_FIFO_EN          (1)
#define MPU6050_FIFO_EN_SLV0_FIFO_EN          (0)

/** Configures the auxilinary I2C bus for single-master or multi-master control. */
#define MPU6050_REGISTER_I2C_MST_CTRL         (0x24)    /* [7] MULT_MST_EN, [6] WAIT_FOR_ES, [5] SLV_3_FIFO_EN, [4] I2C_MST_P_NSR, */ 
#define MPU6050_I2C_MST_CTRL_MULT_MST_EN      (7)       /* [3:0] I2C_MST_CLK                                                       */  
#define MPU6050_I2C_MST_CTRL_WAIT_FOR_ES      (6)
#define MPU6050_I2C_MST_CTRL_SLV_3_FIFO_EN    (5)
#define MPU6050_I2C_MST_CTRL_I2C_MST_P_NSR    (4)

#define MPU6050_REGISTER_I2C_SLV0_ADDR        (0x25)    
#define MPU6050_REGISTER_I2C_SLV0_REG         (0x26)
#define MPU6050_REGISTER_I2C_SLV0_CTRL        (0x27)
#define MPU6050_REGISTER_I2C_SLV1_ADDR        (0x28)
#define MPU6050_REGISTER_I2C_SLV1_REG         (0x29)
#define MPU6050_REGISTER_I2C_SLV1_CTRL        (0x2A)
#define MPU6050_REGISTER_I2C_SLV2_ADDR        (0x2B)
#define MPU6050_REGISTER_I2C_SLV2_REG         (0x2C)
#define MPU6050_REGISTER_I2C_SLV2_CTRL        (0x2D)
#define MPU6050_REGISTER_I2C_SLV3_ADDR        (0x2E)
#define MPU6050_REGISTER_I2C_SLV3_REG         (0x2F)
#define MPU6050_REGISTER_I2C_SLV3_CTRL        (0x30)
#define MPU6050_REGISTER_I2C_SLV4_ADDR        (0x31)
#define MPU6050_REGISTER_I2C_SLV4_REG         (0x32)
#define MPU6050_REGISTER_I2C_SLV4_DO          (0x33)
#define MPU6050_REGISTER_I2C_SLV4_CTRL        (0x34)
#define MPU6050_REGISTER_I2C_SLV4_DI          (0x35)
#define MPU6050_REGISTER_I2C_MST_STATUS       (0x36)

/** Configures the behaviour of the interrupt signals at the INT pins. */
#define MPU6050_REGISTER_INT_PIN_CFG          (0x37)     /* [7] INT_LEVEL, [6] INT_OPEN, [5] LATCH_INT_EN, [4] INT_RD_CLEAR, */
#define MPU6050_INT_PIN_CFG_INT_LEVEL         (7)        /* [3] FSYNC_INT_LEVEL, [2] FSYNC_INT_EN, [1] I2C_BYPASS_EN         */
#define MPU6050_INT_PIN_CFG_INT_OPEN          (6)
#define MPU6050_INT_PIN_CFG_LATCH_INT_EN      (5)
#define MPU6050_INT_PIN_CFG_INT_RD_CLEAR      (4)
#define MPU6050_INT_PIN_CFG_FSYNC_INT_LEVEL   (3)
#define MPU6050_INT_PIN_CFG_FSYNC_INT_EN      (2)
#define MPU6050_INT_PIN_CFG_I2C_BYPASS_EN     (1)

/** Enables interrupt generation by interrupt sources. */
#define MPU6050_REGISTER_INT_ENABLE           (0x38)     /* [4] FIFO_OFLOW_EN, [3] I2C_MST_INT_EN, [0] DATA_RDY_EN */
#define MPU6050_INT_ENABLE_FIFO_OFLOW_EN      (4)
#define MPU6050_INT_ENABLE_I2C_MST_INT_EN     (3)
#define MPU6050_INT_ENABLE_DATA_RDY_EN        (0)

/** Shows the interrupt status of each interrupt generation source. */
#define MPU6050_REGISTER_INT_STATUS           (0x3A)     /* [4] FIFO_OFLOW_INT, [3] I2C_MST_INT_INT, [0] DATA_RDY_INT */
#define MPU6050_INT_STATUS_FIFO_OFLOW_INT     (4)
#define MPU6050_INT_STATUS_I2C_MST_INT_INT    (3)
#define MPU6050_INT_STATUS_DATA_RDY_INT       (0)

/** Registers 0x3B to 0x40 store the most recent accelerometer measurements. */
#define MPU6050_REGISTER_ACCEL_XOUT_H         (0x3B)     /* [15:0] ACCEL_XOUT */
#define MPU6050_REGISTER_ACCEL_XOUT_L         (0x3C)
#define MPU6050_REGISTER_ACCEL_YOUT_H         (0x3D)     /* [15:0] ACCEL_YOUT */
#define MPU6050_REGISTER_ACCEL_YOUT_L         (0x3E)
#define MPU6050_REGISTER_ACCEL_ZOUT_H         (0x3F)     /* [15:0] ACCEL_ZOUT */
#define MPU6050_REGISTER_ACCEL_ZOUT_L         (0x40)

/** Registers 0x41 and 0x42 store the most recent temperature sensor measurement. */
#define MPU6050_REGISTER_TEMP_OUT_H           (0x41)     /* [15:0] TEMP_OUT */
#define MPU6050_REGISTER_TEMP_OUT_L           (0x42)

/** Registers 0x43 to 0x48 store the most recent gyroscope measurements.  */
#define MPU6050_REGISTER_GYRO_XOUT_H          (0x43)     /* [15:0] GYRO_XOUT */
#define MPU6050_REGISTER_GYRO_XOUT_L          (0x44)
#define MPU6050_REGISTER_GYRO_YOUT_H          (0x45)     /* [15:0] GYRO_YOUT */
#define MPU6050_REGISTER_GYRO_YOUT_L          (0x46)
#define MPU6050_REGISTER_GYRO_ZOUT_H          (0x47)     /* [15:0] GYRO_ZOUT */
#define MPU6050_REGISTER_GYRO_ZOUT_L          (0x48)

/** Registers 0x49 to 0x60 store data read from external sensors. */
#define MPU6050_REGISTER_EXT_SENS_DATA_00     (0x49)
#define MPU6050_REGISTER_EXT_SENS_DATA_01     (0x4A)
#define MPU6050_REGISTER_EXT_SENS_DATA_02     (0x4B)
#define MPU6050_REGISTER_EXT_SENS_DATA_03     (0x4C)
#define MPU6050_REGISTER_EXT_SENS_DATA_04     (0x4D)
#define MPU6050_REGISTER_EXT_SENS_DATA_05     (0x4E)
#define MPU6050_REGISTER_EXT_SENS_DATA_06     (0x4F)
#define MPU6050_REGISTER_EXT_SENS_DATA_07     (0x50)
#define MPU6050_REGISTER_EXT_SENS_DATA_08     (0x51)
#define MPU6050_REGISTER_EXT_SENS_DATA_09     (0x52)
#define MPU6050_REGISTER_EXT_SENS_DATA_10     (0x53)
#define MPU6050_REGISTER_EXT_SENS_DATA_11     (0x54)
#define MPU6050_REGISTER_EXT_SENS_DATA_12     (0x55)
#define MPU6050_REGISTER_EXT_SENS_DATA_13     (0x56)
#define MPU6050_REGISTER_EXT_SENS_DATA_14     (0x57)
#define MPU6050_REGISTER_EXT_SENS_DATA_15     (0x58)
#define MPU6050_REGISTER_EXT_SENS_DATA_16     (0x59)
#define MPU6050_REGISTER_EXT_SENS_DATA_17     (0x5A)
#define MPU6050_REGISTER_EXT_SENS_DATA_18     (0x5B)
#define MPU6050_REGISTER_EXT_SENS_DATA_19     (0x5C)
#define MPU6050_REGISTER_EXT_SENS_DATA_20     (0x5D)
#define MPU6050_REGISTER_EXT_SENS_DATA_21     (0x5E)
#define MPU6050_REGISTER_EXT_SENS_DATA_22     (0x5F)
#define MPU6050_REGISTER_EXT_SENS_DATA_23     (0x60)

#define MPU6050_REGISTER_MOT_DETECT_STATUS    (0x61)
#define MPU6050_REGISTER_I2C_SLV0_DO          (0x63)
#define MPU6050_REGISTER_I2C_SLV1_DO          (0x64)
#define MPU6050_REGISTER_I2C_SLV2_DO          (0x65)
#define MPU6050_REGISTER_I2C_SLV3_DO          (0x66)
#define MPU6050_REGISTER_I2C_MST_DELAY_CTRL   (0x67)

/** Reset the analog and digital signal paths of the gyro, accelerometer and temperature sensors. */
#define MPU6050_REGISTER_SIGNAL_PATH_RESET    (0x68)     /* [2] GYRO_RESET, [1] ACCEL_RESET, [0] TEMP_RESET*/
#define MPU6050_SIGNAL_PATH_RESET_GYRO_RESET  (2)
#define MPU6050_SIGNAL_PATH_RESET_ACCEL_RESET (1)
#define MPU6050_SIGNAL_PATH_RESET_TEMP_RESET  (0)

#define MPU6050_REGISTER_MOT_DETECT_CTRL      (0x69)

/** Enable/disable the FIFO buffer, I2C master mode and primary I2C interface. */
#define MPU6050_REGISTER_USER_CTRL            (0x6A)    /* [6] FIFO_EN, [5] I2C_MST_EN, [4] I2C_IF_DIS, [2] FIFO_RESET, */
#define MPU6050_USER_CTRL_FIFO_EN             (6)       /* [1] I2C_MST_RESET, [0] SIG_COND_RESET                        */
#define MPU6050_USER_CTRL_I2C_MST_EN          (5)
#define MPU6050_USER_CTRL_I2C_IF_DIS          (4)
#define MPU6050_USER_CTRL_FIFO_RESET          (2)
#define MPU6050_USER_CTRL_I2C_MST_RESET       (1)
#define MPU6050_USER_CTRL_SIG_COND_RESET      (0)

/** Configure the power mode and clock source. */
#define MPU6050_REGISTER_PWR_MGMT_1           (0x6B)        /* [7] DEVICE_RESET, [6] SLEEP, [5] CYCLE, */
#define MPU6050_PWR_MGMT_1_CLKSEL_BITMASK     (0b11111000)  /* [3] TEMP_DIS, [2:0] CLKSEL              */
#define MPU6050_PWR_MGMT_CLKSEL_POSITION      (0)
#define MPU6050_PWR_MGMT_1_DEVICE_RESET       (7)  
#define MPU6050_PWR_MGMT_1_SLEEP              (6)
#define MPU6050_PWR_MGMT_1_CYCLE              (5)
#define MPU6050_PWR_MGMT_1_TEMP_DIS           (3)

/** Configure the frequency of wake-ups in Accelerometer Only Low Power Mode. */
#define MPU6050_REGISTER_PWR_MGMT_2           (0x6C)       /* [7:6] LP_WAKE_CTRL, [5] STBY_XA, [4] STBY_YA,      */
#define MPU6050_PWR_MGMT_2_WAKE_CTRL_BITMASK  (0b00111111) /* [3] STBY_ZA, [2] STBY_XG, [1] STBY_YG, [0] STBY_ZG */
#define MPU6050_PWR_MGMT_2_WAKE_CTRL_POSITION (6)
#define MPU6050_PWR_MGMT_2_STBY_XA            (5)       
#define MPU6050_PWR_MGMT_2_STBY_YA            (4)
#define MPU6050_PWR_MGMT_2_STBY_ZA            (3)
#define MPU6050_PWR_MGMT_2_STBY_XG            (2)
#define MPU6050_PWR_MGMT_2_STBY_YG            (1)
#define MPU6050_PWR_MGMT_2_STBY_ZG            (0)

/** Register 0x72 and 0x73 keep track of the number of samples currently in the FIFO buffer. */
#define MPU6050_REGISTER_FIFO_COUNTH          (0x72)    /* [15:0] FIFO_COUNT */
#define MPU6050_REGISTER_FIFO_COUNTL          (0x73)

/** Register used to read and write data from the FIFO buffer. */
#define MPU6050_REGISTER_FIFO_R_W             (0x74)    /* [7:0] FIFO_DATA */

/**
 * This register is used to verify the identity of the device
 * The contents are the upper 6 bits of the MPU-6050's 7-bit I2C adress
 */
#define MPU6050_REGISTER_WHO_AM_I             (0x75)    /* [6:1] WHO_AM_I */

//--------------------------------------------------------------------------------

/**
 *  @brief External frame synchronization (FSYNC) pin sampling, 3-bit usigned value. 
 *         FSYNC bit location
 * */
enum mpu6050_config_ext_sync_set
{
    MPU6050_INPUT_DISABLED,     /**< Disabled input*/
    MPU6050_TEMP_OUT_LOW,       /**< FSYNC bit -> TEMP_OUT_LOW[0]*/
    MPU6050_GYRO_XOUT_LOW,      /**< FSYNC bit -> GYRO_XOUT_LOW[0]*/
    MPU6050_GYRO_YOUT_LOW,      /**< FSYNC bit -> GYRO_YOUT_LOW[0]*/
    MPU6050_GYRO_ZOUT_LOW,      /**< FSYNC bit -> GYRO_ZOUT_LOW[0]*/
    MPU6050_ACCEL_XOUT_LOW,     /**< FSYNC bit -> ACCEL_XOUT_LOW[0]*/
    MPU6050_ACCEL_YOUT_LOW,     /**< FSYNC bit -> ACCEL_YOUT_LOW[0]*/
    MPU6050_ACCEL_ZOUT_LOW      /**< FSYNC bit -> ACCEL_ZOUT_LOW[0]*/
};

/** @brief Digital Low Pass Filter (DLPF) setting, 3-bit usigned value. */
enum mpu6050_config_dlpf_cfg
{
    MPU6050_DLPF_CFG_BW_256,
    MPU6050_DLPF_CFG_BW_188,
    MPU6050_DLPF_CFG_BW_98,
    MPU6050_DLPF_CFG_BW_42,
    MPU6050_DLPF_CFG_BW_20,
    MPU6050_DLPF_CFG_BW_10,
    MPU6050_DLPF_CFG_BW_5
};

/** @brief FS_SEL selects the full scale range of the gyroscope outputs. */
enum mpu6050_gyro_config_fs_sel
{
    MPU6050_FS_SEL_250DPS,
    MPU6050_FS_SEL_500DPS,
    MPU6050_FS_SEL_1000DPS,
    MPU6050_FS_SEL_2000DPS
};

/** @brief AFS_SEL selects the full scale range of the accelerometer outputs0. */
enum mpu6050_accel_config_afs_sel
{
    MPU6050_AFS_SEL_2G,
    MPU6050_AFS_SEL_4G,
    MPU6050_AFS_SEL_8G,
    MPU6050_AFS_SEL_16G
};

/** @brief I2C_MST_CLK configures a I2C master clock speed divider. */
enum mpu6050_i2c_mst_ctrl_mst_clk
{
    MPU6050_I2C_MST_CLK_23,
    MPU6050_I2C_MST_CLK_24,
    MPU6050_I2C_MST_CLK_25,
    MPU6050_I2C_MST_CLK_26,
    MPU6050_I2C_MST_CLK_27,
    MPU6050_I2C_MST_CLK_28,
    MPU6050_I2C_MST_CLK_29,
    MPU6050_I2C_MST_CLK_30,
    MPU6050_I2C_MST_CLK_31,
    MPU6050_I2C_MST_CLK_16,
    MPU6050_I2C_MST_CLK_17,
    MPU6050_I2C_MST_CLK_18,
    MPU6050_I2C_MST_CLK_19,
    MPU6050_I2C_MST_CLK_20,
    MPU6050_I2C_MST_CLK_21,
    MPU6050_I2C_MST_CLK_22
};

/** @brief Specifies the clock source of the device. */
enum mpu6050_pwr_mgmt_1_clksel
{
    MPU6050_CLOCK_INTERNAL_8MHZ,        /**< Internal 8MHz oscillator. */
    MPU6050_CLOCK_PLL_XGYRO,            /**< PLL with X axis gyroscope reference. */
    MPU6050_CLOCK_PLL_YGYRO,            /**< PLL with Y axis gyroscope reference. */
    MPU6050_CLOCK_PLL_ZGYRO,            /**< PLL with Z axis gyrosope reference. */
    MPU6050_CLOCK_PLL_EXTERNAL_32KHZ,   /**< PLL with external 32.768kHz reference. */
    MPU6050_CLOCK_PLL_EXTERNAL_19MHZ,   /**< PLL with external 19.2MHz reference. */
    RESERVED,                           /**< Reserved. */
    MPU6050_CLOCK_KEEP_RESET            /**< Stops the clock and keeps the timing generator in reset. */
};

/** @brief The frequency of wake-ups during acceleromenter only low power mode. */
enum mpu6050_pwr_mgmt_2_lp_wake_ctrl
{
    MPU6050_WAKE_CTRL_1_25HZ,
    MPU6050_WAKE_CTRL_5HZ,
    MPU6050_WAKE_CTRL_20HZ,
    MPU6050_WAKE_CTRL_40HZ
};

/** @brief The type used to store data from the sensors. */
struct vector
{
    int16_t x_axis;
    int16_t y_axis;
    int16_t z_axis;
};

//--------------------------------------------------------------------------------

/* Const. (MPU6050 REGISTER MAP DOCUMENT). */
#define MPU6050_AFS_SEL_DIV_2G   16384.0
#define MPU6050_AFS_SEL_DIV_4G   8192.0
#define MPU6050_AFS_SEL_DIV_8G   4096.0
#define MPU6050_AFS_SEL_DIV_16G  2048.0
#define MPU6050_FS_SEL_DIV_250   131.0
#define MPU6050_FS_SEL_DIV_500   65.5
#define MPU6050_FS_SEL_DIV_1000  32.8
#define MPU6050_FS_SEL_DIV_2000  16.4

/* Default MPU6050 settings. */

#define MPU6050_DEFAULT_ADRESS          MPU6050_ADDRESS_HIGH
#define MPU6050_DEFAULT_CLOCK           MPU6050_CLOCK_PLL_XGYRO
#define MPU6050_DEFAULT_GYRO_SCALE      MPU6050_FS_SEL_250DPS
#define MPU6050_DEFAULT_ACCEL_RANGE     MPU6050_AFS_SEL_2G

/* Error codes. */
#define MPU6050_REGISTER_READ_ERROR           (-1)
#define MPU6050_VECTOR_READ_ERROR             (vector){0, 0, 0}
//--------------------------------------------------------------------------------

class MPU6050
{
public:

    //------------------------------------------------------------------------
    /* SMPRT_DIV (0X19) register. */

    /**
     * @brief Secifies the divider from the gyroscope output rate
     *        used to generate the Sample Rate for the MPU-6050.
     * @note  The sensor register output, FIFO output, and DMP sampling
     *        are all based on the Sample Rate.
     *        Sample rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
     * @param [in] smplrt_div - 8-bit unsigned value.
     */
    void set_sample_rate_divider(uint8_t smplrt_div);

    /**
     * @brief Get the sample rate divider
     * @return uint8_t - Sample rate divider
     */
    uint8_t get_sample_rate_divider(void);

    //------------------------------------------------------------------------
    /* CONFIG (0x1A register). */

    /**
     * @brief Configures the external Frame Synchronization pin sampling
     * @param [in] ext_sync - @see mpu6050_config_ext_sync_set
     */
    void set_ext_sync(mpu6050_config_ext_sync_set ext_sync);

    /**
     * @brief  Get the external Frame Synchronization pin sampling
     * @return @see mpu6050_config_ext_sync_set
     */
    mpu6050_config_ext_sync_set get_ext_sync(void);

    /**
     * @brief Configures the Digital Low Pass Filter setting for both
     *        gyroscopes and accelerometers
     * @param [in] dlpf - @see  mpu6050_config_dlpf_cfg
     */
    void set_dlpf_mode(mpu6050_config_dlpf_cfg dlpf);

    /**
     * @brief Get the Digital Low Pass Filter setting
     * @return @see mpu6050_config_dlpf_cfg
     */
    mpu6050_config_dlpf_cfg get_dlpf_mode(void);

    //------------------------------------------------------------------------
    /**
     * GYRO_CONFIG (0x1B) register
     * This register is used to trigger gyroscope self-test and configure the 
     * gyroscopes' full scale range.
     */

    /**
     * @brief Select the full scale range of the gyroscope outputs
     * @param [in] gyro_scale - @see mpu6050_gyro_config_fs_sel
     */
    void set_gyro_scale(mpu6050_gyro_config_fs_sel gyro_scale);

    /**
     * @brief Get the gyroscope full scale range 
     * @return @see mpu6050_gyro_config_fs_sel 
     */
    mpu6050_gyro_config_fs_sel get_gyro_scale(void);

    /**
     * @brief Setting this bit causes the X axis gyroscope to perform self test.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_gyro_x_self_test(bool state);

    /**
     * @brief Get the gyro X axis self test bit.
     * @return true if set, otherwise false.
     */
    bool get_gyro_x_self_test(void);

    /**
     * @brief Setting this bit causes the Y axis gyroscope to perform self test.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_gyro_y_self_test(bool state);

    /**
     * @brief Get the gyro Y axis self test bit.
     * @return true if set, otherwise false.
     */
    bool get_gyro_y_self_test(void);

    /**
     * @brief Setting this bit causes the Z axis gyroscope to perform self test.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_gyro_z_self_test(bool state);

    /**
     * @brief Get the gyro Z axis self test bit.
     * @return true if set, otherwise false.
     */
    bool get_gyro_z_self_test(void);

    //------------------------------------------------------------------------

    /**
     * ACCEL_CONFIG (0x1C register)
     * This register is used to trigger accelerometer self test and configure
     * the accelerometer full scale range and Digital High Pass Filter.
     */

    /**
     * @brief Select the full scale range of the accelerometer outputs
     * @param [in] accel_range - @see mpu6050_accel_config_afs_sel
     */
    void set_accel_range(mpu6050_accel_config_afs_sel accel_range);

    /**
     * @brief Get the full scale range of the accelerometer outputs
     * @return @see mpu6050_accel_config_afs_sel 
     */
    mpu6050_accel_config_afs_sel get_accel_range(void);                         /* TODO : add DHPF configuration*/

    /**
     * @brief Setting this bit causes the X axis accelerometer to perform self test.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_accel_x_self_test(bool state);

    /**
     * @brief Get the accel X axis self test bit.
     * @return true if set, otherwise false.
     */
    bool get_accel_x_self_test(void);

    /**
     * @brief Setting this bit causes the Y axis accelerometer to perform self test.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_accel_y_self_test(bool state);

    /**
     * @brief Get the accel Y axis self test bit.
     * @return true if set, otherwise false.
     */
    bool get_accel_y_self_test(void);

    /**
     * @brief Setting this bit causes the Z axis accelerometer to perform self test.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_accel_z_self_test(bool state);

    /**
     * @brief Get the accel X axis self test bit.
     * @return true if set, otherwise false.
     */
    bool get_accel_z_self_test(void);

    //------------------------------------------------------------------------

    /**
     * FIFO_EN (0x23) register 
     * This register determines which sensor measurements are loaded into the FIFO buffer.
     */

    /**
     * @brief Enables/disables EXT_SENS_DATA registers (Registers 73 to 96)
     *        associated with Slave 0 to be written into the FIFO buffer.
     * @param [in] state - Logical state of the bit being set.
     */     
    void set_fifo_en_slv0(bool state);

    /**
     * @brief Get the state of EXT_SENS_DATA registers associated with Slave 0 to be written into the FIFO buffer.
     * @return true if enabled, false if disabled
     */
    bool get_fifo_en_slv0(void);

    /**
     * @brief Enables/disables EXT_SENS_DATA registers (Registers 73 to 96)
     *        associated with Slave 1 to be written into the FIFO buffer.
     * @param [in] state - Logical state of the bit being set.
     */     
    void set_fifo_en_slv1(bool state);

    /**
     * @brief Get the state of EXT_SENS_DATA registers associated with Slave 1 to be written into the FIFO buffer.
     * @return true if enabled, false if disabled
     */

    bool get_fifo_en_slv1(void);

    /**
     * @brief Enables/disables EXT_SENS_DATA registers (Registers 73 to 96)
     *        associated with Slave 1 to be written into the FIFO buffer.
     * @param [in] state - Logical state of the bit being set.
     */     
    void set_fifo_en_slv2(bool state);

    /**
     * @brief Get the state of EXT_SENS_DATA registers associated with Slave 2 to be written into the FIFO buffer.
     * @return true if enabled, false if disabled
     */

    bool get_fifo_en_slv2(void);

    /**
     * @brief Enables/disables ACCEL_XOUT_H, ACCEL_XOUT_L, ACCEL_YOUT_H, ACCEL_YOUT_L, ACCEL_ZOUT_H,
     *        and ACCEL_ZOUT_L (Registers 59 to 64) to be written into the FIFO buffer.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_fifo_en_accel(bool state);

    /**
     * @brief Get the status of enabled/disabled writing data from accelerometer to the FIFO buffer.
     * @return true if enabled, false if disabled
     */
    bool get_fifo_en_accel(void);

    /**
     * @brief Enables/disables GYRO_XOUT_H and GYRO_XOUT_L (Registers 67 and 68)
     *        to be written into the FIFO buffer.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_fifo_en_xg(bool state);

    /**
     * @brief Get the status of enabled/disabled writing data from gyro X axis to the FIFO buffer.
     * @return true if enabled, false if disabled
     */
    bool get_fifo_en_xg(void);

    /**
     * @brief Enables/disables GYRO_YOUT_H and GYRO_YOUT_L (Registers 69 and 70)
     *        to be written into the FIFO buffer.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_fifo_en_yg(bool state);

    /**
     * @brief Get the status of enabled/disabled writing data from gyro Y axis to the FIFO buffer.
     * @return true if enabled, false if disabled
     */
    bool get_fifo_en_yg(void);

    /**
     * @brief Enables/disables GYRO_ZOUT_H and GYRO_ZOUT_L (Registers 71 and 72)
     *        to be written into the FIFO buffer.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_fifo_en_zg(bool state);

    /**
     * @brief Get the status of enabled/disabled writing data from gyro X axis to the FIFO buffer.
     * @return true if enabled, false if disabled
     */
    bool get_fifo_en_zg(void);

    /**
     * @brief Enables/disables TEMP_OUT_H and TEMP_OUT_L (Registers 65 and 66)
     *        to be written into the FIFO buffer.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_fifo_en_temp(bool state);

    /**
     * @brief Get the status of enabled/disabled writing data from temp sensor to the FIFO buffer.
     * @return true if enabled, false if disabled
     */
    bool get_fifo_en_temp(void);

    //------------------------------------------------------------------------
    /* TODO: Registers 0x24 to 0x36. */


    /* 0x24 register, I2C master control (read/write) */
    /**
     * Configures the auxilinary I2C bus for single-master or mulit-master
     * control. The register is used to delay Data Ready INT.
     * 
     */
    void set_i2c_master_clk(enum mpu6050_i2c_mst_ctrl_mst_clk);
    mpu6050_i2c_mst_ctrl_mst_clk get_i2c_master_clk();

    //------------------------------------------------------------------------

    /**
     * INT_PIN_CFG (0x37) register
     * This register configures the behavior of the interrupt signals at the INT pins.
     */

    /**
     * @brief When this bit is equal to 0, the logic level of the INT pin is active
     *        high, low otherwise
     * @param [in] state - Logical state of the bit being set.
     */
    void set_int_level(bool state);

    /**
     * @brief Get the INT level
     * @return true if logic level of INT is active low, otherwise false
     */
    bool get_int_level(void);

    /**
     * @brief When this bit is equal to 0, the INT pin is configured as pushh-pull,
     *        when 1, the INT pin is configured as open drain.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_int_open(bool state);

    /**
     * @brief Get the INT pin configuration
     * @return true if the INT pin is configured as open drain, false if pin is configured as push-pull.
     */
    bool get_int_open(void);

    /**
     * @brief When this bit is equal to 0, INT pin emits a 50us long pulse.
     *        when 1, the INT pin is held high untill the interrupt is cleared.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_latch_int_en(bool state);

    /**
     * @brief Get the latch int status
     * @return true if bit is set, otherwise false
     */
    bool get_latch_int_en(void);

    /**
     * @brief When this bit is equal to 0, interrupt status bits are cleared only
     *        by reading INT_STATUS (Register 58), when 1, interrupt status bits are
     *        cleared on any read operation
     * @param [in] state - Logical state of the bit being set.
     */
    void set_int_rd_clear(bool state);

    /**
     * @brief Get the int read clear bit status
     * @return true if set, otherwise false
     */
    bool get_int_rd_clear(void);

    /**
     * @brief When this bit is equal to 0, the logic level for the FSYNC pin
     *        (when used as an interrupt to the host processor) is active high.
     *        When 1, the logic level for FSYNC (when used as an interrupt to the
     *        host processor) is active low.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_fsync_int_level(bool state);

    /**
     * @brief Get the fsync int level 
     * @return true if the logic level for FSYNC is active low, otherwise false.
     */
    bool get_fsync_int_level(void);

    /**
     * @brief When equal to 0, this bit disables the FSYNC pin from causing an interrupt
     *        to the host processor. When 1, enables the FSYNC pin to be used as an interrupt
     *        to the host processor.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_fsync_int_en(bool state);

    /**
     * @brief Get the fsync int en bit
     * @return true if FSYNC pin is enabled to be used as interrupt to the host pocessor, otherwise false.
     */
    bool get_fsync_int_en(void);

    /**
     * @brief When this bit is equal to 1 and I2C_MST_EN  is equal to 0, the host application processor
     *        will be able to directly access the auxiliary I2C bus of the MPU-6050.
     *        When 0, the host application processor will not be able to directly access the auxiliary I2C bus
     *        of the MPU-60X0 regardless of the state of I2C_MST_EN.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_i2c_bypass_en(bool state);

    /**
     * @brief Get the I2C bypass enable bit. 
     * @return true if enabled, otherwise false
     */
    bool get_i2c_bypass_en(void);

    //------------------------------------------------------------------------

    /**
     * INT_ENABLE (0x38) register
     * This register enables interrupt generation by interrupt sources.
     */

    /**
     * @brief When set to 1, this bit enables a FIFO buffer overflow to generate an interrupt.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_int_enable_data_rdy(bool state);

    /**
     * @brief Get the data ready interrupt bit state.
     * @return true set, otherwise false
     */
    bool get_int_enable_data_rdy(void);

    /**
     * @brief When set to 1, this bit enables any of the I2C Master interrupt
     *        sources to generate an interrupt.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_int_enable_i2c_mst(bool state);

    /**
     * @brief Get the I2C master interrupt bit state.
     * @return true if set, otherwise false.
     */
    bool get_int_enable_i2c_mst(void);

    /**
     * @brief When set to 1, this bit enables the Data Ready interrupt,
     *        which occurs each time a write operation to all of the sensor registers has been completed.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_int_enable_fifo_oflow(bool state);

    /**
     * @brief Get the FIFO buffer overflow interrupt bit state
     * @return true if set, otherwise false.
     */
    bool get_int_enable_fifo_oflow(void);

    //------------------------------------------------------------------------

    /**
     * INT_STATUS (0x3A) register (Read only)
     * This register shows the interrupt status of each interrupt generation source. Each bit
     * will clear after the register is read.
     */

    /**
     * @brief  This bit automatically sets to 1 when a Data Ready interrupt is generated, clears 
     *         to 0 after the register has been read.
     * @return Data Ready interrupt status.
     */
    bool get_int_status_data_rdy(void);

    /**
     * @brief  This bit automatically sets to 1 when an I2C Master interrupt has been generated, clears 
     *         to 0 after the register has been read.
     * @return I2C Master interrupt status.
     */
    bool get_int_status_i2c_mst(void);

    /**
     * @brief  This bit automatically sets to 1 when a FIFO buffer overflow interrupt has been generated,
     *         clears to 0 after the register has been read.
     * @return FIFO buffer overflow interrupt status.
     */
    bool get_int_status_fifo_oflow(void);

    //------------------------------------------------------------------------

    /**
     *  Accelerometer measurements, 0x3A to 40 registers (Read only)
     *  Measurements are written to these registers at the defined Sample Rate.
     *  Each 16-bit accelerometer measurement has a full scale defined in ACCEL_FS.
     *  These registers store the most recent accelerometer measurements.
     */

    /**
     * @brief  Reads the measurement from the accelerometer.
     * @return vector - Raw accelerometer measurement as a vector
     */
    vector get_accel_data(void);

    /**
     * @brief Reads the measurement from the accelerometer x axis
     * @return int16_t - Raw accelerometer x axis measurement
     */
    int16_t get_accel_x_axis(void);

    /**
     * @brief Reads the measurement from the accelerometer y axis
     * @return int16_t - Raw accelerometer y axis measurement
     */
    int16_t get_accel_y_axis(void);

    /**
     * @brief Reads the measurement from the accelerometer z axis
     * @return int16_t - Raw accelerometer z axis measurement
     */
    int16_t get_accel_z_axis(void);

    //------------------------------------------------------------------------

    /**
     * @brief  Temperature measurement, registers 0x41 and 0x42 (Read only)
     * @note   The temperature in degrees C for a given register value may be computed as:
     *         (TEMP_OUT Register Value as a signed quantity)/340 + 36.53
     * @return int16_t - the most recent temperature sensor measurement.
     */
    int16_t get_temperature(void);

    //------------------------------------------------------------------------

    /** 
     * Gyroscope measurements, 0x43 to 0x48 registers (Read only).
     * These registers store the most recent gyroscope measurements.
     * Gyroscope measurements are written to these registers at the Sample Rate as defined in Register 25.
     * Each 16-bit gyroscope measurement has a full scale defined in FS_SEL.
     */

    /**
     * @brief  Reads the measurement from the gyroscpe.
     * @return vector - Raw gyroscope measurement as a vector
     */
    vector get_gyro_data(void);


    //------------------------------------------------------------------------
    // TODO: External Sensor Data, registers 0x49 to 0x60

    //------------------------------------------------------------------------

    /**
     * SIGNAL_PATH_RESET (0x68) register (Write only)
     * This register is used to reset the analog and digital signal paths of the gyro,
     * accelerometer, and temperature sensors
     */

    /**
     * @brief When set to 1, this bit resets the gyroscope analog and digital signal paths.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_temp_reset(bool state);

    /**
     * @brief When set to 1, this bit resets the accelerometer analog and digital signal paths.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_accel_reset(bool state);

    /**
     * @brief When set to 1, this bit resets the temperature sensor analog and digital signal paths.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_gyro_reset(bool state);

    //------------------------------------------------------------------------
    /**
     * USER_CTRL (0x6A) register
     * This register allows the user to enable and disable the FIFO buffer, I2C Master Mode,
     * and primary I2C interface. The FIFO buffer, I2C Master, sensor signal paths and sensor
     * registers can also be reset using this register.
     */

    /**
     * @brief When set to 1, this bit resets the signal paths for all sensors
     *        and clear the sensor registers. 
     * @note  This bit automatically clears to 0 after the reset has been triggered.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_sig_cond_reset(bool state);

    /**
     * @brief Get the signal cond reset bit state.
     * @return true if set, otherwise false.
     */
    bool get_sig_cond_reset(void);

    /**
     * @brief This bit resets the I2C Master when set to 1 while I2C_MST_EN equals 0.
     * @note  This bit automatically clears to 0 after the reset has been triggered.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_i2c_mst_reset(bool state);

    /**
     * @brief Get the i2c mst reset bit state
     * @return true if set, otherwise false.
     */
    bool get_i2c_mst_reset(void);

    /**
     * @brief This bit resets the FIFO buffer when set to 1 while FIFO_EN equals 0.
     * @note  This bit automatically clears to 0 after the reset has been triggered.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_fifo_reset(bool state);

    /**
     * @brief Get the fifo reset bit state.
     * @return true if set, otherwise false.
     */
    bool get_fifo_reset(void);

    /**
     * @brief Always write this bit as zero.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_i2c_if_dis(bool state);

    /**
     * @brief Get the i2c if dis bit state.
     * @return true if set, otherwise false.
     */
    bool get_i2c_if_dis(void);

    /**
     * @brief When set to 1, this bit enables I2C Master Mode. When this bit is cleared to 0,
     *        the auxiliary I2C bus lines are logically driven by the primary I2C bus.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_i2c_mst_en(bool state);

    /**
     * @brief Get the I2C Master Mode status
     * @return true if enabled, otherwise false.
     */
    bool get_i2c_mst_en(void);
    
    /**
     * @brief When set to 1, this bit enables FIFO operations. When this bit is cleared to 0,
     *        the FIFO buffer is disabled. The FIFO buffer cannot be written to or read from while disabled.
     * @note  The FIFO buffer’s state does not change unless the MPU-6050 is power cycled.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_fifo_en(bool state);

    /**
     * @brief Get the FIFO buffer operations status.
     * @return true if enabled, otherwise false
     */
    bool get_fifo_en(void);

    //------------------------------------------------------------------------
    /**
     * PWM_MGMT_1 (0x6B) register
     * This register allows the user to configure the power mode and clock source. It also provides
     * a bit for resetting the entire device, and a bit for disabling the temperature sensor.
     */

    /**
     * @brief Specifies the clock source of the device, 3-bit unsigned value.
     * @param [in] clk_source - @see mpu6050_pwr_mgmt_1_clksel
     */
    void set_clock_source(mpu6050_pwr_mgmt_1_clksel clk_source);

    /**
     * @brief Get the set clock source of the device
     * @return @see mpu6050_pwr_mgmt_1_clksel
     */
    mpu6050_pwr_mgmt_1_clksel get_clock_source(void);

    /**
     * @brief When set to 1, this bit disables the temperature sensor.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_temp_dis(bool state);

    /**
     * @brief Get the temp dis bit status.
     * @return true if set, otherwise false.
     */
    bool get_temp_dis(void);

    /**
     * @brief When this bit is set to 1 and SLEEP is disabled, the MPU-6050 will cycle
     *        between sleep mode and waking up to take a single sample of data from active
     *        sensors at a rate determined by LP_WAKE_CTRL
     * @param [in] state - Logical state of the bit being set.
     */
    void set_cycle(bool state);

    /**
     * @brief Get the cycle bit status.
     * @return true if set, otherwise false.
     */
    bool get_cycle(void);

    /**
     * @brief When set to 1, this bit puts the MPU-6050 into sleep mode.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_sleep(bool state);

    /**
     * @brief Get the sleep bit status.
     * @return true if set, otherwise false.
     */
    bool get_sleep(void);

    /**
     * @brief When set to 1, this bit resets all internal registers to their default values.
     * @note  The bit automatically clears to 0 once the reset is done.
     * @param [in] state - Logical state of the bit being set.
     */
    void set_device_reset(bool state);

    /**
     * @brief Get the device reset bit status
     * @return true if set, otherwise false.
     */
    bool get_device_reset(void);

    //------------------------------------------------------------------------

    /**
     * PWR_MGMT_2 (0x6C) register
     * This register allows the user to configure the frequency of wake-ups in Accelerometer Only Low Power Mode.
     * Also allows the user to put individual axes of the accelerometer and gyro into standby mode.
     */

    /**
     * @brief Specifies the frequency of wake-ups during Accelerometer Only Low Power Mode.
     * @see   mpu6050_pwr_mgmt_2_lp_wake_ctrl
     */
    void set_lp_wake_ctrl(mpu6050_pwr_mgmt_2_lp_wake_ctrl lp_wake_ctrl);

    /**
     * @brief  Get the frequency of wake-ups during accelerometer only low power mode
     * @return @see mpu6050_pwr_mgmt_2_lp_wake_ctrl 
     */
    mpu6050_pwr_mgmt_2_lp_wake_ctrl get_lp_wake_ctrl(void);

    /** @brief When set to 1, this bit puts the X axis accelerometer into standby mode. 
     *  @param [in] state - Logical state of the bit being set.
    */
    void set_stby_xa(bool state);

    /**
     * @brief Get the stby xa bit status
     * @return true if set, otherwise false.
     */
    bool get_stby_xa(void);

    /** @brief When set to 1, this bit puts the Y axis accelerometer into standby mode. 
     *  @param [in] state - Logical state of the bit being set.
    */
    void set_stby_ya(bool state);

    /**
     * @brief Get the stby ya bit status
     * @return true if set, otherwise false.
     */
    bool get_stby_ya(void);

    /** @brief When set to 1, this bit puts the Z axis accelerometer into standby mode.
     *  @param [in] state - Logical state of the bit being set.
    */
    void set_stby_za(bool state);

    /**
     * @brief Get the stby xa bit status
     * @return true if set, otherwise false.
     */
    bool get_stby_za(void);

    /** @brief When set to 1, this bit puts the X axis gyroscope into standby mode.
     *  @param [in] state - Logical state of the bit being set.
    */
    void set_stby_xg(bool state);
    
    /**
     * @brief Get the stby xg bit status
     * @return true if set, otherwise false.
     */
    bool get_stby_xg(void);

    /** @brief When set to 1, this bit puts the Y axis gyroscope into standby mode.
     *  @param [in] state - Logical state of the bit being set.
    */
    void set_stby_yg(bool state);

    /**
     * @brief Get the stby yg bit status
     * @return true if set, otherwise false.
     */
    bool get_stby_yg(void);

    /** @brief When set to 1, this bit puts the Z axis gyroscope into standby mode.
     *  @param [in] state - Logical state of the bit being set.
    */
    void set_stby_zg(bool state);

    /**
     * @brief Get the stby xg bit status
     * @return true if set, otherwise false.
     */
    bool get_stby_zg(void);

    //------------------------------------------------------------------------

    /**
     * @brief  FIFO_COUNT (0x72 and 0x73) registers (Read only)
     * @note   These registers shadow the FIFO Count value. Both registers are loaded
     *         with the current sample count when FIFO_COUNT_H (Register 0x72) is read.
     * @return uint16_t - Indicates the number of bytes stored in the FIFO buffer.
     */
    uint16_t get_fifo_count(void);

    /**
     * @brief FIFO_R_W (0x74) register
     * @note  This register is used to read and write data from the FIFO buffer.
     * @param [in] data - 8-bit data transferred to the FIFO buffer.
     */
    void fifo_write(uint8_t data);

    /**
     * @brief Read FIFO buffer.
     * @return uint8_t - 8-bit data transferred from the FIFO buffer.
     */
    uint8_t fifo_read(void);

    //------------------------------------------------------------------------
    
    /**
     * @brief  WHO_AM_I (0x75) register (Read only)
     * @note   This register is used to verify the identity of the device
     *         The defalult value of the register is 0x68
     * @return uint8_t - The 6-bit I2C address of the MPU-6050.
     */
    uint8_t get_who_am_i(void);

private:

    uint8_t temp_register;          /**< Temporary register for reading registers*/
    uint16_t temp_register_word;    /**< Temporary 16-bit register. */
    bool temp_register_bit_state;   /**< Temporary 1-bit register. */
    vector accel_data;              /**< Vector of data from accel. */
    vector gyro_data;               /**< Vector of data from gyro*/

    /* Private functions for writing and reading data from I2C interface. */
    
    bool write_register_byte(uint8_t reg, uint8_t value, uint8_t position, uint8_t bitmask);
    bool write_register_byte(uint8_t reg, uint8_t value);
    bool read_register_byte(uint8_t reg, uint8_t *value, uint8_t position, uint8_t bitmask);
    bool read_register_byte(uint8_t reg, uint8_t *value);
    bool write_register_bit(uint8_t reg, uint8_t position, bool state);
    bool read_register_bit(uint8_t reg, uint8_t position, bool *state);
    bool read_register_word(uint8_t reg, uint16_t *value);
    bool write_register_word(uint8_t reg, uint16_t value);
};

//--------------------------------------------------------------------------------

#endif /* MPU6050_H_ */