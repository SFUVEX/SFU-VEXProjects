/*
 * autoSubroutines.c
 *
 *  Created on: Oct 17, 2014
 *      Author: awiebe
 */

#include "main.h"
#include "autoSubroutines.h"
#include <stdbool.h>

void driveForward(int x) {
	int imeAccumulator = 0;
	imeReset(0); // rest rightLine I.M.E

	//Read decoder into counts
	imeGet(0, &imeAccumulator);

	//Move forward at max speed until desired x
	while (abs(imeAccumulator) < x) {
		motorSet(MOTOR1, FORWARD_VELOCITY);
		motorSet(MOTOR2, FORWARD_VELOCITY);
		motorSet(MOTOR10, FORWARD_VELOCITY);
		motorSet(MOTOR9, FORWARD_VELOCITY);

		imeGet(0, &imeAccumulator); // keep getting the value
	}

	//Cancel forward inertia
	motorSet(MOTOR1, -INERTIA_CANCELLATION_FACTOR); // no inertia
	motorSet(MOTOR2, -INERTIA_CANCELLATION_FACTOR);
	motorSet(MOTOR10, -INERTIA_CANCELLATION_FACTOR);
	motorSet(MOTOR9, -INERTIA_CANCELLATION_FACTOR);
	delay(65);

	motorSet(MOTOR1, 0);
	motorSet(MOTOR2, 0);
	motorSet(MOTOR10, 0);
	motorSet(MOTOR9, 0);
	delay(200);

}

void driveBack(int x) {
	int counts = 0;
	imeReset(0); // rest rightLine I.M.E
	imeGet(0, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR1, REVERSE_VELOCITY);
		motorSet(MOTOR2, REVERSE_VELOCITY);
		motorSet(MOTOR10, REVERSE_VELOCITY);
		motorSet(MOTOR9, REVERSE_VELOCITY);

		imeGet(0, &counts); // keep getting the value
	}

	motorSet(MOTOR1, INERTIA_CANCELLATION_FACTOR); // no inertia
	motorSet(MOTOR2, INERTIA_CANCELLATION_FACTOR);
	motorSet(MOTOR10, INERTIA_CANCELLATION_FACTOR);
	motorSet(MOTOR9, INERTIA_CANCELLATION_FACTOR);
	delay(65);

	motorStop(MOTOR1);
	motorStop(MOTOR2);
	motorStop(MOTOR10);
	motorStop(MOTOR9);
	delay(200);
}

void turnRight(int x) {
	int counts = 0;
	imeReset(0); // rest rightLine I.M.E
	imeGet(0, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR1, -64);
		motorSet(MOTOR2, -64);
		motorSet(MOTOR10, 64);
		motorSet(MOTOR9, 64);

		imeGet(0, &counts); // keep getting the value
	}

	motorSet(MOTOR1, 10); // no inertia
	motorSet(MOTOR2, 10);
	motorSet(MOTOR10, -10);
	motorSet(MOTOR9, -10);
	delay(45);

	motorStop(MOTOR1);
	motorStop(MOTOR2);
	motorStop(MOTOR10);
	motorStop(MOTOR9);
	delay(200);
}

void turnLeft(int x) {
	int counts = 0;
	imeReset(0); // rest rightLine I.M.E
	imeGet(0, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR1, 64);
		motorSet(MOTOR2, 64);
		motorSet(MOTOR10, -64);
		motorSet(MOTOR9, -64);

		imeGet(0, &counts); // keep getting the value
	}

	motorSet(MOTOR1, -10); // no inertia
	motorSet(MOTOR2, -10);
	motorSet(MOTOR10, 10);
	motorSet(MOTOR9, 10);
	delay(45);

	motorStop(MOTOR1);
	motorStop(MOTOR2);
	motorStop(MOTOR10);
	motorStop(MOTOR9);
	delay(200);
}

void turnRightSlowDead() {
	motorSet(MOTOR1, -50);
	motorSet(MOTOR2, -50);
	motorSet(MOTOR10, 50);
	motorSet(MOTOR9, 50);
}

void turnLeftSlowDead() {
	motorSet(MOTOR1, 40);
	motorSet(MOTOR2, 40);
	motorSet(MOTOR10, -40);
	motorSet(MOTOR9, -40);
}

void turnLeftArc(int x) {
	int counts = 0;
	imeReset(0); // rest rightLine I.M.E
	imeGet(0, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR1, 127);
		motorSet(MOTOR2, 127);
		motorSet(MOTOR10, 0);
		motorSet(MOTOR9, 0);

		imeGet(0, &counts); // keep getting the value
	}
	motorStop(MOTOR1);
	motorStop(MOTOR2);
	motorStop(MOTOR10);
	motorStop(MOTOR9);
	delay(200);
}

void turnRightArc(int x) {
	int counts = 1;
	imeReset(1); // rest rightLine I.M.E
	imeGet(1, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR1, 0);
		motorSet(MOTOR2, 0);
		motorSet(MOTOR10, 127);
		motorSet(MOTOR9, 127);

		imeGet(0, &counts); // keep getting the value
	}
	motorStop(MOTOR1);
	motorStop(MOTOR2);
	motorStop(MOTOR10);
	motorStop(MOTOR9);

}

void stopDrive() {
	motorStop(MOTOR1);
	motorStop(MOTOR2);
	motorStop(MOTOR10);
	motorStop(MOTOR9);
	delay(200);
}

void stopAll() {
	motorStop(MOTOR1);
	motorStop(MOTOR2);
	motorStop(MOTOR3);
	motorStop(MOTOR4);
	motorStop(MOTOR5);
	motorStop(MOTOR6);
	motorStop(MOTOR7);
	motorStop(MOTOR8);
	motorStop(MOTOR9);
	motorStop(MOTOR10);
}

void stopIntake() {
	motorStop(MOTOR5);
	motorStop(MOTOR6);
}

void driveForwardDead() {
	motorSet(MOTOR1, 127);
	motorSet(MOTOR2, 127);
	motorSet(MOTOR10, 127);
	motorSet(MOTOR9, 127);
}

void driveBackDead() {
	motorSet(MOTOR1, -127);
	motorSet(MOTOR2, -127);
	motorSet(MOTOR10, -127);
	motorSet(MOTOR9, -127);
}

void driveForwardSlow(int x) {
	int counts = 0;
	imeReset(0); // rest rightLine I.M.E
	imeGet(0, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR1, 40);
		motorSet(MOTOR2, 40);
		motorSet(MOTOR10, 40);
		motorSet(MOTOR9, 40);

		imeGet(0, &counts); // keep getting the value
	}

	motorSet(MOTOR1, -10); // no inertia
	motorSet(MOTOR2, -10);
	motorSet(MOTOR10, -10);
	motorSet(MOTOR9, -10);
	delay(45);

	motorSet(MOTOR1, 0);
	motorSet(MOTOR2, 0);
	motorSet(MOTOR10, 0);
	motorSet(MOTOR9, 0);
	delay(200);
}

void driveBackSlow(int x) {
	int counts = 0;
	imeReset(0); // rest rightLine I.M.E
	imeGet(0, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR1, -40);
		motorSet(MOTOR2, -40);
		motorSet(MOTOR10, -40);
		motorSet(MOTOR9, -40);

		imeGet(0, &counts); // keep getting the value
	}

	motorSet(MOTOR1, 10); // no inertia
	motorSet(MOTOR2, 10);
	motorSet(MOTOR10, 10);
	motorSet(MOTOR9, 10);
	delay(45);

	motorSet(MOTOR1, 0);
	motorSet(MOTOR2, 0);
	motorSet(MOTOR10, 0);
	motorSet(MOTOR9, 0);

	delay(200);
}

void driveForwardSlowDead() {

	motorSet(MOTOR1, 50);
	motorSet(MOTOR2, 50);
	motorSet(MOTOR10, 50);
	motorSet(MOTOR9, 50);

}

void driveBackSlowDead() {

	motorSet(MOTOR1, -40);
	motorSet(MOTOR2, -40);
	motorSet(MOTOR10, -40);
	motorSet(MOTOR9, -40);

}

void scrapeRight(int x) {
	int counts = 0;
	imeReset(1); // rest left I.M.E
	imeGet(1, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR1, 0);
		motorSet(MOTOR2, 0);
		motorSet(MOTOR10, 90);
		motorSet(MOTOR9, 90);

		imeGet(1, &counts); // keep getting the value
	}

	motorSet(MOTOR1, 0);
	motorSet(MOTOR2, 0);
	motorSet(MOTOR10, -10);
	motorSet(MOTOR9, -10);
	delay(55);

	motorSet(MOTOR1, 0);
	motorSet(MOTOR2, 0);
	motorSet(MOTOR10, 0);
	motorSet(MOTOR9, 0);
	delay(200);
}

void scrapeLeft(int x) {
	int counts = 0;
	imeReset(0); // rest rightLine I.M.E
	imeGet(0, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR1, 90);
		motorSet(MOTOR2, 90);
		motorSet(MOTOR10, 0);
		motorSet(MOTOR9, 0);

		imeGet(0, &counts); // keep getting the value
	}

	motorSet(MOTOR1, -10); // no intertia
	motorSet(MOTOR2, -10);
	motorSet(MOTOR10, 0);
	motorSet(MOTOR9, 0);
	delay(55);

	motorSet(MOTOR1, 0);
	motorSet(MOTOR2, 0);
	motorSet(MOTOR10, 0);
	motorSet(MOTOR9, 0);
	delay(200);
}

void scrapeLeftBack(int x) {
	int counts = 0;
	imeReset(0); // rest left I.M.E
	imeGet(0, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR1, -90);
		motorSet(MOTOR2, -90);
		motorSet(MOTOR10, 0);
		motorSet(MOTOR9, 0);

		imeGet(0, &counts); // keep getting the value
	}

	motorSet(MOTOR1, 10); // no intertia
	motorSet(MOTOR2, 10);
	motorSet(MOTOR10, 0);
	motorSet(MOTOR9, 0);
	delay(55);

	motorSet(MOTOR1, 0);
	motorSet(MOTOR2, 0);
	motorSet(MOTOR10, 0);
	motorSet(MOTOR9, 0);
	delay(200);

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

void scrapeRightBack(int x) {
	int counts = 0;
	imeReset(1); // rest rightLine I.M.E
	imeGet(1, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR1, 0);
		motorSet(MOTOR2, 0);
		motorSet(MOTOR10, -90);
		motorSet(MOTOR9, -90);

		imeGet(1, &counts); // keep getting the value
	}

	motorSet(MOTOR1, 0); // no intertia
	motorSet(MOTOR2, 0);
	motorSet(MOTOR10, 10);
	motorSet(MOTOR9, 10);
	delay(55);

	motorSet(MOTOR1, 0);
	motorSet(MOTOR2, 0);
	motorSet(MOTOR10, 0);
	motorSet(MOTOR9, 0);
	delay(200);

}

void forwardDetect() {
	int white = 1300;
	int leftLine = analogRead(1);
	int midLine = analogRead(2);
	int rightLine = analogRead(3);

	while (midLine > white) // drive till hit white line
	{
		motorSet(MOTOR1, 60);
		motorSet(MOTOR2, 60);
		motorSet(MOTOR10, 60);
		motorSet(MOTOR9, 60);

		midLine = analogRead(2);
	}

	motorSet(MOTOR1, -10); // no intertia
	motorSet(MOTOR2, -10);
	motorSet(MOTOR10, -10);
	motorSet(MOTOR9, -10);
	delay(55);

	motorSet(MOTOR1, 0);
	motorSet(MOTOR2, 0);
	motorSet(MOTOR10, 0);
	motorSet(MOTOR9, 0);
	delay(200);
}

void backDetect() {
	int white = 2000;
	int leftLine = analogRead(1);
	int midLine = analogRead(2);
	int rightLine = analogRead(3);

	while (midLine > white) // drive till hit white line
	{
		motorSet(MOTOR1, -60);
		motorSet(MOTOR2, -60);
		motorSet(MOTOR10, -60);
		motorSet(MOTOR9, -60);

		midLine = analogRead(2);
	}

	motorSet(MOTOR1, 10); // no intertia
	motorSet(MOTOR2, 10);
	motorSet(MOTOR10, 10);
	motorSet(MOTOR9, 10);
	delay(55);

	motorSet(MOTOR1, 0);
	motorSet(MOTOR2, 0);
	motorSet(MOTOR10, 0);
	motorSet(MOTOR9, 0);
	delay(200);

}

void armUp(int x) {
	int pot = analogRead(8);

	while (pot < x) {
		motorSet(MOTOR3, -127); // arm up
		motorSet(MOTOR4, 127);
		motorSet(MOTOR7, -127);
		motorSet(MOTOR8, 127);
		pot = analogRead(8);
	}

	armUpTrim();
	delay(300);
}

void armDown(int x) {
	int pot = analogRead(8);

	while (pot > x) {
		motorSet(MOTOR3, 127); // arm down
		motorSet(MOTOR4, -127);
		motorSet(MOTOR7, 127);
		motorSet(MOTOR8, -127);
		pot = analogRead(8);
	}

	armDownTrim();
}

void armUpDead() {

	motorSet(MOTOR3, -127); // arm up
	motorSet(MOTOR4, 127);
	motorSet(MOTOR7, -127);
	motorSet(MOTOR8, 127);
}

void armDownDead() {

	motorSet(MOTOR3, 127); // arm Down
	motorSet(MOTOR4, -127);
	motorSet(MOTOR7, 127);
	motorSet(MOTOR8, -127);
}

void armUpTrim() {
	motorSet(MOTOR3, -10); // arm up
	motorSet(MOTOR4, 10);
	motorSet(MOTOR7, -10);
	motorSet(MOTOR8, 10);
}

void armDownTrim()

{
	motorSet(MOTOR3, 20); // arm up
	motorSet(MOTOR4, -20);
	motorSet(MOTOR7, 20);
	motorSet(MOTOR8, -20);
}

void stopArm() // trim
{
	motorSet(MOTOR3, -10); // arm up
	motorSet(MOTOR4, 10);
	motorSet(MOTOR7, -10);
	motorSet(MOTOR8, 10);
}

void intake(int x) {

	motorSet(MOTOR5, 127); // arm rightLine
	motorSet(MOTOR6, -127); // arm leftLine

	delay(x);

	motorSet(MOTOR5, 0); // stop
	motorSet(MOTOR6, 0); //

}

void outtake(int x) {

	motorSet(MOTOR5, -127); // arm rightLine
	motorSet(MOTOR6, 127); // arm leftLine

	delay(x);

	motorSet(MOTOR5, 0); // stop
	motorSet(MOTOR6, 0); //

}

void intakeDead() {

	motorSet(MOTOR5, 127); // arm right
	motorSet(MOTOR6, -127); // arm left

}

void outtakeDead() {

	motorSet(MOTOR5, -127); // arm right
	motorSet(MOTOR6, +127); // arm left

}

void findLineRight() {
	int leftLine = analogRead(1);
	int midLine = analogRead(2);
	int rightLine = analogRead(3);
	int black = 2000;

	while (midLine > black) // black
	{
		printf("%d\r\n", midLine);

		motorSet(MOTOR1, 25); // drive slow until hit
		motorSet(MOTOR2, 25);
		motorSet(MOTOR9, 25);
		motorSet(MOTOR10, 25);
		midLine = analogRead(2);
	}
	stopDrive();

	driveForwardSlow(150); // make sure it will be centered
	stopDrive();
	//delay(160);

	midLine = analogRead(2);
	leftLine = analogRead(1);

	while (leftLine > black) // left is black
	{
		motorSet(MOTOR1, 35); // turn left until mid line is set
		motorSet(MOTOR2, 35);
		motorSet(MOTOR9, -35);
		motorSet(MOTOR10, -35);
		leftLine = analogRead(1);
		midLine = analogRead(2);
	}
	motorSet(MOTOR1, -15); // no inertia
	motorSet(MOTOR2, -15);
	motorSet(MOTOR9, 15);
	motorSet(MOTOR10, 15);
	delay(60);
	stopDrive();

	delay(200);

}

void findLineLeft() {
	int leftLine = analogRead(1);
	int midLine = analogRead(2);
	int rightLine = analogRead(3);
	int black = 2000;

	while (midLine > black) // black
	{
		printf("%d\r\n", midLine);

		motorSet(MOTOR1, 25); // drive slow until hit
		motorSet(MOTOR2, 25);
		motorSet(MOTOR9, 25);
		motorSet(MOTOR10, 25);
		midLine = analogRead(2);
	}
	motorSet(MOTOR1, -15); // no inertia
	motorSet(MOTOR2, -15);
	motorSet(MOTOR9, -15);
	motorSet(MOTOR10, -15);
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
		motorSet(MOTOR1, INERTIA_CANCELLATION_FACTOR); // turn left until mid line is set
		motorSet(MOTOR2, INERTIA_CANCELLATION_FACTOR);
		motorSet(MOTOR9, 55);
		motorSet(MOTOR10, 55);
		leftLine = analogRead(1);
		midLine = analogRead(2);
		rightLine = analogRead(3);

	}

	motorSet(MOTOR1, -15); // no inertia
	motorSet(MOTOR2, -15);
	motorSet(MOTOR9, -15);
	motorSet(MOTOR10, -15);
	delay(50);
	stopDrive();

	stopDrive();
	delay(200);
}

void followLine(int dylanSexxydistance) {

	int lightDegree = 2000;
	int aliSexxySpeed = 40;
	int aliSpeed2 = 35;

	int leftLine = analogRead(1);
	int midLine = analogRead(2);
	int rightLine = analogRead(3);

	int counts = 0;
	imeReset(0); // reset right I.M.E
	imeGet(0, &counts);
	printf("%d\r\n", leftLine);
	printf("%d\r\n", rightLine);
	printf("%d\r\n", midLine);

	while (abs(counts) < dylanSexxydistance) {
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

		if (leftLine < 2000 || rightLine < 2000 || midLine < 2000) //(midLine>100) // Mid is black
				{
			printf("%f \t",
					aliSexxySpeed * ((((rightLine) / (leftLine)) + 5) / 10)); //right
			printf("%f \n",
					aliSexxySpeed * ((((leftLine) / (rightLine)) + 5) / 10)); //left
			motorSet(MOTOR1,
					aliSexxySpeed * ((((rightLine) / (leftLine)) + 5) / 10));
			motorSet(MOTOR2,
					aliSexxySpeed * ((((rightLine) / (leftLine)) + 5) / 10));
			motorSet(MOTOR9,
					aliSexxySpeed * ((((leftLine) / (rightLine)) + 5) / 10));
			motorSet(MOTOR10,
					aliSexxySpeed * ((((leftLine) / (rightLine)) + 5) / 10));
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

	stopDrive();
	delay(200);

}


