#pragma once
#include "../header/global.h"
#include "../header/minesawyer.h"
#include <iostream>
#include <windows.h>
#include <vector>

std::vector<int> load_score();

// Display all highscores
void score_draw();

// Receive inputs by using GetKeyState()
// If user selects an option, process and change scene then return true
// else return false
// List of options:
// - Back: change scene to MENU
bool score_input(struct minesawyer *game);

void score_scene(struct minesawyer *game);
