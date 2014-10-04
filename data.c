#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "data.h"

struct Data data_generate(struct Base base, uint16_t data_number)
{
    struct Data d;
    d.data_number = data_number;
    d.data_base = base;

    uint8_t n = floor((base.l * data_number-1)/8) + 1; //Number of byte needed
    d.data_array = malloc( n * sizeof(uint8_t) );

    //Sets initial values
    uint8_t i = 0;
    for(i=0; i < n; i++)
    {
        d.data_array[i] = 0;
    }
    return d;
}

void data_delete(struct Data* d)
{
    free(d);
}

uint8_t data_get(uint16_t n, struct Data* d) //Returns the n-th data stored. Starting from 0.
{
    uint16_t i = d->data_base.l * n;    // First bit containing the data. First bit is 0, to 7.
    uint8_t data = 0;
    uint8_t c = 0;

    for(c=0; c<d->data_base.l; c++) //For each bit
    {
        if ( d->data_array[i / 8] & (1 << (i%8+c)) )
            data |= (d->data_array[i / 8] & (1 << (i%8+c))) >> i%8;
        else
            data &= ~(d->data_array[i / 8] & (1 << (i%8+c))) >> i%8;
    }
    return data;
}

void data_set(uint16_t n, uint8_t data, struct Data* d) //Sets the n-th block of d to data
{
    uint16_t i = d->data_base.l * n;    // First bit containing the data. First bit is 0, to 7.
    uint8_t c = 0;
    for(c=0; c < d->data_base.l; c++) //For each bit
    {
        if ( data & (1 << c) )
            d->data_array[i / 8] |= ( ( (data & (1 << c) ) >> c) << (i%8+c));
        else
            d->data_array[i / 8] &= ~( ( (data & (1 << c) ) >> c) << (i%8+c));
    }
}
