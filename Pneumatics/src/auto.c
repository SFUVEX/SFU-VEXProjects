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

void autonomous()
{
	int MAX_HEIGHT = 1111;
	int stack1 = 500;
	int stack2 = 0;
	int stack3 = 0;
	int stack4 = 0;
	int stack5 = 0;
	int stack6 = 0;
	int stack7 = 0;
	int vexIntakeHeight = 250;
	int vexSectionBuffer = 100;



	int counts = encoderGet(encoder2);
	encoderReset(encoder2); //Digital 3, 4
	/*while(true)
	{
		counts = encoderGet(encoder2);
		printf("enc = %d\r\n", counts);
	}*/

	armUp(vexIntakeHeight);
	armOpen();
	armSwingRight();
	delay(1000);
	armDown(vexIntakeHeight - vexSectionBuffer);
	delay(1000);
	armClose();
	armUp(vexSectionBuffer);
	armSwingRight();
	armDown(stack1 + vexSectionBuffer);
	armOpen();

	/*
	for(int i = 0; i < 7; i++)
	{
		if(counts < stack1)
		{
			//digitalWrite(11, HIGH); // Arm Right

			armUp(vexIntakeHeight);//Arm up to the next VEX Piece
			armSwingRight(); // arm right to spike
			delay(500);
			armDown(vexSectionBuffer);
			armClose();	//Intake close
			delay (500);
//////Begin gordon code
			//intake up buffer
			armUp(vexIntakeHeight + vexSectionBuffer);
			//arm left to stack
			armSwingLeft();

			//arm down to stack1 height
			armDown(stack1);
			//dealy 500
			delay(500);
			//outtake
			armOpen();

			//arm up to intake height again
			armDown(vexIntakeHeight);
			//arm left to the new spike
			armSwingLeft();
/////</gordon>


			armSwingLeft();	//Arm left
			armOpen();	//Intake open
			delay(1000);				//Wait for arm to reach desired height
			armClose();	//Intake closed
			armUp(stack1);			//Arm up to stack height
			delay(2000);
			armSwingRight();	//Arm right
			delay(2000);
			armDown(vexSectionBuffer);
			armOpen();	//Intake open

			counts = encoderGet(encoder2);
			//printf("enc = %d\r\n", counts);
		}

		else if(counts < stack2 && counts > stack1)
		{
			armUp(vexSectionBuffer);
			digitalWrite(11, HIGH);	//Arm left
			delay(5);
			armDown(vexIntakeHeight);//Arm down to the next VEX Piece
			digitalWrite(12, HIGH);	//Intake open
			delay(30);				//Wait for arm to reach desired height
			digitalWrite(12, LOW);	//Intake closed
			armUp(stack2);			//Arm up to stack height
			delay(30);
			digitalWrite(11, LOW);	//Arm right
			delay(30);
			armDown(vexSectionBuffer);
			digitalWrite(12, HIGH);	//Intake open

			counts = encoderGet(encoder2);
		}

		else if(counts < stack3 && counts > stack2)
		{
			armUp(vexSectionBuffer);
			digitalWrite(11, HIGH);	//Arm left
			delay(5);
			armDown(vexIntakeHeight);//Arm down to the next VEX Piece
			digitalWrite(12, HIGH);	//Intake open
			delay(30);				//Wait for arm to reach desired height
			digitalWrite(12, LOW);	//Intake closed
			armUp(stack3);			//Arm up to stack height
			delay(30);
			digitalWrite(11, LOW);	//Arm right
			delay(30);
			armDown(vexSectionBuffer);
			digitalWrite(12, HIGH);	//Intake open

			counts = encoderGet(encoder2);
		}

		else if(counts < stack4 && counts > stack3)
		{
			armUp(vexSectionBuffer);
			digitalWrite(11, HIGH);	//Arm left
			delay(5);
			armDown(vexIntakeHeight);//Arm down to the next VEX Piece
			digitalWrite(12, HIGH);	//Intake open
			delay(30);				//Wait for arm to reach desired height
			digitalWrite(12, LOW);	//Intake closed
			armUp(stack4);			//Arm up to stack height
			delay(30);
			digitalWrite(11, LOW);	//Arm right
			delay(30);
			armDown(vexSectionBuffer);
			digitalWrite(12, HIGH);	//Intake open

			counts = encoderGet(encoder2);
		}

		else if(counts < stack5 && counts > stack4)
		{
			armUp(vexSectionBuffer);
			digitalWrite(11, HIGH);	//Arm left
			delay(5);
			armDown(vexIntakeHeight);//Arm down to the next VEX Piece
			digitalWrite(12, HIGH);	//Intake open
			delay(30);				//Wait for arm to reach desired height
			digitalWrite(12, LOW);	//Intake closed
			armUp(stack5);			//Arm up to stack height
			delay(30);
			digitalWrite(11, LOW);	//Arm right
			delay(30);
			armDown(vexSectionBuffer);
			digitalWrite(12, HIGH);	//Intake open

			counts = encoderGet(encoder2);
		}

		else if(counts < stack6 && counts > stack5)
		{
			armUp(vexSectionBuffer);
			digitalWrite(11, HIGH);	//Arm left
			delay(5);
			armDown(vexIntakeHeight);//Arm down to the next VEX Piece
			digitalWrite(12, HIGH);	//Intake open
			delay(30);				//Wait for arm to reach desired height
			digitalWrite(12, LOW);	//Intake closed
			armUp(stack6);			//Arm up to stack height
			delay(30);
			digitalWrite(11, LOW);	//Arm right
			delay(30);
			armDown(vexSectionBuffer);
			digitalWrite(12, HIGH);	//Intake open

			counts = encoderGet(encoder2);
		}

		else if(counts < stack7 && counts > stack6)
		{
			armUp(vexSectionBuffer);
			digitalWrite(11, HIGH);	//Arm left
			delay(5);
			armDown(vexIntakeHeight);//Arm down to the next VEX Piece
			digitalWrite(12, HIGH);	//Intake open
			delay(30);				//Wait for arm to reach desired height
			digitalWrite(12, LOW);	//Intake closed
			armUp(stack3);			//Arm up to stack height
			delay(30);
			digitalWrite(11, LOW);	//Arm right
			delay(30);
			armDown(vexSectionBuffer);
			digitalWrite(12, HIGH);	//Intake open

			counts = encoderGet(encoder2);
		}

		else
		{
			digitalWrite(11, HIGH);
			armDown(vexIntakeHeight);
		}*/
}


void armSwingRight()
{
	digitalWrite(11, LOW);
}
void armSwingLeft()
{
	digitalWrite(11, HIGH);
}
void armOpen()
{
	digitalWrite(12, HIGH);
}
void armClose()
{
	digitalWrite(12, LOW);
}
