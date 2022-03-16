#ifndef TIME_H
    #define TIME_H

#include <Arduino.h>
#include "RTClib.h"

class DashClock {
    

    private:
        RTC_DS3231 rtc;
        
    public:

        DashClock();
        void incrementHours();
        void incrementMinutes();
        void getTimeString(char* buf);
        
};

#endif
