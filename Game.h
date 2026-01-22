#ifndef GAME_H
#define GAME_H

#include "EventScheduler.h"
#include "Display.h"

class Game {

  public:
    Game(EventScheduler* scheduler, Display* disp) {
      eventScheduler = scheduler;
      displayPtr = disp;
      gameInstance = this;
    }

    void setup() {
      eventScheduler->addEvent(updateGameState, 2000);  // Update every 2 seconds
      eventScheduler->addEvent(updateDisplay, 500);     // Refresh display every 0.5 seconds
    }

    void loop() {
      eventScheduler->update();
    }


    void feed() {
      hunger = min(100, hunger + 20);
    }

    void doPlay() {
      play = min(100, play + 15);
    }

    void doRave() {
      rave = min(100, rave + 25);
    }

  private:
    int hunger = 100;
    int play = 100;
    int rave = 100;

    int ticks = 0;

    EventScheduler* eventScheduler;
    Display* displayPtr;

    static Game* gameInstance;


    static void updateGameState() {
      // Decrease stats over time
      if (gameInstance->hunger > 0) {
        gameInstance->hunger -= 5;
      }
      if (gameInstance->play > 0) {
        gameInstance->play -= 3;
      }
      if (gameInstance->rave > 0) {
        gameInstance->rave -= 2;
      }

      gameInstance->ticks++;
    }

    static void updateDisplay() {
      gameInstance->displayPtr->printGameState(
        gameInstance->hunger,
        gameInstance->play,
        gameInstance->rave
      );
    }

};

Game* Game::gameInstance = nullptr;

#endif
