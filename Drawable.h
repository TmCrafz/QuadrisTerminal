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

	virtual void fillFieldBuffer
	    (const int startX, const int startY,
	     char fieldBuffer[world_constants::FIELD_ROW][world_constants::FIELD_COLUMN]) const;


};



#endif // !DRAWABL_H
