#include <iostream>
#include <chrono>
#include "Game.h"

using namespace std;

int main()
{
	cout << "Vim cpp program test, compiled with gcc and make file." << endl;
	Game game;
	game.run();
	cout << "Next line 3" << endl;
	return 0;
}
