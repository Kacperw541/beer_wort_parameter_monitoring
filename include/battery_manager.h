/**
 * @file battery_manager.h
 * @author Kacper Wiśniewski (kwisniewski541@gmail.com)
 * @version 1.0
 * @date 2023-01-15
 */

//--------------------------------------------------------------------------------

#ifndef BATTERY_MANAGER_H_
#define BATTERY_MANAGER_H_

//--------------------------------------------------------------------------------

#include <Arduino.h>
#include "log_debug.h"

//--------------------------------------------------------------------------------

#define BATTERY_VERY_LOW 3.3f
#define BATTERY_LOW      3.7f
#define BATTERY_MEDIUM   3.85f
#define BATTERY_HIGH     4.0f 
#define VOLTAGE_OFFSET   0.3f

//--------------------------------------------------------------------------------
/* Public constants and types. */

/** @brief Battery status depends on the voltage level. */
enum battery_status
{
    BATTERY_STATUS_CRITICAL,
    BATTERY_STATUS_LOW,
    BATTERY_STATUS_MEDIUM,
    BATTERY_STATUS_HIGH
};

static const char *battery_status_to_str[]
{
    [BATTERY_STATUS_CRITICAL] = "CRITICAL",
    [BATTERY_STATUS_LOW] = "LOW",
    [BATTERY_STATUS_MEDIUM] = "MEDIUM",
    [BATTERY_STATUS_HIGH] = "HIGH"
};

//--------------------------------------------------------------------------------

/**
 * @brief The class is used to control the battery, sets the status of the voltage level
 *        and allows voltage measurement.
 */
class BatteryManager
{
public:

    /**
     * @brief Battery manager init, reads battery voltage and sets status.
     * @return true if battery status ok, false if critical
     */
    bool init();

    /** @brief Checking battery level, if critical - go to sleep mode max time. */
    void check();

    /**
     * @brief Get the current set battery status
     * @return battery_status - current battery status
     */
    battery_status get_battery_status();

    /**
     * @brief Measures and returns the battery voltage.
     * @return float - battery voltage
     */
    float get_voltage();

private:

    float voltage;          /**< Stores the measured voltage value. */
    battery_status status;  /**< Stores the set battery status. */
};

//--------------------------------------------------------------------------------

#endif /* BATTERY_MANAGER_H_ */