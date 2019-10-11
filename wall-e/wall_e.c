#pragma config(Sensor, port3,  colorSensor,      sensorVexIQ_ColorHue)
#pragma config(Sensor, port4,  gyroscope,      sensorVexIQ_Gyro)
#pragma config(Sensor, port7,  distanceSensor, sensorVexIQ_Distance)
#pragma config(Sensor, port8,  clawBumper,     sensorVexIQ_Touch)
#pragma config(Sensor, port9,  frontBumper,    sensorVexIQ_Touch)
#pragma config(Motor,  motor1,          rightMotor,    tmotorVexIQ, openLoop, reversed, encoder)
#pragma config(Motor,  motor6,          leftMotor,     tmotorVexIQ, openLoop, encoder)
#pragma config(Motor,  motor10,         armMotor,      tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor11,         clawMotor,     tmotorVexIQ, PIDControl, encoder)
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

//used to store the state of the current object picked in[0],
//and the state of the machine path in [1].
//[0] 0: no object has been picked.
//[0] 1: object has been detected.
//[0] 2: object has been detected and is trash.
//[0] 3: object has been detected and is recyclable
//[0] 4: object has been picked and is trash
//[0] 4
//[0] 3: object has been picked and is recyclable
//[0] 4: object has been delivered.
//[1] 0: moving to recycled.
//[2] 1: moving to trash.

//[3] 0-255: Current Color Hue Value
typedef struct {
	int arr[3];
} structArray;


// Converts ticks for the driving encoders to inches that the robot moved
float INCHES_PER_TICK = 0.100178337;
float inchesCalc (float inches)
{
return inches / INCHES_PER_TICK;
}


void moveN(int distance, int power, int direction)
{
    //
    // Adjust power so that it is only negative if distance is negative.
    //
    power = abs(power);
    if (distance < 0)
    {
        power = -power;
    }
    //
    // reset encoders.
    //
    nMotorEncoder[leftMotor] = 0;
    nMotorEncoder[rightMotor] = 0;
    nMotorEncoder[armMotor] = 0;
    //
    // while not reaching target.
    //
    while (abs(nMotorEncoder[leftMotor] + nMotorEncoder[rightMotor])/2 < distance)
    {
        //
        // Check for trash.
        //
       	if(direction == 0) {
     			moveForward(MAX_SPEED);
   			} else {
     			moveBackward(MAX_SPEED);
     		}
        wait1Msec(10);
    }
}

void drive(int distance, int power, int direction)
{
    //
    // Adjust power so that it is only negative if distance is negative.
    //
    power = abs(power);
    if (distance < 0)
    {
        power = -power;
    }
    //
    // reset encoders.
    //
    nMotorEncoder[leftMotor] = 0;
    nMotorEncoder[rightMotor] = 0;
    nMotorEncoder[armMotor] = 0;
    //
    // while not reaching target.
    //
    while (abs(nMotorEncoder[leftMotor] + nMotorEncoder[rightMotor])/2 < distance)
    {
        //
        // Check for trash.
        //
        if (SensorValue[distanceSensor] > 300)
        {
       			if(direction == 0) {
       				moveForward(MAX_SPEED);
       			} else {
       				moveBackward(MAX_SPEED);
       			}
        }
        else
        {
        		stopMotion();
            turnLeft(180);
            moveN(200, 40, 0);
       			setArmPosition(120);
        }
        wait1Msec(10);
    }
}

//7.874 inches in circumference are the wheels
//~46  ticks per inch
task main()
{
	structArray a;
	a.arr[0] = 0; //no object has been picked on init.
	a.arr[1] = 1; //driving to recycled area on init.

	while(1){

		//3000 distance total, 1500 one way.
		drive(1000, 40, 0);
		//do a 360
		turnLeft(180);

		//drive to opposite end
		drive(2000, 40, 0);
	}
}
