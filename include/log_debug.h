/**
 * @file serial_debug.h
 * @author Kacper Wiśniewski
 * @version 1.0
 * @date 2022-10-12
 */
//--------------------------------------------------------------------------------

#ifndef LOG_DEBUG_H_
#define LOG_DEBUG_H_

//--------------------------------------------------------------------------------

#include "time_tool.h"
#include "sender.h"

//--------------------------------------------------------------------------------

#define LOG_OFF    0    /**< Logs disabled*/
#define LOG_SERIAL 1    /**< Logs sending via the serial port. */
#define LOG_WIFI   2    /**< Logs sending to the database via wifi. */

#define LOG_DEBUG  LOG_OFF   /**< Selected logging mode. */

#if (LOG_DEBUG == LOG_SERIAL)
    #define LOG(x) Serial.print(get_utc_time()); Serial.println(x)
#elif (LOG_DEBUG == LOG_WIFI)
    #define LOG(x) send_log(x);
#else
    #define LOG(x)
#endif

//--------------------------------------------------------------------------------
#if (LOG_DEBUG == LOG_WIFI)
/**
 * @brief Send log to database.
 * @param [in] log - Log message to send
 */
void send_log(const String &log);
#endif
//--------------------------------------------------------------------------------

#endif /* LOG_DEBUG_H_ */