#ifndef WORLDCONSTANTS_H
#define WORLDCONSTANTS_H

namespace world_constants
{
	// The dimensions of the screen
	static const short SCREEN_HEIGHT = 21;
	static const short SCREEN_WIDTH = 60; 
	// The dimensions of the field with corners and border
	static const short FIELD_WHOLE_WIDTH = 12;
	static const short FIELD_WHOLE_HEIGHT = 21;
	
	// The dimensions of the play field (where the stones fall and the player can move)
	static const short FIELD_COLUMN = 10;
	static const short FIELD_ROW = 20;

	// Where the play field begins
	static const short FIELD_START_X = 16;
	static const short FIELD_START_Y = 0;
	// Next Stone
	static const short NEXTSTONE_BOX_START_X = 3;
	static const short NEXTSTONE_BOX_START_Y = 4;
	// Statistics
	static const short STAT_START_X = 3;
	static const short STAT_START_Y = 15;
}

#endif //!WORLDCONSTANTS_H
