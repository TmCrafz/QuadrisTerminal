#ifndef STONE_H
#define STONE_H
#include <vector>
#include "Drawable.h"
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

class Stone : public Drawable
{
private:
	// The position of all substones which result in the whole Stone
	Point m_subStones[4];
	// The rotation point
	Point m_rotationPoint;

	// The absolute position of the midpoint
	Point m_position;
	/*
	 * Store the old absolute position and relativ Position of the Stones 
	 * after the position or orientation changed, 
	 * so we can restore if necessary (e.g. if there is a collision)
	 */
	Point m_positionOld;
	Point m_subStonesOld[4];
	// The char which is drawn for a point
	//char m_shape;
public:

	Stone();
	//~Stone();	
	Stone(const int midPointX, const int midPointY,
	      const int subStone1X, const int subStone1Y,
	      const int subStone2X, const int subStone2Y,
	      const int subStone3X, const int subStone3Y,
	      const int subStone4X, const int subStone4Y);

	// Set the Stone to the default point and choose a new Stone sort
	void respawn();
	
	// Get the position of the specific axe of the point which is most in the
	// specic direction
	int getLeft() const;
	int getRight() const;
	int getTop() const;
	int getBottom() const;
	
	// Retrun the Points with global coordinates
	void fillWithGlobalPoints(Point *points) const;

	void moveDown();
	void moveLeft();
	void moveRight();

	void rotateRight();
	void rotateLeft();
	// Store the Stone in the buffer so we can later draw it with
	// all the other Stones
	virtual void fillFieldBuffer
	    (char fieldBuffer[world_constants::FIELD_ROW][world_constants::FIELD_COLUMN]) const;
	
	bool isCollidingWithPoint(const Point &point) const;
	
	void restoreOldPosition();

private:
	void initStone();
	
	void saveOldPosition();
};

#endif // !STONE_H
