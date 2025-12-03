#include "TrafficLight.h"

#define DEFAULT_BRIGHTNESS_DIMM (255)
#define STATE_DELAY_RED_MS      (5000u)
#define STATE_DELAY_CHANGE_MS   (3000u)
#define STATE_DELAY_GREEN_MS    (5000u)
#define BLINK_DELAY_MS          (500u)

// === Private ===
void TrafficLight::init()
{
  redLed.init(LOW);
  yellowLed.init(LOW);
  greenLed.init(LOW);
  yellowLedBlinker.blinkDelaySet(BLINK_DELAY_MS);
  greenLedBlinker.blinkDelaySet(BLINK_DELAY_MS);
  state = STATE_OFF;
  brightness = DEFAULT_BRIGHTNESS_DIMM;
}

bool TrafficLight::timeTick(int delay_ms)
{
  bool ret_stat = false;

  if ((millis() - timePrev_ms) > delay_ms) { // Time is elapsed
    timePrev_ms = millis();

    ret_stat = true;
  }

  return ret_stat;
}

void TrafficLight::nextState(const unsigned long delay_ms)
{
  if (timeTick(delay_ms) != false) {
    if (state < STATE_YELLOW) {
      state++;
    } else {
      state = STATE_RED;
    }
  }
}

// === Public ===
// Constructor
TrafficLight::TrafficLight(Led &redLed, Led &yellowLed, Led &greenLed, LedBlinker &yellowLedBlinker, LedBlinker &greenLedBlinker)
{
  this->redLed = redLed;
  this->yellowLed = yellowLed;
  this->greenLed = greenLed;
  this->yellowLedBlinker = yellowLedBlinker;
  this->greenLedBlinker = greenLedBlinker;

  init();
}


void TrafficLight::off()
{
  state      = STATE_OFF;
  redLed.off();
  yellowLed.off();
  greenLed.off();
}

void TrafficLight::out_of_order()
{
  state      = STATE_OUT_OF_ORDER;
  redLed.off();
  greenLed.off();
}

void TrafficLight::on()
{
  state = STATE_RED;
}

byte TrafficLight::get_dimm()
{
  return brightness;
}

void TrafficLight::set_dimm(const byte dimm_val)
{
  brightness = dimm_val;
}

void TrafficLight::run()
{
  const bool b_state_updated = (state == state_prev) ? false : true;
  if (b_state_updated != false) {
    state_prev = state;
    timePrev_ms = millis();
  }

  switch (state) {
    case STATE_OUT_OF_ORDER:
      yellowLedBlinker.blinkLed(brightness);
      break;
    case STATE_RED:
      nextState(STATE_DELAY_RED_MS);
      if (b_state_updated != false) {
        redLed.on(brightness);
        yellowLed.off();
      }
      break;
    case STATE_RED_YELLOW:
      nextState(STATE_DELAY_CHANGE_MS);
      if (b_state_updated != false) {
        yellowLed.on(brightness);
      }
      break;
    case STATE_GREEN:
      nextState(STATE_DELAY_GREEN_MS);
      if (b_state_updated != false) {
        redLed.off();
        yellowLed.off();
        greenLed.on(brightness);
      }
      break;
    case STATE_GREEN_BLINK:
      greenLedBlinker.blinkLed(brightness);
      nextState(STATE_DELAY_CHANGE_MS);
      break;
    case STATE_YELLOW:
      nextState(STATE_DELAY_CHANGE_MS);
      if (b_state_updated != false) {
        yellowLed.on(brightness);
        greenLed.off();
      }
      break;
    case STATE_OFF:
    default:
      // NOP
      break;
  }
}
