//done
#pragma once

#include <vector>
#include "koma/koma.h"

class Player{
public:
    bool turn;
    vector<Koma*> tegoma;
    
    Player(bool t);
    void makeMove(pair<int, int> from, pair<int, int> to, Koma* grid[9][9]);
    void getKoma();
    void makePromoted();
};