#ifndef TIME_H
    #define TIME_H


#include "RTClib.h"

class Clock {
    RTC_DS3231 rtc;

    public:

        Clock();

        char* getTimeString();
};

#endif