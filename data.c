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

    uint8_t data = d->data_array[i / 8];

    data <<= it;
    data >>= (8 - l);

    return data;
}

void data_set(uint16_t n, uint8_t data, struct Data* d) //Sets the n-th block of d to data
{
    uint8_t l = d->data_base.l;
    uint16_t i = l * n;    // First bit containing the data. First bit is 0, to 7.
    uint8_t it = i % 8; // first bit in the table containing the data

    uint8_t data1 = d->data_array[i / 8]; uint8_t data2 = d->data_array[i / 8];

    data1 >>= 8 - it; data1 <<= 8 - it;
    data2 <<= it + l; data2 >>= it + l;

    d->data_array[i / 8] = ((data) << (8 - l - it)) | (data1 | data2);
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
    uint8_t data;
    printf("-----------------\nShow %d data :\n", d->data_number);
    for(uint16_t i = 0; i < d->data_number; i++)
    {
        data = data_get(i, d);
        printf("%d ", data);
        printf(" | ");
        print_var_bits(data);
    }
    printf("-----------------\n\n", d->data_number);
}
