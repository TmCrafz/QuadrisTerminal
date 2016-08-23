#include <iostream>
#include "Screen.h"
#include "WorldConstants.h"
#include "InputHelper.h"

using namespace std;
using namespace world_constants;

Screen::Screen(ScreenBuffer *screenBuffer):
m_screenBuffer(screenBuffer),
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
	if (InputHelper::isKeyPressed())
	{
		m_command = InputHelper::getInputchar();
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
	display();
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
	m_screenBuffer->clear();
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
				m_screenBuffer->add(x, y, '*');
			}
		}	
	}
}

void Screen::drawCloseText()
{
	const int CloseMenuY = world_constants::SCREEN_HEIGHT - 3;
	const string Text = "Press c to return";
	const int PosX = static_cast<int>( (SCREEN_WIDTH / 2) - (Text.length() / 2) );
	m_screenBuffer->add(PosX, CloseMenuY, Text);
}

void Screen::fillScreenBuffer()
{
	// Do nothing by default
}

void Screen::display() const
{
	m_screenBuffer->display();
}
