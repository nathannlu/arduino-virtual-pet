#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Sprites.h"

// everything related to the game state
// goes here

class GameState {
  public:
    GameState();

    void feed();
    void doPlay();
    void doRave();
    void decay();
    void walk(int minX, int maxX, int spriteWidth);

    bool isAlive() const;
    int getHunger() const;
    int getPlay() const;
    int getRave() const;
    int getX() const;
    int getY() const;
    int getDirection() const;

    void setX(int newX);
    void setY(int newY);
    void setDirection(int newDirection);

  private:
    int hunger;
    int play;
    int rave;
    bool alive;

    int x;
    int y;
    int direction;  // 0 = left, 1 = right

    void checkAlive();
};

#endif
