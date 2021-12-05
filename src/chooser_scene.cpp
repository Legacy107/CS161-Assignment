#include "../header/global.h"
#include "../header/minesawyer.h"
#include <iostream>
#include <windows.h>
#include "game_scene.h"

void chooser_draw()
{
    std::cout << "================" << std::endl;
    std::cout << " Choose a board " << std::endl;
    std::cout << "================" << std::endl;
    std::cout << endl;

    for (int i = 0; i < board_options.size(); i++)
    {
        std::cout << i + 1 << ". ";
        cout << board_options[i].name << " " << board_options[i].width
             << " x " << board_options[i].height << " "
             << board_options[i].mines << " mines (" << i + 1 << ")" << std::endl;
    }

    std::cout << std::endl << "< Menu (M)" << std::endl;
}

bool chooser_input(struct minesawyer *game)
{
    for (int i = 0; i < board_options.size(); i++)
    {
        if (GetKeyState((char)('1' + i)) & 0x8000)
        {
            game->create_board(board_options[i].width, board_options[i].height, board_options[i].mines);
            game->change_scene(GAME);
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
    chooser_draw();
    while (true)
    {
        if (chooser_input(game))
            return;
    }
}
