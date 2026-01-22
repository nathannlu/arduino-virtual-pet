#include "EventScheduler.h"

EventScheduler::EventScheduler() {
}

void EventScheduler::addEvent(
  CallbackFunction cb,
  unsigned long intervalMs
) {
  if (entry_count >= MAX_EVENTS) {
    return;
  }

  // store our event
  events[entry_count].callback = cb;
  events[entry_count].interval = intervalMs;
  events[entry_count].lastRun = millis();

  entry_count++;
}

void EventScheduler::update() {
  unsigned long now = millis();

  for (int i = 0; i < entry_count; i++) {
    if (now - events[i].lastRun >= events[i].interval) {
      events[i].callback();
      events[i].lastRun = now;
    }
  }
}
