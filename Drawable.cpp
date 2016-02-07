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

void Drawable::fillFieldBuffer
(const int startX, const int startY,
 char fieldBuffer[world_constants::FIELD_ROW][world_constants::FIELD_COLUMN]) const
{
	// Do nothing by default
}

#endif // !DRAWABLE_CPP
