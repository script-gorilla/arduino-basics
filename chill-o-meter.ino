// Analog pin connected to the temperature sensor output
const int sensorPin = A0;

// Baseline temperature (in °C) used as a reference for LED thresholds
const float baselineTemp = 28.0;

void setup() {
  // Initialize serial communication at 9600 baud
  // This allows data to be sent to the Serial Monitor for debugging
  Serial.begin(9600);

  // Configure digital pins 2, 3, and 4 as outputs for LEDs
  for (int pinNumber = 2; pinNumber < 5; pinNumber++) {
    pinMode(pinNumber, OUTPUT);   // Set pin as output
    digitalWrite(pinNumber, LOW); // Ensure LED is off at startup
  }
}

void loop() {
  // Read the analog value from the temperature sensor (0–1023)
  int sensorVal = analogRead(sensorPin);

  // Print the raw sensor value to the Serial Monitor
  Serial.print("Sensor Value: ");
  Serial.print(sensorVal);

  // Convert the analog reading to voltage
  // 1024 steps over a 5V reference
  float voltage = (sensorVal / 1024.0) * 5.0;

  // Print the calculated voltage
  Serial.print(", Volts: ");
  Serial.print(voltage);

  // Convert voltage to temperature in Celsius
  // Assumes a TMP36-style sensor:
  // 0.5V offset and 10mV per degree Celsius
  float temperature = (voltage - 0.5) * 100;

  // Print the temperature value
  Serial.print(", degrees C: ");
  Serial.println(temperature);

  // Compare temperature to baseline and control LEDs accordingly

  // Temperature is close to baseline → all LEDs off
  if (temperature < baselineTemp + 2) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);

  // Slightly warmer → first LED on
  } else if (temperature >= baselineTemp + 2 && temperature < baselineTemp + 4) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);

  // Warmer → first two LEDs on
  } else if (temperature >= baselineTemp + 4 && temperature < baselineTemp + 6) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);

  // Hot → all LEDs on
  } else if (temperature >= baselineTemp + 6) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }

  // Small delay to stabilize readings and avoid spamming the Serial Monitor
  delay(1);
}

