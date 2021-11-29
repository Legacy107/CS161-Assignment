#include "../header/global.h"
#include "../header/util.h"
#include "../header/minesawyer.h"
#include "../header/score.h"
#include <iostream>
#include <windows.h>
#include <vector>
#include <iomanip>

void score_draw()
{
    std::vector<int> scores = get_scores();

    std::cout << "============" << std::endl;
    std::cout << " High Score " << std::endl;
    std::cout << "============" << std::endl << std::endl;

    for (int i = 0; i < scores.size(); i++)
        std::cout << std::setw(2) << i + 1 << ". "
                  << format_duration(scores[i]) << std::endl;

    std::cout << std::endl;
    std::cout << "< Menu (M)" << std::endl;
}

bool score_input(struct minesawyer *game)
{
    if (GetKeyState('M') & 0x8000)
    {
        game->change_scene(MENU);
        return true;
    }
    return false;
}

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
