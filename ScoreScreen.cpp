#ifndef SCORESCREEN_CPP
#define SCORESCREEN_CPP
#include <fstream>
#include <algorithm>
#include "ScoreScreen.h"

using namespace std;
using namespace world_constants;

bool Score::operator<(const Score &scoreB) const
{
	return (score < scoreB.score);
}


ScoreScreen::ScoreScreen():
m_scoreNew(0)
{
	loadScores();
}

ScoreScreen::ScoreScreen(const int score):
m_scoreNew(score)
{	
	loadScores();

}

void ScoreScreen::loadScores()
{
	ifstream file("scores.txt", ifstream::in);
	if (file)
	{
		string str;
		while(getline(file, str))
		{
			Score score;
			string nameTmp;
			string scoreTmp;
			// part = 0 -> name, part = 1 -> score
			int part = 0;
			for (size_t i = 0; i != str.length(); i++)
			{
				char c = str[i];
				// Split the read line into name and score
				if (c != ';' && c != '\n')
				{
					if (part == 0)
					{
						nameTmp += c;
					}
					else
					{
						scoreTmp += c;
					}				
				}
				else if (c == ';')
				{
					part++;
				}
			}
			score.name = nameTmp;
			score.score = scoreTmp.length() == 0 ? 0 : stoi(scoreTmp);
			m_scores.push_back(score);
		}
		sort(m_scores.begin(), m_scores.end());
		// we want the scores in descent order so reverse the vector
		reverse(m_scores.begin(), m_scores.end());
		for (Score score : m_scores)
		{
			cout << "Name: " << score.name << " Score: " << score.score << endl;
		}
	}
	file.close();
}

void ScoreScreen::handleInput()
{

}

void ScoreScreen::update()
{

}

void ScoreScreen::drawString(const int startX, const int startY, string text)
{
	for (size_t x = startX; x != startX + text.length(); x++)
	{
		m_screenBuffer[startY][x] = text[x - startX];	
	}
	
}

void ScoreScreen::drawScreenTitle()
{
	const string Title = "HIGHSCORES";
	const int PosX = static_cast<int>( (SCREEN_WIDTH / 2) - (Title.length() / 2) );
	drawString(PosX, 1 , Title);
}

void ScoreScreen::drawTitleBar()
{
	drawString(COLUMN_POS_X, TITLE_BAR_START_Y, "POS");
	drawString(COLUMN_NAME_X, TITLE_BAR_START_Y, "NAME");
	drawString(COLUMN_SCORE_X, TITLE_BAR_START_Y, "SCORE");

}

void ScoreScreen::drawRow(const int pos)
{
	const Score score = m_scores.at(pos);
	const int DrawnPos = pos + 1;
	const int RowStartY = ROW_START_Y + pos;
	drawString(COLUMN_POS_X, RowStartY, to_string(DrawnPos) + ".");
	drawString(COLUMN_NAME_X, RowStartY, score.name);
	drawString(COLUMN_SCORE_X, RowStartY, to_string(score.score));
}

void ScoreScreen::drawCloseText()
{
	const string Text = "Press c to return";
	const int PosX = static_cast<int>( (SCREEN_WIDTH / 2) - (Text.length() / 2) );
	drawString(PosX, CLOSE_MENU_Y, Text);	
}

void ScoreScreen::fillScreenBuffer()
{
	drawScreenTitle();
	drawBorder();
	drawTitleBar();
	for (size_t i = 0; i != m_scores.size(); i++)
	{
		drawRow(i);	
	}
	drawCloseText();
	if (m_editMode)
	{
			
	}
}



#endif // !SCORESCREEN_CPP
