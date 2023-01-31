
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

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", UTC_OFFSET_SEC);
static time_t StartTime;
static time_t timeSinceEpoch;
static char time_buff[32];
static bool is_begin = false;

//--------------------------------------------------------------------------------
/* Private function declatarions. */

static bool begin_time();

//--------------------------------------------------------------------------------

char* get_utc_time()
{
    if (!is_begin)
    {
        is_begin = begin_time();
        if (!is_begin)
        {
            sprintf(time_buff, "");
            return time_buff;
        }
    }

    timeSinceEpoch += (millis()/1000) - StartTime;
    StartTime = millis()/1000;
    std::tm *timeResult{};
    timeResult = std::gmtime( &timeSinceEpoch );
    sprintf(time_buff, "[%04d-%02d-%02d %02d:%02d:%02d] ", timeResult->tm_year + 1900, timeResult->tm_mday, timeResult->tm_mon +1
                                            , timeResult->tm_hour, timeResult->tm_min, timeResult->tm_sec);
    return time_buff;
}

char* get_utc_time_format_()
{
    if (!is_begin)
    {
        is_begin = begin_time();
        if (!is_begin)
        {
            sprintf(time_buff, "");
            return time_buff;
        }
    }

    timeSinceEpoch += (millis()/1000) - StartTime;
    StartTime = millis()/1000;
    std::tm *timeResult{};
    timeResult = std::gmtime( &timeSinceEpoch );
    sprintf(time_buff, "%04d%02d%02d%02d%02d%02d", timeResult->tm_year + 1900 ,timeResult->tm_mday, timeResult->tm_mon +1
                                            , timeResult->tm_hour, timeResult->tm_min, timeResult->tm_sec);
    return time_buff;
}

time_t get_time_since_epoch()
{
    if (!is_begin)
    {
        is_begin = begin_time();    
        if (!is_begin)
            return 0;
    }
    return timeSinceEpoch;
}

/**
 * @brief Time tool initializationh
 * @return true if successful, otherwise false.
 */
static bool begin_time()
{
    timeClient.begin();
    if(!timeClient.update())
        return false;

    timeSinceEpoch = timeClient.getEpochTime();
    StartTime = 0;
    timeClient.end();
    return true;
}
