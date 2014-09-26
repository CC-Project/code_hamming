#include "matrix.h"

struct Matrix new_matrix(int rows, int cols)
{
	struct Matrix m;
	m.rows = rows;
	m.cols = cols;

    m.t = malloc(sizeof(char *) * rows);
    for(int i = 0; i<rows; i++)
    {
        m.t[i] = malloc(sizeof(char) * cols);
    }
    void_matrix(&m);
	return m;
}

void show_matrix(struct Matrix * m)
{
    for(int i = 0; i < m->rows; i++)
    {
        for(int j = 0; j < m->cols; j++)
        {
            printf("%d ", m->t[i][j]);
        }
        printf("\n");
    }
}

void void_matrix(struct Matrix * m)
{
    for(int i = 0; i < m->rows; i++)
    {
        for(int j = 0; j < m->cols; j++)
        {
            m->t[i][j] = 0;
        }
    }
}


void del_matrix(struct Matrix *m)
{
    for(int i = 0; i< m->cols; i++)
    {
        free(m->t[i]);
    }
    free(m->t);
}

struct Matrix mul_matrix(struct Matrix *a, struct Matrix *b)
{
    struct Matrix m = new_matrix(a->rows, b->cols);
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

struct Matrix add_matrix(struct Matrix *a, struct Matrix *b)
{
    struct Matrix m = new_matrix(a->rows, b->cols);
    for(int i = 0; i < m.rows; i++)
    {
        for(int j = 0; j < m.cols; j++)
        {
            m.t[i][j] = a->t[i][j] ^ b->t[i][j];
        }
    }
    return m;
}
