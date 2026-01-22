#include "Game.h"

Game* Game::gameInstance = nullptr;

Game::Game(EventScheduler* scheduler, RenderAnimation* renderer) {
  eventScheduler = scheduler;
  renderPtr = renderer;
  gameInstance = this;
}

void Game::setup() {
  eventScheduler->addEvent(updateGameState, 10000);  // Update every 10 seconds
  eventScheduler->addEvent(updateDisplay, 500);     // Refresh display every 0.5 seconds
  eventScheduler->addRandomEvent(updateDirection, 2000, 10000);  // Update direction randomly every 2-10 seconds
  eventScheduler->addEvent(updateWalk, 200);  // Walk every 200ms

  // Initialize with idle state
  renderPtr->renderPet(ANIM_IDLE, state.getX(), state.getY(), state.getDirection());
  renderPtr->paint();
}

void Game::loop() {
  eventScheduler->update();
}

void Game::doFeed() {
  state.feed();
  renderPtr->playFeedAnimation(state.getX(), state.getY(), state.getDirection());
}

void Game::doPlay() {
  state.doPlay();
  renderPtr->playPlayAnimation(state.getX(), state.getY(), state.getDirection());
}

void Game::doRave() {
  state.doRave();
  renderPtr->playRaveAnimation(state.getX(), state.getY(), state.getDirection());
}

void Game::updateGameState() {
  // Check if pet just died and show death animation
  if (!gameInstance->state.isAlive()) {
    gameInstance->renderPtr->playDeathAnimation();
  }

  gameInstance->state.decay();
}

void Game::updateDirection() {
  // Don't change direction if dead
  if (!gameInstance->state.isAlive()) return;

  // Randomly flip direction: 0 = left, 1 = right
  int newDirection = random(0, 2);
  gameInstance->state.setDirection(newDirection);
}

void Game::updateWalk() {
  // Don't walk if dead
  if (!gameInstance->state.isAlive()) return;

  // Walk within the bottom partition bounds
  // Bottom partition is 84 pixels wide, sprite is 19 pixels wide
  gameInstance->state.walk(0, 84, 19);
}

void Game::updateDisplay() {
  // Don't render normal display if dead
  if (!gameInstance->state.isAlive()) {
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
