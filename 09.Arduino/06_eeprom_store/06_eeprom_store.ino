#include <EEPROM.h>

#define ROM_SIZE_BYTES   1024 // Max. 100k write operations only -> default settings

// Initialize time
unsigned long timePrev_ms = millis();

bool is_tick(int delay_ms)
{
  bool ret_stat = false;

  if ((millis() - timePrev_ms) > delay_ms) { // Time is elapsed
    timePrev_ms += delay_ms;
    ret_stat = true;
  }

  return ret_stat;
}

void setup() {
  EEPROM.write(0, 44);
  EEPROM.write(200, 150);

  // Initialize Serial Port
  Serial.begin(115200);
  Serial.setTimeout(10);
  Serial.println("\n=== ARDUINO EEPROM ACCESS ===");
}

void loop() {
  // Receive command from Serial
  if ((Serial.available() > 0) && (is_tick(100) == true)) { // New data is received
    // long cmd = Serial.parseInt();
    // String cmd = Serial.readString();
    int cmd = Serial.parseInt();
    if ((cmd >= 0) && (cmd < ROM_SIZE_BYTES)) {
      Serial.print("Reading from [");
      Serial.print(cmd);
      Serial.print("] = ");
      Serial.println(EEPROM.read(cmd));
    } else {
      Serial.print("Address is out of bounds: ");
      Serial.println(cmd);
    }
  }
}
