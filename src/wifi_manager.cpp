/**
 * @file wifi_manager.cpp
 * @author Kacper Wiśniewski (kwisniewski541@gmail.com)
 * @version 1.0
 * @date 2022-12-08 
 */

//--------------------------------------------------------------------------------

#include <ArduinoJson.h>
#include <FS.h>
#include <wifi_manager.h>
#include <log_debug.h>
#include <config_manager.h>

//--------------------------------------------------------------------------------

void WifiManager::begin()
{
    if (!load_config())
    {
        LOG("[WIFI MANAGER] WIFI CONFIG LOAD ERROR");
        initialized = false;
        return;
    }
    
    WiFi.begin(ssid, pass);

    if (WiFi.waitForConnectResult(WIFI_TIMEOUT) != WL_CONNECTED)
    {
        LOG("[WIFI MANAGER] WIFI connection timeout!");
        initialized = false;
        return;
    }

    initialized = true;

    LOG("[WIFI MANAGER] WIFI : successful initialization");
    LOG("[WIFI MANAGER] WIFI RSSI : " + String(WiFi.RSSI()));
}

bool WifiManager::is_connected()
{
    return (WiFi.status() == WL_CONNECTED);
}

bool WifiManager::load_config()
{
    ConfigManager& config = ConfigManager::get_instance();

    if (!config.is_device_configured())
    {
        if (!config.load())
            return false;
    }

    config.get(WIFI_PASSWOWRD, this->pass);
    config.get(WIFI_SSID, this->ssid);

    return true;
}
