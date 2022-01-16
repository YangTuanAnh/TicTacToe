#include "tictactoe.h"
int main()
{
    Program currProgram;
    while (!WindowShouldClose())
    {
        Vector2 mousePos = GetMousePosition();
        int posx = (mousePos.x - (WIDTH - SIZE * 3) / 2) / SIZE, posy = (mousePos.y - (HEIGHT - SIZE * 3) / 2) / SIZE;

        if (!currProgram.win && currProgram.tab.filled < 9)
        {
            if (!currProgram.isPlayer)
            {
                while (true)
                {
                    posy = rand() % 3, posx = rand() % 3;
                    if (currProgram.isSafe(posx, posy))
                    {
                        currProgram.checkwin(posx, posy);
                        break;
                    }
                }
            }
            else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && currProgram.isSafe(posx, posy) && currProgram.isPlayer)
                currProgram.checkwin(posx, posy);
        }
        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                posx = (WIDTH - SIZE * 3) / 2 + SIZE * j, posy = (HEIGHT - SIZE * 3) / 2 + SIZE * i;
                DrawRectangle(posx, posy, SIZE, SIZE, WHITE);
                DrawRectangleLines(posx, posy, SIZE, SIZE, LIGHTGRAY);
                DrawText(TextFormat("%c", currProgram.tab.grid[i][j]), posx + SIZE * 3 / 8, posy + SIZE / 2, SIZE / 2, currProgram.tab.grid[i][j] == 'X' ? RED : BLUE);
            }

        if (button({(WIDTH - 100) / 2, HEIGHT - 40, 100, 20}, "RESET"))
        {
            currProgram.win = currProgram.tab.filled = 0;
            std::fill(&currProgram.tab.grid[0][0], &currProgram.tab.grid[0][0] + 9, ' ');
        }

        if (currProgram.win)
            !currProgram.isPlayer ? DrawText("RED WINS", 20, 20, 20, RED) : DrawText("BLUE WINS", 20, 20, 20, BLUE);
        else if (currProgram.tab.filled == 9)
            DrawText("GAME TIED", 20, 20, 20, GREEN);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}