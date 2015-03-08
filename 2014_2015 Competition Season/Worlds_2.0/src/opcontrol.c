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
#define joystickchannel8 8


// pot height settings
const int GOAL_HEIGHT = 1550;
const int FLOOR_HEIGHT = 300;
const int WALL_HEIGHT = 1000;

//dummy variables
int dummyTrim = 1;
int armMax = 0;
int armMin = 0;
int armCenter = 0;

//2nd joystick controls
void twoDrivers();

// cubic drive
void cubicDrive();

void operatorControl()
{

	// go to autonomous mode testing
	//if (digitalRead(1) == LOW) // jumper 1 in = autonomous
	//	{
	//		autonomous ();
	//	}

	if (digitalRead(2) == LOW) // jumper 2 in = two drivers
	{
		twoDrivers();

	}

	//if (digitalRead(3) == LOW)// jumper 3 in = cubic drive
	//	{
	//		cubicDrive ();
	//	}

	while (true)
	{

		int pot = analogRead(8);
		printf("%d\r\n", pot);
		if (digitalRead(1) == LOW) // jumper 1 in = autonomous
		{
			autonomous();
		}

// declare joystick inputs/////////////////////////////////////////////////////////////////////////////////
		int channel2 = joystickGetAnalog(1, 2); // (joystick 1, channel 2)
		int channel3 = joystickGetAnalog(1, 3); // (joystick 1, channel 3)

// drive functions////////////////////////////////////////////////////////////////////////////////////////
		motorSet(MOTOR_DRIVE_RIGHT_BACK, channel2); // right drive back
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, channel2); // right drive front
		motorSet(MOTOR_ARM_LEFT_BACK, channel3); // left drive abck
		motorSet(MOTOR_ARM_LEFT_FRONT, channel3); // left drive front

// arm function/////////////////////////////////////////////////////////////////////////////////////////////
		if (joystickGetDigital(joystick1, joystickchannel6, JOY_UP)) // arm up
		{
			motorSet(MOTOR_ARM_RIGHT_TOP, 127); // arm right up
			motorSet(MOTOR_ARM_LEFT_TOP, -127); // arm left
			motorSet(MOTOR_ARM_RIGHT_BOTTOM, -127); // arm down up
			motorSet(MOTOR_ARM_LEFT_BOTTOM, 127); // arm left down
		}

		else if (joystickGetDigital(joystick1, joystickchannel6, JOY_DOWN)) // arm down
		{
			motorSet(MOTOR_ARM_RIGHT_TOP, -127); // arm right up
			motorSet(MOTOR_ARM_LEFT_TOP, 127); // arm left up
			motorSet(MOTOR_ARM_RIGHT_BOTTOM, 127); // arm right down
			motorSet(MOTOR_ARM_LEFT_BOTTOM, -127); // arm left down
		}
		else // trim arm up
		{
			if (pot > 1600) // high trim
			{
				motorSet(MOTOR_ARM_RIGHT_TOP, 10);
				motorSet(MOTOR_ARM_LEFT_TOP, -10);
				motorSet(MOTOR_ARM_RIGHT_BOTTOM, -10);
				motorSet(MOTOR_ARM_LEFT_BOTTOM, 10);
			}

			else if (pot < 300) //  trim down when arm is low
			{
				motorSet(MOTOR_ARM_RIGHT_TOP, -7);
				motorSet(MOTOR_ARM_LEFT_TOP, 7);
				motorSet(MOTOR_ARM_RIGHT_BOTTOM, 7);
				motorSet(MOTOR_ARM_LEFT_BOTTOM, -7);
			}

			else //trim normal
			{
				motorSet(MOTOR_ARM_RIGHT_TOP, 7);
				motorSet(MOTOR_ARM_LEFT_TOP, -7);
				motorSet(MOTOR_ARM_RIGHT_BOTTOM, -7);
				motorSet(MOTOR_ARM_LEFT_BOTTOM, 7);
			}

		}

// intake functions/////////////////////////////////////////////////////////////////////////////////////
		if (joystickGetDigital(joystick1, joystickchannel5, JOY_UP)) //intake
		{
			motorSet(MOTOR_INTAKE_RIGHT, 127); // arm right
			motorSet(MOTOR_INTAKE_LEFT, -127); // arm left
		}

		else if (joystickGetDigital(joystick1, joystickchannel5, JOY_DOWN)) // outtake
		{
			motorSet(MOTOR_INTAKE_RIGHT, -127); // arm right
			motorSet(MOTOR_INTAKE_LEFT, 127); // arm left
		}
		else
		{
			motorStop(MOTOR_INTAKE_RIGHT); // arm right
			motorStop(MOTOR_INTAKE_LEFT); // arm left
		}

// shortcut manual overrides and cancel ////////////////////////////////////////////////////////////////////////
		if (joystickGetDigital(joystick1, joystickchannel6, JOY_UP)) // manual button override
		{
			armMax = 0;
			armMin = 0;
			armCenter = 0;
		}

		if (joystickGetDigital(joystick1, joystickchannel6, JOY_DOWN)) // manual button override
		{
			armMax = 0;
			armMin = 0;
			armCenter = 0;
		}

		if (joystickGetDigital(joystick1, joystickchannel8, JOY_LEFT)) // manual button cancell
		{
			armMax = 0;
			armMin = 0;
			armCenter = 0;
		}

// arm max shortcut button////////////////////////////////////////////////////////////////////////////////////
		if (joystickGetDigital(joystick1, joystickchannel8, JOY_UP)) //channel 8 button up pressed?
		{
			armMax = 1;
			armMin = 0;
			armCenter = 0;
		}

		if (armMax == 1)
		{
			pot = analogRead(8);

			if (pot < GOAL_HEIGHT)
			{
				motorSet(MOTOR_ARM_RIGHT_BOTTOM, -127); // arm up
				motorSet(MOTOR_ARM_RIGHT_TOP, 127);
				motorSet(MOTOR_ARM_LEFT_TOP, -127);
				motorSet(MOTOR_ARM_LEFT_BOTTOM, 127);
			}

			if (pot > GOAL_HEIGHT)
			{
				motorSet(MOTOR_ARM_RIGHT_BOTTOM, -10); // trim
				motorSet(MOTOR_ARM_RIGHT_TOP, 10);
				motorSet(MOTOR_ARM_LEFT_TOP, -10);
				motorSet(MOTOR_ARM_LEFT_BOTTOM, 10);

				armMax = 0; // reset the variable so it jumps out of this if loop
			}
		}

// arm mmin shortcut button//////////////////////////////////////////////////////////////////////////////////////////////
		if (joystickGetDigital(joystick1, joystickchannel8, JOY_DOWN)) //channel 8 button down pressed ?
		{
			armMax = 0;
			armMin = 1;
			armCenter = 0;
		}

		if (armMin == 1)
		{
			pot = analogRead(8);

			if (pot > FLOOR_HEIGHT)
			{
				motorSet(MOTOR_ARM_RIGHT_BOTTOM, 127); // arm down
				motorSet(MOTOR_ARM_RIGHT_TOP, -127);
				motorSet(MOTOR_ARM_LEFT_TOP, 127);
				motorSet(MOTOR_ARM_LEFT_BOTTOM, -127);
			}

			if (pot < FLOOR_HEIGHT)
			{
				motorSet(MOTOR_ARM_RIGHT_BOTTOM, 7); // trim down
				motorSet(MOTOR_ARM_RIGHT_TOP, -7);
				motorSet(MOTOR_ARM_LEFT_TOP, 7);
				motorSet(MOTOR_ARM_LEFT_BOTTOM, -7);
				armMin = 0; // reset the variable so it jumps out of this if loop
			}
		}

// wall height shortcut button//////////////////////////////////////////////////////////////////////////////////////////////
		if (joystickGetDigital(joystick1, joystickchannel8, JOY_RIGHT)) //channel 8 button right pressed ?
		{
			armMax = 0;
			armMin = 0;
			armCenter = 1;
		}

		if (armCenter == 1)
		{
			pot = analogRead(8);

			if (pot < WALL_HEIGHT)
			{
				motorSet(MOTOR_ARM_RIGHT_BOTTOM, -127); // arm up
				motorSet(MOTOR_ARM_RIGHT_TOP, 127);
				motorSet(MOTOR_ARM_LEFT_TOP, -127);
				motorSet(MOTOR_ARM_LEFT_BOTTOM, 127);
			}

			if (pot > WALL_HEIGHT)
			{
				motorSet(MOTOR_ARM_RIGHT_BOTTOM, -10); // trim
				motorSet(MOTOR_ARM_RIGHT_TOP, 10);
				motorSet(MOTOR_ARM_LEFT_TOP, -10);
				motorSet(MOTOR_ARM_LEFT_BOTTOM, 10);
				armCenter = 0; // reset the variable so it jumps out of this if loop
			}
		}

	} // while(true) close bracket

} // operator close bracket

void twoDrivers()
{
	// go to autonomous mode testing
	//if (digitalRead(1) == LOW) // jumper 1 in = autonomous
	//	{
	//		autonomous ();
	//	}

	int trimThreshHold = 15;

	while (true)

	{
		int pot = analogRead(8);
		printf("%d\r\n", pot);

		int channel2;
		int channel3;
		int channel22;
		int mapped2;
		int mapped3;

		// declare joystick inputs/////////////////////////////////////////////////////////////////////////////////
		channel2 = joystickGetAnalog(1, 2); // (joystick 1, channel 2)
		channel3 = joystickGetAnalog(1, 3); // (joystick 1, channel 3)
		channel22 = joystickGetAnalog(2, 2); // (joystick 2, channel 2)

		// cubic drive//////////////////////////////

		if (channel2 >= 0)  // positive values
		{
			mapped2 = (channel2 * channel2) / 127;
		}
		else  // nagative values
		{
			mapped2 = (channel2 * channel2) / -127;
		}

		if (channel3 >= 0)
		{
			mapped3 = (channel3 * channel3) / 127;
		}
		else
		{
			mapped3 = (channel3 * channel3) / -127;
		}

		// drive functions////////////////////////////////////////////////////////////////////////////////////////
		motorSet(MOTOR_DRIVE_RIGHT_BACK, mapped2); // right drive back
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, mapped2); // right drive front
		motorSet(MOTOR_ARM_LEFT_BACK, mapped3); // left drive abck
		motorSet(MOTOR_ARM_LEFT_FRONT, mapped3); // left drive front

		// arm function/////////////////////////////////////////////////////////////////////////////////////////////
		if (dummyTrim == 1)
		{
			motorSet(MOTOR_ARM_RIGHT_BOTTOM, -channel22); // right arm down
			motorSet(MOTOR_ARM_RIGHT_TOP, channel22); // right arm up
			motorSet(MOTOR_ARM_LEFT_TOP, -channel22); // left arm up
		}
		motorSet(MOTOR_ARM_LEFT_BOTTOM, channel22); // left arm down

		// arm trim////////////////////
		if (dummyTrim == 1) //trim!
		{
			if (abs(channel22) < trimThreshHold) // no touch joystick
			{
				if (pot > 1600) // high trim
				{
					motorSet(MOTOR_ARM_RIGHT_TOP, 10);
					motorSet(MOTOR_ARM_LEFT_TOP, -10);
					motorSet(MOTOR_ARM_RIGHT_BOTTOM, -10);
					motorSet(MOTOR_ARM_LEFT_BOTTOM, 10);
				}

				else if (pot < 300) //  trim down when arm is low
				{
					motorSet(MOTOR_ARM_RIGHT_TOP, -7);
					motorSet(MOTOR_ARM_LEFT_TOP, 7);
					motorSet(MOTOR_ARM_RIGHT_BOTTOM, 7);
					motorSet(MOTOR_ARM_LEFT_BOTTOM, -7);
				}

				else //trim normal
				{
					motorSet(MOTOR_ARM_RIGHT_TOP, 7);
					motorSet(MOTOR_ARM_LEFT_TOP, -7);
					motorSet(MOTOR_ARM_RIGHT_BOTTOM, -7);
					motorSet(MOTOR_ARM_LEFT_BOTTOM, 7);
				}

			}
		} // dummytrim bracket

		if (abs(channel22) < trimThreshHold) // no touch joystick button height shortcuts
		{

			// arm max shortcut button////////////////////////////////////////////////////////////////////////////////////
			if (joystickGetDigital(joystick2, joystickchannel8, JOY_UP)) //channel 8 button up pressed?
			{
				dummyTrim = 0;
				armMax = 1;
				armMin = 0;
				armCenter = 0;
			}

			if (armMax == 1)
			{
				pot = analogRead(8);

				if (pot < GOAL_HEIGHT)
				{
					motorSet(MOTOR_ARM_RIGHT_BOTTOM, -127); // arm up
					motorSet(MOTOR_ARM_RIGHT_TOP, 127);
					motorSet(MOTOR_ARM_LEFT_TOP, -127);
					motorSet(MOTOR_ARM_LEFT_BOTTOM, 127);
				}

				if (pot > GOAL_HEIGHT)
				{
					motorSet(MOTOR_ARM_RIGHT_BOTTOM, -10); // trim
					motorSet(MOTOR_ARM_RIGHT_TOP, 10);
					motorSet(MOTOR_ARM_LEFT_TOP, -10);
					motorSet(MOTOR_ARM_LEFT_BOTTOM, 10);

					armMax = 0; // reset the variable so it jumps out of this if loop
					armMin = 0;
					armCenter = 0;

					dummyTrim = 1;
				}
				else // if you touch joysticks, then cancell everything

				{
					dummyTrim = 1;
					armMax = 0;
					armMin = 0;
					armCenter = 0;

				}
			}

			// arm mmin shortcut button//////////////////////////////////////////////////////////////////////////////////////////////
			if (joystickGetDigital(joystick2, joystickchannel8, JOY_DOWN)) //channel 8 button down pressed ?
			{
				dummyTrim = 0;
				armMax = 0;
				armMin = 1;
				armCenter = 0;
			}

			if (armMin == 1)
			{
				pot = analogRead(8);

				if (pot > FLOOR_HEIGHT)
				{
					motorSet(MOTOR_ARM_RIGHT_BOTTOM, 127); // arm down
					motorSet(MOTOR_ARM_RIGHT_TOP, -127);
					motorSet(MOTOR_ARM_LEFT_TOP, 127);
					motorSet(MOTOR_ARM_LEFT_BOTTOM, -127);
				}

				if (pot < FLOOR_HEIGHT)
				{
					motorSet(MOTOR_ARM_RIGHT_BOTTOM, 7); // trim down
					motorSet(MOTOR_ARM_RIGHT_TOP, -7);
					motorSet(MOTOR_ARM_LEFT_TOP, 7);
					motorSet(MOTOR_ARM_LEFT_BOTTOM, -7);

					armMin = 0; // reset the variable so it jumps out of this if loop
					armMax = 0;
					armCenter = 0;

					dummyTrim = 1;
				}
				else // if you touch joysticks, then cancell everything

				{
					dummyTrim = 1;
					armMax = 0;
					armMin = 0;
					armCenter = 0;

				}
			}

			// wall height shortcut button//////////////////////////////////////////////////////////////////////////////////////////////
			if (joystickGetDigital(joystick2, joystickchannel8, JOY_RIGHT)) //channel 8 button right pressed ?
			{
				dummyTrim = 0;
				armMax = 0;
				armMin = 0;
				armCenter = 1;
			}

			if (armCenter == 1)
			{
				pot = analogRead(8);

				if (pot < WALL_HEIGHT)
				{
					motorSet(MOTOR_ARM_RIGHT_BOTTOM, -127); // arm up
					motorSet(MOTOR_ARM_RIGHT_TOP, 127);
					motorSet(MOTOR_ARM_LEFT_TOP, -127);
					motorSet(MOTOR_ARM_LEFT_BOTTOM, 127);
				}

				if (pot > WALL_HEIGHT)
				{
					motorSet(MOTOR_ARM_RIGHT_BOTTOM, -10); // trim
					motorSet(MOTOR_ARM_RIGHT_TOP, 10);
					motorSet(MOTOR_ARM_LEFT_TOP, -10);
					motorSet(MOTOR_ARM_LEFT_BOTTOM, 10);
					armCenter = 0; // reset the variable so it jumps out of this if loop
					dummyTrim = 1;
				}
			}

			else // if you touch joysticks, then cancell everything

			{
				dummyTrim = 1;
				armMax = 0;
				armMin = 0;
				armCenter = 0;

			}

		}

		// intake functions/////////////////////////////////////////////////////////////////////////////////////
		if (joystickGetDigital(joystick2, joystickchannel6, JOY_UP)) //intake
		{
			motorSet(MOTOR_INTAKE_RIGHT, 127); // arm right
			motorSet(MOTOR_INTAKE_LEFT, -127); // arm left
		}

		else if (joystickGetDigital(joystick2, joystickchannel5, JOY_UP)) // outtake
		{
			motorSet(MOTOR_INTAKE_RIGHT, -127); // arm right
			motorSet(MOTOR_INTAKE_LEFT, 127); // arm left
		}
		else
		{
			motorStop(MOTOR_INTAKE_RIGHT); // arm right
			motorStop(MOTOR_INTAKE_LEFT); // arm left
		}

/////////////TOP OF CUBIC///////////////////////////////////////

	} //while(true) of twoDrivers

} // end of twoDrivers

// cubic drive///////////////////////////////////////////////////////////////////////////////////////////////

void cubicDrive()
{

	int channel2;
	int channel3;
	int mapped2;
	int mapped3;

	while (1 == 1)
	{
		int pot = analogRead(8);
		printf("%d\r\n", pot);

		// declare joystick inputs/////////////////////////////////////////////////////////////////////////////////
		channel2 = joystickGetAnalog(1, 2); // (joystick 1, channel 2)
		channel3 = joystickGetAnalog(1, 3); // (joystick 1, channel 3)

		if (channel2 >= 0)  // positive values
		{
			mapped2 = (channel2 * channel2) / 127;
		}
		else  // nagative values
		{
			mapped2 = (channel2 * channel2) / -127;
		}

		if (channel3 >= 0)
		{
			mapped3 = (channel3 * channel3) / 127;
		}
		else
		{
			mapped3 = (channel3 * channel3) / -127;
		}

		// drive functions////////////////////////////////////////////////////////////////////////////////////////
		motorSet(MOTOR_DRIVE_RIGHT_BACK, mapped2); // right drive back
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, mapped2); // right drive front
		motorSet(MOTOR_ARM_LEFT_BACK, mapped3); // left drive abck
		motorSet(MOTOR_ARM_LEFT_FRONT, mapped3); // left drive front

		// arm function/////////////////////////////////////////////////////////////////////////////////////////////
		if (joystickGetDigital(joystick1, joystickchannel6, JOY_UP)) // arm up
		{
			motorSet(MOTOR_ARM_RIGHT_TOP, 127); // arm right up
			motorSet(MOTOR_ARM_LEFT_TOP, -127); // arm left
			motorSet(MOTOR_ARM_RIGHT_BOTTOM, -127); // arm down up
			motorSet(MOTOR_ARM_LEFT_BOTTOM, 127); // arm left down
		}

		else if (joystickGetDigital(joystick1, joystickchannel6, JOY_DOWN)) // arm down
		{
			motorSet(MOTOR_ARM_RIGHT_TOP, -127); // arm right up
			motorSet(MOTOR_ARM_LEFT_TOP, 127); // arm left up
			motorSet(MOTOR_ARM_RIGHT_BOTTOM, 127); // arm right down
			motorSet(MOTOR_ARM_LEFT_BOTTOM, -127); // arm left down
		}
		else // trim arm up
		{
			if (pot > 1600) // high trim
			{
				motorSet(MOTOR_ARM_RIGHT_TOP, 10);
				motorSet(MOTOR_ARM_LEFT_TOP, -10);
				motorSet(MOTOR_ARM_RIGHT_BOTTOM, -10);
				motorSet(MOTOR_ARM_LEFT_BOTTOM, 10);
			}

			else if (pot < 300) //  trim down when arm is low
			{
				motorSet(MOTOR_ARM_RIGHT_TOP, -7);
				motorSet(MOTOR_ARM_LEFT_TOP, 7);
				motorSet(MOTOR_ARM_RIGHT_BOTTOM, 7);
				motorSet(MOTOR_ARM_LEFT_BOTTOM, -7);
			}

			else //trim normal
			{
				motorSet(MOTOR_ARM_RIGHT_TOP, 7);
				motorSet(MOTOR_ARM_LEFT_TOP, -7);
				motorSet(MOTOR_ARM_RIGHT_BOTTOM, -7);
				motorSet(MOTOR_ARM_LEFT_BOTTOM, 7);
			}

		}

		// intake functions/////////////////////////////////////////////////////////////////////////////////////
		if (joystickGetDigital(joystick1, joystickchannel5, JOY_UP)) //intake
		{
			motorSet(MOTOR_INTAKE_RIGHT, 127); // arm right
			motorSet(MOTOR_INTAKE_LEFT, -127); // arm left
		}

		else if (joystickGetDigital(joystick1, joystickchannel5, JOY_DOWN)) // outtake
		{
			motorSet(MOTOR_INTAKE_RIGHT, -127); // arm right
			motorSet(MOTOR_INTAKE_LEFT, 127); // arm left
		}
		else
		{
			motorStop(MOTOR_INTAKE_RIGHT); // arm right
			motorStop(MOTOR_INTAKE_LEFT); // arm left
		}

		// shortcut manual overrides and cancel ////////////////////////////////////////////////////////////////////////
		if (joystickGetDigital(joystick1, joystickchannel6, JOY_UP)) // manual button override
		{
			armMax = 0;
			armMin = 0;
			armCenter = 0;
		}

		if (joystickGetDigital(joystick1, joystickchannel6, JOY_DOWN)) // manual button override
		{
			armMax = 0;
			armMin = 0;
			armCenter = 0;
		}

		if (joystickGetDigital(joystick1, joystickchannel8, JOY_LEFT)) // manual button cancell
		{
			armMax = 0;
			armMin = 0;
			armCenter = 0;
		}

		// arm max shortcut button////////////////////////////////////////////////////////////////////////////////////
		if (joystickGetDigital(joystick1, joystickchannel8, JOY_UP)) //channel 8 button up pressed?
		{
			armMax = 1;
			armMin = 0;
			armCenter = 0;
		}

		if (armMax == 1)
		{
			pot = analogRead(8);

			if (pot < GOAL_HEIGHT)
			{
				motorSet(MOTOR_ARM_RIGHT_BOTTOM, -127); // arm up
				motorSet(MOTOR_ARM_RIGHT_TOP, 127);
				motorSet(MOTOR_ARM_LEFT_TOP, -127);
				motorSet(MOTOR_ARM_LEFT_BOTTOM, 127);
			}

			if (pot > GOAL_HEIGHT)
			{
				motorSet(MOTOR_ARM_RIGHT_BOTTOM, -10); // trim
				motorSet(MOTOR_ARM_RIGHT_TOP, 10);
				motorSet(MOTOR_ARM_LEFT_TOP, -10);
				motorSet(MOTOR_ARM_LEFT_BOTTOM, 10);

				armMax = 0; // reset the variable so it jumps out of this if loop
			}
		}

		// arm mmin shortcut button//////////////////////////////////////////////////////////////////////////////////////////////
		if (joystickGetDigital(joystick1, joystickchannel8, JOY_DOWN)) //channel 8 button down pressed ?
		{
			armMax = 0;
			armMin = 1;
			armCenter = 0;
		}

		if (armMin == 1)
		{
			pot = analogRead(8);

			if (pot > FLOOR_HEIGHT)
			{
				motorSet(MOTOR_ARM_RIGHT_BOTTOM, 127); // arm down
				motorSet(MOTOR_ARM_RIGHT_TOP, -127);
				motorSet(MOTOR_ARM_LEFT_TOP, 127);
				motorSet(MOTOR_ARM_LEFT_BOTTOM, -127);
			}

			if (pot < FLOOR_HEIGHT)
			{
				motorSet(MOTOR_ARM_RIGHT_BOTTOM, 7); // trim down
				motorSet(MOTOR_ARM_RIGHT_TOP, -7);
				motorSet(MOTOR_ARM_LEFT_TOP, 7);
				motorSet(MOTOR_ARM_LEFT_BOTTOM, -7);
				armMin = 0; // reset the variable so it jumps out of this if loop
			}
		}

		// wall height shortcut button//////////////////////////////////////////////////////////////////////////////////////////////
		if (joystickGetDigital(joystick1, joystickchannel8, JOY_RIGHT)) //channel 8 button right pressed ?
		{
			armMax = 0;
			armMin = 0;
			armCenter = 1;
		}

		if (armCenter == 1)
		{
			pot = analogRead(8);

			if (pot < WALL_HEIGHT)
			{
				motorSet(MOTOR_ARM_RIGHT_BOTTOM, -127); // arm up
				motorSet(MOTOR_ARM_RIGHT_TOP, 127);
				motorSet(MOTOR_ARM_LEFT_TOP, -127);
				motorSet(MOTOR_ARM_LEFT_BOTTOM, 127);
			}

			if (pot > WALL_HEIGHT)
			{
				motorSet(MOTOR_ARM_RIGHT_BOTTOM, -10); // trim
				motorSet(MOTOR_ARM_RIGHT_TOP, 10);
				motorSet(MOTOR_ARM_LEFT_TOP, -10);
				motorSet(MOTOR_ARM_LEFT_BOTTOM, 10);
				armCenter = 0; // reset the variable so it jumps out of this if loop
			}
		}

	} // while(true) close bracket

} //cubic drive close

