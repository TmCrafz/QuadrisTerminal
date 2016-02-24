#ifndef MENUSETTINGS_CPP
#define MENUSETTINGS_CPP
#include "MenuSettings.h"
#include "WorldConstants.h"

using namespace std;
using namespace world_constants;


MenuSettings::MenuSettings(ScreenBuffer *screenBuffer):
Screen(screenBuffer)
{
	m_controlTexts.push_back("[A] - Move Left");
	m_controlTexts.push_back("[D] - Move Right");
	m_controlTexts.push_back("[S] - Faster Down");
	m_controlTexts.push_back("[O] - Rotate Left");
	m_controlTexts.push_back("[P] - Rotate Right");
	m_controlTexts.push_back("[0] - Pause Game");
}

void MenuSettings::handleInput()
{

}

void MenuSettings::update()
{

}

void MenuSettings::fillScreenBuffer()
{
	drawBorder();
	drawCloseText();
	const string ControlText = "CONTROL:";
	m_screenBuffer->add(getCenterPosX(ControlText), 2, ControlText);

	const int StartX = 3;
	int textY = 4;
	for (const string Text : m_controlTexts)
	{
		m_screenBuffer->add(StartX, textY, Text);
		textY += 2;
	}
	void drawCloseText();
}

int MenuSettings::getCenterPosX(const string Text) const
{
	return static_cast<int>( (SCREEN_WIDTH / 2) - (Text.length() / 2) );
}


#endif // MENUSETTINGS_CPP
