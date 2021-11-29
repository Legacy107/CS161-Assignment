#pragma once
#include <map>
#include <vector>
#include <fstream>
#include "../header/global.h"
#include "../header/board.h"

typedef void (*FnPtr)(struct minesawyer*);

struct minesawyer
{
    std::map<Scene, FnPtr> scenes;
    Scene current_scene = MENU;
    std::vector<std::vector<int>> board, mask;
    int width, height, mines;
    int flags = 0;
    std::pair<int, int> cursor = {0, 0};

    minesawyer();

    void add_scene(Scene id, FnPtr scene);

    void process();

    void change_scene(Scene scene);

    void create_board(int width, int height, int mines, int seed);

    // Return true if successfully loaded
    bool load_board();
};
