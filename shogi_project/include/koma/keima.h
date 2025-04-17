#pragma once

#include "koma.h"

class Keima : public Koma{
public:
    Keima(int x, int y, bool t);
    bool validMove(int afterX, int afterY, bool turn) override;
};