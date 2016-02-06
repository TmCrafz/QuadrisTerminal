#ifndef FALLENSTONE_CPP
#define FALLENSTONE_CPP
#include "FallenStone.h"

FallenStone::FallenStone()
{
}

FallenStone::FallenStone(const PointF position):
m_position(position)
{
}

FallenStone::FallenStone(const PointF position, const char shape):
Drawable(shape),
m_position(position)
{
}

PointF FallenStone::getPosition() const
{
	return m_position;
}

void FallenStone::setPosition(const PointF position)
{
	m_position = position;
}

void FallenStone::fillFieldBuffer
	    (char fieldBuffer[world_constants::FIELD_ROW][world_constants::FIELD_COLUMN]) const
{
	fieldBuffer[m_position.getIntY()][m_position.getIntX()] = m_shape;
}

void FallenStone::moveDown()
{
	m_position.setY(m_position.getY() + 1.f);
}

#endif // !FALLENSTONE_CPP
