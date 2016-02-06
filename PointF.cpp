#ifndef POINTF_CPP
#define POINTF_CPP
#include <iostream>
#include <cmath>
#include "PointF.h"


#define PI 3.14159265
using namespace std;

PointF::PointF():
m_x(0.f),
m_y(0.f)
{
}

PointF::PointF(const float x, const float y):
m_x(x),
m_y(y)
{
}

float PointF::getX() const { return m_x; }
float PointF::getY() const { return m_y; }

/* It should be roundet right, so we add 0.5 if the number is bigger or equals zero
 * or subtract 0.5 if the number is smaller then zero.
 * (cast to int truncat the number)
 */
int PointF::getIntX() const
{
	int x = m_x >= 0 ? static_cast<int>(m_x + 0.5f) : static_cast<int>(m_x - 0.5f);
	return x;
}
int PointF::getIntY() const
{
	int y = m_y >= 0 ? static_cast<int>(m_y + 0.5f) : static_cast<int>(m_y - 0.5f);
	return y;
}

void PointF::setX(const float x) { m_x = x; }
void PointF::setY(const float y) { m_y = y; }

/* We dont really need to calculate the rotation around a specific point
 * with a specific angle, because our Stones only rotate with 90* Degrees
 * around the origin, but it isnt a bad idea to know how to rotate.
 
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

void PointF::rotateAround(const float targetPX, const float targetPY, const float angleDegree)
{
	// First we need the angle in radians instead if degrees
	const float angle = ( PI / 180) * angleDegree;
	const float xp = m_x;
	const float yp = m_y;
	const float xt = targetPX;
	const float yt = targetPY;
	// Rotate the Point
	m_x = ( ( cos(angle) * (xp - xt) + sin(angle) * (yp - yt) ) + xt );
	m_y = ( (-sin(angle) * (xp - xt) + cos(angle) * (yp - yt) ) + yt );
	
	// It should be roundet right, so we add 0.5 if the number is bigger or equals zero
	// or subtract 0.5 if the number is smaller then zero. (cast to int truncat the number)
	//m_x  = x >= 0 ? static_cast<int>(x + 0.5f) : static_cast<int>(x - 0.5f);
	//m_y  = y >= 0 ? static_cast<int>(y + 0.5f) : static_cast<int>(y - 0.5f);
}

void PointF::rotateAround(const PointF target, const float angleDegree)    
{
	rotateAround(target.getX(), target.getY(), angleDegree);
}


void PointF::operator=(const PointF &right)
{
	this->m_x = right.m_x;
	this->m_y = right.m_y;
}

PointF PointF::operator+(const PointF &right)
{
	PointF result;
	result.setX(m_x + right.m_x);
	result.setY(m_y + right.m_y);
	return result;
}

PointF PointF::operator+(const PointF &right) const
{
	PointF result;
	result.setX(m_x + right.m_x);
	result.setY(m_y + right.m_y);
	return result;
}

PointF PointF::operator-(const PointF &right)
{
	PointF result;
	result.setX(m_x - right.m_x);
	result.setY(m_y - right.m_y);
	return result;
}

PointF PointF::operator-(const PointF &right) const
{
	PointF result;
	result.setX(m_x - right.m_x);
	result.setY(m_y - right.m_y);
	return result;
}

PointF& PointF::operator+=(const PointF &right)
{
	this->m_x += right.m_x;
	this->m_y += right.m_y;
	return *this;
}

PointF& PointF::operator-=(const PointF &right)
{
	this->m_x -= right.m_x;
	this->m_y -= right.m_y;
	return *this;
}

bool PointF::operator==(const PointF &right)
{
	return (this->m_x == right.m_x && this->m_y == right.m_y);
}



#endif // !POINTF_CPP
