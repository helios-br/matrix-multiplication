#include "BasicAlgorithm.h"

#include <iostream>
#include <omp.h>
#include "MatrixBuilder.h"

using namespace std;

vector<vector<int>> BasicAlgorithm::multiply(vector<vector<int>> firstMatrix, vector<vector<int>> secondMatrix, int order)
{
	vector<vector<int>> resultMatrix = createEmptyMatrix(order);

	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			for (int k = 0; k < order; k++)
			{
				resultMatrix[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
			}
		}
	}

	return resultMatrix;
};

/*int ** BasicAlgorithm::multiply(int **firstMatrix, int **secondMatrix, int order)
{
	int **resultMatrix = createEmptyMatrix(order);
	int i = 0;
	int j = 0;
	int k = 0;

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