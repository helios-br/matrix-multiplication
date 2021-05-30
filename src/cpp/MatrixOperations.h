#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "MatrixBuilder.h"

inline short **add(short **firstMatrix, short **secondMatrix, int order)
{
	short **resultMatrix = createEmptyMatrix(order);

	for (short i = 0; i < order; i++)
		for (short j = 0; j < order; j++)
			resultMatrix[i][j] = firstMatrix[i][j] + secondMatrix[i][j];

	return resultMatrix;
}

inline short **subtract(short **firstMatrix, short **secondMatrix, int order)
{
	short **resultMatrix = createEmptyMatrix(order);

	for (short i = 0; i < order; i++)
		for (short j = 0; j < order; j++)
			resultMatrix[i][j] = firstMatrix[i][j] - secondMatrix[i][j];

	return resultMatrix;
}

#endif