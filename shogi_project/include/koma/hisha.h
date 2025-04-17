//done
#pragma once

#include "koma.h"

class Hisha : public Koma{
public:
    Hisha(pair<int, int> p, bool t);
    bool validMove(pair<int, int> after, bool turn) override;
};