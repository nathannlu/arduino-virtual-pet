#ifndef GAME_H
#define GAME_H

#include "EventScheduler.h"
#include "RenderAnimation.h"
#include "GameState.h"

class Game {

  public:
    GameState state;

    Game(EventScheduler* scheduler, RenderAnimation* renderer) {
      eventScheduler = scheduler;
      renderPtr = renderer;
      gameInstance = this;
    }

    void setup() {
      eventScheduler->addEvent(updateGameState, 10000);  // Update every 2 seconds
      eventScheduler->addEvent(updateDisplay, 500);     // Refresh display every 0.5 seconds
      eventScheduler->addRandomEvent(updateDirection, 2000, 10000);  // Update direction randomly every 2-10 seconds
      eventScheduler->addEvent(updateWalk, 200);

      // Initialize with idle state
      renderPtr->renderPet(ANIM_IDLE, state.getX(), state.getY(), state.getDirection());
      renderPtr->paint();
    }

    void loop() {
      eventScheduler->update();
    }

    void doFeed() {
      state.feed();
      renderPtr->playFeedAnimation(state.getX(), state.getY(), state.getDirection());
    }

    void doPlay() {
      state.doPlay();
      renderPtr->playPlayAnimation(state.getX(), state.getY(), state.getDirection());
    }

    void doRave() {
      state.doRave();
      renderPtr->playRaveAnimation(state.getX(), state.getY(), state.getDirection());
    }


  private:
    EventScheduler* eventScheduler;
    RenderAnimation* renderPtr;

    static Game* gameInstance;


    static void updateGameState() {
      gameInstance->state.decay();
    }

    static void updateDirection() {
      // Don't change direction if dead
      if (!gameInstance->state.isAlive()) return;

      // Randomly flip direction: 0 = left, 1 = right
      int newDirection = random(0, 2);
      gameInstance->state.setDirection(newDirection);
    }

    static void updateWalk() {
      // Don't walk if dead
      if (!gameInstance->state.isAlive()) return;

      // Walk within the bottom partition bounds
      // Bottom partition is 84 pixels wide, sprite is 19 pixels wide
      gameInstance->state.walk(0, 84, 19);
    }

    static void updateDisplay() {
      // Check if dead
      if (!gameInstance->state.isAlive()) {
        gameInstance->renderPtr->playDeathAnimation();
        return;
      }

      // Render stats
      gameInstance->renderPtr->renderStats(
        gameInstance->state.getHunger(),
        gameInstance->state.getPlay(),
        gameInstance->state.getRave()
      );

      // Render pet
      gameInstance->renderPtr->renderPet(
        ANIM_IDLE,
        gameInstance->state.getX(),
        gameInstance->state.getY(),
        gameInstance->state.getDirection()
      );

      gameInstance->renderPtr->paint();
    }

};

Game* Game::gameInstance = nullptr;

#endif
