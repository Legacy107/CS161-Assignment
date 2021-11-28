#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>

const int SCORE_LIMIT = 10;

// Get all scores from score.txt;
std::vector<int> get_scores();

// Get the highest score from score.txt
int get_highscore();

// Insert new score into score.txt
// Only save top 10 highscores
void update_scoreboard(int score);

void score();