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
	    (const int startX, const int startY, 
	     char fieldBuffer[world_constants::SCREEN_HEIGHT][world_constants::SCREEN_WIDTH]) const
{
	fieldBuffer[startY + m_position.getIntY()][startX + m_position.getIntX()] = m_shape;
}

void FallenStone::moveDown()
{
	m_position.setY(m_position.getY() + 1.f);
}

#endif // !FALLENSTONE_CPP
