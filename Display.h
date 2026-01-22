#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Adafruit_PCD8544.h>
#include "Sprites.h"

// this file describes our arduino display


// we define a partition which descibes a section
// of our screen.
//
// e.g.
//  ___________________
// |                   |
// |    partition 1    |
// |                   |
// |-------------------| 
// |                   |
// |    partition 2    |
// |                   |
// |___________________|
//
// this way, we can render into partitions without
// overwriting other UI
class Partition {
  public:
    Partition(int x, int y, int width, int height);

    void clear(Adafruit_PCD8544* display);
    void write(Adafruit_PCD8544* display, const char* text);
    void writeCentered(Adafruit_PCD8544* display, const char* text, int textSize = 1);
    void drawBitmap(
      Adafruit_PCD8544* display,
      const unsigned char* bitmap,
      int bitmapWidth,
      int bitmapHeight,
      int offsetX = -1,
      int offsetY = -1,
      bool flip = false
    );

    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

  private:
    int x, y, width, height;

    void drawFlippedBitmap(
      Adafruit_PCD8544* display,
      const uint8_t* bitmap,
      int x0,
      int y0,
      int w,
      int h
    );
};


// The whole UI that is comprised of partitions
class Display {
  public:
    Display();

    void setup();

    // Partition access
    Partition* getTopPartition() { return &topPartition; }
    Partition* getBottomPartition() { return &bottomPartition; }
    Partition* getTextBoxPartition() { return &textBoxPartition; }

    // Paint all partitions to the display
    void paint();

    Adafruit_PCD8544* getDisplay();

  private:
    Adafruit_PCD8544* display;
    static const int TOP_HEIGHT = 10;      // Top section: 0-9 pixels
    static const int PET_Y = 10;           // Pet section starts at pixel 10
    static const int PET_HEIGHT = 30;      // Pet section: 10-39 pixels
    static const int TEXTBOX_Y = 40;       // Text box starts at pixel 40
    static const int TEXTBOX_HEIGHT = 8;   // Text box: 40-47 pixels (8px tall)

    Partition topPartition{0, 0, 84, TOP_HEIGHT};
    Partition bottomPartition{0, PET_Y, 84, PET_HEIGHT};
    Partition textBoxPartition{0, TEXTBOX_Y, 84, TEXTBOX_HEIGHT};
};

#endif
