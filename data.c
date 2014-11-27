#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "data.h"

struct Data data_generate(struct Base base, uint16_t data_number)
{
    struct Data d;
    d.data_number = data_number;
    d.data_base = base;

    // Dynamic allocation
    uint16_t n = (base.l * data_number - 1)/8 + 1; // Number of byte needed
    d.data_array = malloc( n * sizeof(uint8_t) );

    // Verification of dynamic allocation
    if (d.data_array == NULL)
    {
         fprintf(stderr,"ERROR : data_generate : Dynamic allocation not possible (data_array)\n");
         exit(EXIT_FAILURE);
    }

    //Sets initial values
    for(uint16_t i = 0; i < n; i++)
        d.data_array[i] = 0;

    return d;
}

void data_free(struct Data* d)
{
    free(d->data_array);
    //free(d);
}

uint8_t data_get(uint16_t n, struct Data* d) //Returns the n-th data stored. Starting from 0.
{
    if(n < d->data_number)
    {
        uint8_t l = d->data_base.l;

        /*
        If log2(n) is an integer, then all the sequence is on a table, so we can make a fast get-method
        Else, we must get the bits one by one and recreate the sequence
        */

        if(l == 1 || l == 2 || l == 4 || l == 8) // Si on est dans une puissance de 2
        {
            uint16_t i = l * n;     // First bit containing the data. First bit is 0, to 7.
            uint8_t it = i % 8;     // First bit in the byte containing the data

            uint8_t data = d->data_array[i / 8];

            data <<= it;
            data >>= (8 - l);

            return data;
        }
        else
            return data_getSequence(l * n, l, d);
    }
    else
    {
        fprintf(stderr,"ERROR: Incorect data number. Function data_get (you ask %d in a array with %d elements)\n", n + 1, d->data_number);
        exit(EXIT_FAILURE);
    }
}

void data_set(uint16_t n, uint8_t data, struct Data* d) // Sets the n-th block of d to data
{
    if(n < d->data_number)
    {
        if(0 <= data && data <= d->data_base.d - 1)
        {
            uint8_t l = d->data_base.l;
            uint16_t i = l * n;     // First bit containing the data. First bit is 0, to 7.
            uint8_t it = i % 8;     // First bit in the byte containing the data

            uint8_t data1 = d->data_array[i / 8]; uint8_t data2 = d->data_array[i / 8];
            data1 >>= 8 - it; data1 <<= 8 - it;
            data2 <<= it + l; data2 >>= it + l;

            d->data_array[i / 8] = ((data) << (8 - l - it)) | (data1 | data2);
        }
        else
        {
            fprintf(stderr, "ERROR: Incorect data value. Function data_set, (you have gived the data %d)\n", data);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        fprintf(stderr, "ERROR: Incorect data number. Function data_set (you ask %d in a array with %d elements)\n", n + 1, d->data_number);
        exit(EXIT_FAILURE);
    }
}

void data_add(uint8_t data, struct Data* d)
{
    uint16_t a = (d->data_base.l * (d->data_number +1 ) - 1) / 8 + 1;
    uint16_t b = (d->data_base.l * d->data_number - 1) / 8 + 1;
    if( a > b )
    {
        d->data_array = realloc(d->data_array, a);
        d->data_number += 1;
        data_set(d->data_number-1, data, d);
    }
    else
    {
        d->data_number += 1;
        data_set(d->data_number-1, data, d);
    }
}

void data_delete(uint16_t n, struct Data* d)
{
    if (0 <= n && n < d->data_number)
    {
        uint8_t nb = d->data_number;

        for(uint16_t i = n; i < nb - 1; i++)
            data_set(i, data_get(i + 1, d), d);

        /*
            Determines wether or not it is necessary to allocate a new block of memory.
            Number of byte needed. Taken from data_generate: floor((d->data_base.l * d->data_number - 1)/8) + 1
        */
        uint16_t a = (d->data_base.l * (d->data_number - 1) - 1)/8 + 1;
        uint16_t b = d->data_base.l * d->data_number /8 + 1;
        if( a < b)
            d->data_array = realloc(d->data_array, a);
        else
            data_set(nb - 1, 0, d);
        d->data_number -= 1;
    }
    else
    {
        fprintf(stderr, "ERROR: Deleting a wrong block. Function data_delete\n");
        exit(EXIT_FAILURE);
    }
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
        printf("\n");
    }
    printf("-----------------\n\n", d->data_number);
}

/**
Peu importe la base, on peu avoir besoin de recupéré 1 seul ou plusieurs bits. On doit donc créer des fonctions pour palier a cela
NB : Cela permet par ailleurs de regler le problème des base**/

uint8_t data_getBit(uint16_t n, struct Data * d)
{
    if(n < d->data_number)
    {
        uint8_t data = d->data_array[n / 8];

        data <<= (n % 8);
        data >>= 7;

        return data;
    }
    else
    {
        fprintf(stderr,"ERROR: Incorect data number. Function data_getBit (you ask %d in a array with %d elements)\n", n + 1, d->data_number);
        exit(EXIT_FAILURE);
    }
}

uint8_t data_getSequence(uint16_t n, uint8_t l, struct Data * d) // Get a sequence l long begin in n (l <= 8)
{
    if(n + l < d->data_number)
    {
        uint8_t result = 0;
        for(uint8_t i = 0; i < l; i++)
        {
            result <<= 1;
            result |= data_getBit(n + i, d);
        }

        return result;
    }
    else
    {
        fprintf(stderr,"ERROR: Incorect data number. Function data_getSequence (you ask %d in a array with %d elements)\n", n + 1 + l, d->data_number);
        exit(EXIT_FAILURE);
    }
}

void data_setBit(uint16_t n, uint8_t data, struct Data * d)
{
    if(n < d->data_number)
    {
        if(0 <= data && data <= 1)
        {
            uint8_t it = n % 8;     // First bit in the byte containing the data
            uint8_t data1 = d->data_array[n / 8]; uint8_t data2 = d->data_array[n / 8];

            data1 >>= 8 - it; data1 <<= 8 - it;
            data2 <<= it + 1; data2 >>= it + 1;

            d->data_array[n / 8] = ((data) << (7 - it)) | (data1 | data2);
        }
        else
        {
            fprintf(stderr, "ERROR: Incorect data value. Function data_setBit, (you have gived the data %d)\n", data);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        fprintf(stderr,"ERROR: Incorect data number. Function data_setBit (you ask %d in a array with %d elements)\n", n + 1, d->data_number);
        exit(EXIT_FAILURE);
    }
}

void data_setSequence(uint16_t n, uint8_t l, uint8_t data, struct Data * d) // Get a sequence l long begin in n (l <= 8)
{
    if(n + l < d->data_number)
    {
        if(0 <= data && data <= d->data_base.d - 1)
        {
            uint8_t l = d->data_base.l;
            uint16_t i = l * n;     // First bit containing the data. First bit is 0, to 7.
            uint8_t it = i % 8;     // First bit in the byte containing the data

            uint8_t data1 = d->data_array[i / 8]; uint8_t data2 = d->data_array[i / 8];
            data1 >>= 8 - it; data1 <<= 8 - it;
            data2 <<= it + l; data2 >>= it + l;

            d->data_array[i / 8] = ((data) << (8 - l - it)) | (data1 | data2);
        }
    }
    else
    {
        fprintf(stderr,"ERROR: Incorect data number. Function data_getSequence (you ask %d in a array with %d elements)\n", n + 1 + l, d->data_number);
        exit(EXIT_FAILURE);
    }
}
