#ifndef GAME_H
#define GAME_H

#include "EventScheduler.h"
#include "Display.h"
#include "GameState.h"
#include "Render.h"

class Game {

  public:
    GameState state;

    Game(EventScheduler* scheduler, Display* disp) {
      eventScheduler = scheduler;
      displayPtr = disp;
      gameInstance = this;
    }

    void setup() {
      eventScheduler->addEvent(updateGameState, 2000);  // Update every 2 seconds
      eventScheduler->addEvent(updateDisplay, 500);     // Refresh display every 0.5 seconds

      // Initialize with idle state on bottom partition
      displayPtr->getBottomPartition()->write(displayPtr->getDisplay(), "A");
      displayPtr->paint();
    }

    void loop() {
      eventScheduler->update();
    }

    void doFeed() {
      displayPtr->getBottomPartition()->write(displayPtr->getDisplay(), "B");
      displayPtr->paint();
      state.feed();
      delay(1000);
      displayPtr->getBottomPartition()->write(displayPtr->getDisplay(), "A");
      displayPtr->paint();
    }

    void doPlay() {
      displayPtr->getBottomPartition()->write(displayPtr->getDisplay(), "C");
      displayPtr->paint();
      state.doPlay();
      delay(1000);
      displayPtr->getBottomPartition()->write(displayPtr->getDisplay(), "A");
      displayPtr->paint();
    }

    void doRave() {
      displayPtr->getBottomPartition()->write(displayPtr->getDisplay(), "D");
      displayPtr->paint();
      state.doRave();
      delay(1000);
      displayPtr->getBottomPartition()->write(displayPtr->getDisplay(), "A");
      displayPtr->paint();
    }


  private:
    EventScheduler* eventScheduler;
    Display* displayPtr;

    static Game* gameInstance;


    static void updateGameState() {
      gameInstance->state.decay();
    }

    static void updateDisplay() {
      // Update top partition with stats using icons
      Adafruit_PCD8544* disp = gameInstance->displayPtr->getDisplay();
      Partition* top = gameInstance->displayPtr->getTopPartition();

      // Clear top partition
      top->clear(disp);

      // Draw apple icon + hunger value
      disp->drawBitmap(0, 0, epd_bitmap_apple, 5, 6, BLACK);
      disp->setCursor(7, 0);
      disp->setTextSize(1);
      disp->setTextColor(BLACK);
      disp->print(gameInstance->state.getHunger());

      // Draw smiley icon + play value
      disp->drawBitmap(28, 0, epd_bitmap_smiley, 5, 4, BLACK);
      disp->setCursor(35, 0);
      disp->print(gameInstance->state.getPlay());

      // Draw heart icon + rave value
      disp->drawBitmap(56, 0, epd_bitmap_heart, 5, 4, BLACK);
      disp->setCursor(63, 0);
      disp->print(gameInstance->state.getRave());

      gameInstance->displayPtr->paint();
    }

};

Game* Game::gameInstance = nullptr;

#endif
