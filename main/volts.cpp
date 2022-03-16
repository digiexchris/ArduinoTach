#include "volts.h"

Volts::Volts() {
  pinMode(voltagePin, INPUT);
}

float Volts::getVolts() {

  float ADCMaxVolts = 3.65;

  value = analogRead(voltagePin);

  switch (int(value)) {
    case 0 ... 530:
      ADCMaxVolts = 4.21;
      break;
    case 531 ... 645:
      ADCMaxVolts = 4.05;
      break;
    case 646 ... 757:
      ADCMaxVolts = 3.93;
      break;
    case 758 ... 875:
      ADCMaxVolts = 3.82;
      break;
    case 876 ... 987:
      ADCMaxVolts = 3.77;
      break;
    case 988 ... 1106:
      ADCMaxVolts = 3.7;
      break;
    case 1107 ... 1226:
      ADCMaxVolts = 3.65;
      break;
    case 1227 ... 1340:
      ADCMaxVolts = 3.60;
      break;
    case 1341 ... 1456:
      ADCMaxVolts = 3.57;
      break;
    case 1457 ... 1580:
      ADCMaxVolts = 3.54;
      break;
    default:
      ADCMaxVolts = 3.54;
  }
  Serial.println(value);
  Serial.println(ADCMaxVolts);
  vout = (value * ADCMaxVolts) / 4095.0;   // start with 3.3 and calibrate
  vin = vout / (R2/(R1+R2));

  return vin;
}

