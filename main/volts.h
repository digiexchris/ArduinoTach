#ifndef VOLTS_H
    #define VOLTS_H

#include <Arduino.h>

const int voltagePin = 33;

class Volts {
    private:
        float value = 0.0;
        float vout = 0.0;
        float vin = 0.0;
        const float R1 = 100300;                // Resistor R1 100k 
        const float R2 = 10030;                 // Resistor R2 10k

    public:
        float getVolts();
        Volts();
};

#endif