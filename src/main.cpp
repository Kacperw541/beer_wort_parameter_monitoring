/**
 * @file main.cpp
 * @author Kacper Wiśnewski
 * @version 1.0
 * @date 2022-10-02
 */ 

//--------------------------------------------------------------------------------

#include <Arduino.h>
#include <Esp.h>
#include <config_manager.h>
#include <battery_manager.h>
#include <accelgyro_manager.h>
#include <temp_sensor_manger.h>
#include <wifi_manager.h>
#include <sender.h>
#include <log_debug.h>

//--------------------------------------------------------------------------------

/** @brief Pin responsible for one wire communication. */
#define ONE_WIRE_BUS D6

/** @brief Serial Clock pin to I2C protocol. */
#define I2C_SCL      D1

/** @brief Serial Data pin to I2C protocol. */
#define I2C_SDA      D2

/** @brief Peak of the counter of measurements for which data are not sent to the database. */
#define BATTERY_SAVING_OFFLINE_MODE_MAX 3

//--------------------------------------------------------------------------------
/* Private variables and types. */

ConfigManager& config = ConfigManager::get_instance(); /**< Config singleton instance. */
Sender& sender = Sender::get_instance();               /**< Firebase sender singleton instance. */
static WifiManager wifi;               /**< WiFi instance. */
static BatteryManager battery;         /**< Battery manager instance. */
static Temperature temperature;        /**< Temperature DS18B20 sensor instance. */
static Accelgyro accelgyro;            /**< Accelgyro MPU6050 sensor instance. */
static data measurement;               /**< Measurement data structure. */
static uint64_t sleep_time;            /**< Interval between device wake-ups. */

/** @brief Device operating mode, depends on battery status and wifi connection status. */
enum
{
    DEFAULT_ONLINE,         /**< Battery status better than low, wifi is connected. */
    DEFAULT_OFFLINE,        /**< Battery status better than low, wisi is not connected. */
    BATTERY_SAVING_ONLINE,  /**< Battery status is low, wifi is connected. */
    BATTERY_SAVING_OFFLINE, /**< Battery status is low, wifi is not connected. */
    CRITICAL_BATTERY        /**< Battery status is critical, in this mode, the device immediately goes to sleep. */
} device_mode;

//--------------------------------------------------------------------------------
/* Private functions declarations. */

/** @brief Wifi setup in default mode, when battery status is ok. */
void default_wifi_setup();

/** @brief Wifi setup when battery status is low. */
void battery_saving_wifi_setup();

//--------------------------------------------------------------------------------

void default_wifi_setup()
{
    wifi.begin();
    sender.init();
    device_mode = wifi.is_connected() ? DEFAULT_ONLINE : DEFAULT_OFFLINE;
}

void battery_saving_wifi_setup()
{
    uint32_t offline_wake_counter;
    ESP.rtcUserMemoryRead(0, &offline_wake_counter, sizeof(offline_wake_counter));

    if (offline_wake_counter >= BATTERY_SAVING_OFFLINE_MODE_MAX)
    {
        wifi.begin();
        sender.init();
        
        if (wifi.is_connected())
        {
            device_mode = BATTERY_SAVING_ONLINE;
            offline_wake_counter = 0;
        }
        else
        {
            device_mode = BATTERY_SAVING_OFFLINE;
            offline_wake_counter ++;
        }
    }
    else
    {
        device_mode = BATTERY_SAVING_OFFLINE;
        offline_wake_counter ++;
    }

    ESP.rtcUserMemoryWrite(0, &offline_wake_counter, sizeof(offline_wake_counter));
}

//--------------------------------------------------------------------------------

void setup() 
{
    battery.check();

#if LOG_DEBUG == LOG_SERIAL
    Serial.begin(9600);
#endif

    LOG("----------------------MAIN PROGRAM STARTED----------------------");
    LOG("[MAIN SETUP] Reset reason: " + String(ESP.getResetReason()));
    LOG("[MAIN SETIP] BATTERY STATUS : " + String(battery_status_to_str[battery.get_battery_status()]));

    config.init();
    config.get(SLEEP_TIME, &sleep_time);

    switch (battery.get_battery_status())
    {
    case BATTERY_STATUS_LOW:
        LOG("[MAIN SETUP] Device in saving battery mode. ");
        battery_saving_wifi_setup(); break;
    default: 
        LOG("[MAIN SETUP] Device in default mode. ");
        default_wifi_setup(); break;
    }

    accelgyro.init(I2C_SCL, I2C_SDA);
    temperature.init(ONE_WIRE_BUS);

    LOG("[MAIN SETUP] Setup time: " + String(millis()) + " ms");
}

//--------------------------------------------------------------------------------

/* Main process. Should be executed only once. */
void loop()
{
    measurement.battery_voltage = battery.get_voltage();
    measurement.temperature = temperature.get_temp();
    measurement.plato = accelgyro.get_plato(measurement.temperature);
    
    switch (device_mode)
    {
    case DEFAULT_ONLINE:
    case BATTERY_SAVING_ONLINE:
        sender.send_data(&measurement);
        break;
    case DEFAULT_OFFLINE:
    case BATTERY_SAVING_OFFLINE:
        sender.save_data(measurement);
        break;
    case CRITICAL_BATTERY:
        break;
    }

    LOG("[MAIN] Program execution time :" + String(millis()) + " ms");
    LOG("[MAIN] Deep Sleep for : " + String(sleep_time/60000000) + "min");
    accelgyro.sleep();
    ESP.deepSleep(sleep_time);

    LOG("[MAIN] SHOULD NEVER BE HERE!");
}
