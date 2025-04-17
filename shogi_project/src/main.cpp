#include <iostream>
#include "koma/koma.h"
#include "board.h"
#include "player.h"
#include "global.h"
#include "game.h"

using namespace std;

int main(){
    
    Game game;
    Board board;
    bool currentTurn = PLAYER1;
    Player player1(PLAYER1), player2(PLAYER2);
    int moveType = NORMAL;

    while(true){
        
        cout << "Turn " << game.numOfTurn << "\n" << (currentTurn ? "PLYER1's TURN" : "PLAYER2's TURN") << endl;
        board.show();
    
        int fromX, fromY, toX, toY;
        cin >> fromX >> fromY >> toX >> toY;
  
        Koma* koma = board.grid[y_shogiIndex_to_x_arrayIndex(fromY)][x_shogiIndex_to_y_arrayIndex(fromX)];
    
        // Verify source has a piece && the move is valid && destination isn't occupied by own piece.
        if(koma != nullptr && koma->validMove(toX, toY, currentTurn) && board.validSpaceForMove(currentTurn, toX, toY))
            player1.makeMove(fromX, fromY, toX, toY, board.grid);
        else
            continue;

        game.addKifu(toX, toY, koma, moveType);
        cout << game.kifu << endl;
        currentTurn = !currentTurn;
        game.numOfTurn++;

        cout << endl;
    }

    return 0;
}