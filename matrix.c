#include "matrix.h"

struct Matrix matrix_generate(uint16_t n, uint16_t p, struct Base base)
{
	struct Matrix m;
	m.rows = n;
	m.cols = p;

    m.data = data_generate(base, n*p);
	return m;
}

void matrix_delete(struct Matrix* m)
{
    free(&(m->data));
    free(m);
}

void matrix_show(struct Matrix* m)
{
    uint8_t i = 0;
    uint8_t j = 0;
    for(i = 0; i < m->data.data_number; i++)
    {
        j+=1;
            printf("%d ", data_get(i, &(m->data)));
        if (j == m->cols) {printf("\n"); j = 0;}
    }
    printf("\n");
}

void matrix_void(struct Matrix * m)
{
    uint16_t n = floor((m->data.data_base.l * m->data.data_number-1)/8) + 1; //Number of byte
    uint16_t i = 0;
    for(i=0; i<n; i++) //For each byte
        m->data.data_array[i] = 0;
}

void matrix_set_value(struct Matrix* m, uint16_t i, uint16_t j, uint8_t val) //Sets the i-th line, j-th column of m to val
{
    data_set(, val, &(m->data));
}
/*
struct Matrix matrix_mul(struct Matrix *a, struct Matrix *b)
{
    struct Matrix m = matrix_generate(a->rows, b->cols);
    for(int i = 0; i < m.rows; i++)
    {
        for(int j = 0; j < m.cols; j++)
        {
            for (int k = 0; k < a->cols; k++)
            {
                m.t[i][j] ^= a->t[i][k] * b->t[k][j];
            }
        }
    }
    return m;
}

struct Matrix matrix_add(struct Matrix *a, struct Matrix *b)
{
    struct Matrix m = matrix_generate(a->rows, b->cols);
    for(int i = 0; i < m.rows; i++)
    {
        for(int j = 0; j < m.cols; j++)
        {
            m.t[i][j] = a->t[i][j] ^ b->t[i][j];
        }
    }
    return m;
}
*/

struct Matrix matrix_generate_identity(uint16_t k, struct Base base)
{
    struct Matrix id = matrix_generate(k, k, base);

    uint16_t i = 0;
    for(i = 1; i <= k; i++)
        matrix_set_value(&id, i, i, 1);

    return id;
}


