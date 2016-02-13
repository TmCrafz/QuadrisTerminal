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

void FallenStone::fillScreenBuffer
	    (const int startX, const int startY, 
	     char screenBuffer[world_constants::SCREEN_HEIGHT][world_constants::SCREEN_WIDTH]) const
{
	// The total position on screen
	const int totalPosX = startX + m_position.getIntX();
	const int totalPosY = startY + m_position.getIntY();
	// Only add to screen buffer when the position is in screen area
	if (totalPosX >= 0 && totalPosX < world_constants::SCREEN_WIDTH &&
	    totalPosY >= 0 && totalPosY < world_constants::SCREEN_HEIGHT)
	{
		// Only add to screen buffer whem the position is in screen area
		screenBuffer[totalPosY][totalPosX] = m_shape;
	}
}

void FallenStone::moveDown()
{
	m_position.setY(m_position.getY() + 1.f);
}

#endif // !FALLENSTONE_CPP
