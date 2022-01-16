#include "tictactoe.h"

bool Program::isSafe()
{
    return mousex >= 0 && mousex < 3 && mousey >= 0 && mousey < 3 && tab.grid[mousey][mousex] == ' ';
}
bool Table::checkwin(int x, int y, char turn)
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