//done
#pragma once

#include <string>
#include "koma/koma.h"

using namespace std;

class Game{
public:
    int numOfTurn;
    string kifu;

    Game();
    void addKifu(pair<int, int> after, Koma* koma, int moveType);
    bool sennnitite();
    bool outesennnitite();
};