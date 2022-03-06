#ifndef MAIN_H
    #define MAIN_H
#endif

#include "screen.h"
// #include "temp.h"
#include "volts.h"

#define MODE_BUTTON 0//D3 //wemos pin 0

//modes: tach, volts, temp, clock
volatile int mode = 0;