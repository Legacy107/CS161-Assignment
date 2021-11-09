#include "../header/board.h"
#include <vector>
#include <map>
#include <iostream>

using namespace std;

bool check_win(int flags, int mines, int width, int height, vector<vector<int>> &board, vector<vector<int>> &mask)
{
    if (flags != mines)
        return false;
    for (int row = 0; row < height; row++)
        for (int column = 0; column < width; column++)
            if (mask[row][column] == -1 && board[row][column] != -1)
                return false;
    return true;
}

void draw_board(int width, int height, vector<vector<int>> &board, vector<vector<int>> &mask)
{
    cout << "  ";
    for (int column = 1; column <= width; column++)
        cout << column;

    cout << endl;
    for (int row = 0; row < height; row++)
    {
        cout << static_cast<char>('A' + row) << " ";
        for (int column = 0; column < width; column++)
        {
            if (mask[row][column] == -1)
                cout << 'F';
            else if (!mask[row][column])
                cout << '-';
            else if (board[row][column] == -1)
                cout << "*";
            else
                cout << board[row][column];
        }
        cout << endl;
    }
}

void board()
{
    // Driver code for testing
    vector<vector<int>> board = {{1, 2}, {-1, -1}};
    vector<vector<int>> mask = {{1, 0}, {-1, 1}};
    draw_board(2, 2, board, mask);
}
