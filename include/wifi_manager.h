/**
 * @file wifi_manager.h
 * @author Kacper Wiśniewski (kwisniewski541@gmail.com)
 * @version 1.0
 * @date 2022-12-08
 */

//--------------------------------------------------------------------------------

#ifndef WIFI_MANAGER_H_
#define WIFI_MANAGER_H_

//--------------------------------------------------------------------------------

#include <ESP8266WiFi.h>

//--------------------------------------------------------------------------------

/** @brief Maximum waiting time for connecting to wifi. */
#define WIFI_TIMEOUT 10000

//--------------------------------------------------------------------------------

/**
 * @brief WIFI manager class TODO: opisąć
 * 
 */
class WifiManager
{
public:

    /**
     * @brief WiFi connection initialization.
     * @return true if successful, otherwise false.
     */
    void begin();

    /**
     * @brief Checks wifi connection
     * @return true if connected, otherwise false.
     */
    bool is_connected();

private:

    /** 
     * @brief Wifi config load
     * @return  true if successful, otherwise false.
    */
    bool load_config();

    char *ssid;         /**< WiFi SSID */
    char *pass;         /**< WiFi password. */
    bool initialized;   /**< Flag indicating wifi initialization status. */
};

//--------------------------------------------------------------------------------

#endif /* WIFI_MANAGER_H_ */