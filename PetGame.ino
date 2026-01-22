#include "Display.h"
#include "Game.h"

#define BUTTON_FEED 10
#define BUTTON_PLAY 11
#define BUTTON_RAVE 12

Display display;
EventScheduler scheduler;
Game game(
  &scheduler,
  &display
);

void setup() {
  // Setup buttons as inputs with pull-up resistors
  pinMode(BUTTON_FEED, INPUT_PULLUP);
  pinMode(BUTTON_PLAY, INPUT_PULLUP);
  pinMode(BUTTON_RAVE, INPUT_PULLUP);

  display.setup();
  game.setup();
}

void loop() {
  // Check button presses (LOW = pressed when using INPUT_PULLUP)
  if (digitalRead(BUTTON_FEED) == LOW) {
    game.doFeed();
    delay(200);  // Simple debounce
  }

  if (digitalRead(BUTTON_PLAY) == LOW) {
    game.doPlay();
    delay(200);  // Simple debounce
  }

  if (digitalRead(BUTTON_RAVE) == LOW) {
    game.doRave();
    delay(200);  // Simple debounce
  }

  game.loop();
}
