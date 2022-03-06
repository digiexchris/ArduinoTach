#ifndef TIME_H
    #define TIME_H

#include <Arduino.h>
#include "RTClib.h"

class Clock {
    

    private:
        RTC_DS3231 rtc;
        
    public:

        Clock();
        void incrementHours();
        void incrementMinutes();
        char* getTimeString();
        
};

#endif