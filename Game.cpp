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
	while(m_isRunning)
	{
		if (isStepTimeLeft(timeStart))
		{
			std::cout << "Time Step Left: " << m_stepTime << " ms" << std::endl;
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

#endif // !GAME_CPP



