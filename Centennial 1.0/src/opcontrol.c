/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Copyright (c) 2011-2013, Purdue University ACM SIG BOTS.
 * All rights reserved.
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
#include <math.h> // round()

//TODO make enum, use names that describe purpose
//joysticks
#define joystick1 1
#define joystick2 2
#define joystickchannel2 2
#define joystickchannel3 3
#define joystickchannel5 5
#define joystickchannel6 6
#define joystickchannel8 8

#define RECORDING 1 //if non zero print encoder values every .5 seconds

typedef enum {
	MOTOR_DRIVE_RIGHT_LINE_BACK =1, // = rightLine back
	MOTOR_DRIVE_RIGHT_LINE_FRONT= 2, // = rightLine front
	ARM_MOTOR1 =3, // = rightLine arm down
	ARM_MOTOR2 =4, // = rightLine arm up
	MOTOR_RIGHT_LINE_INTAKE =5, // = rightLine intake
	MOTOR_LEFT_LINE_INTAKE =6, // = leftLine intake
	ARM_MOTOR3 =7, // = leftLine arm up
	ARM_MOTOR4 =8, // = leftLine arm down
	MOTOR_DRIVE_LEFT_LINE_FRONT =9, // = leftLine front
	MOTOR_DRIVE_LEFT_LINE_BACK =10 // = leftLine back
} Motor;
//motors
//old replaced by enum
/*
#define MOTOR_DRIVE_RIGHT_LINE_BACK 1 // = right back
#define MOTOR_DRIVE_RIGHT_LINE_FRONT 2 // = right front
#define ARM_MOTOR1 3 // = right arm down
#define ARM_MOTOR2 4 // = right arm up
#define MOTOR_RIGHT_LINE_INTAKE 5 // = right intake
#define MOTOR_LEFT_LINE_INTAKE 6 // = left intake
#define ARM_MOTOR3 7 // = left arm up
#define ARM_MOTOR4 8 // = left arm down
#define MOTOR_DRIVE_LEFT_LINE_FRONT 9 // = left front
#define MOTOR_DRIVE_LEFT_LINE_BACK 10 // = left back
*/


// pot height settings potpot
//int floorHeight = 380;
int baseHeight = 0;
int wallHeight = 0;
int lvl1Height = 0;

Encoder encoder1;

const int JOYSTICK_MAX = 127;
const int DRIVE_MAX_SPEED = 127;
const int ARM_MAX_SPEED = 64;
/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the schedular is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
void operatorControl()
{

	encoder1= encoderInit (2,3,false);
	while (1)
		{

#if RECORDING
			int pot = analogRead (8);
			printf("pot:%d\r\n", pot);

			int encodeCount = encoderGet(encoder1);
			printf("enc:%d\r\n", encodeCount);
			delay(500);
#endif
			//TODO:Jumper 1 is currently used in mode switch recommend magic key combo
			if (digitalRead(1) == LOW) // jumper 1 in = autonomous
				{
					autonomous ();
				}


	// declare joystick inputs/////////////////////////////////////////////////////////////////////////////////
			int armChannel = joystickGetAnalog(1, 2); // (joystick 1, channel 2)
			int driveChannel = joystickGetAnalog(1, 4); // (joystick 1, channel 4)
			float armPercent = (float)armChannel/(float)JOYSTICK_MAX;
			float drivePercent = (float)driveChannel/(float)JOYSTICK_MAX;

			int driveSpeed = round(drivePercent*DRIVE_MAX_SPEED);
			int armSpeed = round(armPercent *ARM_MAX_SPEED);

	// drive functions////////////////////////////////////////////////////////////////////////////////////////
			motorSet (MOTOR_DRIVE_RIGHT_LINE_BACK, driveChannel); // right drive back
			motorSet (MOTOR_DRIVE_RIGHT_LINE_FRONT, driveChannel); // right drive front
			motorSet (MOTOR_DRIVE_LEFT_LINE_BACK, driveChannel); // left drive abck
			motorSet (MOTOR_DRIVE_LEFT_LINE_FRONT, driveChannel); // left drive front

	// arm function/////////////////////////////////////////////////////////////////////////////////////////////

			motorSet (ARM_MOTOR1, armChannel) ;// arm down up
			motorSet (ARM_MOTOR2, armChannel) ;// arm right up
			motorSet (ARM_MOTOR3, armChannel) ;// arm left
			motorSet (ARM_MOTOR4, armChannel) ;// arm left down



	}// operator close bracket
}// end of armbot





