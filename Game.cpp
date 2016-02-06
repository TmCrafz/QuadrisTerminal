#ifndef GAME_CPP
#define GAME_CPP
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "WorldConstants.h"
#include "InputHelper.h"

using namespace std;

Game::Game():
m_running(true),
m_draw(true),
m_standardStepTime(1000),
m_currentStepTime(m_standardStepTime),
m_stepTimeFast(200),
m_currentStone(),
m_command('\0')
{
}

void Game::run()
{
	CLOCK::time_point timeStart = CLOCK::now();
	while (m_running)
	{
		/* 
		 * Set the current step time back to its standard so its only
		 * faster as long the player press the specific key
		 */
		m_currentStepTime = m_standardStepTime;
		checkInput();
		commandReaction();	
		removeFullRows();
		if (isStepTimeLeft(timeStart))
		{
			cout << "Step Time left" << endl;
			updateTimeAffected();
			m_draw = true;
			timeStart = CLOCK::now();	
		}
		if (m_draw)
		{
			draw();	
			m_draw = false;
		}
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
		/*
		if (stone.isCollidingWithStone(m_currentStone))
		{
			collidingWithStone = true;
		}	
		*/
	}
	return collidingWithFallen;
}

bool Game::isStepTimeLeft(CLOCK::time_point timeStart) const
{
	CLOCK::time_point now = CLOCK::now();
	chrono::duration<float> timeSpan = (now - timeStart);
	auto milli = chrono::duration_cast<chrono::milliseconds>(timeSpan);
	auto time = milli.count();
	if (time >= m_currentStepTime)
	{
		return true;
	}
	return false;
}

void Game::checkInput()
{
	if (InputHelper::kbhit())
	{
		m_command = InputHelper::getch();		
	}
}

void Game::removeFullRows()
{
	// The Amount of fallen stones in the rows
	unsigned int fallenStonesRow[world_constants::FIELD_ROW] = { 0 };
	for (FallenStone fallenStone : m_fallenStones)
	{
		// Increase the number of the row where the fallen stone is
		(fallenStonesRow[fallenStone.getPosition().getIntY()])++;	
	}
	bool rowDeleted = false;
	for (int i = 0; i != world_constants::FIELD_ROW; i++)
	{

		int actualRow = i;
		// Remove the stones which are in a full row
		if (fallenStonesRow[actualRow] == world_constants::FIELD_COLUMN)
		{
			auto remove_st = remove_if(m_fallenStones.begin(), m_fallenStones.end(),
				[actualRow](FallenStone &fallenStone)
				{
					return fallenStone.getPosition().getIntY() == actualRow; 
				});	
			m_fallenStones.erase(remove_st, m_fallenStones.end());
			// Now move the Stone down which are over the deleted line
			for (FallenStone &fallenStone : m_fallenStones)
			{
				if (fallenStone.getPosition().getIntY() < actualRow)
				{
					fallenStone.moveDown();		
				}			
			}
			// Set the row Deleted to true and break the loop so we can restart
			// checking if a row is full, because by moving down now there can be
			// new full lines
			rowDeleted = true;
			break;
		}	
	}
	if (rowDeleted)
	{
		removeFullRows();
	}
}

void Game::spawnStone()
{
	m_currentStone.respawn();
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

void Game::commandReaction()
{
	// First check if there was an input
	if (m_command != '\0')
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
		else if (m_command == 'c')
		{
			m_running = false;
		}
		// Debuging commands
		else if (m_command == '1')
		{
			spawnStone();
		}
		m_command = '\0';	
		// Restore the Stones old Position if it is colliding with something
		if (isCurrentStoneColliding())
			m_currentStone.restoreOldPosition();
		// Something has changed so the field should redraw
		m_draw = true;
	}
}

void Game::draw() 
{
	// Where no Stone is there is a "."
	for (int i = 0; i != world_constants::FIELD_ROW; i++)
	{
		for (int j = 0; j != world_constants::FIELD_COLUMN; j++)
		{
			m_fieldBuffer[i][j] = '.';
		}
	}
	
	m_currentStone.fillFieldBuffer(m_fieldBuffer);
	
	// Draw fallen SubStones
	/*
	for (Point point : m_stones)
	{
		m_fieldBuffer[point.getY()][point.getX()] = '#';	
	}
	*/
	for (FallenStone fallenStone : m_fallenStones)
	{
		fallenStone.fillFieldBuffer(m_fieldBuffer);
	}

	cout << "============" << endl;
	for (int i = 0; i != world_constants::FIELD_ROW; i++)
	{	
		cout << "#";		
		for (int j = 0; j != world_constants::FIELD_COLUMN; j++)
		{
			cout << m_fieldBuffer[i][j];			
		}
		cout << "#" << endl;
	}
	cout << "############" << endl;

}


#endif // !GAME_CPP



