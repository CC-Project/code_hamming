#include "matrix.h"

// Generation and deletion
struct Matrix* matrix_generate(uint16_t n, uint16_t p)
{
	struct Matrix* m = malloc(sizeof(struct Matrix));
	m->rows = n;
	m->cols = p;
    m->data = data_generate(n * p);
	return m;
}

void matrix_free(struct Matrix* m)
{
    data_free(m->data);
    free(m);
}

struct Matrix* matrix_transpose(struct Matrix * m)
{
    struct Matrix* m2 = matrix_generate(m->cols, m->rows);

    for(uint16_t i = 1; i <= m2->rows; i++)
        for(uint16_t j = 1; j <= m2->cols; j++)
            matrix_set(m2, i, j, matrix_get(m, j, i));

    return m2;
}

uint8_t matrix_is_null(struct Matrix* m)
{
    uint16_t n = m->data->data_number / 8; //Number of byte, i.e of cells in the array.
    uint16_t i = 0;

    do
    {
        if (m->data->data_array[i] != 0)
            return 0;
        i++;
    } while (i < n); //For each byte

    return 1;
}

void matrix_make_identity(struct Matrix* m)
{
    uint16_t i = 0;
    for(i = 1; i <= m->cols; i++)
        matrix_set(m, i, i, 1);
}

// Matrix's data manipulations
void matrix_set(struct Matrix* m, uint16_t i, uint16_t j, uint8_t val) //Sets the i-th line, j-th column of m to val
{
    if(i <= m->rows && j <= m->cols)
        data_set(DATA_NUMBER(i, j, m), val, m->data);
    else
    {
        #ifdef DEBUG
            error("ERROR : matrix_set : Incorect matrix size.");
        #endif // DEBUG
        #ifdef __AVR__
            while(1){}
        #else
            system("PAUSE>NUL");
            exit(EXIT_FAILURE);
        #endif
    }
}

uint8_t matrix_get(struct Matrix* m, uint16_t i, uint16_t j) //Gets the i-th line, j-th column of m
{
    if(i <= m->rows && j <= m->cols)
        return data_get(DATA_NUMBER(i, j, m), m->data);
    else
    {
        #ifdef DEBUG
            error("ERROR : matrix_get : Incorect matrix size.");
        #endif // DEBUG
        #ifdef __AVR__
            while(1){}
        #else
            system("PAUSE>NUL");
            exit(EXIT_FAILURE);
        #endif
    }

    return -1;
}

struct Matrix* matrix_copy(struct Matrix *a)
{
    struct Matrix* m = matrix_generate(a->rows, a->cols);

    for(uint16_t i = 1; i <= a->rows; i++)
        for(uint16_t j = 1; j <= a->cols; j++)
            matrix_set(m, i, j, matrix_get(a, i,j));

    return m;
}

// Operations on matrix
struct Matrix* matrix_mul(struct Matrix *a, struct Matrix *b)
{
    if(a->cols != b->rows)
    {
        #ifdef DEBUG
            error("ERROR : matrix_mul : The sizes of matrix are not compatible");
        #endif // DEBUG
        #ifdef __AVR__
            while(1){}
        #else
            system("PAUSE>NUL");
            exit(EXIT_FAILURE);
        #endif
    }

    struct Matrix* m = matrix_generate(a->rows, b->cols);

    for(uint16_t i = 1; i <= m->rows; i++)
        for(uint16_t j = 1; j <= m->cols; j++)
            for (uint16_t k = 1; k <= a->cols; k++)
                matrix_set(m, i, j, matrix_get(m, i, j) ^ (matrix_get(a, i, k) & matrix_get(b, k, j)));

    return m;
}

struct Matrix* matrix_concat_down(struct Matrix* a, struct Matrix* b)
{
    struct Matrix* m = matrix_generate(a->rows + b->rows, a->cols);

    for(uint16_t i = 0; i < m->data->data_number; i++)
        if(i < a->data->data_number)
            data_set(i, data_get(i, a->data), m->data);
        else
            data_set(i, data_get(i - a->data->data_number, b->data), m->data);

    return m;
}

struct Matrix* matrix_concat_right(struct Matrix *a, struct Matrix *b)
{
    if(a->rows != b->rows)
    {
        #ifdef DEBUG
            error("ERROR : matrix_collapse_right : You can only collapse right two matrix with the same rows number.");
        #endif // DEBUG
        #ifdef __AVR__
            while(1){}
        #else
            system("PAUSE>NUL");
            exit(EXIT_FAILURE);
        #endif
    }

    struct Matrix* m = matrix_generate(a->rows, a->cols + b->cols);

    for(uint16_t i = 1; i <= a->rows; i++)
        for(uint16_t j = 1; j <= a->cols; j++)
            matrix_set(m, i, j, matrix_get(a, i, j));

    for(uint16_t i = 1; i <= b->rows; i++)
        for(uint16_t j = 1; j <= b->cols; j++)
            matrix_set(m, i, j + a->cols, matrix_get(b, i, j));

    return m;
}


// Misc
void matrix_del_col(uint16_t j, struct Matrix* m)
{
    for(uint16_t i = 1; i <= m->rows; i++)
        data_delete(DATA_NUMBER(i, j, m) - (i - 1), m->data); // (i - 1) -> Complete the shift due to the removal of the previous datas.

    m->cols -= 1;
}

uint16_t matrix_word_to_int(struct Matrix * m)
{
    uint16_t val = 0;
    for(uint16_t i = 0; i < m->data->data_number; i++)
        if (data_get(i, m->data) == 1)
            val += (1 << (m->data->data_number - i - 1));


    return val;
}

struct Matrix* matrix_int_to_word(uint16_t val)
{
    uint8_t i = 0;

    while((1 << i) < val)
        i++;

    struct Matrix* result = matrix_generate(i + 1, 1);

    for(uint8_t p = 0; p < i + 1; p++)
        if(val & (1 << p))
            matrix_set(result, p + 1, 1, 1);

    return result;
}

// Utilities
#ifdef DEBUG
    void matrix_show(struct Matrix* m)
    {
        #ifdef __AVR__
            for
        #else
            printf("Size is (%d, %d)\n", m->rows, m->cols);
            uint16_t i = 0;
            uint16_t j = 0;

            for(i = 0; i < m->data->data_number; i++)
            {
                j += 1;

                uint8_t data = data_get(i, m->data);
                printf("%d", data);

                printf(" ");

                if (j == m->cols) {printf("\n"); j = 0;}
            }
            printf("\n");
        #endif
    }

    void matrix_show_word(struct Matrix * m)
    {
        struct Matrix* tm = matrix_transpose(m);
        matrix_show(tm);
        matrix_free(tm);
    }
#endif // DEBUG
