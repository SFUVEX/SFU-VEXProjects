// test gladstone
//test workspace 4
/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
 *
 * Copyright (c) 2011-2013, Purdue University ACM SIG BOTS.
 * All rights reserved.
 * 
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Purdue University ACM SIG BOTS nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
static Encoder encoder1;
/*
 * Runs the user autonomous code. This function will be started in its own task with the default
 * priority and stack size whenever the robot is enabled via the Field Management System or the
 * VEX Competition Switch in the autonomous mode. If the robot is disabled or communications is
 * lost, the autonomous task will be stopped by the kernel. Re-enabling the robot will restart
 * the task, not re-start it from where it leftLine off.
 *
 * Code running in the autonomous task cannot access information from the VEX Joystick. However,
 * the autonomous function can be invoked from another task if a VEX Competition Switch is not
 * available, and it can access joystick information if called in this way.
 *
 * The autonomous task may exit, unlike operatorControl() which should never exit. If it does
 * so, the robot will await a switch to another mode or disable/enable cycle.
 */



//movement functions
void driveForward(int x); // x = encoder value
void driveBack(int x); // x = encoder value
void turnRight(int x); // x = encoder value
void turnLeft (int x); // x = encoder value
void turnRightSlowDead();
void turnLeftSlowDead ();

void driveForwardDead ();
void driveBackDead ();
void driveForwardSlow (int x);
void driveBackSlow (int x) ;
void driveForwardSlowDead ();
void driveBackSlowDead ();
void forwardDetect ();
void backDetect ();
void stopAll();
void stopDrive();

void stopIntake();
void armUp (int x); // x = pot value
void armDown(int x); // x = pot value
void armUpDead();
void armDownDead ();
void armDownTime (int x); // x = milisecs
void armDownTime (int x);
void armUpEnc(int x); // x = encoders
void armDownEnc (int x);
void armUpTrim ();
void armDownTrim ();
void stopArm ();
void intake (int x); //x = time
void outtake (int x);
void intakeDead (); // continuous intaking
void outtakeDead ();// countinuous outtake
void followLine (int dylanSexxydistance);
void findLineRight ();
void findLineLeft ();


// autonomous routines
void smallbotRed ();
void smallbotBlue();
void armbotRed();
void armbotBlue();


//motors
#define motor1 1 // = rightLine back
#define motor2 2 // = rightLine front
#define ARM_MOTOR1 3 // = rightLine arm down
#define ARM_MOTOR2 4 // = rightLine arm up
#define motor5 5 // = rightLine intake
#define motor6 6 // = leftLine intake
#define ARM_MOTOR3 7 // = leftLine arm up
#define ARM_MOTOR4 8 // = leftLine arm down
#define motor9 9 // = leftLine front
#define motor10 10 // = leftLine back

void armHelixUp(int spikeNumber);
void armHelixDown();

void armHelixUp (int spikeNumber)
{
	const int TOWER_MOTOR = ARM_MOTOR1;
	const int SWING_MOTOR = ARM_MOTOR2;
	const int SWING_POT = 0; //TODO set
	const Encoder TOWER_ENCODER = 1; //TODO set

	const int TOWER_OFFSET =200; //TODO set
	const int SWING_ANGLE = 200;

	motorSet (TOWER_MOTOR, 127);
	motorSet (SWING_MOTOR, 127);

	//bool done =false, swingDone =false, heightDone =false;
	imeReset(SWING_POT);
	imeReset(TOWER_ENCODER);

	int towerCount=0, swingCount=0;

	//while(!done)
	{
		imeGet(SWING_POT, &towerCount);
		imeGet(TOWER_ENCODER, &swingCount);

		if (towerCount > TOWER_OFFSET * spikeNumber)
		{
			motorSet (TOWER_MOTOR, 0);
			printf("Tower raised, might fall, motor stopped");
		//	heightDone = true;
		}

		if (swingCount > SWING_ANGLE)
		{
			motorSet (SWING_POT, 0);
			printf("Arm swung, may be wrong angle");
		//	swingDone=true;
		}
		//done = swingDone && heightDone;
	}
}

void autonomous()
{

	int jumper1 = digitalRead (1);
	int jumper2 = digitalRead (2);
	int jumper3 = digitalRead (3);


	// all jumper comands here:
	//1 = out
	// 0 = in


	if ((jumper1 == 1) ) // jumper in 1 = red autonomous
	{
		armbotRed();
	}

	if (jumper2 == 0) // jumper 2 in = blue auto
	{
		//rejectionBlue();
	}





}


void driveForward(int x)
{
	int counts = 0;
	imeReset(0); // rest rightLine ime
	imeGet(0, &counts);

	while (abs(counts) < x)
	    {
	      motorSet (motor1, 127)	;
	      motorSet (motor2, 127)	;
	      motorSet (motor10, 127)	;
	      motorSet (motor9, 127)	;

	      imeGet(0, &counts); // keep getting the value
	    }

	motorSet (motor1, -7)	; // no inertia
	motorSet (motor2, -7)	;
	motorSet (motor10, -7)	;
	motorSet (motor9, -7)	;
	delay (65);

	motorSet (motor1, 0)	;
	motorSet (motor2, 0)	;
	motorSet (motor10, 0)	;
	motorSet (motor9, 0)	;
	delay(200);

}

void driveBack(int x)
{
	int counts = 0;
	imeReset(0); // rest rightLine ime
	imeGet(0, &counts);

	while (abs(counts) < x)
	 {
	   motorSet (motor1, -100) ;
	   motorSet (motor2, -100) ;
	   motorSet (motor10, -100) ;
	   motorSet (motor9, -100) ;

       imeGet(0, &counts); // keep getting the value
	}

	motorSet (motor1, 7)	; // no inertia
	motorSet (motor2, 7)	;
	motorSet (motor10, 7)	;
	motorSet (motor9, 7)	;
	delay (65);


	motorStop (motor1);
	motorStop (motor2);
	motorStop (motor10);
	motorStop (motor9);
	delay (200);
}

void turnRight(int x)
{
	int counts = 0;
	imeReset(0); // rest rightLine ime
	imeGet(0, &counts);

	while (abs(counts) < x)
	 {
		motorSet (motor1, -64) ;
		motorSet (motor2, -64) ;
		motorSet (motor10, 64) ;
		motorSet (motor9, 64) ;

		imeGet(0, &counts); // keep getting the value
	 }

	motorSet (motor1, 10)	; // no inertia
	motorSet (motor2, 10)	;
	motorSet (motor10, -10)	;
	motorSet (motor9, -10)	;
	delay (45);

	motorStop (motor1);
	motorStop (motor2);
	motorStop (motor10);
	motorStop (motor9);
	delay (200);
}

void turnLeft(int x)
{
	int counts = 0;
	imeReset(0); // rest rightLine ime
	imeGet(0, &counts);

	while (abs(counts) < x)
	 {
		motorSet (motor1, 64) ;
		motorSet (motor2, 64) ;
		motorSet (motor10, -64) ;
		motorSet (motor9, -64) ;

		imeGet(0, &counts); // keep getting the value
	 }

	motorSet (motor1, -10)	; // no inertia
	motorSet (motor2, -10)	;
	motorSet (motor10, 10)	;
	motorSet (motor9, 10)	;
	delay (45);

	motorStop (motor1);
	motorStop (motor2);
	motorStop (motor10);
	motorStop (motor9);
	delay (200);
}

void turnRightSlowDead ()
{
	motorSet (motor1, -50) ;
	motorSet (motor2, -50) ;
	motorSet (motor10, 50) ;
	motorSet (motor9, 50) ;
}



void turnLeftSlowDead ()
{
	motorSet (motor1, 40) ;
	motorSet (motor2, 40) ;
	motorSet (motor10, -40) ;
	motorSet (motor9, -40) ;
}





void stopDrive()
{
	motorStop (motor1);
	motorStop (motor2);
	motorStop (motor10);
	motorStop (motor9);
	delay (200);
}

void stopAll()
{
	motorStop (motor1);
	motorStop (motor2);
	motorStop (ARM_MOTOR1);
	motorStop (ARM_MOTOR2);
	motorStop (motor5);
	motorStop (motor6);
	motorStop (ARM_MOTOR3);
	motorStop (ARM_MOTOR4);
	motorStop (motor9);
	motorStop (motor10);
}

void stopIntake()
{
	motorStop (motor5);
	motorStop (motor6);
}




void armUpDead()
{

		motorSet (ARM_MOTOR1, -127) ; // arm up
		motorSet (ARM_MOTOR2, 127) ;
		motorSet (ARM_MOTOR3, -127) ;
		motorSet (ARM_MOTOR4, 127) ;
}

void armDownDead()
{

		motorSet (ARM_MOTOR1, 127) ; // arm Down
		motorSet (ARM_MOTOR2, -127) ;
		motorSet (ARM_MOTOR3, 127) ;
		motorSet (ARM_MOTOR4, -127) ;
}

void armUpTime(int x)
{


	motorSet (ARM_MOTOR1, -127) ; // arm up
	motorSet (ARM_MOTOR2, 127) ;
	motorSet (ARM_MOTOR3, -127) ;
	motorSet (ARM_MOTOR4, 127) ;

	delay (x);

		armUpTrim();
}

void armDownTime(int x)
{


	motorSet (ARM_MOTOR1, 127) ; // arm Down
	motorSet (ARM_MOTOR2, -127) ;
	motorSet (ARM_MOTOR3, 127) ;
	motorSet (ARM_MOTOR4, -127) ;

	delay (x);

		armDownTrim();
}

void armUpEnc(int x)
{
	int encoder = 1;
	//int counts = encoderGet(encoder);

	//while (abs(counts) < x)
	{
		motorSet (ARM_MOTOR1, -127) ; // arm up
		motorSet (ARM_MOTOR2, 127) ;
		motorSet (ARM_MOTOR3, -127) ;
		motorSet (ARM_MOTOR4, 127) ;
	//	counts = encoderGet(encoder); //keep getting the value
	}

	armUpTrim();
	delay (300);
}

void armDownEnc(int x)
{
	int counts = encoderGet(encoder);

	while (abs(counts) < x)
	{
		motorSet (ARM_MOTOR1, 127) ; // arm down
		motorSet (ARM_MOTOR2, -127) ;
		motorSet (ARM_MOTOR3, 127) ;
		motorSet (ARM_MOTOR4, -127) ;
		counts = encoderGet(encoder);//keep getting the value
	}

	armDownTrim();
	delay (300);
}

void armUpTrim()
{
	motorSet (ARM_MOTOR1, -10) ; // arm up
	motorSet (ARM_MOTOR2, 10) ;
	motorSet (ARM_MOTOR3, -10) ;
	motorSet (ARM_MOTOR4, 10) ;
}

void armDownTrim ()

{
	motorSet (ARM_MOTOR1, 20) ; // arm up
	motorSet (ARM_MOTOR2, -20) ;
	motorSet (ARM_MOTOR3, 20) ;
	motorSet (ARM_MOTOR4, -20) ;
}



void stopArm () // trim
{
	motorSet (ARM_MOTOR1, -10) ; // arm up
	motorSet (ARM_MOTOR2, 10) ;
	motorSet (ARM_MOTOR3, -10) ;
	motorSet (ARM_MOTOR4, 10) ;
}


void armbotRed()
{
	int wallHeightU = 300; // idk
	int wallHeight = 1000; // idk
	int floorHeightU = 1700; // idk
	int floorHeight = 1600;

	int pot = analogRead (8);
	int halfDist = 900; // encoder value




	armUpEnc(wallHeightU);
	turnRight(halfDist);
	armDownTime (300);
	armUpEnc(wallHeightU); // pick it up
	turnLeft(halfDist);
	//armDown(floorHeightU);
	turnLeft(halfDist);
	armDownTime (300); // score the spike!
	armUpEnc(floorHeightU);
	turnRight(halfDist);
	//////////////////////////////////// and loop/////////////////////////////



	//end of routine
	stopAll () ;
	delay(60000);///////////////////////////////////////////////////////////////////////////////////


}

void armbotBlue()
{


	stopAll () ;
	delay(60000);///////////////////////////////////////////////////////////////////////////////////


}








/*
  // encoder values get code (manual push)

	int counts = 0;
	imeReset(0); // rest right ime
	imeGet(0, &counts);
	int button = digitalRead (2);

	while (1 == 1)
		{
			printf("%d\r\n", counts);
			imeGet(0, &counts);
			delay (200);
			button = digitalRead(2);

			if (button == 0)
			{
				imeReset(0); // rest right ime
			}
		}


  */

