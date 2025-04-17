#pragma once

#include "koma.h"

class Hisha : public Koma{
public:
    Hisha(int x, int y, bool t);
    bool validMove(int afterX, int afterY, bool turn) override;
};