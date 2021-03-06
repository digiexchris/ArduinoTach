#ifndef SCREEN_H
#define SCREEN_H


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// #define ENABLE_I2C_DEBUG_BUFFER 1
#define SSD1306_NO_SPLASH 1
// #define I2C_SDA 22
// #define I2C_SCL 21

const double minVolts = 11.75;
const double maxVolts = 13.6;

const int SCREEN_WIDTH = 128; // OLED display width, in pixels
const int SCREEN_HEIGHT = 64; // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
// On an ESP8266 WEMOS: D1 (SCL), D2 (SDA)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

class Screen {
    private: 
        Adafruit_SSD1306* display;
    public:
        Screen();

        void clearDisplay();
        void write();
        void drawTime(char* time);
        void drawVolts(float volts, int loop);
        void drawTemp(char* temp);
        void drawTach(int rpm);
};



#endif