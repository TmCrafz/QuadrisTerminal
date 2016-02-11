#ifndef MENUMAIN_H
#define MENUMAIN_H
#include "Screen.h"

class MenuMain : public Screen
{
private:
	static const int LOGO_HEIGHT = 7;
	static const int LOGO_WIDTH = 36;
	char m_logo[LOGO_HEIGHT][LOGO_WIDTH];
public:
	
	MenuMain();

private:
	void loadLogo();

	virtual void handleInput();
	
	virtual void update();

	virtual void fillScreenBuffer();

};

#endif // !MENUMAN_H
