struct Matrix
{
	unsigned short int rows;
	unsigned short int cols;
	struct Data data;
};

struct Matrix new_matrix(int rows, int cols);
void show_matrix(struct Matrix *m);
void void_matrix(struct Matrix *m);
void del_matrix(struct Matrix *m);

struct Matrix mul_matrix(struct Matrix *a, struct Matrix *b);
struct Matrix add_matrix(struct Matrix *a, struct Matrix *b);
