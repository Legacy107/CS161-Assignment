#pragma once
#include <vector>

// fill the board vector with 0
// if seed is 0, generate a random seed
// generate a vector<pair<int,int>> containing every cells
// use shuffle() to pick random cells that has mines
// for cells that don't has mines, count the number of mines around them
void gen_board(vector<vector<int>> &board, int width, int height, int mines, int seed = 0);

// return true if board[x][y] has a mine
// else if board[x][y] is 0, call mass_open() and return false
// else set mask[x][y] to 1 and return false
bool open_cell(int x, int y, vector<vector<int>> &board, vector<vector<int>> &mask);

// open all blank cells that are adjacent to (x,y) and 1 outer layer of that area
// set mask[x][y] to 1 to open it
void mass_open(int x, int y, vector<vector<int>> &board, vector<vector<int>> &mask);

// set mask[x][y] to 0 to if the cell is already flagged
// else set mask[x][y] to -1
void flag_cell(int x, int y, vector<vector<int>> &mask);

void board();
