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

// Partition implementation
Partition::Partition(int x, int y, int width, int height)
  : x(x), y(y), width(width), height(height) {}

void Partition::clear(Adafruit_PCD8544* display) {
  display->fillRect(x, y, width, height, WHITE);
}

void Partition::write(Adafruit_PCD8544* display, const char* text) {
  // Clear this partition first
  clear(display);

  // Write text to this partition
  display->setTextSize(1);
  display->setTextColor(BLACK);
  display->setCursor(x, y);
  display->println(text);
}

void Partition::writeCentered(Adafruit_PCD8544* display, const char* text, int textSize) {
  // Clear this partition first
  clear(display);

  // Calculate text width (rough estimate: 6 pixels per char for size 1)
  int textWidth = strlen(text) * 6 * textSize;
  int textX = x + (width - textWidth) / 2;

  // Write centered text to this partition
  display->setTextSize(textSize);
  display->setTextColor(BLACK);
  display->setCursor(textX, y);
  display->print(text);
}

void Partition::drawBitmap(
  Adafruit_PCD8544* display,
  const unsigned char* bitmap,
  int bitmapWidth,
  int bitmapHeight,
  int offsetX,
  int offsetY,
  bool flip
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

void Partition::drawFlippedBitmap(
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

int Partition::getX() const { return x; }
int Partition::getY() const { return y; }
int Partition::getWidth() const { return width; }
int Partition::getHeight() const { return height; }

// Display implementation
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
