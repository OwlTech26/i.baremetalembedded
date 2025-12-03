#include "ErriezDHT22.h"

// Pins definitions

#define TEMP_SENS_PIN   2 // IT pin
#define US_ECHO_PIN     3 // IT pin
#define US_TRG_PIN      4
#define REMOTE_A_PIN    5 
#define REMOTE_B_PIN    6
#define REMOTE_C_PIN    7
#define REMOTE_D_PIN    8
#define LED_PIN         12


enum {
  US_STATE_RDY  = 0,
  US_STATE_BUSY = 1,
  US_STATE_DONE = 2
} e_us_meas_state;

// Global initialization
volatile int US_meas_state = US_STATE_RDY;

volatile long US_echo_duration_us = 0;
unsigned long TIME_prev_ms = millis();
int prev_data = 0;

// Create DHT22 sensor object
double TEMP_data = 22;
double HUMIDITY_data = 60;
DHT22 dht22 = DHT22(TEMP_SENS_PIN);

void us_echo_isr()
{
  if (US_meas_state == US_STATE_RDY) { // Start of the measurement
    US_echo_duration_us = micros();
    US_meas_state = US_STATE_BUSY;
  } else { // End of measurement
    US_echo_duration_us = micros() - US_echo_duration_us;
    US_meas_state = US_STATE_DONE;
  }
}

bool is_tick(int delay_ms)
{
  bool ret_stat = false;

  if ((millis() - TIME_prev_ms) > delay_ms) { // Time is elapsed
    TIME_prev_ms += delay_ms;

    ret_stat = true;
  }

  return ret_stat;
}

int get_active_button(void)
{
  int ret_stat = 0;

  const int INPUT_DATA[] = {REMOTE_A_PIN, REMOTE_B_PIN, REMOTE_C_PIN, REMOTE_D_PIN};
  for (int i=0; i<(sizeof(INPUT_DATA)/sizeof(INPUT_DATA[0])); ++i) {
    const int curr_data = INPUT_DATA[i];
    if (digitalRead(curr_data)== HIGH) {
      ret_stat = curr_data;
      break;
    }
  }

  return ret_stat;
}

void temp_humidity_update()
{
  if (dht22.available()) {
      // Read temperature from sensor (blocking)
      const int16_t temperature = dht22.readTemperature();
      if (temperature != ~0) {
        const int16_t temp_int = temperature / 10;
        TEMP_data = (temp_int > 0) ? (double)temp_int + (double)(temperature % 10) / 10.0 : (double)temp_int - (double)(temperature % 10) / 10.0;
      }

      // Read humidity from sensor (blocking)
      int16_t humidity = dht22.readHumidity();
      if (humidity != ~0) {
        HUMIDITY_data = (double)(humidity / 10) + (double)(humidity % 10) / 10.0;
      }
  }
}

void temp_humidity_display()
{
  // Print temperature
  Serial.print(F("Temperature: "));
  Serial.print(TEMP_data);
  Serial.println(F(" *C"));

  // Print humidity
  Serial.print(F("Humidity: "));
  Serial.print(HUMIDITY_data);
  Serial.println(F(" %"));
}

void us_tx_pulse(const int pulse_duration_us)
{
  digitalWrite(US_TRG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(US_TRG_PIN, HIGH);
  delayMicroseconds(pulse_duration_us);
  digitalWrite(US_TRG_PIN, LOW);
}

double us_get_distance_cm()
{
  // distance = (duration * velocity) / 2
  // velocity = 331.4[m/s] + 0.6*temperature[°C] + 0.0124*rel_humidity[%]
  const double us_velocity = 331.4 + 0.6*TEMP_data + 0.0124*HUMIDITY_data; // in [m/s]

  const double ret_distance = ((double)US_echo_duration_us * us_velocity) / 20000.0; // m/s  --> 1/10000 cm/us

  return ret_distance;
}

void setup()
{
  // Initialize Pins
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(US_TRG_PIN, OUTPUT);
  digitalWrite(US_TRG_PIN, LOW);
  const int INPUT_DATA[] = {US_ECHO_PIN, REMOTE_A_PIN, REMOTE_B_PIN, REMOTE_C_PIN, REMOTE_D_PIN};
  for (int i=0; i<(sizeof(INPUT_DATA)/sizeof(INPUT_DATA[0])); ++i) {
    pinMode(INPUT_DATA[i], INPUT);
  }
  
  // Initialize Serial Port
  Serial.begin(115200);
  Serial.setTimeout(10);
  Serial.println("\n=== ARDUINO REMOTE INTERRUPT ===");

  // Initialize ITs
  attachInterrupt(digitalPinToInterrupt(US_ECHO_PIN), us_echo_isr, CHANGE);
}

void loop()
{
  const int curr_data = get_active_button();

  if ((curr_data != 0) && (curr_data != prev_data) && (is_tick(100) == true)) {
    switch (curr_data) {
       case REMOTE_A_PIN:
        us_tx_pulse(10);
        break;
      case REMOTE_B_PIN:
        temp_humidity_display();
        break;
      case REMOTE_C_PIN:
      case REMOTE_D_PIN:
        const char button_type = 'A' - REMOTE_A_PIN + curr_data;
        Serial.print("Mode '");
        Serial.print(button_type);
        Serial.println("' is active.");
        break;
      default:
        Serial.println("REMOTE CONTROLLER ERROR");
        break;
    }
    prev_data = curr_data;
  }

  temp_humidity_update();

  if (US_meas_state == US_STATE_DONE) {
    Serial.print("Distance [cm]: ");
    Serial.println(us_get_distance_cm());
    US_meas_state = US_STATE_RDY;
  }
}
