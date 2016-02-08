#ifndef FALLENSTONE_H
#define FALLENSTONE_H
#include "WorldConstants.h"
#include "Drawable.h"
#include "PointF.h"

class FallenStone : public Drawable
{
private:
	PointF m_position;
public:
	FallenStone();
	FallenStone(const PointF position);
	FallenStone(const PointF position, const char shape);

	PointF getPosition() const;
	void setPosition(const PointF position);
	
	virtual void fillScreenBuffer
	    (const int startX, const int startY, 
	     char screenBuffer
	     [world_constants::SCREEN_HEIGHT][world_constants::SCREEN_WIDTH]) const;

	void moveDown();

};


#endif // !FALLENSTONE_H
