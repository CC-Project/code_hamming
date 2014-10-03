#include "utilities.h"

uint16_t int_pow(uint8_t a, uint8_t b)
{
    uint16_t r = 1;
    uint8_t i = 0;

    for(i=0; i < b; i++)
        r = r * a;
    return r;
}

void print_var_bits(uint8_t var)
{
    int8_t i;
    printf("0b");
    for(i=7;i>=0;i--)
    {
        printf( "%d", (var & (1 << i)) >> i );
    }
    printf("\n");
}
