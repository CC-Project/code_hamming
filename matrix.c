struct Matrix matrix_generate(uint16_t rows, uint16_t cols)
{
	struct Matrix m;
	m.rows = rows;
	m.cols = cols;

    m.t = malloc(sizeof(char *) * rows);
    for(int i = 0; i<rows; i++)
    {
        m.t[i] = malloc(sizeof(char) * cols);
    }
    matrix_void(&m);
	return m;
}

void matrix_show(struct Matrix * m)
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

void matrix_del(struct Matrix *m)
{
    for(int i = 0; i< m->cols; i++)
    {
        free(m->t[i]);
    }
    free(m->t);
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
