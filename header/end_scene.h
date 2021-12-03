#pragma once
#include "../header/global.h"
#include "../header/util.h"
#include "../header/score.h"
#include "../header/minesawyer.h"
#include "../header/board.h"
#include <iostream>
#include <windows.h>

// Display end msg, board and score
void end_draw(struct minesawyer *game);

// Receive inputs by using GetKeyState()
// If user selects an option, process (and change scene) then return true
// else return false
// List of options:
// - Back: change scene to MENU
bool end_input(struct minesawyer *game);

void end_scene(struct minesawyer *game);
