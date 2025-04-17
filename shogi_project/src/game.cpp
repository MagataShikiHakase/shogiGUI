//done
#include "game.h"

Game::Game(){
    numOfTurn = 0;
    kifu = "";
}

void Game::addKifu(pair<int, int> after, Koma* koma, int moveType){
    std::string move = (koma->turn ? "▲" : "△") +
                       std::to_string(after.first) +
                       std::to_string(after.second) +
                       koma->type;
    kifu.append(move + "\n");
}

bool Game::sennnitite(){
    return false;
}

bool Game::outesennnitite(){
    return false;
}