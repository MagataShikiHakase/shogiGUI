#include <iostream>
#include <vector>

using namespace std;

enum player_turn : bool{
    PLAYER1 = true,
    PLAYER2 = false
};

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

class Koma{
public:
    int x, y;
    string type;
    bool turn, promoted;

    Koma(int x, int y, bool t) : x(x), y(y), turn(t) {
        promoted = false;
    }
    virtual ~Koma() {};
    virtual bool canMove(int afterX, int afterY, bool turn) = 0;
};

class Fu : public Koma{
public:
    Fu(int x, int y, bool t) : Koma(x, y, t){ type = "FU"; }

    bool canMove(int afterX, int afterY, bool turn) override{





        return false;
    }
};

class Kyosha : public Koma{
public:
    Kyosha(int x, int y, bool t) : Koma(x, y, t){ type = "KY"; }
    bool canMove(int afterX, int afterY, bool turn) override{






        return false;
    }
};

class Keima : public Koma{
public:
    Keima(int x, int y, bool t) : Koma(x, y, t){ type = "KE"; }
    bool canMove(int afterX, int afterY, bool turn) override{
    
    
    
    
    
    
        return false;
    }
};

class Ginsho : public Koma{
public:
    Ginsho(int x, int y, bool t) : Koma(x, y, t){ type = "GI"; }
    bool canMove(int afterX, int afterY, bool turn) override{
        
        
        
        
        
        
        return false;
    }
};

class Kinsho : public Koma{
public:
    Kinsho(int x, int y, bool t) : Koma(x, y, t){ type = "KI"; }
    bool canMove(int afterX, int afterY, bool turn) override{
            
            
            
            
            
            
        return false;
    }
};

class Kakugyo : public Koma{
public:
    Kakugyo(int x, int y, bool t) : Koma(x, y, t){ type = "KA"; }
    bool canMove(int afterX, int afterY, bool turn) override{
            
            
            
            
            
            
        return false;
    }
};

class Hisha : public Koma{
public:
    Hisha(int x, int y, bool t) : Koma(x, y, t){ type = "HI"; }
    bool canMove(int afterX, int afterY, bool turn) override{
            
            
            
            
            
            
        return false;
    }
};

class Ousho : public Koma{
public:
    Ousho(int x, int y, bool t) : Koma(x, y, t){ type = "OU"; }
    bool canMove(int afterX, int afterY, bool turn) override{
            
            
            
            
            
            
        return false;
    }
};



template <typename T>
void placeKoma(int x_shogiIndex, int y_shogiIndex, bool turn, Koma* grid[9][9]){
    grid[y_shogiIndex_to_x_arrayIndex(y_shogiIndex)][x_shogiIndex_to_y_arrayIndex(x_shogiIndex)] = new T(x_shogiIndex, y_shogiIndex, turn);
}

class Board{
public:
    Koma* grid[9][9];

    //No Handicap Match
    Board(){
        //Set all grid nullptr
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                grid[i][j] = nullptr;
            }
        }
        //Set Pieces dynamically
        //Player1
        placeKoma<Fu>(1, 7, PLAYER1, grid);
        placeKoma<Fu>(2, 7, PLAYER1, grid);
        placeKoma<Fu>(3, 7, PLAYER1, grid);
        placeKoma<Fu>(4, 7, PLAYER1, grid);
        placeKoma<Fu>(5, 7, PLAYER1, grid);
        placeKoma<Fu>(6, 7, PLAYER1, grid);
        placeKoma<Fu>(7, 7, PLAYER1, grid);
        placeKoma<Fu>(8, 7, PLAYER1, grid);
        placeKoma<Fu>(9, 7, PLAYER1, grid);
        placeKoma<Hisha>(2, 8, PLAYER1, grid);
        placeKoma<Kakugyo>(8, 8, PLAYER1, grid);
        placeKoma<Kyosha>(1, 9, PLAYER1, grid);
        placeKoma<Kyosha>(9, 9, PLAYER1, grid);
        placeKoma<Keima>(2, 9, PLAYER1, grid);
        placeKoma<Keima>(8, 9, PLAYER1, grid);
        placeKoma<Ginsho>(3, 9, PLAYER1, grid);
        placeKoma<Ginsho>(7, 9, PLAYER1, grid);
        placeKoma<Kinsho>(4, 9, PLAYER1, grid);
        placeKoma<Kinsho>(6, 9, PLAYER1, grid);
        placeKoma<Ousho>(5, 9, PLAYER1, grid);

        //Player2
        placeKoma<Fu>(1, 3, PLAYER2, grid);
        placeKoma<Fu>(2, 3, PLAYER2, grid);
        placeKoma<Fu>(3, 3, PLAYER2, grid);
        placeKoma<Fu>(4, 3, PLAYER2, grid);
        placeKoma<Fu>(5, 3, PLAYER2, grid);
        placeKoma<Fu>(6, 3, PLAYER2, grid);
        placeKoma<Fu>(7, 3, PLAYER2, grid);
        placeKoma<Fu>(8, 3, PLAYER2, grid);
        placeKoma<Fu>(9, 3, PLAYER2, grid);
        placeKoma<Kakugyo>(2, 2, PLAYER2, grid);
        placeKoma<Hisha>(8, 2, PLAYER2, grid);
        placeKoma<Kyosha>(1, 1, PLAYER2, grid);
        placeKoma<Kyosha>(9, 1, PLAYER2, grid);
        placeKoma<Keima>(2, 1, PLAYER2, grid);
        placeKoma<Keima>(8, 1, PLAYER2, grid);
        placeKoma<Ginsho>(3, 1, PLAYER2, grid);
        placeKoma<Ginsho>(7, 1, PLAYER2, grid);
        placeKoma<Kinsho>(4, 1, PLAYER2, grid);
        placeKoma<Kinsho>(6, 1, PLAYER2, grid);
        placeKoma<Ousho>(5, 1, PLAYER2, grid);        
    }
    //Handicap Match
    Board(int op){

    }

    ~Board(){
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                delete grid[i][j];
            }
        }
    }

    void show(){
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
};

class Player{
public:
    bool turn;
    vector<Koma*> tegoma;

    Player(bool t) : turn(t){};
    void makeMove(){};
    void getKoma(){};
    void makePromoted(){};
};

int main(){
    bool currentTurn = PLAYER1;
    Player player1(PLAYER1), player2(PLAYER2);
    Board board;

    board.show();

    return 0;
}