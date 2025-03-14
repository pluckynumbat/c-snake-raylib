#include "raylib.h"
#include <stdio.h>

////Constants////

const int WINDOW_WIDTH = 200;
const int WINDOW_HEIGHT = 200;
const char* GAME_TITLE = "C-Snake";

const int SNAKE_CELL_RADIUS = 4;
const int DEFAULT_SNAKE_CELL_DIFF = 4;
const int DEFAULT_SPEED = 4;

const int STARTING_SNAKE_LENGTH = 10;
const int MAX_SNAKE_LENGTH = 500;

const int FRUIT_RADIUS = 4;
const int FRUIT_SCORE = 1;

const int SPECIAL_FRUIT_RADIUS = 8;
const int SPECIAL_FRUIT_SCORE = 10;
const int SPECIAL_FRUIT_ONE_IN_HOW_MANY_CHANCE = 1000;

const int MAX_SCORE_DIGITS = 3;
const int SCORE_FONT_SIZE = 100;
const Color SCORE_FONT_COLOR= {
    .r = 140,
    .g = 140,
    .b = 140,
    .a = 100,
};

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

const Color BG_COLOR_0 = RAYWHITE;
const Color BG_COLOR_1 = DARKGRAY;
const Color BG_COLOR_2 = DARKPURPLE;

const int BG_COLOR_OPTION_COUNT = 3;
const Color BG_COLORS[] = {BG_COLOR_0, BG_COLOR_1, BG_COLOR_2};

const Color SPECIAL_FRUIT_COLOR = {
    .r = 200,
    .g = 40,
    .b = 200,
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
    bool isOn;
};
///end Types////

////Globals////
int startX = WINDOW_WIDTH / 2;
int startY = WINDOW_HEIGHT / 2;

struct snakeCell snake[MAX_SNAKE_LENGTH];
int snakeLength = 0;

int fruitX = 0;
int fruitY = 0;

bool paused = false;
bool ended = false;

enum direction frameStartDirection;

int score = 0;
char scoreDisplay[MAX_SCORE_DIGITS + 1];

int BGColorIndex = 0;

bool specialFruitSpawned = false;

int sFruitX = 0;
int sFruitY = 0;
///end Globals////

void spawnNewFruit()
{
    fruitX = GetRandomValue(0, WINDOW_WIDTH);
    fruitY = GetRandomValue(0, WINDOW_HEIGHT);
}

void initializeGame()
{
    //set snake length
    snakeLength = STARTING_SNAKE_LENGTH;

    // create the snake
    for (int i = 0; i < MAX_SNAKE_LENGTH; i++)
    {
        snake[i].dir = east;
        snake[i].x = startX - (i * (DEFAULT_SNAKE_CELL_DIFF));
        snake[i].y = startY;
        snake[i].isOn = i <= snakeLength;
    }

    //create the fruit
    spawnNewFruit();

    //reset paused and ended states
    paused = false;
    ended = false;

    //reset the score
    score = 0;

    //reset special fruit spawn
    specialFruitSpawned = false;
}

void cacheFrameStartSnakeDirection()
{
    frameStartDirection = snake[0].dir;
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

    if (IsKeyPressed(KEY_A) && frameStartDirection != east)
    {
        if (snake[0].dir != east && snake[0].dir != west)
        {
            snake[0].dir = west;
        }
    }

    if (IsKeyPressed(KEY_D) && frameStartDirection != west)
    {
        if (snake[0].dir != east && snake[0].dir != west)
        {
            snake[0].dir = east;
        }
    }

    if (IsKeyPressed(KEY_SPACE))
    {
        paused = !paused;

        //restart
        if (ended)
        {
            initializeGame();
        }
    }

    if (IsKeyPressed(KEY_B))
    {
        //change the background color
        BGColorIndex = (BGColorIndex + 1) % BG_COLOR_OPTION_COUNT;
    }
}

void moveSnake(struct snakeCell* snake, int speed)
{
    for (int i = 0; i < MAX_SNAKE_LENGTH; i++)
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
    for (int i = MAX_SNAKE_LENGTH - 1; i >= 1; i--)
    {
        snake[i].dir = snake[i - 1].dir;
    }
}

void drawSnake(struct snakeCell* snake, int snakeLength, Color color)
{
    //draw the snake
    for (int i = 0; i < snakeLength; i++)
    {
        DrawCircle(snake[i].x, snake[i].y, SNAKE_CELL_RADIUS, color);
    }
}

void drawFruit(int x, int y, Color color)
{
    DrawCircle(x, y, FRUIT_RADIUS, color);
}

bool doesSnakeEatFruit(int snakeX, int snakeY, int fruitX, int fruitY, int fruitRadius)
{
    int squareDistance = ((snakeX - fruitX) * (snakeX - fruitX)) + ((snakeY - fruitY) * (snakeY - fruitY));
    int radiusSumSquared = (SNAKE_CELL_RADIUS * SNAKE_CELL_RADIUS) + (2 * SNAKE_CELL_RADIUS * fruitRadius) + (fruitRadius * fruitRadius);
    return squareDistance < radiusSumSquared;
}

void increaseSnakeLength()
{
    snakeLength++;
    snake[snakeLength - 1].isOn = true;
}

void increaseScore(int scoreAdded)
{
    score += scoreAdded;
}


bool doesSnakeDie(struct snakeCell* snake, int snakeLength)
{
    int frontX = snake[0].x;
    int frontY = snake[0].y;

    for (int i = 1; i < snakeLength; i++)
    {
        if (snake[i].x == frontX && snake[i].y == frontY)
        {
            return true;
        }
    }
    return false;
}

void drawScore(int score)
{
    snprintf(scoreDisplay, MAX_SCORE_DIGITS + 1, "%d", score);
    DrawText(scoreDisplay, (WINDOW_WIDTH * 0.25), (WINDOW_HEIGHT * 0.25), SCORE_FONT_SIZE, SCORE_FONT_COLOR);
}

bool shouldSpecialFruitSpawn()
{
    if (specialFruitSpawned)
    {
        return false;
    }
    
    int randomRoll = GetRandomValue(0, SPECIAL_FRUIT_ONE_IN_HOW_MANY_CHANCE);
    return randomRoll > (SPECIAL_FRUIT_ONE_IN_HOW_MANY_CHANCE - 1);
}

void spawnSpecialFruit()
{
    specialFruitSpawned = true;
    sFruitX = GetRandomValue(0, WINDOW_WIDTH);
    sFruitY = GetRandomValue(0, WINDOW_HEIGHT);
}


int main()
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_TITLE);
    SetTargetFPS(60);

    initializeGame();


    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BG_COLORS[BGColorIndex]);

        //cache snake's direction at the beginning of frame
        cacheFrameStartSnakeDirection();

        //accept input
        acceptInput();

        //move the snake
        if (!paused && !ended)
        {
            moveSnake(snake, DEFAULT_SPEED);
        }

        //check if the snake eats the fruit
        if (doesSnakeEatFruit(snake[0].x, snake[0].y, fruitX, fruitY, FRUIT_RADIUS)) 
        {
            increaseSnakeLength();
            increaseScore(FRUIT_SCORE);
            spawnNewFruit();
        }

        //check if the snake dies
        if (doesSnakeDie(snake, snakeLength))
        {
            ended = true;
        }

        //draw the score
        drawScore(score);


        //draw the snake
        drawSnake(snake, snakeLength, SNAKE_COLOR);

        //draw the fruit
        drawFruit(fruitX, fruitY, FRUIT_COLOR_0);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}