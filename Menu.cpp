#ifndef MENU_CPP
#define MENU_CPP
#include <iostream>
#include "Menu.h"
#include "WorldConstants.h"
#include "InputHelper.h"

using namespace std;
using namespace world_constants;

Menu::Menu():
m_command('\0'),
m_running(true)
{
}


void Menu::run()
{
	while(m_running)
	{
		checkInput();
		handleInput();
		update();
		draw();
	}
}

void Menu::checkInput()
{
	m_command = '\0';
	if (InputHelper::kbhit())
	{
		m_command = InputHelper::getch();
	}
}

void Menu::handleInput()
{
	// Do nothing by default
}

void Menu::update()
{
	// Do nothing by default
}

void Menu::draw()
{
	clearScreen();
	clearScreenBuffer();
	fillScreenBuffer();
	drawToScreen();
}

void Menu::clearScreen()
{
	for (int i = 0; i != 50; i++)
	{
		cout << endl;
	}
}

void Menu::clearScreenBuffer()
{
	for (int y = 0; y != SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x != SCREEN_WIDTH; x++)
		{
			m_screenBuffer[y][x] = ' ';
		}	
	}
}

void Menu::fillScreenBuffer()
{
	// Do nothing by default
}

void Menu::drawToScreen() const
{
	for (int y = 0; y != SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x != SCREEN_WIDTH; x++)
		{
			cout << m_screenBuffer[y][x];
		}	
		cout << endl;
	}
}

#endif // !MENU_CPP
