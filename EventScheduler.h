#ifndef EVENTSCHEDULER_H
#define EVENTSCHEDULER_H

#include <Arduino.h>

// our callbacks are void functions
using CallbackFunction = void(*)();

enum EventType {
  FIXED_INTERVAL,
  RANDOM_INTERVAL
};

struct FixedIntervalEvent {
  unsigned long interval;
};

struct RandomIntervalEvent {
  unsigned long minInterval;
  unsigned long maxInterval;
  unsigned long currentInterval;
};

// a callback event's state
struct Event {
  EventType type;
  CallbackFunction callback;
  unsigned long lastRun;

  union {
    FixedIntervalEvent fixed;
    RandomIntervalEvent random;
  };
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

    void addRandomEvent(
      CallbackFunction cb,
      unsigned long minIntervalMs,
      unsigned long maxIntervalMs
    );

    void update();
};

#endif
