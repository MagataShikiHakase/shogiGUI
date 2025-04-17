//done
#pragma once

#include <utility>
#include "koma.h"

class Fu : public Koma{
public:
    Fu(pair<int, int> p, bool t);
    bool validMove(pair<int, int> after, bool turn) override;
};