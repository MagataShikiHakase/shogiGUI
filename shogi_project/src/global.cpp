#include "global.h"

using namespace std;

int x_shogiIndex_to_y_arrayIndex(int x){
    return 9 - x;
}
int y_shogiIndex_to_x_arrayIndex(int y){
    return y - 1;
}
int x_arrayIndex_to_y_shogiIndex(int x){
    return 9 - x;
}
int y_arrayIndex_to_x_shogiIndex(int y){
    return y + 1;
}

void getMove(){

}

bool checkInsideBoard(int beforeX, int beforeY, int afterX, int afterY){
    if((1 <= beforeX && beforeX <= 9 && 1 <= beforeY && beforeY <= 9) && (1 <= afterX && afterX <= 9 && 1 <= afterY && afterY <= 9)){
        return true;
    }
    return false;
}