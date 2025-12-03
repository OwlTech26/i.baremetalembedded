#include "Led.h"
#include "LedBlinker.h"

#define LED_RED_PIN    5
#define LED_YELLOW_PIN 6
#define LED_GREEN_PIN  9

Led redLed(LED_RED_PIN);
Led greenLed(LED_GREEN_PIN);
Led yellowLed(LED_YELLOW_PIN);
LedBlinker yellowLedBlink(yellowLed);

// Initialize time
unsigned long timePrev_ms = millis();
unsigned long toggleDelay_ms = 500;

bool is_tick(int delay_ms)
{
  bool ret_stat = false;

  if ((millis() - timePrev_ms) > delay_ms) { // Time is elapsed
    timePrev_ms = millis();

    ret_stat = true;
  }

  return ret_stat;
}

void setup() {
  // Initalize LEDs
  redLed.init(LOW);
  greenLed.init(LOW);
  yellowLed.init(LOW);
  yellowLedBlink.initLed(LOW);

  // Initialize Serial Port
  Serial.begin(115200);
  Serial.setTimeout(10);
  Serial.println("\n=== ARDUINO LED OOP ===");
  Serial.print(">> cmd: ");
}

void loop() {
  // Receive command from Serial
  if (Serial.available() > 0) { // New data is received
    // long cmd = Serial.parseInt();
    // String cmd = Serial.readString();
    int cmd = Serial.parseInt();
    Serial.println(cmd);
    if (cmd == 1) {
      greenLed.toggle();
      Serial.println((greenLed.status() != LOW) ? "LED is ON." : "LED is OFF.");
    } else if (cmd == 2) {
      Serial.print("Toggle Delays (main, class) [ms]: ");
      Serial.print(toggleDelay_ms);
      Serial.print(", ");
      Serial.println(yellowLedBlink.blinkDelayGet());
    } else if ((cmd >= 100) && (cmd <= 1000)) {
      yellowLedBlink.blinkDelaySet(cmd);
      Serial.print("New class Delay [ms]: ");
      Serial.println(yellowLedBlink.blinkDelayGet());
    }
    else {
      Serial.print("Invalid command, cmd: ");
      Serial.println(cmd);
    }
    Serial.print(">> cmd: ");
  }

  if (is_tick(toggleDelay_ms) == true) {
    redLed.toggle();
  }

  yellowLedBlink.blinkLed();
}
