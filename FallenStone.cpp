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
(const int StartX, const int StartY, ScreenBuffer *screenBuffer) const
{
	// The total position on screen
	const int totalPosX = StartX + m_position.getIntX();
	const int totalPosY = StartY + m_position.getIntY();
	screenBuffer->add(totalPosX, totalPosY, m_shape);
}

void FallenStone::moveDown()
{
	m_position.setY(m_position.getY() + 1.f);
}
