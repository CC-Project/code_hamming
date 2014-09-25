#include <stdio.h>
#include <stdlib.h>

struct Matrix
{
	unsigned short int rows;
	unsigned short int cols;
	unsigned char *t; // On travaille avec des 0 et des 1, on prendra donc des char car ils ne prennent que 1 octets en mémoire
};

struct Matrix new_matrix(int rows, int cols);
void show_matrix(struct Matrix *m);
void void_matrix(struct Matrix *m);
void del_matrix(struct Matrix *m);
