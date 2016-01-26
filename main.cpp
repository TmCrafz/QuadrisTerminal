#include <iostream>
#include <chrono>
#include <string>
#include "Game.h"
#include "InputHelper.h"

using namespace std;

int main()
{
	Game game;
	game.run();
	
	cout<< "End Game" << endl;
	return 0;
}
