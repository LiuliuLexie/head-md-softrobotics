//traffic light

int LED1 = 9;
int LED2 = 10;
int LED3 = 11;
// int speed = 200;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED1, HIGH);
  delay(1000);  // Short blink (200ms on)
  digitalWrite(LED1, LOW);
  delay(200);  // Short pause between blinks

  blinkShort(5);

  digitalWrite(LED3, HIGH);
  delay(1000);  // Short blink (200ms on)
  digitalWrite(LED3, LOW);
  delay(200);  // Short pause between blinks
}

// Function for short blinks
void blinkShort(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED2, HIGH);
    delay(200);  // Short blink (200ms on)
    digitalWrite(LED2, LOW);
    delay(200);  // Short pause between blinks
  }
}

// // Function for long blinks
// void blinkLong(int times) {
//   for (int i = 0; i < times; i++) {
//     digitalWrite(LED_PIN, HIGH);
//     delay(1000);  // Long blink (600ms on)
//     digitalWrite(LED_PIN, LOW);
//     delay(300);  // Short pause between blinks
//   }
// }
