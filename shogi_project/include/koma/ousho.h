//done
#pragma once

#include "koma.h"

class Ousho : public Koma{
public:
    Ousho(pair<int, int> p, bool t);
    bool validMove(pair<int, int> after, bool turn) override;
};