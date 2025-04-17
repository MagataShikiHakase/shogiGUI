#pragma once

#include "koma.h"

class Ginsho : public Koma{
public:
    Ginsho(int x, int y, bool t);
    bool validMove(int afterX, int afterY, bool turn) override;
};