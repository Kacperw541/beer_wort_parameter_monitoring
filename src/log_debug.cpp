/**
 * @file serial_debug.cpp
 * @author Kacper Wiśniewski (kwisniewski541@gmail.com)
 * @version 1.0
 * @date 2022-12-08
 */

//--------------------------------------------------------------------------------

#include <log_debug.h>

//--------------------------------------------------------------------------------

#if (LOG_DEBUG == LOG_WIFI)
Sender& log_sender = Sender::get_instance();

//--------------------------------------------------------------------------------

void send_log(const String &log)
{
    const String _log = String((get_utc_time())) + log;
    log_sender.send_message_log(_log);
}
#endif