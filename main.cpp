#include <iostream>
#include <chrono>
#include <string>
#include <cstdlib>
#include <ctime>
#include "MenuMain.h"
#include "Game.h"
#include "InputHelper.h"
#include "ScreenBuffer.h"

using namespace std;

int main()
{
	srand(time(0));
	
	ScreenBuffer screenBuffer(world_constants::SCREEN_WIDTH, world_constants::SCREEN_HEIGHT);
	ScreenBuffer *pScreenBuffer = &screenBuffer;

	MenuMain menuMain(pScreenBuffer);
	menuMain.run();
	cout<< "End Game" << endl;
	return 0;
}
