/*
 * autoSubroutines.c
 *
 *  Created on: Oct 17, 2014
 *      Author: awiebe
 */

#include "main.h"
#include "motorSubroutines.h"
#include <stdbool.h>

void driveForward(int x) {
	int imeAccumulator = 0;
	imeReset(0); // rest rightLine I.M.E

	//Read decoder into counts
	imeGet(0, &imeAccumulator);

	//Move forward at max speed until desired x
	while (abs(imeAccumulator) < x) {
		motorSet(MOTOR_DRIVE_RIGHT_BACK, FORWARD_VELOCITY);
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, FORWARD_VELOCITY);
		motorSet(MOTOR_ARM_LEFT_BACK, FORWARD_VELOCITY);
		motorSet(MOTOR_ARM_LEFT_FRONT, FORWARD_VELOCITY);

		imeGet(0, &imeAccumulator); // keep getting the value
	}

	//Cancel forward inertia
	motorSet(MOTOR_DRIVE_RIGHT_BACK, -INERTIA_CANCELLATION_FACTOR); // no inertia
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, -INERTIA_CANCELLATION_FACTOR);
	motorSet(MOTOR_ARM_LEFT_BACK, -INERTIA_CANCELLATION_FACTOR);
	motorSet(MOTOR_ARM_LEFT_FRONT, -INERTIA_CANCELLATION_FACTOR);
	delay(65);

	motorSet(MOTOR_DRIVE_RIGHT_BACK, 0);
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, 0);
	motorSet(MOTOR_ARM_LEFT_BACK, 0);
	motorSet(MOTOR_ARM_LEFT_FRONT, 0);
	delay(200);

}

void driveBack(int x) {
	int counts = 0;
	imeReset(0); // rest rightLine I.M.E
	imeGet(0, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR_DRIVE_RIGHT_BACK, REVERSE_VELOCITY);
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, REVERSE_VELOCITY);
		motorSet(MOTOR_ARM_LEFT_BACK, REVERSE_VELOCITY);
		motorSet(MOTOR_ARM_LEFT_FRONT, REVERSE_VELOCITY);

		imeGet(0, &counts); // keep getting the value
	}

	motorSet(MOTOR_DRIVE_RIGHT_BACK, INERTIA_CANCELLATION_FACTOR); // no inertia
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, INERTIA_CANCELLATION_FACTOR);
	motorSet(MOTOR_ARM_LEFT_BACK, INERTIA_CANCELLATION_FACTOR);
	motorSet(MOTOR_ARM_LEFT_FRONT, INERTIA_CANCELLATION_FACTOR);
	delay(65);

	motorStop(MOTOR_DRIVE_RIGHT_BACK);
	motorStop(MOTOR_DRIVE_RIGHT_FRONT);
	motorStop(MOTOR_ARM_LEFT_BACK);
	motorStop(MOTOR_ARM_LEFT_FRONT);
	delay(200);
}

void turnRight(int x) {
	int counts = 0;
	imeReset(0); // rest rightLine I.M.E
	imeGet(0, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR_DRIVE_RIGHT_BACK, -64);
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, -64);
		motorSet(MOTOR_ARM_LEFT_BACK, 64);
		motorSet(MOTOR_ARM_LEFT_FRONT, 64);

		imeGet(0, &counts); // keep getting the value
	}

	motorSet(MOTOR_DRIVE_RIGHT_BACK, 10); // no inertia
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, 10);
	motorSet(MOTOR_ARM_LEFT_BACK, -10);
	motorSet(MOTOR_ARM_LEFT_FRONT, -10);
	delay(45);

	motorStop(MOTOR_DRIVE_RIGHT_BACK);
	motorStop(MOTOR_DRIVE_RIGHT_FRONT);
	motorStop(MOTOR_ARM_LEFT_BACK);
	motorStop(MOTOR_ARM_LEFT_FRONT);
	delay(200);
}

void turnLeft(int x) {
	int counts = 0;
	imeReset(0); // rest rightLine I.M.E
	imeGet(0, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR_DRIVE_RIGHT_BACK, 64);
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, 64);
		motorSet(MOTOR_ARM_LEFT_BACK, -64);
		motorSet(MOTOR_ARM_LEFT_FRONT, -64);

		imeGet(0, &counts); // keep getting the value
	}

	motorSet(MOTOR_DRIVE_RIGHT_BACK, -10); // no inertia
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, -10);
	motorSet(MOTOR_ARM_LEFT_BACK, 10);
	motorSet(MOTOR_ARM_LEFT_FRONT, 10);
	delay(45);

	motorStop(MOTOR_DRIVE_RIGHT_BACK);
	motorStop(MOTOR_DRIVE_RIGHT_FRONT);
	motorStop(MOTOR_ARM_LEFT_BACK);
	motorStop(MOTOR_ARM_LEFT_FRONT);
	delay(200);
}

void turnRightSlowDead() {
	motorSet(MOTOR_DRIVE_RIGHT_BACK, -50);
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, -50);
	motorSet(MOTOR_ARM_LEFT_BACK, 50);
	motorSet(MOTOR_ARM_LEFT_FRONT, 50);
}

void turnLeftSlowDead() {
	motorSet(MOTOR_DRIVE_RIGHT_BACK, 40);
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, 40);
	motorSet(MOTOR_ARM_LEFT_BACK, -40);
	motorSet(MOTOR_ARM_LEFT_FRONT, -40);
}

void turnLeftArc(int x) {
	int counts = 0;
	imeReset(0); // rest rightLine I.M.E
	imeGet(0, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR_DRIVE_RIGHT_BACK, 127);
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, 127);
		motorSet(MOTOR_ARM_LEFT_BACK, 0);
		motorSet(MOTOR_ARM_LEFT_FRONT, 0);

		imeGet(0, &counts); // keep getting the value
	}
	motorStop(MOTOR_DRIVE_RIGHT_BACK);
	motorStop(MOTOR_DRIVE_RIGHT_FRONT);
	motorStop(MOTOR_ARM_LEFT_BACK);
	motorStop(MOTOR_ARM_LEFT_FRONT);
	delay(200);
}

void turnRightArc(int x) {
	int counts = 1;
	imeReset(1); // rest rightLine I.M.E
	imeGet(1, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR_DRIVE_RIGHT_BACK, 0);
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, 0);
		motorSet(MOTOR_ARM_LEFT_BACK, 127);
		motorSet(MOTOR_ARM_LEFT_FRONT, 127);

		imeGet(0, &counts); // keep getting the value
	}
	motorStop(MOTOR_DRIVE_RIGHT_BACK);
	motorStop(MOTOR_DRIVE_RIGHT_FRONT);
	motorStop(MOTOR_ARM_LEFT_BACK);
	motorStop(MOTOR_ARM_LEFT_FRONT);

}

void stopDrive() {
	motorStop(MOTOR_DRIVE_RIGHT_BACK);
	motorStop(MOTOR_DRIVE_RIGHT_FRONT);
	motorStop(MOTOR_ARM_LEFT_BACK);
	motorStop(MOTOR_ARM_LEFT_FRONT);
	delay(200);
}

void stopAll() {
	motorStop(MOTOR_DRIVE_RIGHT_BACK);
	motorStop(MOTOR_DRIVE_RIGHT_FRONT);
	motorStop(MOTOR_ARM_RIGHT_BOTTOM);
	motorStop(MOTOR_ARM_RIGHT_TOP);
	motorStop(MOTOR_ARM_RIGHT_MID);
	motorStop(MOTOR_ARM_LEFT_MID);
	motorStop(MOTOR_ARM_LEFT_TOP);
	motorStop(MOTOR_ARM_LEFT_BOTTOM);
	motorStop(MOTOR_ARM_LEFT_FRONT);
	motorStop(MOTOR_ARM_LEFT_BACK);
}

void stopIntake() {
	motorStop(MOTOR_ARM_RIGHT_MID);
	motorStop(MOTOR_ARM_LEFT_MID);
}

void driveForwardDead() {
	motorSet(MOTOR_DRIVE_RIGHT_BACK, 127);
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, 127);
	motorSet(MOTOR_ARM_LEFT_BACK, 127);
	motorSet(MOTOR_ARM_LEFT_FRONT, 127);
}

void driveBackDead() {
	motorSet(MOTOR_DRIVE_RIGHT_BACK, -127);
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, -127);
	motorSet(MOTOR_ARM_LEFT_BACK, -127);
	motorSet(MOTOR_ARM_LEFT_FRONT, -127);
}

void driveForwardSlow(int x) {
	int counts = 0;
	imeReset(0); // rest rightLine I.M.E
	imeGet(0, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR_DRIVE_RIGHT_BACK, 40);
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, 40);
		motorSet(MOTOR_ARM_LEFT_BACK, 40);
		motorSet(MOTOR_ARM_LEFT_FRONT, 40);

		imeGet(0, &counts); // keep getting the value
	}

	motorSet(MOTOR_DRIVE_RIGHT_BACK, -10); // no inertia
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, -10);
	motorSet(MOTOR_ARM_LEFT_BACK, -10);
	motorSet(MOTOR_ARM_LEFT_FRONT, -10);
	delay(45);

	motorSet(MOTOR_DRIVE_RIGHT_BACK, 0);
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, 0);
	motorSet(MOTOR_ARM_LEFT_BACK, 0);
	motorSet(MOTOR_ARM_LEFT_FRONT, 0);
	delay(200);
}

void driveBackSlow(int x) {
	int counts = 0;
	imeReset(0); // rest rightLine I.M.E
	imeGet(0, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR_DRIVE_RIGHT_BACK, -40);
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, -40);
		motorSet(MOTOR_ARM_LEFT_BACK, -40);
		motorSet(MOTOR_ARM_LEFT_FRONT, -40);

		imeGet(0, &counts); // keep getting the value
	}

	motorSet(MOTOR_DRIVE_RIGHT_BACK, 10); // no inertia
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, 10);
	motorSet(MOTOR_ARM_LEFT_BACK, 10);
	motorSet(MOTOR_ARM_LEFT_FRONT, 10);
	delay(45);

	motorSet(MOTOR_DRIVE_RIGHT_BACK, 0);
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, 0);
	motorSet(MOTOR_ARM_LEFT_BACK, 0);
	motorSet(MOTOR_ARM_LEFT_FRONT, 0);

	delay(200);
}

void driveForwardSlowDead() {

	motorSet(MOTOR_DRIVE_RIGHT_BACK, 50);
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, 50);
	motorSet(MOTOR_ARM_LEFT_BACK, 50);
	motorSet(MOTOR_ARM_LEFT_FRONT, 50);

}

void driveBackSlowDead() {

	motorSet(MOTOR_DRIVE_RIGHT_BACK, -40);
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, -40);
	motorSet(MOTOR_ARM_LEFT_BACK, -40);
	motorSet(MOTOR_ARM_LEFT_FRONT, -40);

}

void scrapeRight(int x) {
	int counts = 0;
	imeReset(1); // rest left I.M.E
	imeGet(1, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR_DRIVE_RIGHT_BACK, 0);
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, 0);
		motorSet(MOTOR_ARM_LEFT_BACK, 90);
		motorSet(MOTOR_ARM_LEFT_FRONT, 90);

		imeGet(1, &counts); // keep getting the value
	}

	motorSet(MOTOR_DRIVE_RIGHT_BACK, 0);
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, 0);
	motorSet(MOTOR_ARM_LEFT_BACK, -10);
	motorSet(MOTOR_ARM_LEFT_FRONT, -10);
	delay(55);

	motorSet(MOTOR_DRIVE_RIGHT_BACK, 0);
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, 0);
	motorSet(MOTOR_ARM_LEFT_BACK, 0);
	motorSet(MOTOR_ARM_LEFT_FRONT, 0);
	delay(200);
}

void scrapeLeft(int x) {
	int counts = 0;
	imeReset(0); // rest rightLine I.M.E
	imeGet(0, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR_DRIVE_RIGHT_BACK, 90);
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, 90);
		motorSet(MOTOR_ARM_LEFT_BACK, 0);
		motorSet(MOTOR_ARM_LEFT_FRONT, 0);

		imeGet(0, &counts); // keep getting the value
	}

	motorSet(MOTOR_DRIVE_RIGHT_BACK, -10); // no intertia
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, -10);
	motorSet(MOTOR_ARM_LEFT_BACK, 0);
	motorSet(MOTOR_ARM_LEFT_FRONT, 0);
	delay(55);

	motorSet(MOTOR_DRIVE_RIGHT_BACK, 0);
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, 0);
	motorSet(MOTOR_ARM_LEFT_BACK, 0);
	motorSet(MOTOR_ARM_LEFT_FRONT, 0);
	delay(200);
}

void scrapeLeftBack(int x) {
	int counts = 0;
	imeReset(0); // rest left I.M.E
	imeGet(0, &counts);

	while (abs(counts) < x) {
		motorSet(MOTOR_DRIVE_RIGHT_BACK, -90);
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, -90);
		motorSet(MOTOR_ARM_LEFT_BACK, 0);
		motorSet(MOTOR_ARM_LEFT_FRONT, 0);

		imeGet(0, &counts); // keep getting the value
	}

	motorSet(MOTOR_DRIVE_RIGHT_BACK, 10); // no intertia
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, 10);
	motorSet(MOTOR_ARM_LEFT_BACK, 0);
	motorSet(MOTOR_ARM_LEFT_FRONT, 0);
	delay(55);

	motorSet(MOTOR_DRIVE_RIGHT_BACK, 0);
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, 0);
	motorSet(MOTOR_ARM_LEFT_BACK, 0);
	motorSet(MOTOR_ARM_LEFT_FRONT, 0);
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
		motorSet(MOTOR_DRIVE_RIGHT_BACK, 0);
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, 0);
		motorSet(MOTOR_ARM_LEFT_BACK, -90);
		motorSet(MOTOR_ARM_LEFT_FRONT, -90);

		imeGet(1, &counts); // keep getting the value
	}

	motorSet(MOTOR_DRIVE_RIGHT_BACK, 0); // no intertia
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, 0);
	motorSet(MOTOR_ARM_LEFT_BACK, 10);
	motorSet(MOTOR_ARM_LEFT_FRONT, 10);
	delay(55);

	motorSet(MOTOR_DRIVE_RIGHT_BACK, 0);
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, 0);
	motorSet(MOTOR_ARM_LEFT_BACK, 0);
	motorSet(MOTOR_ARM_LEFT_FRONT, 0);
	delay(200);

}

void forwardDetect() {
	int white = 1300;
	int leftLine = analogRead(1);
	int midLine = analogRead(2);
	int rightLine = analogRead(3);

	while (midLine > white) // drive till hit white line
	{
		motorSet(MOTOR_DRIVE_RIGHT_BACK, 60);
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, 60);
		motorSet(MOTOR_ARM_LEFT_BACK, 60);
		motorSet(MOTOR_ARM_LEFT_FRONT, 60);

		midLine = analogRead(2);
	}

	motorSet(MOTOR_DRIVE_RIGHT_BACK, -10); // no intertia
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, -10);
	motorSet(MOTOR_ARM_LEFT_BACK, -10);
	motorSet(MOTOR_ARM_LEFT_FRONT, -10);
	delay(55);

	motorSet(MOTOR_DRIVE_RIGHT_BACK, 0);
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, 0);
	motorSet(MOTOR_ARM_LEFT_BACK, 0);
	motorSet(MOTOR_ARM_LEFT_FRONT, 0);
	delay(200);
}

void backDetect() {
	int white = 2000;
	int leftLine = analogRead(1);
	int midLine = analogRead(2);
	int rightLine = analogRead(3);

	while (midLine > white) // drive till hit white line
	{
		motorSet(MOTOR_DRIVE_RIGHT_BACK, -60);
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, -60);
		motorSet(MOTOR_ARM_LEFT_BACK, -60);
		motorSet(MOTOR_ARM_LEFT_FRONT, -60);

		midLine = analogRead(2);
	}

	motorSet(MOTOR_DRIVE_RIGHT_BACK, 10); // no intertia
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, 10);
	motorSet(MOTOR_ARM_LEFT_BACK, 10);
	motorSet(MOTOR_ARM_LEFT_FRONT, 10);
	delay(55);

	motorSet(MOTOR_DRIVE_RIGHT_BACK, 0);
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, 0);
	motorSet(MOTOR_ARM_LEFT_BACK, 0);
	motorSet(MOTOR_ARM_LEFT_FRONT, 0);
	delay(200);

}

void armUp(int x) {
	int pot = encoderGet(encoder2);

	while (pot < x) {
		motorSet(MOTOR_ARM_RIGHT_TOP, -127);
		motorSet(MOTOR_ARM_LEFT_TOP, 127);
		motorSet(MOTOR_ARM_RIGHT_BOTTOM, -127);
		motorSet(MOTOR_ARM_LEFT_BOTTOM, 127);
		motorSet(MOTOR_ARM_RIGHT_MID, -127);
		motorSet(MOTOR_ARM_LEFT_MID, 127);
		pot = encoderGet(encoder2);
	}
	stopArm();
	//armUpTrim();
	delay(300);
}

void armDown(int x) {
	int pot = encoderGet(encoder2);

	while (pot > x) {
		motorSet(MOTOR_ARM_RIGHT_TOP, 127);
		motorSet(MOTOR_ARM_LEFT_TOP, -127);
		motorSet(MOTOR_ARM_RIGHT_BOTTOM, 127);
		motorSet(MOTOR_ARM_LEFT_BOTTOM, -127);
		motorSet(MOTOR_ARM_RIGHT_MID, 127);
		motorSet(MOTOR_ARM_LEFT_MID, -127);
		pot = encoderGet(encoder2);
	}

	stopArm();

	//armDownTrim();
	delay(300);
}

void armUpDead() {

	motorSet(MOTOR_ARM_RIGHT_TOP, -127);
			motorSet(MOTOR_ARM_LEFT_TOP, 127);
			motorSet(MOTOR_ARM_RIGHT_BOTTOM, -127);
			motorSet(MOTOR_ARM_LEFT_BOTTOM, 127);
			motorSet(MOTOR_ARM_RIGHT_MID, -127);
			motorSet(MOTOR_ARM_LEFT_MID, 127);
}

void armDownDead() {

	motorSet(MOTOR_ARM_RIGHT_TOP, 127);
			motorSet(MOTOR_ARM_LEFT_TOP, -127);
			motorSet(MOTOR_ARM_RIGHT_BOTTOM, 127);
			motorSet(MOTOR_ARM_LEFT_BOTTOM, -127);
			motorSet(MOTOR_ARM_RIGHT_MID, 127);
			motorSet(MOTOR_ARM_LEFT_MID, -127);
}

void armUpTrim() {
	motorSet(MOTOR_ARM_RIGHT_BOTTOM, -10); // arm up
	motorSet(MOTOR_ARM_RIGHT_TOP, 10);
	motorSet(MOTOR_ARM_LEFT_TOP, -10);
	motorSet(MOTOR_ARM_LEFT_BOTTOM, 10);
}

void armDownTrim()

{
	motorSet(MOTOR_ARM_RIGHT_BOTTOM, 20); // arm up
	motorSet(MOTOR_ARM_RIGHT_TOP, -20);
	motorSet(MOTOR_ARM_LEFT_TOP, 20);
	motorSet(MOTOR_ARM_LEFT_BOTTOM, -20);
}

void stopArm() // trim
{
	motorSet(MOTOR_ARM_RIGHT_BOTTOM, -10); // arm up
	motorSet(MOTOR_ARM_RIGHT_TOP, 10);
	motorSet(MOTOR_ARM_LEFT_TOP, -10);
	motorSet(MOTOR_ARM_LEFT_BOTTOM, 10);
}

void intake(int x) {

	motorSet(MOTOR_ARM_RIGHT_MID, 127); // arm rightLine
	motorSet(MOTOR_ARM_LEFT_MID, -127); // arm leftLine

	delay(x);

	motorSet(MOTOR_ARM_RIGHT_MID, 0); // stop
	motorSet(MOTOR_ARM_LEFT_MID, 0); //

}

void outtake(int x) {

	motorSet(MOTOR_ARM_RIGHT_MID, -127); // arm rightLine
	motorSet(MOTOR_ARM_LEFT_MID, 127); // arm leftLine

	delay(x);

	motorSet(MOTOR_ARM_RIGHT_MID, 0); // stop
	motorSet(MOTOR_ARM_LEFT_MID, 0); //

}

void intakeDead() {

	motorSet(MOTOR_ARM_RIGHT_MID, 127); // arm right
	motorSet(MOTOR_ARM_LEFT_MID, -127); // arm left

}

void outtakeDead() {

	motorSet(MOTOR_ARM_RIGHT_MID, -127); // arm right
	motorSet(MOTOR_ARM_LEFT_MID, +127); // arm left

}

void findLineRight() {
	int leftLine = analogRead(1);
	int midLine = analogRead(2);
	int rightLine = analogRead(3);
	int black = 2000;

	while (midLine > black) // black
	{
		printf("%d\r\n", midLine);

		motorSet(MOTOR_DRIVE_RIGHT_BACK, 25); // drive slow until hit
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, 25);
		motorSet(MOTOR_ARM_LEFT_FRONT, 25);
		motorSet(MOTOR_ARM_LEFT_BACK, 25);
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
		motorSet(MOTOR_DRIVE_RIGHT_BACK, 35); // turn left until mid line is set
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, 35);
		motorSet(MOTOR_ARM_LEFT_FRONT, -35);
		motorSet(MOTOR_ARM_LEFT_BACK, -35);
		leftLine = analogRead(1);
		midLine = analogRead(2);
	}
	motorSet(MOTOR_DRIVE_RIGHT_BACK, -15); // no inertia
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, -15);
	motorSet(MOTOR_ARM_LEFT_FRONT, 15);
	motorSet(MOTOR_ARM_LEFT_BACK, 15);
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

		motorSet(MOTOR_DRIVE_RIGHT_BACK, 25); // drive slow until hit
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, 25);
		motorSet(MOTOR_ARM_LEFT_FRONT, 25);
		motorSet(MOTOR_ARM_LEFT_BACK, 25);
		midLine = analogRead(2);
	}
	motorSet(MOTOR_DRIVE_RIGHT_BACK, -15); // no inertia
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, -15);
	motorSet(MOTOR_ARM_LEFT_FRONT, -15);
	motorSet(MOTOR_ARM_LEFT_BACK, -15);
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
		motorSet(MOTOR_DRIVE_RIGHT_BACK, INERTIA_CANCELLATION_FACTOR); // turn left until mid line is set
		motorSet(MOTOR_DRIVE_RIGHT_FRONT, INERTIA_CANCELLATION_FACTOR);
		motorSet(MOTOR_ARM_LEFT_FRONT, 55);
		motorSet(MOTOR_ARM_LEFT_BACK, 55);
		leftLine = analogRead(1);
		midLine = analogRead(2);
		rightLine = analogRead(3);

	}

	motorSet(MOTOR_DRIVE_RIGHT_BACK, -15); // no inertia
	motorSet(MOTOR_DRIVE_RIGHT_FRONT, -15);
	motorSet(MOTOR_ARM_LEFT_FRONT, -15);
	motorSet(MOTOR_ARM_LEFT_BACK, -15);
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
			motorSet(MOTOR_DRIVE_RIGHT_BACK,
					aliSexxySpeed * ((((rightLine) / (leftLine)) + 5) / 10));
			motorSet(MOTOR_DRIVE_RIGHT_FRONT,
					aliSexxySpeed * ((((rightLine) / (leftLine)) + 5) / 10));
			motorSet(MOTOR_ARM_LEFT_FRONT,
					aliSexxySpeed * ((((leftLine) / (rightLine)) + 5) / 10));
			motorSet(MOTOR_ARM_LEFT_BACK,
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


