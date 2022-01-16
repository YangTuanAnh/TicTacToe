#include "tictactoe.h"

bool Program::isSafe()
{
    return posx >= 0 && posx < 3 && posy >= 0 && posy < 3 && tab.grid[posy][posx] == ' ';
}
void Program::checkwin()
{
    tab.grid[posy][posx] = isPlayer ? 'X' : 'O';
    tab.filled++;
    isPlayer ^= 1;

    if (tab.grid[0][posx] == tab.grid[1][posx] && tab.grid[0][posx] == tab.grid[2][posx])
        win = true;
    if (tab.grid[posy][0] == tab.grid[posy][1] && tab.grid[posy][0] == tab.grid[posy][2])
        win = true;
    if (posx == posy)
        if (tab.grid[0][0] == tab.grid[1][1] && tab.grid[0][0] == tab.grid[2][2])
            win = true;
    if ((posx == 0 && posy == 2) || (posx == 2 && posy == 0))
        if (tab.grid[0][2] == tab.grid[1][1] && tab.grid[0][2] == tab.grid[2][0])
            win = true;
}