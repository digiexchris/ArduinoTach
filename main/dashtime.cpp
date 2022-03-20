#include "dashtime.h"

DashClock::DashClock() {
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

void DashClock::getTimeString(char* buf) {
  char t[6] = "hh:mm";
  char* o;

  o = rtc.now().toString(t);

  for(int i=0; i < 6; ++i){
    buf[i] = o[i];
  }

  Serial.println(buf);
}

void DashClock::incrementMinutes() {
  DateTime now = rtc.now();
  now = now + 60;

  
  rtc.adjust(now);
}

void DashClock::incrementHours() {
  DateTime now = rtc.now();
  now = now + 3600;

  rtc.adjust(now);
}
