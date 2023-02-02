/**
 * @file firebase_manager.h
 * @author Kacper Wiśniewski (kwisniewski541@gmail.com)
 * @version 1.0
 * @date 2023-01-11
 */

//--------------------------------------------------------------------------------

#ifndef SENDER_H_
#define SENDER_H_

//--------------------------------------------------------------------------------

#include <FS.h>
#include <Firebase_ESP_Client.h>
#include "log_debug.h"
#include "config_manager.h"

//--------------------------------------------------------------------------------

/** @brief Maximum number of measurement files stored in memory. */
#define SENDER_DATA_FILES_MAX 1000

//--------------------------------------------------------------------------------
/* Public constants and types*/

/** @brief Measurement data structure. */
struct data
{
    float temperature;      /**< Value of the measured temperature. */
    float plato;            /**< Value of the measured degrees plato.*/
    float battery_voltage;  /**< Value of the measured battery voltage. */
};

//--------------------------------------------------------------------------------

/** @brief Class for handling the Firebase database. 
 *         It is used to send measurements data and logs.
 *         When wifi is not connected, it saves measurements to flash memory.
 */
class Sender
{
public:

    /** @brief Destroy the Sender object. */
    ~Sender();

    /**
     * @brief Get the static instance of Sender.
     * @return Sender& - reference to the Sender object
     */
    static Sender& get_instance();

    /** @brief Database initialization, must be called before using Sender. */
    void init();

    /**
     * @brief Send measurement data to the database, including data stored in files
     * @param [in] measurement - Pointer to the structure with measurement data
     */
    void send_data(data *measurement);

    /**
     * @brief Save measurement data to a file
     * @param [in] measurement - Reference to the structure with measurement data
     */
    void save_data(data &measurement);

#if LOG_DEBUG == LOG_WIFI
    /**
     * @brief Send the log to the database
     * @param [in] log - Log message to send
     */
    void send_message_log(const String &log);
#endif
private:

    /** @brief Construct a new Sender object. */
    Sender();

    /**
     * @brief Send the temperature measurement to the database
     * @param [in] temp - Measured temperature to send
     * @return true if sending was successful, otherwise false
     */
    bool send_temperature(float temp);

    /**
     * @brief Send the measured degrees plato to the database
     * @param plato  - Measured plato to send
     * @return true if sending was successful, otherwise false
     */
    bool send_plato(float plato);

    /**
     * @brief Send the battery voltage measurement to the database
     * @param voltage - Measured battery voltage to send
     * @return true if sending was successful, otherwise false
     */
    bool send_battery_voltage(float voltage);

    /**
     * @brief Send the given time to the database
     * @param time - Time value to send
     * @return true if sending was successful, otherwise false
     */
    bool send_time(time_t time);

    /**
     * @brief Retrieves the current time and sends it to the database
     * @return true if sending was successful, otherwise false
     */
    bool send_time();

    /**
     * @brief Parse files with previous saved measurements
     * @param [out] data_array - Pointer to the vector of structures to which the data from files is written.
     */
    void parse_data_files(std::vector <data> *data_vector);

    /**
     * @brief  Checks if files with saved measurements exist.
     * @return true if there are saved measurements, otherwise false.
     */
    bool data_waiting_to_sent();
    
    static Sender instance;     /**< The only static sender instance in the program*/
    bool initialized;           /**< Initialization status flag. */
    data *measurement;          /**< Pointer to the measurement data to be sent. */
    FB_RTDB *database;          /**< Pointer to the */
    FirebaseData *fbdo;         /**< Pointer to the FirebaseData. */    
    FirebaseAuth *auth;         /**< Pointer to the FirebaseAuth. */
    FirebaseConfig *fb_config;  /**< Pointer to the Firebase Config. */
    char *email;            /**< Firebase user email. */
    char *password;         /**< Firebase user password. */
    char *api_key;          /**< Firebase API key. */
    char *database_url;     /**< URL to the database. */
    const char *uid;        /**< User ID. */
    String database_path;   /**< Main path in the database. */
    String parent_path;     /**< Subpath for data. */

#if LOG_DEBUG == LOG_WIFI
    bool is_path;           /**< Flag indicating whether the log path has been created. */
    FirebaseJsonArray *log_buf; /**< LOG buffer, it is used before wifi connection. */
    String log_path;        /**< Subpath for logs. */
#endif
};

//--------------------------------------------------------------------------------

#endif /* SENDER_H_ */