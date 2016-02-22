#ifndef MENUSETTINGS_H
#define MENUSETTINGS_H
#include "Screen.h"


class MenuSettings : public Screen
{
private:


public:
	MenuSettings();

private:
	
	virtual void handleInput();

	virtual void update();

	virtual void fillScreenBuffer();

};

#endif // !MENUSETTINGS_H
