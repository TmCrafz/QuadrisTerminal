#ifndef STONE_CPP
#define STONE_CPP
#include "Stone.h"

Stone::Stone(Point position, Point subStone1, Point subStone2, 
	      Point subStone3, Point subStone4):
	m_position(position)
{
	m_subStones[0] = subStone1;
	m_subStones[1] = subStone2;
	m_subStones[2] = subStone3;
	m_subStones[3] = subStone4;
}
	

Stone::Stone(int midPointX, int midPointY,
	      int subStone1X, int subStone1Y,
	      int subStone2X, int subStone2Y,
	      int subStone3X, int subStone3Y,
	      int subStone4X, int subStone4Y)
{
	m_position = Point(midPointX, midPointY);
	m_subStones[0] = Point(subStone1X, subStone1Y);
	m_subStones[1] = Point(subStone2X, subStone2Y);
	m_subStones[2] = Point(subStone3X, subStone3Y);
	m_subStones[3] = Point(subStone4X, subStone4Y);
}


#endif // !STONE_CPP
