#ifndef DRAWABLE_CPP
#define DRAWABLE_CPP
#include <iostream>
#include "Drawable.h"

using namespace std;

Drawable::Drawable():
m_shape('\0')
{
}

Drawable::Drawable(const char shape):
m_shape(shape)
{
}

char Drawable::getShape() const 
{
	return m_shape;
}

void Drawable::setShape(const char shape)
{
	m_shape = shape;
}

void Drawable::fillScreenBuffer
(const int startX, const int startY,
 char screenBuffer[world_constants::SCREEN_HEIGHT][world_constants::SCREEN_WIDTH]) const
{
	// Do nothing by default
}

#endif // !DRAWABLE_CPP
