//done
#pragma once

#include "koma.h"

class Kinsho : public Koma{
public:
    Kinsho(pair<int, int> p, bool t);
    bool validMove(pair<int, int> after, bool turn) override;
};