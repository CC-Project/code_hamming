/**
 Contains unused func
**/

//Data
void data_add(uint8_t data, struct Data* d);                // Add a block of data at the end of d
void data_add(uint8_t data, struct Data* d)
{
    uint16_t a = (BASE_L * (d->data_number +1 ) - 1) / 8 + 1;
    uint16_t b = (BASE_L * d->data_number - 1) / 8 + 1;

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



//Matrix
void matrix_opposite(struct Matrix *a);       // Returns the opposite matrix (Replace 0 by 1)
void matrix_make_jidentity(struct Matrix* m);   // Returns J_k
void matrix_void(struct Matrix* m);             // Voids a matrix i.e sets all data to 0.
struct Matrix* matrix_add(struct Matrix* a, struct Matrix* b);               // Adds two matrix
struct Matrix* matrix_pow(struct Matrix * m, uint8_t n);                     // Returns M^n
void matrix_del_row(uint16_t i, struct Matrix* m);  // Removes the i-th row of m. Thus the format is changed
void matrix_exchange_rows(uint16_t i1, uint16_t i2, struct Matrix * m);
void matrix_exchange_cols(uint16_t j1, uint16_t j2, struct Matrix * m);

void matrix_opposite(struct Matrix *a)
{
    for(uint16_t i = 1; i <= a->rows; i++)
        for(uint16_t j = 1; j <= a->cols; j++)
        {
            uint8_t data = ~(matrix_get(a, i, j)) << (8 - BASE_L);
            matrix_set(a, i,j, data >> (8 - BASE_L));
        }
}

void matrix_make_jidentity(struct Matrix* m)
{
    uint16_t i = 0;
    for(i = 1; i <= m->cols; i++)
        matrix_set(m, i, m->cols - i + 1, 1);
}

void matrix_void(struct Matrix * m)
{
    uint16_t n = floor((BASE_L * m->data->data_number-1)/8) + 1; //Number of byte
    uint16_t i = 0;
    for(i=0; i<n; i++) //For each byte
        m->data->data_array[i] = 0;
}

struct Matrix* matrix_add(struct Matrix *a, struct Matrix *b)
{
    struct Matrix* m = matrix_generate(a->rows, b->cols);

    if (BASE_D == 2)
        for(uint16_t i = 1; i <= m->rows; i++)
            for(uint16_t j = 1; j <= m->cols; j++)
                matrix_set(m, i, j, (matrix_get(a, i, j) ^ matrix_get(b, i, j)));

    return m;
}

struct Matrix* matrix_pow(struct Matrix * m, uint8_t n)
{
    if(m->cols != m->rows)
        error("ERROR : matrix_pow : The array passed as an argument is not square");

    struct Matrix* m_pow = matrix_copy(m);
    for(uint8_t i = 2; i <= n; i++)
        m_pow = matrix_mul(m_pow, m_pow);

    return m_pow;
}

void matrix_del_row(uint16_t i, struct Matrix* m)
{
    for(uint16_t j = 1; j <= m->cols; j++)
        data_delete(matrix_get_data_number(i, j, m) - (j - 1), m->data);
        // On fait un - (j - 1) pour compenser le décalage du a la supression des données

    m->rows -= 1;
}

void matrix_exchange_rows(uint16_t i1, uint16_t i2, struct Matrix * m)
{
    uint8_t temp;
    for (uint16_t j = 1; j <= m->cols; j++)
    {
        temp = matrix_get(m, j, i1);
        matrix_set(m, j, i1, matrix_get(m, j, i2));
        matrix_set(m, j, i2, temp);
    }
}

void matrix_exchange_cols(uint16_t j1, uint16_t j2, struct Matrix * m)
{
    uint8_t temp;
    for (uint16_t i = 1; i <= m->rows; i++)
    {
        temp = matrix_get(m, i, j1);
        matrix_set(m, i, j1, matrix_get(m, i, j2));
        matrix_set(m, i, j2, temp);
    }
}
