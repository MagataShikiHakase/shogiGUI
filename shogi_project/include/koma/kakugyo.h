//done
#pragma once

#include "koma.h"

class Kakugyo : public Koma{
public:
    Kakugyo(pair<int, int> p, bool t);
    bool validMove(pair<int, int> after, bool turn) override;
};