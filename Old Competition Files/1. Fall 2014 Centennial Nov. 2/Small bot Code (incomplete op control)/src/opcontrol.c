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

//joysticks
#define joystick1 1
#define joystick2 2
#define joystickchannel2 2
#define joystickchannel3 3
#define joystickchannel5 5
#define joystickchannel6 6
#define joystickchannel8 8


//motors
#define motor1 1 // = right back
#define motor2 2 // = right front
#define motor3 3 // = right arm down
#define motor4 4 // = right arm up
#define motor5 5 // = right intake
#define motor6 6 // = left intake
#define motor7 7 // = left arm up
#define motor8 8 // = left arm down
#define motor9 9 // = left front
#define motor10 10 // = left back


// pot height settings potpot
//int floorHeight = 380;
int baseHeight = 0;
int wallHeight = 0;
int lvl1Height = 0;

static Encoder encoder1;



void operatorControl()
{

	//encoder1= encoderInit (2,3,false);
	while (1)
		{

			//int pot = analogRead (8);
			//printf("%d\r\n", pot);

			int encodeCount = encoderGet(encoder1);
			printf("%d\r\n", encodeCount);


			if (digitalRead(1) == LOW) // jumper 1 in = autonomous
				{
					autonomous ();
				}


	// declare joystick inputs/////////////////////////////////////////////////////////////////////////////////
			int channel2 = joystickGetAnalog(1, 2); // (joystick 1, channel 2)
			int channel3 = joystickGetAnalog(1, 3); // (joystick 1, channel 4)

	// drive functions////////////////////////////////////////////////////////////////////////////////////////
			motorSet (motor1, channel2); // right drive back
			motorSet (motor2, channel2); // right drive front
			motorSet (motor10, channel3); // left drive abck
			motorSet (motor9, channel3); // left drive front

	// arm function/////////////////////////////////////////////////////////////////////////////////////////////



const int INPUT_RIGHT_TRIGGER = 6;
const int INPUT_LEFT_TRIGGER = 5;
const int  ARM_POWER = 127;
const int  INTAKE_POWER = 127;
			int rightTriggerUp = joystickGetDigital(1,INPUT_RIGHT_TRIGGER,JOY_UP);
			int rightTriggerDown = joystickGetDigital(1,INPUT_RIGHT_TRIGGER,JOY_DOWN);

			int leftTriggerUp = joystickGetDigital(1,INPUT_LEFT_TRIGGER,JOY_UP);
			int leftTriggerDown = joystickGetDigital(1,INPUT_LEFT_TRIGGER,JOY_DOWN);
			if(rightTriggerUp)
			{
				motorSet (motor4, ARM_POWER) ;// arm right up
				motorSet (motor3, ARM_POWER) ;// arm right down
				motorSet (motor8, ARM_POWER) ;// arm left down
				motorSet (motor7, ARM_POWER) ;// arm left up
			}else
			{
								motorSet (motor4, 1) ;// arm right up
								motorSet (motor3, 1) ;// arm right down
								motorSet (motor8, 1) ;// arm left down
								motorSet (motor7, 1) ;// arm left up
			}
			if(rightTriggerDown)
			{
							motorSet (motor4, -ARM_POWER) ;// arm right up
							motorSet (motor3,-ARM_POWER) ;// arm right down
							motorSet (motor8, -ARM_POWER) ;// arm left down
							motorSet (motor7, -ARM_POWER) ;// arm left up
			}

			if(leftTriggerDown)
			{
										motorSet (motor6, - INTAKE_POWER) ;// arm right up
										motorSet (motor5,-INTAKE_POWER) ;// arm right down
			}
			else if(leftTriggerUp)
			{
				motorSet (motor6,  INTAKE_POWER) ;// arm right up
				motorSet (motor5, INTAKE_POWER) ;// arm right down
			}else
			{
				motorSet (motor6,  0) ;// arm right up
				motorSet (motor5, 0) ;// arm right down
			}


#define motor5 5 // = right intake
#define motor6 6 // = left intake


	}// operator close bracket
}// end of armbot





