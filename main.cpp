#include <iostream>
#include <chrono>
#include <string>
#include <cstdlib>
#include <ctime>
#include "MenuMain.h"
#include "Game.h"
#include "InputHelper.h"

using namespace std;

int main()
{
	srand(time(0));

	MenuMain menuMain;
	menuMain.run();
	//Game game;
	//game.run();
	cout<< "End Game" << endl;
	return 0;
}
