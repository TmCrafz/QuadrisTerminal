#ifndef SCREEN_CPP
#define SCREEN_CPP
#include <iostream>
#include "Screen.h"
#include "WorldConstants.h"
#include "InputHelper.h"

using namespace std;
using namespace world_constants;

Screen::Screen():
m_screenBuffer(SCREEN_WIDTH, SCREEN_HEIGHT),
m_command('\0'),
m_running(true),
m_draw(true),
m_handleScreenClosing(true)
{
}

void Screen::run()
{
	while(m_running)
	{
		checkInput();
		handleInput();
		update();
		if (m_draw)
		{
			draw();
		}
	}
}

void Screen::checkInput()
{
	m_command = '\0';
	if (InputHelper::kbhit())
	{
		m_command = InputHelper::getch();
		if (m_command == 'c' && m_handleScreenClosing)
		{
			m_running = false;
		}
	}
}

void Screen::handleInput()
{
	// Do nothing by default
}

void Screen::update()
{
	// Do nothing by default
}

void Screen::draw()
{
	clearScreen();
	clearScreenBuffer();
	fillScreenBuffer();
	drawToScreen();
	m_draw = false;
}

void Screen::clearScreen()
{
	for (int i = 0; i != 50; i++)
	{
		cout << endl;
	}
}

void Screen::clearScreenBuffer()
{
	m_screenBuffer.clear();
}

void Screen::drawBorder()
{
	for (int y = 0; y != SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x != SCREEN_WIDTH; x++)
		{
			if (y == 0 || y == SCREEN_HEIGHT -1 ||
			    x == 0 || x == SCREEN_WIDTH -1)
			{			
				m_screenBuffer.add(x, y, '*');
			}
		}	
	}
}

void Screen::fillScreenBuffer()
{
	// Do nothing by default
}

void Screen::drawToScreen() const
{
	m_screenBuffer.drawToScreen();
}

#endif // !SCREEN_CPP
