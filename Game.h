#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <chrono>
#include <vector>
#include "WorldConstants.h"
#include "Stone.h"


//#define timePoint std::chrono::high_resolution_clock::time_point
typedef std::chrono::high_resolution_clock CLOCK;


class Game 
{
public:
	// The size of the main play field where the Stones are in
	static const short FIELD_ROW = 20;
	static const short FIELD_COLUMN = 10;
private:
	bool m_isRunning;
	//std::chrono::high_resolution_clock::time_point m_timePoint;
	//CLOCK::time_point m_timeStart;
	// The timestep in miliseconds
	int m_stepTime;
	Stone m_currentStone;
	std::vector<Stone> m_stones;
	// Store the elements which get drawn later
	char m_fieldBuffer[world_constants::FIELD_ROW][world_constants::FIELD_COLUMN];
public:
	Game();
	void run();
private:
	bool isStepTimeLeft(CLOCK::time_point timeStart);
	
	void checkInput();

	void spawnStone();

	void update();

	void draw();
};

#endif // !GAME_H
