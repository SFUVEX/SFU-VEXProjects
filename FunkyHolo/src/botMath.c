#include <math.h>
typedef struct Vector2
{
float x;
float y;
} Vector2;

double v2Distance(Vector2 a, Vector2 b)
{
	double x = a.x*b.x;
	double y= a.y*b.y;
	return sqrt(x+y);
}


