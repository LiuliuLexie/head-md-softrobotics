// LIGHT CONE 1.1
// Wemo board
// Interactions and feedbacks:
// - When stay there without interactions, LED on, white light,  but with a random blink at random time, for example, every random(10,30) seconds, it blinks random(1,5) times
// - If invert it (tilt sensor), LED randomly gives feedback1: LED off or feedback2: blue-to-red gradient
// - If light it (Photoresistor), when sense light value > 450, the LED randomly turns feedback 3: rainbow color change or feedback4:LED off for 5 seconds

// Pin
const int tiltPin = D2;  //(GPIO4)
const int photoResistorPin = A0;
// const int soundPin = A1;
const int redPin = D6;    //(GPIO12)
const int greenPin = D7;  //(GPIO13)
const int bluePin = D8;   //(GPIO15)

// Variables
unsigned long lastBlinkTime = 0;
unsigned long nextBlinkInterval = random(10000, 30000);  //random interval for blink
unsigned long lastLightTime = 0;
const int lightCooldown = 5000;

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
  unsigned long currentTime = millis();

  // Default state: LED on, white light with random blinking
  if (tiltState == LOW && lightValue <= 750) {
    setLED(255, 255, 255);
    Serial.println("State 1");
    Serial.println(lightValue);

    // Random Blink at Random Interval
    if (currentTime - lastBlinkTime > nextBlinkInterval) {
      int blinkTimes = random(1, 6);             // Random blink 1-5 times
      blinkLED(255, 255, 255, blinkTimes, 100);  // Blink white light
      lastBlinkTime = currentTime;
      nextBlinkInterval = random(10000, 30000);  // Set next random interval
    }
  }

  // Interaction: Tilt sensor / ball switch (invert it)
  if (tiltState == HIGH) {
    int feedback = random(0, 2);  // Randomly choose feedback1 or feedback2
    if (feedback == 0) {
      setLED(0, 0, 0);
      Serial.println("State 2: Feedback 1 - LED Off");
    } else {
      gradientBlueToRed();
      Serial.println("State 2: Feedback 2 - Blue to Red Gradient");
    }
  }

  // Interaction: Light the sensor
  if (lightValue > 750 && (currentTime - lastLightTime > lightCooldown)) {
    Serial.println(lightValue);
    int feedback = random(0, 2); 
    if (feedback == 0) {
      rainbowEffect(10);  // Rainbow color change
      Serial.println("State 3: Feedback 3 - Rainbow Effect");
    } else {
      setLED(0, 0, 0); 
      delay(5000); 
      setLED(255, 255, 255);
      Serial.println("State 3: Feedback 4 - LED Off for 5 seconds");
    }
    lastLightTime = currentTime;
  }
}

// Helper Functions

// Set RGB LED color
void setLED(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

// Blink LED a specified number of times
void blinkLED(int red, int green, int blue, int times, int delayTime) {
  for (int i = 0; i < times; i++) {
    setLED(red, green, blue);
    delay(delayTime);
    setLED(0, 0, 0);
    delay(delayTime);
  }
}

// Gradient effect: Blue to Red
void gradientBlueToRed() {
  for (int i = 0; i <= 255; i++) {
    setLED(i, 0, 255 - i); 
    delay(10);
  }
  setLED(255, 0, 0);
}

// Rainbow color effect
void rainbowEffect(int delayTime) {
  for (int i = 0; i < 256; i++) {
    setLED(255, i, 0); 
    delay(delayTime);
  }
  for (int i = 255; i >= 0; i--) {
    setLED(i, 255, 0); 
    delay(delayTime);
  }
  for (int i = 0; i < 256; i++) {
    setLED(0, 255, i); 
    delay(delayTime);
  }
  for (int i = 255; i >= 0; i--) {
    setLED(0, i, 255); 
    delay(delayTime);
  }
  for (int i = 0; i < 256; i++) {
    setLED(i, 0, 255); 
    delay(delayTime);
  }
  for (int i = 255; i >= 0; i--) {
    setLED(255, 0, i); 
    delay(delayTime);
  }
}
