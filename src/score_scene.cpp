#include "../header/global.h"
#include "../header/minesawyer.h"
#include <iostream>
#include <windows.h>
#include <vector>

void score_scene(struct minesawyer *game)
{
    while (true)
    {
        score_draw();
        while (true)
        {
            if (score_input(game))
                return;
        }
    }
}
