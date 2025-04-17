#pragma once

#include "koma.h"

class Kakugyo : public Koma{
public:
    Kakugyo(int x, int y, bool t);
    bool validMove(int afterX, int afterY, bool turn) override;
};