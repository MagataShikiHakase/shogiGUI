//dond
#include "player.h"
#include "global.h"
#include "koma/koma.h"

Player::Player(bool t) : turn(t){};

void Player::makeMove(pair<int, int> from, pair<int, int> to, Koma* grid[9][9]){
    Koma* moving = grid[y_shogiIndex_to_x_arrayIndex(from.second)][x_shogiIndex_to_y_arrayIndex(from.first)];

    if(grid[y_shogiIndex_to_x_arrayIndex(to.second)][x_shogiIndex_to_y_arrayIndex(to.first)] != nullptr)
        delete grid[y_shogiIndex_to_x_arrayIndex(to.second)][x_shogiIndex_to_y_arrayIndex(to.first)];

    grid[y_shogiIndex_to_x_arrayIndex(to.second)][x_shogiIndex_to_y_arrayIndex(to.first)] = moving;
    grid[y_shogiIndex_to_x_arrayIndex(from.second)][x_shogiIndex_to_y_arrayIndex(from.first)] = nullptr;

    moving->pos.first = to.first;
    moving->pos.second = to.second;
}
        
void Player::getKoma(){

}
        
void Player::makePromoted(){

}
