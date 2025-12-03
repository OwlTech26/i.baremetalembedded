// Pins definitions
#define LED_PIN   12
#define DATA_A    2 // IT pin
#define DATA_B    3 // IT pin
#define DATA_C    4
#define DATA_D    5

// Global initialization
volatile bool irq_1_state = false;
volatile bool irq_2_state = false;
unsigned long timePrev_ms = millis();
int prev_data = 0;

void irq_1_handle()
{
  irq_1_state = true;
}

void irq_2_handle()
{
  irq_2_state = true;
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

int get_active_button(void)
{
  int ret_stat = 0;

  const int INPUT_DATA[] = {DATA_A, DATA_B, DATA_C, DATA_D};
  for (int i=0; i<(sizeof(INPUT_DATA)/sizeof(INPUT_DATA[0])); ++i) {
    const int curr_data = INPUT_DATA[i];
    if (digitalRead(curr_data)== HIGH) {
      ret_stat = curr_data;
      break;
    }
  }

  return ret_stat;
}

void remote_led_control()
{
  if (irq_1_state == true) {
    Serial.println("LED ON");
    digitalWrite(LED_PIN, HIGH);
    irq_1_state = false;
  } else if (irq_2_state == true) {
    Serial.println("LED OFF");
    digitalWrite(LED_PIN, LOW);
    irq_2_state = false;
  } else { // NO IT
    const int curr_data = get_active_button();

    if ((curr_data != 0) && (curr_data != prev_data) && (is_tick(10) == true)) {
      const char button_type = 'A' - DATA_A + curr_data;
      Serial.print("Mode '");
      Serial.print(button_type);
      Serial.println("' is active.");
      prev_data = curr_data;
    }
  }
}

void setup() {
  // Initialize Pins
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  const int INPUT_DATA[] = {DATA_A, DATA_B, DATA_C, DATA_D};
  for (int i=0; i<(sizeof(INPUT_DATA)/sizeof(INPUT_DATA[0])); ++i) {
    pinMode(INPUT_DATA[i], INPUT);
  }
  
  // Initialize Serial Port
  Serial.begin(115200);
  Serial.setTimeout(10);
  Serial.println("\n=== ARDUINO REMOTE INTERRUPT ===");

  // Initialize ITs
  attachInterrupt(digitalPinToInterrupt(DATA_A), irq_1_handle, RISING);
  attachInterrupt(digitalPinToInterrupt(DATA_B), irq_2_handle, RISING);
}

void loop() {
  remote_led_control();

  
}
