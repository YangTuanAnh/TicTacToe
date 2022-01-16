#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "tictactoe.h"

int main()
{
    InitWindow(WIDTH, HEIGHT, "TicTacToe 💖");
    SetTargetFPS(60);
    srand(time(0));
    Program currProgram;

    while (!WindowShouldClose())
    {
        if (currProgram.tab.gen)
        {
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    currProgram.tab.grid[i][j] = ' ';
            currProgram.currWin = NONE;
            currProgram.tab.end = false;
            currProgram.tab.filled = 0;
            currProgram.tab.gen = false;
        }

        if (currProgram.tab.filled == 9)
            currProgram.tab.end = true;

        Vector2 mousePos = GetMousePosition();
        currProgram.mousex = (mousePos.x - (WIDTH - SIZE * 3) / 2) / SIZE;
        currProgram.mousey = (mousePos.y - (HEIGHT - SIZE * 3) / 2) / SIZE;

        if (!currProgram.tab.end)
        {
            if (currProgram.currTurn == AI)
            {
                bool found = false;
                while (!found)
                    for (int i = 0; i < 3 && !found; i++)
                        for (int j = 0; j < 3 && !found; j++)
                            if (currProgram.tab.grid[i][j] == ' ' && rand() % 3 == 0)
                            {
                                currProgram.tab.grid[i][j] = 'O';
                                currProgram.tab.filled++;
                                found = true;
                                if (currProgram.tab.checkwin(j, i, 'O'))
                                {
                                    currProgram.tab.end = true;
                                    currProgram.currWin = BLUEWIN;
                                }
                            }
                currProgram.currTurn = PLAYER;
            }
            else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && currProgram.isSafe() && currProgram.currTurn == PLAYER)
            {
                currProgram.tab.grid[currProgram.mousey][currProgram.mousex] = 'X';
                currProgram.tab.filled++;
                if (currProgram.tab.checkwin(currProgram.mousex, currProgram.mousey, 'X'))
                {
                    currProgram.tab.end = true;
                    currProgram.currWin = REDWIN;
                }
                currProgram.currTurn = AI;
            }
        }
        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                int posx = (WIDTH - SIZE * 3) / 2 + SIZE * j, posy = (HEIGHT - SIZE * 3) / 2 + SIZE * i;
                DrawRectangle(posx, posy, SIZE, SIZE, WHITE);
                DrawRectangleLines(posx, posy, SIZE, SIZE, LIGHTGRAY);
                DrawText(TextFormat("%c", currProgram.tab.grid[i][j]),
                         posx + SIZE * 3 / 8, posy + SIZE / 2, SIZE / 2,
                         currProgram.tab.grid[i][j] == 'X' ? RED : BLUE);
            }

        currProgram.tab.gen = GuiButton({(WIDTH - 100) / 2, HEIGHT - 40, 100, 20}, "RESET");

        switch (currProgram.currWin)
        {
        case REDWIN:
            DrawText("RED WINS!", 20, 20, 20, RED);
            break;
        case BLUEWIN:
            DrawText("BLUE WINS!", 20, 20, 20, BLUE);
            break;
        case NONE:
            if (currProgram.tab.end)
                DrawText("GAME TIED", 20, 20, 20, GREEN);
            break;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}