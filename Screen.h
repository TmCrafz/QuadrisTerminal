#ifndef SCREEN_H
#define SCREEN_H
#include "ScreenBuffer.h"

class Screen
{
protected:
	// Store the chars which get drawn to screen
	ScreenBuffer m_screenBuffer;	
	char m_command;
	bool m_running;
	// Is true when something has changed, which make it necessary to redraw the Screen
	bool m_draw;
	// Only handle closing the window in checkInput if m_handleScreenClosing is true
	bool m_handleScreenClosing;
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
	
	// Draw a text which inform the player how leave the actual screen
	void drawCloseText();

	// Add the chars whicht should get drawn to screen
	virtual void fillScreenBuffer();

	void drawToScreen() const;

};

#endif // !SCREEN_H
