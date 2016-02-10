#ifndef MENU_H
#define MENU_H
#include "WorldConstants.h"

class Menu
{
protected:
	char m_screenBuffer[world_constants::SCREEN_HEIGHT][world_constants::SCREEN_WIDTH];
	char m_command;
	bool m_running;
public:
	Menu();

	void run();
	
private:

	void checkInput();
	
	virtual void handleInput();

	void draw();

	void clearScreenBuffer();

	virtual void fillScreenBuffer();

	void drawToScreen() const;

};



#endif // !MENU_H
