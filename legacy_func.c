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

// Data generation/free
struct Data* data_generate(uint16_t data_number)
{
    //Allocates memory for the struct
    struct Data* d = malloc(sizeof(struct Data));
    if (d == NULL)
         error("ERROR : data_generate : Dynamic allocation not possible for the data structure");

    //Allocates memory for the array
    uint16_t n = (BASE_L * data_number - 1)/8 + 1; // Number of byte needed
    d->data_array = calloc(n,sizeof(uint8_t)); //Automatically sets the bits to zero
    if (d->data_array == NULL)
         error("ERROR : data_generate : Dynamic allocation not possible for the array");

    //Sets the data_number field
    d->data_number = data_number;

    return d;
}

void data_free(struct Data* d)
{
    free(d->data_array);
    free(d);
}



// Data operations
uint8_t data_get(uint16_t n, struct Data* d)
{
    if(n < d->data_number)
    {
        /*
            If log2(n) is an integer, then all the sequence is on a table, so we can make a fast get-method
            Else, we must get the bits one by one and recreate the sequence
        */

        if(BASE_L == 1 || BASE_L == 2 || BASE_L == 4 || BASE_L == 8) // If a power of 2.
        {
            uint16_t i = BASE_L * n;     // First bit containing the data. First bit is 0, to 7.
            uint8_t it = i % 8;     // First bit in the byte containing the data

            uint8_t data = d->data_array[i / 8];

            data <<= it;
            data >>= (8 - BASE_L);

            return data;
        }
        else
            return data_getSequence(BASE_L * n, BASE_L, d);
    }
    else
        error("ERROR: Incorect data number. Function data_get");
    return EXIT_FAILURE;
}

void data_set(uint16_t n, uint8_t data, struct Data* d)
{
    if(n < d->data_number)
    {
        if(BASE_L == 1 || BASE_L == 2 || BASE_L == 4 || BASE_L == 8) // If it is a power of 2
        {
            if(0 <= data && data <= BASE_D - 1)
            {
                uint16_t i = BASE_L * n;    // First bit containing the data. First bit is 0, to 7.
                uint8_t it = i % 8;         // First bit in the byte containing the data

                uint8_t data1 = d->data_array[i / 8]; uint8_t data2 = d->data_array[i / 8];
                data1 >>= 8 - it; data1 <<= 8 - it;
                data2 <<= it + BASE_L; data2 >>= it + BASE_L;

                d->data_array[i / 8] = ((data) << (8 - BASE_L - it)) | (data1 | data2);
            }
            else
                error("ERROR: Incorect data value. Function data_set");
        }
        else
            data_setSequence(BASE_L * n, BASE_L, data, d);
    }
    else
        error("ERROR: Incorect data number. Function data_set.");
}

void data_delete(uint16_t n, struct Data* d)
{
    if (0 <= n && n < d->data_number)
    {
        for(uint16_t i = n; i < d->data_number - 1; i++)
            data_set(i, data_get(i + 1, d), d);

        /*
            Determines wether or not it is necessary to allocate a new block of memory.
            Number of byte needed. Taken from data_generate: floor((d->data_base.l * d->data_number - 1)/8) + 1
        */
        uint16_t a = (BASE_L * (d->data_number - 1) - 1)/8 + 1;
        uint16_t b = (BASE_L * (d->data_number / 8)) + 1;

        if(a < b)
            d->data_array = realloc(d->data_array, a);
        else
            data_set(d->data_number - 1, 0, d);

        d->data_number -= 1;
    }
    else
        error("ERROR: Deleting a wrong block. Function data_delete.");
}




uint8_t data_getBit(uint16_t n, struct Data* d)
{
    if(n <= d->data_number * BASE_L)
    {
        uint8_t data = d->data_array[n / 8];

        data <<= (n % 8);
        data >>= 7;

        return data;
    }
    else
        return error("ERROR: Incorect data number. Function data_getBit.");
    return EXIT_FAILURE;
}

uint8_t data_getSequence(uint16_t n, uint8_t l, struct Data* d)
{
    if(n + (l - 1) < d->data_number * BASE_L)
    {
        uint8_t result = 0;
        for(uint8_t i = 0; i < l; i++)
        {
            result <<= 1;
            result |= data_getBit(n + i, d);
        }

        return result;
    }
    else
        error("ERROR: Incorect data number. Function data_getSequence.");
    return EXIT_FAILURE;
}

void data_setBit(uint16_t n, uint8_t data, struct Data* d)
{
    if(n < d->data_number * BASE_L)
    {
        if(0 <= data && data <= 1)
        {
            uint8_t it = n % 8;     // First bit in the byte containing the data
            uint8_t data1 = d->data_array[n / 8]; uint8_t data2 = d->data_array[n / 8];

            data1 >>= 8 - it; data1 <<= 8 - it;
            data2 <<= it + 1; data2 >>= it + 1;

            d->data_array[n / 8] = ((data) << (7 - it)) | (data1 | data2);
        }
        else
            error("ERROR: Incorect data value. Function data_setBit.");
    }
    else
        error("ERROR: Incorect data number. Function data_setBit.");
}

void data_setSequence(uint16_t n, uint8_t l, uint8_t data, struct Data* d)
{
    if(n + (l - 1) < d->data_number * BASE_L)
    {
        if(0 <= data && data <= BASE_D - 1)
        {
            //Put the sequence to replace in a data
            struct Data * dBis = data_generate(1);
            dBis->data_array[0] = data;

            for(uint8_t i = 0; i < l; i++)
                data_setBit((n + (l - 1)) - i, data_getBit((8 - 1) - i, dBis), d);

            data_free(dBis);
        }
        else
            error("ERROR: Incorect data value. Function data_setSequence.");
    }
    else
        error("ERROR: Incorect data number. Function data_setSequence.");
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
