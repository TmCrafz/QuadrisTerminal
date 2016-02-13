#ifndef SCREEN_H
#define SCREEN_H
#include "WorldConstants.h"

class Screen
{
protected:
	// Store the chars which get drawn in drawToScreen method
	char m_screenBuffer[world_constants::SCREEN_HEIGHT][world_constants::SCREEN_WIDTH];
	char m_command;
	bool m_running;
	// Is true when something has changed, which make it necessary to redraw the Screen
	bool m_draw;
public:
	Screen();

	void run();
	
protected:

	void checkInput();
	
	virtual void handleInput();
	
	virtual void update();

	void draw();
	
	void clearScreen();

	void clearScreenBuffer();
	// Draw a border around the screen
	virtual void drawBorder();

	// Add the chars whicht should get drawn to screen
	virtual void fillScreenBuffer();

	void drawToScreen() const;

};

#endif // !SCREEN_H
