const int potPin = A0;
int potVal;
int angle;

void setup() {
  // Use 12-bit ADC resolution (required for boards like Arduino R4)
  analogReadResolution(12);

  // Attach the servo to PWM pin 9
  myServo.attach(9);

  // Serial used only for monitoring/debugging values
  Serial.begin(9600);
}

void loop() {
  // Read potentiometer (0–4095 with 12-bit resolution)
  potVal = analogRead(potPin);

  // Convert potentiometer range to safe servo angle range
  angle = map(potVal, 0, 4095, 0, 179);

  // Command servo position
  myServo.write(angle);

  // Short delay prevents servo jitter and over-updating
  delay(15);
}
