#pragma once

#include <string>
#include "koma/koma.h"

using namespace std;

class Game{
public:
    int numOfTurn;
    string kifu;

    Game();
    void addKifu(int afterX, int afterY, Koma* koma, int moveType);
    bool sennnitite();
    bool outesennnitite();
};