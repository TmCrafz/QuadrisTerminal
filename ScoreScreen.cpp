#ifndef SCORESCREEN_CPP
#define SCORESCREEN_CPP
#include <fstream>
#include <algorithm>
#include "ScoreScreen.h"
#include "WorldConstants.h"


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
void ScoreScreen::drawRow(const int pos)
{
	const int ROW_START_Y = 4;
	const int COLUMN_POS_X = 2;
	const int COLUMN_NAME_X = 20;
	const int COLUMN_SCORE_X = SCREEN_WIDTH - 25;
	const Score score = m_scores.at(pos);
	const int drawnPos = pos + 1;
	drawString(COLUMN_POS_X, ROW_START_Y, to_string(drawnPos) + ".");
}


void ScoreScreen::fillScreenBuffer()
{
	drawBorder();
	drawRow(0);		
}



#endif // !SCORESCREEN_CPP
