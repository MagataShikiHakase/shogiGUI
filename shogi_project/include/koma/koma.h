#pragma once

#include <string>
using namespace std;

class Koma{
public:
    int x, y;
    string type;
    bool turn, promoted;
    
    Koma(int x, int y, bool t);
    virtual ~Koma();
    virtual bool validMove(int afterX, int afterY, bool turn) = 0;
};