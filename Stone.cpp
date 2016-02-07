#ifndef STONE_CPP
#define STONE_CPP
#include <iostream>
#include "Stone.h"

using namespace std;

Stone::Stone()
{
	initStone();
}
/*
Stone::~Stone() 
{
	cout<< "Stone destructor" << endl;

}
*/
void Stone::respawn()
{
	initStone();
}


void Stone::initStone()
{
	m_position.setX(5.f);
	m_position.setY(0.f);
	m_shape = '#';

	
	// Get random number between 0 and 6, because we have 7 sorts of Stones
	int randNum = rand() % 7;
	// The L Stone
	if (randNum == 0)
	{
		m_subStones[0] = PointF(-1.f,  0.f);
		m_subStones[1] = PointF( 0.f,  0.f);
		m_subStones[2] = PointF( 1.f,  0.f);
		m_subStones[3] = PointF( 1.f, -1.f);
	}
	// The J Stone
	else if (randNum == 1)
	{
		m_subStones[0] = PointF(-1.f, -1.f);
		m_subStones[1] = PointF(-1.f,  0.f);
		m_subStones[2] = PointF( 0.f,  0.f);
		m_subStones[3] = PointF( 1.f,  0.f);
	}
	// The S Stone
	else if (randNum == 2)
	{
		m_subStones[0] = PointF(-1.f,  0.f);
		m_subStones[1] = PointF( 0.f,  0.f);
		m_subStones[2] = PointF( 0.f, -1.f);
		m_subStones[3] = PointF( 1.f, -1.f);	
	}
	// The z Stone
	else if (randNum == 3)
	{
		m_subStones[0] = PointF(-1.f, -1.f);
		m_subStones[1] = PointF( 0.f, -1.f);
		m_subStones[2] = PointF( 0.f,  0.f);
		m_subStones[3] = PointF( 1.f,  0.f);		
	}
	// The T Stone
	else if (randNum == 4)
	{
		m_subStones[0] = PointF(-1.f,  0.f);
		m_subStones[1] = PointF( 0.f,  0.f);
		m_subStones[2] = PointF( 0.f, -1.f);
		m_subStones[3] = PointF( 1.f,  0.f);		
	}
	// The I Stone
	else if (randNum == 5)
	{
		m_subStones[0] = PointF(-2.f,  0.f);
		m_subStones[1] = PointF(-1.f,  0.f);
		m_subStones[2] = PointF( 0.f,  0.f);
		m_subStones[3] = PointF( 1.f,  0.f);
		// The rotation point have to be shifted because the
		// because the midpoint is not at 0|0 by the I Stone 
		m_rotationPoint = PointF(-0.5f, -0.5f);
	}
	// The O Stone
	else if (randNum == 6)
	{
		m_subStones[0] = PointF(-1.f,  0.f);
		m_subStones[1] = PointF( 0.f,  0.f);
		m_subStones[2] = PointF(-1.f, -1.f);
		m_subStones[3] = PointF( 0.f, -1.f);
		// Same as by the I Stone, the rotation point have to be shifted
		m_rotationPoint = PointF(-0.5f, -0.5f);	
	}
	
	m_positionOld = m_position;
	for (int i = 0; i != 4; i++)
	{
		m_subStonesOld[i] = m_subStones[i];		
	}

}

Stone::Stone(const float midPointX, const float midPointY,
	      const float subStone1X, const float subStone1Y,
	      const float subStone2X, const float subStone2Y,
	      const float subStone3X, const float subStone3Y,
	      const float subStone4X, const float subStone4Y):
	Drawable('#')
{
	m_position = PointF(midPointX, midPointY);
	m_subStones[0] = PointF(subStone1X, subStone1Y);
	m_subStones[1] = PointF(subStone2X, subStone2Y);
	m_subStones[2] = PointF(subStone3X, subStone3Y);
	m_subStones[3] = PointF(subStone4X, subStone4Y);
}

int Stone::getLeft() const
{	
	int x = m_subStones[0].getIntX();
	for (int i = 1; i != 4; i++)
	{
		if (m_subStones[i].getIntX() < x)
			x = m_subStones[i].getIntX();	
	}
	return m_position.getIntX() + x;	
}

int Stone::getRight() const
{
	int x = m_subStones[0].getIntX();
	for (int i = 1; i != 4; i++)
	{
		if (m_subStones[i].getIntX() > x)
			x = m_subStones[i].getIntX();	
	}
	return m_position.getIntX() + x;	
}

int Stone::getTop() const
{
	int y = m_subStones[0].getIntY();
	for (int i = 1; i != 4; i++)
	{
		if (m_subStones[i].getIntY() < y)
			y = m_subStones[i].getIntY();	
	}
	return m_position.getIntY() + y;	
}

int Stone::getBottom() const
{
	int y = m_subStones[0].getIntY();
	for (int i = 1; i != 4; i++)
	{
		if (m_subStones[i].getIntY() > y)
			y = m_subStones[i].getIntY();	
	}
	return m_position.getIntY() + y;	
}

void Stone::fillWithGlobalPoints(PointF points[4]) const
{
	for (int i = 0; i != 4; i++)
	{
		 points[i] = m_subStones[i] + m_position;	
	}
}

void Stone::moveDown()
{
	saveOldPosition();
	// Remember: Our coordinate system get postive to the down
	// (inverse y-axses) so we have to add 1
	m_position.setY(m_position.getY() + 1.f);
}

void Stone::moveLeft()
{
	saveOldPosition();
	m_position.setX(m_position.getX() - 1.f);
}

void Stone::moveRight()
{
	saveOldPosition();
	m_position.setX(m_position.getX() + 1.f);
}

void Stone::rotateRight()
{
	saveOldPosition();
	for (PointF &point : m_subStones)
	{
		point.rotateAround(m_rotationPoint.getX(), m_rotationPoint.getY(), -90.f);	
	}
}

void Stone::rotateLeft()
{
	saveOldPosition();
	for (PointF &point : m_subStones)
	{
		point.rotateAround(m_rotationPoint.getX(), m_rotationPoint.getY(), 90.f);
	}
}

void Stone::fillFieldBuffer
(const int startX, const int startY,
 char fieldBuffer[world_constants::SCREEN_HEIGHT][world_constants::SCREEN_WIDTH]) const
{
	for (PointF point : m_subStones)
	{
		/* We have to cast to int because the terminals coordinate system
		 * only works with real numbers
	       	*/
		int globalPosX = m_position.getIntX() + point.getIntX(); 
		int globalPosY  = m_position.getIntY() + point.getIntY();
		
		// Only save 
		if (globalPosX >= 0 && globalPosX <= world_constants::FIELD_COLUMN &&
		    globalPosY >= 0 && globalPosY <= world_constants::FIELD_ROW)
		{			
			
			/* We have to switch the axes here, because by looping
			 * over the 2d array we first go to the row and then loop
			 * over all columns.
			 */
			fieldBuffer[startY + globalPosY][startX + globalPosX] = m_shape;
		}
	}
}


bool Stone::isCollidingWithPoint(const PointF &point) const
{	
	PointF subStones[4];
	this->fillWithGlobalPoints(subStones);
	for (PointF pointSub : subStones)
	{
		if (pointSub.isFullNumberEquals(point))
			return true;		
	}
	return false;
}

void Stone::restoreOldPosition() 
{
	m_position = m_positionOld;
	for (int i = 0; i != 4; i++)
	{
		m_subStones[i] = m_subStonesOld[i];	
	}
}

void Stone::saveOldPosition() 
{
	m_positionOld = m_position;
	for (int i = 0; i != 4; i++)
	{
		m_subStonesOld[i] = m_subStones[i];
	}
}

#endif // !STONE_CPP
