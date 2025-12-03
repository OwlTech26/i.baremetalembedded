#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led
{
  private:
    // Attribute
    byte pin;
    byte state;

  public:
    // Constructor
    Led() {} // Default constuctor, DO NOT USE -> need it for the usage the class in another class
    Led(byte pin);

    // Methods
    void init();
    void init(byte default_state); // Function overloading -> init()
    void on();
    void off();
    byte status();
    void toggle();
};

#endif /* LED_H */