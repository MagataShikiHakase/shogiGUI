//done
#pragma once

#include <string>
#include <utility>

using namespace std;

class Koma{
public:
    pair<int, int> pos;
    string type;
    bool turn, promoted;
    
    Koma(pair<int, int> p, bool t);
    virtual ~Koma();
    virtual bool validMove(pair<int, int> after, bool turn) = 0;
};