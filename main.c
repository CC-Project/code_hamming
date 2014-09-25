#include "matrix.h"

int main()
{
    struct Matrix m = new_matrix(4,4);
	//void_matrix(&m);
    show_matrix(&m);
    //del_matrix(&m);
    return 0;
}
