#ifndef MENUSETTINGS_H
#define MENUSETTINGS_H
#include <iostream>
#include <string>
#include <vector>
#include "Screen.h"
#include "ScreenBuffer.h"

class MenuSettings : public Screen
{
private:
	std::vector<std::string> m_controlTexts;

public:
	MenuSettings(ScreenBuffer *screenBuffer);

private:
	
	virtual void handleInput();

	virtual void update();

	virtual void fillScreenBuffer();
	
	int getCenterPosX(const std::string Text) const;
};

#endif // !MENUSETTINGS_H
