#include "game.h"

Game::Game(){
    numOfTurn = 0;
    kifu = "";
}

void Game::addKifu(int afterX, int afterY, Koma* koma, int moveType){
    std::string move = (koma->turn ? "▲" : "△") +
                       std::to_string(afterX) +
                       std::to_string(afterY) +
                       koma->type;
    kifu.append(move + "\n");
}

bool Game::sennnitite(){
    return false;
}

bool Game::outesennnitite(){
    return false;
}