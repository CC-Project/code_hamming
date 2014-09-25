#include "matrix.h"

struct Matrix new_matrix(int rows, int cols)
{
	struct Matrix m;
	m.rows = rows;
	m.cols = cols;

    unsigned char t2[rows][cols];
    m.t = t2;
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
    free(m->t);
}

/*
- Multiplication de matrices (les matrices sont des matrices de binaire, fait gaffe)
- Addition de matrices
- Soustraction de matrices
*/
