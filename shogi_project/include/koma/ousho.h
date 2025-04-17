#pragma once

#include "koma.h"

class Ousho : public Koma{
public:
    Ousho(int x, int y, bool t);
    bool validMove(int afterX, int afterY, bool turn) override;
};