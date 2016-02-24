#ifndef FALLENSTONE_H
#define FALLENSTONE_H
#include "WorldConstants.h"
#include "Drawable.h"
#include "PointF.h"
#include "ScreenBuffer.h"

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
	    (const int StartX, const int StartY, ScreenBuffer *screenBuffer) const;

	void moveDown();

};


#endif // !FALLENSTONE_H
