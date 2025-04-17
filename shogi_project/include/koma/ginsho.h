//done
#pragma once

#include "koma.h"

class Ginsho : public Koma{
public:
    Ginsho(pair<int, int> p, bool t);
    bool validMove(pair<int, int> after, bool turn) override;
};