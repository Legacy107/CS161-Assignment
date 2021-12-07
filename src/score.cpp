#include "../header/score.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

std::vector<int> get_scores(int mines)
{
    int n = 0, tmp;
    std::vector<int> scores;
    std::ifstream score_file("score" + std::to_string(mines) + ".txt");

    score_file >> n;
    for (int i = 0; i < n; i++)
    {
        score_file >> tmp;
        scores.push_back(tmp);
    }

    score_file.close();

    return scores;
}

int get_highscore(int mines)
{
    std::vector<int> scores = get_scores(mines);
    return scores[0];
}

void update_scoreboard(int mines, int score)
{
    std::vector<int> scores = get_scores(mines);
    std::ofstream score_file("score" + std::to_string(mines) + ".txt");
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
    std::vector<int> scores = get_scores(10);
    for (score : scores)
        std::cout << score << " ";
    std::cout << std::endl << get_highscore(10) << std::endl;

    update_scoreboard(10, 100);

    scores = get_scores(10);
    for (score : scores)
        std::cout << score << " ";
}
