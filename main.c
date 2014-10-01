#include "matrix.h"
int main()
{
    struct Matrix m1 = new_matrix(5,1);
    struct Matrix m2 = new_matrix(1,5);

    m1.t[0][0] = 1; m1.t[2][0] = 1; m1.t[3][0] = 1;
    m2.t[0][1] = 1; m2.t[0][0] = 1; m2.t[0][3] = 1;

    struct Matrix m3 = add_matrix(&m2, &m1);

    show_matrix(&m1);
    printf("+\n");
    show_matrix(&m2);
    printf("=\n");
    show_matrix(&m3);
    del_matrix(&m1);
    del_matrix(&m2);
    del_matrix(&m3);
    return 0;
}
