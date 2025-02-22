#include "raylib.h"

////Constants////

const int WINDOW_WIDTH = 200;
const int WINDOW_HEIGHT = 200;
const char* GAME_TITLE = "C-Snake";

const int SNAKE_CELL_RADIUS = 4;
const int DEFAULT_SNAKE_CELL_DIFF = 4;

const int STARTING_SNAKE_LENGTH = 10;

const int FRUIT_RADIUS = 4;

const Color SNAKE_COLOR = {
    .r = 240,
    .g = 140,
    .b = 0,
    .a = 255,
};

const Color FRUIT_COLOR_0 = {
    .r = 220,
    .g = 20,
    .b = 0,
    .a = 255,
};

///end Constants////

///Types////
enum direction
{
    north,
    south,
    east,
    west,
};

struct snakeCell
{
    int x;
    int y;
};
///end Types////

////Globals////
int startX = WINDOW_WIDTH / 2;
int startY = WINDOW_HEIGHT / 2;

struct snakeCell snake[STARTING_SNAKE_LENGTH];

int fruitX = 0;
int fruitY = 0;

///end Globals////

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_TITLE);
    SetTargetFPS(60);

    // create the snake
    for (int i = 0; i < STARTING_SNAKE_LENGTH; i++)
    {
        snake[i].x = startX - (i * (DEFAULT_SNAKE_CELL_DIFF));
        snake[i].y = startY;
    }

    //create the fruit
    fruitX = GetRandomValue(0, WINDOW_WIDTH);
    fruitY = GetRandomValue(0, WINDOW_HEIGHT);


    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        //draw the snake
        for (int i = 0; i < STARTING_SNAKE_LENGTH; i++)
        {
            DrawCircle(snake[i].x, snake[i].y, SNAKE_CELL_RADIUS, SNAKE_COLOR);
        }

        //draw the fruit
        DrawCircle(fruitX, fruitY, FRUIT_RADIUS, FRUIT_COLOR_0);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}