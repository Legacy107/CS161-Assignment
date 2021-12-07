#include "../header/global.h"
#include "../header/minesawyer.h"
#include <iostream>
#include <windows.h>

void chooser_draw(struct minesawyer *game)
{
    system("cls");
    std::cout << "================" << std::endl;
    std::cout << " Choose a board " << std::endl;
    std::cout << "================" << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < board_options[game->mode].size(); i++)
    {
        std::cout << i + 1 << ". ";
        std::cout << board_options[game->mode][i].name << " "
                  << board_options[game->mode][i].width
                  << " x " << board_options[game->mode][i].height << " "
                  << board_options[game->mode][i].mines
                  << " mines (" << i + 1 << ")" << std::endl;
    }

    if (game->mode == 1)
    {
        std::cout << std::endl << std::endl;
        std::cout << "Minesawyer's rule:" << std::endl;
        std::cout << "Each cell has either a mine or a number indicating the distance to the nearest mine." << std::endl;
        std::cout << "To win the game, you have to open all the cells that have mines inside." << std::endl;
        std::cout << "For each cell you open that does not contain a mine, a 30 seconds penalty will be applied." << std::endl;
        std::cout << "GLHF! :D" << std::endl << std::endl;
    }

    std::cout << std::endl << "< Menu (M)" << std::endl;
}

bool chooser_input(struct minesawyer *game)
{
    for (int i = 0; i < board_options[game->mode].size(); i++)
    {
        if (GetKeyState((char)('1' + i)) & 0x8000)
        {
            game->create_board(board_options[game->mode][i].width, board_options[game->mode][i].height, board_options[game->mode][i].mines);
            if (game->mode == 0)
                game->change_scene(GAME);
            else if (game->mode == 1)
                game->change_scene(SAW);
            return true;
        }
    }

    if (GetKeyState('M') & 0x8000)
    {
        game->change_scene(MENU);
        return true;
    }

    return false;
}

void chooser_scene(struct minesawyer *game)
{
    chooser_draw(game);
    while (true)
    {
        if (chooser_input(game))
            return;
    }
}
