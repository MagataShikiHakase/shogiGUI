//done
#include <iostream>
#include <utility>
#include "koma/koma.h"
#include "board.h"
#include "player.h"
#include "global.h"
#include "game.h"

using namespace std;

int main(){
    
    Game game;
    Board board;
    pair<int, int> from, to;
    bool currentTurn = PLAYER1;
    Player player1(PLAYER1), player2(PLAYER2);
    int moveType = NORMAL;

    while(true){
        
        cout << "Turn " << game.numOfTurn << "\n" << (currentTurn ? "PLYER1's TURN" : "PLAYER2's TURN") << endl;
        board.show();
        
        cin >> from.first >> from.second >> to.first >> to.second;
  
        Koma* koma = board.grid[y_shogiIndex_to_x_arrayIndex(from.second)][x_shogiIndex_to_y_arrayIndex(from.first)];
    
        // Verify source has a piece && the move is valid && destination isn't occupied by own piece.
        if(koma != nullptr && koma->validMove(to, currentTurn) && board.validSpaceForMove(currentTurn, to))
            player1.makeMove(from, to, board.grid);
        else
            continue;

        game.addKifu(to, koma, moveType);
        cout << game.kifu << endl;
        currentTurn = !currentTurn;
        game.numOfTurn++;

        cout << endl;
    }

    return 0;
}