#include "tictactoe.h"

bool Program::isSafe(int posx, int posy)
{
    return posx >= 0 && posx < 3 && posy >= 0 && posy < 3 && tab.grid[posy][posx] == ' ';
}
void Program::checkwin(int posx, int posy)
{
    tab.grid[posy][posx] = isPlayer ? 'X' : 'O';
    tab.filled++;
    isPlayer ^= 1;

    if ((tab.grid[0][posx] == tab.grid[1][posx] && tab.grid[0][posx] == tab.grid[2][posx]) ||
        (tab.grid[posy][0] == tab.grid[posy][1] && tab.grid[posy][0] == tab.grid[posy][2]) ||
        (tab.grid[0][0] == tab.grid[1][1] && tab.grid[0][0] == tab.grid[2][2] && posx == posy) ||
        (tab.grid[0][2] == tab.grid[1][1] && tab.grid[0][2] == tab.grid[2][0] && posx == 2 - posy))
        win = true;
}