#ifndef DRAWABLE_H
#define DRAWABLE_H
#include "WorldConstants.h"

class Drawable
{
protected:
	char m_shape;
public:
	Drawable();
	Drawable(const char shape);

	char getShape() const;
	void setShape(const char shape);

	virtual void fillScreenBuffer
	    (const int startX, const int startY,
	     char screenBuffer
	          [world_constants::SCREEN_HEIGHT][world_constants::SCREEN_WIDTH]) const;


};



#endif // !DRAWABL_H
