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
	
	virtual void fillFieldBuffer
	    (const int startX, const int startY, 
	     char fieldBuffer[world_constants::FIELD_ROW][world_constants::FIELD_COLUMN]) const;

	void moveDown();

};


#endif // !FALLENSTONE_H
