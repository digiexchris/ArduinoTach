#include "tach.h"
#include <Arduino.h>

void IRAM_ATTR tachISR() {
  revcounter++;
}

Tach::Tach() {
  rpm = 0;
  attachInterrupt(digitalPinToInterrupt(rpmPin),tachISR,RISING);
}

int Tach::calcRPM() {
  // Serial.println(revcounter);
  detachInterrupt(rpmPin);           //detaches the interrupt while calculating
  time=millis()-oldtime;        //finds the time 
  // Serial.println(revcounter);
  // Serial.println(time);
  rpm=(revcounter/time)*60000;         //calculates rpm
  oldtime=millis();             //saves the current time
  revcounter=0;
  attachInterrupt(digitalPinToInterrupt(rpmPin),tachISR,RISING);
  // Serial.println(revcounter);
  // Serial.println(time);
  // Serial.println(rpm);
  // return 6200;
  return rpm;
}