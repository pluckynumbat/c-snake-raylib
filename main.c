#include "raylib.h"

////Constants////

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


int main()
{
    InitWindow(200, 200, "C-Snake");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}