#include <iostream>
#include <chrono>
#include <string>
#include "Game.h"
#include "InputHelper.h"

using namespace std;

int main()
{
	char tmp;
	do 
	{
		if (InputHelper::kbhit())
		{
			tmp = InputHelper::getch();
			cout << "Pressed: " << tmp << endl;
		}
	} while (tmp != 'k');
	
	tmp = ' ';
	

	do 
	{
		if (InputHelper::kbhit())
			tmp = InputHelper::getch();
	} while (tmp != 'k');

	 

	cout << "Vim cpp program test, compiled with gcc and make file." << endl;
	Game game;
	game.run();
	
	return 0;
}
