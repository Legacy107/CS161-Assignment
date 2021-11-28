#include "../header/score.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string.h>

std::vector<int> get_scores()
{
    int n = 0, tmp;
    std::vector<int> scores;
    std::ifstream score_file("score.txt");

    score_file >> n;
    for (int i = 0; i < n; i++)
    {
        score_file >> tmp;
        scores.push_back(tmp);
    }

    score_file.close();

    return scores;
}

int get_highscore()
{
    std::vector<int> scores = get_scores();
    return scores[0];
}

void update_scoreboard(int score)
{
    std::vector<int> scores = get_scores();
    std::ofstream score_file("score.txt");
    int n = std::min(SCORE_LIMIT, (int)scores.size() + 1);

    auto it = std::lower_bound(scores.begin(), scores.end(), score);
    scores.insert(it, score);

    score_file << n << std::endl;
    for (int i = 0; i < n; i++)
    {
        score_file << scores[i] << std::endl;
    }

    score_file.close();
}

void score()
{
    std::vector<int> scores = get_scores();
    for (score : scores)
        std::cout << score << " ";
    std::cout << std::endl << get_highscore() << std::endl;

    update_scoreboard(100);

    scores = get_scores();
    for (score : scores)
        std::cout << score << " ";
}