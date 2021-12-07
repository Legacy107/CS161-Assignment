#pragma once
#include "../header/global.h"
#include "../header/minesawyer.h"
#include <iostream>
#include <windows.h>

// Display all options
void chooser_draw(struct minesawyer *game);

// Receive inputs by using GetKeyState()
// If user selects an option, process and change scene then return true
// else return false
// List of options:
// - Beginner: call game->create_board(), change to scene GAME
// - Intermediate: call game->create_board(), change to scene GAME
// - Expert: call game->create_board(), change to scene GAME
bool chooser_input(struct minesawyer *game);

void chooser_scene(struct minesawyer *game);
