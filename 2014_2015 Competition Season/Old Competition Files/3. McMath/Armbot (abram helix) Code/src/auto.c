// test gladstone

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
#include <stdbool.h>
#include "auto.h"


void turnRight(int x);
void turnRightSlow(int x);
void turnLeftSlow(int x);
void turnLeftSlow(int x);
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



////WARNING WARNING WARNING WARNING WARNING WARNING
////
//SET TO 0 for COMEPETITION, removes delays that make it easy to see what's going on
////
#define DEBUG 1

//motors
typedef enum {
	MOTOR_DRIVE_RIGHT_LINE_BACK =1, // = rightLine back
	MOTOR_DRIVE_RIGHT_LINE_FRONT= 2, // = rightLine front
	ARM_MOTOR3 =3, // = rightLine arm down
	ARM_MOTOR4 =4, // = rightLine arm up
	MOTOR_RIGHT_LINE_INTAKE =5, // = rightLine intake
	MOTOR_LEFT_LINE_INTAKE =6, // = leftLine intake
	ARM_MOTOR7 =7, // = leftLine arm up
	ARM_MOTOR8 =8, // = leftLine arm down
	MOTOR_DRIVE_LEFT_LINE_FRONT =9, // = leftLine front
	MOTOR_DRIVE_LEFT_LINE_BACK =10 // = leftLine back
} Motor;

typedef enum{
	BLUE_RESERVED0 =0,
	BLUE_RESERVED1 =1,
	BLUE_RESERVED2 =2,
	BLUE_RESERVED3 =3,
	RED_RESERVED4 =4,
	RED_RESERVED5 =5,
	RED_RESERVED6 =6,
	RED_RESERVED7 =7
} AutonomousMode;

const int REVERSE_DRIVE_SPEED = -100;


static const int MOTOR_MAX = 64;
const int SPIKE_OFFSET =442; //There are ~ 442 =avg(458,442,423,446) ticks per spike

const Motor SWING_MOTOR = MOTOR_RIGHT_LINE_INTAKE;//TODO set
const Motor GRIP_MOTOR = MOTOR_LEFT_LINE_INTAKE;//TODO set

const int MOTOR_TURN_SPEED =64;
const int SWING_MOTOR_SPEED = 64;
const int GRIP_MOTOR_SPEED = 64;

const int SWING_POT_PIN = 8; //TODO set
const int SWING_ANGLE = 200;  //TODO set

Encoder TOWER_ENCODER; // declared in main.h, initialized in init.c

void armTest();
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
void autonomous()
{
	// jumper in = 1
	int jumper1 = digitalRead (1);
	int jumper2 = digitalRead (2);
	int jumper3 = digitalRead (3);
	encoderReset(TOWER_ENCODER);
	if (jumper2 == 1) // this is gordons last sec brute force method cuz theres no time //jumper 2 in
	{// jumper 2 in
		armbotRed();
	}

	AutonomousMode mode = (jumper3) | (jumper2 << 1) | (jumper1 <<2);
	printf("Entered autonomous mode %d\n\r",mode);

	encoderReset(TOWER_ENCODER);
	printf("ENCODER %x reset\n\r",TOWER_ENCODER);
	//jumper 1 = MSB // jumper 3 = LSB
	armbotRed();
	//armTest();
	/*
	switch(mode)
	{
	case BLUE_RESERVED0:  // 0 0 0
		armbotRed();;
		break;

	case BLUE_RESERVED1:  // 0 0 1
		stackEm();
		break;

	case BLUE_RESERVED2:  // 0 1 0
		stackEm();
		break;

	case BLUE_RESERVED3:  // 0 1 0
		//mode3()
		break;
	case RED_RESERVED4:  // 1 0 0
			stackEm();
				break;
	case RED_RESERVED5:  // 1 0 1
			stackEm();
				break;
	case RED_RESERVED6:  // 1 1 0
		stackEm();
				break;

	default:
		printf("Jumpers are set to unkown configuration\n\r");
		stackEm();
		break;
	}
	*/


	// all jumper comands here:
	//1 = out
	// 0 = in

/*
	if ((jumper1 == 1) ) // jumper in 1 = red autonomous
	{
		armbotRed();
	}

	if (jumper2 == 0) // jumper 2 in = blue auto
	{
		//rejectionBlue();
	}
*/

	//allstop
	stopAll();
	delay(600000);



}

void armTest()
{
	armUpTime(3000);
	armDownTime(3000);
}

///Centenial spike stack routine
void stackEm()
{
	const int SPIKE_COUNT =5;

	///HI GORDON, set the height for each spike here
	//TODO set to real encoder values
	//You may need to modify helix down for height, you will definately need to modify it for rotation
	//You need to un comment the rotation (pot) if statement in the helix routines.

	armHelixDown();
	grip();
	armHelixUpEnc(460,100);
	releaseGrip();

	armHelixDown();
	grip();
	armHelixUpEnc(920,100);
	releaseGrip();

	armHelixDown();
	grip();
	armHelixUpEnc(1200,100);
	releaseGrip();



	}


void grip()
{
	printf("Grip() NOT IMPLEMENTED\n\r");
	motorSet (GRIP_MOTOR, -GRIP_MOTOR_SPEED);
}

void releaseGrip()
{
	printf("releaseGript() NOT IMPLEMENTED\n\r");
	motorSet (GRIP_MOTOR, GRIP_MOTOR_SPEED);
}

///Move to loading height
void armHelixDown()
{
	printf("Helix Down\r\n");
	motorSet (SWING_MOTOR, -SWING_MOTOR_SPEED);
	armDownDead(); // power all lift motors to max

	//Swingdone is true for testing, set it back for production
	bool done =false, swingDone =true, heightDone =false;
	int towerCount=0, swingCount=0;


	while(!done)
	{
		swingCount = analogRead (SWING_POT_PIN); //4095 is 5 volts
		towerCount = encoderGet(TOWER_ENCODER);//documentation claims 360 ticks in 1 revolution

		//Should not be quite zero
		int threshold = SPIKE_OFFSET*0.01;


		printf("Height stop: %d < %d \n\r ",towerCount,threshold);

		if (towerCount < threshold) //1.25 is an estimate for the load height
		{
			stopArm();
			printf("Tower lowered to load position\n\r");
			heightDone = true;
#if DEBUG
			delay(5000);
#endif
		}

//		if (swingCount < 100) //TODo no measurements for pot yet
//		{
//			motorSet (SWING_POT_PIN, 0);
//			printf("Arm swung, may be wrong angle\n");
//			swingDone=true;
//		}
		done = swingDone && heightDone;
	}
}

void armHelixUpEnc (int enc, int potTargetValue)
{
	//moved to init once
	//const Encoder TOWER_ENCODER = encoderInit (2,3,false);
	//TOWER_ENCODER = encoderInit (TOWER_ENCODER_TOP_CHANNEL,TOWER_ENCODER_BOTTOM_CHANNEL,false);
	armUpDead(); // power all lift motors to max
	motorSet (SWING_MOTOR, SWING_MOTOR_SPEED);

	//TODO hack, set wingDone true
	bool done =false, swingDone =true, heightDone =false;

	int towerCount=0, swingCount=0;
	printf("Arm Helix up \n\r");
	int threshold =enc;
	while(!done)
	{
		swingCount = analogRead (SWING_POT_PIN); //4095 is 5 volts
		towerCount = encoderGet(TOWER_ENCODER);//documentation claims 360 ticks in 1 revolution
		printf("Height stop: %d > %d \n\r ",towerCount,threshold);

		if (towerCount > threshold)
		{
			stopArm();
			printf("Tower raised, might fall, motor stopped\n\r");
			heightDone = true;
		}

//		if (swingCount > potTargetValue)
//		{
//			motorSet (SWING_MOTOR, 0);
//			printf("Arm swung, may be wrong angle\n");
//			swingDone=true;
//		}
		done = swingDone && heightDone;
	}
#if DEBUG
	delay(5000);
#endif
}

void armHelixUp (double spikeNumber)
{
	//moved to init once
	//const Encoder TOWER_ENCODER = encoderInit (2,3,false);
	//TOWER_ENCODER = encoderInit (TOWER_ENCODER_TOP_CHANNEL,TOWER_ENCODER_BOTTOM_CHANNEL,false);
	//armUpDead(); // power all lift motors to max
	//motorSet (SWING_MOTOR, SWING_MOTOR_SPEED);

	//TODO hack, set wingDone true
	bool done =false, swingDone =true, heightDone =false;
	int threshold = SPIKE_OFFSET*.8 * spikeNumber;
	armHelixUpEnc(threshold,200);
}



void driveForward(int x)
{
	int counts = 0;
	imeReset(0); // rest rightLine ime
	imeGet(0, &counts);

	while (abs(counts) < x)
	{
		motorSet(MOTOR_DRIVE_RIGHT_LINE_BACK, MOTOR_MAX);
		motorSet(MOTOR_DRIVE_RIGHT_LINE_FRONT, MOTOR_MAX);
		motorSet(MOTOR_DRIVE_LEFT_LINE_BACK, MOTOR_MAX);
		motorSet(MOTOR_DRIVE_LEFT_LINE_FRONT, MOTOR_MAX);

		imeGet(0, &counts); // keep getting the value
	}

	motorSet (MOTOR_DRIVE_RIGHT_LINE_BACK, -7)	; // no inertia
	motorSet (MOTOR_DRIVE_RIGHT_LINE_FRONT, -7)	;
	motorSet (MOTOR_DRIVE_LEFT_LINE_BACK, -7)	;
	motorSet (MOTOR_DRIVE_LEFT_LINE_FRONT, -7)	;
	delay (65);

	motorSet (MOTOR_DRIVE_RIGHT_LINE_BACK, 0)	;
	motorSet (MOTOR_DRIVE_RIGHT_LINE_FRONT, 0)	;
	motorSet (MOTOR_DRIVE_LEFT_LINE_BACK, 0)	;
	motorSet (MOTOR_DRIVE_LEFT_LINE_FRONT, 0)	;
	delay(200);

}

void driveBack(int x)
{
	int counts = 0;
	imeReset(0); // rest rightLine ime
	imeGet(0, &counts);

	while (abs(counts) < x)
	{
		motorSet (MOTOR_DRIVE_RIGHT_LINE_BACK, REVERSE_DRIVE_SPEED) ;
		motorSet (MOTOR_DRIVE_RIGHT_LINE_FRONT, REVERSE_DRIVE_SPEED) ;
		motorSet (MOTOR_DRIVE_LEFT_LINE_BACK, REVERSE_DRIVE_SPEED) ;
		motorSet (MOTOR_DRIVE_LEFT_LINE_FRONT, REVERSE_DRIVE_SPEED) ;

		imeGet(0, &counts); // keep getting the value
	}

	motorSet (MOTOR_DRIVE_RIGHT_LINE_BACK, 7)	; // no inertia
	motorSet (MOTOR_DRIVE_RIGHT_LINE_FRONT, 7)	;
	motorSet (MOTOR_DRIVE_LEFT_LINE_BACK, 7)	;
	motorSet (MOTOR_DRIVE_LEFT_LINE_FRONT, 7)	;
	delay (65);


	motorStop (MOTOR_DRIVE_RIGHT_LINE_BACK);
	motorStop (MOTOR_DRIVE_RIGHT_LINE_FRONT);
	motorStop (MOTOR_DRIVE_LEFT_LINE_BACK);
	motorStop (MOTOR_DRIVE_LEFT_LINE_FRONT);
	delay (200);
}

void turnRight(int x)
{

	int pot = analogRead (8);

		while (pot < x)
		{
			motorSet (1, -127) ;
			motorSet (2, -127) ;
			motorSet (9, 127) ;
			motorSet (10, 127) ;
			pot = analogRead (8);
		}

	motorStop (1);
	motorStop (2);
	motorStop (9);
	motorStop (10);

	delay (200);
}

void turnLeft(int x)
{

	int pot = analogRead (8);

		while (pot > x)
		{
			motorSet (1, 127) ;
			motorSet (2, 127) ;
			motorSet (9, -127) ;
			motorSet (10, -127) ;
			pot = analogRead (8);
		}

	motorStop (1);
	motorStop (2);
	motorStop (9);
	motorStop (10);

	delay (200);
}

void turnRightSlow(int x)
{

	int pot = analogRead (8);

		while (pot < x)
		{
			printf("Turn right pot %d < %d \r\n",pot,x);
			motorSet (1, 80) ;
			motorSet (2, -80) ;
			motorSet (9, -80) ;
			motorSet (10, -80) ;
			pot = analogRead (8);
		}

	motorStop (1);
	motorStop (2);
	motorStop (9);
	motorStop (10);

	delay (200);
}

void turnLeftSlow(int x)
{

	int pot = analogRead (8);

		while (pot < x)
		{
			printf("Turn left pot %d < %d \r\n",pot,x);
			motorSet (1, -80) ;
			motorSet (2, -80) ;
			motorSet (9, 80) ;
			motorSet (10, 80) ;
			pot = analogRead (8);
		}

	motorStop (1);
	motorStop (2);
	motorStop (9);
	motorStop (10);

	delay (200);
}

//TODO make constants... but why are they different?
void turnRightSlowDead ()
{
	motorSet (MOTOR_DRIVE_RIGHT_LINE_BACK, -50) ;
	motorSet (MOTOR_DRIVE_RIGHT_LINE_FRONT, -50) ;
	motorSet (MOTOR_DRIVE_LEFT_LINE_BACK, 50) ;
	motorSet (MOTOR_DRIVE_LEFT_LINE_FRONT, 50) ;
}

void turnLeftSlowDead ()
{
	motorSet (MOTOR_DRIVE_RIGHT_LINE_BACK, 40) ;
	motorSet (MOTOR_DRIVE_RIGHT_LINE_FRONT, 40) ;
	motorSet (MOTOR_DRIVE_LEFT_LINE_BACK, -40) ;
	motorSet (MOTOR_DRIVE_LEFT_LINE_FRONT, -40) ;
}


void stopDrive()
{
	motorStop (MOTOR_DRIVE_RIGHT_LINE_BACK);
	motorStop (MOTOR_DRIVE_RIGHT_LINE_FRONT);
	motorStop (MOTOR_DRIVE_LEFT_LINE_BACK);
	motorStop (MOTOR_DRIVE_LEFT_LINE_FRONT);
	delay (200);
}

void stopAll()
{
	/*
	motorStop (MOTOR_DRIVE_RIGHT_LINE_BACK);
	motorStop (MOTOR_DRIVE_RIGHT_LINE_FRONT);
	motorStop (ARM_MOTOR3);
	motorStop (ARM_MOTOR4);
	motorStop (MOTOR_RIGHT_LINE_INTAKE);
	motorStop (MOTOR_LEFT_LINE_INTAKE);
	motorStop (ARM_MOTOR3);
	motorStop (ARM_MOTOR4);
	motorStop (MOTOR_DRIVE_LEFT_LINE_FRONT);
	motorStop (MOTOR_DRIVE_LEFT_LINE_BACK);
	*/
	const int MOTOR_COUNT =10;
	for(int i=1; i<MOTOR_COUNT+1;i++)
	{
		motorStop(i);
	}
}

void stopIntake()
{
	motorStop (MOTOR_RIGHT_LINE_INTAKE);
	motorStop (MOTOR_LEFT_LINE_INTAKE);
}




void armUpDead()
{

	motorSet(ARM_MOTOR3, MOTOR_MAX); // arm up
	motorSet(ARM_MOTOR4, MOTOR_MAX);
	motorSet(ARM_MOTOR7, MOTOR_MAX);
	motorSet(ARM_MOTOR8, MOTOR_MAX);
}

void armDownDead()
{

	motorSet(ARM_MOTOR3, -MOTOR_MAX); // arm Down
	motorSet(ARM_MOTOR4, -MOTOR_MAX);
	motorSet(ARM_MOTOR7, -MOTOR_MAX);
	motorSet(ARM_MOTOR8, -MOTOR_MAX);
}

void armUpTime(int millis)
{


	motorSet(ARM_MOTOR3, MOTOR_MAX); // arm up
	motorSet(ARM_MOTOR4, MOTOR_MAX);
	motorSet(ARM_MOTOR7, MOTOR_MAX);
	motorSet(ARM_MOTOR8, MOTOR_MAX);

	delay (millis);

	armUpTrim();
}

void armDownTime(int millis)
{


	motorSet(ARM_MOTOR3, -MOTOR_MAX); // arm Down
	motorSet(ARM_MOTOR4, -MOTOR_MAX);
	motorSet(ARM_MOTOR7, -MOTOR_MAX);
	motorSet(ARM_MOTOR8, -MOTOR_MAX);

	delay (millis);

	armDownTrim();
}

void armUpEnc(int x)
{

	int towerCount = encoderGet(TOWER_ENCODER);//documentation claims 360 ticks in 1 revolution
		printf("Height stop: %d > %d \n\r ",towerCount,x);

	while (towerCount > x)
	{
		motorSet(ARM_MOTOR3, MOTOR_MAX); // arm up
		motorSet(ARM_MOTOR4, MOTOR_MAX);
		motorSet(ARM_MOTOR7, MOTOR_MAX);
		motorSet(ARM_MOTOR8, MOTOR_MAX);

		towerCount = encoderGet(TOWER_ENCODER);
	}
	stopArm();

	armUpTrim();
	delay (300);
}

void armDownEnc(int x)
{

	int towerCount = encoderGet(TOWER_ENCODER);//documentation claims 360 ticks in 1 revolution
			printf("Height stop: %d > %d \n\r ",towerCount,x);

	while (towerCount > x)
	{
		motorSet(ARM_MOTOR3, -MOTOR_MAX); // arm up
		motorSet(ARM_MOTOR4, -MOTOR_MAX);
		motorSet(ARM_MOTOR7, -MOTOR_MAX);
		motorSet(ARM_MOTOR8, -MOTOR_MAX);

		towerCount = encoderGet(TOWER_ENCODER);
	}

	stopArm();

	armUpTrim();
	delay (300);
}

void armUpTrim()
{
	motorSet (ARM_MOTOR3, 10) ; // arm up
	motorSet (ARM_MOTOR4, 10) ;
	motorSet (ARM_MOTOR7, 10) ;
	motorSet (ARM_MOTOR8, 10) ;
}

void armDownTrim ()

{
	motorSet (ARM_MOTOR3, -20) ; // arm down
	motorSet (ARM_MOTOR4, -20) ;
	motorSet (ARM_MOTOR7, -20) ;
	motorSet (ARM_MOTOR8, -20) ;
}


///@deprecated
void stopArm () // trim
{
	motorSet (ARM_MOTOR3, -10) ; // arm up
	motorSet (ARM_MOTOR4, 10) ;
	motorSet (ARM_MOTOR7, -10) ;
	motorSet (ARM_MOTOR8, 10) ;
}

void intake(int x)
{


	motorSet (5, 127) ;
	motorSet (6, 127) ;

	delay (x);

	motorSet (5, 0) ;
	motorSet (6, 0) ;
}

void outtake(int x)
{


	motorSet (5, -127) ;
	motorSet (6, -127) ;

	delay (x);

	motorSet (5, 0) ;
	motorSet (6, 0) ;
}


void armbotRed()
{
	encoderReset(TOWER_ENCODER);
	printf("ENCODER %x reset\n\r",TOWER_ENCODER);

	int stackRot = 3360;
	int loadRot = 100;
	int loadHeight = 70;
	int loadHeightHigh = 376 +30; //30 is error
	int wallHeightU = loadHeightHigh; // idk
	int wallHeight = loadHeight; // idk
	int spike1 = -6; // heights for the individual spikes!
	int spike2 = 450; //n*(offset+ drift)
	//150 = 450-300 release height
	int spike3 = 800;
	int spike4 = 0;
	int spike5 = 0;
	int spike6 = 0;


	int pot = analogRead (8);
	int wall = 980; //pot value

	int stack = 3360; // pot value
	int center = (stack-wall)/2;

/////////////////////////////////////spike 1//////////////////////////////////////////

	armUpEnc(wallHeight);
	turnRightSlow(wall);
	intake(300); //clamp it!
	armUpEnc(wallHeightU); // pick it up
	turnLeftSlow(stack); // rotate to stack
	armDownEnc(spike1); //score the spike!
	outtake(300);
	armUpEnc(spike1 + 500);
	turnRightSlow(center);

	// and loop!/////////////////////spike 2//////////////////////////

	armUpEnc(wallHeightU);
	turnRightSlow(wall);
	intake(300); //clamp it!
	armUpEnc(spike2 + 100); // pick it up + go abit higher than spike height!
	turnLeftSlow(stack); // rotate to stack
	delay(500);  // wait for swing to stop!
	armDownEnc(spike1); //score the spike!
	outtake(300);
	armUpEnc(spike2 + 500);
	turnRightSlow(center);




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
