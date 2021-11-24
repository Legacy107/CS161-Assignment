#include "../header/global.h"
#include "../header/minesawyer.h"
#include "../header/board.h"
#include <map>
#include <vector>

typedef void (*FnPtr)(struct minesawyer*);

minesawyer::minesawyer(){};

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

void minesawyer::create_board(int width, int height, int mines)
{
    this->width = width;
    this->height = height;
    this->mines = mines;

    for (int i = 0; i < height; i++)
    {
        std::vector<int> board_row(width);
        board.push_back(board_row);
    }
    gen_board(board, width, height, mines);

    for (int i = 0; i < height; i++)
    {
        std::vector<int> mask_row(width);
        mask.push_back(mask_row);
    }
}