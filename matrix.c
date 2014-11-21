#include "matrix.h"

struct Matrix matrix_generate(uint16_t n, uint16_t p, struct Base base)
{
	struct Matrix m;
	m.rows = n;
	m.cols = p;

    m.data = data_generate(base, n*p);
	return m;
}

void matrix_free(struct Matrix* m)
{
    data_free(&(m->data));
    free(m);
}

void matrix_show(struct Matrix* m)
{
    uint16_t i = 0;
    uint16_t j = 0;
    printf("------------------\nMatrice de taille (%d, %d)\n", m->rows, m->cols);
    for(i = 0; i < m->data.data_number; i++)
    {
        j+=1;
        uint8_t data = data_get(i, &(m->data));

        for(int8_t j = m->data.data_base.l - 1; j >= 0; j--)
            printf("%d", (data & (1 << j)) >> j);

        printf(" ");
        //printf("%d ", data_get(i, &(m->data)));
        if (j == m->cols) {printf("\n"); j = 0;}
    }
    printf("\n");
}

void matrix_show_word(struct Matrix * m)
{
    struct Matrix tm = matrix_transpose(m);
    matrix_show(&tm);
}

void matrix_void(struct Matrix * m)
{
    uint16_t n = floor((m->data.data_base.l * m->data.data_number-1)/8) + 1; //Number of byte
    uint16_t i = 0;
    for(i=0; i<n; i++) //For each byte
        m->data.data_array[i] = 0;
}
uint8_t matrix_isempty(struct Matrix* m)
{
    uint16_t n = floor((m->data.data_base.l * m->data.data_number-1)/8) + 1; //Number of byte
    uint16_t i = 0;
    do{
        if (m->data.data_array[i] != 0)
            return 0;
        i+=1;
    } while (i < n); //For each byte
    return 1;
}

void matrix_set(struct Matrix* m, uint16_t i, uint16_t j, uint8_t val) //Sets the i-th line, j-th column of m to val
{
    data_set(matrix_get_data_number(i, j, m), val, &(m->data));
}

 uint8_t matrix_get(struct Matrix* m, uint16_t i, uint16_t j) //Gets the i-th line, j-th column of m
 {
     return data_get(matrix_get_data_number(i, j, m), &(m->data));
 }

struct Matrix matrix_mul(struct Matrix *a, struct Matrix *b)
{
    if(a->cols == b->rows)
    {
        struct Matrix m = matrix_generate(a->rows, b->cols, a->data.data_base);

        // Pour la base 2
        if (a->data.data_base.d == 2)
            for(uint16_t i = 1; i <= m.rows; i++)
                for(uint16_t j = 1; j <= m.cols; j++)
                    for (uint16_t k = 1; k <= a->cols; k++)
                        matrix_set(&m, i, j, matrix_get(&m, i, j) ^ (matrix_get(a, i, k) & matrix_get(b, k, j)));

        return m;
    }
    else
        printf("Erreur : matric_mul : Les tailles des matrices sont incompatibles");
}

struct Matrix matrix_add(struct Matrix *a, struct Matrix *b)
{
    struct Matrix m = matrix_generate(a->rows, b->cols, a->data.data_base);

    if (a->data.data_base.d == 2)
        for(uint16_t i = 1; i <= m.rows; i++)
            for(uint16_t j = 1; j <= m.cols; j++)
                matrix_set(&m, i, j, (matrix_get(a, i, j) ^ matrix_get(b, i, j)));

    return m;
}

void matrix_make_identity(struct Matrix* m) // Return I_k
{
    uint16_t i = 0;
    for(i = 1; i <= m->cols; i++)
        matrix_set(m, i, i, 1);
}

void matrix_make_jidentity(struct Matrix* m) // Return J_k
{
    uint16_t i = 0;
    for(i = 1; i <= m->cols; i++)
        matrix_set(m, i, m->cols - i + 1, 1);
}

void matrix_del_col(uint16_t j, struct Matrix* m)
{
    for(uint16_t i = 1; i <= m->rows; i++)
        data_delete(matrix_get_data_number(i, j, m) - (i - 1), &(m->data));
        // On fait un - (i - 1) pour compenser le décalage du a la supression des données

    m->cols -= 1;
}

void matrix_del_line(uint16_t i, struct Matrix* m)
{
    for(uint16_t j = 1; j <= m->cols; j++)
        data_delete(matrix_get_data_number(i, j, m) - (j - 1), &(m->data));
        // On fait un - (j - 1) pour compenser le décalage du a la supression des données

    m->rows -= 1;
}

uint16_t matrix_get_data_number(uint16_t i, uint16_t j, struct Matrix* m)
{
    return (i-1) * m->cols + j-1;
}

struct Matrix matrix_collapse_down(struct Matrix *a, struct Matrix *b)
{
    struct Matrix m = matrix_generate(a->rows + b->rows, a->cols, a->data.data_base);

    for(uint16_t i = 0; i < m.data.data_number; i++)
        if(i < a->data.data_number)
            data_set(i, data_get(i, &(a->data)), &(m.data));
        else
            data_set(i, data_get(i - a->data.data_number, &(b->data)), &(m.data));

    return m;
}

struct Matrix matrix_collapse_right(struct Matrix *a, struct Matrix *b)
{
    if(a->rows == b->rows)
    {
        struct Matrix m = matrix_generate(a->rows, a->cols + b->cols, a->data.data_base);

        for(uint16_t i = 1; i <= a->rows; i++)
            for(uint16_t j = 1; j <= a->cols; j++)
                matrix_set(&m, i, j, matrix_get(a, i, j));

        for(uint16_t i = 1; i <= b->rows; i++)
            for(uint16_t j = 1; j <= b->cols; j++)
                matrix_set(&m, i, j + a->cols, matrix_get(b, i, j));

        return m;
    }
    else
        printf("Error : You can only collapse right two matrix with the same rows number. matrix_collapse_right");
}

struct Matrix matrix_copy(struct Matrix *a)
{
    struct Matrix m = matrix_generate(a->rows, a->cols, a->data.data_base);

    for(uint16_t i = 1; i <= a->rows; i++)
        for(uint16_t j = 1; j <= a->cols; j++)
            matrix_set(&m, i, j, matrix_get(a, i,j));

    return m;
}

void matrix_reverse(struct Matrix *a) // Renvoi la matrice opposé
{
    for(uint16_t i = 1; i <= a->rows; i++)
        for(uint16_t j = 1; j <= a->cols; j++)
        {
            uint8_t data = ~(matrix_get(a, i, j)) << (8 - a->data.data_base.l);
            matrix_set(a, i,j, data >> (8 - a->data.data_base.l));
        }
}

void matrix_exchange_cols(uint16_t j1, uint16_t j2, struct Matrix * m)
{
    uint8_t temp;
    for (uint16_t i = 1; i <= m->rows; i++)
    {
        temp = matrix_get(&m, i, j1);
        matrix_set(&m, i, j1, matrix_get(&m, i, j2));
        matrix_set(&m, i, j2, temp);
    }
}
void matrix_exchange_lines(uint16_t i1, uint16_t i2, struct Matrix * m)
{
    uint8_t temp;
    for (uint16_t j = 1; j <= m->cols; j++)
    {
        temp = matrix_get(&m, j, i1);
        matrix_set(&m, j, i1, matrix_get(&m, j, i2));
        matrix_set(&m, j, i2, temp);
    }
}

struct Matrix matrix_transpose(struct Matrix * m)
{
    struct Matrix m2 = matrix_generate(m->cols, m->rows, m->data.data_base);

    for(uint16_t i = 1; i <= m2.rows; i++)
        for(uint16_t j = 1; j <= m2.cols; j++)
            matrix_set(&m, i, j, matrix_get(m, j, i));

    return m2;
}

struct Matrix matrix_pow(struct Matrix * m, uint8_t n)
{
    if(m->cols == m->rows)
    {
        struct Matrix m_pow = matrix_copy(m);
        for(uint8_t i = 2; i <= n; i++)
            m_pow = matrix_mul(&m_pow, &m_pow);

        return m_pow;
    }
    else
        printf("Erreur : matrix_pow : La matrice passe en argument n'est pas carre");
}

uint8_t matrix_word_to_int(struct Matrix * m)
{

}
