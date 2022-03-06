#ifndef TEMP_H
#define TEMP_H
#include <OneWire.h>
#include <DallasTemperature.h>
// GPIO where the DS18B20 is connected to
const int oneWireBus = 4; 

class Temp {
    private:
        OneWire* oneWire;
        DallasTemperature* sensors;

    public:
        Temp();

        char* getTempString();

};

#endif