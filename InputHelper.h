#ifndef INPUTHELPER_H
#define INPUTHELPER_H

/*
 * Implemention of the kbhit() and getch()
 */

class InputHelper
{
public:
	// Check if a key was pressed
	static int kbhit();
	// Get the key which was pressed
	 static int getch();
};

#endif // !INPUTHELPER
