#include "../header/board.h"

using namespace std;

void input()
{
    // Driver code for testing
}

bool start_input()
{
    char ans;

    do
    {
        cout << "Press y to start or n to quit: ";
        cin >> ans;
        if (ans != 'y' || ans != 'n') cout << " Wrong input. Try again. ";
    }
    while (ans != 'y' || ans != 'n');

    if (ans == 'y') return true;
    else return false;
}

// output instruction and example (A1 -> open, A1F -> flag or unflag)
// get and validate input (if the cell is already open -> invalid)
// convert to numbers A->0 1->0
// if of open type return {{0, 0}, 0}
// if of flag type return {{0, 0}, 1}

pair<pair<int, int>, bool> cell_input(int width, int height, vector<vector<int>>& mask)
{
    char pos;
    
    do
    {
        cout << "Enter your action (A1 -> open, A1F -> flag or unflag): ";
        cin.get(pos);
        int a = pos - 'A';
        cin.get(pos);
        int b = pos - '0';
        if (a > width && b > height) cout << " Wrong input. Try again!. ";
        if (mask[a][b] == 1) cout << " Already open. Try again. ";
    } while ((a > width && b > height) || mask[a][b] == 1);

    cin.get(pos);
    if (pos == 'F') return { {a, b}, 1 };
    else return { {a, b}, 0 };
}


