#include "../header/global.h"
#include "../header/minesawyer.h"
#include "../header/board.h"
#include <iostream>
#include <windows.h>

void game_draw(struct minesawyer* game)
{
    cout << "Use the arrow keys to move" << endl;
    cout << "To open a cell, press O" << endl;
    cout << "To flag a cell, press F" << endl;
    cout << "To go back, press B " << endl;
}

bool game_input(struct minesawyer* game)
{
    if (GetKeyState(VK_UP) & 0x8000)
    {
        if (is_valid_cell(game->cursor.first, game->cursor.second - 1, game->width, game->height))
        {
            game->cursor.second -= 1;
        }
        return true;
    }
    else if (GetKeyState(VK_DOWN) & 0x8000)
    {
        if (is_valid_cell(game->cursor.first, game->cursor.second + 1, game->width, game->height))
        {
            game->cursor.second += 1;
        }
        return true;
    }
    else if (GetKeyState(VK_RIGHT) & 0x8000)
    {
        if (is_valid_cell(game->cursor.first + 1, game->cursor.second, game->width, game->height))
        {
            game->cursor.first += 1;
        }
        return true;
    }
    else if (GetKeyState(VK_LEFT) & 0x8000)
    {
        if (is_valid_cell(game->cursor.first - 1, game->cursor.second, game->width, game->height))
        {
            game->cursor.first -= 1;
        }
        return true;
    }
    else if (GetKeyState('O') & 0x8000)
    {
        if (game->mask[game->cursor.first][game->cursor.second] == 0)
        {
            if (open_cell(game->cursor.first, game->cursor.second, game->width, game->height, game->board, game->mask))
                minesawyer::change_scene(MENU);
        }
        return true;
    }
    else if (GetKeyState('F') & 0x8000)
    {
        if (game->mask[game->cursor.first][game->cursor.second] == 0)
            flag_cell(game->cursor.first, game->cursor.second, game->flags, game->mask);
        return true;
    }
    else if (GetKeyState('B') & 0x8000)
    {
        save_board(game->width, game->height, game->mines, game->seed, game->mask);
        minesawyer::change_scene(MENU);
        return true;
    }
    else return false;
}

void game_scene(struct minesawyer *game)
{
    while (true)
    {
        game_draw(game);
        while (!game_input(game)) {}
        if (game->current_scene != GAME)
            return;
    }
}