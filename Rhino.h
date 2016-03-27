/*
	Rhino.h - Library for controlling Rhino Servo DC Motor with UART (Example: http://robokits.co.in/motors/high-torque-encoder-dc-servo-motor-10rpm-with-uart-i2c-ppm-drive?cPath=2_71&).
	Created by Samvrit Srinivas, 24 March, 2016.
	Released into the public domain.
	Contact: samvrit.goku@gmail.com
*/

#ifndef Rhino_h
#define Rhino_h


#include "Arduino.h"
#include "SoftwareSerial.h"

class SoftwareSerial;

class Rhino
{
public:
    Rhino(uint8_t rx, uint8_t tx):_serial(rx,tx){};
	
	void init()
	{
		Serial.begin(9600);
		_serial.begin(9600);
		_serial.flush();
		_serial.write("P0\r");
		_constraint = 0;
		if(_print)
			Serial.println("Motor Initiated!");
	}
	void reset()
	{
		_serial.flush();
		_serial.write("Y\r");
		if(_print)
			Serial.println("Motor Reset!");
	}
	void autoCalibrate()
	{
		_serial.flush();
		_serial.write("X\r");
		if(_print)
			Serial.println("Motor auto-calibrating..");
	}
	void sendCmd(String cmd)
	{
		char s[cmd.length()+2];
		cmd.toCharArray(s,cmd.length()+1);
		_serial.flush();
		_serial.write(s);
		_serial.write("\r");
		Serial.write("Command sent: ");
		if(_print)
		{
			Serial.write(s);
			Serial.println();
		}
	}
	void sendCmd(char cmd[])
	{
		_serial.flush();
		_serial.write(cmd);
		_serial.write("\r");
		Serial.write("Command sent: ");
		if(_print)
		{
			Serial.write(cmd);
			Serial.println();
		}
		
	}
	void rotate(int speed1)
	{
		speed1 = constrain(speed1,-255,255);
		String speed = String(speed1);
		speed = "S"+speed;
		char s[speed.length()+2];
		speed.toCharArray(s,speed.length()+1);
		_serial.flush();
		_serial.write(s);
		_serial.write("\r");
		if(_print)
		{
			Serial.write("Rotating motor at speed: ");
			Serial.println(speed1);
		}
		
	}
	void stopMotor()
	{
		_serial.flush();
		_serial.write("S0\r");
		if(_print)
			Serial.println("Motor stopped");
	}
	void gotoPos(float pos1)
	{
        pos1 = ceil(pos1);
		int pos2 = (int)pos1;
		if(_constraint)
			pos2 = constrain(pos2,_min,_max);
		String pos = String(pos2);
		pos = "G"+pos;
		char s[pos.length()+2];
		pos.toCharArray(s,pos.length()+1);
		_serial.flush();
		_serial.write(s);
		_serial.write("\r");
		if(_print)
		{
			Serial.write("Go to position: ");
			Serial.println(pos2);
		}
		
    }
	void gotoAngleDeg(float angle1)
	{
		angle1 *= 5;
		angle1 = ceil(angle1);
		int angle2 = (int)angle1;
		if(_constraint)
			angle2 = constrain(angle2,_min,_max);
		String angle = "G"+String(angle2);
		char s[angle.length()+2];
		angle.toCharArray(s,angle.length()+1);
		_serial.flush();
		_serial.write(s);
		_serial.write("\r");
		if(_print)
		{
			Serial.write("Go to angle: ");
			Serial.println(angle1/5);
		}
		
	}
	void gotoAngleRad(float angle1)
	{
		angle1 *= 286.6242;
		angle1 = ceil(angle1);
		int angle2 = (int)angle1;
		if(_constraint)
			angle2 = constrain(angle2,_min,_max);
		String angle = "G"+String(angle2);
		char s[angle.length()+2];
		angle.toCharArray(s,angle.length()+1);
		_serial.flush();
		_serial.write(s);
		_serial.write("\r");
		if(_print)
		{
			Serial.write("Go to angle: ");
			Serial.println(angle1/286.6242);
		}
		
	}
	void gotoAngleDegC(float angle1)
	{
		angle1 = constrain(angle1,-180,180);
		angle1 *= 5;
		angle1 = ceil(angle1);
		int angle2 = (int)angle1;
		if(_constraint)
			angle2 = constrain(angle2,_min,_max);
		String angle = "G"+String(angle2);
		char s[angle.length()+2];
		angle.toCharArray(s,angle.length()+1);
		_serial.flush();
		_serial.write(s);
		_serial.write("\r");
		if(_print)
		{
			Serial.write("Go to angle: ");
			Serial.println(angle2);
		}
		
	}
	void gotoAngleRadC(float angle1)
	{
		angle1 = constrain(angle1,-3.1415,3.1415);
		angle1 *= 286.6242;
		angle1 = ceil(angle1);
		int angle2 = (int)angle1;
		if(_constraint)
			angle2 = constrain(angle2,_min,_max);
		String angle = "G"+String(angle2);
		char s[angle.length()+2];
		angle.toCharArray(s,angle.length()+1);
		_serial.flush();
		_serial.write(s);
		_serial.write("\r");
		if(_print)
		{
			Serial.write("Go to angle: ");
			Serial.println(angle2/286.6242);
		}
		
	}
	void gotoRel(long pos1)
	{
        if(_constraint)
		{
			if(_print)
			{
				printOutput(0);
				int curr_pos = getPos();
				printOutput(1);
				if((pos1 > (_max - curr_pos))||(pos1 < (_min - curr_pos)))
					pos1 = 0;
			}
			else
			{
				int curr_pos = getPos();
				if((pos1 > (_max - curr_pos))||(pos1 < (_min - curr_pos)))
					pos1 = 0;
			}	
		}
		String pos = String(pos1);
		pos = "R"+pos;
		char s[pos.length()+2];
		pos.toCharArray(s,pos.length()+1);
		_serial.flush();
		_serial.write(s);
		_serial.write("\r");
		if(_print)
		{
			Serial.write("Go to relative position: ");
			Serial.println(pos1);
		}
		
    }
	void gotoRelDeg(float pos1)
	{
        pos1 = pos1*5;
		int pos2 = ceil(pos1);
		if(_constraint)
		{
			if(_print)
			{
				printOutput(0);
				int curr_pos = getPos();
				printOutput(1);
				if((pos1 > (_max - curr_pos))||(pos1 < (_min - curr_pos)))
					pos2 = 0;
			}
			else
			{
				int curr_pos = getPos();
				if((pos1 > (_max - curr_pos))||(pos1 < (_min - curr_pos)))
					pos2 = 0;
			}
		}
		String pos = String(pos2);
		pos = "R"+pos;
		char s[pos.length()+2];
		pos.toCharArray(s,pos.length()+1);
		_serial.flush();
		_serial.write(s);
		_serial.write("\r");
		if(_print)
		{
			Serial.write("Go to relative position: ");
			Serial.println(pos2/5);
		}
		
    }
	void gotoRelRad(float pos1)
	{
        pos1 = pos1*286.6242;
		int pos2 = ceil(pos1);
		if(_constraint)
		{
			if(_print)
			{
				printOutput(0);
				int curr_pos = getPos();
				printOutput(1);
				if((pos1 > (_max - curr_pos))||(pos1 < (_min - curr_pos)))
					pos2 = 0;
				
			}
			else
			{
				int curr_pos = getPos();
				if((pos1 > (_max - curr_pos))||(pos1 < (_min - curr_pos)))
					pos2 = 0;
			}
		}
		String pos = String(pos2);
		pos = "R"+pos;
		char s[pos.length()+2];
		pos.toCharArray(s,pos.length()+1);
		_serial.flush();
		_serial.write(s);
		_serial.write("\r");
		if(_print)
		{
			Serial.write("Go to relative position: ");
			Serial.println(pos2/286.6242);
		}
		
    }
	void setSFGain(int gain1)
	{
        gain1 = constrain(gain1,0,32767);
		String gain = String(gain1);
		gain = "A"+gain;
		char s[gain.length()+2];
		gain.toCharArray(s,gain.length()+1);
		_serial.flush();
		_serial.write(s);
		_serial.write("\r");
		if(_print)
		{
			Serial.write("Setting Speed Feedback Gain: ");
			Serial.println(gain1);
		}
		
    }
	void setP(int p1)
	{
		String p = String(p1);
		p = "B"+p;
		char s[p.length()+2];
		p.toCharArray(s,p.length()+1);
		_serial.flush();
		_serial.write(s);
		_serial.write("\r");
		if(_print)
		{
			Serial.write("Setting P: ");
			Serial.println(p1);
		}
		
	}
	void setI(int i1)
	{
		String i = String(i1);
		i = "C"+i;
		char s[i.length()+2];
		i.toCharArray(s,i.length()+1);
		_serial.flush();
		_serial.write(s);
		_serial.write("\r");
		if(_print)
		{
			Serial.write("Setting I: ");
			Serial.println(i1);
		}
		
	}
	void setD(int d1)
	{
		d1 = constrain(d1,0,255);
		String d = String(d1);
		d = "D"+d;
		char s[d.length()+2];
		d.toCharArray(s,d.length()+1);
		_serial.flush();
		_serial.write(s);
		_serial.write("\r");
		if(_print)
		{
			Serial.write("Setting D: ");
			Serial.println(d1);
		}
		
	}
	void setSpeed(int speed1)
	{
		speed1 = constrain(speed1,0,255);
		String speed = String(speed1);
		speed = "M"+speed;
		char s[speed.length()+2];
		speed.toCharArray(s,speed.length()+1);
		_serial.flush();
		_serial.write(s);
		_serial.write("\r");
		if(_print)
		{
			Serial.write("Setting maximum speed: ");
			Serial.println(speed1);
		}
		
	}
	void setI2CAddr(int addr1)
	{
		addr1 = constrain(addr1,0,255);
		String addr = String(addr1);
		addr = "D"+addr;
		char s[addr.length()+2];
		addr.toCharArray(s,addr.length()+1);
		_serial.flush();
		_serial.write(s);
		_serial.write("\r");
		if(_print)
		{
			Serial.write("Setting I2C address: ");
			Serial.println(addr1);
		}
		
	}
	void setPos(int pos1)
	{
		if(_constraint)
		{
			if(_print)
			{
				printOutput(0);
				int curr_pos = getPos();
				printOutput(1);
				if(pos1 > _max)
					pos1 = _max;
				else if(pos1 < _min)
					pos1 = _min;
			}
			else
			{
				int curr_pos = getPos();
				if(pos1 > _max)
					pos1 = _max;
				else if(pos1 < _min)
					pos1 = _min;
			}
		}
		String pos = String(pos1);
		pos = "P"+pos;
		char s[pos.length()+2];
		pos.toCharArray(s,pos.length()+1);
		_serial.flush();
		_serial.write(s);
		_serial.write("\r");
		if(_print)
		{
			Serial.write("Setting motor position: ");
			Serial.println(pos1);
		}
		
	}
	void setConstraint()
	{
		_constraint = 1;
	}
	void setConstraint(float min, float max)
	{
		_constraint = 1;
		_min = (long)min;
		_max = (long)max;
	}
	void setConstraintRad(float min, float max)
	{
		_constraint = 1;
		_min = (long)(min*286.6242);
		_max = (long)(max*286.6242);
	}
	void setConstraintDeg(float min, float max)
	{
		_constraint = 1;
		_min = (long)(min*5);
		_max = (long)(max*5);
	}
	void removeConstraint()
	{
		_constraint = 0;
	}
	void printOutput(bool choice)
	{
		if(choice)
			_print = 1;
		else if(!choice)
			_print = 0;
	}
	int getPos()
	{
		int position;
		bool neg = 0;
		String inString = "";
		_serial.flush();
		_serial.write("P\r");
		_serial.listen();
		while(_serial.available()<=2);
		while (_serial.available()) 
		{
			int inChar = _serial.read();
			if(isDigit(inChar))
				inString += (char)inChar;
			if(inChar=='-')
				neg = 1;
			if(inChar=='\r')
			{
				position = inString.toInt();
				if(neg)
					position *= -1;
				if(_print)
					Serial.println(position);
				return position;
			}
		}
	}
	float getAngleDeg()
	{
		float angle;
		bool neg = 0;
		String inString = "";
		_serial.flush();
		_serial.write("P\r");
		_serial.listen();
		while(_serial.available()<=2);
		while (_serial.available()) 
		{
			int inChar = _serial.read();
			if(isDigit(inChar))
				inString += (char)inChar;
			if(inChar=='-')
				neg = 1;
			if(inChar=='\r')
			{
				angle = (inString.toInt())/5;
				if(neg)
					angle *= -1;
				if(_print)
					Serial.println(angle);
				return angle;
			}
		}
	}
	float getAngleRad()
	{
		float angle;
		bool neg = 0;
		String inString = "";
		_serial.flush();
		_serial.write("P\r");
		_serial.listen();
		while(_serial.available()<=2);
		while (_serial.available()) 
		{
			int inChar = _serial.read();
			if(isDigit(inChar))
				inString += (char)inChar;
			if(inChar=='-')
				neg = 1;
			if(inChar=='\r')
			{
				angle = (inString.toInt())/286.6242;
				if(neg)
					angle *= -1;
				if(_print)
					Serial.println(angle);
				return angle;
			}
		}
	}
	int getSpeed()
	{
		int speed;
		bool neg = 0;
		String inString = "";
		_serial.flush();
		_serial.write("M\r");
		_serial.listen();
		while(_serial.available()<=2);
		while (_serial.available()) 
		{
			int inChar = _serial.read();
			if(isDigit(inChar))
				inString += (char)inChar;
			if(inChar=='-')
				neg = 1;
			if(inChar=='\r')
			{
				speed = inString.toInt();
				if(neg)
					speed *= -1;
				if(_print)
					Serial.println(speed);
				return speed;
			}
		}
	}
	int getRotSpeed()
	{
		int speed;
		bool neg = 0;
		String inString = "";
		_serial.flush();
		_serial.write("S\r");
		_serial.listen();
		while(_serial.available()<=2);
		while (_serial.available()) 
		{
			int inChar = _serial.read();
			if(isDigit(inChar))
				inString += (char)inChar;
			if(inChar=='-')
				neg = 1;
			if(inChar=='\r')
			{
				speed = inString.toInt();
				if(neg)
					speed *= -1;
				if(_print)
					Serial.println(speed);
				return speed;
			}
		}
	}
	int getI2CAddr()
	{
		int addr;
		bool neg = 0;
		String inString = "";
		_serial.flush();
		_serial.write("E\r");
		_serial.listen();
		while(_serial.available()<=2);
		while (_serial.available()) 
		{
			int inChar = _serial.read();
			if(isDigit(inChar))
				inString += (char)inChar;
			if(inChar=='-')
				neg = 1;
			if(inChar=='\r')
			{
				addr = inString.toInt();
				if(neg)
					addr *= -1;
				if(_print)
					Serial.println(addr);
				return addr;
			}
		}
	}
	int getSFGain()
	{
		int gain;
		bool neg = 0;
		String inString = "";
		_serial.flush();
		_serial.write("A\r");
		_serial.listen();
		while(_serial.available()<=2);
		while (_serial.available()) 
		{
			int inChar = _serial.read();
			if(isDigit(inChar))
				inString += (char)inChar;
			if(inChar=='-')
				neg = 1;
			if(inChar=='\r')
			{
				gain = inString.toInt();
				if(neg)
					gain *= -1;
				if(_print)
					Serial.println(gain);
				return gain;
			}
		}
	}
	int getP()
	{
		int gain;
		bool neg = 0;
		String inString = "";
		_serial.flush();
		_serial.write("B\r");
		_serial.listen();
		while(_serial.available()<=2);
		while (_serial.available()) 
		{
			int inChar = _serial.read();
			if(isDigit(inChar))
				inString += (char)inChar;
			if(inChar=='-')
				neg = 1;
			if(inChar=='\r')
			{
				gain = inString.toInt();
				if(neg)
					gain *= -1;
				if(_print)
					Serial.println(gain);
				return gain;
			}
		}
	}
	int getI()
	{
		int gain;
		bool neg = 0;
		String inString = "";
		_serial.flush();
		_serial.write("C\r");
		_serial.listen();
		while(_serial.available()<=2);
		while (_serial.available()) 
		{
			int inChar = _serial.read();
			if(isDigit(inChar))
				inString += (char)inChar;
			if(inChar=='-')
				neg = 1;
			if(inChar=='\r')
			{
				gain = inString.toInt();
				if(neg)
					gain *= -1;
				if(_print)
					Serial.println(gain);
				return gain;
			}
		}
	}
	int getD()
	{
		int gain;
		bool neg = 0;
		String inString = "";
		_serial.flush();
		_serial.write("D\r");
		_serial.listen();
		while(_serial.available()<=2);
		while (_serial.available()) 
		{
			int inChar = _serial.read();
			if(isDigit(inChar))
				inString += (char)inChar;
			if(inChar=='-')
				neg = 1;
			if(inChar=='\r')
			{
				gain = inString.toInt();
				if(neg)
					gain *= -1;
				if(_print)
					Serial.println(gain);
				return gain;
			}
		}
	}
private:
	SoftwareSerial _serial;
	bool _constraint,_print;
	long _max,_min;
};

#endif