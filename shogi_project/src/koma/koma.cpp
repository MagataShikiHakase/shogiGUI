#include "koma/koma.h"

Koma::Koma(int x, int y, bool t) : x(x), y(y), turn(t){
    promoted = false;
}
        
Koma::~Koma() {}
