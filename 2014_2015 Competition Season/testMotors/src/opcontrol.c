/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS.
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
#include "motorsubroutines.h"
//#include <stdbool.h>

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
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */

void doButtonsP1();
void doJoysticksP1();

typedef enum InputChannels
{
	INPUT_RIGHT_X=1,
	INPUT_RIGHT_Y=2,
	INPUT_LEFT_Y=3,
	INPUT_LEFT_X=4,
	INPUT_RIGHT_TRIGGER=5,
	INPUT_LEFT_TRIGGER=6,
	INPUT_LEFT_BUTTONS=7,
	INPUT_RIGHT_BUTTONS = 8

}InputChannels;

typedef struct Vector2
{
	float x;
	float y;
} Vector2;

int controller1 =1;
void operatorControl() {
QuadDrive q;
	while(1)
		{
		//delay(200);
		//motorSet(2, 64);
		//delay(20);

		/*
		zigZagHolo(& q, 127, 64,
				30, true );
		motorSet(2, q.topRight);
		motorSet(9, q.topLeft);
		motorSet(10, q.bottomLeft);
		motorSet(1, q.bottomRight);
		*/
		//doJoysticksP1();
		int pwr = joystickGetAnalog(controller1, INPUT_LEFT_Y);
		int armpwr = joystickGetAnalog(controller1, INPUT_RIGHT_Y);//
		//int pwr = 50;

		motorSet(3,armpwr);
		motorSet(7,armpwr);
		motorSet(4,armpwr);

		//clawbot test
		/*
		motorSet(3,armpwr);
		motorSet(7,-armpwr);
		*/
		
				motorSet(9, -pwr/2);  //TL
				//delay(2000);
				//motorSet(9, 0);
				motorSet(10, pwr/2);  //BL
				//delay(2000);
				//motorSet(10, 0);
				motorSet(1, pwr);  //BR
				//delay(2000);
				//motorSet(1, 0);
                motorSet(2,-pwr ); // TR
                //delay(2000);
                //motorSet(2, 0);
		}
	while (1) {
		delay(20);
	}
}

void doButtonsP1()
{
	char lu = joystickGetDigital(controller1, INPUT_LEFT_BUTTONS, JOY_UP);
	char lr = joystickGetDigital(controller1, INPUT_LEFT_BUTTONS, JOY_RIGHT);
	char ll = joystickGetDigital(controller1, INPUT_LEFT_BUTTONS, JOY_LEFT);
	char ld = joystickGetDigital(controller1, INPUT_LEFT_BUTTONS, JOY_DOWN);

	char ru = joystickGetDigital(controller1, INPUT_RIGHT_BUTTONS, JOY_UP);
	char rr = joystickGetDigital(controller1, INPUT_RIGHT_BUTTONS, JOY_RIGHT);
	char rl = joystickGetDigital(controller1, INPUT_RIGHT_BUTTONS, JOY_LEFT);
	char rd = joystickGetDigital(controller1, INPUT_RIGHT_BUTTONS, JOY_DOWN);

	int lt = joystickGetDigital(controller1, INPUT_LEFT_TRIGGER, JOY_DOWN);
	int rt = joystickGetDigital(controller1, INPUT_RIGHT_TRIGGER, JOY_DOWN);

	//leftButtonsP1(lu,ld,ll,lr);
	//rightButtonsP1(ru,rd,rl,rr);

	//if(lt)
	//leftTriggerP1();

	//if(rt)
	//rightTriggerP1();
}



void doJoysticksP1()
{
	printf("joy1\r\n");
	Vector2 l,r;
	l.x= joystickGetAnalog(3, INPUT_LEFT_X);
	l.y = joystickGetAnalog(1, INPUT_LEFT_Y);
	r.x = joystickGetAnalog(1, INPUT_RIGHT_X);
	r.y = joystickGetAnalog(1, INPUT_RIGHT_Y);


	QuadDrive q;
	zigZagHolo(&q, r.x, r.y,
			l.y, 1 );
	motorSet(2, q.topRight);
	motorSet(9, q.topLeft);
	motorSet(10, q.bottomLeft);
	motorSet(1, q.bottomRight);
		printf("NW=%d SW=%d NE=%d SE=%d\n\r",q.topLeft,q.bottomLeft,q.topLeft,q.topRight);
			int lt = joystickGetDigital(controller1, INPUT_LEFT_TRIGGER, JOY_DOWN);
			if(lt)
			{

			}
	//controlScheme
}
