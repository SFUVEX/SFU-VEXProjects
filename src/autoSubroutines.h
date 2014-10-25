/*
 * autoSubroutines.h
 *
 *  Created on: Oct 17, 2014
 *      Author: awiebe
 */

#ifndef AUTOSUBROUTINES_H_
#define AUTOSUBROUTINES_H_

#include "botConstants.h"



//movement functions
void driveForward(int x); // x = encoder value
void driveBack(int x); // x = encoder value

void turnRight(int x); // x = encoder value
void turnLeft(int x); // x = encoder value
void turnRightSlowDead();
void turnLeftSlowDead();
void turnLeftArc(int x); // x = encoder
void turnRightArc(int x);

void driveForwardDead();
void driveBackDead();
void driveForwardSlow(int x);
void driveBackSlow(int x);
void driveForwardSlowDead();
void driveBackSlowDead();

void scrapeRight(int x); // x = encoder
void scrapeLeft(int x);
void scrapeRightBack(int x); // x = timer
void scrapeLeftBack(int x); // x = encoder

void forwardDetect();
void backDetect();

void stopAll();
void stopDrive();
void stopIntake();

void stopArm();
void armUp(int x); // x = pot value
void armDown(int x); // x = pot value
void armUpDead();
void armDownDead();
void armUpTrim();
void armDownTrim();


void intake(int x); //x = time
void outtake(int x);
void intakeDead(); // continuous intaking
void outtakeDead(); // countinuous outtake

void followLine(int dylanSexxydistance);
void findLineRight();
void findLineLeft();



#endif /* AUTOSUBROUTINES_H_ */
