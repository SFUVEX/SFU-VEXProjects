/*
 * interpolate.c
 *
 *  Created on: Oct 17, 2014
 *      Author: awiebe
 */

#include <math.h>
#ifndef M_PI
#define M_PI 3.14159624
#endif
/**
 *
 */
double cosineInterpolate(
   double y1,double y2,
   double x)
{
   double mu2;

   mu2 = (1-cos(x*M_PI))/2;
   return(y1*(1-mu2)+y2*mu2);
}

/**
 * Do a straight linear interpolation between y1 and y2.
 * @param x value from 0.0 to 1.0 where y1=L(0.0) and y2=L(1.0)
 */
double linearInterpolate(
   double y1,double y2,
   double x)
{
   return(y1*(1-x)+y2*x);
}

typedef struct
{
	double a0;
	double a1;
	double a2;
	double a3;
}CubicSpline;

/**
 * Generate a cubic spline through the given points
 */
CubicSpline cubicInterpolate(
   double y0,double y1,
   double y2,double y3
   )
{
	CubicSpline s;



   s.a0 = y3 - y2 - y0 + y1;
   s.a1 = y0 - y1 - s.a0;
   s.a2 = y2 - y0;
   s.a3 = y1;

   return s;
}

/**
 * Evaluate an existing cubic spline at a given point
 */
double evalCubicSpline(CubicSpline s,double x)
{
	double x2 = x*x;
	return(s.a0*x*x2+s.a1*x2+s.a2*x+s.a3);
}
