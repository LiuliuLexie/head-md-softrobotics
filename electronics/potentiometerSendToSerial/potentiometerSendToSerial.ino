// Read a potentiometer value and send it to the serial port
// 
// Pierre Rossel / 2024-11-25

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  
  // Read an analog input, which returns a value between 0 and 1023
  int a0 = analogRead(A0); 

  // convert analog input to voltage in millivolts
  long voltage = map(a0, 0, 1023, 0, 5000);
  
  float volts = voltage / 1000.0;

  Serial.print(a0);
  Serial.print("\t");
  Serial.print(voltage);
  Serial.print(" mV\t\t");
  Serial.print(volts);
  Serial.println(" V");

  delay(100);
}
