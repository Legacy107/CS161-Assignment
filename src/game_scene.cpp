#include "../header/global.h"
#include "../header/util.h"
#include "../header/minesawyer.h"
#include "../header/board.h"
#include <iostream>
#include <windows.h>
#include <iomanip>

void update_timer(struct minesawyer *game)
{
    set_cursor(18, 0);
    std::cout << "\t\tTime: " << format_duration(get_duration(game->start_time))
              << std::endl << std::endl;
}

void game_draw(struct minesawyer *game)
{
    system("cls");
    std::cout << "Remaining Flags: " << std::setw(2) << game->mines - game->flags;
    std::cout << std::endl << std::endl;

    draw_board(game->width, game->height, game->board, game->mask, game->cursor);
}

void game_draw(struct minesawyer *game)
{
    system("cls");
    std::cout << "Move (arrow kes)" << std::endl;
    std::cout << "Open (O)" << std::endl;
    std::cout << "Flag (F)" << std::endl;
    std::cout << "Save and exit (M)" << std::endl;
}

bool game_input(struct minesawyer *game)
{
    if (GetKeyState(VK_UP) & 0x8000)
    {
        if (is_valid_cell(game->cursor.first, game->cursor.second - 1, game->width, game->height))
        {
            game->cursor.second -= 1;
            return true;
        }
    }
    else if (GetKeyState(VK_DOWN) & 0x8000)
    {
        if (is_valid_cell(game->cursor.first, game->cursor.second + 1, game->width, game->height))
        {
            game->cursor.second += 1;
            return true;
        }
    }
    else if (GetKeyState(VK_RIGHT) & 0x8000)
    {
        if (is_valid_cell(game->cursor.first + 1, game->cursor.second, game->width, game->height))
        {
            game->cursor.first += 1;
            return true;
        }
    }
    else if (GetKeyState(VK_LEFT) & 0x8000)
    {
        if (is_valid_cell(game->cursor.first - 1, game->cursor.second, game->width, game->height))
        {
            game->cursor.first -= 1;
            return true;
        }
    }
    else if (GetKeyState('O') & 0x8000)
    {
        if (game->mask[game->cursor.first][game->cursor.second] == 0 &&
            open_cell(game->cursor.first, game->cursor.second, game->width, game->height, game->board, game->mask))
        {
            game->change_scene(END);
            return true;
        }
    }
    else if (GetKeyState('F') & 0x8000)
    {
        if (game->mask[game->cursor.first][game->cursor.second] == 0)
        {
            flag_cell(game->cursor.first, game->cursor.second, game->flags, game->mask);
            return true;
        }
    }
    else if (GetKeyState('M') & 0x8000)
    {
        save_board(game->width, game->height, game->mines, game->seed, game->flags, get_duration(game->start_time), game->mask);
        game->change_scene(MENU);
        return true;
    }

    return false;
}

void game_scene(struct minesawyer *game)
{
    while (true)
    {
        game_draw(game);

        while (!game_input(game))
        {
            update_timer(game);
        }

        if (check_win(game->flags, game->mines, game->width, game->height, game->board, game->mask))
            game->change_scene(END);

        if (game->current_scene != GAME)
            return;
    }
}