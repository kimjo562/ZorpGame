#pragma once

const char* const CSI = "\x1b[";						// ControlSequenceIntroducer
const char* const TITLE = "\x1b[5;20H";		  	    // Commands move cursor x,y (20,5)
const char* const INDENT = "\x1b[5C";					// Moves the cursor right by 5
const char* const YELLOW = "\x1b[93m";				// Sets the Text Colour Yellow
const char* const MAGENTA = "\x1b[95m";				// Sets the Text Colour Magenta
const char* const RESET_COLOR = "\x1b[0m";			// Resets the Text colour to default
const char* const EXTRA_OUTPUT_POS = "\x1b[25;6H";

const char* const RED = "\x1b[91m";					// Sets the Text Colour Red
const char* const BLUE = "\x1b[94m";					// Sets the Text Colour Blue
const char* const WHITE = "\x1b[97m";					// Sets the Text Colour White
const char* const GREEN = "\x1b[92m";					// Sets the Text Colour Green
const char* const CYAN = "\x1b[96m";					// Sets the Text Colour Cyan

const int EMPTY = 0;
const int ENEMY = 1;
const int TREASURE = 2;
const int FOOD = 3;
const int ENTRANCE = 4;
const int EXIT = 5;
const int MAX_RANDOM_TYPE = FOOD + 1;
const int MAZE_WIDTH = 10;
const int MAZE_HEIGHT = 6;

const int INDENT_X = 5;  // how many spaces to use to indent all text
const int ROOM_DESC_Y = 8;  // the line to use for our room descriptions
const int MOVEMENT_DESC_Y = 9;
const int MAP_Y = 13; // the first line where the map is drawn.

const int PLAYER_INPUT_X = 30;  // the character column where the player will type their input.
const int PLAYER_INPUT_Y = 23;  // the line where the player will type their input.

const int WEST = 4;
const int EAST = 6;
const int NORTH = 8;
const int SOUTH = 2;

const int LOOK = 9;
const int FIGHT = 10;