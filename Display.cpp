#include "Display.h"
#include <SPI.h>
#include <Adafruit_GFX.h>


// these hardcoded constants
// correspond to the arduino pins
#define CLK 7
#define DIN 6
#define DC  5
#define CE  4
#define RST 3
#define BACKLIGHT 9

Display::Display() {
  display = new Adafruit_PCD8544(CLK, DIN, DC, CE, RST);
}

void Display::setup() {
  Serial.begin(9600);

  // Setup backlight
  pinMode(BACKLIGHT, OUTPUT);

  display->begin();
  display->setContrast(65);
  display->setRotation(2); // why are we setting the rotation here?
  delay(1000);

  // clears the screen and buffer
  display->clearDisplay();
}

Adafruit_PCD8544* Display::getDisplay() {
  return display;
}

void Display::printGameState(int hunger, int play, int rave) {
  display->clearDisplay();
  display->setTextSize(1);
  display->setTextColor(BLACK);

  display->setCursor(0, 0);
  display->print("Hunger: ");
  display->println(hunger);

  display->setCursor(0, 10);
  display->print("Play: ");
  display->println(play);

  display->setCursor(0, 20);
  display->print("Rave: ");
  display->println(rave);

  display->display();
}
