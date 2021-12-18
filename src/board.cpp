#include "../header/global.h"
#include "../header/board.h"
#include "../header/util.h"
#include <iostream>
#include <vector>
#include <windows.h>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <queue>
#include <cmath>

bool is_valid_cell(int x, int y, int width, int height)
{
    return 0 <= x && x < width && 0 <= y && y < height;
}

int manhattan_distance(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

int nearby_mines
(
    int x, int y, int width, int height,
    const std::vector<std::vector<int>> &board
)
{
    int count = 0;
    for (int i = y - 1; i <= y + 1; i++)
        for (int j = x - 1; j <= x + 1; j++)
            if (is_valid_cell(j, i, width, height) && board[i][j] == -1)
                count++;

    return count;
}

void gen_mines
(
    std::vector<std::vector<int>> &board,
    int width, int height, int mines, int &seed
)
{
    if (!seed)
        seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);

    std::vector<std::pair<int, int>> cells;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            cells.push_back({i, j});

    shuffle(cells.begin(), cells.end(), rng);

    for (int i = 0; i < mines; i++)
        board[cells[i].first][cells[i].second] = -1;
}

void gen_board
(
    std::vector<std::vector<int>> &board,
    int width, int height, int mines, int &seed
)
{
    gen_mines(board, width, height, mines, seed);

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (board[i][j] != -1)
                board[i][j] = nearby_mines(j, i, width, height, board);
}

void saw_gen_board
(
    std::vector<std::vector<int>> &board,
    int width, int height, int mines, int &seed
)
{
    const int drow[4] = {-1, 0, 0, 1};
    const int dcol[4] = {0, -1, 1, 0};
    std::queue<std::pair<int, int>> cell_queue;

    gen_mines(board, width, height, mines, seed);

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            if (board[i][j] == -1)
                cell_queue.push({i, j});

    while(!cell_queue.empty())
    {
        int y = cell_queue.front().first;
        int x = cell_queue.front().second;
        cell_queue.pop();

        for (int i = 0; i < 4; i++)
        {
            int row = y + drow[i];
            int col = x + dcol[i];

            if (is_valid_cell(col, row, width, height) && board[row][col] == 0)
            {
                if (board[y][x] == -1)
                    board[row][col] = 1;
                else
                    board[row][col] = board[y][x] + 1;

                cell_queue.push({row, col});
            }
        }
    }
}

bool open_cell
(
    int x, int y, int width, int height,
    const std::vector<std::vector<int>> &board,
    std::vector<std::vector<int>> &mask
)
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

void mass_open
(
    int x, int y, int width, int height,
    const std::vector<std::vector<int>> &board,
    std::vector<std::vector<int>> &mask
)
{
    const int drow[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dcol[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    mask[y][x] = 1;

    if (board[y][x])
        return;

    for (int i = 0; i < 8; i++)
    {
        int row = y + drow[i];
        int col = x + dcol[i];
        if (
            is_valid_cell(col, row, width, height)
            && board[row][col] != -1 && !mask[row][col]
        )
            mass_open(col, row, width, height, board, mask);
    }
}

bool check_win
(
    int flags, int mines, int width, int height,
    const std::vector<std::vector<int>> &board,
    const std::vector<std::vector<int>> &mask
)
{
    if (flags != mines)
        return false;

    for (int row = 0; row < height; row++)
        for (int column = 0; column < width; column++)
            if (mask[row][column] == 0 && board[row][column] != -1)
                return false;

    return true;
}

void draw_board
(
    int width, int height,
    const std::vector<std::vector<int>> &board,
    const std::vector<std::vector<int>> &mask,
    std::vector<std::vector<int>> &prev_mask,
    std::pair<int, int> cursor
)
{
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h_console, BRIGHT_BLUE);

    std::cout << "  ";
    for (int column = 1; column <= width; column++)
        std::cout << std::setw(3) << column;

    std::cout << "\n";
    for (int row = 0; row < height; row++)
    {
        SetConsoleTextAttribute(h_console, BRIGHT_BLUE);
        std::cout << static_cast<char>('A' + row) << " ";

        for (int column = 0; column < width; column++)
        {
            if (
                mask[row][column] != prev_mask[row][column]
                || manhattan_distance(column, row, cursor.first, cursor.second) <= 1
            )
            {
                auto background = (
                    (cursor.first == column && cursor.second == row)
                    ? INVERSE
                    : 0
                );

                prev_mask[row][column] = mask[row][column];

                if (mask[row][column] == -1)
                {
                    SetConsoleTextAttribute(h_console, background | YELLOW);
                    std::cout << std::setw(3) << 'F';
                }
                else if (!mask[row][column])
                {
                    SetConsoleTextAttribute(h_console, background | WHITE);
                    std::cout << std::setw(3) << '-';
                }
                else if (board[row][column] == -1)
                {
                    SetConsoleTextAttribute(h_console, background | BRIGHT_RED);
                    std::cout << std::setw(3) << "*";
                }
                else if (board[row][column] == 0)
                {
                    SetConsoleTextAttribute(h_console, background | GRAY);
                    std::cout << std::setw(3) << board[row][column];
                }
                else
                {
                    SetConsoleTextAttribute(h_console, background | GREEN);
                    std::cout << std::setw(3) << board[row][column];
                }
            }
            else
            {
                COORD console_cursor = get_cursor();
                set_cursor(console_cursor.X + 3, console_cursor.Y);
            }
        }
        std::cout << "\n";
    }
    std::cout << std::flush;
    SetConsoleTextAttribute(h_console, WHITE);
}

void save_board
(
    int width, int height, int mines, int seed, int flags, int duration,
    const std::vector<std::vector<int>> &mask
)
{
    std::ofstream MyFile("board.txt");

    MyFile << width << " " << height << " " << mines << " " << seed << " "
           << flags << " " << duration << "\n";

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            MyFile << mask[i][j] << "\t";
        MyFile << "\n";
    }

    MyFile.close();
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
    int seed = 0;

    gen_board(board, 4, 4, 5, seed);
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
            std::cout << board[i][j] << " ";
        std::cout << std::endl;
    }

    board = {{1, 2}, {-1, -1}};
    std::vector<std::vector<int>> mask = {{1, 0}, {-1, 1}};
    std::vector<std::vector<int>> prev_mask = {{-2, -2}, {-2, -2}};
    draw_board(2, 2, board, mask, prev_mask, {0, 1});
}
