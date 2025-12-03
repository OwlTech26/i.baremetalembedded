// Initialize delay
int blinkDelay_ms = 1000;

void setup()
{
  // Initialize Serial Port
  Serial.begin(115200);
  Serial.setTimeout(10);
  Serial.println("\n=== ARDUINO LED BLINK ===");
  // Initialize Build-in LED
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  // Toggle LED
  Serial.println("LED ON");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(blinkDelay_ms); // Wait for 1000 millisecond(s)
  Serial.println("LED OFF");
  digitalWrite(LED_BUILTIN, LOW);
  delay(blinkDelay_ms); // Wait for 1000 millisecond(s)

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
}
