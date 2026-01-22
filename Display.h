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

    void drawBitmap(
      Adafruit_PCD8544* display, 
      const unsigned char* bitmap, 
      int bitmapWidth, 
      int bitmapHeight, 
      int offsetX = -1, 
      int offsetY = -1, 
      bool flip = false
    ) {
      // Clear this partition first
      clear(display);

      int bitmapX, bitmapY;

      // If offsets are provided (not -1), use them; otherwise center the bitmap
      if (offsetX == -1 || offsetY == -1) {
        bitmapX = x + (width - bitmapWidth) / 2;
        bitmapY = y + (height - bitmapHeight) / 2;
      } else {
        bitmapX = x + offsetX;
        bitmapY = y + offsetY;
      }

      if (flip) {
        // Draw flipped bitmap pixel by pixel
        drawFlippedBitmap(display, bitmap, bitmapX, bitmapY, bitmapWidth, bitmapHeight);
      } else {
        display->drawBitmap(bitmapX, bitmapY, bitmap, bitmapWidth, bitmapHeight, BLACK);
      }
    }

  private:
    int x, y, width, height;

    void drawFlippedBitmap(
      Adafruit_PCD8544* display,
      const uint8_t* bitmap,
      int x0,
      int y0,
      int w,
      int h
    ) {
      int bytesPerRow = (w + 7) / 8;

      for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {

          int byteIndex = y * bytesPerRow + (x / 8);
          int bitIndex  = 7 - (x % 8);

          uint8_t b = pgm_read_byte(&bitmap[byteIndex]);
          bool pixel = (b >> bitIndex) & 1;

          if (pixel) {
            display->drawPixel(
                x0 + (w - 1 - x),  // horizontal flip
                y0 + y,
                BLACK
            );
          }
        }
      }
    }

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
    static const int TOP_HEIGHT = 10;    // Top section: 0-9 pixels
    static const int BOTTOM_Y = 10;      // Bottom section starts at pixel 10

    Partition topPartition{0, 0, 84, TOP_HEIGHT};
    Partition bottomPartition{0, BOTTOM_Y, 84, 48 - BOTTOM_Y};
};

#endif
