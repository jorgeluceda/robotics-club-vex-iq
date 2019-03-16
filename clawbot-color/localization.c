#pragma config(Sensor, port7,  distanceSensor, sensorVexIQ_Distance)
#pragma config(Motor,  motor1,          rightMotor,    tmotorVexIQ, openLoop, reversed, encoder)
#pragma config(Motor,  motor6,          leftMotor,     tmotorVexIQ, openLoop, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard!!*//

/*------------------------------------------------------------------------------------------------
Move forward until the VEX IQ Distance Sensors sees an object 100 millimeters (mm) away. The VEX
IQ Distance Sensor returns values in millimeters.

ROBOT CONFIGURATION: VEX IQ Clawbot
MOTORS & SENSORS:
[I/O Port]          [Name]              [Type]                			[Info]
Port 7        			distanceSensor      VEX IQ Distance		      		Distance Sensor (returns mm)
Port 1        			rightMotor          VEX IQ Motor		      			Left side motor (reversed)
Port 6       				leftMotor          	VEX IQ Motor		      			Right side motor
------------------------------------------------------------------------------------------------*/
const int ACTUATOR_DELAY = 300; // in ms
const int SENSOR_DELAY = 100; // in ms
const int MAX_SPEED = 75;
const float ACCEL_RATE = 1.0; // range: (0.0, 1.0]
const int ACCEL_TIME = 10; // in ms

static int currSpeed = 0;

// Function returns error code -1 if rate is not within the range (0.0, 1.0].
int gradualAcceleration(int startSpeed, int finalSpeed, float rate,  int incTime)
{
	if (rate <= 0.0 || rate > 1.0)
	{
		return -1;
	}

	int range = abs(finalSpeed - startSpeed);
	int increments = range / rate;

	if (finalSpeed >= startSpeed)
	{
		for(int i = startSpeed; i < increments; i += rate)
		{
			setMotorSpeed(leftMotor, i);
			setMotorSpeed(rightMotor, i);
			sleep(incTime);
		}
	}
	else
	{
		for(int i = startSpeed; i > increments; i -= rate)
	  {
			setMotorSpeed(leftMotor, i);
			setMotorSpeed(rightMotor, i);
			sleep(incTime);
		}
	}

	currSpeed = finalSpeed;
	return 0;
}

void turnRight(float degrees)
{
	degrees = abs(degrees) * -1;
	float offset = 3.0;

	resetGyro(3);
	while(getGyroDegreesFloat(3) > degrees + offset)
	{
		setMotorSpeed(leftMotor, 100);
		setMotorSpeed(rightMotor, -100);
	}
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);

	currSpeed = 0;
}

void turnLeft(float degrees)
{
	degrees = abs(degrees);
	float offset = 3.0;

	resetGyro(3);
	while(getGyroDegreesFloat(3) < degrees - offset)
	{
		setMotorSpeed(leftMotor, -100);
		setMotorSpeed(rightMotor, 100);
	}
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);

	currSpeed = 0;
}

void moveForward(int targetSpeed)
{
	targetSpeed = abs(targetSpeed);

	if (targetSpeed > MAX_SPEED)
	{
		targetSpeed = MAX_SPEED;
	}
	else if (targetSpeed == 0)
	{
		targetSpeed = 1;
	}

	if(currSpeed != targetSpeed)
	{
		gradualAcceleration(0, targetSpeed, ACCEL_RATE, ACCEL_TIME);
	}
	setMotorSpeed(leftMotor, targetSpeed);
	setMotorSpeed(rightMotor, targetSpeed);
	currSpeed = targetSpeed;
}

void moveBackward(int targetSpeed)
{
	targetSpeed = abs(targetSpeed) * -1;

	if (targetSpeed < -MAX_SPEED)
	{
		targetSpeed = -MAX_SPEED;
	}
	else if (targetSpeed == 0)
	{
		targetSpeed = -1;
	}

	if(currSpeed != targetSpeed)
	{
		gradualAcceleration(0, targetSpeed, ACCEL_RATE, ACCEL_TIME);
	}
	setMotorSpeed(leftMotor, targetSpeed);
	setMotorSpeed(rightMotor, targetSpeed);
	currSpeed = targetSpeed;
}

void stopMotion()
{
	gradualAcceleration(currSpeed, 0, ACCEL_RATE, ACCEL_TIME);
	setMotorSpeed(leftMotor, 0);
	setMotorSpeed(rightMotor, 0);
	currSpeed = 0;
}

float max (float x, float y)
{
	return (x > y) ? x : y;
}

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
		if(forwardDist > 300.0)
		{
			moveForward(MAX_SPEED);
		}
		else
		{
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
					moveBackward(MAX_SPEED);
					sleep(1000);
					stopMotion();
					sleep(ACTUATOR_DELAY);
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
