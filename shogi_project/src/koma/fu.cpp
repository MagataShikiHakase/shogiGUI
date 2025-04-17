//done
#include "koma/fu.h"
#include "global.h"

Fu::Fu(pair<int, int> p, bool t) : Koma(p, t){
    type = "FU";
}
    
bool Fu::validMove(pair<int, int> after, bool turn){

    if(turn == PLAYER1){
        if(pos.first == after.first && pos.second == after.second + 1){
            return true;
        }
    }

    //turn == PLAYER2
    else{
        if(pos.first == after.first && pos.second == after.second - 1)
            return true;
    }
    return false;
}