#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <windows.h>

enum Scene { MENU, CHOOSER, GAME, SAW, END, SCORE, EXIT };

const std::chrono::milliseconds saw_penalty_duration(30000);

struct board_option
{
    std::string name;
    int width, height, mines;
};

const std::vector<std::vector<board_option>> board_options = {
    {
        {"Beginner", 10, 10, 10},
        {"Intermediate", 16, 16, 40},
        {"Expert", 30, 16, 99},
    },
    {
        {"Saw Beginner", 10, 10, 1},
        {"Saw Intermediate", 16, 16, 4},
        {"Saw Expert", 30, 16, 8},
    },
};

const auto BRIGHT_BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
const auto BRIGHT_RED = FOREGROUND_RED | FOREGROUND_INTENSITY;
const auto WHITE = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED;
const auto YELLOW = FOREGROUND_GREEN | FOREGROUND_RED;
const auto GREEN = FOREGROUND_GREEN;
const auto GRAY = FOREGROUND_INTENSITY;
const auto INVERSE = COMMON_LVB_REVERSE_VIDEO;
