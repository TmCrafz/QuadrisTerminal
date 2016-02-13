#ifndef MENUMAIN_CPP
#define MENUMAIN_CPP
#include <fstream>
#include "MenuMain.h"
#include "WorldConstants.h"
#include "Game.h"

using namespace world_constants;
using namespace std;

MenuMain::MenuMain():
Screen(),
m_actualMenuPos(0)
{
	for (int i = 0; i != 7; i++)
	{
		for (int j = 0; j != 36; j++)
		{
			m_logo[i][j] = ' ';
		}
	}
	loadLogo();
	m_menuEntries.push_back("START GAME");
	m_menuEntries.push_back("OPTION");
	m_menuEntries.push_back("END GAME");
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
		// Control which menu entry is selected
		if (m_command == 'w')
		{
			if (m_actualMenuPos > 0)
			{
				m_actualMenuPos--;
				m_draw = true;
			}
		
		}			
		else if (m_command == 's')
		{	if (m_actualMenuPos < static_cast<int>( m_menuEntries.size() - 1) )
			{
				m_actualMenuPos++;
				m_draw = true;
			}
		}
		// React to players selection if player clicks enter
		else if (m_command == '\n')
		{
			switch (m_actualMenuPos)
			{
				case 0:
				{
					Game game;
					game.run();
					break;	
				}				
				case 1:
					break;

				case 2: 
					m_running = false;
					break;			
			}
			m_draw = true;
		}
	}
}

void MenuMain::update()
{

}

void MenuMain::drawBorder()
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
}

void MenuMain::drawLogo()
{
	const int logoStartY = 1;
	// Center the logo horizontal
	const int logoStartX = static_cast<int>((SCREEN_WIDTH / 2) - (LOGO_WIDTH / 2));
	// Add the Logo to screenBuffer
	for (int y = logoStartY ; y != logoStartY + LOGO_HEIGHT ; y++)
	{
		for (int x = logoStartX; x != logoStartX + LOGO_WIDTH; x++)
		{
			m_screenBuffer[y][x] = m_logo[y - logoStartY][x - logoStartX];
		}
	}
}

void MenuMain::drawMenuEntry(const int entryNumber)
{
	const string text = m_menuEntries.at(entryNumber);
	const int textWidth = text.length();
	
	// The menu entries should start at the bottom and go up from there
	const int textY = SCREEN_HEIGHT - 1 - ( m_menuEntries.size() * 2 ) + ( entryNumber * 2 );
	// Center the text horizontal
	const int textX =
		static_cast<int>( (SCREEN_WIDTH / 2) - (textWidth / 2) );
	for (int x = textX; x != textX + textWidth; x++)
	{
		m_screenBuffer[textY][x] = text[x - textX];
	}
	// Show if the actual entry is selected
	if (m_actualMenuPos == entryNumber)
	{
		m_screenBuffer[textY][textX - 2] = '>';
		m_screenBuffer[textY][textX + textWidth + 1] = '<';	
	}
}

void MenuMain::fillScreenBuffer()
{
	drawBorder();
	drawLogo();
	for (size_t i = 0; i != m_menuEntries.size(); i++)
	{
		drawMenuEntry(i);
	}
}


#endif // !MENUMAIN_CPP
