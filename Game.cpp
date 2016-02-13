#ifndef GAME_CPP
#define GAME_CPP
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Game.h"
#include "WorldConstants.h"
#include "InputHelper.h"

using namespace std;
using namespace world_constants;

Game::Game():
Screen(),
m_paused(false),
m_timeStart(CLOCK::now()),
m_standardStepTime(1100),
m_currentStepTime(m_standardStepTime),
m_stepTimeFast(50),
m_currentStone(),
m_nextStone(),
m_removedLinesLevel(0),
m_removedLinesTotal(0),
m_level(0),
m_score(0)
{
	m_currentStone.toFieldStartPos();
	m_standardStepTime = (1000 - (m_level * 100)) + 100;
}

void Game::update()
{
	if (!m_paused)
	{
		removeFullRows();
		if (isStepTimeLeft())
		{
			updateTimeAffected();
			m_draw = true;
			m_timeStart = CLOCK::now();	
		}	
		// Set the current step time back to its standard so its only
		// faster as long the player press the specific key
		m_currentStepTime = m_standardStepTime;
	}

}

bool Game::isCurrentStoneColliding() const
{
	if (m_currentStone.getLeft() < 0)
		return true;
	if (m_currentStone.getRight() >= (world_constants::FIELD_COLUMN))
		return true;
	if (m_currentStone.getBottom() == world_constants::FIELD_ROW)
		return true;
	bool collidingWithFallen = false;
	for (FallenStone fallenStone : m_fallenStones)
	{
		if(m_currentStone.isCollidingWithPoint(fallenStone.getPosition()))
		{
			collidingWithFallen = true;
		}
	}
	return collidingWithFallen;
}

bool Game::isStepTimeLeft() const
{
	CLOCK::time_point now = CLOCK::now();
	chrono::duration<float> timeSpan = (now - m_timeStart);
	auto milli = chrono::duration_cast<chrono::milliseconds>(timeSpan);
	auto time = milli.count();
	if (time >= m_currentStepTime)
	{
		return true;
	}
	return false;
}

void Game::cleanFullRow(const int row)
{
	
	auto remove_st = remove_if(m_fallenStones.begin(), m_fallenStones.end(),
	[row](FallenStone &fallenStone)
	{
		return fallenStone.getPosition().getIntY() == row; 
	});	
	m_fallenStones.erase(remove_st, m_fallenStones.end());
	// Now move the Stone down which are over the deleted line
	for (FallenStone &fallenStone : m_fallenStones)
	{
		if (fallenStone.getPosition().getIntY() < row)
		{
			fallenStone.moveDown();		
		}			
	}
}

void Game::removeFullRows()
{
	// Count the remove lines so we can later calculate the score
	unsigned int removedLines = 0;
	bool rowDeletion = true;
	while (rowDeletion)
	{
		rowDeletion = false;
		// The Amount of fallen stones in the rows
		unsigned int fallenStonesRow[world_constants::FIELD_ROW] = { 0 };
		for (FallenStone fallenStone : m_fallenStones)
		{
			// Increase the number of the row where the fallen stone is
			(fallenStonesRow[fallenStone.getPosition().getIntY()])++;	
		}
		for (int i = 0; i != world_constants::FIELD_ROW; i++)
		{
		
			int actualRow = i;
			// Remove the stones which are in a full row
			if (fallenStonesRow[actualRow] == world_constants::FIELD_COLUMN)
			{
				cleanFullRow(actualRow);
				// Set the row Deleted to true and break the loop so we can restart
				// checking if a row is full, because by moving down
				// now there can be new full lines
				rowDeletion = true;
				removedLines++;
				break;
			}	
		}	
	}
	if (removedLines > 0)
	{
		m_removedLinesLevel += removedLines;
		m_removedLinesTotal += removedLines;
		if (m_removedLinesLevel >= 10 && m_level <= 10)
		{
			m_level++;
			m_standardStepTime = (1000 - (m_level * 100)) + 100;
			m_currentStepTime = m_standardStepTime;
			// Add the rest lines to the actual level lines
			m_removedLinesLevel = m_removedLinesLevel % 10;
		}
		m_score += (40 * (m_level + 1) * pow(2 , removedLines)); 
	}
	
}

bool Game::isGameOver()
{
	return m_currentStone.getBottom() <= 0;
}

void Game::spawnStone()
{
	m_currentStone = m_nextStone;
	m_currentStone.toFieldStartPos();
	m_nextStone = Stone();
}

void Game::updateTimeAffected()
{
	/*
	 * Move down the last added stone, because its
	 * the actual stone which the user can control
	 */
	 m_currentStone.moveDown();
	/*
	 * If the Stone collides with the ground "freeze" the Stone
	 * (Add the Stone to the m_stones container so it is not longer
	 * under the users control.
	  */
	if (isCurrentStoneColliding()) 
	{
		m_currentStone.restoreOldPosition();
		if (isGameOver())
		{
			m_running = false;
		}
		PointF subStones[4];
		m_currentStone.fillWithGlobalPoints(subStones);
		for (PointF subStone : subStones)
		{
			FallenStone fallenStone(subStone, m_currentStone.getShape());
			m_fallenStones.push_back(fallenStone);		
		}
		spawnStone();
		removeFullRows();
	}
}

void Game::handleInput()
{
	// First check if there was an input
	if (m_command != '\0')
	{
		if (m_command == '0')
		{
			m_paused = !m_paused;
		}
		else if (!m_paused)
		{
			if (m_command == 'a')
			{
				m_currentStone.moveLeft(); 
			}
			else if (m_command == 'd')
			{
				m_currentStone.moveRight();
			}
			else if (m_command == 's')
			{
				// The stone should fall faster as long the button is pressed
				m_currentStepTime = m_stepTimeFast;
			}
			else if (m_command == 'o')
			{
				m_currentStone.rotateLeft();
			}
			else if (m_command == 'p')
			{
				m_currentStone.rotateRight();
			}
			// Debuging commands
			else if (m_command == '1')
			{
				spawnStone();
			}

			if (isCurrentStoneColliding())
			{
				// Restore the Stones old Position if it is colliding with something
				m_currentStone.restoreOldPosition();
				if (isGameOver())
				{
					m_running = false;
				}
			}			
		}		
		m_command = '\0';	
		// Something has changed so the Screen should redraw
		m_draw = true;
	}
}

void Game::drawStats()
{
	// First store all string in a array which should drawm later
	string stats[3] = { 
		"Score: " + to_string(m_score),
		"Lines: " + to_string(m_removedLinesTotal),
		"Level: " + to_string(m_level)
	};
	// Now we have to convert then to chars so we can store then in the ScreenBuffer
	for (int i = 0; i != 3; i++)
	{
		string stat = stats[i];
		for (size_t j = 0; j != stat.size(); j++)
		{
			char c = stat[j];
			m_screenBuffer[STAT_START_Y + i][STAT_START_X + j] = c;
		}
	}
}

void Game::drawNextStone()
{
	// Store the Next Stone Box in buffer
	for (int y = NEXTSTONE_BOX_START_Y; y != NEXTSTONE_BOX_START_Y + 6; y++)
	{
		for (int x = NEXTSTONE_BOX_START_X; x != NEXTSTONE_BOX_START_X + 9; x++)
		{
			if (x == NEXTSTONE_BOX_START_X || x == NEXTSTONE_BOX_START_X + 8 ||
					y == NEXTSTONE_BOX_START_Y || y == NEXTSTONE_BOX_START_Y + 5)
			{
				m_screenBuffer[y][x] = '#';
			}
		}
	}	
	//Store the Next Stone in buffer
	m_nextStone.fillScreenBuffer
		(NEXTSTONE_BOX_START_X + 4, NEXTSTONE_BOX_START_Y + 3, m_screenBuffer);	
}

void Game::drawGameField()
{
	// Store the Game Screen with borders and the ground in buffer
	for (int y = FIELD_START_Y; y != FIELD_START_Y + FIELD_WHOLE_HEIGHT; y++)
	{
		for (int x = FIELD_START_X; x != FIELD_START_X + FIELD_WHOLE_WIDTH; x++)
		{	
			// Store the ground
			if (y == FIELD_START_Y + FIELD_WHOLE_HEIGHT - 1)
			{
				m_screenBuffer[y][x] = '#';
			}
			// Store the borders left and right in the Screen
			else if (x == FIELD_START_X || x == FIELD_START_X + FIELD_WHOLE_WIDTH - 1)
			{
				m_screenBuffer[y][x] = '#';			
			}
			// Store the empty Screen
			else
			{
				m_screenBuffer[y][x] =  ' ';
			}
		}
	}
}

void Game::drawFallenStones()
{
	// Store the fallen Stones in buffer
	for (FallenStone fallenStone : m_fallenStones)
	{
		fallenStone.fillScreenBuffer
			(FIELD_START_X + 1, FIELD_START_Y, m_screenBuffer);
	}
}

void Game::drawPauseInfo()
{	if (m_paused)
	{
		const string text = "--PAUSED--";
		const int textWidth = text.length();
		const int textY = static_cast<int> (SCREEN_HEIGHT / 2);
		const int textX = 
		      static_cast<int> (FIELD_START_X + (FIELD_WHOLE_WIDTH / 2) - (textWidth / 2) );
		for (int i = textX; i != textX + textWidth; i++)
		{
			m_screenBuffer[textY][i] = text[i - textX];		
		}
	}
}

void Game::fillScreenBuffer()
{
	
	// Store the statistics in buffer
	drawStats();		
	drawNextStone();	
	drawGameField();
	drawFallenStones();
	// FIELD_START_X + 1 because we have a border with a with of one, 
	// so start after the left border
	m_currentStone.fillScreenBuffer(FIELD_START_X + 1, FIELD_START_Y, m_screenBuffer);
	drawPauseInfo();
}

#endif // !GAME_CPP

