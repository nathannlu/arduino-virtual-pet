#ifndef RENDERANIMATION_H
#define RENDERANIMATION_H

#include "Display.h"
#include "Sprites.h"
#include "GameState.h"


// this file contains all the code describing the
// sprite animations

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
      Adafruit_PCD8544* disp = displayPtr->getDisplay();
      Partition* textBox = displayPtr->getTextBoxPartition();
      const int appleHeight = 2;  // Height above pet's head to show apple
      const int jumpHeight = 6;    // How high the pet jumps

      // Random feed text
      const char* feedTexts[] = {"INFINITE APPLE", "munch!", "nommers"};
      const char* selectedText = feedTexts[random(0, 3)];
      textBox->writeCentered(disp, selectedText, 1);

      // Step 1: Show apple floating above pet
      renderPet(ANIM_IDLE, x, y, direction);
      disp->drawBitmap(x + 7, y - appleHeight, epd_bitmap_apple, 5, 6, BLACK);
      paint();
      delay(200);

      // Step 2: Pet jumps up (idle animation while jumping)
      for (int i = 0; i <= jumpHeight; i += 2) {
        renderPet(ANIM_IDLE, x, y - i, direction);
        disp->drawBitmap(x + 7, y - appleHeight, epd_bitmap_apple, 5, 6, BLACK);
        paint();
        delay(50);
      }

      // Step 3: At peak of jump, eat the apple
      renderPet(ANIM_EAT, x, y - jumpHeight, direction);
      paint();
      delay(300);

      // Step 4: Fall back down (idle animation while falling)
      for (int i = jumpHeight; i >= 0; i -= 2) {
        renderPet(ANIM_IDLE, x, y - i, direction);
        paint();
        delay(50);
      }

      // Step 5: Back to idle on ground
      renderPet(ANIM_IDLE, x, y, direction);
      paint();

      // Clear text after animation
      textBox->clear(disp);
      paint();
    }

    void playPlayAnimation(int x, int y, int direction) {
      Adafruit_PCD8544* disp = displayPtr->getDisplay();
      Partition* bottom = displayPtr->getBottomPartition();
      Partition* textBox = displayPtr->getTextBoxPartition();
      const int arrowWidth = 22;
      const int arrowHeight = 7;
      const int petWidth = SPRITE_WIDTH;

      // Show play text
      textBox->writeCentered(disp, "ouch", 1);

      // Pet faces right, arrow comes from right
      int arrowStartX = 84;
      int arrowEndX = x + petWidth;  // Arrow stops when it hits the right edge of pet
      int arrowY = y + 6;  // Arrow at pet's middle height

      // Arrow flies in from right to left
      for (int arrowX = arrowStartX; arrowX >= arrowEndX; arrowX -= 4) {
        // Clear bottom partition
        bottom->clear(disp);

        // Draw pet facing right (direction = 1, no flip)
        disp->drawBitmap(x + bottom->getX(), y + bottom->getY(), epd_bitmap_idle, 19, 20, BLACK);

        // Draw arrow
        disp->drawBitmap(arrowX + bottom->getX(), arrowY + bottom->getY(), epd_bitmap_arrow, arrowWidth, arrowHeight, BLACK);

        paint();
        delay(30);
      }

      // Arrow hits! Play animation (facing right)
      renderPet(ANIM_PLAY, x, y, 1);
      paint();
      delay(800);

      // Return to idle with original direction
      renderPet(ANIM_IDLE, x, y, direction);
      paint();

      // Clear text after animation
      textBox->clear(disp);
      paint();
    }

    void playRaveAnimation(int x, int y, int direction) {
      Adafruit_PCD8544* disp = displayPtr->getDisplay();
      Partition* textBox = displayPtr->getTextBoxPartition();
      unsigned long startTime = millis();
      const int jumpHeight = 6;
      const int moveDistance = 4;  // How far to move horizontally per jump
      int currentDirection = direction;
      int currentX = x;

      // Random rave text
      const char* raveTexts[] = {"Yay rave", "I love molly!", "Zedd is so good"};
      const char* selectedText = raveTexts[random(0, 4)];
      textBox->writeCentered(disp, selectedText, 1);

      // Rave for 5 seconds
      while (millis() - startTime < 5000) {
        // Jump up and move forward
        for (int i = 0; i <= jumpHeight; i += 2) {
          renderPet(ANIM_RAVE, currentX, y - i, currentDirection);
          paint();
          delay(20);  // Faster jumping
        }

        // Move forward in current direction
        if (currentDirection == 1) {  // Moving right
          currentX += moveDistance;
          if (currentX + 19 >= 84) {  // Hit right wall
            currentX = 84 - 19;
            currentDirection = 0;  // Turn left
          }
        } else {  // Moving left
          currentX -= moveDistance;
          if (currentX <= 0) {  // Hit left wall
            currentX = 0;
            currentDirection = 1;  // Turn right
          }
        }

        // Fall down
        for (int i = jumpHeight; i >= 0; i -= 2) {
          renderPet(ANIM_RAVE, currentX, y - i, currentDirection);
          paint();
          delay(20);  // Faster jumping
        }

        // Randomly change direction after landing (50% chance)
        if (random(0, 2) == 1) {
          currentDirection = 1 - currentDirection;  // Flip direction
        }
      }

      // Return to idle
      renderPet(ANIM_IDLE, currentX, y, currentDirection);
      paint();

      // Clear text after animation
      textBox->clear(disp);
      paint();
    }

    void playDeathAnimation() {
      Adafruit_PCD8544* disp = displayPtr->getDisplay();
      Partition* bottom = displayPtr->getBottomPartition();
      Partition* textBox = displayPtr->getTextBoxPartition();

      // Clear bottom partition
      bottom->clear(disp);

      // Death sprite is 41x24px, center it in the partition
      int deathX = (84 - 41) / 2;  // Center horizontally in 84px wide partition
      int deathY = (30 - 24) / 2;  // Center vertically in 30px tall partition

      // Draw death sprite centered (no flip)
      disp->drawBitmap(deathX + bottom->getX(), deathY + bottom->getY(), epd_bitmap_death, 41, 24, BLACK);

      // Show death text
      textBox->writeCentered(disp, "im ded", 1);

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
          return epd_bitmap_death;
        default:
          return epd_bitmap_idle;
      }
    }
};

#endif
