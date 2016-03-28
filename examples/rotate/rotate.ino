/*
This sketch rotates the motor continuously at 10rpm.
Connect the TX pin coming out of the motor(orange wire) to pin 9 on Arduino.
Connect the RX pin coming out of the motor(yellow wire) to pin 10 on Arduino.
Remember to give common ground connection to the motor and the Arduino.
*/
#include <SoftwareSerial.h>
#include <Rhino.h>


Rhino motor1(9,10);	// RX( -> TX of motor), TX( -> RX of motor)

void setup()
{
  delay(2000);
  motor1.printOutput(1);	// enables Serial printing of function outputs
  motor1.init();	// initializes the motor and sets current position as origin
  motor1.setSpeed(255);  // sets speed to max speed (10 rpm)
  motor1.rotate(255);  // starts rotating motor at max speed (10 rpm)
  delay(5000);
  motor1.stopMotor();	// stops motor after 5 seconds
}

void loop()
{
  
}

