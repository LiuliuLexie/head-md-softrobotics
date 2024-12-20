#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();

uint16_t lasttouched = 0;
uint16_t currtouched = 0;

void setup() {
  Serial.begin(9600);

  while (!Serial) { 
    delay(10); // Wait for serial to initialize
  }

  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 initialized!");
}

void loop() {
  currtouched = cap.touched();
  
  for (uint8_t i = 0; i < 12; i++) {
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i))) {
      Serial.print("TOUCH "); // Send "TOUCH" followed by the pin number
      Serial.println(i);
    }
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i))) {
      Serial.print("RELEASE "); // Send "RELEASE" followed by the pin number
      Serial.println(i);
    }
  }
  
  lasttouched = currtouched;

  delay(50);
}
