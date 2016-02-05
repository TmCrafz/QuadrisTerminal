#ifdef POINTF_CPP
#define POINTF_CPP
#include <iostream>
#include <PointF.h>

PointF::PointF():
m_x(0.f),
m_y(0.f)
{
}

PointF::PointF(const float x, const float y):
m_x(x),
m_y(y)
{
}

float PointF::getX() const { return m_x; }
float PointF::getY() const { return m_y; }

void PointF::setX(const float x) { m_x = x; }
void PointF::setY(const float y) { m_y = y; }

void PointF::operator=(const PointF &right)
{
	this->m_x = right.m_x;
	this->m_y = right.m_y;
}

PointF PointF::operator+(const PointF &right)
{
	PointF result;
	result.setX(m_x + right.m_x);
	result.setY(m_y + right.m_y);
	return result;
}

PointF PointF::operator+(const PointF &right) const
{
	PointF result;
	result.setX(m_x + right.m_x);
	result.setY(m_y + right.m_y);
	return result;
}

PointF PointF::operator-(const PointF &right)
{
	PointF result;
	result.setX(m_x - right.m_x);
	result.setY(m_y - right.m_y);
	return result;
}

PointF PointF::operator-(const PointF &right) const
{
	PointF result;
	result.setX(m_x - right.m_x);
	result.setY(m_y - right.m_y);
	return result;
}

PointF& PointF::operator+=(const PointF &right)
{
	this->m_x += right.m_x;
	this->m_y += right.m_y;
	return *this;
}

PointF& PointF::operator-=(const PointF &right)
{
	this->m_x -= right.m_x;
	this->m_y -= right.m_y;
	return *this;
}

bool PointF::operator==(const PointF &right)
{
	return (this->m_x == right.m_x && this->m_y == right.m_y);
}



#endif // !POINTF_CPP
