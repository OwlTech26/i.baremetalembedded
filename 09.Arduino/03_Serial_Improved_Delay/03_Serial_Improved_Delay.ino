// Initialize delay
int blinkDelay_ms = 1000;

// Initialize time
unsigned long timePrev_ms = millis();

void setup()
{
  // Initialize Serial Port
  Serial.begin(115200);
  Serial.setTimeout(10);
  Serial.println("\n=== ARDUINO LED BLINK ===");
  
  // Initialize Build-in LED
  pinMode(LED_BUILTIN, OUTPUT);
}

bool is_tick(int delay_ms)
{
  bool ret_stat = false;

  if ((millis() - timePrev_ms) > delay_ms) { // Time is elapsed
    timePrev_ms += delay_ms;
    ret_stat = true;
  }

  return ret_stat;
}

void loop()
{
  // Toggle LED
  if (is_tick(blinkDelay_ms) == true) {
    Serial.println("LED ON");
    digitalWrite(LED_BUILTIN, HIGH);
  }
  if (is_tick(blinkDelay_ms) == true) {
    Serial.println("LED OFF");
    digitalWrite(LED_BUILTIN, LOW);
  }
  

  // Receive command from Serial
  if (Serial.available() > 0) { // New data is received
    // long cmd = Serial.parseInt();
    // String cmd = Serial.readString();
    int cmd = Serial.parseInt();
    if ((cmd != blinkDelay_ms) && (cmd >= 100) && (cmd <= 1000)) {
      Serial.print("New delay is set -> ");
      blinkDelay_ms = cmd;
    } else {
      Serial.print("New delay is NOT set -> ");
    }
    Serial.println(cmd);
  }

  delayMicroseconds(10);
}
