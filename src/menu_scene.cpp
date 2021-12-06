#include "../header/global.h"
#include "../header/minesawyer.h"
#include "../header/board.h"
#include <iostream>
#include <windows.h>

void menu_draw()
{
    system("cls");
    std::cout << "============" << std::endl;
    std::cout << " MINESAWYER " << std::endl;
    std::cout << "============" << std::endl << std::endl;
    std::cout << "NEW GAME (N)" << std::endl;
    std::cout << "CONTINUE (C)" << std::endl;
    std::cout << "SCOREBOARD (S)" << std::endl;
    std::cout << "EXIT (E)" << std::endl << std::endl;
    std::cout << "Press the letter after each option to choose" << std::endl;
}

bool menu_input(struct minesawyer *game)
{
    if (GetKeyState('N') & 0x8000)
    {
        game->change_scene(CHOOSER);
        return true;
    }
    if (GetKeyState('C') & 0x8000)
    {
        game->loadboard();
        game->change_scene(GAME);
        return true;
    }
    if (GetKeyState('S') & 0x8000)
    {
        game->change_scene(SCORE);
        return true;
    }
    if (GetKeyState('E') & 0x8000)
    {
        game->change_scene(EXIT);
        return true;
    }

    return false;
}

void menu_scene(struct minesawyer *game)
{
    menu_draw();
    while (!menu_input(game)) {}
}

