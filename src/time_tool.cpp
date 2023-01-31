
/**
 * @file time_tool.cpp
 * @author Kacper Wiśniewski (kwisniewski541@gmail.com)
 * @version 1.0
 * @date 2022-12-07
 */
//--------------------------------------------------------------------------------

#include <time_tool.h>

//--------------------------------------------------------------------------------

#define UTC_OFFSET_SEC 3600L

//--------------------------------------------------------------------------------
/* Private variables. */

static WiFiUDP ntpUDP;
static NTPClient time_client(ntpUDP, "pool.ntp.org", UTC_OFFSET_SEC);
static time_t time_since_epoch;
static time_t start_time;
static char time_buff[32];
static bool initialized = false;

//--------------------------------------------------------------------------------
/* Private function declatarions. */

static bool begin_time();

//--------------------------------------------------------------------------------

char* get_utc_time()
{
    if (!initialized)
    {
        if (!begin_time())
        {
            sprintf(time_buff, "");
            return time_buff;
        }
    }

    time_since_epoch += (millis()/1000) - start_time;
    start_time = millis()/1000;
    std::tm *timeResult{};
    timeResult = std::gmtime( &time_since_epoch );
    sprintf(time_buff, "[%04d-%02d-%02d %02d:%02d:%02d] ", timeResult->tm_year + 1900, timeResult->tm_mday, timeResult->tm_mon +1
                                            , timeResult->tm_hour, timeResult->tm_min, timeResult->tm_sec);
    return time_buff;
}

char* get_utc_time_format_()
{
    if (!initialized)
    {
        if (!begin_time())
        {
            sprintf(time_buff, "");
            return time_buff;
        }
    }

    time_since_epoch += (millis()/1000) - start_time;
    start_time = millis()/1000;
    std::tm *timeResult{};
    timeResult = std::gmtime( &time_since_epoch );
    sprintf(time_buff, "%04d%02d%02d%02d%02d%02d", timeResult->tm_year + 1900 ,timeResult->tm_mday, timeResult->tm_mon +1
                                            , timeResult->tm_hour, timeResult->tm_min, timeResult->tm_sec);
    return time_buff;
}

time_t get_time_since_epoch()
{
    if (!initialized)
    {
        if (!begin_time())
            return 0;
    }
    time_since_epoch += (millis()/1000) - start_time;
    start_time = millis()/1000;

    return time_since_epoch;
}

/**
 * @brief Time tool initializationh
 * @return true if successful, otherwise false.
 */
static bool begin_time()
{
    if (!WiFi.isConnected())
        return false;
        
    time_client.begin();
    if (!time_client.update())
        return false;

    time_since_epoch = time_client.getEpochTime();
    start_time = 0;
    time_client.end();
    initialized = true;
    return true;
}
