/*
 * auto.h
 *
 *  Created on: Oct 17, 2014
 *      Author: awiebe
 */

#ifndef AUTO_H_
#define AUTO_H_
#include "main.h"
#include "autoSubroutines.h"

//Strategies
//Note I think the MSB should be used as the "colour" switch
typedef enum AUTONOMOUS_MODE {
	RUSH_BLUE = 0,
	CLASSIC15_BLUE = 1,
	RUSH_RED = 2,
	CLASSIC15_RED = 3,
	REJECTION_BLUE = 4,
	REJECTION_RED = 5,
	RESERVED6 = 6,
	RESERVED7 = 7
} AUTONOMOUS_MODE;


/*
 #define MOTOR1 1 // = rightLine back
 #define MOTOR2 2 // = rightLine front
 #define MOTOR3 3 // = rightLine arm down
 #define MOTOR4 4 // = rightLine arm up
 #define MOTOR5 5 // = rightLine intake
 #define MOTOR6 6 // = leftLine intake
 #define MOTOR7 7 // = leftLine arm up
 #define MOTOR8 8 // = leftLine arm down
 #define MOTOR9 9 // = leftLine front
 #define MOTOR10 10 // = leftLine back
 */



// autonomous routines
void rushRed();
void rushBlue();
void classic15Red();
void classic15Blue();
void rejectionRed();
void rejectionBlue();
void rejectionBlueSkills();
void kakitRed();
//void kakitBlue ();
void ram();

#endif /* AUTO_H_ */
