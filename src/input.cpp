#include "../header/input.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <string.h>

bool start_input()
{
    char ans;

    while (true)
    {
        std::cout << "Enter y to start or n to quit: ";
        std::cin >> ans;
        if (ans != 'y' && ans != 'n')
            std::cout << "Wrong input. Try again." << std::endl;
        if (ans == 'y')
            return true;
        return false;
    }
}

std::pair<std::pair<int, int>, bool> cell_input(int width, int height, std::vector<std::vector<int>> &mask)
{
    std::string s;
    char pos;
    int a, b;

    while (true)
    {
        std::cout << "Enter your action (A1 -> open, A1F -> flag or unflag): ";
        std::cin >> s;
        std::stringstream ss(s);
        ss >> pos;
        a = pos - 'A';
        ss >> b;
        --b;
        if (a < 0 || a >= height || b < 0 || b >= width)
            std::cout << "Wrong input. Try again!." << std::endl;
        else if (mask[a][b] == 1)
            std::cout << "Already open. Try again." << std::endl;
        else
        {
            if (s[s.size() - 1] == 'F')
                return {{b, a}, 1};
            return {{b, a}, 0};
        }
    }
}

void input()
{
    std::cout << start_input() << std::endl;

    std::vector<std::vector<int>> mask = {{0, 0}, {1, 1}};
    std::pair<std::pair<int, int>, bool> tmp = cell_input(2, 2, mask);
    std::cout << tmp.first.first << " " << tmp.first.second << " " << tmp.second;
}
