#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <chrono>
#include <vector>
#include "Stone.h"

//#define timePoint std::chrono::high_resolution_clock::time_point
typedef std::chrono::high_resolution_clock CLOCK;


class Game 
{
private:
	const short m_ROW = 20;
	const short m_COLUMN = 10;

	bool m_isRunning;
	//std::chrono::high_resolution_clock::time_point m_timePoint;
	//CLOCK::time_point m_timeStart;
	// The timestep in miliseconds
	int m_stepTime;
	std::vector<Stone> m_stones;
public:
	Game();
	void run();
private:
	bool isStepTimeLeft(CLOCK::time_point timeStart);

	void draw();
};

#endif // !GAME_H
