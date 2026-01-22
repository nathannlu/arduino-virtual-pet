#ifndef GAME_H
#define GAME_H

#include "EventScheduler.h"
#include "Display.h"
#include "GameState.h"
#include "GameState.h"

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
      // Update top partition with stats
      char statsBuffer[50];
      sprintf(statsBuffer, "H:%d P:%d R:%d",
        gameInstance->state.getHunger(),
        gameInstance->state.getPlay(),
        gameInstance->state.getRave()
      );
      gameInstance->displayPtr->getTopPartition()->write(
        gameInstance->displayPtr->getDisplay(),
        statsBuffer
      );
      gameInstance->displayPtr->paint();
    }

};

Game* Game::gameInstance = nullptr;

#endif
