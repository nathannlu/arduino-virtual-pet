#ifndef GAME_H
#define GAME_H

#include "EventScheduler.h"
#include "RenderAnimation.h"
#include "GameState.h"

class Game {
  public:
    GameState state;

    Game(EventScheduler* scheduler, RenderAnimation* renderer);

    void setup();
    void loop();
    void doFeed();
    void doPlay();
    void doRave();

  private:
    EventScheduler* eventScheduler;
    RenderAnimation* renderPtr;

    static Game* gameInstance;

    static void updateGameState();
    static void updateDirection();
    static void updateWalk();
    static void updateDisplay();
};

#endif
