#pragma once

#include "koma.h"

class Kinsho : public Koma{
public:
    Kinsho(int x, int y, bool t);
    bool validMove(int afterX, int afterY, bool turn) override;
};