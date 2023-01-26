/**
 * @file battery_manager.cpp
 * @author Kacper Wiśniewski (kwisniewski541@gmail.com)
 * @version 1.0
 * @date 2023-01-15
 */

//--------------------------------------------------------------------------------

#include <battery_manager.h>

//--------------------------------------------------------------------------------

bool BatteryManager::init()
{
    voltage = (analogRead(A0) / (float)191.8) + VOLTAGE_OFFSET;
    if (voltage <= BATTERY_VERY_LOW)
    {
        status = BATTERY_STATUS_CRITICAL;
        return false;
    }
    else if (voltage <= BATTERY_LOW)
        status = BATTERY_STATUS_LOW;
    else if (voltage <= BATTERY_MEDIUM)
        status = BATTERY_STATUS_MEDIUM;
    else
        status = BATTERY_STATUS_HIGH;

    return true;
}

battery_status BatteryManager::get_battery_status()
{
    return this->status;
}

float BatteryManager::get_voltage()
{
    voltage = (analogRead(A0) / 191.8) + VOLTAGE_OFFSET;
    LOG("[BATTERY MANAGER] Battery voltage : " + String(this->voltage));
    return this->voltage;
}
