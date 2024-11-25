#include <Servo.h>  // Include the Servo library

Servo myServo;             // Create a Servo object
int joyPinX = A0;          // Joystick X-axis connected to analog pin 0
int joyPinY = A1;          // Joystick Y-axis connected to analog pin 1
int valueX = 0;            // Variable for joystick X-axis
int valueY = 0;            // Variable for joystick Y-axis
const int centerX = 512;   // Center value for X-axis
const int centerY = 512;   // Center value for Y-axis
const int threshold = 50;  // Threshold to ignore small joystick movements

int servoPosition = 90;  // Starting position for the servo (center)
int servoSpeed = 1;      // Speed of servo movement

void setup() {
  myServo.attach(10);            // Attach the servo to pin 10
  myServo.write(servoPosition);  // Initialize the servo at 90 degrees
  Serial.begin(9600);            // Start serial communication
}

void loop() {
  valueX = analogRead(joyPinX);  // Read X-axis value
  valueY = analogRead(joyPinY);  // Read Y-axis value

  // Determine the speed based on Y-axis (up = faster, down = stop)
  if (valueY < centerY - threshold) {            // Joystick moved up
    servoSpeed = map(valueY, 0, centerY, 5, 1);  // Map speed from fast to slow
  } else if (valueY > centerY + threshold) {     // Joystick moved down
    servoSpeed = 0;                              // Stop the servo
  } else {
    servoSpeed = 1;  // Default slow speed
  }

  // Determine the direction based on X-axis (right = CW, left = CCW)
  if (valueX > centerX + threshold) {         // Joystick moved right
    servoPosition += servoSpeed;              // Move clockwise
  } else if (valueX < centerX - threshold) {  // Joystick moved left
    servoPosition -= servoSpeed;              // Move counterclockwise
  }

  // Constrain the servo position between 0 and 180 degrees
  servoPosition = constrain(servoPosition, 0, 180);

  // Update the servo position
  if (servoSpeed > 0) {  // Only move the servo if speed > 0
    myServo.write(servoPosition);
  }

  // Debugging output
  Serial.print("Joystick X: ");
  Serial.print(valueX);
  Serial.print(" Joystick Y: ");
  Serial.print(valueY);
  Serial.print(" Servo Position: ");
  Serial.print(servoPosition);
  Serial.print(" Speed: ");
  Serial.println(servoSpeed);

  delay(15);  // Small delay for smooth servo movement
}
