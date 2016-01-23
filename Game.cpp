#ifndef GAME_CPP
#define GAME_CPP
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "WorldConstants.h"
#include "InputHelper.h"

using namespace std;

Game::Game():
m_isRunning(true),
m_stepTime(1000)
{
	std::cout << "Konstruktor Game Class" << std::endl;		
}

void Game::run()
{
	spawnStone();
	CLOCK::time_point timeStart = CLOCK::now();
	while (m_isRunning)
	{
		if (isStepTimeLeft(timeStart))
		{
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
	if (time >= 1000)
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
			;	
		}	
	}

}

void Game::spawnStone()
{
	//Stone stone;
	
	
	//m_stones.push_back(stone);
}

void Game::update()
{
	m_currentStone.moveDown();
	/*
	for (Stone &stone : m_stones)
	{
		stone.moveDown();
	}
	*/
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



