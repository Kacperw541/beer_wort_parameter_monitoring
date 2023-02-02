/**
 * @file config_manager.h
 * @author Kacper Wisniewski (kwisniewski541@gmail.com)
 * @version 1.0
 * @date 2022-12-08
 */

//--------------------------------------------------------------------------------

#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

//--------------------------------------------------------------------------------

#include <ArduinoJson.h>
#include <FS.h>
#include <LittleFS.h>
#include "log_debug.h"

//--------------------------------------------------------------------------------

#define CONFIG_MAX_READING_ATTEMPS 3

//--------------------------------------------------------------------------------
/* Public constants and types. */

/** @brief  Setting type used to get and set the value. */
enum setting
{
    WIFI_PASSWOWRD,
    WIFI_SSID,
    EMAIL,
    FIREBASE_PASSWORD,
    API_KEY,
    DATABASE_URL,
    SLEEP_TIME,
    COEFFICIENT_A,
    COEFFICIENT_B,
    COEFFICIENT_C,
    COEFFICIENT_D,
    COEFFICIENT_E
};

//--------------------------------------------------------------------------------

/**
 * @brief Singleton class for retrieving settings from a json file stored in flash memory
 *        and for saving new settings in this file. Stores settings in private variables
 */
class ConfigManager
{
public:

    /** @brief Destroy the Config Manager object. */
    ~ConfigManager();

    /**
     * @brief Get the static instance of config.
     * @return ConfigManager& - reference to the config object
     */
    static ConfigManager& get_instance();

    /** @brief Initialize the saved settings and checks if they are correct.*/
    void init();

    /**
     * @brief Read config from json file.
     * @return true if successful, false otherwise.
     */
    bool load();

    /**
     * @brief Save settings in json file.
     * @return true if successful, false otherwise.
     */
    bool save();

    /**
     * @brief Check if settings are configured and saved
     * @return true if settings exist, otherwise false.
     */
    bool is_device_configured();

    /**
     * @brief Get the selected setting for a string.
     * @param [in] setting - type of setting to get
     * @param [out] buf - reference to the pointer where the setting will be assigned.
     */
    void get(setting setting, char *&buf);

    /**
     * @brief Get the selected setting for a uint64_t.
     * @param [in] setting - type of setting to get
     * @param [out] buf - pointer to the variable to which the setting will be loaded
     */
    void get(setting setting, uint64_t *buf);

    /**
     * @brief Get the selected setting for a double.
     * @param [in] setting - type of setting to get
     * @param [out] buf - pointer to the variable to which the setting will be loaded
     */
    void get(setting setting, double *buf);
    
    /**
     * @brief Set the selected setting for a string.
     * @param [in] setting - type of setting to set
     * @param [in] buf - string to set
     */
    void set(setting setting, const char *buf);

    /**
     * @brief Set the selected setting for a uint64_t.
     * @param [in] setting - type of setting to set
     * @param [in] buf - value to set
     */
    void set(setting setting, uint64_t buf);

    /**
     * @brief Set the selected setting for a double.
     * @param [in] setting - type of setting to set
     * @param [in] buf - value to set
     */
    void set(setting setting, double buf);

private:

    /** @brief Construct a new Config Manager object. */
    ConfigManager();

    static ConfigManager instance;  /**< Static config instance*/
    char *ssid;                     /**< WiFi SSID */
    char *pass;                     /**< WiFi PASS*/
    char *email;                    /**< Firebase email address. */
    char *firebase_password;        /**< Firebase account password. */
    char *api_key;                  /**< Firebase api key. */
    char *database_url;             /**< Firebase realtime database url. */
    uint64_t sleep_time;            /**< Interval between waking up the device. */
    double coeff_a;                 /**< The coefficient of the function that calculates the density of the solution. */
    double coeff_b;                 /**< The coefficient of the function that calculates the density of the solution. */
    double coeff_c;                 /**< The coefficient of the function that calculates the density of the solution. */
    double coeff_d;                 /**< The coefficient of the function that calculates the density of the solution. */
    double coeff_e;                 /**< The coefficient of the function that calculates the density of the solution. */
};

//--------------------------------------------------------------------------------

#endif /* CONFIGMANAGER_H */