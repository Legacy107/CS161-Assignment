#include "../header/global.h"
#include "../header/minesawyer.h"
#include <iostream>
#include <windows.h>
#include "game_scene.h"

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
bool chooser_input(struct minesawyer *game)
{
    // Receive inputs by using GetKeyState()
    // If user selects an option, process and change scene then return true
    // else return false
    // List of options:
    // - Beginner: call game->create_board(), change to scene GAME
    // - Intermediate: call game->create_board(), change to scene GAME
    // - Expert: call game->create_board(), change to scene GAME
    if(GetKeyState('B') & 0x8000)
    {
        game->create_board(10,10,10);
        game->process();
        game->change_scene(game->current_scene);
        return true;
    }
    else if(GetKeyState('I') & 0x8000)
    {
        game->create_board(16,16,40);
        game->process();
        game->change_scene(game->current_scene);
        return true;
    }
    else if(GetKeyState('E') & 0x8000)
    {
        game->create_board(16,30,99);
        game->process();
        game->change_scene(game->current_scene);
        return true;
    }
    else 
        return false;
}