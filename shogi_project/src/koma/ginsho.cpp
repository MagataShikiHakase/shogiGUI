//done
#include "koma/ginsho.h"
#include "global.h"

Ginsho::Ginsho(pair<int, int> p, bool t) : Koma(p, t){
    type = "GI";
}

bool Ginsho::validMove(pair<int, int> after, bool turn){
    int dx = after.first - pos.first, dy = after.second - pos.second;
    
    if(turn == PLAYER1){
        if((dx == 1 || dx == 0 || dx == -1) && dy == -1)
            return true;
        if((dx == 1 || dx == -1) && dy == 1)
            return true;
    }
    //turn == PLAYER2
    else{
        if((dx == -1 || dx == 0 || dx == 1) && dy == 1)
            return true;
        if((dx == 1 || dx == -1) && dy == -1)
            return true;
    }
    return false;
}
