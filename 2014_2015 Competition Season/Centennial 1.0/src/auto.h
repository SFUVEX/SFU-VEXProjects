/*
 * auto.h
 *
 *  Created on: Nov 8, 2014
 *      Author: awiebe
 */

#ifndef AUTO_H_
#define AUTO_H_

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


void armUp (int x); // x = pot value
void armDown(int x); // x = pot value
void armUpDead();
void armDownDead ();
void armDownTime (int millis); // x = milisecs
void armDownTime (int millis);
void armUpEnc(int x); // x = encoders
void armDownEnc (int x);
void armUpTrim ();
void armDownTrim ();
void stopArm ();
void intake (int x); //x = time
void outtake (int x);
void stopIntake();
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


void armHelixUp(double spikeNumber);
void armHelixDown();
void grip();
void releaseGrip();

void stackEm();

#endif /* AUTO_H_ */
