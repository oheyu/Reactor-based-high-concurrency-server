#ifndef TIME_STAMP_H
#define TIME_STAMP_H

#include <iostream>
#include <string>
#include <time.h>

class TimeStamp {
private:
    time_t seconds_since_epoch_;

public:
    TimeStamp();

    TimeStamp(int64_t seconds_since_epoch);

    static TimeStamp now();

    time_t toInt() const;

    std::string toString() const;
};

#endif // !TimeStamp_H
