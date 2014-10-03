#ifndef MATRIX_H
    #define MATRIX_H
    #include <inttypes.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include "data.h"

    struct Matrix
    {
        uint8_t rows;
        uint8_t cols;
        struct Data data;
    };

    struct Matrix matrix_generate(uint16_t n, uint16_t p, struct Base base);
    void matrix_delete(struct Matrix* m);
    void matrix_void(struct Matrix* m);
    #ifdef DEBUG
    void matrix_show(struct Matrix *m);
    #endif

    struct Matrix matrix_mul(struct Matrix* a, struct Matrix* b);
    struct Matrix matrix_add(struct Matrix* a, struct Matrix* b);

#endif // MATRIX_H
