#pragma once
#include <vector>

// output instruction: y to start or n to quit
// get and validate input
// return true if y and false if n
bool start_input();

// output instruction and example (A1 -> open, A1F -> flag or unflag)
// get and validate input (if the cell is already open -> invalid)
// convert to numbers A->0 1->0
// if of open type return {{0, 0}, 0}
// if of flag type return {{0, 0}, 1}
std::pair<std::pair<int, int>, bool> cell_input(int width, int height, std::vector<std::vector<int>> &mask);

void input();
