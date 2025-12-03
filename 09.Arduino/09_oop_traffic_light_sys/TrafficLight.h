#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <Arduino.h>

#include "Led.h"
#include "LedBlinker.h"

#define DIMM_VAL_MIN  (10u)
#define DIMM_VAL_MAX  (255u)

class TrafficLight
{
  private:
    Led redLed;
    Led yellowLed;
    Led greenLed;
    LedBlinker yellowLedBlinker;
    LedBlinker greenLedBlinker;

    enum trafficLightState {
      STATE_OFF          = 0,
      STATE_OUT_OF_ORDER = 1,
      STATE_RED          = 2,
      STATE_RED_YELLOW   = 3,
      STATE_GREEN        = 4,
      STATE_GREEN_BLINK  = 5,
      STATE_YELLOW       = 6,
      STATE_MAX          = 7
    };

    unsigned long timePrev_ms;
    int state_prev;
    int state;
    byte brightness;

    void init();
    bool timeTick(int delay_ms);
    void nextState(const unsigned long delay_ms);

  public:
    TrafficLight(); // Default constructor
    TrafficLight(Led &redLed, Led &yellowLed, Led &greenLed, LedBlinker &yellowLedBlinker, LedBlinker &greenLedBlinker);

    void off();
    void out_of_order();
    void on();
    byte get_dimm();
    void set_dimm(const byte dimm_val);
    void run();
};

#endif /* TRAFFIC_LIGHT_H */