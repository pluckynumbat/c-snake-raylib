#include "raylib.h"

////Constants////

const int WINDOW_WIDTH = 200;
const int WINDOW_HEIGHT = 200;
const char* GAME_TITLE = "C-Snake";

const int SNAKE_CELL_RADIUS = 4;
const int DEFAULT_SNAKE_CELL_DIFF = 4;
const int DEFAULT_SPEED = 4;

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
    enum direction dir;
};
///end Types////

////Globals////
int startX = WINDOW_WIDTH / 2;
int startY = WINDOW_HEIGHT / 2;

struct snakeCell snake[STARTING_SNAKE_LENGTH];

int fruitX = 0;
int fruitY = 0;

bool paused = false;
///end Globals////

void initializeGame()
{
    // create the snake
    for (int i = 0; i < STARTING_SNAKE_LENGTH; i++)
    {
        snake[i].dir = east;
        snake[i].x = startX - (i * (DEFAULT_SNAKE_CELL_DIFF));
        snake[i].y = startY;
    }

    //create the fruit
    fruitX = GetRandomValue(0, WINDOW_WIDTH);
    fruitY = GetRandomValue(0, WINDOW_HEIGHT);
}

void acceptInput()
{
    if (IsKeyPressed(KEY_W))
    {
        if (snake[0].dir != south && snake[0].dir != north)
        {
            snake[0].dir = north;
        }
    }

    if (IsKeyPressed(KEY_S))
    {
        if (snake[0].dir != south && snake[0].dir != north)
        {
            snake[0].dir = south;
        }
    }

    if (IsKeyPressed(KEY_A))
    {
        if (snake[0].dir != east && snake[0].dir != west)
        {
            snake[0].dir = west;
        }
    }

    if (IsKeyPressed(KEY_D))
    {
        if (snake[0].dir != east && snake[0].dir != west)
        {
            snake[0].dir = east;
        }
    }

    if (IsKeyPressed(KEY_SPACE))
    {
        paused = !paused;
    }
}

void moveSnake(struct snakeCell* snake, int speed)
{
    for (int i = 0; i < STARTING_SNAKE_LENGTH; i++)
    {
        switch (snake[i].dir)
        {
        case north:
            snake[i].y -= speed;
            if (snake[i].y < 0)
            {
                snake[i].y = WINDOW_HEIGHT;
            }
            break;

        case east:
            snake[i].x += speed;
            if (snake[i].x > WINDOW_WIDTH)
            {
                snake[i].x = 0;
            }
            break;

        case south:
            snake[i].y += speed;
            if (snake[i].y > WINDOW_HEIGHT)
            {
                snake[i].y = 0;
            }
            break;

        case west:
            snake[i].x -= speed;
            if (snake[i].x < 0)
            {
                snake[i].x = WINDOW_WIDTH;
            }
            break;
        }
    }

    //propagate the direction throughout the snake
    for (int i = STARTING_SNAKE_LENGTH - 1; i >= 1; i--)
    {
        snake[i].dir = snake[i - 1].dir;
    }
}

void drawSnake(struct snakeCell* snake, int snakeLength, Color color)
{
    //draw the snake
    for (int i = 0; i < STARTING_SNAKE_LENGTH; i++)
    {
        DrawCircle(snake[i].x, snake[i].y, SNAKE_CELL_RADIUS, color);
    }
}

void drawFruit(int x, int y, Color color)
{
    DrawCircle(x, y, FRUIT_RADIUS, color);
}

int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_TITLE);
    SetTargetFPS(60);

    initializeGame();


    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        //accept input
        acceptInput();

        //move the snake
        if (!paused)
        {
            moveSnake(snake, DEFAULT_SPEED);
        }

        //draw the snake
        drawSnake(snake, STARTING_SNAKE_LENGTH, SNAKE_COLOR);

        //draw the fruit
        drawFruit(fruitX, fruitY, FRUIT_COLOR_0);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}