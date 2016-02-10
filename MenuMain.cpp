#ifndef MENUMAIN_CPP
#define MENUMAIN_CPP
#include <iostream>
#include <fstream>
#include "MenuMain.h"
#include "WorldConstants.h"

using namespace world_constants;
using namespace std;

MenuMain::MenuMain():
Menu()
{
	for (int i = 0; i != 7; i++)
	{
		for (int j = 0; j != 36; j++)
		{
			m_logo[i][j] = ' ';
		}
	}


	ifstream file("logo.txt", ifstream::in);
	if (file)
	{
		char c;
		for (int i = 0; i != 7; i++)
		{
			for (int j = 0; j != 36; j++)
			{
				file.get(c);
				if (c != '\n')
				{
					//file >> m_logo[i][j]; 
					//file.get(m_logo[i][j]);
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
			m_screenBuffer[y][x] = '*';
		}	
	}

	for (int i = 0; i != 7; i++)
	{
		for (int j = 0; j != 36; j++)
		{
			cout << m_logo[i][j];
		}
		cout << endl;	
	}
}


#endif // !MENUMAIN_CPP
