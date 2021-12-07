#pragma once
#include <iostream>
#include <vector>
#include <windows.h>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <queue>

// check if a cell is inside the board
bool is_valid_cell(int x, int y, int width, int height);

// count all nearby mines of a cell
int nearby_mines(int x, int y, int width, int height, std::vector<std::vector<int>> &board);

// if seed is 0, generate a random seed
// generate a vector<pair<int,int>> containing every cells
// use shuffle() to pick random cells that has mines
void gen_mines(std::vector<std::vector<int>> &board, int width, int height, int mines, int &seed);

// fill the board vector with 0
// call gen_mines()
// for cells that don't has mines, count the number of mines around them
void gen_board(std::vector<std::vector<int>> &board, int width, int height, int mines, int &seed);

// call gen_mines()
// for cells that don't has mines, calculate the distance to the nearest mines
void saw_gen_board(std::vector<std::vector<int>> &board, int width, int height, int mines, int &seed);

// return true if board[x][y] has a mine
// else if board[x][y] is 0, call mass_open() and return false
// else set mask[x][y] to 1 and return false
bool open_cell(int x, int y, int width, int height, std::vector<std::vector<int>> &board, std::vector<std::vector<int>> &mask);

// open all blank cells that are adjacent to (x,y) and 1 outer layer of that area
// set mask[x][y] to 1 to open it
void mass_open(int x, int y, int width, int height, std::vector<std::vector<int>> &board, std::vector<std::vector<int>> &mask);

// set mask[x][y] to 0 to if the cell is already flagged
// else set mask[x][y] to -1
void flag_cell(int x, int y, int &flags, std::vector<std::vector<int>> &mask);

bool check_win(int flags, int mines, int width, int height, std::vector<std::vector<int>> &board, std::vector<std::vector<int>> &mask);

void draw_board(int width, int height, std::vector<std::vector<int>> &board, std::vector<std::vector<int>> &mask, std::pair<int, int> cursor = { -1, -1});

// write board to board.txt
// format:
// width height mines seed flags duration
// mask[0][0] ... mask[0][width]
//    :					:
// mask[height][0] ... mask[width][height]
void save_board(int width, int height, int mines, int seed, int flags, int duration, std::vector<std::vector<int>> &mask);

void board();
