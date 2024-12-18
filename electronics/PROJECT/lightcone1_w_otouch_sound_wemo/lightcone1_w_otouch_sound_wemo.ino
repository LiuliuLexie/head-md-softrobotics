// LIGHT CONE 1.0
// Wemo board
// Interactions and feedbacks:
// - When stay there without interactions, LED on, white light
// - If invert it (tilt sensor), LED off
// - If light it (Photoresistor), when sense light value > 500(indoor)/1000(sunshine), the LED turns off for 5 seconds
// no A1, no sound sensor now for wemo - If sound value > 75, LED blinks 3 times

// Pin
const int tiltPin = D2; //(GPIO4)
const int photoResistorPin = A0;
// const int soundPin = A1;
const int redPin = D6; //(GPIO12)
const int greenPin = D7; //(GPIO13)
const int bluePin = D8; //(GPIO15)

// // Variables
// const int soundThreshold = 75;
// unsigned long lastBlinkTime = 0;
// const int debounceDelay = 300;

void setup() {
  pinMode(tiltPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);  // For debugging
}

void loop() {
  // Read sensors
  int tiltState = digitalRead(tiltPin);
  int lightValue = analogRead(photoResistorPin);
  // int soundValue = analogRead(soundPin);

  // Default state: LED on, white light
  if (tiltState == LOW && lightValue <= 780) {
    setLED(255, 255, 255);  // White light
    Serial.println("State 1");
    Serial.println(lightValue);
  }

  // Interaction: Tilt sensor (invert it)
  if (tiltState == HIGH) {
    setLED(0, 0, 0);  // LED off
    Serial.println("State 2");
  }

  // Interaction: Light the sensor, If light it (Photoresistor), when sense light value > 1000, the LED turns off for 5 seconds
  if (lightValue > 780) {
    setLED(0, 0, 0);
    delay(5000);
    setLED(255, 255, 255);
    Serial.println("State 3");
    Serial.println(lightValue);
  }

  // // Interaction: Sound sensor
  // if (soundValue > soundThreshold) {
  //   unsigned long currentTime = millis();
  //   if (currentTime - lastBlinkTime > debounceDelay) {
  //     blinkLED(255, 0, 0, 3, 200); // Blink red 3 times
  //     lastBlinkTime = currentTime; // Update last blink time
  //   }
  // }
  // Serial.print("Sound Value: ");
  // Serial.println(soundValue);
}

// Set RGB LED color
void setLED(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

// // Blink LED
// void blinkLED(int red, int green, int blue, int times, int delayTime) {
//   for (int i = 0; i < times; i++) {
//     setLED(red, green, blue);
//     delay(delayTime);
//     setLED(0, 0, 0);
//     delay(delayTime);
//   }
// }
