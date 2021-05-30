#include "BasicAlgorithm.h"

#include <iostream>
#include <omp.h>
#include "MatrixBuilder.h"

using namespace std;

short **BasicAlgorithm::multiply(short **firstMatrix, short **secondMatrix, int order)
{

	short **resultMatrix = createEmptyMatrix(order);

	for (short i = 0; i < order; i++)
	{
		for (short j = 0; j < order; j++)
		{
			for (short k = 0; k < order; k++)
			{
				resultMatrix[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
			}
		}
	}

	return resultMatrix;
};

/*short ** BasicAlgorithm::multiply(short **firstMatrix, short **secondMatrix, int order)
{
	short **resultMatrix = createEmptyMatrix(order);
	short i = 0;
	short j = 0;
	short k = 0;

	#pragma omp parallel for private(i, j, k)
	for (i = 0; i < order; i++)
	{
		for (j = 0; j < order; j++)
		{
			for (k = 0; k < order; k++)
			{
				resultMatrix[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
			}
		}
	}

	return resultMatrix;
};*/