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

bool checkInsideBoard(int beforeX, int beforeY, int afterX, int afterY);

template <typename T>
void placeKoma(int x_shogiIndex, int y_shogiIndex, bool turn, Koma* grid[9][9]){
    grid[y_shogiIndex_to_x_arrayIndex(y_shogiIndex)][x_shogiIndex_to_y_arrayIndex(x_shogiIndex)] = new T(x_shogiIndex, y_shogiIndex, turn);
}