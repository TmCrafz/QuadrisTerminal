#ifndef MENUMAIN_CPP
#define MENUMAIN_CPP
#include "MenuMain.h"
#include "WorldConstants.h"

using namespace world_constants;

MenuMain::MenuMain():
Menu()
{
}

void MenuMain::handleInput()
{
	if (m_command != '\0')
	{
		if (m_command == 'c')
		{
			m_running = false;		
		}
	}
}

void MenuMain::fillScreenBuffer()
{
	for (int y = 0; y != SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x != SCREEN_WIDTH; x++)
		{
			m_screenBuffer[y][x] = '*';
		}	
	}
}


#endif // !MENUMAIN_CPP
