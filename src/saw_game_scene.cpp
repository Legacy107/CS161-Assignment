#include "../header/global.h"
#include "../header/util.h"
#include "../header/minesawyer.h"
#include "../header/board.h"
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <map>
#include <vector>

void saw_update_timer(struct minesawyer *game)
{
    set_cursor(18, 0);
    std::cout << "\t\tTime: " << format_duration(get_duration(game->start_time)) << "       ";
}

void saw_draw_instruction(struct minesawyer *game)
{
    set_cursor(0, game->height + 5);
    std::cout << "Minesawyer's rule:" << std::endl;
    std::cout << "Each cell has either a mine or a number indicating the Manhattan distance to the nearest mine." << std::endl;
    std::cout << "To win the game, you have to open all the cells that have mines inside." << std::endl;
    std::cout << "For each cell you open that does not contain a mine, a 30 seconds penalty will be applied." << std::endl;
    std::cout << "GLHF! :D" << std::endl << std::endl;
    std::cout << "Move (arrow kes)" << std::endl;
    std::cout << "Open (O)" << std::endl;
    std::cout << "Flag (F)" << std::endl;
    std::cout << "Exit (M)" << std::endl;
}

void saw_game_draw(struct minesawyer *game, int remaning_mines)
{
    set_cursor(0, 0);
    std::cout << "Remaining Mines: " << std::setw(2) << remaning_mines;

    set_cursor(0, 2);
    draw_board(game->width, game->height, game->board, game->mask, game->prev_mask, game->cursor);
}

bool saw_game_input(struct minesawyer *game, std::map<int, bool> &prev_key_state, int &remaning_mines)
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
            {
                --remaning_mines;
                if (!remaning_mines)
                    game->change_scene(END);
            }
            else
                game->start_time = game->start_time - saw_penalty_duration;

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
        game->change_scene(MENU);
        flag = true;
    }

    prev_key_state = key_state;

    return flag;
}

void saw_game_scene(struct minesawyer *game)
{
    int remaning_mines = game->mines;
    std::map<int, bool> prev_key_state;
    system("cls");
    saw_draw_instruction(game);
    while (true)
    {
        saw_game_draw(game, remaning_mines);

        while (!saw_game_input(game, prev_key_state, remaning_mines))
        {
            saw_update_timer(game);
        }

        if (game->current_scene != SAW)
            return;
    }
}
