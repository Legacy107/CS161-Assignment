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

        update_scoreboard(score);
        highscore = get_highscore();

        std::cout << "You win!" << std::endl;
        std::cout << "Score: " << score << "\t" << "Highscore: " << highscore;
    }
    else
        std::cout << "You lose!";

    cout <<  std::endl << std::endl;
    draw_board(game->width, game->height, game->board, game->mask);
}

bool end_input(struct minesawyer *game)
{
    if (GetKeyState(VK_BACK) & 0x8000)
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
        game_draw(game);
        while (!game_input(game)) {}
        if (game->current_scene != END)
            return;
    }
}
