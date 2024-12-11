//LIGHT CONE 1.0

//interactions and feedbacks:
// when stay there without interactions, LED on, white light;
// if invert it (tilt sensor), led off;
// if light it (Photoresistor), when sense light value>500, the led fade out, 5 seconds, fade in again;

// Pin
const int tiltPin = 2;            // Tilt sensor digital pin
const int photoResistorPin = A0;  // Photoresistor analog pin
const int redPin = 11;            // RGB LED red channel
const int greenPin = 10;          // RGB LED green channel
const int bluePin = 9;            // RGB LED blue channel

void setup() {
  pinMode(tiltPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Read sensors
  int tiltState = digitalRead(tiltPin);
  int lightValue = analogRead(photoResistorPin);

  // Default state: LED on, white light
  if (tiltState == LOW && lightValue <= 500) {
    setLED(255, 255, 255);  // White light
  }

  // Interaction: Tilt sensor (invert it)
  if (tiltState == HIGH) {
    setLED(0, 0, 0);  // LED off
  }

  // Interaction: Light the sensor
  Serial.println(lightValue);
  if (lightValue > 500) {
    setLED(0, 0, 0);        // Turn off the LED
    delay(5000);            // Wait for 5 seconds
    setLED(255, 255, 255);  // Turn LED back to white
  }
}

// Helper Function: Set RGB LED color
void setLED(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

// Helper Function: Fade LED
void fadeLED(int targetRed, int targetGreen, int targetBlue, int duration) {
  int currentRed = analogRead(redPin);
  int currentGreen = analogRead(greenPin);
  int currentBlue = analogRead(bluePin);

  int steps = 50;  // Number of steps for smooth fading
  int stepDelay = duration / steps;

  for (int i = 0; i <= steps; i++) {
    int redValue = currentRed + (targetRed - currentRed) * i / steps;
    int greenValue = currentGreen + (targetGreen - currentGreen) * i / steps;
    int blueValue = currentBlue + (targetBlue - currentBlue) * i / steps;

    setLED(redValue, greenValue, blueValue);
    delay(stepDelay);
  }
}
