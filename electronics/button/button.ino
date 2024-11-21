/*
  Read Joystick
  ------------
  Controls an LED based on joystick movement.
  LED is always on when joystick is moved down.
  Blinking frequency changes depending on the joystick direction.
*/

int ledPin = 13;                  // Pin for the LED
int joyPin1 = A0;                 // Joystick X-axis connected to analog pin 0
int joyPin2 = A1;                 // Joystick Y-axis connected to analog pin 1
int valueX = 0;                   // Variable for joystick X-axis
int valueY = 0;                   // Variable for joystick Y-axis
const int threshold = 100;        // Threshold for joystick idle position

void setup() {
  pinMode(ledPin, OUTPUT);        // Initialize the LED pin
  Serial.begin(9600);             // Start serial communication
}

void loop() {
  valueX = analogRead(joyPin1);   // Read X-axis
  delay(10);                      // Small delay for stable readings
  valueY = analogRead(joyPin2);   // Read Y-axis

  int freq = getBlinkFrequency(valueX, valueY);

  if (freq > 0) {
    // Blink LED with the determined frequency
    digitalWrite(ledPin, HIGH);
    delay(freq);
    digitalWrite(ledPin, LOW);
    delay(freq);
  } else if (valueY > 512 + threshold) {
    // LED is always on when joystick is moved down
    digitalWrite(ledPin, HIGH);
  } else {
    // Turn off LED when joystick is idle or in other directions
    digitalWrite(ledPin, LOW);
  }
}

// Determine blink frequency based on joystick position
int getBlinkFrequency(int x, int y) {
  const int centerX = 512;        // Center value for X-axis
  const int centerY = 512;        // Center value for Y-axis

  // Joystick is idle
  if (abs(x - centerX) < threshold && abs(y - centerY) < threshold) {
    return 0;
  }

  // Joystick moved up
  if (y < centerY - threshold) {
    return 100; // Fast blink
  }

  // Joystick moved down (LED stays on)
  if (y > centerY + threshold) {
    return 0; // LED is always on, no blinking
  }

  // Joystick moved left
  if (x < centerX - threshold) {
    return 200; // Medium blink
  }

  // Joystick moved right
  if (x > centerX + threshold) {
    return 400; // Slower blink
  }

  return 0; // Default idle state
}
