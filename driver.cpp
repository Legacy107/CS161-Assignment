#include <map>
#include <iostream>
#include "./header/board.h"
#include "./header/input.h"
#include "./header/score.h"

using namespace std;

typedef void (*FnPtr)();

int main(int argc, char *argv[])
{
    map<string, FnPtr> strategy;
    strategy["board"] = board;
    strategy["input"] = input;
    strategy["score"] = score;

    strategy[argv[1]]();

    return 0;
}
