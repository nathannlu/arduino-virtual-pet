#include "Display.h"
#include "Game.h"

Display display;
EventScheduler scheduler;
Game game(
  &scheduler,
  &display
);

void setup() {
  display.setup();
  game.setup();
}

void loop() {
  game.loop();
}
