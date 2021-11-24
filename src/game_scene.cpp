#include "../header/global.h"
#include "../header/minesawyer.h"
#include "../header/board.h"
#include <iostream>
#include <windows.h>

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
