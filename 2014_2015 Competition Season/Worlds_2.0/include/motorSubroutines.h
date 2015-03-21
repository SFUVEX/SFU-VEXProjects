/*
 * autoSubroutines.h
 *
 *  Created on: Oct 17, 2014
 *      Author: awiebe
 */

#ifndef MOTORSUBROUTINES_H_
#define MOTORSUBROUTINES_H_

#include "botConstants.h"



//movement functions

/**
 * Set drive motors to max speed until encoder value met
 * @param x Encoder count.
 */
void driveForward(int x); // x = encoder value

/**
 * Set drive motors to negative max speed until encoder value met
 * @param x Encoder count.
 */
void driveBack(int x); // x = encoder value

/**
 * Drive foward until told to stop.
 */
void driveForwardDead();

/**
 * Drive backwards until told to stop
 */
void driveBackDead();

/**
 * Drive forward ast half normal speed until the encoder value is met
 */
void driveForwardSlow(int x);
void driveBackSlow(int x);
void driveForwardSlowDead();
void driveBackSlowDead();

//////TURNING/////

void turnRight(int x); // x = encoder value
void turnLeft(int x); // x = encoder value
void turnRightSlowDead();
void turnLeftSlowDead();
void turnLeftArc(int x); // x = encoder
void turnRightArc(int x);

void scrapeRight(int x); // x = encoder
void scrapeLeft(int x);
void scrapeRightBack(int x); // x = timer
void scrapeLeftBack(int x); // x = encoder

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

void forwardDetect();
void backDetect();


void stopAll();
void stopDrive();
void stopIntake();

void stopArm();

#endif /* AUTOSUBROUTINES_H_ */
