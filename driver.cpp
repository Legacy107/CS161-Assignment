#include <map>
#include <iostream>
#include "./header/global.h"
#include "./header/minesawyer.h"
#include "./header/board.h"
#include "./header/input.h"
#include "./header/score.h"
#include "./header/util.h"
#include "./header/score_scene.h"

using namespace std;

typedef void (*FnPtrVoid)();

int main(int argc, char *argv[])
{
    map<string, FnPtrVoid> strategy;
    map<string, FnPtr> scene_strategy;
    strategy["board"] = board;
    strategy["input"] = input;
    strategy["score"] = score;
    strategy["util"] = util;
    scene_strategy["score"] = score_scene;

    if (argv[1][0] == '#')
    {
        struct minesawyer game;
        game.add_scene(SCORE, score_scene);
        scene_strategy[argv[2]](&game);
        std::cout << std::endl << "Scene: " << game.current_scene;
    }
    else
        strategy[argv[1]]();

    return 0;
}
