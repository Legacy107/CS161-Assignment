#include "../header/board.h"
#include <iostream>
#include <vector>
#include <windows.h>
#include <ctime>
#include <random>
#include <algorithm>
#include <iomanip>

bool is_valid_cell(int x, int y, int width, int height)
{
    return 0 <= x && x < width && 0 <= y && y < height;
}

int nearby_mines(int x, int y, int width, int height, std::vector<std::vector<int>> &board)
{
    int count = 0;
    for (int i = y - 1; i <= y + 1; i++)
    {
        for (int j = x - 1; j <= x + 1; j++)
        {
            if (is_valid_cell(j, i, width, height) && board[i][j] == -1)
                count++;
        }
    }
    return count;
}

void gen_board(std::vector<std::vector<int>> &board, int width, int height, int mines, int seed)
{
    if (seed == 0)
        srand(time(0));

    std::vector<std::pair<int, int>> cells;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cells.push_back({i, j});
        }
    }
    random_shuffle(cells.begin(), cells.end());
    for (int i = 0; i < mines; i++)
    {
        board[cells[i].first][cells[i].second] = -1;
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (board[i][j] != -1)
                board[i][j] = nearby_mines(j, i, width, height, board);
        }
    }
}

bool open_cell(int x, int y, int width, int height, std::vector<std::vector<int>> &board, std::vector<std::vector<int>> &mask)
{
    if (board[y][x] == -1)
    {
        mask[y][x] = 1;
        return true;
    }
    if (board[y][x] == 0)
        mass_open(x, y, width, height, board, mask);
    else
        mask[y][x] = 1;
    return false;
}

void flag_cell(int x, int y, int &flags, std::vector<std::vector<int>> &mask)
{
    if (mask[y][x] == -1)
    {
        mask[y][x] = 0;
        --flags;
    }
    else
    {
        mask[y][x] = -1;
        ++flags;
    }
}

void mass_open(int x, int y, int width, int height, std::vector<std::vector<int>> &board, std::vector<std::vector<int>> &mask)
{
    const int drow[4] = {-1, 0, 0, 1};
    const int dcol[4] = {0, -1, 1, 0};

    mask[y][x] = 1;

    if (board[y][x])
        return;

    for (int i = 0; i < 4; i++)
    {
        int row = y + drow[i];
        int col = x + dcol[i];
        if (is_valid_cell(col, row, width, height) && board[row][col] != -1 && !mask[row][col])
            mass_open(col, row, width, height, board, mask);
    }
}

bool check_win(int flags, int mines, int width, int height, std::vector<std::vector<int>> &board, std::vector<std::vector<int>> &mask)
{
    if (flags != mines)
        return false;
    for (int row = 0; row < height; row++)
        for (int column = 0; column < width; column++)
            if (mask[row][column] == -1 && board[row][column] != -1)
                return false;
    return true;
}

void draw_board(int width, int height, std::vector<std::vector<int>> &board, std::vector<std::vector<int>> &mask)
{
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h_console, FOREGROUND_BLUE);
    std::cout << "  ";
    for (int column = 1; column <= width; column++)
        std::cout << std::setw(3) << column;

    std::cout << std::endl;
    for (int row = 0; row < height; row++)
    {
        SetConsoleTextAttribute(h_console, FOREGROUND_BLUE);
        std::cout << static_cast<char>('A' + row) << " ";
        for (int column = 0; column < width; column++)
        {
            if (mask[row][column] == -1)
            {
                SetConsoleTextAttribute(h_console, FOREGROUND_GREEN | FOREGROUND_RED);
                std::cout << std::setw(3) << 'F';
            }
            else if (!mask[row][column])
            {
                SetConsoleTextAttribute(h_console, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
                std::cout << std::setw(3) << '-';
            }
            else if (board[row][column] == -1)
            {
                SetConsoleTextAttribute(h_console, FOREGROUND_RED);
                std::cout << std::setw(3) << "*";
            }
            else
            {
                SetConsoleTextAttribute(h_console, FOREGROUND_GREEN);
                std::cout << std::setw(3) << board[row][column];
            }
        }
        std::cout << std::endl;
    }
    SetConsoleTextAttribute(h_console, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
}

void board()
{
    // Driver code for testing
    std::vector<std::vector<int>> board = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    };
    gen_board(board, 4, 4, 5);
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
            std::cout << board[i][j] << " ";
        std::cout << std::endl;
    }

    board = {{1, 2}, {-1, -1}};
    std::vector<std::vector<int>> mask = {{1, 0}, {-1, 1}};
    draw_board(2, 2, board, mask);
}
