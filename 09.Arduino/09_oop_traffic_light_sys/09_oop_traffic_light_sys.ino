#include "Led.h"
#include "LedBlinker.h"
#include "TrafficLight.h"

#define CMD_TRAFFIC_LIGHT_ON            1
#define CMD_TRAFFIC_LIGHT_OUT_OF_ORDER  2
#define CMD_TRAFFIC_LIGHT_OFF           3

#define LED_RED_PIN    6
#define LED_YELLOW_PIN 5
#define LED_GREEN_PIN  9

Led redLed(LED_RED_PIN);
Led yellowLed(LED_YELLOW_PIN);
Led greenLed(LED_GREEN_PIN);
LedBlinker yellowLedBlink(yellowLed);
LedBlinker greenLedBlink(greenLed);
TrafficLight trafficLight(redLed, yellowLed, greenLed, yellowLedBlink, greenLedBlink);

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
  yellowLed.init(LOW);
  greenLed.init(LOW);
  yellowLedBlink.initLed(LOW);
  greenLedBlink.initLed(LOW);

  // Initialize Serial Port
  Serial.begin(115200);
  Serial.setTimeout(10);
  Serial.println("\n=== ARDUINO LED OOP ===");
  Serial.print(">> cmd: ");

  // Initalize Traffic Light
  trafficLight.out_of_order();
}

void loop() {
  // Receive command from Serial
  if (Serial.available() > 0) { // New data is received
    // int cmd = Serial.parseInt();
    String cmd_str = Serial.readString();
    cmd_str.trim();
    int cmd = cmd_str.toInt();
    Serial.println(cmd);
    if (cmd == CMD_TRAFFIC_LIGHT_ON) {
      trafficLight.on();
      Serial.println("Traffic Light ON.");
    } else if (cmd == CMD_TRAFFIC_LIGHT_OUT_OF_ORDER) {
      trafficLight.out_of_order();
      Serial.println("Traffic Light OUT OF ORDER.");
    } else if (cmd == CMD_TRAFFIC_LIGHT_OFF) {
      trafficLight.off();
      Serial.println("Traffic Light OFF.");
    }
    else if ((cmd >= DIMM_VAL_MIN) && (cmd <= DIMM_VAL_MAX)) {
      trafficLight.set_dimm(cmd);
      Serial.print("Lumen dimming: ");
      Serial.println(cmd);
    }
    else {
      Serial.print("Invalid command, cmd: ");
      Serial.println(cmd);
    }
    Serial.print(">> cmd: ");
  }

  trafficLight.run();
}
