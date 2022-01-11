#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <time.h>
#include <stdio.h>
const int WIDTH = 800, HEIGHT = 600;
const int SIZE = 128;

typedef enum Turn
{
    PLAYER = 0,
    AI
} Turn;

int grid[3][3], mousex, mousey;
bool gen = true, full = false, redwin = false, bluewin = false, end = false;

bool isSafe()
{
    return mousex >= 0 && mousex < 3 && mousey >= 0 && mousey < 3;
}
bool checkwin(int x, int y, int turn)
{
    if (grid[0][x] == turn && grid[1][x] == turn && grid[2][x] == turn)
        return true;
    if (grid[y][0] == turn && grid[y][1] == turn && grid[y][2] == turn)
        return true;
    if (x == y)
        if (grid[0][0] == turn && grid[1][1] == turn && grid[2][2] == turn)
            return true;
    if ((x == 0 && y == 2) || (x == 2 && y == 0))
        if (grid[0][2] == turn && grid[1][1] == turn && grid[2][0] == turn)
            return true;
    return false;
}
int main()
{
    InitWindow(WIDTH, HEIGHT, "TicTacToe 💖");
    SetTargetFPS(60);

    Turn currTurn = PLAYER;

    while (!WindowShouldClose())
    {

        if (gen)
        {
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    grid[i][j] = 0;
            gen = false;
        }

        full = true;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (grid[i][j] == 0)
                    full = false;

        Vector2 mousePos = GetMousePosition();
        mousex = (mousePos.x - (WIDTH - SIZE * 3) / 2) / SIZE;
        mousey = (mousePos.y - (HEIGHT - SIZE * 3) / 2) / SIZE;

        if (!end)
        {
            if (currTurn == AI && !full)
            {
                bool found = false;
                srand(time(0));
                while (!found)
                    for (int i = 0; i < 3 && !found; i++)
                        for (int j = 0; j < 3; j++)
                            if (grid[i][j] == 0 && rand() % 3 == 0)
                            {
                                grid[i][j] = 2;
                                if (checkwin(j, i, 2))
                                {
                                    end = true;
                                    bluewin = true;
                                }
                                found = true;
                                break;
                            }
                currTurn = PLAYER;
            }
            else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
                     isSafe() &&
                     grid[mousey][mousex] == 0 &&
                     currTurn == PLAYER)
            {
                grid[mousey][mousex] = 1;
                if (checkwin(mousex, mousey, 1))
                {
                    end = true;
                    redwin = true;
                }
                currTurn = AI;
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                int posx = (WIDTH - SIZE * 3) / 2 + SIZE * j;
                int posy = (HEIGHT - SIZE * 3) / 2 + SIZE * i;
                DrawRectangle(posx, posy, SIZE, SIZE, WHITE);
                DrawRectangleLines(posx, posy, SIZE, SIZE, LIGHTGRAY);
                if (grid[i][j] == 1)
                    DrawText("X", posx + SIZE * 3 / 8, posy + SIZE / 2, SIZE / 2, RED);
                if (grid[i][j] == 2)
                    DrawText("O", posx + SIZE * 3 / 8, posy + SIZE / 2, SIZE / 2, BLUE);
            }

        if (GuiButton({(WIDTH - 100) / 2, HEIGHT - 40, 100, 20}, "RESET"))
        {
            gen = true;
            redwin = false;
            bluewin = false;
            end = false;
        }

        if (redwin)
            DrawText("RED WINS!", 20, 20, 20, RED);
        if (bluewin)
            DrawText("BLUE WINS!", 20, 20, 20, BLUE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}