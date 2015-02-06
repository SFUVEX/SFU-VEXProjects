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
void turnLeftArc(int x); // x = encoder
void turnRightArc(int x);
void driveForwardDead ();
void driveBackDead ();
void driveForwardSlow (int x);
void driveBackSlow (int x) ;
void driveForwardSlowDead ();
void driveBackSlowDead ();

void scrapeRightBack (int x); // x = timer
void scrapeLeftBack (int x); // x = encoder
void forwardDetect ();
void backDetect ();
void stopAll();
void stopDrive();

void stopIntake();
void armUp (int x); // x = pot value
void armDown(int x); // x = pot value
void armUpDead();
void armDownDead ();
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
void rushRed ();
void rushBlue();
void classic15Red();
void classic15Blue();
void rejectionRed();
void rejectionBlue();
void rejectionBlueSkills ();
void kakitRed ();
//void kakitBlue ();
void ram ();

//motors
#define motor1 1 // = rightLine back
#define motor2 2 // = rightLine front
#define motor3 3 // = rightLine arm down
#define motor4 4 // = rightLine arm up
#define motor5 5 // = rightLine intake
#define motor6 6 // = leftLine intake
#define motor7 7 // = leftLine arm up
#define motor8 8 // = leftLine arm down
#define motor9 9 // = leftLine front
#define motor10 10 // = leftLine back



void autonomous()
{

int jumper1 = digitalRead (1);
int jumper2 = digitalRead (2);
int jumper3 = digitalRead (3);


//1 = out
// 0 = in
if ((jumper1 == 0) && (jumper2 == 0))
{
	rushBlue();
}

if ((jumper1 == 0) && (jumper3 == 0))
{
	classic15Blue();
}

if ((jumper1 == 1) && (jumper2 == 0))
{
	rushRed();
}

if ((jumper1 == 1) && (jumper3 == 0))
{
	classic15Red();
}

if (jumper1 == 0)
{
	rejectionBlue();
}

if (jumper1 == 1)
{
	rejectionRed();
}

//forwardDetect (1000);

//armUpTrim();
//findLineRight();
//followLine(1200);

//rejectionRed();
rejectionBlue();

//classic15Red();
//classic15Blue();
//rushRed();
//rushBlue();
//kakitRed ();

// all jumper comands here:





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



void turnLeftArc(int x)
{
	int counts = 0;
	imeReset(0); // rest rightLine ime
	imeGet(0, &counts);

	while (abs(counts) < x)
	 {
		motorSet (motor1, 127) ;
		motorSet (motor2, 127) ;
		motorSet (motor10, 0) ;
		motorSet (motor9, 0) ;

		imeGet(0, &counts); // keep getting the value
	 }
	motorStop (motor1);
	motorStop (motor2);
	motorStop (motor10);
	motorStop (motor9);
	delay (200);
}

void turnRightArc(int x)
{
	int counts = 1;
	imeReset(1); // rest rightLine ime
	imeGet(1, &counts);

	while (abs(counts) < x)
	 {
		motorSet (motor1, 0) ;
		motorSet (motor2, 0) ;
		motorSet (motor10, 127) ;
		motorSet (motor9, 127) ;

		imeGet(0, &counts); // keep getting the value
	 }
	motorStop (motor1);
	motorStop (motor2);
	motorStop (motor10);
	motorStop (motor9);

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
	motorStop (motor3);
	motorStop (motor4);
	motorStop (motor5);
	motorStop (motor6);
	motorStop (motor7);
	motorStop (motor8);
	motorStop (motor9);
	motorStop (motor10);
}

void stopIntake()
{
	motorStop (motor5);
	motorStop (motor6);
}

void driveForwardDead ()
{
	motorSet (motor1, 127)	;
	motorSet (motor2, 127)	;
	motorSet (motor10, 127) ;
	motorSet (motor9, 127)	;
}

void driveBackDead ()
{
	motorSet (motor1, -127)	;
	motorSet (motor2, -127)	;
	motorSet (motor10, -127) ;
	motorSet (motor9, -127)	;
}

void driveForwardSlow(int x)
{
	int counts = 0;
	imeReset(0); // rest rightLine ime
	imeGet(0, &counts);

	while (abs(counts) < x)
	 {
		motorSet (motor1, 40)	;
		motorSet (motor2, 40)	;
		motorSet (motor10, 40);
		motorSet (motor9, 40)	;

		imeGet(0, &counts); // keep getting the value
	  }

	motorSet (motor1, -10)	; // no inertia
	motorSet (motor2, -10)	;
	motorSet (motor10, -10)	;
	motorSet (motor9, -10)	;
	delay (45);

	motorSet (motor1, 0)	;
	motorSet (motor2, 0)	;
	motorSet (motor10, 0)	;
	motorSet (motor9, 0)	;
	delay (200);
}

void driveBackSlow(int x)
{
	int counts = 0;
	imeReset(0); // rest rightLine ime
	imeGet(0, &counts);

	while (abs(counts) < x)
	 {
		  motorSet (motor1, -40)	;
		  motorSet (motor2, -40)	;
		  motorSet (motor10, -40);
		  motorSet (motor9, -40)	;

		  imeGet(0, &counts); // keep getting the value
	 }

	motorSet (motor1, 10)	; // no inertia
	motorSet (motor2, 10)	;
	motorSet (motor10, 10)	;
	motorSet (motor9, 10)	;
	delay (45);

	motorSet (motor1, 0)	;
	motorSet (motor2, 0)	;
	motorSet (motor10, 0)	;
	motorSet (motor9, 0)	;

	delay (200);
}

void driveForwardSlowDead()
{


		  motorSet (motor1, 50)	;
		  motorSet (motor2, 50)	;
		  motorSet (motor10, 50);
		  motorSet (motor9, 50)	;


}

void driveBackSlowDead()
{


		  motorSet (motor1, -40)	;
		  motorSet (motor2, -40)	;
		  motorSet (motor10, -40);
		  motorSet (motor9, -40)	;

}




void scrapeRight(int x)
{
	int counts = 0;
		imeReset(1); // rest left ime
		imeGet(1, &counts);

		while (abs(counts) < x)
		    {
		      motorSet (motor1, 0)	;
		      motorSet (motor2, 0)	;
		      motorSet (motor10, 90);
		      motorSet (motor9, 90)	;

		      imeGet(1, &counts); // keep getting the value
		    }

		motorSet (motor1, 0)	;
		motorSet (motor2, 0)	;
		motorSet (motor10, -10);
		motorSet (motor9, -10)	;
	    delay (55);

	    motorSet (motor1, 0)	;
		motorSet (motor2, 0)	;
		motorSet (motor10, 0);
		motorSet (motor9, 0)	;
		delay (200);
}

void scrapeLeft(int x)
{
	int counts = 0;
	imeReset(0); // rest rightLine ime
	imeGet(0, &counts);

		while (abs(counts) < x)
		    {
		      motorSet (motor1, 90)	;
		      motorSet (motor2,90)	;
		      motorSet (motor10, 0);
		      motorSet (motor9, 0)	;

		      imeGet(0, &counts); // keep getting the value
		    }

		motorSet (motor1, -10)	; // no intertia
		motorSet (motor2, -10)	;
		motorSet (motor10, 0);
		motorSet (motor9, 0)	;
		delay (55);


		motorSet (motor1, 0)	;
		motorSet (motor2, 0)	;
		motorSet (motor10, 0);
		motorSet (motor9, 0)	;
		delay (200);
}

void scrapeLeftBack (int x)
{
	int counts = 0;
			imeReset(0); // rest left ime
			imeGet(0, &counts);

				while (abs(counts) < x)
				    {
				      motorSet (motor1, -90)	;
				      motorSet (motor2,-90)	;
				      motorSet (motor10, 0);
				      motorSet (motor9, 0)	;

				      imeGet(0, &counts); // keep getting the value
				    }

				motorSet (motor1, 10)	; // no intertia
				motorSet (motor2, 10)	;
				motorSet (motor10, 0);
				motorSet (motor9, 0)	;
				delay (55);


				motorSet (motor1, 0)	;
				motorSet (motor2, 0)	;
				motorSet (motor10, 0);
				motorSet (motor9, 0)	;
				delay (200);



	/*motorSet (motor1, 90)	;
	motorSet (motor2, 90)	;
	motorSet (motor10, 0);
	motorSet (motor9, 0)	;
	delay(x);

	motorSet (motor1, 0)	;
	motorSet (motor2, 0)	;
	motorSet (motor10, 0);
	motorSet (motor9, 0)	;
*/
}

void scrapeRightBack (int x)
{
	int counts = 0;
		imeReset(1); // rest rightLine ime
		imeGet(1, &counts);

			while (abs(counts) < x)
			    {
			      motorSet (motor1, 0)	;
			      motorSet (motor2,0)	;
			      motorSet (motor10, -90);
			      motorSet (motor9, -90)	;

			      imeGet(1, &counts); // keep getting the value
			    }

			motorSet (motor1, 0)	; // no intertia
			motorSet (motor2, 0)	;
			motorSet (motor10, 10);
			motorSet (motor9, 10)	;
			delay (55);


			motorSet (motor1, 0)	;
			motorSet (motor2, 0)	;
			motorSet (motor10, 0);
			motorSet (motor9, 0)	;
			delay (200);

}

void forwardDetect()
{
	int white = 1300;
	int leftLine = analogRead(1);
	int midLine = analogRead(2);
	int rightLine = analogRead(3);


		while (midLine > white) // drive till hit white line
		 {
			motorSet (motor1, 60)	;
			motorSet (motor2, 60)	;
			motorSet (motor10, 60);
			motorSet (motor9, 60)	;

			midLine = analogRead(2);
		  }


		motorSet (motor1, -10)	; // no intertia
		motorSet (motor2, -10)	;
		motorSet (motor10, -10);
		motorSet (motor9, -10)	;
		delay (55);


		motorSet (motor1, 0)	;
		motorSet (motor2, 0)	;
		motorSet (motor10, 0);
		motorSet (motor9, 0)	;
		delay (200);
}

void backDetect()
{
	int white = 2000;
	int leftLine = analogRead(1);
	int midLine = analogRead(2);
	int rightLine = analogRead(3);


		while (midLine > white) // drive till hit white line
		 {
			motorSet (motor1, -60)	;
			motorSet (motor2, -60)	;
			motorSet (motor10, -60);
			motorSet (motor9, -60)	;

			midLine = analogRead(2);
		  }


		motorSet (motor1, 10)	; // no intertia
		motorSet (motor2, 10)	;
		motorSet (motor10, 10);
		motorSet (motor9, 10)	;
		delay (55);


		motorSet (motor1, 0)	;
		motorSet (motor2, 0)	;
		motorSet (motor10, 0);
		motorSet (motor9, 0)	;
		delay (200);

}





void armUp(int x)
{
	int pot = analogRead (8);

	while (pot < x)
	{
		motorSet (motor3, -127) ; // arm up
		motorSet (motor4, 127) ;
		motorSet (motor7, -127) ;
		motorSet (motor8, 127) ;
		pot = analogRead (8);
	}

	armUpTrim();
	delay (300);
}


void armDown(int x)
{
	int pot = analogRead (8);

		while (pot > x)
		{
			motorSet (motor3, 127) ; // arm down
			motorSet (motor4, -127) ;
			motorSet (motor7, 127) ;
			motorSet (motor8, -127) ;
			pot = analogRead (8);
		}

		armDownTrim();
}

void armUpDead()
{

		motorSet (motor3, -127) ; // arm up
		motorSet (motor4, 127) ;
		motorSet (motor7, -127) ;
		motorSet (motor8, 127) ;
}

void armDownDead()
{

		motorSet (motor3, 127) ; // arm Down
		motorSet (motor4, -127) ;
		motorSet (motor7, 127) ;
		motorSet (motor8, -127) ;
}

void armUpTrim()
{
	motorSet (motor3, -10) ; // arm up
	motorSet (motor4, 10) ;
	motorSet (motor7, -10) ;
	motorSet (motor8, 10) ;
}

void armDownTrim ()

{
	motorSet (motor3, 20) ; // arm up
	motorSet (motor4, -20) ;
	motorSet (motor7, 20) ;
	motorSet (motor8, -20) ;
}



void stopArm () // trim
{
	motorSet (motor3, -10) ; // arm up
	motorSet (motor4, 10) ;
	motorSet (motor7, -10) ;
	motorSet (motor8, 10) ;
}

void intake (int x)
{

	motorSet (motor5, 127) ;// arm rightLine
	motorSet (motor6, -127) ;// arm leftLine

	delay(x);

	motorSet (motor5, 0) ;// stop
	motorSet (motor6, 0) ;//


}

void outtake (int x)
{

	motorSet (motor5, -127) ;// arm rightLine
	motorSet (motor6, 127) ;// arm leftLine

	delay(x);

	motorSet (motor5, 0) ;// stop
	motorSet (motor6, 0) ;//

}



void intakeDead ()
{

	motorSet (motor5, 127) ;// arm righ
	motorSet (motor6, -127) ;// arm left

}

void outtakeDead ()
{

	motorSet (motor5, -127) ;// arm righ
	motorSet (motor6, +127) ;// arm left

}


void findLineRight ()
{
			int leftLine = analogRead(1);
			int midLine = analogRead(2);
			int rightLine = analogRead(3);
			int black = 2000;

			while ( midLine > black ) // black
			{
				printf("%d\r\n", midLine);

				motorSet (motor1, 25); // drive slow until hit
				motorSet (motor2, 25);
				motorSet (motor9, 25);
				motorSet (motor10, 25);
				midLine = analogRead(2);
			}
			stopDrive ();


			driveForwardSlow(150); // make sure it will be centered
			stopDrive();
			//delay(160);

			midLine = analogRead(2);
			leftLine = analogRead(1);

			while (leftLine > black) // left is black
			{
				motorSet (motor1, 35); // turn left until mid line is set
				motorSet (motor2, 35);
				motorSet (motor9, -35);
				motorSet (motor10, -35);
				leftLine = analogRead(1);
				midLine = analogRead(2);
			}
			motorSet (motor1, -15); // no inertia
			motorSet (motor2, -15);
			motorSet (motor9, 15);
			motorSet (motor10, 15);
			delay(60);
			stopDrive();

			delay(200);

}

void findLineLeft ()
{
	int leftLine = analogRead(1);
				int midLine = analogRead(2);
				int rightLine = analogRead(3);
				int black = 2000;

				while ( midLine > black ) // black
				{
					printf("%d\r\n", midLine);

					motorSet (motor1, 25); // drive slow until hit
					motorSet (motor2, 25);
					motorSet (motor9, 25);
					motorSet (motor10, 25);
					midLine = analogRead(2);
				}
				motorSet (motor1, -15); // no inertia
				motorSet (motor2, -15);
				motorSet (motor9, -15);
				motorSet (motor10, -15);
				delay(50);
				stopDrive();

				driveForwardSlow(60); // make sure it will be centered
				stopDrive();
				delay(160);

				rightLine = analogRead(3);
				midLine = analogRead(2);
				leftLine = analogRead(1);

				while (rightLine > black) // left is black
				{
					motorSet (motor1, 7); // turn left until mid line is set
					motorSet (motor2, 7);
					motorSet (motor9, 55);
					motorSet (motor10, 55);
					leftLine = analogRead(1);
					midLine = analogRead(2);
					rightLine = analogRead(3);

				}

				motorSet (motor1, -15); // no inertia
				motorSet (motor2, -15);
				motorSet (motor9, -15);
				motorSet (motor10, -15);
				delay(50);
				stopDrive();


				stopDrive();
				delay(200);
}



void followLine ( int dylanSexxydistance)
{

	int lightDegree = 2000;
	int aliSexxySpeed = 40;
	int aliSpeed2 = 35;


	int leftLine = analogRead(1);
	int midLine = analogRead(2);
	int rightLine = analogRead(3);

	int counts = 0;
		imeReset(0); // reset right ime
		imeGet(0, &counts);
		printf("%d\r\n", leftLine);
		printf("%d\r\n", rightLine);
		printf("%d\r\n", midLine);

		while (abs(counts) < dylanSexxydistance)
		{
			double leftLine = analogRead(1);
			double midLine = analogRead(2);
			double rightLine = analogRead(3);
			//printf("%d\r\n  ", leftLine);
			//printf("%d\r\n	", rightLine);
			//printf("%d\r\n \n ", midLine);
			//printf("\r\n  ");
			//printf("\r\n  ");
			//printf("\r\n  ");
			//printf("\r\n  ");
			//printf("\r\n  ");

			//if(leftLine>1300 && rightLine>1300 && midLine <1300)
			//{

			//}

			imeGet(0, &counts); // keep getting the value





			if (leftLine<2000 || rightLine<2000 || midLine<2000)//(midLine>100) // Mid is black
			{
				printf("%f \t", aliSexxySpeed*((((rightLine)/(leftLine))+5)/10));//right
				printf("%f \n", aliSexxySpeed*((((leftLine)/(rightLine))+5)/10));//left
				motorSet (motor1, aliSexxySpeed*((((rightLine)/(leftLine))+5)/10));
				motorSet (motor2, aliSexxySpeed*((((rightLine)/(leftLine))+5)/10));
				motorSet (motor9, aliSexxySpeed*((((leftLine)/(rightLine))+5)/10));
				motorSet (motor10, aliSexxySpeed*((((leftLine)/(rightLine))+5)/10));
			}


			/*else
			{
				printf("%f\t", aliSexxySpeed*((((rightLine)/(leftLine*1.5))+2)/5));//right
				printf("%f\t", aliSexxySpeed*((((leftLine)/(rightLine*1.5))+2)/5));//left
				motorSet (motor1, aliSexxySpeed*((((rightLine)/(leftLine*2))+2)/5));
				motorSet (motor2, aliSexxySpeed*((((rightLine)/(leftLine*2))+2)/5));
				motorSet (motor9, aliSexxySpeed*((((leftLine)/(rightLine*2))+2)/5));
				motorSet (motor10, aliSexxySpeed*((((leftLine)/(rightLine*2))+2)/5));
			}*/

/*
			if (leftLine < 2000) // leftLine white
			{

				motorSet (motor1, 40);
				motorSet (motor2, 40);
				motorSet (motor9, 0);
				motorSet (motor10, 0);

			}

			if (rightLine < 2000) // rightLine white
			{

				motorSet (motor1, 0);
				motorSet (motor2, 0);
				motorSet (motor9, 40);
				motorSet (motor10, 40);

			}

			if (midLine < 2000)
			{
				motorSet (motor1, 40);
				motorSet (motor2, 40);
				motorSet (motor9, 40);
				motorSet (motor10, 40);
			}
*/

		}

		stopDrive ();
		delay (200);


}




void rushRed ()
{

// variables
	int armMin = 300;
	int wallHeight = 1000;
	int goalHeight = 1700;
	int pot = analogRead (8);
	int midLine = analogRead(2);


	int encoder1 = 1875; //drive under wall
	int encoder2 = 170; // rotate 90 degrees
	int encoder3 = 1400; // backwards to the opponets goal
	int encoder4 = 630; //turn to goal + enclose it


	// begin routine

	intakeDead(); // unfold
	delay(300); // needs to clear the wall..
	driveBack (encoder1); // drive backwards to under the bridge
	stopIntake();
	turnRight (encoder2); // turn ass to opponets goal
	driveBackDead(encoder3); // drive to opponets goal
	delay(500);

	midLine = 3000;
	while (midLine > 2000)
	{
		midLine = analogRead(2);
	}

	motorSet (motor1, 10)	; // no inertia
	motorSet (motor2, 10)	;
	motorSet (motor10, 10)	;
	motorSet (motor9, 10)	;
	delay (85);


	//driveBackDead(); // push them
	//delay (300);
	stopDrive ();
	delay (7000); // wait till auto end
	driveBackDead ();// push them
	delay (800);
	stopDrive();
	delay(100);
	driveForwardDead(); // driveback towards goal
	delay(300);
	stopDrive ();
	armUp(goalHeight); //arm up
	scrapeRight (encoder4);  //encase the goal
	driveForwardSlowDead ();
	delay(700);
	stopDrive();
	outtake (3000);

	stopAll ();

}


void rushBlue ()
{


	// variables
		int armMin = 300;
		int wallHeight = 1000;
		int goalHeight = 1700;
		int pot = analogRead (8);
		int midLine = analogRead(2);


		int encoder1 = 1800; //drive under wall
		int encoder2 = 130; // rotate 90 degrees
		int encoder3 = 1400; // backwards to the opponets goal
		int encoder4 = 630; //turn to goal + enclose it


		// begin routine

		intakeDead(); // unfold
		delay(300); // needs to clear the wall..
		driveBack (encoder1); // drive backwards to under the bridge
		stopIntake();
		turnLeft (encoder2); // turn ass to opponets goal
		driveBackDead(encoder3); // drive to opponets goal
		delay(500);

		midLine = 3000;
		while (midLine > 2000)
		{
			midLine = analogRead(2);
		}

		motorSet (motor1, 10)	; // no inertia
		motorSet (motor2, 10)	;
		motorSet (motor10, 10)	;
		motorSet (motor9, 10)	;
		delay (85);


		//driveBackDead(); // push them
		//delay (300);
		stopDrive ();
		delay (7000); // wait till auto end
		driveBackDead ();// push them
		delay (800);
		stopDrive();
		delay(100);
		driveForwardDead(); // driveback towards goal
		delay(300);
		stopDrive ();
		intakeDead();
		armUp(goalHeight); //arm up
		scrapeLeft (encoder4);  //encase the goal
		driveForwardSlowDead ();
		delay(700);
		stopDrive();
		outtake (3000);

		stopAll ();


}


void classic15Red()
{
		int armMin = 300;
		int wallHeight = 1000;
		int goalHeight = 1700;
		int dead1 = 1200;
		int dead2 = 2000;
		int dead3 = 3000;
		int pot = analogRead (8);

	//encoder values
		int encoder1 = 900; //drive to goal
		int encoder2 = 325; //keep going towards goal
		int encoder3 = 0; //drive slow, adjust to 90 degrees
		int encoder4 = 325; //back up
		int encoder5 = 1300; //back up across the barrier again
		int encoder6 = 80; // turn towards center large ball
		int encoder7 = 550; // hit 1st ball off the barrier
		int encoder8 = 350; // drive back
		int encoder9 = 200; // turn towards other large ball
		int encoder10 = 400; // hit 2nd ball off the barrier
		int encoder11 = 300; // drive back to square
		int encoder12 = 270; // turn to barf
		int encoder13 = 700; // drive to barf + pickup
		int encoder14 = 400;
		int encoder15 = 700;


	// begin routine

	intakeDead();
	delay(1000);
	stopIntake();

	// driveforward (some curve)////////////////////////////////////////////////////
	int counts = 0;
		imeReset(0); // rest rightLine ime
		imeGet(0, &counts);

		while (abs(counts) < encoder1)
		    {
		      motorSet (motor1, 110)	; // slight curve cuz friction
		      motorSet (motor2, 110)	;
		      motorSet (motor10, 127)	;
		      motorSet (motor9, 127)	;

		      imeGet(0, &counts); // keep getting the value
		    }

		motorSet (motor1, 0)	;
		motorSet (motor2, 0)	;
		motorSet (motor10, 0)	;
		motorSet (motor9, 0)	;
		delay(200);

///////////////////////////////////////////////////////////////////////////////



	//driveForward(encoder1); // drive to goal
	armUp (goalHeight); //raise arm after cross barrier
	driveForwardSlow(encoder2);  //keep going towards goal
	driveForwardSlowDead (); //drive slow, adjust to 90 degrees
	delay(1000);
	outtake (1700);// outtake
	driveBack(encoder4); // back up
	delay(300);
	armDown(armMin); // lower arm
	driveBack(encoder5); //back up across the barrier again
	delay(300);
	turnRight(encoder6); // turn towards center large ball
	armUp(wallHeight); // arm up to wall height
	driveForward(encoder7); // hit it off the barrier
	delay (500);
	driveBack(encoder8); // drive back
	delay(300);
	turnLeft(encoder9); // turn towards other large ball
	driveForward(encoder10); // hit 2nd ball off the barrier
	delay(500);
	driveBack(encoder11); // drive back to square
	delay(600);
	turnRight(encoder12); // turn to barf
	delay(300);
	armDown(armMin);
	intakeDead(); // pick up barf
	driveForward(encoder13); // drive towards barf + intake it
	delay(500);



	//end of routine




	stopAll () ;
	delay(60000);///////////////////////////////////////////////////////////////////////////////////


}

void classic15Blue()
{
		int armMin = 290;
		int wallHeight = 1000;
		int goalHeight = 1700;
		int dead1 = 1200;
		int dead2 = 2000;
		int dead3 = 3000;
		int pot = analogRead (8);

	//encoder values
		int encoder1 = 900; //drive to goal
		int encoder2 = 325; //keep going towards goal
		int encoder3 = 0; //drive slow, adjust to 90 degrees
		int encoder4 = 325; //back up
		int encoder5 = 1350; //back up across the barrier again
		int encoder6 = 80; // turn towards center large ball
		int encoder7 = 600; // hit 1st ball off the barrier
		int encoder8 = 350; // drive back
		int encoder9 = 200; // turn towards other large ball
		int encoder10 = 400; // hit 2nd ball off the barrier
		int encoder11 = 300; // drive back to square
		int encoder12 = 290; // turn to barf
		int encoder13 = 800; // drive to barf + pickup
		int encoder14 = 400;
		int encoder15 = 700;


	// begin routine

	intakeDead();
	delay(1000);
	stopIntake();

	// driveforward (some curve)////////////////////////////////////////////////////
	int counts = 0;
		imeReset(0); // rest rightLine ime
		imeGet(0, &counts);

		while (abs(counts) < encoder1)
		    {
		      motorSet (motor1, 110)	; // slight curve cuz friction
		      motorSet (motor2, 110)	;
		      motorSet (motor10, 127)	;
		      motorSet (motor9, 127)	;

		      imeGet(0, &counts); // keep getting the value
		    }

		motorSet (motor1, 0)	;
		motorSet (motor2, 0)	;
		motorSet (motor10, 0)	;
		motorSet (motor9, 0)	;
		delay(200);

///////////////////////////////////////////////////////////////////////////////



	//driveForward(encoder1); // drive to goal
	armUp (goalHeight); //raise arm after cross barrier
	driveForwardSlow(encoder2);  //keep going towards goal
	driveForwardSlowDead (); //drive slow, adjust to 90 degrees
	delay(1000);
	outtake (1700);// outtake
	driveBack(encoder4); // back up
	delay(300);
	armDown(armMin); // lower arm
	driveBack(encoder5); //back up across the barrier again
	delay(300);
	turnLeft(encoder6); // turn towards center large ball
	armUp(wallHeight); // arm up to wall height
	driveForward(encoder7); // hit it off the barrier
	delay (500);
	driveBack(encoder8); // drive back
	delay(300);
	turnRight(encoder9); // turn towards other large ball
	driveForward(encoder10); // hit 2nd ball off the barrier
	delay(500);
	driveBack(encoder11); // drive back to square
	delay(600);
	turnLeft(encoder12); // turn to barf
	delay(300);
	armDown(armMin);
	intakeDead(); // pick up barf
	driveForward(encoder13); // drive towards barf + intake it
	delay(500);



	//end of routine




	stopAll () ;
	delay(60000);///////////////////////////////////////////////////////////////////////////////////


}





void rejectionRed()
{
	// variables
		int armMin = 300;
		int wallHeight = 1000;
		int goalHeight = 1700;
		int pot = analogRead (8);
		int midLine = analogRead(2);


		int encoder1 = 1875; //drive under wall
		int encoder2 = 170; // rotate 90 degrees
		int encoder3 = 1900; // backwards to the opponets goal
		int encoder4 = 100; // turn to first blue ball
		int encoder5 = 450; //hit 1st blue ball off
		int encoder6 = 350; // drive back
		int encoder7 = 175; // turn to 2nd blue ball
		int encoder8 = 550; // hit 2nd ball off
		int encoder9 = 250; // drive back to position
		int encoder10 = 400; // rotate to line

		// begin routine

		intakeDead(); // unfold
		delay(300); // needs to clear the wall..
		driveBack (encoder1); // drive backwards to under the bridge
		stopIntake();
		turnRight (encoder2); // turn ass to opponets goal
		driveBackDead(encoder3); // drive to opponets goal
		delay(500);

		midLine = 3000;
		while (midLine > 2000)
		{
			midLine = analogRead(2);
		}

		motorSet (motor1, 10)	; // no inertia
		motorSet (motor2, 10)	;
		motorSet (motor10, 10)	;
		motorSet (motor9, 10)	;
		delay (85);





		armUp(wallHeight);// arm up
		turnLeft (encoder4); // turn towards center blue ball
		driveForward(encoder5); // hit 1st ball off
		delay(700);
		driveBack(encoder6); // back
		delay (700);
		turnLeft(encoder7); // turn towards 2nd blue ball
		delay (700);
		driveForward(encoder8); // hit off 2nd blue ball
		delay (700);
		intakeDead();
		driveBack(encoder9); // position
		delay(700);
		turnRight(encoder10); // encase opponet goal
		delay(700);
		armUp(goalHeight);

		findLineLeft();
		//followLine(300);


		driveForwardDead (); // drive to goal
		delay(700);
		stopDrive();
		outtake(3000);


		stopAll ();
		delay(60000);

}

void rejectionBlue ()
{

	// variables
			int armMin = 300;
			int wallHeight = 1000;
			int goalHeight = 1700;
			int pot = analogRead (8);
			int midLine = analogRead(2);





			int encoder1 = 1800; //drive under wall
			int encoder2 = 130; // rotate 90 degrees
			int encoder3 = 1400; // backwards to the opponets goal
			int encoder4 = 100; //turn to goal + enclose it
			int encoder5 = 450; //hit 1st blue ball off
			int encoder6 = 350; // drive back
			int encoder7 = 175; // turn to 2nd blue ball
			int encoder8 = 550; // hit 2nd ball off
			int encoder9 = 250; // drive back to position
			int encoder10 = 370; // rotate to line

			// begin routine

			intakeDead(); // unfold
			delay(300); // needs to clear the wall..
			driveBack (encoder1); // drive backwards to under the bridge
			stopIntake();
			turnLeft (encoder2); // turn ass to opponets goal
			driveBackDead(encoder3); // drive to opponets goal
			delay(500);

			midLine = 3000;
			while (midLine > 2000)
			{
				midLine = analogRead(2);
			}

			motorSet (motor1, 10)	; // no inertia
			motorSet (motor2, 10)	;
			motorSet (motor10, 10)	;
			motorSet (motor9, 10)	;
			delay (85);





			armUp(wallHeight);// arm up
			turnRight (encoder4); // turn towards center blue ball
			driveForward(encoder5); // hit 1st ball off
			delay(700);
			driveBack(encoder6); // back
			delay (700);
			turnRight(encoder7); // turn towards 2nd blue ball
			delay (700);
			driveForward(encoder8); // hit off 2nd blue ball
			delay (700);
			intakeDead();
			driveBack(encoder9); // position
			delay(700);
			turnLeft(encoder10); // encase opponet goal
			delay(700);
			armUp(goalHeight);

			findLineRight();
			//followLine(300);


			driveForwardDead (); // drive to goal
			delay(700);
			stopDrive();
			outtake(3000);


			stopAll ();
			delay(60000);




}



void ram ()

{
	intakeDead(); // unfold
	;

	driveForwardDead ();
	delay (5000);
	stopDrive ();
	stopIntake();

	stopAll ();

}

void kakitRed ()
{

// variables
	int armMin = 300;
	int wallHeight = 1000;
	int goalHeight = 1650;

	int pot = analogRead (8);

	int encoder00 = 250; // back up abit to row
	int encoder0 = 950; // turn 360 degrees, knock off buckys, face line
	int encoder1 = 162; // rotate towards 2 buckys
	int encoder2 = 150; // drive towards buckys
	int encoder3 = 400; // back up to bump
	int encoder4 = 200; // back up towards bridge
	int encoder5 = 360; // rotate 180 degrees to the large ball
	int encoder6 = 900; // go under bridge and knock out large ball
	int encoder7 = 90; // turn to goal
	int encoder8 = 200; // drive to goal
	int encoder9 = 75;


	// begin routine
	intake(300);
	armDownTrim();

	driveForwardDead (); //ram big balls
	delay (1500);
	stopDrive();
	delay(500);

	driveBack(encoder00); // back up to row abit
	intakeDead();



	turnLeft (encoder0); // turn 360 degrees

	driveBackDead(); // drive back + wall align
	delay(1300);
	stopDrive();
	delay(500);

	turnRight (encoder1); // turn to two buckys
	intakeDead();

	followLine(300); // make sure ur straight

	driveForwardSlowDead (); // drive towards buckys
	delay(500);
	stopDrive();
	delay(600);

	driveForwardDead(); //get the 2nd ball
	delay (200);
	stopDrive ();
	delay (600);


	stopIntake ();

	driveBack(encoder3); // back up to bump

	armUpDead();// armup
	delay(50);
	stopArm();
	stopIntake();

	driveBackSlowDead (); // allign the bump
	delay (300);
	stopDrive();
	delay (500);

	driveBackDead();  // over the bump
	delay(1000);
	stopDrive();
	delay(500);

	driveForwardSlowDead(); // alighn to bump
	delay(800);
	stopDrive ();
	delay (500);

	driveBackSlow(encoder4); // back up towards bridge
	turnLeft (encoder5); // rotate 180 degrees to the large ball
	armDown(armMin);
	armDownTrim();

	driveForward (encoder6) ; // go under the bridge + knock large ball
	armUp (goalHeight);

	turnRight(encoder7); // turn to goal

	findLineRight();
	followLine(300);



	driveForwardSlowDead (); // drive to goal
	delay (700);
	stopDrive();
	outtake (7000); // outtake 3


	stopAll ();

}

void rejectionBlueSkills ()
{

	// variables
			int armMin = 300;
			int wallHeight = 1000;
			int goalHeight = 1700;
			int pot = analogRead (8);
			int midLine = analogRead(2);





			int encoder1 = 1800; //drive under wall
			int encoder2 = 130; // rotate 90 degrees
			int encoder3 = 1400; // backwards to the opponets goal
			int encoder4 = 270; //turn to center of large balls
			int encoder5 = 200; //hit 1st blue ball off
			int encoder55 = 300; // back a bit
			int encoder6 = 450; //hit 2nd ball off
			int encoder7 = 450; // drive back past line
			int encoder8 = 160; // turn to line

			// begin routine

			intakeDead(); // unfold
			delay(300); // needs to clear the wall..
			driveBack (encoder1); // drive backwards to under the bridge
			stopIntake();
			turnLeft (encoder2); // turn ass to opponets goal
			driveBackDead(encoder3); // drive to opponets goal
			delay(500);

			midLine = 3000;
			while (midLine > 2000)
			{
				midLine = analogRead(2);
			}

			motorSet (motor1, 10)	; // no inertia
			motorSet (motor2, 10)	;
			motorSet (motor10, 10)	;
			motorSet (motor9, 10)	;
			delay (85);





			armUp(wallHeight);// arm up
			turnRight (encoder4); // turn towards center of large balls
			driveForwardSlowDead(); // go between large balls
			delay(1200);
			stopDrive ();
			delay(300);
			turnLeft (encoder5); //hit center ball
			driveBackSlow(encoder55);
			turnRight (encoder6); // hit far ball
			driveBackSlow (encoder7); // back up past line
			turnRight (encoder8); // tun to line

			armUp (goalHeight);

			findLineLeft();
			//followLine(300);


			driveForwardDead (); // drive to goal
			delay(700);
			stopDrive();
			outtake(3000);


			stopAll ();
			delay(60000);




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

