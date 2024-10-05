#include "TimeStamp.h"

TimeStamp::TimeStamp() {seconds_since_epoch_ = time(0);}

TimeStamp::TimeStamp(int64_t seconds_since_epoch) : seconds_since_epoch_(seconds_since_epoch) {}

TimeStamp TimeStamp::now() {return TimeStamp();}

time_t TimeStamp::toInt() const {return seconds_since_epoch_;}

std::string TimeStamp::toString() const {
    char buffer[80] = {0};
    tm* tm_time {::localtime(&seconds_since_epoch_)};
    snprintf(buffer, 80, "%4d-%02d-%02d %02d:%02d:%02d", 
            tm_time->tm_year + 1900, 
            tm_time->tm_mon + 1, 
            tm_time->tm_mday, 
            tm_time->tm_hour, 
            tm_time->tm_min, 
            tm_time->tm_sec
            );
    return buffer;
}
