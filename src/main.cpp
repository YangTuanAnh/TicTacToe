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
        if (!currProgram.tab.filled)
            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                    currProgram.tab.grid[i][j] = ' ';

        Vector2 mousePos = GetMousePosition();
        currProgram.posx = (mousePos.x - (WIDTH - SIZE * 3) / 2) / SIZE;
        currProgram.posy = (mousePos.y - (HEIGHT - SIZE * 3) / 2) / SIZE;

        if (!currProgram.win && currProgram.tab.filled < 9)
        {
            if (!currProgram.isPlayer)
            {
                while (true)
                {
                    currProgram.posy = rand() % 3, currProgram.posx = rand() % 3;
                    if (currProgram.isSafe())
                    {
                        currProgram.checkwin();
                        break;
                    }
                }
            }
            else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && currProgram.isSafe() && currProgram.isPlayer)
                currProgram.checkwin();
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

        if (GuiButton({(WIDTH - 100) / 2, HEIGHT - 40, 100, 20}, "RESET"))
            currProgram.win = currProgram.tab.filled = 0;

        if (currProgram.win)
            !currProgram.isPlayer ? DrawText("RED WINS", 20, 20, 20, RED) : DrawText("BLUE WINS", 20, 20, 20, BLUE);
        else if (currProgram.tab.filled == 9)
            DrawText("GAME TIED", 20, 20, 20, GREEN);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}