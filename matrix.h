struct Matrix
{
	unsigned short int rows;
	unsigned short int cols;
	struct Data data;
};

struct Matrix matrix_generate(int rows, int cols);
void matrix_show(struct Matrix *m);
void matrix_void(struct Matrix *m);
void matrix_del(struct Matrix *m);

struct Matrix matrix_mul(struct Matrix *a, struct Matrix *b);
struct Matrix matrix_add(struct Matrix *a, struct Matrix *b);
