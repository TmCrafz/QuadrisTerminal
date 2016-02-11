#ifndef SCREEN_H
#define SCREEN_H
#include "WorldConstants.h"

class Screen
{
protected:
	char m_screenBuffer[world_constants::SCREEN_HEIGHT][world_constants::SCREEN_WIDTH];
	char m_command;
	bool m_running;
public:
	Screen();

	void run();
	
private:

	void checkInput();
	
	virtual void handleInput();
	
	virtual void update();

	void draw();
	
	void clearScreen();

	void clearScreenBuffer();

	virtual void fillScreenBuffer();

	void drawToScreen() const;

};

#endif // !SCREEN_H
