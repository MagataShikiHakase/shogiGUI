#include <iostream>
#include <vector>
#include <unistd.h> // getopt
#include <cmath>
#include <algorithm> //remove, erase

using namespace std;

enum class Handicap {
    Hirate,
    KyoOchi,
    KakuOchi,
    HishaOchi,
    NimaiOchi,
    YonmaiOchi,
    RokumaiOchi,
    HachimaiOchi,
    JumaiOchi
};

Handicap handicapFromString(const std::string& str) {
    if (str == "平手" || str == "hirate") return Handicap::Hirate;
    if (str == "香落ち" || str == "kyo") return Handicap::KyoOchi;
    if (str == "角落ち" || str == "kaku") return Handicap::KakuOchi;
    if (str == "飛車落ち" || str == "hisha") return Handicap::HishaOchi;
    if (str == "二枚落ち" || str == "nimai") return Handicap::NimaiOchi;
    if (str == "四枚落ち" || str == "yonmai") return Handicap::YonmaiOchi;
    if (str == "六枚落ち" || str == "rokumai") return Handicap::RokumaiOchi;
    if (str == "八枚落ち" || str == "hachimai") return Handicap::HachimaiOchi;
    if (str == "十枚落ち" || str == "jumai") return Handicap::JumaiOchi;
    throw std::invalid_argument("Unknown handicap type: " + str);
}

std::string handicapToString(Handicap h) {
    switch (h) {
        case Handicap::Hirate: return "平手";
        case Handicap::KyoOchi: return "香落ち";
        case Handicap::KakuOchi: return "角落ち";
        case Handicap::HishaOchi: return "飛車落ち";
        case Handicap::NimaiOchi: return "二枚落ち";
        case Handicap::YonmaiOchi: return "四枚落ち";
        case Handicap::RokumaiOchi: return "六枚落ち";
        case Handicap::HachimaiOchi: return "八枚落ち";
        case Handicap::JumaiOchi: return "十枚落ち";
    }
    return "不明";
}

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

bool isNotSurroundingGrid(pair<int, int> ouPos, pair<int, int> attackKomaPos){
    if((abs(ouPos.first - attackKomaPos.first) > 1) || (abs(ouPos.second - attackKomaPos.second) > 1))
        return true;

    return false;
}

class Game{
public:
    int turnCount;
    string kifu;

    Game(string s){
        turnCount = 1;
        kifu = s + "\n";
    };
    void addKifu(pair<int, int> from, pair<int, int> to, string komaType, player_turn pt, bool promotionOrNot){
        kifu += to_string(turnCount) + " " + ((pt == PLAYER1) ? "▲" : "△") + to_string(to.first) + to_string(to.second);
        if((komaType == "TO" || komaType == "NY" || komaType == "NE" || komaType == "NG" || komaType == "UM" || komaType == "RY") && promotionOrNot){
            if(komaType == "TO")
                kifu += "FU nari";
                    
            if(komaType == "NY")
                kifu += "KY nari";
                    
            if(komaType == "NE")
                kifu += "KE nari";
                
            if(komaType == "NG")
                kifu += "GI nari";
                    
            if(komaType == "UM")
                    kifu += "KA nari";
                    
            if(komaType == "RY")
                kifu += "HI nari";    
            }
        else{
            kifu += komaType;
                    //turn PLAYER1
            if((komaType == "FU" || komaType == "KY" || komaType == "KE" || komaType == "GI" || komaType == "KA" || komaType == "HI") && (!promotionOrNot) && ((to.second >= 1  && to.second <= 3) || (from.second >= 1 && from.second <= 3)) && pt == PLAYER1){
                kifu += " narazu";
            }
            //turn PLAYER2
            else if((komaType == "FU" || komaType == "KY" || komaType == "KE" || komaType == "GI" || komaType == "KA" || komaType == "HI") && (!promotionOrNot) && ((to.second >= 7  && to.second <= 9) || (from.second >= 7 && from.second <= 9)) && pt == PLAYER2){
                kifu += " narazu";
            }
        }
        kifu += ((from.first == 0) ? " Uti" : (" (" + to_string(from.first) + to_string(from.second) + ")")) + "\n";

        //kifu += to_string(turnCount) + " " + ((pt == PLAYER1) ? "▲" : "△") + to_string(to.first) + to_string(to.second) + komaType + ((from.first == 0) ? " Uti" : (" (" + to_string(from.first) + to_string(from.second) + ")")) + "\n";
    }
    void show(){
        cout << kifu << endl;
    }
    bool sennnitite();
    bool outesennnitite();
};

class Koma{
public:
    pair<int, int> pos;
    string type;
    player_turn turn;
    bool promoted;

    Koma(pair<int,int> p, player_turn t) : pos(p), turn(t) {
        promoted = false;
    }
    virtual ~Koma() {};
    virtual bool validMove(pair<int, int> after) = 0;
    void changePosition(pair<int, int> after){
        pos = after;
    }
    virtual void promote() = 0;
    virtual void demote() = 0;
};

class Fu : public Koma{
public:
    Fu(pair<int, int> p, player_turn t) : Koma(p, t){ type = "FU"; }

    bool validMove(pair<int, int> after) override{
        //Fu move
        if(!promoted){
            //turn == PLAYER1
            if(turn == PLAYER1){
                if(pos.first == after.first && pos.second == after.second + 1){
                    return true;
                }
            }
            //turn == PLAYER2
            else{
                if(pos.first == after.first && pos.second == after.second - 1){
                    return true;
                }
            }
        }
        //Tokin move
        else{
            //turn == PLAYER1
        if(turn == PLAYER1){
            if((abs(pos.first - after.first) <= 1 && pos.second == after.second + 1) || (abs(pos.first - after.first) == 1 && pos.second == after.second) || (pos.first == after.first && pos.second == after.second - 1)){
                return true;
            }
        }
        //turn == PLAYER2
        else{
            if((abs(pos.first - after.first) <= 1 && pos.second == after.second - 1) || (abs(pos.first - after.first) == 1 && pos.second == after.second) || (pos.first == after.first && pos.second == after.second + 1)){
                return true;
            }
        }
        }
        return false;
    }

    void promote() override{
        promoted = true;
        type = "TO";
    }
    void demote() override{
        promoted = false;
        type = "FU";
    }
};

class Kyosha : public Koma{
public:
    Kyosha(pair<int, int> p, player_turn t) : Koma(p, t){ type = "KY"; }

    bool validMove(pair<int, int> after) override{
        //Kyosya move
        if(!promoted){
            if(turn == PLAYER1){
                if(pos.first == after.first && pos.second > after.second){
                    return true;
                }
            }
            else{
                if(pos.first == after.first && pos.second < after.second){
                    return true;
                }
            }
        }
        //NariKyo move
        else{
            //turn == PLAYER1
            if(turn == PLAYER1){
                if((abs(pos.first - after.first) <= 1 && pos.second == after.second + 1) || (abs(pos.first - after.first) == 1 && pos.second == after.second) || (pos.first == after.first && pos.second == after.second - 1)){
                    return true;
                }
            }
            //turn == PLAYER2
            else{
                if((abs(pos.first - after.first) <= 1 && pos.second == after.second - 1) || (abs(pos.first - after.first) == 1 && pos.second == after.second) || (pos.first == after.first && pos.second == after.second + 1)){
                    return true;
                }
            }
        }
        return false;   
    }

    void promote() override{
        promoted = true;
        type = "NY";
    }
    void demote() override{
        promoted = false;
        type = "KY";
    }
};

class Keima : public Koma{
public:
    Keima(pair<int, int> p, player_turn t) : Koma(p, t){ type = "KE"; }
    bool validMove(pair<int, int> after) override{
        //Keima move
        if(!promoted){
            //turn == PLAYER1
            if(turn == PLAYER1){
                if(abs(pos.first - after.first) == 1 && pos.second == after.second + 2){
                    return true;
                }
            }
            //turn == PLAYER2
            else{
                if(abs(pos.first - after.first) == 1 && pos.second == after.second - 2){
                    return true;
                }
            }
        }
        //NariKei move
        else{
            //turn == PLAYER1
            if(turn == PLAYER1){
                if((abs(pos.first - after.first) <= 1 && pos.second == after.second + 1) || (abs(pos.first - after.first) == 1 && pos.second == after.second) || (pos.first == after.first && pos.second == after.second - 1)){
                    return true;
                }
            }
            //turn == PLAYER2
            else{
                if((abs(pos.first - after.first) <= 1 && pos.second == after.second - 1) || (abs(pos.first - after.first) == 1 && pos.second == after.second) || (pos.first == after.first && pos.second == after.second + 1)){
                    return true;
                }
            }
        }
        return false;
    }

    void promote() override{
        promoted = true;
        type = "NE";
    }
    void demote() override{
        promoted = false;
        type = "KE";
    }
};

class Ginsho : public Koma{
public:
    Ginsho(pair<int, int> p, player_turn t) : Koma(p, t){ type = "GI"; }
    bool validMove(pair<int, int> after) override{
        //Ginsho move
        if(!promoted){
            //turn == PLAYER1
            if(turn == PLAYER1){
                if((abs(pos.first - after.first) <= 1 && pos.second == after.second + 1) || (abs(pos.first - after.first) == 1 && pos.second == after.second - 1)){
                    return true;
                }
            }
            //turn == PLAYER2
            else{
                if((abs(pos.first - after.first) <= 1 && pos.second == after.second - 1) || (abs(pos.first - after.first) == 1 && pos.second == after.second + 1)){
                    return true;
                }
            }
        }
        //NariGin move
        else{
            //turn == PLAYER1
            if(turn == PLAYER1){
                if((abs(pos.first - after.first) <= 1 && pos.second == after.second + 1) || (abs(pos.first - after.first) == 1 && pos.second == after.second) || (pos.first == after.first && pos.second == after.second - 1)){
                    return true;
                }
            }
            //turn == PLAYER2
            else{
                if((abs(pos.first - after.first) <= 1 && pos.second == after.second - 1) || (abs(pos.first - after.first) == 1 && pos.second == after.second) || (pos.first == after.first && pos.second == after.second + 1)){
                    return true;
                }
            }
        }
        return false;
    }

    void promote() override{
        promoted = true;
        type = "NG";
    }
    void demote() override{
        promoted = false;
        type = "GI";
    }
};

class Kinsho : public Koma{
public:
    Kinsho(pair<int, int> p, player_turn t) : Koma(p, t){ type = "KI"; }
    bool validMove(pair<int, int> after) override{
        //turn == PLAYER1
        if(turn == PLAYER1){
            if((abs(pos.first - after.first) <= 1 && pos.second == after.second + 1) || (abs(pos.first - after.first) == 1 && pos.second == after.second) || (pos.first == after.first && pos.second == after.second - 1)){
                return true;
            }
        }
        //turn == PLAYER2
        else{
            if((abs(pos.first - after.first) <= 1 && pos.second == after.second - 1) || (abs(pos.first - after.first) == 1 && pos.second == after.second) || (pos.first == after.first && pos.second == after.second + 1)){
                return true;
            }
        }
        return false;
    }

    void promote() override {};
    void demote() override {};
};

class Kakugyo : public Koma{
public:
    Kakugyo(pair<int, int> p, player_turn t) : Koma(p, t){ type = "KA"; }
    bool validMove(pair<int, int> after) override{
        //Kakugyo move
        if(!promoted){
            if(abs(pos.first - after.first) == abs(pos.second - after.second))
                return true;     
        }
        //Uma move
        else{
            if((abs(pos.first - after.first) == abs(pos.second - after.second)) || (abs(pos.first - after.first) <= 1 && abs(pos.second - after.second) <= 1 && !(pos.first == after.first && pos.second == after.second)))
                return true;
        }
        return false;
    }
    void promote() override{
        promoted = true;
        type = "UM";
    }
    void demote() override{
        promoted = false;
        type = "KA";
    }
};

class Hisha : public Koma{
public:
    Hisha(pair<int, int> p, player_turn t) : Koma(p, t){ type = "HI"; }
    bool validMove(pair<int, int> after) override{
        //Ryuou move
        if(!promoted){
            if((pos.first == after.first && pos.second != after.second) || (pos.first != after.first && pos.second == after.second))
                return true;
        }
        else{
            if((pos.first == after.first && pos.second != after.second) || (pos.first != after.first && pos.second == after.second) || (abs(pos.first - after.first) <= 1 && abs(pos.second - after.second) <= 1 && !(pos.first == after.first && pos.second == after.second)))
                return true;
        }      
        return false;
    }
    void promote() override{
        promoted = true;
        type = "RY";
    }
    void demote() override{
        promoted = false;
        type = "HI";
    }
};

class Ousho : public Koma{
public:
    Ousho(pair<int, int> p, player_turn t) : Koma(p, t){ type = "OU"; }
    bool validMove(pair<int, int> after) override{
        //turn == PLAYER1&2
        if(abs(pos.first - after.first) <= 1 && abs(pos.second - after.second) <= 1 && !(pos.first == after.first && pos.second == after.second)){
            return true;
        }
        return false;
    }
    void promote() override {};
    void demote() override {};
};

class Player{
public:
    string name;
    player_turn turn;
    vector<Koma*> tegoma;

    Player(player_turn t, string n) : turn(t), name(n){};
    void getKoma(Koma* k){
        k->turn = turn;
        k->pos = {0, 0};
        //promoted komaなら戻す
        tegoma.push_back(k);
        for(int i = 0; i < tegoma.size(); i++){
            cout << tegoma[i]->type << " ";
        }
        cout << endl;
    }
    void getTegoma() const {
        if(turn == PLAYER1){
            for(int i = 0; i < tegoma.size(); i++){
                cout << tegoma[i]->type << "(" << 0 << " " << i << ")  ";
            }
        cout << endl;
        }
        else{
            for(int i = 0; i < tegoma.size(); i++){
                cout << "\033[34m" << tegoma[i]->type << "(" << 0<< " " << i << ")  " << "\033[0m";
            }
        cout << endl;
        }
    }
    
};



template <typename T>
void placeKoma(int x_shogiIndex, int y_shogiIndex, player_turn turn, Koma* grid[9][9]){
    grid[y_shogiIndex_to_x_arrayIndex(y_shogiIndex)][x_shogiIndex_to_y_arrayIndex(x_shogiIndex)] = new T(x_shogiIndex, y_shogiIndex, turn);
}

class Board {
public:
    Koma* grid[9][9];

    Board(Handicap h = Handicap::Hirate) {
        // 全マス nullptr に初期化
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                grid[i][j] = nullptr;
            }
        }

        // 平手の初期配置
        setupHirate();

        // ハンデ戦の場合は駒を取り除く
        applyHandicap(h);
    }

    ~Board() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                delete grid[i][j];
            }
        }
    }

    void show(player_turn currentTurn, const Player& p1, const Player& p2) {
        if(currentTurn == PLAYER1){
            p2.getTegoma();
            cout << "  ";
            for (int i = 9; i > 0; i--) cout << i << "    ";
            cout << "\n----------------------------------------------" << endl;

            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    cout << "|";
                    if (grid[i][j] == nullptr)
                        cout << "    ";
                    else if (grid[i][j]->turn == PLAYER1)
                        cout << " " << grid[i][j]->type << " ";
                    else
                        cout << " \033[34m" << grid[i][j]->type << "\033[0m ";
                }
                cout << "| " << i + 1 << endl;
                cout << "----------------------------------------------" << endl;
            }
            p1.getTegoma();
        }
        else{
            p1.getTegoma();
            cout << "  ";
            for (int i = 9; i > 0; i--) cout << 10 - i << "    ";
            cout << "\n----------------------------------------------" << endl;

            for (int i = 8; i >= 0; i--) {
                for (int j = 8; j >= 0; j--) {
                    cout << "|";
                    if (grid[i][j] == nullptr)
                        cout << "    ";
                    else if (grid[i][j]->turn == PLAYER1)
                        cout << " " << grid[i][j]->type << " ";
                    else
                        cout << " \033[34m" << grid[i][j]->type << "\033[0m ";
                }
                cout << "| " << i + 1  << endl;
                cout << "----------------------------------------------" << endl;
                
            }
            p2.getTegoma();
        }
    }

    bool hasOwnPieceAt(pair<int,int> from, player_turn player) const {
        if(grid[y_shogiIndex_to_x_arrayIndex(from.second)][x_shogiIndex_to_y_arrayIndex(from.first)] != nullptr && grid[y_shogiIndex_to_x_arrayIndex(from.second)][x_shogiIndex_to_y_arrayIndex(from.first)]->turn == player)
            return true;
        
        cout << "Constrain: You can only move your piece FROM the grid where your piece is at." << endl;
        return false;
    }

    bool isNotDestinationOccupiedByOwn(pair<int,int> to, player_turn player) const {
        if(grid[y_shogiIndex_to_x_arrayIndex(to.second)][x_shogiIndex_to_y_arrayIndex(to.first)] == nullptr || grid[y_shogiIndex_to_x_arrayIndex(to.second)][x_shogiIndex_to_y_arrayIndex(to.first)]->turn != player)
            return true;
        
        cout << "Constrain: You can only move your piece TO the grid where your piece ISN'T at." << endl;
        return false;
    }

    bool canMoveKY(pair<int,int> from, pair<int,int> to, player_turn p, Koma* k) const {
        if(p == PLAYER1){
            for(int i = from.second - 1; i > to.second; i--){
                cout << to.first << " " << i << endl;
                if(grid[y_shogiIndex_to_x_arrayIndex(i)][x_shogiIndex_to_y_arrayIndex(from.first)] != nullptr){
                    cout << "Constrain: Kyosya can't be over any your and opponent's pieces." << endl;
                    return false;
                }
            }
        }
        else{
            for(int i = from.second + 1; i < to.second; i++){
                if(grid[y_shogiIndex_to_x_arrayIndex(i)][x_shogiIndex_to_y_arrayIndex(from.first)] != nullptr){
                    cout << "Constrain: Kyosya can't be over any your and opponent's pieces." << endl;
                    return false;
                }
            }

        }
        return true;
    }

    bool canMoveHI(pair<int,int> from, pair<int,int> to, player_turn p, Koma* k) const {
    //Move vertically
    if(from.first == to.first){
        int step = (to.second > from.second) ? 1 : -1;
        for(int i = from.second + step; i != to.second; i += step){
            if(grid[y_shogiIndex_to_x_arrayIndex(i)][x_shogiIndex_to_y_arrayIndex(from.first)] != nullptr){
                cout << "Constrain: Hisha can't jump over pieces." << endl;
                return false;
            }
        }
    }
    //Move holizontaly
    else if(from.second == to.second){
        int step = (to.first > from.first) ? 1 : -1;
        for(int i = from.first + step; i != to.first; i += step){
            if(grid[y_shogiIndex_to_x_arrayIndex(from.second)][x_shogiIndex_to_y_arrayIndex(i)] != nullptr){
                cout << "Constrain: Hisha can't jump over pieces." << endl;
                return false;
            }
        }
    }
    //Other
    else {
        return false;
    }

    return true;
}


   bool canMoveKA(pair<int,int> from, pair<int,int> to, player_turn p, Koma* k) const {
    int dx = to.first - from.first;
    int dy = to.second - from.second;

    // 斜めじゃない場合はNG
    if(abs(dx) != abs(dy)){
        return false;
    }

    // 移動方向を求める（±1）
    int stepX = (dx > 0) ? 1 : -1;
    int stepY = (dy > 0) ? 1 : -1;

    int x = from.first + stepX;
    int y = from.second + stepY;

    // 経路上の駒をチェック（終点は含めない）
    while(x != to.first && y != to.second){
        if(grid[y_shogiIndex_to_x_arrayIndex(y)][x_shogiIndex_to_y_arrayIndex(x)] != nullptr){
            cout << "Constrain: Kakugyo can't jump over pieces." << endl;
            return false;
        }
        x += stepX;
        y += stepY;
    }

    return true;
}

    bool canSelectAndMove(pair<int,int> from, pair<int,int> to, player_turn player, Koma* k) const {
        bool flag = true;
        if(k->type == "KY"){
            if(!canMoveKY(from, to, player, k))
                flag = false;
        }
        if(k->type == "HI"/*|| k->type == "RY"*/){
            if(!canMoveHI(from, to, player, k))
                flag = false;
        }
        if(k->type == "KA" /*|| k->type == "UM"*/){
            if(!canMoveKA(from, to, player, k))
                flag = false;
        }

        if(!(hasOwnPieceAt(from, player) && isNotDestinationOccupiedByOwn(to, player)))
            flag = false;

        return flag;
    }

    void movement(pair<int, int> from, pair<int, int> to){
        grid[y_shogiIndex_to_x_arrayIndex(to.second)][x_shogiIndex_to_y_arrayIndex(to.first)] = grid[y_shogiIndex_to_x_arrayIndex(from.second)][x_shogiIndex_to_y_arrayIndex(from.first)];
        grid[y_shogiIndex_to_x_arrayIndex(from.second)][x_shogiIndex_to_y_arrayIndex(from.first)] = nullptr;
    }

    bool canPutKY(pair<int, int> to, player_turn t){
        if(t == PLAYER1){
            if(to.second == 1){
                cout << "Constrain: You CAN'T put the piece that can't be moved anymore." << endl;
                return false;
            }
        }
        else{
            if(to.second == 9){
                cout << "Constrain: You CAN'T put the piece that can't be moved anymore." << endl;
                return false;
            }
        }
        return true;
    }

    bool canPutKE(pair<int, int> to, player_turn t){
        if(t == PLAYER1){
            if(to.second == 1 || to.second == 2){
                cout << "Constrain: You CAN'T put the piece that can't be moved anymore." << endl;
                return false;
            }
        }
        else{
            if(to.second == 9 || to.second == 8){
                cout << "Constrain: You CAN'T put the piece that can't be moved anymore." << endl;
                return false;
            }
        }
        return true;
    }
    bool canPutFU(Koma* k, pair<int, int> to, player_turn t){
        bool flag = true;
        if(t == PLAYER1){
            if(to.second == 1){
                cout << "Constrain: You CAN'T put the piece that can't be moved anymore." << endl;
                flag = false;
            }
        }
        else{
            if(to.second == 9){
                cout << "Constrain: You CAN'T put the piece that can't be moved anymore." << endl;
                flag = false;
            }
        }

        //Check 二歩 constrain
        for(int i = 0; i < 9; i++){
            if(grid[y_shogiIndex_to_x_arrayIndex(i + 1)][x_shogiIndex_to_y_arrayIndex(to.first)] == nullptr){
                continue;
            }
            if(grid[y_shogiIndex_to_x_arrayIndex(i + 1)][x_shogiIndex_to_y_arrayIndex(to.first)]->type == "FU"){
                if(grid[y_shogiIndex_to_x_arrayIndex(i + 1)][x_shogiIndex_to_y_arrayIndex(to.first)]->turn == t){
                    cout << "Constrain: Violates the rule of NIFU." << endl;
                    flag = false;
                }
            }
        }
        return flag;
    }

    bool canPut(Koma* k, pair<int, int> to, player_turn t){
        bool flag = true;
        if(k->type == "FU"){
            if(!canPutFU(k, to, t))
                flag = false;
        }
        if(k->type == "KY"){
            if(!canPutKY(to, t))
                flag = false;
        }
        if(k->type == "KE"){
            if(!canPutKE(to, t))
                flag = false;
        }

        if(grid[y_shogiIndex_to_x_arrayIndex(to.second)][x_shogiIndex_to_y_arrayIndex(to.first)] != nullptr){
            cout << "Constrain: You ONLY can put the piece to the vacant grid." << endl;
            flag = false;
        }

        return flag;
    }

    void putKoma(Koma* k, pair<int, int> to){
        grid[y_shogiIndex_to_x_arrayIndex(to.second)][x_shogiIndex_to_y_arrayIndex(to.first)] = k;
    }

    pair<int, int> getOpponentOuPosition(player_turn pt){
        for(int i = 1; i <= 9; i++){
            for(int j = 1; j <= 9; j++){
                if(grid[y_shogiIndex_to_x_arrayIndex(j)][x_shogiIndex_to_y_arrayIndex(i)] == nullptr)
                    continue;
                
                if((grid[y_shogiIndex_to_x_arrayIndex(j)][x_shogiIndex_to_y_arrayIndex(i)]->type == "OU") && (grid[y_shogiIndex_to_x_arrayIndex(j)][x_shogiIndex_to_y_arrayIndex(i)]->turn != pt))
                    return {i, j};
            }
        }
        cout << "No " << ((pt == PLAYER1) ? "PLAYER2" : "PLAYER1") << "'s OU in borad" << endl;
        
    }

    vector<pair<pair<int, int>, pair<int, int>>> getAttackGrids(player_turn pt){
        vector<pair<pair<int, int>, pair<int, int>>> attackGrids;
        for(int y = 1; y <= 9; y++){
            for(int x = 1; x <= 9; x++){
                Koma* k = grid[y_shogiIndex_to_x_arrayIndex(y)][x_shogiIndex_to_y_arrayIndex(x)];
                if(k == nullptr || k->turn != pt) continue;

                string type = k->type;

                if(type == "KY"){
                    int step = (pt == PLAYER1 ? -1 : 1);
                    int ny = y + step;
                    while(ny >= 1 && ny <= 9){
                        if(grid[y_shogiIndex_to_x_arrayIndex(ny)][x_shogiIndex_to_y_arrayIndex(x)] != nullptr){
                            attackGrids.push_back({{x,y},{x,ny}});
                            break; // 駒にぶつかったら終了
                        }
                        attackGrids.push_back({{x,y},{x,ny}});
                        ny += step;
                    }
                }
                else if(type == "HI" || type == "RY"){ // 飛車
                    // 縦横4方向ループ
                    vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
                    for(auto [dx,dy] : dirs){
                        int nx = x + dx, ny = y + dy;
                        while(nx >= 1 && nx <= 9 && ny >= 1 && ny <= 9){
                            if(grid[y_shogiIndex_to_x_arrayIndex(ny)][x_shogiIndex_to_y_arrayIndex(nx)] != nullptr){
                                attackGrids.push_back({{x,y},{nx,ny}});
                                break;
                            }
                            attackGrids.push_back({{x,y},{nx,ny}});
                            nx += dx; ny += dy;
                        }
                    }
                    if(type == "RY"){
                        if(x + 1 <= 9 && y + 1 <= 9)
                            attackGrids.push_back({{x,y},{x + 1,y + 1}});
                        if(x - 1 >= 1 && y + 1 <= 9)
                            attackGrids.push_back({{x,y},{x - 1,y + 1}});
                        if(x - 1 >= 1 && y - 1 >= 1)
                            attackGrids.push_back({{x,y},{x - 1,y - 1}});
                        if(x + 1 <= 9 && y - 1 >= 1)
                            attackGrids.push_back({{x,y},{x + 1,y - 1}});
                    }
                }
                else if(type == "KA" || type == "UM"){ // 角
                    vector<pair<int,int>> dirs = {{1,1},{1,-1},{-1,1},{-1,-1}};
                    for(auto [dx,dy] : dirs){
                        int nx = x + dx, ny = y + dy;
                        while(nx >= 1 && nx <= 9 && ny >= 1 && ny <= 9){
                            if(grid[y_shogiIndex_to_x_arrayIndex(ny)][x_shogiIndex_to_y_arrayIndex(nx)] != nullptr){
                                attackGrids.push_back({{x,y},{nx,ny}});
                                break;
                            }
                            attackGrids.push_back({{x,y},{nx,ny}});
                            nx += dx; ny += dy;
                        }
                    }

                    if(type == "UM"){
                        if(x + 1 <= 9)
                            attackGrids.push_back({{x,y},{x + 1,y}});
                        if(x - 1 >= 1)
                            attackGrids.push_back({{x,y},{x - 1,y}});
                        if(y + 1 <= 9)
                            attackGrids.push_back({{x,y},{x,y + 1}});
                        if(y - 1 >= 1)
                            attackGrids.push_back({{x,y},{x,y - 1}});
                    }
                }
                else {
                    // それ以外の駒（歩、桂、銀、金、玉…）
                    for(int ny = 1; ny <= 9; ny++){
                        for(int nx = 1; nx <= 9; nx++){
                            if(nx == x && ny == y) continue;
                            if(k->validMove({nx,ny})){
                                attackGrids.push_back({{x,y},{nx,ny}});
                            }
                        }
                    }
                }
            }
        }
        return attackGrids;
    }

    bool komaHasHimo(pair<int, int> komaPos, player_turn pt){
        vector<pair<pair<int, int>, pair<int, int>>> attackGrids = getAttackGrids(pt);
        
        for(int i = 0; i < attackGrids.size(); i++){
            if(komaPos == attackGrids[i].second){
                return true;
            }
        }
        return false;
    }

    //Number of elements: 0->No Oute, 1->Oute, 2->RyoOute
    vector<pair<pair<int, int>, pair<int, int>>> judgeOute(player_turn pt){

        pair<int, int> ouPosition = getOpponentOuPosition(pt);
        vector<pair<pair<int, int>, pair<int, int>>> attackGrids = getAttackGrids(pt), ans;

        cout << "OU position {" << ouPosition.first << "," << ouPosition.second << "}\n" << "attaked Grids: " << endl;
        for(int i = 0; i < attackGrids.size(); i++){
            cout << "From{" << attackGrids[i].first.first << "," << attackGrids[i].first.second << "}" << " TO{" << attackGrids[i].second.first << "," << attackGrids[i].second.second << "}" << endl; 
        }
        
        for(int i = 0; i < attackGrids.size(); i++){
            if(ouPosition == attackGrids[i].second){
                ans.push_back({attackGrids[i]});
            }
        }
        return ans;
    }

    bool judgeTsumi(player_turn pt){

        vector<pair<pair<int, int>, pair<int, int>>> outeGomas = judgeOute(pt);

        if(outeGomas.empty()){
            cout << "Not Oute" << endl;
            return false;
        }
        player_turn notPt = (pt == PLAYER1)? PLAYER2 : PLAYER1;

        //get valid move of OU
        vector<pair<int, int>> ouValidMove,gyokuNoNigemichi;
        pair<int, int> ouPosition = getOpponentOuPosition(pt);
        for(int i = 1; i <= 9; i++){
            for(int j = 1; j <= 9; j++){
                if(grid[y_shogiIndex_to_x_arrayIndex(ouPosition.second)][x_shogiIndex_to_y_arrayIndex(ouPosition.first)]->validMove({i,j}) && canSelectAndMove(ouPosition, {i,j}, notPt, grid[y_shogiIndex_to_x_arrayIndex(ouPosition.second)][x_shogiIndex_to_y_arrayIndex(ouPosition.first)]) && grid[y_shogiIndex_to_x_arrayIndex(j)][x_shogiIndex_to_y_arrayIndex(i)] == nullptr)
                    ouValidMove.push_back({i,j});
            }
        }
        //show ou valid grids
        cout << "OU Position: " << "(" << ouPosition.first << ", " << ouPosition.second << ")" << endl;
        for(int i = 0; i < ouValidMove.size(); i++){
            cout << "(" << ouValidMove[i].first << ", " << ouValidMove[i].second << ")" << endl;
        }

        vector<pair<pair<int, int>, pair<int, int>>> attackGrids = getAttackGrids(pt);

        //check valid move
        gyokuNoNigemichi = ouValidMove;

        for(int i = 0; i < ouValidMove.size(); i++){
            for(int j = 0; j < attackGrids.size(); j++){
                if(ouValidMove[i] == attackGrids[j].second){
                    cout << "i:" << i << " j:" << j << " (" << ouValidMove[i].first << "," << ouValidMove[i].second << ")" << endl;
                    gyokuNoNigemichi.erase(remove(gyokuNoNigemichi.begin(), gyokuNoNigemichi.end(), ouValidMove[i]), gyokuNoNigemichi.end());
                }
            }
        }

        cout << "Gyoku no Nigemichi" << endl;
        for(int i = 0; i < gyokuNoNigemichi.size(); i++){
            cout << "(" << gyokuNoNigemichi[i].first << "," << gyokuNoNigemichi[i].second << ")" << endl;
        }

        //if(gyokuNoNigemichi.empty()) tsumi

        if(outeGomas.size() == 1){
            cout << "outeGomas == 1" << endl;
            bool flag = false;
            if(!gyokuNoNigemichi.empty()){
                cout << "Tip: There are at lease one move to avoid oute." << endl;
                flag = false;
            }

            
            //Oute by far position koma
            if(isNotSurroundingGrid(ouPosition, outeGomas[0].first)){
                
                cout << "oute by far position koma" << endl;
                return false; 





            }
            //Oute by surrounding position koma
            else{
                cout << "oute by surrounding position." << endl;
                //Ou can get outeGoma
                if(!komaHasHimo(outeGomas[0].first, pt)){
                    cout << "Tip: Ou can capture outeGoma." << endl;
                    flag = false;
                }

                //koma without ou can get outeGoma
                vector<pair<pair<int, int>, pair<int, int>>> opponentAttackGrids = getAttackGrids(notPt);
                cout << "First opponentAttackGrids (" << opponentAttackGrids[0].first.first << "," << opponentAttackGrids[0].first.second << ")" << endl;
                for(int i = 0; i < opponentAttackGrids.size(); i++){
                    if(outeGomas[0].first == opponentAttackGrids[i].second){
                        Koma* capturedKoma = grid[y_shogiIndex_to_x_arrayIndex(outeGomas[0].first.second)][x_shogiIndex_to_y_arrayIndex(outeGomas[0].first.first)];

                    }
                }
                
            }
            return flag;

        }
        else if(outeGomas.size() == 2){
            cout << "outeGomas == 2" << endl;
            //RyoOute
            if(isNotSurroundingGrid(ouPosition, outeGomas[0].first) && isNotSurroundingGrid(ouPosition, outeGomas[1].first)){
                if(gyokuNoNigemichi.empty()){
                    cout << "Tsumi by RyoOute" << endl;
                    return true;
                }
                cout << "Not Tsumi even it's RyoOute" << endl;
                return false;
            }
            //GijiRyouOute
            else if(isNotSurroundingGrid(ouPosition, outeGomas[0].first) || isNotSurroundingGrid(ouPosition, outeGomas[1].first)){
                pair<int, int> surroundingKoma = (isNotSurroundingGrid(ouPosition, outeGomas[0].first))? outeGomas[1].first : outeGomas[0].first;
                if(gyokuNoNigemichi.empty() && komaHasHimo(surroundingKoma, pt)){
                    cout << "Tsumi by GijiRyoOute" << endl;
                    return true;
                }
                cout << "Not Tsumi even it's GijiRyoOute" << endl;
                return false;
            }
            //Error Handling
            else{
                cout << "Not expected error even I worte this lol" << endl;
            }
            return false;
        }
        else{
            cout << "outeGomas stores more than 2 element which isn't valid input: " << outeGomas.size() << endl;
        }
        return false;
    }

 private:
    template <typename T>
    void placeKoma(pair<int, int> shogiIndex, player_turn turn) {
        grid[y_shogiIndex_to_x_arrayIndex(shogiIndex.second)]
            [x_shogiIndex_to_y_arrayIndex(shogiIndex.first)] = new T({shogiIndex.first, shogiIndex.second}, turn);
    }

    void setupHirate() {
        // Player1
        for (int x = 1; x <= 9; x++) placeKoma<Fu>({x, 7}, PLAYER1);
        placeKoma<Hisha>({2, 8}, PLAYER1);
        placeKoma<Kakugyo>({8, 8}, PLAYER1);
        placeKoma<Kyosha>({1, 9}, PLAYER1);
        placeKoma<Kyosha>({9, 9}, PLAYER1);
        placeKoma<Keima>({2, 9}, PLAYER1);
        placeKoma<Keima>({8, 9}, PLAYER1);
        placeKoma<Ginsho>({3, 9}, PLAYER1);
        placeKoma<Ginsho>({7, 9}, PLAYER1);
        placeKoma<Kinsho>({4, 9}, PLAYER1);
        placeKoma<Kinsho>({6, 9}, PLAYER1);
        placeKoma<Ousho>({5, 9}, PLAYER1);

        // Player2
        for (int x = 1; x <= 9; x++) placeKoma<Fu>({x, 3}, PLAYER2);
        placeKoma<Kakugyo>({2, 2}, PLAYER2);
        placeKoma<Hisha>({8, 2}, PLAYER2);
        placeKoma<Kyosha>({1, 1}, PLAYER2);
        placeKoma<Kyosha>({9, 1}, PLAYER2);
        placeKoma<Keima>({2, 1}, PLAYER2);
        placeKoma<Keima>({8, 1}, PLAYER2);
        placeKoma<Ginsho>({3, 1}, PLAYER2);
        placeKoma<Ginsho>({7, 1}, PLAYER2);
        placeKoma<Kinsho>({4, 1}, PLAYER2);
        placeKoma<Kinsho>({6, 1}, PLAYER2);
        placeKoma<Ousho>({5, 1}, PLAYER2);
    }

    void removePiece(pair<int, int>shogiIndex) {
        int i = y_shogiIndex_to_x_arrayIndex(shogiIndex.second);
        int j = x_shogiIndex_to_y_arrayIndex(shogiIndex.first);
        delete grid[i][j];
        grid[i][j] = nullptr;
    }

    void applyHandicap(Handicap h) {
        switch (h) {
            case Handicap::KyoOchi:
                removePiece({1, 1}); // 香車(左)
                break;
            case Handicap::KakuOchi:
                removePiece({2, 2}); // 角
                break;
            case Handicap::HishaOchi:
                removePiece({8, 2}); // 飛車
                break;
            case Handicap::NimaiOchi:
                removePiece({2, 2}); // 角
                removePiece({8, 2}); // 飛車
                break;
            case Handicap::YonmaiOchi:
                removePiece({2, 2}); // 角
                removePiece({8, 2}); // 飛車
                removePiece({1, 1});// 香車
                removePiece({9, 1});
                break;
            case Handicap::RokumaiOchi:
                removePiece({2, 2}); // 角
                removePiece({8, 2}); // 飛車
                removePiece({1, 1});// 香車
                removePiece({9, 1});
                removePiece({2, 1});// 桂馬
                removePiece({8, 1});
                break;
            case Handicap::HachimaiOchi:
                removePiece({2, 2}); // 角
                removePiece({8, 2}); // 飛車
                removePiece({1, 1});// 香車
                removePiece({9, 1});
                removePiece({2, 1});// 桂馬
                removePiece({8, 1});
                removePiece({3, 1});// 銀
                removePiece({7, 1});
                break;
            case Handicap::JumaiOchi:
                removePiece({2, 2}); // 角
                removePiece({8, 2}); // 飛車
                removePiece({1, 1});// 香車
                removePiece({9, 1});
                removePiece({2, 1});// 桂馬
                removePiece({8, 1});
                removePiece({3, 1});// 銀
                removePiece({7, 1});
                removePiece({4, 1});// 金
                removePiece({6, 1});
                break;
            default:
                break;
        }
    }
};


struct GameSettings {
    Handicap handicap;
    int timeLimit;
};


GameSettings parseOptions(int argc, char* argv[]) {
    GameSettings settings { Handicap::Hirate, 0 };

    int opt;
    while ((opt = getopt(argc, argv, "m:t:")) != -1) {
        switch (opt) {
            case 'm':
                settings.handicap = handicapFromString(optarg);
                break;
            case 't':
                settings.timeLimit = std::stoi(optarg);
                break;
        }
    }
    return settings;
}

bool validInputInBoard(pair<int, int> from, pair<int, int> to){
    if(from.first < 1 || 9 < from.first)
        return false;
    if(from.second < 1 || 9 < from.second)
        return false;
    if(to.first < 1 || 9 < to.first)
        return false;
    if(to.second < 1 || 9 < to.second)
        return false;      
    return true;
}

bool promotionProcess(pair<int, int> from, pair<int, int> to, Koma* k){
    char ans;
    if(k->turn == PLAYER1){
        if(((k->type == "FU" || k->type == "KE" || k->type == "KY") && to.second == 1) || (k->type == "KE" && to.second == 2)){
            k->promote();
            cout << k->type << "promoted" << endl;
            return true;
        }
        if((k->type == "FU" || k->type == "KE" || k->type == "KY" || k->type == "GI" || k->type == "HI" || k->type == "KA") && ((to.second >= 1  && to.second <= 3) || (from.second >= 1 && from.second <= 3))){
            while (true) {
                cout << "Do you want to promote this piece? (y/n): ";
                cin >> ans;

                if (ans == 'y' || ans == 'Y') {
                    k->promote();
                    cout << k->type << "promoted" << endl;
                    return true;
                } 
                else if (ans == 'n' || ans == 'N') {
                    cout << "Promotion skipped." << endl;
                    return false;
                } 
                else {
                    cout << "Invalid input. Please enter 'y' or 'n'." << endl;
                }
            }
        }
    }
    else{
        if(((k->type == "FU" || k->type == "KE" || k->type == "KY") && to.second == 9) || (k->type == "KE" && to.second == 8)){
            k->promote();
            cout << k->type << "promoted" << endl;
            return true;
        }
        if((k->type == "FU" || k->type == "KE" || k->type == "KY" || k->type == "GI" || k->type == "HI" || k->type == "KA") && ((to.second >= 7  && to.second <= 9) || (from.second >= 7 && from.second <= 9))){
            while (true) {
                cout << "Do you want to promote this piece? (y/n): ";
                cin >> ans;

                if (ans == 'y' || ans == 'Y') {
                    k->promote();
                    cout << k->type << "promoted" << endl;
                    return true;
                } 
                else if (ans == 'n' || ans == 'N') {
                    cout << "Promotion skipped." << endl;
                    return false;
                } 
                else {
                    cout << "Invalid input. Please enter 'y' or 'n'." << endl;
                }
            }
        }
    }
    return false;
}


int main(int argc, char* argv[]) {
    
    GameSettings settings = parseOptions(argc, argv);

    player_turn currentTurn = (settings.handicap != Handicap::Hirate) ? PLAYER2 : PLAYER1;
    Player player1(PLAYER1, "player1"), player2(PLAYER2, "player2");
    Player* currentPlayer = (currentTurn == PLAYER1) ? &player1 : &player2;
    Board board(settings.handicap);
    Game game(handicapToString(settings.handicap));

    pair<int, int> from, to;
    bool promotionOrNot;
    

    while (true) {
        cout << "\n--------------------------------------------------------------------------\n" << endl;
        cout << "Turn " << game.turnCount << "(" << ((currentTurn == PLAYER1) ? player1.name : player2.name) << ")\n" << endl;
        board.show(currentTurn, player1, player2);

        cin >> from.first >> from.second >> to.first >> to.second;
        cout << "From(" << from.first << ", " << from.second << ")" << " -> TO(" << to.first << ", " << to.second << ")\n" << endl;

        // case: put the piece form Tegoma
        if (from.first == 0) {
            // Select piece from Tegoma
            if (from.second < 0 || from.second > (int)currentPlayer->tegoma.size()) {
                cout << "Invalid hand piece index" << endl;
                continue;
            }
            Koma* komaFromTegoma = currentPlayer->tegoma[from.second];


            if (!board.canPut(komaFromTegoma, to, currentTurn)) {
                cout << "Invalid put position" << endl;
                continue;
            }

            board.putKoma(komaFromTegoma, to);
            komaFromTegoma->changePosition(to);
            currentPlayer->tegoma.erase(currentPlayer->tegoma.begin() + (from.second));
        }
        // case: Advance piece that is on the board
        else {
            if(board.grid[y_shogiIndex_to_x_arrayIndex(from.second)][x_shogiIndex_to_y_arrayIndex(from.first)] == nullptr){
                cout << "Enter the valid movement" << endl;
                continue;
            }

            Koma* currentKoma = board.grid[y_shogiIndex_to_x_arrayIndex(from.second)][x_shogiIndex_to_y_arrayIndex(from.first)];

            if(validInputInBoard(from, to) && currentKoma->turn == currentTurn && board.canSelectAndMove(from, to, currentTurn, currentKoma) && currentKoma->validMove(to)) {

                // 相手の駒を取る処理
                if(board.grid[y_shogiIndex_to_x_arrayIndex(to.second)][x_shogiIndex_to_y_arrayIndex(to.first)] != nullptr 
                && board.grid[y_shogiIndex_to_x_arrayIndex(to.second)][x_shogiIndex_to_y_arrayIndex(to.first)]->turn != currentKoma->turn) {
                    
                    cout << currentPlayer->name << " gets piece "
                        << board.grid[y_shogiIndex_to_x_arrayIndex(to.second)][x_shogiIndex_to_y_arrayIndex(to.first)]->type << endl;

                    board.grid[y_shogiIndex_to_x_arrayIndex(to.second)][x_shogiIndex_to_y_arrayIndex(to.first)]->demote();
                    currentPlayer->getKoma(board.grid[y_shogiIndex_to_x_arrayIndex(to.second)][x_shogiIndex_to_y_arrayIndex(to.first)]);
                    board.grid[y_shogiIndex_to_x_arrayIndex(to.second)][x_shogiIndex_to_y_arrayIndex(to.first)] = nullptr;
                }
                board.movement(from, to);
                currentKoma->changePosition(to);
                promotionOrNot = promotionProcess(from, to, currentKoma);
            }
            else {
                cout << "Enter the valid movement." << endl;
                continue;
            }
        }

        // Judge that game is over or not
        if(board.judgeTsumi(currentTurn)){
            game.addKifu(from, to, board.grid[y_shogiIndex_to_x_arrayIndex(to.second)][x_shogiIndex_to_y_arrayIndex(to.first)]->type, currentTurn, promotionOrNot);
            break;
        }

        // Add to write the kifu
        game.addKifu(from, to, board.grid[y_shogiIndex_to_x_arrayIndex(to.second)][x_shogiIndex_to_y_arrayIndex(to.first)]->type, currentTurn, promotionOrNot);
        promotionOrNot = false;

        // Switch the turn Information
        game.turnCount++;
        currentTurn = (currentTurn == PLAYER1) ? PLAYER2 : PLAYER1;
        currentPlayer = (currentTurn == PLAYER1) ? &player1 : &player2;
        game.show();
    }

    cout << "Winer: " << ((currentTurn == PLAYER1) ? "PLAYER1" : "PLAYER2") << endl;
}
 //2 8 5 8 6 1 7 2 5 7 5 6 4 1 3 2 5 6 5 5 1 3 1 4 5 5 5 4 1 4 1 5 1 7 1 6 5 1 5 2 5 4 5 3 y