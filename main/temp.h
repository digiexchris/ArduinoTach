#ifndef TEMP_H
#define TEMP_H
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Arduino.h>
// GPIO where the DS18B20 is connected to
const int oneWireBus = 18; 

class Temp {
    private:
        OneWire* oneWire;
        DallasTemperature* sensors;

    public:
        Temp();

        void getTempString(char* buffer);

};

#endif