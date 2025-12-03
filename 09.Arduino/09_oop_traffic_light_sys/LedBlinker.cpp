#include "Arduino.h"
#include "LedBlinker.h"

#define DEFAULT_BLINK_DELAY_MS   (500u)

// Private Methods

// Public Methods
LedBlinker::LedBlinker(Led &led)
{
  this->led = led;
  timePrev_ms = millis();
  blinkDelay_ms = DEFAULT_BLINK_DELAY_MS;
}

LedBlinker::LedBlinker(Led &led, unsigned long blinkDelay_ms)
{
  this->led = led;
  timePrev_ms = millis();
  this->blinkDelay_ms = blinkDelay_ms;
}

void LedBlinker::initLed(byte default_state)
{
  led.init(default_state);
}

void LedBlinker::blinkLed()
{
  unsigned long timeNow = millis();
  if ((timeNow - timePrev_ms) > blinkDelay_ms) { // Time is elapsed
    timePrev_ms = timeNow;
    led.toggle();
  }
}

void LedBlinker::blinkLed(const byte dimm_val)
{
  unsigned long timeNow = millis();
  if ((timeNow - timePrev_ms) > blinkDelay_ms) { // Time is elapsed
    timePrev_ms = timeNow;
    led.toggle(dimm_val);
  }
}

unsigned long LedBlinker::blinkDelayGet()
{
  return blinkDelay_ms;
}

void LedBlinker::blinkDelaySet(unsigned long blinkDelay_ms)
{
  this->blinkDelay_ms = blinkDelay_ms;
}