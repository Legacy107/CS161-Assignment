#pragma once
#include "../header/global.h"
#include "../header/util.h"
#include "../header/minesawyer.h"
#include "../header/board.h"
#include <iostream>
#include <windows.h>
#include <iomanip>
#include <map>
#include <vector>

void saw_update_timer(struct minesawyer *game);

void saw_draw_instruction(struct minesawyer *game);

// Display board and all options
void saw_game_draw(struct minesawyer *game);

// Receive inputs by using GetKeyState()
// If user selects an option, process (and change scene) then return true
// else return false
// List of options:
// - arrows: move game->cursor
// - Open: validate and call open_cell()
// - Flag: validate and call flag_cell()
// - Back: change scene to MENU
bool saw_game_input(struct minesawyer *game, std::map<int, bool> &prev_key_state);

void saw_game_scene(struct minesawyer *game);
