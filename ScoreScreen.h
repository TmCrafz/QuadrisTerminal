#ifndef SCORESCREEN_H
#define SCORESCREEN_H
#include <iostream>
#include <string>
#include <vector>
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

	void drawRow(const int pos);

	virtual void fillScreenBuffer();

};


#endif // !SCORESCREEN_H
