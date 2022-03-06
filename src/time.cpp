#include "time.h"

Clock::Clock() {
  // initializing the rtc
    if(!rtc.begin()) {
        Serial.println("Couldn't find RTC!");
        Serial.flush();
        while (1) delay(10);
    }

    Serial.println("RTC Up");

    if(rtc.lostPower()) {
        // this will adjust to the date and time at compilation
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    //we don't need the 32K Pin, so disable it
    rtc.disable32K();
    rtc.disableAlarm(1);
    rtc.disableAlarm(2);
}

char* Clock::getTimeString() {
  char t[10] = "hh:mm";
  return rtc.now().toString(t);
}