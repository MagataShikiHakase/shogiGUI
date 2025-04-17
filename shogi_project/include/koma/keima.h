//done
#pragma once

#include "koma.h"

class Keima : public Koma{
public:
    Keima(pair<int, int> p, bool t);
    bool validMove(pair<int, int> after, bool turn) override;
};