#include "Arduino.h"
#include "Led.h"

// Constructor
Led::Led(byte pin) // Functon overloading -> Led() def. const.
{
  this->pin = pin; // 'this->' refers to the class attribute
  state = LOW;
}

// Methods
void Led::init()
{
  pinMode(pin, OUTPUT);
}

void Led::init(byte default_state) // Function overloading -> init()
{
  init();

  if (default_state == HIGH) {
    on();
  } else {
    off();
  }
}

void Led::on()
{
  state = HIGH;
  digitalWrite(pin, HIGH);
}

void Led::off()
{
  state = LOW;
  digitalWrite(pin, LOW);
}

byte Led::status()
{
  return state;
}

void Led::toggle()
{
  state ^= HIGH;
  digitalWrite(pin, state);
}