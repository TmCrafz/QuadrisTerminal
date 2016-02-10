#ifndef MENUMAIN_H
#define MENUMAIN_H
#include "Menu.h"

class MenuMain : public Menu
{

public:
	
	MenuMain();

private:

	virtual void handleInput();
	
	virtual void fillScreenBuffer();

};

#endif // !MENUMAN_H
