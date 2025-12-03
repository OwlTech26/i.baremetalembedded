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
    void on(const byte brightness);
    void off();
    byte get_status();
    byte get_io_status();
    byte get_io_dimm_status();
    void toggle();
    void toggle(const byte dimm_val);
};

#endif /* LED_H */