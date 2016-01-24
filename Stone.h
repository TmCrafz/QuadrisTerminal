#ifndef STONE_H
#define STONE_H
#include <vector>
#include "WorldConstants.h"
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
	// The char which is drawn for a point
	const char m_Shape = '#';
public:

	Stone();

	/*
	Stone(Point position, Point subStone1, Point subStone2, 
	      Point subStone3, Point subStone4);
	*/

	Stone(const int midPointX, const int midPointY,
	      const int subStone1X, const int subStone1Y,
	      const int subStone2X, const int subStone2Y,
	      const int subStone3X, const int subStone3Y,
	      const int subStone4X, const int subStone4Y);
	
	// Get the position of the specific axe of the point which is most in the
	// specic direction
	int getLeft() const;
	int getRight() const;
	int getTop() const;
	int getBottom() const;
	
	void moveDown();
	void moveLeft();
	void moveRight();
	// Store the Stone in the buffer so we can later draw it with
	// all the other Stones
	void fillFieldBuffer(char fieldBuffer[world_constants::FIELD_ROW][world_constants::FIELD_COLUMN]);
	
};

#endif // !STONE_H
