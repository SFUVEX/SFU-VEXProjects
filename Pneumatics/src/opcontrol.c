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
#include "botConstants.h"
#include <stdbool.h>
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
#define joystickchannel7 7
#define joystickchannel8 8

// pot height settings
const int GOAL_HEIGHT = 1550;
const int FLOOR_HEIGHT = 300;
const int WALL_HEIGHT = 1000;
const int TRIM = 50;

//dummy variables
int dummyTrim = 1;
int armMax = 0;
int armMin = 0;
int armCenter = 0;

void operatorControl()
{

	while (true)
	{

		//int pot = analogRead(8);
		//printf("%d\r\n", pot);
		if (digitalRead(1) == LOW) // jumper 1 in = autonomous
		{
			autonomous();
		}
		//flashLED();
// declare joystick inputs/////////////////////////////////////////////////////////////////////////////////
		int channel2 = joystickGetAnalog(1, 2); // (joystick 1, channel 2) //ry
		int channel3 = joystickGetAnalog(1, 3); // (joystick 1, channel 3) //ly

// drive functions////////////////////////////////////////////////////////////////////////////////////////
		motorSet(MOTOR_DRIVE_RIGHT_BACK, channel2); // right drive back
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, channel2); // right drive front
		motorSet(MOTOR_ARM_LEFT_BACK, channel3); // left drive abck
		motorSet(MOTOR_ARM_LEFT_FRONT, channel3); // left drive front




// arm function/////////////////////////////////////////////////////////////////////////////////////////////
		if (joystickGetDigital(joystick1, joystickchannel6, JOY_UP)) // arm up
		{
			motorSet(MOTOR_ARM_RIGHT_TOP, -127);
			motorSet(MOTOR_ARM_LEFT_TOP, 127);
			motorSet(MOTOR_ARM_RIGHT_BOTTOM, -127);
			motorSet(MOTOR_ARM_LEFT_BOTTOM, 127);
			motorSet(MOTOR_ARM_RIGHT_MID, -127);
			motorSet(MOTOR_ARM_LEFT_MID, 127);
		}

		else if (joystickGetDigital(joystick1, joystickchannel6, JOY_DOWN)) // arm down
		{
			motorSet(MOTOR_ARM_RIGHT_TOP, 127);
			motorSet(MOTOR_ARM_LEFT_TOP, -127);
			motorSet(MOTOR_ARM_RIGHT_BOTTOM, 127);
			motorSet(MOTOR_ARM_LEFT_BOTTOM, -127);
			motorSet(MOTOR_ARM_RIGHT_MID, 127);
			motorSet(MOTOR_ARM_LEFT_MID, -127);
		}
		else //Lift Idle
		{
			motorSet(MOTOR_ARM_RIGHT_TOP, TRIM);
			motorSet(MOTOR_ARM_LEFT_TOP, -TRIM);
			motorSet(MOTOR_ARM_RIGHT_BOTTOM, TRIM);
			motorSet(MOTOR_ARM_LEFT_BOTTOM, -TRIM);
			motorSet(MOTOR_ARM_RIGHT_MID, TRIM);
			motorSet(MOTOR_ARM_LEFT_MID, -TRIM);
		}

		if(joystickGetDigital(joystick1, joystickchannel7, JOY_LEFT)) // arm left
		{
			//trigger pneumatic cylinder
			digitalWrite(11, LOW);
		}

		if(joystickGetDigital(joystick1, joystickchannel7, JOY_RIGHT)) // arm right
		{
			//trigger retraction of pneumatic cylinder
			digitalWrite(11, HIGH);
		}

		if(joystickGetDigital(joystick1, joystickchannel7, JOY_UP)) // intake forward
		{
			digitalWrite(12, HIGH);
		}

		if(joystickGetDigital(joystick1, joystickchannel7, JOY_DOWN)) // intake backward
		{
			digitalWrite(12, LOW);
		}

		delay(20);
	} // while(true) close bracket

} // operator close bracket
