#pragma once

#include "koma/koma.h"


class Board{
public:
    Koma* grid[9][9];
    
    //No Handicap Match
    Board();       
    //Handicap Match
    Board(int op);
    
    ~Board();
    
    void show();
    bool validSpaceForMove(bool currentTurn, int toX, int toY);

    //Board can check the situation is game orver or not but it cant check the oute
    bool tumi();
};