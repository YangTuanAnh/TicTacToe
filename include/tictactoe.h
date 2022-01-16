#pragma once
#include <raylib.h>
#include <time.h>
#include <stdio.h>
const int WIDTH = 800, HEIGHT = 600, SIZE = 128;

typedef enum Turn
{
    PLAYER = 0,
    AI
} Turn;

typedef enum Win
{
    NONE = 0,
    REDWIN,
    BLUEWIN
} Win;

struct Table
{
    char grid[3][3], filled;
    bool gen, end;

    Table() : gen(true), end(false) {}

    bool checkwin(int, int, char);
};
struct Program
{
    int mousex, mousey;
    Table tab;
    Turn currTurn;
    Win currWin;

    Program() : currTurn(PLAYER) {}

    bool isSafe();
};