#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

const int SCORE_LIMIT = 5;

// Get all scores from score${mines}.txt;
std::vector<int> get_scores(int mines);

// Get the highest score from score${mines}.txt
int get_highscore(int mines);

// Insert new score into score${mines}.txt
// Only save top 10 highscores
void update_scoreboard(int mines, int score);

void score();