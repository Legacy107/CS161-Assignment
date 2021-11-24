#include "../header/global.h"
#include "../header/minesawyer.h"
#include <iostream>
#include <windows.h>

void chooser_scene(struct minesawyer *game)
{
    while (true)
    {
        chooser_draw();
        while (true)
        {
            if (chooser_input(game))
                return;
        }
    }
}
