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
	MOTOR_DRIVE_RIGHT_BACK = 1, // = rightLine back
	MOTOR_DRIVE_RIGHT_FRONT = 2, // = rightLine front
	MOTOR_ARM_RIGHT_BOTTOM = 3, // = rightLine arm down
	MOTOR_ARM_RIGHT_TOP = 4, // = rightLine arm up
	MOTOR_INTAKE_RIGHT = 5, // = rightLine intake
	MOTOR_INTAKE_LEFT = 6, // = leftLine intake
	MOTOR_ARM_LEFT_TOP = 7, // = leftLine arm up
	MOTOR_ARM_LEFT_BOTTOM = 8, // = leftLine arm down
	MOTOR_ARM_LEFT_FRONT = 9, // = leftLine front
	MOTOR_ARM_LEFT_BACK = 10 // = leftLine back
} MOTOR;
