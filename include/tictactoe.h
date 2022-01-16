#pragma once
#include <raylib.h>
#include <algorithm>
#include <time.h>
#include <stdio.h>
#include <cstring>
const int WIDTH = 800, HEIGHT = 600, SIZE = 128;

struct Table
{
    char grid[3][3], filled;

    Table() : filled(0)
    {
        std::fill(&grid[0][0], &grid[0][0] + 9, ' ');
    }
};
struct Program
{
    Table tab;
    bool isPlayer;
    bool win;

    Program() : isPlayer(true)
    {
        InitWindow(WIDTH, HEIGHT, "TicTacToe 💖");
        SetTargetFPS(60);
        srand(time(0));
    }

    bool isSafe(int, int);
    void checkwin(int, int);
};

bool button(Rectangle, const char *);