//done
#pragma once

#include "koma/koma.h"

enum player_turn : bool{
    PLAYER1 = true,
    PLAYER2 = false
};

enum MoveType {
    NORMAL = 0,   // 通常の手
    DROP = 1,     // 打ち
    PROMOTE = 2,  // 成り
    UNPROMOTE = 3,// 不成
};


int x_shogiIndex_to_y_arrayIndex(int x);
int y_shogiIndex_to_x_arrayIndex(int y);
int x_arrayIndex_to_y_shogiIndex(int x);
int y_arrayIndex_to_x_shogiIndex(int y);

void getMove();

bool checkInsideBoard(pair<int, int> before, pair<int, int> after);

template <typename T>
void placeKoma(pair<int,int> shogiIndex, bool turn, Koma* grid[9][9]){
    grid[y_shogiIndex_to_x_arrayIndex(shogiIndex.second)][x_shogiIndex_to_y_arrayIndex(shogiIndex.first)] = new T(shogiIndex, turn);
}