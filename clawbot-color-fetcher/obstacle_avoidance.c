#pragma config(Sensor, port4,    gyroscope,      sensorVexIQ_Gyro)
#pragma config(Sensor, port7,    distanceSensor, sensorVexIQ_Distance)
#pragma config(Sensor, port8,    clawBumper,     sensorVexIQ_Touch)
#pragma config(Sensor, port9,    frontBumper,    sensorVexIQ_Touch)
#pragma config(Motor,  motor1,   rightMotor,     tmotorVexIQ, openLoop,   reversed, encoder)
#pragma config(Motor,  motor6,   leftMotor,      tmotorVexIQ, openLoop,   encoder)
#pragma config(Motor,  motor10,  armMotor,       tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor11,  clawMotor,      tmotorVexIQ, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*------------------------------------------------------------------------------------------------
Move forward until the VEX IQ Distance Sensors sees an object 100 millimeters (mm) away. The VEX
IQ Distance Sensor returns values in millimeters.

ROBOT CONFIGURATION: VEX IQ Clawbot
MOTORS & SENSORS:
[I/O Port]          [Name]              [Type]                  [Info]
Port 7              distanceSensor      VEX IQ Distance         Distance Sensor (returns mm)
Port 1              rightMotor          VEX IQ Motor            Left side motor (reversed)
Port 6              leftMotor           VEX IQ Motor            Right side motor
------------------------------------------------------------------------------------------------*/
#include "movement.h"

task main()
{
	while(1)
	{
		sleep(SENSOR_DELAY);

		float leftDist = 0.0;
		float rightDist = 0.0;
		float backDist = 0.0;
		float forwardDist = getDistanceValue(distanceSensor);

		// If distance sensor is more than 300mm (30cm) away.
		if(forwardDist > 300.0 && getBumperValue(frontBumper) == 0)
		{
			moveForward(MAX_SPEED);
		}
		else
		{
			if (getBumperValue(frontBumper) == 1)
			{
				stopMotionImmediate();
			}
			else
			{
				stopMotion();
			}
			sleep(ACTUATOR_DELAY);

			moveBackward(MAX_SPEED / 2);
			sleep(1000);
			stopMotion();
			sleep(ACTUATOR_DELAY);

			turnLeft(90.0);
			leftDist = getDistanceValue(distanceSensor);
			sleep(SENSOR_DELAY);

			turnRight(180.0);
			rightDist = getDistanceValue(distanceSensor);
			sleep(SENSOR_DELAY);

			turnRight(90.0);
			backDist = getDistanceValue(distanceSensor);
			sleep(SENSOR_DELAY);

			turnLeft(180.0);
			sleep(SENSOR_DELAY);

			int maxDist = max(max(rightDist, backDist), leftDist);

			if (maxDist > 300.0)
			{
				if (leftDist == maxDist)
				{
					turnLeft(90.0);
					sleep(ACTUATOR_DELAY);
					moveForward(MAX_SPEED);
				}
				else if (rightDist == maxDist)
				{
					turnRight(90.0);
					sleep(ACTUATOR_DELAY);
					moveForward(MAX_SPEED);
				}
				else
				{
					turnRight(180.0);
					sleep(ACTUATOR_DELAY);
					moveForward(MAX_SPEED);
				}
				sleep(ACTUATOR_DELAY);
			}
			else
			{
				stopMotion();
				sleep(ACTUATOR_DELAY);
			}
		}
	}
}
