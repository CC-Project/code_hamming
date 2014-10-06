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
    for(uint8_t i = 0; i < n; i++)
        d.data_array[i] = 0;

    return d;
}

void data_free(struct Data* d)
{
    free(d);
}

uint8_t data_get(uint16_t n, struct Data* d) //Returns the n-th data stored. Starting from 0.
{
    uint8_t l = d->data_base.l;
    uint16_t i = l * n;    // First bit containing the data. First bit is 0, to 7.
    uint8_t it = i % 8; // first bit in the table containing the data

    /*
    uint8_t data = 0;
    for(uint8_t c = 0; c < d->data_base.l; c++) //For each bit
        if ( d->data_array[i / 8] & (1 << (i%8+c)) )
            data |= (d->data_array[i / 8] & (1 << (i%8+c))) >> i%8;
        else
            data &= ~(d->data_array[i / 8] & (1 << (i%8+c))) >> i%8;
    */

    return (d->data_array[i / 8] << it) >> 8 - l;
}

void data_set(uint16_t n, uint8_t data, struct Data* d) //Sets the n-th block of d to data
{
    uint8_t l = d->data_base.l;
    uint16_t i = d->data_base.l * n;    // First bit containing the data. First bit is 0, to 7.
    uint8_t it = i % 8; // first bit in the table containing the data
    uint8_t dt = d->data_array[i / 8];

/*
    for(uint8_t c = 0; c < d->data_base.l; c++) //For each bit
        if ( data & (1 << c) )
            d->data_array[i / 8] |= ( ( (data & (1 << c) ) >> c) << (i%8+c));
        else
            d->data_array[i / 8] &= ~( ( (data & (1 << c) ) >> c) << (i%8+c));
*/
    d->data_array[i / 8] = ((data) << (8 - l - it)) |
                    ((dt >> (8 - it)) << (8 - it)) |
                    ((dt << (it + l)) >> (it + l));
}

void data_delete(uint16_t n, struct Data* d)
{
    uint8_t nb = d->data_number;

    for(uint16_t i = n; i < nb - 1; i++)
        data_set(i, data_get(i + 1, d), d);

    data_set(nb - 1, 0, d);

    d->data_number -= 1;
}

void data_show(struct Data* d)
{
    for(uint16_t i = 0; i < d->data_number; i++)
        printf("%d ", data_get(i, d));
}
