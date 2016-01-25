#ifndef POINT_CPP
#define POINT_CPP
#include <iostream>
#include <cmath>
#include "Point.h"


#define PI 3.14159265
using namespace std;

Point::Point():
m_x(0),
m_y(0)
{
}

Point::Point(const int x, const int y):
m_x(x),
m_y(y)
{
}

int Point::getX() const { return m_x; }
int Point::getY() const { return m_y; }

void Point::setX(const int x) { m_x = x; }
void Point::setY(const int y) { m_y = y; }


/* We dont really need to calculate the rotation around a specific point
 * with a specific angle, because our Stones only rotate with 90* Degrees
 * around the origin, but it isnt a bad idea to know how to rotate.
 * In this case the we cast the new angle to an int,
 * because our terminal coordinate system only can handle integral numbers. 
 *
 * Rotation around origin:
 *           rotation matrix      P
 * ( x' ) = ( cos a  -sin a ) * ( x ) = cos a * x - sin a * y  
 * ( y' )   ( sin a   cos a )   ( y ) = sin a * x + cos a * y
 * Our Coordinate system has other axes (reversed y Axes)
 * So the rotation matrix is different: *
 * ( x' ) = ( cos a   sin a ) * ( x ) = cos a * x + sin a * y
 * ( y' )   (-sin a   cos a )	( y ) =-sin a * x + cos a * y
 *
 * Rotation around specific Point:
 * The Point we want to rotate is called P and the point we 
 * rotate around is called T.    
 *                                       ->          ->
 *           rotation matrix     Vector: TP  Vector: OT 
 * ( x' ) = ( cos a  -sin a ) * ( xp - xt) + ( xt )
 * ( y' )   ( sin a   cos a )   ( yp - yt)   ( yt )
 * ==>
 * x' = (cos a * (xp - xt) - sin a * (yp - yt)) + xt
 * y' = (sin a * (xp - xt) + cos a * (yp - yt)) + yt
 * In our coordinate system with the custom rotation matrix:
 * x' = ( cos a * (xp - xt) + sin a * (yp - yt)) + xt
 * y' = (-sin a * (xp - xt) + cos a * (yp - yt)) + yt
 * 
 */

void Point::rotateAround(const int targetPX, const int targetPY, const float angleDegree)
{
	// First we need the angle in radians instead if degrees
	const float angle = ( PI / 180) * angleDegree;
	const int xp = m_x;
	const int yp = m_y;
	const int xt = targetPX;
	const int yt = targetPY;
	float x = ( ( cos(angle) * (xp - xt) + sin(angle) * (yp - yt) ) + xt );
	float y = ( (-sin(angle) * (xp - xt) + cos(angle) * (yp - yt) ) + yt );
	// Rotate the Point
	// It should be roundet right, so we add 0.5 if the number is bigger or equals zero
	// or subtract 0.5 if the number is smaller then zero. (cast to int truncat the number)
	m_x  = x >= 0 ? static_cast<int>(x + 0.5f) : static_cast<int>(x - 0.5f);
	m_y  = y >= 0 ? static_cast<int>(y + 0.5f) : static_cast<int>(y - 0.5f);
}

void Point::rotateAround(const Point target, const float angleDegree)    
{
	rotateAround(target.getX(), target.getY(), angleDegree);
}
#endif // !POINT_CPP
