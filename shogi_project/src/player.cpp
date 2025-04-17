#include "player.h"
#include "global.h"
#include "koma/koma.h"

Player::Player(bool t) : turn(t){};

void Player::makeMove(int fromX, int fromY, int toX, int toY, Koma* grid[9][9]){
    Koma* moving = grid[y_shogiIndex_to_x_arrayIndex(fromY)][x_shogiIndex_to_y_arrayIndex(fromX)];

    if(grid[y_shogiIndex_to_x_arrayIndex(toY)][x_shogiIndex_to_y_arrayIndex(toX)] != nullptr)
        delete grid[y_shogiIndex_to_x_arrayIndex(toY)][x_shogiIndex_to_y_arrayIndex(toX)];

    grid[y_shogiIndex_to_x_arrayIndex(toY)][x_shogiIndex_to_y_arrayIndex(toX)] = moving;
    grid[y_shogiIndex_to_x_arrayIndex(fromY)][x_shogiIndex_to_y_arrayIndex(fromX)] = nullptr;

    moving->x = toX;
    moving->y = toY;
}
        
void Player::getKoma(){

}
        
void Player::makePromoted(){

}
