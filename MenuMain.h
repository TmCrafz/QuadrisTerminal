#ifndef MENUMAIN_H
#define MENUMAIN_H
#include "Screen.h"

class MenuMain : public Screen
{
private:
	char m_logo[7][36];


public:
	
	MenuMain();

private:

	virtual void handleInput();
	
	virtual void update();

	virtual void fillScreenBuffer();

};

#endif // !MENUMAN_H
