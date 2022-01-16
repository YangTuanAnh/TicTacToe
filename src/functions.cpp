#include "tictactoe.h"

bool Program::isSafe(int posx, int posy)
{
    return posx >= 0 && posx < 3 && posy >= 0 && posy < 3 && tab.grid[posy][posx] == ' ';
}
void Program::checkwin(int posx, int posy)
{
    tab.grid[posy][posx] = isPlayer ? 'X' : 'O';
    tab.filled++;

    if ((tab.grid[0][posx] == tab.grid[1][posx] && tab.grid[0][posx] == tab.grid[2][posx]) ||
        (tab.grid[posy][0] == tab.grid[posy][1] && tab.grid[posy][0] == tab.grid[posy][2]) ||
        (tab.grid[0][0] == tab.grid[1][1] && tab.grid[0][0] == tab.grid[2][2] && posx == posy) ||
        (tab.grid[0][2] == tab.grid[1][1] && tab.grid[0][2] == tab.grid[2][0] && posx == 2 - posy))
        win = true;

    if (!win)
        isPlayer ^= 1;
}
bool button(Rectangle bounds, const char *text)
{
    Vector2 mousePoint = GetMousePosition();

    bool pressed = (CheckCollisionPointRec(mousePoint, bounds) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON));

    DrawRectangleRec(bounds, LIGHTGRAY);
    DrawText(text, bounds.x + (bounds.width - bounds.height / 3 * strlen(text)) / 2,
             bounds.y + bounds.height / 4, bounds.height / 2, GRAY);

    return pressed;
}