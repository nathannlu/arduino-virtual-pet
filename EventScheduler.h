#ifndef EVENTSCHEDULER_H
#define EVENTSCHEDULER_H

#include <Arduino.h>

// our callbacks are void functions
using CallbackFunction = void(*)();

// a callback event's state
struct Event {
  CallbackFunction callback;
  unsigned long interval;
  unsigned long lastRun;
};

// handle running events every
// t seconds
class EventScheduler {

  private:
    static const int MAX_EVENTS = 5;
    Event events[MAX_EVENTS];
    int entry_count = 0;

  public:
    EventScheduler();

    void addEvent(
      CallbackFunction cb,
      unsigned long intervalMs
    );

    void update();
};

#endif
