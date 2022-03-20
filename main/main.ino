

#include <EEPROM.h>
#include "main.h"

// #include "soc/soc.h"
// #include "soc/rtc_cntl_reg.h"

// static DashClock* dashclock;
static Screen* screen;
static Temp* temp;
static Volts* volts;
static Tach* tach;

// bool incrementMinute = false;
// bool incrementHour = false;

void setMode() {
  mode++;
}

// void incrementMinutes() {
//   dashclock->incrementMinutes();
//   incrementMinute = false;
// }

// void incrementHours() {
//   dashclock->incrementHours();
//   incrementHour = false;
// }

void IRAM_ATTR handleMode() {
  unsigned long debounceLockOut = 200;//set lock out time
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceLockOut)
  {
    setMode();
  }
  last_interrupt_time = interrupt_time;
}

// void IRAM_ATTR incrementMinutesISR() {
//   unsigned long debounceLockOut = 200;//set lock out time
//   static unsigned long last_interrupt_time = 0;
//   unsigned long interrupt_time = millis();
  
//   if (interrupt_time - last_interrupt_time > debounceLockOut)
//   {
//     mode = 2;
//     incrementMinute = true;
//   }
//   last_interrupt_time = interrupt_time;
// }

// void IRAM_ATTR incrementHoursISR() {
//   unsigned long debounceLockOutH = 200;//set lock out time
//   static unsigned long last_interrupt_timeH = 0;
//   unsigned long interrupt_time = millis();
  
//   if (interrupt_time - last_interrupt_timeH > debounceLockOutH)
//   {
//     mode = 2;
//     incrementHour = true;
//   }
//   last_interrupt_timeH = interrupt_time;
// }

void setup() {
  // WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

  //load mode from eeprom
  EEPROM.begin(512);
  mode = EEPROM.read(0);
  savedMode = mode;
  
  Serial.begin(115200);
  Serial.print("\n"); // skip garbage
  // delay(1000);
  Serial.println("Starting init");
  // dashclock = new DashClock();
  // Serial.println("Clock Up");
  screen = new Screen();
  Serial.println("Screen Up");
  temp = new Temp();
  Serial.println("Temp Up");
  volts = new Volts();
  Serial.println("Volts Up");
  tach = new Tach();
  Serial.println("Tach Up");

  pinMode(MODE_BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(MODE_BUTTON), handleMode, FALLING);  
  // pinMode(hourPin, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(hourPin), incrementHoursISR, FALLING);
  // pinMode(minutePin, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(minutePin), incrementMinutesISR, FALLING);
}

void loop() {
  if (mode > 2) {
    mode = 0;
  }

  loopCounter++;

  if (loopCounter > 11) {
    loopCounter = 0;
  }

  saveCounter++;
  if (saveCounter > 599) {
    saveCounter = 0;
    //save mode to eeprom
    if (mode != savedMode) {
      EEPROM.write(0,mode);
      EEPROM.commit();
    }
  }

  if(volts->getVolts() < minVolts && saveCounter >598) {
    //set mode to volt display if we're below the threshold
    //and a minute has gone by
    mode = 1;
  }

  // if(incrementHour) {
  //   incrementHours();
  // }

  // if(incrementMinute) {
  //   incrementMinutes();
  // }

  screen->clearDisplay();
  switch(mode) {
    case 0:
      screen->drawTach(tach->calcRPM());
      delay(500);
      break;
    case 1:
      screen->drawVolts(volts->getVolts(), loopCounter);
      delay(200);
      break;
    // case 2:
    //   char t[10];
    //   dashclock->getTimeString(t);
    //   screen->drawTime(t);
    //   delay(200);
    //   break;
    case 2:
      char tempStr [16];
      temp->getTempString(tempStr);
      screen->drawTemp(tempStr);
      delay(300);
      break;
  }

  screen->write();
}
