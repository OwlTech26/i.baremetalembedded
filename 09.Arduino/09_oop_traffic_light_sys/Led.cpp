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

  state = default_state;
  digitalWrite(pin, state);
}

void Led::on()
{
  state = HIGH;
  digitalWrite(pin, HIGH);
}

void Led::on(const byte brightness)
{
  state = HIGH;
  analogWrite(pin, brightness);
}

void Led::off()
{
  state = LOW;
  digitalWrite(pin, LOW);
}

byte Led::get_status()
{
  return state;
}

byte Led::get_io_status()
{
  return digitalRead(pin);
}

byte Led::get_io_dimm_status()
{
  return analogRead(pin);
}

void Led::toggle()
{
  state ^= HIGH;
  digitalWrite(pin, state);
}

void Led::toggle(const byte dimm_val)
{
  state ^= HIGH;
  if (state == HIGH) {
    on(dimm_val);
  } else {
    off();
  }
}