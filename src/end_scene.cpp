#include "../header/global.h"
#include "../header/util.h"
#include "../header/score.h"
#include "../header/minesawyer.h"
#include "../header/board.h"
#include <iostream>
#include <windows.h>

void end_draw(struct minesawyer *game)
{
    system("cls");

    if (check_win(game->flags, game->mines, game->width, game->height, game->board, game->mask))
    {
        int score = get_duration(game->start_time), highscore = 0;

        update_scoreboard(game->mines, score);
        highscore = get_highscore(game->mines);

        std::cout << "==========" << std::endl;
        std::cout << " You win! " << std::endl;
        std::cout << "==========" << std::endl << std::endl;
        std::cout << "Score: " << format_duration(score) << "\t"
                  << "Highscore: " << format_duration(highscore) <<std::endl;
    }
    else
    {
        std::cout << "===========" << std::endl;
        std::cout << " You lose! " << std::endl;
        std::cout << "===========" << std::endl;
    }

    std::cout << std::endl;
    draw_board(game->width, game->height, game->board, game->mask);

    std::cout << std::endl << "< Menu (M)" << std::endl;
}

bool end_input(struct minesawyer *game)
{
    if (GetKeyState('M') & 0x8000)
    {
        game->change_scene(MENU);
        return true;
    }
    return false;
}

void end_scene(struct minesawyer *game)
{
    while (true)
    {
        end_draw(game);
        while (!end_input(game)) {}
        if (game->current_scene != END)
            return;
    }
}
