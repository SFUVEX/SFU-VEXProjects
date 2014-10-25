/**
 * This file contains constant values for controlling the robot
 */
/* Note: In ANSI-C (not C++), shared constants must be declared
 * static to indicate that they will be resolved
 * at link time.  Otherwise the compiler beleives the constant has
 * been re-declared in every file it is included into
 */
static const int MAX_SPEED = 127;
static const int MAX_REVERSE_SPEED = 127;

static const int MAX_FORWARD_VELOCITY = 127;
static const int MAX_REVERSE_VELOCITY = -127;

static const int FORWARD_VELOCITY = 127;
static const int REVERSE_VELOCITY = -100;

static const int INERTIA_CANCELLATION_FACTOR = 7;

//Motors, duh
//motors
typedef enum MOTORS {
	MOTOR1 = 1, // = rightLine back
	MOTOR2 = 2, // = rightLine front
	MOTOR3 = 3, // = rightLine arm down
	MOTOR4 = 4, // = rightLine arm up
	MOTOR5 = 5, // = rightLine intake
	MOTOR6 = 6, // = leftLine intake
	MOTOR7 = 7, // = leftLine arm up
	MOTOR8 = 8, // = leftLine arm down
	MOTOR9 = 9, // = leftLine front
	MOTOR10 = 10 // = leftLine back
} MOTOR;
