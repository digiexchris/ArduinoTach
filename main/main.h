#ifndef MAIN_H
    #define MAIN_H
#endif

#include "screen.h"
#include "temp.h"
#include "volts.h"
#include "tach.h"
// #include "dashtime.h"

#define MODE_BUTTON 27//D3 //wemos pin 0

//modes: tach, volts, temp, clock
volatile int mode = 0;
int savedMode = 0;
int modeAddress = 0;
int loopCounter = 0;
int saveCounter = 0;

const int hourPin = 25;
const int minutePin = 32;