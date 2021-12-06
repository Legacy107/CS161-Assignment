#pragma once
#include <string.h>
#include <vector>

enum Scene { MENU, CHOOSER, GAME, END, SCORE, EXIT };

struct board_option
{
    string name;
    int width, height, mines;
};

vector<board_option> board_options = {
    {"Beginner", 10, 10, 10},
    {"Intermediate", 16, 16, 40},
    {"Expert", 30, 16, 99},
}
