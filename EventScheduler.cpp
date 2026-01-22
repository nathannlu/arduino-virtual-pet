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
  events[entry_count].type = FIXED_INTERVAL;
  events[entry_count].callback = cb;
  events[entry_count].lastRun = millis();

  // interval
  events[entry_count].fixed.interval = intervalMs;

  entry_count++;
}

void EventScheduler::addRandomEvent(
  CallbackFunction cb,
  unsigned long minIntervalMs,
  unsigned long maxIntervalMs
) {
  if (entry_count >= MAX_EVENTS) {
    return;
  }

  // store our event
  events[entry_count].type = RANDOM_INTERVAL;
  events[entry_count].callback = cb;
  events[entry_count].lastRun = millis();

  // random interval
  events[entry_count].random.minInterval = minIntervalMs;
  events[entry_count].random.maxInterval = maxIntervalMs;
  events[entry_count].random.currentInterval = random(minIntervalMs, maxIntervalMs + 1);

  entry_count++;
}

void EventScheduler::update() {
  unsigned long now = millis();

  for (int i = 0; i < entry_count; i++) {
    unsigned long interval;

    // Get the interval based on event type
    if (events[i].type == FIXED_INTERVAL) {
      interval = events[i].fixed.interval;
    } else { 
      interval = events[i].random.currentInterval;
    }

    if (now - events[i].lastRun >= interval) {
      events[i].callback();
      events[i].lastRun = now;


      // HANDLE RANDOM INTERVAL EVENT
      // if this is a random event, pick a new random interval for next time
      if (events[i].type == RANDOM_INTERVAL) {
        events[i].random.currentInterval = random(
          events[i].random.minInterval,
          events[i].random.maxInterval + 1
        );
      }
    }
  }
}
