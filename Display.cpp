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


void Display::paint() {
  // the paint function just calls display() to render everything to screen
  //
  // partitions handle their own drawing using write()
  display->display();
}
