#include "screen.h"

void Screen::clearDisplay() {
  display->clearDisplay();
}

void Screen::write() {
  display->display();
}

Screen::Screen() {
  display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
  //   // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display->clearDisplay();
  display->display();
  delay(1);

  display->setTextColor(SSD1306_WHITE);
  display->setTextSize(2.5); 
  display->print("TW200");
  delay(200);
  display->setTextSize(4.5);             // Draw 2X-scale text
  Serial.println("Screen Up");
}

void Screen::drawTach(int rpm) {
  display->setCursor(0, 0);
  display->print(rpm);
  display->fillRect(0, 25, int(display->width()*(rpm/9800.0)),7, SSD1306_WHITE);
  display->invertDisplay(false);
}

void Screen::drawTime(char* time) {
  display->setCursor(0, 0);
  display->print(time);
  display->invertDisplay(false);
}

void Screen::drawVolts(float volts, int loop) {
  double vc = 0;

  if(volts < minVolts) {
    vc = 0;
    if(loop % 3 == 0) {
      display->invertDisplay(true);
    } else {
      display->invertDisplay(false);
    }
    
  } else if(volts > maxVolts) {
    vc = 1;
    display->invertDisplay(false);
  } else {
    double dv = maxVolts - minVolts;
    double v = volts - minVolts;
    vc = v/dv;
    display->invertDisplay(false);
    //Serial.println(vc);
  }

  display->setCursor(0, 0);
  display->print(volts);

  display->fillRect(0, 25, int(display->width()*(vc)),7, SSD1306_WHITE);
}

void Screen::drawTemp(char* temp) {
  display->setCursor(0, 0);
  display->print(temp);
  display->invertDisplay(false);
}