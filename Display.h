#ifndef DISPLAY_H
#define DISPLAY_H

// this file describes our arduino display

#include <Arduino.h>
#include <Adafruit_PCD8544.h>

class Display {
  public:
    Display();

    void setup();

    void printGameState(int hunger, int play, int rave);

    Adafruit_PCD8544* getDisplay();

  private:
    Adafruit_PCD8544* display;
};

#endif
