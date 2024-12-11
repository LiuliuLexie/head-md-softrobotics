// LIGHT CONE 1.0

// Interactions and feedbacks:
// - When stay there without interactions, LED on, white light
// - If invert it (tilt sensor), LED off
// - If light it (Photoresistor), when sense light value > 500, the LED turns off for 5 seconds
// - If sound value > 75, LED blinks 3 times

// Pin
const int tiltPin = 2;           // Tilt sensor digital pin
const int photoResistorPin = A0; // Photoresistor analog pin
const int soundPin = A1;         // Sound sensor analog pin
const int redPin = 11;           // RGB LED red channel
const int greenPin = 10;         // RGB LED green channel
const int bluePin = 9;           // RGB LED blue channel

// Variables
const int soundThreshold = 75;  // Sound value threshold
unsigned long lastBlinkTime = 0; // Time of the last blink to avoid rapid re-triggering
const int debounceDelay = 300;  // Debounce delay for consecutive sound events

void setup() {
  pinMode(tiltPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600); // For debugging
}

void loop() {
  // Read sensors
  int tiltState = digitalRead(tiltPin);
  int lightValue = analogRead(photoResistorPin);
  int soundValue = analogRead(soundPin);

  // Debugging: Print sound sensor value to Serial Monitor
  Serial.print("Sound Value: ");
  Serial.println(soundValue);

  // Default state: LED on, white light
  if (tiltState == LOW && lightValue <= 500) {
    setLED(255, 255, 255); // White light
  }

  // Interaction: Tilt sensor (invert it)
  if (tiltState == HIGH) {
    setLED(0, 0, 0); // LED off
  }

  // Interaction: Light the sensor
  if (lightValue > 500) {
    setLED(0, 0, 0); // Turn off the LED
    delay(5000);     // Wait for 5 seconds
    setLED(255, 255, 255); // Turn LED back to white
  }

  // Interaction: Sound sensor
  if (soundValue > soundThreshold) {
    unsigned long currentTime = millis();
    if (currentTime - lastBlinkTime > debounceDelay) {
      blinkLED(255, 0, 0, 3, 200); // Blink red 3 times
      lastBlinkTime = currentTime; // Update last blink time
    }
  }
}

// Helper Function: Set RGB LED color
void setLED(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

// Helper Function: Blink LED
void blinkLED(int red, int green, int blue, int times, int delayTime) {
  for (int i = 0; i < times; i++) {
    setLED(red, green, blue);
    delay(delayTime);
    setLED(0, 0, 0);
    delay(delayTime);
  }
}
