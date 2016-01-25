#ifndef STONE_CPP
#define STONE_CPP
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Stone.h"

using namespace std;

Stone::Stone():
m_position(5, 0)
{
	//m_position = Point(3, 4);	
	srand(time(0));
	// Get random number between 0 and 6, because we have 7 sorts of Stones
	int randNum = rand() % 1; // 6;
	// I Stone
	// The I Stone is speciale beacuase it have a other midpoint
	if (randNum == 0)
	{
		// Do nothing at the moment
		m_subStones[0] = Point(-1, -1);
		m_subStones[1] = Point(-1,  0);
		m_subStones[2] = Point( 0,  0);
		m_subStones[3] = Point (1,  0);	
	
	}
	// The J Stone
	else if (randNum == 1)
	{
		m_subStones[0] = Point(-1, -1);
		m_subStones[1] = Point(-1,  0);
		m_subStones[2] = Point( 0,  0);
		m_subStones[3] = Point (1,  0);	
	}
}

/*
Stone::Stone(Point position, Point subStone1, Point subStone2, 
	      Point subStone3, Point subStone4):
	m_position(position),
	m_Shape('#')
{
	m_subStones[0] = subStone1;
	m_subStones[1] = subStone2;
	m_subStones[2] = subStone3;
	m_subStones[3] = subStone4;
}
*/	

Stone::Stone(const int midPointX, const int midPointY,
	      const int subStone1X, const int subStone1Y,
	      const int subStone2X, const int subStone2Y,
	      const int subStone3X, const int subStone3Y,
	      const int subStone4X, const int subStone4Y):
	m_Shape('#')
{
	m_position = Point(midPointX, midPointY);
	m_subStones[0] = Point(subStone1X, subStone1Y);
	m_subStones[1] = Point(subStone2X, subStone2Y);
	m_subStones[2] = Point(subStone3X, subStone3Y);
	m_subStones[3] = Point(subStone4X, subStone4Y);
}

int Stone::getLeft() const
{	
	int x = m_subStones[0].getX();
	for (int i = 1; i != 4; i++)
	{
		if (m_subStones[i].getX() < x)
			x = m_subStones[i].getX();	
	}
	return m_position.getX() + x;	
}

int Stone::getRight() const
{
	int x = m_subStones[0].getX();
	for (int i = 1; i != 4; i++)
	{
		if (m_subStones[i].getX() > x)
			x = m_subStones[i].getX();	
	}
	return m_position.getX() + x;	
}

int Stone::getTop() const
{
	int y = m_subStones[0].getY();
	for (int i = 1; i != 4; i++)
	{
		if (m_subStones[i].getY() < y)
			y = m_subStones[i].getY();	
	}
	return m_position.getY() + y;	
}

int Stone::getBottom() const
{
	int y = m_subStones[0].getY();
	for (int i = 1; i != 4; i++)
	{
		if (m_subStones[i].getY() > y)
			y = m_subStones[i].getY();	
	}
	return m_position.getY() + y;	
}	

void Stone::moveDown()
{
	// Remember: Our coordinate system get postive to the down
	// (inverse y-axses) so we have to add 1
	m_position.setY(m_position.getY() + 1);
}

void Stone::moveLeft()
{
	m_position.setX(m_position.getX() - 1);
}

void Stone::moveRight()
{
	m_position.setX(m_position.getX() + 1);
}

void Stone::rotateRight()
{
	for (Point &point : m_subStones)
	{
		point.rotateAround(0, 0, -90.f);	
	}
}

void Stone::rotateLeft()
{
	for (Point &point : m_subStones)
	{
		point.rotateAround(0, 0, 90.f);
	}
}

void Stone::fillFieldBuffer
(char fieldBuffer[world_constants::FIELD_ROW][world_constants::FIELD_COLUMN])
{
	for (Point point : m_subStones)
	{
		int globalPosX = m_position.getX() + point.getX();
		int globalPosY = m_position.getY() + point.getY();
		//cout << "GlobalPosX: " << globalPosX << " gloabalPosY: " << globalPosY << endl;
		// Only save 
		if (globalPosX >= 0 && globalPosX <= world_constants::FIELD_COLUMN &&
		    globalPosY >= 0 && globalPosY <= world_constants::FIELD_ROW)
		{			
			/*
			 * We have to switch the axes here, because by looping
			 * over the 2d array we first go to the row and then loop
			 * over all columns.
			 */
			fieldBuffer[globalPosY][globalPosX] = m_Shape;;
		}
	}




}

#endif // !STONE_CPP
