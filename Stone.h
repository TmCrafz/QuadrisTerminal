#ifndef STONE_H
#define STONE_H
#include <vector>
#include "ScreenBuffer.h"
#include "Drawable.h"
#include "WorldConstants.h"
#include "PointF.h" 

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
	PointF m_subStones[4];
	// The rotation point
	PointF m_rotationPoint;

	// The absolute position of the midpoint
	PointF m_position;
	/*
	 * Store the old absolute position and relativ Position of the Stones 
	 * after the position or orientation changed, 
	 * so we can restore if necessary (e.g. if there is a collision)
	 */
	PointF m_positionOld;
	PointF m_subStonesOld[4];

public:

	Stone();

	Stone(const float midPointX, const float midPointY,
	      const float subStone1X, const float subStone1Y,
	      const float subStone2X, const float subStone2Y,
	      const float subStone3X, const float subStone3Y,
	      const float subStone4X, const float subStone4Y);

	// Set the Stone to the default point and choose a new Stone sort
	void spawn();
	// Set the field start position
	void toFieldStartPos();

	// Get the position of the specific axe of the point which is most in the
	// specic direction
	int getLeft() const;
	int getRight() const;
	int getTop() const;
	int getBottom() const;
	
	// Retrun the Points with global coordinates
	void fillWithGlobalPoints(PointF *points) const;

	void moveDown();
	void moveLeft();
	void moveRight();

	void rotateRight();
	void rotateLeft();
	// Store the Stone in the buffer so we can later draw it with
	// all the other Stones
	virtual void fillScreenBuffer
		(const int StartX, const int StartY, ScreenBuffer &screenBuffer) const;
	
	bool isCollidingWithPoint(const PointF &point) const;
	
	void restoreOldPosition();

private:
	void initStone();
	
	void saveOldPosition();
};

#endif // !STONE_H
