#include "koma/ginsho.h"
#include "global.h"

Ginsho::Ginsho(int x, int y, bool t) : Koma(x, y, t){
    type = "GI";
}

bool Ginsho::validMove(int afterX, int afterY, bool turn){
    int dx = afterX - x, dy = afterY - y;
    
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
