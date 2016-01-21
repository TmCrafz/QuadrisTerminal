#ifndef STONE_H
#define STONE_H
#include <vector>
#include "Point.h" 
/*
 *  A Stone consists of 4 subStones, represented in Points.
 *  The Stones have an own inner coordinate system:
 *          -2
 *      ....|....
 *      ....|....
 *    -4----+----+4
 *      ....|....
 *      ....|.... 
 *          +2
 *  The "+" is the midpoint relative it is always (0|0),
 *  but the absolute position depence from the Stone position in the
 *  Play field.
 */

class Stone
{
private:
	// The position of all substones which result in the whole Stone
	Point m_subStones[4];
	// The absolute position of the midpoint
	Point m_position;

public:
	Stone(Point position, Point subStone1, Point subStone2, 
	      Point subStone3, Point subStone4);

	Stone(int midPointX, int midPointY,
	      int subStone1X, int subStone1Y,
	      int subStone2X, int subStone2Y,
	      int subStone3X, int subStone3Y,
	      int subStone4X, int subStone4Y);


	
};

#endif // !STONE_H
