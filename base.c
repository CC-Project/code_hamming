#include "base.h"

struct Base base_generate(uint8_t d, uint8_t l)
{
    struct Base b;
    b.l = l;
    b.d = d;
    return b;
}
