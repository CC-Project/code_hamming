#include "matrix.h"

struct ControlMatrix
{
	unsigned short int basis;
	struct Matrix matrix;
};

uint8_t hamming_encode(uint8_t *code);
