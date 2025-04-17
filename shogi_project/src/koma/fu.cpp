#include "koma/fu.h"
#include "global.h"

Fu::Fu(int x, int y, bool t) : Koma(x, y, t){
    type = "FU";
}
    
bool Fu::validMove(int afterX, int afterY, bool turn){

    if(turn == PLAYER1){
        if(x == afterX && y == afterY + 1){
            return true;
        }
    }

    //turn == PLAYER2
    else{
        if(x == afterX && y == afterY - 1)
            return true;
    }
    return false;
}