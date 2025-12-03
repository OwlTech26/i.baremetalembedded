void setup()
{
  // Initialize Serial Port
  Serial.begin(9600);
  Serial.println("\n=== ARDUINO LED BLINK ===");
  // Initialize Build-in LED
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  // Toggle LED
  Serial.println("LED ON");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  Serial.println("LED OFF");
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}
