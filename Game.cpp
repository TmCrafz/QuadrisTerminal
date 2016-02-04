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
	for (Point fallenStone : m_stones)
	{
		if(m_currentStone.isCollidingWithPoint(fallenStone))
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
		
		Point subStones[4];
		m_currentStone.fillWithGlobalPoints(subStones);
		for (Point subStone : subStones)
		{
			m_stones.push_back(subStone);		
		}
		spawnStone();
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
	for (Point point : m_stones)
	{
		m_fieldBuffer[point.getY()][point.getX()] = '#';	
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



