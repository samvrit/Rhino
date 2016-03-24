/*
This sketch instructs the motor to go through 90 degrees.
Connect the TX pin coming out of the motor(orange wire) to RX of the SoftwareSerial port, ie., pin 9 on Arduino.
Connect the RX pin coming out of the motor(yellow wire) to TX of the SoftwareSerial port, ie., pin 10 on Arduino.
Remember to give common ground connection to the motor and the Arduino.
*/
#include <SoftwareSerial.h>
#include <Rhino.h>

SoftwareSerial m1(9,10); // RX( -> TX of motor), TX( -> RX of motor)
Rhino motor1(m1);

void setup()
{
  motor1.printOutput(1);
  motor1.init();
  motor1.gotoAngleDeg(90);
}

void loop()
{
  
}
