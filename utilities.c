#include "utilities.h"

uint16_t int_pow(uint16_t a, uint16_t b)
{
    uint16_t r = 1;

    for(uint16_t i = 0; i < b; i++)
        r = r * a;

    return r;
}

void print_var_bits(uint8_t var)
{
    int8_t i;
    printf("0b");
    for(i = 7; i >= 0; i--)
        printf( "%d", (var & (1 << i)) >> i );

    printf("\n");
}
