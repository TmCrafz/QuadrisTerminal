#ifndef SCORESCREEN_CPP
#define SCORESCREEN_CPP
#include <fstream>
#include <algorithm>
#include <iterator>
#include "ScoreScreen.h"

using namespace std;
using namespace world_constants;

bool Score::operator<(const Score &scoreB) const
{
	return (score < scoreB.score);
}

ScoreScreen::ScoreScreen():
m_showScore(false),
m_editMode(false),
m_ScoreNew(0),
m_scorePos(0)
{
	loadScores();
}

ScoreScreen::ScoreScreen(const int score):
m_showScore(true),
m_editMode(false),
m_ScoreNew(score),
m_scorePos(0)
{
	loadScores();
	checkIfScoreIsInTopList();
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
	}
	file.close();
}

void ScoreScreen::saveScore() const
{
	ofstream file("scores.txt");
	if (file)
	{
		for (Score score : m_scores)
		{
			file << score.name << ";" << score.score << "\n";	
		}
	}
	file.close();
}

void ScoreScreen::checkIfScoreIsInTopList()
{
	bool inTopList = false;
	int listPos = 0;
	// if there are no scores in toplist the new score is definetely in top list
	if (m_scores.size() < 10)
	{
		inTopList = true;		
	}
	for (size_t i = 0; i != m_scores.size(); i++)
	{
		Score &score = m_scores.at(i);
		if (m_ScoreNew > score.score)
		{
			// The vector is sorted, so se highest store is on position
			// 0. If the actual score is higher then the actual we now its new position
			// and can leave the loop, to store the new score.
			inTopList = true;
			listPos = i;
			break;
		}
	}
	// Save new score if it is in top 10 list
	if (inTopList)
	{	
		
		Score scoreNew;
		m_scorePos = listPos;
		scoreNew.score = m_ScoreNew;
		// Store the new score at its new position
		m_scores.insert(m_scores.begin() + listPos, scoreNew);
		// Remove the last score, because there are only 10 scores in the top list
		if (m_scores.size() > 10)
		{				
			m_scores.pop_back();	
		}
		// Set the edit mode to true so the player can input its name
		m_editMode = true;
		// Dont let parent class handle closing as long we are in edit mode
		m_handleScreenClosing = false;
	}
}

void ScoreScreen::handleInput()
{
	if (m_editMode)
	{
		char allowedNameChars[] = {
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',	               
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
		'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
		'w', 'x', 'y', 'z',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
                'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V',
                'W', 'X', 'Y', 'Z', 
		'?', '!', ':'
		};
		if (m_command != '\0')
		{
			// Check if the input is a legal char for the name
			bool legalChar = 
				find( begin(allowedNameChars), end(allowedNameChars), m_command ) 
				!= end(allowedNameChars);
			// Only add legal chars to name
			if (legalChar)
			{
				// Add the input char to the name of the new score
				Score &score = m_scores.at(m_scorePos);
				score.name += m_command;
				m_draw = true;
			}
			// Backspace key
			else if (m_command == 127)
			{
				Score &score = m_scores.at(m_scorePos);
				// Delete last char if there is something to delete
				if (score.name.length() > 0)
				{
					score.name.pop_back();
				}
				m_draw = true;
			}
			else if (m_command == '\n')
			{
				// The player accept the name so leave the edit mode
				// and let parent class handle closing the screen
				// when pressing the key
				m_editMode = false;
				m_handleScreenClosing = true;
				saveScore();
				m_draw = true;
			}
		}
	}
}

void ScoreScreen::update()
{

}

void ScoreScreen::drawScreenTitle()
{
	const string Title = "HIGHSCORES";
	const int PosX = static_cast<int>( (SCREEN_WIDTH / 2) - (Title.length() / 2) );
	m_screenBuffer.add(PosX, 1, Title);
}

void ScoreScreen::drawTitleBar()
{
	m_screenBuffer.add(COLUMN_POS_X, TITLE_BAR_START_Y, "POS");
	m_screenBuffer.add(COLUMN_NAME_X, TITLE_BAR_START_Y, "NAME");
	m_screenBuffer.add(COLUMN_SCORE_X, TITLE_BAR_START_Y, "SCORE");

}

void ScoreScreen::drawRow(const int pos)
{
	const Score &score = m_scores.at(pos);
	const int DrawnPos = pos + 1;
	const int RowStartY = ROW_START_Y + pos;
	m_screenBuffer.add(COLUMN_POS_X, RowStartY, to_string(DrawnPos) + ".");
	m_screenBuffer.add(COLUMN_NAME_X, RowStartY, score.name);
	m_screenBuffer.add(COLUMN_SCORE_X, RowStartY, to_string(score.score));
}

void ScoreScreen::drawNewScore()
{
	const string Text = "Your Score: " + to_string(m_ScoreNew);
	const int PosX = static_cast<int>( (SCREEN_WIDTH / 2) - (Text.length() / 2) );
	m_screenBuffer.add(PosX, PLAYERS_NEW_SCORE_Y, Text);	
}

void ScoreScreen::drawEditText()
{
	const string Text = "New Highscore, enter name";
	const int PosX = static_cast<int>( (SCREEN_WIDTH / 2) - (Text.length() / 2) );
	m_screenBuffer.add(PosX, CLOSE_MENU_Y, Text);	
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
	if (m_showScore)
	{
		drawNewScore();
	}
	if (!m_editMode)
	{
		drawCloseText();
	}
	else
	{
		drawEditText();		
	}
}



#endif // !SCORESCREEN_CPP
