#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <algorithm>

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

void gen_board(std::vector<std::vector<int>> &board, int width, int height, int mines, int seed = 0)
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
        return true;
    if (board[y][x] == 0)
        mass_open(x, y, width, height, board, mask);
    else
        mask[y][x] == 1;
    return false;
}

void flag_cell(int x, int y, std::vector<std::vector<int>> &mask)
{
    if (mask[y][x] == -1)
        mask[y][x] == 0;
    else
        mask[y][x] == -1;
}

void board()
{
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
}
