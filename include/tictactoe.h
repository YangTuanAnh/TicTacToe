#pragma once
#include <raylib.h>
#include <time.h>
#include <stdio.h>
const int WIDTH = 800, HEIGHT = 600, SIZE = 128;

struct Table
{
    char grid[3][3], filled;

    Table() : filled(0) {}
};
struct Program
{
    Table tab;
    bool isPlayer;
    bool win;

    Program() : isPlayer(true) {}

    bool isSafe(int, int);
    void checkwin(int, int);
};