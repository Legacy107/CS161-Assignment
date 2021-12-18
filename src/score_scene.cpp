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
    const int OFFSET = 100;
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);

    system("cls");

    std::cout << "============" << std::endl;
    std::cout << " High Score " << std::endl;
    std::cout << "============" << std::endl << std::endl;

    for (int i = 0; i < board_options.size(); i++)
    {
        set_cursor(0, 4);

        for (int j = 0; j < board_options[i].size(); j++)
        {
            std::vector<int> scores = get_scores(
                board_options[i][j].mines + i * OFFSET
            );

            COORD console_cursor = get_cursor();
            set_cursor(console_cursor.X + 35 * i, console_cursor.Y);

            SetConsoleTextAttribute(h_console, BRIGHT_BLUE);
            std::cout << board_options[i][j].name << " scoreboard" << std::endl;

            SetConsoleTextAttribute(h_console, WHITE);
            for (int id = 0; id < SCORE_LIMIT; id++)
            {
                console_cursor = get_cursor();
                set_cursor(console_cursor.X + 35 * i, console_cursor.Y);

                std::cout << std::setw(2) << id + 1 << ". ";

                if (id < scores.size())
                    std::cout << format_duration(scores[id]);
                std::cout << std::endl;
            }

            std::cout << std::endl;
        }
    }

    set_cursor(0, 26);
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
