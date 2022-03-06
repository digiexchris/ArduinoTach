#include "volts.h"

Volts::Volts() {
  pinMode(voltagePin, INPUT);
}

float Volts::getVolts() {
  value = analogRead(voltagePin);
  vout = (value * 3.125) / 1023.0;   // start with 3.3 and calibrate
  vin = vout / (R2/(R1+R2));

  return vin;
}

