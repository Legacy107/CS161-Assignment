#pragma once
#include <map>
#include <vector>
#include <fstream>
#include <chrono>
#include "../header/global.h"
#include "../header/board.h"

typedef void (*FnPtr)(struct minesawyer*);

struct minesawyer
{
    std::map<Scene, FnPtr> scenes;
    Scene current_scene = MENU;
    std::vector<std::vector<int>> board, mask;
    int width, height, mines, seed;
    int flags = 0;
    int mode = 0; // 0: minesweeper     1: minesawyer
    std::pair<int, int> cursor = {0, 0};
    std::chrono::steady_clock::time_point start_time;

    minesawyer();

    void add_scene(Scene id, FnPtr scene);

    void process();

    void change_scene(Scene scene);

    void reset_board();

    void get_blank_board(int width, int height, int mines, int seed);

    void create_board(int width, int height, int mines, int seed = 0);

    // Return true if successfully loaded
    bool load_board();
};
