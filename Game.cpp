#ifndef GAME_CPP
#define GAME_CPP
#include "Game.h"

using namespace std;

Game::Game():
m_isRunning(true),
m_stepTime(1000)
{
	std::cout << "Konstruktor Game Class" << std::endl;		
}

void Game::run()
{
	CLOCK::time_point timeStart = CLOCK::now();
	while (m_isRunning)
	{
		if (isStepTimeLeft(timeStart))
		{
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

void Game::spawnStone()
{
	

}

void Game::draw() 
{
	cout << "============" << endl;
	for (int i = 0; i != world_constants::FIELD_ROW; i++)
	{	
		cout << "#";		
		for (int j = 0; j != world_constants::FIELD_COLUMN; j++)
		{
			cout << ".";			
		}
		cout << "#" << endl;
	}
	cout << "############" << endl;

}


#endif // !GAME_CPP



