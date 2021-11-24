#include "../header/global.h"
#include "../header/minesawyer.h"
#include "../header/board.h"
#include <iostream>
#include <windows.h>

void menu_scene(struct minesawyer *game)
{
    while (true)
    {
        menu_draw();
        while (true)
        {
            if (menu_input(game))
                return;
        }
    }
}
