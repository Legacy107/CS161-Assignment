#include <map>
#include <iostream>
#include "./header/board.h"
#include "./header/input.h"

using namespace std;

typedef void (*FnPtr)();

int main(int argc, char *argv[])
{
    map<string, FnPtr> strategy;
    strategy["board"] = board;
    strategy["input"] = input;

    strategy[argv[1]]();

    return 0;
}
