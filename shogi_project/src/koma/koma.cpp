//done
#include "koma/koma.h"

Koma::Koma(pair<int, int> p, bool t) : pos(p), turn(t){
    promoted = false;
}
        
Koma::~Koma() {}
