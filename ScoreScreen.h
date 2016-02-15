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
	static const int CLOSE_MENU_Y = world_constants::SCREEN_HEIGHT - 3;


	bool m_editMode;
	const int m_scoreNew;	
	std::vector<Score> m_scores;
	std::string m_actualInput;
	


public:
	ScoreScreen();
	ScoreScreen(const int score);

private:
	void loadScores();

	virtual void handleInput();

	virtual void update();
	
	void drawString(const int startX, const int startY, std::string text);
	
	void drawScreenTitle();

	void drawTitleBar();

	void drawRow(const int pos);
	
	void drawCloseText();

	virtual void fillScreenBuffer();

};


#endif // !SCORESCREEN_H
