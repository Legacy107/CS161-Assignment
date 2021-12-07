#include "../header/global.h"
#include "../header/minesawyer.h"
#include "../header/board.h"
#include <map>
#include <vector>
#include <fstream>
#include <chrono>

typedef void (*FnPtr)(struct minesawyer*);

minesawyer::minesawyer(){}

void minesawyer::add_scene(Scene id, FnPtr scene)
{
    scenes[id] = scene;
}

void minesawyer::process()
{
    while (current_scene != EXIT)
        scenes[current_scene](this);
}

void minesawyer::change_scene(Scene scene)
{
    current_scene = scene;
}

void minesawyer::reset_board()
{
    flags = 0;
    cursor = {0, 0};
    board.clear();
    mask.clear();
}

void minesawyer::get_blank_board(int width, int height, int mines, int seed)
{
    this->width = width;
    this->height = height;
    this->mines = mines;
    this->seed = seed;

    for (int i = 0; i < height; i++)
    {
        std::vector<int> board_row(width);
        board.push_back(board_row);
    }

    for (int i = 0; i < height; i++)
    {
        std::vector<int> mask_row(width);
        mask.push_back(mask_row);
    }
}

void minesawyer::create_board(int width, int height, int mines, int seed)
{
    reset_board();

    get_blank_board(width, height, mines, seed);

    if (mode == 0)
        gen_board(board, width, height, mines, this->seed);
    else if (mode == 1)
        saw_gen_board(board, width, height, mines, this->seed);

    start_time = std::chrono::steady_clock::now();
}

bool minesawyer::load_board()
{
    int duration = 0;
    std::ifstream board_file("board.txt");

    // No board is found
    if (!(board_file >> width >> height >> mines >> seed >> flags >> duration))
        return false;

    create_board(width, height, mines, seed);

    this->flags = flags;
    std::chrono::milliseconds chrono_duration(duration);
    start_time = start_time - chrono_duration;

    // Read mask
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            board_file >> mask[i][j];

    board_file.close();
    return true;
}
