#pragma config(Motor,  motor1,   rightMotor,     tmotorVexIQ, openLoop,  reversed,  encoder)
#pragma config(Motor,  motor6,   leftMotor,      tmotorVexIQ, openLoop,   encoder)
#pragma config(Sensor, port4,  gyroscope,      sensorVexIQ_Gyro)
//#pragma config(Sensor, port7,  distanceSensor, sensorVexIQ_Distance)
//#pragma config(Sensor, port9,  frontBumper,    sensorVexIQ_Touch)
//NOTE: need to unreverse for usability/building purposes
//NOTE: only using motors 1 and 6 currently
#include "manual_obstacles.h"

task main()
{
	//accepts feet as parameter to go forward
	goForwardFeet(1);
	turnRight();
	goForwardFeet(1);
	turnLeft();
	goForwardFeet(1);
	turnRight();
	goForwardFeet(1);
	goForwardFeet(1);
	turnLeft();
	goForwardFeet(1);
}
