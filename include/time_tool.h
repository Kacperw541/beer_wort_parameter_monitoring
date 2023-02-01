/**
 * @file time_tool.h
 * @author Kacper Wiśniewski (kwisniewski541@gmail.com)
 * @version 1.0
 * @date 2022-12-07
 */

//--------------------------------------------------------------------------------

#ifndef TIME_TOOL_H_
#define TIME_TOOL_H_

//--------------------------------------------------------------------------------

#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <ctime>

//--------------------------------------------------------------------------------

#define TIME_ERROR 0

//--------------------------------------------------------------------------------
/* Public functions declatarions. */

/**
 * @brief Get the utc time in format : [yyyy-mm-dd hh:mm:ss]
 * @return char* - string with formatted time
 */
char* get_utc_time();

/**
 * @brief Get the utc time in format : yyyymmddhhmmss
 * @return char* - string with formatted time
 */
char *get_utc_time_format_();

/**
 * @brief Get the time since epoch
 * @return time_t - value of time since epoch
 */
time_t get_time_since_epoch();

//--------------------------------------------------------------------------------

#endif /* TIME_TOOL_H_ */