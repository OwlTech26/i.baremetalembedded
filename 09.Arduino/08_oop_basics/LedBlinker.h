#ifndef LED_BLINKER_H
#define LED_BLINKER_H

#include "Led.h"

class LedBlinker
{
  private:
    // Members
    Led led; // Led class inside the LedBlinker class as an object
    unsigned long timePrev_ms;
    unsigned long blinkDelay_ms;

    // Methods
    void toggleLed();

  public:
    // Contructor
    LedBlinker() {}
    LedBlinker(Led &led); // Take the reference of the object, otherwise a new instance will be created as a copy
    LedBlinker(Led &led, unsigned long blinkDelay_ms);

    void initLed(byte default_state);
    void blinkLed();
    unsigned long blinkDelayGet();
    void blinkDelaySet(unsigned long blinkDelay_ms);
};


#endif /* LED_BLINKER_H */