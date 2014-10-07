#ifndef MATRIX_H
    #define MATRIX_H
    #include <inttypes.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include "data.h"

    struct Matrix
    {
        uint8_t rows;
        uint8_t cols;
        struct Data data;
    };

    struct Matrix matrix_generate(uint16_t n, uint16_t p, struct Base base);
    void matrix_free(struct Matrix* m);
    void matrix_show(struct Matrix* m);
    void matrix_void(struct Matrix* m);
    uint8_t matrix_isempty(struct Matrix* m);
    void matrix_set(struct Matrix* m, uint16_t i, uint16_t j, uint8_t val); //Sets the i-th line, j-th column of m to val
    uint8_t matrix_get(struct Matrix* m, uint16_t i, uint16_t j); //Gets the i-th line, j-th column of m

    void matrix_del_line(uint16_t i, struct Matrix* m);
    void matrix_del_col(uint16_t j, struct Matrix* m);

    uint16_t matrix_get_data_number(uint16_t i, uint16_t j, struct Matrix* m); // Return the number of the (i,j) data

    struct Matrix matrix_mul(struct Matrix* a, struct Matrix* b);
    struct Matrix matrix_add(struct Matrix* a, struct Matrix* b);
    struct Matrix matrix_collapse_down(struct Matrix *a, struct Matrix *b); // Collapse two matrix
    void matrix_make_identity(struct Matrix* m);

#endif // MATRIX_H
