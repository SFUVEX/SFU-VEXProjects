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
