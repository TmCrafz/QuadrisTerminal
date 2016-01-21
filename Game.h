#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <chrono>


//#define timePoint std::chrono::high_resolution_clock::time_point
typedef std::chrono::high_resolution_clock CLOCK;


class Game 
{
private:
	bool m_isRunning;
	//std::chrono::high_resolution_clock::time_point m_timePoint;
	//CLOCK::time_point m_timeStart;
	// The timestep in miliseconds
	int m_stepTime;
public:
	Game();
	void run();
private:
	bool isStepTimeLeft(CLOCK::time_point timeStart);

};

#endif // !GAME_H
