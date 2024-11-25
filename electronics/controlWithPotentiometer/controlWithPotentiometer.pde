import processing.serial.*;

Serial myPort;  // Create object from Serial class
int val;      // Data received from the serial port
String line;

void setup()
{
  size(200, 500);

  // print the list of available serial ports
  println(Serial.list());


  //String portName = Serial.list()[0];
  String portName = Serial.list()[Serial.list().length - 1];
  myPort = new Serial(this, portName, 9600);
}

void draw()
{
  if ( myPort.available() > 0) {  // If data is available,
    line = myPort.readStringUntil(10);

    // Example: 320\t240 mV\t3.22 V
    if (line != null) {
      String[] list = split(line, "\t");
      if (list.length > 1) {
        //println(list[0]);
        val = Integer.parseInt(list[0]); 
        println(val);
      }
    }
  }
  background(255);             // Set background to white
  if (val == 0) {              // If the serial value is 0,
    fill(0);                   // set fill to black
  } else {                       // If the serial value is not 0,
    fill(map(val, 0, 1023, 0, 255));                 // set fill to light gray
  }
  rect(50, map(val, 0, 1023, height - 100, 0), 100, 100);
}
