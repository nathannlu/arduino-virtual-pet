#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Adafruit_PCD8544.h>

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
    Partition(int x, int y, int width, int height)
      : x(x), y(y), width(width), height(height) {}

    void clear(Adafruit_PCD8544* display) {
      display->fillRect(x, y, width, height, WHITE);
    }

    void write(Adafruit_PCD8544* display, const char* text) {
      // Clear this partition first
      clear(display);

      // Write text to this partition
      display->setTextSize(1);
      display->setTextColor(BLACK);
      display->setCursor(x, y);
      display->println(text);
    }

    void drawBitmap(Adafruit_PCD8544* display, const unsigned char* bitmap, int bitmapWidth, int bitmapHeight) {
      // Clear this partition first
      clear(display);

      // Draw bitmap centered in the partition
      int bitmapX = x + (width - bitmapWidth) / 2;
      int bitmapY = y + (height - bitmapHeight) / 2;
      display->drawBitmap(bitmapX, bitmapY, bitmap, bitmapWidth, bitmapHeight, BLACK);
    }

    int getX() const { return x; }
    int getY() const { return y; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

  private:
    int x, y, width, height;
};


// The whole UI that is comprised of partitions
class Display {
  public:
    Display();

    void setup();

    // Partition access
    Partition* getTopPartition() { return &topPartition; }
    Partition* getBottomPartition() { return &bottomPartition; }

    // Paint all partitions to the display
    void paint();

    Adafruit_PCD8544* getDisplay();

  private:
    Adafruit_PCD8544* display;
    static const int TOP_HEIGHT = 24;    // Top section: 0-23 pixels
    static const int BOTTOM_Y = 24;      // Bottom section starts at pixel 24

    Partition topPartition{0, 0, 84, TOP_HEIGHT};
    Partition bottomPartition{0, BOTTOM_Y, 84, 48 - BOTTOM_Y};
};

#endif
