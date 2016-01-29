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
m_stepTime(1000),
m_currentStone(),
m_command('\0')
{
	for (int i = 0; i != 100; i++)
		m_currentStone.respawn();
}

void Game::run()
{
	CLOCK::time_point timeStart = CLOCK::now();
	while (m_running)
	{
		
		checkInput();
		commandReaction();	
		if (isStepTimeLeft(timeStart))
		{
			cout << "Step Time left" << endl;
			updateTimeAffected();
			m_draw = true;
			//std::cout << "Time Step Left: " << m_stepTime << " ms" << std::endl;
			timeStart = CLOCK::now();	
		}
		if (m_draw)
		{
			draw();	
			m_draw = false;
		}
	}
}

bool Game::isStepTimeLeft(CLOCK::time_point timeStart)
{
	CLOCK::time_point now = CLOCK::now();
	chrono::duration<float> timeSpan = (now - timeStart);
	auto milli = chrono::duration_cast<chrono::milliseconds>(timeSpan);
	auto time = milli.count();
	if (time >= m_stepTime)
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
	// Move down the last added stone, because its
	// the actual stone which the user can control
	m_currentStone.moveDown();
	// If the Stone collides with the ground "freeze" the Stone
	// (Add the Stone to the m_stones container so it is not longer
	// under the users control.
	if (m_currentStone.getBottom() == world_constants::FIELD_ROW - 1) 
	{
		m_stones.push_back(m_currentStone);
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
			// Only move Stone if it does not collide which anything
			if (m_currentStone.getLeft() > 0)	
				m_currentStone.moveLeft();
		}
		else if (m_command == 'd')
		{
			if (m_currentStone.getRight() < (world_constants::FIELD_COLUMN - 1))
				m_currentStone.moveRight();
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

	
	for (Stone stone : m_stones)
	{
		stone.fillFieldBuffer(m_fieldBuffer);	
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



