#pragma once

#include <vector>
#include "koma/koma.h"

class Player{
public:
    bool turn;
    vector<Koma*> tegoma;
    
    Player(bool t);
    void makeMove(int fromX, int fromY, int toX, int toY, Koma* grid[9][9]);
    void getKoma();
    void makePromoted();
};