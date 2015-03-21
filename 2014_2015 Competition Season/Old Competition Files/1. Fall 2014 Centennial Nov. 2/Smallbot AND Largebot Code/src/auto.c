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


	// all jumper comands here:
	//1 = out
	// 0 = in
	if ((jumper1 == 0) && (jumper2 == 0))
	{
		smallbotBlue();
	}

	if ((jumper1 == 0) && (jumper3 == 0))
	{
		armbotBlue();
	}

	if ((jumper1 == 1) && (jumper2 == 0))
	{
		smallbotRed();
	}

	if ((jumper1 == 1) && (jumper3 == 0))
	{
		armbotRed();
	}

	if (jumper1 == 0)
	{
		//rejectionBlue();
	}

	if (jumper1 == 1)
	{
		//rejectionRed();
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

void armUpTime(int x)
{


	motorSet (motor3, -127) ; // arm up
	motorSet (motor4, 127) ;
	motorSet (motor7, -127) ;
	motorSet (motor8, 127) ;

	delay (x);

		armUpTrim();
}

void armDownTime(int x)
{


	motorSet (motor3, 127) ; // arm Down
	motorSet (motor4, -127) ;
	motorSet (motor7, 127) ;
	motorSet (motor8, -127) ;

	delay (x);

		armDownTrim();
}

void armUpEnc(int x)
{
	int counts = encoderGet(encoder);

	while (abs(counts) < x)
	{
		motorSet (motor3, -127) ; // arm up
		motorSet (motor4, 127) ;
		motorSet (motor7, -127) ;
		motorSet (motor8, 127) ;
		counts = encoderGet(encoder); //keep getting the value
	}

	armUpTrim();
	delay (300);
}

void armDownEnc(int x)
{
	int counts = encoderGet(encoder);

	while (abs(counts) < x)
	{
		motorSet (motor3, 127) ; // arm down
		motorSet (motor4, -127) ;
		motorSet (motor7, 127) ;
		motorSet (motor8, -127) ;
		counts = encoderGet(encoder);//keep getting the value
	}

	armDownTrim();
	delay (300);
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




void smallbotRed ()
{

	// variables
	int armMin = 300; // idk
	int wallHeight = 1000; // idk
	int goalHeight24 = 1700; // idk
	int pot = analogRead (8);
	int midLine = analogRead(2);


	int encoder1 = 1800; //drive back towards pyramid
	int encoder2 = 130; // rotate 90 degrees
	int encoder3 = 1400; // backwards to the opponets floor


	// begin routine

	armUp(goalHeight24); // arm up to the goal height
	outtake (2000); // outtake for 2 secs
	delay(300); // no clutch
	intake (2000); // move unicorn horn back up
	driveBack (encoder1);
	turnLeft(encoder2);
	driveBack (encoder3);



	stopAll ();
	delay (60000);

}


void smallbotBlue ()
{

		stopAll ();


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
	armDown(floorHeightU);
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

