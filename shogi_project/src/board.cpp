//done
#include <iostream>
#include "board.h"
#include "global.h"
#include "koma/fu.h"
#include "koma/ginsho.h"
#include "koma/hisha.h"
#include "koma/kakugyo.h"
#include "koma/keima.h"
#include "koma/kinsho.h"
#include "koma/kyosha.h"
#include "koma/ousho.h"

Board::Board(){
    //Set all grid nullptr
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            grid[i][j] = nullptr;
        }
    }
    //Set Pieces dynamically
    //Player1
    placeKoma<Fu>({1, 7}, PLAYER1, grid);
    placeKoma<Fu>({2, 7}, PLAYER1, grid);
    placeKoma<Fu>({3, 7}, PLAYER1, grid);
    placeKoma<Fu>({4, 7}, PLAYER1, grid);
    placeKoma<Fu>({5, 7}, PLAYER1, grid);
    placeKoma<Fu>({6, 7}, PLAYER1, grid);
    placeKoma<Fu>({7, 7}, PLAYER1, grid);
    placeKoma<Fu>({8, 7}, PLAYER1, grid);
    placeKoma<Fu>({9, 7}, PLAYER1, grid);
    placeKoma<Hisha>({2, 8}, PLAYER1, grid);
    placeKoma<Kakugyo>({8, 8}, PLAYER1, grid);
    placeKoma<Kyosha>({1, 9}, PLAYER1, grid);
    placeKoma<Kyosha>({9, 9}, PLAYER1, grid);
    placeKoma<Keima>({2, 9}, PLAYER1, grid);
    placeKoma<Keima>({8, 9}, PLAYER1, grid);
    placeKoma<Ginsho>({3, 9}, PLAYER1, grid);
    placeKoma<Ginsho>({7, 9}, PLAYER1, grid);
    placeKoma<Kinsho>({4, 9}, PLAYER1, grid);
    placeKoma<Kinsho>({6, 9}, PLAYER1, grid);
    placeKoma<Ousho>({5, 9}, PLAYER1, grid);
    
    //Player2
    placeKoma<Fu>({1, 3}, PLAYER2, grid);
    placeKoma<Fu>({2, 3}, PLAYER2, grid);
    placeKoma<Fu>({3, 3}, PLAYER2, grid);
    placeKoma<Fu>({4, 3}, PLAYER2, grid);
    placeKoma<Fu>({5, 3}, PLAYER2, grid);
    placeKoma<Fu>({6, 3}, PLAYER2, grid);
    placeKoma<Fu>({7, 3}, PLAYER2, grid);
    placeKoma<Fu>({8, 3}, PLAYER2, grid);
    placeKoma<Fu>({9, 3}, PLAYER2, grid);
    placeKoma<Kakugyo>({2, 2}, PLAYER2, grid);
    placeKoma<Hisha>({8, 2}, PLAYER2, grid);
    placeKoma<Kyosha>({1, 1}, PLAYER2, grid);
    placeKoma<Kyosha>({9, 1}, PLAYER2, grid);
    placeKoma<Keima>({2, 1}, PLAYER2, grid);
    placeKoma<Keima>({8, 1}, PLAYER2, grid);
    placeKoma<Ginsho>({3, 1}, PLAYER2, grid);
    placeKoma<Ginsho>({7, 1}, PLAYER2, grid);
    placeKoma<Kinsho>({4, 1}, PLAYER2, grid);
    placeKoma<Kinsho>({6, 1}, PLAYER2, grid);
    placeKoma<Ousho>({5, 1}, PLAYER2, grid);
}

//Handicap Match
Board::Board(int op){
    
}
    
Board::~Board(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            delete grid[i][j];
        }
    }
}
    
void Board::show(){
    cout << "  ";
    
    //column number
    for(int i = 9; i > 0; i--)
        cout << i << "    ";
    
    cout << "\n----------------------------------------------" << endl;
    
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            cout << "|";
    
            //Case: No piece
            if(grid[i][j] == nullptr)
                cout << "    ";
            //Case: First turn player piece
            else if(grid[i][j]->turn == PLAYER1)
                cout << " " << grid[i][j]->type << " ";
            //Case: Second turn player piece
            else
                cout << " \033[34m" << grid[i][j]->type << "\033[0m ";
        }
    
        //Right end
        cout << "|";
    
        //Row number
        cout << " " << i + 1 << endl;
    
        cout << "----------------------------------------------" << endl;
    }
}

bool Board::validSpaceForMove(bool currentTurn, pair<int, int> to){
    // Valid move only if the destination is empty or occupied by an opponent's piece
    if(grid[y_shogiIndex_to_x_arrayIndex(to.second)][x_shogiIndex_to_y_arrayIndex(to.first)] == nullptr || grid[y_shogiIndex_to_x_arrayIndex(to.second)][x_shogiIndex_to_y_arrayIndex(to.first)]->turn == !currentTurn)
        return true;
    
    return false;
}
