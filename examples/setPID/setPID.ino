/*
This sketch sets PID values.
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
  
  int p = getP();  // gets current P gain
  int i = getI();  // gets current I gain
  int d = getD();  // gets current D gain
  
  motor1.setP(p);  // sets P gain
  motor1.setI(i);  // sets I gain
  motor1.setD(d);  // sets D gain
}

void loop()
{
  
}

