#pragma once

#include "koma.h"

class Kyosha : public Koma{
public:
    Kyosha(int x, int y, bool t);
    bool validMove(int afterX, int afterY, bool turn) override;
};