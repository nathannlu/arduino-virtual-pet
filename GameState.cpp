#include "GameState.h"
#include <Arduino.h>

GameState::GameState() {
  hunger = 100;
  play = 100;
  rave = 100;
  alive = true;
  x = 0;
  y = 30 - SPRITE_HEIGHT;  // Bottom of pet partition (30px tall - 20px sprite)
  direction = 1;  // Start facing right
}

void GameState::feed() {
  if (!alive) return;
  hunger = min(100, hunger + 20);
  checkAlive();
}

void GameState::doPlay() {
  if (!alive) return;
  play = min(100, play + 15);
  checkAlive();
}

void GameState::doRave() {
  if (!alive) return;
  rave = min(100, rave + 25);
  checkAlive();
}

void GameState::decay() {
  if (!alive) return;

  if (hunger > 0) {
    hunger -= 5;
  }
  if (play > 0) {
    play -= 3;
  }
  if (rave > 0) {
    rave -= 2;
  }

  checkAlive();
}

void GameState::walk(int minX, int maxX, int spriteWidth) {
  if (!alive) return;

  // Move in the current direction
  if (direction == 1) {  // Moving right
    x += 1;
    // Check if hit right wall
    if (x + spriteWidth >= maxX) {
      x = maxX - spriteWidth;
      direction = 0;  // Change to left
    }
  } else {  // Moving left (direction == 0)
    x -= 1;
    // Check if hit left wall
    if (x <= minX) {
      x = minX;
      direction = 1;  // Change to right
    }
  }
}

bool GameState::isAlive() const {
  return alive;
}

int GameState::getHunger() const {
  return hunger;
}

int GameState::getPlay() const {
  return play;
}

int GameState::getRave() const {
  return rave;
}

int GameState::getX() const {
  return x;
}

int GameState::getY() const {
  return y;
}

int GameState::getDirection() const {
  return direction;
}

void GameState::setX(int newX) {
  x = newX;
}

void GameState::setY(int newY) {
  y = newY;
}

void GameState::setDirection(int newDirection) {
  direction = newDirection;
}

void GameState::checkAlive() {
  // Pet dies if any stat reaches 0
  if (hunger <= 0 || play <= 0 || rave <= 0) {
    alive = false;
  }
}
