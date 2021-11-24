#pragma once
#include "../header/global.h"
#include "../header/minesawyer.h"
#include "../header/board.h"
#include <iostream>
#include <windows.h>

// Display game title and all options
void menu_draw();

// Receive inputs by using GetKeyState()
// If user selects an option, process and change scene then return true
// else return false
// List of options:
// - New game: change to scene CHOOSER
// - Continue: call game->load_board(), change to scene GAME
// - Score board: change to scene SCORE
// - Exit: change to scene EXIT
bool menu_input(struct minesawyer *game);

void menu_scene(struct minesawyer *game);