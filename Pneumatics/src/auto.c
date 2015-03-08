// test gladstone

/** @file auto.c
 * @brief File for autonomous code
 *
 * This file should contain the user autonomous() function and any functions related to it.
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

#include "auto.h"


void armSwingRight();
void armSwingLeft();
void armOpen();
void armClose();

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
#define NStack 7
void autonomous()
{
	//int MAX_HEIGHT = 2111;
	const int stack[NStack]={
			325,1650,2600,3900,5200,6800,2050
	};
//	int stack1 = 500;
//	int stack2 = 0;
//	int stack3 = 0;
//	int stack4 = 0;
//	int stack5 = 0;
//	int stack6 = 0;
//	int stack7 = 0;
	int vexIntakeHeight = 1500;
	int vexSectionBuffer = 75;



	encoderReset(encoder2); //Digital 3, 4

	int i;
	for(i=0;i<NStack;i++)
	{
		armUp(vexIntakeHeight);
		armSwingLeft();
		//delay(3600000); //uncomment when aligning.
		delay(100);
		//counts = encoderGet(encoder2);
		//printf("enc = %d\r\n", counts);
		stopArm();

		armOpen();
		delay(2000);
		armDown(vexIntakeHeight-vexSectionBuffer); // into the hole
		delay(700);
		stopArm();
		delay(100);
		armClose();
		armUp(vexIntakeHeight);
		////////////////////////unload
		if(stack[i] < vexIntakeHeight)
		{
			//destination below load height
			armSwingRight();
			armDown(stack[i]);
		}else
		{
			//destination aboe load height.
			armUp(stack[i]);
			delay(i*1000);
			armSwingRight();
		}


		delay(1000);
		armOpen();
		delay(4000);
		armDown(vexIntakeHeight);
	}
	printf("END PROG\r\n");
	delay(20);
}


void armSwingRight()
{
	digitalWrite(11, HIGH);

}
void armSwingLeft()
{
	digitalWrite(11, LOW);
}
void armOpen()
{
	digitalWrite(12, HIGH);
}
void armClose()
{
	digitalWrite(12, LOW);
}
