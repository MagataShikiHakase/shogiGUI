//done
#include <utility>
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

bool checkInsideBoard(pair<int, int> before, pair<int, int> after){
    if((1 <= before.first && before.first <= 9 && 1 <= before.second && before.second <= 9) && (1 <= after.first && after.first <= 9 && 1 <= after.second && after.second <= 9)){
        return true;
    }
    return false;
}