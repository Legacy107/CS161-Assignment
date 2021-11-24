#include <iostream>
#include <windows.h>
#include "./header/global.h"
#include "./header/minesawyer.h"
#include "./header/menu_scene.h"
#include "./header/chooser_scene.h"
#include "./header/game_scene.h"
#include "./header/score_scene.h"

using namespace std;

int main()
{
    // Initialize
    system("cls");
    struct minesawyer game;
    game.add_scene(MENU, menu_scene);
    game.add_scene(CHOOSER, chooser_scene);
    game.add_scene(GAME, game_scene);
    game.add_scene(SCORE, score_scene);

    // Main loop
    game.process();

    return 0;
}
