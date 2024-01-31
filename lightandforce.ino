#define LIGHT_SENSOR_PIN  25  // ESP32 pin GPIO25 connected to light sensor
#define FORCE_SENSOR_PIN  13  // ESP32 pin GPIO13 connected to force sensor
#define LED_PIN           33  // ESP32 pin GPIO33 connected to LED
#define ANALOG_THRESHOLD  500
#define FORCE_THRESHOLD   500 // Threshold for force detection
#define TIMEOUT           5000 // 5 seconds in milliseconds

bool isDark = false;
unsigned long forceBelowThresholdTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(FORCE_SENSOR_PIN, INPUT);
  pinMode(LIGHT_SENSOR_PIN, INPUT);
}

void loop() {
  int lightValue = analogRead(LIGHT_SENSOR_PIN);
  int forceValue = analogRead(FORCE_SENSOR_PIN);

  // Determine if it's dark
  isDark = lightValue < ANALOG_THRESHOLD;

  // Check if force is below threshold
  if (forceValue < FORCE_THRESHOLD) {
    if (forceBelowThresholdTime == 0) {
      // Start the timer
      forceBelowThresholdTime = millis();
    } else if (millis() - forceBelowThresholdTime >= TIMEOUT) {
      // Turn off the LED after 5 seconds of low force
      digitalWrite(LED_PIN, LOW);
    }
  } else {
    // Reset timer
    forceBelowThresholdTime = 0;

    if (isDark && forceValue >= FORCE_THRESHOLD) {
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
  }

  Serial.print("Light Value = ");
  Serial.print(lightValue);
  Serial.print(", Force Value = ");
  Serial.println(forceValue);

  delay(250);
}
