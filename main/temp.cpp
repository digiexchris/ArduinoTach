#include "temp.h"

void Temp::getTempString(char* buffer) {
  sensors->requestTemperatures();
  float temperatureC = sensors->getTempCByIndex(0);
  sprintf(buffer, "%dC",int(temperatureC));
}

Temp::Temp() {
  oneWire = new OneWire(oneWireBus);
  sensors = new DallasTemperature(oneWire);
  // Start the DS18B20 sensor
  sensors->begin();
  Serial.println("Temp Up");
}
