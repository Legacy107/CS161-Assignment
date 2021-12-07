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
    system("cls");
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);

    std::cout << "============" << std::endl;
    std::cout << " High Score " << std::endl;
    std::cout << "============" << std::endl << std::endl;

    for (int i = 0; i < board_options.size(); i++)
    {
        std::vector<int> scores = get_scores(board_options[i].mines);

        SetConsoleTextAttribute(h_console, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        std::cout << board_options[i].name << " scoreboard" << std::endl;

        SetConsoleTextAttribute(h_console, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
        for (int id = 0; id < scores.size(); id++)
            std::cout << std::setw(2) << id + 1 << ". "
                      << format_duration(scores[id]) << std::endl;

        std::cout << std::endl;
    }
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
