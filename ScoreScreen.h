#ifndef SCORESCREEN_H
#define SCORESCREEN_H
#include <iostream>
#include <string>
#include <vector>
#include "WorldConstants.h"
#include "Screen.h"

struct Score
{
	std::string name;
	int score = 0;

	// Overade the < operator so we can sort vectors whith score objects
	bool operator<(const Score &scoreB) const;
};


class ScoreScreen : public Screen
{
private:
	static const int TITLE_BAR_START_Y = 3;
	static const int ROW_START_Y = 4;
	static const int COLUMN_POS_X = 2;
	static const int COLUMN_NAME_X = 20;
	static const int COLUMN_SCORE_X = world_constants::SCREEN_WIDTH - 10;
	static const int PLAYERS_NEW_SCORE_Y = world_constants::SCREEN_HEIGHT - 5;
	static const int CLOSE_MENU_Y = world_constants::SCREEN_HEIGHT - 3;

	/* If it is true show the players score, from the game.
	 * If its false it only shows the scores and there is no new score
	 * e.g. when the screen is called from the main menu instead after a game. 
	 */
	bool m_showScore;
	// If it is true the player can type his name and store his score
	bool m_editMode;
	const int m_ScoreNew;
	// The position in the top score list (if in toplist)
	int m_scorePos;
	std::vector<Score> m_scores;
	std::string m_actualInput;
	


public:
	ScoreScreen();
	ScoreScreen(const int score);

private:
	void loadScores();
	
	void saveScore() const;

	void checkIfScoreIsInTopList();

	virtual void handleInput();

	virtual void update();
	
	void drawString(const int startX, const int startY, std::string text);
	
	void drawScreenTitle();

	void drawTitleBar();

	void drawRow(const int pos);

	void drawNewScore();

	void drawCloseText();

	// The text which is shown when the players score is in top 10
	void drawEditText();

	virtual void fillScreenBuffer();

};


#endif // !SCORESCREEN_H
