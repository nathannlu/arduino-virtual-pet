#ifndef RENDERANIMATION_H
#define RENDERANIMATION_H

#include "Display.h"
#include "Sprites.h"
#include "GameState.h"

enum AnimationType {
  ANIM_IDLE,
  ANIM_EAT,
  ANIM_PLAY,
  ANIM_RAVE,
  ANIM_DEATH
};

class RenderAnimation {
  public:
    RenderAnimation(Display* disp) : displayPtr(disp) {}

    void renderStats(int hunger, int play, int rave) {
      Adafruit_PCD8544* disp = displayPtr->getDisplay();
      Partition* top = displayPtr->getTopPartition();

      // Clear top partition
      top->clear(disp);

      // Draw apple icon + hunger value
      disp->drawBitmap(0, 0, epd_bitmap_apple, 5, 6, BLACK);
      disp->setCursor(7, 0);
      disp->setTextSize(1);
      disp->setTextColor(BLACK);
      disp->print(hunger);

      // Draw smiley icon + play value
      disp->drawBitmap(28, 0, epd_bitmap_smiley, 5, 4, BLACK);
      disp->setCursor(35, 0);
      disp->print(play);

      // Draw heart icon + rave value
      disp->drawBitmap(56, 0, epd_bitmap_heart, 5, 4, BLACK);
      disp->setCursor(63, 0);
      disp->print(rave);
    }

    void renderPet(AnimationType animType, int x, int y, int direction) {
      Adafruit_PCD8544* disp = displayPtr->getDisplay();
      Partition* bottom = displayPtr->getBottomPartition();

      const unsigned char* sprite = getSpriteForAnimation(animType);
      bool flip = (direction == 0);  // Flip if facing left

      bottom->drawBitmap(disp, sprite, 19, 20, x, y, flip);
    }

    void paint() {
      displayPtr->paint();
    }

    void playFeedAnimation(int x, int y, int direction) {
      renderPet(ANIM_EAT, x, y, direction);
      paint();
      delay(1000);
      renderPet(ANIM_IDLE, x, y, direction);
      paint();
    }

    void playPlayAnimation(int x, int y, int direction) {
      renderPet(ANIM_PLAY, x, y, direction);
      paint();
      delay(1000);
      renderPet(ANIM_IDLE, x, y, direction);
      paint();
    }

    void playRaveAnimation(int x, int y, int direction) {
      renderPet(ANIM_RAVE, x, y, direction);
      paint();
      delay(1000);
      renderPet(ANIM_IDLE, x, y, direction);
      paint();
    }

    void playDeathAnimation(int x, int y, int direction) {
      renderPet(ANIM_DEATH, x, y, direction);
      paint();
    }

  private:
    Display* displayPtr;

    const unsigned char* getSpriteForAnimation(AnimationType type) {
      switch (type) {
        case ANIM_IDLE:
          return epd_bitmap_idle;
        case ANIM_EAT:
          return epd_bitmap_eat;
        case ANIM_PLAY:
          return epd_bitmap_fun;
        case ANIM_RAVE:
          return epd_bitmap_rave;
        case ANIM_DEATH:
          return epd_bitmap_idle;  // TODO: Add death sprite
        default:
          return epd_bitmap_idle;
      }
    }
};

#endif
