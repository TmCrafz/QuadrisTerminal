#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include "WorldConstants.h"
#include "PointF.h"
#include "Stone.h"
#include "FallenStone.h"

typedef std::chrono::high_resolution_clock CLOCK;


class Game 
{
private:
	bool m_running;
	bool m_paused;
	// is true when something has changed which nake it necessary to redraw the field
	bool m_draw;
	// The current standard step time in miliseconds
	int m_standardStepTime;

	int m_currentStepTime;
	// The player can manually increase the Step Time so the stone falls faster
	const int m_stepTimeFast;
	
	// The actual Stone which are under the players controll
	Stone m_currentStone;
	// The next Stone
	Stone m_nextStone;

	std::vector<FallenStone> m_fallenStones;
	char m_command;
	// Store the elements which get drawn later
	char m_fieldBuffer[world_constants::FIELD_ROW][world_constants::FIELD_COLUMN];

	// The removed lines since the the player is in the current level
	unsigned int m_removedLinesLevel;

	unsigned int m_removedLinesTotal;
	unsigned int m_level;
	unsigned int m_score;

public:
	Game();
	void run();
private:
	bool isCurrentStoneColliding() const;

	bool isStepTimeLeft(CLOCK::time_point timeStart) const;
	
	void checkInput();
	
	void cleanFullRow(const int row);

	void removeFullRows();
	
	bool isGameOver();

	void spawnStone();

	void updateTimeAffected();
	
	void commandReaction();

	void draw();
};

#endif // !GAME_H
