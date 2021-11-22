#include <iostream>
#include <vector>
#include <windows.h>
#include "./header/board.h"
#include "./header/input.h"

using namespace std;

struct minesawyer
{
    vector<vector<int>> board, mask;
    int width, height, mines;
    int flags = 0;

    minesawyer(int width, int height, int mines)
    {
        this->width = width;
        this->height = height;
        this->mines = mines;

        for (int i = 0; i < height; i++)
        {
            vector<int> board_row(width);
            board.push_back(board_row);
        }
        gen_board(board, width, height, mines);

        for (int i = 0; i < height; i++)
        {
            vector<int> mask_row(width);
            mask.push_back(mask_row);
        }
    }

    bool has_won()
    {
        return check_win(flags, mines, width, height, board, mask);
    }

    void handleWin()
    {
        draw();
        cout << "You win" << endl;
    }

    void handleLose()
    {
        draw();
        cout << "You lose" << endl;
    }

    void draw()
    {
        system("cls");
        cout << "==========" << endl;
        cout << "Minesawyer" << endl;
        cout << "==========" << endl;
        draw_board(width, height, board, mask);
    }
};

int main()
{
    // Initialize
    system("cls");
    minesawyer game(10, 10, 10);
    if (!start_input())
        return 0;

    // Main loop
    while (true)
    {
        game.draw();

        auto command = cell_input(game.width, game.height, game.mask);
        if (command.second)
            flag_cell(command.first.first, command.first.second, game.flags, game.mask);
        else if (open_cell(command.first.first, command.first.second, game.width, game.height, game.board, game.mask))
        {
            game.handleLose();
            break;
        }

        if (game.has_won())
        {
            game.handleWin();
            break;
        }
    }

    // Cleanup
    system("pause");

    return 0;
}
