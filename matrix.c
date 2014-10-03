#include "matrix.h"

struct Matrix matrix_generate(uint16_t n, uint16_t p, struct Base base)
{
	struct Matrix m;
	m.rows = n;
	m.cols = p;

    m.data = data_generate(base, n*p);
	return m;
}

void matrix_delete(struct Matrix *m)
{
    free(&(m->data));
    free(m);
}

#ifdef DEBUG
void matrix_show(struct Matrix* m)
{
    uint8_t i = 0;
    uint8_t j = 0;
    uint8_t k = 0;
    for(i = 0; i < m->rows; i++)
    {
        for(j = 0; j < m->cols; j++)
        {
            printf("%d ", data_get(j+k, &(m->data));
        }
        printf("\n");
        k+=8;
    }
}
#endif

/*

void matrix_void(struct Matrix * m)
{
    for(int i = 0; i < m->rows; i++)
    {
        for(int j = 0; j < m->cols; j++)
        {
            m->t[i][j] = 0;
        }
    }
}

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

struct Matrix matrix_generate_identity(uint8_t k) // Genère la matrice identité de M_k
{
    struct Matrix id = matrix_generate(k, k);

    if(matrix_set_value(0,0, id) != 0)
        matrix_void_matrix(&id);

    for(int i = 0; i < k; i++)
        matrix_set_value(i, i, 1, &id);

    return id;
}
*/
