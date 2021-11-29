#include "../header/global.h"
#include "../header/util.h"
#include "../header/minesawyer.h"
#include "../header/board.h"
#include <iostream>
#include <windows.h>
#include <iomanip>

void game_draw(struct minesawyer *game)
{
    std::cout << "Remaining Flags: " << std::setw(2) << game->mines - game->flags;
    std::cout << "\t\tTime: " << format_duration(get_duration(game->start_time))
              << std::endl << std::endl;
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
