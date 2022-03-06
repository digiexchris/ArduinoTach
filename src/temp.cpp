#include "temp.h"

char* Temp::getTempString() {
  sensors->requestTemperatures(); 
  float temperatureC = sensors->getTempCByIndex(0);
  return "12.33";//sprintf("%fºC",temperatureC);
}

Temp::Temp() {
  oneWire = new OneWire(oneWireBus);
  sensors = new DallasTemperature(oneWire);
  // Start the DS18B20 sensor
  sensors->begin();
}
