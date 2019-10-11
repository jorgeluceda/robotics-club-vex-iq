#pragma config(Sensor, port4,  gyroscope,      sensorVexIQ_Gyro)
#pragma config(Sensor, port7,  distanceSensor, sensorVexIQ_Distance)
#pragma config(Sensor, port9,  frontBumper,    sensorVexIQ_Touch)
#pragma config(Motor,  motor1,          rightMotor,    tmotorVexIQ, openLoop, reversed, encoder)
#pragma config(Motor,  motor6,          leftMotor,     tmotorVexIQ, openLoop, encoder)

#include "manual_obstacles.h"

task main()
{
	goForward(1, 40);
}
