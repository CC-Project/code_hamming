#include <stdlib.h>
#include <stdio.h>
#include "hamming.h"

int main()
{
    struct Base base = base_generate(2,1);
    struct Data d = data_generate(base, 14);

    for(uint16_t j = 0; j < 20000; j++)
    {
        for(uint8_t i = 0; i < d.data_number; i++)
            data_set(i, 1, &d);

        for(uint8_t i = 0; i < d.data_number; i++)
            data_set(i, 0, &d);
    }

    data_show(&d);


    return 0;
}
