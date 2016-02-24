#ifndef MENUMAIN_H
#define MENUMAIN_H
#include <iostream>
#include <vector>
#include <string>
#include "Screen.h"
#include "ScreenBuffer.h"

class MenuMain : public Screen
{
private:
	static const int LOGO_HEIGHT = 7;
	static const int LOGO_WIDTH = 36;
	char m_logo[LOGO_HEIGHT][LOGO_WIDTH];
	
	std::vector<std::string> m_menuEntries;
	// The actual selected menu entry
	int m_actualMenuPos;
public:
	
	MenuMain(ScreenBuffer *screenBuffer);

private:
	void loadLogo();

	virtual void handleInput();
	
	virtual void update();
	
	void drawLogo();

	void drawMenuEntry(const int entryNumber);

	virtual void fillScreenBuffer();

};

#endif // !MENUMAN_H
