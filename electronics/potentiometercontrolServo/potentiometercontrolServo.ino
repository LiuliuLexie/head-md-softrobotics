#include <Servo.h>               // Include the Servo library

const int analogInPin = A0;      // Analog input pin for the potentiometer
int sensorValue = 0;             // Value read from the potentiometer
int servoPosition = 0;           // Value mapped to servo position (0-180)

Servo myServo;                   // Create a Servo object

void setup() {
  myServo.attach(9);             // Attach the servo to pin 9
  Serial.begin(9600);            // Initialize serial communication at 9600 bps
}

void loop() {
  // Read the potentiometer value
  sensorValue = analogRead(analogInPin);

  // Map the potentiometer value (0–1023) to servo range (0–180)
  servoPosition = map(sensorValue, 0, 1023, 0, 180);

  // Set the servo to the mapped position
  myServo.write(servoPosition);

  // Print the values to the Serial Monitor for debugging
  Serial.print("Potentiometer Value: ");
  Serial.print(sensorValue);
  Serial.print("\tServo Position: ");
  Serial.println(servoPosition);

  // Small delay for smooth servo movement
  delay(15);
}
