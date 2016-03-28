/*
This sketch sets constraints to the motor.
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
  motor1.setConstraintDeg(0,180);  // sets constraint for motor to rotate only from 0 to 180 deg
  motor1.gotoAngleDeg(200);  // rotates only to 180 deg, because of constraints
  delay(5000);
  motor1.removeConstraint();  // removes constraints
  motor1.gotoAngleDeg(200);  // rotates to 200 deg, because the constraints have been removed
}

void loop()
{
  
}

