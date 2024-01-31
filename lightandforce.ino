// code voor de esp met de daglichtsensor, force sensor en de verlichting

#define LIGHT_SENSOR_PIN  25  // ESP32 pin GPIO36 (ADC0) connected to light sensor
#define LED_PIN           33  // ESP32 pin GPIO22 connected to LED
#define ANALOG_THRESHOLD  500

void setup() {
  pinMode(LED_PIN, OUTPUT); // set ESP32 pin to output mode
}

void loop() {
  int analogValue = analogRead(LIGHT_SENSOR_PIN); // read the value on analog pin

  if (analogValue < ANALOG_THRESHOLD)
    digitalWrite(LED_PIN, HIGH); // turn on LED
  else
    digitalWrite(LED_PIN, LOW);  // turn off LED
}