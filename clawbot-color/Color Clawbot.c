#pragma config(Sensor, port7, distanceSensor,     sensorVexIQ_Distance)
#pragma config(Motor,  motor1,          leftMotor,     tmotorVexIQ, openLoop, encoder)
#pragma config(Motor,  motor6,          rightMotor,    tmotorVexIQ, openLoop, reversed, encoder)

/*------------------------------------------------------------------------------------------------
Move forward until the VEX IQ Distance Sensors sees an object 100 millimeters (mm) away. The VEX
IQ Distance Sensor returns values in millimeters.

ROBOT CONFIGURATION: VEX IQ Clawbot
MOTORS & SENSORS:
[I/O Port]          [Name]              [Type]                			[Info]
Port 7        			distanceSensor      VEX IQ Distance		      		Distance Sensor (returns mm)
Port 1        			leftMotor           VEX IQ Motor		      			Left side motor
Port 6       				rightMotor          VEX IQ Motor		      			Right side motor (reversed)
------------------------------------------------------------------------------------------------*/
void interpolateAcceleration(int startSpeed, int finalSpeed, float rate,  int incTime) {
	int range = abs(finalSpeed - startSpeed);

	int increments = range / rate;

	for(int i = 0; i < increments; i += rate) {
		setMotorSpeed(leftMotor, -i);
		setMotorSpeed(rightMotor, -i);
		sleep(incTime);
	}
}

void interpolateDeceleration(int startSpeed, int finalSpeed, float rate,  int incTime) {
	int range = abs(finalSpeed - startSpeed);

	int increments = range / rate;

	for(int i = range; i > finalSpeed; i -= rate) {
		setMotorSpeed(leftMotor, -i);
		setMotorSpeed(rightMotor, -i);
		sleep(incTime);
	}
}

task main()
{
	/*
	int currSpeed;
	const int maxSpeed = 75;
	while(1) {
		//If distance sensor is more than 300mm (30cm) away
		if(getDistanceValue(distanceSensor) > 300) {
				if(currSpeed == 0) {
					interpolateAcceleration(0, maxSpeed, 1, 50);
					currSpeed = maxSpeed;
				}
				setMotorSpeed(leftMotor, (maxSpeed));
				setMotorSpeed(rightMotor, (maxSpeed));
			} else {
				if(currSpeed > 0) {
					interpolateDeceleration(maxSpeed, 0, 1, 50);
				}
				setMotorSpeed(leftMotor, 0);
				setMotorSpeed(rightMotor, 0);
			}
	}*/
	const int maxSpeed = -75;
	int curSpeed = 0;
	while(1)
	{
		//If distance sensor is more than 300mm (30cm) away
		if(getDistanceValue(distanceSensor) > 300)
		{
			if(curSpeed == 0)
			{
				interpolateAcceleration(0, maxSpeed, 1, 5);
				curSpeed = maxSpeed;
			}
			setMotorSpeed(leftMotor, (maxSpeed));
			setMotorSpeed(rightMotor, (maxSpeed));
		}
		else
		{
			if(curSpeed < 0)
			{
				interpolateDeceleration(curSpeed, 0, 1, 5);
				curSpeed = 0;
			}
			setMotorSpeed(leftMotor, 0);
			setMotorSpeed(rightMotor, 0);
		}
	}
}
