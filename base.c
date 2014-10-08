#include "base.h"

struct Base base_generate(uint8_t l)
{
    struct Base b;
    b.l = l;
    b.d = int_pow(2, l);
    return b;
}
