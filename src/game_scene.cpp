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

void game_scene(struct minesawyer *game)
{
    while (true)
    {
        game_draw(game);
        while (!game_input(game))
        {
            update_timer(game);
        }
        if (game->current_scene != GAME)
            return;
    }
}
