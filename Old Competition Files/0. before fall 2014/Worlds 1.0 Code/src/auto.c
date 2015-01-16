// test gladstone
// test workspace 2
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
void turnLeftArc(int x); // x = encoder
void turnRightArc(int x);
void driveForwardDead ();
void driveBackDead ();
void driveForwardSlow (int x);
void driveBackSlow (int x) ;
void driveForwardSlowDead ();
void driveBackSlowDead ();
void scrapeRight (int x) ; // x = encoder
void scrapeLeft (int x);
void scrapeRightBack (int x); // x = timer
void scrapeLeftBack (int x); // x = encoder
void stopAll();
void stopDrive();

void stopIntake();
void armUp (int x); // x = pot value
void armDown(int x); // x = pot value
void armUpDead();
void armDownDead ();
void stopArm ();
void intake (int x); //x = time
void outtake (int x);
void intakeDead (); // continuous intaking
void outtakeDead ();// countinuous outtake
void allLine (int dylanSexxydistance);
void findLineRight (int x);
void findLineLeft (int x);


// autonomous routines
void rushRed ();
void rushBlue();
void classic15Red();
void classic15Blue();
void rejectionRed();
void rejectionBlue();
void kakitRed ();
void kakitBlue ();
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


rushBlue ();
allLine (99999);

// all jumper comands here:





}


void driveForward(int x)
{
	int counts = 0;
	imeReset(0); // rest rightLine ime
	imeGet(0, &counts);

	while (abs(counts) < x)
	    {
	      motorSet (motor1, 100)	;
	      motorSet (motor2, 100)	;
	      motorSet (motor10, 100)	;
	      motorSet (motor9, 100)	;

	      imeGet(0, &counts); // keep getting the value
	    }
	motorStop (motor1);
	motorStop (motor2);
	motorStop (motor10);
	motorStop (motor9);
	delay (200);
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
	motorStop (motor1);
	motorStop (motor2);
	motorStop (motor10);
	motorStop (motor9);
	delay (200);
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
	delay (200);
}

void driveForwardSlowDead()
{


		  motorSet (motor1, 40)	;
		  motorSet (motor2, 40)	;
		  motorSet (motor10, 40);
		  motorSet (motor9, 40)	;


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

		    motorSet (motor1, 0)	;
		    motorSet (motor2, 0)	;
		    motorSet (motor10, 90);
		    motorSet (motor9, 90)	;
		    delay(x);

		    motorSet (motor1, 0)	;
		   	motorSet (motor2, 0)	;
		   	motorSet (motor10, 0);
		   	motorSet (motor9, 0)	;
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
		delay (200);
}

void scrapeRightBack (int x)
{
	motorSet (motor1, 90)	;
	motorSet (motor2, 90)	;
	motorSet (motor10, 0);
	motorSet (motor9, 0)	;
	delay(x);

	motorSet (motor1, 0)	;
	motorSet (motor2, 0)	;
	motorSet (motor10, 0);
	motorSet (motor9, 0)	;

}

void scrapeLeftBack (int x)
{
	int counts = 0;
		imeReset(0); // rest rightLine ime
		imeGet(0, &counts);

			while (abs(counts) < x)
			    {
			      motorSet (motor1, 0)	;
			      motorSet (motor2,0)	;
			      motorSet (motor10, 90);
			      motorSet (motor9, 90)	;

			      imeGet(0, &counts); // keep getting the value
			    }
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

	stopArm();
	delay (1000);
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

		stopArm();
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


void findLineRight (int x)
{
			int leftLine = analogRead(1);
			int midLine = analogRead(2);
			int rightLine = analogRead(3);

			if ( midLine > 1300 ) // black
			{
				printf("%d\r\n", midLine);

				motorSet (motor1, 40); // drive slow until hit
				motorSet (motor2, 40);
				motorSet (motor9, 40);
				motorSet (motor10, 40);

			}

			if ( midLine < 1300 )
			{
				turnRight(x);
			}
}

void findLineLeft (int x)
{
			int leftLine = analogRead(1);
			int midLine = analogRead(2);
			int rightLine = analogRead(3);

			if ( midLine > 1300 ) //black
			{
				printf("%d\r\n", midLine);

				motorSet (motor1, 40);
				motorSet (motor2, 40);
				motorSet (motor9, 40);
				motorSet (motor10, 40);
			}

			if ( midLine < 1300 )
			{
				turnLeft(x);
			}
}



void allLine ( int dylanSexxydistance)
{

	int lightDegree = 2000;
	int aliSexxySpeed = 40;
	int aliSpeed2 = 35;
	while (1 == 1)
	{
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
		}

}




void rushRed ()
{

// variables
	int armMin = 300;
	int wallHeight = 1000;
	int goalHeight = 1550;
	int pot = analogRead (8);


	int encoder1 = 1550; //drive under wall
	int encoder2 = 136; // rotate 90 degrees
	int encoder3 = 900; // backwards to the opponets goal
	int encoder4 = 900; //turn to goal + enclose it


	// begin routine

	intakeDead(); // unfold
	delay(300); // needs to clear the wall..
	driveBack (encoder1); // drive backwards to under the bridge
	stopIntake();
	turnRight (encoder2); // turn ass to opponets goal
	driveBack (encoder3); // drive to opponets goal
	driveBackDead(); // push them
	delay (200);
	stopDrive ();
	delay (7000); // wait till auto end
	driveBackDead ();// push them
	delay (600);
	stopDrive();
	delay(100);
	driveForwardDead(); // driveback towards goal
	delay(400);
	stopDrive ();
	armUp(goalHeight); //arm up
	scrapeRight (encoder4);  //encase the goal
	outtake (3000);

	stopAll ();

}


void worldsBlue ()
{

// variables
	int armMin = 300;
	int wallHeight = 100;
	int goalHeight = 1550;
	int dead1 = 1000;
	int dead2 = 2000;
	int dead3 = 3000;
	int pot = analogRead (8);


	int encoder1 = 1500; //drive under wall
	int encoder2 = 136; // rotate 90 degrees
	int encoder3 = 900; // backwards to the opponets goal
	int encoder4 = 400; //turn to goal + enclose it


	// begin routine

	intakeDead(); // unfold
	delay(300); // needs to clear the wall..
	driveBack (encoder1); // drive backwards to under the bridge
	stopIntake();
	turnLeft (encoder2); // turn ass to opponets goal
	driveBack (encoder3); // drive to opponets goal
	driveBackDead(); // push them
	delay (200);
	stopDrive ();
	delay (7000); // wait till auto end
	driveBackDead ();// push them
	delay (600);
	stopDrive();
	delay(100);
	driveForwardDead(); // driveback towards goal
	delay(400);
	stopDrive ();
	armUp(goalHeight); //arm up
	scrapeLeft (encoder4);  //encase the goal
	outtake (300);

	stopAll ();

}


void classic15Red()
{
		int armMin = 300;
		int wallHeight = 1000;
		int goalHeight = 1550;
		int dead1 = 1000;
		int dead2 = 2000;
		int dead3 = 3000;
		int pot = analogRead (8);

	//encoder values
		int encoder1 = 1125; //drive to goal
		int encoder2 = 325; //keep going towards goal
		int encoder3 = 0; //drive slow, adjust to 90 degrees
		int encoder4 = 275; //back up
		int encoder5 = 800; //back up across the barrier again
		int encoder6 = 90; // turn towards center large ball
		int encoder7 = 220; // hit it off the barrier
		int encoder8 = 350; // drive back
		int encoder9 = 110; // turn towards other large ball
		int encoder10 = 681; // hit it off the barrier
		int encoder11 = 300; // drive back to square
		int encoder12 = 150; // ass to wall
		int encoder13 = 800;
		int encoder14 = 400;
		int encoder15 = 700;
		int encoder16 = 400;
		int encoder17 = 100;
		int encoder18 = 400;
		int encoder19 = 700;
		int encoder20 = 400;
		int encoder21 = 100;
		int encoder22 = 400;
		int encoder23 = 700;

	// begin routine

	intakeDead();
	delay(1000);
	stopIntake();
	driveForward(encoder1); // drive to goal
	armUp (goalHeight); //raise arm after cross barrier
	driveForwardSlow(encoder2);  //keep going towards goal
	driveForwardSlowDead (dead1); //drive slow, adjust to 90 degrees
	outtake (1500);
	driveBack(encoder4); // back up
	armDown(armMin); // lower arm
	driveBack(encoder5); //back up across the barrier again
	turnRight(encoder6); // turn towards center large ball
	armUp(wallHeight); // arm up to wall height
	driveForward(encoder7); // hit it off the barrier
	driveBack(encoder8); // drive back
	turnLeft(encoder9); // turn towards other large ball
	driveForward(encoder10); // hit it off the barrier
	driveBackSlowDead (dead2);  // drive back to square
	turnLeftArc (encoder12); // ass to wall
	driveBackSlowDead (dead2) ; // wall align 90degrees
	armDown (armMin); // arm down to floor
	intakeDead (); // start intaking
	driveForwardSlow (encoder13) ;// drive towards barf and intake whatever
	turnRightArc (encoder14); // rotate towards the barrier
	stopIntake();
	armUp(wallHeight); // arm up to wall height
	driveForwardSlow (encoder15); // drive to barrier
	stopDrive(); // stop at barrier
	outtake (1500); //drop the barf
	driveBackSlowDead(dead2); //hump da bump
	armDown (armMin); // arm down to floor
	intakeDead (); //start intaking
	turnLeftArc (encoder16); //face the barf
	driveForwardSlow (encoder17) ;// drive towards barf and intake whatever
	turnRightArc (encoder18) ; // rotate towards the barrier
	stopIntake();
	armUp(wallHeight); // arm up to wall height
	driveForwardSlow (encoder19); // drive to barrier
	stopDrive(); // stop at barrier
	outtake (1500); //drop the barf
	driveBackSlowDead(dead2); //drive to and align on bump
	armDown (armMin); // arm down to floor
	intakeDead (); //start intaking
	turnLeftArc (encoder20); //face the barf
	driveForwardSlow (encoder21) ;// drive towards barf and intake whatever
	turnRightArc (encoder22) ; // rotate towards the barrier
	stopIntake();
	armUp(wallHeight); // arm up to wall height
	driveForwardSlow (encoder23); // drive to barrier
	outtake (1500); //drop the barf



	//end of routine




	stopAll () ;
	delay(60000);///////////////////////////////////////////////////////////////////////////////////


}

void rejectionRed()
{
	// variables
		int armMin = 300;
		int wallHeight = 1000;
		int goalHeight = 1550;
		int pot = analogRead (8);


		int encoder1 = 1200; //drive under wall
		int encoder2 = 136; // rotate 90 degrees
		int encoder3 = 900; // backwards to the opponets goal
		int encoder4 = 150; //rotate 90
		int encoder5 = 200; // ass towards bridge


		// begin routine

		intakeDead(); // unfold
		delay(300); // needs to clear the wall..
		driveBack (encoder1); // drive backwards to under the bridge
		stopIntake();
		turnRight (encoder2); // turn ass to opponets goal
		driveBack (encoder3); // drive to opponets goal
		turnRight (encoder4); // ass to bridge
		armUp(wallHeight);// arm up
		driveBack(encoder5); // block their launch

		stopAll ();

}


void reverse15Red()
{
	// variables
			int armMin = 300;
			int wallHeight = 1000;
			int goalHeight = 1550;
			int pot = analogRead (8);


			int encoder1 = 1200; //drive under wall
			int encoder2 = 136; // rotate 90 degrees
			int encoder3 = 1300; // backwards to the opponets goal
			int encoder4 = 900; //turn to bridge
			int encoder5 = 200; // knock their wallball
			int encoder6 = 200; // turn to other ball
			int encoder7 = 400; // knock their center ball
			int encoder8 = 400; // positioning



			// begin routine

			intakeDead(); // unfold
			delay(300); // needs to clear the wall..
			driveBack (encoder1); // drive backwards to under the bridge
			stopIntake();
			turnRight (encoder2); // turn ass to opponets goal
			driveBack (encoder3); // drive to opponets goal
			driveBackDead(); // 90 deg align
			delay(400);
			stopDrive ();
			armUp(wallHeight);// arm up
			scrapeLeft (encoder4); // turn to wall ball
			driveForward (encoder5); // knock off wall ball
			scrapeLeftBack(encoder6); // turn to middle ball
			driveForward(encoder7); // knock off middle ball
			driveBack (encoder8); // positioning

			stopAll ();




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
	int goalHeight = 1550;
	int dead1 = 1000;
	int dead2 = 2000;
	int dead3 = 3000;
	int pot = analogRead (8);


	int encoder1 = 1000;
	int encoder2 = 150;
	int encoder3 = 2000;
	int encoder4 = 75;
	int encoder5 = 75;
	int encoder6 = 75;
	int encoder7 = 75;
	int encoder8 = 75;
	int encoder9 = 75;


	// begin routine
	driveForwardDead (); //ram big balls
	intakeDead ();
	delay (3000);
	stopIntake();
	driveBackDead (4000); // wall align to 90 deg
	driveForward (encoder1);
	turnRight (encoder2); // turn towards buckys
	intakeDead ();
	//line follow forward (encoder 4)

	driveBackSlowDead (); // allign the bump
	driveBackDead();  // over the bump
	driveForwardSlowDead(); // alighn to bump
	driveBackSlow(encoder4);
	turnRight (encoder5);
	driveBackSlow (encoder6) ; // go under the bridge
	armUpDead (); // break the bridge
	delay(500);
	armDown (armMin);
	driveBack (encoder7);
	turnRight (encoder8);
	armUp (goalHeight);
	//line follow (encoder9);
	outtake(8000); // score all three balls in the goal

	stopAll ();

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

