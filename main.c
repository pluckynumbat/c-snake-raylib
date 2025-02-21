#include "raylib.h"

////Constants////

const int WINDOW_WIDTH = 200;
const int WINDOW_HEIGHT = 200;
const char* GAME_TITLE = "C-Snake";

const int SNAKE_CELL_RADIUS = 4;
const int DEFAULT_SNAKE_CELL_DIFF = 4;

const int STARTING_SNAKE_LENGTH = 10;

const Color SNAKE_COLOR = {
    .r = 240,
    .g = 140,
    .b = 0,
    .a = 255,
};

///end Constants////

///Types////
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


    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        //draw the snake
        for (int i = 0; i < STARTING_SNAKE_LENGTH; i++)
        {
            DrawCircle(snake[i].x, snake[i].y, SNAKE_CELL_RADIUS, SNAKE_COLOR);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}