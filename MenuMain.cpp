#ifndef MENUMAIN_CPP
#define MENUMAIN_CPP
#include <iostream>
#include <fstream>
#include "MenuMain.h"
#include "WorldConstants.h"

using namespace world_constants;
using namespace std;

MenuMain::MenuMain():
Screen()
{
	for (int i = 0; i != 7; i++)
	{
		for (int j = 0; j != 36; j++)
		{
			m_logo[i][j] = ' ';
		}
	}
	loadLogo();
}

void MenuMain::loadLogo()
{
	ifstream file("logo.txt", ifstream::in);
	if (file)
	{
		char c;
		for (int i = 0; i != LOGO_HEIGHT; i++)
		{
			for (int j = 0; j != LOGO_WIDTH; j++)
			{
				file.get(c);
				// We don want to save next line chars.
				// Next lines are handled by the drawing method
				if (c != '\n')
				{
					m_logo[i][j] = c;
				}
			}
		}	
	}
	file.close();
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

void MenuMain::update()
{

}

void MenuMain::fillScreenBuffer()
{
	for (int y = 0; y != SCREEN_HEIGHT; y++)
	{
		for (int x = 0; x != SCREEN_WIDTH; x++)
		{
			if (y == 0 || y == SCREEN_HEIGHT -1 ||
			    x == 0 || x == SCREEN_WIDTH -1)
			{			
				m_screenBuffer[y][x] = '*';
			}
		}	
	}
	const int logoStartY = 1;
	// Center the logo horizontal
	const int logoStartX = (SCREEN_WIDTH / 2) - (LOGO_WIDTH / 2);
	// Add the Logo to screenBuffer
	for (int y = logoStartY ; y != logoStartY + LOGO_HEIGHT ; y++)
	{
		for (int x = logoStartX; x != logoStartX + LOGO_WIDTH; x++)
		{
			m_screenBuffer[y][x] = m_logo[y - logoStartY][x - logoStartX];
		}
	}
	
	char textStart[] =
		{'P', 'R', 'E', 'S', 'S', ' ', 'c', ' ', 'T', 'O', ' ', 'S', 'T', 'A', 'R', 'T' };
	const int textStartWidth = sizeof(textStart) / sizeof(char);
	const int textStartY = 18;
	// Center the text horizontal
	const int textStartX = (SCREEN_WIDTH / 2) - (textStartWidth / 2);
	cout << "Lenghth: " << textStartWidth << "startX: " << textStartX << endl;
	for (int x = textStartX; x != textStartX + textStartWidth; x++)
	{
		cout << "Char:" << textStart[x - textStartX];
		m_screenBuffer[textStartY][x] = textStart[x - textStartX];
		cout << "X: " << x << " ScreenBufferChar: " << m_screenBuffer[textStartY][x];
		cout << endl;
	}
}


#endif // !MENUMAIN_CPP
