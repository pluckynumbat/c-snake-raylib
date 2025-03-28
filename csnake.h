#ifndef C_SNAKE_H
#define C_SNAKE_H

////Constants////

// Related to the window
const int WINDOW_WIDTH = 200;
const int WINDOW_HEIGHT = 200;
const char* GAME_TITLE = "C-Snake";

// Snake constants
const int SNAKE_CELL_RADIUS = 4;
const int DEFAULT_SNAKE_CELL_DIFF = 4;
const int DEFAULT_SPEED = 4;
const int STARTING_SNAKE_LENGTH = 10;
const int MAX_SNAKE_LENGTH = 500;

// Snake color constants
const Color SNAKE_COLOR_0 = {.r =   0, .g = 240, .b = 140, .a = 255,};
const Color SNAKE_COLOR_1 = {.r = 140, .g =   0, .b = 240, .a = 255,};
const Color SNAKE_COLOR_2 = {.r = 240, .g = 140, .b =   0, .a = 255,};
const Color SNAKE_COLOR_DEAD = {.r = 140,  .g = 140, .b = 140, .a = 255,};

const int SNAKE_COLOR_OPTION_COUNT = 3;
const Color SNAKE_COLORS[] = {SNAKE_COLOR_0, SNAKE_COLOR_1, SNAKE_COLOR_2};


#endif