#ifndef INPUTHELPER_H
#define INPUTHELPER_H

/*
 * Implemention of the kbhit() and getch()
 */

class InputHelper
{
public:
	// Check if a key was pressed (kbhit)
	static int isKeyPressed();
	// Get the key which was pressed (getch)
	static int getInputchar();
};

#endif // !INPUTHELPER
