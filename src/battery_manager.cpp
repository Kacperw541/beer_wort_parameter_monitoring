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
    voltage = (analogRead(ADC_PIN) / ADC_DIVIDER);
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

void BatteryManager::check()
{
    /* If the voltage level is critical, the program cannot be allowed to run. */
    if (!this->init())
        ESP.deepSleep(ESP.deepSleepMax(), RF_DISABLED);
}


battery_status BatteryManager::get_battery_status()
{
    return this->status;
}

float BatteryManager::get_voltage()
{
    voltage = (analogRead(ADC_PIN) / ADC_DIVIDER);
    LOG("[BATTERY MANAGER] Battery voltage : " + String(this->voltage));
    return this->voltage;
}
