//done
#pragma once

#include "koma.h"

class Kyosha : public Koma{
public:
    Kyosha(pair<int, int> p, bool t);
    bool validMove(pair<int, int> after, bool turn) override;
};