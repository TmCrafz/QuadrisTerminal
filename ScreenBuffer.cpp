#ifndef SCREENBUFFER_CPP
#define SCREENBUFFER_CPP
#include "ScreenBuffer.h"

using namespace std;

ScreenBuffer::ScreenBuffer(const int screenWidth, const int screenHeight):
m_BufferHeight(screenHeight),
m_BufferWidth(screenWidth),
// Allocate the memory for the 2d array
m_screenBuffer(new char *[m_BufferHeight])
{
	for (int i = 0; i != m_BufferHeight; i++)
	{
		m_screenBuffer[i] = new char[m_BufferWidth];	
	}
}

ScreenBuffer::~ScreenBuffer()
{
	// Free the memory of the screenBuffer
	for (int i = 0; i != m_BufferHeight; i++)
	{
		delete[] m_screenBuffer[i];
	}
	delete[] m_screenBuffer;
}

int ScreenBuffer::getHeight() const
{
	return m_BufferHeight;
}

int ScreenBuffer::getWidth() const
{
	return m_BufferWidth;
}

void ScreenBuffer::add(const int X, const int Y, const char C)
{
	if (isInBufferArea(X, Y))
	{
		m_screenBuffer[Y][X] = C;
	}
}

void ScreenBuffer::add(const int StartX, const int StartY, const string Text)
{
	for (size_t x = StartX; x != StartX + Text.length(); x++)
	{
		if (isInBufferArea(x, StartY))
		{
			m_screenBuffer[StartY][x] = Text[x - StartX];	
		}
	}
}

void ScreenBuffer::clear()
{
	for (int y = 0; y != m_BufferHeight; y++)
	{
		for (int x = 0; x != m_BufferWidth; x++)
		{
			m_screenBuffer[y][x] = ' ';
		}	
	}
}

void ScreenBuffer::drawToScreen() const
{
	for (int y = 0; y != m_BufferHeight; y++)
	{
		for (int x = 0; x != m_BufferWidth; x++)
		{
			cout << m_screenBuffer[y][x];
		}	
		cout << endl;
	}
}

bool ScreenBuffer::isInBufferArea(const int X, const int Y) const
{
	return (X >= 0 && X < m_BufferWidth && Y >= 0 && Y < m_BufferHeight);
}

#endif // !SCREENBUFFER_CPP
