#pragma once
#include "../header/global.h"
#include "../header/util.h"
#include "../header/minesawyer.h"
#include "../header/board.h"
#include <iostream>
#include <windows.h>
#include <iomanip>

void update_timer(struct minesawyer *game);

// Display board and all options
void game_draw(struct minesawyer *game);

// Receive inputs by using GetKeyState()
// If user selects an option, process (and change scene) then return true
// else return false
// List of options:
// - arrows: move game->cursor
// - Select: validate and call open_cell()
// - Flag: validate and call open_cell()
// - Back: call save_board(), change scene to MENU
bool game_input(struct minesawyer *game);

void game_scene(struct minesawyer *game);
