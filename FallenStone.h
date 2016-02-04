#ifndef FALLENSTONE_H
#define FALLENSTONE_H
#include "WorldConstants.h"
#include "Drawable.h"
#include "Point.h"

class FallenStone : public Drawable
{
private:
	Point m_position;
public:
	FallenStone();
	FallenStone(const Point position);
	FallenStone(const Point position, const char shape);

	Point getPosition() const;
	void setPosition(const Point position);
	
	virtual void fillFieldBuffer
	    (char fieldBuffer[world_constants::FIELD_ROW][world_constants::FIELD_COLUMN]) const;

	void moveDown();

};


#endif // !FALLENSTONE_H
