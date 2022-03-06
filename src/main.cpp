

#include <EEPROM.h>
#include "main.h"

int loopCounter = 0;
int saveCounter = 0;

Clock clock;
Screen* screen;
// Temp* temp;
Volts* volts;

char* timeStr;

void setMode() {
  mode++;
}

void IRAM_ATTR handleMode() {
  unsigned long debounceLockOut = 150;//set lock out time
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > debounceLockOut)
  {
    setMode();
  }
  last_interrupt_time = interrupt_time;
}

void setup() {

  //load mode from eeprom
  
  Serial.begin(9600);
  Serial.print("\n"); // skip garbage
  clock = Clock();
  screen = new Screen();
  // temp = new Temp();
  volts = new Volts();

  pinMode(MODE_BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(MODE_BUTTON), handleMode, FALLING);  
}

void loop() {
  if (mode > 3) {
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
  }

  screen->clearDisplay();
  switch(mode) {
    case 0:
      screen->drawTach(3456);
      break;
    case 1:
      screen->drawVolts(volts->getVolts(), loopCounter);
      break;
    case 2:
      timeStr = clock.getTimeString();
      screen->drawTime(timeStr);
      break;
    case 3:
      // char* tempStr = temp->getTempString();
      // screen->drawTemp(tempStr);
      break;
  }

  screen->write();
  delay(100);
}