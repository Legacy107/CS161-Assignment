#include "../header/global.h"
#include "../header/util.h"
#include "../header/minesawyer.h"
#include "../header/board.h"
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <map>
#include <vector>

void update_timer(struct minesawyer *game)
{
    set_cursor(18, 0);
    std::cout << "\t\tTime: " << format_duration(get_duration(game->start_time)) << "       ";
}

void draw_instruction(struct minesawyer *game)
{
    set_cursor(0, game->height + 5);
    std::cout << "Move (arrow kes)" << std::endl;
    std::cout << "Open (O)" << std::endl;
    std::cout << "Flag (F)" << std::endl;
    std::cout << "Save and exit (M)" << std::endl;
}

void game_draw(struct minesawyer *game)
{
    set_cursor(0, 0);
    std::cout << "Remaining Flags: " << std::setw(2) << game->mines - game->flags;

    set_cursor(0, 2);
    draw_board(game->width, game->height, game->board, game->mask, game->prev_mask, game->cursor);
}

bool game_input(struct minesawyer *game, std::map<int, bool> &prev_key_state)
{
    bool flag = false;
    std::map<int, bool> key_state;
    std::vector<int> keys = {VK_UP, VK_DOWN, VK_RIGHT, VK_LEFT, 'O', 'F', 'M'};
    for (auto i : keys)
        key_state[i] = GetKeyState(i) & 0x8000;

    if (!key_state[VK_UP] && prev_key_state[VK_UP])
    {
        if (is_valid_cell(game->cursor.first, game->cursor.second - 1, game->width, game->height))
        {
            game->cursor.second -= 1;
            flag = true;
        }
    }
    else if (!key_state[VK_DOWN] && prev_key_state[VK_DOWN])
    {
        if (is_valid_cell(game->cursor.first, game->cursor.second + 1, game->width, game->height))
        {
            game->cursor.second += 1;
            flag = true;
        }
    }
    else if (!key_state[VK_RIGHT] && prev_key_state[VK_RIGHT])
    {
        if (is_valid_cell(game->cursor.first + 1, game->cursor.second, game->width, game->height))
        {
            game->cursor.first += 1;
            flag = true;
        }
    }
    else if (!key_state[VK_LEFT] && prev_key_state[VK_LEFT])
    {
        if (is_valid_cell(game->cursor.first - 1, game->cursor.second, game->width, game->height))
        {
            game->cursor.first -= 1;
            flag = true;
        }
    }
    else if (!key_state['O'] && prev_key_state['O'])
    {
        if (game->mask[game->cursor.second][game->cursor.first] == 0)
        {
            if (open_cell(game->cursor.first, game->cursor.second, game->width, game->height, game->board, game->mask))
                game->change_scene(END);
            flag = true;
        }
    }
    else if (!key_state['F'] && prev_key_state['F'])
    {
        if (game->mask[game->cursor.second][game->cursor.first] != 1)
        {
            flag_cell(game->cursor.first, game->cursor.second, game->flags, game->mask);
            flag = true;
        }
    }
    else if (!key_state['M'] && prev_key_state['M'])
    {
        save_board(game->width, game->height, game->mines, game->seed, game->flags, get_duration(game->start_time), game->mask);
        game->change_scene(MENU);
        flag = true;
    }

    prev_key_state = key_state;

    return flag;
}

void game_scene(struct minesawyer *game)
{
    std::map<int, bool> prev_key_state;
    system("cls");
    draw_instruction(game);
    while (true)
    {
        game_draw(game);

        while (!game_input(game, prev_key_state))
        {
            update_timer(game);
        }

        if (check_win(game->flags, game->mines, game->width, game->height, game->board, game->mask))
            game->change_scene(END);

        if (game->current_scene != GAME)
            return;
    }
}