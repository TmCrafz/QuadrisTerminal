#ifndef FALLENSTONE_CPP
#define FALLENSTONE_CPP
#include "FallenStone.h"

FallenStone::FallenStone()
{
}

FallenStone::FallenStone(const Point position):
m_position(position)
{
}

FallenStone::FallenStone(const Point position, const char shape):
Drawable(shape),
m_position(position)
{
}

Point FallenStone::getPosition() const
{
	return m_position;
}

void FallenStone::setPosition(const Point position)
{
	m_position = position;
}

void FallenStone::fillFieldBuffer
	    (char fieldBuffer[world_constants::FIELD_ROW][world_constants::FIELD_COLUMN]) const
{
	fieldBuffer[m_position.getY()][m_position.getX()] = m_shape;
}

void FallenStone::moveDown()
{
	m_position.setY(m_position.getX() + 1);
}

#endif // !FALLENSTONE_CPP
