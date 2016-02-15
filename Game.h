/*
 *	The main Game class.
 *	Game specific Stuff is handled here but the input reading
 *	and drawing and the Gameloop is handled by the parent "Screen"
 *	class. But we have to fill the screen buffer here, 
 *	so the parent class know what to draw.
 **/

#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include "Screen.h"
#include "WorldConstants.h"
#include "PointF.h"
#include "Stone.h"
#include "FallenStone.h"


typedef std::chrono::high_resolution_clock CLOCK;



class Game : public Screen
{
private:
	bool m_paused;
	
	// The time since the last regular update	
	CLOCK::time_point m_timeStart;
	
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

	// The removed lines since the the player is in the current level
	unsigned int m_removedLinesLevel;

	unsigned int m_removedLinesTotal;
	unsigned int m_level;
	unsigned int m_score;

public:
	Game();
private:
	bool isCurrentStoneColliding() const;

	bool isStepTimeLeft() const;
	
	
	void cleanFullRow(const int row);

	void removeFullRows();
	
	void leaveGame();

	bool isGameOver();

	void spawnStone();

	void updateTimeAffected();
	
	virtual void handleInput();

	virtual void update();

	
	void drawStats();

	void drawNextStone();

	void drawGameField();
	
	void drawFallenStones();

	void drawPauseInfo();

	virtual void fillScreenBuffer();
};

#endif // !GAME_H
