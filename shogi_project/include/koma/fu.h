#pragma once

#include "koma.h"

class Fu : public Koma{
public:
    Fu(int x, int y, bool t);
    bool validMove(int afterX, int afterY, bool turn) override;
};