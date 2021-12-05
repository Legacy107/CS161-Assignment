#include "../header/global.h"
#include "../header/minesawyer.h"
#include "../header/board.h"
#include <iostream>
#include <windows.h>

void menu_draw()
{
    cout << "  ================MINESWEEPER================" << endl;
    cout << "                  NEW GAME (N)" << endl;
    cout << "                  CONTINUE (C)" << endl;
    cout << "                SCORE BOARD (S)" << endl;
    cout << "                   EXIT (E)" << endl;
    cout << "  Press the letter after each option to choose" << endl;
}

bool menu_input(struct minesawyer* game)
{
    if (GetKeyState('N') & 0x8000)
    {
        minesawyer::change_scene(CHOOSER);
        return true;
    }
    else if (GetKeyState('C') & 0x8000)
    {
        minesawyer::loadboard();
        minesawyer::change_scene(GAME);
        return true;
    }
    else if (GetKeyState('S') & 0x8000)
    {
        minesawyer::change_scene(SCORE);
        return true;
    }
    else if (GetKeyState('E') & 0x8000)
    {
        minesawyer::change_scene(EXIT);
        return true;
    }
    else return false;
}

void menu_scene(struct minesawyer *game)
{
    while (true)
    {
        menu_draw();
        while (true)
        {
            if (menu_input(game))
                return;
        }
    }
}

