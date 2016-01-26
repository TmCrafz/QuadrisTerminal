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
m_isRunning(true),
m_stepTime(1000),
m_currentStone()
{
	std::cout << "Konstruktor Game Class" << std::endl;		
}

void Game::run()
{
	CLOCK::time_point timeStart = CLOCK::now();
	while (m_isRunning)
	{
		
		checkInput();
		
		if (isStepTimeLeft(timeStart))
		{
			cout << "Step Time left" << endl;
			update();
			draw();
			//std::cout << "Time Step Left: " << m_stepTime << " ms" << std::endl;
			timeStart = CLOCK::now();	
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
	char inputKey = ' ';
	if (InputHelper::kbhit())
	{
		inputKey = InputHelper::getch();
		
		if (inputKey == 'a')
		{
			// Only move Stone if it does not collide which anything
			if (m_currentStone.getLeft() > 0)	
				m_currentStone.moveLeft();
		}
		else if (inputKey == 'd')
		{
			if (m_currentStone.getRight() < (world_constants::FIELD_COLUMN - 1))
				m_currentStone.moveRight();
		}
		else if (inputKey == 'o')
		{
			m_currentStone.rotateLeft();
		}
		else if (inputKey == 'p')
		{
			m_currentStone.rotateRight();
		}
		else if (inputKey == 'c')
		{
			m_isRunning = false;
		}
	}

}

void Game::spawnStone()
{
	m_currentStone.respawn();
}

void Game::update()
{
	// Move down the last added stone, because its
	// the actual stone which the user can control
	m_currentStone.moveDown();
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



