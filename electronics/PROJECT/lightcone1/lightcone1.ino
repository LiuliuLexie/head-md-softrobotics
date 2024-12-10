//LIGHT CONE 1.0

//interactions and feedbacks:
// when stay there without interactions, LED on, white light;
// if invert it (tilt sensor), led off;
// if light it (Photoresistor), when sense light value>500, the led fade out, 5 seconds, fade in again;
// if touch it (touch sensor), the led blinks;
// if being touched quickly(5 times), the led blinks in different color;
// if hearing sound, led get brighter with the volume gets louder;



// Pin
const int tiltPin = 2;          // Tilt sensor digital pin
const int photoResistorPin = A0; // Photoresistor analog pin
const int touchPin = 3;         // Touch sensor digital pin
const int soundPin = A1;        // Sound sensor analog pin
const int redPin = 11;           // RGB LED red channel
const int greenPin = 10;        // RGB LED green channel
const int bluePin = 9;         // RGB LED blue channel

// Variables for state tracking
int touchCount = 0;
unsigned long lastTouchTime = 0;
bool isTouchedQuickly = false;   // quick touch detection

void setup() {
  pinMode(tiltPin, INPUT);
  pinMode(touchPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600); 
}

void loop() {
  // Read sensors
  int tiltState = digitalRead(tiltPin);
  int lightValue = analogRead(photoResistorPin);
  int touchState = digitalRead(touchPin);
  int soundValue = analogRead(soundPin);

  // Default state: LED on, white light
  if (tiltState == LOW && touchState == LOW && lightValue <= 500) {
    setLED(255, 255, 255); // White light
  }

  // Interaction: Tilt sensor (invert it)
  if (tiltState == HIGH) {
    setLED(0, 0, 0); // LED off
  }

  // Interaction: Light the sensor
  if (lightValue > 500) {
    fadeLED(0, 0, 0, 5000);  // Fade out to black in 5 seconds
    delay(100);
    fadeLED(255, 255, 255, 5000);  // Fade back to white
  }

  // Interaction: Touch sensor
  if (touchState == HIGH) {
    blinkLED(255, 0, 0, 3, 200); // Blink red 3 times

    // Quick touch detection
    unsigned long currentTime = millis();
    if (currentTime - lastTouchTime < 500) { // Within 500ms window
      touchCount++;
    } else {
      touchCount = 1; // Reset if too slow
    }
    lastTouchTime = currentTime;

    if (touchCount >= 5) {
      isTouchedQuickly = true;
      touchCount = 0; // Reset count
    }
  }

  if (isTouchedQuickly) {
    blinkLED(0, 0, 255, 5, 150); // Blink blue 5 times
    isTouchedQuickly = false;    // Reset flag
  }

  // Interaction: Sound sensor
  int brightness = map(soundValue, 0, 1023, 0, 255);
  setLED(brightness, brightness, brightness); // Adjust brightness
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

  int steps = 50; // Number of steps for smooth fading
  int stepDelay = duration / steps;

  for (int i = 0; i <= steps; i++) {
    int redValue = currentRed + (targetRed - currentRed) * i / steps;
    int greenValue = currentGreen + (targetGreen - currentGreen) * i / steps;
    int blueValue = currentBlue + (targetBlue - currentBlue) * i / steps;

    setLED(redValue, greenValue, blueValue);
    delay(stepDelay);
  }
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
