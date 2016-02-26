#ifndef SCREENBUFFER_H
#define SCREENBUFFER_H
#include <iostream>

class ScreenBuffer
{
private:
	const int m_BufferHeight;
	const int m_BufferWidth;
	// Store the chars which get drawn in drawToScreen method
	char **m_screenBuffer;

public:
	ScreenBuffer(const int screenWidth, const int screenHeight);

	~ScreenBuffer();
	
	int getHeight() const;

	int getWidth() const;

	void add(const int X, const int Y, const char C);

	void add(const int StartX, const int StartY, const std::string Text);
	
	void clear();

	void display() const;

private:

	// Only true when the position is in screen area
	bool isInBufferArea(const int X, const int Y) const;


};


#endif // !SCREENBUFFER_H
